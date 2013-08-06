/* sfft_cb_v0_Default.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/09/2012
 * Last Modified    : 02/09/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      v0      =   Vectorize by 1
 * 
 */

#include <string.h>
#include <stdio.h>

#pragma once
#ifndef _sfft_cb_v0_Default_H
#define _sfft_cb_v0_Default_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Block Copy
void sfft_cb_pb_raw_to_FFT(f_vector *T,const f_word *A,i_ptr vsize){
    memcpy(T,A,sizeof(f_vector) * vsize * 2);

//    f_vector *stop = T + vsize*2;

    //while (T < stop){

    //    T += 2;
    //}
}
void sfft_cb_pb_FFT_to_raw(const f_vector *T,f_word *A,i_ptr vsize){
    memcpy(A,T,sizeof(f_vector) * vsize * 2);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 2
#include "sfft_cb_v0_bitreverse.h"
#include "../vk_Generic/sfft_cb_tg_b2.h"
#include "../vk_Generic/sfft_cb_tg_b3.h"
#include "../vk_Generic/sfft_cb_tg_b4.h"
#include "../vk_Generic/sfft_cb_tg_b5.h"
#include "../vk_Generic/sfft_cb_tg_b7.h"
#include "sfft_cb_v0_t4_Default.h"
#include "sfft_cb_v0_t8_Default.h"
#include "sfft_cb_v0_t16_Default.h"
#include "sfft_cb_v0_t32_Default.h"
#include "sfft_cb_v0_t64_Default.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 2
void sfft_cb_t16_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t16_forward_Default(I,O,tw);
}
void sfft_cb_t16_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t16_inverse_Default(I,O,tw);
}
void sfft_cb_t32_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t32_forward_Default(I,O,tw);
}
void sfft_cb_t32_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t32_inverse_Default(I,O,tw);
}
void sfft_cb_t64_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t64_forward_Default(I,O,tw);
}
void sfft_cb_t64_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t64_inverse_Default(I,O,tw);
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
void sfft_cb_t12_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wr = tw->r3_1.ptr[9];
    f_vector wi = tw->r3_1.ptr[8];
    const f_vector *w1 = tw->r3_1.table[2];
    const f_vector *w2 = tw->r3_2.table[2];

    sfft_cb_tg_vt3_m16_forward_s0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  0,I +  8,I + 16,
        wr,wi
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  2,I + 10,I + 18,
        wr,wi,
        w1 + 2,w2 + 2
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  4,I + 12,I + 20,
        wr,wi,
        w1 + 4,w2 + 4
    );
    sfft_cb_tg_vt3_m16_forward_s1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  6,I + 14,I + 22,
        wr,wi
    );

    sfft_cb_v0_t4_forward_Default(I +  0,O +  0);
    sfft_cb_v0_t4_forward_Default(I +  8,O +  8);
    sfft_cb_v0_t4_forward_Default(I + 16,O + 16);
}
void sfft_cb_t12_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t4_inverse_Default(I +  0,O +  0);
    sfft_cb_v0_t4_inverse_Default(I +  8,O +  8);
    sfft_cb_v0_t4_inverse_Default(I + 16,O + 16);

    f_vector wr = tw->r3_1.ptr[9];
    f_vector wi = tw->r3_1.ptr[8];
    const f_vector *w1 = tw->r3_1.table[2];
    const f_vector *w2 = tw->r3_2.table[2];

    sfft_cb_tg_vt3_m16_inverse_s0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  0,O +  8,O + 16,
        wr,wi
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  2,O + 10,O + 18,
        wr,wi,
        w1 + 2,w2 + 2
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  4,O + 12,O + 20,
        wr,wi,
        w1 + 4,w2 + 4
    );
    sfft_cb_tg_vt3_m16_inverse_s1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  6,O + 14,O + 22,
        wr,wi
    );
}
void sfft_cb_t24_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wr = tw->r3_1.ptr[9];
    f_vector wi = tw->r3_1.ptr[8];
    const f_vector *w1 = tw->r3_1.table[3];
    const f_vector *w2 = tw->r3_2.table[3];

    sfft_cb_tg_vt3_m16_forward_s0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  0,I + 16,I + 32,
        wr,wi
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  2,I + 18,I + 34,
        wr,wi,
        w1 +  2,w2 +  2
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  4,I + 20,I + 36,
        wr,wi,
        w1 +  4,w2 +  4
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  6,I + 22,I + 38,
        wr,wi,
        w1 +  6,w2 +  6
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I +  8,I + 24,I + 40,
        wr,wi,
        w1 +  8,w2 +  8
    );
    sfft_cb_tg_vt3_m16_forward_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I + 10,I + 26,I + 42,
        wr,wi,
        w1 + 10,w2 + 10
    );
    sfft_cb_tg_vt3_m16_forward_s1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I + 12,I + 28,I + 44,
        wr,wi
    );
    sfft_cb_tg_vt3_m16_forward_v1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        I + 14,I + 30,I + 46,
        wr,wi,
        w1 +  2,w2 +  2
    );

    const f_vector *t8 = (tw)->r1_1.ptr;
    sfft_cb_v0_t8_forward_Default(I +  0,O +  0,t8);
    sfft_cb_v0_t8_forward_Default(I + 16,O + 16,t8);
    sfft_cb_v0_t8_forward_Default(I + 32,O + 32,t8);
}
void sfft_cb_t24_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    const f_vector *t8 = (tw)->r1_1.ptr;
    sfft_cb_v0_t8_inverse_Default(I +  0,O +  0,t8);
    sfft_cb_v0_t8_inverse_Default(I + 16,O + 16,t8);
    sfft_cb_v0_t8_inverse_Default(I + 32,O + 32,t8);

    f_vector wr = tw->r3_1.ptr[9];
    f_vector wi = tw->r3_1.ptr[8];
    const f_vector *w1 = tw->r3_1.table[3];
    const f_vector *w2 = tw->r3_2.table[3];

    sfft_cb_tg_vt3_m16_inverse_s0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  0,O + 16,O + 32,
        wr,wi
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  2,O + 18,O + 34,
        wr,wi,
        w1 +  2,w2 +  2
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  4,O + 20,O + 36,
        wr,wi,
        w1 +  4,w2 +  4
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  6,O + 22,O + 38,
        wr,wi,
        w1 +  6,w2 +  6
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O +  8,O + 24,O + 40,
        wr,wi,
        w1 +  8,w2 +  8
    );
    sfft_cb_tg_vt3_m16_inverse_v0(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O + 10,O + 26,O + 42,
        wr,wi,
        w1 + 10,w2 + 10
    );
    sfft_cb_tg_vt3_m16_inverse_s1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O + 12,O + 28,O + 44,
        wr,wi
    );
    sfft_cb_tg_vt3_m16_inverse_v1(
        f_vector,
        fv_add,fv_sub,fv_mul,
        fv_pma,fv_pms,
        O + 14,O + 30,O + 46,
        wr,wi,
        w1 +  2,w2 +  2
    );
}
const sfft_block sfft_cb_pb_t12 = {
    12 * 2 >> f_vk, 3, 2,
    sfft_cb_t12_forward,
    sfft_cb_t12_inverse,
    {12 * 2 >> f_vk,2,3}
};
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
void sfft_cb_t20_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wAr = fv_set1(((double*)tw->r5_1.ptr)[18]);
    f_vector wAi = fv_set1(((double*)tw->r5_1.ptr)[19]);
    f_vector wBr = fv_set1(((double*)tw->r5_1.ptr)[17]);
    f_vector wBi = fv_set1(((double*)tw->r5_1.ptr)[15]);
    const f_vector *w1 = tw->r5_1.table[2];
    const f_vector *w2 = tw->r5_2.table[2];
    const f_vector *w3 = tw->r5_3.table[2];
    const f_vector *w4 = tw->r5_4.table[2];

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

    sfft_cb_v0_t4_forward_Default(I +  0,O +  0);
    sfft_cb_v0_t4_forward_Default(I +  8,O +  8);
    sfft_cb_v0_t4_forward_Default(I + 16,O + 16);
    sfft_cb_v0_t4_forward_Default(I + 24,O + 24);
    sfft_cb_v0_t4_forward_Default(I + 32,O + 32);
}
void sfft_cb_t20_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t4_inverse_Default(I +  0,O +  0);
    sfft_cb_v0_t4_inverse_Default(I +  8,O +  8);
    sfft_cb_v0_t4_inverse_Default(I + 16,O + 16);
    sfft_cb_v0_t4_inverse_Default(I + 24,O + 24);
    sfft_cb_v0_t4_inverse_Default(I + 32,O + 32);

    f_vector wAr = fv_set1(((double*)tw->r5_1.ptr)[18]);
    f_vector wAi = fv_set1(((double*)tw->r5_1.ptr)[19]);
    f_vector wBr = fv_set1(((double*)tw->r5_1.ptr)[17]);
    f_vector wBi = fv_set1(((double*)tw->r5_1.ptr)[15]);
    const f_vector *w1 = tw->r5_1.table[2];
    const f_vector *w2 = tw->r5_2.table[2];
    const f_vector *w3 = tw->r5_3.table[2];
    const f_vector *w4 = tw->r5_4.table[2];

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
const sfft_block sfft_cb_pb_t20 = {
    20 * 2 >> f_vk, 5, 2,
    sfft_cb_t20_forward,
    sfft_cb_t20_inverse,
    {20 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix 7
void sfft_cb_t28_forward(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    f_vector wAr = fv_set1(((double*)tw->r7_1.ptr)[22]);
    f_vector wAi = fv_set1(((double*)tw->r7_1.ptr)[23]);
    f_vector wBr = fv_set1(((double*)tw->r7_1.ptr)[17]);
    f_vector wBi = fv_set1(((double*)tw->r7_1.ptr)[27]);
    f_vector wCr = fv_set1(((double*)tw->r7_1.ptr)[25]);
    f_vector wCi = fv_set1(((double*)tw->r7_1.ptr)[19]);
    const f_vector *w1 = tw->r7_1.table[2];
    const f_vector *w2 = tw->r7_2.table[2];
    const f_vector *w3 = tw->r7_3.table[2];
    const f_vector *w4 = tw->r7_4.table[2];
    const f_vector *w5 = tw->r7_5.table[2];
    const f_vector *w6 = tw->r7_6.table[2];

//    cout << wAr << "  " << wAi << endl;
//    cout << wBr << "  " << wBi << endl;
//    cout << wCr << "  " << wCi << endl;

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

    sfft_cb_v0_t4_forward_Default(I +  0,O +  0);
    sfft_cb_v0_t4_forward_Default(I +  8,O +  8);
    sfft_cb_v0_t4_forward_Default(I + 16,O + 16);
    sfft_cb_v0_t4_forward_Default(I + 24,O + 24);
    sfft_cb_v0_t4_forward_Default(I + 32,O + 32);
    sfft_cb_v0_t4_forward_Default(I + 40,O + 40);
    sfft_cb_v0_t4_forward_Default(I + 48,O + 48);
}
void sfft_cb_t28_inverse(const sfft_cb_tables *tw,f_vector *I,f_vector *O){
    sfft_cb_v0_t4_inverse_Default(I +  0,O +  0);
    sfft_cb_v0_t4_inverse_Default(I +  8,O +  8);
    sfft_cb_v0_t4_inverse_Default(I + 16,O + 16);
    sfft_cb_v0_t4_inverse_Default(I + 24,O + 24);
    sfft_cb_v0_t4_inverse_Default(I + 32,O + 32);
    sfft_cb_v0_t4_inverse_Default(I + 40,O + 40);
    sfft_cb_v0_t4_inverse_Default(I + 48,O + 48);

    f_vector wAr = fv_set1(((double*)tw->r7_1.ptr)[22]);
    f_vector wAi = fv_set1(((double*)tw->r7_1.ptr)[23]);
    f_vector wBr = fv_set1(((double*)tw->r7_1.ptr)[17]);
    f_vector wBi = fv_set1(((double*)tw->r7_1.ptr)[27]);
    f_vector wCr = fv_set1(((double*)tw->r7_1.ptr)[25]);
    f_vector wCi = fv_set1(((double*)tw->r7_1.ptr)[19]);
    const f_vector *w1 = tw->r7_1.table[2];
    const f_vector *w2 = tw->r7_2.table[2];
    const f_vector *w3 = tw->r7_3.table[2];
    const f_vector *w4 = tw->r7_4.table[2];
    const f_vector *w5 = tw->r7_5.table[2];
    const f_vector *w6 = tw->r7_6.table[2];

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
const sfft_block sfft_cb_pb_t28 = {
    28 * 2 >> f_vk, 7, 2,
    sfft_cb_t28_forward,
    sfft_cb_t28_inverse,
    {28 * 2 >> f_vk,2,3}
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Point Block Selection
int sfft_cb_pb_get(sfft_plan *plan,i_ptr L){
    //  Pull out factors of 2.
    int k = 0;
    while ((L & 1) == 0){
        k++;
        L >>= 1;
    }

    plan->pb = NULL;

    switch (L){
        case 1:
            if (k < 4) break;
            if (k == 4){plan->pb = &sfft_cb_pb_t16; break;}
            if (k == 5){plan->pb = &sfft_cb_pb_t32; break;}
            plan->pb = &sfft_cb_pb_t64; break;
        case 3:
            if (k < 2) break;
            if (k == 2){plan->pb = &sfft_cb_pb_t12; break;}
            plan->pb = &sfft_cb_pb_t24; break;
        case 5:
            if (k < 2) break;
            plan->pb = &sfft_cb_pb_t20; break;
        case 7:
            if (k < 2) break;
            plan->pb = &sfft_cb_pb_t28; break;
        default:;
    }

    if (plan->pb == NULL){
        printf("FFT size not supported.");
        plan->k = 0;
        return 1;
    }else{
        plan->k = k - plan->pb->k;
        return 0;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
