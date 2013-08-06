/* sfft_cb_f64v1_Power7.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 06/02/2011
 * Last Modified    : 06/02/2011
 * 
 */

#pragma once
#ifndef _sfft_cb_f64v1_Power7_H
#define _sfft_cb_f64v1_Power7_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include "sfft_cb_f64v1_convert_Power7.h"
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
#include "sfft_cb_f64v1_t2_Power7.h"
#include "sfft_cb_f64v1_t4_Power7.h"
#include "sfft_cb_f64v1_t8_Power7.h"
#include "sfft_cb_f64v1_t16_Power7.h"
#include "sfft_cb_f64v1_t32_Power7.h"
#include "sfft_cb_f64v1_t64_Power7.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define sfft_i_cb_t2               sfft_cb_f64v1_t2_Power7
#define sfft_i_cb_t4_forward       sfft_cb_f64v1_t4_forward_Power7
#define sfft_i_cb_t4_inverse       sfft_cb_f64v1_t4_inverse_Power7
#define sfft_i_cb_t8_forward       sfft_cb_f64v1_t8_forward_Power7
#define sfft_i_cb_t8_inverse       sfft_cb_f64v1_t8_inverse_Power7
#define sfft_i_cb_t16_forward      sfft_cb_f64v1_t16_forward_Power7
#define sfft_i_cb_t16_inverse      sfft_cb_f64v1_t16_inverse_Power7
#define sfft_i_cb_t32_forward      sfft_cb_f64v1_t32_forward_Power7
#define sfft_i_cb_t32_inverse      sfft_cb_f64v1_t32_inverse_Power7
#define sfft_i_cb_t64_forward      sfft_cb_f64v1_t64_forward_Power7
#define sfft_i_cb_t64_inverse      sfft_cb_f64v1_t64_inverse_Power7
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
