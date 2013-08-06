/* sfft_cb_mb_mc_b4.h
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
 *      b4          =   Radix 4 butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_mb_mc_b4_H
#define _sfft_cb_mb_mc_b4_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_mb_mc_b4_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1*s);
    f_vector *C2 = C + sfft_padding_get(&pb->pad,i + 2*s);
    f_vector *C3 = C + sfft_padding_get(&pb->pad,i + 3*s);

    f_vector *M0 = M + 0*S;
    f_vector *M1 = M + 1*S;
    f_vector *M2 = M + 2*S;
    f_vector *M3 = M + 3*S;

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
        M0,M1,M2,M3,
        C0,C1,C2,C3,
        w2,w1,w3,
        is,ie
    );
}
void sfft_cb_mb_mc_b4_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0*s);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1*s);
    f_vector *C2 = C + sfft_padding_get(&pb->pad,i + 2*s);
    f_vector *C3 = C + sfft_padding_get(&pb->pad,i + 3*s);

    f_vector *M0 = M + 0*S;
    f_vector *M1 = M + 1*S;
    f_vector *M2 = M + 2*S;
    f_vector *M3 = M + 3*S;

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
        C0,C1,C2,C3,
        M0,M1,M2,M3,
        w2,w1,w3,
        is,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
