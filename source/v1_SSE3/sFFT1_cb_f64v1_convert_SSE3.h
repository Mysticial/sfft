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
        __m128d _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7;

        _r0 = _mm_loadu_pd(R +  0);
        _r1 = _mm_loadu_pd(R +  2);
        _r2 = _mm_loadu_pd(R +  4);
        _r3 = _mm_loadu_pd(R +  6);

        T[0] = fv_unpacklo(_r0,_r1);
        _r4 = _mm_loadu_pd(R +  8);
        T[1] = fv_unpackhi(_r0,_r1);
        _r5 = _mm_loadu_pd(R + 10);
        T[2] = fv_unpacklo(_r2,_r3);
        _r6 = _mm_loadu_pd(R + 12);
        T[3] = fv_unpackhi(_r2,_r3);
        _r7 = _mm_loadu_pd(R + 14);

        T[4] = fv_unpacklo(_r4,_r5);
        T[5] = fv_unpackhi(_r4,_r5);
        T[6] = fv_unpacklo(_r6,_r7);
        T[7] = fv_unpackhi(_r6,_r7);

        T += 8;
        R += 16;
    }while (R < stop);
}
void sfft_cb_irp_to_raw(const f_vector *T,double *R,i_ptr L){
    double *stop = R + L;
    do{
        __m128d _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7;
        
        _r0 = T[0];
        _r1 = T[1];
        _r2 = T[2];
        _r3 = T[3];

        _mm_storeu_pd(R +  0,fv_unpacklo(_r0,_r1));
        _r4 = T[4];
        _mm_storeu_pd(R +  2,fv_unpackhi(_r0,_r1));
        _r5 = T[5];
        _mm_storeu_pd(R +  4,fv_unpacklo(_r2,_r3));
        _r6 = T[6];
        _mm_storeu_pd(R +  6,fv_unpackhi(_r2,_r3));
        _r7 = T[7];

        _mm_storeu_pd(R +  8,fv_unpacklo(_r4,_r5));
        _mm_storeu_pd(R + 10,fv_unpackhi(_r4,_r5));
        _mm_storeu_pd(R + 12,fv_unpacklo(_r6,_r7));
        _mm_storeu_pd(R + 14,fv_unpackhi(_r6,_r7));

        T += 8;
        R += 16;
    }while (R < stop);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
