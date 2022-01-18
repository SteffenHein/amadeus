/* [ file: deflt_par.h ] */
/* Update: January 12, 2022 */
/*----------------------------------------------------------------------------*/
# ifndef LINLEN
   # define LINLEN 61
# endif
/*============================================================================*/

void deflt_params( void ) /* default model parameters */
{
   void
      cpypar( short index, const char *ltext, const char *bracket );
/*----------------------------------------------------------------------------*/
/* parameter strings: */
/* number of parameters */
   
   par->s[0]  = 16;

/* write only connected (!) strings into the string copy function strcpy(*) */
/* [ 2nd. argument       | ] */
/*                       V   */
/*............................................................................*/
   strcpy( par->stx[0], "parameters\n" );
   strcat( par->stx[0], "[do_not_change_file_topology:"\
     "_connected_strings_must_remain_connected!]" );

   cpypar( 1, \
      "Herd_size_[Nhrd]", "0<Nhrd<=Nref" );
   cpypar( 2, \
      "Initially_infective_('sick')_members_[Ninf]", "0<Ninf" );
   cpypar( 3, \
      "Initially_infected_members_[Nifc]", "Ninf<=Nifc" );
   cpypar( 4, \
      "Initially_immune_members", "0<=N" );
   cpypar( 5, \
      "Already_deceased_members", "0<N" );
   cpypar( 6, \
      "Initial_reproduction_factor", "0<R" );
   cpypar( 7, \
      "Dispersion_factor", "0<=D" );
   cpypar( 8, \
      "Incidence_threshold", "stop_below_that_number_of_cases" );
   cpypar( 9, \
      "Immunization_coefficient", "0<C<=1" );
   cpypar( 10, \
      "Percentage_of_asymptomatic_cases", "0<=P<100" );
   cpypar( 11, \
      "Percentage_of_lethal_cases", "0<=P<=100" );
   cpypar( 12, \
      "Mean_transmission_time_[T/days]", "0<=T" );
   cpypar( 13, \
      "Mean_duration_of_immunity_[T/days]", "0<T" );
   cpypar( 14, \
      "Cumulative_incidence_over_time_[T/days]", "0<T" );
   cpypar( 15, \
      "Length_of_time_interval_[T/days]", "0<T" );
   cpypar( 16, \
      "Time_step_[Dt/days]", "0<Dt" );
/*............................................................................*/
/* parameters: */
                                                                               
   par->s[1]  = 1.000e+05; /* Nhrd; herd size [(real) number of members]  */
   par->s[2]  = 1.000e+00; /* Ninf; Initially transmissive members [number] */ 
   par->s[3]  = 1.000e+00; /* Nifc; Initially infected members [number] */
   par->s[4]  = 1.000e+00; /* Nimn; Initially immune members [number] */
   par->s[5]  = 0.000e+00; /* Nlty; Init. already deceased members [number] */
   par->s[6]  = 3.000e+00; /* Nrpd; The reproduction factor */
   par->s[7]  = 1.000e+00; /* Dspf; Dispersion factor [ real number >=0 ] */
   par->s[8]  = 0.000e+00; /* Ithr; The incidence threshold [ number ] */
   par->s[9]  = 1.000e+00; /* Immc; The immunization coefficient */
   par->s[10] = 2.000e+01; /* Percentage of asymptomatic ('silent') cases */
   par->s[11] = 2.000e-02; /* Percentage of lethal cases */
   par->s[12] = 1.400e+01; /* Ttrm; The mean tansmissive time [days] */
   par->s[13] = 9.000e+01; /* Timu; The mean duration of immunity [days] */
   par->s[14] = 7.000e+00; /* Tinc; The incidence averaging time [days] */
   par->s[15] = 7.300e+02; /* Tend; End of the time interval [days] */
   par->s[16] = 1.000e-01; /* DltT; The time step [days] */

   return;
}
/*============================================================================*/
/************************ end of function deflt_par(*) ************************/
