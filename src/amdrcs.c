/* [ file: amdrcs.c ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Reweights recovery history                                                  *
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
# ifndef AMS_RECPAST
   # define AMD_RECPAST "rec_history"
# endif
/*----------------------------------------------------------------------------*/
/* [0] 1: [don't] rewrite incidence history */
# ifndef REWRITE_REC
   # define REWRITE_REC 0
# endif
# if REWRITE_REC == 1
   # define RECPAST_NEW "rec_history_rewritten"
# endif
/*============================================================================*/

AMDSTATE *amdrcs( AMDSTATE *state )
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
     *rec_hist = NULL;
/*............................................................................*/
# if REWRITE_REC == 1
   static FILE 
     *wrt_hist = NULL;
# endif
/*............................................................................*/
   static long 
      ll = null;

   static short 
      ii = null;

   static double 
      intrec = ZERO,
      intfmd = ZERO;

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
      fleptr[STS_SIZE] = AMD_RECPAST,
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

   rec_hist = fopen( fleptr, "r" );

   if ( rec_hist == NULL )
   {
      fprintf( logfle, "\n%s '%s' %s",\
         "Recovery history file", fleptr, "not found" );

      strcpy( longstr, "Continuing with unweighted "\
         "recovery history [ par.log" );
      strcat( longstr, lotos( state->job, null, "" ));
      strcat( longstr, " ]   " ); 
      fprintf( logfle, "\n%s", longstr );
      
      fclose( logfle );
      return state;
   };

   ii = null;
   while ( ii < 50 )
   {
      fscanf( rec_hist, "%s", ptr );

      if ( null == strncmp( ptr, "========", 8 ))
      {
         ll = ftell( rec_hist ) + ONE;
	 
         fprintf( logfle, "\n%s '%s' found",\
            "Recovery history file", fleptr );

	 break;
      }
      else
         ++ii;
   };
/*----------------------------------------------------------------------------*/
   if ( ll == null )
   {
      fclose( rec_hist );

      fprintf( logfle, "\n%s '%s' %s",\
         "Recovery history file", fleptr, "incorrectly formated" );

      strcpy( longstr, "Continuing with unweighted "\
         "recovery history [ par.log" );
      strcat( longstr, lotos( state->job, null, "" ));
      strcat( longstr, " ]   " ); 
      fprintf( logfle, "\n%s", longstr );

      fclose( logfle );
      return state;
   }
   else 
   {
      strcpy( longstr, "Reweighting recovered cases" );
      fprintf( logfle, "\n%s", longstr );
/*............................................................................*/
# if REWRITE_REC == 1
      wrt_hist = fopen( RECPAST_NEW, "w" );
      fprintf( wrt_hist, "%s\n", "# Recovery history\n"\
         "# [ time_unit: days, y_unit: daily recovered ]" );
      fprintf( wrt_hist, "# %s\n",\
         "======================================="\
         "=======================================" );
# endif 
/*............................................................................*/
/* decay time: */

      Tdcy = ppt->Timu/LN2;

      fseek( rec_hist, ll, SEEK_SET );
      fscanf( rec_hist, "%s", xxptr );
      tt1 = strtod( xxptr, endp );
/*............................................................................*/
/* integrate incidence history: */

      tlen = ZERO;
      intrec = ZERO;

      while ( EOF != fscanf( rec_hist, "%s", yyptr ))
      {
         yy = strtod( yyptr, endp );

         fscanf( rec_hist, "%s", xxptr );
         tt = strtod( xxptr, endp );
	 dt = tt - tt1;
         tlen += dt;

         intrec += ( dt*yy );
/*
         fprintf( stdout, "%le", tt );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le", yy );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le\n", intrec );
*/
/*............................................................................*/
# if REWRITE_REC == 1
         fprintf( wrt_hist, "%10le          %10le\n", tt1, yy );
# endif
/*............................................................................*/
	 tt1 = tt;
      };
      fprintf( logfle, "\nNumber of cases reweighted: %le", intrec );
/*............................................................................*/
# if REWRITE_REC == 1
      fclose( wrt_hist );
# endif
/*............................................................................*/
/* reweight recovered cases by decaying immunity and integrate */

      intfmd = ZERO;

      fseek( rec_hist, ll, SEEK_SET );
      fscanf( rec_hist, "%s", xxptr );
      tt1 = strtod( xxptr, endp );

      while ( EOF != fscanf( rec_hist, "%s", yyptr ))
      {
         yy = strtod( yyptr, endp );
	 
         fscanf( rec_hist, "%s", xxptr );
         tt = strtod( xxptr, endp );
	 dt = tt - tt1;
	 tlen -= dt;

         intfmd += ( dt*yy*exp(( - tlen )/Tdcy ));
/*
         fprintf( stdout, "%le", tt );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le", yy );
         fprintf( stdout, "%s", " ---- " );
         fprintf( stdout, "%le\n", intfmd );
*/
	 tt1 = tt;
      };
/*
      fprintf( stdout, "\n%le\n", intrec );
      fprintf( stdout, "%le\n", intfmd );
      fprintf( stdout, "%le\n", ( intfmd/intrec ));
*/     
      yy = ( intfmd/intrec );
      yy *= ppt->Ieff;
      ppt->rimn *= yy;

      fprintf( logfle, "\nWeighting factor: %le", yy );
      fclose( logfle );
   };

   fclose( rec_hist );
   return state;
}
/*============================================================================*/
/****************************** end of amdrcs(*) ******************************/
