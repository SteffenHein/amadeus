/* [ file: rvise_par.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A plain numerical Model Approximating the Development of Epidemics          *
*  Under varied conditions if Spread                                           *
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
*  [ Update: May 07, 2022 ]                                 <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# include "../src/PARSTRNGS.M"
/*----------------------------------------------------------------------------*/
# undef LINLEN
   # define LINLEN 56
/*============================================================================*/

short rvise_par( void )
{
   static PARMTRS
     *par = &parmtrs;

   static short
      ll = LINLEN;
/*
   short 
      ii = null;

   double 
      dd = 0.;

   static char
      ptr[STS_SIZE] = {null};
*/
/* prototypes: */

   char
     *lotos ( long nn, char cc, char *format );

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   par = &parmtrs;

   PARSTRNGS( ); /* copy number of parameters and parameter strings */
/*............................................................................*/

   if ( par->s[3] < par->s[2] )
      par->s[3] = par->s[2];

   if (  par->s[13] < 0. )
      par->s[13] = 0.;

   if ( 1. < par->s[7] )
      par->s[7] = 1.;
   else if ( par->s[7] <= 0. )
      par->s[7] = 1.;

   return null;
}
/*============================================================================*/
# undef LINLEN
/*********************** end of function rvise_par(*) *************************/
