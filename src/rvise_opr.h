/* [ file: rvise_opr.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A plain numerical Model Approximating the Development of Epidemics          *
*  Under varied conditions if Spread                                           *
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
*  [ Update: February 05, 2022 ]                            <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# include "../src/OPRSTRNGS.M"
/*----------------------------------------------------------------------------*/
# undef LINLEN
   # define LINLEN 61
/*============================================================================*/

short rvise_opr( void )
{
/* declarations: */

   static OPERTNS
     *opr = &opertns;

   static short
      ii = null,  
      ll = LINLEN;

/* prototypes: */

   char
     *lotos ( long nn, char cc, char *format );

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   opr = &opertns;

   OPRSTRNGS( ); /* copy number of operation parameters and parameter strings */
/*............................................................................*/
   if ( 100000 < opr->n[1] )
      opr->n[1] = 100000;
   else if ( opr->n[1] < ONE )
      opr->n[1] = 100000;

   if ( 100 < opr->n[2] )
      opr->n[2] = 100;
   else if ( opr->n[2] < ONE )
      opr->n[2] = ONE;

   ii = opr->n[3];
   switch( ii )
   { 
     default:
      opr->n[3] = null;
      break;
     
     case 1:
      break;

     case 2:
      break;
   };
     
   ii = 3; do
   {
      ++ii;
      if ( opr->n[ii] != null )
         opr->n[ii] = ONE;
   } while ( ii < 5 );

   ii = opr->n[5];
   switch( ii )
   { 
     default:
      opr->n[5] = null;
      break;

     case 1:
      break;

     case 2:
      break;

     case 3:
      break;
   };

   ii = 6; do
   {
      ++ii;
      if ( opr->n[ii] != null )
         opr->n[ii] = ONE;
   } while ( ii < 8 );

   return null;
}
# undef LINLEN
/*============================================================================*/
/*********************** end of function rvise_opr(*) *************************/
