/* sfft_cb_mb_mc_bk.h
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
 *      bk          =   Radix 2^k butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_mb_mc_bk_H
#define _sfft_cb_mb_mc_bk_H
#include "sfft_cb_mb_mc_b2.h"
#include "sfft_cb_mb_mc_b4.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_mb_mc_bk_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    if (k == 1){
        sfft_cb_mb_mc_b2_forward(pb,tw,M,S,C,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_mb_mc_b4_forward(pb,tw,M,S,C,i,s,wk,wi);
        return;
    }

    i_ptr c;
    int rk = k >> 1;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    int hk = wk - k;
    int uk = wk - rk;

    //  Row Reduction
    c = 0;
    do{
        sfft_cb_mb_mc_bk_forward(pb,tw,rk,M + c*S,bkL*S,C,i + c*s,bkL*s,wk,wi + ((i_ptr)c << hk));
        c++;
    }while (c < bkL);

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_pb_bk_forward(pb,tw,bk,C,i + c*bkL*s,s,uk,wi);
        c++;
    }while (c < rkL);
}
void sfft_cb_mb_mc_bk_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    if (k == 1){
        sfft_cb_mb_mc_b2_inverse(pb,tw,M,S,C,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_mb_mc_b4_inverse(pb,tw,M,S,C,i,s,wk,wi);
        return;
    }

    i_ptr c;
    int rk = k >> 1;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    int hk = wk - k;
    int uk = wk - rk;

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_pb_bk_inverse(pb,tw,bk,C,i + c*bkL*s,s,uk,wi);
        c++;
    }while (c < rkL);
    
    //  Row Reduction
    c = 0;
    do{
        sfft_cb_mb_mc_bk_inverse(pb,tw,rk,M + c*S,bkL*S,C,i + c*s,bkL*s,wk,wi + ((i_ptr)c << hk));
        c++;
    }while (c < bkL);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
