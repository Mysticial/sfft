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
        f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7;

        _r0 = ((const f_vector*)R)[0];
        _r1 = ((const f_vector*)R)[1];
        _r2 = ((const f_vector*)R)[2];
        _r3 = ((const f_vector*)R)[3];
        _r4 = ((const f_vector*)R)[4];
        _r5 = ((const f_vector*)R)[5];
        _r6 = ((const f_vector*)R)[6];
        _r7 = ((const f_vector*)R)[7];

        T[0] = fv_mergeh(_r0,_r1);
        T[1] = fv_mergel(_r0,_r1);
        T[2] = fv_mergeh(_r2,_r3);
        T[3] = fv_mergel(_r2,_r3);
        T[4] = fv_mergeh(_r4,_r5);
        T[5] = fv_mergel(_r4,_r5);
        T[6] = fv_mergeh(_r6,_r7);
        T[7] = fv_mergel(_r6,_r7);

        T += 8;
        R += 16;
    }while (R < stop);
}
void sfft_cb_irp_to_raw(const f_vector *T,double *R,i_ptr L){
    double *stop = R + L;
    do{
        f_vector _r0,_r1,_r2,_r3,_r4,_r5,_r6,_r7;
        
        _r0 = T[0];
        _r1 = T[1];
        _r2 = T[2];
        _r3 = T[3];
        _r4 = T[4];
        _r5 = T[5];
        _r6 = T[6];
        _r7 = T[7];

        ((f_vector*)R)[0] = fv_mergeh(_r0,_r1);
        ((f_vector*)R)[1] = fv_mergel(_r0,_r1);
        ((f_vector*)R)[2] = fv_mergeh(_r2,_r3);
        ((f_vector*)R)[3] = fv_mergel(_r2,_r3);
        ((f_vector*)R)[4] = fv_mergeh(_r4,_r5);
        ((f_vector*)R)[5] = fv_mergel(_r4,_r5);
        ((f_vector*)R)[6] = fv_mergeh(_r6,_r7);
        ((f_vector*)R)[7] = fv_mergel(_r6,_r7);

        T += 8;
        R += 16;
    }while (R < stop);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
