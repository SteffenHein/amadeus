/* [ file: rvise_opr.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function rvise_opr(*)                                                       *
*                                                                              *
*  This function revises [ and if necessary correts ] the operation parameters *
*  [ input option "operation" ], thereby respecting the following hierarchy    *
*  from highest to lower priority:                                             *
*                                                                              *
*                          OPERATIONS -> PARAMETERS                            *
*                                                                              *
*  That is, a former input in this order always dominates subsequent inputs    *
*  [ which, of course, only affects conflicting cases ].                       *
*  Also, this function settles any internal parameter dependencies in input    *
*  option "operation" whenever such dependencies exist.                        *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 04, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# include "../src/OPRSTRNGS.M"
# include "../src/FIXOPERTN.M"
/*----------------------------------------------------------------------------*/
# ifndef LINELGTH 
   # define LINELGTH 61
# endif
/*============================================================================*/

short rvise_opr( void )
{
/* declarations: */

   static OPERTNS
     *opr = &opertns;

   static short
      ii = null,  
      lln = LINELGTH;

/* prototypes: */

   char
     *lotos ( long nn, char cc, char *format );

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   opr = &opertns;

   OPRSTRNGS( ); /* copy number of operation parameters and parameter strings */
/*............................................................................*/
/* x-units [ transmission cycles ('natural'): 0, days: 1 ] */

   if ( opr->n[1] != null )
      opr->n[1] = ONE;

/* y-units [ normalized: 0 or 2, conventional: 1 or 3 ] */

   if ( opr->n[2] != null )
      opr->n[2] = ONE;

/* y-scale [ linear:0 , logarithmic: 1 ] */

   if ( opr->n[3] != null )
      opr->n[3] = ONE;

/* [don't] write titles on graphics */

   if ( opr->n[4] != null )
      opr->n[4] = ONE;
      
/* [don't] stop when no sick individuals remain */

   if ( opr->n[5] != null )
      opr->n[5] = ONE;

/* [don't] weight recovery history */

   if ( opr->n[6] != null )
      opr->n[6] = ONE;

/* [don't] weight vaccination history */

   if ( opr->n[7] != null )
      opr->n[7] = ONE;

/* reproduction factor [ to be read as ... */
/* ... basic: 0 /current: 1 /constant: 2 ] */

   ii = opr->n[8];
   switch( ii )
   { 
     default:
      opr->n[8] = null;
      break;
     
     case 1: case 2:
      break;
   };

/* reproduction factor modulation mode [ 0,...,4] */     

   ii = opr->n[9];
   switch( ii )
   { 
     default:
      opr->n[9] = null;
      break;
     
     case 1: case 2: case 3: case 4:
      break;
   };

/* random burst mode [ shifts: 0, slats: 1 ] */

   if ( opr->n[10] != null )
      opr->n[10] = ONE;

/* minimum/maximum number of outer iterations */

   if ( 100000 < opr->n[11] )
      opr->n[11] = 100000;
   else if ( opr->n[11] < ONE )
      opr->n[11] = 100000;

/* minimum/maximum number of inner iterations */ 

   if ( 100 < opr->n[12] ) 
      opr->n[12] = 100;
   else if ( opr->n[12] < ONE )
      opr->n[12] = ONE;

/* some operation parameters may be fixed with this macro: */

   FIXOPERTN( );

   return null;
}
/*============================================================================*/
/*********************** end of function rvise_opr(*) *************************/
