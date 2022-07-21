/* [ file: rvise_par.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function rvise_par(*)                                                       *
*                                                                              *
*  This function revises [ and if necessary correts ] the model parameters     *
*  [ input option "parameters" ], thereby respecting the following hierarchy   *
*  from highest to lower priority:                                             *
*                                                                              *
*                          OPERATIONS -> PARAMETERS                            *
*                                                                              *
*  That is, a former input in this order always dominates subsequent inputs    *
*  [ which, of course, only affects conflicting cases ].                       *
*  Also, this function settles any internal parameter dependencies in input    *
*  option "parameters" whenever such dependencies exist.                       *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 11, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# include "../src/PARSTRNGS.M"
# include "../src/FIXPARMTR.M"
/*----------------------------------------------------------------------------*/
# ifndef LINELGTH 
   # define LINELGTH 61
# endif
/*============================================================================*/

short rvise_par( void )
{
   static PARMTRS
     *par = &parmtrs;

   static short
      lln = LINELGTH;

/* prototypes: */

   char
     *lotos ( long nn, char cc, char *format );

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   par = &parmtrs;

   PARSTRNGS( ); /* copy parameter strings and parameters */
/*............................................................................*/

   if ( par->s[3] < par->s[2] )
      par->s[3] = par->s[2];

   if ( par->s[5] < ZERO )
      par->s[5] = ZERO;
   else if ( ONE < par->s[5] )
      par->s[5] = ONE;

   if ( par->s[6] <= ZERO )
      par->s[6] = 1.0e+99;

   if ( par->s[9] < ZERO )
      par->s[9] = ZERO;
   else if ( ONE < par->s[9] )
      par->s[9] = ONE;

   if ( par->s[10] <= ZERO ) 
      par->s[10] = 1.0e+99;

   if ( par->s[20] < ZERO )
      par->s[20] = ZERO;

/* [ to be completed ] */

/* some parameters may be fixed with this macro: */
   
   FIXPARMTR( );

   return null;
}
/*============================================================================*/
/*********************** end of function rvise_par(*) *************************/
