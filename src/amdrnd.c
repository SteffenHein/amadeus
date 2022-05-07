/* [ file: amdrnd.c ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A plain numerical Model Approximating the Development of Epidemics          *
*  Under varied conditions if Spread                                           *
*                                                                              *
*  Random events
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: March 16, 2022 ]                               <contact@sfenx.de> *
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

AMDSTATE *amdrnd( AMDSTATE *state )
{
/*--- user function prototypes ---------------------------------------------->*/

   int rand( void );
   double exp( double x );
   double log( double x );
   double fmin( double x, double y );
   double fmod( double x, double y );

   static PARMTRS
     *ppt = null;

   static UPDATES
     *upd = null;
/*----------------------------------------------------------------------------*/
   upd = state->upd;
   ppt = state->par;

   if ( ZERO < ppt->Bstf )
   {
      if ( upd->nxtbst < upd->tt ) /* burst start */
      {
         upd->rnd = ( double ) rand( );
         upd->rnd /= RAND_MAX; 

         upd->bststp = upd->tt;
	 upd->bststp += ( 2.*upd->rnd*ppt->tlen ); /* next stop */
         upd->nxtbst = upd->bststp;

         upd->rnd = ( double ) rand( ); 
         upd->rnd /= RAND_MAX; 
         upd->rnd = 1. + 2.*upd->rnd*ppt->Bstf;
      };

      if ( upd->bststp < upd->tt ) /* burst stop */
      {
         upd->rnd = ( double ) rand( ); 
         upd->rnd /= RAND_MAX; 

         upd->nxtbst = upd->tt;
         upd->nxtbst += ( 2.*upd->rnd*ppt->trep ); /* next burst */
         upd->bststp = upd->nxtbst;

         upd->rnd = 1.;
      };

      upd->incidc *= upd->rnd;
   }; 
   return state;
}
/*============================================================================*/
/****************************** end of amdrnd(*) ******************************/
