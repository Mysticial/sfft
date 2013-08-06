/* Globals.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/03/2012
 * Last Modified    : 02/03/2012
 * 
 */

#pragma once
#ifndef _sfft_Globals_H
#define _sfft_Globals_H
#ifdef __cplusplus
extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dynamic Linking
#if (defined _WIN32)
#ifdef DLL_BUILD_CORE
#define DLL_EXTERN      __declspec(dllexport)
#else
#define DLL_EXTERN      __declspec(dllimport)
#endif
#elif (defined __GNUC__)
#define DLL_EXTERN      __attribute__ ((visibility("default")))
#else
#define DLL_EXTERN      extern
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Profiles
#include "Profiles.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Memory Alocation
void*   sfft_malloc             (i_ptr bytes,i_ptr align);
void    sfft_free               (void *ptr);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
