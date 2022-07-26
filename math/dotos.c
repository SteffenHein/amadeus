/* [ file: dotos.c ] */
# define DO_DOTOS "dotos(*)"
/*******************************************************************************
*                                                                              *
*   This function converts given  double lngdbl into a fixed point [ *format   *
*   = 'f' ] or floating point [ *format = 'e', 'E' ] ASCII character string,   *
*   pointed to by char *dblstr, which is returned to the calling program.      *
*                                                                              *
*   (C) SHEIN; Munich, April 2020                             Steffen Hein     *
*   [ Update: December 19, 2021 ]                          <contact@sfenx.de>  *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 1 /* set to 1: if POSIX.1 standard headers will be used*/
/*----------------------------------------------------------------------------*/
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <string.h>
# include <float.h>
# include <math.h>
# include <time.h>
/*----------------------------------------------------------------------------*/
# include "../math/consts.h"
# include "../math/maths.h"
/*----------------------------------------------------------------------------*/
# ifndef DBL_SGN
   # define DBL_SGN 0
# endif
# ifndef DBL_DIG
   # define DBL_DIG 15
# endif
/*============================================================================*/

char *dotos ( double lngdbl, char precision, char *format )
{
   static double
      dd = ZERO,
      qq = ZERO,
      rr = ZERO,
      ss = ZERO,
      pw10 = ZERO,
      ln10 = ZERO,
      one_ =.9999999999999999;

   static signed char
      ff = null,
      ii = null,
      jj = null,
      ssize  = null,
      mxprcs = null,
      mxsize = null;

   static short
      ld = null,
      expt = null;

   static char
      dblstr[STS_SIZE] = {null};
/*      
   static char
      ptr[STS_SIZE] = {null};
*/
/* prototypes: */
   
   double exp( double x );
   double log( double x );
   double log10( double x );

   mxprcs = DBL_DIG;
   mxsize = DBL_DIG + EIGHT; /* must be greater than FIVE ! */
/*----------------------------------------------------------------------------*/
   ff = *format;

   if (( ff != 'e' )&&( ff != 'E' ))
      ff = 'f'; /* fixed point */

   if ( mxprcs < precision )
      precision = mxprcs;

   dd = lngdbl;
   ssize = null;
   if ( dd == ZERO )
   {
     dd_zero:

      dblstr[ssize] = 48;  /* ASCII char '0' */
      ssize++;
      dblstr[ssize] = 46;  /* ASCII char '.' */
      ssize++;

      if ( ff == 'f' )
         jj = mxsize - TWO;
      else if (( ff == 'e' )||( ff == 'E' ))
         jj = mxsize - FIVE;

      ii = ONE;
      while (( ssize < jj )&&( ii < precision ))
      {
         dblstr[ssize] = 48; /* ASCII char '0' */
         ssize++;
         ii++;
      };
      
      if (( ff == 'e' )||( ff == 'E' ))
      {
         dblstr[ssize] = ff; /* ASCII char format */
         ssize++;
         dblstr[ssize] = 43;  /* ASCII char '+' */
         ssize++;
         dblstr[ssize] = 48;  /* ASCII char '0' */
         ssize++;
         dblstr[ssize] = 48; 
         ssize++;
      };

      dblstr[ssize] = null;    /* trailing null */
      return dblstr;
   }
   else if ( ZERO < dd )
   { 
# if DBL_SGN == 1
      dblstr[ssize] = 40;  /* ASCII char ' ' [ SPACE ] */
      ssize++;
# elif DBL_SGN == 2
      dblstr[ssize] = 43;  /* ASCII char '+' */
      ssize++;
# endif
   }
   else if ( dd < ZERO )
   {
      dblstr[ssize] = 45;  /* ASCII char '-' */
      ssize++;
      dd = - dd;
   };

   ln10 = log( 10.0000000000000 );
   expt = ( signed int ) log10( dd );

   if (( ff == 'f' )&&( precision <= expt ))
      ff = 'e';
/*............................................................................*/
/* round off [ upto precision = number of decimal digits ] */
   ld = expt;

   if (( ff == 'f' )&&( ld < -ONE ))
      ld = -ONE;
      
   rr = dd;
   ss = ZERO;

   ii = null;
   while ( ii <= precision )
   {
      pw10 = exp( ln10*ld );

      if ( ZERO < pw10 )
      {
         qq = rr/pw10;
         jj = ( char ) qq;
      }
      else
      {
         jj = NINE;
         goto brk1;
      };
      ss += ( double ) jj * pw10;

      rr -= ( double ) jj * pw10;
      ld -= ONE;

      ii++;
   };

   pw10 = exp( ld * ln10 );

   if ( ZERO < pw10 )
   {
      qq = rr/( one_*pw10 );      /* ! */
      jj = ( char ) qq;
   };

   ss += ( double ) jj * pw10;

  brk1:

   if ( FOUR < jj ) 
      dd = ss + ( double ) ( 10.01 - jj ) * pw10;

   if ( dd == ZERO )
      goto dd_zero;

   expt = ( signed int ) log10( dd );
/*............................................................................*/
/* log10(dd): find leading digit != null */

   rr = dd;
   ld = expt + ONE; do
   {
      ld--;
      pw10 = exp( ld * ln10 );
      qq = rr/( one_*pw10 );
      jj = ( char ) qq;
   } while ( jj <= null );
   expt = ld;                          /* expt is the greatest interger n     */
                                       /* such that 10^n <= dd < 10^(n+1)     */
/*............................................................................*/
/* write floating point ASCII string: */

   if (( ff == 'e' )||( ff == 'E' ))
   {
      if( NINE < jj )  
         jj = NINE;  

      dblstr[ssize] = jj + 48;  /* ASCII char of integer jj */
      ssize++;
      dblstr[ssize] = 46;       /* ASCII char '.' */
      ssize++;

      ii = ONE;
      while (( ssize < mxsize - SIX )&&( ii < precision ))
      {
         rr -= ( double ) jj * pw10;
         ld -= ONE;
         pw10 = exp( ld * ln10 );

         if ( ZERO < pw10 )
         { 
            qq = rr/pw10;
            jj = ( char ) qq;
         }
         else
         {
            jj = NINE;
         };

         if ( jj < null )
            jj = null;
         if ( NINE < jj )
            jj = NINE; 

         dblstr[ssize] = jj + 48;  /* ASCII char of integer jj */
         ssize++;

         ii++;
      };

      dblstr[ssize] = ff; /* ASCII char format[0], e.g. 'e' = 101      */
      ssize++;

      if ( null <= expt )
      {
         dblstr[ssize] = 43;  /* ASCII char '+' */
         ssize++;
      }
      else
      {
         dblstr[ssize] = 45;  /* ASCII char '-' */
         ssize++;
         expt = - expt;
      };
      
      if ( 10000 <= expt )
      {
         printf( "\n\n Error in function '%s' : ", DO_DOTOS ); 
         printf( "\n Floating point overflow ! " );
         printf( "\n [ overrides and returns a null pointer ] \n" );
         return null;
      };

      ld = ( int ) expt/1000;

      if ( ld != null )
      {
         dblstr[ssize] = ld + 48;  /* ASCII char of integer ld */
         ssize++;

         expt -= (( int ) ld )*1000;
         ld = ( int ) expt/100; 

         dblstr[ssize] = ld + 48;  /* ASCII char of integer ld */
         ssize++;
      }
      else
      {
         ld = ( int ) expt/100;

         if ( ld != null )
         {
            dblstr[ssize] = ld + 48;  /* ASCII char of integer ld */
            ssize++;
         };
      };

      expt -= (( int ) ld )*100;
      ld = ( int ) expt/10;

      dblstr[ssize] = ld + 48;  /* ASCII char of integer ld */
      ssize++;

      expt -= (( int ) ld )*10;
      ld = ( int ) expt;

      dblstr[ssize] = ld + 48;  /* ASCII char of integer ld */
      ssize++;
   }
   else /* ff == 'f': fixed point ASCII string */ 
   {
      rr = dd;
      ld = expt;

      if ( ld < -ONE )
      {
         ld = -ONE;
         pw10 = exp( ln10*ld );

         if ( ZERO < pw10 )
	 {
            qq = rr / pw10;
            jj = ( char ) qq;
         };
      };

      ii = null;
      while (( ssize < mxsize )&&( ii < precision ))
      {
         if ( jj < null )
            jj = null;
         if ( NINE < jj )
            jj = NINE;

         if ( ld == -ONE )
         {
            dblstr[ssize] = 46; /* ASCII char '.' */
            ssize++;
         };

         if (( null < jj )||( null < ii )||( ld < null))
         {
            dblstr[ssize] = jj + 48;  /* ASCII char of integer jj */
            ssize++;
            ii++;
         };

         rr -= ( double ) jj * pw10;
         ld -= ONE;
         pw10 = exp( ln10*ld );

         if ( ZERO < pw10 )
         {
            qq = rr / pw10;
            jj = ( char ) qq;
         }
         else
         {
            jj = NINE;
         }; 
      };

      if ( ld == ( -ONE ))
      {
         dblstr[ssize] = 46; /* ASCII char '.' */
         ssize++;
      };
   };

   dblstr[ssize] = null;     /* trailing null */
   return dblstr;
}
# undef DBL_SGN
# undef DBL_DIG
/************ end of double-to-string conversion function dotos(*) ************/
