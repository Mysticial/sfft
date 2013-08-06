/* sfft_cb_pb_b4.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/16/2012
 * Last Modified    : 04/16/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      pb          =   Point Block
 *      b4          =   Radix 4 butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_pb_b4_H
#define _sfft_cb_pb_b4_H
#include "../vk_Generic/sfft_cb_tg_r4.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  End-Point Transform
void sfft_cb_pb_t4_forward(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1);
    f_vector *T2 = T + sfft_padding_get(&pb->pad,i + 2);
    f_vector *T3 = T + sfft_padding_get(&pb->pad,i + 3);

    //  Row Reduction
    int k = pb->k + 2;
    const f_vector *w1 = tw->w1[pb->m]->table[k];
    const f_vector *w2 = tw->w2[pb->m]->table[k];
    const f_vector *w3 = tw->w3[pb->m]->table[k];
    i_ptr is = 0;
    i_ptr ie = pb->vsize * sizeof(f_vector);
    sfft_cb_tg_r4i_t0_u0(
        sfft_cb_dt_b4w_m16_forward_u0,
        T0,T1,T2,T3,
        w2,w1,w3,
        is,ie
    );

    //  Sub-Transforms
    pb->fp_forward(tw,T0,T0);
    pb->fp_forward(tw,T1,T1);
    pb->fp_forward(tw,T2,T2);
    pb->fp_forward(tw,T3,T3);
}
void sfft_cb_pb_t4_inverse(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1);
    f_vector *T2 = T + sfft_padding_get(&pb->pad,i + 2);
    f_vector *T3 = T + sfft_padding_get(&pb->pad,i + 3);

    //  Sub-Transforms
    pb->fp_inverse(tw,T0,T0);
    pb->fp_inverse(tw,T1,T1);
    pb->fp_inverse(tw,T2,T2);
    pb->fp_inverse(tw,T3,T3);

    //  Row Reduction
    int k = pb->k + 2;
    const f_vector *w1 = tw->w1[pb->m]->table[k];
    const f_vector *w2 = tw->w2[pb->m]->table[k];
    const f_vector *w3 = tw->w3[pb->m]->table[k];
    i_ptr is = 0;
    i_ptr ie = pb->vsize * sizeof(f_vector);
    sfft_cb_tg_r4_t0_u0(
        sfft_cb_dt_b4w_m16_inverse_u0,
        T0,T1,T2,T3,
        T0,T1,T2,T3,
        w2,w1,w3,
        is,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_pb_b4_forward(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1*s);
    f_vector *T2 = T + sfft_padding_get(&pb->pad,i + 2*s);
    f_vector *T3 = T + sfft_padding_get(&pb->pad,i + 3*s);

    //  Row Reduction
    wi *= pb->vsize;
    int k = pb->k + wk;
    const f_vector *w1 = tw->w1[pb->m]->table[k] + wi;
    const f_vector *w2 = tw->w2[pb->m]->table[k] + wi;
    const f_vector *w3 = tw->w3[pb->m]->table[k] + wi;
    i_ptr is = 0;
    i_ptr ie = pb->vsize * sizeof(f_vector);
    sfft_cb_tg_r4_t0_u0(
        sfft_cb_dt_b4w_m16_forward_u0,
        T0,T1,T2,T3,
        T0,T1,T2,T3,
        w2,w1,w3,
        is,ie
    );
}
void sfft_cb_pb_b4_inverse(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T,i_ptr i,i_ptr s,int wk,i_ptr wi){
    f_vector *T0 = T + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *T1 = T + sfft_padding_get(&pb->pad,i + 1*s);
    f_vector *T2 = T + sfft_padding_get(&pb->pad,i + 2*s);
    f_vector *T3 = T + sfft_padding_get(&pb->pad,i + 3*s);

    //  Row Reduction
    wi *= pb->vsize;
    int k = pb->k + wk;
    const f_vector *w1 = tw->w1[pb->m]->table[k] + wi;
    const f_vector *w2 = tw->w2[pb->m]->table[k] + wi;
    const f_vector *w3 = tw->w3[pb->m]->table[k] + wi;
    i_ptr is = 0;
    i_ptr ie = pb->vsize * sizeof(f_vector);
    sfft_cb_tg_r4_t0_u0(
        sfft_cb_dt_b4w_m16_inverse_u0,
        T0,T1,T2,T3,
        T0,T1,T2,T3,
        w2,w1,w3,
        is,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
