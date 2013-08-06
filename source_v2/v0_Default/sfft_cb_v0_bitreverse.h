/* sfft_cb_v0_bitreverse_Default.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 08/31/2011
 * Last Modified    : 08/31/2011
 * 
 */

#pragma once
#ifndef _sfft_cb_v0_bitreverse_Default_H
#define _sfft_cb_v0_bitreverse_Default_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cbr_transpose_b1(  \
    I0,I1,    \
    O0,O1   \
){  \
    ((f_vector*)(O0))[0] = ((const f_vector*)(I0))[0];   \
    ((f_vector*)(O0))[1] = ((const f_vector*)(I0))[1];   \
    ((f_vector*)(O1))[0] = ((const f_vector*)(I0))[2];   \
    ((f_vector*)(O1))[1] = ((const f_vector*)(I0))[3];   \
    ((f_vector*)(O0))[2] = ((const f_vector*)(I1))[0];   \
    ((f_vector*)(O0))[3] = ((const f_vector*)(I1))[1];   \
    ((f_vector*)(O1))[2] = ((const f_vector*)(I1))[2];   \
    ((f_vector*)(O1))[3] = ((const f_vector*)(I1))[3];   \
}
#define sfft_cbr_transpose_b1_normal    sfft_cbr_transpose_b1
#define sfft_cbr_transpose_b1_stream    sfft_cbr_transpose_b1
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_cbr_transpose_b2(  \
    I0,I1,I2,I3,    \
    O0,O1,O2,O3 \
){  \
    ((f_vector*)(O0))[0] = ((const f_vector*)(I0))[0];   \
    ((f_vector*)(O0))[1] = ((const f_vector*)(I0))[1];   \
    ((f_vector*)(O2))[0] = ((const f_vector*)(I0))[2];   \
    ((f_vector*)(O2))[1] = ((const f_vector*)(I0))[3];   \
    ((f_vector*)(O1))[0] = ((const f_vector*)(I0))[4];   \
    ((f_vector*)(O1))[1] = ((const f_vector*)(I0))[5];   \
    ((f_vector*)(O3))[0] = ((const f_vector*)(I0))[6];   \
    ((f_vector*)(O3))[1] = ((const f_vector*)(I0))[7];   \
    \
    ((f_vector*)(O0))[4] = ((const f_vector*)(I1))[0];   \
    ((f_vector*)(O0))[5] = ((const f_vector*)(I1))[1];   \
    ((f_vector*)(O2))[4] = ((const f_vector*)(I1))[2];   \
    ((f_vector*)(O2))[5] = ((const f_vector*)(I1))[3];   \
    ((f_vector*)(O1))[4] = ((const f_vector*)(I1))[4];   \
    ((f_vector*)(O1))[5] = ((const f_vector*)(I1))[5];   \
    ((f_vector*)(O3))[4] = ((const f_vector*)(I1))[6];   \
    ((f_vector*)(O3))[5] = ((const f_vector*)(I1))[7];   \
    \
    ((f_vector*)(O0))[2] = ((const f_vector*)(I2))[0];   \
    ((f_vector*)(O0))[3] = ((const f_vector*)(I2))[1];   \
    ((f_vector*)(O2))[2] = ((const f_vector*)(I2))[2];   \
    ((f_vector*)(O2))[3] = ((const f_vector*)(I2))[3];   \
    ((f_vector*)(O1))[2] = ((const f_vector*)(I2))[4];   \
    ((f_vector*)(O1))[3] = ((const f_vector*)(I2))[5];   \
    ((f_vector*)(O3))[2] = ((const f_vector*)(I2))[6];   \
    ((f_vector*)(O3))[3] = ((const f_vector*)(I2))[7];   \
    \
    ((f_vector*)(O0))[6] = ((const f_vector*)(I3))[0];   \
    ((f_vector*)(O0))[7] = ((const f_vector*)(I3))[1];   \
    ((f_vector*)(O2))[6] = ((const f_vector*)(I3))[2];   \
    ((f_vector*)(O2))[7] = ((const f_vector*)(I3))[3];   \
    ((f_vector*)(O1))[6] = ((const f_vector*)(I3))[4];   \
    ((f_vector*)(O1))[7] = ((const f_vector*)(I3))[5];   \
    ((f_vector*)(O3))[6] = ((const f_vector*)(I3))[6];   \
    ((f_vector*)(O3))[7] = ((const f_vector*)(I3))[7];   \
}
#define sfft_cbr_transpose_b2_normal    sfft_cbr_transpose_b2
#define sfft_cbr_transpose_b2_stream    sfft_cbr_transpose_b2
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
