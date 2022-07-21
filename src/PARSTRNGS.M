/* [ file: PARSTRNGS.M ] */
/* Update: July 21, 2022 */
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
      "Herd_size_[Nhrd]", "0<Nhrd<=Nref", lln ); \
 \
   cpylne( par->stx[2], \
      "Initially_infective_[acutely_sick]", "0<Ninf", lln ); \
 \
   cpylne( par->stx[3], \
      "Initially_infected_[Nifc]", "Ninf<=Nifc", lln ); \
 \
   cpylne( par->stx[4], \
      "Initially_recovered", "0<=N" , lln ); \
 \
   cpylne( par->stx[5], \
      "Immunization_efficacy", "ratio:_0<Ieff<=1", lln ); \
 \
   cpylne( par->stx[6], \
      "Immunity_half-life_[days]", "0<T", lln ); \
 \
   cpylne( par->stx[7], \
      "Vaccinated", "0<=N" , lln ); \
 \
   cpylne( par->stx[8], \
      "Vaccination_rate", "vaccinations_per_day;_0<=Nvac", lln ); \
 \
   cpylne( par->stx[9], \
      "Vaccination_efficacy", "ratio;_0<Veff<=1", lln ); \
 \
   cpylne( par->stx[10], \
      "Vaccination_half-life_[days]", "0<T" , lln ); \
 \
   cpylne( par->stx[11], \
      "Deceased", "0<=N", lln ); \
 \
   cpylne( par->stx[12], \
      "Percentage_of_lethal_cases", "0<=P<=100", lln ); \
 \
   cpylne( par->stx[13], \
      "Initial_reproduction_factor", "0<R", lln ); \
 \
   cpylne( par->stx[14], \
      "Reproduction_factor_modulation", "amplitude:_-1<Rm", lln ); \
 \
   cpylne( par->stx[15], \
      "If_Rm_!=_0:_Repr._factor_modulation_length_[days]", "0<T", lln ); \
 \
   cpylne( par->stx[16], \
      "If_Rm_!=_0:_Repr._factor_modulation_delay_[days]", "0<=T", lln ); \
 \
   cpylne( par->stx[17], \
      "Percentage_of_asymptomatic_cases", "0<=P<100", lln ); \
 \
   cpylne( par->stx[18], \
      "Incidence_threshold", "stop_below_that_number_of_cases", lln ); \
 \
   cpylne( par->stx[19], \
      "Incidence_cumulation_time_[days]", "0<T", lln ); \
 \
   cpylne( par->stx[20], \
      "Random_burst_factor_[average]", "0<=Bf", lln ); \
 \
   cpylne( par->stx[21], \
      "If_0<Bf:_Average_burst_length_[T/days]", "0<=T", lln ); \
 \
   cpylne( par->stx[22], \
      "If_0<Bf:_Average_burst_pause_[T/days]", "0<=T", lln ); \
 \
   cpylne( par->stx[23], \
      "Mean_transmission_time_[days]", "0<T", lln ); \
 \
   cpylne( par->stx[24], \
      "Time_limit_[T/days]", "0<T", lln ); \
 \
   cpylne( par->stx[25], \
      "Time_step_[Dt/days]", "0<Dt", lln ); \
}
/*============================================================================*/
