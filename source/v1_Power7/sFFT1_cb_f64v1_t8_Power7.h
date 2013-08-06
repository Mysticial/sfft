/* sfft_cb_f64v1_t8_Power7.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 06/02/2011
 * Last Modified    : 06/02/2011
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t8      =   8-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t8_Power7_H
#define _sfft_cb_f64v1_t8_Power7_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t8_forward_Power7(T,w){  \
    const vector double NEGATE0 = {0.0,-0.0};   \
    const vector double NEGATE1 = {-0.0,0.0};   \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC;  \
    \
    _r0 = ((const f_vector*)(T))[0];    \
    _r4 = ((const f_vector*)(T))[4];    \
    _r1 = ((const f_vector*)(T))[1];    \
    _r5 = ((const f_vector*)(T))[5];    \
    \
    _r8 = fv_sub(_r0,_r4);  \
    _r9 = fv_sub(_r1,_r5);  \
    _r2 = ((const f_vector*)(T))[2];    \
    _r6 = ((const f_vector*)(T))[6];    \
    _r3 = ((const f_vector*)(T))[3];    \
    _r7 = ((const f_vector*)(T))[7];    \
    \
    _r0 = fv_add(_r0,_r4);  \
    _r1 = fv_add(_r1,_r5);  \
    _rA = fv_sub(_r2,_r6);  \
    _rB = fv_sub(_r3,_r7);  \
    \
    fv_ld1_broadcast(_rC,(const double*)(w) + 7);   \
    _r2 = fv_add(_r2,_r6);  \
    _r3 = fv_add(_r3,_r7);  \
    _r4 = fv_mergel(_r8,_rA);   \
    _r5 = fv_mergel(_r9,_rB);   \
    \
    ((f_vector*)(T))[0] = _r0;  \
    ((f_vector*)(T))[1] = _r1;  \
    _r4 = fv_mul(_r4,_rC);  \
    _r5 = fv_mul(_r5,_rC);  \
    \
    ((f_vector*)(T))[2] = _r2;  \
    ((f_vector*)(T))[3] = _r3;  \
    _r6 = fv_sub(_r4,_r5);  \
    \
    _r4 = fv_add(_r4,_r5);  \
    \
    _r8 = fv_mergeh(_r8,_r4);   \
    _r9 = fv_mergeh(_r9,_r6);   \
    _rB = fv_perm1(_rB,_r6);    \
    _rA = fv_perm1(_rA,_r4);    \
    \
    _r8 = fv_xor(_r8,NEGATE0);  \
    _rA = fv_xor(_rA,NEGATE1);  \
    \
    ((f_vector*)(T))[4] = _r8;  \
    ((f_vector*)(T))[5] = _r9;  \
    ((f_vector*)(T))[6] = _rB;  \
    ((f_vector*)(T))[7] = _rA;  \
    \
    sfft_cb_f64v1_t4_forward_u1_Power7((f_vector*)(T));    \
}
    //sfft_cb_f64v1_t4_forward_u1_Power7((f_vector*)(T));    \
    //sfft_cb_f64v1_t4_forward_Power7((f_vector*)(T) + 0);   \
    //sfft_cb_f64v1_t4_forward_Power7((f_vector*)(T) + 4);   \
    //sfft_cb_f64v1_t4_inverse_Power7((f_vector*)(T) + 0); \
    //sfft_cb_f64v1_t4_inverse_Power7((f_vector*)(T) + 4); \
    //sfft_cb_f64v1_t4_inverse_u1_Power7((f_vector*)(T));    \

#define sfft_cb_f64v1_t8_inverse_Power7(T,w){  \
    const vector double NEGATE0 = {-0.0,-0.0};  \
    \
    sfft_cb_f64v1_t4_inverse_u1_Power7((f_vector*)(T));    \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC;  \
    \
    _r4 = ((const f_vector*)(T))[4];    \
    _r6 = ((const f_vector*)(T))[6];    \
    _r5 = ((const f_vector*)(T))[5];    \
    _r7 = ((const f_vector*)(T))[7];    \
    \
    _r8 = fv_mergel(_r4,_r6);   \
    _r9 = fv_mergel(_r5,_r7);   \
    _r0 = ((const f_vector*)(T))[0];    \
    _r2 = ((const f_vector*)(T))[2];    \
    \
    _rA = fv_sub(_r8,_r9);  \
    fv_ld1_broadcast(_rC,(const double*)(w) + 5);   \
    \
    _r9 = fv_add(_r8,_r9);  \
    \
    _rA = fv_mul(_rA,_rC);  \
    _r9 = fv_mul(_r9,_rC);  \
    _r1 = ((const f_vector*)(T))[1];    \
    _r3 = ((const f_vector*)(T))[3];    \
    \
    _r4 = fv_mergeh(_r4,_rA);   \
    _rC = fv_perm1(_r7,_r9);    \
    _r5 = fv_mergeh(_r5,_r9);   \
    _r7 = fv_perm1(_r6,_rA);    \
    \
    _rC = fv_xor(_rC,NEGATE0);  \
    \
    _r8 = fv_add(_r0,_r4);  \
    _rB = fv_add(_r1,_r5);  \
    _r9 = fv_add(_r2,_rC);  \
    _rA = fv_add(_r3,_r7);  \
    \
    ((f_vector*)(T))[0] = _r8;  \
    ((f_vector*)(T))[1] = _rB;  \
    ((f_vector*)(T))[2] = _r9;  \
    ((f_vector*)(T))[3] = _rA;  \
    \
    _r0 = fv_sub(_r0,_r4);  \
    _r1 = fv_sub(_r1,_r5);  \
    _r2 = fv_sub(_r2,_rC);  \
    _r3 = fv_sub(_r3,_r7);  \
    \
    ((f_vector*)(T))[4] = _r0;  \
    ((f_vector*)(T))[5] = _r1;  \
    ((f_vector*)(T))[6] = _r2;  \
    ((f_vector*)(T))[7] = _r3;  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
