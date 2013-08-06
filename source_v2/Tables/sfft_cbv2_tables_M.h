/* sfft_cb_tables_M_Default.h - Multiplier Twiddle Tables
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/02/2012
 * Last Modified    : 02/02/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      v2      =   Vectorize by 4
 *      tables  =   Twiddle Factor Tables
 * 
 */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static int sfft_cb_table_make(sfft_cb_table *tw,int r,int m,int k){
    if (k < 4)
        k = 4;

    //  Allocate Table
    tw->ptr = (f_vector*)sfft_malloc((i_ptr)r * sizeof(i_ptr) << k,sizeof(f_vector));
    if (tw->ptr == NULL)
        return 1;

    //  First 3 entries are not used.
    tw->table[0] = NULL;
    tw->table[1] = NULL;
    tw->table[2] = NULL;
    tw->table[3] = NULL;

    //  Fill the table
    f_word *T = (f_word*)tw->ptr;
    i_ptr L = (i_ptr)r << k;
    f_word w = -6.2831853071795864769252867665590057683943387987502 * m / L;

    //  Zero unused entries
    for (i_ptr c = 0; c < 8*r; c++){
        T[c] = 0;
    }

    L >>= 1;
    T += L;
    tw->table[k] = (f_vector*)T;
    f_word *T0 = T;
    
    //  Build upper most table.
    L >>= 1;
    for (i_ptr c = 0; c < L;){
        f_word angle;
        f_word r;
        f_word i;

        angle = w * c++;
        r = cos(angle);
        i = sin(angle);
        T0[0] = r;
        T0[4] = i;

        angle = w * c++;
        r = cos(angle);
        i = sin(angle);
        T0[1] = r;
        T0[5] = i;

        angle = w * c++;
        r = cos(angle);
        i = sin(angle);
        T0[2] = r;
        T0[6] = i;

        angle = w * c++;
        r = cos(angle);
        i = sin(angle);
        T0[3] = r;
        T0[7] = i;

        T0 += 8;
    }

    //  Copy to bottom tables.
    while (k > 4){
        f_word *Th = T;
        f_word *stop = T;
        T -= L;
        tw->table[--k] = (f_vector*)T;
        f_word *Tl = T;

        while (Tl < stop){
            Tl[0] = Th[ 0];
            Tl[1] = Th[ 2];
            Tl[2] = Th[ 8];
            Tl[3] = Th[10];
            Tl[4] = Th[ 4];
            Tl[5] = Th[ 6];
            Tl[6] = Th[12];
            Tl[7] = Th[14];

            Tl += 8;
            Th += 16;
        }
        
        L >>= 1;
    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
