/* sfft_cb_f64v2_AVX.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/31/2011
 * Last Modified    : 03/31/2011
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v2_AVX_H
#define _sfft_cb_f64v2_AVX_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "sfft_cb_f64v2_convert_AVX.h"
#include "sfft_cb_f64v2_bitreverse_AVX.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Generic
#include "../vk_Generic/sfft_cb_tg_b2.h"
#include "../vk_Generic/sfft_cb_tg_b4.h"
#include "../vk_Generic/sfft_cb_tg_r2.h"
#include "../vk_Generic/sfft_cb_tg_r4.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Butterflies + End Points
#include "sfft_cb_f64v2_t16_AVX.h"
#include "sfft_cb_f64v2_t32_AVX.h"
#include "sfft_cb_f64v2_t64_AVX.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_i_cb_t2()
#define sfft_i_cb_t4_forward()
#define sfft_i_cb_t4_inverse()
#define sfft_i_cb_t8_forward()
#define sfft_i_cb_t8_inverse()
#define sfft_i_cb_t16_forward      sfft_cb_f64v2_t16_forward_AVX
#define sfft_i_cb_t16_inverse      sfft_cb_f64v2_t16_inverse_AVX
#define sfft_i_cb_t32_forward      sfft_cb_f64v2_t32_forward_AVX
#define sfft_i_cb_t32_inverse      sfft_cb_f64v2_t32_inverse_AVX
#define sfft_i_cb_t64_forward      sfft_cb_f64v2_t64_forward_AVX
#define sfft_i_cb_t64_inverse      sfft_cb_f64v2_t64_inverse_AVX
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
