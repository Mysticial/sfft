/* sfft_cbs_tg_r2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/30/2011
 * Last Modified    : 04/16/2012
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
#define sfft_cb_tg_r2_t0_u0(   \
    loop0,  \
    I0,I1,  \
    O0,O1,  \
    w1,  \
    is,ie   \
){   \
    register i_ptr _c = (is);   \
    \
    do{ \
        loop0(  \
            (char*)(I0) + _c,   \
            (char*)(I1) + _c,   \
            (char*)(O0) + _c,   \
            (char*)(O1) + _c,   \
            (const char*)(w1)  + _c \
        );  \
        \
        _c += 2 * sizeof(f_vector); \
    }while (_c < (ie)); \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
