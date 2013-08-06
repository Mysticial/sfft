#include <stdio.h>
#ifdef __cplusplus
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#endif

// icl main.cpp source_v2/Debuggers.c source_v2/sfft_malloc.c source_v2/WallClock.c /TP /O3 /arch:SSE3 -D "sfft_dp_x86_SSE3"

//#include <papi.h>

//#define DLL_BUILD_CORE

#include "source_v2/WallClock.h"
#include "source_v2/sfft_malloc.h"
#include "source_v2/PointBlock/sfft_block_internals.h"

#include "source_v2/Tables/sfft_cb_tables_M_internals.h"



//  Debuggers
//void sfft_rand(f_word *T,i_ptr L,i_ptr shift);


//#include "source/v0_Default/sfft_cb_f64v0_Default.h"


//void sfft_cb_t16_forward(const sfft_cb_tables *tw,f_vector *T);
//void sfft_cb_t16_inverse(const sfft_cb_tables *tw,f_vector *T);
//void sfft_cb_t32_forward(const sfft_cb_tables *tw,f_vector *T);
//void sfft_cb_t32_inverse(const sfft_cb_tables *tw,f_vector *T);
//void sfft_cb_t64_forward(const sfft_cb_tables *tw,f_vector *T);
//void sfft_cb_t64_inverse(const sfft_cb_tables *tw,f_vector *T);

//#include "source_v2/vK_Generic/sfft_cb_tg_b2.h"
//#include "source_v2/vK_Generic/sfft_cb_tg_b3.h"
//#include "source_v2/vK_Generic/sfft_cb_tg_b4.h"


//#include "source_v2/v0_Default/sfft_cb_v0_Default.h"
//#include "source_v2/v1_SSE3/sfft_cb_f64v1_SSE3.h"
//#include "source_v2/v2_AVX/sfft_cb_f64v2_AVX.h"


//#include "source_v2/v1_SSE3/sfft_cb_f64v1_t4_SSE3.h"
//#include "source_v2/v1_SSE3/sfft_cb_f64v1_t8_SSE3.h"
//#include "source_v2/v1_SSE3/sfft_cb_f64v1_t16_SSE3.h"
//#include "source_v2/v1_SSE3/sfft_cb_f64v1_t32_SSE3.h"
//#include "source_v2/v1_SSE3/sfft_cb_f64v1_t64_SSE3.h"

//#include "source_v2/v2_AVX/sfft_cb_f64v2_t16_AVX.h"
//#include "source_v2/v2_AVX/sfft_cb_f64v2_t32_AVX.h"
//#include "source_v2/v2_AVX/sfft_cb_f64v2_t64_AVX.h"

//#include "source_v2/PointBlock_Cache/sfft_cb_pb_bk.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#define DISABLE_LAZY_COPY
//#include "source_v2/PointBlock_Memory/sfft_cb_mb_mc_bk.h"
//#include "source_v2/PointBlock_Memory/sfft_cb_mb_cm_bk.h"
//#include "source_v2/PointBlock_Memory/sfft_cb_mb_mm_bk.h"

//#include "source_v2/v0_Default/sfft_cb_v0_bitreverse.h"
#if 0
void test_cb_block(int m,int ks,int ke,int seconds){
    //  Benchmark and test bit-reversed FFT.

    //  FFT Parameters
//    int m = 1;
    int k = ks;

    while (k <= ke){

        //  Initialize Tables
        sfft_cb_tables tw;
        sfft_cb_tables_init(&tw);

        //  Get Point Block
        const sfft_block *pb = NULL;
        int pk;
        switch (m){
            case 1:
                pb = &sfft_cb_pb_m1;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                break;
            case 3:
                pb = &sfft_cb_pb_m3;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                sfft_cb_tables_ensure_r3(&tw,pb->k,pk);
                break;
            case 5:
                pb = &sfft_cb_pb_m5;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                sfft_cb_tables_ensure_r5(&tw,pb->k,pk);
                break;
            case 7:
                pb = &sfft_cb_pb_m7;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                sfft_cb_tables_ensure_r7(&tw,pb->k,pk);
                break;
            default:
                cout << "multiplier not supported: " << m << endl;
                return;
        }
    //    ks -= pb->k;
        i_ptr L = (i_ptr)1 << pk;

        //  Compute size
        i_ptr bytes = sfft_cb_pb_size(pb,pk);
        cout << "FFT bytes = " << bytes << endl;

        //  Allocate data
        f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
        memset(T,0,bytes);

        cout << endl;
        cout << "k = " << k << endl;

        bytes = sfft_cb_pb_size(pb,pk);
        memset(T,0,bytes);

        wallclock time0 = wc_now();
        double secs;
        i_ptr iterations = 0;
        while ((secs = wc_time_since(time0)) < seconds){
            if (k < 12){
                for (int c = 0; c < 1000; c++)
                    sfft_cb_pb_forward(pb,&tw,pk,T);
                iterations += 1000;
            }else{
                sfft_cb_pb_forward(pb,&tw,pk,T);
                iterations++;
            }
        }

        cout << "Seconds:        " << secs / iterations << endl;
        cout << "Iterations/sec: " << (i_ptr)(iterations / secs) << endl;

        sfft_cb_pb_rand(pb,T,L);
        sfft_cb_pb_forward(pb,&tw,pk,T);
        sfft_cb_pb_sqr(pb,T,L);
        sfft_cb_pb_inverse(pb,&tw,pk,T);
        sfft_cb_pb_scale(pb,T,L,1. / (L << pb->k));
        f_word residual = sfft_cb_pb_residual(pb,T,L);
        cout << "Residual = " << residual << endl;
        cout << endl;

        k++;

        //  Free
        sfft_free(T);
        sfft_cb_tables_kill(&tw);
    }
}
void test_ci_block(int m,int ks,int ke,int seconds){
    //  Benchmark and test bit-reversed FFT.

    //  FFT Parameters
//    int m = 1;
    int k = ks;

    while (k <= ke){

        //  Initialize Tables
        sfft_cb_tables tw;
        sfft_cb_tables_init(&tw);

        //  Get Point Block
        const sfft_block *pb = NULL;
        int pk;
        switch (m){
            case 1:
                pb = &sfft_cb_pb_m1;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                break;
            case 3:
                pb = &sfft_cb_pb_m3;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                sfft_cb_tables_ensure_r3(&tw,pb->k,pk);
                break;
            case 5:
                pb = &sfft_cb_pb_m5;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                sfft_cb_tables_ensure_r5(&tw,pb->k,pk);
                break;
            case 7:
                pb = &sfft_cb_pb_m7;
                pk = k - pb->k;
                sfft_cb_tables_ensure_r1(&tw,pb->k,pk);
                sfft_cb_tables_ensure_r7(&tw,pb->k,pk);
                break;
            default:
                cout << "multiplier not supported: " << m << endl;
                return;
        }
    //    ks -= pb->k;
        i_ptr L = (i_ptr)1 << pk;

        //  Compute size
        i_ptr bytes = sfft_cb_pb_size(pb,pk);
        cout << "FFT bytes = " << bytes << endl;

        //  Allocate data
        f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
        f_vector *U = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
        memset(T,0,bytes);
        memset(U,0,bytes);

        cout << endl;
        cout << "k = " << k << endl;

        bytes = sfft_cb_pb_size(pb,pk);
        memset(T,0,bytes);

        wallclock time0 = wc_now();
        double secs;
        i_ptr iterations = 0;
        while ((secs = wc_time_since(time0)) < seconds){
            if (k < 12){
                for (int c = 0; c < 1000; c++){
                    sfft_cb_pb_forward(pb,&tw,pk,T);
                    sfft_cb_bitreverse_copy_b2_normal(pb,pk,T,U);
                }
                iterations += 1000;
            }else{
                sfft_cb_pb_forward(pb,&tw,pk,T);
                sfft_cb_bitreverse_copy_b2_normal(pb,pk,T,U);
                iterations++;
            }
        }

        cout << "Seconds:        " << secs / iterations << endl;
        cout << "Iterations/sec: " << (i_ptr)(iterations / secs) << endl;

        sfft_cb_pb_rand(pb,T,L);
        sfft_cb_pb_forward(pb,&tw,pk,T);
        sfft_cb_pb_sqr(pb,T,L);
        sfft_cb_pb_inverse(pb,&tw,pk,T);
        sfft_cb_pb_scale(pb,T,L,1. / (L << pb->k));
        f_word residual = sfft_cb_pb_residual(pb,T,L);
        cout << "Residual = " << residual << endl;
        cout << endl;

        k++;

        //  Free
        sfft_free(T);
        sfft_free(U);
        sfft_cb_tables_kill(&tw);
    }
}
void test_ci_block_(int m,int ks,int ke,int seconds){
    //  Benchmark and test bit-reversed FFT.

    //  Initialize Tables
    sfft_cb_tables tw;
    sfft_cb_tables_init(&tw);

    //  Get Point Block
    const sfft_block *pb = NULL;
    switch (m){
        case 1:
            pb = &sfft_cb_pb_m1;
            ke -= pb->k;
            sfft_cb_tables_ensure_r1(&tw,pb->k,ke);
            break;
        case 3:
            pb = &sfft_cb_pb_m3;
            ke -= pb->k;
            sfft_cb_tables_ensure_r1(&tw,pb->k,ke);
            sfft_cb_tables_ensure_r3(&tw,pb->k,ke);
            break;
        case 5:
            pb = &sfft_cb_pb_m5;
            ke -= pb->k;
            sfft_cb_tables_ensure_r1(&tw,pb->k,ke);
            sfft_cb_tables_ensure_r5(&tw,pb->k,ke);
            break;
        case 7:
            pb = &sfft_cb_pb_m7;
            ke -= pb->k;
            sfft_cb_tables_ensure_r1(&tw,pb->k,ke);
            sfft_cb_tables_ensure_r7(&tw,pb->k,ke);
            break;
        default:
            cout << "multiplier not supported: " << m << endl;
            return;
    }
    ks -= pb->k;

    //  Compute size
    i_ptr bytes = sfft_cb_pb_size(pb,ke);
    cout << "FFT bytes = " << bytes << endl;

    //  Allocate data
    f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    f_vector *U = (f_vector*)sfft_malloc(bytes,64);
    memset(T,0,bytes);
    memset(U,0,bytes);

    //  FFT Parameters
//    int m = 1;
    int k = ks;
    i_ptr L = (i_ptr)1 << k;

    cout << endl;
    while (k <= ke){
        cout << "k = " << k + pb->k << endl;

        bytes = sfft_cb_pb_size(pb,k);
        memset(T,0,bytes);

        wallclock time0 = wc_now();
        double secs;
        i_ptr iterations = 0;
        while ((secs = wc_time_since(time0)) < seconds){
            sfft_cb_pb_forward(pb,&tw,k,T);
            sfft_cb_bitreverse_copy_b2_normal(pb,k,T,U);
            iterations++;
        }

        cout << "Seconds: " << secs / iterations << endl;

        sfft_cb_pb_rand(pb,T,L);
        sfft_cb_pb_forward(pb,&tw,k,T);
        sfft_cb_pb_sqr(pb,T,L);
        sfft_cb_pb_inverse(pb,&tw,k,T);
        sfft_cb_pb_scale(pb,T,L,1. / (L << pb->k));
        f_word residual = sfft_cb_pb_residual(pb,T,L);
        cout << "Residual = " << residual << endl;
        cout << endl;

        k++;
    }


    //  Free
    sfft_free(T);
    sfft_free(U);
    sfft_cb_tables_kill(&tw);
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int main(){
    printf(SFFT_ARCH);
    printf("\n\n");

















#if 0
    i_ptr length = 160;

    sfft_plan plan;
    int ret = sfft_cb_pb_get(&plan,length);
    if (ret){
        system("pause");
        exit(1);
    }
    cout << "block = " << (plan.pb->m << plan.pb->k) << endl;
    cout << "k     = " << plan.k << endl;
    cout << endl;


    //  Initialize Tables
    sfft_cb_tables tw;
    sfft_cb_tables_init(&tw);
    sfft_cb_tables_ensure_r1(&tw,plan.pb->k,0);
    sfft_cb_tables_ensure_r5(&tw,plan.pb->k,plan.k);

    //  Generate Data
    double *A = (double*)malloc(sizeof(double)*2 * length);
    sfft_rand_complex(A,length,4);
    sfft_print_farray(A,length,0);

    //  Allocate FFT array
    i_ptr bytes = sfft_cb_pb_size(plan.pb,plan.k);
    f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector)*4);







    
    sfft_free(T);
    free(A);
    sfft_cb_tables_kill(&tw);
#endif

    
    //int k = 2;
    //const sfft_block *pb = &sfft_cb_pb_t28;

    //k -= pb->k;
    //i_ptr pbL = (i_ptr)1 << k;
    //
    ////  Initialize Tables
    //sfft_cb_tables tw;
    //sfft_cb_tables_init(&tw);
    //sfft_cb_tables_ensure_r1(&tw,pb->k,0);
    //sfft_cb_tables_ensure_r7(&tw,pb->k,k);


    //i_ptr bytes = sfft_cb_pb_size(pb,k);
    //cout << bytes << endl;

    //f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    //sfft_cb_pb_rand(pb,T,pbL);
    //sfft_cb_pb_print(pb,T,pbL);

    //sfft_cb_pb_tk_forward(pb,&tw,k,T,0);
    //sfft_cb_pb_print(pb,T,pbL);


    //sfft_free(T);
    //sfft_cb_tables_kill(&tw);



    //test_cb_block(1,8,24,4);
    //system("pause");
    //test_cb_block(3,8,24,4);
    //test_ci_block(1,8,16,4);
    //system("pause");
    //test_ci_block(3,8,16,4);
    //system("pause");
    //test_ci_block(5,8,16,4);
    //system("pause");
    //test_ci_block(7,8,16,4);

//
//#if 0
//    int k = 6;
//    i_ptr L = (i_ptr)1 << k;
//    i_ptr bytes = L * sizeof(f_word) * 2;
//
//    //  Initialize Tables
//    sfft_cb_tables tw;
//    sfft_cb_tables_init(&tw);
//    sfft_cb_tables_ensure_r1(&tw,k,0);
//
//    f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
//    memset(T,0,bytes);
//
//    sfft_cb_t64_forward(&tw,T,T);
//    sfft_cb_t64_inverse(&tw,T,T);
//
//    sfft_free(T);
//    sfft_cb_tables_kill(&tw);
//#else
//    int k = 6;
//    const sfft_block *pb = &sfft_cb_pb_t64;
//
//    //  Initialize Tables
//    sfft_cb_tables tw;
//    sfft_cb_tables_init(&tw);
//    sfft_cb_tables_ensure_r1(&tw,k,0);
//
//    int pbk = k - pb->k;
//    i_ptr L = (i_ptr)1 << pbk;
//    i_ptr bytes = sfft_pb_size(pb,pbk);
//
////    cout << k - pb->k << endl;
////    cout << bytes << endl;
//    f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
//    memset(T,0,bytes);
//    sfft_pb_rand(pb,T,L);
//    sfft_pb_print(pb,T,L);
//
//    sfft_cb_pb_tk_forward(pb,&tw,pbk,T,0);
//    sfft_cb_pb_tk_inverse(pb,&tw,pbk,T,0);
//    sfft_pb_scale(pb,T,L,1./(L*pb->m << pb->k));
//    
//    sfft_pb_print(pb,T,L);
//
//    sfft_free(T);
//    sfft_cb_tables_kill(&tw);
//#endif



    //cout << sfft_cb_reverse_index_m3(2,2,0) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,1) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,2) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,3) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,4) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,5) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,6) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,7) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,8) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,9) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,10) << endl;
    //cout << sfft_cb_reverse_index_m3(2,2,11) << endl;


    //int k = 6;
    //i_ptr L = (i_ptr)1 << k;
    //i_ptr bytes = L * sizeof(f_word) * 2;

    ////  Initialize Tables
    //sfft_cb_tables tw;
    //sfft_cb_tables_init(&tw);

    //sfft_cb_tables_ensure_r1(&tw,k,0);



    //f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    //memset(T,0,bytes);


    //wallclock start = wc_now();

    //i_ptr i = 0;
    //double secs;
    //while ((secs = wc_time_since(start)) < 4.0){
    //    for (int c = 0; c < 1000; c++){
    //        sfft_cb_t64_forward(&tw,T,T);
    //    }
    //    i += 1000;
    //}

    //cout << "iterations     = " << i << endl;
    //cout << "iterations/sec = " << (i_ptr)(i / secs) << endl;



    //sfft_free(T);
    //sfft_cb_tables_kill(&tw);


    //  Bitreverse 1 Block
#if 0
    //  Initialize Tables
    sfft_cb_tables tw;
    sfft_cb_tables_init(&tw);

    const sfft_block *pb = &sfft_cb_pb_m3;
    sfft_cb_tables_ensure_r1(&tw,pb->k,0);
    sfft_cb_tables_ensure_r3(&tw,pb->k,0);

//    int m = 3;
//    int k = pb->k;
//    i_ptr L = (i_ptr)m << k;
    i_ptr blocks = 1;

    i_ptr bytes = sfft_pb_size(pb,0);
    cout << bytes << endl;

    f_vector P[100];

    //  Allocate data
    f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    f_vector *U = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    memset(T,0,bytes);
    memset(U,0,bytes);
    sfft_pb_rand(pb,T,blocks);

    sfft_pb_print(pb,T,blocks);

    sfft_pb_forward(pb,&tw,0,T);

    sfft_pb_print(pb,T,blocks);

    sfft_cbr_transpose_m3_k1(T +  0,T + 16,T + 32,U +  0,U + 24);
    sfft_cbr_transpose_m3_k1(T +  4,T + 20,T + 36,U + 12,U + 36);
    sfft_cbr_transpose_m3_k1(T +  8,T + 24,T + 40,U +  6,U + 30);
    sfft_cbr_transpose_m3_k1(T + 12,T + 28,T + 44,U + 18,U + 42);



    
    sfft_pb_print(pb,U,blocks);

    sfft_free(T);
    sfft_free(U);
#endif
    
#if 0
    //  Initialize Tables
    sfft_cb_tables tw;
    sfft_cb_tables_init(&tw);

    int k = 3;

    const sfft_block *pb = &sfft_cb_pb_m3;
    i_ptr pbL = pb->m << pb->k;
    cout << "pbL = " << pbL << endl;

    sfft_cb_tables_ensure_r1(&tw,pb->k,k);
    sfft_cb_tables_ensure_r3(&tw,pb->k,k);

    i_ptr blocks = 1 << k;
    i_ptr L = pbL << k;
    cout << "L   = " << L << endl;

    i_ptr bytes = sfft_pb_size(pb,k);
    cout << bytes << endl;

    //  Allocate data
    f_vector *T = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    f_vector *U = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    memset(T,0,bytes);
    memset(U,0,bytes);
    sfft_pb_rand(pb,T,blocks);

    sfft_pb_print(pb,T,blocks);

    sfft_pb_forward(pb,&tw,k,T);

//    sfft_pb_print(pb,T,blocks);

    //f_vector *T0 = T + sfft_padding_get(&pb->pad,0);
    //f_vector *T1 = T + sfft_padding_get(&pb->pad,1);
    //f_vector *T2 = T + sfft_padding_get(&pb->pad,2);
    //f_vector *T3 = T + sfft_padding_get(&pb->pad,3);
//    f_vector *U0 = U + sfft_padding_get(&pb->pad,0);
//    f_vector *U1 = U + sfft_padding_get(&pb->pad,1);
//    f_vector *U2 = U + sfft_padding_get(&pb->pad,2);
//    f_vector *U3 = U + sfft_padding_get(&pb->pad,3);

    //sfft_cbr_transpose_b1(T0 +  0,T2 +  0,U0 +  0,U2 +  0);
    //sfft_cbr_transpose_b1(T0 +  4,T2 +  4,U1 +  0,U3 +  0);
    //sfft_cbr_transpose_b1(T0 +  8,T2 +  8,U0 + 24,U2 + 24);
    //sfft_cbr_transpose_b1(T0 + 12,T2 + 12,U1 + 24,U3 + 24);
    //sfft_cbr_transpose_b1(T0 + 16,T2 + 16,U0 +  8,U2 +  8);
    //sfft_cbr_transpose_b1(T0 + 20,T2 + 20,U1 +  8,U3 +  8);

    //sfft_cbr_transpose_b1(T0 + 24,T2 + 24,U0 + 32,U2 + 32);
    //sfft_cbr_transpose_b1(T0 + 28,T2 + 28,U1 + 32,U3 + 32);
    //sfft_cbr_transpose_b1(T0 + 32,T2 + 32,U0 + 16,U2 + 16);
    //sfft_cbr_transpose_b1(T0 + 36,T2 + 36,U1 + 16,U3 + 16);
    //sfft_cbr_transpose_b1(T0 + 40,T2 + 40,U0 + 40,U2 + 40);
    //sfft_cbr_transpose_b1(T0 + 44,T2 + 44,U1 + 40,U3 + 40);

    //sfft_cbr_transpose_b1(T1 +  0,T3 +  0,U0 +  4,U2 +  4);
    //sfft_cbr_transpose_b1(T1 +  4,T3 +  4,U1 +  4,U3 +  4);
    //sfft_cbr_transpose_b1(T1 +  8,T3 +  8,U0 + 28,U2 + 28);
    //sfft_cbr_transpose_b1(T1 + 12,T3 + 12,U1 + 28,U3 + 28);
    //sfft_cbr_transpose_b1(T1 + 16,T3 + 16,U0 + 12,U2 + 12);
    //sfft_cbr_transpose_b1(T1 + 20,T3 + 20,U1 + 12,U3 + 12);

    //sfft_cbr_transpose_b1(T1 + 24,T3 + 24,U0 + 36,U2 + 36);
    //sfft_cbr_transpose_b1(T1 + 28,T3 + 28,U1 + 36,U3 + 36);
    //sfft_cbr_transpose_b1(T1 + 32,T3 + 32,U0 + 20,U2 + 20);
    //sfft_cbr_transpose_b1(T1 + 36,T3 + 36,U1 + 20,U3 + 20);
    //sfft_cbr_transpose_b1(T1 + 40,T3 + 40,U0 + 44,U2 + 44);
    //sfft_cbr_transpose_b1(T1 + 44,T3 + 44,U1 + 44,U3 + 44);




    //    sfft_cbr_transpose_m3_k1(T +  0,T + 16,T + 32,U +  0,U + 24);

    //f_vector *U0 = U;
    //f_vector *U1 = U + L;
    //cout << L << endl;

    sfft_cb_bitreverse_copy_b2_normal(pb,k,T,U);


//    i_ptr stop = 3 << (1 + 1);
//    i_ptr i = 0;
//    for (i_ptr c = 0; i < 12; i++){
//        i_ptr oi = 2*2*sfft_cb_reverse_index_m3(2,1,i);
//        sfft_cbr_transpose_b1(T0 + c,T2 + c,U0 + oi,U1 + oi);
////        cout << i << "  " << oi << endl;
//        c += 4;
//    }
//    
//    for (i_ptr c = 0; i < 24; i++){
//        i_ptr oi = 2*2*sfft_cb_reverse_index_m3(2,1,i);
//        sfft_cbr_transpose_b1(T1 + c,T3 + c,U0 + oi,U1 + oi);
////        cout << i << "  " << oi << endl;
//        c += 4;
//    }


    cout << endl;
//    sfft_pb_print(pb,U,blocks);
    sfft_print_farray((f_word*)U,L,0);



    sfft_free(T);
    sfft_free(U);
#endif






#if 0
    //  FFT Parameters
    int m = 3;
    int k = 3;
    i_ptr L = (i_ptr)m << k;

    //  Get Point Block
    const sfft_block *pb = &sfft_cb_pb_t24;
    cout << "k   = " << k << endl;
    cout << "pbk = " << pb->k << endl;
    k -= pb->k;
    L = (i_ptr)1 << k;
    cout << "L   = " << L << endl;

    //  Compute size
    i_ptr bytes = sfft_pb_size(pb,k);
    cout << "FFT bytes = " << bytes << endl;

    //  Build Table
    sfft_cb_tables tw;
    sfft_cb_tables_init(&tw);
    sfft_cb_tables_ensure_r1(&tw,pb->k,k);
    sfft_cb_tables_ensure_r3(&tw,pb->k,k);


    //  Allocate and generate random data.
    f_vector *A = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    sfft_pb_rand(pb,A,L);

    sfft_pb_print(pb,A,L);


    //  Test
    sfft_pb_forward_1(pb,&tw,A);
    sfft_pb_sqr(pb,A,L);
    sfft_pb_inverse_1(pb,&tw,A);
    sfft_pb_scale(pb,A,L,1. / (L << pb->k));

    //  Print Residual
//    sfft_pb_print(pb,A,L);
    cout << sfft_pb_residual(pb,A,L) << endl;



    //  Free
    sfft_free(A);
    sfft_cb_tables_kill(&tw);
#endif

    cout << endl;
#ifdef _WIN32
    system("pause");
#endif
}







#define sfft_cbr_transpose_m3_k1(   \
    I0,I1,I2,   \
    O0,O1   \
){  \
    ((f_vector*)(O0))[0] = ((const f_vector*)(I0))[0];   \
    ((f_vector*)(O0))[1] = ((const f_vector*)(I0))[1];   \
    ((f_vector*)(O1))[0] = ((const f_vector*)(I0))[2];   \
    ((f_vector*)(O1))[1] = ((const f_vector*)(I0))[3];   \
    \
    ((f_vector*)(O0))[2] = ((const f_vector*)(I1))[0];   \
    ((f_vector*)(O0))[3] = ((const f_vector*)(I1))[1];   \
    ((f_vector*)(O1))[2] = ((const f_vector*)(I1))[2];   \
    ((f_vector*)(O1))[3] = ((const f_vector*)(I1))[3];   \
    \
    ((f_vector*)(O0))[4] = ((const f_vector*)(I2))[0];   \
    ((f_vector*)(O0))[5] = ((const f_vector*)(I2))[1];   \
    ((f_vector*)(O1))[4] = ((const f_vector*)(I2))[2];   \
    ((f_vector*)(O1))[5] = ((const f_vector*)(I2))[3];   \
}
