/* sfft_cb_mb_cm_bk.h
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
 *      bk          =   Radix 2^k butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_mb_cm_bk_H
#define _sfft_cb_mb_cm_bk_H
//#include "sfft_cb_mb_cm_b2.h"
#include "sfft_cb_mb_cm_b4.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_mb_cm_bk_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    if (k == 1){
//        sfft_cb_mb_cm_b2_forward(pb,tw,M,S,C,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_mb_cm_b4_forward(pb,tw,M,S,C,i,s,wk,wi);
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
        sfft_cb_pb_bk_forward(pb,tw,rk,C,i + c*s,bkL*s,wk,wi + ((i_ptr)c << hk));
        c++;
    }while (c < bkL);

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_mb_cm_bk_forward(pb,tw,bk,M + c*bkL*S,S,C,i + c*bkL*s,s,uk,wi);
        c++;
    }while (c < rkL);
}
void sfft_cb_mb_cm_bk_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,i_ptr S,
    f_vector *C,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    if (k == 1){
//        sfft_cb_mb_cm_b2_inverse(pb,tw,M,S,C,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_mb_cm_b4_inverse(pb,tw,M,S,C,i,s,wk,wi);
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
        sfft_cb_mb_cm_bk_inverse(pb,tw,bk,M + c*bkL*S,S,C,i + c*bkL*s,s,uk,wi);
        c++;
    }while (c < rkL);

    //  Row Reduction
    c = 0;
    do{
        sfft_cb_pb_bk_inverse(pb,tw,rk,C,i + c*s,bkL*s,wk,wi + ((i_ptr)c << hk));
        c++;
    }while (c < bkL);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  End-Point Transform
void sfft_cb_mb_cm_tk_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,
    f_vector *C,i_ptr i
){
    if (k == 1){
//        sfft_cb_mb_cm_t2_forward(pb,tw,M,C,i);
        return;
    }
    if (k == 2){
        sfft_cb_mb_cm_t4_forward(pb,tw,M,C,i);
        return;
    }

    i_ptr c;
    int rk = k >> 1;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    i_ptr vsize = pb->vsize;

    //  Row Reduction
    c = 0;
    do{
        sfft_cb_pb_bk_forward(pb,tw,rk,C,i + c,bkL,k,c);
        c++;
    }while (c < bkL);

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_mb_cm_tk_forward(pb,tw,bk,M + c*bkL*vsize,C,i + c*bkL);
        c++;
    }while (c < rkL);
}
void sfft_cb_mb_cm_tk_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,
    f_vector *C,i_ptr i
){
    if (k == 1){
//        sfft_cb_mb_cm_t2_inverse(pb,tw,M,C,i);
        return;
    }
    if (k == 2){
        sfft_cb_mb_cm_t4_inverse(pb,tw,M,C,i);
        return;
    }

    i_ptr c;
    int rk = k >> 1;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    i_ptr vsize = pb->vsize;

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_mb_cm_tk_inverse(pb,tw,bk,M + c*bkL*vsize,C,i + c*bkL);
        c++;
    }while (c < rkL);

    //  Row Reduction
    c = 0;
    do{
        sfft_cb_pb_bk_inverse(pb,tw,rk,C,i + c,bkL,k,c);
        c++;
    }while (c < bkL);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
