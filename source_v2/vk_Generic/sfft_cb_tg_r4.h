/* sfft_cbs_tg_r4.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/30/2011
 * Last Modified    : 04/16/2012
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
#define sfft_cb_tg_r4_t0_u0(   \
    loop0,  \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3,    \
    w2,w1,w3,   \
    is,ie   \
){  \
    register i_ptr _c = (is);   \
    \
    do{ \
        loop0(  \
            (char*)(I0) + _c,   \
            (char*)(I1) + _c,   \
            (char*)(I2) + _c,   \
            (char*)(I3) + _c,   \
            (char*)(O0) + _c,   \
            (char*)(O1) + _c,   \
            (char*)(O2) + _c,   \
            (char*)(O3) + _c,   \
            (const char*)(w2)  + _c,    \
            (const char*)(w1)  + _c,    \
            (const char*)(w3)  + _c     \
        );  \
        \
        _c += 2 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
#define sfft_cb_tg_r4_t0_u1(   \
    loop0,  \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3,    \
    w2,w1,w3,   \
    is,ie   \
){  \
    register i_ptr _c = (is);   \
    \
    do{ \
        loop0(  \
            (char*)(I0) + _c,   \
            (char*)(I1) + _c,   \
            (char*)(I2) + _c,   \
            (char*)(I3) + _c,   \
            (char*)(O0) + _c,   \
            (char*)(O1) + _c,   \
            (char*)(O2) + _c,   \
            (char*)(O3) + _c,   \
            (const char*)(w2)  + _c,    \
            (const char*)(w1)  + _c,    \
            (const char*)(w3)  + _c     \
        );  \
        _c += 2 * sizeof(f_vector); \
        \
        loop0(  \
            (char*)(I0) + _c,   \
            (char*)(I1) + _c,   \
            (char*)(I2) + _c,   \
            (char*)(I3) + _c,   \
            (char*)(O0) + _c,   \
            (char*)(O1) + _c,   \
            (char*)(O2) + _c,   \
            (char*)(O3) + _c,   \
            (const char*)(w2)  + _c,    \
            (const char*)(w1)  + _c,    \
            (const char*)(w3)  + _c     \
        );  \
        _c += 2 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_tg_r4i_t0_u0(   \
    loop0,  \
    T0,T1,T2,T3,    \
    w2,w1,w3,   \
    is,ie   \
){  \
    register i_ptr _c = (is);   \
    \
    do{ \
        loop0(  \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (char*)(T2) + _c,   \
            (char*)(T3) + _c,   \
            (char*)(T0) + _c,   \
            (char*)(T1) + _c,   \
            (char*)(T2) + _c,   \
            (char*)(T3) + _c,   \
            (const char*)(w2)  + _c,    \
            (const char*)(w1)  + _c,    \
            (const char*)(w3)  + _c     \
        );  \
        \
        _c += 2 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
#define sfft_cb_tg_r4i_t1_u0(   \
    loop0,  \
    T0,T1,T2,T3,    \
    w2,w1,w3,   \
    is,ie   \
){  \
    register i_ptr _c = (is);   \
    f_vector *_T0 = T0; \
    f_vector *_T1 = T1; \
    f_vector *_T2 = T2; \
    f_vector *_T3 = T3; \
    const f_vector *_w2 = w2;   \
    const f_vector *_w1 = w1;   \
    const f_vector *_w3 = w3;   \
    f_vector *_stop = (f_vector*)((char*)T0 + ie - is); \
    \
    do{ \
        loop0(  \
            _T0,_T1,_T2,_T3,    \
            _T0,_T1,_T2,_T3,    \
            _w2,_w1,_w3     \
        );  \
        \
        _T0 += 2;   \
        _T1 += 2;   \
        _T2 += 2;   \
        _T3 += 2;   \
        _w2 += 2;   \
        _w1 += 2;   \
        _w3 += 2;   \
    }while (_T0 < _stop);   \
}
#define sfft_cb_tg_r4i_t1_u1(   \
    loop0,  \
    T0,T1,T2,T3,    \
    w2,w1,w3,   \
    is,ie   \
){  \
    register i_ptr _c = (is);   \
    f_vector *_T0 = T0; \
    f_vector *_T1 = T1; \
    f_vector *_T2 = T2; \
    f_vector *_T3 = T3; \
    const f_vector *_w2 = w2;   \
    const f_vector *_w1 = w1;   \
    const f_vector *_w3 = w3;   \
    f_vector *_stop = (f_vector*)((char*)T0 + ie - is); \
    \
    do{ \
        loop0(  \
            _T0 + 0,_T1 + 0,_T2 + 0,_T3 + 0,    \
            _T0 + 0,_T1 + 0,_T2 + 0,_T3 + 0,    \
            _w2 + 0,_w1 + 0,_w3 + 0     \
        );  \
        loop0(  \
            _T0 + 2,_T1 + 2,_T2 + 2,_T3 + 2,    \
            _T0 + 2,_T1 + 2,_T2 + 2,_T3 + 2,    \
            _w2 + 2,_w1 + 2,_w3 + 2     \
        );  \
        \
        _T0 += 4;   \
        _T1 += 4;   \
        _T2 += 4;   \
        _T3 += 4;   \
        _w2 += 4;   \
        _w1 += 4;   \
        _w3 += 4;   \
    }while (_T0 < _stop);   \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
