/* sfft_cb_f64v2_AVX.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/09/2012
 * Last Modified    : 02/09/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 4)
 * 
 */

#pragma once
#ifndef _sfft_cb_v2_AVX_H
#define _sfft_cb_v2_AVX_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 2
#include "sfft_cb_f64v2_bitreverse_AVX.h"
#include "../vk_Generic/sfft_cb_tg_b2.h"
#include "../vk_Generic/sfft_cb_tg_b3.h"
#include "../vk_Generic/sfft_cb_tg_b4.h"
#include "../vk_Generic/sfft_cb_tg_b5.h"
#include "../vk_Generic/sfft_cb_tg_b7.h"
#include "sfft_cb_f64v2_t16_AVX.h"
#include "sfft_cb_f64v2_t32_AVX.h"
#include "sfft_cb_f64v2_t64_AVX.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 2
void sfft_cb_t16_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t16_forward_AVX(I,O,tw);
}
void sfft_cb_t16_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t16_inverse_AVX(I,O,tw);
}
void sfft_cb_t32_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t32_forward_AVX(I,O,tw);
}
void sfft_cb_t32_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t32_inverse_AVX(I,O,tw);
}
void sfft_cb_t64_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t64_forward_AVX(I,O,tw);
}
void sfft_cb_t64_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t64_inverse_AVX(I,O,tw);
}
const sfft_block sfft_cb_pb_t16 = {
    16 * 2 >> f_vk, 1, 4,
    sfft_cb_t16_forward,
    sfft_cb_t16_inverse,
    {16 * 2 >> f_vk,2,3}
};
const sfft_block sfft_cb_pb_t32 = {
    32 * 2 >> f_vk, 1, 5,
    sfft_cb_t32_forward,
    sfft_cb_t32_inverse,
    {32 * 2 >> f_vk,2,3}
};
const sfft_block sfft_cb_pb_t64 = {
    64 * 2 >> f_vk, 1, 6,
    sfft_cb_t64_forward,
    sfft_cb_t64_inverse,
    {64 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 3
void sfft_cb_t48_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wr = fv_set1(((double*)tw->r3_1.ptr)[36]);
    f_vector wi = fv_set1(((double*)tw->r3_1.ptr)[32]);
    const f_vector *w1 = tw->r3_1.table[4];
    const f_vector *w2 = tw->r3_2.table[4];

    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  0,I +  8,I + 16,
        wr,wi,
        w1 +  0,w2 +  0
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  2,I + 10,I + 18,
        wr,wi,
        w1 +  2,w2 +  2
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  4,I + 12,I + 20,
        wr,wi,
        w1 +  4,w2 +  4
    );
    sfft_cb_tg_vt3_m16_forward_v1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  6,I + 14,I + 22,
        wr,wi,
        w1 +  0,w2 +  0
    );

    sfft_cb_f64v2_t16_forward_AVX(I +  0,O +  0,tw);
    sfft_cb_f64v2_t16_forward_AVX(I +  8,O +  8,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 16,O + 16,tw);
}
void sfft_cb_t48_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t16_inverse_AVX(I +  0,O +  0,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I +  8,O +  8,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 16,O + 16,tw);

    f_vector wr = fv_set1(((double*)tw->r3_1.ptr)[36]);
    f_vector wi = fv_set1(((double*)tw->r3_1.ptr)[32]);
    const f_vector *w1 = tw->r3_1.table[4];
    const f_vector *w2 = tw->r3_2.table[4];

    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  0,O +  8,O + 16,
        wr,wi,
        w1 +  0,w2 +  0
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  2,O + 10,O + 18,
        wr,wi,
        w1 +  2,w2 +  2
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  4,O + 12,O + 20,
        wr,wi,
        w1 +  4,w2 +  4
    );
    sfft_cb_tg_vt3_m16_inverse_v1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  6,O + 14,O + 22,
        wr,wi,
        w1 +  0,w2 +  0
    );
}
const sfft_block sfft_cb_pb_t48 = {
    48 * 2 >> f_vk, 3, 4,
    sfft_cb_t48_forward,
    sfft_cb_t48_inverse,
    {48 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 5
void sfft_cb_t80_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wAr = fv_set1(((double*)tw->r5_1.ptr)[18*4]);
    f_vector wAi = fv_set1(((double*)tw->r5_1.ptr)[19*4]);
    f_vector wBr = fv_set1(((double*)tw->r5_1.ptr)[17*4]);
    f_vector wBi = fv_set1(((double*)tw->r5_1.ptr)[15*4]);
    const f_vector *w1 = tw->r5_1.table[4];
    const f_vector *w2 = tw->r5_2.table[4];
    const f_vector *w3 = tw->r5_3.table[4];
    const f_vector *w4 = tw->r5_4.table[4];

    sfft_cb_tg_vt5_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  0,I +  8,I + 16,I + 24,I + 32,
        wAr,wAi,wBr,wBi,
        w1 +  0,w2 +  0,w3 +  0,w4 +  0
    );
    sfft_cb_tg_vt5_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  2,I + 10,I + 18,I + 26,I + 34,
        wAr,wAi,wBr,wBi,
        w1 +  2,w2 +  2,w3 +  2,w4 +  2
    );
    sfft_cb_tg_vt5_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  4,I + 12,I + 20,I + 28,I + 36,
        wAr,wAi,wBr,wBi,
        w1 +  4,w2 +  4,w3 +  4,w4 +  4
    );
    sfft_cb_tg_vt5_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  6,I + 14,I + 22,I + 30,I + 38,
        wAr,wAi,wBr,wBi,
        w1 +  6,w2 +  6,w3 +  6,w4 +  6
    );

    sfft_cb_f64v2_t16_forward_AVX(I +  0,O +  0,tw);
    sfft_cb_f64v2_t16_forward_AVX(I +  8,O +  8,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 16,O + 16,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 24,O + 24,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 32,O + 32,tw);
}
void sfft_cb_t80_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t16_inverse_AVX(I +  0,O +  0,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I +  8,O +  8,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 16,O + 16,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 24,O + 24,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 32,O + 32,tw);
    
    f_vector wAr = fv_set1(((double*)tw->r5_1.ptr)[18*4]);
    f_vector wAi = fv_set1(((double*)tw->r5_1.ptr)[19*4]);
    f_vector wBr = fv_set1(((double*)tw->r5_1.ptr)[17*4]);
    f_vector wBi = fv_set1(((double*)tw->r5_1.ptr)[15*4]);
    const f_vector *w1 = tw->r5_1.table[4];
    const f_vector *w2 = tw->r5_2.table[4];
    const f_vector *w3 = tw->r5_3.table[4];
    const f_vector *w4 = tw->r5_4.table[4];

    sfft_cb_tg_vt5_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  0,O +  8,O + 16,O + 24,O + 32,
        wAr,wAi,wBr,wBi,
        w1 +  0,w2 +  0,w3 +  0,w4 +  0
    );
    sfft_cb_tg_vt5_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  2,O + 10,O + 18,O + 26,O + 34,
        wAr,wAi,wBr,wBi,
        w1 +  2,w2 +  2,w3 +  2,w4 +  2
    );
    sfft_cb_tg_vt5_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  4,O + 12,O + 20,O + 28,O + 36,
        wAr,wAi,wBr,wBi,
        w1 +  4,w2 +  4,w3 +  4,w4 +  4
    );
    sfft_cb_tg_vt5_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  6,O + 14,O + 22,O + 30,O + 38,
        wAr,wAi,wBr,wBi,
        w1 +  6,w2 +  6,w3 +  6,w4 +  6
    );
}
const sfft_block sfft_cb_pb_t80 = {
    80 * 2 >> f_vk, 5, 4,
    sfft_cb_t80_forward,
    sfft_cb_t80_inverse,
    {80 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 7
void sfft_cb_t112_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wAr = fv_set1(((double*)tw->r7_1.ptr)[22*4]);
    f_vector wAi = fv_set1(((double*)tw->r7_1.ptr)[23*4]);
    f_vector wBr = fv_set1(((double*)tw->r7_1.ptr)[17*4]);
    f_vector wBi = fv_set1(((double*)tw->r7_1.ptr)[27*4]);
    f_vector wCr = fv_set1(((double*)tw->r7_1.ptr)[25*4]);
    f_vector wCi = fv_set1(((double*)tw->r7_1.ptr)[19*4]);
    const f_vector *w1 = tw->r7_1.table[4];
    const f_vector *w2 = tw->r7_2.table[4];
    const f_vector *w3 = tw->r7_3.table[4];
    const f_vector *w4 = tw->r7_4.table[4];
    const f_vector *w5 = tw->r7_5.table[4];
    const f_vector *w6 = tw->r7_6.table[4];

    sfft_cb_tg_vt7_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  0,I +  8,I + 16,I + 24,I + 32,I + 40,I + 48,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  0,w2 +  0,w3 +  0,w4 +  0,w5 +  0,w6 +  0
    );
    sfft_cb_tg_vt7_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  2,I + 10,I + 18,I + 26,I + 34,I + 42,I + 50,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  2,w2 +  2,w3 +  2,w4 +  2,w5 +  2,w6 +  2
    );
    sfft_cb_tg_vt7_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  4,I + 12,I + 20,I + 28,I + 36,I + 44,I + 52,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  4,w2 +  4,w3 +  4,w4 +  4,w5 +  4,w6 +  4
    );
    sfft_cb_tg_vt7_m16_forward0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  6,I + 14,I + 22,I + 30,I + 38,I + 46,I + 54,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  6,w2 +  6,w3 +  6,w4 +  6,w5 +  6,w6 +  6
    );

    sfft_cb_f64v2_t16_forward_AVX(I +  0,O +  0,tw);
    sfft_cb_f64v2_t16_forward_AVX(I +  8,O +  8,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 16,O + 16,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 24,O + 24,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 32,O + 32,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 40,O + 40,tw);
    sfft_cb_f64v2_t16_forward_AVX(I + 48,O + 48,tw);
}
void sfft_cb_t112_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v2_t16_inverse_AVX(I +  0,O +  0,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I +  8,O +  8,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 16,O + 16,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 24,O + 24,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 32,O + 32,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 40,O + 40,tw);
    sfft_cb_f64v2_t16_inverse_AVX(I + 48,O + 48,tw);
    
    f_vector wAr = fv_set1(((double*)tw->r7_1.ptr)[22*4]);
    f_vector wAi = fv_set1(((double*)tw->r7_1.ptr)[23*4]);
    f_vector wBr = fv_set1(((double*)tw->r7_1.ptr)[17*4]);
    f_vector wBi = fv_set1(((double*)tw->r7_1.ptr)[27*4]);
    f_vector wCr = fv_set1(((double*)tw->r7_1.ptr)[25*4]);
    f_vector wCi = fv_set1(((double*)tw->r7_1.ptr)[19*4]);
    const f_vector *w1 = tw->r7_1.table[4];
    const f_vector *w2 = tw->r7_2.table[4];
    const f_vector *w3 = tw->r7_3.table[4];
    const f_vector *w4 = tw->r7_4.table[4];
    const f_vector *w5 = tw->r7_5.table[4];
    const f_vector *w6 = tw->r7_6.table[4];

    sfft_cb_tg_vt7_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  0,O +  8,O + 16,O + 24,O + 32,O + 40,O + 48,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  0,w2 +  0,w3 +  0,w4 +  0,w5 +  0,w6 +  0
    );
    sfft_cb_tg_vt7_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  2,O + 10,O + 18,O + 26,O + 34,O + 42,O + 50,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  2,w2 +  2,w3 +  2,w4 +  2,w5 +  2,w6 +  2
    );
    sfft_cb_tg_vt7_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  4,O + 12,O + 20,O + 28,O + 36,O + 44,O + 52,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  4,w2 +  4,w3 +  4,w4 +  4,w5 +  4,w6 +  4
    );
    sfft_cb_tg_vt7_m16_inverse0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  6,O + 14,O + 22,O + 30,O + 38,O + 46,O + 54,
        wAr,wAi,wBr,wBi,wCr,wCi,
        w1 +  6,w2 +  6,w3 +  6,w4 +  6,w5 +  6,w6 +  6
    );
}
const sfft_block sfft_cb_pb_t112 = {
    112 * 2 >> f_vk, 7, 4,
    sfft_cb_t112_forward,
    sfft_cb_t112_inverse,
    {112 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
