# Original handwritten retail assembly, not a matching C implementation.
# Tracked here so restoring the owner does not depend on cached split output.
/* Handwritten function */
glabel func_8000B6C0
    /* 00C2C0 8000B6C0 8C870008 */  lw          $a3, 0x8($a0)
    /* 00C2C4 8000B6C4 8C99000C */  lw          $t9, 0xC($a0)
    /* 00C2C8 8000B6C8 8C980004 */  lw          $t8, 0x4($a0)
    /* 00C2CC 8000B6CC 00E43820 */  add         $a3, $a3, $a0 /* handwritten instruction */
    /* 00C2D0 8000B6D0 0324C820 */  add         $t9, $t9, $a0 /* handwritten instruction */
    /* 00C2D4 8000B6D4 00003025 */  or          $a2, $zero, $zero
    /* 00C2D8 8000B6D8 20840010 */  addi        $a0, $a0, 0x10 /* handwritten instruction */
    /* 00C2DC 8000B6DC 0305C020 */  add         $t8, $t8, $a1 /* handwritten instruction */
  .L8000B6E0:
    /* 00C2E0 8000B6E0 54C00005 */  bnel        $a2, $zero, .L8000B6F8
    /* 00C2E4 8000B6E4 0100482A */   slt        $t1, $t0, $zero
    /* 00C2E8 8000B6E8 8C880000 */  lw          $t0, 0x0($a0)
    /* 00C2EC 8000B6EC 24060020 */  addiu       $a2, $zero, 0x20
    /* 00C2F0 8000B6F0 20840004 */  addi        $a0, $a0, 0x4 /* handwritten instruction */
    /* 00C2F4 8000B6F4 0100482A */  slt         $t1, $t0, $zero
  .L8000B6F8:
    /* 00C2F8 8000B6F8 51200007 */  beql        $t1, $zero, .L8000B718
    /* 00C2FC 8000B6FC 94EA0000 */   lhu        $t2, 0x0($a3)
    /* 00C300 8000B700 832A0000 */  lb          $t2, 0x0($t9)
    /* 00C304 8000B704 23390001 */  addi        $t9, $t9, 0x1 /* handwritten instruction */
    /* 00C308 8000B708 20A50001 */  addi        $a1, $a1, 0x1 /* handwritten instruction */
    /* 00C30C 8000B70C 1000000E */  b           .L8000B748
    /* 00C310 8000B710 A0AAFFFF */   sb         $t2, -0x1($a1)
    /* 00C314 8000B714 94EA0000 */  lhu         $t2, 0x0($a3)
  .L8000B718:
    /* 00C318 8000B718 20E70002 */  addi        $a3, $a3, 0x2 /* handwritten instruction */
    /* 00C31C 8000B71C 000A5B02 */  srl         $t3, $t2, 12
    /* 00C320 8000B720 314A0FFF */  andi        $t2, $t2, 0xFFF
    /* 00C324 8000B724 1160000D */  beqz        $t3, .L8000B75C
    /* 00C328 8000B728 00AA4822 */   sub        $t1, $a1, $t2 /* handwritten instruction */
    /* 00C32C 8000B72C 216B0002 */  addi        $t3, $t3, 0x2 /* handwritten instruction */
  .L8000B730:
    /* 00C330 8000B730 812AFFFF */  lb          $t2, -0x1($t1)
    /* 00C334 8000B734 216BFFFF */  addi        $t3, $t3, -0x1 /* handwritten instruction */
    /* 00C338 8000B738 21290001 */  addi        $t1, $t1, 0x1 /* handwritten instruction */
    /* 00C33C 8000B73C 20A50001 */  addi        $a1, $a1, 0x1 /* handwritten instruction */
    /* 00C340 8000B740 1560FFFB */  bnez        $t3, .L8000B730
    /* 00C344 8000B744 A0AAFFFF */   sb         $t2, -0x1($a1)
  .L8000B748:
    /* 00C348 8000B748 00084040 */  sll         $t0, $t0, 1
    /* 00C34C 8000B74C 14B8FFE4 */  bne         $a1, $t8, .L8000B6E0
    /* 00C350 8000B750 20C6FFFF */   addi       $a2, $a2, -0x1 /* handwritten instruction */
    /* 00C354 8000B754 03E00008 */  jr          $ra
    /* 00C358 8000B758 00000000 */   nop
  .L8000B75C:
    /* 00C35C 8000B75C 932B0000 */  lbu         $t3, 0x0($t9)
    /* 00C360 8000B760 23390001 */  addi        $t9, $t9, 0x1 /* handwritten instruction */
    /* 00C364 8000B764 1000FFF2 */  b           .L8000B730
    /* 00C368 8000B768 216B0012 */   addi       $t3, $t3, 0x12 /* handwritten instruction */
    /* 00C36C 8000B76C 00000000 */  nop
  glabel func_8000B770
    /* 00C370 8000B770 03E00008 */  jr          $ra
    /* 00C374 8000B774 46006005 */   abs.s      $fv0, $fa0
    /* 00C378 8000B778 00000000 */  nop
    /* 00C37C 8000B77C 00000000 */  nop
