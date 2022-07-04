/* [ file: txcnsl.c ] */
# define DO_TXCNSL "txcnsl(*)"
/*******************************************************************************
*                                                                              *
*   Provides standardized command line and parameter input format on a text    *
*   console.                                                                   *
*                                                                              *
*   (C) SHEIN; Munich, April 2020                             Steffen Hein     *
*   [ Update: June 29, 2022 ]                              <contact@sfenx.de>  *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 0 /* set to 1: if POSIX.1 standard headers will be used*/
/*----------------------------------------------------------------------------*/
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <string.h>
# include <ctype.h>
# include <time.h>           /* cf. time( ),ctime( ),asctime( ),localtime( )  */
/*----------------------------------------------------------------------------*/
# include "../math/maths.h"  /* 'my' computation environment headers */
# include "../math/consts.h" /* some frequently used constants */
/*----------------------------------------------------------------------------*/
/* some user defined constants  
[ e.g.:
   # define SSTRNG "***.......
   # define null   0
   # define ONE    1
     ***
   # define DEC   10
   # define ZERO   0.
   # define PI     3.14.......
] */
/*----------------------------------------------------------------------------*/
/* the general configuration file: */  
# include "../CONFIG.H"

# ifndef USE_NCURSES
   # define USE_NCURSES 1
# endif
/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
   # include <ncurses.h>
# endif 
/*----------------------------------------------------------------------------*/
# include "../disp/txctyp.h" /* structure of type TXCNSL, cf. below */
/*----------------------------------------------------------------------------*/
# define CNS_DEFLT  "active"   
                     
# ifndef CNS_ITEMS
   # define CNS_ITEMS 10 /* maximum number of menu items                      */
# endif
# ifndef CNS_POSIT
   # define CNS_POSIT 67 /* position of menu labels [indices] in line         */
# endif
# ifndef CNS_LNLEN
   # define CNS_LNLEN 79 /* number of characters in menu line                 */
# endif
# ifndef CNS_LNINT
   # define CNS_LNINT  2 /* first non-space character in line                 */
# endif
# ifndef HUGE_VALF
   # define HUGE_VALF (( double ) 1.0e+299 )
# endif
# ifndef LONG_MIN
   # define LONG_MIN (( long ) null )
# endif
/*----------------------------------------------------------------------------*/
# ifndef TP_TXCNSL

/* Transfer structure of function 'txcnsl(*)' [ which provides standardized   */
/* command line / menu options on a text console ] */

typedef struct
{
   signed char 
      clscr,
      rtn; 

   int
      items, dfopt, dflnf,
      lnlen, posit, lnint,
      lglen, dblen, stlen,
      option;

   char
      title[LGS_SIZE],
      rqfrm[SHS_SIZE],
      tasks[CNS_LNLEN],
      flags[CNS_LNLEN],
      cmmnt[CNS_LNLEN],
      envmt[CNS_LNLEN],
      escpe[CNS_LNLEN],
      cnfrm[CNS_LNLEN],
      instr[CNS_LNLEN],
      dfstr[CNS_LNLEN],
      rqdbl[CNS_LNLEN],
      rqlng[CNS_LNLEN],
      rqstr[CNS_LNLEN],
      mflag[CNS_ITEMS],
      mflin[CNS_ITEMS],
      mline[CNS_ITEMS][CNS_LNLEN];

   long
      dflng, inlng;

   double
      dfdbl, indbl;
   
} TXCNSL;
# endif
/*----------------------------------------------------------------------------*/
static TXCNSL
   cns = {null};
/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
/* 'my_terminal' configuration: */

# include <termcap.h>   /* terminal type header */

   static char *term;   /* terminal type string */ 

   # define CLSCREEN {\
     printf( "\f%s", tgetstr( "cl", null )); \
   }

   # define PRBLDCLR(a) {\
     printf( "%s%s", tgetstr( "md", null ), (a)); /* bold clear output */ \
   }

   # define PRINVERS(a) {\
     printf( "%s%s", tgetstr( "mr", null ), (a)); /* inverse */ \
   }

   # define PRNORMAL(a) {\
     printf( "%s%s", tgetstr( "me", null ), (a)); /* back to normal output */ \
   }
# else
   # define CLSCREEN {\
     printf ( "\f" ); \
   }

   # define PRBLDCLR(a) {\
     printf( "%s", (a));\
   }

   # define PRINVERS(a) {\
     printf( "%s", (a));\
   }

   # define PRNORMAL(a) {\
     printf( "%s", (a));\
   }
# endif
/*============================================================================*/

TXCNSL *clcnsl( TXCNSL *cxp )
{
/* declarations: */

   static TXCNSL 
     *cpt = &cns;

   static short
      ii = null,
      jj = null;
/*----------------------------------------------------------------------------*/
   ii = null;
   while( ii < SHS_SIZE )
   {
      ( cpt->rqfrm[ii] ) = null;
      ++ii;
   };

   ii = null;
   while( ii < LGS_SIZE )
   {
      ( cpt->title[ii] ) = null;
      ++ii;
   };

   ii = null;
   while( ii < CNS_ITEMS )
   {
      jj = null;
      while( jj < CNS_LNLEN )
      {
         ( cpt->mline[ii][jj] ) = null;
         ++jj;
      };
      ( cpt->mflag[ii] ) = null;
      ++ii;
   };

   ii = null;
   while( ii < CNS_LNLEN )
   {
      ( cpt->envmt[ii] ) = null; /* clear any environment indicator */
      ( cpt->cmmnt[ii] ) = null; /* clear any comment line */
      ( cpt->tasks[ii] ) = null; /* clear any tasks line */
      ( cpt->flags[ii] ) = null; /* clear any flags line */
      ( cpt->escpe[ii] ) = null; /* clear any escape path */
      ( cpt->cnfrm[ii] ) = null; /* clear any confirmation command */
      ( cpt->dfstr[ii] ) = null; /* clear any default of the former */
      ( cpt->rqlng[ii] ) = null; /* clear any long integer request */
      ( cpt->rqdbl[ii] ) = null; /* clear any floating point / double request */
      ( cpt->rqstr[ii] ) = null; /* clear any char string request */
      ++ii;
   };

/* reset: */

   ( cpt->posit ) = CNS_POSIT;
   ( cpt->lnlen ) = CNS_LNLEN;
   ( cpt->lnint ) = CNS_LNINT;
   
   ( cpt->clscr ) = null;
   ( cpt->lglen ) = null;
   ( cpt->dblen ) = null;
   ( cpt->stlen ) = null;

   ( cpt->items ) = null;
   ( cpt->dflng ) = LONG_MIN;
   ( cpt->dfopt ) = - ONE;
   ( cpt->dflnf ) = - ONE;

   ( cpt->dfdbl ) = - HUGE_VALF;
   ( cpt->rtn ) = null;

   return cpt;
}
/*======================== end of function clcnsl(*) =========================*/

# define FGETC(MM) \
{ \
   ii = null; \
   ptr[ii] = fgetc( stdin ); \
   while(( ptr[ii] != '\n' ) \
       &&( ii < (MM) )) \
   { \
      ++ii; \
      ptr[ii] = fgetc( stdin ); \
   }; \
}

# define CNS_CLSTR(MM,NN) \
{ \
   ii = (MM); \
   while ( ii < (NN) ) \
   { \
      ptr[ii] = 0; \
      ++ii; \
   }; \
}

# define CNS_BLANCS(MM,NN) \
{ \
   ii = (MM); \
   while( ii < (NN) ) \
   { \
      ptr[ii] = ' '; \
      ++ii; \
   }; \
}

# define CNS_POINTS(MM,NN) \
{ \
   ii = (MM); \
   while( ii < (NN) ) \
   { \
      ptr[ii] = '.'; \
      ++ii; \
   }; \
}

# define CNS_ARROW(MM,NN) \
{ \
   ii = (MM); \
   ptr[ii] = '>'; \
   ++ii; \
   while( ii < (NN) ) \
   { \
      ptr[ii] = '-'; \
      ++ii; \
   }; \
   ptr[ii] = '>'; \
   ++ii; \
}
/*============================================================================*/

TXCNSL *txcnsl( TXCNSL *csp )
{
/* declarations */

   static TXCNSL 
     *cpt = &cns;

   static short
      ii = null,
      jj = null,
      kk = null,
      ll = null,
      mm = null;

   static char
      ptr[STS_SIZE+ONE] = {null},
    **endp = null;

/* prototypes: */

   TXCNSL 
      *clcnsl( TXCNSL *csp );
   
   char 
      *lotos ( long lngint, char length, char *format ),
      *dotos ( double lngdbl, char precision, char *format );
/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
/* get the terminal info: */

   term = ( char *) getenv( "TERM" ); /* get the terminal */

   ii = tgetent( null, term );

   if( ONE != ii )
   {
      fprintf( stderr, "Error on getting the termcap info\n" ); 
      exit( EXIT_FAILURE );
   };
# endif
/*............................................................................*/
/* set buffer length = null: */

   ii = setvbuf( stdin, null, _IONBF, null );
   ii = setvbuf( stdout, null, _IONBF, null );
/*............................................................................*/
/* initialize: */

   if( csp == null )
   {
      ii = null;
      while( ii < CNS_LNLEN )
      {
         ( cpt->instr[ii] ) = null;
         ++ii;
      };

      ii = null;
      while( ii < CNS_ITEMS )
      {
         ( cpt->mflin[ii] ) = null;
         ++ii;
      };

      ( cpt->inlng ) = null;
      ( cpt->inlng ) = null;
      ( cpt->indbl ) = null;
/*............................................................................*/
      cpt = clcnsl( cpt );     /*                                             */
/*...........................*/
      ( cpt->rtn ) = null;

      return cpt;
   }
   else
   {
      if( CNS_LNLEN < csp->lnlen )
         csp->lnlen = CNS_LNLEN;

      if( csp->lnint < null )
         csp->lnint = CNS_LNINT;

      if( csp->lnlen < csp->lnint )
         csp->lnint = csp->lnlen;

      if( csp->posit < null )
         csp->posit = CNS_POSIT;

      if( csp->lnlen < cpt->posit )
         csp->posit = csp->lnlen;

      ii = null;
      while( ii < CNS_ITEMS )
      {
         cpt->mflin[ii] = cpt->mflag[ii];

         if(( null == cpt->mflag[null] )
	  &&( null != cpt->mflag[ii] ))
            csp->mflag[null] = ii;
         ++ii;
      };
   };
/*...........................................................................*/
/* clear screen, scroll ( csp->clscr ) number of lines: */

  start:

   if( null < ( csp->clscr ))
   {
      CLSCREEN;

      ii = ONE;
      while( ii < ( csp->clscr ))
      {
         printf( "\n" );
         ++ii;
      };
   };
/*...........................................................................*/
/* write title [ if any ]: */

   if( null < strlen( csp->title ))
   {
      PRNORMAL( "\n" );
      ii = null;
      ll = ( csp->lnint );
      while( ii < ll )
      {
         printf( "%c", ' ' );
         ++ii;
      };
      printf( "%s", csp->title );
   };
/*............................................................................*/
/* underline and display environment label [ if any ]: */

   if( null < strlen( csp->envmt ))
   {
      printf( "\n" );
      ii = null;
      ll = ( csp->lnint );
      while ( ii < ll )
      {
         printf( "%c", ' ' );
         ++ii ;
      };
      ll = ( csp->lnlen );
      while ( ii < ll )
      {
         printf( "%c", '=' );
         ++ii ;
      };

      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      strcat( ptr, csp->cmmnt );

      ii += strlen( csp->cmmnt );
      jj = strlen( csp->envmt );
      kk = ii;
      ll = ( csp->lnlen ) - jj;

      CNS_BLANCS( kk, ll ); /* fill with blancs */

      strcat( ptr, csp->envmt );

      PRBLDCLR( "" );
      printf( "\n%s", ptr );
      PRNORMAL( "\n" );
   };

/*............................................................................*/
/* build the menu: */

   if( null < csp->items )
   {
/*............................................................................*/
/* display the tasks description [ if any ] and point to the items: */

      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      strcat( ptr, csp->tasks );
      jj = strlen( ptr );
      kk = strlen( "Select |" );
      ll = CNS_POSIT - kk;

      CNS_BLANCS( jj, ll ); /* fill with blancs */

      strcat( ptr, "Select |" );
      printf( "\n%s", ptr );

      CNS_CLSTR( ll, STS_SIZE );   /* clear string ptr[] */
      ll = ( csp->posit ) - ONE;
      CNS_BLANCS( null, ll ); /* fill with blancs */

      ptr[ii] = 'V';
      printf( "\n%s", ptr );

/*............................................................................*/
/* display the menu items [ options ]: */

      jj = ONE;
      while( jj <= ( csp->items ))
      {
/*............................................................................*/
/* display the flag comment [ if any ]: */

         if(( jj == ( csp->mflag[null] ))&&( null != strlen( csp->flags )))
         {
            CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
            ll = ( csp->lnint );
            CNS_BLANCS( null, ll ); /* indent */

            strcat( ptr, csp->flags );
            kk = strlen( ptr );

            if( ONE < jj )
            {
               ll = ( short ) ( - strlen( "Change |" ));
               ll += CNS_POSIT;
               CNS_BLANCS( kk, ll ); /* fill with blancs */

               strcat( ptr, "Change |" );
            };
            printf( "\n\n%s", ptr );

            if( ONE < jj )
            {
               CNS_CLSTR( ll, STS_SIZE ); /* clear string ptr[] */
               ll = ( csp->posit ) - ONE;
               CNS_BLANCS( null, ll ); /* fill with blancs */

               ptr[ii] = 'V';
               printf( "\n%s", ptr );
            };
         };

         CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
         ll = ( csp->lnint );
         CNS_BLANCS( null, ll ); /* indent */

         ll = strlen( csp->mline[jj] );
         kk = null;
         while( kk < ll )
         {
            ptr[ii] = csp->mline[jj][kk];
            ++ii;
            ++kk;
         };
         ptr[ii] = ' ';
         ++ii;
         ll = CNS_POSIT - FOUR;

         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         ptr[ii] = ' ';
         ++ii;
         ptr[ii] = '[';
         ++ii;

         if(( csp->dflnf ) == jj )
            printf( "\n" );

         if(( csp->dfopt ) == jj )
         {
            printf( "\n%s", ptr );

            PRBLDCLR( lotos( jj, null, " " ));
            PRNORMAL( "] " );
            PRBLDCLR( "<-proposed" );
            PRNORMAL( "" );

            if ((( csp->dflnf ) == ONE )&&( jj < csp->items ))
               printf( "\n" );
         }
         else
         {
            printf( "\n%s", ptr );
            if (( csp->mflin[jj] ) == -ONE )
            {
               PRNORMAL( lotos( jj, null, " " ));
               PRNORMAL( "] " );
               PRNORMAL( "<- not set" );
               PRNORMAL( "" );
            }
            else if (( csp->mflin[jj] ) == ONE )
            {
               PRBLDCLR( lotos( jj, null, " " ));
               PRNORMAL( "] " );
               PRBLDCLR( "<- set" );
               PRNORMAL( "" );
            }
            else
            {
               PRNORMAL( lotos( jj, null, " " ));
               PRNORMAL( "] " );
            };
         };
         ++jj;
      }; /* end while ( jj <= csp->items ) */

/*............................................................................*/
/* display the escape option: */

      if( null < strlen( csp->escpe ))
      {
         CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
         ll = ( csp->lnint );
         CNS_BLANCS( null, ll ); /* indent */

         ll = strlen( csp->escpe );
         kk = null;
         while( kk < ll )
         {
            ptr[ii] = csp->escpe[kk];
            ++ii;
            ++kk;
         };
         ptr[ii] = ' ';
         ++ii;
         ll = ( csp->posit ) - FOUR;

         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         ptr[ii] = ' ';
         ++ii;
         ptr[ii] = '[';
         ++ii;

         printf( "\n\n%s", ptr );

         if( null == ( csp->dfopt ))
         {
            PRBLDCLR( lotos( null, null, " " ));
            PRNORMAL( "] " );
            PRBLDCLR( "<-proposed" );
            PRNORMAL( "" );
         }
         else
            printf( "%c%s", 48, "]" ); /* 48: ASCII char <null> */
         ++ii;
      }; /* end if ( null != strlen( csp->escpe )) */
/*............................................................................*/
/* position the cursor: */

      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->posit );
      CNS_BLANCS( null, ll ); /* fill with blancs */

      ptr[ii] = ']';
      ++ii;
      strcat( ptr, " <- ?" );
      printf( "\n\n%s", ptr );

      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      strcat( ptr, "Please select item " );
      ii = strlen( ptr );
      ll = ( csp->posit ) - strlen( " [ enter 1,2,... or 0 ] >-> (" ) - TWO ;

      CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

      strcat( ptr, " [ enter 1,2,... or 0 ] >-> [" );

      printf( "\r%s", ptr );

      if( null <= ( csp->dfopt ))
      {
         PRBLDCLR( lotos( csp->dfopt, null, " " ));
         PRNORMAL( "\b" );
      };
/*............................................................................*/
/* enter menu option on keyboard: */

      FGETC(CNS_LNLEN );

      if( ii == null )
         cpt->option = csp->dfopt;
      else
         cpt->option = strtol( ptr, endp, DEC );

      if( null != csp->mflin[ csp->option ] )
      {
         ( csp->mflin[ csp->option ] ) *= ( - ONE );
         goto start;
      };

      if(( null == csp->option )
       &&( null < strlen( csp->cnfrm )))
      {
         CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
         ll = ( csp->posit );
         CNS_BLANCS( null, ll ); /* fill with blancs */

         ptr[ii] = ']';
         ++ii;
         strcat( ptr, " <- ?" );
         printf( "\r%s", ptr );

         CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
         ll = ( csp->lnint );
         CNS_BLANCS( null, ll ); /* indent */
/*
         e.g.: csp->cnfrm: "Do you really want to quit ? "
*/
         strcat( ptr, csp->cnfrm );
         ii = strlen( ptr );
         ptr[ii] = ' ';
         ++ii;

         ll = csp->posit - strlen( " [ enter y/n ] >-> [" ) - TWO;
         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         strcat( ptr, " [ enter y/n ] >-> [" );
         printf( "\r%s", ptr );
         PRBLDCLR( "y");
         PRNORMAL( "\b");

         CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */

         FGETC(CNS_LNLEN);
	 
	 if ( ii == ONE )
	 {
            mm = null;
	    while ( mm < cpt->items )
	    {
/* [ ASCII ( char ) 49 = '1', 50 = '2', 51 = '3',..., 57 = '9' ] */

               ++mm;
	       if ( ptr[null] == ( char )( mm + 48 ))
	       {
                   cpt->option = mm;
		   return cpt;
               };
            };
         };

/* [ ASCII ( char ) 78 = 'N', 110 = 'n' ] */

         if(( ptr[null] == ( char ) 78 )
          ||( ptr[null] == ( char ) 110 ))
         {
            CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
            goto start;
         };
      };
   }; /* end if ( null < csp->items ) */
/*............................................................................*/
/* long integer request: */

   if( null < strlen( csp->rqlng ))
   {
      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      if( LONG_MIN == ( csp->dflng ))
      {
         if( null == strncmp( csp->rqfrm, "brackets", TWO ))
         {
            if( null < ( csp->lglen ))
               ll = ( csp->posit ) + ( csp->lglen ) - ONE;
            else
               ll = ( csp->posit );

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            strcat( ptr, "] <- ?" );
         }
         else if( null == strncmp( csp->rqfrm, "points", TWO )) 
         {
            if( null < ( csp->lglen ))
               ll = ( csp->posit ) + ( csp->lglen ) - ONE;
            else
               ll = ( csp->lnlen ) - ONE;

            CNS_POINTS( ii, ll ); /* fill with blancs */
            ptr[ii] = '?';
         }
         else if( null == strncmp( csp->rqfrm, "blancs", TWO )) 
         {
            if( null < ( csp->lglen ))
               ll = ( csp->posit ) + ( csp->lglen ) - ONE;
            else
               ll = ( csp->lnlen ) - ONE;

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            ptr[ii] = '?';
         }
         else
         {
            if( null < ( csp->lglen ))
               ll = ( csp->posit ) + ( csp->lglen ) - ONE;
            else
               ll = ( csp->posit );

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            strcat( ptr, "] <- ?" );
         };
         printf( "\r%s", ptr );
      }
      else
      { 
         kk = ( csp->lnlen ) - ( csp->posit );
         kk -= ( strlen( lotos( csp->dflng, null, " " )) + FIVE );

         if( kk < null )
            ( csp->posit ) += kk;

         ll = ( csp->posit ) - TWO;
         CNS_BLANCS( null, ll ); /* fill with blancs */

         if( null == strncmp( csp->rqfrm, "brackets", TWO ))
         {
            printf( "\r%s[", ptr );
            strcpy( ptr, lotos( csp->dflng, null, " " ));
            PRBLDCLR( ptr );
            PRNORMAL( "] <- ?" );
         }
         else
         {
            printf( "\r%s[", ptr );
            strcpy( ptr, lotos( csp->dflng, null, " " ));
            PRBLDCLR( ptr );
            PRNORMAL( "] <- ?" );
         };
      };

      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      strcat( ptr, csp->rqlng );
      ii = strlen( ptr );
      ptr[ii] = ' ';
      ++ii;

      if( LONG_MIN == ( csp->dflng ))
      {
         ll = ( csp->posit ) - FOUR;
         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         if( null == strncmp( csp->rqfrm, "brackets", TWO )) 
            strcat( ptr, " [" );
         else if( null == strncmp( csp->rqfrm, "points", TWO )) 
            strcat( ptr, " :" );
         else if( null == strncmp( csp->rqfrm, "blancs", TWO ))
            strcat( ptr, " :" );
         else
            strcat( ptr, " [" );
      }
      else
      {
         ll = ( csp->posit ) - FOUR;
         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         if( null == strncmp( csp->rqfrm, "brackets", TWO )) 
            strcat( ptr, " [" );
         else
            strcat( ptr, " [" );
      };
      printf( "\r%s", ptr );

      FGETC(CNS_LNLEN);

      if( ii == null )
         ( cpt->inlng ) = ( csp->dflng );
      else
         ( cpt->inlng ) = strtol( ptr, endp, DEC );
   };

/*............................................................................*/
/* floating point / double request: */

   if( null < strlen( csp->rqdbl ))
   {
      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      if(( - HUGE_VALF ) == ( csp->dfdbl ))
      {
         if( null == strncmp( csp->rqfrm, "brackets", TWO ))
         {
            if( null < ( csp->dblen ))
               ll = ( csp->posit ) + ( csp->lglen ) - ONE;
            else
               ll = ( csp->posit );

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            strcat( ptr, "] <- ?" );
         }
         else if( null == strncmp( csp->rqfrm, "points", TWO )) 
         {
            if( null < ( csp->dblen ))
               ll = ( csp->posit ) + ( csp->dblen ) - ONE;
            else
               ll = ( csp->lnlen ) - ONE;

            CNS_POINTS( ii, ll ); /* fill with blancs */
            ptr[ii] = '?';
         }
         else if( null == strncmp( csp->rqfrm, "blancs", TWO )) 
         {
            if( null < ( csp->dblen ))
               ll = ( csp->posit ) + ( csp->dblen ) - ONE;
            else
               ll = ( csp->lnlen ) - ONE;

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            ptr[ii] = '?';
         }
         else
         {
            if( null < ( csp->dblen ))
               ll = ( csp->posit ) + ( csp->dblen ) - ONE;
            else
               ll = ( csp->posit );

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            strcat( ptr, "] <- ?" );
         };
         printf( "\r%s", ptr );
      }
      else
      { 
         kk = ( csp->lnlen ) - ( csp->posit );
         kk -= ( strlen( dotos( csp->dfdbl, 7, "e" )) + FIVE );

         if( kk < null )
            ( csp->posit ) += kk;

         ll = ( csp->posit ) - TWO;
         CNS_BLANCS( null, ll ); /* fill with blancs */

         if( null == strncmp( csp->rqfrm, "brackets", TWO ))
         {
            printf( "\r%s[", ptr );
            strcpy( ptr, dotos( csp->dfdbl, 7, "e" ));
            PRBLDCLR( ptr );
            PRNORMAL( "] <- ?" );
         }
         else
         {
            printf( "\r%s[", ptr );
            strcpy( ptr, dotos( csp->dfdbl, 7, "e" ));
            PRBLDCLR( ptr );
            PRNORMAL( "] <- ?" );
         };
      };

      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      strcat( ptr, csp->rqdbl );
      ii = strlen( ptr );
      ptr[ii] = ' ';
      ++ii;

      if(( - HUGE_VALF ) == ( csp->dfdbl ))
      {
         ll = ( csp->posit ) - FOUR;
         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         if( null == strncmp( csp->rqfrm, "brackets", TWO )) 
            strcat( ptr, " [" );
         else if( null == strncmp( csp->rqfrm, "points", TWO )) 
            strcat( ptr, " :" );
         else if( null == strncmp( csp->rqfrm, "blancs", TWO ))
            strcat( ptr, " :" );
         else
            strcat( ptr, " [" );

         ( csp->dfdbl ) = null;
      }
      else
      {
         ll = ( csp->posit ) - FOUR;
         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         if( null == strncmp( csp->rqfrm, "brackets", TWO )) 
            strcat( ptr, " [" );
         else
            strcat( ptr, " [" );
      };
      printf( "\r%s", ptr );

      FGETC(CNS_LNLEN);

      if( ii == null )
         ( cpt->indbl ) = ( csp->dfdbl );
      else
         ( cpt->indbl ) = strtod( ptr, endp );
   };
/*............................................................................*/
/* character string request: */

   if( null < strlen( csp->rqstr ))
   {
      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      if( null == strlen( csp->dfstr ))
      {
         if( null == strncmp( csp->rqfrm, "brackets", TWO ))
         {
            if( null < ( csp->stlen ))
               ll = ( csp->posit ) + ( csp->stlen ) - ONE;
            else
               ll = ( csp->posit );

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            strcat( ptr, "] <- ?" );
         }
         else if( null == strncmp( csp->rqfrm, "points", TWO )) 
         {
            if( null < ( csp->stlen ))
               ll = ( csp->posit ) + ( csp->stlen ) - ONE;
            else
               ll = ( csp->lnlen ) - ONE;

            CNS_POINTS( ii, ll ); /* fill with blancs */
            ptr[ii] = '?';
         }
         else if( null == strncmp( csp->rqfrm, "blancs", TWO )) 
         {
            if( null < ( csp->stlen ))
               ll = ( csp->posit ) + ( csp->stlen ) - ONE;
            else
               ll = ( csp->lnlen ) - ONE;

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            ptr[ii] = '?';
         }
         else
         {
            if( null < ( csp->stlen ))
               ll = ( csp->posit ) + ( csp->stlen ) - ONE;
            else
               ll = ( csp->posit );

            CNS_BLANCS( ii, ll ); /* fill with blancs */
            strcat( ptr, "] <- ?" );
         };
         printf( "\r%s", ptr );
      }
      else
      { 
         kk = ( csp->lnlen ) - ( csp->posit );
         kk -= ( strlen( csp->dfstr ) + FIVE );

         if( kk < null )
            ( csp->posit ) += kk;

         ll = ( csp->posit ) - TWO;
         CNS_BLANCS( null, ll ); /* fill with blancs */

         if( null == strncmp( csp->rqfrm, "brackets", TWO ))
         {
            printf( "\r%s[", ptr );
            strcpy( ptr, csp->dfstr );
            PRBLDCLR( ptr );
            PRNORMAL( "] <- ?" );
         }
         else
         {
            printf( "\r%s[", ptr );
            strcpy( ptr, csp->dfstr );
            PRBLDCLR( ptr );
            PRNORMAL( "] <- ?" );
         };
      };

      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */
      ll = ( csp->lnint );
      CNS_BLANCS( null, ll ); /* indent */

      strcat( ptr, csp->rqstr );
      ii = strlen( ptr );
      ptr[ii] = ' ';
      ++ii;

      if( null == strlen ( csp->dfstr ))
      {
         ll = ( csp->posit ) - FOUR;
         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */

         if( null == strncmp( csp->rqfrm, "brackets", TWO )) 
            strcat( ptr, " [" );
         else if( null == strncmp( csp->rqfrm, "points", TWO )) 
            strcat( ptr, " :" );
         else if( null == strncmp( csp->rqfrm, "blancs", TWO ))
            strcat( ptr, " :" );
         else
            strcat( ptr, " [" );
      }
      else
      {
         ll = ( csp->posit ) - FOUR;
         CNS_ARROW( ii, ll ); /* draw arrow >---...---> */
         if( null == strncmp( csp->rqfrm, "brackets", TWO )) 
            strcat( ptr, " [" );
         else
            strcat( ptr, " [" );
      };
      printf( "\r%s", ptr );

      ii = null;
      CNS_CLSTR( null, STS_SIZE ); /* clear string ptr[] */

      FGETC(CNS_LNLEN);

      if( ii == null )
         strcpy( cpt->instr, csp->dfstr );
      else
         strncpy( cpt->instr, ptr, ii );
   };
/*............................................................................*/
   cpt = clcnsl( csp );  /* clear console input                               */
/*.....................*/
   ( cpt->rtn ) = null;
   return cpt;
}
# undef CNS_CLSTR
# undef CNS_BLANCS
# undef CNS_POINTS
# undef CNS_ARROW
/*============================================================================*/
/************************ end of function txcnsl(*) ***************************/
