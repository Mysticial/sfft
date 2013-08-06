/* TwiddleTable.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 09/06/2010
 * Last Modified    : 09/06/2010
 * 
 */

#pragma once
#ifndef _sfft_TwiddleTable_H
#define _sfft_TwiddleTable_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void sfft_table_kill(sfft_table *T){
    sfft_free(T->P);
}
void sfft_tables_kill(sfft_tables *T){
    if (T == NULL)
        return;
    sfft_table_kill(&T->w1);
    sfft_table_kill(&T->w2);
    sfft_table_kill(&T->w3);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  1 word per vector (no vectorization)
#if f_vk == 0
void sfft_table_make(sfft_table *T,i_ptr k,i_ptr multiplier){
    if (k < 2)
        k = 2;

    T->k = k;

    i_ptr bytes = sizeof(f_word) << k;

    T->P = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    if (T->P == NULL){
        printf("Memory Allocation Failure\n");
//        cout << "Attempted to allocate: " << bytes << " bytes" << endl;
#ifdef _WIN32
        system("pause");
#endif
        exit(1);
    }

    f_word *table = (f_word*)T->P;

    T->w[0] = NULL;
    T->w[1] = NULL;
    table[0] = 0;
    table[1] = 0;

    i_ptr current_k = 2;
    while (current_k <= k){
        f_word *current_table = (f_word*)(table + ((i_ptr)1 << (current_k - 1)));
        T->w[current_k] = (f_vector*)current_table;

        i_ptr L = (i_ptr)1 << current_k;
        f_word w = -(f_word)3.1415926535897932384626433832795028841971693993751 * multiplier / (f_word)L;

        L >>= 1;
        i_ptr c = 0;
        while (c < L){
            f_word current_w = w * c;

            current_table[c + 0] = cos(current_w);
            current_table[c + 1] = sin(current_w);

            c += 2;
        }

        current_k++;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  2 words per vector
#elif f_vk == 1
void sfft_table_make(sfft_table *T,i_ptr k,i_ptr multiplier){
    if (k < 3)
        k = 3;

    T->k = k;

    i_ptr bytes = sizeof(f_word) << k;

    T->P = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    if (T->P == NULL){
        printf("Memory Allocation Failure\n");
//        cout << "Attempted to allocate: " << bytes << " bytes" << endl;
#ifdef _WIN32
        system("pause");
#endif
        exit(1);
    }

    f_word *table = (f_word*)T->P;

    T->w[0] = NULL;
    T->w[1] = NULL;
    T->w[2] = NULL;
    table[0] = 0;
    table[1] = 0;
    table[2] = 0;
    table[3] = 0;

    i_ptr current_k = 3;
    while (current_k <= k){
        f_word *current_table = (f_word*)(table + ((i_ptr)1 << (current_k - 1)));
        T->w[current_k] = (f_vector*)current_table;

        i_ptr L = (i_ptr)1 << current_k;
        f_word w = -(f_word)3.1415926535897932384626433832795028841971693993751 * multiplier / (f_word)L;

        L >>= 1;
        i_ptr c = 0;
        while (c < L){
            f_word current_w = w * c;
            current_table[c + 0] = cos(current_w);
            current_table[c + 2] = sin(current_w);

            current_w = w * (c + 2);
            current_table[c + 1] = cos(current_w);
            current_table[c + 3] = sin(current_w);

            c += 4;
        }

        current_k++;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  4 words per vector
#elif f_vk == 2
void sfft_table_make(sfft_table *T,i_ptr k,i_ptr multiplier){
    if (k < 4)
        k = 4;

    T->k = k;

    i_ptr bytes = sizeof(f_word) << k;

    T->P = (f_vector*)sfft_malloc(bytes,sizeof(f_vector));
    if (T->P == NULL){
        printf("Memory Allocation Failure\n");
//        cout << "Attempted to allocate: " << bytes << " bytes" << endl;
#ifdef _WIN32
        system("pause");
#endif
        exit(1);
    }

    f_word *table = (f_word*)T->P;

    T->w[0] = NULL;
    T->w[1] = NULL;
    T->w[2] = NULL;
    T->w[3] = NULL;
    table[0] = 0;
    table[1] = 0;
    table[2] = 0;
    table[3] = 0;
    table[4] = 0;
    table[5] = 0;
    table[6] = 0;
    table[7] = 0;

    i_ptr current_k = 4;
    while (current_k <= k){
        f_word *current_table = (f_word*)(table + ((i_ptr)1 << (current_k - 1)));
        T->w[current_k] = (f_vector*)current_table;

        i_ptr L = (i_ptr)1 << current_k;
        f_word w = -(f_word)3.1415926535897932384626433832795028841971693993751 * multiplier / (f_word)L;

        L >>= 1;
        i_ptr c = 0;
        while (c < L){
            f_word current_w = w * c;
            current_table[c + 0] = cos(current_w);
            current_table[c + 4] = sin(current_w);

            current_w = w * (c + 2);
            current_table[c + 1] = cos(current_w);
            current_table[c + 5] = sin(current_w);

            current_w = w * (c + 4);
            current_table[c + 2] = cos(current_w);
            current_table[c + 6] = sin(current_w);

            current_w = w * (c + 6);
            current_table[c + 3] = cos(current_w);
            current_table[c + 7] = sin(current_w);

            c += 8;
        }

        current_k++;
    }
}
#else
#error "Unsupported Vector Size."
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
