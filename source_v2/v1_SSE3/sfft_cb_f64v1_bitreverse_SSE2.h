/* sfft_cb_f64v1_bitreverse_SSE2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 08/31/2011
 * Last Modified    : 08/31/2011
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_bitreverse_SSE2_H
#define _sfft_cb_f64v1_bitreverse_SSE2_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cbr_transpose_b1_normal(   \
    I0,I1,    \
    O0,O1   \
){  \
    f_vector _r0_0,_i0_0;   \
    f_vector _r1_0,_i1_0;   \
    \
    _r0_0 = ((const f_vector*)(I0))[0]; \
    _i0_0 = ((const f_vector*)(I0))[1]; \
    _r1_0 = ((const f_vector*)(I1))[0]; \
    _i1_0 = ((const f_vector*)(I1))[1]; \
    \
    ((f_vector*)(O0))[0] = _mm_unpacklo_pd(_r0_0,_r1_0);    \
    ((f_vector*)(O0))[1] = _mm_unpacklo_pd(_i0_0,_i1_0);    \
    ((f_vector*)(O1))[0] = _mm_unpackhi_pd(_r0_0,_r1_0);    \
    ((f_vector*)(O1))[1] = _mm_unpackhi_pd(_i0_0,_i1_0);    \
}
#define sfft_cbr_transpose_b1_stream    sfft_cbr_transpose_b1_normal
#define sfft_cbr_transpose_b2_normal(  \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3 \
){  \
    f_vector _r0_0,_i0_0,_r0_1,_i0_1;   \
    f_vector _r1_0,_i1_0,_r1_1,_i1_1;   \
    f_vector _r2_0,_i2_0,_r2_1,_i2_1;   \
    f_vector _r3_0,_i3_0,_r3_1,_i3_1;   \
    \
    _r0_0 = ((const f_vector*)(I0))[0]; \
    _i0_0 = ((const f_vector*)(I0))[1]; \
    _r0_1 = ((const f_vector*)(I0))[2]; \
    _i0_1 = ((const f_vector*)(I0))[3]; \
    \
    _r2_0 = ((const f_vector*)(I2))[0]; \
    _i2_0 = ((const f_vector*)(I2))[1]; \
    _r2_1 = ((const f_vector*)(I2))[2]; \
    _i2_1 = ((const f_vector*)(I2))[3]; \
    \
    _r1_0 = ((const f_vector*)(I1))[0]; \
    _i1_0 = ((const f_vector*)(I1))[1]; \
    _r1_1 = ((const f_vector*)(I1))[2]; \
    _i1_1 = ((const f_vector*)(I1))[3]; \
    \
    _r3_0 = ((const f_vector*)(I3))[0]; \
    _i3_0 = ((const f_vector*)(I3))[1]; \
    _r3_1 = ((const f_vector*)(I3))[2]; \
    _i3_1 = ((const f_vector*)(I3))[3]; \
    \
    _mm_store_pd((double*)(O0) + 0,_mm_unpacklo_pd(_r0_0,_r2_0));  \
    _mm_store_pd((double*)(O0) + 2,_mm_unpacklo_pd(_i0_0,_i2_0));  \
    _mm_store_pd((double*)(O0) + 4,_mm_unpacklo_pd(_r1_0,_r3_0));  \
    _mm_store_pd((double*)(O0) + 6,_mm_unpacklo_pd(_i1_0,_i3_0));  \
    \
    _mm_store_pd((double*)(O1) + 0,_mm_unpacklo_pd(_r0_1,_r2_1));  \
    _mm_store_pd((double*)(O1) + 2,_mm_unpacklo_pd(_i0_1,_i2_1));  \
    _mm_store_pd((double*)(O1) + 4,_mm_unpacklo_pd(_r1_1,_r3_1));  \
    _mm_store_pd((double*)(O1) + 6,_mm_unpacklo_pd(_i1_1,_i3_1));  \
    \
    _mm_store_pd((double*)(O2) + 0,_mm_unpackhi_pd(_r0_0,_r2_0));  \
    _mm_store_pd((double*)(O2) + 2,_mm_unpackhi_pd(_i0_0,_i2_0));  \
    _mm_store_pd((double*)(O2) + 4,_mm_unpackhi_pd(_r1_0,_r3_0));  \
    _mm_store_pd((double*)(O2) + 6,_mm_unpackhi_pd(_i1_0,_i3_0));  \
    \
    _mm_store_pd((double*)(O3) + 0,_mm_unpackhi_pd(_r0_1,_r2_1));  \
    _mm_store_pd((double*)(O3) + 2,_mm_unpackhi_pd(_i0_1,_i2_1));  \
    _mm_store_pd((double*)(O3) + 4,_mm_unpackhi_pd(_r1_1,_r3_1));  \
    _mm_store_pd((double*)(O3) + 6,_mm_unpackhi_pd(_i1_1,_i3_1));  \
}
#define sfft_cbr_transpose_b2_stream(   \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3 \
){  \
    f_vector _r0_0,_i0_0,_r0_1,_i0_1;   \
    f_vector _r1_0,_i1_0,_r1_1,_i1_1;   \
    f_vector _r2_0,_i2_0,_r2_1,_i2_1;   \
    f_vector _r3_0,_i3_0,_r3_1,_i3_1;   \
    \
    _r0_0 = ((const f_vector*)(I0))[0]; \
    _i0_0 = ((const f_vector*)(I0))[1]; \
    _r0_1 = ((const f_vector*)(I0))[2]; \
    _i0_1 = ((const f_vector*)(I0))[3]; \
    \
    _r2_0 = ((const f_vector*)(I2))[0]; \
    _i2_0 = ((const f_vector*)(I2))[1]; \
    _r2_1 = ((const f_vector*)(I2))[2]; \
    _i2_1 = ((const f_vector*)(I2))[3]; \
    \
    _r1_0 = ((const f_vector*)(I1))[0]; \
    _i1_0 = ((const f_vector*)(I1))[1]; \
    _r1_1 = ((const f_vector*)(I1))[2]; \
    _i1_1 = ((const f_vector*)(I1))[3]; \
    \
    _r3_0 = ((const f_vector*)(I3))[0]; \
    _i3_0 = ((const f_vector*)(I3))[1]; \
    _r3_1 = ((const f_vector*)(I3))[2]; \
    _i3_1 = ((const f_vector*)(I3))[3]; \
    \
    _mm_stream_pd((double*)(O0) + 0,_mm_unpacklo_pd(_r0_0,_r2_0));  \
    _mm_stream_pd((double*)(O0) + 2,_mm_unpacklo_pd(_i0_0,_i2_0));  \
    _mm_stream_pd((double*)(O0) + 4,_mm_unpacklo_pd(_r1_0,_r3_0));  \
    _mm_stream_pd((double*)(O0) + 6,_mm_unpacklo_pd(_i1_0,_i3_0));  \
    \
    _mm_stream_pd((double*)(O1) + 0,_mm_unpacklo_pd(_r0_1,_r2_1));  \
    _mm_stream_pd((double*)(O1) + 2,_mm_unpacklo_pd(_i0_1,_i2_1));  \
    _mm_stream_pd((double*)(O1) + 4,_mm_unpacklo_pd(_r1_1,_r3_1));  \
    _mm_stream_pd((double*)(O1) + 6,_mm_unpacklo_pd(_i1_1,_i3_1));  \
    \
    _mm_stream_pd((double*)(O2) + 0,_mm_unpackhi_pd(_r0_0,_r2_0));  \
    _mm_stream_pd((double*)(O2) + 2,_mm_unpackhi_pd(_i0_0,_i2_0));  \
    _mm_stream_pd((double*)(O2) + 4,_mm_unpackhi_pd(_r1_0,_r3_0));  \
    _mm_stream_pd((double*)(O2) + 6,_mm_unpackhi_pd(_i1_0,_i3_0));  \
    \
    _mm_stream_pd((double*)(O3) + 0,_mm_unpackhi_pd(_r0_1,_r2_1));  \
    _mm_stream_pd((double*)(O3) + 2,_mm_unpackhi_pd(_i0_1,_i2_1));  \
    _mm_stream_pd((double*)(O3) + 4,_mm_unpackhi_pd(_r1_1,_r3_1));  \
    _mm_stream_pd((double*)(O3) + 6,_mm_unpackhi_pd(_i1_1,_i3_1));  \
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
