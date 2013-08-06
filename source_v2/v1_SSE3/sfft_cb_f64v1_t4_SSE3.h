/* sfft_cb_f64v1_t4_SSE3.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/12/2010
 * Last Modified    : 09/12/2010
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t4      =   4-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t4_SSE3_H
#define _sfft_cb_f64v1_t4_SSE3_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t4_forward_SSE3(I,O){    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    \
    _r0 = ((const f_vector*)(I))[0];    \
    _r1 = ((const f_vector*)(I))[1];    \
    _r2 = ((const f_vector*)(I))[2];    \
    _r3 = ((const f_vector*)(I))[3];    \
    \
    _r4 = fv_sub(_r0,_r2);  \
    _r5 = fv_sub(_r1,_r3);  \
    \
    _r0 = fv_add(_r0,_r2);  \
    _r1 = fv_add(_r1,_r3);  \
    \
    _r2 = fv_shuffle(_r4,_r5,2);    \
    _r5 = fv_shuffle(_r5,_r4,2);    \
    \
    _r2 = fv_xor(_r2,_mm_set_pd(-0.0,0.0)); \
    \
    _r4 = fv_hadd(_r0,_r2); \
    _r3 = fv_hadd(_r1,_r5); \
    _r0 = fv_hsub(_r0,_r2); \
    _r1 = fv_hsub(_r1,_r5); \
    \
    ((f_vector*)(O))[0] = fv_unpacklo(_r4,_r0); \
    ((f_vector*)(O))[1] = fv_unpacklo(_r3,_r1); \
    ((f_vector*)(O))[2] = fv_unpackhi(_r0,_r4); \
    ((f_vector*)(O))[3] = fv_unpackhi(_r1,_r3); \
}
#define sfft_cb_f64v1_t4_inverse_SSE3(I,O){    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    \
    _r0 = ((const f_vector*)(I))[0];    \
    _r1 = ((const f_vector*)(I))[1];    \
    _r2 = ((const f_vector*)(I))[2];    \
    _r3 = ((const f_vector*)(I))[3];    \
    \
    _r4 = fv_hsub(_r0,_r2); \
    _r5 = fv_hsub(_r1,_r3); \
    \
    _r0 = fv_hadd(_r0,_r2); \
    _r1 = fv_hadd(_r1,_r3); \
    \
	_r3 = fv_hsub(_r0,_r1); \
    _r2 = fv_hadd(_r0,_r1); \
	\
	_r0 = fv_unpacklo(_r4,_r5); \
	_r1 = fv_unpackhi(_r5,_r4); \
	_r1 = fv_xor(_r1,_mm_set_pd(0.0,-0.0)); \
	\
	_r4 = fv_add(_r0,_r1);  \
	_r5 = fv_sub(_r0,_r1);  \
	\
    ((f_vector*)(O))[0] = fv_unpacklo(_r2,_r4);  \
    ((f_vector*)(O))[1] = fv_unpackhi(_r2,_r4);  \
    ((f_vector*)(O))[2] = fv_unpacklo(_r3,_r5);  \
    ((f_vector*)(O))[3] = fv_unpackhi(_r3,_r5);  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
