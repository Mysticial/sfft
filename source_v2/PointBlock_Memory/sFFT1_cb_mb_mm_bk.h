/* sfft_cb_mb_mm_bk.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/23/2012
 * Last Modified    : 04/23/2012
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      mb          =   Memory Block
 *      mm          =   Memory -> Memory
 *      bk          =   Radix 2^k butterfly
 * 
 */

#pragma once
#ifndef _sfft_cb_mb_mm_bk_H
#define _sfft_cb_mb_mm_bk_H
#include "sfft_cb_mb_mm_b2.h"
#include "sfft_cb_mb_mm_b4.h"
#include "sfft_cb_mb_mm_bk.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddled Butterfly
void sfft_cb_mb_mm_bk_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,i_ptr S,
    f_vector *C,int ck,
    int wk,i_ptr wi
){
    if (k == 1){
        sfft_cb_mb_mm_b2_forward(pb,tw,M,S,C,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_mb_mm_b4_forward(pb,tw,M,S,C,wk,wi);
        return;
    }

#ifdef DISABLE_LAZY_COPY
    if (k <= ck){
        i_ptr c;
        i_ptr L = (i_ptr)1 << k;

        //  Copy to cache
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(T,M + c*S,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        //  Perform computation
        sfft_cb_pb_bk_forward(pb,tw,k,C,0,1,wk,wi);

        //  Copy back to memory
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(M + c*S,T,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        return;
    }
#endif

    i_ptr c;
    int rk = k >> 1;
    if (rk > ck)
        rk = ck;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    int hk = wk - k;
    int uk = wk - rk;

    if (k <= ck){
        //  Row Reduction
        c = 0;
        do{
            sfft_cb_mb_mc_bk_forward(pb,tw,rk,M + c*S,bkL*S,C,c,bkL,wk,wi + ((i_ptr)c << hk));
            c++;
        }while (c < bkL);

        //  Sub-Transforms
        c = 0;
        do{
            sfft_cb_mb_cm_bk_forward(pb,tw,bk,M + c*bkL*S,S,C,c*bkL,1,uk,wi);
            c++;
        }while (c < rkL);
    }else{
        cout << "Not Implemented Yet: sfft_cb_mb_mm_bk_forward()" << endl;
    }
}
void sfft_cb_mb_mm_bk_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,i_ptr S,
    f_vector *C,int ck,
    int wk,i_ptr wi
){
    if (k == 1){
        sfft_cb_mb_mm_b2_inverse(pb,tw,M,S,C,wk,wi);
        return;
    }
    if (k == 2){
        sfft_cb_mb_mm_b4_inverse(pb,tw,M,S,C,wk,wi);
        return;
    }
    
#ifdef DISABLE_LAZY_COPY
    if (k <= ck){
        i_ptr c;
        i_ptr L = (i_ptr)1 << k;

        //  Copy to cache
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(T,M + c*S,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        //  Perform computation
        sfft_cb_pb_bk_inverse(pb,tw,k,C,0,1,wk,wi);

        //  Copy back to memory
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(M + c*S,T,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        return;
    }
#endif

    i_ptr c;
    int rk = k >> 1;
    if (rk > ck)
        rk = ck;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    int hk = wk - k;
    int uk = wk - rk;

    if (k <= ck){
        //  Sub-Transforms
        c = 0;
        do{
            sfft_cb_mb_cm_bk_inverse(pb,tw,bk,M + c*bkL*S,S,C,c*bkL,1,uk,wi);
            c++;
        }while (c < rkL);

        //  Row Reduction
        c = 0;
        do{
            sfft_cb_mb_mc_bk_inverse(pb,tw,rk,M + c*S,bkL*S,C,c,bkL,wk,wi + ((i_ptr)c << hk));
            c++;
        }while (c < bkL);
    }else{
        cout << "Not Implemented Yet sfft_cb_mb_mm_bk_inverse()" << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  End-Point Transform
void sfft_cb_mb_mm_tk_forward(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,
    f_vector *C,int ck
){
    if (k == 1){
        sfft_cb_mb_mm_t2_forward(pb,tw,M);
        return;
    }
    if (k == 2){
        sfft_cb_mb_mm_t4_forward(pb,tw,M,C);
        return;
    }
    
#ifdef DISABLE_LAZY_COPY
    if (k <= ck){
        i_ptr c;
        i_ptr L = (i_ptr)1 << k;

        //  Copy to cache
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(T,M + c*pb->vsize,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        //  Perform computation
        sfft_cb_pb_tk_forward(pb,tw,k,C,0);

        //  Copy back to memory
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(M + c*pb->vsize,T,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        return;
    }
#endif

    i_ptr c;
    int rk = k >> 1;
    if (rk > ck)
        rk = ck;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    i_ptr vsize = pb->vsize;

    if (k <= ck){
        //  Row Reduction
        c = 0;
        do{
            sfft_cb_mb_mc_bk_forward(pb,tw,rk,M + c*vsize,bkL*vsize,C,c,bkL,k,c);
            c++;
        }while (c < bkL);

        //  Sub-Transforms
        c = 0;
        do{
            sfft_cb_mb_cm_tk_forward(pb,tw,bk,M + c*bkL*vsize,C,c*bkL);
            c++;
        }while (c < rkL);
    }else{
        //  Row Reduction
        c = 0;
        do{
            sfft_cb_mb_mm_bk_forward(pb,tw,rk,M + c*vsize,bkL*vsize,C,ck,k,c);
            c++;
        }while (c < bkL);

        //  Sub-Transforms
        c = 0;
        do{
            sfft_cb_mb_mm_tk_forward(pb,tw,bk,M + c*bkL*vsize,C,ck);
            c++;
        }while (c < rkL);
    }
}
void sfft_cb_mb_mm_tk_inverse(
    const sfft_block *pb,const sfft_cb_tables *tw,
    int k,
    f_vector *M,
    f_vector *C,int ck
){
    if (k == 1){
        sfft_cb_mb_mm_t2_inverse(pb,tw,M,C);
        return;
    }
    if (k == 2){
        sfft_cb_mb_mm_t4_inverse(pb,tw,M,C);
        return;
    }

#ifdef DISABLE_LAZY_COPY
    if (k <= ck){
        i_ptr c;
        i_ptr L = (i_ptr)1 << k;

        //  Copy to cache
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(T,M + c*pb->vsize,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        //  Perform computation
        sfft_cb_pb_tk_inverse(pb,tw,k,C,0);

        //  Copy back to memory
        c = 0;
        do{
            f_vector *T = C + sfft_padding_get(&pb->pad,c);
            memcpy(M + c*pb->vsize,T,pb->vsize * sizeof(f_vector));
            c++;
        }while (c < L);

        return;
    }
#endif

    i_ptr c;
    int rk = k >> 1;
    if (rk > ck)
        rk = ck;
    int bk = k - rk;
    i_ptr rkL = (i_ptr)1 << rk;
    i_ptr bkL = (i_ptr)1 << bk;
    i_ptr vsize = pb->vsize;

    if (k <= ck){
        //  Sub-Transforms
        c = 0;
        do{
            sfft_cb_mb_cm_tk_inverse(pb,tw,bk,M + c*bkL*vsize,C,c*bkL);
            c++;
        }while (c < rkL);

        //  Row Reduction
        c = 0;
        do{
            sfft_cb_mb_mc_bk_inverse(pb,tw,rk,M + c*vsize,bkL*vsize,C,c,bkL,k,c);
            c++;
        }while (c < bkL);
    }else{
        //  Sub-Transforms
        c = 0;
        do{
            sfft_cb_mb_mm_tk_inverse(pb,tw,bk,M + c*bkL*vsize,C,ck);
            c++;
        }while (c < rkL);

        //  Row Reduction
        c = 0;
        do{
            sfft_cb_mb_mm_bk_inverse(pb,tw,rk,M + c*vsize,bkL*vsize,C,ck,k,c);
            c++;
        }while (c < bkL);
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
