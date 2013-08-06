/* sfft_cb_f64v2_t64_AVX.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/31/2011
 * Last Modified    : 03/31/2011
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v2   =   64-bit floating point (vectorize by 4)
 *      t64     =   64-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v2_t64_AVX_H
#define _sfft_cb_f64v2_t64_AVX_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v2_t64_forward_AVX(I,O,tw){ \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w2 = (tw)->r1_2.table[6];  \
    _w1 = (tw)->r1_1.table[6];  \
    _w3 = (tw)->r1_3.table[6];  \
    \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  0,_I +  8,_I + 16,_I + 24,    \
        _I +  0,_I +  8,_I + 16,_I + 24,    \
        _w2 + 0,_w1 + 0,_w3 + 0 \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  2,_I + 10,_I + 18,_I + 26,    \
        _I +  2,_I + 10,_I + 18,_I + 26,    \
        _w2 + 2,_w1 + 2,_w3 + 2 \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  4,_I + 12,_I + 20,_I + 28,    \
        _I +  4,_I + 12,_I + 20,_I + 28,    \
        _w2 + 4,_w1 + 4,_w3 + 4 \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  6,_I + 14,_I + 22,_I + 30,    \
        _I +  6,_I + 14,_I + 22,_I + 30,    \
        _w2 + 6,_w1 + 6,_w3 + 6 \
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
        _I +  0,_O +  0,    \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_forward_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I +  8,_O +  8,    \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_forward_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 16,_O + 16,    \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_forward_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 24,_O + 24,    \
        _w2,_w1,_w3 \
    );  \
}
#define sfft_cb_f64v2_t64_inverse_AVX(I,O,tw){ \
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
        _I +  0,_O +  0,    \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_inverse_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I +  8,_O +  8,    \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_inverse_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 16,_O + 16,    \
        _w2,_w1,_w3 \
    );  \
    sfft_cb_f64v2_t16_inverse_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        _I + 24,_O + 24,    \
        _w2,_w1,_w3 \
    );  \
    \
    _w2 = (tw)->r1_2.table[6];  \
    _w1 = (tw)->r1_1.table[6];  \
    _w3 = (tw)->r1_3.table[6];  \
    \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  0,_O +  8,_O + 16,_O + 24,    \
        _O +  0,_O +  8,_O + 16,_O + 24,    \
        _w2 + 0,_w1 + 0,_w3 + 0 \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  2,_O + 10,_O + 18,_O + 26,    \
        _O +  2,_O + 10,_O + 18,_O + 26,    \
        _w2 + 2,_w1 + 2,_w3 + 2 \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  4,_O + 12,_O + 20,_O + 28,    \
        _O +  4,_O + 12,_O + 20,_O + 28,    \
        _w2 + 4,_w1 + 4,_w3 + 4 \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  6,_O + 14,_O + 22,_O + 30,    \
        _O +  6,_O + 14,_O + 22,_O + 30,    \
        _w2 + 6,_w1 + 6,_w3 + 6 \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
