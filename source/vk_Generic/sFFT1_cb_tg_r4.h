/* sfft_cbs_tg_r4.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/27/2010
 * Last Modified    : 09/27/2010
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform (simple transform - no padding)
 *      tg      =   Type Generic
 *      r4      =   Radix-4 Row Reduction
 * 
 */

#pragma once
#ifndef _sfft_cb_tg_r4_H
#define _sfft_cb_tg_r4_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 1
#define sfft_cb_tg_r4_t0_u0(   \
    loop0,  \
    T0,T1,T2,T3,    \
    k,  \
    tw, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w2 = (tw)->w2.w[k];    \
    const f_vector *_w1 = (tw)->w1.w[k];    \
    const f_vector *_w3 = (tw)->w3.w[k];    \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (char*)(T2) + _c,   \
            (char*)(T3) + _c,   \
            (const char*)_w2  + _c, \
            (const char*)_w1  + _c, \
            (const char*)_w3  + _c  \
        );  \
        \
        _c += 2 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
#define sfft_cb_tg_r4p_t0_u0(  \
    loop0,  \
    T0,T1,T2,T3,    \
    wk,wi,  \
    tw, \
    uk, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w2 = (tw)->w2.w[wk] + wi;  \
    const f_vector *_w1 = (tw)->w1.w[wk] + wi;  \
    const f_vector *_w3 = (tw)->w3.w[wk] + wi;  \
    \
    const i_ptr _inc = 2 * sizeof(f_vector) << (uk);    \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (char*)(T2) + _c,   \
            (char*)(T3) + _c,   \
            (const char*)_w2  + _c, \
            (const char*)_w1  + _c, \
            (const char*)_w3  + _c  \
        );  \
        \
        _c += _inc; \
    }while (_c < (ie)); \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 2
#define sfft_cb_tg_r4_t0_u1(   \
    loop0,  \
    T0,T1,T2,T3,    \
    k,  \
    tw, \
    uk, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w2 = (tw)->w2.w[k];    \
    const f_vector *_w1 = (tw)->w1.w[k];    \
    const f_vector *_w3 = (tw)->w3.w[k];    \
    \
    const i_ptr inc = 2 * sizeof(f_vector) << (uk); \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c + 0*inc,   \
            (char*)(T1) + _c + 0*inc,   \
            (char*)(T2) + _c + 0*inc,   \
            (char*)(T3) + _c + 0*inc,   \
            (const char*)_w2  + _c + 0*inc, \
            (const char*)_w1  + _c + 0*inc, \
            (const char*)_w3  + _c + 0*inc  \
        );  \
        loop0(  \
            (char*)(T0) + _c + 1*inc,   \
            (char*)(T1) + _c + 1*inc,   \
            (char*)(T2) + _c + 1*inc,   \
            (char*)(T3) + _c + 1*inc,   \
            (const char*)_w2  + _c + 1*inc, \
            (const char*)_w1  + _c + 1*inc, \
            (const char*)_w3  + _c + 1*inc  \
        );  \
        \
        _c += inc << 1; \
    }while (_c < (ie)); \
}
#define sfft_cb_tg_r4p_t0_u1(  \
    loop0,  \
    T0,T1,T2,T3,    \
    wk,wi,  \
    tw, \
    uk, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w2 = (tw)->w2.w[wk] + wi;  \
    const f_vector *_w1 = (tw)->w1.w[wk] + wi;  \
    const f_vector *_w3 = (tw)->w3.w[wk] + wi;  \
    \
    const i_ptr inc = 2 * sizeof(f_vector) << (uk); \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c + 0*inc,   \
            (char*)(T1) + _c + 0*inc,   \
            (char*)(T2) + _c + 0*inc,   \
            (char*)(T3) + _c + 0*inc,   \
            (const char*)_w2  + _c + 0*inc, \
            (const char*)_w1  + _c + 0*inc, \
            (const char*)_w3  + _c + 0*inc  \
        );  \
        loop0(  \
            (char*)(T0) + _c + 1*inc,   \
            (char*)(T1) + _c + 1*inc,   \
            (char*)(T2) + _c + 1*inc,   \
            (char*)(T3) + _c + 1*inc,   \
            (const char*)_w2  + _c + 1*inc, \
            (const char*)_w1  + _c + 1*inc, \
            (const char*)_w3  + _c + 1*inc  \
        );  \
        \
        _c += inc << 1; \
    }while (_c < (ie)); \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 4
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifndef sfft_cb_tg_r4_UNROLL
#define sfft_cb_tg_r4_UNROLL   1
#endif

#if sfft_cb_tg_r4_UNROLL >= 1
#define sfft_cb_tg_r4      sfft_cb_tg_r4_t0_u1
#else
#define sfft_cb_tg_r4      sfft_cb_tg_r4_t0_u0
#endif

#if sfft_cb_tg_r4_UNROLL >= 1
#define sfft_i_cb_r4_forward(  \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 2);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    register f_word *T2 = T1 + block;   \
    register f_word *T3 = T2 + block;   \
    \
    sfft_cb_tg_r4_t0_u1(   \
        sfft_cb_dt_b4w_m16_forward_u0, \
        T0,T1,T2,T3,    \
        k,  \
        tw, \
        0,  \
        is,ie   \
    );  \
}
#define sfft_i_cb_r4_inverse(  \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 2);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    register f_word *T2 = T1 + block;   \
    register f_word *T3 = T2 + block;   \
    \
    sfft_cb_tg_r4_t0_u1(   \
        sfft_cb_dt_b4w_m16_inverse_u0, \
        T0,T1,T2,T3,    \
        k,  \
        tw, \
        0,  \
        is,ie   \
    );  \
}
#else
#define sfft_i_cb_r4_forward(  \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 2);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    register f_word *T2 = T1 + block;   \
    register f_word *T3 = T2 + block;   \
    \
    sfft_cb_tg_r4_t0_u0(   \
        sfft_cb_dt_b4w_m16_forward_u0, \
        T0,T1,T2,T3,    \
        k,  \
        tw, \
        0,  \
        is,ie   \
    );  \
}
#define sfft_i_cb_r4_inverse(  \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 2);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    register f_word *T2 = T1 + block;   \
    register f_word *T3 = T2 + block;   \
    \
    sfft_cb_tg_r4_t0_u0(   \
        sfft_cb_dt_b4w_m16_inverse_u0, \
        T0,T1,T2,T3,    \
        k,  \
        tw, \
        0,  \
        is,ie   \
    );  \
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifndef sfft_cb_tg_r4p_UNROLL
#define sfft_cb_tg_r4p_UNROLL      1
#endif

#if sfft_cb_tg_r4p_UNROLL >= 1
#define sfft_cb_tg_r4p     sfft_cb_tg_r4p_t0_u1
#else
#define sfft_cb_tg_r4p     sfft_cb_tg_r4p_t0_u0
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
