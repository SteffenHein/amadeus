/* [ file: dsplay.h ] */
# define DO_DSPLAY "dsplay(*)"
/*******************************************************************************
*                                                                              *
*   Displays process states [ running cursor function ] and runtime messages   *
*   on screen.                                                                 *
*                                                                              *
*   (C) SHEIN; Munich, December 2021                          Steffen Hein     *
*   [ Update: December 19, 2021 ]                          <contact@sfenx.de>  *
*                                                                              *
*******************************************************************************/
# define DSP_LMRGN_   1 /* left margin */
# define DSP_SIGNS_  76 /* number of monitored signs per line */
# define DSP_LINE__ ( DSP_LMRGN_ + DSP_SIGNS_ + ONE )

# define DSP_FLECHE  45 /* ASCII characters */
# define DSP_POINTE  62
# define DSP_MEET__ 124
# define DSP_TRACE_  46
# define DSP_SHIFT_   1
/*----------------------------------------------------------------------------*/
typedef struct
{
   long
      range;

   char
      sln, /* actual length of string dsplay */ 
      crs; /* actual cursor position         */

   char 
      *dsplay;
        
} DSPLAY;
static DSPLAY disp = {null};

/*============================================================================*/
DSPLAY *
dsplay( const char *messge, const long state, const char option )
{
/* allusions: */
/*
   extern DSPLAY disp;
*/
/* declarations: */

   DSPLAY
      *dsp = &disp;

   static short
      lc = null,
      dc = null,
      cc = null,
      shift;
/*............................................................................*/

   switch( option )
   {
     default: /* move cursor */

      dc = ( char )(( DSP_SIGNS_ * state ) / dsp->range );
      dc -= ( dsp->crs );

      if ( dc < null )
         return dsp;
/*............................................................................*/

      dc += shift;
      cc = null;
      while ( cc < dc )
      {
         if(( dsp->crs ) <= ( dsp->sln - shift )) 
         {                                     /* sln = strlen( dsp->dsplay ) */
            printf( "%c%c\b", dsp->dsplay[dsp->crs+shift], DSP_POINTE );
         }
         else 
         {
            ( dsp->dsplay[dsp->crs] ) = DSP_FLECHE;
            printf( "%c%c\b", DSP_FLECHE, DSP_POINTE );
         };
         ( dsp->crs )++ ;
         cc++ ;
      };

      return dsp;
/*............................................................................*/

     case null: /* clear display line */

      printf( "\r" );

      cc = null;
      while( cc <= DSP_LINE__ )
      {
         printf( " " );
         cc++ ;
      };
      printf( "\r" );

      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         printf( " " );
         cc++ ;
      };

      if( messge != null )
         printf( "\r %s", messge );

      ( dsp->crs ) = null;
      ( dsp->sln ) = null;

      return dsp;
/*............................................................................*/

     case 's': /* display start message, initialize struct dsp  */
     case 'S':

      printf( "\r" );

      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         printf( " " );
         cc++ ;
      };
      printf( "%s\n", messge );

      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         printf( " " );
         cc++ ;
      };
      while( cc < DSP_LINE__ )
      {
         printf( "%c", DSP_TRACE_ );
         cc++ ;
      };
      printf( "%c\r", DSP_MEET__ );

      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         printf( " " );
         cc++ ;
      };
      printf( "%c", DSP_MEET__ );

      ( dsp->crs ) = null;
      ( dsp->sln ) = null;
      ( dsp->dsplay ) = ( char * ) calloc( STS_SIZE, ONE );
      shift = DSP_SHIFT_;

      return dsp;
/*............................................................................*/

     case 'm': /* display restart message, left to cursor       */
     case 'M': /* [ right from former text, which is retained ] */

      lc = strlen( messge );
      dc = dsp->crs - lc + ONE;

      if( dc < dsp->sln )
         dc = dsp->sln;

      cc = null;
      while( cc < lc )
      {
         dsp->dsplay[dc+cc] = messge[cc];
         cc++ ;
      };

      dsp->sln = strlen( dsp->dsplay );
      dsp->dsplay[dsp->sln] = DSP_FLECHE;

      printf( "\r" );

# if null < DSP_LMRGN_ 
      cc = null;
      while( cc < DSP_LMRGN_ )
      {
         printf( " " );
         cc++ ;
      }; 
# endif

      cc = null;
      while( cc < dsp->sln )
      {
         if( cc < dsp->crs )
            printf( "%c", dsp->dsplay[cc+shift] );
         else if( cc == dsp->crs )
            printf( "%c", DSP_POINTE );
         else if( dsp->crs < cc )
            printf( "%c", dsp->dsplay[cc] );
         cc++ ;
      };
      while ( dsp->crs < cc )
      {
         printf( "\b" );
         cc-- ;
      };

      return dsp;
   }; /* end switch( option ) */
}
/*============================================================================*/
# undef DSP_LMRGN_
# undef DSP_SIGNS_
# undef DSP_LINE__
# undef DSP_FLECHE
# undef DSP_POINTE
# undef DSP_MEET__
# undef DSP_TRACE_
# undef DSP_SHIFT_
/************************* end of function dsplay(*) **************************/
