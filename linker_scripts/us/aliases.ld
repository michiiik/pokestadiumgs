/* Descriptive compatibility names are aliases only; owners remain
 * address-stable until their C implementations are byte-matched.
 *
 * This file is hand-written and tracked outside the splat-generated
 * pokestadiumgs.ld so a re-split does not silently drop it (splat rewrites
 * that file from scratch on every `splat split`). It is linked in via an
 * extra `-T` script from the Makefile, the same way hardware_regs.ld,
 * undefined_syms.ld, and the other hand-written scripts are.
 */
Audio_BuildSchedulerTask = func_80021B74;
Audio_ThreadEntry = func_80035174;
Audio_RequestEvent = func_800355E4;
