/* sfft.h
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
 *      FMA4 - Linux        :   gcc "" -lm -mfma4 -O2 -D "sfft_dp_x86_FMA4"
 * 
 */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <omp.h>

#include "Globals.h"
#include "Tools/DataTypes.h"

#pragma once
#ifndef _sfft_H
#define _sfft_H
#ifdef __cplusplus
extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Debuggers
void    sfft_cb_1D_print_fwords (f_word *T,i_ptr L);
void    sfft_rand               (f_word *T,i_ptr L,i_ptr shift);
i_ptr   sfft_bitreverse         (i_ptr x,i_ptr bits);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Twiddle Factor Tables
typedef struct{
    int k1;     //  Current size: 1 * 2^k
    int k3;     //  Current size: 3 * 2^k
    int k5;     //  Current size: 5 * 2^k
    int k7;     //  Current size: 7 * 2^k

    sfft_tables *tw1;   //  Table: 1 * 2^k
    sfft_tables *tw3;   //  Table: 3 * 2^k
    sfft_tables *tw5;   //  Table: 5 * 2^k
    sfft_tables *tw7;   //  Table: 7 * 2^k

    sfft_block pb1;    //  Tuning + Padding settings.
    sfft_block pb3;    //  Tuning + Padding settings.
    sfft_block pb5;    //  Tuning + Padding settings.
    sfft_block pb7;    //  Tuning + Padding settings.
} sfft_table_t0;
////////////////////////////////////////////////////////////////////////////////
DLL_EXTERN  void    sfft_table_t0_init          (sfft_table_t0 *tw);            //  Initialize the table.
DLL_EXTERN  void    sfft_table_t0_kill          (sfft_table_t0 *tw);            //  Destroy the table and free its memory.
////////////////////////////////////////////////////////////////////////////////
DLL_EXTERN  int     sfft_table_t0_build         (sfft_table_t0 *tw,i_ptr L);    //  Build a table that can do an FFT size of L. Returns non-zero when FFT size is not supported.
DLL_EXTERN  void    sfft_table_t0_ensure_f1     (sfft_table_t0 *tw,int k);      //  Ensure that table is large enough for a size 1 * 2^k FFT.
//DLL_EXTERN  void    sfft_table_t0_ensure_f3     (sfft_table_t0 *tw,int k);      //  Ensure that table is large enough for a size 3 * 2^k FFT.
//DLL_EXTERN  void    sfft_table_t0_ensure_f5     (sfft_table_t0 *tw,int k);      //  Ensure that table is large enough for a size 5 * 2^k FFT.
//DLL_EXTERN  void    sfft_table_t0_ensure_f7     (sfft_table_t0 *tw,int k);      //  Ensure that table is large enough for a size 7 * 2^k FFT.
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Complex Transforms
DLL_EXTERN  int     sfft_cb_1D_t0_pointwise_sqr     (sfft_table_t0 *tw,f_vector *T,i_ptr L);
DLL_EXTERN  void    sfft_cb_1D_t0f1_pointwise_sqr   (sfft_table_t0 *tw,f_vector *,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f3_pointwise_sqr   (sfft_table_t0 *tw,f_vector *,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f5_pointwise_sqr   (sfft_table_t0 *tw,f_vector *,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f7_pointwise_sqr   (sfft_table_t0 *tw,f_vector *,int k);
DLL_EXTERN  int     sfft_cb_1D_t0_pointwise_scale   (sfft_table_t0 *tw,f_vector *T,i_ptr L,f_word scale);
DLL_EXTERN  void    sfft_cb_1D_t0f1_pointwise_scale (sfft_table_t0 *tw,f_vector *,int k,f_word scale);
//DLL_EXTERN  void    sfft_cb_1D_t0f3_pointwise_scale (sfft_table_t0 *tw,f_vector *,int k,f_word scale);
//DLL_EXTERN  void    sfft_cb_1D_t0f5_pointwise_scale (sfft_table_t0 *tw,f_vector *,int k,f_word scale);
//DLL_EXTERN  void    sfft_cb_1D_t0f7_pointwise_scale (sfft_table_t0 *tw,f_vector *,int k,f_word scale);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Buffer Sizes
DLL_EXTERN  i_ptr   sfft_cb_1D_t0_Tbytes        (sfft_table_t0 *tw,i_ptr L);    //  Returns the buffer size needed for an FFT of size L. Returns -1 when FFT size is not supported.
DLL_EXTERN  i_ptr   sfft_cb_1D_t0f1_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for an FFT of size 1 * 2^k FFT.
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0f3_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for an FFT of size 3 * 2^k FFT.
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0f5_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for an FFT of size 5 * 2^k FFT.
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0f7_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for an FFT of size 7 * 2^k FFT.
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Copy padding - Copy data to and from the padded format used by this library.
DLL_EXTERN  int     sfft_cb_1D_t0_raw_to_padded     (const sfft_table_t0 *tw,f_vector *T,const double *raw,i_ptr L);    //  Returns non-zero when FFT size is not supported.
DLL_EXTERN  void    sfft_cb_1D_t0f1_raw_to_padded   (const sfft_table_t0 *tw,f_vector *T,const double *raw,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f3_raw_to_padded   (const sfft_table_t0 *tw,f_vector *T,const double *raw,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f5_raw_to_padded   (const sfft_table_t0 *tw,f_vector *T,const double *raw,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f7_raw_to_padded   (const sfft_table_t0 *tw,f_vector *T,const double *raw,int k);
DLL_EXTERN  int     sfft_cb_1D_t0_padded_to_raw     (const sfft_table_t0 *tw,const f_vector *T,double *raw,i_ptr L);    //  Returns non-zero when FFT size is not supported.
DLL_EXTERN  void    sfft_cb_1D_t0f1_padded_to_raw   (const sfft_table_t0 *tw,const f_vector *T,double *raw,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f3_padded_to_raw   (const sfft_table_t0 *tw,const f_vector *T,double *raw,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f5_padded_to_raw   (const sfft_table_t0 *tw,const f_vector *T,double *raw,int k);
//DLL_EXTERN  void    sfft_cb_1D_t0f7_padded_to_raw   (const sfft_table_t0 *tw,const f_vector *T,double *raw,int k);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Indexing function for accessing bit-reversed frequency domain.
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0_index     (const sfft_table_t0 *tw,i_ptr L,i_ptr index);  //  Returns -1 when FFT size is not supported.
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0f1_index   (const sfft_table_t0 *tw,int k,i_ptr index);
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0f3_index   (const sfft_table_t0 *tw,int k,i_ptr index);
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0f5_index   (const sfft_table_t0 *tw,int k,i_ptr index);
//DLL_EXTERN  i_ptr   sfft_cb_1D_t0f7_index   (const sfft_table_t0 *tw,int k,i_ptr index);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (Any Length) - Returns non-zero if the table does not support the requested FFT size.
DLL_EXTERN  int     sfft_b_1D_cb_t0_forward     (const sfft_table_t0 *tw,f_vector *T,i_ptr L);          //  Forward transform
DLL_EXTERN  int     sfft_b_1D_cb_t0_inverse     (const sfft_table_t0 *tw,f_vector *T,i_ptr L);          //  Inverse transform
//DLL_EXTERN  int     sfft_p_1D_cb_t0_forward     (const sfft_table_t0 *tw,f_vector *T,i_ptr L,int tds);  //  Forward transform   (multi-threaded)
//DLL_EXTERN  int     sfft_p_1D_cb_t0_inverse     (const sfft_table_t0 *tw,f_vector *T,i_ptr L,int tds);  //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 1 * 2^k)
DLL_EXTERN  void    sfft_b_1D_cb_t0f1_forward  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Forward transform
DLL_EXTERN  void    sfft_b_1D_cb_t0f1_inverse  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_cb_t0f1_forward  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_cb_t0f1_inverse  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 3 * 2^k)
//DLL_EXTERN  void    sfft_b_1D_cb_t0f3_forward  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Forward transform
//DLL_EXTERN  void    sfft_b_1D_cb_t0f3_inverse  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_cb_t0f3_forward  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_cb_t0f3_inverse  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 5 * 2^k)
//DLL_EXTERN  void    sfft_b_1D_cb_t0f5_forward  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Forward transform
//DLL_EXTERN  void    sfft_b_1D_cb_t0f5_inverse  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_cb_t0f5_forward  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_cb_t0f5_inverse  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 7 * 2^k)
//DLL_EXTERN  void    sfft_b_1D_cb_t0f7_forward  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Forward transform
//DLL_EXTERN  void    sfft_b_1D_cb_t0f7_inverse  (const sfft_table_t0 *tw,f_vector *T,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_cb_t0f7_forward  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_cb_t0f7_inverse  (const sfft_table_t0 *tw,f_vector *T,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Real Transforms
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Buffer Sizes
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0_Tbytes        (sfft_table_t0 *tw,i_ptr L);    //  Returns the buffer size needed for a complex->real FFT of size L. Returns -1 when FFT size is not supported.
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f1_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for a complex->real FFT of size 1 * 2^k FFT.
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f3_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for a complex->real FFT of size 3 * 2^k FFT.
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f5_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for a complex->real FFT of size 5 * 2^k FFT.
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f7_Tbytes      (sfft_table_t0 *tw,int k);      //  Returns the buffer size needed for a complex->real FFT of size 7 * 2^k FFT.
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Copy padding - Copy data to and from the padded format used by this library.

//  TBA...

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Indexing function for accessing bit-reversed frequency domain.
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0_index     (const sfft_table_t0 *tw,i_ptr L,i_ptr index);  //  Returns -1 when FFT size is not supported.
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f1_index   (const sfft_table_t0 *tw,int k,i_ptr index);
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f3_index   (const sfft_table_t0 *tw,int k,i_ptr index);
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f5_index   (const sfft_table_t0 *tw,int k,i_ptr index);
//DLL_EXTERN  i_ptr   sfft_rb_1D_t0f7_index   (const sfft_table_t0 *tw,int k,i_ptr index);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (Any Length) - Returns non-zero if the table does not support the requested FFT size.
//DLL_EXTERN  int     sfft_b_1D_rb_t0_forward     (const sfft_table_t0 *tw,f_vector *R,f_vector *C,i_ptr L);          //  Forward transform
//DLL_EXTERN  int     sfft_b_1D_rb_t0_inverse     (const sfft_table_t0 *tw,f_vector *R,f_vector *C,i_ptr L);          //  Inverse transform
//DLL_EXTERN  int     sfft_p_1D_rb_t0_forward     (const sfft_table_t0 *tw,f_vector *R,f_vector *C,i_ptr L,int tds);  //  Forward transform   (multi-threaded)
//DLL_EXTERN  int     sfft_p_1D_rb_t0_inverse     (const sfft_table_t0 *tw,f_vector *R,f_vector *C,i_ptr L,int tds);  //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 1 * 2^k)
//DLL_EXTERN  void    sfft_b_1D_rb_t0f1_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Forward transform
//DLL_EXTERN  void    sfft_b_1D_rb_t0f1_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_rb_t0f1_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_rb_t0f1_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 3 * 2^k)
//DLL_EXTERN  void    sfft_b_1D_rb_t0f3_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Forward transform
//DLL_EXTERN  void    sfft_b_1D_rb_t0f3_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_rb_t0f3_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_rb_t0f3_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 5 * 2^k)
//DLL_EXTERN  void    sfft_b_1D_rb_t0f5_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Forward transform
//DLL_EXTERN  void    sfft_b_1D_rb_t0f5_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_rb_t0f5_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_rb_t0f5_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
//  1D Complex Bit-reversed FFT (length = 7 * 2^k)
//DLL_EXTERN  void    sfft_b_1D_rb_t0f7_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Forward transform
//DLL_EXTERN  void    sfft_b_1D_rb_t0f7_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k);            //  Inverse transform
//DLL_EXTERN  void    sfft_p_1D_rb_t0f7_forward   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Forward transform   (multi-threaded)
//DLL_EXTERN  void    sfft_p_1D_rb_t0f7_inverse   (const sfft_table_t0 *tw,f_vector *R,f_vector *C,int k,int tds);    //  Inverse transform   (multi-threaded)
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
