# Original handwritten retail assembly, not a matching C implementation.
# Tracked here so restoring the owner does not depend on cached split output.
/* Handwritten function */
glabel func_8001FC60
    /* 020860 8001FC60 20AF0020 */  addi        $t7, $a1, 0x20 /* handwritten instruction */
  .L8001FC64:
    /* 020864 8001FC64 8CA80000 */  lw          $t0, 0x0($a1)
    /* 020868 8001FC68 8CA90004 */  lw          $t1, 0x4($a1)
    /* 02086C 8001FC6C 8CAA0008 */  lw          $t2, 0x8($a1)
    /* 020870 8001FC70 8CAB000C */  lw          $t3, 0xC($a1)
    /* 020874 8001FC74 20A50010 */  addi        $a1, $a1, 0x10 /* handwritten instruction */
    /* 020878 8001FC78 AC880000 */  sw          $t0, 0x0($a0)
    /* 02087C 8001FC7C AC890004 */  sw          $t1, 0x4($a0)
    /* 020880 8001FC80 AC8A0008 */  sw          $t2, 0x8($a0)
    /* 020884 8001FC84 AC8B000C */  sw          $t3, 0xC($a0)
    /* 020888 8001FC88 14AFFFF6 */  bne         $a1, $t7, .L8001FC64
    /* 02088C 8001FC8C 20840010 */   addi       $a0, $a0, 0x10 /* handwritten instruction */
    /* 020890 8001FC90 03E00008 */  jr          $ra
    /* 020894 8001FC94 00000000 */   nop
    /* 020898 8001FC98 00000000 */  nop
    /* 02089C 8001FC9C 00000000 */  nop
