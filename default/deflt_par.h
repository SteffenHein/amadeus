/* [ file: deflt_par.h ] */
/* Update: January 09, 2022 */
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
      "The_community_size", "number" );
   cpypar( 2, \
      "The_herd_size", "number" );
   cpypar( 3, \
      "The_initially_infective_['sick']_members", "number" );
   cpypar( 4, \
      "The_initially_infected_members", "number" );
   cpypar( 5, \
      "The_initially_immune_members_[eg.Nimn=Nifc]", "number" );
   cpypar( 6, \
      "The_already_deceased_members", "number" );
   cpypar( 7, \
      "The_reproduction_number", "number" );
   cpypar( 8, \
      "The_incidence_threshold", "number" );
   cpypar( 9, \
      "The_immunization_coefficient", "number" );
   cpypar( 10, \
      "The_percentage_of_asymptomatic_('silent')_cases", "P<100" );
   cpypar( 11, \
      "The_percentage_of_lethal_cases", "P<100" );
   cpypar( 12, \
      "The_mean_transmission_time", "Ttrm/days" );
   cpypar( 13, \
      "The_mean_duration_of_immunity", "Timu/days" );
   cpypar( 14, \
      "Cumulative_incidence_over_time", "Tinc/days" );
   cpypar( 15, \
      "The_time_interval", "Tend/days" );
   cpypar( 16, \
      "The_time_step", "DltT/days" );
/*............................................................................*/
/* parameters: */
                                                                               
   par->s[1]  = 1.000e+05; /* Ncom; community size [number of members]  */
   par->s[2]  = 1.000e+05; /* Nhrd; herd size [number of members]  */
   par->s[3]  = 1.000e+00; /* Ninf; Initially transmissive members [number] */ 
   par->s[4]  = 1.000e+00; /* Nifc; Initially infected members [number] */
   par->s[5]  = 1.000e+00; /* Nimn; Initially immune members [number] */
   par->s[6]  = 0.000e+00; /* Nlty; Init. already deceased members [number] */
   par->s[7]  = 3.000e+00; /* Nrpd; The reproduction number */
   par->s[8]  = 0.000e+00; /* Nthr; The incidence threshold */
   par->s[9]  = 1.000e+00; /* Nthr; The immunization coefficient */
   par->s[10] = 2.000e+01; /* Percentage of asymptomatic ('silent') cases */
   par->s[11] = 2.000e-02; /* Percentage of lethal cases */
   par->s[12] = 7.000e+00; /* Ttrm; The mean tansmissive time [days] */
   par->s[13] = 9.000e+01; /* Timu; The mean duration of immunity [days] */
   par->s[14] = 7.000e+00; /* Tinc; The incidence averaging time [days] */
   par->s[15] = 7.300e+02; /* Tend; End of the time interval [days] */
   par->s[16] = 1.000e-01; /* DltT; The time step [days] */

   return;
}
/*============================================================================*/
/************************ end of function deflt_par(*) ************************/
