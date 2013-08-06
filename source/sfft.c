/* sfft.c
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 05/16/2011
 * Last Modified    : 06/04/2011
 * 
 * 
 * 
 *  Compiler Options
 * 
 * 
 *  Default
 *      No options needed.
 * 
 * 
 *  PowerPC
 *      Power7 - Linux/AIX  :   gcc "" -lm -maltivec -mcpu=power7 -O2 -D "sfft_dp_Power7"
 *      Power7 - Linux/AIX  :   xlc "" -qaltivec -qlanglvl=extc99 -qarch=pwr7 -O2 -D "sfft_dp_Power7"
 * 
 * 
 *  x86/x64
 *      SSE3 - Windows      :   cl  "" /TP /O2 /Oy- -D "sfft_dp_x86_SSE3"
 *                          :   icl "" /TP /O3 /arch:SSE3 -D "sfft_dp_x86_SSE3"
 *      SSE3 - Linux        :   gcc "" -lm -msse3 -O2 -D "sfft_dp_x86_SSE3"
 * 
 *      AVX  - Windows      :   cl  "" /TP /O2 /Oy- /arch:AVX -D "sfft_dp_x86_AVX"
 *      AVX  - Linux        :   gcc "" -lm -mavx -O2 -D "sfft_dp_x86_AVX"
 * 
 *      FMA4 - Windows      :   cl  "" /TP /O2 /Oy- /arch:AVX -D "sfft_dp_x86_FMA4"
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
#ifdef __cplusplus
//#include "Tools/DebugPrinting.h"
#endif
#include "Tools/AlignedMalloc.h"
#include "Tools/Padding.h"
#include "Tools/TwiddleTable.h"
#include "Tools/BitReverse.h"

#ifdef sfft_dp_Default
#include "v0_Default/sFFT1_cb_f64v0_Default.h"
#elif defined sfft_dp_x86_SSE3
#include "v1_SSE3/sFFT1_cb_f64v1_SSE3.h"
#elif defined sfft_dp_Power7
#include "v1_Power7/sFFT1_cb_f64v1_Power7.h"
#elif defined sfft_dp_x86_AVX
#include "v2_AVX/sFFT1_cb_f64v2_AVX.h"
#elif defined sfft_dp_x86_FMA4
#include "v2_AVX/sFFT1_cb_f64v2_AVX.h"
#else
#error "No Architecture Selected."
#endif

#include "Basic/sFFT1_cb_tk.h"
#include "Block/sFFT1_block.h"
#include "Block/sFFT1_cb_pb_bk.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void sfft_get_km(i_ptr L,int *k,int *m){
    *k = 0;
    while ((L & 1) == 0){
        L >>= 1;
        (*k)++;
    }
    *m = (int)L;
}
void sfft_print_complex(f_word r,f_word i){
    printf("%g",r);
    if (i < 0){
        printf(" - %g i",-i);
    }else{
        printf(" + %g i",i);
    }
}
void sfft_cb_1D_print_fwords(f_word *T,i_ptr L){
    //  Print function for non-vectorized array.

    if (L == 0){
        printf("{}\n");
        return;
    }

    f_word *stopT = T + 2*L;
    {
        printf("{");
        sfft_print_complex(T[0],T[1]);
        T += 2;
    }


    while (T < stopT){
        printf(", ");
        sfft_print_complex(T[0],T[1]);
        T += 2;
    }
    printf("}\n");
}
void sfft_rand(f_word *T,i_ptr L,i_ptr shift){
    f_word *stop = T + 2*L;
    i_ptr i = 2*L * shift;
    while (T < stop){
        *T++ = (f_word)(i * i % 17);
        i++;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddle Factor Tables
DLL_EXTERN void sfft_table_t0_init(sfft_table_t0 *table){
    table->k1 = 0;
    table->k3 = 0;
    table->k5 = 0;
    table->k7 = 0;

    table->tw1 = NULL;
    table->tw3 = NULL;
    table->tw5 = NULL;
    table->tw7 = NULL;

    sFFT1_block_init_m(&table->pb1,1,6);
    sFFT1_block_init_m(&table->pb3,3,6);
    sFFT1_block_init_m(&table->pb5,5,6);
    sFFT1_block_init_m(&table->pb7,7,6);
}
DLL_EXTERN void sfft_table_t0_kill(sfft_table_t0 *table){
    //  Free all the tables.
    sfft_tables_kill(table->tw1);
    sfft_tables_kill(table->tw3);
    sfft_tables_kill(table->tw5);
    sfft_tables_kill(table->tw7);

    //  Zero the entire struct.
    memset(table,0,sizeof(sfft_table_t0));
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
DLL_EXTERN int sfft_table_t0_build(sfft_table_t0 *tw,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_table_t0_ensure_f1(tw,k); return 0;}
//        case 3: {sfft_table_t0_ensure_f3(tw,k); return 0;}
//        case 5: {sfft_table_t0_ensure_f5(tw,k); return 0;}
//        case 7: {sfft_table_t0_ensure_f7(tw,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_table_t0_ensure_f1(sfft_table_t0 *tw,int k){
    sfft_tables *tw1 = (sfft_tables*)malloc(sizeof(sfft_tables));
    tw->tw1 = tw1;

    sfft_table_make(&tw1->w1,k,1);
    sfft_table_make(&tw1->w2,k,2);
    sfft_table_make(&tw1->w3,k,3);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Complex Transforms
DLL_EXTERN int sfft_cb_1D_t0_pointwise_sqr(sfft_table_t0 *tw,f_vector *T,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_cb_1D_t0f1_pointwise_sqr(tw,T,k); return 0;}
//        case 3: {sfft_cb_1D_t0f3_pointwise_sqr(tw,T,k); return 0;}
//        case 5: {sfft_cb_1D_t0f5_pointwise_sqr(tw,T,k); return 0;}
//        case 7: {sfft_cb_1D_t0f7_pointwise_sqr(tw,T,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_cb_1D_t0f1_pointwise_sqr(sfft_table_t0 *tw,f_vector *T,int k){
    int bk = tw->pb1.k;
    if (k < bk){
        printf("Degenerate cases have not implemented yet. Minimum size of k is %d.",bk);
        exit(1);
        return;
    }

    i_ptr TL = (i_ptr)1 << (k - bk);

    i_ptr c = 0;
    do{
        sFFT1_block_psqr(&tw->pb1,T,c++);
    }while (c < TL);
}
DLL_EXTERN int sfft_cb_1D_t0_pointwise_scale(sfft_table_t0 *tw,f_vector *T,i_ptr L,f_word scale){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_cb_1D_t0f1_pointwise_scale(tw,T,k,scale); return 0;}
//        case 3: {sfft_cb_1D_t0f3_pointwise_sqr(tw,T,k,scale); return 0;}
//        case 5: {sfft_cb_1D_t0f5_pointwise_sqr(tw,T,k,scale); return 0;}
//        case 7: {sfft_cb_1D_t0f7_pointwise_sqr(tw,T,k,scale); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_cb_1D_t0f1_pointwise_scale(sfft_table_t0 *tw,f_vector *T,int k,f_word scale){
    int bk = tw->pb1.k;
    if (k < bk){
        printf("Degenerate cases have not implemented yet. Minimum size of k is %d.",bk);
        exit(1);
        return;
    }

    i_ptr TL = (i_ptr)1 << (k - bk);

    i_ptr c = 0;
    do{
        sFFT1_block_pscale(&tw->pb1,T,c++,scale);
    }while (c < TL);
}
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
    return sfft_padding_get(&tw->pb1.pad,TL) * sizeof(f_vector);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Copy padding - Copy data to and from the padded format used by this library.
DLL_EXTERN int sfft_cb_1D_t0_raw_to_padded(const sfft_table_t0 *tw,f_vector *T,const double *raw,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_cb_1D_t0f1_raw_to_padded(tw,T,raw,k); return 0;}
//        case 3: {sfft_cb_1D_t0f3_raw_to_padded(tw,T,raw,k); return 0;}
//        case 5: {sfft_cb_1D_t0f5_raw_to_padded(tw,T,raw,k); return 0;}
//        case 7: {sfft_cb_1D_t0f7_raw_to_padded(tw,T,raw,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_cb_1D_t0f1_raw_to_padded(const sfft_table_t0 *tw,f_vector *T,const double *raw,int k){
    if (k < 4){
        printf("Minimum size of k is 4.");
        exit(1);
    }

    int bk = tw->pb1.k;
    if (k < bk){
        printf("Degenerate cases have not implemented yet. Minimum size of k is %d.",bk);
        exit(1);
        return;
    }
    
    i_ptr TL = (i_ptr)1 << (k - bk);
    i_ptr block = tw->pb1.vsize << f_vk;

    i_ptr c = 0;
    while (c < TL){
        f_vector *point = T + sfft_padding_get(&tw->pb1.pad,c++);
        sFFT1_cb_raw_to_irp(point,raw,block);
        raw += block;
    }
}
DLL_EXTERN int sfft_cb_1D_t0_padded_to_raw(const sfft_table_t0 *tw,const f_vector *T,double *raw,i_ptr L){
    int k,m;
    sfft_get_km(L,&k,&m);

    switch (m){
        case 1: {sfft_cb_1D_t0f1_padded_to_raw(tw,T,raw,k); return 0;}
//        case 3: {sfft_cb_1D_t0f3_padded_to_raw(tw,T,raw,k); return 0;}
//        case 5: {sfft_cb_1D_t0f5_padded_to_raw(tw,T,raw,k); return 0;}
//        case 7: {sfft_cb_1D_t0f7_padded_to_raw(tw,T,raw,k); return 0;}
        default: return 1;
    }
}
DLL_EXTERN void sfft_cb_1D_t0f1_padded_to_raw(const sfft_table_t0 *tw,const f_vector *T,double *raw,int k){
    if (k < 4){
        printf("Minimum size of k is 4.");
        exit(1);
    }

    int bk = tw->pb1.k;
    if (k < bk){
        printf("Degenerate cases have not implemented yet. Minimum size of k is %d.",bk);
        exit(1);
        return;
    }
    
    i_ptr TL = (i_ptr)1 << (k - bk);
    i_ptr block = tw->pb1.vsize << f_vk;

    i_ptr c = 0;
    while (c < TL){
        const f_vector *point = T + sfft_padding_get(&tw->pb1.pad,c++);
        sFFT1_cb_irp_to_raw(point,raw,block);
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
DLL_EXTERN int sfft_b_1D_cb_t0_forward(const sfft_table_t0 *tw,f_vector *T,i_ptr L){
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
DLL_EXTERN int sfft_b_1D_cb_t0_inverse(const sfft_table_t0 *tw,f_vector *T,i_ptr L){
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
        sfft_cb_tk_f1_forward(tw->tw1,T,k);
    else
        sFFT1_cb_block_tk_forward(tw->tw1,&tw->pb1,T,tk,0,1);
}
DLL_EXTERN void sfft_b_1D_cb_t0f1_inverse(const sfft_table_t0 *tw,f_vector *T,int k){
    int bk = tw->pb1.k;
    int tk = k - bk;
    if (tk < 0)
        sfft_cb_tk_f1_inverse(tw->tw1,T,k);
    else
        sFFT1_cb_block_tk_inverse(tw->tw1,&tw->pb1,T,tk,0,1);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
