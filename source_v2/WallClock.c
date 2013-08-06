#include <stddef.h>
#include "WallClock.h"

#ifdef _WIN32
wallclock wc_now(){
    wallclock wc;
    wc.val = clock();
    return wc;
}
double wc_time_since(wallclock start){
    wallclock now = wc_now();
    return (double)(now.val - start.val) / CLOCKS_PER_SEC;
}
#else
wallclock wc_now(){
    wallclock wc;
    gettimeofday(&wc.val,NULL);
    return wc;
}
double wc_time_since(wallclock start){
    wallclock now = wc_now();
    unsigned long long isec = (unsigned long long)now.val.tv_sec - (unsigned long long)start.val.tv_sec;
    int usec = now.val.tv_usec - start.val.tv_usec;
    if (usec < 0){
        usec += 1000000;
        isec--;
    }
    return (double)isec + (double)usec * .000001;
}
#endif
