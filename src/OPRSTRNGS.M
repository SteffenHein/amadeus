/* [ file: OPRSTRNGS.M ] */
/* Update: June 17, 2022 */
/*============================================================================*/
# define OPRSTRNGS( ) \
{ \
   opr->n[null] = 10; /* the number of operation parameters */ \
/*..........................................................................*/ \
/* the operation parameter strings, something like that: */ \
 \
/* write only connected (!) strings in the string copy function strcpy(*) */ \
/* [ 2nd. argument       | ]  */ \
/*                       V    */ \
/* strcpy( opr->ntx[0], "computation_modes" ); */ \
/*..........................................................................*/ \
 \
   strcpy( opr->ntx[0], \
      "operation_parameters" ); \
 \
   cpylne( opr->ntx[1], \
      "maximum_number_of_outer_iterations", "<=100000", ll ); \
 \
   cpylne( opr->ntx[2], \
      "number_of_inner_iterations", "1-100", ll ); \
 \
   cpylne( opr->ntx[3], \
      "reproduction_factor", "basic:0_|_current:1_|_fixed:2", ll ); \
 \
   cpylne( opr->ntx[4], \
      "reproduction_factor_modulation_mode", "0,1,...4", ll ); \
 \
   cpylne( opr->ntx[5], \
      "random_burst_mode", "shift:0_|_slats:1", ll ); \
 \
   cpylne( opr->ntx[6], \
    	  "x-units", "transmission_cycles:0_|_days:1", ll ); \
 \
   cpylne( opr->ntx[7], \
    	  "y-units", "normalized:0/2_|_conventional:1/3", ll ); \
 \
   cpylne( opr->ntx[8], \
    	  "y-scale", "linear:0_|_logarithmic:1", ll ); \
 \
   cpylne( opr->ntx[9], \
      "[0]_1:_[don't]_write_titles_on_graphics", "0/1", ll ); \
 \
   cpylne( opr->ntx[10], \
          "[0]_1:_[don't]_stop_when_no_sick_individuals_remain", "0/1", ll ); \
}
/*============================================================================*/
