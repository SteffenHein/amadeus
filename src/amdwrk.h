/*[ file: amdwrk.h ] */
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
*  [ Update: January 09, 2022 ]                             <contact@sfenx.de> *
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

   double exp( double x );
   double log( double x );
   double fmin( double x, double y );

   char 
      *lotos ( long lngint, char length, char *format );

   char 
      *dotos ( double lngdbl, char precision, char *format );
/*............................................................................*/
   AMDSTATE
     *stp = state;

   static PARMTRS
     *ppt = null;

   static OPERTNS
     *opr = null;

   static FILE
     *pltptr_ica = null,
     *pltptr_ifc = null,
     *pltptr_imn = null,
     *pltptr_inc = null,
     *pltptr_lty = null,
     *pltptr_rpd = null,
     *fleptr_par = null;

   static FILE
     *gnuptr_ica = null,
     *gnuptr_ifc = null,
     *gnuptr_imn = null,
     *gnuptr_inc = null,
     *gnuptr_lty = null,
     *gnuptr_rpd = null;

   char   
      optnstr[50] = {'\0'},
      timestr[50] = {'\0'},
      longstr[50] = {'\0'},

      flname_ica[50] = {'\0'},
      flname_ifc[50] = {'\0'},
      flname_imn[50] = {'\0'},
      flname_inc[50] = {'\0'},
      flname_lty[50] = {'\0'},
      flname_rpd[50] = {'\0'},

      pltfle_ica[50] = AMD_RESULTS,
      pltfle_ifc[50] = AMD_RESULTS,
      pltfle_imn[50] = AMD_RESULTS,
      pltfle_inc[50] = AMD_RESULTS,
      pltfle_lty[50] = AMD_RESULTS,
      pltfle_rpd[50] = AMD_RESULTS,

      parmtr_fle[50] = AMD_RESULTS;

   char
      plot_ica[50] = AMD_RESULTS,
      plot_ifc[50] = AMD_RESULTS,
      plot_imn[50] = AMD_RESULTS,
      plot_inc[50] = AMD_RESULTS,
      plot_lty[50] = AMD_RESULTS,
      plot_rpd[50] = AMD_RESULTS;

   long
     ii = null,
     kk = null;

   static double
      hh0 = ZERO,
      scpt0 = ZERO,
      lnrpt = ZERO,   /* log( Repr(t)/Ttrm ) */
      ndays_inc_upd = ZERO,
      suscpt_upd = ZERO,   /* 1. - h(t) */
      infected_upd = ZERO,
      immune_upd = ZERO, /* updated immunity, inner loop */
      incidence_upd = ZERO,
      lethal_upd = ZERO,
      reprod_upd = ZERO, /* updated reproduction number, inner loop */
      integral_incidence = ZERO;

/*----------------------------- end declarations -----------------------------*/
/* assign structure pointers */

   stp = state;
   ppt = stp->par;
   opr = stp->opr;
/*............................................................................*/
   strcat( parmtr_fle, "parameters" );

   strcat( plot_ica, "gpl_n_days_incidence" );
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

   strcat( plot_ica, longstr );
   strcat( plot_ifc, longstr );
   strcat( plot_imn, longstr );
   strcat( plot_inc, longstr );
   strcat( plot_lty, longstr );
   strcat( plot_rpd, longstr );
/*............................................................................*/
/* dictionary: */
      
/* Ncom = 8.20e+07;  herd size [ number of members ] */
/* Nifc = 1.60e+05;  number of initially infected members [sum] */
/* Nimn = Nifc;      initial number immune members [ usually ~ Nifc ] */
/* Ninf = 3.40e+04;  initial number of infective [sick] members */
/* Nlty = 2.40e+03;  initial number of deceased members */

/* rifc = Nifc/Ncom; initial ratio of infected members */
/* rimn = Nimn/Ncom; initial herd immunity [ ratio ] */
/* rinf = Ninf/Ncom; initial ratio of infective members */
/* rlty = Nlty/Ncom; initial ratio of deceased members */
/*............................................................................*/
/* desease features [example values]: */

/* Repr = 1.000;  initial reproduction number */
/* Tend = 365.0;  computed time intervall [ days ] */
/* Tinc =   14.;  incidence average time [ days ] */
/* Ttrm =    7.;  mean transmissive time [ days ] */
/*............................................................................*/
/* LnRp = log( Repr )/Ttrm;  i.e. exp( LnRp ) = Repr[0]^(1./Ttrm) */ 
/* rrpd = exp( LnRp ); = Repr[0]^(1./Ttrm), base of init. exp. incr.  */
/*............................................................................*/
/* copy the input parameters */

   ppt->Ncom = ppt->s[1];
   ppt->Ninf = ppt->s[2];
   ppt->Nifc = ppt->s[3];
   ppt->Nimn = ppt->s[4];
   ppt->Nlty = ppt->s[5];
   ppt->Repr = ppt->s[6];
   ppt->Nthr = ppt->s[7];
   ppt->Immc = ppt->s[8];
   ppt->Slnt = ppt->s[9];
   ppt->Ltlt = ppt->s[10];
   ppt->Ttrm = ppt->s[11];
   ppt->Timu = ppt->s[12];
   ppt->Tinc = ppt->s[13];
   ppt->Tend = ppt->s[14];
   ppt->DltT = ppt->s[15];
/*............................................................................*/
/* normalized parameters: */

   ppt->dt = ppt->DltT/ppt->Ttrm;
   ppt->timn = ppt->Timu/ppt->Ttrm; /* timn: Timu in natural units */
   ppt->ticn = ppt->Tinc/ppt->Ttrm; /* ticn: Tinc in natural units */

   ppt->kend = ( long )( ppt->Tend/ppt->DltT );
   ppt->kinc = ( long )( ppt->Tinc/ppt->DltT );
   ppt->ktrm = ( long )( ppt->Ttrm/ppt->DltT );

   ppt->mxictm = ppt->ktrm;

   if ( ppt->mxictm < ppt->kinc )
      ppt->mxictm = ppt->kinc;

   ppt->rifc = ppt->Nifc/ppt->Ncom;
   ppt->rimn = ppt->Nimn/ppt->Ncom;
   ppt->rinf = ppt->Ninf/ppt->Ncom;
   ppt->rlty = ppt->Nlty/ppt->Ncom;
   ppt->rthr = ppt->Nthr/ppt->Ncom;
   
   ppt->wght_imm = ( 100.*ppt->Immc - ppt->Ltlt )/( 100. - ppt->Slnt );
   ppt->wght_ifc = ( 100./( 100. - ppt->Slnt ));
   ppt->wght_lty = ppt->Ltlt/( 100. - ppt->Slnt );
/*............................................................................*/
/* limits: */

   ppt->maxout = ( long ) opr->n[1]; /* null < maxout <= 10000 !!! */
   ppt->maxinn = ( long ) opr->n[2]; /* null < maxinn <= 10000 !!! */

   if ( 100000 < ppt->maxinn )
      ppt->maxinn = 100000;
   else if ( ppt->maxinn < ONE )
      ppt->maxinn = 1;
      
   ppt->maxout = \
   ( long ) fminl(( ppt->kend/ppt->maxinn ), 100000. );

   ppt->formula = ( char ) ( opr->n[3] );
   ppt->xscale = ( char ) ( opr->n[4] );
   ppt->yscale = ( char ) ( opr->n[5] );
   ppt->yunits = ( char ) ( opr->n[6] );
   ppt->titles = ( char ) ( opr->n[7] );
   ppt->nmstop = ( char ) ( opr->n[8] );
/*............................................................................*/
/* Repr^(1./Ttrm), base of initial exponential increase */
/* exp( LnRp ) = Repr^(1./Ttrm) */ 

   ppt->repr = ppt->Repr;
/*............................................................................*/
/* store initial parameters in file <parmtr_fle> */

   fleptr_par = fopen( parmtr_fle, "w+" ); 

   fprintf( fleptr_par,
      "Total number of community members: %10.5e\n", ppt->Ncom );

   fprintf( fleptr_par,
      "Number of initially infected members: %10.5e\n\n", ppt->Nifc );

   fprintf( fleptr_par,
      "Initial group immunity: %10.5e %%\n", 100.*( ppt->rimn ));

   fprintf( fleptr_par,
      "Mean transmission time: %f days\n", ppt->Ttrm );

   fprintf( fleptr_par,
      "Incidence averaged over %f days\n", ppt->Tinc );

   fprintf( fleptr_par,
      "Mean duration of immunity: %f days\n", ppt->Timu );

   fprintf( fleptr_par,
      "Initial reproduction number\n"\
      "( mean number of herd members "\
      "infected by one contagious member ): %f\n\n", ppt->Repr );
      
   fprintf( fleptr_par,
      "Time limit: T = %10.5e days\n", ppt->Tend );

   if ( ppt->xscale == null )
      fprintf( fleptr_par,
         "Internal time step: dt = %10.5e transmission periods\n", ppt->dt );
   else
      fprintf( fleptr_par,
         "Time step: Dt = %10.5e days\n", ppt->DltT );

   fprintf( fleptr_par,
      "Total number of iterations: [ Tend/Dt ] = %ld\n", ppt->kend );

   fprintf( fleptr_par,
      "Incidence averaged over iterations: [ Tinc/Dt ] = %ld\n", ppt->kinc );

   fprintf( fleptr_par,
      "Base of initial exponential increase: %10.5e\n", ppt->repr );

   fclose( fleptr_par );
/*............................................................................*/
   strcpy( longstr, "R0" );
   
/* strcat( longstr, lotos(( state->job ), null, " " )); */

   strcat( longstr, "=" );
   strcat( longstr, dotos( ppt->Repr, 4, "f" ));

   strcat( flname_ica, lotos(( short ) ppt->Tinc, null, " " ));
   strcat( flname_ica, "_days_incidence_" );
   strcat( flname_ica, longstr );
   strcat( pltfle_ica, flname_ica );

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

   pltptr_ica = fopen( pltfle_ica, "w+" );
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
   fprintf( pltptr_ica, "%s",\
      "# Epidemic | " );
*/
   fprintf( pltptr_ica, "%s",\
      "# Epidemic " );
    
   strcpy( optnstr, "Incidence," );
   strcat( optnstr, lotos(( long ) ppt->Tinc, 2, " " ));
   strcat( optnstr, " days " );

   fprintf( pltptr_ica, "%s", optnstr );

   fprintf( pltptr_ica, "%s",\
      "[ x-unit: " );
   fprintf( pltptr_ica, "%s", timestr );

   if ( ppt->yunits == null )
      fprintf( pltptr_ica, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_ica, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_ifc, "%s",\
      "# Epidemic | infected members [ x-unit: " );
   fprintf( pltptr_ifc, "%s", timestr );

   if ( ppt->yunits == null )
      fprintf( pltptr_ifc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_ifc, "%s", " | y-unit: % ]\n" );

   fprintf( pltptr_imn, "%s",\
      "# Epidemic | immune members [ x-unit: " );
   fprintf( pltptr_imn, "%s", timestr );

   if ( ppt->yunits == null )
      fprintf( pltptr_imn, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_imn, "%s", " | y-unit: % ]\n" );

   fprintf( pltptr_inc, "%s",\
      "# Epidemic | incidence [ x-unit: " );
   fprintf( pltptr_inc, "%s", timestr );

   if ( ppt->yunits == null )
      fprintf( pltptr_inc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_inc, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_lty, "%s",\
      "# Epidemic | deceased members [ x-unit: " );
   fprintf( pltptr_lty, "%s", timestr );

   if ( ppt->yunits == null )
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

   ppt->minica =  1.00e+27;
   ppt->maxica = -1.00e+27;
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

   hh0 = immune_upd + lethal_upd;
   scpt0 = 1. - hh0;

   if ( ppt->formula == null ) /* Repr is basic reproduction number */
      reprod_upd = scpt0*ppt->repr;
   else /* Repr is current reproduction number */
      reprod_upd = ppt->repr;

   lnrpt= log( reprod_upd ); 
   ppt->dudt[null] = incidence_upd;
   
   ii = null;
   while( ii < ppt->mxictm )
   {
      ii++;
      ppt->dudt[ii] = ZERO;
   };

   kk = null;
   ppt->tt = ZERO;
   integral_incidence = ZERO;
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
         hh0 = immune_upd + lethal_upd;
         suscpt_upd = ( 1. - hh0 ); 


         if ( ppt->nmstop == ONE ) /* stop if no sick members remain */
	 {
            if ((( incidence_upd * reprod_upd ) < ppt->rthr )
	       || ( suscpt_upd <= ppt->rthr ))
            { 
/* [ no new cases or group immunity attained ] */

	       ppt->dudt[null] = ZERO;
       	       ppt->Timmun = ppt->tt;
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
               lnrpt = log( reprod_upd );
               incidence_upd *= \
                  exp( ppt->dt*lnrpt );

              break;
/*...........................................................................*/
              case 1:

               suscpt_upd /= scpt0;

	       reprod_upd = suscpt_upd*ppt->repr;
               lnrpt = log( reprod_upd );
               incidence_upd *= \
                  exp( ppt->dt*lnrpt );

              break;
/*...........................................................................*/
              case 2: /* R(t) = R(0) [ constant ] */

               incidence_upd *= exp( ppt->dt*lnrpt );
		  
              break;
            };
/*...........................................................................*/
/* integrate incidence */

            integral_incidence += ( ppt->dt * incidence_upd );

/*...........................................................................*/
/* update herd infection, immunity and incidence */

            infected_upd +=\
               ( ppt->dt * ppt->wght_ifc * incidence_upd );

            if ( infected_upd > ( 1. - ppt->rthr ))
	       infected_upd = 1.;

            lethal_upd +=\
               ( ppt->dt * ppt->wght_lty * incidence_upd );
         }
	 else /* suscpt_upd <= ppt->rthr */
            incidence_upd = ZERO;

         ppt->dudt[null] = incidence_upd;

/*...........................................................................*/
/* the immune fraction */
	 
         immune_upd *= ( exp( - ppt->dt / ppt->timn ));
         immune_upd +=\
            ( ppt->dt * ppt->wght_imm * ppt->dudt[null] );

/*...........................................................................*/
/* mean n days incidence */
/* and shift dudt from k to k+1 */    

         ndays_inc_upd = ZERO;
         ii = ppt->mxictm;
	 while( null < ii )
         {
            ppt->dudt[ii] = ppt->dudt[ii-ONE];
	    
	    if ( ii < ppt->kinc )
               ndays_inc_upd += \
                  ( ppt->dt*ppt->dudt[ii] );

	    ii--;
         };
         ndays_inc_upd /= ppt->ticn;

         ppt->tt += ppt->dt;
         ppt->ninn++ ;
	 kk++;
      }; /* while ( ppt->ninn < ppt->maxinn ) */

/*......................end inner loop .........................*/
      ppt->nout++;

   }; /* while ( ppt->nout < ppt->maxout) */
   
/*............................end of outer loop ..............................*/
  finish:

   fclose( pltptr_ica );
   fclose( pltptr_ifc );
   fclose( pltptr_imn );
   fclose( pltptr_inc );
   fclose( pltptr_lty );
   fclose( pltptr_rpd );

/*............................................................................*/
/* form the plot headers
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
      strcpy( optnstr, "Incidence (" );
      strcat( optnstr, lotos(( long ) ppt->Tinc, 2, " " ));
      strcat( optnstr, " days )" );
   }
   else
      strcpy( optnstr, " " );

   if ( ppt->yunits == null ) /* normalized y-units [ herd size = 1 ] */
   {
      GNUPLOT( gnuptr_ica, plot_ica, flname_ica, optnstr, timestr, \
         " ", ( .77*1.0e+0*ppt->minica ), ( 1.10e+0*ppt->maxica ));

      if ( ppt->titles == ONE )
         strcpy( optnstr,
            "Herd infection [ sum of recovered, "
	    "sick, asymptomatic, and lethal cases ]" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr, \
         " ", ( .77*1.0e+0*ppt->rifc ), ( 1.10e+0*ppt->maxifc ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Immunity" );
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
      GNUPLOT( gnuptr_ica, plot_ica, flname_ica, optnstr, timestr, \
         "per 100000", ( .77*1.0e+5*ppt->minica ), ( 1.10e+5*ppt->maxica ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, \
            "Herd infection [ sum of recovered, "
	    "sick, asymptomatic, and lethal cases ]" );
      else
         strcpy( optnstr, " " );

      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr, \
         "percent", ( .77*1.0e+2*ppt->rifc ), ( 1.10e+2*ppt->maxifc ));

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Immunity" );
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
         "members", ( .77*ppt->rlty*ppt->Ncom ), \
            ( 1.10e+0*ppt->maxlty*ppt->Ncom ));
   };

   if ( ppt->titles == ONE )
      strcpy( optnstr, "Reproduction number" );
   else
         strcpy( optnstr, " " );

   GNUPLOT( gnuptr_rpd, plot_rpd, flname_rpd, optnstr, timestr, \
      "reprod. no", ( .77*ppt->minrpd ), ( 1.10*ppt->maxrpd ));
/*............................................................................*/
/* store maxima: */ 
      
   fleptr_par = fopen( parmtr_fle, "a+" );
      
   fprintf( fleptr_par,
      "\nIncidence maximum at %10.5e-th day: ", ppt->Tmxinc );
   fprintf( fleptr_par,
      "%10.5e %%\n", 100.*( ppt->maxinc ));
   fprintf( fleptr_par,
      "Maximum number of sick members attained "\
      "at %10.5e-th day: ", ppt->Tmxinc );
   fprintf( fleptr_par,
      "%10.5e\n", ( ppt->maxinc )*( ppt->Ncom ));
	 
   fprintf( fleptr_par,
      "%s", "integral_incidence = ");
   fprintf( fleptr_par,
      "%10.5e\n", integral_incidence );

   if ( ZERO < ppt->Timmun )
      fprintf( fleptr_par,
         "\n100%% group immunity attained "\
         "at %10.5e-th day\n", ppt->Timmun );
   else
      fprintf( fleptr_par,
         "\nGroup immunity not attained !\n" );

   fclose( fleptr_par );
/*...........................................................................*/
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

                        Seneca
                        Briefe an Lucilius
*/
/* EOF */
