/* sfft_cb_f64v1_t32_SSE3.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/16/2010
 * Last Modified    : 02/05/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t32     =   32-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t32_SSE3_H
#define _sfft_cb_f64v1_t32_SSE3_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t32_forward_SSE3(I,O,tw){  \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w2 = (tw)->r1_2.table[5];  \
    _w1 = (tw)->r1_1.table[5];  \
    _w3 = (tw)->r1_3.table[5];  \
    \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  0,_I +  8,_I + 16,_I + 24,    \
        _I +  0,_I +  8,_I + 16,_I + 24,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  2,_I + 10,_I + 18,_I + 26,    \
        _I +  2,_I + 10,_I + 18,_I + 26,    \
        _w2 +  2,_w1 +  2,_w3 +  2  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  4,_I + 12,_I + 20,_I + 28,    \
        _I +  4,_I + 12,_I + 20,_I + 28,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  6,_I + 14,_I + 22,_I + 30,    \
        _I +  6,_I + 14,_I + 22,_I + 30,    \
        _w2 +  6,_w1 +  6,_w3 +  6  \
    );  \
    \
    _w1 = (tw)->r1_1.ptr;   \
    sfft_cb_f64v1_t8_forward_SSE3(_I +  0,_O +  0,_w1);    \
    sfft_cb_f64v1_t8_forward_SSE3(_I +  8,_O +  8,_w1);    \
    sfft_cb_f64v1_t8_forward_SSE3(_I + 16,_O + 16,_w1);    \
    sfft_cb_f64v1_t8_forward_SSE3(_I + 24,_O + 24,_w1);    \
}
#define sfft_cb_f64v1_t32_inverse_SSE3(I,O,tw){    \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w1 = (tw)->r1_1.ptr;   \
    sfft_cb_f64v1_t8_inverse_SSE3(_I +  0,_O +  0,_w1);    \
    sfft_cb_f64v1_t8_inverse_SSE3(_I +  8,_O +  8,_w1);    \
    sfft_cb_f64v1_t8_inverse_SSE3(_I + 16,_O + 16,_w1);    \
    sfft_cb_f64v1_t8_inverse_SSE3(_I + 24,_O + 24,_w1);    \
    \
    _w2 = (tw)->r1_2.table[5];  \
    _w1 = (tw)->r1_1.table[5];  \
    _w3 = (tw)->r1_3.table[5];  \
    \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  0,_O +  8,_O + 16,_O + 24,    \
        _O +  0,_O +  8,_O + 16,_O + 24,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  2,_O + 10,_O + 18,_O + 26,    \
        _O +  2,_O + 10,_O + 18,_O + 26,    \
        _w2 +  2,_w1 +  2,_w3 +  2  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  4,_O + 12,_O + 20,_O + 28,    \
        _O +  4,_O + 12,_O + 20,_O + 28,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  6,_O + 14,_O + 22,_O + 30,    \
        _O +  6,_O + 14,_O + 22,_O + 30,    \
        _w2 +  6,_w1 +  6,_w3 +  6  \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
