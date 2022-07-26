/* [ file: OPRSTRNGS.M ] */
/* Update: July 21, 2022 */
/*============================================================================*/
# define OPRSTRNGS( ) \
{ \
   opr->n[null] = 12; /* the number of operation parameters */ \
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
    	  "x-units", "transmission_cycles:0_|_days:1", lln ); \
 \
   cpylne( opr->ntx[2], \
    	  "y-units", "normalized:0/2_|_conventional:1/3", lln ); \
 \
   cpylne( opr->ntx[3], \
    	  "y-scale", "linear:0_|_logarithmic:1", lln ); \
 \
   cpylne( opr->ntx[4], \
      "[0]_1:_[don't]_write_titles_on_graphics", "0/1", lln ); \
 \
   cpylne( opr->ntx[5], \
          "[0]_1:_[don't]_stop_when_no_sick_individuals_remain", "0/1", lln ); \
 \
   cpylne( opr->ntx[6], \
      "[0]_1:_[don't]_reweight_recovery_history", "0/1", lln ); \
 \
   cpylne( opr->ntx[7], \
      "[0]_1:_[don't]_reweight_vaccination_history", "0/1", lln ); \
 \
   cpylne( opr->ntx[8], \
      "reproduction_factor", "basic:0_|_effective:1_|_fixed:2", lln ); \
 \
   cpylne( opr->ntx[9], \
      "reproduction_factor_modulation_mode", "0,1,...4", lln ); \
 \
   cpylne( opr->ntx[10], \
      "random_burst_mode", "shifts:0_|_slats:1", lln ); \
 \
   cpylne( opr->ntx[11], \
      "maximum_number_of_outer_iterations", "<=100000", lln ); \
 \
   cpylne( opr->ntx[12], \
      "number_of_inner_iterations", "<=100", lln ); \
}
/*============================================================================*/
