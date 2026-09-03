glabel func_800047B0
    addiu       $sp, $sp, -0x18
    sw          $a0, 0x18($sp)
    sw          $ra, 0x14($sp)
    or          $a0, $a1, $zero
    or          $a1, $a2, $zero
    jal         Memmap_RelocateFragment
    sw          $a2, 0x20($sp)
    lw          $a2, 0x20($sp)
    lw          $a0, 0x18($sp)
    lw          $t6, 0x1C($a2)
    lw          $t8, 0x8($a0)
    addu        $t7, $a2, $t6
    jal         MainPool_ResetStateToOffset
    subu        $a1, $t7, $t8
    lw          $ra, 0x14($sp)
    addiu       $sp, $sp, 0x18
    jr          $ra
    nop
