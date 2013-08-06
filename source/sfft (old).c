/* sfft.c
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 05/16/2011
 * Last Modified    : 05/16/2011
 * 
 */

#ifdef __cplusplus
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#endif

#define DLL_BUILD_CORE
#include "sfft.h"

#include "DebugPrinting.h"
#if (defined FFT_dp_x64_AVX) || (defined FFT_dp_x64_FMA4)
#include "Basic1D/v2_AVX/FFT1D_cb_f64v2_AVX.h"
#endif
#ifdef  FFT_dp_x64_SSE3
#include "Basic1D/v1_SSE3/FFT1D_cb_f64v1_SSE3.h"
#endif
#ifdef  FFT_dp_Default
#include "Basic1D/v0_Default/FFT1D_cb_f64v0_Default.h"
#endif

//  Memory Allocation
#include "AlignedMalloc.h"

//  Twiddle Tables
#include "TwiddleTable.h"
#include "TwiddleTable2.h"
#if   f_vk == 0
#define FFT_table_make      FFT_table_v0_make
#define FFT_sp_table_make   FFT_sp_table_v0_make
#elif f_vk == 1
#define FFT_table_make      FFT_table_v1_make
#define FFT_sp_table_make   FFT_sp_table_v1_make
#elif f_vk == 2
#define FFT_table_make      FFT_table_v2_make
#define FFT_sp_table_make   FFT_sp_table_v2_make
#else
#error "Vector Size not supported"
#endif

#include "Basic1D/FFT1D_cb_top_tk.h"
#include "Basic1D/FFT1D_cb_block_bk.h"

void sfft_get_km(i_ptr L,int *k,int *m){
    *k = 0;
    while ((L & 1) == 0){
        L >>= 1;
        (*k)++;
    }
    *m = (int)L;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DLL_EXTERN void sfft_table_t0_init(sfft_table_t0 *table){
    table->k1 = 0;
    table->k3 = 0;
    table->k5 = 0;
    table->k7 = 0;

    table->tw1 = NULL;
    table->tw3 = NULL;
    table->tw5 = NULL;
    table->tw7 = NULL;

    FFT1D_block_init_m(&table->pb1,1,6);
    FFT1D_block_init_m(&table->pb3,3,6);
    FFT1D_block_init_m(&table->pb5,5,6);
    FFT1D_block_init_m(&table->pb7,7,6);
}
DLL_EXTERN void sfft_table_t0_kill(sfft_table_t0 *table){
    //  Free all the tables.
    FFT_tables_kill(table->tw1);
    FFT_tables_kill(table->tw3);
    FFT_tables_kill(table->tw5);
    FFT_tables_kill(table->tw7);

    //  Zero the entire struct.
    memset(table,0,sizeof(sfft_table_t0));
}
////////////////////////////////////////////////////////////////////////////////
DLL_EXTERN int sfft_table_t0_build(sfft_table_t0 *tw,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_table_t0_ensure_f1(tw,k); return 0;}
        case 3: {sfft_table_t0_ensure_f1(tw,k); return 0;}
        case 5: {sfft_table_t0_ensure_f1(tw,k); return 0;}
        case 7: {sfft_table_t0_ensure_f1(tw,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_table_t0_ensure_f1(sfft_table_t0 *tw,int k){
    FFT_tables *tw1 = (FFT_tables*)malloc(sizeof(FFT_tables));
    tw->tw1 = tw1;

    FFT_table_make(&tw1->w1,k,1);
    FFT_table_make(&tw1->w2,k,2);
    FFT_table_make(&tw1->w3,k,3);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Buffer Sizes
DLL_EXTERN i_ptr sfft_cb_1D_t0_Tbytes(sfft_table_t0 *tw,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: return sfft_cb_1D_t0f1_Tbytes(tw,k);
//        case 3: return sfft_cb_1D_t0f3_Tbytes(tw,k);
//        case 5: return sfft_cb_1D_t0f5_Tbytes(tw,k);
//        case 7: return sfft_cb_1D_t0f7_Tbytes(tw,k);
        default: return (i_ptr)0 - 1;
    }
}
DLL_EXTERN i_ptr sfft_cb_1D_t0f1_Tbytes(sfft_table_t0 *tw,int k){
    int bk = tw->pb1.k;
    if (k < bk)
        return (i_ptr)2 * sizeof(f_word) << k;

    i_ptr TL = (i_ptr)1 << (k - bk);
    return FFT_padding_get(&tw->pb1.pad,TL) * sizeof(f_vector);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Copy padding - Copy data to and from the padded format used by this library.
DLL_EXTERN int sfft_cb_1D_cb_t0_raw_to_padded(const sfft_table_t0 *tw,f_vector *T,const double *raw,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_cb_1D_cb_t0f1_raw_to_padded(tw,T,raw,k); return 0;}
//        case 3: {sfft_cb_1D_cb_t0f3_raw_to_padded(tw,T,raw,k); return 0;}
//        case 5: {sfft_cb_1D_cb_t0f5_raw_to_padded(tw,T,raw,k); return 0;}
//        case 7: {sfft_cb_1D_cb_t0f7_raw_to_padded(tw,T,raw,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_cb_1D_cb_t0f1_raw_to_padded(const sfft_table_t0 *tw,f_vector *T,const double *raw,int k){
    if (k < 4){
        printf("Minimum size of k is 4.");
        exit(1);
    }

    int bk = tw->pb1.k;
    if (k < bk){
//        memcpy(T,raw,(i_ptr)2 * sizeof(f_word) << k);
        printf("Degenerate cases have not implemented yet. Minimum size of k is %d.",bk);
        exit(1);
        return;
    }
    
    i_ptr TL = (i_ptr)1 << (k - bk);
    i_ptr block = tw->pb1.vsize << f_vk;

    i_ptr c = 0;
    while (c < TL){
        f_vector *point = T + FFT_padding_get(&tw->pb1.pad,c++);
        FFT1D_cb_raw_to_irp(point,raw,block);
        raw += block;
    }
}
DLL_EXTERN int sfft_cb_1D_cb_t0_padded_to_raw(const sfft_table_t0 *tw,const f_vector *T,double *raw,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_cb_1D_cb_t0f1_padded_to_raw(tw,T,raw,k); return 0;}
//        case 3: {sfft_cb_1D_cb_t0f3_padded_to_raw(tw,T,raw,k); return 0;}
//        case 5: {sfft_cb_1D_cb_t0f5_padded_to_raw(tw,T,raw,k); return 0;}
//        case 7: {sfft_cb_1D_cb_t0f7_padded_to_raw(tw,T,raw,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_cb_1D_cb_t0f1_padded_to_raw(const sfft_table_t0 *tw,const f_vector *T,double *raw,int k){
    if (k < 4){
        printf("Minimum size of k is 4.");
        exit(1);
    }

    int bk = tw->pb1.k;
    if (k < bk){
//        memcpy(raw,T,(i_ptr)2 * sizeof(f_word) << k);
        printf("Degenerate cases have not implemented yet. Minimum size of k is %d.",bk);
        exit(1);
        return;
    }
    
    i_ptr TL = (i_ptr)1 << (k - bk);
    i_ptr block = tw->pb1.vsize << f_vk;

    i_ptr c = 0;
    while (c < TL){
        const f_vector *point = T + FFT_padding_get(&tw->pb1.pad,c++);
        FFT1D_cb_irp_to_raw(point,raw,block);
        raw += block;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Indexing function for accessing bit-reversed frequency domain.
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (Any Length) - Returns non-zero if the table does not support the requested FFT size.
DLL_EXTERN int sfft_b_1D_rb_t0_forward(const sfft_table_t0 *tw,f_vector *T,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_b_1D_cb_t0f1_forward(tw,T,k); return 0;}
//        case 3: {sfft_b_1D_cb_t0f3_forward(tw,T,k); return 0;}
//        case 5: {sfft_b_1D_cb_t0f5_forward(tw,T,k); return 0;}
//        case 7: {sfft_b_1D_cb_t0f7_forward(tw,T,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN int sfft_b_1D_rb_t0_inverse(const sfft_table_t0 *tw,f_vector *T,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_b_1D_cb_t0f1_inverse(tw,T,k); return 0;}
//        case 3: {sfft_b_1D_cb_t0f3_inverse(tw,T,k); return 0;}
//        case 5: {sfft_b_1D_cb_t0f5_inverse(tw,T,k); return 0;}
//        case 7: {sfft_b_1D_cb_t0f7_inverse(tw,T,k); return 0;}
        default: return 1;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 1 * 2^k)
DLL_EXTERN void sfft_b_1D_cb_t0f1_forward(const sfft_table_t0 *tw,f_vector *T,int k){
    int bk = tw->pb1.k;
    int tk = k - bk;
    if (tk < 0)
        FFT1D_cb_tk_forward(T,k,tw->tw1);
    else
        FFT1D_cb_block_tk_forward(&tw->pb1,T,tk,0,1,tw->tw1);
}
DLL_EXTERN void sfft_b_1D_cb_t0f1_inverse(const sfft_table_t0 *tw,f_vector *T,int k){
    int bk = tw->pb1.k;
    int tk = k - bk;
    if (tk < 0)
        FFT1D_cb_tk_inverse(T,k,tw->tw1);
    else
        FFT1D_cb_block_tk_inverse(&tw->pb1,T,tk,0,1,tw->tw1);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
