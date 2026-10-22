/* datamig: fixed-address NOLOAD sections for C-owned bss that must land at
 * retail addresses splat's group segments cannot pin (the group's single
 * .fragmentXX_bss section places objects in file order).
 *
 * This script is linked BEFORE the generated pokestadiumgs.ld (see the
 * Makefile LD invocation), so ld assigns the listed input sections here
 * first; the generated group bss section simply misses them.
 */

SECTIONS
{
    /* Spline trio (func_8290E040/E0FC/E1D8) function statics: retail stores
     * reach them at 0x8291BC14-0x8291BC38 (lui 0x8291 + sw 0xBC1C/18/14);
     * 0x30 bytes. */
    .fragment67_34AB40_bss 0x8291BC14 (NOLOAD) : SUBALIGN(4)
    {
        build/src/fragments/67/fragment67_34AB40.o(.bss)
    }
}
