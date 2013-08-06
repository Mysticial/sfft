/* sfft_cb_f64v1_t64_Power7.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/18/2010
 * Last Modified    : 09/18/2010
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t64     =   64-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t64_Power7_H
#define _sfft_cb_f64v1_t64_Power7_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t64_forward_Power7(T,tw){    \
    f_vector *_T = (f_vector*)(T);  \
    \
    const f_vector *_w2 = (tw)->w2.w[6];    \
    const f_vector *_w1 = (tw)->w1.w[6];    \
    const f_vector *_w3 = (tw)->w3.w[6];    \
    \
    sfft_cb_dt_b4w_m32_forward_u1( \
        _T +  0,_T + 16,_T + 32,_T + 48,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m32_forward_u1( \
        _T +  4,_T + 20,_T + 36,_T + 52,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m32_forward_u1( \
        _T +  8,_T + 24,_T + 40,_T + 56,    \
        _w2 +  8,_w1 +  8,_w3 +  8  \
    );  \
    sfft_cb_dt_b4w_m32_forward_u1( \
        _T + 12,_T + 28,_T + 44,_T + 60,    \
        _w2 + 12,_w1 + 12,_w3 + 12  \
    );  \
    \
    f_vector *_t = _T;  \
    sfft_cb_f64v1_t16_forward_Power7(_t +  0,tw);  \
    sfft_cb_f64v1_t16_forward_Power7(_t + 16,tw);  \
    sfft_cb_f64v1_t16_forward_Power7(_t + 32,tw);  \
    sfft_cb_f64v1_t16_forward_Power7(_t + 48,tw);  \
}
#define sfft_cb_f64v1_t64_inverse_Power7(T,tw){    \
    f_vector *_T = (f_vector*)(T);  \
    \
    f_vector *_t = _T;  \
    sfft_cb_f64v1_t16_inverse_Power7(_t +  0,tw);  \
    sfft_cb_f64v1_t16_inverse_Power7(_t + 16,tw);  \
    sfft_cb_f64v1_t16_inverse_Power7(_t + 32,tw);  \
    sfft_cb_f64v1_t16_inverse_Power7(_t + 48,tw);  \
    \
    const f_vector *_w2 = (tw)->w2.w[6];    \
    const f_vector *_w1 = (tw)->w1.w[6];    \
    const f_vector *_w3 = (tw)->w3.w[6];    \
    \
    sfft_cb_dt_b4w_m32_inverse_u1( \
        _T +  0,_T + 16,_T + 32,_T + 48,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m32_inverse_u1( \
        _T +  4,_T + 20,_T + 36,_T + 52,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m32_inverse_u1( \
        _T +  8,_T + 24,_T + 40,_T + 56,    \
        _w2 +  8,_w1 +  8,_w3 +  8  \
    );  \
    sfft_cb_dt_b4w_m32_inverse_u1( \
        _T + 12,_T + 28,_T + 44,_T + 60,    \
        _w2 + 12,_w1 + 12,_w3 + 12  \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
