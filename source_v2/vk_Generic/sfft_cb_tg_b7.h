/* sfft_cb_tg_b7.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/22/2012
 * Last Modified    : 02/22/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      tg          =   Type Generic
 *      b7          =   Radix 7 butterfly
 * 
 * 
 * 
 *      This file implements a radix 7 butterfly using only vector operations.
 *  By setting the parameters, the macros in this file can be used on any
 *  machine that supports:
 *  
 *      -   Load
 *      -   Store
 *      -   Add
 *      -   Subtract
 *      -   Multiply
 * 
 *      Note that the size of the vector as well as the data type is irrelevant
 *  as they can also be set using the macro parameters.
 * 
 * 
 * 
 *      "m16"       specifies that the macros uses at most 16 data registers.
 *      "Default"   specifes that only the basic 5 instructions above are used.
 */

#pragma once
#ifndef _sfft_cb_tg_b7_H
#define _sfft_cb_tg_b7_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Scalar
//  wAr + wAi*i = e^(-2pi*i * 1/7)
//  wBr + wBi*i = e^(-2pi*i * 2/7)
//  wCr + wCi*i = e^(-2pi*i * 3/7)
#define sfft_cb_tg_vt7_m16_forward(  \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    T0,T1,T2,T3,T4,T5,T6,   \
    wAr,wAi,wBr,wBi,wCr,wCi \
){  \
    {   \
        vtype _r0 = ((const vtype*)(T0))[0]; \
        vtype _i0 = ((const vtype*)(T0))[1]; \
        \
        _t0 = ((const vtype*)(T1))[0];  \
        _t1 = ((const vtype*)(T1))[1];  \
        _t2 = ((const vtype*)(T6))[0];  \
        _t3 = ((const vtype*)(T6))[1];  \
        \
        vtype _ra1 = vadd(_t0,_t2); \
        vtype _ia1 = vadd(_t1,_t3); \
        vtype _rs1 = vsub(_t0,_t2); \
        vtype _is1 = vsub(_t1,_t3); \
        \
        _Ar = vadd(_r0,_ra1); \
        _Ai = vadd(_i0,_ia1); \
        \
        vtype _ra0 = vmul(_ra1,wAr); \
        vtype _ia0 = vmul(_ia1,wAr); \
        vtype _rs0 = vmul(_rs1,wAi); \
        vtype _is0 = vmul(_is1,wAi); \
        \
        _Br = vadd(_r0,vsub(_ra0,_is0));  \
        _Bi = vadd(_i0,vadd(_ia0,_rs0));  \
        _Gr = vadd(_r0,vadd(_ra0,_is0));  \
        _Gi = vadd(_i0,vsub(_ia0,_rs0));  \
        \
        _ra0 = vmul(_ra1,wBr); \
        _ia0 = vmul(_ia1,wBr); \
        _rs0 = vmul(_rs1,wBi); \
        _is0 = vmul(_is1,wBi); \
        \
        _Cr = vadd(_r0,vsub(_ra0,_is0));  \
        _Ci = vadd(_i0,vadd(_ia0,_rs0));  \
        _Fr = vadd(_r0,vadd(_ra0,_is0));  \
        _Fi = vadd(_i0,vsub(_ia0,_rs0));  \
        \
        _ra1 = vmul(_ra1,wCr); \
        _ia1 = vmul(_ia1,wCr); \
        _rs1 = vmul(_rs1,wCi); \
        _is1 = vmul(_is1,wCi); \
        \
        _Dr = vadd(_r0,vsub(_ra1,_is1));  \
        _Di = vadd(_i0,vadd(_ia1,_rs1));  \
        _Er = vadd(_r0,vadd(_ra1,_is1));  \
        _Ei = vadd(_i0,vsub(_ia1,_rs1));  \
    }   \
    {   \
        _t0 = ((const vtype*)(T2))[0];  \
        _t1 = ((const vtype*)(T2))[1];  \
        _t2 = ((const vtype*)(T5))[0];  \
        _t3 = ((const vtype*)(T5))[1];  \
        \
        vtype _ra1 = vadd(_t0,_t2);    \
        vtype _ia1 = vadd(_t1,_t3);    \
        vtype _rs1 = vsub(_t0,_t2);    \
        vtype _is1 = vsub(_t1,_t3);    \
        \
        _Ar = vadd(_Ar,_ra1);  \
        _Ai = vadd(_Ai,_ia1);  \
        \
        vtype _ra0 = vmul(_ra1,wBr); \
        vtype _ia0 = vmul(_ia1,wBr); \
        vtype _rs0 = vmul(_rs1,wBi); \
        vtype _is0 = vmul(_is1,wBi); \
        \
        _Br = vadd(_Br,vsub(_ra0,_is0));  \
        _Bi = vadd(_Bi,vadd(_ia0,_rs0));  \
        _Gr = vadd(_Gr,vadd(_ra0,_is0));  \
        _Gi = vadd(_Gi,vsub(_ia0,_rs0));  \
        \
        _ra0 = vmul(_ra1,wCr); \
        _ia0 = vmul(_ia1,wCr); \
        _rs0 = vmul(_rs1,wCi); \
        _is0 = vmul(_is1,wCi); \
        \
        _Cr = vadd(_Cr,vadd(_ra0,_is0));  \
        _Ci = vadd(_Ci,vsub(_ia0,_rs0));  \
        _Fr = vadd(_Fr,vsub(_ra0,_is0));  \
        _Fi = vadd(_Fi,vadd(_ia0,_rs0));  \
        \
        _ra1 = vmul(_ra1,wAr); \
        _ia1 = vmul(_ia1,wAr); \
        _rs1 = vmul(_rs1,wAi); \
        _is1 = vmul(_is1,wAi); \
        \
        _Dr = vadd(_Dr,vadd(_ra1,_is1));  \
        _Di = vadd(_Di,vsub(_ia1,_rs1));  \
        _Er = vadd(_Er,vsub(_ra1,_is1));  \
        _Ei = vadd(_Ei,vadd(_ia1,_rs1));  \
    }   \
    {   \
        _t0 = ((const vtype*)(T3))[0];  \
        _t1 = ((const vtype*)(T3))[1];  \
        _t2 = ((const vtype*)(T4))[0];  \
        _t3 = ((const vtype*)(T4))[1];  \
        \
        vtype _ra1 = vadd(_t0,_t2);    \
        vtype _ia1 = vadd(_t1,_t3);    \
        vtype _rs1 = vsub(_t0,_t2);    \
        vtype _is1 = vsub(_t1,_t3);    \
        \
        _Ar = vadd(_Ar,_ra1);  \
        _Ai = vadd(_Ai,_ia1);  \
        \
        vtype _ra0 = vmul(_ra1,wCr); \
        vtype _ia0 = vmul(_ia1,wCr); \
        vtype _rs0 = vmul(_rs1,wCi); \
        vtype _is0 = vmul(_is1,wCi); \
        \
        _Br = vadd(_Br,vsub(_ra0,_is0));  \
        _Bi = vadd(_Bi,vadd(_ia0,_rs0));  \
        _Gr = vadd(_Gr,vadd(_ra0,_is0));  \
        _Gi = vadd(_Gi,vsub(_ia0,_rs0));  \
        \
        _ra0 = vmul(_ra1,wAr); \
        _ia0 = vmul(_ia1,wAr); \
        _rs0 = vmul(_rs1,wAi); \
        _is0 = vmul(_is1,wAi); \
        \
        _Cr = vadd(_Cr,vadd(_ra0,_is0));  \
        _Ci = vadd(_Ci,vsub(_ia0,_rs0));  \
        _Fr = vadd(_Fr,vsub(_ra0,_is0));  \
        _Fi = vadd(_Fi,vadd(_ia0,_rs0));  \
        \
        _ra1 = vmul(_ra1,wBr); \
        _ia1 = vmul(_ia1,wBr); \
        _rs1 = vmul(_rs1,wBi); \
        _is1 = vmul(_is1,wBi); \
        \
        _Dr = vadd(_Dr,vsub(_ra1,_is1));  \
        _Di = vadd(_Di,vadd(_ia1,_rs1));  \
        _Er = vadd(_Er,vadd(_ra1,_is1));  \
        _Ei = vadd(_Ei,vsub(_ia1,_rs1));  \
    }   \
}
#define sfft_cb_tg_vt7_m16_inverse(  \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    T0,T1,T2,T3,T4,T5,T6,   \
    wAr,wAi,wBr,wBi,wCr,wCi \
){  \
    {   \
        vtype _r0 = _Ar;  \
        vtype _i0 = _Ai;  \
        \
        vtype _ra1 = vadd(_Br,_Gr);  \
        vtype _ia1 = vadd(_Bi,_Gi);  \
        vtype _rs1 = vsub(_Br,_Gr);  \
        vtype _is1 = vsub(_Bi,_Gi);  \
        \
        _Ar = vadd(_Ar,_ra1);  \
        _Ai = vadd(_Ai,_ia1);  \
        \
        vtype _ra0 = vmul(_ra1,wAr); \
        vtype _ia0 = vmul(_ia1,wAr); \
        vtype _rs0 = vmul(_rs1,wAi); \
        vtype _is0 = vmul(_is1,wAi); \
        \
        _Br = vadd(_r0,vadd(_ra0,_is0));  \
        _Bi = vadd(_i0,vsub(_ia0,_rs0));  \
        _Gr = vadd(_r0,vsub(_ra0,_is0));  \
        _Gi = vadd(_i0,vadd(_ia0,_rs0));  \
        \
        _ra0 = vmul(_ra1,wBr); \
        _ia0 = vmul(_ia1,wBr); \
        _rs0 = vmul(_rs1,wBi); \
        _is0 = vmul(_is1,wBi); \
        \
        _t0 = vadd(_r0,vadd(_ra0,_is0));  \
        _t1 = vadd(_i0,vsub(_ia0,_rs0));  \
        _t2 = vadd(_r0,vsub(_ra0,_is0));  \
        _t3 = vadd(_i0,vadd(_ia0,_rs0));  \
        \
        _ra1 = vmul(_ra1,wCr); \
        _ia1 = vmul(_ia1,wCr); \
        _rs1 = vmul(_rs1,wCi); \
        _is1 = vmul(_is1,wCi); \
        \
        _t4 = vadd(_r0,vadd(_ra1,_is1));  \
        _t5 = vadd(_i0,vsub(_ia1,_rs1));  \
        _t6 = vadd(_r0,vsub(_ra1,_is1));  \
        _t7 = vadd(_i0,vadd(_ia1,_rs1));  \
    }   \
    {   \
        vtype _ra1 = vadd(_Cr,_Fr);  \
        vtype _ia1 = vadd(_Ci,_Fi);  \
        vtype _rs1 = vsub(_Cr,_Fr);  \
        vtype _is1 = vsub(_Ci,_Fi);  \
        \
        _Ar = vadd(_Ar,_ra1);  \
        _Ai = vadd(_Ai,_ia1);  \
        \
        vtype _ra0 = vmul(_ra1,wBr); \
        vtype _ia0 = vmul(_ia1,wBr); \
        vtype _rs0 = vmul(_rs1,wBi); \
        vtype _is0 = vmul(_is1,wBi); \
        \
        _Br = vadd(_Br,vadd(_ra0,_is0));  \
        _Bi = vadd(_Bi,vsub(_ia0,_rs0));  \
        _Gr = vadd(_Gr,vsub(_ra0,_is0));  \
        _Gi = vadd(_Gi,vadd(_ia0,_rs0));  \
        \
        _ra0 = vmul(_ra1,wCr); \
        _ia0 = vmul(_ia1,wCr); \
        _rs0 = vmul(_rs1,wCi); \
        _is0 = vmul(_is1,wCi); \
        \
        _Cr = vadd(_t0,vsub(_ra0,_is0));  \
        _Ci = vadd(_t1,vadd(_ia0,_rs0));  \
        _Fr = vadd(_t2,vadd(_ra0,_is0));  \
        _Fi = vadd(_t3,vsub(_ia0,_rs0));  \
        \
        _ra1 = vmul(_ra1,wAr); \
        _ia1 = vmul(_ia1,wAr); \
        _rs1 = vmul(_rs1,wAi); \
        _is1 = vmul(_is1,wAi); \
        \
        _t4 = vadd(_t4,vsub(_ra1,_is1));  \
        _t5 = vadd(_t5,vadd(_ia1,_rs1));  \
        _t6 = vadd(_t6,vadd(_ra1,_is1));  \
        _t7 = vadd(_t7,vsub(_ia1,_rs1));  \
    }   \
    {   \
        vtype _ra1 = vadd(_Dr,_Er);  \
        vtype _ia1 = vadd(_Di,_Ei);  \
        vtype _rs1 = vsub(_Dr,_Er);  \
        vtype _is1 = vsub(_Di,_Ei);  \
        \
        _Ar = vadd(_Ar,_ra1);  \
        _Ai = vadd(_Ai,_ia1);  \
        ((vtype*)(T0))[0] = _Ar;    \
        ((vtype*)(T0))[1] = _Ai;    \
        \
        vtype _ra0 = vmul(_ra1,wCr); \
        vtype _ia0 = vmul(_ia1,wCr); \
        vtype _rs0 = vmul(_rs1,wCi); \
        vtype _is0 = vmul(_is1,wCi); \
        \
        _Br = vadd(_Br,vadd(_ra0,_is0));  \
        _Bi = vadd(_Bi,vsub(_ia0,_rs0));  \
        _Gr = vadd(_Gr,vsub(_ra0,_is0));  \
        _Gi = vadd(_Gi,vadd(_ia0,_rs0));  \
        ((vtype*)(T1))[0] = _Br;    \
        ((vtype*)(T1))[1] = _Bi;    \
        ((vtype*)(T6))[0] = _Gr;    \
        ((vtype*)(T6))[1] = _Gi;    \
        \
        _ra0 = vmul(_ra1,wAr); \
        _ia0 = vmul(_ia1,wAr); \
        _rs0 = vmul(_rs1,wAi); \
        _is0 = vmul(_is1,wAi); \
        \
        _Cr = vadd(_Cr,vsub(_ra0,_is0));  \
        _Ci = vadd(_Ci,vadd(_ia0,_rs0));  \
        _Fr = vadd(_Fr,vadd(_ra0,_is0));  \
        _Fi = vadd(_Fi,vsub(_ia0,_rs0));  \
        ((vtype*)(T2))[0] = _Cr;    \
        ((vtype*)(T2))[1] = _Ci;    \
        ((vtype*)(T5))[0] = _Fr;    \
        ((vtype*)(T5))[1] = _Fi;    \
        \
        _ra1 = vmul(_ra1,wBr); \
        _ia1 = vmul(_ia1,wBr); \
        _rs1 = vmul(_rs1,wBi); \
        _is1 = vmul(_is1,wBi); \
        \
        _Dr = vadd(_t4,vadd(_ra1,_is1));  \
        _Di = vadd(_t5,vsub(_ia1,_rs1));  \
        _Er = vadd(_t6,vsub(_ra1,_is1));  \
        _Ei = vadd(_t7,vadd(_ia1,_rs1));  \
        ((vtype*)(T3))[0] = _Dr;    \
        ((vtype*)(T3))[1] = _Di;    \
        ((vtype*)(T4))[0] = _Er;    \
        ((vtype*)(T4))[1] = _Ei;    \
    }   \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Vector
//  wAr + wAi*i = e^(-2pi*i * 1/7)
//  wBr + wBi*i = e^(-2pi*i * 2/7)
//  wCr + wCi*i = e^(-2pi*i * 3/7)
#define sfft_cb_tg_vt7_m16_forward0(   \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    T0,T1,T2,T3,T4,T5,T6,   \
    wAr,wAi,wBr,wBi,wCr,wCi,    \
    w1_0,w2_0,w3_0,w4_0,w5_0,w6_0 \
){  \
    vtype _Ar,_Ai,_Br,_Bi,_Cr,_Ci,_Dr,_Di,_Er,_Ei,_Fr,_Fi,_Gr,_Gi;    \
    vtype _t0,_t1,_t2,_t3;    \
    \
    sfft_cb_tg_vt7_m16_forward(    \
        vtype,  \
        vadd,vsub,  \
        vmul,vpma,vpms, \
        T0,T1,T2,T3,T4,T5,T6,   \
        wAr,wAi,wBr,wBi,wCr,wCi \
    );    \
    \
    ((vtype*)(T0))[0] = _Ar; \
    ((vtype*)(T0))[1] = _Ai; \
    \
    _t0 = ((vtype*)(w1_0))[0]; \
    _t1 = ((vtype*)(w1_0))[1]; \
    ((vtype*)(T1))[0] = vpms(_Br,_t0,vmul(_Bi,_t1));    \
    ((vtype*)(T1))[1] = vpma(_Bi,_t0,vmul(_Br,_t1));    \
    \
    _t2 = ((vtype*)(w2_0))[0]; \
    _t3 = ((vtype*)(w2_0))[1]; \
    ((vtype*)(T2))[0] = vpms(_Cr,_t2,vmul(_Ci,_t3));    \
    ((vtype*)(T2))[1] = vpma(_Ci,_t2,vmul(_Cr,_t3));    \
    \
    _t0 = ((vtype*)(w3_0))[0]; \
    _t1 = ((vtype*)(w3_0))[1]; \
    ((vtype*)(T3))[0] = vpms(_Dr,_t0,vmul(_Di,_t1));    \
    ((vtype*)(T3))[1] = vpma(_Di,_t0,vmul(_Dr,_t1));    \
    \
    _t2 = ((vtype*)(w4_0))[0]; \
    _t3 = ((vtype*)(w4_0))[1]; \
    ((vtype*)(T4))[0] = vpms(_Er,_t2,vmul(_Ei,_t3));    \
    ((vtype*)(T4))[1] = vpma(_Ei,_t2,vmul(_Er,_t3));    \
    \
    _t0 = ((vtype*)(w5_0))[0]; \
    _t1 = ((vtype*)(w5_0))[1]; \
    ((vtype*)(T5))[0] = vpms(_Fr,_t0,vmul(_Fi,_t1));    \
    ((vtype*)(T5))[1] = vpma(_Fi,_t0,vmul(_Fr,_t1));    \
    \
    _t2 = ((vtype*)(w6_0))[0]; \
    _t3 = ((vtype*)(w6_0))[1]; \
    ((vtype*)(T6))[0] = vpms(_Gr,_t2,vmul(_Gi,_t3));    \
    ((vtype*)(T6))[1] = vpma(_Gi,_t2,vmul(_Gr,_t3));    \
}
#define sfft_cb_tg_vt7_m16_inverse0(   \
    vtype,  \
    vadd,vsub,  \
    vmul,vpma,vpms, \
    T0,T1,T2,T3,T4,T5,T6,   \
    wAr,wAi,wBr,wBi,wCr,wCi,    \
    w1_0,w2_0,w3_0,w4_0,w5_0,w6_0 \
){  \
    vtype _Ar,_Ai,_Br,_Bi,_Cr,_Ci,_Dr,_Di,_Er,_Ei,_Fr,_Fi,_Gr,_Gi;    \
    vtype _t0,_t1,_t2,_t3,_t4,_t5,_t6,_t7;    \
    \
    _Ar = ((const vtype*)(T0))[0];  \
    _Ai = ((const vtype*)(T0))[1];  \
    \
    _t0 = ((vtype*)(w1_0))[0];  \
    _t1 = ((vtype*)(w1_0))[1];  \
    _t2 = ((const vtype*)(T1))[0];  \
    _t3 = ((const vtype*)(T1))[1];  \
    _Br = vpma(_t2,_t0,vmul(_t3,_t1));  \
    _Bi = vpms(_t3,_t0,vmul(_t2,_t1));  \
    \
    _t0 = ((vtype*)(w2_0))[0];  \
    _t1 = ((vtype*)(w2_0))[1];  \
    _t2 = ((const vtype*)(T2))[0];  \
    _t3 = ((const vtype*)(T2))[1];  \
    _Cr = vpma(_t2,_t0,vmul(_t3,_t1));  \
    _Ci = vpms(_t3,_t0,vmul(_t2,_t1));  \
    \
    _t0 = ((vtype*)(w3_0))[0];  \
    _t1 = ((vtype*)(w3_0))[1];  \
    _t2 = ((const vtype*)(T3))[0];  \
    _t3 = ((const vtype*)(T3))[1];  \
    _Dr = vpma(_t2,_t0,vmul(_t3,_t1));  \
    _Di = vpms(_t3,_t0,vmul(_t2,_t1));  \
    \
    _t0 = ((vtype*)(w4_0))[0];  \
    _t1 = ((vtype*)(w4_0))[1];  \
    _t2 = ((const vtype*)(T4))[0];  \
    _t3 = ((const vtype*)(T4))[1];  \
    _Er = vpma(_t2,_t0,vmul(_t3,_t1));  \
    _Ei = vpms(_t3,_t0,vmul(_t2,_t1));  \
    \
    _t0 = ((vtype*)(w5_0))[0];  \
    _t1 = ((vtype*)(w5_0))[1];  \
    _t2 = ((const vtype*)(T5))[0];  \
    _t3 = ((const vtype*)(T5))[1];  \
    _Fr = vpma(_t2,_t0,vmul(_t3,_t1));  \
    _Fi = vpms(_t3,_t0,vmul(_t2,_t1));  \
    \
    _t0 = ((vtype*)(w6_0))[0];  \
    _t1 = ((vtype*)(w6_0))[1];  \
    _t2 = ((const vtype*)(T6))[0];  \
    _t3 = ((const vtype*)(T6))[1];  \
    _Gr = vpma(_t2,_t0,vmul(_t3,_t1));  \
    _Gi = vpms(_t3,_t0,vmul(_t2,_t1));  \
    \
    sfft_cb_tg_vt7_m16_inverse(    \
        vtype,  \
        vadd,vsub,  \
        vmul,vpma,vpms, \
        T0,T1,T2,T3,T4,T5,T6,   \
        wAr,wAi,wBr,wBi,wCr,wCi \
    );    \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
