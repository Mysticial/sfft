/* sfft_cb_pb_b2.h
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
#ifndef _sfft_cb_pb_b2_H
#define _sfft_cb_pb_b2_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Butterfly - No Twiddle
void sfft_cb_block_b2_forward_0(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;

    int k = block->k + 1;
    i_ptr ie = 1 * (i_ptr)sizeof(f_word) << block->k;

    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_forward_0_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
    T0 = (f_vector*)((char*)T0 + ie);
    T1 = (f_vector*)((char*)T1 + ie);
    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_forward_1_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
}
void sfft_cb_block_b2_inverse_0(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;

    int k = block->k + 1;
    i_ptr ie = 1 * (i_ptr)sizeof(f_word) << block->k;

    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_inverse_0_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
    T0 = (f_vector*)((char*)T0 + ie);
    T1 = (f_vector*)((char*)T1 + ie);
    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_inverse_1_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Butterfly - Twiddled
void sfft_cb_block_b2_forward_w(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    
    wk += block->k;
    wi *= block->vsize;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;

    i_ptr boundary = 1 * (i_ptr)sizeof(f_word) << wk;
    boundary /= sizeof(f_vector) * 2;
    if (wi < boundary){
        sfft_cb_tg_r2p_t0_u1(
            sfft_cb_dt_b2w_m16_forward_0_u1,
            T0,T1,
            wk,wi,
            tw,
            0,ie
        );
    }else{
        wi -= boundary;
        sfft_cb_tg_r2p_t0_u1(
            sfft_cb_dt_b2w_m16_forward_1_u1,
            T0,T1,
            wk,wi,
            tw,
            0,ie
        );
    }
}
void sfft_cb_block_b2_inverse_w(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;
    
    wk += block->k;
    wi *= block->vsize;
    i_ptr ie = 2 * (i_ptr)sizeof(f_word) << block->k;

    i_ptr boundary = 1 * (i_ptr)sizeof(f_word) << wk;
    boundary /= sizeof(f_vector) * 2;
    if (wi < boundary){
        sfft_cb_tg_r2p_t0_u1(
            sfft_cb_dt_b2w_m16_inverse_0_u1,
            T0,T1,
            wk,wi,
            tw,
            0,ie
        );
    }else{
        wi -= boundary;
        sfft_cb_tg_r2p_t0_u1(
            sfft_cb_dt_b2w_m16_inverse_1_u1,
            T0,T1,
            wk,wi,
            tw,
            0,ie
        );
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Run-Through Transform
void sfft_cb_block_t2_forward(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;

    int k = block->k + 1;
    i_ptr ie = 1 * (i_ptr)sizeof(f_word) << block->k;

    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_forward_0_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
    T0 = (f_vector*)((char*)T0 + ie);
    T1 = (f_vector*)((char*)T1 + ie);
    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_forward_1_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
    T0 = (f_vector*)((char*)T0 - ie);
    T1 = (f_vector*)((char*)T1 - ie);

    sfft_block_forward(tw,block,T0);
    sfft_block_forward(tw,block,T1);
}
void sfft_cb_block_t2_inverse(const sfft_tables *tw,const sfft_block *block,f_vector *T,i_ptr i,i_ptr s){
    //  Get Offsets
    i_ptr i0 = sfft_padding_get(&block->pad,i + s*0);
    i_ptr i1 = sfft_padding_get(&block->pad,i + s*1);

    f_vector *T0 = T + i0;
    f_vector *T1 = T + i1;

    int k = block->k + 1;
    i_ptr ie = 1 * (i_ptr)sizeof(f_word) << block->k;

    sfft_block_inverse(tw,block,T0);
    sfft_block_inverse(tw,block,T1);

    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_inverse_0_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
    T0 = (f_vector*)((char*)T0 + ie);
    T1 = (f_vector*)((char*)T1 + ie);
    sfft_cb_tg_r2_t0_u1(
        sfft_cb_dt_b2w_m16_inverse_1_u1,
        T0,T1,
        k,
        tw,
        0,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
