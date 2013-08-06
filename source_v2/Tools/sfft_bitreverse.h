/* sfft_bitreverse.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 08/31/2011
 * Last Modified    : 08/23/2012
 * 
 * 
 * 
 *      Bit-Reversals
 * 
 *      There's lots of code-duplication in this file. I might sort it out later.
 */

#pragma once
#ifndef _sfft_bitreverse_H
#define _sfft_bitreverse_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Bit Reverse
#if (defined _M_X64) || (defined __x86_64)
#define sfft_bitreverse_m(I,O,bits){    \
    register i_ptr _a0,_a1; \
    \
    _a0 = (I);  \
    \
    _a1 = _a0 >> 32;    \
    _a0 = _a0 << 32;    \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xffff0000ffff0000ull;  \
    _a0 = _a0 & 0x0000ffff0000ffffull;  \
    _a1 >>= 16; \
    _a0 <<= 16; \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xff00ff00ff00ff00ull;  \
    _a0 = _a0 & 0x00ff00ff00ff00ffull;  \
    _a1 >>= 8;  \
    _a0 <<= 8;  \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xf0f0f0f0f0f0f0f0ull;  \
    _a0 = _a0 & 0x0f0f0f0f0f0f0f0full;  \
    _a1 >>= 4;  \
    _a0 <<= 4;  \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xccccccccccccccccull;  \
    _a0 = _a0 & 0x3333333333333333ull;  \
    _a1 >>= 2;  \
    _a0 <<= 2;  \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xaaaaaaaaaaaaaaaaull;  \
    _a0 = _a0 & 0x5555555555555555ull;  \
    _a1 >>= 1;  \
    _a0 <<= 1;  \
    _a0 |= _a1; \
    \
    (O) = _a0 >> (64 - (bits)); \
}
inline i_ptr sfft_bitreverse(i_ptr x,i_ptr bits){
    sfft_bitreverse_m(x,x,bits);
    return x;
}
#else
#define sfft_bitreverse_m(I,O,bits){    \
    register i_ptr _a0,_a1; \
    \
    _a0 = (I);  \
    \
    _a1 = _a0 >> 16;    \
    _a0 = _a0 << 16;    \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xff00ff00; \
    _a0 = _a0 & 0x00ff00ff; \
    _a1 >>= 8;  \
    _a0 <<= 8;  \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xf0f0f0f0; \
    _a0 = _a0 & 0x0f0f0f0f; \
    _a1 >>= 4;  \
    _a0 <<= 4;  \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xcccccccc; \
    _a0 = _a0 & 0x33333333; \
    _a1 >>= 2;  \
    _a0 <<= 2;  \
    _a0 |= _a1; \
    \
    _a1 = _a0 & 0xaaaaaaaa; \
    _a0 = _a0 & 0x55555555; \
    _a1 >>= 1;  \
    _a0 <<= 1;  \
    _a0 |= _a1; \
    \
    (O) = _a0 >> (32 - (bits)); \
}
inline i_ptr sfft_bitreverse(i_ptr x,i_ptr bits){
    sfft_bitreverse_m(x,x,bits);
    return x;
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Radix Reverse
i_ptr sfft_cb_reverse_index_m1(int before,int after,i_ptr index){
    i_ptr bits = before + after;
    sfft_bitreverse_m(index,index,bits);
    return index;
}
i_ptr sfft_cb_reverse_index_m3(int before,int after,i_ptr index){
    i_ptr x = 0;
    for (int i = 0; i < before; i++){
        x <<= 1;
        x |= index & 1;
        index >>= 1;
    }

    x *= 3;
    x += index % 3;
    index /= 3;

    for (int i = 0; i < after; i++){
        x <<= 1;
        x |= index & 1;
        index >>= 1;
    }

    return x;
}
i_ptr sfft_cb_reverse_index_m5(int before,int after,i_ptr index){
    i_ptr x = 0;
    for (int i = 0; i < before; i++){
        x <<= 1;
        x |= index & 1;
        index >>= 1;
    }

    x *= 5;
    x += index % 5;
    index /= 5;

    for (int i = 0; i < after; i++){
        x <<= 1;
        x |= index & 1;
        index >>= 1;
    }

    return x;
}
i_ptr sfft_cb_reverse_index_m7(int before,int after,i_ptr index){
    i_ptr x = 0;
    for (int i = 0; i < before; i++){
        x <<= 1;
        x |= index & 1;
        index >>= 1;
    }

    x *= 7;
    x += index % 7;
    index /= 7;

    for (int i = 0; i < after; i++){
        x <<= 1;
        x |= index & 1;
        index >>= 1;
    }

    return x;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Copy - block by 2
#if f_vk < 2
void sfft_cb_bitreverse_copy_b1_normal(const sfft_block *pb,int k,const f_vector *T,f_vector *U){
    //  Bit-reverse Copy (block by 2)

    int before = pb->k - 1;
    int after  = k - 1;

    //  Get reverse index function pointer.
    i_ptr (*fp_reverse)(int, int, i_ptr);
    fp_reverse = NULL;
    switch (pb->m){
        case 1: fp_reverse = sfft_cb_reverse_index_m1; break;
        case 3: fp_reverse = sfft_cb_reverse_index_m3; break;
        case 5: fp_reverse = sfft_cb_reverse_index_m5; break;
        case 7: fp_reverse = sfft_cb_reverse_index_m7; break;
        default:;
    }

    //  Input Stride
    i_ptr stride_T = (i_ptr)1 << (k - 1);
    i_ptr i0 = 0;
    i_ptr i1 = stride_T;

    //  Output Stride
    i_ptr stride_U = 2 * sizeof(f_word) * pb->m << (pb->k + k - 1);
    stride_U /= sizeof(f_vector);
    f_vector *U0 = U;
    f_vector *U1 = U0 + stride_U;

    //  Iterate sequentially through input. (input point blocks)
    i_ptr i = 0;
    while (i0 < stride_T){
//        cout << i0 << endl;

        //  Get point-blocks
        const f_vector *T0 = T + sfft_padding_get(&pb->pad,i0);
        const f_vector *T1 = T + sfft_padding_get(&pb->pad,i1);
        const f_vector *stop = T0 + pb->vsize;
        const i_ptr shift = 4 >> f_vk;

        //  Iterate within each point-block.
        while (T0 < stop){
            i_ptr oi = shift * fp_reverse(before,after,i);
            sfft_cbr_transpose_b1_normal(T0,T1,U0 + oi,U1 + oi);
//            cout << i << "  " << oi << endl;

            T0 += shift;
            T1 += shift;
            i++;
        }

        //  Increment point-block counters.
        i0++;
        i1++;
    }
}
void sfft_cb_bitreverse_copy_b1_stream(const sfft_block *pb,int k,const f_vector *T,f_vector *U){
    //  Bit-reverse Copy (block by 2)

    int before = pb->k - 1;
    int after  = k - 1;

    //  Get reverse index function pointer.
    i_ptr (*fp_reverse)(int, int, i_ptr);
    fp_reverse = NULL;
    switch (pb->m){
        case 1: fp_reverse = sfft_cb_reverse_index_m1; break;
        case 3: fp_reverse = sfft_cb_reverse_index_m3; break;
        case 5: fp_reverse = sfft_cb_reverse_index_m5; break;
        case 7: fp_reverse = sfft_cb_reverse_index_m7; break;
        default:;
    }

    //  Input Stride
    i_ptr stride_T = (i_ptr)1 << (k - 1);
    i_ptr i0 = 0;
    i_ptr i1 = stride_T;

    //  Output Stride
    i_ptr stride_U = 2 * sizeof(f_word) * pb->m << (pb->k + k - 1);
    stride_U /= sizeof(f_vector);
    f_vector *U0 = U;
    f_vector *U1 = U0 + stride_U;

    //  Iterate sequentially through input. (input point blocks)
    i_ptr i = 0;
    while (i0 < stride_T){
//        cout << i0 << endl;

        //  Get point-blocks
        const f_vector *T0 = T + sfft_padding_get(&pb->pad,i0);
        const f_vector *T1 = T + sfft_padding_get(&pb->pad,i1);
        const f_vector *stop = T0 + pb->vsize;
        const i_ptr shift = 4 >> f_vk;

        //  Iterate within each point-block.
        while (T0 < stop){
            i_ptr oi = shift * fp_reverse(before,after,i);
            sfft_cbr_transpose_b1_stream(T0,T1,U0 + oi,U1 + oi);
//            cout << i << "  " << oi << endl;

            T0 += shift;
            T1 += shift;
            i++;
        }

        //  Increment point-block counters.
        i0++;
        i1++;
    }
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Copy - block by 4
void sfft_cb_bitreverse_copy_b2_normal(const sfft_block *pb,int k,const f_vector *T,f_vector *U){
    //  Bit-reverse Copy (block by 4)

    int before = pb->k - 2;
    int after  = k - 2;

    //  Get reverse index function pointer.
    i_ptr (*fp_reverse)(int, int, i_ptr);
    fp_reverse = NULL;
    switch (pb->m){
        case 1: fp_reverse = sfft_cb_reverse_index_m1; break;
        case 3: fp_reverse = sfft_cb_reverse_index_m3; break;
        case 5: fp_reverse = sfft_cb_reverse_index_m5; break;
        case 7: fp_reverse = sfft_cb_reverse_index_m7; break;
        default:;
    }

    //  Input Stride
    i_ptr stride_T = (i_ptr)1 << (k - 2);
    i_ptr i0 = 0;
    i_ptr i1 = stride_T;
    i_ptr i2 = i1 + stride_T;
    i_ptr i3 = i2 + stride_T;

    //  Output Stride
    i_ptr stride_U = 2 * sizeof(f_word) * pb->m << (pb->k + k - 2);
    stride_U /= sizeof(f_vector);
    f_vector *U0 = U;
    f_vector *U1 = U0 + stride_U;
    f_vector *U2 = U1 + stride_U;
    f_vector *U3 = U2 + stride_U;

    //  Iterate sequentially through input. (input point blocks)
    i_ptr i = 0;
    while (i0 < stride_T){
//        cout << i0 << endl;

        //  Get point-blocks
        const f_vector *T0 = T + sfft_padding_get(&pb->pad,i0);
        const f_vector *T1 = T + sfft_padding_get(&pb->pad,i1);
        const f_vector *T2 = T + sfft_padding_get(&pb->pad,i2);
        const f_vector *T3 = T + sfft_padding_get(&pb->pad,i3);
        const f_vector *stop = T0 + pb->vsize;
        const i_ptr shift = 8 >> f_vk;

        //  Iterate within each point-block.
        while (T0 < stop){
            i_ptr oi = shift * fp_reverse(before,after,i);
            sfft_cbr_transpose_b2_normal(T0,T1,T2,T3,U0 + oi,U1 + oi,U2 + oi,U3 + oi);
//            cout << i << "  " << oi << endl;

            T0 += shift;
            T1 += shift;
            T2 += shift;
            T3 += shift;
            i++;
        }

        //  Increment point-block counters.
        i0++;
        i1++;
        i2++;
        i3++;
    }
}
void sfft_cb_bitreverse_copy_b2_stream(const sfft_block *pb,int k,const f_vector *T,f_vector *U){
    //  Bit-reverse Copy (block by 4)

    int before = pb->k - 2;
    int after  = k - 2;

    //  Get reverse index function pointer.
    i_ptr (*fp_reverse)(int, int, i_ptr);
    fp_reverse = NULL;
    switch (pb->m){
        case 1: fp_reverse = sfft_cb_reverse_index_m1; break;
        case 3: fp_reverse = sfft_cb_reverse_index_m3; break;
        case 5: fp_reverse = sfft_cb_reverse_index_m5; break;
        case 7: fp_reverse = sfft_cb_reverse_index_m7; break;
        default:;
    }

    //  Input Stride
    i_ptr stride_T = (i_ptr)1 << (k - 2);
    i_ptr i0 = 0;
    i_ptr i1 = stride_T;
    i_ptr i2 = i1 + stride_T;
    i_ptr i3 = i2 + stride_T;

    //  Output Stride
    i_ptr stride_U = 2 * sizeof(f_word) * pb->m << (pb->k + k - 2);
    stride_U /= sizeof(f_vector);
    f_vector *U0 = U;
    f_vector *U1 = U0 + stride_U;
    f_vector *U2 = U1 + stride_U;
    f_vector *U3 = U2 + stride_U;

    //  Iterate sequentially through input. (input point blocks)
    i_ptr i = 0;
    while (i0 < stride_T){
//        cout << i0 << endl;

        //  Get point-blocks
        const f_vector *T0 = T + sfft_padding_get(&pb->pad,i0);
        const f_vector *T1 = T + sfft_padding_get(&pb->pad,i1);
        const f_vector *T2 = T + sfft_padding_get(&pb->pad,i2);
        const f_vector *T3 = T + sfft_padding_get(&pb->pad,i3);
        const f_vector *stop = T0 + pb->vsize;
        const i_ptr shift = 8 >> f_vk;

        //  Iterate within each point-block.
        while (T0 < stop){
            i_ptr oi = shift * fp_reverse(before,after,i);
            sfft_cbr_transpose_b2_stream(T0,T1,T2,T3,U0 + oi,U1 + oi,U2 + oi,U3 + oi);
//            cout << i << "  " << oi << endl;

            T0 += shift;
            T1 += shift;
            T2 += shift;
            T3 += shift;
            i++;
        }

        //  Increment point-block counters.
        i0++;
        i1++;
        i2++;
        i3++;
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
