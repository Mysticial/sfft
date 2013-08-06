/* sfft_pb_object.h - Point Block Object
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 03/01/2011
 * Last Modified    : 04/13/2012
 * 
 */

#pragma once
#ifndef _sfft_pb_object_H
#define _sfft_pb_object_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
typedef struct sfft_cb_tables sfft_cb_tables;
typedef struct{
    //  Size of the block in vectors.
    i_ptr vsize;

    //  Transform length of the block.
    int m;
    int k;

    //  End-point Function pointers
    void (*fp_forward)(const sfft_cb_tables *tw,f_vector *I,f_vector *O);
    void (*fp_inverse)(const sfft_cb_tables *tw,f_vector *I,f_vector *O);

    //  Padding
    sfft_padding pad;
} sfft_block;
inline  static  i_ptr   sfft_pb_size    (const sfft_block *pb,int k);
        static  void    sfft_pb_rand    (const sfft_block *pb,f_vector *T,i_ptr L);
        static  void    sfft_pb_print   (const sfft_block *pb,const f_vector *T,i_ptr L);
        static  void    sfft_pb_sqr     (const sfft_block *pb,f_vector *T,i_ptr L);
        static  void    sfft_pb_scale   (const sfft_block *pb,f_vector *T,i_ptr L,f_word scale);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Inlines
static void sfft_pb_rand_internal(const sfft_block *pb,f_vector *T,i_ptr index){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    f_word *t = (f_word*)(T + sfft_padding_get(&pb->pad,index));

    f_word *stop = t + 2*L;
    i_ptr i = 2*L * index;
    while (t < stop){
        *t++ = (f_word)(i * i % 71);
        i++;
    }
}
static void sfft_pb_print_internal(const sfft_block *pb,const f_vector *T,i_ptr index){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    T += sfft_padding_get(&pb->pad,index);
    sfft_print_farray((const f_word*)T,L,1);
}
static void sfft_pb_sqr_internal(const sfft_block *pb,f_vector *T,i_ptr index){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    T += sfft_padding_get(&pb->pad,index);

    f_vector *stop = T + pb->vsize;
    while (T < stop){
        f_vector r = T[0];
        f_vector i = T[1];

        T[0] = fv_sub(fv_mul(r,r),fv_mul(i,i));
        i = fv_mul(r,i);
        T[1] = fv_add(i,i);

        T += 2;
    }
}
static void sfft_pb_scale_internal(const sfft_block *pb,f_vector *T,i_ptr index,f_vector scale){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    T += sfft_padding_get(&pb->pad,index);

    f_vector *stop = T + pb->vsize;
    while (T < stop){
        T[0] = fv_mul(T[0],scale);
        T++;
    }
}
static f_word sfft_pb_residual_internal(const sfft_block *pb,const f_vector *T,i_ptr index){
    i_ptr L = pb->vsize * sizeof(f_vector) / (2 * sizeof(f_word));
    const f_word *t = (const f_word*)(T + sfft_padding_get(&pb->pad,index));

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
inline static i_ptr sfft_pb_size(const sfft_block *pb,int k){
    return sfft_padding_get(&pb->pad,(i_ptr)1 << k) * sizeof(f_vector);
}
static void sfft_pb_rand(const sfft_block *pb,f_vector *T,i_ptr L){
    for (i_ptr i = 0; i < L; i++){
        sfft_pb_rand_internal(pb,T,i);
    }
}
static void sfft_pb_print(const sfft_block *pb,const f_vector *T,i_ptr L){
    for (i_ptr i = 0; i < L; i++){
        sfft_pb_print_internal(pb,T,i);
    }
}
static void sfft_pb_sqr(const sfft_block *pb,f_vector *T,i_ptr L){
    for (i_ptr i = 0; i < L; i++){
        sfft_pb_sqr_internal(pb,T,i);
    }
}
static void sfft_pb_scale(const sfft_block *pb,f_vector *T,i_ptr L,f_word scale){
    f_vector SCALE = fv_set1(scale);
    for (i_ptr i = 0; i < L; i++){
        sfft_pb_scale_internal(pb,T,i,SCALE);
    }
}
static f_word sfft_pb_residual(const sfft_block *pb,f_vector *T,i_ptr L){
    f_word residual = 0;
    for (i_ptr i = 0; i < L; i++){
        f_word r = sfft_pb_residual_internal(pb,T,i);
        if (residual < r)
            residual = r;
    }

    return residual;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
