/* AlignedMalloc.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/06/2010
 * Last Modified    : 09/06/2010
 * 
 * 
 * 
 *      This file implements an aligned malloc() function.
 *          This is needed to ensure that floating-point arrays are sufficiently
 *          aligned to use SSE instructions.
 *
 */

#include <stdlib.h>

#pragma once
#ifndef _AlignedMalloc_H
#define _AlignedMalloc_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void* sfft_malloc(i_ptr bytes,i_ptr align){
    //  This function allocates memory that is aligned to at least "align" bytes.
    //  Otherwise, it behaves the same as malloc().
    //  The pointer returned by this function MUST be freed by "sfft_free".

    //  "align" MUST be a power of two

    if (align < sizeof(i_ptr))
        align = sizeof(i_ptr);

    void *ptr = malloc((size_t)(bytes + align + sizeof(i_ptr)));
    if (ptr == NULL)
        return NULL;

    i_ptr *ret = (i_ptr*)((((i_ptr)ptr + sizeof(i_ptr)) & ~(i_ptr)(align - 1)) + align);

    ret[-1] = (i_ptr)ptr;

    return ret;
}
void sfft_free(void *ptr){
    if (ptr == NULL)
        return;

    ptr = (void*)(((i_ptr*)ptr)[-1]);

    free(ptr);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
