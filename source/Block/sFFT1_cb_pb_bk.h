/* sfft_cb_pb_bk.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 06/03/2011
 * Last Modified    : 06/03/2011
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      pb          =   Point Block
 *      tk          =   Transform of size 2^k
 */

#pragma once
#ifndef _sfft_cb_pb_bk_H
#define _sfft_cb_pb_bk_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include "sfft_cb_pb_b2.h"
#include "sfft_cb_pb_b4.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  rk Selection
inline i_ptr sfft_cb_block_bk_select_rk_getmem(const sfft_block *block,int rk){
    return block->vsize * sizeof(f_vector) << rk;
}
int sfft_cb_block_bk_select_rk(const sfft_block *block,int k){
    const i_ptr CACHE_SIZE = 524288 * 1;

    int max_rk = (k + 0) >> 1;
    int rk = max_rk;
    while (rk > 1 && sfft_cb_block_bk_select_rk_getmem(block,rk) > CACHE_SIZE)
        rk--;

    return rk;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Butterfly - No Twiddle
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Butterfly - Twiddled
void sfft_cb_block_bk_forward_w(const sfft_tables *tw,const sfft_block *block,f_vector *T,int k,i_ptr i,i_ptr s,int wk,i_ptr wi){
    if (k == 1){
        sfft_cb_block_b2_forward_w(tw,block,T,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_block_b4_forward_w(tw,block,T,i,s,wk,wi);
        return;
    }

    int rk = sfft_cb_block_bk_select_rk(block,k);
    int sk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr skL = (i_ptr)1 << sk;
    i_ptr kL = (i_ptr)1 << k;
    int hk = wk - k;
    int uk = wk - rk;

    //  Row-Reduction
    i_ptr c = 0;
    do{
        sfft_cb_block_bk_forward_w(tw,block,T,rk,i + c*s,skL*s,wk,wi + (c << hk));
        c++;
    }while (c < skL);

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_block_bk_forward_w(tw,block,T,sk,i + c*s,s,uk,wi);
        c += skL;
    }while (c < kL);
}
void sfft_cb_block_bk_inverse_w(const sfft_tables *tw,const sfft_block *block,f_vector *T,int k,i_ptr i,i_ptr s,int wk,i_ptr wi){
    if (k == 1){
        sfft_cb_block_b2_inverse_w(tw,block,T,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_block_b4_inverse_w(tw,block,T,i,s,wk,wi);
        return;
    }

    int rk = sfft_cb_block_bk_select_rk(block,k);
    int sk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr skL = (i_ptr)1 << sk;
    i_ptr kL = (i_ptr)1 << k;
    int hk = wk - k;
    int uk = wk - rk;

    //  Sub-Transforms
    i_ptr c = 0;
    do{
        sfft_cb_block_bk_inverse_w(tw,block,T,sk,i + c*s,s,uk,wi);
        c += skL;
    }while (c < kL);

    //  Row-Reduction
    c = 0;
    do{
        sfft_cb_block_bk_inverse_w(tw,block,T,rk,i + c*s,skL*s,wk,wi + (c << hk));
        c++;
    }while (c < skL);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Run-Through Transform
void sfft_cb_block_tk_forward(const sfft_tables *tw,const sfft_block *block,f_vector *T,int k,i_ptr i,i_ptr s){
    if (k == 0){
        i_ptr i0 = sfft_padding_get(&block->pad,i);
        f_vector *T0 = T + i0;
        sfft_block_forward(tw,block,T0);
        return;
    }
    if (k == 1){
        sfft_cb_block_t2_forward(tw,block,T,i,s);
        return;
    }
    if (k == 2){
        sfft_cb_block_t4_forward(tw,block,T,i,s);
        return;
    }

    int rk = sfft_cb_block_bk_select_rk(block,k);
    int sk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr skL = (i_ptr)1 << sk;
    i_ptr kL = (i_ptr)1 << k;

    //  Row-Reduction
    i_ptr c = 0;
    do{
        sfft_cb_block_bk_forward_w(tw,block,T,rk,i + c*s,skL*s,k,c);
        c++;
    }while (c < skL);

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_block_tk_forward(tw,block,T,sk,i + c*s,s);
        c += skL;
    }while (c < kL);
}
void sfft_cb_block_tk_inverse(const sfft_tables *tw,const sfft_block *block,f_vector *T,int k,i_ptr i,i_ptr s){
    if (k == 0){
        i_ptr i0 = sfft_padding_get(&block->pad,i);
        f_vector *T0 = T + i0;
        sfft_block_inverse(tw,block,T0);
        return;
    }
    if (k == 1){
        sfft_cb_block_t2_inverse(tw,block,T,i,s);
        return;
    }
    if (k == 2){
        sfft_cb_block_t4_inverse(tw,block,T,i,s);
        return;
    }

    int rk = sfft_cb_block_bk_select_rk(block,k);
    int sk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr skL = (i_ptr)1 << sk;
    i_ptr kL = (i_ptr)1 << k;

    //  Sub-Transforms
    i_ptr c = 0;
    do{
        sfft_cb_block_tk_inverse(tw,block,T,sk,i + c*s,s);
        c += skL;
    }while (c < kL);

    //  Row-Reduction
    c = 0;
    do{
        sfft_cb_block_bk_inverse_w(tw,block,T,rk,i + c*s,skL*s,k,c);
        c++;
    }while (c < skL);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
