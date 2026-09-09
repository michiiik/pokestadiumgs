#!/usr/bin/env python3
"""Ensure the fragment-vaddr resolver hooks are present in generated C.

``game.toml`` defines an entry/exit hook pair for ``Memmap_GetFragmentVaddr``.
Older generated snapshots predate those hooks, so a native build can silently
fall back to the single global fragment table and select the wrong resident
pattern variant.  Generation is intentionally not repeated here; this small,
idempotent post-step repairs a snapshot while preserving the generated body.
"""

from __future__ import annotations

import argparse
from pathlib import Path


ENTRY = "librecomp_fragment_input_push((uint32_t)ctx->r4);"
EXIT = "librecomp_fragment_resolve_exit("

# Older generated snapshots also carry two guest-side assumptions that are
# valid on the original hardware but not on the native runner:
#
# * func_800422B4 intentionally emits no request when the optional secondary
#   model slot is empty, while its caller still enters func_80042968's blocking
#   wait.  The native scheduler has no completion to deliver in that case.
# * fragment 242's animation helper divides by a frame-count field that is
#   legitimately zero for an absent animation track.  The ROM's `break 7`
#   protects the hardware path; returning through the normal epilogue is the
#   useful native equivalent.
#
# These are post-generation repairs for the local native snapshot only.  They
# never touch the ROM-matched `generated/` tree used by the decomp build.
MODEL_WAIT_GUARD = """    if (MEM_BU(ctx->r4, 0) == 1 && MEM_W(ctx->r4, 0x14) == 0) {
        return;
    }
"""
ANIM_ZERO_GUARD = """    if (ctx->r2 == 0) {
        goto L_84112148;
    }
"""


def find_owner(root: Path) -> Path:
    for path in sorted(root.glob("funcs_*.c")):
        if "RECOMP_FUNC void func_800024A0" in path.read_text(encoding="utf-8"):
            return path
    raise SystemExit(f"fragment resolver owner not found under {root}")


def find_function_owner(root: Path, signature: str) -> Path:
    for path in sorted(root.glob("funcs_*.c")):
        if signature in path.read_text(encoding="utf-8"):
            return path
    raise SystemExit(f"generated owner not found under {root}: {signature}")


def apply_native_guards(root: Path) -> bool:
    """Repair native-only missing-asset paths in the generated snapshot."""
    changed = False

    wait_owner = find_function_owner(root, "RECOMP_FUNC void func_80042968")
    wait_text = wait_owner.read_text(encoding="utf-8")
    wait_anchor = "L_80042968:\n"
    if MODEL_WAIT_GUARD in wait_text:
        pass
    else:
        if wait_text.count(wait_anchor) != 1:
            raise SystemExit(f"{wait_owner}: unexpected model-wait label count")
        wait_text = wait_text.replace(
            wait_anchor, wait_anchor + MODEL_WAIT_GUARD, 1
        )
        wait_owner.write_text(wait_text, encoding="utf-8", newline="")
        print(f"{wait_owner}: inserted missing-model wait guard")
        changed = True

    anim_owner = find_function_owner(root, "RECOMP_FUNC void func_841120AC")
    anim_text = anim_owner.read_text(encoding="utf-8")
    anim_anchor = "    ctx->r2 = MEM_HU(ctx->r8, 0XA);\n"
    if ANIM_ZERO_GUARD in anim_text:
        pass
    else:
        if anim_text.count(anim_anchor) != 1:
            raise SystemExit(f"{anim_owner}: unexpected animation frame-count anchor")
        anim_text = anim_text.replace(
            anim_anchor, anim_anchor + ANIM_ZERO_GUARD, 1
        )
        anim_owner.write_text(anim_text, encoding="utf-8", newline="")
        print(f"{anim_owner}: inserted zero-frame animation guard")
        changed = True

    return changed


def apply(root: Path) -> bool:
    owner = find_owner(root)
    text = owner.read_text(encoding="utf-8")
    changed = False
    if ENTRY in text and EXIT in text:
        print(f"{owner}: hooks already present")
    else:
        if ENTRY in text or EXIT in text:
            raise SystemExit(f"{owner}: fragment hook pair is only partially present")

        entry_anchor = "L_800024A0:\n"
        exit_anchor = "L_800024FC:\n"
        if text.count(entry_anchor) != 1 or text.count(exit_anchor) != 1:
            raise SystemExit(f"{owner}: unexpected resolver label count")

        entry = (
            entry_anchor
            + "    librecomp_fragment_input_push((uint32_t)ctx->r4);\n"
        )
        exit = (
            exit_anchor
            + "    ctx->r4 = librecomp_fragment_resolve_exit(\n"
            + "        (uint32_t)ctx->r4, (uint32_t)ctx->fragment_runtime_base);\n"
        )
        text = text.replace(entry_anchor, entry, 1)
        text = text.replace(exit_anchor, exit, 1)
        owner.write_text(text, encoding="utf-8", newline="")
        print(f"{owner}: inserted fragment resolver hooks")
        changed = True

    return apply_native_guards(root) or changed


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("generated_dir", type=Path)
    args = parser.parse_args()
    root = args.generated_dir.resolve()
    if not root.is_dir():
        raise SystemExit(f"generated directory does not exist: {root}")
    apply(root)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
