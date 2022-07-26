/* [ file: lotos.c ] */
# define DO_LOTOS "lotos(*)"
/*******************************************************************************
*                                                                              *
*   This function converts given integer lngint into                           *
*   an  ASCII character string  pointed to by lngstr                           *
*                                                                              *
*   (C) SHEIN; Munich, April 2020                             Steffen Hein     *
*   [ Update: December 19, 2021 ]                          <contact@sfenx.de>  *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 1 /* some headers of the POSIX.1 standard will be used */
# define _ISOC99_SOURCE 1
/*----------------------------------------------------------------------------*/
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <string.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include <ctype.h>
/*----------------------------------------------------------------------------*/
# if _ISOC99_SOURCE == 1
   # include <fenv.h>
   # include <iso646.h>
# endif
/*----------------------------------------------------------------------------*/
# include "../math/maths.h"
# include "../math/consts.h"
/*============================================================================*/

char *lotos ( long lngint, char length, char *mode )
{
   static long
      nn = null,
      dd = null;

   static signed char
      ii    = null,
      jj    = null,
      ssize = null;

   static char 
      *lngstr;
      
   lngstr = ( char *) calloc ( SHS_SIZE, ONE );
/*............................................................................*/

   nn    = ONE;
   ii    = null;
   ssize = null;
   if ( lngint < null )
   {
      lngstr[ssize] = '-';
      lngint = - lngint;
      ssize = ONE;
      ii = ONE;
   };
   do
   {
      lngstr[ssize] = 48; /* 48:  ASCII sign '0' */
      nn *= 10;
      ssize++;
   }  while (( ssize < SHS_SIZE )&&( nn <= lngint ));
   do
   {
      nn /=10;
      dd = lngint / nn ;
      lngstr[ii] = ( char ) dd + 48;        /* (+ 48) converts  digit  dd     */
      lngint -= dd*nn;                      /*        into ASCII sign 'dd'    */
      ii++;
   }  while ( ii < ssize );

   lngstr[ssize] = null;

/* write trailing ZEROs if length > ssize: */

   if ( length > ssize ) 
   {
      jj = length;

      while ( ssize >= null )
      { 
         lngstr[jj] = lngstr[ssize]; 
         jj--;
         ssize--;
      };
      while ( jj >= null )
      {
         lngstr[jj] = mode[0];
         jj--; 
      };
   };

   return lngstr; 
}
/************* end of long-to-string conversion function 'lotos(*)' ***********/
