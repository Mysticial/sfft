#include <stdlib.h>
#include "Globals.h"
#include "sfft_malloc.h"

#ifdef __cplusplus
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#endif

//DLL_EXTERN
void* sfft_malloc(i_ptr bytes,i_ptr align){
    //  This function allocates memory that is aligned to at least "align" bytes.
    //  Otherwise, it behaves the same as malloc().
    //  The pointer returned by this function MUST be freed by "sfft_free".

    //  "align" MUST be a power of two

    if (align < sizeof(i_ptr))
        align = sizeof(i_ptr);

//#ifdef __cplusplus
//    cout << "Allocating: " << bytes << endl;
//    system("pause");
//#endif

    void *ptr = malloc((size_t)(bytes + align + sizeof(i_ptr)));
    if (ptr == NULL)
        return NULL;

    i_ptr *ret = (i_ptr*)((((i_ptr)ptr + sizeof(i_ptr)) & ~(i_ptr)(align - 1)) + align);

    ret[-1] = (i_ptr)ptr;

    return ret;
}
//DLL_EXTERN
void sfft_free(void *ptr){
    if (ptr == NULL)
        return;

    ptr = (void*)(((i_ptr*)ptr)[-1]);

    free(ptr);
}
