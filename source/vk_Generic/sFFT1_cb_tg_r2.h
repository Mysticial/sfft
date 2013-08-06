/* sfft_cbs_tg_r2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/30/2011
 * Last Modified    : 03/30/2011
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform (simple transform - no padding)
 *      tg      =   Type Generic
 *      r2      =   Radix-2 Row Reduction
 * 
 */

#pragma once
#ifndef _sfft_cb_tg_r2_H
#define _sfft_cb_tg_r2_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 1
#define sfft_cb_tg_r2_t0_u0(   \
    loop0,  \
    T0,T1,  \
    k,  \
    tw, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w1 = (tw)->w1.w[k];    \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (const char*)_w1  + _c  \
        );  \
        \
        _c += 2 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
#define sfft_cb_tg_r2p_t0_u0(  \
    loop0,  \
    T0,T1,  \
    wk,wi,  \
    tw, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w1 = (tw)->w1.w[wk] + wi;  \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (const char*)_w1  + _c  \
        );  \
        \
        _c += 2 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 2
#define sfft_cb_tg_r2_t0_u1(   \
    loop0,  \
    T0,T1,  \
    k,  \
    tw, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w1 = (tw)->w1.w[k];    \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (const char*)_w1  + _c  \
        );  \
        \
        _c += 4 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
#define sfft_cb_tg_r2p_t0_u1(  \
    loop0,  \
    T0,T1,  \
    wk,wi,  \
    tw, \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    const f_vector *_w1 = (tw)->w1.w[wk] + wi;  \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (const char*)_w1  + _c  \
        );  \
        \
        _c += 4 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Unroll 4
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifndef sfft_cb_tg_r2_UNROLL
#define sfft_cb_tg_r2_UNROLL   1
#endif

#if sfft_cb_tg_r2_UNROLL >= 1
#define sfft_i_cb_r2_forward_0(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u1(   \
        sfft_cb_dt_b2w_m16_forward_0_u1,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#define sfft_i_cb_r2_forward_1(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u1(   \
        sfft_cb_dt_b2w_m16_forward_1_u1,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#define sfft_i_cb_r2_inverse_0(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u1(   \
        sfft_cb_dt_b2w_m16_inverse_0_u1,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#define sfft_i_cb_r2_inverse_1(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u1(   \
        sfft_cb_dt_b2w_m16_inverse_1_u1,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#else
#define sfft_i_cb_r2_forward_0(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u0(   \
        sfft_cb_dt_b2w_m16_forward_0_u0,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#define sfft_i_cb_r2_forward_1(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u0(   \
        sfft_cb_dt_b2w_m16_forward_1_u0,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#define sfft_i_cb_r2_inverse_0(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u0(   \
        sfft_cb_dt_b2w_m16_inverse_0_u0,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#define sfft_i_cb_r2_inverse_1(    \
    T,k,    \
    tw, \
    is,ie   \
){   \
    i_ptr block = (i_ptr)2 << (k - 1);  \
    \
    register f_word *T0 = (f_word*)(T); \
    register f_word *T1 = T0 + block;   \
    \
    sfft_cb_tg_r2_t0_u0(   \
        sfft_cb_dt_b2w_m16_inverse_1_u0,   \
        T0,T1,  \
        k,  \
        tw, \
        is,ie   \
    );  \
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
