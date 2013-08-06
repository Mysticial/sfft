/* Profiles.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 05/16/2011
 * Last Modified    : 05/16/2011
 * 
 * 
 * 
 *      This file contains the type-definitions of all the different modes.
 */

//  Select a Profile
//#define sfft_dp_x86_SSE3
//#define sfft_dp_x86_AVX
//#define sfft_dp_x86_FMA4
//#define sfft_dp_Power7

#pragma once
#ifndef _sfft_Profiles_H
#define _sfft_Profiles_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define     i_ptr       size_t                  //  64-bit integer for pointers and indexes
//#define     i_word      unsigned long long      //  Integer word
typedef unsigned int        uint32;
typedef unsigned long long  uint64;
//#include "InstructionCounters.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  FMA4 - Double Precision (Untested)
#ifdef  sfft_dp_x86_FMA4
#ifdef _M_X64
#define SFFT_ARCH "Double-Precision - x64 FMA4"
#else
#define SFFT_ARCH "Double-Precision - x86 FMA4"
#endif
#include <immintrin.h>
#include <ammintrin.h>
#ifndef WIN32
#include <x86intrin.h>
#endif
#define     f_word                  double              //  Floating-point word
#define     f_vk                    2                   //  2^f_vk = words per vector
#define     f_vector                __m256d             //  Floating-point vector
#define     fv_set1(x)              _mm256_set1_pd(x)
#define     fv_ld1_broadcast(T,p)   (T) = _mm256_broadcast_sd((double*)(p))
#define     fv_add(x,y)             _mm256_add_pd(x,y)
#define     fv_sub(x,y)             _mm256_sub_pd(x,y)
#define     fv_mul(x,y)             _mm256_mul_pd(x,y)
#define     fv_pma(a,b,c)           _mm256_macc_pd(a,b,c)
#define     fv_pms(a,b,c)           _mm256_msub_pd(a,b,c)
//#define     fv_nma(a,b,c)           _mm256_nmacc_pd(a,b,c)
//#define     fv_nms(a,b,c)           _mm256_nmsub_pd(a,b,c)
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  AVX - Double Precision
#ifdef  sfft_dp_x86_AVX
#ifdef _M_X64
#define SFFT_ARCH "Double-Precision - x64 AVX"
#else
#define SFFT_ARCH "Double-Precision - x86 AVX"
#endif
#include <immintrin.h>
#define     f_word                  double              //  Floating-point word
#define     f_vk                    2                   //  2^f_vk = words per vector
#define     f_vector                __m256d             //  Floating-point vector
#define     fv_set1(x)              _mm256_set1_pd(x)
#define     fv_ld1_broadcast(T,p)   (T) = _mm256_broadcast_sd((double*)(p))
#define     fv_add(x,y)             _mm256_add_pd(x,y)
#define     fv_sub(x,y)             _mm256_sub_pd(x,y)
#define     fv_mul(x,y)             _mm256_mul_pd(x,y)
#define     fv_pma(a,b,c)           _mm256_add_pd(_mm256_mul_pd(a,b),c)
#define     fv_pms(a,b,c)           _mm256_sub_pd(_mm256_mul_pd(a,b),c)
//#define     fv_nma(a,b,c)           _mm256_sub_pd(c,_mm256_mul_pd(a,b))
//#define     fv_nms(a,b,c)           _mm256_sub_pd(_mm256_sub_pd(_mm256_setzero_pd(),c),_mm256_mul_pd(a,b))
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  AVX - Single Precision (Not yet supported)
#ifdef  sfft_sp_x86_AVX
#ifdef _M_X64
#define SFFT_ARCH "Single-Precision - x64 AVX"
#else
#define SFFT_ARCH "Single-Precision - x86 AVX"
#endif
#include <immintrin.h>
#define     f_word                  float               //  Floating-point word
#define     f_vk                    3                   //  2^f_vk = words per vector
#define     f_vector                __m256              //  Floating-point vector
#define     fv_set1(x)              _mm256_set1_ps(x)
#define     fv_add(x,y)             _mm256_add_ps(x,y)
#define     fv_sub(x,y)             _mm256_sub_ps(x,y)
#define     fv_mul(x,y)             _mm256_mul_ps(x,y)
#define     fv_pma(a,b,c)           _mm256_add_ps(_mm256_mul_ps(a,b),c)
#define     fv_pms(a,b,c)           _mm256_sub_ps(_mm256_mul_ps(a,b),c)
//#define     fv_nma(a,b,c)           _mm256_sub_ps(c,_mm256_mul_ps(a,b))
//#define     fv_nms(a,b,c)           _mm256_sub_ps(_mm256_sub_ps(_mm256_setzero_ps(),c),_mm256_mul_ps(a,b))
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  SSE3 - Double Precision
#ifdef  sfft_dp_x86_SSE3
#ifdef _M_X64
#define SFFT_ARCH "Double-Precision - x64 SSE3"
#else
#define SFFT_ARCH "Double-Precision - x86 SSE3"
#endif
//#define sFFT_REGISTERS          32
//#define sfft_cb_tg_r4p_UNROLL  0
#include <pmmintrin.h>
#define     f_word                  double              //  Floating-point word
#define     f_vk                    1                   //  2^f_vk = words per vector
#define     f_vector                __m128d             //  Floating-point vector
#define     fv_set1(x)              _mm_set1_pd(x)
#define     fv_ld1_broadcast(T,p)   (T) = _mm_loaddup_pd((double*)(p))

#ifndef SFFT_STRIP_COMPUTATION
#define     fv_add(x,y)             _mm_add_pd(x,y)
#define     fv_sub(x,y)             _mm_sub_pd(x,y)
#define     fv_mul(x,y)             _mm_mul_pd(x,y)
#define     fv_pma(a,b,c)           _mm_add_pd(_mm_mul_pd(a,b),c)
#define     fv_pms(a,b,c)           _mm_sub_pd(_mm_mul_pd(a,b),c)
#define     fv_hadd(x,y)            _mm_hadd_pd(x,y)
#define     fv_hsub(x,y)            _mm_hsub_pd(x,y)
#define     fv_unpacklo(x,y)        _mm_unpacklo_pd(x,y)
#define     fv_unpackhi(x,y)        _mm_unpackhi_pd(x,y)
#define     fv_shuffle(x,y,i)       _mm_shuffle_pd(x,y,i)
#define     fv_xor(x,y)             _mm_xor_pd(x,y)
#else
#define     fv_add(x,y)             (x)
#define     fv_sub(x,y)             (y)
#define     fv_mul(x,y)             (x)
#define     fv_pma(a,b,c)           (b)
#define     fv_pms(a,b,c)           (c)
#define     fv_hadd(x,y)            (x)
#define     fv_hsub(x,y)            (y)
#define     fv_unpacklo(x,y)        (x)
#define     fv_unpackhi(x,y)        (y)
#define     fv_shuffle(x,y,i)       (y)
#define     fv_xor(x,y)             (x)
#endif

#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  SSE3 - Single Precision (Not yet supported)
#ifdef  sfft_sp_x86_SSE3
#ifdef _M_X64
#define SFFT_ARCH "Single-Precision - x64 SSE3"
#else
#define SFFT_ARCH "Single-Precision - x86 SSE3"
#endif
#include <pmmintrin.h>
#define     f_word                  float               //  Floating-point word
#define     f_vk                    2                   //  2^f_vk = words per vector
#define     f_vector                __m128              //  Floating-point vector
#define     fv_set1(x)              _mm_set1_ps(x)
#define     fv_add(x,y)             _mm_add_ps(x,y)
#define     fv_sub(x,y)             _mm_sub_ps(x,y)
#define     fv_mul(x,y)             _mm_mul_ps(x,y)
#define     fv_pma(a,b,c)           _mm_add_ps(_mm_mul_ps(a,b),c)
#define     fv_pms(a,b,c)           _mm_sub_ps(_mm_mul_ps(a,b),c)
//#define     fv_nma(a,b,c)           _mm_sub_ps(c,_mm_mul_ps(a,b))
//#define     fv_nms(a,b,c)           _mm_sub_ps(_mm_sub_ps(_mm_setzero_ps(),c),_mm_mul_ps(a,b))
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Power7 - Double Precision
#ifdef  sfft_dp_Power7
#define SFFT_ARCH "Double-Precision - Power7 AltiVec"
#define sFFT_REGISTERS          32
#define sfft_cb_tg_r4p_UNROLL  0
#include <altivec.h>
#define     f_word                  double              //  Floating-point word
#define     f_vk                    1                   //  2^f_vk = words per vector
#define     f_vector                vector double
#define     fv_ld1_broadcast(T,p)   (T) = vec_splats(*(double*)(p))

#ifndef SFFT_STRIP_COMPUTATION
#define     fv_add(x,y)             vec_add(x,y)
#define     fv_sub(x,y)             vec_sub(x,y)
#define     fv_mul(x,y)             vec_mul(x,y)
#define     fv_pma(a,b,c)           vec_madd(a,b,c)
#define     fv_pms(a,b,c)           vec_msub(a,b,c)
//#define     fv_nma(a,b,c)           vec_nmadd(a,b,c)
//#define     fv_nms(a,b,c)           vec_nmsub(a,b,c)
#define     fv_mergeh(x,y)          vec_mergeh(x,y)
#define     fv_mergel(x,y)          vec_mergel(x,y)
#define     fv_xor(x,y)             vec_xor(x,y)
#ifdef __GNUC__
#define     fv_perm1(x,y)           vec_perm(x,y,(vector unsigned char){ 0, 1, 2, 3, 4, 5, 6, 7,24,25,26,27,28,29,30,31})
#define     fv_perm2(x,y)           vec_perm(x,y,(vector unsigned char){ 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23})
#else
#define     fv_perm1(x,y)           vec_permi(x,y,1)
#define     fv_perm2(x,y)           vec_permi(x,y,2)
#endif
#else
#define     fv_add(x,y)             (x)
#define     fv_sub(x,y)             (y)
#define     fv_mul(x,y)             (x)
#define     fv_pma(a,b,c)           (b)
#define     fv_pms(a,b,c)           (c)
#define     fv_hadd(x,y)            (x)
#define     fv_hsub(x,y)            (y)
#define     fv_mergeh(x,y)          (x)
#define     fv_mergel(x,y)          (y)
#define     fv_xor(x,y)             (x)
#define     fv_perm1(x,y)           (y)
#define     fv_perm2(x,y)           (x)
#endif
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Default - Double Precision
#ifndef f_vector
#define SFFT_ARCH "Double-Precision - Default"
#define sfft_dp_Default
#define     f_word                  double              //  Floating-point word
#define     f_vk                    0                   //  2^f_vk = words per vector
#define     f_vector                double
#define     fv_set1(x)              (x)
#define     fv_ld1_broadcast(T,p)   (T) = *(double*)(p)
#define     fv_add(x,y)             ((x) + (y))
#define     fv_sub(x,y)             ((x) - (y))
#define     fv_mul(x,y)             ((x) * (y))
#define     fv_pma(a,b,c)           ((a) * (b) + (c))
#define     fv_pms(a,b,c)           ((a) * (b) - (c))
//#define     fv_nma(a,b,c)           ((c) - (a) * (b))
//#define     fv_nms(a,b,c)           (-(a) * (b) - (c))
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
