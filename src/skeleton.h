

#ifndef __SKELETON__
#define __SKELETON__

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#ifdef __linux__
    #define      __stderrp stderr
    #define      __stdoutp stdout
    #define      __stdinp  stdin
    #define      uint16_t  u_int16_t
#endif

int IsEqual(float *, float *, int, int);

void Matrix_Multiply(float *, float *, float *, int , int, int);

#endif /*__SKELETON__*/