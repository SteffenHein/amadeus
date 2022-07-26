/* [ file: amdevs.c ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Reweights vaccination history                                               *
*                                                                              *
*  (C) SHEIN; Munich, June 2022                                Steffen Hein    *
*  [ Update: July 05, 2022 ]                                <contact@sfenx.de> *
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
/*----------------------------------------------------------------------------*/
# ifndef AMD_VACPAST
   # define AMD_VACPAST "vac_history"
# endif
/*----------------------------------------------------------------------------*/
/* [0] 1: [don't] rewrite vaccination history */
# ifndef REWRITE_VAC
   # define REWRITE_VAC 0
# endif
# if REWRITE_VAC == 1
   # define VACPAST_NEW "vac_history_rewritten"
# endif
/*----------------------------------------------------------------------------*/

/*============================================================================*/

AMDSTATE *amdevs( AMDSTATE *state )
{
/* --- function prototypes -------------------------------------------------->*/

   double 
      expm1( double x ),
      strtod ( const char * restrict str, char ** restrict ptr );

   char 
      *lotos ( long lngint, char length, char *format );

/* --- declarations --------------------------------------------------------->*/

   DSPLAY 
     *dsplay( DSPLAY *dsp );

   static DSPLAY
     *dsp = null;

   static PARMTRS
     *ppt = null;

   static FILE 
     *logfle = NULL,
     *vac_hist = NULL;

/*............................................................................*/
# if REWRITE_VAC == 1
   static FILE 
     *wrt_hist = NULL;
# endif
/*............................................................................*/

   static long 
      ll = null;

   static short 
      ii = null;

   static double 
      intvac = ZERO,
      intvmd = ZERO;

   static double 
      dt = ZERO,
      tt = ZERO,
      tt1 = ZERO,
      tlen = ZERO,
      yy = ZERO;

   static double 
      Tdcy = ZERO; /* decay time */

   static char
      ptr[STS_SIZE] = {'\0'},
      xxptr[STS_SIZE] = {'\0'},
      yyptr[STS_SIZE] = {'\0'},
      fleptr[STS_SIZE] = AMD_VACPAST,
      longstr[STS_SIZE] = {'\0'},
    **endp = null;

   static time_t
      bufsize = null;
/*............................................................................*/
/* initialize dsplay(*) [ structure dsp* DSPLAY ]: */

   dsp = dsplay( null );

   logfle = fopen( state->logfle, "a+" );
   fseek( logfle, state->fleps, SEEK_SET );
/*
   errfle = fopen( state->errfle, "a+" );
*/
   if ( state->uif != 't' )
   {
      /* kk = setvbuf( logfle, null, _IONBF, bufsize ); */
      setvbuf( logfle, null, _IONBF, bufsize ); /* set unbuffered */
      dsp->display = logfle;
   }
   else
      dsp->display = stdout;
/*............................................................................*/
   ppt = state->par;

   vac_hist = fopen( fleptr, "r" );

   if ( vac_hist == NULL )
   {
      fprintf( logfle, "\n%s '%s' %s",\
         "Vaccination history file", fleptr, "not found" );

      strcpy( longstr, "Continuing with unweighted "\
         "vaccination history [ par.log" );
      strcat( longstr, lotos(( state->job ), null, "" ));
      strcat( longstr, " ]   " );
      fprintf( logfle, "\n%s", longstr );

      fclose( logfle );
      return state;
   };

   ii = null;
   while ( ii < 50 )
   {
      fscanf( vac_hist, "%s", ptr );

      if ( null == strncmp( ptr, "========", 8 ))
      {
         ll = ftell( vac_hist ) + ONE;
	 
         fprintf( logfle, "\n%s '%s' found",\
            "Vaccination history file", fleptr );

	 break;
      }
      else
         ++ii;
   };
/*----------------------------------------------------------------------------*/
   if ( ll == null )
   {
      fclose( vac_hist );

      fprintf( logfle, "\n%s '%s' %s",\
         "Vaccination history file", fleptr, "incorrectly formated" );

      strcpy( longstr, "Continuing with unweighted "\
         "vaccination history [ par.log" );
      strcat( longstr, lotos(( state->job ), null, "" ));
      strcat( longstr, " ]   " ); 
      fprintf( logfle, "\n%s", longstr );

      fclose( logfle );
      return state;
   }
   else 
   {
      strcpy( longstr, "Reweighting past vaccinations" );
      fprintf( logfle, "\n%s", longstr );
/*............................................................................*/
# if REWRITE_VAC == 1
      wrt_hist = fopen( VACPAST_NEW, "w" );
      fprintf( wrt_hist, "%s\n", "# Vaccination history\n"\
         "# [ time_unit: days, yunit: daily vaccinations ]" );
      fprintf( wrt_hist, "# %s\n",
         "======================================="\
         "=======================================" );
# endif 
/*............................................................................*/
/* decay time: */

      Tdcy = ppt->Tvac/LN2;

/* integrate daily vaccinations: */

      intvac = ZERO;

      fseek( vac_hist, ll, SEEK_SET );
      fscanf( vac_hist, "%s", xxptr );
      tt1 = strtod( xxptr, endp );
     
      tlen = ZERO;
      while ( EOF != fscanf( vac_hist, "%s", yyptr ))
      {
         yy = strtod( yyptr, endp );

         fscanf( vac_hist, "%s", xxptr );
         tt = strtod( xxptr, endp );
	 dt = tt - tt1;
         tlen += dt;

         intvac += ( dt*yy );
/*
         fprintf( stdout, "%le", tt );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le", yy );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le\n", intvac );
*/
/*............................................................................*/
# if REWRITE_VAC == 1
         fprintf( wrt_hist, "%10le          %10le\n", tt1, yy );
# endif
/*............................................................................*/
	 tt1 = tt;
      };
      fprintf( logfle, "\nNumber of vaccinations reweighted: %le", intvac );
/*............................................................................*/
# if REWRITE_VAC == 1
      fclose( wrt_hist );
# endif
/*............................................................................*/
/* reweight vaccinatons by decaying immunity and integrate */

      fseek( vac_hist, ll, SEEK_SET );
      fscanf( vac_hist, "%s", xxptr );
      tt1 = strtod( xxptr, endp );

      intvmd = ZERO;
      while ( EOF != fscanf( vac_hist, "%s", yyptr ))
      {
         yy = strtod( yyptr, endp );
	 
         fscanf( vac_hist, "%s", xxptr );
         tt = strtod( xxptr, endp );
	 dt = tt - tt1;
         tlen -= dt;

         intvmd += ( dt*yy*exp(( - tlen )/Tdcy ));
/*
         fprintf( stdout, "%le", tt );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le", yy );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le\n", intvmd );
*/
	 tt1 = tt;
      };

      yy = ( intvmd/intvac );
      yy *= ppt->Veff;
      ppt->rvcd *= yy;

      fprintf( logfle, "\nWeighting factor: %le", yy );
      fclose( logfle );
   };

   fclose( vac_hist );
   return state;
}
/*============================================================================*/
/****************************** end of amdevs(*) ******************************/
