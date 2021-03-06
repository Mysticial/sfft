/* sfft_cb_f64v1_SSE3.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/09/2012
 * Last Modified    : 02/09/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      f64v1   =   64-bit floating point (vectorize by 2)
 * 
 */

#pragma once
#ifndef _sfft_cb_v1_SSE3_H
#define _sfft_cb_v1_SSE3_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 2
#include "sfft_cb_f64v1_bitreverse_SSE2.h"
#include "../vk_Generic/sfft_cb_tg_b2.h"
#include "../vk_Generic/sfft_cb_tg_b3.h"
#include "../vk_Generic/sfft_cb_tg_b4.h"
#include "../vk_Generic/sfft_cb_tg_b5.h"
#include "../vk_Generic/sfft_cb_tg_b7.h"
#include "sfft_cb_f64v1_t4_SSE3.h"
#include "sfft_cb_f64v1_t8_SSE3.h"
#include "sfft_cb_f64v1_t16_SSE3.h"
#include "sfft_cb_f64v1_t32_SSE3.h"
#include "sfft_cb_f64v1_t64_SSE3.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 2
void sfft_cb_t16_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v1_t16_forward_SSE3(I,O,tw);
}
void sfft_cb_t16_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v1_t16_inverse_SSE3(I,O,tw);
}
void sfft_cb_t32_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v1_t32_forward_SSE3(I,O,tw);
}
void sfft_cb_t32_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v1_t32_inverse_SSE3(I,O,tw);
}
void sfft_cb_t64_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v1_t64_forward_SSE3(I,O,tw);
}
void sfft_cb_t64_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_f64v1_t64_inverse_SSE3(I,O,tw);
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
void sfft_cb_t24_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wr = fv_set1(((double*)tw->r3_1.ptr)[18]);
    f_vector wi = fv_set1(((double*)tw->r3_1.ptr)[16]);
    const f_vector *w1 = tw->r3_1.table[3];
    const f_vector *w2 = tw->r3_2.table[3];

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

    const f_vector *t8 = (tw)->r1_1.ptr;
    sfft_cb_f64v1_t8_forward_SSE3(I +  0,O +  0,t8);
    sfft_cb_f64v1_t8_forward_SSE3(I +  8,O +  8,t8);
    sfft_cb_f64v1_t8_forward_SSE3(I + 16,O + 16,t8);
}
void sfft_cb_t24_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    const f_vector *t8 = (tw)->r1_1.ptr;
    sfft_cb_f64v1_t8_inverse_SSE3(I +  0,O +  0,t8);
    sfft_cb_f64v1_t8_inverse_SSE3(I +  8,O +  8,t8);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 16,O + 16,t8);

    f_vector wr = fv_set1(((double*)tw->r3_1.ptr)[18]);
    f_vector wi = fv_set1(((double*)tw->r3_1.ptr)[16]);
    const f_vector *w1 = tw->r3_1.table[3];
    const f_vector *w2 = tw->r3_2.table[3];

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
const sfft_block sfft_cb_pb_t24 = {
    24 * 2 >> f_vk, 3, 3,
    sfft_cb_t24_forward,
    sfft_cb_t24_inverse,
    {24 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 5
void sfft_cb_t40_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wAr = fv_set1(((double*)tw->r5_1.ptr)[18*2]);
    f_vector wAi = fv_set1(((double*)tw->r5_1.ptr)[19*2]);
    f_vector wBr = fv_set1(((double*)tw->r5_1.ptr)[17*2]);
    f_vector wBi = fv_set1(((double*)tw->r5_1.ptr)[15*2]);
    const f_vector *w1 = tw->r5_1.table[3];
    const f_vector *w2 = tw->r5_2.table[3];
    const f_vector *w3 = tw->r5_3.table[3];
    const f_vector *w4 = tw->r5_4.table[3];

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

    w1 = tw->r1_1.ptr;
    sfft_cb_f64v1_t8_forward_SSE3(I +  0,O +  0,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I +  8,O +  8,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 16,O + 16,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 24,O + 24,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 32,O + 32,w1);
}
void sfft_cb_t40_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    const f_vector *w1,*w2,*w3,*w4;

    w1 = tw->r1_1.ptr;
    sfft_cb_f64v1_t8_inverse_SSE3(I +  0,O +  0,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I +  8,O +  8,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 16,O + 16,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 24,O + 24,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 32,O + 32,w1);

    f_vector wAr = fv_set1(((double*)tw->r5_1.ptr)[18*2]);
    f_vector wAi = fv_set1(((double*)tw->r5_1.ptr)[19*2]);
    f_vector wBr = fv_set1(((double*)tw->r5_1.ptr)[17*2]);
    f_vector wBi = fv_set1(((double*)tw->r5_1.ptr)[15*2]);
    w1 = tw->r5_1.table[3];
    w2 = tw->r5_2.table[3];
    w3 = tw->r5_3.table[3];
    w4 = tw->r5_4.table[3];

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
const sfft_block sfft_cb_pb_t40 = {
    40 * 2 >> f_vk, 5, 3,
    sfft_cb_t40_forward,
    sfft_cb_t40_inverse,
    {40 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 7
void sfft_cb_t56_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wAr = fv_set1(((double*)tw->r7_1.ptr)[22*2]);
    f_vector wAi = fv_set1(((double*)tw->r7_1.ptr)[23*2]);
    f_vector wBr = fv_set1(((double*)tw->r7_1.ptr)[17*2]);
    f_vector wBi = fv_set1(((double*)tw->r7_1.ptr)[27*2]);
    f_vector wCr = fv_set1(((double*)tw->r7_1.ptr)[25*2]);
    f_vector wCi = fv_set1(((double*)tw->r7_1.ptr)[19*2]);
    const f_vector *w1 = tw->r7_1.table[3];
    const f_vector *w2 = tw->r7_2.table[3];
    const f_vector *w3 = tw->r7_3.table[3];
    const f_vector *w4 = tw->r7_4.table[3];
    const f_vector *w5 = tw->r7_5.table[3];
    const f_vector *w6 = tw->r7_6.table[3];

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

    w1 = tw->r1_1.ptr;
    sfft_cb_f64v1_t8_forward_SSE3(I +  0,O +  0,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I +  8,O +  8,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 16,O + 16,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 24,O + 24,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 32,O + 32,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 40,O + 40,w1);
    sfft_cb_f64v1_t8_forward_SSE3(I + 48,O + 48,w1);
}
void sfft_cb_t56_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    const f_vector *w1,*w2,*w3,*w4,*w5,*w6;

    w1 = tw->r1_1.ptr;
    sfft_cb_f64v1_t8_inverse_SSE3(I +  0,O +  0,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I +  8,O +  8,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 16,O + 16,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 24,O + 24,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 32,O + 32,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 40,O + 40,w1);
    sfft_cb_f64v1_t8_inverse_SSE3(I + 48,O + 48,w1);

    f_vector wAr = fv_set1(((double*)tw->r7_1.ptr)[22*2]);
    f_vector wAi = fv_set1(((double*)tw->r7_1.ptr)[23*2]);
    f_vector wBr = fv_set1(((double*)tw->r7_1.ptr)[17*2]);
    f_vector wBi = fv_set1(((double*)tw->r7_1.ptr)[27*2]);
    f_vector wCr = fv_set1(((double*)tw->r7_1.ptr)[25*2]);
    f_vector wCi = fv_set1(((double*)tw->r7_1.ptr)[19*2]);
    w1 = tw->r7_1.table[3];
    w2 = tw->r7_2.table[3];
    w3 = tw->r7_3.table[3];
    w4 = tw->r7_4.table[3];
    w5 = tw->r7_5.table[3];
    w6 = tw->r7_6.table[3];

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
const sfft_block sfft_cb_pb_t56 = {
    56 * 2 >> f_vk, 7, 3,
    sfft_cb_t56_forward,
    sfft_cb_t56_inverse,
    {56 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
