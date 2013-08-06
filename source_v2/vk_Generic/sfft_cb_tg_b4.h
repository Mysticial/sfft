/* sfft_cb_tg_b4.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 10/06/2010
 * Last Modified    : 10/06/2010
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      tg          =   Type Generic
 *      b4          =   Radix 4 butterfly
 * 
 * 
 * 
 *      This file implements a radix 4 butterfly using only vector operations.
 *  By setting the parameters, the macros in this file can be used on any
 *  machine that supports:
 *  
 *      -   Load
 *      -   Store
 *      -   Add
 *      -   Subtract
 *      -   Multiply
 * 
 *      Note that the size of the vector as well as the data type is irrelevant
 *  as they can also be set using the macro parameters.
 * 
 * 
 * 
 *      "m16"       specifies that the macros uses at most 16 data registers.
 *      "Default"   specifes that only the basic 5 instructions above are used.
 */

#pragma once
#ifndef _sfft_cb_tg_b4_H
#define _sfft_cb_tg_b4_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 1
//  Twiddle Factors: {1, w2, w1, w3}
//
//  I0   I1   I2   I3
//   \    \   /    /
//     \    *    /
//       \/   \/
//      /  \ /  \
//    /    / \    \
//   1    1   1    i  (apply intermediate twiddles)
//   \    /   \    /
//    \  /     \  /
//     \/       \/
//     /\       /\
//    /  \     /  \
//   /    \   /    \
//  1    w2   w1   w3
//  |    |    |    |
//  O0   O1   O2   O3
#define sfft_cb_tg_b4w_m16_forward_u0( \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3,    \
    w2,w1,w3    \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    \
    _r0 = ((const vtype*)(I0))[0];  \
    _r4 = ((const vtype*)(I2))[0];  \
    _r1 = ((const vtype*)(I0))[1];  \
    _r5 = ((const vtype*)(I2))[1];  \
    \
    _r8 = vsub(_r0,_r4);    \
    _r9 = vsub(_r1,_r5);    \
    _r2 = ((const vtype*)(I1))[0];  \
    _r6 = ((const vtype*)(I3))[0];  \
    _r3 = ((const vtype*)(I1))[1];  \
    _r7 = ((const vtype*)(I3))[1];  \
    \
    _r0 = vadd(_r0,_r4);    \
    _r1 = vadd(_r1,_r5);    \
    _rA = vsub(_r2,_r6);    \
    _rB = vsub(_r3,_r7);    \
    \
    _rC = ((const vtype*)(w1))[0];  \
    _rD = ((const vtype*)(w1))[1];  \
    _r2 = vadd(_r2,_r6);    \
    _r3 = vadd(_r3,_r7);    \
    \
    _r4 = vadd(_r8,_rB);    \
    _r5 = vsub(_r9,_rA);    \
    _r6 = vsub(_r0,_r2);    \
    _r7 = vsub(_r1,_r3);    \
    \
    _rE = ((const vtype*)(w3))[0];  \
    _rF = ((const vtype*)(w3))[1];  \
    _r8 = vsub(_r8,_rB);    \
    _r9 = vadd(_r9,_rA);    \
    _r0 = vadd(_r0,_r2);    \
    _r1 = vadd(_r1,_r3);    \
    \
    _rB = vmul(_r5,_rD);    \
    _rA = vmul(_r4,_rD);    \
    ((vtype*)(O0))[0] = _r0;    \
    ((vtype*)(O0))[1] = _r1;    \
    \
    _r2 = vmul(_r9,_rF);    \
    _r3 = vmul(_r8,_rF);    \
    _r4 = vpms(_r4,_rC,_rB);    \
    _r5 = vpma(_r5,_rC,_rA);    \
    \
    _r0 = ((const vtype*)(w2))[0];  \
    _r1 = ((const vtype*)(w2))[1];  \
    _r8 = vpms(_r8,_rE,_r2);    \
    _r9 = vpma(_r9,_rE,_r3);    \
    \
    ((vtype*)(O2))[0] = _r4;    \
    ((vtype*)(O2))[1] = _r5;    \
    _rC = vmul(_r7,_r1);    \
    _rD = vmul(_r6,_r1);    \
    \
    ((vtype*)(O3))[0] = _r8;    \
    ((vtype*)(O3))[1] = _r9;    \
    _r6 = vpms(_r6,_r0,_rC);    \
    _r7 = vpma(_r7,_r0,_rD);    \
    \
    ((vtype*)(O1))[0] = _r6;    \
    ((vtype*)(O1))[1] = _r7;    \
}
#define sfft_cb_tg_b4w_m16_inverse_u0( \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3,    \
    w2,w1,w3    \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    \
    _r3 = ((const vtype*)(I1))[1];  \
    _r2 = ((const vtype*)(I1))[0];  \
    _rD = ((const vtype*)(w2))[1];  \
    _rC = ((const vtype*)(w2))[0];  \
    \
    _r8 = vmul(_r3,_rD);    \
    _r9 = vmul(_r2,_rD);    \
    _r5 = ((const vtype*)(I2))[1];  \
    _r4 = ((const vtype*)(I2))[0];  \
    \
    _r2 = vpma(_r2,_rC,_r8);    \
    _r3 = vpms(_r3,_rC,_r9);    \
    _rF = ((const vtype*)(w1))[1];  \
    _rE = ((const vtype*)(w1))[0];  \
    \
    _r7 = ((const vtype*)(I3))[1];  \
    _r6 = ((const vtype*)(I3))[0];  \
    _rA = vmul(_r5,_rF);    \
    _rB = vmul(_r4,_rF);    \
    \
    _r1 = ((const vtype*)(I0))[1];  \
    _r0 = ((const vtype*)(I0))[0];  \
    _rD = ((const vtype*)(w3))[1];  \
    _rC = ((const vtype*)(w3))[0];  \
    \
    _r4 = vpma(_r4,_rE,_rA);    \
    _r5 = vpms(_r5,_rE,_rB);    \
    _r8 = vmul(_r7,_rD);    \
    _r9 = vmul(_r6,_rD);    \
    \
    _r6 = vpma(_r6,_rC,_r8);    \
    _r7 = vpms(_r7,_rC,_r9);    \
    \
    _rA = vadd(_r0,_r2);    \
    _rB = vadd(_r1,_r3);    \
    \
    _r0 = vsub(_r0,_r2);    \
    _r1 = vsub(_r1,_r3);    \
    _rE = vadd(_r4,_r6);    \
    _rF = vadd(_r5,_r7);    \
    \
    _r4 = vsub(_r4,_r6);    \
    _r5 = vsub(_r5,_r7);    \
    _r2 = vadd(_rA,_rE);    \
    _r3 = vadd(_rB,_rF);    \
    \
    _r6 = vsub(_r0,_r5);    \
    _r7 = vadd(_r1,_r4);    \
    ((vtype*)(O0))[0] = _r2;    \
    ((vtype*)(O0))[1] = _r3;    \
    \
    ((vtype*)(O1))[0] = _r6;    \
    ((vtype*)(O1))[1] = _r7;    \
    _rA = vsub(_rA,_rE);    \
    _rB = vsub(_rB,_rF);    \
    \
    _r0 = vadd(_r0,_r5);    \
    _r1 = vsub(_r1,_r4);    \
    ((vtype*)(O2))[0] = _rA;    \
    ((vtype*)(O2))[1] = _rB;    \
    \
    ((vtype*)(O3))[0] = _r0;    \
    ((vtype*)(O3))[1] = _r1;    \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Experimental - unused
#define sfft_cb_tg_b4w_m8_forward_u0(  \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    A,B,C,D,    \
    w2,w1,w3    \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7; \
    vtype _r8;  \
    \
    _r0 = ((const vtype*)(A))[0];   \
    _r4 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(B))[1];   \
    _r7 = ((const vtype*)(D))[1];   \
    \
    _r6 = vsub(_r0,_r4);    \
    _r1 = ((const vtype*)(A))[1];   \
    _r0 = vadd(_r0,_r4);    \
    _r5 = ((const vtype*)(C))[1];   \
    _r4 = vsub(_r3,_r7);    \
    _r2 = ((const vtype*)(B))[0];   \
    _r3 = vadd(_r3,_r7);    \
    _r7 = vadd(_r6,_r4);    \
    _r6 = vsub(_r6,_r4);    \
    _r8 = _r6;      /*  Spill Store */  \
    _r6 = ((const vtype*)(D))[0];   \
    \
    _r4 = vsub(_r1,_r5);    \
    _r1 = vadd(_r1,_r5);    \
    _r5 = vsub(_r2,_r6);    \
    _r2 = vadd(_r2,_r6);    \
    \
    _r6 = vsub(_r1,_r3);    \
    _r1 = vadd(_r1,_r3);    \
    ((vtype*)(A))[1] = _r1; \
    _r3 = vsub(_r4,_r5);    \
    _r4 = vadd(_r4,_r5);    \
    _r5 = vsub(_r0,_r2);    \
    _r0 = vadd(_r0,_r2);    \
    ((vtype*)(A))[0] = _r0; \
    \
    _r0 = ((const vtype*)(w2))[0];  \
    _r1 = ((const vtype*)(w2))[1];  \
    _r2 = vmul(_r6,_r1);    \
    _r1 = vmul(_r1,_r5);    \
    _r5 = vpms(_r5,_r0,_r2);    \
    _r6 = vpma(_r6,_r0,_r1);    \
    ((vtype*)(B))[0] = _r5; \
    ((vtype*)(B))[1] = _r6; \
    \
    _r0 = ((const vtype*)(w1))[0];  \
    _r1 = ((const vtype*)(w1))[1];  \
    _r2 = vmul(_r3,_r1);    \
    _r1 = vmul(_r1,_r7);    \
    _r7 = vpms(_r7,_r0,_r2);    \
    _r3 = vpma(_r3,_r0,_r1);    \
    ((vtype*)(C))[0] = _r7; \
    ((vtype*)(C))[1] = _r3; \
    \
    _r0 = _r8;      /*  Spill Load  */  \
    _r6 = ((const vtype*)(w3))[0];  \
    _r5 = ((const vtype*)(w3))[1];  \
    _r2 = vmul(_r4,_r5);    \
    _r5 = vmul(_r5,_r0);    \
    _r0 = vpms(_r0,_r6,_r2);    \
    _r4 = vpma(_r4,_r6,_r5);    \
    ((vtype*)(D))[0] = _r0; \
    ((vtype*)(D))[1] = _r4; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 2
#define sfft_cb_tg_b4w_m32_forward_u1( \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    A,B,C,D,    \
    w2,w1,w3    \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    register vtype _s0,_s1,_s2,_s3,_s4,_s5,_s6,_s7,_s8,_s9,_sA,_sB,_sC,_sD,_sE,_sF; \
    \
    _r0 = ((const vtype*)(A))[0];   \
    _r4 = ((const vtype*)(C))[0];   \
    _r1 = ((const vtype*)(A))[1];   \
    _r5 = ((const vtype*)(C))[1];   \
    _s0 = ((const vtype*)(A))[2];   \
    _s4 = ((const vtype*)(C))[2];   \
    _s1 = ((const vtype*)(A))[3];   \
    _s5 = ((const vtype*)(C))[3];   \
    \
    _r8 = vsub(_r0,_r4);    \
    _r2 = ((const vtype*)(B))[0];   \
    _r9 = vsub(_r1,_r5);    \
    _r6 = ((const vtype*)(D))[0];   \
    _s8 = vsub(_s0,_s4);    \
    _r3 = ((const vtype*)(B))[1];   \
    _s9 = vsub(_s1,_s5);    \
    _r7 = ((const vtype*)(D))[1];   \
    \
    _r0 = vadd(_r0,_r4);    \
    _s2 = ((const vtype*)(B))[2];   \
    _r1 = vadd(_r1,_r5);    \
    _s6 = ((const vtype*)(D))[2];   \
    _rA = vsub(_r2,_r6);    \
    _s3 = ((const vtype*)(B))[3];   \
    _rB = vsub(_r3,_r7);    \
    _s7 = ((const vtype*)(D))[3];   \
    \
    _s0 = vadd(_s0,_s4);    \
    _s1 = vadd(_s1,_s5);    \
    _sA = vsub(_s2,_s6);    \
    _sB = vsub(_s3,_s7);    \
    \
    _rC = ((const vtype*)(w1))[0];  \
    _r2 = vadd(_r2,_r6);    \
    _rD = ((const vtype*)(w1))[1];  \
    _r3 = vadd(_r3,_r7);    \
    _sC = ((const vtype*)(w1))[2];  \
    _s2 = vadd(_s2,_s6);    \
    _sD = ((const vtype*)(w1))[3];  \
    _s3 = vadd(_s3,_s7);    \
    \
    _r4 = vadd(_r8,_rB);    \
    _r5 = vsub(_r9,_rA);    \
    _r6 = vsub(_r0,_r2);    \
    _r7 = vsub(_r1,_r3);    \
    _s4 = vadd(_s8,_sB);    \
    _s5 = vsub(_s9,_sA);    \
    _s6 = vsub(_s0,_s2);    \
    _s7 = vsub(_s1,_s3);    \
    \
    _rE = ((const vtype*)(w3))[0];  \
    _r8 = vsub(_r8,_rB);    \
    _r9 = vadd(_r9,_rA);    \
    _rF = ((const vtype*)(w3))[1];  \
    _r0 = vadd(_r0,_r2);    \
    _r1 = vadd(_r1,_r3);    \
    _sE = ((const vtype*)(w3))[2];  \
    _s8 = vsub(_s8,_sB);    \
    _s9 = vadd(_s9,_sA);    \
    _sF = ((const vtype*)(w3))[3];  \
    _s0 = vadd(_s0,_s2);    \
    _s1 = vadd(_s1,_s3);    \
    \
    _rB = vmul(_r5,_rD);    \
    ((vtype*)(A))[0] = _r0; \
    _rA = vmul(_r4,_rD);    \
    ((vtype*)(A))[1] = _r1; \
    _sB = vmul(_s5,_sD);    \
    ((vtype*)(A))[2] = _s0; \
    _sA = vmul(_s4,_sD);    \
    ((vtype*)(A))[3] = _s1; \
    \
    _r2 = vmul(_r9,_rF);    \
    _r3 = vmul(_r8,_rF);    \
    _r4 = vpms(_r4,_rC,_rB);    \
    _r5 = vpma(_r5,_rC,_rA);    \
    _s2 = vmul(_s9,_sF);    \
    _s3 = vmul(_s8,_sF);    \
    _s4 = vpms(_s4,_sC,_sB);    \
    _s5 = vpma(_s5,_sC,_sA);    \
    \
    _r0 = ((const vtype*)(w2))[0];  \
    _r8 = vpms(_r8,_rE,_r2);    \
    _r1 = ((const vtype*)(w2))[1];  \
    _r9 = vpma(_r9,_rE,_r3);    \
    _s0 = ((const vtype*)(w2))[2];  \
    _s8 = vpms(_s8,_sE,_s2);    \
    _s1 = ((const vtype*)(w2))[3];  \
    _s9 = vpma(_s9,_sE,_s3);    \
    \
    ((vtype*)(C))[0] = _r4; \
    _rC = vmul(_r7,_r1);    \
    ((vtype*)(C))[1] = _r5; \
    _rD = vmul(_r6,_r1);    \
    ((vtype*)(C))[2] = _s4; \
    _sC = vmul(_s7,_s1);    \
    ((vtype*)(C))[3] = _s5; \
    _sD = vmul(_s6,_s1);    \
    \
    ((vtype*)(D))[0] = _r8; \
    _r6 = vpms(_r6,_r0,_rC);    \
    ((vtype*)(D))[1] = _r9; \
    _r7 = vpma(_r7,_r0,_rD);    \
    ((vtype*)(D))[2] = _s8; \
    _s6 = vpms(_s6,_s0,_sC);    \
    ((vtype*)(D))[3] = _s9; \
    _s7 = vpma(_s7,_s0,_sD);    \
    \
    ((vtype*)(B))[0] = _r6; \
    ((vtype*)(B))[1] = _r7; \
    ((vtype*)(B))[2] = _s6; \
    ((vtype*)(B))[3] = _s7; \
}
#define sfft_cb_tg_b4w_m32_inverse_u1( \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    A,B,C,D,    \
    w2,w1,w3    \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    register vtype _s0,_s1,_s2,_s3,_s4,_s5,_s6,_s7,_s8,_s9,_sA,_sB,_sC,_sD,_sE,_sF; \
    \
    _r3 = ((const vtype*)(B))[1];   \
    _r2 = ((const vtype*)(B))[0];   \
    _rD = ((const vtype*)(w2))[1];  \
    _rC = ((const vtype*)(w2))[0];  \
    _s3 = ((const vtype*)(B))[3];   \
    _s2 = ((const vtype*)(B))[2];   \
    _sD = ((const vtype*)(w2))[3];  \
    _sC = ((const vtype*)(w2))[2];  \
    \
    _r8 = vmul(_r3,_rD);    \
    _r5 = ((const vtype*)(C))[1];   \
    _r9 = vmul(_r2,_rD);    \
    _r4 = ((const vtype*)(C))[0];   \
    _s8 = vmul(_s3,_sD);    \
    _s5 = ((const vtype*)(C))[3];   \
    _s9 = vmul(_s2,_sD);    \
    _s4 = ((const vtype*)(C))[2];   \
    \
    _r2 = vpma(_r2,_rC,_r8);    \
    _rF = ((const vtype*)(w1))[1];  \
    _r3 = vpms(_r3,_rC,_r9);    \
    _rE = ((const vtype*)(w1))[0];  \
    _s2 = vpma(_s2,_sC,_s8);    \
    _sF = ((const vtype*)(w1))[3];  \
    _s3 = vpms(_s3,_sC,_s9);    \
    _sE = ((const vtype*)(w1))[2];  \
    \
    _rA = vmul(_r5,_rF);    \
    _rD = ((const vtype*)(w3))[1];  \
    _rB = vmul(_r4,_rF);    \
    _r7 = ((const vtype*)(D))[1];   \
    _sA = vmul(_s5,_sF);    \
    _r6 = ((const vtype*)(D))[0];   \
    _sB = vmul(_s4,_sF);    \
    _sD = ((const vtype*)(w3))[3];  \
    \
    \
    _r4 = vpma(_r4,_rE,_rA);    \
    _s7 = ((const vtype*)(D))[3];   \
    _r5 = vpms(_r5,_rE,_rB);    \
    _s6 = ((const vtype*)(D))[2];   \
    _r8 = vmul(_r7,_rD);    \
    _rC = ((const vtype*)(w3))[0];  \
    _r9 = vmul(_r6,_rD);    \
    _sC = ((const vtype*)(w3))[2];  \
    \
    _s4 = vpma(_s4,_sE,_sA);    \
    _r0 = ((const vtype*)(A))[0];   \
    _s5 = vpms(_s5,_sE,_sB);    \
    _r1 = ((const vtype*)(A))[1];   \
    _s8 = vmul(_s7,_sD);    \
    _s0 = ((const vtype*)(A))[2];   \
    _s9 = vmul(_s6,_sD);    \
    _s1 = ((const vtype*)(A))[3];   \
    \
    _r6 = vpma(_r6,_rC,_r8);    \
    _r7 = vpms(_r7,_rC,_r9);    \
    _s6 = vpma(_s6,_sC,_s8);    \
    _s7 = vpms(_s7,_sC,_s9);    \
    _rA = vadd(_r0,_r2);    \
    _rB = vadd(_r1,_r3);    \
    _sA = vadd(_s0,_s2);    \
    _sB = vadd(_s1,_s3);    \
    \
    _r0 = vsub(_r0,_r2);    \
    _r1 = vsub(_r1,_r3);    \
    _rE = vadd(_r4,_r6);    \
    _rF = vadd(_r5,_r7);    \
    _s0 = vsub(_s0,_s2);    \
    _s1 = vsub(_s1,_s3);    \
    _sE = vadd(_s4,_s6);    \
    _sF = vadd(_s5,_s7);    \
    \
    _r4 = vsub(_r4,_r6);    \
    _r5 = vsub(_r5,_r7);    \
    _r2 = vadd(_rA,_rE);    \
    _r3 = vadd(_rB,_rF);    \
    _s4 = vsub(_s4,_s6);    \
    _s5 = vsub(_s5,_s7);    \
    _s2 = vadd(_sA,_sE);    \
    _s3 = vadd(_sB,_sF);    \
    \
    ((vtype*)(A))[0] = _r2; \
    _r6 = vsub(_r0,_r5);    \
    ((vtype*)(A))[1] = _r3; \
    _r7 = vadd(_r1,_r4);    \
    ((vtype*)(A))[2] = _s2; \
    _s6 = vsub(_s0,_s5);    \
    ((vtype*)(A))[3] = _s3; \
    _s7 = vadd(_s1,_s4);    \
    \
    ((vtype*)(B))[0] = _r6; \
    _rA = vsub(_rA,_rE);    \
    ((vtype*)(B))[1] = _r7; \
    _rB = vsub(_rB,_rF);    \
    ((vtype*)(B))[2] = _s6; \
    _sA = vsub(_sA,_sE);    \
    ((vtype*)(B))[3] = _s7; \
    _sB = vsub(_sB,_sF);    \
    \
    ((vtype*)(C))[0] = _rA; \
    _r0 = vadd(_r0,_r5);    \
    ((vtype*)(C))[1] = _rB; \
    _r1 = vsub(_r1,_r4);    \
    ((vtype*)(C))[2] = _sA; \
    _s0 = vadd(_s0,_s5);    \
    ((vtype*)(C))[3] = _sB; \
    _s1 = vsub(_s1,_s4);    \
    \
    ((vtype*)(D))[0] = _r0; \
    ((vtype*)(D))[1] = _r1; \
    ((vtype*)(D))[2] = _s0; \
    ((vtype*)(D))[3] = _s1; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_tg_b4w_m16_forward_u1( \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    A,B,C,D,    \
    w2,w1,w3    \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7; \
    register vtype _s0,_s1,_s2,_s3,_s4,_s5,_s6,_s7; \
    vtype _r8,_s8;  \
    \
    _r0 = ((const vtype*)(A))[0];   \
    _r4 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(B))[1];   \
    _r7 = ((const vtype*)(D))[1];   \
    _s0 = ((const vtype*)(A))[2];   \
    _s4 = ((const vtype*)(C))[2];   \
    _s3 = ((const vtype*)(B))[3];   \
    _s7 = ((const vtype*)(D))[3];   \
    \
    _r6 = vsub(_r0,_r4);    \
    _r1 = ((const vtype*)(A))[1];   \
    _r0 = vadd(_r0,_r4);    \
    _r5 = ((const vtype*)(C))[1];   \
    _r4 = vsub(_r3,_r7);    \
    _r2 = ((const vtype*)(B))[0];   \
    _r3 = vadd(_r3,_r7);    \
    _r7 = vadd(_r6,_r4);    \
    _r6 = vsub(_r6,_r4);    \
    _r8 = _r6;      /*  Spill Store */  \
    _r6 = ((const vtype*)(D))[0];   \
    _s6 = vsub(_s0,_s4);    \
    _s1 = ((const vtype*)(A))[3];   \
    _s0 = vadd(_s0,_s4);    \
    _s5 = ((const vtype*)(C))[3];   \
    _s4 = vsub(_s3,_s7);    \
    _s2 = ((const vtype*)(B))[2];   \
    _s3 = vadd(_s3,_s7);    \
    _s7 = vadd(_s6,_s4);    \
    _s6 = vsub(_s6,_s4);    \
    _s8 = _s6;      /*  Spill Store */  \
    _s6 = ((const vtype*)(D))[2];   \
    \
    _r4 = vsub(_r1,_r5);    \
    _r1 = vadd(_r1,_r5);    \
    _r5 = vsub(_r2,_r6);    \
    _r2 = vadd(_r2,_r6);    \
    _s4 = vsub(_s1,_s5);    \
    _s1 = vadd(_s1,_s5);    \
    _s5 = vsub(_s2,_s6);    \
    _s2 = vadd(_s2,_s6);    \
    \
    _r6 = vsub(_r1,_r3);    \
    _r1 = vadd(_r1,_r3);    \
    ((vtype*)(A))[1] = _r1; \
    _r3 = vsub(_r4,_r5);    \
    _r4 = vadd(_r4,_r5);    \
    _r5 = vsub(_r0,_r2);    \
    _r0 = vadd(_r0,_r2);    \
    ((vtype*)(A))[0] = _r0; \
    _s6 = vsub(_s1,_s3);    \
    _s1 = vadd(_s1,_s3);    \
    ((vtype*)(A))[3] = _s1; \
    _s3 = vsub(_s4,_s5);    \
    _s4 = vadd(_s4,_s5);    \
    _s5 = vsub(_s0,_s2);    \
    _s0 = vadd(_s0,_s2);    \
    ((vtype*)(A))[2] = _s0; \
    \
    _r0 = ((const vtype*)(w2))[0];  \
    _r1 = ((const vtype*)(w2))[1];  \
    _r2 = vmul(_r6,_r1);    \
    _r1 = vmul(_r1,_r5);    \
    _r5 = vpms(_r5,_r0,_r2);    \
    _r6 = vpma(_r6,_r0,_r1);    \
    ((vtype*)(B))[0] = _r5; \
    ((vtype*)(B))[1] = _r6; \
    _s0 = ((const vtype*)(w2))[2];  \
    _s1 = ((const vtype*)(w2))[3];  \
    _s2 = vmul(_s6,_s1);    \
    _s1 = vmul(_s1,_s5);    \
    _s5 = vpms(_s5,_s0,_s2);    \
    _s6 = vpma(_s6,_s0,_s1);    \
    ((vtype*)(B))[2] = _s5; \
    ((vtype*)(B))[3] = _s6; \
    \
    _r0 = ((const vtype*)(w1))[0];  \
    _r1 = ((const vtype*)(w1))[1];  \
    _r2 = vmul(_r3,_r1);    \
    _r1 = vmul(_r1,_r7);    \
    _r7 = vpms(_r7,_r0,_r2);    \
    _r3 = vpma(_r3,_r0,_r1);    \
    ((vtype*)(C))[0] = _r7; \
    ((vtype*)(C))[1] = _r3; \
    _s0 = ((const vtype*)(w1))[2];  \
    _s1 = ((const vtype*)(w1))[3];  \
    _s2 = vmul(_s3,_s1);    \
    _s1 = vmul(_s1,_s7);    \
    _s7 = vpms(_s7,_s0,_s2);    \
    _s3 = vpma(_s3,_s0,_s1);    \
    ((vtype*)(C))[2] = _s7; \
    ((vtype*)(C))[3] = _s3; \
    \
    _r0 = _r8;      /*  Spill Load  */  \
    _r6 = ((const vtype*)(w3))[0];  \
    _r5 = ((const vtype*)(w3))[1];  \
    _r2 = vmul(_r4,_r5);    \
    _r5 = vmul(_r5,_r0);    \
    _r0 = vpms(_r0,_r6,_r2);    \
    _r4 = vpma(_r4,_r6,_r5);    \
    ((vtype*)(D))[0] = _r0; \
    ((vtype*)(D))[1] = _r4; \
    _s0 = _s8;      /*  Spill Load  */  \
    _s6 = ((const vtype*)(w3))[2];  \
    _s5 = ((const vtype*)(w3))[3];  \
    _s2 = vmul(_s4,_s5);    \
    _s5 = vmul(_s5,_s0);    \
    _s0 = vpms(_s0,_s6,_s2);    \
    _s4 = vpma(_s4,_s6,_s5);    \
    ((vtype*)(D))[2] = _s0; \
    ((vtype*)(D))[3] = _s4; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 4
#define sfft_cb_tg_b4w_m32_forward_u2( \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    A,B,C,D,    \
    w2,w1,w3    \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7; \
    register vtype _s0,_s1,_s2,_s3,_s4,_s5,_s6,_s7; \
    register vtype _t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7; \
    register vtype _u0,_u1,_u2,_u3,_u4,_u5,_u6,_u7; \
    vtype _r8,_s8,_t8,_u8;  \
    \
    _r0 = ((const vtype*)(A))[0];   \
    _r4 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(B))[1];   \
    _r7 = ((const vtype*)(D))[1];   \
    _s0 = ((const vtype*)(A))[2];   \
    _s4 = ((const vtype*)(C))[2];   \
    _s3 = ((const vtype*)(B))[3];   \
    _s7 = ((const vtype*)(D))[3];   \
    _t0 = ((const vtype*)(A))[4];   \
    _t4 = ((const vtype*)(C))[4];   \
    _t3 = ((const vtype*)(B))[5];   \
    _t7 = ((const vtype*)(D))[5];   \
    _u0 = ((const vtype*)(A))[6];   \
    _u4 = ((const vtype*)(C))[6];   \
    _u3 = ((const vtype*)(B))[7];   \
    _u7 = ((const vtype*)(D))[7];   \
    \
    _r6 = vsub(_r0,_r4);    \
    _r1 = ((const vtype*)(A))[1];   \
    _r0 = vadd(_r0,_r4);    \
    _r5 = ((const vtype*)(C))[1];   \
    _r4 = vsub(_r3,_r7);    \
    _r2 = ((const vtype*)(B))[0];   \
    _r3 = vadd(_r3,_r7);    \
    _s6 = vsub(_s0,_s4);    \
    _s1 = ((const vtype*)(A))[3];   \
    _s0 = vadd(_s0,_s4);    \
    _s5 = ((const vtype*)(C))[3];   \
    _s4 = vsub(_s3,_s7);    \
    _s2 = ((const vtype*)(B))[2];   \
    _s3 = vadd(_s3,_s7);    \
    _t6 = vsub(_t0,_t4);    \
    _t1 = ((const vtype*)(A))[5];   \
    _t0 = vadd(_t0,_t4);    \
    _t5 = ((const vtype*)(C))[5];   \
    _t4 = vsub(_t3,_t7);    \
    _t2 = ((const vtype*)(B))[4];   \
    _t3 = vadd(_t3,_t7);    \
    _u6 = vsub(_u0,_u4);    \
    _u1 = ((const vtype*)(A))[7];   \
    _u0 = vadd(_u0,_u4);    \
    _u5 = ((const vtype*)(C))[7];   \
    _u4 = vsub(_u3,_u7);    \
    _u2 = ((const vtype*)(B))[6];   \
    _u3 = vadd(_u3,_u7);    \
    \
    _r7 = vadd(_r6,_r4);    \
    _r6 = vsub(_r6,_r4);    \
    _r8 = _r6;      /*  Spill Store */  \
    _r6 = ((const vtype*)(D))[0];   \
    _s7 = vadd(_s6,_s4);    \
    _s6 = vsub(_s6,_s4);    \
    _s8 = _s6;      /*  Spill Store */  \
    _s6 = ((const vtype*)(D))[2];   \
    _t7 = vadd(_t6,_t4);    \
    _t6 = vsub(_t6,_t4);    \
    _t8 = _t6;      /*  Spill Store */  \
    _t6 = ((const vtype*)(D))[4];   \
    _u7 = vadd(_u6,_u4);    \
    _u6 = vsub(_u6,_u4);    \
    _u8 = _u6;      /*  Spill Store */  \
    _u6 = ((const vtype*)(D))[6];   \
    \
    _r4 = vsub(_r1,_r5);    \
    _r1 = vadd(_r1,_r5);    \
    _r5 = vsub(_r2,_r6);    \
    _r2 = vadd(_r2,_r6);    \
    _s4 = vsub(_s1,_s5);    \
    _s1 = vadd(_s1,_s5);    \
    _s5 = vsub(_s2,_s6);    \
    _s2 = vadd(_s2,_s6);    \
    _t4 = vsub(_t1,_t5);    \
    _t1 = vadd(_t1,_t5);    \
    _t5 = vsub(_t2,_t6);    \
    _t2 = vadd(_t2,_t6);    \
    _u4 = vsub(_u1,_u5);    \
    _u1 = vadd(_u1,_u5);    \
    _u5 = vsub(_u2,_u6);    \
    _u2 = vadd(_u2,_u6);    \
    \
    _r6 = vsub(_r1,_r3);    \
    _r1 = vadd(_r1,_r3);    \
    ((vtype*)(A))[1] = _r1; \
    _r1 = ((const vtype*)(w2))[1];  \
    _r3 = vsub(_r4,_r5);    \
    _r4 = vadd(_r4,_r5);    \
    _r5 = vsub(_r0,_r2);    \
    _r0 = vadd(_r0,_r2);    \
    ((vtype*)(A))[0] = _r0; \
    _r0 = ((const vtype*)(w2))[0];  \
    _r2 = vmul(_r6,_r1);    \
    _r1 = vmul(_r1,_r5);    \
    _s6 = vsub(_s1,_s3);    \
    _s1 = vadd(_s1,_s3);    \
    ((vtype*)(A))[3] = _s1; \
    _s1 = ((const vtype*)(w2))[3];  \
    _s3 = vsub(_s4,_s5);    \
    _s4 = vadd(_s4,_s5);    \
    _s5 = vsub(_s0,_s2);    \
    _s0 = vadd(_s0,_s2);    \
    ((vtype*)(A))[2] = _s0; \
    _s0 = ((const vtype*)(w2))[2];  \
    _s2 = vmul(_s6,_s1);    \
    _s1 = vmul(_s1,_s5);    \
    _t6 = vsub(_t1,_t3);    \
    _t1 = vadd(_t1,_t3);    \
    ((vtype*)(A))[5] = _t1; \
    _t1 = ((const vtype*)(w2))[5];  \
    _t3 = vsub(_t4,_t5);    \
    _t4 = vadd(_t4,_t5);    \
    _t5 = vsub(_t0,_t2);    \
    _t0 = vadd(_t0,_t2);    \
    ((vtype*)(A))[4] = _t0; \
    _t0 = ((const vtype*)(w2))[4];  \
    _t2 = vmul(_t6,_t1);    \
    _t1 = vmul(_t1,_t5);    \
    _u6 = vsub(_u1,_u3);    \
    _u1 = vadd(_u1,_u3);    \
    ((vtype*)(A))[7] = _u1; \
    _u1 = ((const vtype*)(w2))[7];  \
    _u3 = vsub(_u4,_u5);    \
    _u4 = vadd(_u4,_u5);    \
    _u5 = vsub(_u0,_u2);    \
    _u0 = vadd(_u0,_u2);    \
    ((vtype*)(A))[6] = _u0; \
    _u0 = ((const vtype*)(w2))[6];  \
    _u2 = vmul(_u6,_u1);    \
    _u1 = vmul(_u1,_u5);    \
    \
    _r6 = vpma(_r6,_r0,_r1);    \
    _r1 = ((const vtype*)(w1))[1];  \
    _r5 = vpms(_r5,_r0,_r2);    \
    _r0 = ((const vtype*)(w1))[0];  \
    _r2 = vmul(_r3,_r1);    \
    _r1 = vmul(_r1,_r7);    \
    ((vtype*)(B))[1] = _r6; \
    ((vtype*)(B))[0] = _r5; \
    _r6 = ((const vtype*)(w3))[0];  \
    _r5 = ((const vtype*)(w3))[1];  \
    _s6 = vpma(_s6,_s0,_s1);    \
    _s1 = ((const vtype*)(w1))[3];  \
    _s5 = vpms(_s5,_s0,_s2);    \
    _s0 = ((const vtype*)(w1))[2];  \
    _s2 = vmul(_s3,_s1);    \
    _s1 = vmul(_s1,_s7);    \
    ((vtype*)(B))[3] = _s6; \
    ((vtype*)(B))[2] = _s5; \
    _s6 = ((const vtype*)(w3))[2];  \
    _s5 = ((const vtype*)(w3))[3];  \
    _t6 = vpma(_t6,_t0,_t1);    \
    _t1 = ((const vtype*)(w1))[5];  \
    _t5 = vpms(_t5,_t0,_t2);    \
    _t0 = ((const vtype*)(w1))[4];  \
    _t2 = vmul(_t3,_t1);    \
    _t1 = vmul(_t1,_t7);    \
    ((vtype*)(B))[5] = _t6; \
    ((vtype*)(B))[4] = _t5; \
    _t6 = ((const vtype*)(w3))[4];  \
    _t5 = ((const vtype*)(w3))[5];  \
    _u6 = vpma(_u6,_u0,_u1);    \
    _u1 = ((const vtype*)(w1))[7];  \
    _u5 = vpms(_u5,_u0,_u2);    \
    _u0 = ((const vtype*)(w1))[6];  \
    _u2 = vmul(_u3,_u1);    \
    _u1 = vmul(_u1,_u7);    \
    ((vtype*)(B))[7] = _u6; \
    ((vtype*)(B))[6] = _u5; \
    _u6 = ((const vtype*)(w3))[6];  \
    _u5 = ((const vtype*)(w3))[7];  \
    \
    _r7 = vpms(_r7,_r0,_r2);    \
    _r2 = vmul(_r4,_r5);    \
    _r3 = vpma(_r3,_r0,_r1);    \
    _r0 = _r8;      /*  Spill Load  */  \
    _r5 = vmul(_r5,_r0);    \
    ((vtype*)(C))[0] = _r7; \
    ((vtype*)(C))[1] = _r3; \
    _s7 = vpms(_s7,_s0,_s2);    \
    _s2 = vmul(_s4,_s5);    \
    _s3 = vpma(_s3,_s0,_s1);    \
    _s0 = _s8;      /*  Spill Load  */  \
    _s5 = vmul(_s5,_s0);    \
    ((vtype*)(C))[2] = _s7; \
    ((vtype*)(C))[3] = _s3; \
    _t7 = vpms(_t7,_t0,_t2);    \
    _t2 = vmul(_t4,_t5);    \
    _t3 = vpma(_t3,_t0,_t1);    \
    _t0 = _t8;      /*  Spill Load  */  \
    _t5 = vmul(_t5,_t0);    \
    ((vtype*)(C))[4] = _t7; \
    ((vtype*)(C))[5] = _t3; \
    _u7 = vpms(_u7,_u0,_u2);    \
    _u2 = vmul(_u4,_u5);    \
    _u3 = vpma(_u3,_u0,_u1);    \
    _u0 = _u8;      /*  Spill Load  */  \
    _u5 = vmul(_u5,_u0);    \
    ((vtype*)(C))[6] = _u7; \
    ((vtype*)(C))[7] = _u3; \
    \
    _r0 = vpms(_r0,_r6,_r2);    \
    _r4 = vpma(_r4,_r6,_r5);    \
    ((vtype*)(D))[0] = _r0; \
    ((vtype*)(D))[1] = _r4; \
    _s0 = vpms(_s0,_s6,_s2);    \
    _s4 = vpma(_s4,_s6,_s5);    \
    ((vtype*)(D))[2] = _s0; \
    ((vtype*)(D))[3] = _s4; \
    _t0 = vpms(_t0,_t6,_t2);    \
    _t4 = vpma(_t4,_t6,_t5);    \
    ((vtype*)(D))[4] = _t0; \
    ((vtype*)(D))[5] = _t4; \
    _u0 = vpms(_u0,_u6,_u2);    \
    _u4 = vpma(_u4,_u6,_u5);    \
    ((vtype*)(D))[6] = _u0; \
    ((vtype*)(D))[7] = _u4; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Default Vectors
#define sfft_cb_dt_b4w_m16_forward_u0( \
    T0,T1,T2,T3,    \
    O0,O1,O2,O3,    \
    w2,w1,w3    \
){  \
    sfft_cb_tg_b4w_m16_forward_u0( \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,T2,T3,    \
        O0,O1,O2,O3,    \
        w2,w1,w3    \
    );  \
}
#define sfft_cb_dt_b4w_m16_inverse_u0( \
    T0,T1,T2,T3,    \
    O0,O1,O2,O3,    \
    w2,w1,w3    \
){  \
    sfft_cb_tg_b4w_m16_inverse_u0( \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,T2,T3,    \
        O0,O1,O2,O3,    \
        w2,w1,w3    \
    );  \
}
#define sfft_cb_dt_b4w_m8_forward_u0(  \
    T0,T1,T2,T3,    \
    w2,w1,w3    \
){  \
    sfft_cb_tg_b4w_m8_forward_u0(  \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,T2,T3,    \
        w2,w1,w3    \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_dt_b4w_m32_forward_u1( \
    T0,T1,T2,T3,    \
    w2,w1,w3    \
){  \
    sfft_cb_tg_b4w_m32_forward_u1( \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,T2,T3,    \
        w2,w1,w3    \
    );  \
}
#define sfft_cb_dt_b4w_m32_inverse_u1( \
    T0,T1,T2,T3,    \
    w2,w1,w3    \
){  \
    sfft_cb_tg_b4w_m32_inverse_u1( \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,T2,T3,    \
        w2,w1,w3    \
    );  \
}
#define sfft_cb_dt_b4w_m16_forward_u1( \
    T0,T1,T2,T3,    \
    w2,w1,w3    \
){  \
    sfft_cb_tg_b4w_m16_forward_u1( \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,T2,T3,    \
        w2,w1,w3    \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_dt_b4w_m32_forward_u2( \
    T0,T1,T2,T3,    \
    w2,w1,w3    \
){  \
    sfft_cb_tg_b4w_m32_forward_u2( \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,T2,T3,    \
        w2,w1,w3    \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
