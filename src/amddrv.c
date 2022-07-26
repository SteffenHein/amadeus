/* [ file: amddrv.c ] */
# define DO_AMDDRV "amddrv(*)"
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Driver function amddrv(*)                                                   *
*  Coordinates all parameter input, corrections and computational steps        *
*  by subsequently calling the respective functions                            *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 01, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 1 /* some headers of the POSIX.1 standard will be used */
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
# include "../math/maths.h"
# include "../math/consts.h"
/*----------------------------------------------------------------------------*/
/* Edit and customize this general configuration header: */
# include "../CONFIG.H" 
/*----------------------------------------------------------------------------*/
# include "../src/NCURSES.M"
/*----------------------------------------------------------------------------*/
# ifndef OPERATIONS
   # define OPERATIONS 20
# endif
/*----------------------------------------------------------------------------*/
# ifndef IPT_OPRINIT
   # define IPT_OPRINIT "opr.init"
# endif
/*----------------------------------------------------------------------------*/
# ifndef IPT_OPRLOG
   # define IPT_OPRLOG "opr.log"
# endif
/*----------------------------------------------------------------------------*/
# ifndef PARAMETERS
   # define PARAMETERS 50
# endif
/*----------------------------------------------------------------------------*/
# ifndef IPT_PARINIT
   # define IPT_PARINIT "par.init"
# endif
/*----------------------------------------------------------------------------*/
# ifndef IPT_PARLOG
   # define IPT_PARLOG "par.log"
# endif
/*----------------------------------------------------------------------------*/
/* precision in heliosdrv: */
# ifndef PRECISION
   # define PRECISION ( 1.0e-15 )
# endif
/*----------------------------------------------------------------------------*/
/* very small double in heliosdrv: */
# ifndef SMALL_VAL
   # define SMALL_VAL ( 1.0e-301 )
# endif
/*----------------------------------------------------------------------------*/
/* giant double in amddrv: */
# ifndef GIANT_VAL
   # define GIANT_VAL ( 1.0e+277 )
# endif
/*----------------------------------------------------------------------------*/
/* structures typedefs, etc.: */

# include "../src/types.h"
/*----------------------------------------------------------------------------*/
static AMDSTATE amdstat = {null};
/*----------------------------------------------------------------------------*/
static OPERTNS opertns = {null};
/*----------------------------------------------------------------------------*/
static PARMTRS parmtrs = {null};
/*----------------------------------------------------------------------------*/
static UPDATES updates = {null};
/*----------------------------------------------------------------------------*/
static TXCNSL cns = {null};
/*----------------------------------------------------------------------------*/
static char /* temporary file name */
   tmpfle[STS_SIZE] = {null};
/*----------------------------------------------------------------------------*/
# include "../src/inputs.h"
/*----------------------------------------------------------------------------*/
# include "../src/PRNTCRS.M"
/*============================================================================*/
/* include the function body [ short amddrv( int argn, char **args ) ] */
# include "./amddrv.h" 
/*============================================================================*/
# undef DO_AMDDRV
/********************** end of function 'amddrv(*)' ***************************/
/*
   Es ist gleichermassen toedlich fuer den Geist, ein System zu haben - und
   keines zu haben. Daher muss man sich dazu entschließen, beides miteinander
   zu verbinden.
                                                          Friedrich Schlegel
*/
