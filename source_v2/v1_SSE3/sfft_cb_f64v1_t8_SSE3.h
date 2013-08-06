/* sfft_cb_f64v1_t8_SSE3.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/14/2010
 * Last Modified    : 09/16/2010
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t8      =   8-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t8_SSE3_H
#define _sfft_cb_f64v1_t8_SSE3_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t8_forward_SSE3(I,O,w){  \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC;  \
    \
    _r0 = ((const f_vector*)(I))[0];    \
    _r4 = ((const f_vector*)(I))[4];    \
    _r1 = ((const f_vector*)(I))[1];    \
    _r5 = ((const f_vector*)(I))[5];    \
    \
    _r8 = fv_sub(_r0,_r4);  \
    _r9 = fv_sub(_r1,_r5);  \
    _r2 = ((const f_vector*)(I))[2];    \
    _r6 = ((const f_vector*)(I))[6];    \
    _r3 = ((const f_vector*)(I))[3];    \
    _r7 = ((const f_vector*)(I))[7];    \
    \
    _r0 = fv_add(_r0,_r4);  \
    _r1 = fv_add(_r1,_r5);  \
    _rA = fv_sub(_r2,_r6);  \
    _rB = fv_sub(_r3,_r7);  \
    \
    _rC = _mm_loaddup_pd((const double*)(w) + 7);   \
    _r2 = fv_add(_r2,_r6);  \
    _r3 = fv_add(_r3,_r7);  \
    _r4 = fv_unpackhi(_r8,_rA); \
    _r5 = fv_unpackhi(_r9,_rB); \
    \
    ((f_vector*)(I))[0] = _r0;  \
    ((f_vector*)(I))[1] = _r1;  \
    _r4 = fv_mul(_r4,_rC);  \
    _r5 = fv_mul(_r5,_rC);  \
    \
    ((f_vector*)(I))[2] = _r2;  \
    ((f_vector*)(I))[3] = _r3;  \
    _r6 = fv_sub(_r4,_r5);  \
    \
    _r4 = fv_add(_r4,_r5);  \
    \
    _r8 = fv_unpacklo(_r8,_r4); \
    _r9 = fv_unpacklo(_r9,_r6); \
    _rB = fv_shuffle(_rB,_r6,2);    \
    _rA = fv_shuffle(_rA,_r4,2);    \
    \
    ((f_vector*)(I))[4] = fv_xor(_r8,_mm_set_pd(-0.0,0.0));  \
    ((f_vector*)(I))[5] = _r9;  \
    ((f_vector*)(I))[6] = _rB;  \
    ((f_vector*)(I))[7] = fv_xor(_rA,_mm_set_pd(0.0,-0.0));  \
    \
    sfft_cb_f64v1_t4_forward_SSE3((f_vector*)(I) + 0,(f_vector*)(O) + 0); \
    sfft_cb_f64v1_t4_forward_SSE3((f_vector*)(I) + 4,(f_vector*)(O) + 4); \
}
#define sfft_cb_f64v1_t8_inverse_SSE3(I,O,w){  \
    sfft_cb_f64v1_t4_inverse_SSE3((f_vector*)(I) + 0,(f_vector*)(O) + 0); \
    sfft_cb_f64v1_t4_inverse_SSE3((f_vector*)(I) + 4,(f_vector*)(O) + 4); \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC;  \
    \
    _r4 = ((const f_vector*)(O))[4];    \
    _r6 = ((const f_vector*)(O))[6];    \
    _r5 = ((const f_vector*)(O))[5];    \
    _r7 = ((const f_vector*)(O))[7];    \
    \
    _r8 = fv_unpackhi(_r4,_r6); \
    _r9 = fv_unpackhi(_r5,_r7); \
    _r0 = ((const f_vector*)(O))[0];    \
    _r2 = ((const f_vector*)(O))[2];    \
    \
    _rA = fv_sub(_r8,_r9);  \
    _rC = _mm_loaddup_pd((const double*)(w) + 5);   \
    \
    _r9 = fv_add(_r8,_r9);  \
    \
    _rA = fv_mul(_rA,_rC);  \
    _r9 = fv_mul(_r9,_rC);  \
    _r1 = ((const f_vector*)(O))[1];    \
    _r3 = ((const f_vector*)(O))[3];    \
    \
    _r4 = fv_unpacklo(_r4,_rA); \
    _rC = fv_shuffle(_r7,_r9,2);    \
    _r5 = fv_unpacklo(_r5,_r9); \
    _r7 = fv_shuffle(_r6,_rA,2);    \
    \
    _rC = fv_xor(_rC,_mm_set_pd(-0.0,-0.0));    \
    \
    _r8 = fv_add(_r0,_r4);  \
    _rB = fv_add(_r1,_r5);  \
    _r9 = fv_add(_r2,_rC);  \
    _rA = fv_add(_r3,_r7);  \
    \
    ((f_vector*)(O))[0] = _r8;  \
    ((f_vector*)(O))[1] = _rB;  \
    ((f_vector*)(O))[2] = _r9;  \
    ((f_vector*)(O))[3] = _rA;  \
    \
    _r0 = fv_sub(_r0,_r4);  \
    _r1 = fv_sub(_r1,_r5);  \
    _r2 = fv_sub(_r2,_rC);  \
    _r3 = fv_sub(_r3,_r7);  \
    \
    ((f_vector*)(O))[4] = _r0;  \
    ((f_vector*)(O))[5] = _r1;  \
    ((f_vector*)(O))[6] = _r2;  \
    ((f_vector*)(O))[7] = _r3;  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
