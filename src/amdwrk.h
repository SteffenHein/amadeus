/* [ file: amdwrk.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A plain numerical Model Approximating the Development of Epidemics          *
*  Under varied conditions if Spread                                           *
*                                                                              *
*  Body of function amdwrk(*)                                                  *
*  Here is where the numerical computations are done                           *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: January 21, 2022 ]                             <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/

/*============================================================================*/
AMDSTATE *amdwrk( AMDSTATE *state )
{
/*--- system function prototypes -------------------------------------------->*/

   FILE *fopen( const char *restrict filename, const char *restrict mode );
   int fprintf( FILE *restrict stream, const char *restrict format,...);

   long   strtol( const char *ptr, char **endp, int base );
   double strtod( const char *ptr, char **endp );

   char *strcpy( char *dest, const char *src );
   char *strcat( char *dest, const char *src );
   char *strncpy( char *dest, const char *src, size_t N );

/*--- user function prototypes ---------------------------------------------->*/

   int rand( void );
   double exp( double x );
   double log( double x );
   double fmin( double x, double y );
   double fmod( double x, double y );

   char 
      *lotos ( long lngint, char length, char *format );

   char 
      *dotos ( double lngdbl, char precision, char *format );

   void 
      cpylne( char txlne[], const char *ltext, const char *bracket, short ll );
/*............................................................................*/
   AMDSTATE
     *stp = state;

   static PARMTRS
     *ppt = null;

   static OPERTNS
     *opt = null;

   static FILE
     *pltptr_cic = null,
     *pltptr_ifc = null,
     *pltptr_imn = null,
     *pltptr_inc = null,
     *pltptr_lty = null,
     *pltptr_rpd = null,
     *fleptr_par = null;

   static FILE
     *gnuptr_cic = null,
     *gnuptr_ifc = null,
     *gnuptr_imn = null,
     *gnuptr_inc = null,
     *gnuptr_lty = null,
     *gnuptr_rpd = null;

   char   
      inptstr[80] = {'\0'},
      outpstr[80] = {'\0'},
      optnstr[50] = {'\0'},
      timestr[50] = {'\0'},
      longstr[50] = {'\0'},

      flname_cic[50] = {'\0'},
      flname_ifc[50] = {'\0'},
      flname_imn[50] = {'\0'},
      flname_inc[50] = {'\0'},
      flname_lty[50] = {'\0'},
      flname_rpd[50] = {'\0'},

      pltfle_cic[50] = AMD_RESULTS,
      pltfle_ifc[50] = AMD_RESULTS,
      pltfle_imn[50] = AMD_RESULTS,
      pltfle_inc[50] = AMD_RESULTS,
      pltfle_lty[50] = AMD_RESULTS,
      pltfle_rpd[50] = AMD_RESULTS,

      parmtr_fle[50] = AMD_RESULTS;

   char
      plot_cic[50] = AMD_RESULTS,
      plot_ifc[50] = AMD_RESULTS,
      plot_imn[50] = AMD_RESULTS,
      plot_inc[50] = AMD_RESULTS,
      plot_lty[50] = AMD_RESULTS,
      plot_rpd[50] = AMD_RESULTS;

   long
     ii = null,
     kk = null,
     krd = null;

   static double
      hh = ZERO,
      rnd = ZERO,
      rrpd = ZERO,
      tntb = ZERO,     
      scpt0 = ZERO,
      lnrpd = ZERO,   /* log( Repr(t)/Ttrm ) */
      ndays_cic_upd = ZERO,
      suscpt_upd = ZERO,   /* 1. - h(t) */
      infected_upd = ZERO,
      immune_upd = ZERO, /* updated immunity, inner loop */
      incidence_upd = ZERO,
      lethal_upd = ZERO,
      reprod_upd = ZERO, /* updated reproduction number, inner loop */
      integral_inc = ZERO;

/*----------------------------- end declarations -----------------------------*/
/* assign structure pointers */

   stp = state;
   ppt = stp->par;
   opt = stp->opr;
/*............................................................................*/
   strcat( parmtr_fle, "parameters" );

   strcat( plot_cic, "gpl_n_days_incidence" );
   strcat( plot_ifc, "gpl_infection" );
   strcat( plot_imn, "gpl_immunity" );
   strcat( plot_inc, "gpl_incidence" );
   strcat( plot_lty, "gpl_lethality" );
   strcat( plot_rpd, "gpl_reproduction" );
/*............................................................................*/
/* append job number to filenames */

   strcpy( longstr, "_job." );
   strcat( longstr, lotos(( state->job ), null, " " ));
   strcat( parmtr_fle, longstr );

   strcat( plot_cic, longstr );
   strcat( plot_ifc, longstr );
   strcat( plot_imn, longstr );
   strcat( plot_inc, longstr );
   strcat( plot_lty, longstr );
   strcat( plot_rpd, longstr );
/*............................................................................*/
/* dictionary: */
      
/* Nhrd = 8.20e+07;  herd size [ number of members ] */
/* Ninf = 3.40e+04;  initial number of infective [sick] members */
/* Nifc = 1.60e+05;  number of initially infected members Ninf <= Nifc */
/* Nimn = 1.60e+05;  initial number immune members */
/* Nlty = 2.40e+03;  initial number of deceased members */
/* Lvlb = 0.000+00;  random burst level [0<=Lvlb] */

/* rinf = Ninf/Nhrd; initial ratio of infective members */
/* rifc = Nifc/Nhrd; initial ratio of infected members */
/* rimn = Nimn/Nhrd; initial herd immunity [ ratio ] */
/* rlty = Nlty/Nhrd; initial ratio of deceased members */
/*............................................................................*/
/* desease features [ parameter examples ]: */

/* Repr = 1.000;  initial reproduction number */
/* Tend = 365.0;  computed time intervall [ days ] */
/* Tcic =   14.;  incidence cumulated over time [ days ] */
/* Ttrm =    7.;  mean transmission time [ days ] */
/*............................................................................*/
/* LnRp = log( Repr )/Ttrm;  i.e. exp( LnRp ) = Repr[0]^(1./Ttrm) */ 
/* rrpd = exp( LnRp ); = Repr[0]^(1./Ttrm), base of init. exp. incr. */
/*...........................................................................*/
/* legend: 

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
/* copy the input parameters */

   ppt->Nhrd = ppt->s[1];
   ppt->Ninf = ppt->s[2];
   ppt->Nifc = ppt->s[3];
   ppt->Nimn = ppt->s[4];
   ppt->Nlty = ppt->s[5];
   ppt->Repr = ppt->s[6];
   ppt->Immc = ppt->s[7];
   ppt->Slnt = ppt->s[8];
   ppt->Ltlt = ppt->s[9];
   ppt->Ttrm = ppt->s[10];
   ppt->Timu = ppt->s[11];
   ppt->Tcic = ppt->s[12];
   ppt->Ithr = ppt->s[13];
   ppt->Lvlb = ppt->s[14];
   ppt->Tmeb = ppt->s[15];
   ppt->Tbst = ppt->s[16];
   ppt->Tend = ppt->s[17];
   ppt->DltT = ppt->s[18];
/*............................................................................*/
/* normalized parameters: */

   ppt->dt = ppt->DltT/ppt->Ttrm;
   ppt->timn = ppt->Timu/ppt->Ttrm; /* timn: Timu in natural units */
   ppt->tcin = ppt->Tcic/ppt->Ttrm; /* tcin: Tcic in natural units */
   ppt->tbst = ppt->Tbst/ppt->Ttrm; /* tbst: Tbst in natural units */
   ppt->tmeb = ppt->Tmeb/ppt->Ttrm; /* bstl: Tmeb in natural units */

   tntb = ppt->tmeb;

   ppt->kend = ( long )( ppt->Tend/ppt->DltT );
   ppt->kcic = ( long )( ppt->Tcic/ppt->DltT );
   ppt->ktrm = ( long )( ppt->Ttrm/ppt->DltT );
   ppt->kbst = ( long )( ppt->Tbst/ppt->DltT );

   krd = ppt->kbst;

   ppt->mxictm = ppt->ktrm;

   if ( ppt->mxictm < ppt->kcic )
      ppt->mxictm = ppt->kcic;

   ppt->rifc = ppt->Nifc/ppt->Nhrd;
   ppt->rimn = ppt->Nimn/ppt->Nhrd;
   ppt->rinf = ppt->Ninf/ppt->Nhrd;
   ppt->rlty = ppt->Nlty/ppt->Nhrd;
   ppt->rthr = ppt->Ithr/ppt->Nhrd;
   
   ppt->wght_imm = ( 100.*ppt->Immc - ppt->Ltlt )/( 100. - ppt->Slnt );
   ppt->wght_ifc = ( 100./( 100. - ppt->Slnt ));
   ppt->wght_lty = ppt->Ltlt/( 100. - ppt->Slnt );

/*............................................................................*/
/* limits: */

   ppt->maxout = ( long ) opt->n[1]; /* null < maxout <= 10000 !!! */
   ppt->maxinn = ( long ) opt->n[2]; /* null < maxinn <= 10000 !!! */

   if ( 100000 < ppt->maxinn )
      ppt->maxinn = 100000;
   else if ( ppt->maxinn < ONE )
      ppt->maxinn = 1;
      
   ppt->maxout = \
   ( long ) fminl(( ppt->kend/ppt->maxinn ), 100000. );

   ppt->formula = ( char ) ( opt->n[3] );
   ppt->xscale = ( char ) ( opt->n[4] );
   ppt->yscale = ( char ) ( opt->n[5] );
   ppt->yunits = ( char ) ( opt->n[6] );
   ppt->titles = ( char ) ( opt->n[7] );
   ppt->nmstop = ( char ) ( opt->n[8] );
/*............................................................................*/
/* Repr^(1./Ttrm), base of initial exponential increase */
/* exp( LnRp ) = Repr^(1./Ttrm) */ 
   ppt->repr = ppt->Repr;
 
   lnrpd = log( ppt->Repr );
   rrpd = exp( lnrpd/ppt->Ttrm );
/*............................................................................*/
/* store initial parameters in file <parmtr_fle> */

   fleptr_par = fopen( parmtr_fle, "w+" ); 
   fprintf( fleptr_par, "Essential_parameters\n" );

   cpylne( outpstr,
      "\nHerd_size","members", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Nhrd, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInitially_infected","members", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Nifc, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInitially_immune","members", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( ppt->Nimn ), 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nMean_transmission_time","days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Ttrm, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nMean_duration_of_immunity","days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Timu, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nCumulative_incidence,_integrated_over","days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Tcic, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nCumulative_incidence,_summed_up_over","iterations", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, lotos( ppt->kcic, 9, " " ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInitial_reproduction_factor","dimensionless", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Repr, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInitial_base_of_exponential_increase","dimensionless", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( rrpd, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

   if ( ZERO < ppt->Lvlb )
   {
      cpylne( outpstr,
         "\nRandom_burst_level","dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Lvlb, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nAverage_burst_length","days", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Tmeb, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nAverage_burst_period","days", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Tbst, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      fprintf( fleptr_par, "\n" );
   };

   cpylne( outpstr,
      "\nTime_limit","days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Tend, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nTime_step","days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->DltT, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInternal_time_step","transmission_cycles", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->dt, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nMaximum_number_of_iterations","number", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, lotos( ppt->kend, 9, " " ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nMaximum_number_of_outer_iterations","number", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, lotos( ppt->maxout, 9, " " ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nNumber_of_inner_iterations","number", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, lotos( ppt->maxinn, 9, " " ));
   fprintf( fleptr_par, outpstr );

   fclose( fleptr_par );
/*............................................................................*/
   strcpy( longstr, "R0" );
   
/* strcat( longstr, lotos(( state->job ), null, " " )); */

   strcat( longstr, "=" );
   strcat( longstr, dotos( ppt->Repr, 4, "f" ));

   strcat( flname_cic, lotos(( short ) ppt->Tcic, null, " " ));
   strcat( flname_cic, "_days_incidence_" );
   strcat( flname_cic, longstr );
   strcat( pltfle_cic, flname_cic );

   strcat( flname_ifc, "h(t)_" );
   strcat( flname_ifc, longstr );
   strcat( pltfle_ifc, flname_ifc );

   strcat( flname_imn, "im(t)_" );
   strcat( flname_imn, longstr );
   strcat( pltfle_imn, flname_imn );

   strcat( flname_inc, "u(t)_" );
   strcat( flname_inc, longstr );
   strcat( pltfle_inc, flname_inc );

   strcat( flname_lty, "l(t)_" );
   strcat( flname_lty, longstr );
   strcat( pltfle_lty, flname_lty );

   strcat( flname_rpd, "r(t)_" );
   strcat( flname_rpd, longstr );
   strcat( pltfle_rpd, flname_rpd );

   pltptr_cic = fopen( pltfle_cic, "w+" );
   pltptr_ifc = fopen( pltfle_ifc, "w+" );
   pltptr_imn = fopen( pltfle_imn, "w+" );
   pltptr_inc = fopen( pltfle_inc, "w+" );
   pltptr_lty = fopen( pltfle_lty, "w+" );
   pltptr_rpd = fopen( pltfle_rpd, "w+" );
   
   if ( ppt->xscale == null )
      strcpy ( timestr, "transmission cycles" );
   else
      strcpy ( timestr, "days" );
/* 
   fprintf( pltptr_cic, "%s",\
      "# Epidemic | " );
*/
   fprintf( pltptr_cic, "%s",\
      "# Epidemic | " );
    
   strcpy( optnstr, "total " );
   strcat( optnstr, lotos(( long ) ppt->Tcic, 2, " " ));
   strcat( optnstr, " days incidence " );

   fprintf( pltptr_cic, "%s", optnstr );

   fprintf( pltptr_cic, "%s",\
      "[ x-unit: " );
   fprintf( pltptr_cic, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_cic, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_cic, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_ifc, "%s",\
      "# Epidemic | infected members [ x-unit: " );
   fprintf( pltptr_ifc, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_ifc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_ifc, "%s", " | y-unit: % ]\n" );

   fprintf( pltptr_imn, "%s",\
      "# Epidemic | immune members [ x-unit: " );
   fprintf( pltptr_imn, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_imn, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_imn, "%s", " | y-unit: % ]\n" );

   fprintf( pltptr_inc, "%s",\
      "# Epidemic | total incidence [ x-unit: " );
   fprintf( pltptr_inc, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_inc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_inc, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_lty, "%s",\
      "# Epidemic | deceased members [ x-unit: " );
   fprintf( pltptr_lty, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_lty, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_lty, "%s", " | y-unit: % ]\n" );

   fprintf( pltptr_rpd, "%s",\
      "# Epidemic | reproduction number\n"
      "# [ x-unit: " );
   fprintf( pltptr_rpd, "%s", timestr );

   fprintf( pltptr_rpd, "%s", \
      " | y-unit: members infected by one sick member ]\n");
/*............................................................................*/
/* initialize iteration */

   ppt->mincic =  1.00e+27;
   ppt->maxcic = -1.00e+27;
   ppt->mininc =  1.00e+27;
   ppt->maxinc = -1.00e+27;
   ppt->maxifc = -1.00e+27;
   ppt->maximn = -1.00e+27;
   ppt->maxlty = -1.00e+27;
   ppt->maxrpd = -1.00e+27;
   ppt->minrpd = +1.00e+27;

/*............................................................................*/
/* start outer loop */

   incidence_upd = ppt->rinf;
   infected_upd = ppt->rifc;
   immune_upd = ppt->rimn;
   lethal_upd = ppt->rlty;

   hh = immune_upd + lethal_upd;
   scpt0 = 1. - hh;

   if ( ppt->formula == null )      /* Repr is basic reproduction number */
      reprod_upd = scpt0*ppt->repr;
   else                             /* Repr is current reproduction number */
      reprod_upd = ppt->repr;

   lnrpd= log( reprod_upd );
   ppt->dudt[null] = incidence_upd;
   
   ii = null;
   while( ii < ppt->mxictm )
   {
      ii++;
      ppt->dudt[ii] = ZERO;
   };

   kk = null;
   krd = ppt->kbst;
   ppt->tt = ZERO;
   integral_inc = ZERO;
/*...........................................................................*/
/* here start the iterations */
/* outer loop */

   ppt->nout = null;
   while ( ppt->nout < ppt->maxout )
   {
/*...........................................................................*/
/* store values */

      FPRINTF(1);
/*...........................................................................*/
/* compute extrema in outer loop: set EXTREMA(1)  */

      EXTREMA(1);
/*...........................................................................*/
/* start inner loop */

      ppt->ninn = null;
      while ( ppt->ninn < ppt->maxinn )
      {
/*...........................................................................*/
/* compute extrema in inner loop: set EXTREMA(1) */

         EXTREMA(0);
/*...........................................................................*/
         hh = immune_upd + lethal_upd;
         suscpt_upd = ( 1. - hh ); 

         if ( ppt->nmstop == ONE ) /* stop if no sick members remain */
	 {
            if ((( incidence_upd*reprod_upd ) < ppt->rthr )
	       || ( suscpt_upd <= ppt->rthr ))
            { 
/* [ no new cases or group immunity attained ] */

	       ppt->dudt[null] = ZERO;
       	       ppt->timmun = ppt->tt;
	       ppt->kend = kk;

               goto finish;
	    };
	 };
/*...........................................................................*/
/* update df/dt */

         if ( ppt->rthr < suscpt_upd )
	 {
            switch ( ppt->formula )
	    {
              default: 
              case 0:

	       reprod_upd = suscpt_upd*ppt->repr;
               lnrpd = log( reprod_upd );
               incidence_upd *= \
                  exp( ppt->dt*lnrpd );

              break;
/*...........................................................................*/
              case 1:

               suscpt_upd /= scpt0;

	       reprod_upd = suscpt_upd*ppt->repr;
               lnrpd = log( reprod_upd );
               incidence_upd *= \
                  exp( ppt->dt*lnrpd );

              break;
/*...........................................................................*/
              case 2: /* R(t) = R(0) [ constant ] */

               incidence_upd *= exp( ppt->dt*lnrpd );
		  
              break;
            };
         }
	 else /* suscpt_upd <= ppt->rthr */
            incidence_upd = ZERO;
/*...........................................................................*/
         ppt->dudt[null] = incidence_upd;

         if ( ZERO < ppt->Lvlb )
         {
            if ( tntb < ppt->tt )
	    {
               if ( fmod( kk, krd ) < 0.1 )
	       {
                  rnd = ( double ) rand( );
                  rnd /= RAND_MAX; 
	          tntb = ppt->tt + 2*rnd*ppt->tmeb;

                  rnd = ( double ) rand( ); 
                  rnd /= RAND_MAX; 
	          krd = 1 + ( long ) 2*rnd*ppt->kbst;

                  rnd = ( double ) rand( ); 
                  rnd /= RAND_MAX; 
                  rnd = 1.+ 2.*rnd*ppt->Lvlb;
               };
            }; 
            ppt->dudt[null] *= rnd;
         }; 
/*...........................................................................*/
/* integrate incidence */

         integral_inc += ( ppt->dt*ppt->dudt[null] );

/*...........................................................................*/
/* update herd infection, immunity and incidence */

         infected_upd +=\
            ( ppt->dt*ppt->wght_ifc*ppt->dudt[null] );

         if ( infected_upd > 1. )
	    infected_upd = 1.;

         lethal_upd +=\
            ( ppt->dt*ppt->wght_lty*ppt->dudt[null] );
/*...........................................................................*/
/* the immune fraction */
	 
         immune_upd *= ( exp( - ppt->dt / ppt->timn ));
         immune_upd +=\
            ( ppt->dt*ppt->wght_imm*ppt->dudt[null] );

/*...........................................................................*/
/* mean n days incidence */
/* and shift dudt from k to k+1 */    

         ndays_cic_upd = ZERO;
         ii = ppt->mxictm;
	 while( null < ii )
         {
            ppt->dudt[ii] = ppt->dudt[ii-ONE];
	    
	    if ( ii < ppt->kcic )
               ndays_cic_upd += \
                  ( ppt->dt*ppt->dudt[ii] );
	    ii--;
         };

         ppt->tt += ppt->dt;
         ppt->ninn++ ;
	 kk++;
      }; /* while ( ppt->ninn < ppt->maxinn ) */

/*......................end inner loop .........................*/
      ppt->nout++;

   }; /* while ( ppt->nout < ppt->maxout) */
   
/*............................end of outer loop ..............................*/
  finish:

   fclose( pltptr_cic );
   fclose( pltptr_ifc );
   fclose( pltptr_imn );
   fclose( pltptr_inc );
   fclose( pltptr_lty );
   fclose( pltptr_rpd );

/*............................................................................*/
/* store maxima: */ 
      
   fleptr_par = fopen( parmtr_fle, "a+" );
      
   cpylne( outpstr,
      "\nIncidence_maximum_attained_at","transmission_cycle", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->tmxinc, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nMaximum_herd_incidence","percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->maxinc, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   strcpy( inptstr, "\nMaximum_cumulative_herd_incidence_(");
   strcat( inptstr, dotos( ppt->Tcic, 4, "f" ));
   strcat( inptstr, "_days)");
   cpylne( outpstr, inptstr, "percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->maxcic, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nTotal_herd_incidence_(sum_t=0->Tend)",
      "members", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( integral_inc*ppt->Nhrd ), 4, "e" ));
   fprintf( fleptr_par, outpstr );

   if ( ZERO < ppt->timmun )
   {
      fprintf( fleptr_par, "\n" );

      cpylne( outpstr,
         "\n100%%_herd_immunity_attained_at","transmission_cycle", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->timmun, 4, "e" ));
      fprintf( fleptr_par, outpstr );
   }
   else
      fprintf( fleptr_par,
         "\n\nHerd immunity not attained.\n" );

   fclose( fleptr_par );
/*............................................................................*/
/* store gnuplot headers

   Format: 
   GNUPLOT( STREAM, FILENAME, PLOTFILE, "OPTION", "XUNIT", "YUNIT", YMIN, YMAX )
   yscale: 0 linear, 1 logarithmic
*/
/*............................................................................*/
   if ( ppt->xscale == null )
      strcpy ( timestr, "transmission cycles" );
   else
      strcpy ( timestr, "days" );

   if ( ppt->titles == ONE )
   {
      strcpy( optnstr, "Cumulative incidence ( " );
      strcat( optnstr, lotos(( long ) ppt->Tcic, null, " " ));
      strcat( optnstr, " days )" );
   }
   else
      strcpy( optnstr, " " );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
   {
      GNUPLOT( gnuptr_cic, plot_cic, flname_cic, optnstr, timestr, \
         " ", ( .77*1.0e+0*ppt->mincic ), ( 1.10e+0*ppt->maxcic ));

      if ( ppt->titles == ONE )
         strcpy( optnstr,
            "Herd infection [ sum of recovered, "
	    "sick, asymptomatic, and lethal cases ]" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr, \
         " ", ( .77*1.0e+0*ppt->rifc ), ( 1.10e+0*ppt->maxifc ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Herd immunity" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_imn, plot_imn, flname_imn, optnstr, timestr, \
         " ", ( .77*1.0e+0*ppt->rimn ), ( 1.10e+0*ppt->maximn ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Incidence" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_inc, plot_inc, flname_inc, optnstr, timestr, \
         " ", ( .77*1.0e+0*ppt->mininc ), ( 1.10e+0*ppt->maxinc ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Deceased" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_lty, plot_lty, flname_lty, optnstr, timestr, \
         " ", ( .77*1.0e+0*ppt->rlty ), ( 1.10e+0*ppt->maxlty ));\
   }
   else /* conventional units */
   {
      GNUPLOT( gnuptr_cic, plot_cic, flname_cic, optnstr, timestr, \
         "per 100000", ( .77*1.0e+5*ppt->mincic ), ( 1.10e+5*ppt->maxcic ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, \
            "Herd infection [ sum of recovered, "
	    "sick, asymptomatic, and lethal cases ]" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr, \
         "percent", ( .77*1.0e+2*ppt->rifc ), ( 1.10e+2*ppt->maxifc ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Herd immunity" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_imn, plot_imn, flname_imn, optnstr, timestr, \
         "percent", ( .77*1.0e+2*ppt->rimn ), ( 1.10e+2*ppt->maximn ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Incidence" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_inc, plot_inc, flname_inc, optnstr, timestr, \
         "per 100000", ( .77*1.0e+5*ppt->mininc ), ( 1.10e+5*ppt->maxinc ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Deceased" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_lty, plot_lty, flname_lty, optnstr, timestr, \
         "members", ( .77*ppt->rlty*ppt->Nhrd ), \
            ( 1.10e+0*ppt->maxlty*ppt->Nhrd ));
   };

   if ( ppt->titles == ONE )
      strcpy( optnstr, "Reproduction number" );
   else
         strcpy( optnstr, " " );

   GNUPLOT( gnuptr_rpd, plot_rpd, flname_rpd, optnstr, timestr, \
      "reprod. no", ( .77*ppt->minrpd ), ( 1.10*ppt->maxrpd ));

/*............................................................................*/
   return state;
}
/*============================================================================*/

/****************************** end of amdwrk(*) ******************************/
/*
    Ein grosser Teil des Lebens
    entgleitet den Menschen,
    wenn sie Schlechtes tun, 
    der groesste, wenn sie nichts tun,
    das ganze Leben, 
    wenn sie Nebensaechliches tun.

    Seneca [ Briefe an Lucilius ]
*/
/* EOF */
