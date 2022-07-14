/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

//-----------------------------------------------------------------------------
// 1. 这个start.S 已经禁止了总中断
// 2. 禁止了TIMER中断使能, 但是代码从头开始执行时, TMIER中断的标志位还是会
//    存在的. 因此在中断处理中忽略TMER中断标志位就行.
//-----------------------------------------------------------------------------

#include "cpu.h"
#include "regdef.h"

#include "stackp.h"

//-----------------------------------------------------------------------------
// bss 段起始地址和结束地址
//-----------------------------------------------------------------------------

.extern __bss_start
.extern __bss_end

//-----------------------------------------------------------------------------
// 内存地址, 从 0xA0001000 ~ 0xA0001FFF
//-----------------------------------------------------------------------------

#define MY_BSS 0xA0001000       // DRAM = 4K

//-----------------------------------------------------------------------------

    .set noreorder

    .globl _RAM_BSS
    _RAM_BSS = MY_BSS           // =0xA0001000
    .bss
    .globl tmpgp
tmpgp:
     .word 0

//-----------------------------------------------------------------------------
// 启动代码, 链接到 0xbfc00000
//-----------------------------------------------------------------------------

    .extern bsp_start

    .globl start
    .ent   start
    .text
start:
    .set noreorder
    .set mips32

    la      gp, tmpgp
    li      sp, 0xa0000ffc      // 低 4K 内存的顶部
    li      t0, 0x08000000      // disable cp0_count, no 8M timer_interrupt
    mtc0    t0, C0_CAUSE
    li      t0, 0x10400000      // vec 位置1: 中断入口地址在0xbfc00380
    mtc0    t0, C0_STATUS

    .set mips32r2
    ehb
    .set mips32

    li      t0, 0xa0000ffc      /* XXX 设置sp ? */
    move    sp, t0
    nop

    li      t0, 1               /* 清除count/compare时钟中断 */
    mtc0    t0, C0_COMPARE

/*
 * TODO 是否加入清理 bss 段的代码?
 */

    bal     bsp_start           /* 跳到 bsp_start 入口 */
    nop

loop:                           /* 如果main函数返回, 则死循环 */
    b   loop
    nop

    .end start

//-----------------------------------------------------------------------------
// 标号 Exception 以上的代码反汇编不能超过 0Xbfc00380
// 确保中断异常入口地址是 0xbfc00380.
// 芯片跳到 0xbfc00380 后, 硬件上自动就禁止了总中断
// 然后中断返回的 eret 指令, 硬件上自动就把总中断打开了
//-----------------------------------------------------------------------------

/*
 * 异常处理
 */
    .extern c_interrupt_handler
    .extern exception_handler
    .set    mips32
    .org    0x380                       /* XXX 异常入口地址 */
    .ent    exception_entry
exception_entry:
    .set   noat
    .set    noreorder

    la      k1, (0x1f << 2)
    mfc0    k0, C0_CAUSE
    and     k0, k0, k1
    beq     zero, k0, 1f                /* 中断 */
    nop
    la      k0, exception_handler       /* 例外 */
    jr      k0
    nop

1:
    SAVE_REG_ALL                        /* 入栈 */

    jal     c_interrupt_handler         /* 跳到中断处理中 */
    nop

    LOAD_REG_ERET                       /* 出栈 */

    nop
    .set    at
    .set    reorder
    .end    exception_entry

//-----------------------------------------------------------------------------
// 例外处理入口
//-----------------------------------------------------------------------------

    .global exception_handler
    .type   exception_handler, @function
    .set    noreorder
exception_handler:
    .set    noreorder
    .set    at
    mfc0    t0, C0_STATUS           //disable interrupt
    and     t0, t0, 0xfffffffe
    mtc0    t0, C0_STATUS
    sw      $0, (4*0)(sp)
    sw      $1, (4*1)(sp)
    sw      $2, (4*2)(sp)
    sw      $3, (4*3)(sp)
    sw      $4, (4*4)(sp)
    sw      $5, (4*5)(sp)
    sw      $6, (4*6)(sp)
    sw      $7, (4*7)(sp)
    sw      $8, (4*8)(sp)
    sw      $9, (4*9)(sp)
    sw      $10, (4*10)(sp)
    sw      $11, (4*11)(sp)
    sw      $12, (4*12)(sp)
    sw      $13, (4*13)(sp)
    sw      $14, (4*14)(sp)
    sw      $15, (4*15)(sp)
    sw      $16, (4*16)(sp)
    sw      $17, (4*17)(sp)
    sw      $18, (4*18)(sp)
    sw      $19, (4*19)(sp)
    sw      $20, (4*20)(sp)
    sw      $21, (4*21)(sp)
    sw      $22, (4*22)(sp)
    sw      $23, (4*23)(sp)
    sw      $24, (4*24)(sp)
    sw      $25, (4*25)(sp)
    sw      $26, (4*26)(sp)
    sw      $27, (4*27)(sp)
    sw      $28, (4*28)(sp)
    sw      $29, (4*29)(sp)
    sw      $30, (4*30)(sp)
    sw      $31, (4*31)(sp)
    move    a0, sp
    la      k0, c_exception_handler
    jr      k0
    nop
    .set    reorder

//-----------------------------------------------------------------------------

/*
 * @@END
 */
