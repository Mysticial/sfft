/* sfft_cb_f64v2_t32_AVX.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/31/2011
 * Last Modified    : 02/05/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v2   =   64-bit floating point (vectorize by 4)
 *      t32     =   32-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v2_t32_AVX_H
#define _sfft_cb_f64v2_t32_AVX_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v2_t32_forward_AVX(I,O,tw){ \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w1 = (tw)->r1_1.table[5];  \
    \
    sfft_cb_dt_b2w_m16_forward_0_u1(   \
        _I +  0,_I +  8,    \
        _w1 + 0 \
    );  \
    sfft_cb_dt_b2w_m16_forward_1_u1(   \
        _I +  4,_I + 12,    \
        _w1 + 0 \
    );  \
    \
    _w2 = (tw)->r1_2.ptr;   \
    _w1 = (tw)->r1_1.ptr;   \
    _w3 = (tw)->r1_3.ptr;   \
    \
    sfft_cb_f64v2_t16_forward_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 0,_O + 0,  \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_forward_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 8,_O + 8,  \
        _w2,_w1,_w3 \
    );  \
}
#define sfft_cb_f64v2_t32_inverse_AVX(I,O,tw){   \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w2 = (tw)->r1_2.ptr;   \
    _w1 = (tw)->r1_1.ptr;   \
    _w3 = (tw)->r1_3.ptr;   \
    \
    sfft_cb_f64v2_t16_inverse_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 0,_O + 0,  \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_inverse_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 8,_O + 8,  \
        _w2,_w1,_w3 \
    );  \
    \
    _w1 = (tw)->r1_1.table[5];  \
    \
    sfft_cb_dt_b2w_m16_inverse_0_u1(   \
        _O +  0,_O +  8,    \
        _w1 + 0 \
    );  \
    sfft_cb_dt_b2w_m16_inverse_1_u1(   \
        _O +  4,_O + 12,    \
        _w1 + 0 \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
