/* [ file: amdrnd.c ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Random bursts                                                               *
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
/* returns real random number within the interval [0, 1]: */
# define RNDNRN(NRR)\
{ \
   (NRR) = ( double ) rand( ); \
            (NRR) /= RAND_MAX; \
}
/*----------------------------------------------------------------------------*/
/* Edit this general configuration header: */
# include "../CONFIG.H" 
/*----------------------------------------------------------------------------*/
# include "../src/types.h"
/*----------------------------------------------------------------------------*/
/* define burst plateau: BSTPLT > 0.
*/
# ifndef BSTPLT
   # define BSTPLT 1.0e+00 
# endif
/*----------------------------------------------------------------------------*/
/* burst length and pause: 
   fixed:  RNDBST = 0 [ <- just for testing perposes ]
   random: RNDBST = 1  
*/   
# ifndef RNDBST 
   # define RNDBST 1
# endif
/*============================================================================*/

AMDSTATE *amdrnd( AMDSTATE *state )
{
/*--- function prototypes --------------------------------------------------->*/

   int rand( void );
   double exp( double x );
   double log( double x );
   double fmin( double x, double y );
   double fmod( double x, double y );

/* --- declarations --------------------------------------------------------->*/

   static PARMTRS
     *ppt = null;

   static UPDATES
     *upd = null;

   static double 
      nrr = ZERO,
      rndbst = ZERO;
/*----------------------------------------------------------------------------*/
   upd = state->upd;
   ppt = state->par;

   if ( ZERO < ppt->Bstf )
   {
      if ( upd->burst == null )
      {
         if ( upd->nxtbst < upd->tt )
         {
/*.................................................................................*/
/* switch on: */

	    upd->burst = ONE;
/*.................................................................................*/
/* burst mode "shift" [ random factor within the interval ]P, P+2.*Bstf[
                        ( P = BSTPLT ), constant during each burst ] */

            if ( ppt->bstmde == null )
	    {
               RNDNRN(nrr);

               rndbst = BSTPLT + 2.*nrr*ppt->Bstf;
            };
/*.................................................................................*/
/* next stop: */

# if RNDBST == 0
	    upd->stpbst = upd->tt + ppt->tbln;
# else  
            RNDNRN(nrr);

            upd->stpbst = upd->tt;
	    upd->stpbst += 2.*nrr*ppt->tbln; /* next stop */
# endif
/*.................................................................................*/
         } /* if upd->nxtbst < upd->tt */
         else /* if ( upd->tt <= upd->nxtbst ) */
	    rndbst = 1.;
      }; /* end if bst == null */

      if ( upd->burst == ONE )
      {
         if ( upd->stpbst < upd->tt )  /* stop burst */
         {
/*.................................................................................*/
/* switch off: */
	    upd->burst = null;
	    rndbst = 1.;
/*.................................................................................*/
/* next start: */

# if RNDBST == 0
	    upd->nxtbst = upd->tt + ppt->tbps;
# else
            RNDNRN(nrr);

            upd->nxtbst = upd->tt;
            upd->nxtbst += 2.*nrr*ppt->tbps;
# endif
/*.................................................................................*/
	 }
	 else if ( ppt->bstmde == ONE )
	 {
/*.................................................................................*/
/* burst mode "slats" [ positive factor within the interval ]P, P+2*Bstf[,
                        randomly at every time step during the burst ] */

            RNDNRN(nrr);

            rndbst = BSTPLT + 2.*nrr*ppt->Bstf;
/*.................................................................................*/
         };
      }; /* end if bst == ONE */
      upd->incidc *= rndbst;
   }; /* end if ZERO < Bstf */
   return state;
}
/*============================================================================*/
/****************************** end of amdrnd(*) ******************************/
