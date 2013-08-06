/* sfft_block_internals.h - Blocked + Padded FFT
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/01/2011
 * Last Modified    : 08/15/2012
 * 
 */

#pragma once
#ifndef _sfft_block_internals_H
#define _sfft_block_internals_H
#include "sfft_block_headers.h"
#include "../PointBlock_Cache/sfft_cb_pb_bk.h"
#include "../Tools/sfft_bitreverse.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Point Block Methods
static void sfft_cb_pb_rand_internal(const sfft_block *pb,f_vector *T,i_ptr index){
    //  Generate Random Data on the index'th point-block.

    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    f_word *t = (f_word*)(T + sfft_padding_get(&pb->pad,index));

    f_word *stop = t + 2*L;
    i_ptr i = 2*L * index;
    while (t < stop){
        *t++ = (f_word)(i * i % 71);
        i++;
    }
}
static void sfft_cb_pb_print_internal(const sfft_block *pb,const f_vector *T,i_ptr index){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    T += sfft_padding_get(&pb->pad,index);
    sfft_print_farray((const f_word*)T,L,1);
}
static void sfft_cb_pb_sqr_internal(const sfft_block *pb,f_vector *T,i_ptr index){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    T += sfft_padding_get(&pb->pad,index);

    f_vector *stop = T + pb->vsize;
    while (T < stop){
        f_vector r = T[0];
        f_vector i = T[1];

        T[0] = fv_sub(fv_mul(r,r),fv_mul(i,i));
        i = fv_mul(r,i);
        T[1] = fv_add(i,i);

        T += 2;
    }
}
static void sfft_cb_pb_scale_internal(const sfft_block *pb,f_vector *T,i_ptr index,f_vector scale){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    T += sfft_padding_get(&pb->pad,index);

    f_vector *stop = T + pb->vsize;
    while (T < stop){
        T[0] = fv_mul(T[0],scale);
        T++;
    }
}
static f_word sfft_cb_pb_residual_internal(const sfft_block *pb,const f_vector *T,i_ptr index){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    const f_word *t = (const f_word*)(T + sfft_padding_get(&pb->pad,index));

    f_word residual = 0;

    const f_word *stop = t + 2*L;
    while (t < stop){
        f_word r = t[0];
        if (r < 0)
            r = -r;

        long long i = (long long)(r + 0.5);
        r -= (f_word)i;
        if (r < 0)
            r = -r;

        if (residual < r)
            residual = r;

        t++;
    }

    return residual;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
i_ptr sfft_cb_pb_size(const sfft_block *pb,int k){
    //  For a transform length of 2^k point-blocks:
    //      -   Return the size (in bytes) of the dataset.

    return sfft_padding_get(&pb->pad,(i_ptr)1 << k) * sizeof(f_vector);
}
void sfft_cb_pb_rand(const sfft_block *pb,f_vector *T,i_ptr L){
    //  For a transform length of 2^k point-blocks:
    //      -   Randomize the entire dataset

    for (i_ptr i = 0; i < L; i++){
        sfft_cb_pb_rand_internal(pb,T,i);
    }
}
void sfft_cb_pb_print(const sfft_block *pb,const f_vector *T,i_ptr L){
    //  For a transform length of 2^k point-blocks:
    //      -   Print the entire dataset

    for (i_ptr i = 0; i < L; i++){
        sfft_cb_pb_print_internal(pb,T,i);
    }
}
void sfft_cb_pb_sqr(const sfft_block *pb,f_vector *T,i_ptr L){
    //  For a transform length of 2^k point-blocks:
    //      -   Pointwise square the entire dataset. (for testing purposes via convolution)

    for (i_ptr i = 0; i < L; i++){
        sfft_cb_pb_sqr_internal(pb,T,i);
    }
}
void sfft_cb_pb_scale(const sfft_block *pb,f_vector *T,i_ptr L,f_word scale){
    //  For a transform length of 2^k point-blocks:
    //      -   Multiply the entire dataset by "scale"

    f_vector SCALE = fv_set1(scale);
    for (i_ptr i = 0; i < L; i++){
        sfft_cb_pb_scale_internal(pb,T,i,SCALE);
    }
}
f_word sfft_cb_pb_residual(const sfft_block *pb,f_vector *T,i_ptr L){
    //  For a transform length of 2^k point-blocks:
    //      -   Find the largest distance from 1. (for testing purposes via convolution)

    f_word residual = 0;
    for (i_ptr i = 0; i < L; i++){
        f_word r = sfft_cb_pb_residual_internal(pb,T,i);
        if (residual < r)
            residual = r;
    }

    return residual;
}
void sfft_cb_pb_forward_1(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T){
    pb->fp_forward(tw,T,T);
}
void sfft_cb_pb_inverse_1(const sfft_block *pb,const sfft_cb_tables *tw,f_vector *T){
    pb->fp_inverse(tw,T,T);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  FFTs
void sfft_cb_pb_forward(const sfft_block *pb,const sfft_cb_tables *tw,int k,f_vector *T){
    sfft_cb_pb_tk_forward(pb,tw,k,T,0);
}
void sfft_cb_pb_inverse(const sfft_block *pb,const sfft_cb_tables *tw,int k,f_vector *T){
    sfft_cb_pb_tk_inverse(pb,tw,k,T,0);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
