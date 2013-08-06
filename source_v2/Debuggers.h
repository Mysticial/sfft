/* Debuggers.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/03/2012
 * Last Modified    : 02/03/2012
 * 
 */

#pragma once
#ifndef _Debuggers_H
#define _Debuggers_H
#ifdef __cplusplus
extern "C" {
#endif
#include "Globals.h"
#include "Profiles.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void    sfft_rand_complex   (f_word *T,i_ptr L,i_ptr shift);
void    sfft_print_complex  (f_word r,f_word i);
void    sfft_print_farray   (const f_word *T,i_ptr L,int comma);
////////////////////////////////////////////////////////////////////////////////
void    sfft_cb_sqr        (f_vector *T,i_ptr L);
void    sfft_cb_scale      (f_vector *T,i_ptr L,f_word scale);
f_word  sfft_cb_residual   (const f_vector *T,i_ptr L);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif