/* sfft_cb_tg_b2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 10/06/2010
 * Last Modified    : 10/06/2010
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      tg          =   Type Generic
 *      b2          =   Radix 2 butterfly
 * 
 * 
 * 
 *      This file implements a radix 2 butterfly using only vector operations.
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
#ifndef _sfft_cb_tg_b2_H
#define _sfft_cb_tg_b2_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 1
//  Twiddle Factors: {1, w1}
//
//  I0   I1
//   \  /
//    \/
//    /\
//   /  \
//  1   w1
//  |    |
//  O0  O1
#define sfft_cb_tg_b2w_m16_forward_0_u0(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I0,I1,  \
    O0,O1,  \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7; \
    \
    _r0 = ((const vtype*)(I0))[0];  \
    _r2 = ((const vtype*)(I1))[0];  \
    _r1 = ((const vtype*)(I0))[1];  \
    _r3 = ((const vtype*)(I1))[1];  \
    \
    _r4 = vsub(_r0,_r2);    \
    _r5 = vsub(_r1,_r3);    \
    _r6 = ((const vtype*)(w1))[0];  \
    _r7 = ((const vtype*)(w1))[1];  \
    \
    _r0 = vadd(_r0,_r2);    \
    _r1 = vadd(_r1,_r3);    \
    \
    _r2 = vmul(_r5,_r7);    \
    _r3 = vmul(_r4,_r7);    \
    ((vtype*)(O0))[0] = _r0;    \
    ((vtype*)(O0))[1] = _r1;    \
    \
    _r4 = vpms(_r4,_r6,_r2);    \
    _r5 = vpma(_r5,_r6,_r3);    \
    \
    ((vtype*)(O1))[0] = _r4;    \
    ((vtype*)(O1))[1] = _r5;    \
}
#define sfft_cb_tg_b2w_m16_inverse_0_u0(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I0,I1,  \
    O0,O1,  \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7; \
    \
    _r3 = ((const vtype*)(I1))[1];  \
    _r7 = ((const vtype*)(w1))[1];  \
    _r1 = ((const vtype*)(I1))[0];  \
    _r6 = ((const vtype*)(w1))[0];  \
    \
    _r4 = vmul(_r3,_r7);    \
    _r5 = vmul(_r1,_r7);    \
    _r0 = ((const vtype*)(I0))[0];  \
    _r2 = ((const vtype*)(I0))[1];  \
    \
    _r1 = vpma(_r1,_r6,_r4);    \
    _r3 = vpms(_r3,_r6,_r5);    \
    \
    _r4 = vadd(_r0,_r1);    \
    _r5 = vadd(_r2,_r3);    \
    \
    _r0 = vsub(_r0,_r1);    \
    _r2 = vsub(_r2,_r3);    \
    ((vtype*)(O0))[0] = _r4;    \
    ((vtype*)(O0))[1] = _r5;    \
    \
    ((vtype*)(O1))[0] = _r0;    \
    ((vtype*)(O1))[1] = _r2;    \
}
////////////////////////////////////////////////////////////////////////////////
//  Twiddle Factors: {1, w1*i}
//
//  I0   I1
//   \  /
//    \/
//    /\
//   /  \
//  1   w1*i
//  |    |
//  O0  O1
#define sfft_cb_tg_b2w_m16_forward_1_u0(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I0,I1,  \
    O0,O1,  \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7; \
    \
    _r0 = ((const vtype*)(I0))[0];  \
    _r2 = ((const vtype*)(I1))[0];  \
    _r1 = ((const vtype*)(I0))[1];  \
    _r3 = ((const vtype*)(I1))[1];  \
    \
    _r4 = vsub(_r0,_r2);    \
    _r5 = vsub(_r1,_r3);    \
    _r6 = ((const vtype*)(w1))[1];  \
    _r7 = ((const vtype*)(w1))[0];  \
    \
    _r0 = vadd(_r0,_r2);    \
    _r1 = vadd(_r1,_r3);    \
    \
    _r2 = vmul(_r5,_r7);    \
    _r3 = vmul(_r4,_r7);    \
    ((vtype*)(O0))[0] = _r0;    \
    ((vtype*)(O0))[1] = _r1;    \
    \
    _r4 = vpma(_r4,_r6,_r2);    \
    _r5 = vpms(_r5,_r6,_r3);    \
    \
    ((vtype*)(O1))[0] = _r4;    \
    ((vtype*)(O1))[1] = _r5;    \
}
#define sfft_cb_tg_b2w_m16_inverse_1_u0(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I0,I1,  \
    O0,O1,  \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7; \
    \
    _r3 = ((const vtype*)(I1))[1];  \
    _r7 = ((const vtype*)(w1))[0];  \
    _r1 = ((const vtype*)(I1))[0];  \
    _r6 = ((const vtype*)(w1))[1];  \
    \
    _r4 = vmul(_r3,_r7);    \
    _r5 = vmul(_r1,_r7);    \
    _r0 = ((const vtype*)(I0))[0];  \
    _r2 = ((const vtype*)(I0))[1];  \
    \
    _r1 = vpms(_r1,_r6,_r4);    \
    _r3 = vpma(_r3,_r6,_r5);    \
    \
    _r4 = vadd(_r0,_r1);    \
    _r5 = vadd(_r2,_r3);    \
    \
    _r0 = vsub(_r0,_r1);    \
    _r2 = vsub(_r2,_r3);    \
    ((vtype*)(O0))[0] = _r4;    \
    ((vtype*)(O0))[1] = _r5;    \
    \
    ((vtype*)(O1))[0] = _r0;    \
    ((vtype*)(O1))[1] = _r2;    \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 2
#define sfft_cb_tg_b2w_m16_forward_0_u1(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,    \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    \
    _r0 = ((const vtype*)(A))[0];   \
    _r2 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(A))[1];   \
    _r3 = ((const vtype*)(B))[1];   \
    \
    _r4 = vsub(_r0,_r2);    \
    _r5 = vsub(_r1,_r3);    \
    _r8 = ((const vtype*)(A))[2];   \
    _rA = ((const vtype*)(B))[2];   \
    \
    _r0 = vadd(_r0,_r2);    \
    _r9 = ((const vtype*)(A))[3];   \
    _r1 = vadd(_r1,_r3);    \
    _rB = ((const vtype*)(B))[3];   \
    \
    _rC = vsub(_r8,_rA);    \
    _r7 = ((const vtype*)(w1))[1];  \
    _rD = vsub(_r9,_rB);    \
    _rF = ((const vtype*)(w1))[3];  \
    \
    _r8 = vadd(_r8,_rA);    \
    _r6 = ((const vtype*)(w1))[0];  \
    _r9 = vadd(_r9,_rB);    \
    _rE = ((const vtype*)(w1))[2];  \
    \
    _r2 = vmul(_r5,_r7);    \
    ((vtype*)(A))[0] = _r0; \
    _r3 = vmul(_r4,_r7);    \
    ((vtype*)(A))[1] = _r1; \
    _rA = vmul(_rD,_rF);    \
    ((vtype*)(A))[2] = _r8; \
    _rB = vmul(_rC,_rF);    \
    ((vtype*)(A))[3] = _r9; \
    \
    _r4 = vpms(_r4,_r6,_r2);    \
    _r5 = vpma(_r5,_r6,_r3);    \
    _rC = vpms(_rC,_rE,_rA);    \
    _rD = vpma(_rD,_rE,_rB);    \
    \
    ((vtype*)(B))[0] = _r4; \
    ((vtype*)(B))[1] = _r5; \
    ((vtype*)(B))[2] = _rC; \
    ((vtype*)(B))[3] = _rD; \
}
#define sfft_cb_tg_b2w_m16_inverse_0_u1(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,    \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    \
    _r3 = ((const vtype*)(B))[1];   \
    _r7 = ((const vtype*)(w1))[1];  \
    _r1 = ((const vtype*)(B))[0];   \
    _rF = ((const vtype*)(w1))[3];  \
    \
    _rB = ((const vtype*)(B))[3];   \
    _r9 = ((const vtype*)(B))[2];   \
    _r4 = vmul(_r3,_r7);    \
    _r5 = vmul(_r1,_r7);    \
    \
    _r6 = ((const vtype*)(w1))[0];  \
    _rC = vmul(_rB,_rF);    \
    _rD = vmul(_r9,_rF);    \
    _rE = ((const vtype*)(w1))[2];  \
    \
    _r1 = vpma(_r1,_r6,_r4);    \
    _r0 = ((const vtype*)(A))[0];   \
    _r3 = vpms(_r3,_r6,_r5);    \
    _r2 = ((const vtype*)(A))[1];   \
    \
    _r9 = vpma(_r9,_rE,_rC);    \
    _r8 = ((const vtype*)(A))[2];   \
    _rB = vpms(_rB,_rE,_rD);    \
    _rA = ((const vtype*)(A))[3];   \
    \
    _r4 = vadd(_r0,_r1);    \
    _r5 = vadd(_r2,_r3);    \
    _rC = vadd(_r8,_r9);    \
    _rD = vadd(_rA,_rB);    \
    \
    ((vtype*)(A))[0] = _r4; \
    _r0 = vsub(_r0,_r1);    \
    ((vtype*)(A))[1] = _r5; \
    _r2 = vsub(_r2,_r3);    \
    ((vtype*)(A))[2] = _rC; \
    _r8 = vsub(_r8,_r9);    \
    ((vtype*)(A))[3] = _rD; \
    _rA = vsub(_rA,_rB);    \
    \
    ((vtype*)(B))[0] = _r0; \
    ((vtype*)(B))[1] = _r2; \
    ((vtype*)(B))[2] = _r8; \
    ((vtype*)(B))[3] = _rA; \
}
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_tg_b2w_m16_forward_1_u1(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,    \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    \
    _r0 = ((const vtype*)(A))[0];   \
    _r2 = ((const vtype*)(B))[0];   \
    _r1 = ((const vtype*)(A))[1];   \
    _r3 = ((const vtype*)(B))[1];   \
    \
    _r4 = vsub(_r0,_r2);    \
    _r5 = vsub(_r1,_r3);    \
    _r8 = ((const vtype*)(A))[2];   \
    _rA = ((const vtype*)(B))[2];   \
    \
    _r0 = vadd(_r0,_r2);    \
    _r9 = ((const vtype*)(A))[3];   \
    _r1 = vadd(_r1,_r3);    \
    _rB = ((const vtype*)(B))[3];   \
    \
    _rC = vsub(_r8,_rA);    \
    _r7 = ((const vtype*)(w1))[0];  \
    _rD = vsub(_r9,_rB);    \
    _rF = ((const vtype*)(w1))[2];  \
    \
    _r8 = vadd(_r8,_rA);    \
    _r6 = ((const vtype*)(w1))[1];  \
    _r9 = vadd(_r9,_rB);    \
    _rE = ((const vtype*)(w1))[3];  \
    \
    _r2 = vmul(_r5,_r7);    \
    ((vtype*)(A))[0] = _r0; \
    _r3 = vmul(_r4,_r7);    \
    ((vtype*)(A))[1] = _r1; \
    _rA = vmul(_rD,_rF);    \
    ((vtype*)(A))[2] = _r8; \
    _rB = vmul(_rC,_rF);    \
    ((vtype*)(A))[3] = _r9; \
    \
    _r4 = vpma(_r4,_r6,_r2);    \
    _r5 = vpms(_r5,_r6,_r3);    \
    _rC = vpma(_rC,_rE,_rA);    \
    _rD = vpms(_rD,_rE,_rB);    \
    \
    ((vtype*)(B))[0] = _r4; \
    ((vtype*)(B))[1] = _r5; \
    ((vtype*)(B))[2] = _rC; \
    ((vtype*)(B))[3] = _rD; \
}
#define sfft_cb_tg_b2w_m16_inverse_1_u1(   \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    A,B,    \
    w1  \
){   \
    register vtype _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF; \
    \
    _r3 = ((const vtype*)(B))[1];   \
    _r7 = ((const vtype*)(w1))[0];  \
    _r1 = ((const vtype*)(B))[0];   \
    _rF = ((const vtype*)(w1))[2];  \
    \
    _rB = ((const vtype*)(B))[3];   \
    _r9 = ((const vtype*)(B))[2];   \
    _r4 = vmul(_r3,_r7);    \
    _r5 = vmul(_r1,_r7);    \
    \
    _r6 = ((const vtype*)(w1))[1];  \
    _rC = vmul(_rB,_rF);    \
    _rD = vmul(_r9,_rF);    \
    _rE = ((const vtype*)(w1))[3];  \
    \
    _r1 = vpms(_r1,_r6,_r4);    \
    _r0 = ((const vtype*)(A))[0];   \
    _r3 = vpma(_r3,_r6,_r5);    \
    _r2 = ((const vtype*)(A))[1];   \
    \
    _r9 = vpms(_r9,_rE,_rC);    \
    _r8 = ((const vtype*)(A))[2];   \
    _rB = vpma(_rB,_rE,_rD);    \
    _rA = ((const vtype*)(A))[3];   \
    \
    _r4 = vadd(_r0,_r1);    \
    _r5 = vadd(_r2,_r3);    \
    _rC = vadd(_r8,_r9);    \
    _rD = vadd(_rA,_rB);    \
    \
    ((vtype*)(A))[0] = _r4; \
    _r0 = vsub(_r0,_r1);    \
    ((vtype*)(A))[1] = _r5; \
    _r2 = vsub(_r2,_r3);    \
    ((vtype*)(A))[2] = _rC; \
    _r8 = vsub(_r8,_r9);    \
    ((vtype*)(A))[3] = _rD; \
    _rA = vsub(_rA,_rB);    \
    \
    ((vtype*)(B))[0] = _r0; \
    ((vtype*)(B))[1] = _r2; \
    ((vtype*)(B))[2] = _r8; \
    ((vtype*)(B))[3] = _rA; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Default Vectors
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 1
#define sfft_cb_dt_b2w_m16_forward_0_u0(   \
    I0,I1,  \
    O0,O1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_forward_0_u0(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        I0,I1,  \
        O0,O1,  \
        w1  \
    );  \
}
#define sfft_cb_dt_b2w_m16_inverse_0_u0(   \
    I0,I1,  \
    O0,O1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_inverse_0_u0(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        I0,I1,  \
        O0,O1,  \
        w1  \
    );  \
}
#define sfft_cb_dt_b2w_m16_forward_1_u0(   \
    I0,I1,  \
    O0,O1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_forward_1_u0(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        I0,I1,  \
        O0,O1,  \
        w1  \
    );  \
}
#define sfft_cb_dt_b2w_m16_inverse_1_u0(   \
    I0,I1,  \
    O0,O1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_inverse_1_u0(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        I0,I1,  \
        O0,O1,  \
        w1  \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 2
#define sfft_cb_dt_b2w_m16_forward_0_u1(   \
    T0,T1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_forward_0_u1(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,  \
        w1  \
    );  \
}
#define sfft_cb_dt_b2w_m16_inverse_0_u1(   \
    T0,T1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_inverse_0_u1(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,  \
        w1  \
    );  \
}
#define sfft_cb_dt_b2w_m16_forward_1_u1(   \
    T0,T1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_forward_1_u1(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,  \
        w1  \
    );  \
}
#define sfft_cb_dt_b2w_m16_inverse_1_u1(   \
    T0,T1,  \
    w1  \
){  \
    sfft_cb_tg_b2w_m16_inverse_1_u1(   \
        f_vector,   \
        fv_add, \
        fv_sub, \
        fv_mul, \
        fv_pma, \
        fv_pms, \
        T0,T1,  \
        w1  \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
