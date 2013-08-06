/* sfft_cb_tables_M.c - Multiplier Twiddle Tables
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/02/2012
 * Last Modified    : 02/02/2012
 * 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../sfft_malloc.h"
#include "sfft_cb_tables_M_headers.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#if f_vk == 0
#include "sfft_cbv0_tables_M.h"
#elif f_vk == 1
#include "sfft_cbv1_tables_M.h"
#elif f_vk == 2
#include "sfft_cbv2_tables_M.h"
#else
#error "Vector Size Not Supported"
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void sfft_cb_table_init(sfft_cb_table *tw){
    tw->ptr = NULL;
    tw->m = 0;
    tw->k = 0;
}
void sfft_cb_table_kill(sfft_cb_table *tw){
    sfft_free(tw->ptr);
    tw->ptr = NULL;
    tw->k = 0;
}
void sfft_cb_tables_init(sfft_cb_tables *tw){
    memset(&tw->w1,0,sizeof(tw->w1));
    tw->w1[1] = &tw->r1_1;
    tw->w2[1] = &tw->r1_2;
    tw->w3[1] = &tw->r1_3;
    tw->w1[3] = &tw->r3_1;
    tw->w2[3] = &tw->r3_2;
    tw->w3[3] = &tw->r3_3;
    tw->w1[5] = &tw->r5_1;
    tw->w2[5] = &tw->r5_2;
    tw->w3[5] = &tw->r5_3;
    tw->w1[7] = &tw->r7_1;
    tw->w2[7] = &tw->r7_2;
    tw->w3[7] = &tw->r7_3;

    sfft_cb_table_init(&tw->r1_1);
    sfft_cb_table_init(&tw->r1_2);
    sfft_cb_table_init(&tw->r1_3);

    sfft_cb_table_init(&tw->r3_1);
    sfft_cb_table_init(&tw->r3_2);
    sfft_cb_table_init(&tw->r3_3);

    sfft_cb_table_init(&tw->r5_1);
    sfft_cb_table_init(&tw->r5_2);
    sfft_cb_table_init(&tw->r5_3);
    sfft_cb_table_init(&tw->r5_4);

    sfft_cb_table_init(&tw->r7_1);
    sfft_cb_table_init(&tw->r7_2);
    sfft_cb_table_init(&tw->r7_3);
    sfft_cb_table_init(&tw->r7_4);
    sfft_cb_table_init(&tw->r7_5);
    sfft_cb_table_init(&tw->r7_6);
}
void sfft_cb_tables_kill(sfft_cb_tables *tw){
    sfft_cb_table_kill(&tw->r1_1);
    sfft_cb_table_kill(&tw->r1_2);
    sfft_cb_table_kill(&tw->r1_3);

    sfft_cb_table_kill(&tw->r3_1);
    sfft_cb_table_kill(&tw->r3_2);

    sfft_cb_table_kill(&tw->r5_1);
    sfft_cb_table_kill(&tw->r5_2);
    sfft_cb_table_kill(&tw->r5_3);
    sfft_cb_table_kill(&tw->r5_4);

    sfft_cb_table_kill(&tw->r7_1);
    sfft_cb_table_kill(&tw->r7_2);
    sfft_cb_table_kill(&tw->r7_3);
    sfft_cb_table_kill(&tw->r7_4);
    sfft_cb_table_kill(&tw->r7_5);
    sfft_cb_table_kill(&tw->r7_6);
}
int sfft_cb_tables_ensure_r1(sfft_cb_tables *tw,int pbk,int k){
    k += pbk;

    if (k <= tw->r1_1.k)
        return 0;

    sfft_cb_table_kill(&tw->r1_1);
    sfft_cb_table_kill(&tw->r1_2);
    sfft_cb_table_kill(&tw->r1_3);

    int ret = 0;
    ret |= sfft_cb_table_make(&tw->r1_1,1,1,k);
    ret |= sfft_cb_table_make(&tw->r1_2,1,2,k);
    ret |= sfft_cb_table_make(&tw->r1_3,1,3,k);

    if (ret == 0)
        return 0;
    
    sfft_cb_table_kill(&tw->r1_1);
    sfft_cb_table_kill(&tw->r1_2);
    sfft_cb_table_kill(&tw->r1_3);
    return ret;
}
int sfft_cb_tables_ensure_r3(sfft_cb_tables *tw,int pbk,int k){
    k += pbk;

    if (k <= tw->r3_1.k)
        return 0;

    sfft_cb_table_kill(&tw->r3_1);
    sfft_cb_table_kill(&tw->r3_2);
    sfft_cb_table_kill(&tw->r3_3);

    int ret = 0;
    ret |= sfft_cb_table_make(&tw->r3_1,3,1,k);
    ret |= sfft_cb_table_make(&tw->r3_2,3,2,k);
    ret |= sfft_cb_table_make(&tw->r3_3,3,3,k);

    if (ret == 0)
        return 0;
    
    sfft_cb_table_kill(&tw->r3_1);
    sfft_cb_table_kill(&tw->r3_2);
    sfft_cb_table_kill(&tw->r3_3);
    return ret;
}
int sfft_cb_tables_ensure_r5(sfft_cb_tables *tw,int pbk,int k){
    k += pbk;

    if (k <= tw->r5_1.k)
        return 0;

    sfft_cb_table_kill(&tw->r5_1);
    sfft_cb_table_kill(&tw->r5_2);
    sfft_cb_table_kill(&tw->r5_3);
    sfft_cb_table_kill(&tw->r5_4);

    int ret = 0;
    ret |= sfft_cb_table_make(&tw->r5_1,5,1,k);
    ret |= sfft_cb_table_make(&tw->r5_2,5,2,k);
    ret |= sfft_cb_table_make(&tw->r5_3,5,3,k);
    ret |= sfft_cb_table_make(&tw->r5_4,5,4,pbk);

    if (ret == 0)
        return 0;
    
    sfft_cb_table_kill(&tw->r5_1);
    sfft_cb_table_kill(&tw->r5_2);
    sfft_cb_table_kill(&tw->r5_3);
    sfft_cb_table_kill(&tw->r5_4);
    return ret;
}
int sfft_cb_tables_ensure_r7(sfft_cb_tables *tw,int pbk,int k){
    k += pbk;

    if (k <= tw->r7_1.k)
        return 0;

    sfft_cb_table_kill(&tw->r7_1);
    sfft_cb_table_kill(&tw->r7_2);
    sfft_cb_table_kill(&tw->r7_3);
    sfft_cb_table_kill(&tw->r7_4);
    sfft_cb_table_kill(&tw->r7_5);
    sfft_cb_table_kill(&tw->r7_6);

    int ret = 0;
    ret |= sfft_cb_table_make(&tw->r7_1,7,1,k);
    ret |= sfft_cb_table_make(&tw->r7_2,7,2,k);
    ret |= sfft_cb_table_make(&tw->r7_3,7,3,k);
    ret |= sfft_cb_table_make(&tw->r7_4,7,4,pbk);
    ret |= sfft_cb_table_make(&tw->r7_5,7,5,pbk);
    ret |= sfft_cb_table_make(&tw->r7_6,7,6,pbk);

    if (ret == 0)
        return 0;
    
    sfft_cb_table_kill(&tw->r7_1);
    sfft_cb_table_kill(&tw->r7_2);
    sfft_cb_table_kill(&tw->r7_3);
    sfft_cb_table_kill(&tw->r7_4);
    sfft_cb_table_kill(&tw->r7_5);
    sfft_cb_table_kill(&tw->r7_6);
    return ret;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
