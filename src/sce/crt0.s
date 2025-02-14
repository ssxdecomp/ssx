// SCE crt0

.set noat
.set noreorder
.align 3

.global _start
.global _exit

.text

// entry point
.ent	_start
_start:
    nop
    nop
.size _start, . - _start

    // zero .bss section
.zero_bss:
    /* 1008 00100008 2C00023C */  lui        $v0, %hi(D_002C5B80)
    /* 100C 0010000C 2E00033C */  lui        $v1, %hi(D_002D8807)
    /* 1010 00100010 805B4224 */  addiu      $v0, $v0, %lo(D_002C5B80)
    /* 1014 00100014 07886324 */  addiu      $v1, $v1, %lo(D_002D8807)
  .L00100018:
    /* 1018 00100018 00000000 */  nop
    /* 101C 0010001C 00000000 */  nop
    /* 1020 00100020 0000407C */  sq         $zero, 0x0($v0)
    /* 1024 00100024 2B084300 */  sltu       $at, $v0, $v1
    /* 1028 00100028 FBFF2014 */  bnez       $at, .L00100018
    /* 102C 0010002C 10004224 */   addiu     $v0, $v0, 0x10

    // init main thread
    /* 1030 00100030 2D00043C */  lui        $a0, %hi(D_002C8FF0)
    /* 1034 00100034 FE01053C */  lui        $a1, %hi(D_1FE0000)
    /* 1038 00100038 0200063C */  lui        $a2, %hi(D_20000)
    /* 103C 0010003C 2C00073C */  lui        $a3, %hi(D_002C5C80)
    /* 1040 00100040 1000083C */  lui        $t0, %hi(_root)
    /* 1044 00100044 F08F8424 */  addiu      $a0, $a0, %lo(D_002C8FF0)
    /* 1048 00100048 0000A524 */  addiu      $a1, $a1, %lo(D_1FE0000)
    /* 104C 0010004C 0000C624 */  addiu      $a2, $a2, %lo(D_20000)
    /* 1050 00100050 805CE724 */  addiu      $a3, $a3, %lo(D_002C5C80)
    /* 1054 00100054 B0000825 */  addiu      $t0, $t0, %lo(_root)
    /* 1058 00100058 2DE08000 */  daddu      $gp, $a0, $zero
    /* 105C 0010005C 3C000324 */  addiu      $v1, $zero, 0x3C
    /* 1060 00100060 0C000000 */  syscall    0 /* handwritten instruction */

    /* 1064 00100064 2DE84000 */  daddu      $sp, $v0, $zero
    /* 1068 00100068 2E00043C */  lui        $a0, %hi(D_002D8807)
    /* 106C 0010006C 0000053C */  lui        $a1, (0x0 >> 16)
    /* 1070 00100070 07888424 */  addiu      $a0, $a0, %lo(D_002D8807)
    /* 1074 00100074 FFFFA524 */  addiu      $a1, $a1, -0x1
    /* 1078 00100078 3D000324 */  addiu      $v1, $zero, 0x3D
    /* 107C 0010007C 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1080 00100080 1892090C */  jal        func_00264860
    /* 1084 00100084 2D200000 */   daddu     $a0, $zero, $zero
    /* 1088 00100088 38000042 */  ei /* handwritten instruction */
    /* 108C 0010008C 2C00023C */  lui        $v0, %hi(D_002C5C80)
    /* 1090 00100090 805C4224 */  addiu      $v0, $v0, %lo(D_002C5C80)
    /* 1094 00100094 0000448C */  lw         $a0, 0x0($v0)
    /* 1098 00100098 E62A060C */  jal        main
    /* 109C 0010009C 04004524 */   addiu     $a1, $v0, 0x4


    /* 10A0 001000A0 80900908 */  j          func_00264200
    /* 10A4 001000A4 2D204000 */   daddu     $a0, $v0, $zero
.end _start
.size _start, . - _start

.global _exit
.ent _exit
_exit:
    /* 10A8 001000A8 80900908 */  j          func_00264200
    /* 10AC 001000AC 2D200000 */   daddu     $a0, $zero, $zero
.end _exit
.size _exit, . - _exit

.ent _root
_root:
    addiu  $v1, $zero, 0x23 
    syscall 0 // ExitThread(0)
.end _root
.size _root, . - _root