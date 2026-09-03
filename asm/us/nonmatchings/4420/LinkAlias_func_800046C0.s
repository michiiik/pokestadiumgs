glabel func_800046C0
    lui         $at, (0xFF000000 >> 16)
    and         $t6, $a1, $at
    addiu       $sp, $sp, -0x28
    lui         $at, (0x81000000 >> 16)
    sw          $ra, 0x14($sp)
    bne         $t6, $at, .L80004708
    sw          $a0, 0x28($sp)
    lui         $at, (0xFFFFFF >> 16)
    ori         $at, $at, (0xFFFFFF & 0xFFFF)
    and         $a0, $a1, $at
    jal         Memmap_GetFragmentBaseVaddr
    sw          $a0, 0x1C($sp)
    lw          $t7, 0x28($sp)
    lw          $a0, 0x1C($sp)
    bnel        $v0, $t7, .L8000470C
    lw          $ra, 0x14($sp)
    jal         Memmap_ClearFragmentMemmap
    nop
.L80004708:
    lw          $ra, 0x14($sp)
.L8000470C:
    addiu       $sp, $sp, 0x28
    jr          $ra
    nop
