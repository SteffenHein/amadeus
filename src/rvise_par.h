/* [ file: rvise_par.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A plain numerical Model Approximating the Development of Epidemics          *
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
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: January 21, 2022 ]                             <contact@sfenx.de> *
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
   short 
      ii = null;

   double 
      dd = 0.;

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

   ( prp->s[null] )  = 18;

/*............................................................................*/
   strcpy( par->stx[0] , "parameters\n" );
   strcat( par->stx[0] , "[do_not_change_file_topology:"\
     "_connected_strings_must_remain_connected]" );
/*............................................................................*/
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
      "Immunization_ratio", "0<Ir<=1" );
   cpypar( 8, \
      "Percentage_of_asymptomatic_cases", "0<=P<100" );
   cpypar( 9, \
      "Percentage_of_lethal_cases", "0<=P<=100" );
   cpypar( 10, \
      "Mean_transmission_time_[T/days]", "0<=T" );
   cpypar( 11, \
      "Mean_duration_of_immunity_[T/days]", "0<T" );
   cpypar( 12, \
      "Cumulative_incidence_over_time_[T/days]", "0<T" );
   cpypar( 13, \
      "Incidence_threshold", "stop_below_that_number_of_cases" );
   cpypar( 14, \
      "Burst_level_on_average", "0<=Bl" );
   cpypar( 15, \
      "If_0<Bl:_Burst_length_on_average_[T/days]", "0<=T" );
   cpypar( 16, \
      "If_0<Bl:_Burst_every_T-th_day_on_average", "0<=T" );
   cpypar( 17, \
      "Time_limit_[T/days]", "0<T" );
   cpypar( 18, \
      "Time_step_[Dt/days]", "0<Dt" );
/*............................................................................*/

   if ( prp->s[3] < prp->s[2] )
      prp->s[3] = prp->s[2];

   if (  prp->s[13] < 0. )
      prp->s[13] = 0.;

   if ( 1. < prp->s[7] )
      prp->s[7] = 1.;
   else if ( prp->s[7] <= 0. )
      prp->s[7] = 1.;

   return null;
}
/*============================================================================*/
# undef LINLEN
/*********************** end of function rvise_par(*) *************************/
