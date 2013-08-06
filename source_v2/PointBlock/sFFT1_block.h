/* sfft_block.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/01/2011
 * Last Modified    : 06/02/2011
 * 
 */

#pragma once
#ifndef _sfft_block_H
#define _sfft_block_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void    sfft_block_init    (sfft_block *block,int k);
void    sfft_block_forward (const sfft_tables *tw,const sfft_block *block,f_vector *T);
void    sfft_block_inverse (const sfft_tables *tw,const sfft_block *block,f_vector *T);
void    sfft_block_rand    (const sfft_block *block,f_vector *T,i_ptr index);
void    sfft_block_print   (const sfft_block *block,f_vector *T,i_ptr index);
void    sfft_block_psqr    (const sfft_block *block,f_vector *T,i_ptr index);
void    sfft_block_pscale  (const sfft_block *block,f_vector *T,i_ptr index,f_word scale);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Implementations
void sfft_block_init(sfft_block *block,int k){
    i_ptr L = (i_ptr)1 << (k + 1);
    L >>= f_vk;

    block->vsize = L;
    block->k = k;

    sfft_padding_init(&block->pad,L);
}
void sfft_block_init_m(sfft_block *block,int m,int k){
    i_ptr L = (i_ptr)m << (k + 1);
    L >>= f_vk;

    block->vsize = L;
    block->k = k;

    sfft_padding_init(&block->pad,L);
}
void sfft_block_forward(const sfft_tables *tw,const sfft_block *block,f_vector *T){
    sfft_cb_tk_f1_forward(tw,T,block->k);
}
void sfft_block_inverse(const sfft_tables *tw,const sfft_block *block,f_vector *T){
    sfft_cb_tk_f1_inverse(tw,T,block->k);
}
void sfft_block_rand(const sfft_block *block,f_vector *T,i_ptr index){
    i_ptr L = (i_ptr)1 << block->k;

    f_word *t = (f_word*)(T + sfft_padding_get(&block->pad,index));

    f_word *stop = t + 2*L;
    i_ptr i = 2*L * index;
    while (t < stop){
        *t++ = (f_word)(i * i % 71);
        i++;
    }
}
//#ifdef __cplusplus
//void sfft_block_print(const sfft_block *block,f_vector *T,i_ptr index){
//    T += sfft_padding_get(&block->pad,index);
//    sfft_print_farray((f_word*)T,(i_ptr)1 << block->k,1);
//}
//#endif
void sfft_block_psqr(const sfft_block *block,f_vector *T,i_ptr index){
    T += sfft_padding_get(&block->pad,index);

    f_vector *stop = T + block->vsize;
    while (T < stop){
        f_vector r = T[0];
        f_vector i = T[1];
        T[0] = fv_sub(fv_mul(r,r),fv_mul(i,i));
        r = fv_mul(r,i);
        T[1] = fv_add(r,r);
        T += 2;
    }
}
void sfft_block_pscale(const sfft_block *block,f_vector *T,i_ptr index,f_word scale){
    T += sfft_padding_get(&block->pad,index);

    f_vector SCALE;
    fv_ld1_broadcast(SCALE,&scale);

    f_vector *stop = T + block->vsize;
    while (T < stop){
        T[0] = fv_mul(T[0],SCALE);
        T++;
    }
}
f_word sfft_block_frac(const sfft_block *block,f_vector *T,i_ptr index){
    T += sfft_padding_get(&block->pad,index);

    f_word peak = 0;

    f_word *ptr = (f_word*)T;
    f_word *stop = (f_word*)(T + block->vsize);
    while (ptr < stop){
        f_word t = *ptr++;

        t = abs(t);
        t = t - (f_word)(long long)(t + 0.5);

        if (peak < t)
            peak = t;
    }

    return peak;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
