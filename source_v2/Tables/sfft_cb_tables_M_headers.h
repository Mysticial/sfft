/* sfft_cb_tables_M.h - Multiplier Twiddle Tables
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/02/2012
 * Last Modified    : 02/02/2012
 * 
 */

#pragma once
#ifndef _sfft_cb_tables_M_H
#define _sfft_cb_tables_M_H
#ifdef __cplusplus
extern "C" {
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <limits.h>
#include "../Globals.h"
#include "../Profiles.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef struct{
    f_vector *ptr;                              //  Base pointer of the table
    f_vector *table[CHAR_BIT * sizeof(i_ptr)];  //  Pointer to each sub-table
    int m;                                      //  Multiplier of the table: 1, 3, 5, or 7
    int k;                                      //  Size of the table = m * 2^k
} sfft_cb_table;
typedef struct sfft_cb_tables{
    sfft_cb_table *w1[8];
    sfft_cb_table *w2[8];
    sfft_cb_table *w3[8];

    //  1 * 2^k
    sfft_cb_table r1_1;
    sfft_cb_table r1_2;
    sfft_cb_table r1_3;

    //  3 * 2^k
    sfft_cb_table r3_1;
    sfft_cb_table r3_2;
    sfft_cb_table r3_3;

    //  5 * 2^k
    sfft_cb_table r5_1;
    sfft_cb_table r5_2;
    sfft_cb_table r5_3;
    sfft_cb_table r5_4;

    //  7 * 2^k
    sfft_cb_table r7_1;
    sfft_cb_table r7_2;
    sfft_cb_table r7_3;
    sfft_cb_table r7_4;
    sfft_cb_table r7_5;
    sfft_cb_table r7_6;
} sfft_cb_tables;
void sfft_cb_tables_init(sfft_cb_tables *tw);
void sfft_cb_tables_kill(sfft_cb_tables *tw);
int sfft_cb_tables_ensure_r1(sfft_cb_tables *tw,int pbk,int k);
int sfft_cb_tables_ensure_r3(sfft_cb_tables *tw,int pbk,int k);
int sfft_cb_tables_ensure_r5(sfft_cb_tables *tw,int pbk,int k);
int sfft_cb_tables_ensure_r7(sfft_cb_tables *tw,int pbk,int k);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
#endif
