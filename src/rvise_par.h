/* [ file: rvise_par.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A simple numerical Model Approximating the Development of Epidemics         *
*  Under varied conditions if Spread                                           *
*                                                                              *
*  Function rvise_par(*)                                                       *
*                                                                              *
*  This function revises [ and if necessary correts ] the model parameters     *
*  [ input option "parameters" ], thereby respecting the following hierarchy   *
*  from highest to lower priority:                                             *
*                                                                              *
*                          OPERATIONS -> PARAMETERS                            *
*                                                                              *
*  That is, a former input in this order always dominates subsequent inputs    *
*  [ which, of course, only affects conflicting cases ].                       *
*  Also, this function settles any internal parameter dependencies in input    *
*  option "parameters" whenever such dependencies exist.                       *
*                                                                              *
*  (C) SHEIN; Munich, December 2021                         Steffen Hein       *
*  [ Update: December 19, 2021 ]                         <contact@sfenx.de>    *
*                                                                              *
*******************************************************************************/

/*============================================================================*/

short rvise_params( void )
{
   AMDSTATE 
     *state = &amdstat;

   static PARMTRS
     *par = &parmtrs;

   static PARMTRS
     *prp = NULL;
/*
   static char
      ptr[STS_SIZE] = {null};
*/
   void
      cpypar( short index, const char *ltext, const char *bracket );
/*----------------------------------------------------------------------------*/
/* parameter strings:                                                         */

   ( state->par ) = &parmtrs;

   prp = ( state->par );
/*............................................................................*/
/* number of parameters */

   ( prp->s[null] )  = 16;
/*............................................................................*/
   strcpy( par->stx[0] , "parameters\n" );
   strcat( par->stx[0] , "[do_not_change_file_topology:"\
     "_connected_strings_must_remain_connected]" );

   cpypar( 1, \
      "The_total_herd_size", "Ncom>0" );
   cpypar( 2, \
      "The_initially_infective_('sick')_members", "Ninf>0" );
   cpypar( 3, \
      "The_initially_infected_members", "Nifc>=Ninf" );
   cpypar( 4, \
      "The_initially_immune_members", "Nimn>=0" );
   cpypar( 5, \
      "The_already_deceased_members", "Nlty>=0" );
   cpypar( 6, \
      "The_reproduction_number", "Repr>0" );
   cpypar( 7, \
      "The_incidence_threshold", "stop_below_that_No>=0_of_cases" );
   cpypar( 8, \
      "The_immunization_coefficient", "0<=C<=1" );
   cpypar( 9, \
      "The_percentage_of_asymptomatic_cases", "0<=P<100" );
   cpypar( 10, \
      "The_percentage_of_lethal_cases", "0<=P<100" );
   cpypar( 11, \
      "The_mean_transmissive_time", "0<=days" );
   cpypar( 12, \
      "The_mean_incubation_time", "0<=days" );
   cpypar( 13, \
      "The_mean_duration_of_acute_sickness", "0<days" );
   cpypar( 14, \
      "The_non_portability_delay_[after_infection]", "0<=days" );
   cpypar( 15, \
      "The_time_interval", "0<days" );
   cpypar( 16, \
      "The_time_step", "0<days" );
/*............................................................................*/
   if ( prp->s[3] < prp->s[2] )
      prp->s[3] = prp->s[2]; 
/*
   if ( prp->s[4] < prp->s[3] )
      prp->s[4] = prp->s[3]; 
*/
   return null;
}
/*============================================================================*/
# undef LINLEN
/*********************** end of function rvise_par(*) *************************/
