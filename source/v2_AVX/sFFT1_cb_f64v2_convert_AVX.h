/* sfft_cb_convert.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 05/26/2011
 * Last Modified    : 05/26/2011
 *
 */

#pragma once
#ifndef _sfft_cb_convert_H
#define _sfft_cb_convert_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void sfft_cb_raw_to_irp(f_vector *T,const double *R,i_ptr L){
    const double *stop = R + L;
    do{
        __m256d _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB;

        _r0 = _mm256_loadu_pd(R +  0);
        _r1 = _mm256_loadu_pd(R +  4);
        _r2 = _mm256_loadu_pd(R +  8);
        _r3 = _mm256_loadu_pd(R + 12);
        _r4 = _mm256_loadu_pd(R + 16);
        _r5 = _mm256_loadu_pd(R + 20);
        _r6 = _mm256_loadu_pd(R + 24);
        _r7 = _mm256_loadu_pd(R + 28);
        
        _r8 = _mm256_permute2f128_pd(_r0,_r1,32);
        _r0 = _mm256_permute2f128_pd(_r0,_r1,49);
        _r9 = _mm256_permute2f128_pd(_r2,_r3,32);
        _r2 = _mm256_permute2f128_pd(_r2,_r3,49);
        _rA = _mm256_permute2f128_pd(_r4,_r5,32);
        _r4 = _mm256_permute2f128_pd(_r4,_r5,49);
        _rB = _mm256_permute2f128_pd(_r6,_r7,32);
        _r6 = _mm256_permute2f128_pd(_r6,_r7,49);

        _r1 = _mm256_unpacklo_pd(_r8,_r0);
        _r8 = _mm256_unpackhi_pd(_r8,_r0);
        _r3 = _mm256_unpacklo_pd(_r9,_r2);
        _r9 = _mm256_unpackhi_pd(_r9,_r2);
        _r5 = _mm256_unpacklo_pd(_rA,_r4);
        _rA = _mm256_unpackhi_pd(_rA,_r4);
        _r7 = _mm256_unpacklo_pd(_rB,_r6);
        _rB = _mm256_unpackhi_pd(_rB,_r6);

        T[0] = _r1;
        T[1] = _r8;
        T[2] = _r3;
        T[3] = _r9;
        T[4] = _r5;
        T[5] = _rA;
        T[6] = _r7;
        T[7] = _rB;

        T += 8;
        R += 32;
    }while (R < stop);
}
void sfft_cb_irp_to_raw(const f_vector *T,double *R,i_ptr L){
    double *stop = R + L;
    do{
        __m256d _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7,_r8,_r9,_rA,_rB;
        
        _r0 = T[0];
        _r1 = T[1];
        _r2 = T[2];
        _r3 = T[3];
        _r4 = T[4];
        _r5 = T[5];
        _r6 = T[6];
        _r7 = T[7];
        
        _r8 = _mm256_unpacklo_pd(_r0,_r1);
        _r0 = _mm256_unpackhi_pd(_r0,_r1);
        _r9 = _mm256_unpacklo_pd(_r2,_r3);
        _r2 = _mm256_unpackhi_pd(_r2,_r3);
        _rA = _mm256_unpacklo_pd(_r4,_r5);
        _r4 = _mm256_unpackhi_pd(_r4,_r5);
        _rB = _mm256_unpacklo_pd(_r6,_r7);
        _r6 = _mm256_unpackhi_pd(_r6,_r7);
        
        _r1 = _mm256_permute2f128_pd(_r8,_r0,32);
        _r8 = _mm256_permute2f128_pd(_r8,_r0,49);
        _r3 = _mm256_permute2f128_pd(_r9,_r2,32);
        _r9 = _mm256_permute2f128_pd(_r9,_r2,49);
        _r5 = _mm256_permute2f128_pd(_rA,_r4,32);
        _rA = _mm256_permute2f128_pd(_rA,_r4,49);
        _r7 = _mm256_permute2f128_pd(_rB,_r6,32);
        _rB = _mm256_permute2f128_pd(_rB,_r6,49);

        _mm256_storeu_pd(R +  0,_r1);
        _mm256_storeu_pd(R +  4,_r8);
        _mm256_storeu_pd(R +  8,_r3);
        _mm256_storeu_pd(R + 12,_r9);
        _mm256_storeu_pd(R + 16,_r5);
        _mm256_storeu_pd(R + 20,_rA);
        _mm256_storeu_pd(R + 24,_r7);
        _mm256_storeu_pd(R + 28,_rB);

        T += 8;
        R += 32;
    }while (R < stop);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
