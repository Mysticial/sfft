/* sfft_cb_pb_b4.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/30/2011
 * Last Modified    : 06/02/2011
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      pb          =   Point Block
 *      tk          =   Transform of size 2^k
 */

#pragma once
#ifndef _sfft_cb_pb_b4_H
#define _sfft_cb_pb_b4_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Butterfly - No Twiddle
void sfft_cb_block_b4_forward_0_disabled(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);
    i_ptr i2 = sfft_padding_get(&block->pad,i + s*2);
    i_ptr i3 = sfft_padding_get(&block->pad,i + s*3);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    f_vector *T2 = T + i2;
    f_vector *T3 = T + i3;

    int k = block->k + 2;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;

    sfft_cb_tg_r4_t0_u1(
        sfft_cb_dt_b4w_m16_forward_u0,
        T0,T1,T2,T3,
        k,
        tw,
        0,
        0,ie
    );
}
void sfft_cb_block_b4_inverse_0_disabled(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);
    i_ptr i2 = sfft_padding_get(&block->pad,i + s*2);
    i_ptr i3 = sfft_padding_get(&block->pad,i + s*3);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    f_vector *T2 = T + i2;
    f_vector *T3 = T + i3;

    int k = block->k + 2;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;

    sfft_cb_tg_r4_t0_u1(
        sfft_cb_dt_b4w_m16_inverse_u0,
        T0,T1,T2,T3,
        k,
        tw,
        0,
        0,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Butterfly - Twiddled
void sfft_cb_block_b4_forward_w(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);
    i_ptr i2 = sfft_padding_get(&block->pad,i + s*2);
    i_ptr i3 = sfft_padding_get(&block->pad,i + s*3);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    f_vector *T2 = T + i2;
    f_vector *T3 = T + i3;
    
    wk += block->k;
    wi *= block->vsize;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;

#if sFFT_REGISTERS >= 32
    sfft_cb_tg_r4p(
        sfft_cb_dt_b4w_m32_forward_u2,
        T0,T1,T2,T3,
        wk,wi,
        tw,
        2,
        0,ie
    );
    //sfft_cb_tg_r4p(
    //    sfft_cb_dt_b4w_m32_forward_u1,
    //    T0,T1,T2,T3,
    //    wk,wi,
    //    tw,
    //    1,
    //    0,ie
    //);
    //sfft_cb_tg_r4p(
    //    sfft_cb_dt_b4w_m8_forward_u0,
    //    T0,T1,T2,T3,
    //    wk,wi,
    //    tw,
    //    0,
    //    0,ie
    //);
#else
    sfft_cb_tg_r4p(
        sfft_cb_dt_b4w_m16_forward_u0,
//        sfft_cb_dt_b4w_m8_forward_u0,
        T0,T1,T2,T3,
        wk,wi,
        tw,
        0,
        0,ie
    );
#endif
}
void sfft_cb_block_b4_inverse_w(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);
    i_ptr i2 = sfft_padding_get(&block->pad,i + s*2);
    i_ptr i3 = sfft_padding_get(&block->pad,i + s*3);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    f_vector *T2 = T + i2;
    f_vector *T3 = T + i3;
    
    wk += block->k;
    wi *= block->vsize;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;
    
#if sFFT_REGISTERS >= 32
    sfft_cb_tg_r4p(
        sfft_cb_dt_b4w_m32_inverse_u1,
        T0,T1,T2,T3,
        wk,wi,
        tw,
        1,
        0,ie
    );
#else
    sfft_cb_tg_r4p(
        sfft_cb_dt_b4w_m16_inverse_u0,
        T0,T1,T2,T3,
        wk,wi,
        tw,
        0,
        0,ie
    );
#endif
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Run-Through Transform
void sfft_cb_block_t4_forward(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);
    i_ptr i2 = sfft_padding_get(&block->pad,i + s*2);
    i_ptr i3 = sfft_padding_get(&block->pad,i + s*3);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    f_vector *T2 = T + i2;
    f_vector *T3 = T + i3;

    int k = block->k + 2;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;
    
#if sFFT_REGISTERS >= 32
    sfft_cb_tg_r4(
        sfft_cb_dt_b4w_m32_forward_u1,
        T0,T1,T2,T3,
        k,
        tw,
        1,
        0,ie
    );
#else
    sfft_cb_tg_r4(
        sfft_cb_dt_b4w_m16_forward_u0,
        T0,T1,T2,T3,
        k,
        tw,
        0,
        0,ie
    );
#endif

    sfft_block_forward(tw,block,T0);
    sfft_block_forward(tw,block,T1);
    sfft_block_forward(tw,block,T2);
    sfft_block_forward(tw,block,T3);
}
void sfft_cb_block_t4_inverse(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);
    i_ptr i2 = sfft_padding_get(&block->pad,i + s*2);
    i_ptr i3 = sfft_padding_get(&block->pad,i + s*3);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    f_vector *T2 = T + i2;
    f_vector *T3 = T + i3;
    
    sfft_block_inverse(tw,block,T0);
    sfft_block_inverse(tw,block,T1);
    sfft_block_inverse(tw,block,T2);
    sfft_block_inverse(tw,block,T3);

    int k = block->k + 2;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;
    
#if sFFT_REGISTERS >= 32
    sfft_cb_tg_r4(
        sfft_cb_dt_b4w_m32_inverse_u1,
        T0,T1,T2,T3,
        k,
        tw,
        1,
        0,ie
    );
#else
    sfft_cb_tg_r4(
        sfft_cb_dt_b4w_m16_inverse_u0,
        T0,T1,T2,T3,
        k,
        tw,
        0,
        0,ie
    );
#endif
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
