/* [ file: amdmdl.c ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Reproduction factor modulation                                              *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 04, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 1 /* some headers of the POSIX.1 standard will be used */
# define _ISOC99_SOURCE 1
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
/*============================================================================*/

AMDSTATE *amdmdl( AMDSTATE *state )
{
/*--- user function prototypes ---------------------------------------------->*/

   double sin( double x );
   double fmax( double x, double y );

   static PARMTRS
     *ppt = null;

   static UPDATES
     *upd = null;
     
   static double
      xx = null,
      yy = null;

/*----------------------------------------------------------------------------*/
   upd = state->upd;
   ppt = state->par;

   if (( ppt->trrd < upd->tt )\
     &&( upd->tt < ( ppt->trrd + ppt->trml )))
   {
      switch ( ppt->rfmmde ) /* modulation mode */
      {
        case 0: /* rectangular */
	default:
         yy = 1.;
        break;

        case 1: /* parabolic */
         yy = ppt->trml/2.;
         xx = ppt->trrd + yy;
	 xx = upd->tt - xx;
	 yy = 1./yy;
	 yy *= yy;
	 yy *= ( xx * xx );
	 yy = 1. - yy;
        break;

        case 2: /* sinus, half wave */
         yy = sin( PI*( upd->tt - ppt->trrd )/ppt->trml );
        break;

        case 3: /* sinus, full wave */
         yy = sin( 2.*PI*( upd->tt - ppt->trrd )/ppt->trml );
        break;

        case 4: /* sinus squared, half wave */
         yy = sin( PI*( upd->tt - ppt->trrd )/ppt->trml );
         yy *= yy;
        break;
      };
      
      yy *= ppt->Rmda;
      yy = fmax( yy, -9.9999999e-1 );
      yy += 1.;
      upd->reprod *= yy;
   };

   return state;
}
/*============================================================================*/
/****************************** end of amdmdl(*) ******************************/
