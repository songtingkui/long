/*
 * Copyright (C) 2020-2021 Suzhou Tiancheng Software Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * CP0 Registers Stack
 */

#ifndef __STACKP_H__
#define __STACKP_H__

#include "cpu.h"
#include "regdef.h"

#define CTX_SIZE  (32*4)

//-----------------------------------------------------------------------------
// push context: at, v0-v1,a0-a3,t0-t9,s0-s7,gp,fp,ra, & pc
//-----------------------------------------------------------------------------

.macro SAVE_REG_ALL
    .set    noat
    .set    noreorder
    
    subu    sp, CTX_SIZE    // stack -= CTX_SIZE
    sw      ra, (0*4)(sp)
    sw      fp, (1*4)(sp)
    sw      gp, (2*4)(sp)
    sw      t9, (3*4)(sp)
    sw      t8, (4*4)(sp)
    sw      s7, (5*4)(sp)
    sw      s6, (6*4)(sp)
    sw      s5, (7*4)(sp)
    sw      s4, (8*4)(sp)
    sw      s3, (9*4)(sp)

    sw      s2, (10*4)(sp)
    sw      s1, (11*4)(sp)
    sw      s0, (12*4)(sp)
    sw      t7, (13*4)(sp)
    sw      t6, (14*4)(sp)
    sw      t5, (15*4)(sp)
    sw      t4, (16*4)(sp)
    sw      t3, (17*4)(sp)
    sw      t2, (18*4)(sp)
    sw      t1, (19*4)(sp)

    sw      t0, (20*4)(sp)
    sw      a3, (21*4)(sp)
    sw      a2, (22*4)(sp)
    sw      a1, (23*4)(sp)
    sw      a0, (24*4)(sp)
    sw      v1, (25*4)(sp)
    sw      v0, (26*4)(sp)
    sw      AT, (27*4)(sp)

	mflo	k0
	mfhi	k1
	sw	    k0, (28*4)(sp)      // lo ==> (28)
	sw	    k1, (29*4)(sp)      // hi ==> (29)

    mfc0    k0, C0_STATUS
    mfc0    k1, C0_EPC
    sw      k0, (30*4)(sp)      // sr  ==> (30)
    sw      k1, (31*4)(sp)      // epc ==> (31)

    .set    at
.endm

//-----------------------------------------------------------------------------
// pop context: at, v0-v1,a0-a3,t0-t9,s0-s7,gp,fp,ra, & pc
//-----------------------------------------------------------------------------

.macro LOAD_REG_ERET
    .set    noat
    .set    noreorder
    
    lw      ra, (0*4)(sp)
    lw      fp, (1*4)(sp)
    lw      gp, (2*4)(sp)
    lw      t9, (3*4)(sp)
    lw      t8, (4*4)(sp)
    lw      s7, (5*4)(sp)
    lw      s6, (6*4)(sp)
    lw      s5, (7*4)(sp)
    lw      s4, (8*4)(sp)
    lw      s3, (9*4)(sp)
    
    lw      s2, (10*4)(sp)
    lw      s1, (11*4)(sp)
    lw      s0, (12*4)(sp)
    lw      t7, (13*4)(sp)
    lw      t6, (14*4)(sp)
    lw      t5, (15*4)(sp)
    lw      t4, (16*4)(sp)
    lw      t3, (17*4)(sp)
    lw      t2, (18*4)(sp)
    lw      t1, (19*4)(sp)
    
    lw      t0, (20*4)(sp)
    lw      a3, (21*4)(sp)
    lw      a2, (22*4)(sp)
    lw      a1, (23*4)(sp)
    lw      a0, (24*4)(sp)
    lw      v1, (25*4)(sp)
    lw      v0, (26*4)(sp)
    lw      AT, (27*4)(sp)

#if 0
    //-----------------------------------------
    // disable interrupt here?
    //-----------------------------------------

    mfc0    k0, C0_SR;
    li      k1, 0xfffffffe;
    and     k0, k0, k1;
    mtc0    k0, C0_SR;
#endif

	lw   	k0, (28*4)(sp)
	lw   	k1, (29*4)(sp)
	mtlo	k0                  // lo <== (28)
	mthi	k1                  // hi <== (29)

    lw      k0, (30*4)(sp)
    lw      k1, (31*4)(sp)
    addu    sp, CTX_SIZE        // stack += CTX_SIZE
    mtc0    k0, C0_STATUS       // sr  <== (30)
    mtc0    k1, C0_EPC          // epc <== (31)
    ehb                         /* exception hazard barrier */

    eret                        /* return from exception */
    nop
    
    .set at
.endm

#endif /*__STACKP_H__*/


