#include <stdio.h>

//#ifdef __cplusplus
//#include <iostream>
//using std::cin;
//using std::cout;
//using std::endl;
//#endif

#include "Debuggers.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void sfft_rand_complex(f_word *T,i_ptr L,i_ptr shift){
    f_word *stop = T + 2*L;
    i_ptr i = 2*L * shift;
    while (T < stop){
        *T++ = (f_word)(i * i % 17);
        i++;
    }
}
void sfft_print_complex(f_word r,f_word i){
    printf("%g",r);
    if (i < 0){
        printf(" - %g i",-i);
    }else{
        printf(" + %g i",i);
    }
}
void sfft_print_farray_v0(const f_word *T,i_ptr L,int comma){
    //  Print function for non-vectorized array.

    if (L == 0){
        if (comma)
            printf("{},\n");
        else
            printf("{}\n");
        return;
    }

    const f_word *stopT = T + 2*L;
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
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
void sfft_print_farray_v1(const f_word *T,i_ptr L,int comma){
    //  Print function for an array vectorized to 2 words per vector.
    //  L must be a multiple of 2.

    if (L == 0){
        if (comma)
            printf("{},\n");
        else
            printf("{}\n");
        return;
    }

    const f_word *stopT = T + 2*L;
    {
        printf("{");
        sfft_print_complex(T[0],T[2]);
        printf(", ");
        sfft_print_complex(T[1],T[3]);
        T += 4;
    }


    while (T < stopT){
        printf(", ");
        sfft_print_complex(T[0],T[2]);
        printf(", ");
        sfft_print_complex(T[1],T[3]);
        T += 4;
    }
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
void sfft_print_farray_v2(const f_word *T,i_ptr L,int comma){
    //  Print function for an array vectorized to 4 words per vector.
    //  L must be a multiple of 4.

    if (L == 0){
        if (comma)
            printf("{},\n");
        else
            printf("{}\n");
        return;
    }

    const f_word *stopT = T + 2*L;
    {
        printf("{");
        sfft_print_complex(T[0],T[4]);
        printf(", ");
        sfft_print_complex(T[1],T[5]);
        printf(", ");
        sfft_print_complex(T[2],T[6]);
        printf(", ");
        sfft_print_complex(T[3],T[7]);
        T += 8;
    }


    while (T < stopT){
        printf(", ");
        sfft_print_complex(T[0],T[4]);
        printf(", ");
        sfft_print_complex(T[1],T[5]);
        printf(", ");
        sfft_print_complex(T[2],T[6]);
        printf(", ");
        sfft_print_complex(T[3],T[7]);
        T += 8;
    }
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
void sfft_print_farray(const f_word *T,i_ptr L,int comma){
#if f_vk == 2
    sfft_print_farray_v2(T,L,comma);
#elif f_vk == 1
    sfft_print_farray_v1(T,L,comma);
#elif f_vk == 0
    sfft_print_farray_v0(T,L,comma);
#else
#error "No Vector Size Specified."
#endif
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void sfft_cb_sqr(f_vector *T,i_ptr L){
    f_vector *stop = T + (2*L >> f_vk);
    while (T < stop){
        f_vector r = T[0];
        f_vector i = T[1];

        T[0] = fv_sub(fv_mul(r,r),fv_mul(i,i));
        i = fv_mul(r,i);
        T[1] = fv_add(i,i);

        T += 2;
    }
}
void sfft_cb_scale(f_vector *T,i_ptr L,f_word scale){
    f_vector SCALE = fv_set1(scale);

    f_vector *stop = T + (2*L >> f_vk);
    while (T < stop){
        T[0] = fv_mul(T[0],SCALE);
        T++;
    }
}
f_word sfft_cb_residual(const f_vector *T,i_ptr L){
    const f_word *t = (const f_word*)(T);

    f_word residual = 0;
    
    const f_word *stop = t + 2*L;
    while (t < stop){
        f_word r = t[0];
        if (r < 0)
            r = -r;

        long long i = (long long)(r + 0.5);
        r -= (f_word)i;
        if (r < 0)
            r = -r;

        if (residual < r)
            residual = r;

        t++;
    }

    return residual;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
