/* sfft_cb_pb_b2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/16/2012
 * Last Modified    : 04/16/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      pb          =   Point Block
 *      b2          =   Radix 2 butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_pb_b2_H
#define _sfft_cb_pb_b2_H
#include "../vk_Generic/sfft_cb_tg_r2.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  End-Point Transform
void sfft_cb_pb_t2_forward(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1);

    //  Row Reduction
    int k = pb->k + 1;
    const f_vector *w1 = tw->w1[pb->m]->table[k];
    i_ptr is = 0;
    i_ptr ie = pb->vsize * (sizeof(f_vector) >> 1);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_forward_0_u0,
        T0,T1,
        T0,T1,
        w1,
        is,ie
    );
    T0 = (f_vector*)((char*)T0 + ie);
    T1 = (f_vector*)((char*)T1 + ie);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_forward_1_u0,
        T0,T1,
        T0,T1,
        w1,
        is,ie
    );
    T0 = (f_vector*)((char*)T0 - ie);
    T1 = (f_vector*)((char*)T1 - ie);

    //  Sub-Transforms
    pb->fp_forward(tw,T0,T0);
    pb->fp_forward(tw,T1,T1);
}
void sfft_cb_pb_t2_inverse(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1);

    //  Sub-Transforms
    pb->fp_inverse(tw,T0,T0);
    pb->fp_inverse(tw,T1,T1);

    //  Row Reduction
    int k = pb->k + 1;
    const f_vector *w1 = tw->w1[pb->m]->table[k];
    i_ptr is = 0;
    i_ptr ie = pb->vsize * (sizeof(f_vector) >> 1);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_inverse_0_u0,
        T0,T1,
        T0,T1,
        w1,
        is,ie
    );
    T0 = (f_vector*)((char*)T0 + ie);
    T1 = (f_vector*)((char*)T1 + ie);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_inverse_1_u0,
        T0,T1,
        T0,T1,
        w1,
        is,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_pb_b2_forward(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1*s);

    //  Row Reduction
    wi *= pb->vsize;
    int k = pb->k + wk;
    const f_vector *w1 = tw->w1[pb->m]->table[k] + wi;
    i_ptr is = 0;
    i_ptr ie = pb->vsize * sizeof(f_vector);

    i_ptr width = (i_ptr)pb->vsize << (wk - 2);
    if (wi < width){
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_forward_0_u0,
            T0,T1,
            T0,T1,
            w1,
            is,ie
        );
    }else{
        w1 -= width;
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_forward_1_u0,
            T0,T1,
            T0,T1,
            w1,
            is,ie
        );
    }
}
void sfft_cb_pb_b2_inverse(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1*s);

    //  Row Reduction
    wi *= pb->vsize;
    int k = pb->k + wk;
    const f_vector *w1 = tw->w1[pb->m]->table[k] + wi;
    i_ptr is = 0;
    i_ptr ie = pb->vsize * sizeof(f_vector);

    i_ptr width = (i_ptr)pb->vsize << (wk - 2);
    if (wi < width){
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_inverse_0_u0,
            T0,T1,
            T0,T1,
            w1,
            is,ie
        );
    }else{
        w1 -= width;
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_inverse_1_u0,
            T0,T1,
            T0,T1,
            w1,
            is,ie
        );
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
