/* sfft_cb_mb_cm_b2.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/23/2012
 * Last Modified    : 04/23/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      mb          =   Memory Block
 *      cm          =   Cache -> Memory
 *      b2          =   Radix 2 butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_mb_cm_b2_H
#define _sfft_cb_mb_cm_b2_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  End-Point Transform
void sfft_cb_mb_cm_t2_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,
    f_vector *C,i_ptr i
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1);

    //  Row Reduction
    int k = pb->k + 1;
    const f_vector *w1 = tw->w1[pb->m]->table[k];
    i_ptr is = 0;
    i_ptr ie = pb->vsize * (sizeof(f_vector) >> 1);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_forward_0_u0,
        C0,C1,
        C0,C1,
        w1,
        is,ie
    );
    C0 = (f_vector*)((char*)C0 + ie);
    C1 = (f_vector*)((char*)C1 + ie);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_forward_1_u0,
        C0,C1,
        C0,C1,
        w1,
        is,ie
    );
    C0 = (f_vector*)((char*)C0 - ie);
    C1 = (f_vector*)((char*)C1 - ie);

    //  Sub-Transforms
    pb->fp_forward(tw,C0);
    pb->fp_forward(tw,C1);

    //  Copy to Memory
    i_ptr vsize = pb->vsize;
    memcpy(M + 0*vsize,C0,vsize * sizeof(f_vector));
    memcpy(M + 1*vsize,C1,vsize * sizeof(f_vector));
}
void sfft_cb_mb_cm_t2_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,
    f_vector *C,i_ptr i
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1);

    //  Copy from Memory
    i_ptr vsize = pb->vsize;
    memcpy(C0,M + 0*vsize,vsize * sizeof(f_vector));
    memcpy(C1,M + 1*vsize,vsize * sizeof(f_vector));

    //  Sub-Transforms
    pb->fp_inverse(tw,C0);
    pb->fp_inverse(tw,C1);

    //  Row Reduction
    int k = pb->k + 1;
    const f_vector *w1 = tw->w1[pb->m]->table[k];
    i_ptr is = 0;
    i_ptr ie = pb->vsize * (sizeof(f_vector) >> 1);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_inverse_0_u0,
        C0,C1,
        C0,C1,
        w1,
        is,ie
    );
    C0 = (f_vector*)((char*)C0 + ie);
    C1 = (f_vector*)((char*)C1 + ie);
    sfft_cb_tg_r2_t0_u0(
        sfft_cb_dt_b2w_m16_inverse_1_u0,
        C0,C1,
        C0,C1,
        w1,
        is,ie
    );
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_mb_cm_b2_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1);

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
            C0,C1,
            C0,C1,
            w1,
            is,ie
        );
    }else{
        w1 -= width;
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_forward_1_u0,
            C0,C1,
            C0,C1,
            w1,
            is,ie
        );
    }

    //  Copy to Memory
    i_ptr vsize = pb->vsize;
    memcpy(M + 0*S,C0,vsize * sizeof(f_vector));
    memcpy(M + 1*S,C1,vsize * sizeof(f_vector));
}
void sfft_cb_mb_cm_b2_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    f_vector *C0 = C + sfft_padding_get(&pb->pad,i + 0);
    f_vector *C1 = C + sfft_padding_get(&pb->pad,i + 1);

    //  Copy from Memory
    i_ptr vsize = pb->vsize;
    memcpy(C0,M + 0*S,vsize * sizeof(f_vector));
    memcpy(C1,M + 1*S,vsize * sizeof(f_vector));

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
            C0,C1,
            w1,
            is,ie
        );
    }else{
        w1 -= width;
        sfft_cb_tg_r2_t0_u0(
            sfft_cb_dt_b2w_m16_inverse_1_u0,
            C0,C1,
            C0,C1,
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
