/* BitReverse.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 08/31/2011
 * Last Modified    : 08/31/2011
 * 
 * 
 * 
 *      Bit-Reversals
 */

#pragma once
#ifndef _sfft_BitReverse_H
#define _sfft_BitReverse_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
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
i_ptr sfft_bitreverse(i_ptr x,i_ptr bits){
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
i_ptr sfft_bitreverse(i_ptr x,i_ptr bits){
    sfft_bitreverse_m(x,x,bits);
    return x;
}
#endif
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
