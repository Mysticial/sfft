/* sfft_cb_f64v2_bitreverse_AVX.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 08/31/2011
 * Last Modified    : 08/31/2011
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v2_bitreverse_AVX_H
#define _sfft_cb_f64v2_bitreverse_AVX_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cbr_transpose_b2_normal(   \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3 \
){  \
    f_vector _r0_0,_i0_0;   \
    f_vector _r1_0,_i1_0;   \
    f_vector _r2_0,_i2_0;   \
    f_vector _r3_0,_i3_0;   \
    f_vector _r0,_r1,_r2,_r3;   \
    f_vector _i0,_i1,_i2,_i3;   \
    \
    _r0_0 = ((const f_vector*)(I0))[0]; \
    _i0_0 = ((const f_vector*)(I0))[1]; \
    _r1_0 = ((const f_vector*)(I1))[0]; \
    _i1_0 = ((const f_vector*)(I1))[1]; \
    _r2_0 = ((const f_vector*)(I2))[0]; \
    _i2_0 = ((const f_vector*)(I2))[1]; \
    _r3_0 = ((const f_vector*)(I3))[0]; \
    _i3_0 = ((const f_vector*)(I3))[1]; \
    \
    _r0 = _mm256_permute2f128_pd(_r0_0,_r1_0,32);   \
    _r1 = _mm256_permute2f128_pd(_r0_0,_r1_0,49);   \
    _i0 = _mm256_permute2f128_pd(_i0_0,_i1_0,32);   \
    _i1 = _mm256_permute2f128_pd(_i0_0,_i1_0,49);   \
    _r2 = _mm256_permute2f128_pd(_r2_0,_r3_0,32);   \
    _r3 = _mm256_permute2f128_pd(_r2_0,_r3_0,49);   \
    _i2 = _mm256_permute2f128_pd(_i2_0,_i3_0,32);   \
    _i3 = _mm256_permute2f128_pd(_i2_0,_i3_0,49);   \
    \
    _mm256_store_pd((double*)(O0) + 0,_mm256_unpacklo_pd(_r0,_r2));    \
    _mm256_store_pd((double*)(O0) + 4,_mm256_unpacklo_pd(_i0,_i2));    \
    _mm256_store_pd((double*)(O1) + 0,_mm256_unpacklo_pd(_r1,_r3));    \
    _mm256_store_pd((double*)(O1) + 4,_mm256_unpacklo_pd(_i1,_i3));    \
    _mm256_store_pd((double*)(O2) + 0,_mm256_unpackhi_pd(_r0,_r2));    \
    _mm256_store_pd((double*)(O2) + 4,_mm256_unpackhi_pd(_i0,_i2));    \
    _mm256_store_pd((double*)(O3) + 0,_mm256_unpackhi_pd(_r1,_r3));    \
    _mm256_store_pd((double*)(O3) + 4,_mm256_unpackhi_pd(_i1,_i3));    \
}
#define sfft_cbr_transpose_b2_stream(   \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3 \
){  \
    f_vector _r0_0,_i0_0;   \
    f_vector _r1_0,_i1_0;   \
    f_vector _r2_0,_i2_0;   \
    f_vector _r3_0,_i3_0;   \
    f_vector _r0,_r1,_r2,_r3;   \
    f_vector _i0,_i1,_i2,_i3;   \
    \
    _r0_0 = ((const f_vector*)(I0))[0]; \
    _i0_0 = ((const f_vector*)(I0))[1]; \
    _r1_0 = ((const f_vector*)(I1))[0]; \
    _i1_0 = ((const f_vector*)(I1))[1]; \
    _r2_0 = ((const f_vector*)(I2))[0]; \
    _i2_0 = ((const f_vector*)(I2))[1]; \
    _r3_0 = ((const f_vector*)(I3))[0]; \
    _i3_0 = ((const f_vector*)(I3))[1]; \
    \
    _r0 = _mm256_permute2f128_pd(_r0_0,_r1_0,32);   \
    _r1 = _mm256_permute2f128_pd(_r0_0,_r1_0,49);   \
    _i0 = _mm256_permute2f128_pd(_i0_0,_i1_0,32);   \
    _i1 = _mm256_permute2f128_pd(_i0_0,_i1_0,49);   \
    _r2 = _mm256_permute2f128_pd(_r2_0,_r3_0,32);   \
    _r3 = _mm256_permute2f128_pd(_r2_0,_r3_0,49);   \
    _i2 = _mm256_permute2f128_pd(_i2_0,_i3_0,32);   \
    _i3 = _mm256_permute2f128_pd(_i2_0,_i3_0,49);   \
    \
    _mm256_stream_pd((double*)(O0) + 0,_mm256_unpacklo_pd(_r0,_r2));    \
    _mm256_stream_pd((double*)(O0) + 4,_mm256_unpacklo_pd(_i0,_i2));    \
    _mm256_stream_pd((double*)(O1) + 0,_mm256_unpacklo_pd(_r1,_r3));    \
    _mm256_stream_pd((double*)(O1) + 4,_mm256_unpacklo_pd(_i1,_i3));    \
    _mm256_stream_pd((double*)(O2) + 0,_mm256_unpackhi_pd(_r0,_r2));    \
    _mm256_stream_pd((double*)(O2) + 4,_mm256_unpackhi_pd(_i0,_i2));    \
    _mm256_stream_pd((double*)(O3) + 0,_mm256_unpackhi_pd(_r1,_r3));    \
    _mm256_stream_pd((double*)(O3) + 4,_mm256_unpackhi_pd(_i1,_i3));    \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
