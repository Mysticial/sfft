/* sfft_cb_v0_t4_Default.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/12/2010
 * Last Modified    : 02/03/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      v0      =   Vectorize by 1
 *      t4      =   4-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_v0_t4_Default_H
#define _sfft_cb_v0_t4_Default_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_v0_t4_forward_Default(I,O){    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB;  \
    \
    _r0 = ((const f_vector*)(I))[0];    \
    _r1 = ((const f_vector*)(I))[1];    \
    _r2 = ((const f_vector*)(I))[2];    \
    _r3 = ((const f_vector*)(I))[3];    \
    _r4 = ((const f_vector*)(I))[4];    \
    _r5 = ((const f_vector*)(I))[5];    \
    _r6 = ((const f_vector*)(I))[6];    \
    _r7 = ((const f_vector*)(I))[7];    \
    \
    _r8 = _r0 + _r4;    \
    _r9 = _r1 + _r5;    \
    _rA = _r2 + _r6;    \
    _rB = _r3 + _r7;    \
    \
    _r0 -= _r4; \
    _r1 -= _r5; \
    _r2 -= _r6; \
    _r3 -= _r7; \
    \
    ((f_vector*)(O))[0] = _r8 + _rA;    \
    ((f_vector*)(O))[1] = _r9 + _rB;    \
    ((f_vector*)(O))[2] = _r8 - _rA;    \
    ((f_vector*)(O))[3] = _r9 - _rB;    \
    ((f_vector*)(O))[4] = _r0 + _r3;    \
    ((f_vector*)(O))[5] = _r1 - _r2;    \
    ((f_vector*)(O))[6] = _r0 - _r3;    \
    ((f_vector*)(O))[7] = _r1 + _r2;    \
}
#define sfft_cb_v0_t4_inverse_Default(I,O){    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB;  \
    \
    _r0 = ((const f_vector*)(I))[0];    \
    _r1 = ((const f_vector*)(I))[1];    \
    _r2 = ((const f_vector*)(I))[2];    \
    _r3 = ((const f_vector*)(I))[3];    \
    _r4 = ((const f_vector*)(I))[4];    \
    _r5 = ((const f_vector*)(I))[5];    \
    _r6 = ((const f_vector*)(I))[6];    \
    _r7 = ((const f_vector*)(I))[7];    \
    \
    _r8 = _r0 + _r2;    \
    _r9 = _r1 + _r3;    \
    _rA = _r4 + _r6;    \
    _rB = _r5 + _r7;    \
    \
    _r0 -= _r2; \
    _r1 -= _r3; \
    _r4 -= _r6; \
    _r5 -= _r7; \
    \
    ((f_vector*)(O))[0] = _r8 + _rA;    \
    ((f_vector*)(O))[1] = _r9 + _rB;    \
    ((f_vector*)(O))[2] = _r0 - _r5;    \
    ((f_vector*)(O))[3] = _r1 + _r4;    \
    ((f_vector*)(O))[4] = _r8 - _rA;    \
    ((f_vector*)(O))[5] = _r9 - _rB;    \
    ((f_vector*)(O))[6] = _r0 + _r5;    \
    ((f_vector*)(O))[7] = _r1 - _r4;    \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
