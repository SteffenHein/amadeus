/*[ file: amdwrk.c ] */
# define DO_AMDWRK "amdwrk(*)"
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function amdwrk(*)                                                          *
*  Here is where the numerical computations are done                           *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: February 01, 2022 ]                            <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 1 /* some headers of the POSIX.1 standard will be used */
# define _ISOC99_SOURCE 1
/*----------------------------------------------------------------------------*/
# define INNER_MAXIMA 1
/*----------------------------------------------------------------------------*/
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <string.h>
# include <ctype.h>
# include <time.h>            /* cf. time( ),ctime( ),asctime( ),localtime( ) */
/*----------------------------------------------------------------------------*/
# if _ISOC99_SOURCE == 1
   # include <fenv.h>
   # include <iso646.h>
# endif
/*----------------------------------------------------------------------------*/
# include "../math/maths.h"
# include "../math/consts.h"
/*----------------------------------------------------------------------------*/
/* Edit this general configuration header: */
# include "../CONFIG.H" 
/*----------------------------------------------------------------------------*/
# include "../src/types.h"
/*----------------------------------------------------------------------------*/
/* Macros: */ 
# include "../src/NCURSES.M"
# include "../src/STOREVAL.M"
# include "../src/EXTREMA.M"
# include "../src/GNUPLOT.M"
/*----------------------------------------------------------------------------*/
/*============================================================================*/
# include "./amdwrk.h"
/*============================================================================*/
# undef DO_AMDWRK 
/****************************** end of amdwrk(*) ******************************/
/*
    Ein grosser Teil des Lebens
    entgleitet den Menschen,
    wenn sie Schlechtes tun, 
    der groesste, wenn sie nichts tun,
    das ganze Leben, 
    wenn sie Nebensaechliches tun.

                        Seneca
                        Briefe an Lucilius
*/
/* EOF */
