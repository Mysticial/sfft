/* sfft_cb_f64v1_t16_SSE3.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/15/2010
 * Last Modified    : 02/05/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t16     =   16-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t16_SSE3_H
#define _sfft_cb_f64v1_t16_SSE3_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t16_forward_SSE3(I,O,tw){    \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    \
    const f_vector *_w2 = (tw)->r1_2.table[4];  \
    const f_vector *_w1 = (tw)->r1_1.table[4];  \
    const f_vector *_w3 = (tw)->r1_3.table[4];  \
    \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  0,_I +  4,_I +  8,_I + 12,    \
        _I +  0,_I +  4,_I +  8,_I + 12,    \
        _w2 + 0,_w1 + 0,_w3 + 0     \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  2,_I +  6,_I + 10,_I + 14,    \
        _I +  2,_I +  6,_I + 10,_I + 14,    \
        _w2 + 2,_w1 + 2,_w3 + 2     \
    );  \
    \
    sfft_cb_f64v1_t4_forward_SSE3(_I +  0,_O +  0);    \
    sfft_cb_f64v1_t4_forward_SSE3(_I +  4,_O +  4);    \
    sfft_cb_f64v1_t4_forward_SSE3(_I +  8,_O +  8);    \
    sfft_cb_f64v1_t4_forward_SSE3(_I + 12,_O + 12);    \
}
#define sfft_cb_f64v1_t16_inverse_SSE3(I,O,tw){    \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    \
    sfft_cb_f64v1_t4_inverse_SSE3(_I +  0,_O +  0);    \
    sfft_cb_f64v1_t4_inverse_SSE3(_I +  4,_O +  4);    \
    sfft_cb_f64v1_t4_inverse_SSE3(_I +  8,_O +  8);    \
    sfft_cb_f64v1_t4_inverse_SSE3(_I + 12,_O + 12);    \
    \
    const f_vector *_w2 = (tw)->r1_2.table[4];  \
    const f_vector *_w1 = (tw)->r1_1.table[4];  \
    const f_vector *_w3 = (tw)->r1_3.table[4];  \
    \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  0,_O +  4,_O +  8,_O + 12,    \
        _O +  0,_O +  4,_O +  8,_O + 12,    \
        _w2 + 0,_w1 + 0,_w3 + 0     \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  2,_O +  6,_O + 10,_O + 14,    \
        _O +  2,_O +  6,_O + 10,_O + 14,    \
        _w2 + 2,_w1 + 2,_w3 + 2     \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
