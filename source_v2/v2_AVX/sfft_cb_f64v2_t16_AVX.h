/* sfft_cb_f64v2_t16_AVX.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/31/2011
 * Last Modified    : 02/05/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v2   =   64-bit floating point (vectorize by 4)
 *      t16     =   16-point transform
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v2_t16_AVX_H
#define _sfft_cb_f64v2_t16_AVX_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v2_t16_forward_AVX_readable_raw(    \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I,O,    \
    w2,w1,w3    \
){   \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF;  \
    \
    _r0 = ((vtype*)(I))[0]; \
    _r4 = ((vtype*)(I))[4]; \
    _r1 = ((vtype*)(I))[1]; \
    _r5 = ((vtype*)(I))[5]; \
    _r2 = ((vtype*)(I))[2]; \
    _r6 = ((vtype*)(I))[6]; \
    _r3 = ((vtype*)(I))[3]; \
    _r7 = ((vtype*)(I))[7]; \
    \
    \
    _r8 = vsub(_r0,_r4);    \
    _r0 = vadd(_r0,_r4);    \
    _r9 = vsub(_r1,_r5);    \
    _r1 = vadd(_r1,_r5);    \
    \
    _rA = vsub(_r2,_r6);    \
    _r2 = vadd(_r2,_r6);    \
    _rB = vsub(_r3,_r7);    \
    _r3 = vadd(_r3,_r7);    \
    \
    \
    _r4 = vadd(_r8,_rB);    \
    _r8 = vsub(_r8,_rB);    \
    _r5 = vsub(_r9,_rA);    \
    _r9 = vadd(_r9,_rA);    \
    \
    _r6 = vsub(_r0,_r2);    \
    _r0 = vadd(_r0,_r2);    \
    _r7 = vsub(_r1,_r3);    \
    _r1 = vadd(_r1,_r3);    \
    \
    \
    _rC = ((const vtype*)(w1))[2];  \
    _rD = ((const vtype*)(w1))[3];  \
    _rE = vmul(_r5,_rD);    \
    _rF = vmul(_r4,_rD);    \
    _r4 = vpms(_r4,_rC,_rE);    \
    _r5 = vpma(_r5,_rC,_rF);    \
    \
    _rA = ((const vtype*)(w3))[2];  \
    _rB = ((const vtype*)(w3))[3];  \
    _r2 = vmul(_r9,_rB);    \
    _r3 = vmul(_r8,_rB);    \
    _r8 = vpms(_r8,_rA,_r2);    \
    _r9 = vpma(_r9,_rA,_r3);    \
    \
    _rC = ((const vtype*)(w2))[2];  \
    _rD = ((const vtype*)(w2))[3];  \
    _rE = vmul(_r7,_rD);    \
    _rF = vmul(_r6,_rD);    \
    _r6 = vpms(_r6,_rC,_rE);    \
    _r7 = vpma(_r7,_rC,_rF);    \
    \
    \
    _rA = _mm256_permute2f128_pd(_r0,_r4,32);   \
    _r0 = _mm256_permute2f128_pd(_r0,_r4,49);   \
    _rB = _mm256_permute2f128_pd(_r1,_r5,32);   \
    _r1 = _mm256_permute2f128_pd(_r1,_r5,49);   \
    \
    _r2 = _mm256_permute2f128_pd(_r6,_r8,32);   \
    _r6 = _mm256_permute2f128_pd(_r6,_r8,49);   \
    _r3 = _mm256_permute2f128_pd(_r7,_r9,32);   \
    _r7 = _mm256_permute2f128_pd(_r7,_r9,49);   \
    \
    _rC = _mm256_unpacklo_pd(_rA,_r2);  \
    _rA = _mm256_unpackhi_pd(_rA,_r2);  \
    _rD = _mm256_unpacklo_pd(_rB,_r3);  \
    _rB = _mm256_unpackhi_pd(_rB,_r3);  \
    \
    _rE = _mm256_unpacklo_pd(_r0,_r6);  \
    _r0 = _mm256_unpackhi_pd(_r0,_r6);  \
    _rF = _mm256_unpacklo_pd(_r1,_r7);  \
    _r1 = _mm256_unpackhi_pd(_r1,_r7);  \
    \
    \
    _r2 = vadd(_rC,_rE);    \
    _rC = vsub(_rC,_rE);    \
    _r3 = vadd(_rD,_rF);    \
    _rD = vsub(_rD,_rF);    \
    \
    _r6 = vadd(_rA,_r0);    \
    _rA = vsub(_rA,_r0);    \
    _r7 = vadd(_rB,_r1);    \
    _rB = vsub(_rB,_r1);    \
    \
    \
    _rE = vadd(_r2,_r6);    \
    _r2 = vsub(_r2,_r6);    \
    _rF = vadd(_r3,_r7);    \
    _r3 = vsub(_r3,_r7);    \
    \
    _r0 = vadd(_rC,_rB);    \
    _rC = vsub(_rC,_rB);    \
    _r1 = vsub(_rD,_rA);    \
    _rD = vadd(_rD,_rA);    \
    \
    \
    _r6 = _mm256_unpacklo_pd(_rE,_r2);  \
    _rE = _mm256_unpackhi_pd(_rE,_r2);  \
    _r7 = _mm256_unpacklo_pd(_rF,_r3);  \
    _rF = _mm256_unpackhi_pd(_rF,_r3);  \
    \
    _rB = _mm256_unpacklo_pd(_r0,_rC);  \
    _r0 = _mm256_unpackhi_pd(_r0,_rC);  \
    _rA = _mm256_unpacklo_pd(_r1,_rD);  \
    _r1 = _mm256_unpackhi_pd(_r1,_rD);  \
    \
    _r2 = _mm256_permute2f128_pd(_r6,_rB,32);   \
    _r6 = _mm256_permute2f128_pd(_r6,_rB,49);   \
    _r3 = _mm256_permute2f128_pd(_r7,_rA,32);   \
    _r7 = _mm256_permute2f128_pd(_r7,_rA,49);   \
    \
    _rC = _mm256_permute2f128_pd(_rE,_r0,32);   \
    _rE = _mm256_permute2f128_pd(_rE,_r0,49);   \
    _rD = _mm256_permute2f128_pd(_rF,_r1,32);   \
    _rF = _mm256_permute2f128_pd(_rF,_r1,49);   \
    \
    \
    ((vtype*)(O))[0] = _r2; \
    ((vtype*)(O))[1] = _r3; \
    ((vtype*)(O))[4] = _r6; \
    ((vtype*)(O))[5] = _r7; \
    ((vtype*)(O))[2] = _rC; \
    ((vtype*)(O))[3] = _rD; \
    ((vtype*)(O))[6] = _rE; \
    ((vtype*)(O))[7] = _rF; \
}
#define sfft_cb_f64v2_t16_inverse_AVX_readable_raw(    \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I,O,    \
    w2,w1,w3    \
){   \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF;  \
    \
    _r0 = ((vtype*)(I))[0]; \
    _r1 = ((vtype*)(I))[1]; \
    _r2 = ((vtype*)(I))[2]; \
    _r3 = ((vtype*)(I))[3]; \
    _r4 = ((vtype*)(I))[4]; \
    _r5 = ((vtype*)(I))[5]; \
    _r6 = ((vtype*)(I))[6]; \
    _r7 = ((vtype*)(I))[7]; \
    \
    \
    _r8 = _mm256_permute2f128_pd(_r0,_r4,32);   \
    _r0 = _mm256_permute2f128_pd(_r0,_r4,49);   \
    _r9 = _mm256_permute2f128_pd(_r1,_r5,32);   \
    _r1 = _mm256_permute2f128_pd(_r1,_r5,49);   \
    \
    _rA = _mm256_permute2f128_pd(_r2,_r6,32);   \
    _r2 = _mm256_permute2f128_pd(_r2,_r6,49);   \
    _rB = _mm256_permute2f128_pd(_r3,_r7,32);   \
    _r3 = _mm256_permute2f128_pd(_r3,_r7,49);   \
    \
    _r4 = _mm256_unpacklo_pd(_r8,_rA);  \
    _r8 = _mm256_unpackhi_pd(_r8,_rA);  \
    _r5 = _mm256_unpacklo_pd(_r9,_rB);  \
    _r9 = _mm256_unpackhi_pd(_r9,_rB);  \
    \
    _r6 = _mm256_unpacklo_pd(_r0,_r2);  \
    _r0 = _mm256_unpackhi_pd(_r0,_r2);  \
    _r7 = _mm256_unpacklo_pd(_r1,_r3);  \
    _r1 = _mm256_unpackhi_pd(_r1,_r3);  \
    \
    \
    _rA = vadd(_r4,_r8);    \
    _r4 = vsub(_r4,_r8);    \
    _rB = vadd(_r5,_r9);    \
    _r5 = vsub(_r5,_r9);    \
    \
    _r2 = vadd(_r6,_r0);    \
    _r6 = vsub(_r6,_r0);    \
    _r3 = vadd(_r7,_r1);    \
    _r7 = vsub(_r7,_r1);    \
    \
    \
    _r8 = vadd(_rA,_r2);    \
    _rA = vsub(_rA,_r2);    \
    _r9 = vadd(_rB,_r3);    \
    _rB = vsub(_rB,_r3);    \
    \
    _r0 = vsub(_r4,_r7);    \
    _r4 = vadd(_r4,_r7);    \
    _r1 = vadd(_r5,_r6);    \
    _r5 = vsub(_r5,_r6);    \
    \
    \
    _r2 = _mm256_unpacklo_pd(_r8,_r0);  \
    _r8 = _mm256_unpackhi_pd(_r8,_r0);  \
    _r3 = _mm256_unpacklo_pd(_r9,_r1);  \
    _r9 = _mm256_unpackhi_pd(_r9,_r1);  \
    \
    _r6 = _mm256_unpacklo_pd(_rA,_r4);  \
    _rA = _mm256_unpackhi_pd(_rA,_r4);  \
    _r7 = _mm256_unpacklo_pd(_rB,_r5);  \
    _rB = _mm256_unpackhi_pd(_rB,_r5);  \
    \
    _r0 = _mm256_permute2f128_pd(_r2,_r6,32);   \
    _r1 = _mm256_permute2f128_pd(_r3,_r7,32);   \
    _r2 = _mm256_permute2f128_pd(_r2,_r6,49);   \
    _r3 = _mm256_permute2f128_pd(_r3,_r7,49);   \
    \
    _r4 = _mm256_permute2f128_pd(_r8,_rA,32);   \
    _r5 = _mm256_permute2f128_pd(_r9,_rB,32);   \
    _r8 = _mm256_permute2f128_pd(_r8,_rA,49);   \
    _r9 = _mm256_permute2f128_pd(_r9,_rB,49);   \
    \
    \
    _rC = ((const vtype*)(w1))[2];  \
    _rD = ((const vtype*)(w1))[3];  \
    _rE = vmul(_r3,_rD);    \
    _rF = vmul(_r2,_rD);    \
    _r2 = vpma(_r2,_rC,_rE);    \
    _r3 = vpms(_r3,_rC,_rF);    \
    \
    _r6 = ((const vtype*)(w2))[2];  \
    _r7 = ((const vtype*)(w2))[3];  \
    _rA = vmul(_r5,_r7);    \
    _rB = vmul(_r4,_r7);    \
    _r4 = vpma(_r4,_r6,_rA);    \
    _r5 = vpms(_r5,_r6,_rB);    \
    \
    _rC = ((const vtype*)(w3))[2];  \
    _rD = ((const vtype*)(w3))[3];  \
    _rE = vmul(_r9,_rD);    \
    _rF = vmul(_r8,_rD);    \
    _r8 = vpma(_r8,_rC,_rE);    \
    _r9 = vpms(_r9,_rC,_rF);    \
    \
    \
    _r6 = vadd(_r0,_r4);    \
    _r0 = vsub(_r0,_r4);    \
    _r7 = vadd(_r1,_r5);    \
    _r1 = vsub(_r1,_r5);    \
    \
    _rA = vadd(_r2,_r8);    \
    _r2 = vsub(_r2,_r8);    \
    _rB = vadd(_r3,_r9);    \
    _r3 = vsub(_r3,_r9);    \
    \
    \
    _r4 = vadd(_r6,_rA);    \
    _r6 = vsub(_r6,_rA);    \
    _r5 = vadd(_r7,_rB);    \
    _r7 = vsub(_r7,_rB);    \
    \
    _r8 = vsub(_r0,_r3);    \
    _rA = vadd(_r0,_r3);    \
    _r9 = vadd(_r1,_r2);    \
    _rB = vsub(_r1,_r2);    \
    \
    \
    ((vtype*)(O))[0] = _r4; \
    ((vtype*)(O))[1] = _r5; \
    ((vtype*)(O))[4] = _r6; \
    ((vtype*)(O))[5] = _r7; \
    ((vtype*)(O))[2] = _r8; \
    ((vtype*)(O))[3] = _r9; \
    ((vtype*)(O))[6] = _rA; \
    ((vtype*)(O))[7] = _rB; \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cb_f64v2_t16_forward_AVX_raw( \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I,O,    \
    w2,w1,w3    \
){   \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF;  \
    \
    _r0 = ((vtype*)(I))[0]; \
    _r4 = ((vtype*)(I))[4]; \
    \
    _r8 = vsub(_r0,_r4);    \
    _r1 = ((vtype*)(I))[1]; \
    _r0 = vadd(_r0,_r4);    \
    _r5 = ((vtype*)(I))[5]; \
    \
    _r9 = vsub(_r1,_r5);    \
    _r2 = ((vtype*)(I))[2]; \
    _r1 = vadd(_r1,_r5);    \
    _r6 = ((vtype*)(I))[6]; \
    \
    _rA = vsub(_r2,_r6);    \
    _r3 = ((vtype*)(I))[3]; \
    _r2 = vadd(_r2,_r6);    \
    _r7 = ((vtype*)(I))[7]; \
    \
    _rB = vsub(_r3,_r7);    \
    _rC = ((const vtype*)(w1))[2];  \
    _r3 = vadd(_r3,_r7);    \
    _rD = ((const vtype*)(w1))[3];  \
    \
    \
    _r5 = vsub(_r9,_rA);    \
    _r4 = vadd(_r8,_rB);    \
    _r9 = vadd(_r9,_rA);    \
    _r8 = vsub(_r8,_rB);    \
    _rB = ((const vtype*)(w3))[3];  \
    \
    _rE = vmul(_r5,_rD);    \
    _r6 = vsub(_r0,_r2);    \
    _rF = vmul(_r4,_rD);    \
    _r0 = vadd(_r0,_r2);    \
    _rD = ((const vtype*)(w2))[3];  \
    _r2 = vmul(_r9,_rB);    \
    _r7 = vsub(_r1,_r3);    \
    _r1 = vadd(_r1,_r3);    \
    _r3 = vmul(_r8,_rB);    \
    _rA = ((const vtype*)(w3))[2];  \
    \
    _r4 = vpms(_r4,_rC,_rE);    \
    _rE = vmul(_r7,_rD);    \
    _r5 = vpma(_r5,_rC,_rF);    \
    _rB = ((const vtype*)(w2))[ 2]; \
    _rF = vmul(_r6,_rD);    \
    \
    _r8 = vpms(_r8,_rA,_r2);    \
    _r9 = vpma(_r9,_rA,_r3);    \
    _rA = _mm256_permute2f128_pd(_r0,_r4,32);   \
    _r0 = _mm256_permute2f128_pd(_r0,_r4,49);   \
    _r6 = vpms(_r6,_rB,_rE);    \
    _r7 = vpma(_r7,_rB,_rF);    \
    _rB = _mm256_permute2f128_pd(_r1,_r5,32);   \
    _r1 = _mm256_permute2f128_pd(_r1,_r5,49);   \
    \
    _r2 = _mm256_permute2f128_pd(_r6,_r8,32);   \
    _r6 = _mm256_permute2f128_pd(_r6,_r8,49);   \
    _r3 = _mm256_permute2f128_pd(_r7,_r9,32);   \
    _r7 = _mm256_permute2f128_pd(_r7,_r9,49);   \
    \
    _rC = _mm256_unpacklo_pd(_rA,_r2);  \
    _rE = _mm256_unpacklo_pd(_r0,_r6);  \
    _rD = _mm256_unpacklo_pd(_rB,_r3);  \
    _r4 = vadd(_rC,_rE);    \
    _rF = _mm256_unpacklo_pd(_r1,_r7);  \
    _rC = vsub(_rC,_rE);    \
    \
    _rA = _mm256_unpackhi_pd(_rA,_r2);  \
    _r5 = vadd(_rD,_rF);    \
    _r0 = _mm256_unpackhi_pd(_r0,_r6);  \
    _rD = vsub(_rD,_rF);    \
    _rB = _mm256_unpackhi_pd(_rB,_r3);  \
    _r6 = vadd(_rA,_r0);    \
    _r1 = _mm256_unpackhi_pd(_r1,_r7);  \
    _rA = vsub(_rA,_r0);    \
    \
    _r7 = vadd(_rB,_r1);    \
    _rE = vadd(_r4,_r6);    \
    _r4 = vsub(_r4,_r6);    \
    _rB = vsub(_rB,_r1);    \
    \
    _rF = vadd(_r5,_r7);    \
    _r6 = _mm256_unpacklo_pd(_rE,_r4);  \
    _r5 = vsub(_r5,_r7);    \
    _rE = _mm256_unpackhi_pd(_rE,_r4);  \
    _r0 = vadd(_rC,_rB);    \
    _r7 = _mm256_unpacklo_pd(_rF,_r5);  \
    _rC = vsub(_rC,_rB);    \
    _rF = _mm256_unpackhi_pd(_rF,_r5);  \
    \
    _r1 = vsub(_rD,_rA);    \
    _rB = _mm256_unpacklo_pd(_r0,_rC);  \
    _rD = vadd(_rD,_rA);    \
    _r0 = _mm256_unpackhi_pd(_r0,_rC);  \
    \
    _r4 = _mm256_permute2f128_pd(_r6,_rB,32);   \
    _rA = _mm256_unpacklo_pd(_r1,_rD);  \
    ((vtype*)(O))[0] = _r4; \
    _r6 = _mm256_permute2f128_pd(_r6,_rB,49);   \
    _r1 = _mm256_unpackhi_pd(_r1,_rD);  \
    ((vtype*)(O))[4] = _r6; \
    \
    _r5 = _mm256_permute2f128_pd(_r7,_rA,32);   \
    _r7 = _mm256_permute2f128_pd(_r7,_rA,49);   \
    \
    ((vtype*)(O))[1] = _r5; \
    _rC = _mm256_permute2f128_pd(_rE,_r0,32);   \
    ((vtype*)(O))[5] = _r7; \
    _rE = _mm256_permute2f128_pd(_rE,_r0,49);   \
    ((vtype*)(O))[2] = _rC; \
    _rD = _mm256_permute2f128_pd(_rF,_r1,32);   \
    ((vtype*)(O))[6] = _rE; \
    _rF = _mm256_permute2f128_pd(_rF,_r1,49);   \
    \
    ((vtype*)(O))[3] = _rD; \
    ((vtype*)(O))[7] = _rF; \
}
#define sfft_cb_f64v2_t16_inverse_AVX_raw( \
    vtype,  \
    vadd,vsub,vmul, \
    vpma,vpms,  \
    I,O,    \
    w2,w1,w3    \
){   \
    register f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB,_rC,_rD,_rE,_rF;  \
    \
    _r0 = ((vtype*)(I))[0]; \
    _r4 = ((vtype*)(I))[4]; \
    \
    _r8 = _mm256_permute2f128_pd(_r0,_r4,32);   \
    _r1 = ((vtype*)(I))[1]; \
    _r0 = _mm256_permute2f128_pd(_r0,_r4,49);   \
    _r5 = ((vtype*)(I))[5]; \
    \
    _r9 = _mm256_permute2f128_pd(_r1,_r5,32);   \
    _r2 = ((vtype*)(I))[2]; \
    _r1 = _mm256_permute2f128_pd(_r1,_r5,49);   \
    _r6 = ((vtype*)(I))[6]; \
    \
    _rA = _mm256_permute2f128_pd(_r2,_r6,32);   \
    _r3 = ((vtype*)(I))[3]; \
    _r2 = _mm256_permute2f128_pd(_r2,_r6,49);   \
    _r7 = ((vtype*)(I))[7]; \
    \
    _r4 = _mm256_unpacklo_pd(_r8,_rA);  \
    _r8 = _mm256_unpackhi_pd(_r8,_rA);  \
    _rB = _mm256_permute2f128_pd(_r3,_r7,32);   \
    _r3 = _mm256_permute2f128_pd(_r3,_r7,49);   \
    \
    _r6 = _mm256_unpacklo_pd(_r0,_r2);  \
    _rA = vadd(_r4,_r8);    \
    _r0 = _mm256_unpackhi_pd(_r0,_r2);  \
    _r4 = vsub(_r4,_r8);    \
    \
    _r5 = _mm256_unpacklo_pd(_r9,_rB);  \
    _r2 = vadd(_r6,_r0);    \
    _r9 = _mm256_unpackhi_pd(_r9,_rB);  \
    _r6 = vsub(_r6,_r0);    \
    \
    _r7 = _mm256_unpacklo_pd(_r1,_r3);  \
    _rB = vadd(_r5,_r9);    \
    _r1 = _mm256_unpackhi_pd(_r1,_r3);  \
    _r5 = vsub(_r5,_r9);    \
    \
    _r3 = vadd(_r7,_r1);    \
    _r7 = vsub(_r7,_r1);    \
    \
    _rC = ((const vtype*)(w1))[2];  \
    _r1 = vadd(_r5,_r6);    \
    _rD = ((const vtype*)(w1))[3];  \
    _r9 = vadd(_rB,_r3);    \
    _r5 = vsub(_r5,_r6);    \
    _rB = vsub(_rB,_r3);    \
    \
    _r3 = _mm256_unpacklo_pd(_r9,_r1);  \
    _r0 = vsub(_r4,_r7);    \
    _r9 = _mm256_unpackhi_pd(_r9,_r1);  \
    _r4 = vadd(_r4,_r7);    \
    _r7 = _mm256_unpacklo_pd(_rB,_r5);  \
    _r8 = vadd(_rA,_r2);    \
    _rB = _mm256_unpackhi_pd(_rB,_r5);  \
    _rA = vsub(_rA,_r2);    \
    \
    _rF = ((const vtype*)(w3))[3];  \
    _r1 = _mm256_permute2f128_pd(_r3,_r7,32);   \
    _r3 = _mm256_permute2f128_pd(_r3,_r7,49);   \
    _rE = ((const vtype*)(w3))[2];  \
    _r2 = _mm256_unpacklo_pd(_r8,_r0);  \
    _r6 = _mm256_unpacklo_pd(_rA,_r4);  \
    _r7 = vmul(_r3,_rD);    \
    \
    _r8 = _mm256_unpackhi_pd(_r8,_r0);  \
    _r0 = _mm256_permute2f128_pd(_r2,_r6,32);   \
    _r2 = _mm256_permute2f128_pd(_r2,_r6,49);   \
    _rA = _mm256_unpackhi_pd(_rA,_r4);  \
    \
    _r6 = vmul(_r2,_rD);    \
    _r5 = _mm256_permute2f128_pd(_r9,_rB,32);   \
    _rD = ((const vtype*)(w2))[3];  \
    _r2 = vpma(_r2,_rC,_r7);    \
    _r4 = _mm256_permute2f128_pd(_r8,_rA,32);   \
    \
    _r9 = _mm256_permute2f128_pd(_r9,_rB,49);   \
    _r8 = _mm256_permute2f128_pd(_r8,_rA,49);   \
    _r3 = vpms(_r3,_rC,_r6);    \
    \
    _rC = ((const vtype*)(w2))[2];  \
    _r7 = vmul(_r9,_rF);    \
    _r6 = vmul(_r8,_rF);    \
    _rA = vmul(_r5,_rD);    \
    _rB = vmul(_r4,_rD);    \
    \
    _r8 = vpma(_r8,_rE,_r7);    \
    _r9 = vpms(_r9,_rE,_r6);    \
    _r4 = vpma(_r4,_rC,_rA);    \
    _r5 = vpms(_r5,_rC,_rB);    \
    \
    _rA = vadd(_r2,_r8);    \
    _r2 = vsub(_r2,_r8);    \
    _rB = vadd(_r3,_r9);    \
    _r3 = vsub(_r3,_r9);    \
    \
    _r6 = vadd(_r0,_r4);    \
    _r0 = vsub(_r0,_r4);    \
    _r7 = vadd(_r1,_r5);    \
    _r1 = vsub(_r1,_r5);    \
    \
    _r4 = vadd(_r6,_rA);    \
    _r6 = vsub(_r6,_rA);    \
    _r5 = vadd(_r7,_rB);    \
    ((vtype*)(O))[0] = _r4; \
    _r7 = vsub(_r7,_rB);    \
    ((vtype*)(O))[4] = _r6; \
    _r8 = vsub(_r0,_r3);    \
    ((vtype*)(O))[1] = _r5; \
    _rA = vadd(_r0,_r3);    \
    ((vtype*)(O))[5] = _r7; \
    _r9 = vadd(_r1,_r2);    \
    ((vtype*)(O))[2] = _r8; \
    _rB = vsub(_r1,_r2);    \
    ((vtype*)(O))[3] = _r9; \
    \
    ((vtype*)(O))[6] = _rA; \
    ((vtype*)(O))[7] = _rB; \
}
#define sfft_cb_f64v2_t16_forward_AVX(I,O,tw){ \
    const f_vector *_w2 = (tw)->r1_2.ptr;   \
    const f_vector *_w1 = (tw)->r1_1.ptr;   \
    const f_vector *_w3 = (tw)->r1_3.ptr;   \
    \
    sfft_cb_f64v2_t16_forward_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        I,O,    \
        _w2,    \
        _w1,    \
        _w3 \
    );  \
}
#define sfft_cb_f64v2_t16_inverse_AVX(I,O,tw){ \
    const f_vector *_w2 = (tw)->r1_2.ptr;   \
    const f_vector *_w1 = (tw)->r1_1.ptr;   \
    const f_vector *_w3 = (tw)->r1_3.ptr;   \
    \
    sfft_cb_f64v2_t16_inverse_AVX_raw( \
        f_vector,   \
        fv_add,fv_sub,fv_mul,   \
        fv_pma,fv_pms,  \
        I,O,    \
        _w2,    \
        _w1,    \
        _w3 \
    );  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
