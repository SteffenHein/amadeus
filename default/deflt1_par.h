/* [ file: deflt_par.h ] */
/* Update: July 21, 2022 */
/*----------------------------------------------------------------------------*/
# ifndef LINLEN
   # define LINLEN 61
# endif
/*----------------------------------------------------------------------------*/
# include "../src/PARSTRNGS.M"
/*============================================================================*/

void deflt_par( void ) /* default model parameters */
{
   static PARMTRS
     *par = &parmtrs;

   static short
      lln = LINLEN;

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   par = &parmtrs;

   PARSTRNGS( );  /* copy number of parameters and parameter strings */
/*............................................................................*/
/* default parameters: */
                                                                               
/* s001:Herd_size_[Nhrd]__________________________[0<Nhrd<=Nref]: */  par->s[1]  = 1.00000e+05;
/* s002=Initially_infective_[acutely_sick]______________[0<Ninf]: */  par->s[2]  = 1.00000e+00;
/* s003=Initially_infected_[Nifc]___________________[Ninf<=Nifc]: */  par->s[3]  = 1.00000e+00;
/* s004=Initially_recovered_______________________________[0<=N]: */  par->s[4]  = 0.00000e+00;
/* s005=Immunization_efficacy_________________[ratio:_0<Ieff<=1]: */  par->s[5]  = 1.00000e+00;
/* s006=Immunity_half-life_[days]__________________________[0<T]: */  par->s[6]  = 1.80000e+02;
/* s007=Initially_vaccinated______________________________[0<=N]: */  par->s[7]  = 0.00000e+00;
/* s008=Vaccination_rate_________[vaccinations_per_day;_0<=Nvac]: */  par->s[8]  = 5.00000e+01;
/* s009=Vaccination_efficacy__________________[ratio;_0<Veff<=1]: */  par->s[9]  = 8.00000e-01;
/* s010=Vaccination_half-life_[days]_______________________[0<T]: */  par->s[10] = 3.60000e+02;
/* s011=Deceased__________________________________________[0<=N]: */  par->s[11] = 0.00000e+00;
/* s012=Percentage_of_lethal_cases___________________[0<=P<=100]: */  par->s[12] = 2.00000e-03;
/* s013=Initial_reproduction_factor________________________[0<R]: */  par->s[13] = 2.00000e+00;
/* s014=Reproduction_factor_modulation________[amplitude:_-1<Rm]: */  par->s[14] = 0.00000e+00;
/* s015=If_Rm_!=_0:_Repr._factor_modulation_length_[days]__[0<T]: */  par->s[15] = 0.00000e+00;
/* s016=If_Rm_!=_0:_Repr._factor_modulation_delay_[days]__[0<=T]: */  par->s[16] = 0.00000e+00;
/* s017=Percentage_of_asymptomatic_cases______________[0<=P<100]: */  par->s[17] = 2.00000e+01;
/* s018=Incidence_threshold____[stop_below_that_number_of_cases]: */  par->s[18] = 1.00000e-03;
/* s019=Incidence_cumulation_time_[days]___________________[0<T]: */  par->s[19] = 7.00000e+00;
/* s020=Random_burst_factor_[average]____________________[0<=Bf]: */  par->s[20] = 0.00000e+00;
/* s021=If_0<Bf:_Average_burst_length_[T/days]____________[0<=T]: */  par->s[21] = 0.00000e+00;
/* s022=If_0<Bf:_Average_burst_pause_[T/days]_____________[0<=T]: */  par->s[22] = 0.00000e+00;
/* s023=Mean_transmission_time_[days]______________________[0<T]: */  par->s[23] = 5.00000e+00;
/* s024=Time_limit_[T/days]________________________________[0<T]: */  par->s[24] = 1.80000e+02;
/* s025=Time_step_[Dt/days]_______________________________[0<Dt]: */  par->s[25] = 1.00000e-02;

   return;
}
/*============================================================================*/
/************************ end of function deflt_par(*) ************************/
