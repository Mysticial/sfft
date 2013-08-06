/* sfft_cb_v0_t32_Default.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/16/2010
 * Last Modified    : 02/04/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      v0      =   Vectorize by 1
 *      t32     =   32-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_v0_t32_Default_H
#define _sfft_cb_v0_t32_Default_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_v0_t32_forward_Default(I,O,tw){    \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w2 = (tw)->r1_2.table[5];  \
    _w1 = (tw)->r1_1.table[5];  \
    _w3 = (tw)->r1_3.table[5];  \
    \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  0,_I + 16,_I + 32,_I + 48,    \
        _I +  0,_I + 16,_I + 32,_I + 48,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  2,_I + 18,_I + 34,_I + 50,    \
        _I +  2,_I + 18,_I + 34,_I + 50,    \
        _w2 +  2,_w1 +  2,_w3 +  2  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  4,_I + 20,_I + 36,_I + 52,    \
        _I +  4,_I + 20,_I + 36,_I + 52,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  6,_I + 22,_I + 38,_I + 54,    \
        _I +  6,_I + 22,_I + 38,_I + 54,    \
        _w2 +  6,_w1 +  6,_w3 +  6  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  8,_I + 24,_I + 40,_I + 56,    \
        _I +  8,_I + 24,_I + 40,_I + 56,    \
        _w2 +  8,_w1 +  8,_w3 +  8  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 10,_I + 26,_I + 42,_I + 58,    \
        _I + 10,_I + 26,_I + 42,_I + 58,    \
        _w2 + 10,_w1 + 10,_w3 + 10  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 12,_I + 28,_I + 44,_I + 60,    \
        _I + 12,_I + 28,_I + 44,_I + 60,    \
        _w2 + 12,_w1 + 12,_w3 + 12  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 14,_I + 30,_I + 46,_I + 62,    \
        _I + 14,_I + 30,_I + 46,_I + 62,    \
        _w2 + 14,_w1 + 14,_w3 + 14  \
    );  \
    \
    _w1 = (tw)->r1_1.ptr;   \
    sfft_cb_v0_t8_forward_Default(_I +  0,_O +  0,_w1);    \
    sfft_cb_v0_t8_forward_Default(_I + 16,_O + 16,_w1);    \
    sfft_cb_v0_t8_forward_Default(_I + 32,_O + 32,_w1);    \
    sfft_cb_v0_t8_forward_Default(_I + 48,_O + 48,_w1);    \
}
#define sfft_cb_v0_t32_inverse_Default(I,O,tw){    \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w1 = (tw)->r1_1.ptr;   \
    sfft_cb_v0_t8_inverse_Default(_I +  0,_O +  0,_w1);    \
    sfft_cb_v0_t8_inverse_Default(_I + 16,_O + 16,_w1);    \
    sfft_cb_v0_t8_inverse_Default(_I + 32,_O + 32,_w1);    \
    sfft_cb_v0_t8_inverse_Default(_I + 48,_O + 48,_w1);    \
    \
    _w2 = (tw)->r1_2.table[5];  \
    _w1 = (tw)->r1_1.table[5];  \
    _w3 = (tw)->r1_3.table[5];  \
    \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  0,_O + 16,_O + 32,_O + 48,    \
        _O +  0,_O + 16,_O + 32,_O + 48,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  2,_O + 18,_O + 34,_O + 50,    \
        _O +  2,_O + 18,_O + 34,_O + 50,    \
        _w2 +  2,_w1 +  2,_w3 +  2  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  4,_O + 20,_O + 36,_O + 52,    \
        _O +  4,_O + 20,_O + 36,_O + 52,    \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  6,_O + 22,_O + 38,_O + 54,    \
        _O +  6,_O + 22,_O + 38,_O + 54,    \
        _w2 +  6,_w1 +  6,_w3 +  6  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  8,_O + 24,_O + 40,_O + 56,    \
        _O +  8,_O + 24,_O + 40,_O + 56,    \
        _w2 +  8,_w1 +  8,_w3 +  8  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 10,_O + 26,_O + 42,_O + 58,    \
        _O + 10,_O + 26,_O + 42,_O + 58,    \
        _w2 + 10,_w1 + 10,_w3 + 10  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 12,_O + 28,_O + 44,_O + 60,    \
        _O + 12,_O + 28,_O + 44,_O + 60,    \
        _w2 + 12,_w1 + 12,_w3 + 12  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 14,_O + 30,_O + 46,_O + 62,    \
        _O + 14,_O + 30,_O + 46,_O + 62,    \
        _w2 + 14,_w1 + 14,_w3 + 14  \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
