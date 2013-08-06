/* sfft_cb_mb_mc_b2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/23/2012
 * Last Modified    : 04/23/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      mb          =   Memory Block
 *      mc          =   Memory -> Cache
 *      b2          =   Radix 2 butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_mb_mc_b2_H
#define _sfft_cb_mb_mc_b2_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_mb_mc_b2_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1*s);

    f_vector *M0 = M + 0*S;
    f_vector *M1 = M + 1*S;

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
            M0,M1,
            C0,C1,
            w1,
            is,ie
        );
    }else{
        w1 -= width;
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_forward_1_u0,
            M0,M1,
            C0,C1,
            w1,
            is,ie
        );
    }
}
void sfft_cb_mb_mc_b2_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1*s);

    f_vector *M0 = M + 0*S;
    f_vector *M1 = M + 1*S;

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
            C0,C1,
            M0,M1,
            w1,
            is,ie
        );
    }else{
        w1 -= width;
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_inverse_1_u0,
            C0,C1,
            M0,M1,
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
