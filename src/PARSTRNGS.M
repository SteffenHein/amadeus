/* [ file: PARSTRNGS.M ] */
/* Update: June 10, 2022 */
/*============================================================================*/
# define PARSTRNGS( ) \
{ \
   par->s[null] = ( double ) 25; \
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
      "Initially_infective_[acutely_sick]_members_[Ninf]", "0<Ninf", ll ); \
 \
   cpylne( par->stx[3], \
      "Initially_infected_members_[Nifc]", "Ninf<=Nifc", ll ); \
 \
   cpylne( par->stx[4], \
      "Initially_immune_members", "0<=N" , ll ); \
 \
   cpylne( par->stx[5], \
      "Immunity_half-life_[days]", "0<T", ll ); \
 \
   cpylne( par->stx[6], \
      "Immunization_efficacy", "ratio:_0<Ieff<=1", ll ); \
 \
   cpylne( par->stx[7], \
      "Initially_vaccinated_members", "0<=N" , ll ); \
 \
   cpylne( par->stx[8], \
      "Vaccination_half-life_[days]", "0<T" , ll ); \
 \
   cpylne( par->stx[9], \
      "Vaccination_rate", "vaccinations_per_day;_0<=Nvac", ll ); \
 \
   cpylne( par->stx[10], \
      "Vaccination_efficacy", "ratio;_0<Veff<=1", ll ); \
 \
   cpylne( par->stx[11], \
      "Initially_deceased_members", "0<=N", ll ); \
 \
   cpylne( par->stx[12], \
      "Percentage_of_lethal_cases", "0<=P<=100", ll ); \
 \
   cpylne( par->stx[13], \
      "Initial_reproduction_factor", "0<R", ll ); \
 \
   cpylne( par->stx[14], \
      "Reproduction_factor_modulation", "amplitude:_-1<Rm", ll ); \
 \
   cpylne( par->stx[15], \
      "If_Rm_!=_0:_Repr._factor_modulation_length_[days]", "0<T", ll ); \
 \
   cpylne( par->stx[16], \
      "If_Rm_!=_0:_Repr._factor_modulation_delay_[days]", "0<=T", ll ); \
 \
   cpylne( par->stx[17], \
      "Percentage_of_asymptomatic_cases", "0<=P<100", ll ); \
 \
   cpylne( par->stx[18], \
      "Incidence_threshold", "stop_below_that_number_of_cases", ll ); \
 \
   cpylne( par->stx[19], \
      "Incidence_cumulation_time_[days]", "0<T", ll ); \
 \
   cpylne( par->stx[20], \
      "Random_burst_factor_[average]", "0<=Bf", ll ); \
 \
   cpylne( par->stx[21], \
      "If_0<Bf:_Average_burst_length_[T/days]", "0<=T", ll ); \
 \
   cpylne( par->stx[22], \
      "If_0<Bf:_Average_burst_pause_[T/days]", "0<=T", ll ); \
 \
   cpylne( par->stx[23], \
      "Mean_transmission_time_[days]", "0<T", ll ); \
 \
   cpylne( par->stx[24], \
      "Time_limit_[T/days]", "0<T", ll ); \
 \
   cpylne( par->stx[25], \
      "Time_step_[Dt/days]", "0<Dt", ll ); \
}
/*============================================================================*/
