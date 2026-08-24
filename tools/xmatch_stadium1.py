#!/usr/bin/env python3
"""Transfer evidence-backed function names from the Pokemon Stadium 1 decomp to
Pokemon Stadium 2 (G&S) by matching the two ROMs' machine code.

The two games share a large part of their engine verbatim.  This tool slices
both ROMs into functions using each project's splat symbol table, normalises out
the parts that legitimately differ between two links of the same source
(jump/branch targets, `lui` high halves, immediates that encode absolute
addresses), and matches what is left.

Four match classes, in descending confidence:

  identical   the two bodies are the same length and every instruction is equal
              once relocation-bearing fields are masked -- the same function,
              compiled from the same source.
  normalised  a unique match on the looser signature (register fields only).
  callgraph   the Nth `jal` of an already-matched pair, corroborated by >=80%
              instruction agreement.
  aligned     both segments lay their functions out in the same order, and this
              one sits in a run of equal length between two anchors; requires
              >=50% instruction agreement.  Review these by hand.

    python3 tools/xmatch_stadium1.py --report          # summary, write nothing
    python3 tools/xmatch_stadium1.py --out tools/s1_transfer.json
    python3 tools/xmatch_stadium1.py --near-source disasm/src/fragments/26/fragment26_1646B0.c
"""
import argparse
import bisect
import collections
import json
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_S1 = "/Users/michaegg/projects/PokemonStadiumRecomp-rental"
GS_ROM_CANDIDATES = [
    os.path.join(ROOT, "disasm", "baseroms", "us", "baserom.z64"),
    os.path.join(ROOT, "build-mac", "source", "baserom.z64"),
    "/Users/michaegg/ps2-recomp-build/disasm/baseroms/us/baserom.z64",
]
S1_ROM_RELPATHS = ["pokestadium.us.1.0.z64", "baserom.z64"]

ADDRNAME = re.compile(r"^(func|D|jtbl|jlabel)_[0-9A-Fa-f]{6,8}$")


def is_named(sym):
    """True if `sym` carries meaning rather than just its address."""
    return not ADDRNAME.match(sym)


# --- splat inputs -------------------------------------------------------

def parse_segments(paths):
    """[(name, rom_start, vram)] for every top-level segment, in ROM order.

    A hand-rolled scan rather than a YAML parse: splat's segment headers are a
    fixed four-line shape and this keeps the tool dependency-free (the build
    host has no pyyaml).
    """
    segs, cur, text = [], None, ""
    for p in paths:
        text += open(p, encoding="utf-8").read() + "\n"
    for line in text.splitlines():
        m = re.match(r"^  - name:\s*(\S+)", line)
        if m:
            if cur and cur["start"] is not None:
                segs.append(cur)
            cur = {"name": m.group(1), "start": None, "vram": None}
            continue
        if not cur:
            continue
        m = re.match(r"^    start:\s*(0x[0-9A-Fa-f]+|\d+)", line)
        if m:
            cur["start"] = int(m.group(1), 0)
            continue
        m = re.match(r"^    vram:\s*(0x[0-9A-Fa-f]+|\d+)", line)
        if m:
            cur["vram"] = int(m.group(1), 0)
    if cur and cur["start"] is not None:
        segs.append(cur)
    return segs


def build_vram_map(segs):
    """[(vram_lo, vram_hi, rom_lo, name)].

    A segment's extent is bounded by the next segment that starts later in ROM;
    fragments are not stored in ROM order throughout, hence the scan forward
    rather than a simple pairwise zip.
    """
    out = []
    for i, s in enumerate(segs):
        if s["vram"] is None or s["start"] is None:
            continue
        nxt = next((t["start"] for t in segs[i + 1:]
                    if t["start"] is not None and t["start"] > s["start"]), None)
        size = (nxt - s["start"]) if nxt else 0x100000
        out.append((s["vram"], s["vram"] + size, s["start"], s["name"]))
    return out


def vram_to_rom(vmap, vram):
    for lo, hi, rom, name in vmap:
        if lo <= vram < hi:
            return rom + (vram - lo), name
    return None, None


def parse_subsegments(paths):
    """[(rom_offset, kind)] for every splat subsegment, sorted.

    Needed because splat's symbol table lists more than functions: inside a `c`
    subsegment, `do_c_func_detection` merges a symbol into the function that
    contains it, so an entry there with no emitted function is a mid-function
    label rather than a function of its own.
    """
    subs, text = [], ""
    for p in paths:
        text += open(p, encoding="utf-8").read() + "\n"
    for line in text.splitlines():
        m = re.match(r"^\s+-\s*\[\s*(0x[0-9A-Fa-f]+)\s*,\s*([A-Za-z_]\w*)", line)
        if m:
            subs.append((int(m.group(1), 0), m.group(2)))
    subs.sort()
    return subs


def subsegment_kind(subs, rom_off):
    i = bisect.bisect_right(subs, (rom_off, "\xff")) - 1
    return subs[i][1] if i >= 0 else None


def pragma_functions(src_dir):
    """Symbols splat actually emits a standalone .s file for, per the checked-in
    `#pragma GLOBAL_ASM` paths."""
    out = set()
    for dirpath, _, names in os.walk(src_dir):
        for n in names:
            if not n.endswith(".c"):
                continue
            text = open(os.path.join(dirpath, n), encoding="utf-8",
                        errors="replace").read()
            for m in re.finditer(r'GLOBAL_ASM\("(asm/us/[^"]+)"\)', text):
                out.add(os.path.basename(m.group(1))[:-2])
    return out


def parse_syms(paths):
    """symbol -> vram, for everything splat calls a function."""
    funcs = {}
    for path in paths:
        if not os.path.exists(path):
            continue
        for line in open(path, encoding="utf-8", errors="replace"):
            m = re.match(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$", line)
            if not m:
                continue
            name, addr, rest = m.group(1), int(m.group(2), 0), m.group(3)
            if "type:func" in rest or re.match(r"^func_[0-9A-Fa-f]{6,8}$", name):
                funcs[name] = addr
    return funcs


# --- function extraction ------------------------------------------------

JR_RA = 0x03E00008


def load_functions(rom_path, yaml_paths, sym_paths, label, verbose=True,
                   src_dir=None):
    rom = open(rom_path, "rb").read()
    vmap = build_vram_map(parse_segments(yaml_paths))
    syms = parse_syms(sym_paths)
    subs = parse_subsegments(yaml_paths) if src_dir else None
    emitted = pragma_functions(src_dir) if src_dir else None
    skipped = 0
    addrs = sorted(set(syms.values()))
    nxt = dict(zip(addrs, addrs[1:]))
    funcs = {}
    for name, vram in syms.items():
        off, seg = vram_to_rom(vmap, vram)
        if off is None:
            continue
        if subs is not None:
            kind = subsegment_kind(subs, off)
            if kind == "c" and name not in emitted:
                # A symbol inside a decompiled/stubbed C file that splat emits no
                # function for is a label in the middle of one.  Slicing from it
                # yields a function tail that can match something unrelated.
                skipped += 1
                continue
            if kind not in ("c", "asm", "hasm"):
                skipped += 1
                continue
        # The symbol table gives starts, not sizes.  Read up to the next symbol,
        # then cut at the delay slot of the last `jr $ra` -- which also strips
        # the alignment padding splat's next-symbol bound would otherwise include.
        limit = min(nxt.get(vram, vram + 0x3000) - vram, 0x6000)
        n = limit // 4
        if n < 4 or off + n * 4 > len(rom):
            continue
        words = struct.unpack(f">{n}I", rom[off:off + n * 4])
        end = None
        for i, w in enumerate(words):
            if w == JR_RA:
                end = i + 2
        if end is None or end < 4:
            continue
        funcs[name] = {"vram": vram, "seg": seg, "w": words[:end]}
    if verbose:
        named = sum(1 for n in funcs if is_named(n))
        extra = f", {skipped} non-functions skipped" if skipped else ""
        print(f"{label}: {len(funcs)} functions from {len(syms)} symbols "
              f"({named} already named{extra})", file=sys.stderr)
    return funcs


# --- normalisation ------------------------------------------------------

def norm(w):
    """Mask the fields that differ between two links of identical source."""
    op = w >> 26
    if op in (2, 3):                       # j / jal -- absolute target
        return 0x08000000
    if op == 15:                           # lui -- high half of an address
        return w & 0xFFFF0000
    if op == 0 or op in (0x10, 0x11):      # SPECIAL / COP0 / COP1: registers only
        return w
    return w & 0xFFFF0000                  # every other I-type: drop the immediate


# Opcodes whose immediate is always data, never part of an address: a bound, a
# mask, a count.  `addiu`/`ori` qualify only when the source register is $zero,
# which makes them a `li` rather than the low half of a `lui`/`addiu` pair.
_DATA_IMM_OPS = {0x0A, 0x0B, 0x0C, 0x0E}          # slti sltiu andi xori


def semi_strict_equal(a, b):
    """Like the normalised comparison, but literal constants must also agree.

    The normalised signature throws away every immediate, which is what lets it
    see through relocation.  For a function whose entire content is "compare
    against a constant, branch, store to a global", that leaves almost nothing
    to match on, and two unrelated functions of that shape collide.  This adds
    the immediates back for the opcodes where an immediate cannot be an address.
    """
    if len(a) != len(b):
        return False
    for x, y in zip(a, b):
        if norm(x) != norm(y):
            return False
        op = x >> 26
        rs = (x >> 21) & 0x1F
        if op in _DATA_IMM_OPS or (op in (0x09, 0x0D) and rs == 0):
            if (x & 0xFFFF) != (y & 0xFFFF):
                return False
    return True


def strict_sig(words):
    return tuple(words)


def loose_sig(words):
    return tuple(norm(w) for w in words)


def similarity(a, b):
    """Fraction of positionally-agreeing normalised instructions."""
    if not a or not b:
        return 0.0
    if abs(len(a) - len(b)) > 0.25 * max(len(a), len(b)) + 3:
        return 0.0
    same = sum(1 for x, y in zip(a, b) if norm(x) == norm(y))
    return same / max(len(a), len(b))


def near_matches(function, gs, s1, *, minimum=0.60, limit=10):
    """Rank Stadium 1 bodies that share substantial instruction shape.

    This is deliberately separate from ``match``.  A near match is useful for
    finding a Stadium 1 source pattern after Stadium 2 added fields or control
    flow, but it is not safe evidence for a name transfer or C replacement.
    """
    target = gs.get(function)
    if target is None:
        return []
    rows = []
    for name, candidate in s1.items():
        score = similarity(target["w"], candidate["w"])
        if score < minimum:
            continue
        rows.append(
            {
                "function": name,
                "similarity": score,
                "instructions": len(candidate["w"]),
                "segment": candidate["seg"],
                "vram": candidate["vram"],
            }
        )
    rows.sort(key=lambda row: (-row["similarity"], abs(row["instructions"] - len(target["w"])), row["function"]))
    return rows[:limit]


def is_identical(a, b):
    return len(a) == len(b) and all(norm(x) == norm(y) for x, y in zip(a, b))


def call_targets(f):
    """VRAMs of every `jal` in the body, in order."""
    base = f["vram"] & 0xF0000000
    return [base | ((w & 0x03FFFFFF) << 2) for w in f["w"] if (w >> 26) == 3]


# --- matching -----------------------------------------------------------

MIN_WORDS = 6


def match(gs, s1):
    """Returns {gs_symbol: (s1_symbol, class, detail)}."""
    matches = {}

    def take(g, r, cls, detail):
        if g in matches:
            return False
        matches[g] = (r, cls, detail, r)
        return True

    # Pass 1: unique whole-body signature matches.
    for sigfn, cls in ((strict_sig, "identical"), (loose_sig, "normalised")):
        idx = collections.defaultdict(list)
        for n, f in s1.items():
            if len(f["w"]) >= MIN_WORDS:
                idx[sigfn(f["w"])].append(n)
        for n, f in gs.items():
            if n in matches or len(f["w"]) < MIN_WORDS:
                continue
            cand = idx.get(sigfn(f["w"]))
            if cand and len(cand) == 1:
                take(n, cand[0], cls, f"{len(f['w'])} instructions")

    # Pass 2: call-graph propagation.  If A matches A', then A's Nth call and
    # A''s Nth call are the same callee -- provided the bodies agree too.
    gs_by_vram = {f["vram"]: n for n, f in gs.items()}
    s1_by_vram = {f["vram"]: n for n, f in s1.items()}
    for _ in range(8):
        used_s1 = {r for r, *_ in matches.values()}
        added = 0
        for g, (r, _, _, _) in list(matches.items()):
            gc, rc = call_targets(gs[g]), call_targets(s1[r])
            if not gc or len(gc) != len(rc):
                continue
            for gv, rv in zip(gc, rc):
                gn, rn = gs_by_vram.get(gv), s1_by_vram.get(rv)
                if not gn or not rn or gn in matches or rn in used_s1:
                    continue
                s = similarity(gs[gn]["w"], s1[rn]["w"])
                if s < 0.80:
                    continue
                cls = "identical" if gs[gn]["w"] == s1[rn]["w"] else "callgraph"
                if take(gn, rn, cls, f"called from {g} <-> {r}, {s:.0%} body agreement"):
                    used_s1.add(rn)
                    added += 1
        if not added:
            break

    return matches


def screen_shape_generic(matches, gs, s1):
    """Drop matches that rest on shape alone.

    A body that calls nothing already-matched offers no corroboration beyond its
    instruction shape -- and the normalised signature has discarded exactly the
    literals that would tell two same-shaped functions apart.  For those, require
    that the constants agree too.  Bodies that do call a matched function keep
    their match: the callee is independent evidence.
    """
    matched_vrams = {s1[r]["vram"] for r, *_ in matches.values()}
    gs_matched_vrams = {gs[g]["vram"] for g in matches}
    dropped = []
    for g, (r, cls, detail, proposed) in list(matches.items()):
        if cls not in ("normalised", "aligned"):
            continue
        corroborated = any(v in gs_matched_vrams for v in call_targets(gs[g]))
        if corroborated:
            continue
        if not semi_strict_equal(gs[g]["w"], s1[r]["w"]):
            dropped.append((g, proposed, len(gs[g]["w"])))
            del matches[g]
    if dropped:
        print(f"shape-only screen: dropped {len(dropped)} matches whose body calls "
              f"nothing already matched and whose literals disagree", file=sys.stderr)
        for g, n, ln in sorted(dropped, key=lambda x: x[2])[:15]:
            print(f"  {g} -> {n} ({ln} instructions)", file=sys.stderr)
    return matches


def segment_map(matches, gs, s1, min_anchors=3):
    """GS segment -> (S1 segment, anchor count), by plurality vote."""
    votes = collections.Counter(
        (gs[g]["seg"], s1[r]["seg"]) for g, (r, *_) in matches.items())
    out = {}
    for (gseg, rseg), c in votes.most_common():
        if gseg not in out and c >= min_anchors:
            out[gseg] = (rseg, c)
    return out


def align_gaps(matches, gs, s1, segmap, min_sim=0.50):
    """Fill runs of equal length between consecutive in-order anchors.

    Both ROMs emit a translation unit's functions in source order, so between
    two anchors an equal number of unmatched functions on each side is a forced
    correspondence -- but only where the bodies still broadly agree, since
    Stadium 2 also inserted and deleted functions in these files.
    """
    found = {}
    for gseg, (rseg, _) in segmap.items():
        G = sorted((f["vram"], n) for n, f in gs.items() if f["seg"] == gseg)
        R = sorted((f["vram"], n) for n, f in s1.items() if f["seg"] == rseg)
        gi = {n: i for i, (v, n) in enumerate(G)}
        ri = {n: i for i, (v, n) in enumerate(R)}
        pairs = sorted((gi[g], ri[r]) for g, (r, _, _, _) in matches.items()
                       if gs[g]["seg"] == gseg and s1[r]["seg"] == rseg)
        if len(pairs) < 4:
            continue
        # Longest increasing subsequence on the S1 index: the largest anchor set
        # that agrees on ordering.  Anything outside it is a layout reshuffle and
        # cannot be used to bound a gap.
        tails, tail_idx, prev = [], [], [-1] * len(pairs)
        for k, (_, b) in enumerate(pairs):
            j = bisect.bisect_left(tails, b)
            if j == len(tails):
                tails.append(b)
                tail_idx.append(k)
            else:
                tails[j], tail_idx[j] = b, k
            prev[k] = tail_idx[j - 1] if j else -1
        lis, k = [], (tail_idx[-1] if tail_idx else -1)
        while k >= 0:
            lis.append(pairs[k])
            k = prev[k]
        lis.reverse()
        for (a1, b1), (a2, b2) in zip(lis, lis[1:]):
            dg, dr = a2 - a1 - 1, b2 - b1 - 1
            if dg != dr or dg <= 0:
                continue
            for t in range(1, dg + 1):
                gn, rn = G[a1 + t][1], R[b1 + t][1]
                if gn in matches or gn in found:
                    continue
                s = similarity(gs[gn]["w"], s1[rn]["w"])
                if s < min_sim:
                    continue
                anchor = G[a1][1]
                found[gn] = (rn, "aligned",
                             f"position {t}/{dg} between anchors {anchor} and {G[a2][1]}, "
                             f"{s:.0%} body agreement", rn)
    return found


# --- output -------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--gs-rom", default=None)
    ap.add_argument("--s1-root", default=DEFAULT_S1)
    ap.add_argument("--out", default=os.path.join(ROOT, "tools", "s1_transfer.json"))
    ap.add_argument("--report", action="store_true", help="summarise, write nothing")
    ap.add_argument(
        "--near-function",
        action="append",
        default=[],
        help="rank Stadium 1 near-matches for this GS function (repeatable)",
    )
    ap.add_argument(
        "--near-source",
        help="rank near-matches for every GLOBAL_ASM owner in this C source",
    )
    ap.add_argument(
        "--near-min",
        type=float,
        default=0.60,
        help="minimum normalized instruction similarity for --near-* (default: 0.60)",
    )
    ap.add_argument(
        "--near-top",
        type=int,
        default=5,
        help="maximum Stadium 1 references per near-match target (default: 5)",
    )
    ap.add_argument("--force", action="store_true",
                    help="overwrite the output even if it shrinks sharply")
    ap.add_argument("--classes", default="identical,normalised,callgraph",
                    help="comma-separated match classes to emit")
    a = ap.parse_args()

    gs_rom = a.gs_rom or next((p for p in GS_ROM_CANDIDATES if os.path.exists(p)), None)
    if not gs_rom:
        sys.exit("no Stadium 2 ROM found; pass --gs-rom (see README for the md5)")
    s1_rom = next((os.path.join(a.s1_root, p) for p in S1_ROM_RELPATHS
                   if os.path.exists(os.path.join(a.s1_root, p))), None)
    if not s1_rom:
        sys.exit(f"no Stadium 1 ROM under {a.s1_root}")
    print(f"GS ROM: {gs_rom}\nS1 ROM: {s1_rom}", file=sys.stderr)

    gs = load_functions(gs_rom,
                        [os.path.join(ROOT, "disasm", "yamls", "us", "rom.yaml")],
                        [os.path.join(ROOT, "disasm", "linker_scripts", "us", f)
                         for f in ("symbol_addrs_code.txt", "symbol_addrs_ultralib.txt")],
                        "GS", src_dir=os.path.join(ROOT, "disasm", "src"))
    s1d = os.path.join(a.s1_root, "disasm")
    s1 = load_functions(s1_rom,
                        [os.path.join(s1d, "pokestadium-us.yaml")],
                        [os.path.join(s1d, "linker_scripts", "us", f)
                         for f in ("symbol_addrs_code.txt", "symbol_addrs_ultralib.txt")],
                        "S1")

    near_targets = list(a.near_function)
    if a.near_source:
        source_path = a.near_source
        if not os.path.isabs(source_path):
            source_path = os.path.join(ROOT, source_path)
        if not os.path.exists(source_path):
            sys.exit(f"near-match source does not exist: {a.near_source}")
        text = open(source_path, encoding="utf-8", errors="replace").read()
        near_targets.extend(
            re.findall(r'GLOBAL_ASM\("asm/us/[^\"]+/([^/\"]+)\.s"\)', text)
        )
    if near_targets:
        seen = set()
        for function in near_targets:
            if function in seen:
                continue
            seen.add(function)
            rows = near_matches(
                function,
                gs,
                s1,
                minimum=max(0.0, min(a.near_min, 1.0)),
                limit=max(1, a.near_top),
            )
            print(f"{function}:")
            if not rows:
                print("  (no Stadium 1 body above threshold)")
                continue
            for row in rows:
                print(
                    f"  {row['similarity']:.1%} {row['function']} "
                    f"({row['instructions']} instructions, {row['segment']}, "
                    f"0x{row['vram']:08X})"
                )
        return

    matches = match(gs, s1)
    segmap = segment_map(matches, gs, s1)
    matches.update(align_gaps(matches, gs, s1, segmap))
    screen_shape_generic(matches, gs, s1)

    # A symbol can only be applied once.  Two things produce a duplicate claim
    # and they need opposite treatment:
    #
    #   * Stadium 2 links the same helper into several fragments, so one S1
    #     function legitimately corresponds to several GS ones.  Those are real
    #     matches and keep their name, disambiguated by the segment they live in.
    #   * A short, generic body (a two-instruction osSendMesg wrapper, say)
    #     collides with an unrelated function.  Two claimants inside one segment
    #     cannot be told apart, so the whole in-segment set is dropped.
    claims = collections.defaultdict(list)
    for g, (r, *_) in matches.items():
        claims[r].append(g)
    dropped = renamed = 0
    for r, gl in sorted(claims.items()):
        if len(gl) < 2:
            continue
        by_seg = collections.defaultdict(list)
        for g in gl:
            by_seg[gs[g]["seg"]].append(g)
        survivors = []
        for seg, group in by_seg.items():
            if len(group) > 1:
                for g in group:
                    del matches[g]
                    dropped += 1
            else:
                survivors.append(group[0])
        if len(survivors) > 1:
            # The copy in `text` is the engine's own; the fragment copies are the
            # duplicates, so they are the ones that carry a suffix.
            for g in survivors:
                if gs[g]["seg"] == "text":
                    continue
                sym, cls, detail, _ = matches[g]
                matches[g] = (sym, cls,
                              detail + f"; one of {len(survivors)} copies of {sym} "
                                       f"linked into separate fragments",
                              f"{sym}_{gs[g]['seg']}")
                renamed += 1
    if dropped or renamed:
        print(f"duplicate claims: dropped {dropped} (ambiguous within one segment), "
              f"suffixed {renamed} (same helper linked into several fragments)",
              file=sys.stderr)

    # Where GS already has a name, we learn nothing -- but a disagreement is a
    # finding worth surfacing rather than silently dropping.
    conflicts, transfers = [], {}
    for g, (r, cls, detail, proposed) in sorted(matches.items()):
        if not is_named(r):
            continue
        if is_named(g):
            if g != r:
                conflicts.append((g, r, cls))
            continue
        transfers[g] = (r, cls, detail, proposed)

    by_class = collections.Counter(v[1] for v in transfers.values())
    print(f"\n{len(matches)} matched functions; {len(transfers)} transferable names",
          file=sys.stderr)
    for cls in ("identical", "normalised", "callgraph", "aligned"):
        print(f"  {cls:<11} {by_class[cls]}", file=sys.stderr)
    print(f"\nGS segment -> S1 segment:", file=sys.stderr)
    for gseg, (rseg, c) in sorted(segmap.items(), key=lambda x: -x[1][1]):
        print(f"  {gseg:<14} -> {rseg:<14} ({c} anchors)", file=sys.stderr)
    if conflicts:
        print(f"\n{len(conflicts)} name disagreements on already-named GS functions:",
              file=sys.stderr)
        for g, r, cls in conflicts[:40]:
            print(f"  GS {g:<28} vs S1 {r:<28} ({cls})", file=sys.stderr)

    if a.report:
        return

    wanted = set(a.classes.split(","))
    out = {
        "_README": [
            "Function names transferred from the Pokemon Stadium 1 decomp by",
            "matching machine code between the two ROMs. Generated by",
            "tools/xmatch_stadium1.py -- do not hand-edit; hand-written names",
            "belong in tools/gs_names.json.",
            "Each entry is [new_name, evidence]. The evidence records the S1",
            "symbol, its address, the match class and the corroboration.",
        ],
        "functions": {},
    }
    for g, (r, cls, detail, proposed) in sorted(transfers.items()):
        if cls not in wanted:
            continue
        out["functions"][g] = [
            proposed, f"Stadium 1 {r} @ 0x{s1[r]['vram']:08X} ({s1[r]['seg']}); "
                      f"match class {cls}; {detail}"]
    # Running the matcher against an already-renamed tree yields almost nothing:
    # every transferable symbol now has a name, so it is skipped as already
    # named.  Refuse to overwrite a good mapping with that.
    if os.path.exists(a.out) and not a.force:
        prev = len(json.load(open(a.out, encoding="utf-8")).get("functions", {}))
        if prev and len(out["functions"]) < prev * 0.9:
            sys.exit(f"REFUSING: would replace {prev} names with "
                     f"{len(out['functions'])}. Either disasm/ is already "
                     f"renamed (revert it first) or --classes is narrower than "
                     f"the run that wrote this file. Pass --force if intended.")
    json.dump(out, open(a.out, "w", encoding="utf-8"), indent=1, ensure_ascii=False)
    print(f"\nwrote {len(out['functions'])} names to {os.path.relpath(a.out, ROOT)}",
          file=sys.stderr)


if __name__ == "__main__":
    main()
