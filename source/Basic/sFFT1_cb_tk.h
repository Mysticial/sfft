/* sfft_cb_tk.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 10/06/2010
 * Last Modified    : 06/02/2011
 * 
 * 
 * 
 *      cb          =   Complex Bit-reversed Transform
 *      tk          =   Transform of size 2^k
 */

#pragma once
#ifndef _sfft_cb_tk_H
#define _sfft_cb_tk_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  End Points
void sfft_cb_t16_forward(const sfft_tables *tw,f_vector *T){
    sfft_i_cb_t16_forward(T,tw);
}
void sfft_cb_t16_inverse(const sfft_tables *tw,f_vector *T){
    sfft_i_cb_t16_inverse(T,tw);
}
void sfft_cb_t32_forward(const sfft_tables *tw,f_vector *T){
    sfft_i_cb_t32_forward(T,tw);
}
void sfft_cb_t32_inverse(const sfft_tables *tw,f_vector *T){
    sfft_i_cb_t32_inverse(T,tw);
}
void sfft_cb_t64_forward(const sfft_tables *tw,f_vector *T){
    sfft_i_cb_t64_forward(T,tw);
}
void sfft_cb_t64_inverse(const sfft_tables *tw,f_vector *T){
    sfft_i_cb_t64_inverse(T,tw);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Generic
void sfft_cb_tk_f1_forward(const sfft_tables *tw,f_vector *T,int k){
    if (k < 4){
        printf("Minimum transform size is 16.\n");
        exit(1);
    }
    if (k == 4){
        sfft_cb_t16_forward(tw,T);
        return;
    }
    if (k == 5){
        sfft_cb_t32_forward(tw,T);
        return;
    }
    if (k == 6){
        sfft_cb_t64_forward(tw,T);
        return;
    }

    //  Row Reduction
    register i_ptr is = 0;
    register i_ptr ie = 2 * (i_ptr)sizeof(f_word) << ((k) - 2);
    sfft_i_cb_r4_forward(T,k,tw,is,ie);

    //  Sub-Transforms
    k -= 2;
    i_ptr block = (i_ptr)2 << (k - f_vk);
    sfft_cb_tk_f1_forward(tw,T + block * 0,k);
    sfft_cb_tk_f1_forward(tw,T + block * 1,k);
    sfft_cb_tk_f1_forward(tw,T + block * 2,k);
    sfft_cb_tk_f1_forward(tw,T + block * 3,k);
}
void sfft_cb_tk_f1_inverse(const sfft_tables *tw,f_vector *T,int k){
    if (k < 4){
        printf("Minimum transform size is 16.\n");
        exit(1);
    }
    if (k == 4){
        sfft_cb_t16_inverse(tw,T);
        return;
    }
    if (k == 5){
        sfft_cb_t32_inverse(tw,T);
        return;
    }
    if (k == 6){
        sfft_cb_t64_inverse(tw,T);
        return;
    }
    
    //  Sub-Transforms
    k -= 2;
    i_ptr block = (i_ptr)2 << (k - f_vk);
    sfft_cb_tk_f1_inverse(tw,T + block * 0,k);
    sfft_cb_tk_f1_inverse(tw,T + block * 1,k);
    sfft_cb_tk_f1_inverse(tw,T + block * 2,k);
    sfft_cb_tk_f1_inverse(tw,T + block * 3,k);

    //  Row Reduction
    k += 2;
    register i_ptr is = 0;
    register i_ptr ie = 2 * (i_ptr)sizeof(f_word) << ((k) - 2);
    sfft_i_cb_r4_inverse(T,k,tw,is,ie);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
