/* sfft_cb_f64v1_t2_Power7.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 06/02/2011
 * Last Modified    : 06/02/2011
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t2      =   2-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t2_Power7_H
#define _sfft_cb_f64v1_t2_Power7_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t2_Power7(T){    \
    register f_vector _r0,_r1,_r2;  \
    \
    _r0 = ((const f_vector*)(T))[0];    \
    _r1 = ((const f_vector*)(T))[1];    \
    \
    _r2 = fv_mergeh(_r0,_r1);   \
    _r0 = fv_mergel(_r0,_r1);   \
    \
    _r1 = fv_add(_r2,_r0);  \
    _r2 = fv_sub(_r2,_r0);  \
    \
    _r0 = fv_mergeh(_r1,_r2);   \
    _r1 = fv_mergel(_r1,_r2);   \
    \
    ((f_vector*)(T))[0] = _r0;  \
    ((f_vector*)(T))[1] = _r1;  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
