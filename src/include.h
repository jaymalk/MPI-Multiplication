
/*
 * Including libraries, for avoiding repetitive include.
 */

#ifndef __INCLUDE
#define __INCLUDE

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <omp.h>
#include <pthread.h>
#include <unistd.h>

#ifdef __linux__
#define      __stderrp stderr
#define      __stdoutp stdout
#define      __stdinp  stdin
#define      uint16_t  u_int16_t
#endif


/*
 * Default file access permissions for new files.
 */
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#endif