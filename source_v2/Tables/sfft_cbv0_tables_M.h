/* sfft_cb_tables_M_Default.h - Multiplier Twiddle Tables
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 02/02/2012
 * Last Modified    : 02/02/2012
 * 
 * 
 * 
 *      cb      =   Complex Bit-reversed Transform
 *      v0      =   Vectorize by 1
 *      tables  =   Twiddle Factor Tables
 * 
 */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
static int sfft_cb_table_make(sfft_cb_table *tw,int r,int m,int k){
    if (k < 2)
        k = 2;

    //  Allocate Table
    tw->ptr = (f_vector*)sfft_malloc((i_ptr)r * sizeof(i_ptr) << k,sizeof(f_vector));
    if (tw->ptr == NULL)
        return 1;

    //  First 2 entries are not used.
    tw->table[0] = NULL;
    tw->table[1] = NULL;

    //  Fill the table
    f_word *T = (f_word*)tw->ptr;
    i_ptr L = (i_ptr)r << k;
    f_word w = -6.2831853071795864769252867665590057683943387987502 * m / L;

    //  Zero unused entries
    for (i_ptr c = 0; c < 2*r; c++){
        T[c] = 0;
    }

    L >>= 1;
    T += L;
    tw->table[k] = (f_vector*)T;
    f_word *T0 = T;
    
    //  Build upper most table.
    L >>= 1;
    for (i_ptr c = 0; c < L; c++){
        f_word angle = w * c;
        f_word r = cos(angle);
        f_word i = sin(angle);

        T0[0] = r;
        T0[1] = i;

        T0 += 2;
    }

    //  Copy to bottom tables.
    while (k > 2){
        f_word *Th = T;
        f_word *stop = T;
        T -= L;
        tw->table[--k] = (f_vector*)T;
        f_word *Tl = T;

        while (Tl < stop){
            Tl[0] = Th[0];
            Tl[1] = Th[1];

            Tl += 2;
            Th += 4;
        }
        
        L >>= 1;
    }

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
