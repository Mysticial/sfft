/* sfft_cb_v0_t64_Default.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/18/2010
 * Last Modified    : 02/04/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      v0      =   Vectorize by 1
 *      t64     =   64-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_v0_t64_Default_H
#define _sfft_cb_v0_t64_Default_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_v0_t64_forward_Default(I,O,tw){    \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    _w2 = (tw)->r1_2.table[6];  \
    _w1 = (tw)->r1_1.table[6];  \
    _w3 = (tw)->r1_3.table[6];  \
    \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  0,_I + 32,_I + 64,_I + 96,    \
        _I +  0,_I + 32,_I + 64,_I + 96,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  2,_I + 34,_I + 66,_I + 98,    \
        _I +  2,_I + 34,_I + 66,_I + 98,    \
        _w2 +  2,_w1 +  2,_w3 +  2  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  4,_I + 36,_I + 68,_I + 100,   \
        _I +  4,_I + 36,_I + 68,_I + 100,   \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  6,_I + 38,_I + 70,_I + 102,   \
        _I +  6,_I + 38,_I + 70,_I + 102,   \
        _w2 +  6,_w1 +  6,_w3 +  6  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I +  8,_I + 40,_I + 72,_I + 104,   \
        _I +  8,_I + 40,_I + 72,_I + 104,   \
        _w2 +  8,_w1 +  8,_w3 +  8  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 10,_I + 42,_I + 74,_I + 106,   \
        _I + 10,_I + 42,_I + 74,_I + 106,   \
        _w2 + 10,_w1 + 10,_w3 + 10  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 12,_I + 44,_I + 76,_I + 108,   \
        _I + 12,_I + 44,_I + 76,_I + 108,   \
        _w2 + 12,_w1 + 12,_w3 + 12  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 14,_I + 46,_I + 78,_I + 110,   \
        _I + 14,_I + 46,_I + 78,_I + 110,   \
        _w2 + 14,_w1 + 14,_w3 + 14  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 16,_I + 48,_I + 80,_I + 112,   \
        _I + 16,_I + 48,_I + 80,_I + 112,   \
        _w2 + 16,_w1 + 16,_w3 + 16  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 18,_I + 50,_I + 82,_I + 114,   \
        _I + 18,_I + 50,_I + 82,_I + 114,   \
        _w2 + 18,_w1 + 18,_w3 + 18  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 20,_I + 52,_I + 84,_I + 116,   \
        _I + 20,_I + 52,_I + 84,_I + 116,   \
        _w2 + 20,_w1 + 20,_w3 + 20  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 22,_I + 54,_I + 86,_I + 118,   \
        _I + 22,_I + 54,_I + 86,_I + 118,   \
        _w2 + 22,_w1 + 22,_w3 + 22  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 24,_I + 56,_I + 88,_I + 120,   \
        _I + 24,_I + 56,_I + 88,_I + 120,   \
        _w2 + 24,_w1 + 24,_w3 + 24  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 26,_I + 58,_I + 90,_I + 122,   \
        _I + 26,_I + 58,_I + 90,_I + 122,   \
        _w2 + 26,_w1 + 26,_w3 + 26  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 28,_I + 60,_I + 92,_I + 124,   \
        _I + 28,_I + 60,_I + 92,_I + 124,   \
        _w2 + 28,_w1 + 28,_w3 + 28  \
    );  \
    sfft_cb_dt_b4w_m16_forward_u0( \
        _I + 30,_I + 62,_I + 94,_I + 126,   \
        _I + 30,_I + 62,_I + 94,_I + 126,   \
        _w2 + 30,_w1 + 30,_w3 + 30  \
    );  \
    \
    sfft_cb_v0_t16_forward_Default((f_vector*)(I) +  0,(f_vector*)(O) +  0,tw);    \
    sfft_cb_v0_t16_forward_Default((f_vector*)(I) + 32,(f_vector*)(O) + 32,tw);    \
    sfft_cb_v0_t16_forward_Default((f_vector*)(I) + 64,(f_vector*)(O) + 64,tw);    \
    sfft_cb_v0_t16_forward_Default((f_vector*)(I) + 96,(f_vector*)(O) + 96,tw);    \
}
#define sfft_cb_v0_t64_inverse_Default(I,O,tw){    \
    f_vector *_I = (f_vector*)(I);  \
    f_vector *_O = (f_vector*)(O);  \
    const f_vector *_w1,*_w2,*_w3;  \
    \
    sfft_cb_v0_t16_inverse_Default((f_vector*)(I) +  0,(f_vector*)(O) +  0,tw);    \
    sfft_cb_v0_t16_inverse_Default((f_vector*)(I) + 32,(f_vector*)(O) + 32,tw);    \
    sfft_cb_v0_t16_inverse_Default((f_vector*)(I) + 64,(f_vector*)(O) + 64,tw);    \
    sfft_cb_v0_t16_inverse_Default((f_vector*)(I) + 96,(f_vector*)(O) + 96,tw);    \
    \
    _w2 = (tw)->r1_2.table[6];  \
    _w1 = (tw)->r1_1.table[6];  \
    _w3 = (tw)->r1_3.table[6];  \
    \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  0,_O + 32,_O + 64,_O + 96,    \
        _O +  0,_O + 32,_O + 64,_O + 96,    \
        _w2 +  0,_w1 +  0,_w3 +  0  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  2,_O + 34,_O + 66,_O + 98,    \
        _O +  2,_O + 34,_O + 66,_O + 98,    \
        _w2 +  2,_w1 +  2,_w3 +  2  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  4,_O + 36,_O + 68,_O + 100,   \
        _O +  4,_O + 36,_O + 68,_O + 100,   \
        _w2 +  4,_w1 +  4,_w3 +  4  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  6,_O + 38,_O + 70,_O + 102,   \
        _O +  6,_O + 38,_O + 70,_O + 102,   \
        _w2 +  6,_w1 +  6,_w3 +  6  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O +  8,_O + 40,_O + 72,_O + 104,   \
        _O +  8,_O + 40,_O + 72,_O + 104,   \
        _w2 +  8,_w1 +  8,_w3 +  8  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 10,_O + 42,_O + 74,_O + 106,   \
        _O + 10,_O + 42,_O + 74,_O + 106,   \
        _w2 + 10,_w1 + 10,_w3 + 10  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 12,_O + 44,_O + 76,_O + 108,   \
        _O + 12,_O + 44,_O + 76,_O + 108,   \
        _w2 + 12,_w1 + 12,_w3 + 12  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 14,_O + 46,_O + 78,_O + 110,   \
        _O + 14,_O + 46,_O + 78,_O + 110,   \
        _w2 + 14,_w1 + 14,_w3 + 14  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 16,_O + 48,_O + 80,_O + 112,   \
        _O + 16,_O + 48,_O + 80,_O + 112,   \
        _w2 + 16,_w1 + 16,_w3 + 16  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 18,_O + 50,_O + 82,_O + 114,   \
        _O + 18,_O + 50,_O + 82,_O + 114,   \
        _w2 + 18,_w1 + 18,_w3 + 18  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 20,_O + 52,_O + 84,_O + 116,   \
        _O + 20,_O + 52,_O + 84,_O + 116,   \
        _w2 + 20,_w1 + 20,_w3 + 20  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 22,_O + 54,_O + 86,_O + 118,   \
        _O + 22,_O + 54,_O + 86,_O + 118,   \
        _w2 + 22,_w1 + 22,_w3 + 22  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 24,_O + 56,_O + 88,_O + 120,   \
        _O + 24,_O + 56,_O + 88,_O + 120,   \
        _w2 + 24,_w1 + 24,_w3 + 24  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 26,_O + 58,_O + 90,_O + 122,   \
        _O + 26,_O + 58,_O + 90,_O + 122,   \
        _w2 + 26,_w1 + 26,_w3 + 26  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 28,_O + 60,_O + 92,_O + 124,   \
        _O + 28,_O + 60,_O + 92,_O + 124,   \
        _w2 + 28,_w1 + 28,_w3 + 28  \
    );  \
    sfft_cb_dt_b4w_m16_inverse_u0( \
        _O + 30,_O + 62,_O + 94,_O + 126,   \
        _O + 30,_O + 62,_O + 94,_O + 126,   \
        _w2 + 30,_w1 + 30,_w3 + 30  \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
