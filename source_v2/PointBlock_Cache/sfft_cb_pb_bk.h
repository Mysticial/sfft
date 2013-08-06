/* sfft_cb_pb_bk.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/21/2012
 * Last Modified    : 04/21/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      pb          =   Point Block
 *      bk          =   Radix k butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_pb_bk_H
#define _sfft_cb_pb_bk_H
#include "sfft_cb_pb_b2.h"
#include "sfft_cb_pb_b4.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_pb_bk_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *T,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    if (k == 1){
        sfft_cb_pb_b2_forward(pb,tw,T,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_pb_b4_forward(pb,tw,T,i,s,wk,wi);
        return;
    }
    //if (k == 3){
    //    int hk = wk - k;
    //    int uk = wk - 1;
    //    sfft_cb_pb_b2_forward(pb,tw,T,i + 0*s,4*s,wk,wi + ((i_ptr)0 << hk));
    //    sfft_cb_pb_b2_forward(pb,tw,T,i + 1*s,4*s,wk,wi + ((i_ptr)1 << hk));
    //    sfft_cb_pb_b2_forward(pb,tw,T,i + 2*s,4*s,wk,wi + ((i_ptr)2 << hk));
    //    sfft_cb_pb_b2_forward(pb,tw,T,i + 3*s,4*s,wk,wi + ((i_ptr)3 << hk));
    //    sfft_cb_pb_b4_forward(pb,tw,T,i + 0*s,s,uk,wi);
    //    sfft_cb_pb_b4_forward(pb,tw,T,i + 4*s,s,uk,wi);
    //    return;
    //}
    //if (k == 4){
    //    int hk = wk - k;
    //    int uk = wk - 2;
    //    sfft_cb_pb_b4_forward(pb,tw,T,i + 0*s,4*s,wk,wi + ((i_ptr)0 << hk));
    //    sfft_cb_pb_b4_forward(pb,tw,T,i + 1*s,4*s,wk,wi + ((i_ptr)1 << hk));
    //    sfft_cb_pb_b4_forward(pb,tw,T,i + 2*s,4*s,wk,wi + ((i_ptr)2 << hk));
    //    sfft_cb_pb_b4_forward(pb,tw,T,i + 3*s,4*s,wk,wi + ((i_ptr)3 << hk));
    //    sfft_cb_pb_b4_forward(pb,tw,T,i +  0*s,s,uk,wi);
    //    sfft_cb_pb_b4_forward(pb,tw,T,i +  4*s,s,uk,wi);
    //    sfft_cb_pb_b4_forward(pb,tw,T,i +  8*s,s,uk,wi);
    //    sfft_cb_pb_b4_forward(pb,tw,T,i + 12*s,s,uk,wi);
    //    return;
    //}
    
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
        sfft_cb_pb_bk_forward(pb,tw,rk,T,i + c*s,bkL*s,wk,wi + ((i_ptr)c << hk));
        c++;
    }while (c < bkL);

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_pb_bk_forward(pb,tw,bk,T,i + c*bkL*s,s,uk,wi);
        c++;
    }while (c < rkL);
}
void sfft_cb_pb_bk_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *T,i_ptr i,i_ptr s,
    int wk,i_ptr wi
){
    if (k == 1){
        sfft_cb_pb_b2_inverse(pb,tw,T,i,s,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_pb_b4_inverse(pb,tw,T,i,s,wk,wi);
        return;
    }
    //if (k == 3){
    //    int hk = wk - k;
    //    int uk = wk - 1;
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i + 0*s,s,uk,wi);
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i + 4*s,s,uk,wi);
    //    sfft_cb_pb_b2_inverse(pb,tw,T,i + 0*s,4*s,wk,wi + ((i_ptr)0 << hk));
    //    sfft_cb_pb_b2_inverse(pb,tw,T,i + 1*s,4*s,wk,wi + ((i_ptr)1 << hk));
    //    sfft_cb_pb_b2_inverse(pb,tw,T,i + 2*s,4*s,wk,wi + ((i_ptr)2 << hk));
    //    sfft_cb_pb_b2_inverse(pb,tw,T,i + 3*s,4*s,wk,wi + ((i_ptr)3 << hk));
    //    return;
    //}
    //if (k == 4){
    //    int hk = wk - k;
    //    int uk = wk - 2;
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i +  0*s,s,uk,wi);
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i +  4*s,s,uk,wi);
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i +  8*s,s,uk,wi);
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i + 12*s,s,uk,wi);
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i + 0*s,4*s,wk,wi + ((i_ptr)0 << hk));
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i + 1*s,4*s,wk,wi + ((i_ptr)1 << hk));
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i + 2*s,4*s,wk,wi + ((i_ptr)2 << hk));
    //    sfft_cb_pb_b4_inverse(pb,tw,T,i + 3*s,4*s,wk,wi + ((i_ptr)3 << hk));
    //    return;
    //}
    
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
        sfft_cb_pb_bk_inverse(pb,tw,bk,T,i + c*bkL*s,s,uk,wi);
        c++;
    }while (c < rkL);

    //  Row Reduction
    c = 0;
    do{
        sfft_cb_pb_bk_inverse(pb,tw,rk,T,i + c*s,bkL*s,wk,wi + ((i_ptr)c << hk));
        c++;
    }while (c < bkL);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  End-Point Transform
void sfft_cb_pb_tk_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *T,i_ptr i
){
    if (k == 0){
        pb->fp_forward(tw,T,T);
        return;
    }
    if (k == 1){
        sfft_cb_pb_t2_forward(pb,tw,T,i);
        return;
    }
    if (k == 2){
        sfft_cb_pb_t4_forward(pb,tw,T,i);
        return;
    }

    i_ptr c;
    int rk = k >> 1;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;

    //  Row Reduction
//    if (k < 10){
    c = 0;
    do{
        sfft_cb_pb_bk_forward(pb,tw,rk,T,i + c,bkL,k,c);
        c++;
    }while (c < bkL);
//    }

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_pb_tk_forward(pb,tw,bk,T,i + c*bkL);
        c++;
    }while (c < rkL);
}
void sfft_cb_pb_tk_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *T,i_ptr i
){
    if (k == 0){
        pb->fp_inverse(tw,T,T);
        return;
    }
    if (k == 1){
        sfft_cb_pb_t2_inverse(pb,tw,T,i);
        return;
    }
    if (k == 2){
        sfft_cb_pb_t4_inverse(pb,tw,T,i);
        return;
    }

    i_ptr c;
    int rk = k >> 1;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;

    //  Sub-Transforms
    c = 0;
    do{
        sfft_cb_pb_tk_inverse(pb,tw,bk,T,i + c*bkL);
        c++;
    }while (c < rkL);

    //  Row Reduction
    c = 0;
    do{
        sfft_cb_pb_bk_inverse(pb,tw,rk,T,i + c,bkL,k,c);
        c++;
    }while (c < bkL);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
