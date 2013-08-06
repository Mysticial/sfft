/* DebugPrinting.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/04/2010
 * Last Modified    : 09/09/2010
 * 
 */

#include <stdio.h>

#pragma once
#ifndef _sfft_DebugPrinting_H
#define _sfft_DebugPrinting_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void sfft_print_fvector(f_vector x){
#if f_vk == 2
    cout << ((double*)&x)[0] << "  " << ((double*)&x)[1] << "  " << ((double*)&x)[2] << "  " << ((double*)&x)[3] << endl;
#elif f_vk == 1
    cout << ((double*)&x)[0] << "  " << ((double*)&x)[1] << endl;
#elif f_vk == 0
    cout << ((double*)&x)[0] << endl;
#else
#error "No Vector Size Specified."
#endif
}
void sfft_print_complex(f_word r,f_word i);
//void sfft_print_complex(f_word r,f_word i){
//    cout << r;
//    if (i < 0)
//        cout << " - " << -i << "i";
//    else
//        cout << " + " << i << "i";
//}
void sfft_print_sum(f_word *T,i_ptr L){
    f_word sum = 0;
    f_word *stop = T + 2*L;
    while (T < stop){
        sum += *T++;
    }
    cout << sum << endl;
}
////////////////////////////////////////////////////////////////////////////////
void sfft_print_array(f_word *T,i_ptr L,int comma = 0){
    //  Print function for non-vectorized array.

    if (L == 0){
        if (comma)
            printf("{},\n");
        else
            printf("{}\n");
        return;
    }

    f_word *stopT = T + L;
    {
        printf("{");
//        sfft_print_complex(T[0],T[1]);
        cout << T[0];
        T++;
    }


    while (T < stopT){
        printf(",");
        cout << T[0];
        T++;
    }
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
void sfft_print_farray_v0(f_word *T,i_ptr L,int comma = 0){
    //  Print function for non-vectorized array.

    if (L == 0){
        if (comma)
            printf("{},\n");
        else
            printf("{}\n");
        return;
    }

    f_word *stopT = T + 2*L;
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
void sfft_print_farray_v1(f_word *T,i_ptr L,int comma = 0){
    //  Print function for an array vectorized to 2 words per vector.
    //  L must be a multiple of 2.

    if (L == 0){
        if (comma)
            printf("{},\n");
        else
            printf("{}\n");
        return;
    }

    f_word *stopT = T + 2*L;
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
void sfft_print_farray_v2(f_word *T,i_ptr L,int comma = 0){
    //  Print function for an array vectorized to 4 words per vector.
    //  L must be a multiple of 4.

    if (L == 0){
        if (comma)
            printf("{},\n");
        else
            printf("{}\n");
        return;
    }

    f_word *stopT = T + 2*L;
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
#if f_vk == 2
#define sfft_print_farray    sfft_print_farray_v2
#elif f_vk == 1
#define sfft_print_farray    sfft_print_farray_v1
#elif f_vk == 0
#define sfft_print_farray    sfft_print_farray_v0
#else
#error "No Vector Size Specified."
#endif
////////////////////////////////////////////////////////////////////////////////
void sfft_print_farray2_v0(f_word *T,i_ptr x,i_ptr y,int comma = 0){
    printf("{\n");
    i_ptr c = 0;
    while (c++ < y){
        printf("    ");
        sfft_print_farray_v0(T,x,c != y);
        T += 2 * x;
    }
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
void sfft_print_farray2_v1(f_word *T,i_ptr x,i_ptr y,int comma = 0){
    printf("{\n");
    i_ptr c = 0;
    while (c++ < y){
        printf("    ");
        sfft_print_farray_v1(T,x,c != y);
        T += 2 * x;
    }
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
////////////////////////////////////////////////////////////////////////////////
void sfft_print_farray3_v0(f_word *T,i_ptr x,i_ptr y,i_ptr z,int comma = 0){
    printf("{\n");
    i_ptr c = 0;
    while (c++ < z){
        printf("    ");
        sfft_print_farray2_v0(T,x,y,c != z);
        T += 2 * x * y;
    }
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
void sfft_print_farray3_v1(f_word *T,i_ptr x,i_ptr y,i_ptr z,int comma = 0){
    printf("{\n");
    i_ptr c = 0;
    while (c++ < z){
        printf("    ");
        sfft_print_farray2_v1(T,x,y,c != z);
        T += 2 * x * y;
    }
    if (comma)
        printf("},\n");
    else
        printf("}\n");
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
