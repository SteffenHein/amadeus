/* [ file: deflt_par.h ] */
/* Update: December 19, 2021 */
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
   strcpy( par->stx[0] , "parameters\n" );
   strcat( par->stx[0] , "[do_not_change_file_topology:"\
     "_connected_strings_must_remain_connected]" );

   cpypar( 1, \
      "The_total_herd_size", "number" );
   cpypar( 2, \
      "The_initially_infective_['sick']_members", "number" );
   cpypar( 3, \
      "The_initially_infected_members", "number" );
   cpypar( 4, \
      "The_initially_immune_members_[eg.Nimn=Nifc]", "number" );
   cpypar( 5, \
      "The_already_deceased_members", "number" );
   cpypar( 6, \
      "The_reproduction_number", "number" );
   cpypar( 7, \
      "The_incidence_threshold", "number" );
   cpypar( 8, \
      "The_immunization_coefficient", "number" );
   cpypar( 9, \
      "The_percentage_of_asymptomatic_('silent')_cases", "P<100" );
   cpypar( 10, \
      "The_percentage_of_lethal_cases", "P<100" );
   cpypar( 11, \
      "The_mean_transmissive_time", "Ttrm/days" );
   cpypar( 12, \
      "The_mean_incubation_time", "Ticb/days" );
   cpypar( 13, \
      "The_mean_duration_of_acute_sickness", "Tacu/days" );
   cpypar( 14, \
      "The_non_portability_delay_[after_infection]", "Tnif/days" );
   cpypar( 15, \
      "The_time_interval", "Tend/days" );
   cpypar( 16, \
      "The_time_step", "DltT/days" );
/*............................................................................*/
/* parameters: */
                                                                               
   par->s[1]  = 1.000e+05; /* Ncom; total herd size [number of members]  */
   par->s[2]  = 1.000e+00; /* Ninf; Initially transmissive members [number] */ 
   par->s[3]  = 0.000e+00; /* Nifc; Initially infected members [number] */
   par->s[4]  = 0.000e+00; /* Nimn; Initially immune members [number] */
   par->s[5]  = 0.000e+00; /* Nlty; Initially dead members [number] */
   par->s[6]  = 2.000e+00; /* Nrpd; The reproduction number */
   par->s[7]  = 1.000e-02; /* Nthr; The incidence threshold */
   par->s[8]  = 1.000e+00; /* Nthr; The immunization coefficient */
   par->s[9]  = 2.000e+01; /* Percentage of asymptomatic ('silent') cases */
   par->s[10] = 3.000e-01; /* Percentage of lethal cases */
   par->s[11] = 7.000e+00; /* Tinf; The mean tansmissive time [days] */
   par->s[12] = 4.000e+00; /* Ticb; The mean incubation time [days] */
   par->s[13] = 7.000e+00; /* Tinc; The mean duration of sickness [days] */
   par->s[14] = 2.000e+00; /* Tnif; Non-portability after infection [days] */
   par->s[15] = 7.650e+02; /* Tend; End of the time interval [days] */
   par->s[16] = 1.000e-01; /* DltT; The time step [days] */

   return;
}
/*============================================================================*/
/************************ end of function deflt_par(*) ************************/
