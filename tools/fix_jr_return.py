#!/usr/bin/env python3
"""Make `jr $ra` return when its target is the caller's continuation.

The emitter put the intra-function label `switch` BEFORE the
host_return_target check, so a `jr $ra` whose target is also a label inside
the same function always took the local `goto` — even when that address was
exactly where the caller expected control to resume.

For a function entered at its top this is harmless (the caller's return
address is rarely one of the callee's own labels). It breaks badly when a
function is re-entered at an interior label through a dispatch alias: the
callee absorbs the caller's continuation, the caller's frame never unwinds,
and a guest routine that calls a PC-relative local helper in a loop grows the
host stack every iteration. Pokemon Stadium 2's static_5_80021834 does exactly
that (`addiu $t3, $ra, 0x190` then `jalr $t3` in a loop) and overflows the
thread stack after a few thousand iterations -> SIGSEGV at ~8s.

Fix: only consider the local dispatch when the target is NOT our return
address. The existing trailing logic (tailcall request, then normal return) is
untouched.
"""
import os
import shutil

P = "/Users/michaegg/ps2-recomp-build/n64recomp-2b/src/recompilation.cpp"
t = open(P, encoding="utf-8", newline="").read()

old = """        for (uint32_t label_vram : branch_labels) {
            if (label_vram >= func.vram && label_vram < func_vram_end) {
                if (!emitted_local_dispatch) {
                    indent_line();
                    fmt::print(output_file, "switch ({}) {{\\n", jr_target_vram_var);
                    emitted_local_dispatch = true;
                }
                indent_line();
                fmt::print(output_file, "case 0x{:08X}u: goto L_{:08X};\\n", label_vram, label_vram);
            }
        }
        if (emitted_local_dispatch) {
            indent_line();
            fmt::print(output_file, "default: break;\\n");
            indent_line();
            fmt::print(output_file, "}}\\n");
        }
"""

new = """        std::vector<uint32_t> jr_local_labels;
        for (uint32_t label_vram : branch_labels) {
            if (label_vram >= func.vram && label_vram < func_vram_end) {
                jr_local_labels.push_back(label_vram);
            }
        }
        emitted_local_dispatch = !jr_local_labels.empty();
        if (emitted_local_dispatch) {
            // Only branch locally when the target is NOT where our caller
            // expects us to resume. Taking the local goto for the caller's
            // continuation makes this frame absorb the caller's remaining
            // work, so the caller never unwinds; a guest routine that calls a
            // PC-relative local helper inside a loop then grows the host stack
            // once per iteration until it overflows.
            indent_line();
            fmt::print(output_file, "if ({} != ctx->host_return_target) {{\\n", jr_target_vram_var);
            indent_line();
            fmt::print(output_file, "switch ({}) {{\\n", jr_target_vram_var);
            for (uint32_t label_vram : jr_local_labels) {
                indent_line();
                fmt::print(output_file, "case 0x{:08X}u: goto L_{:08X};\\n", label_vram, label_vram);
            }
            indent_line();
            fmt::print(output_file, "default: break;\\n");
            indent_line();
            fmt::print(output_file, "}}\\n");
            indent_line();
            fmt::print(output_file, "}}\\n");
        }
"""

assert t.count(old) == 1, t.count(old)
if not os.path.exists(P + ".jrreturn.orig"):
    shutil.copy2(P, P + ".jrreturn.orig")
open(P, "w", encoding="utf-8", newline="").write(t.replace(old, new, 1))
print("OK jr $ra return-vs-local-goto ordering fixed")
