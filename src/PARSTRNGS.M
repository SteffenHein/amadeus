/* [ file: PARSTRNGS.M ] */
/* Update: January 25, 2022 */
/*============================================================================*/
# define PARSTRNGS( ) \
{ \
   par->s[null] = ( double ) 18; \
/*.........................................................................*/ \
/* the parameter strings: */ \
 \
/* write only connected (!) strings into the string copy function strcpy(*)*/ \
/* [ 2nd. argument       | ] */ \
/*                       V   */ \
/*.........................................................................*/ \
   strcpy( par->stx[0], "Do_not_change_file_topology_!!!\n" ); \
   strcat( par->stx[0], "[Leave_contiguous_strings_contiguous.]" ); \
/*.........................................................................*/ \
   cpylne( par->stx[1], \
      "Herd_size_[Nhrd]", "0<Nhrd<=Nref", ll ); \
 \
   cpylne( par->stx[2], \
      "Initially_infective_('sick')_members_[Ninf]", "0<Ninf", ll ); \
 \
   cpylne( par->stx[3], \
      "Initially_infected_members_[Nifc]", "Ninf<=Nifc", ll ); \
 \
   cpylne( par->stx[4], \
      "Initially_immune_members", "0<=N" , ll ); \
 \
   cpylne( par->stx[5], \
      "Already_deceased_members", "0<N", ll ); \
 \
   cpylne( par->stx[6], \
      "Initial_reproduction_factor", "0<R", ll ); \
 \
   cpylne( par->stx[7], \
      "Immunization_ratio", "0<Ir<=1", ll ); \
 \
   cpylne( par->stx[8], \
      "Percentage_of_asymptomatic_cases", "0<=P<100", ll ); \
 \
   cpylne( par->stx[9], \
      "Percentage_of_lethal_cases", "0<=P<=100", ll ); \
 \
   cpylne( par->stx[10], \
      "Mean_transmission_time_[T/days]", "0<=T", ll ); \
 \
   cpylne( par->stx[11], \
      "Mean_duration_of_immunity_[T/days]", "0<T", ll ); \
 \
   cpylne( par->stx[12], \
      "Cumulative_incidence_over_time_[T/days]", "0<T", ll ); \
 \
   cpylne( par->stx[13], \
      "Incidence_threshold", "stop_below_that_number_of_cases", ll ); \
 \
   cpylne( par->stx[14], \
      "Random_burst_factor_[average:_Bf]", "0<=Bf", ll ); \
 \
   cpylne( par->stx[15], \
      "If_0<Bf:_Random_burst_length_[average:_T/days]", "0<=T", ll ); \
 \
   cpylne( par->stx[16], \
      "If_0<Bf:_Random_burst_every_T-th_day_[average]", "0<=T", ll ); \
 \
   cpylne( par->stx[17], \
      "Time_limit_[T/days]", "0<T", ll ); \
 \
   cpylne( par->stx[18], \
      "Time_step_[Dt/days]", "0<Dt", ll ); \
}
/*============================================================================*/
