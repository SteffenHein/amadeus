/* [ file: dsplay.c ] */
# define DO_DSPLAY "dsplay(*)"
/*******************************************************************************
*                                                                              *
*   Displays process states [ running cursor function ] and runtime messages   *
*   on screen.                                                                 *
*                                                                              *
*   (C) SHEIN; Munich, April 2020                             Steffen Hein     *
*   [ Update: July 01, 2022 ]                              <contact@sfenx.de>  *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 0 /* set to 1: if POSIX.1 standard headers will be used*/
/*----------------------------------------------------------------------------*/
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
/*----------------------------------------------------------------------------*/
# include "../math/maths.h"
# include "../math/consts.h"
# include "../disp/scropr.h"
/*----------------------------------------------------------------------------*/
# include "../CONFIG.H"
/*----------------------------------------------------------------------------*/
# define DSP_CMODE_ 1 /* running cursor implementation [ mode 0, 1 or 2 ] */ 
/*----------------------------------------------------------------------------*/
# define DSP_RMRGN_   1 /* right margin */
# define DSP_LMRGN_   1 /* left margin */
# define DSP_SIGNS_  78 /* monitored number of charcters */
# define DSP_LINE__ ( DSP_SIGNS_ + DSP_RMRGN_ + DSP_LMRGN_ )
# define DSP_FXPREC   3 /* fixed point precision of percent indication */

# define DSP_FLECHE  45 /* ASCII character '-' */
# define DSP_POINTE  62 /* ASCII character '>' */
# define DSP_MEET__ 124 /* ASCII character '|' */
# define DSP_TRACE_  32 /* ASCII characters 32 = ' ' or 46 = '.' */
# define DSP_EQUAL_  61 /* ASCII character '=' */
/*----------------------------------------------------------------------------*/
# ifndef USE_NCURSES
   # define USE_NCURSES 0 /* =1: my_terminal window [ BSD, Linux ]            */
# endif
/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
/* 'my_terminal' configuration: */

   # include <termcap.h> /* terminal type headers */
   # include <term.h>

   static char *term = {null}; /* terminal type string */

   # define CLSCREEN /* clear screen */\
   {\
      fprintf(( dsp->display ), "%s", tgetstr( "cl", null ));\
   }

   # define PRBLDCLR(a) /* bold clear output */\
   {\
      fprintf(( dsp->display ), "%s%s", tgetstr( "md", null ), (a));\
   }

   # define PRINVERS(a) /* inverse: black <-> white */\
   {\
      fprintf(( dsp->display ), "%s%s", tgetstr( "mr", null ), (a));\
   }

   # define PRNORMAL(a) /* back to normal output */\
   {\
      fprintf(( dsp->display ), "%s%s", tgetstr( "me", null ), (a));\
   }
# else
   # define CLSCREEN /* clear screen */\
   {\
      fprintf(( dsp->display ), "\f" );\
   }

   # define PRBLDCLR(a) \
   {\
      fprintf(( dsp->display ), "%s", (a));\
   }

   # define PRINVERS(a) \
   {\
      fprintf(( dsp->display ), "%s", (a));\
   }

   # define PRNORMAL(a) \
   {\
      fprintf(( dsp->display ), "%s", (a));\
   }
# endif
/*----------------------------------------------------------------------------*/
/*
*//* # include "dsptyp.h" 
*//* i.e. the following:
*/
typedef struct
{
   char 
      rtn;

   char 
      option,
      messge[LGS_SIZE];

   short
      rcsps; /* relative curser position */
   
   long
      fleps, /* file position pointer [ fleps = ftell(*) etc. ] */
      state,
      range;

   FILE 
     *display;

} DSPLAY;
static DSPLAY disp = {null};
/*----------------------------------------------------------------------------*/
static int unbuff     = _IONBF;
static size_t bufsize =  null;
/*============================================================================*/

DSPLAY *\
dsplay( DSPLAY *dsp )
{
  static DSPLAY
    *rpt = &disp;

  static char
      cr = null,
      arrow = null,
      dsplay[LGS_SIZE] = {null};

  static short
      lc = null,
      cc = null,
      sln = null, /* length of new string under running cursor */ 
      slp = null, /* length of previous string */ 
      crs = null; /* the actual cursor position */

  static double
      pc = ZERO;

  static char
     pcs[STS_SIZE] = {null};

  char *dotos ( double xx, char precision, char *format );
/*---------------------------------------------------------------------------*/
   ( rpt->rtn ) = null;

   if( dsp == null ) /* initialize terminal buffer and struct DSPLAY */
   {
/* set buffer length to null: */

      setvbuf( stdout, null, unbuff, bufsize );
/*............................................................................*/
# if USE_NCURSES == 1
/* get the terminal type: */

      term = ( char *) getenv( "TERM" );

      if ( *term != null )
      {
         cc = tgetent( null, term );

         if( ONE != cc )
         {
            fprintf( stderr, "Error on getting the termcap info\n" );
            exit( EXIT_FAILURE );
         };
      };
# endif
/*............................................................................*/
      ( rpt->display ) = stdout;
      ( rpt->option ) = null;
      ( rpt->state ) = null;
      ( rpt->range ) = null;
      ( rpt->fleps ) = null;
      ( rpt->rcsps ) = null;

      cc = null;
      while ( cc < LGS_SIZE )
      {
	 dsplay[cc] = null;
         ( rpt->messge[cc] ) = null;
         cc++ ;
      };

      cc = null;
      cr = null;
      lc = null;
      sln = null;
      slp = null;
      crs = null;
      pc = ZERO;
      
      return rpt;
/*............................................................................*/
   }
   else
      rpt = dsp;
/*............................................................................*/

   switch( dsp->option )
   {
/*............................................................................*/
# if (( DSP_CMODE_ == 0 ) \
    ||( DSP_CMODE_ == 1 ))

     default: /* write running cursor [ evtlly into  any message ] */

      if (( dsp->range ) != null )
      {
	 lc = DSP_SIGNS_ - ONE;
         crs = ( int )(( lc*( dsp->state )) / ( dsp->range ));

         if( crs <= ( dsp->rcsps ))
            return rpt;
         else if ( lc < crs )
            return rpt;
/*............................................................................*/
         arrow = DSP_FLECHE;

/* rotate helix: */

	 if ( null < DSP_LMRGN_ )
	 {
            switch ( cr )
            {
              case 0:
               cr = 124; /* 124: ASCII character '|' */
               break;

              case 124:
               cr = 47; /* 47: ASCII character '/' */
               break;

              case 47:
               cr = 45; /* 45: ASCII character '-' */
               break;

              case 45:
               cr = 92; /* 97: ASCII character '\' */
               break;

              case 92:
               cr = 124;
               break;
            };
         }
	 else
            cr = 32; /* 32: ASCII character space */

/* write message on display: */

         fprintf(( dsp->display ), "\r" );

         cc = null;
         while ( cc < ( DSP_LMRGN_-ONE ))
         {
           fprintf(( dsp->display ), "%c", 32 );
            cc++;
         };

         PRBLDCLR( "" );
         fprintf( dsp->display, "%c", cr );
         PRNORMAL( "" );

         cc = null;
         while ( cc < crs )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };

         PRBLDCLR( "" );
         fprintf( dsp->display, "%c\b", DSP_POINTE );
         PRNORMAL( "" );

         while ( cc < sln )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };
         while ( cc < lc )
         {
            dsplay[cc] = arrow;
            cc++;
         };

         ( rpt->rcsps ) = crs; /* the new cursor position */

         return rpt;
      }
      else
         return rpt;

      break;
/*............................................................................*/
# else /* if DSP_CMODE != 0,1 */

     default: /* write running cursor [ evtlly into  any message ] */

      if (( dsp->range ) != null )
      {
	 lc = DSP_SIGNS_ - ONE;
         crs = ( int )(( lc*( dsp->state )) / ( dsp->range ));

         if( crs <= ( dsp->rcsps ))
            return rpt;
         else if ( lc < crs )
            return rpt;
/*............................................................................*/
         arrow = DSP_FLECHE;

/* rotate helix: */

         fprintf( dsp->display, "\r" );

	 if ( null < DSP_LMRGN_ )
	 {
            switch ( cr )
            {
              case 0:
               cr = 124; /* 124: ASCII character '|' */
               break;

              case 124:
               cr = 47; /* 47: ASCII character '/' */
               break;

              case 47:
               cr = 45; /* 45: ASCII character '-' */
               break;

              case 45:
               cr = 92; /* 97: ASCII character '\' */
               break;

              case 92:
               cr = 124;
               break;
            };
         }
	 else
            cr = 32; /* 32: ASCII character space */

/* write message on display: */

         fprintf(( dsp->display ), "\r%*c", DSP_LMRGN_, 124 );

         cc = null;
         while ( cc < ( dsp->rcsps ))
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };
         fprintf(( dsp->display ), "%c", 32 );
         while ( cc < sln )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };

/* write cursor on new position [ eventually into message ]: */

         fprintf( dsp->display, "\r" );

         cc = ONE;
         while ( cc < DSP_LMRGN_ )
         {
            fprintf(( dsp->display ), "%c", 32 );
	    cc++;
         };

         PRBLDCLR( "" );
         fprintf( dsp->display, "\r%c", cr );
         PRNORMAL( "" );

         cc = null;
         while ( cc < crs )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
	    cc++;
         };

         PRBLDCLR( "" );
         fprintf( dsp->display, "%c\b", DSP_POINTE );
         PRNORMAL( "" );

	 cc = sln;
         while ( cc < lc )
         {
            dsplay[cc] = arrow;
            cc++;
         };
	 
	 ( dsp->rcsps ) = crs; /* the new cursor position */
         return rpt;
      }
      else
         return rpt;

      break;
/*............................................................................*/
# endif /* if DSP_CMODE != 0,1 */
/*............................................................................*/
# if DSP_CMODE_ == 0

     case 'c': /* move cursor and display percent state [ mode 2 ] */
     case 'C':

      if (( dsp->range ) != null )
      {
         lc = ( DSP_SIGNS_ - ( DSP_FXPREC+FIVE ));
         crs = ( int )(( lc*( dsp->state )) / ( dsp->range ));

         if( crs <= ( dsp->rcsps ))
            return rpt;
         else if ( lc < crs )
            return rpt;
/*............................................................................*/
         arrow = DSP_EQUAL_;

/* rotate helix: */

         switch ( cr )
         {
           case 0:
            cr = 124; /* 124: ASCII character '|' */
            break;

           case 124:
            cr = 47; /* 47: ASCII character '/' */
            break;

           case 47:
            cr = 45; /* 45: ASCII character '-' */
            break;

           case 45:
            cr = 92; /* 97: ASCII character '\' */
            break;

           case 92:
            cr = 124;
            break;
         };

/* compute and write percent value: */      

         pc = 100.* ( double )( dsp->state ) / ( dsp->range );

         pcs[0] = cr;
         pcs[1] = null;
         strcat( pcs, "[" );
         strcat( pcs, ( dotos( pc, DSP_FXPREC, "fixed" )));
         strcat( pcs, "%]" );

         fprintf(( dsp->display ), "\r" );

         PRBLDCLR( "" );
         fprintf(( dsp->display ), "\r%*s", ( DSP_SIGNS_ + DSP_LMRGN_ ), pcs );
         PRNORMAL( "" );

/* write complete message on display: */

         fprintf(( dsp->display ), "\r" );

         cc = null;
         while ( cc < DSP_LMRGN_ )
         {
            fprintf(( dsp->display ), "%c", 32 );
            cc++;
         };

         cc = null;
         while ( cc < crs )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };

         PRBLDCLR( "" );
         fprintf( dsp->display, "%c", DSP_POINTE );
         PRNORMAL( "" );

         while ( cc < sln )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };
         while ( cc < lc )
         {
            dsplay[cc] = arrow;
            cc++;
         };

         fprintf( dsp->display, "\b" );

         ( rpt->rcsps ) = crs; /* the new cursor position */

         return rpt;
      }
      else
         return rpt;

      break;
/*............................................................................*/
# elif DSP_CMODE_ == 1

     case 'c': /* move cursor and display percent state [ mode 2 ] */
     case 'C':

      if (( dsp->range ) != null )
      {
         lc = ( DSP_SIGNS_ - ( DSP_FXPREC+FIVE ));
         crs = ( int )(( lc*( dsp->state )) / ( dsp->range ));

         if( crs <= ( dsp->rcsps ))
            return rpt;
         else if ( lc < crs )
            return rpt;
/*............................................................................*/
         arrow = DSP_EQUAL_;

/* rotate helix: */

         switch ( cr )
         {
           case 0:
            cr = 124; /* 124: ASCII character '|' */
            break;

           case 124:
            cr = 47; /* 47: ASCII character '/' */
            break;

           case 47:
            cr = 45; /* 45: ASCII character '-' */
            break;

           case 45:
            cr = 92; /* 97: ASCII character '\' */
            break;

           case 92:
            cr = 124;
            break;
         };

/* compute percent value: */      

         pc = 100.* ( double )( dsp->state ) / ( dsp->range );

         pcs[0] = cr;
         pcs[1] = null;
         strcat( pcs, "[" );
         strcat( pcs, ( dotos( pc, DSP_FXPREC, "fixed" )));
         strcat( pcs, "%]" );

/* write complete message on display: */

         fprintf(( dsp->display ), "\r" );

         cc = null;
         while ( cc < DSP_LMRGN_ )
         {
            fprintf(( dsp->display ), "%c", 32 );
            cc++;
         };

         cc = null;
         while ( cc < crs )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };

         PRBLDCLR( "" );
         fprintf( dsp->display, "%c", DSP_POINTE );
         PRNORMAL( "" );

         while ( cc < sln )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };
         while ( cc < lc )
         {
            fprintf(( dsp->display ), "%c", DSP_TRACE_ );
            dsplay[cc] = arrow;
            cc++;
         };

         PRBLDCLR( "\b" );
         if ( lc <= crs )
            fprintf(( dsp->display ), "%c", DSP_POINTE );
         else
            fprintf(( dsp->display ), "%c", pcs[null] );

         cc = ONE;
         while ( cc < 8 )
         {
            fprintf(( dsp->display ), "%c", pcs[cc] );
            cc++;
         };
         PRNORMAL( "" );

         ( rpt->rcsps ) = crs; /* the new cursor position */

         return rpt;
      }
      else
         return rpt;

      break;
/*............................................................................*/
# else /* if DSP_CMODE_ != 1,2 */

     case 'c': /* move cursor and display percent state */
     case 'C':

      if (( dsp->range ) != null )
      {
         lc = ( DSP_SIGNS_ - ( DSP_FXPREC+FIVE ));
         crs = ( int )(( lc*( dsp->state )) / ( dsp->range ));

         if( crs <= ( dsp->rcsps ))
            return rpt;
         else if ( lc < crs ) 
            return rpt;
/*............................................................................*/
         arrow = DSP_EQUAL_;

/* rotate helix: */

         switch ( cr )
         {
           case 0:
            cr = 124; /* 124: ASCII character '|' */
            break;

           case 124:
            cr = 47; /* 47: ASCII character '/' */
            break;

           case 47:
            cr = 45; /* 45: ASCII character '-' */
            break;

           case 45:
            cr = 92; /* 97: ASCII character '\' */
            break;

           case 92:
            cr = 124;
            break;
         };

/* compute and write percent value: */      

         pc = 100.* ( double )( dsp->state ) / ( dsp->range );

         pcs[0] = cr;
         pcs[1] = null;
         strcat( pcs, "[" );
         strcat( pcs, ( dotos( pc, DSP_FXPREC, "fixed" )));
         strcat( pcs, "%]" );
	 
         PRBLDCLR( "" );
         fprintf(( dsp->display ), "\r%*s", ( DSP_SIGNS_ + DSP_LMRGN_ ), pcs );
         PRNORMAL( "" );

/* write complete message on display: */

         fprintf(( dsp->display ), "\r%*c", DSP_LMRGN_, 124 );
         cc = null;
         while ( cc < ( dsp->rcsps ))
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };
         fprintf(( dsp->display ), "%c", 32 );
         while ( cc < sln )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
            cc++;
         };

/* write cursor on new position [ eventually into message ]: */

         fprintf(( dsp->display ), "\r" );
         cc = null;
         while ( cc < DSP_LMRGN_ )
         {
            fprintf(( dsp->display ), "%c", 32 );
	    cc++;
         };
         cc = null;
         while ( cc < crs )
         {
            fprintf(( dsp->display ), "%c", dsplay[cc] );
	    cc++;
         };

         PRBLDCLR( "" );
         fprintf( dsp->display, "%c\b", DSP_POINTE );
         PRNORMAL( "" );

         cc = sln;
         while ( cc < lc )
         {
            dsplay[cc] = arrow;
            cc++;
         };

         ( rpt->rcsps ) = crs; /* the new cursor position */

         return rpt;
      }
      else
         return rpt;

      break;
/*............................................................................*/

# endif /* DSP_CMODE_ == 1 */
/*............................................................................*/

     case 'p': /* only display percent state */
     case 'P':

      if (( dsp->range ) != null )
      {
         crs = ( int ) DSP_SIGNS_ * ( dsp->state ) / ( dsp->range );

         if( crs == ( dsp->rcsps ))
            return rpt;
         else
            ( rpt->rcsps ) = crs;
      }
      else
         return rpt;
/*............................................................................*/

      pc = 100.* ( double )( dsp->state ) / ( dsp->range );
      fseek( dsp->display, ( dsp->fleps ), SEEK_SET );
      fprintf( dsp->display,
         " [>>->%s%%]", ( dotos( pc, DSP_FXPREC, "fixed" )));

      break;
/*............................................................................*/
     case null: /* clear display line */

      fprintf( dsp->display, "\r" );

      cc = null;
      while( cc < DSP_LINE__ )
      {
         fprintf( dsp->display, " " );
         cc++ ;
      };

      fprintf( dsp->display, "\r" );

      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         fprintf( dsp->display, " " );
         cc++ ;
      };

      if(( dsp->messge ) != null )
         fprintf( dsp->display, "\r %s", ( dsp->messge ));

      lc = null;
      crs = null;
      crs = null;
      sln = null;
      arrow = null;

      break;
/*............................................................................*/
     case 's': /* dsp->display start message, initialize struct dsp */
     case 'S':

      crs = null; /* reset cursor position */
      sln = null; /* reset length of cursor message */
      
      fprintf( dsp->display, "\r" );

      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         fprintf( dsp->display, "%c", 32 );
         cc++ ;
      };

      PRBLDCLR( "" );
      fprintf( dsp->display, "%s\n", ( dsp->messge ));
      PRNORMAL( "" );

      arrow = DSP_TRACE_;

      break;
/*............................................................................*/
     case 't': /* dsp->display termination message, initialize struct dsp */
     case 'T':

      fprintf( dsp->display, "\r" );

      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         fprintf( dsp->display, "%c", 32 );
         cc++ ;
      };

      PRBLDCLR( "" );
      fprintf( dsp->display, "%s", ( dsp->messge )); 
      PRNORMAL( "" );

      arrow = DSP_TRACE_;

      break;
/*............................................................................*/
     case 'm': /* dsp->display restart message, left to cursor  */
     case 'M': /* [ right from former text, which is retained ] */

      ( rpt->rcsps ) = null;
      sln = strlen( dsp->messge );

      cc = null;
      while( cc < sln )
      {
         dsplay[cc] = ( dsp->messge[cc] );
         cc++ ;
      };
      while( cc < DSP_SIGNS_ )
      {
         dsplay[cc] = arrow;
         cc++ ;
      };

      if ( sln != slp )
      {
         slp = sln;

         fprintf( dsp->display, "\r" );
	 cc = null;
         while( cc < DSP_LMRGN_ )
         {
            fprintf(( dsp->display ), "%c", 32 );
	    cc++ ;
         };
	 cc = null;
         while( cc < sln )
         {
            fprintf( dsp->display, "%c", dsplay[cc] );
	    cc++ ;
         };
         lc = DSP_SIGNS_ - ONE;
         while( cc < lc )
         {
            cc++ ;
            fprintf( dsp->display, "%c", DSP_TRACE_ );
         };
         fprintf( dsp->display, "%c\r", DSP_MEET__ );
      };

      break;
/*............................................................................*/

     case 'd': /* dsp->display the message */
     case 'D':

      lc = strlen( dsp->messge );
      crs = DSP_SIGNS_ - DSP_LMRGN_;

      fprintf( dsp->display, "\r" );
      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         fprintf( dsp->display, "%c", 32 );
         cc++ ;
      };
      cc = null;
      while (( cc <= crs )&&( cc <= lc ))
      {
         fprintf( dsp->display, "%c", ( dsp->messge[cc] ));
         cc++ ;
      };

      break;
   }; /* end switch( dsp->option ) */

   return rpt;
}
/*============================================================================*/
# undef DSP_LMRGN_
# undef DSP_SIGNS_
# undef DSP_FXPREC
# undef DSP_LINE__
# undef DSP_FLECHE
# undef DSP_EQUAL_
# undef DSP_POINTE
# undef DSP_MEET__
# undef DSP_TRACE_
/************************* end of function dsplay(*) **************************/
