/* sfft_cb_v0_t8_Default.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/13/2010
 * Last Modified    : 02/04/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      v0      =   Vectorize by 1
 *      t8      =   8-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_v0_t8_Default_H
#define _sfft_cb_v0_t8_Default_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_v0_t8_forward_Default(I,O,w){  \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC;  \
    \
    _r0 = ((const f_vector*)(I))[ 0];   \
    _r4 = ((const f_vector*)(I))[ 8];   \
    _r1 = ((const f_vector*)(I))[ 1];   \
    _r5 = ((const f_vector*)(I))[ 9];   \
    \
    ((f_vector*)(I))[ 0] = _r0 + _r4;   \
    ((f_vector*)(I))[ 1] = _r1 + _r5;   \
    _r2 = ((const f_vector*)(I))[ 4];   \
    _r6 = ((const f_vector*)(I))[12];   \
    _r3 = ((const f_vector*)(I))[ 5];   \
    _r7 = ((const f_vector*)(I))[13];   \
    \
    ((f_vector*)(I))[ 4] = _r2 + _r6;   \
    ((f_vector*)(I))[ 5] = _r3 + _r7;   \
    \
    _r8 = ((const f_vector*)(I))[ 2];   \
    _r9 = ((const f_vector*)(I))[10];   \
    _rA = ((const f_vector*)(I))[ 3];   \
    _rB = ((const f_vector*)(I))[11];   \
    ((f_vector*)(I))[ 8] = _r0 - _r4;   \
    ((f_vector*)(I))[ 9] = _r1 - _r5;   \
    ((f_vector*)(I))[12] = _r3 - _r7;   \
    ((f_vector*)(I))[13] = _r6 - _r2;   \
    \
    ((f_vector*)(I))[ 2] = _r8 + _r9;   \
    ((f_vector*)(I))[ 3] = _rA + _rB;   \
    _r4 = ((const f_vector*)(I))[ 6];   \
    _r5 = ((const f_vector*)(I))[14];   \
    _r6 = ((const f_vector*)(I))[ 7];   \
    _r7 = ((const f_vector*)(I))[15];   \
    \
    _rC = ((const f_vector*)(w))[ 6];   \
    ((f_vector*)(I))[ 6] = _r4 + _r5;   \
    ((f_vector*)(I))[ 7] = _r6 + _r7;   \
    \
    _r8 -= _r9; \
    _rA -= _rB; \
    _r5 -= _r4; \
    _r6 -= _r7; \
    \
    ((f_vector*)(I))[10] = (_r8 + _rA) * _rC;   \
    ((f_vector*)(I))[11] = (_rA - _r8) * _rC;   \
    ((f_vector*)(I))[14] = (_r6 + _r5) * _rC;   \
    ((f_vector*)(I))[15] = (_r5 - _r6) * _rC;   \
    \
    sfft_cb_v0_t4_forward_Default((f_vector*)(I) +  0,(f_vector*)(O) +  0);    \
    sfft_cb_v0_t4_forward_Default((f_vector*)(I) +  8,(f_vector*)(O) +  8);    \
}
#define sfft_cb_v0_t8_inverse_Default(I,O,w){  \
    sfft_cb_v0_t4_inverse_Default((f_vector*)(I) +  0,(f_vector*)(O) +  0);    \
    sfft_cb_v0_t4_inverse_Default((f_vector*)(I) +  8,(f_vector*)(O) +  8);    \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC;  \
    \
    _r0 = ((const f_vector*)(O))[ 0];   \
    _r4 = ((const f_vector*)(O))[ 8];   \
    _r1 = ((const f_vector*)(O))[ 1];   \
    _r5 = ((const f_vector*)(O))[ 9];   \
    \
    ((f_vector*)(O))[ 0] = _r0 + _r4;   \
    ((f_vector*)(O))[ 1] = _r1 + _r5;   \
    _r2 = ((const f_vector*)(O))[ 4];   \
    _r7 = ((const f_vector*)(O))[13];   \
    _r3 = ((const f_vector*)(O))[ 5];   \
    _r6 = ((const f_vector*)(O))[12];   \
    \
    ((f_vector*)(O))[ 8] = _r0 - _r4;   \
    ((f_vector*)(O))[ 9] = _r1 - _r5;   \
    ((f_vector*)(O))[ 4] = _r2 - _r7;   \
    ((f_vector*)(O))[ 5] = _r3 + _r6;   \
    _rC = ((const f_vector*)(w))[ 6];   \
    \
    _rA = ((const f_vector*)(O))[10];   \
    _rB = ((const f_vector*)(O))[11];   \
    _r8 = ((const f_vector*)(O))[ 2];   \
    _r9 = ((const f_vector*)(O))[ 3];   \
    ((f_vector*)(O))[12] = _r2 + _r7;   \
    ((f_vector*)(O))[13] = _r3 - _r6;   \
    \
    _r4 = (_rA - _rB) * _rC;    \
    _r5 = (_rA + _rB) * _rC;    \
    _r6 = ((const f_vector*)(O))[14];   \
    _r7 = ((const f_vector*)(O))[15];   \
    _r0 = ((const f_vector*)(O))[ 6];   \
    _r1 = ((const f_vector*)(O))[ 7];   \
    \
    _r2 = (_r7 + _r6) * _rC;    \
    _r3 = (_r6 - _r7) * _rC;    \
    ((f_vector*)(O))[ 2] = _r8 + _r4;   \
    ((f_vector*)(O))[ 3] = _r9 + _r5;   \
    ((f_vector*)(O))[ 6] = _r0 - _r2;   \
    ((f_vector*)(O))[ 7] = _r1 + _r3;   \
    \
    ((f_vector*)(O))[10] = _r8 - _r4;   \
    ((f_vector*)(O))[11] = _r9 - _r5;   \
    ((f_vector*)(O))[14] = _r0 + _r2;   \
    ((f_vector*)(O))[15] = _r1 - _r3;   \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
