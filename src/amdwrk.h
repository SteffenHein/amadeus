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
*  [ Update: February 23, 2022 ]                            <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# ifndef AMD_JOBLBL
   # define AMD_JOBLBL ONE /* [0] 1: [don't] append job labels at file names  */
# endif
/*----------------------------------------------------------------------------*/
# ifndef AMD_INTRPL
   # define AMD_INTRPL ONE /* [0] 1: [no] initial N-days incid. interpolation */
# endif
/*----------------------------------------------------------------------------*/
# ifndef AMD_FRAME
   # define AMD_FRAME ( 7.7e-02 ) /* frame of graphics [ cf. GNUPLOT ] */
# endif
/*----------------------------------------------------------------------------*/
/* susceptibility threshold */
# ifndef SUSCPT_THR
     # define SUSCPT_THR ( PRECISION )
# endif
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
   static time_t
      bufsize = null;

/* time_t types etc.: */

   time_t
      nseconds = null,
     *timer = null;

   static char
     timeptr[STS_SIZE] = {null};
/*----------------------------------------------------------------------------*/

   AMDSTATE
     *stp = state;

   DSPLAY 
     *dsplay( DSPLAY *dsp );

   static DSPLAY
     *dsp = null;

   static PARMTRS
     *ppt = null;

   static OPERTNS
     *opt = null;

   static FILE
     *logfle = null,
     *pltptr_cic = null,
     *pltptr_ifc = null,
     *pltptr_imm = null,
     *pltptr_inc = null,
     *pltptr_dcd = null,
     *pltptr_rpd = null,
     *fleptr_par = null;

   static FILE
     *gnuptr_cic = null,
     *gnuptr_ifc = null,
     *gnuptr_imm = null,
     *gnuptr_inc = null,
     *gnuptr_dcd = null,
     *gnuptr_rpd = null;

   char   
      inptstr[80] = {'\0'},
      outpstr[80] = {'\0'},
      optnstr[50] = {'\0'},
      timestr[50] = {'\0'},
      longstr[50] = {'\0'},

      flname_cic[50] = {'\0'},
      flname_ifc[50] = {'\0'},
      flname_imm[50] = {'\0'},
      flname_inc[50] = {'\0'},
      flname_dcd[50] = {'\0'},
      flname_rpd[50] = {'\0'},

      pltfle_cic[50] = AMD_RESULTS,
      pltfle_ifc[50] = AMD_RESULTS,
      pltfle_imm[50] = AMD_RESULTS,
      pltfle_inc[50] = AMD_RESULTS,
      pltfle_dcd[50] = AMD_RESULTS,
      pltfle_rpd[50] = AMD_RESULTS,

      parmtr_fle[50] = AMD_RESULTS;

   char
      plot_cic[50] = AMD_RESULTS,
      plot_ifc[50] = AMD_RESULTS,
      plot_imm[50] = AMD_RESULTS,
      plot_inc[50] = AMD_RESULTS,
      plot_dcd[50] = AMD_RESULTS,
      plot_rpd[50] = AMD_RESULTS;

   long
     ii = null,
     kk = null;

   static double
      hh = ZERO,
      rnd = ZERO,
      frm = ZERO,
      rrpd = ZERO,
      lwbnd = ZERO,
      upbnd = ZERO,
      scpt0 = ZERO,
      lnrpd = ZERO, /* log( Repr(t)/Ttrm ) */
      nxtbst = ZERO,     
      bststp = ZERO,     
      suscpt_upd = ZERO,   /* 1. - h(t) */
      incdnc_upd = ZERO,
      incidc_upd = ZERO,
      infctd_upd = ZERO,
      cmlinc_upd = ZERO,
      immune_upd = ZERO, /* updated immunity, inner loop */
      lethal_upd = ZERO,
      reprod_upd = ZERO, /* updated reproduction number, inner loop */
      integral_inc = ZERO;

# if AMD_INTRPL == 1
      static double 
         uu = ZERO,
         vv = ZERO;
# endif
/*----------------------------- end declarations -----------------------------*/
/* assign structure pointers */

   stp = state; 
   ppt = state->par;
   opt = state->opr;
/*............................................................................*/
/* initialize dsplay(*) [ structure dsp* DSPLAY ]: */

   dsp = dsplay( null );

   logfle = fopen( stp->logfle, "r+" );
   fseek( logfle, stp->fleps, SEEK_SET );
/*
   errfle = fopen( stp->errfle, "a+" );
*/
   if ( stp->uif != 't' )
   {
      kk = setvbuf( logfle, null, _IONBF, bufsize ); /* set unbuffered */
      dsp->display = logfle;
   }
   else
      dsp->display = stdout;
/*............................................................................*/
   strcat( parmtr_fle, "parameters" );

   strcat( plot_cic, "gpl_n_days_incidence" );
   strcat( plot_ifc, "gpl_infection" );
   strcat( plot_imm, "gpl_immunity" );
   strcat( plot_inc, "gpl_incidence" );
   strcat( plot_dcd, "gpl_lethality" );
   strcat( plot_rpd, "gpl_reproduction" );
/*............................................................................*/
/* append job number to filenames */

# if AMD_JOBLBL == 1
   strcpy( longstr, "_job_no_" );
   strcat( longstr, lotos(( state->job ), null, " " ));

   strcat( parmtr_fle, longstr );
   strcat( plot_cic, longstr );
   strcat( plot_ifc, longstr );
   strcat( plot_imm, longstr );
   strcat( plot_inc, longstr );
   strcat( plot_dcd, longstr );
   strcat( plot_rpd, longstr );
# endif
/*............................................................................*/
/* dictionary: */
      
/* Nhrd = 8.20e+07;  herd size [ number of members ] */
/* Ninf = 3.40e+04;  initial number of infective [acutely sick] members */
/* Nifc = 1.60e+05;  number of initially infected members Ninf <= Nifc */
/* Nimn = 1.60e+05;  initially immune members */
/* Nlty = 2.40e+03;  initially already of deceased members */
/* Bstf = 0.000+00;  random burst level [0<=Bstf] */

/* rinf = Ninf/Nhrd; initial ratio of infective members */
/* rifc = Nifc/Nhrd; initial ratio of infected members */
/* rimn = Nimn/Nhrd; initial herd immunity [ ratio ] */
/* rlty = Nlty/Nhrd; initial ratio of deceased members */
/*............................................................................*/
/* desease features [ parameter examples ]: */

/* Repr = 1.000;  initial reproduction number */
/* Tend = 365.0;  computed time intervall [ days ] */
/* Tcic =    7.;  incidence cumulated over time [ days ] */
/* Ttrm =    5.;  mean transmission time [ days ] */
/*............................................................................*/
/* LnRp = log( Repr )/Ttrm;  i.e. exp( LnRp ) = Repr[0]^(1./Ttrm) */ 
/* rrpd = exp( LnRp ); = Repr[0]^(1./Ttrm), base of init. exp. incr. */
/*...........................................................................*/
/* copy the input parameters */

   ppt->Nhrd = ppt->s[1];  /* herd size */
   ppt->Ninf = ppt->s[2];  /* initially infective [ acutely sick ] members */
   ppt->Nifc = ppt->s[3];  /* initially infected members */
   ppt->Nimn = ppt->s[4];  /* initially immune members */
   ppt->Nlty = ppt->s[5];  /* initially already deceased members */
   ppt->Repr = ppt->s[6];  /* initial reproduction factor */
   ppt->Immc = ppt->s[7];  /* immunization coefficient [ ratio: 0<Immc<=1 ] */
   ppt->Slnt = ppt->s[8];  /* percentage of asymptomatic ['silent'] cases */
   ppt->Ltlt = ppt->s[9];  /* percentage of lethal cases */
   ppt->Ttrm = ppt->s[10]; /* mean transmission time [ days ] */
   ppt->Timu = ppt->s[11]; /* immunity half-life time [ days ] */
   ppt->Tcic = ppt->s[12]; /* incidence cumulation time [ days ] */
   ppt->Ithr = ppt->s[13]; /* incidence threshold [stop below that number...] */
   ppt->Bstf = ppt->s[14]; /* average burst factor */
   ppt->Tlen = ppt->s[15]; /* average burst length [ days ] */
   ppt->Trep = ppt->s[16]; /* average burst repetion time [ days ] */
   ppt->Tend = ppt->s[17]; /* length of modelled time interval [ days ] */ 
   ppt->DltT = ppt->s[18]; /* time increment [ days ] */ 
/*............................................................................*/
/* normalized parameters: */

   ppt->dt = ppt->DltT/ppt->Ttrm;
   ppt->tcin = ppt->Tcic/ppt->Ttrm; /* tcin: Tcic in natural units */
   ppt->tlen = ppt->Tlen/ppt->Ttrm; /* tlen: Tlen in natural units */
   ppt->trep = ppt->Trep/ppt->Ttrm; /* trep: Trep in natural units */
   ppt->timn = ppt->Timu/ppt->Ttrm/LN2; /* immunity half-life [ LN2 = log(2) ]*/

   nxtbst = ppt->trep; /* burst start */ 
   bststp = ppt->tlen; /* burst stop */

   ppt->kend = ( long )( ppt->Tend/ppt->DltT );
   ppt->kcic = ( long )( ppt->Tcic/ppt->DltT );
   ppt->ktrm = ( long )( ppt->Ttrm/ppt->DltT );

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
   ppt->xunits = ( char ) ( opt->n[4] );
   ppt->yunits = ( char ) ( opt->n[5] );
   ppt->yscale = ( char ) ( opt->n[6] );
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
      "\nImmunity_half-life_time","days", 60 );
   strcat( outpstr, ": ");

   if ( ppt->Timu < 1.00e+05 )
      strcat( outpstr, dotos( ppt->Timu, 4, "e" ));
   else
      strcat( outpstr, "Infinite" );

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

   if ( ppt->formula == null )      /* Repr is basic reproduction number */
   {
      cpylne( outpstr,
         "\nBasic_reproduction_factor","dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Repr, 4, "e" ));
      fprintf( fleptr_par, outpstr );
   }
   else
   {
      cpylne( outpstr,
         "\nInitial_reproduction_factor","dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Repr, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      scpt0 = 1. - ( ppt->rimn + ppt->rlty );

      cpylne( outpstr,
         "\nBasic_reproduction_factor_[estimate]","dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Repr/scpt0, 4, "e" ));
      fprintf( fleptr_par, outpstr );
   };

   cpylne( outpstr,
      "\nInitial_base_of_exponential_increase","dimensionless", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( rrpd, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

   if ( ZERO < ppt->Bstf )
   {
      cpylne( outpstr,
         "\nRandom_burst_level","dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Bstf, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nAverage_burst_length","days", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Tlen, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nAverage_burst_repetition_rate","days", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Trep, 4, "e" ));
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
   strcat( longstr, "=" );
   strcat( longstr, dotos( ppt->Repr, 4, "f" ));
/*----------------------------------------------------------------------------*/
# if AMD_JOBLBL == 1
/* append job number to filenames */

   strcat( longstr, "_job_no_" );
   strcat( longstr, lotos(( state->job ), null, " " ));
# endif
/*----------------------------------------------------------------------------*/
   strcat( flname_cic, lotos(( short ) ppt->Tcic, null, " " ));
   strcat( flname_cic, "_days_incidence_" );
   strcat( flname_cic, longstr );
   strcat( pltfle_cic, flname_cic );

   strcat( flname_ifc, "ifc_" );
   strcat( flname_ifc, longstr );
   strcat( pltfle_ifc, flname_ifc );

   strcat( flname_imm, "imm_" );
   strcat( flname_imm, longstr );
   strcat( pltfle_imm, flname_imm );

   strcat( flname_inc, "inc_" );
   strcat( flname_inc, longstr );
   strcat( pltfle_inc, flname_inc );

   strcat( flname_dcd, "dcd_" );
   strcat( flname_dcd, longstr );
   strcat( pltfle_dcd, flname_dcd );

   strcat( flname_rpd, "rpd_" );
   strcat( flname_rpd, longstr );
   strcat( pltfle_rpd, flname_rpd );

   pltptr_cic = fopen( pltfle_cic, "w+" );
   pltptr_ifc = fopen( pltfle_ifc, "w+" );
   pltptr_imm = fopen( pltfle_imm, "w+" );
   pltptr_inc = fopen( pltfle_inc, "w+" );
   pltptr_dcd = fopen( pltfle_dcd, "w+" );
   pltptr_rpd = fopen( pltfle_rpd, "w+" );
   
   if ( ppt->xunits == null )
      strcpy ( timestr, "transmission cycles" );
   else
      strcpy ( timestr, "days" );

   fprintf( pltptr_cic, "%s", "# Epidemic | " );
    
   strcpy( optnstr, lotos(( long ) ppt->Tcic, 2, " " ));
   strcat( optnstr, " days incidence " );

   fprintf( pltptr_cic, "%s", optnstr );
   fprintf( pltptr_cic, "%s", "[ x-unit: " );
   fprintf( pltptr_cic, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_cic, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_cic, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_ifc, "%s",\
      "# Epidemic | infected members [ x-unit: " );
   fprintf( pltptr_ifc, "%s", timestr );

   if (( ppt->yunits == null )
     ||( ppt->yunits == TWO ))
      fprintf( pltptr_ifc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_ifc, "%s", " | y-unit: % ]\n" );

   fprintf( pltptr_imm, "%s",\
      "# Epidemic | immune members [ x-unit: " );
   fprintf( pltptr_imm, "%s", timestr );

   if (( ppt->yunits == null )
     ||( ppt->yunits == TWO ))
      fprintf( pltptr_imm, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_imm, "%s", " | y-unit: % ]\n" );
      
   if ( ppt->xunits == null )
      fprintf( pltptr_inc, "%s",\
         "# Epidemic | incidence [ x-unit: " );
   else
      fprintf( pltptr_inc, "%s",\
         "# Epidemic | daily incidence [ x-unit: " );

   fprintf( pltptr_inc, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_inc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_inc, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_dcd, "%s",\
      "# Epidemic | deceased members [ x-unit: " );
   fprintf( pltptr_dcd, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_dcd, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_dcd, "%s", " | y-unit: % ]\n" );

   fprintf( pltptr_rpd, "%s",\
      "# Epidemic | reproduction number\n"
      "# [ x-unit: " );
   fprintf( pltptr_rpd, "%s", timestr );

   fprintf( pltptr_rpd, "%s", \
      " | y-unit: members infected by one sick member ]\n");
/*............................................................................*/
/* initialize iteration */

   ppt->mincic =  1.00e+77;
   ppt->maxcic = -1.00e+77;
   ppt->mininc =  1.00e+77;
   ppt->maxinc = -1.00e+77;
   ppt->minifc =  1.00e+77;
   ppt->maxifc = -1.00e+77;
   ppt->minimn =  1.00e+77;
   ppt->maximn = -1.00e+77;
   ppt->minlty =  1.00e+77;
   ppt->maxlty = -1.00e+77;
   ppt->minrpd =  1.00e+77;
   ppt->maxrpd = -1.00e+77;

/*............................................................................*/
/* start outer loop */

   incdnc_upd = ppt->rinf;
   infctd_upd = ppt->rifc;
   immune_upd = ppt->rimn;
   lethal_upd = ppt->rlty;

   hh = immune_upd + lethal_upd;
   scpt0 = 1. - hh;

   if ( ppt->formula == null )      /* Repr is basic reproduction number */
      reprod_upd = scpt0*ppt->repr;
   else                             /* Repr is initial reproduction number */
      reprod_upd = ppt->repr;

   lnrpd= log( reprod_upd );
   ppt->dhdt[null] = incdnc_upd;
   
   ii = null;
   while( ii < ppt->mxictm )
   {
      ii++;
      ppt->dhdt[ii] = ZERO;
   };

   rnd = 1.;
   integral_inc = ZERO;
   incidc_upd = incdnc_upd;
   cmlinc_upd = incidc_upd*ppt->Tcic/ppt->Ttrm;
/*...........................................................................*/
/* here start the iterations */
/* outer loop */

   kk = null;
   ppt->tt = ZERO;
   ppt->nout = null;
   while ( ppt->nout < ppt->maxout )
   {
/*...........................................................................*/
/* store values */

      if ( ppt->xunits == ONE ) /* [ xunits "days" ] */
         incidc_upd /= ppt->Ttrm;

      STOREVAL(1, AMD_INTRPL );
/*...........................................................................*/
/* compute extrema in outer loop: set EXTREMA(1)  */

      EXTREMA( ONE );
/*...........................................................................*/
/* start inner loop */

      ppt->ninn = null;
      while ( ppt->ninn < ppt->maxinn )
      {
/*...........................................................................*/
/* compute extrema in inner loop: set EXTREMA(1) */

         EXTREMA( null );
/*...........................................................................*/
         hh = immune_upd + lethal_upd;
         suscpt_upd = fmax(( 1. - hh ), SUSCPT_THR ); 

         if ( ppt->nmstop == ONE ) /* stop if no susceptible members remain */
	 {
	    if ( suscpt_upd < ppt->rthr )
            { 
/* susceptible fraction smaller than N = ppt->Tthr herd members */

	       ppt->dhdt[null] = ZERO;
       	       ppt->timmun = ppt->tt;
	       incidc_upd = ZERO;
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
               incdnc_upd *= \
                  exp( ppt->dt*lnrpd );

              break;
/*...........................................................................*/
              case 1:

               suscpt_upd /= scpt0;

	       reprod_upd = suscpt_upd*ppt->repr;
               lnrpd = log( reprod_upd );
               incdnc_upd *= \
                  exp( ppt->dt*lnrpd );

              break;
/*...........................................................................*/
              case 2: /* R(t) = R(0) [ constant ] */

               incdnc_upd *= exp( ppt->dt*lnrpd );
		  
              break;
            };
         }
	 else /* suscpt_upd <= ppt->rthr */
            incdnc_upd = ZERO;
/*...........................................................................*/
         incidc_upd = incdnc_upd;

         if ( ZERO < ppt->Bstf )
         {
            if ( nxtbst < ppt->tt ) /* burst start */
	    {
               rnd = ( double ) rand( );
               rnd /= RAND_MAX; 

	       bststp = ppt->tt;
	       bststp += ( 2.*rnd*ppt->tlen ); /* next stop */
               nxtbst = bststp;

               rnd = ( double ) rand( ); 
               rnd /= RAND_MAX; 
               rnd = 1. + 2.*rnd*ppt->Bstf;
            }

            if ( bststp < ppt->tt ) /* burst stop */
	    {
               rnd = ( double ) rand( ); 
               rnd /= RAND_MAX; 

	       nxtbst = ppt->tt;
	       nxtbst += ( 2.*rnd*ppt->trep ); /* next burst */
               bststp = nxtbst;

	       rnd = 1.;
            };

            incidc_upd *= rnd;
         }; 
/*...........................................................................*/
/* integrate incidence */

         integral_inc += ( ppt->dt*incidc_upd );

/*...........................................................................*/
/* update herd infection, immunity and incidence */

         infctd_upd +=\
            ( ppt->dt*ppt->wght_ifc*incidc_upd );

         if ( 1. < infctd_upd )
	    infctd_upd = 1.;

         lethal_upd +=\
            ( ppt->dt*ppt->wght_lty*incidc_upd );
/*...........................................................................*/
/* the immune fraction */
	 
         immune_upd *= ( exp( - ppt->dt / ppt->timn ));
         immune_upd +=\
            ( ppt->dt*ppt->wght_imm*incidc_upd );

         if ( 1. < immune_upd )
	    immune_upd = 1.;
/*...........................................................................*/
/* mean n days incidence */
/* and shift dudt from k to k+1 */    

         ppt->dhdt[null] = incidc_upd;
	 
         cmlinc_upd = ZERO;
         ii = ppt->kcic;
	 while( null < ii )
         {
            ppt->dhdt[ii] = ppt->dhdt[ii-ONE];
            cmlinc_upd += ppt->dhdt[ii];
	    --ii;
         };
         cmlinc_upd *= ppt->dt;

# if AMD_INTRPL == 1

         if ( kk < ppt->kcic )
	    cmlinc_upd = incidc_upd*ppt->Tcic/ppt->Ttrm;
	 else if ( kk < 3.*ppt->kcic )
         {
            uu = ( double )( kk - ppt->kcic )/( 2.*ppt->kcic );
	    vv = 1. - uu;
	    cmlinc_upd = uu*cmlinc_upd + vv*incidc_upd*ppt->Tcic/ppt->Ttrm;
         }; 
# endif
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
   fclose( pltptr_imm );
   fclose( pltptr_inc );
   fclose( pltptr_dcd );
   fclose( pltptr_rpd );

/*............................................................................*/
/* store maxima: */ 
      
   fleptr_par = fopen( parmtr_fle, "a+" );
      
   cpylne( outpstr,
      "\nIncidence_maximum_attained_at",
           "transmission_cycle", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->tmxinc, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   if ( ppt->xunits == null )
   {
      cpylne( outpstr,
         "\nMaximum_incidence","percent", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( 100.*ppt->maxinc, 4, "e" ));
   }
   else
   {
      cpylne( outpstr,
         "\nMaximum_daily_incidence","percent", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( 100.*ppt->maxinc/ppt->Ttrm, 4, "e" ));
   };
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
   if ( ppt->xunits == null )
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

   if (( ppt->yunits == null )
     ||( ppt->yunits == TWO ))
   {
      frm = AMD_FRAME*( ppt->maxcic - ppt->mincic );
      lwbnd = fmax( ppt->mincic - frm, ZERO );
      upbnd = ppt->maxcic + frm;
      GNUPLOT( gnuptr_cic, plot_cic, flname_cic, optnstr, timestr,
        " ", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr,
            "Herd infection [ sum of recovered, "
	    "sick, asymptomatic, and lethal cases ]" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxifc - ppt->minifc );
      lwbnd = fmax( ppt->minifc - frm, ZERO );
      upbnd = ppt->maxifc + frm;
      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr,
        " ", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Immunity" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maximn - ppt->minimn );
      lwbnd = fmax( ppt->minimn - frm, ZERO );
      upbnd = ppt->maximn + frm;
      GNUPLOT( gnuptr_imm, plot_imm, flname_imm, optnstr, timestr,
        " ", lwbnd, upbnd );

      if ( ppt->titles == ONE )
      {
         if ( ppt->xunits == null )
            strcpy( optnstr, "Incidence [ dh/dt ]" );
	 else
            strcpy( optnstr, "Daily incidence [ dh/dt ]" );
      }
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxinc - ppt->mininc );
      lwbnd = fmax( ppt->mininc - frm, ZERO );
      upbnd = ppt->maxinc + frm;
      GNUPLOT( gnuptr_inc, plot_inc, flname_inc, optnstr, timestr, 
        " ", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Deceased" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxlty - ppt->minlty );
      lwbnd = fmax( ppt->minlty - frm, ZERO );
      upbnd = ppt->maxlty + frm;
      GNUPLOT( gnuptr_dcd, plot_dcd, flname_dcd, optnstr, timestr, 
        " ", lwbnd, upbnd );\
   }
   else /* conventional yunits */
   {
      frm = AMD_FRAME*( ppt->maxcic - ppt->mincic );
      lwbnd = fmax( ppt->mincic - frm, ZERO );
      upbnd = ppt->maxcic + frm;
      GNUPLOT( gnuptr_cic, plot_cic, flname_cic, optnstr, timestr,
        "per 100000", 1.0e+05*lwbnd, 1.0e+05*upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, \
            "Herd infection [ sum of recovered, "
	    "sick, asymptomatic, and lethal cases ]" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxifc - ppt->minifc );
      lwbnd = fmax( ppt->minifc - frm, ZERO );
      upbnd = ppt->maxifc + frm;
      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr,
        "percent", 1.0e+02*lwbnd, 1.02e+02*upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Immunity" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maximn - ppt->minimn );
      lwbnd = fmax( ppt->minimn - frm, ZERO );
      upbnd = ppt->maximn + frm;
      GNUPLOT( gnuptr_imm, plot_imm, flname_imm, optnstr, timestr,
        "percent", 1.0e+02*lwbnd, 1.0e+02*upbnd );

      if ( ppt->titles == ONE )
      {
         if ( ppt->xunits == null )
            strcpy( optnstr, "Incidence [ dh/dt ]" );
	 else
            strcpy( optnstr, "Daily incidence [ dh/dt ]" );
      }
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxinc - ppt->mininc );
      lwbnd = fmax( ppt->mininc - frm, ZERO );
      upbnd = ppt->maxinc + frm;
      GNUPLOT( gnuptr_inc, plot_inc, flname_inc, optnstr, timestr,
        "per 100000", 1.0e+05*lwbnd, 1.0e+05*upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Deceased" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxlty - ppt->minlty );
      lwbnd = fmax( ppt->minlty - frm, ZERO );
      upbnd = ppt->maxlty + frm;
      GNUPLOT( gnuptr_dcd, plot_dcd, flname_dcd, optnstr, timestr,
        "members", ppt->Nhrd*lwbnd, ppt->Nhrd*upbnd );
   };

   if ( ppt->titles == ONE )
      strcpy( optnstr, "Reproduction number" );
   else
      strcpy( optnstr, " " );

   frm = AMD_FRAME*( ppt->maxrpd - ppt->minrpd );
   lwbnd = fmax( ppt->minrpd - frm, ZERO );
   upbnd = ppt->maxrpd + frm;
   GNUPLOT( gnuptr_rpd, plot_rpd, flname_rpd, optnstr, timestr,
      "reprod. no", lwbnd, upbnd );
/*............................................................................*/
   if ( stp->uif == 't' )
   {
      strcpy(( dsp->messge ), "\n Job no " );
      strcat(( dsp->messge ), lotos( stp->job, null, " " ));
      strcat(( dsp->messge ), " terminated" );

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ) + 11 );
      strncat(( dsp->messge ), " at ", 4 );
      strncat(( dsp->messge ), timeptr, 8 );
      strcat(( dsp->messge ), "\r" );
/*............................................................................*/
/* termination message - display on screen:                                   */

      dsp->option = 't'; /* terminated */
      dsplay( dsp );
   };

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
