/* sfft_cb_tg_b3.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/10/2012
 * Last Modified    : 02/10/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      tg          =   Type Generic
 *      b3          =   Radix 3 butterfly
 * 
 * 
 * 
 *      This file implements a radix 3 butterfly using only vector operations.
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
#ifndef _sfft_cb_tg_b3_H
#define _sfft_cb_tg_b3_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Scalar
//  wr = -1/2
//  wi = sqrt(3) / 2
////////////////////////////////////////////////////////////////////////////////
//  w0 = 0 pi
#define sfft_cb_tg_vt3_m16_forward_s0(    \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi   \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB; \
    \
    _r0 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(B))[1];   \
    _r2 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(C))[1];   \
    \
    _r4 = vadd(_r0,_r2);    \
    _r0 = vsub(_r0,_r2);    \
    _r5 = vadd(_r1,_r3);    \
    _r1 = vsub(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r4 = vsub(_r4,_r1);    \
    _r9 = vsub(_r5,_r0);    \
    _r0 = vadd(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r4 = vadd(_r4,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vadd(_r0,_rB);    \
    \
    ((vtype*)(B))[0] = _r8; \
    ((vtype*)(B))[1] = _r9; \
    \
    ((vtype*)(C))[0] = _r4; \
    ((vtype*)(C))[1] = _r0; \
}
#define sfft_cb_tg_vt3_m16_inverse_s0(    \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi   \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB; \
    \
    _r0 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(B))[1];   \
    _r2 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(C))[1];   \
    \
    _r4 = vadd(_r0,_r2);    \
    _r0 = vsub(_r0,_r2);    \
    _r5 = vadd(_r1,_r3);    \
    _r1 = vsub(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r4 = vsub(_r4,_r1);    \
    _r9 = vsub(_r5,_r0);    \
    _r0 = vadd(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r4 = vadd(_r4,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vadd(_r0,_rB);    \
    \
    ((vtype*)(B))[0] = _r4; \
    ((vtype*)(B))[1] = _r0; \
    \
    ((vtype*)(C))[0] = _r8; \
    ((vtype*)(C))[1] = _r9; \
}
////////////////////////////////////////////////////////////////////////////////
//  w0 = 1/2 pi
#define sfft_cb_tg_vt3_m16_forward_s1(    \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi   \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB; \
    \
    _r0 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(B))[1];   \
    _r2 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(C))[1];   \
    \
    _r4 = vadd(_r0,_r2);    \
    _r0 = vsub(_r2,_r0);    \
    _r5 = vadd(_r1,_r3);    \
    _r1 = vsub(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r1 = vsub(_r1,_r4);    \
    _r9 = vadd(_r0,_r5);    \
    _r0 = vsub(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r1 = vsub(_r1,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vsub(_r0,_rB);    \
    \
    ((vtype*)(B))[0] = _r9; \
    ((vtype*)(B))[1] = -_r8;    \
    \
    ((vtype*)(C))[0] = _r1; \
    ((vtype*)(C))[1] = _r0; \
}
#define sfft_cb_tg_vt3_m16_inverse_s1(    \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi   \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB; \
    \
    _r0 = -((const vtype*)(B))[1];  \
    _r1 = ((const vtype*)(B))[0];   \
    _r2 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(C))[1];   \
    \
    _r4 = vsub(_r0,_r2);    \
    _r0 = vadd(_r0,_r2);    \
    _r5 = vsub(_r1,_r3);    \
    _r1 = vadd(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r4 = vsub(_r4,_r1);    \
    _r9 = vsub(_r5,_r0);    \
    _r0 = vadd(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r4 = vadd(_r4,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vadd(_r0,_rB);    \
    \
    ((vtype*)(B))[0] = _r4; \
    ((vtype*)(B))[1] = _r0; \
    \
    ((vtype*)(C))[0] = _r8; \
    ((vtype*)(C))[1] = _r9; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Vector
//  wr = -1/2
//  wi = sqrt(3) / 2
////////////////////////////////////////////////////////////////////////////////
//  w0 = [0 , 1/2) pi
//
//  Twiddle Factors: {1, w1, w2}
//
//  A   B   C
//   \  |  /
//    \ | /
//     \|/
//     /|\
//    / | \
//   /  |  \
//  1   w1  w2
//  |   |   |
//  A   B   C
#define sfft_cb_tg_vt3_m16_forward_v0(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi,w1,w2 \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD; \
    \
    _r0 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(B))[1];   \
    _r2 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(C))[1];   \
    \
    _r4 = vadd(_r0,_r2);    \
    _r0 = vsub(_r0,_r2);    \
    _r5 = vadd(_r1,_r3);    \
    _r1 = vsub(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r4 = vsub(_r4,_r1);    \
    _r9 = vsub(_r5,_r0);    \
    _r0 = vadd(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r4 = vadd(_r4,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vadd(_r0,_rB);    \
    \
    _rC = ((const vtype*)(w1))[0];  \
    _rD = ((const vtype*)(w1))[1];  \
    ((vtype*)(B))[0] = vpms(_r8,_rC,vmul(_r9,_rD)); \
    ((vtype*)(B))[1] = vpma(_r9,_rC,vmul(_r8,_rD)); \
    \
    _rC = ((const vtype*)(w2))[0];  \
    _rD = ((const vtype*)(w2))[1];  \
    ((vtype*)(C))[0] = vpms(_r4,_rC,vmul(_r0,_rD)); \
    ((vtype*)(C))[1] = vpma(_r0,_rC,vmul(_r4,_rD)); \
}
#define sfft_cb_tg_vt3_m16_inverse_v0(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi,w1,w2 \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD; \
    \
    _r0 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(B))[1];   \
    _r2 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(C))[1];   \
    \
    _rC = ((const vtype*)(w1))[0];  \
    _rD = ((const vtype*)(w1))[1];  \
    _r4 = vmul(_r1,_rD);    \
    _r5 = vmul(_r0,_rD);    \
    _r0 = vpma(_r0,_rC,_r4);    \
    _r1 = vpms(_r1,_rC,_r5);    \
    \
    _rC = ((const vtype*)(w2))[0];  \
    _rD = ((const vtype*)(w2))[1];  \
    _r4 = vmul(_r3,_rD);    \
    _r5 = vmul(_r2,_rD);    \
    _r2 = vpma(_r2,_rC,_r4);    \
    _r3 = vpms(_r3,_rC,_r5);    \
    \
    _r4 = vadd(_r0,_r2);    \
    _r0 = vsub(_r0,_r2);    \
    _r5 = vadd(_r1,_r3);    \
    _r1 = vsub(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r4 = vsub(_r4,_r1);    \
    _r9 = vsub(_r5,_r0);    \
    _r0 = vadd(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r4 = vadd(_r4,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vadd(_r0,_rB);    \
    \
    ((vtype*)(B))[0] = _r4; \
    ((vtype*)(B))[1] = _r0; \
    \
    ((vtype*)(C))[0] = _r8; \
    ((vtype*)(C))[1] = _r9; \
}
////////////////////////////////////////////////////////////////////////////////
//  w0 = [1/2 , 1) pi
//
//  Twiddle Factors: {1, w1*i, *w2}
//
//  A   B   C
//   \  |  /
//    \ | /
//     \|/
//     /|\
//    / | \
//   /  |  \
//  1 w1*i -w2
//  |   |   |
//  A   B   C
#define sfft_cb_tg_vt3_m16_forward_v1(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi,w1,w2 \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD; \
    \
    _r0 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(B))[1];   \
    _r2 = ((const vtype*)(C))[0];   \
    _r3 = ((const vtype*)(C))[1];   \
    \
    _r4 = vadd(_r0,_r2);    \
    _r0 = vsub(_r0,_r2);    \
    _r5 = vadd(_r1,_r3);    \
    _r1 = vsub(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r4 = vsub(_r1,_r4);    \
    _r9 = vsub(_r5,_r0);    \
    _r0 = vadd(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r4 = vsub(_r4,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vadd(_r0,_rB);    \
    \
    _rC = ((const vtype*)(w1))[1];  \
    _rD = ((const vtype*)(w1))[0];  \
    ((vtype*)(B))[0] = vpma(_r8,_rC,vmul(_r9,_rD)); \
    ((vtype*)(B))[1] = vpms(_r9,_rC,vmul(_r8,_rD)); \
    \
    _rC = ((const vtype*)(w2))[0];  \
    _rD = ((const vtype*)(w2))[1];  \
    ((vtype*)(C))[0] = vpma(_r0,_rD,vmul(_r4,_rC)); \
    ((vtype*)(C))[1] = vpms(_r4,_rD,vmul(_r0,_rC)); \
}
#define sfft_cb_tg_vt3_m16_inverse_v1(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,C,  \
    wr,wi,w1,w2 \
){  \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD; \
    \
    _r0 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(B))[1];   \
    _r3 = ((const vtype*)(C))[0];   \
    _r2 = ((const vtype*)(C))[1];   \
    \
    _rC = ((const vtype*)(w1))[1];  \
    _rD = ((const vtype*)(w1))[0];  \
    _r4 = vmul(_r1,_rD);    \
    _r5 = vmul(_r0,_rD);    \
    _r0 = vpms(_r0,_rC,_r4);    \
    _r1 = vpma(_r1,_rC,_r5);    \
    \
    _rC = ((const vtype*)(w2))[0];  \
    _rD = ((const vtype*)(w2))[1];  \
    _r4 = vmul(_r3,_rC);    \
    _r5 = vmul(_r2,_rC);    \
    _r2 = vpma(_r2,_rD,_r4);    \
    _r3 = vpms(_r3,_rD,_r5);    \
    \
    _r4 = vsub(_r0,_r2);    \
    _r0 = vadd(_r0,_r2);    \
    _r5 = vadd(_r1,_r3);    \
    _r1 = vsub(_r1,_r3);    \
    \
    _r6 = _r4;  \
    _r7 = _r5;  \
    \
    _r4 = vmul(_r4,wr); \
    _r5 = vmul(_r5,wr); \
    _r0 = vmul(_r0,wi); \
    _r1 = vmul(_r1,wi); \
    \
    _r8 = vadd(_r1,_r4);    \
    _r4 = vsub(_r4,_r1);    \
    _r9 = vsub(_r5,_r0);    \
    _r0 = vadd(_r0,_r5);    \
    \
    _rA = ((const vtype*)(A))[0];   \
    _rB = ((const vtype*)(A))[1];   \
    \
    ((vtype*)(A))[0] = vadd(_r6,_rA);   \
    ((vtype*)(A))[1] = vadd(_r7,_rB);   \
    \
    _r9 = vadd(_r9,_rB);    \
    _r4 = vadd(_r4,_rA);    \
    _r8 = vadd(_r8,_rA);    \
    _r0 = vadd(_r0,_rB);    \
    \
    ((vtype*)(B))[0] = _r4; \
    ((vtype*)(B))[1] = _r0; \
    \
    ((vtype*)(C))[0] = _r8; \
    ((vtype*)(C))[1] = _r9; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
