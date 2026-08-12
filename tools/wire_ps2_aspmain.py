#!/usr/bin/env python3
"""Route M_AUDTASK to Stadium 2's own recompiled audio microcode.

M_AUDTASK has been going to aspMain_skip (a no-op) since Stadium 1's aspMain was
found to be the wrong microcode for this ROM. rsp/aspMain_ps2.cpp is now
recompiled from Stadium 2's own ucode (ROM 0x1060 + rspboot at ROM 0xB70), so
the task can run for real and audio comes back.

aspMain_skip is left in place, unused, so it is a one-line revert if the new
microcode misbehaves.
"""
import os
import shutil

CMAKE = "/Users/michaegg/ps2-recomp-build/runtime/CMakeLists.txt"
MAIN = "/Users/michaegg/ps2-recomp-build/runtime/src/main/main.cpp"


def nl_of(t):
    return "\r\n" if "\r\n" in t else "\n"


def fit(s, nl):
    return s.replace("\n", nl)


# ---- CMake: compile the new microcode --------------------------------
c = open(CMAKE, encoding="utf-8", newline="").read()
cnl = nl_of(c)
anchor = fit("    ${CMAKE_SOURCE_DIR}/rsp/aspMain.cpp", cnl)
assert c.count(anchor) == 1, c.count(anchor)
if "aspMain_ps2.cpp" not in c:
    if not os.path.exists(CMAKE + ".ps2asp.orig"):
        shutil.copy2(CMAKE, CMAKE + ".ps2asp.orig")
    c = c.replace(anchor, anchor + fit("\n    ${CMAKE_SOURCE_DIR}/rsp/aspMain_ps2.cpp", cnl), 1)
    open(CMAKE, "w", encoding="utf-8", newline="").write(c)
    print("CMakeLists.txt: added rsp/aspMain_ps2.cpp")
else:
    print("CMakeLists.txt: already present")

# ---- main.cpp: declare and route -------------------------------------
m = open(MAIN, encoding="utf-8", newline="").read()
mnl = nl_of(m)
assert "aspMain_ps2" not in m, "already routed"

decl = fit("extern RspUcodeFunc aspMain;", mnl)
assert m.count(decl) == 1
m = m.replace(decl, decl + fit("\nextern RspUcodeFunc aspMain_ps2;", mnl), 1)

route = fit("            return aspMain_skip;", mnl)
assert m.count(route) == 1, m.count(route)
m = m.replace(route, fit("""            // Stadium 2's own recompiled microcode (rsp/aspMain_ps2.cpp,
            // built from ROM 0x1060 + rspboot at ROM 0xB70). aspMain_skip is
            // kept above as a one-line revert.
            return aspMain_ps2;""", mnl), 1)

if not os.path.exists(MAIN + ".ps2asp.orig"):
    shutil.copy2(MAIN, MAIN + ".ps2asp.orig")
open(MAIN, "w", encoding="utf-8", newline="").write(m)
print("main.cpp: M_AUDTASK now routes to aspMain_ps2")
