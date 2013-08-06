/* sfft_cb_f64v1_t32_Power7.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 06/02/2011
 * Last Modified    : 06/02/2011
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t32     =   32-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t32_Power7_H
#define _sfft_cb_f64v1_t32_Power7_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t32_forward_Power7(T,tw){    \
    f_vector *_T = (f_vector*)(T);  \
    \
    const f_vector *_w2 = (tw)->w2.w[5];    \
    const f_vector *_w1 = (tw)->w1.w[5];    \
    const f_vector *_w3 = (tw)->w3.w[5];    \
    \
    sfft_cb_dt_b4w_m32_forward_u1( \
        _T +  0,_T +  8,_T + 16,_T + 24,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m32_forward_u1( \
        _T +  4,_T + 12,_T + 20,_T + 28,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    \
    _w1 = (tw)->w1.P;   \
    sfft_cb_f64v1_t8_forward_Power7(_T +  0,_w1);  \
    sfft_cb_f64v1_t8_forward_Power7(_T +  8,_w1);  \
    sfft_cb_f64v1_t8_forward_Power7(_T + 16,_w1);  \
    sfft_cb_f64v1_t8_forward_Power7(_T + 24,_w1);  \
}
#define sfft_cb_f64v1_t32_inverse_Power7(T,tw){    \
    f_vector *_T = (f_vector*)(T);  \
    \
    const f_vector *_w1 = (tw)->w1.P;   \
    sfft_cb_f64v1_t8_inverse_Power7(_T +  0,_w1);  \
    sfft_cb_f64v1_t8_inverse_Power7(_T +  8,_w1);  \
    sfft_cb_f64v1_t8_inverse_Power7(_T + 16,_w1);  \
    sfft_cb_f64v1_t8_inverse_Power7(_T + 24,_w1);  \
    \
    const f_vector *_w2 = (tw)->w2.w[5];    \
    _w1 = (tw)->w1.w[5];    \
    const f_vector *_w3 = (tw)->w3.w[5];    \
    \
    sfft_cb_dt_b4w_m32_inverse_u1( \
        _T +  0,_T +  8,_T + 16,_T + 24,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m32_inverse_u1( \
        _T +  4,_T + 12,_T + 20,_T + 28,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
