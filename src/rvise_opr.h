/* [ file: rvise_opr.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A simple numerical Model Approximating the Development of Epidemics         *
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
*  [ Update: January 01, 2022 ]                             <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# ifndef OPR_SSTRNG
   # include "../src/OPRSTRNGS.M"
# endif
/*----------------------------------------------------------------------------*/
# ifndef LINLEN
   # define LINLEN 58
# endif
/*============================================================================*/

short rvise_operts( void )
{
/* declarations: */

   AMDSTATE 
     *state = &amdstat;

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
   ( state->opr ) = &opertns;

   opr->n[null] = 8; /* the number of operation parameters */
/*............................................................................*/
/* the operation parameter strings, something like that: */

/* write only connected (!) strings in the string copy function strcpy(*) */
/* [ 2nd. argument       | ]  */
/*                       V    */
/* strcpy( opr->ntx[0], "computation_modes" ); */
/*............................................................................*/

   cpylne( opr->ntx[1],
              "maximum_number_of_outer_iterations",
    	         "<=100000", ll );
		  
   cpylne( opr->ntx[2],
              "number_of_inner_iterations", 
	         "1-100", ll );
		  
   cpylne( opr->ntx[3],
              "formula_0,1,2",
                 "_0:_input_is_BASIC/_else:_CURRENT/_repr._no.", ll );

   cpylne( opr->ntx[4],
              "x-scale",
    	         "transmission_time:0_|_days:1", ll );

   cpylne( opr->ntx[5],
              "y-scale",
    	         "linear:0_|_logarithmic:1", ll );

   cpylne( opr->ntx[6],
              "y-units",
    	         "normalized_(herd_size=1):0_|_conventional_units:1", ll );

   cpylne( opr->ntx[7],
             "[0]_1:_[don't]_write_titels_on_graphics",
    	        "0/1", ll );

   cpylne( opr->ntx[8],
             "[0]_1:_[don't]_stop_when_no_sick_individuals_remain",
    	        "0/1", ll );
/*............................................................................*/
   ii = 4; do
   {
      if ( opr->n[ii] != null )
         opr->n[ii] = ONE;
      ii++;
   } while ( ii < 9 );

   return null;
}
/*============================================================================*/
/*********************** end of function rvise_opr(*) *************************/
