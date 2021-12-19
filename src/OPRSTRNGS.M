/* [ file: OPRSTRNGS.M ] */
/* Update: December 06, 2021 */
/*---------------------------------------------------------------------------*/
# define OPRSTRNGS( ) \
{ \
/* the operation parameter strings: */ \
 \
/* write only connected (!) strings in the string copy function strcpy(*) */ \
/* [ 2nd. argument       | ]  */ \
/*                       V    */ \
   strcpy( opr->ntx[0], \
      "computation_modes" ); \
   cpylne( opr->ntx[1], \
          "maximum_number_of_outer_iterations", "<=100000", ll ); \
   cpylne( opr->ntx[2], \
          "number_of_inner_iterations", "1-100", ll ); \
   cpylne( opr->ntx[3], \
          "the_formula", "0,1_or_2", ll ); \
   cpylne( opr->ntx[4], \
          "[1]_0:_[don't]_stop_when_there_are_no_more_sick_persons", \
							    "0/1", ll ); \
   cpylne( opr->ntx[5], \
    	  "x-scale", "days:1_|_transmission_time:2", ll ); \
   cpylne( opr->ntx[6], \
    	  "y-scale", "linear:1_|_logarithmic:2", ll ); \
   cpylne( opr->ntx[7], \
    	  "y-units", "conventional:1_|_normalized:2", ll ); \
}
