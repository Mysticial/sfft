/* sfft_cb_f64v1_t4_Power7.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 06/02/2011
 * Last Modified    : 06/02/2011
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 *      t4      =   4-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_t4_Power7_H
#define _sfft_cb_f64v1_t4_Power7_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t4_forward_Power7(T){    \
    const vector double NEGATE0 = {0.0,-0.0};   \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    \
    _r0 = ((const f_vector*)(T))[0];    \
    _r1 = ((const f_vector*)(T))[1];    \
    _r2 = ((const f_vector*)(T))[2];    \
    _r3 = ((const f_vector*)(T))[3];    \
    \
    _r4 = fv_add(_r0,_r2);  \
    _r5 = fv_add(_r1,_r3);  \
    _r0 = fv_sub(_r0,_r2);  \
    _r1 = fv_sub(_r1,_r3);  \
    \
    _r2 = fv_mergeh(_r4,_r5);   \
    _r4 = fv_mergel(_r4,_r5);   \
    _r3 = fv_mergeh(_r0,_r1);   \
    _r0 = fv_mergel(_r1,_r0);   \
    _r0 = fv_xor(_r0,NEGATE0);  \
    \
    _r5 = fv_add(_r2,_r4);  \
    _r1 = fv_add(_r3,_r0);  \
    _r2 = fv_sub(_r2,_r4);  \
    _r3 = fv_sub(_r3,_r0);  \
    \
    _r4 = fv_mergeh(_r5,_r2);   \
    _r5 = fv_mergel(_r5,_r2);   \
    _r0 = fv_mergeh(_r1,_r3);   \
    _r1 = fv_mergel(_r1,_r3);   \
    \
    ((f_vector*)(T))[0] = _r4;  \
    ((f_vector*)(T))[1] = _r5;  \
    ((f_vector*)(T))[2] = _r0;  \
    ((f_vector*)(T))[3] = _r1;  \
}
#define sfft_cb_f64v1_t4_inverse_Power7(T){    \
    const vector double NEGATE0 = {0.0,-0.0};   \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    \
    _r0 = ((const f_vector*)(T))[0];    \
    _r1 = ((const f_vector*)(T))[1];    \
    _r2 = ((const f_vector*)(T))[2];    \
    _r3 = ((const f_vector*)(T))[3];    \
    \
    _r4 = fv_mergeh(_r0,_r1);   \
    _r0 = fv_mergel(_r0,_r1);   \
    _r5 = fv_mergeh(_r2,_r3);   \
    _r2 = fv_mergel(_r2,_r3);   \
    \
    _r1 = fv_add(_r4,_r0);  \
    _r4 = fv_sub(_r4,_r0);  \
    _r3 = fv_add(_r5,_r2);  \
    _r5 = fv_sub(_r5,_r2);  \
    \
    _r0 = fv_mergeh(_r1,_r4);   \
    _r1 = fv_mergel(_r1,_r4);   \
    _r2 = fv_perm1(_r3,_r5);    \
    _r3 = fv_perm2(_r3,_r5);    \
    _r2 = fv_xor(_r2,NEGATE0);  \
    \
    _r4 = fv_add(_r0,_r2);  \
    _r5 = fv_add(_r1,_r3);  \
    _r0 = fv_sub(_r0,_r2);  \
    _r1 = fv_sub(_r1,_r3);  \
    \
    ((f_vector*)(T))[0] = _r4;  \
    ((f_vector*)(T))[1] = _r5;  \
    ((f_vector*)(T))[2] = _r0;  \
    ((f_vector*)(T))[3] = _r1;  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t4_forward_u1_Power7(T){ \
    const vector double NEGATE0 = {0.0,-0.0};   \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    register f_vector _s0,_s1,_s2,_s3,_s4,_s5;  \
    \
    _r0 = ((const f_vector*)(T))[0];    \
    _r1 = ((const f_vector*)(T))[1];    \
    _r2 = ((const f_vector*)(T))[2];    \
    _r3 = ((const f_vector*)(T))[3];    \
    \
    _r4 = fv_add(_r0,_r2);  \
    _r5 = fv_add(_r1,_r3);  \
    _r0 = fv_sub(_r0,_r2);  \
    _r1 = fv_sub(_r1,_r3);  \
    _s0 = ((const f_vector*)(T))[4];    \
    _s1 = ((const f_vector*)(T))[5];    \
    _s2 = ((const f_vector*)(T))[6];    \
    _s3 = ((const f_vector*)(T))[7];    \
    \
    _r2 = fv_mergeh(_r4,_r5);   \
    _r4 = fv_mergel(_r4,_r5);   \
    _r3 = fv_mergeh(_r0,_r1);   \
    _r0 = fv_mergel(_r1,_r0);   \
    _r0 = fv_xor(_r0,NEGATE0);  \
    _s4 = fv_add(_s0,_s2);  \
    _s5 = fv_add(_s1,_s3);  \
    _s0 = fv_sub(_s0,_s2);  \
    _s1 = fv_sub(_s1,_s3);  \
    \
    _r5 = fv_add(_r2,_r4);  \
    _r1 = fv_add(_r3,_r0);  \
    _r2 = fv_sub(_r2,_r4);  \
    _r3 = fv_sub(_r3,_r0);  \
    _s2 = fv_mergeh(_s4,_s5);   \
    _s4 = fv_mergel(_s4,_s5);   \
    _s3 = fv_mergeh(_s0,_s1);   \
    _s0 = fv_mergel(_s1,_s0);   \
    _s0 = fv_xor(_s0,NEGATE0);  \
    \
    _r4 = fv_mergeh(_r5,_r2);   \
    _r5 = fv_mergel(_r5,_r2);   \
    _r0 = fv_mergeh(_r1,_r3);   \
    _r1 = fv_mergel(_r1,_r3);   \
    _s5 = fv_add(_s2,_s4);  \
    _s1 = fv_add(_s3,_s0);  \
    _s2 = fv_sub(_s2,_s4);  \
    _s3 = fv_sub(_s3,_s0);  \
    \
    ((f_vector*)(T))[0] = _r4;  \
    ((f_vector*)(T))[1] = _r5;  \
    ((f_vector*)(T))[2] = _r0;  \
    ((f_vector*)(T))[3] = _r1;  \
    _s4 = fv_mergeh(_s5,_s2);   \
    _s5 = fv_mergel(_s5,_s2);   \
    _s0 = fv_mergeh(_s1,_s3);   \
    _s1 = fv_mergel(_s1,_s3);   \
    \
    ((f_vector*)(T))[4] = _s4;  \
    ((f_vector*)(T))[5] = _s5;  \
    ((f_vector*)(T))[6] = _s0;  \
    ((f_vector*)(T))[7] = _s1;  \
}
#define sfft_cb_f64v1_t4_inverse_u1_Power7(T){ \
    const vector double NEGATE0 = {0.0,-0.0};   \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    register f_vector _s0,_s1,_s2,_s3,_s4,_s5;  \
    \
    _r0 = ((const f_vector*)(T))[0];    \
    _r1 = ((const f_vector*)(T))[1];    \
    _r2 = ((const f_vector*)(T))[2];    \
    _r3 = ((const f_vector*)(T))[3];    \
    \
    _r4 = fv_mergeh(_r0,_r1);   \
    _r0 = fv_mergel(_r0,_r1);   \
    _r5 = fv_mergeh(_r2,_r3);   \
    _r2 = fv_mergel(_r2,_r3);   \
    _s0 = ((const f_vector*)(T))[4];    \
    _s1 = ((const f_vector*)(T))[5];    \
    _s2 = ((const f_vector*)(T))[6];    \
    _s3 = ((const f_vector*)(T))[7];    \
    \
    _r1 = fv_add(_r4,_r0);  \
    _r4 = fv_sub(_r4,_r0);  \
    _r3 = fv_add(_r5,_r2);  \
    _r5 = fv_sub(_r5,_r2);  \
    _s4 = fv_mergeh(_s0,_s1);   \
    _s0 = fv_mergel(_s0,_s1);   \
    _s5 = fv_mergeh(_s2,_s3);   \
    _s2 = fv_mergel(_s2,_s3);   \
    \
    _r0 = fv_mergeh(_r1,_r4);   \
    _r1 = fv_mergel(_r1,_r4);   \
    _r2 = fv_perm1(_r3,_r5);    \
    _r3 = fv_perm2(_r3,_r5);    \
    _r2 = fv_xor(_r2,NEGATE0);  \
    _s1 = fv_add(_s4,_s0);  \
    _s4 = fv_sub(_s4,_s0);  \
    _s3 = fv_add(_s5,_s2);  \
    _s5 = fv_sub(_s5,_s2);  \
    \
    _r4 = fv_add(_r0,_r2);  \
    _r5 = fv_add(_r1,_r3);  \
    _r0 = fv_sub(_r0,_r2);  \
    _r1 = fv_sub(_r1,_r3);  \
    _s0 = fv_mergeh(_s1,_s4);   \
    _s1 = fv_mergel(_s1,_s4);   \
    _s2 = fv_perm1(_s3,_s5);    \
    _s3 = fv_perm2(_s3,_s5);    \
    _s2 = fv_xor(_s2,NEGATE0);  \
    \
    ((f_vector*)(T))[0] = _r4;  \
    ((f_vector*)(T))[1] = _r5;  \
    ((f_vector*)(T))[2] = _r0;  \
    ((f_vector*)(T))[3] = _r1;  \
    _s4 = fv_add(_s0,_s2);  \
    _s5 = fv_add(_s1,_s3);  \
    _s0 = fv_sub(_s0,_s2);  \
    _s1 = fv_sub(_s1,_s3);  \
    \
    ((f_vector*)(T))[4] = _s4;  \
    ((f_vector*)(T))[5] = _s5;  \
    ((f_vector*)(T))[6] = _s0;  \
    ((f_vector*)(T))[7] = _s1;  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v1_t4_forward_u2_Power7(T){ \
    const vector double NEGATE0 = {0.0,-0.0};   \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    register f_vector _s0,_s1,_s2,_s3,_s4,_s5;  \
    register f_vector _t0,_t1,_t2,_t3,_t4,_t5;  \
    register f_vector _u0,_u1,_u2,_u3,_u4,_u5;  \
    \
    _r0 = ((const f_vector*)(T))[ 0];   \
    _r1 = ((const f_vector*)(T))[ 1];   \
    _r2 = ((const f_vector*)(T))[ 2];   \
    _r3 = ((const f_vector*)(T))[ 3];   \
    \
    _r4 = fv_add(_r0,_r2);  \
    _s0 = ((const f_vector*)(T))[ 4];   \
    _r5 = fv_add(_r1,_r3);  \
    _s1 = ((const f_vector*)(T))[ 5];   \
    _r0 = fv_sub(_r0,_r2);  \
    _s2 = ((const f_vector*)(T))[ 6];   \
    _r1 = fv_sub(_r1,_r3);  \
    _s3 = ((const f_vector*)(T))[ 7];   \
    \
    _s4 = fv_add(_s0,_s2);  \
    _s5 = fv_add(_s1,_s3);  \
    _t0 = ((const f_vector*)(T))[ 8];   \
    _s0 = fv_sub(_s0,_s2);  \
    _s1 = fv_sub(_s1,_s3);  \
    _t1 = ((const f_vector*)(T))[ 9];   \
    _r2 = fv_mergeh(_r4,_r5);   \
    _r4 = fv_mergel(_r4,_r5);   \
    _t2 = ((const f_vector*)(T))[10];   \
    _r3 = fv_mergeh(_r0,_r1);   \
    _r0 = fv_mergel(_r1,_r0);   \
    _r0 = fv_xor(_r0,NEGATE0);  \
    _t3 = ((const f_vector*)(T))[11];   \
    \
    _t4 = fv_add(_t0,_t2);  \
    _t5 = fv_add(_t1,_t3);  \
    _t0 = fv_sub(_t0,_t2);  \
    _u0 = ((const f_vector*)(T))[12];   \
    _t1 = fv_sub(_t1,_t3);  \
    _s2 = fv_mergeh(_s4,_s5);   \
    _s4 = fv_mergel(_s4,_s5);   \
    _u1 = ((const f_vector*)(T))[13];   \
    _s3 = fv_mergeh(_s0,_s1);   \
    _s0 = fv_mergel(_s1,_s0);   \
    _s0 = fv_xor(_s0,NEGATE0);  \
    _u2 = ((const f_vector*)(T))[14];   \
    _r5 = fv_add(_r2,_r4);  \
    _r1 = fv_add(_r3,_r0);  \
    _r2 = fv_sub(_r2,_r4);  \
    _r3 = fv_sub(_r3,_r0);  \
    _u3 = ((const f_vector*)(T))[15];   \
    \
    _u4 = fv_add(_u0,_u2);  \
    _u5 = fv_add(_u1,_u3);  \
    _u0 = fv_sub(_u0,_u2);  \
    _u1 = fv_sub(_u1,_u3);  \
    _t2 = fv_mergeh(_t4,_t5);   \
    _t4 = fv_mergel(_t4,_t5);   \
    _t3 = fv_mergeh(_t0,_t1);   \
    _t0 = fv_mergel(_t1,_t0);   \
    _t0 = fv_xor(_t0,NEGATE0);  \
    _s5 = fv_add(_s2,_s4);  \
    _s1 = fv_add(_s3,_s0);  \
    _s2 = fv_sub(_s2,_s4);  \
    _s3 = fv_sub(_s3,_s0);  \
    _r4 = fv_mergeh(_r5,_r2);   \
    _r5 = fv_mergel(_r5,_r2);   \
    _r0 = fv_mergeh(_r1,_r3);   \
    _r1 = fv_mergel(_r1,_r3);   \
    \
    ((f_vector*)(T))[ 0] = _r4; \
    _u2 = fv_mergeh(_u4,_u5);   \
    _u4 = fv_mergel(_u4,_u5);   \
    _u3 = fv_mergeh(_u0,_u1);   \
    _u0 = fv_mergel(_u1,_u0);   \
    ((f_vector*)(T))[ 1] = _r5; \
    _u0 = fv_xor(_u0,NEGATE0);  \
    _t5 = fv_add(_t2,_t4);  \
    _t1 = fv_add(_t3,_t0);  \
    ((f_vector*)(T))[ 2] = _r0; \
    _t2 = fv_sub(_t2,_t4);  \
    _t3 = fv_sub(_t3,_t0);  \
    _s4 = fv_mergeh(_s5,_s2);   \
    ((f_vector*)(T))[ 3] = _r1; \
    _s5 = fv_mergel(_s5,_s2);   \
    _s0 = fv_mergeh(_s1,_s3);   \
    _s1 = fv_mergel(_s1,_s3);   \
    \
    ((f_vector*)(T))[ 4] = _s4; \
    _u5 = fv_add(_u2,_u4);  \
    _u1 = fv_add(_u3,_u0);  \
    ((f_vector*)(T))[ 5] = _s5; \
    _u2 = fv_sub(_u2,_u4);  \
    _u3 = fv_sub(_u3,_u0);  \
    ((f_vector*)(T))[ 6] = _s0; \
    _t4 = fv_mergeh(_t5,_t2);   \
    _t5 = fv_mergel(_t5,_t2);   \
    ((f_vector*)(T))[ 7] = _s1; \
    _t0 = fv_mergeh(_t1,_t3);   \
    _t1 = fv_mergel(_t1,_t3);   \
    \
    ((f_vector*)(T))[ 8] = _t4; \
    _u4 = fv_mergeh(_u5,_u2);   \
    ((f_vector*)(T))[ 9] = _t5; \
    _u5 = fv_mergel(_u5,_u2);   \
    ((f_vector*)(T))[10] = _t0; \
    _u0 = fv_mergeh(_u1,_u3);   \
    ((f_vector*)(T))[11] = _t1; \
    _u1 = fv_mergel(_u1,_u3);   \
    \
    ((f_vector*)(T))[12] = _u4; \
    ((f_vector*)(T))[13] = _u5; \
    ((f_vector*)(T))[14] = _u0; \
    ((f_vector*)(T))[15] = _u1; \
}
#define sfft_cb_f64v1_t4_inverse_u2_Power7(T){ \
    const vector double NEGATE0 = {0.0,-0.0};   \
    \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5;  \
    register f_vector _s0,_s1,_s2,_s3,_s4,_s5;  \
    register f_vector _t0,_t1,_t2,_t3,_t4,_t5;  \
    register f_vector _u0,_u1,_u2,_u3,_u4,_u5;  \
    \
    _r0 = ((const f_vector*)(T))[ 0];   \
    _r1 = ((const f_vector*)(T))[ 1];   \
    _r2 = ((const f_vector*)(T))[ 2];   \
    _r3 = ((const f_vector*)(T))[ 3];   \
    \
    _r4 = fv_mergeh(_r0,_r1);   \
    _s0 = ((const f_vector*)(T))[ 4];   \
    _r0 = fv_mergel(_r0,_r1);   \
    _s1 = ((const f_vector*)(T))[ 5];   \
    _r5 = fv_mergeh(_r2,_r3);   \
    _s2 = ((const f_vector*)(T))[ 6];   \
    _r2 = fv_mergel(_r2,_r3);   \
    _s3 = ((const f_vector*)(T))[ 7];   \
    \
    _r1 = fv_add(_r4,_r0);  \
    _r4 = fv_sub(_r4,_r0);  \
    _t0 = ((const f_vector*)(T))[ 8];   \
    _r3 = fv_add(_r5,_r2);  \
    _r5 = fv_sub(_r5,_r2);  \
    _t1 = ((const f_vector*)(T))[ 9];   \
    _s4 = fv_mergeh(_s0,_s1);   \
    _s0 = fv_mergel(_s0,_s1);   \
    _t2 = ((const f_vector*)(T))[10];   \
    _s5 = fv_mergeh(_s2,_s3);   \
    _s2 = fv_mergel(_s2,_s3);   \
    _t3 = ((const f_vector*)(T))[11];   \
    \
    _r0 = fv_mergeh(_r1,_r4);   \
    _r1 = fv_mergel(_r1,_r4);   \
    _r2 = fv_perm1(_r3,_r5);    \
    _u0 = ((const f_vector*)(T))[12];   \
    _r3 = fv_perm2(_r3,_r5);    \
    _r2 = fv_xor(_r2,NEGATE0);  \
    _s1 = fv_add(_s4,_s0);  \
    _s4 = fv_sub(_s4,_s0);  \
    _u1 = ((const f_vector*)(T))[13];   \
    _s3 = fv_add(_s5,_s2);  \
    _s5 = fv_sub(_s5,_s2);  \
    _t4 = fv_mergeh(_t0,_t1);   \
    _u2 = ((const f_vector*)(T))[14];   \
    _t0 = fv_mergel(_t0,_t1);   \
    _t5 = fv_mergeh(_t2,_t3);   \
    _t2 = fv_mergel(_t2,_t3);   \
    _u3 = ((const f_vector*)(T))[15];   \
    \
    _r4 = fv_add(_r0,_r2);  \
    _r5 = fv_add(_r1,_r3);  \
    _r0 = fv_sub(_r0,_r2);  \
    _r1 = fv_sub(_r1,_r3);  \
    _s0 = fv_mergeh(_s1,_s4);   \
    _s1 = fv_mergel(_s1,_s4);   \
    _s2 = fv_perm1(_s3,_s5);    \
    _s3 = fv_perm2(_s3,_s5);    \
    _s2 = fv_xor(_s2,NEGATE0);  \
    _t1 = fv_add(_t4,_t0);  \
    _t4 = fv_sub(_t4,_t0);  \
    _t3 = fv_add(_t5,_t2);  \
    _t5 = fv_sub(_t5,_t2);  \
    _u4 = fv_mergeh(_u0,_u1);   \
    _u0 = fv_mergel(_u0,_u1);   \
    _u5 = fv_mergeh(_u2,_u3);   \
    _u2 = fv_mergel(_u2,_u3);   \
    \
    ((f_vector*)(T))[ 0] = _r4; \
    _s4 = fv_add(_s0,_s2);  \
    _s5 = fv_add(_s1,_s3);  \
    _s0 = fv_sub(_s0,_s2);  \
    ((f_vector*)(T))[ 1] = _r5; \
    _s1 = fv_sub(_s1,_s3);  \
    _t0 = fv_mergeh(_t1,_t4);   \
    _t1 = fv_mergel(_t1,_t4);   \
    ((f_vector*)(T))[ 2] = _r0; \
    _t2 = fv_perm1(_t3,_t5);    \
    _t3 = fv_perm2(_t3,_t5);    \
    _t2 = fv_xor(_t2,NEGATE0);  \
    _u1 = fv_add(_u4,_u0);  \
    ((f_vector*)(T))[ 3] = _r1; \
    _u4 = fv_sub(_u4,_u0);  \
    _u3 = fv_add(_u5,_u2);  \
    _u5 = fv_sub(_u5,_u2);  \
    \
    ((f_vector*)(T))[ 4] = _s4; \
    _t4 = fv_add(_t0,_t2);  \
    _t5 = fv_add(_t1,_t3);  \
    ((f_vector*)(T))[ 5] = _s5; \
    _t0 = fv_sub(_t0,_t2);  \
    _t1 = fv_sub(_t1,_t3);  \
    ((f_vector*)(T))[ 6] = _s0; \
    _u0 = fv_mergeh(_u1,_u4);   \
    _u1 = fv_mergel(_u1,_u4);   \
    ((f_vector*)(T))[ 7] = _s1; \
    _u2 = fv_perm1(_u3,_u5);    \
    _u3 = fv_perm2(_u3,_u5);    \
    _u2 = fv_xor(_u2,NEGATE0);  \
    \
    ((f_vector*)(T))[ 8] = _t4; \
    _u4 = fv_add(_u0,_u2);  \
    ((f_vector*)(T))[ 9] = _t5; \
    _u5 = fv_add(_u1,_u3);  \
    ((f_vector*)(T))[10] = _t0; \
    _u0 = fv_sub(_u0,_u2);  \
    ((f_vector*)(T))[11] = _t1; \
    _u1 = fv_sub(_u1,_u3);  \
    \
    ((f_vector*)(T))[12] = _u4; \
    ((f_vector*)(T))[13] = _u5; \
    ((f_vector*)(T))[14] = _u0; \
    ((f_vector*)(T))[15] = _u1; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
