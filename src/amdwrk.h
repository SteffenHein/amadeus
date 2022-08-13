/* [ file: amdwrk.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Body of function amdwrk(*)                                                  *
*  Here is where the numerical computations are done                           *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 21, 2022 ]                                <contact@sfenx.de> *
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
/* graphics frame [ cf. GNUPLOT ] */
# ifndef AMD_FRAME
   # define AMD_FRAME (( double ) 1.0e-01 ) 
# endif
/*----------------------------------------------------------------------------*/
/* least y range [ cf. GNUPLOT ] */
# ifndef AMD_GNURNG
   # define AMD_GNURNG (( double ) 1.0e-14 )
# endif
/*----------------------------------------------------------------------------*/
/* [0] 1 : [don't] reweight recovery history with decaying immunity */
# ifndef AMD_CRRIMN
   # define AMD_CRRIMN 1
# endif
/*----------------------------------------------------------------------------*/
/* [0] N : [don't] reweight vaccination history with decaying immunity */ 
# ifndef AMD_CRRVAC
   # define AMD_CRRVAC 1
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

/*--- function prototypes --------------------------------------------------->*/

   double log( double x );
   double exp( double x );
   double expm1( double x );
   double fmin( double x, double y );
   double fmod( double x, double y );

   char 
      *lotos ( long lngint, char length, char *format );

   char 
      *dotos ( double lngdbl, char precision, char *format );

   void 
      cpylne( char txlne[], const char *ltext, const char *bracket, short ll );

   AMDSTATE 
     *amdmdl( AMDSTATE *state );

   AMDSTATE 
     *amdrnd( AMDSTATE *state );

   AMDSTATE 
     *amdrcs( AMDSTATE *state );

   AMDSTATE 
     *amdevs( AMDSTATE *state );
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

   static OPERTNS
     *opt = null;

   static PARMTRS
     *ppt = null;

   static UPDATES
     *upd = null;

   static FILE
     *logfle = null,
     *fleptr_par = null,
     *pltptr_cic = null,
     *pltptr_ifc = null,
     *pltptr_imm = null,
     *pltptr_inc = null,
     *pltptr_dcd = null,
     *pltptr_rpd = null,
     *pltptr_vac = null;

   static FILE
     *gnuptr_cic = null,
     *gnuptr_ifc = null,
     *gnuptr_inc = null,
     *gnuptr_imm = null,
     *gnuptr_rpd = null,
     *gnuptr_vac = null,
     *gnuptr_dcd = null;

   static char
      inptstr[STS_SIZE] = {'\0'},
      outpstr[STS_SIZE] = {'\0'},
      optnstr[STS_SIZE] = {'\0'},
      timestr[STS_SIZE] = {'\0'},
      longstr[STS_SIZE] = {'\0'},

      flname_cic[STS_SIZE] = {'\0'},
      flname_ifc[STS_SIZE] = {'\0'},
      flname_inc[STS_SIZE] = {'\0'},
      flname_imm[STS_SIZE] = {'\0'},
      flname_rpd[STS_SIZE] = {'\0'},
      flname_vac[STS_SIZE] = {'\0'},
      flname_dcd[STS_SIZE] = {'\0'},

      parmtr_fle[STS_SIZE] = {'\0'},

      pltfle_cic[STS_SIZE] = {'\0'},
      pltfle_ifc[STS_SIZE] = {'\0'},
      pltfle_inc[STS_SIZE] = {'\0'},
      pltfle_imm[STS_SIZE] = {'\0'},
      pltfle_rpd[STS_SIZE] = {'\0'},
      pltfle_vac[STS_SIZE] = {'\0'},
      pltfle_dcd[STS_SIZE] = {'\0'},

      plot_cic[STS_SIZE] = {'\0'},
      plot_ifc[STS_SIZE] = {'\0'},
      plot_inc[STS_SIZE] = {'\0'},
      plot_imm[STS_SIZE] = {'\0'},
      plot_rpd[STS_SIZE] = {'\0'},
      plot_vac[STS_SIZE] = {'\0'},
      plot_dcd[STS_SIZE] = {'\0'};

   static const char
     *dline = "======================================="\
              "=======================================";
   static long
     ii = null;

   static double
      hh = ZERO,
      frm = ZERO,
      rrpd = ZERO,
      lwbnd = ZERO,
      upbnd = ZERO,
      scpt0 = ZERO,
      lnrpd = ZERO; /* log( Repr(t)/Ttrm ) */

# if AMD_INTRPL == 1
      static double 
         uu = ZERO,
         vv = ZERO;
# endif
/*----------------------------- end declarations -----------------------------*/
/* assign structure pointers */

   stp = state; 
   opt = state->opr;
   ppt = state->par;
   upd = state->upd;
/*............................................................................*/
/* initialize dsplay(*) [ structure dsp* DSPLAY ]: */

   dsp = dsplay( null );

   logfle = fopen( stp->logfle, "a+" );
   fseek( logfle, stp->fleps, SEEK_SET );

/* errfle = fopen( stp->errfle, "a+" ); */

   if ( stp->uif != 't' )
   {
    /* kk = setvbuf( logfle, null, _IONBF, bufsize ); */
      setvbuf( logfle, null, _IONBF, bufsize ); 
      dsp->display = logfle;
   }
   else
      dsp->display = stdout;
/*............................................................................*/
/* initialize: */

   ii = null;   
   while ( ii < STS_SIZE )
   {
      inptstr[ii] = '\0';
      outpstr[ii] = '\0';
      optnstr[ii] = '\0';
      timestr[ii] = '\0';
      longstr[ii] = '\0';

      flname_cic[ii] = '\0';
      flname_ifc[ii] = '\0';
      flname_inc[ii] = '\0';
      flname_imm[ii] = '\0';
      flname_rpd[ii] = '\0';
      flname_vac[ii] = '\0';
      flname_dcd[ii] = '\0';

      parmtr_fle[ii] = '\0';

      pltfle_cic[ii] = '\0';
      pltfle_ifc[ii] = '\0';
      pltfle_inc[ii] = '\0';
      pltfle_imm[ii] = '\0';
      pltfle_rpd[ii] = '\0';
      pltfle_vac[ii] = '\0';
      pltfle_dcd[ii] = '\0';

      plot_cic[ii] = '\0';
      plot_ifc[ii] = '\0';
      plot_inc[ii] = '\0';
      plot_imm[ii] = '\0';
      plot_rpd[ii] = '\0';
      plot_vac[ii] = '\0';
      plot_dcd[ii] = '\0';

      ++ii;
   };
/*............................................................................*/
   strcpy( parmtr_fle, AMD_RESULTS );
   strcat( parmtr_fle, "parameters" );

   strcpy( plot_cic, AMD_RESULTS );
   strcat( plot_cic, "gpl_n_days_incidence" );

   strcpy( plot_ifc, AMD_RESULTS );
   strcat( plot_ifc, "gpl_infection" );

   strcpy( plot_inc, AMD_RESULTS );
   strcat( plot_inc, "gpl_incidence" );

   strcpy( plot_imm, AMD_RESULTS );
   strcat( plot_imm, "gpl_immunity" );

   strcpy( plot_rpd, AMD_RESULTS );
   strcat( plot_rpd, "gpl_reproduction" );

   strcpy( plot_vac, AMD_RESULTS );
   strcat( plot_vac, "gpl_vaccination" );

   strcpy( plot_dcd, AMD_RESULTS );
   strcat( plot_dcd, "gpl_deceased" );
/*............................................................................*/
/* append job number at filenames */

# if AMD_JOBLBL == 1
   strcpy( longstr, "_job_no_" );
   strcat( longstr, lotos( state->job, null, "" ));
   
   strcat( parmtr_fle, longstr );

   strcat( plot_inc, longstr );
   strcat( plot_cic, longstr );
   strcat( plot_ifc, longstr );
   strcat( plot_imm, longstr );
   strcat( plot_rpd, longstr );
   strcat( plot_vac, longstr );
   strcat( plot_dcd, longstr );
# endif
/*............................................................................*/
/* dictionary: */
      
/* Nhrd = 8.20e+07;  herd size [ number of individuals ] */
/* Ninf = 3.40e+04;  initial number of infective [acutely sick] individuals */
/* Nifc = 1.60e+05;  number of initially infected individuals Ninf <= Nifc */
/* Nimn = 1.60e+05;  initially immune individuals */
/* Nvac = 0.00e+00;  initially vaccinated individuals */
/* Nlty = 2.40e+03;  initially already of deceased individuals */
/* Bstf = 0.000+00;  random burst level [0<=Bstf] */

/* rinf = Ninf/Nhrd; initially infective fraction */
/* rifc = Nifc/Nhrd; initially infected fraction */
/* rimn = Nimn/Nhrd; initially recovered immune fraction */
/* rvcd = Nvac/Nhrd; initially vaccinated fraction */
/* rlty = Nlty/Nhrd; initially already deceased fraction */
/*............................................................................*/
/* disease features [ parameter examples ]: */

/* Repr = 1.000; initial reproduction number [ basic or effective ] */
/* Tend = 365.0; computed time intervall [ days ] */
/* Tcic =    7.; incidence cumulated over time [ days ] */
/* Ttrm =    5.; mean transmission time [ days ] */
/*............................................................................*/
/* copy operation parameters: */

   ppt->xunits = ( char ) ( opt->n[1] ); /* 0: natural; 1: days */
   ppt->yunits = ( char ) ( opt->n[2] ); /* 0: normalized; 1: conventional */
   ppt->yscale = ( char ) ( opt->n[3] ); /* 0: linear; 1: logarithmic */

   ppt->titles = ( char ) ( opt->n[4] ); /* 0: no titles; 1: titles on graphics */
   
   ppt->nmstop = ( char ) ( opt->n[5] ); /* 0/1: don't/do stop when ... */ 
   ppt->wgtrec = ( char ) ( opt->n[6] ); /* 0/1: don't/do reweight recv. hist */
   ppt->wgtvac = ( char ) ( opt->n[7] ); /* 0/1: don't/do reweight vacc. hist */
   
   ppt->formula = ( char ) ( opt->n[8] ); /* integration formula */
   ppt->rfmmde = ( char ) ( opt->n[9] );  /* reproduction factor modul. mode */
   ppt->bstmde = ( char ) ( opt->n[10] ); /* burst mode [ 0: shift; 1:slats ] */

   ppt->maxout = ( long ) opt->n[11]; /* null < maxout <= 100000 !!! */
   ppt->maxinn = ( long ) opt->n[12]; /* null < maxinn <= 100 !!! */
/*............................................................................*/
/* copy initial values and constants: */

   ppt->Nhrd = ppt->s[1];  /* herd size */
   ppt->Ninf = ppt->s[2];  /* initially infective [ acutely sick ] individuals */
   ppt->Nifc = ppt->s[3];  /* initially infected individuals */

   ppt->Nimn = ppt->s[4];  /* initially immune individuals */
   ppt->Ieff = ppt->s[5];  /* immunization efficay [ ratio: 0<Ieff<=1 ] */
   ppt->Timu = ppt->s[6];  /* immunity half-life [ days ] */
   
   ppt->Nvac = ppt->s[7];  /* initially vaccinated individuals */
   ppt->Vacr = ppt->s[8];  /* vaccination rate [ vaccinations per day ] */
   ppt->Veff = ppt->s[9];  /* vaccination efficacy [ ratio: 0<Veff<=1 ] */
   ppt->Tvac = ppt->s[10]; /* vaccination half-life [ days ] */
   
   ppt->Nlty = ppt->s[11]; /* initially deceased individuals */
   ppt->Ltlt = ppt->s[12]; /* percentage of lethal cases */

   ppt->Repr = ppt->s[13]; /* initial reproduction factor [ basic or effective,
                              depending on ppt->formula, cf. above  ] */
   ppt->Rmda = ppt->s[14]; /* R modulation amplitude [ 0<Rmda; default: 1 ] */
   ppt->Trml = ppt->s[15]; /* R modulation length [ days ] */
   ppt->Trrd = ppt->s[16]; /* R modulation delay [ days ] */

   ppt->Slnt = ppt->s[17]; /* percentage of asymptomatic ['silent'] cases */
   ppt->Ithr = ppt->s[18]; /* incidence threshold [stop below that number...] */
   ppt->Tcic = ppt->s[19]; /* incidence cumulation time [ days ] */

   ppt->Bstf = ppt->s[20]; /* average burst factor */
   ppt->Tbln = ppt->s[21]; /* average burst length [ days ] */
   ppt->Tbps = ppt->s[22]; /* average burst pause [ days ] */

   ppt->Ttrm = ppt->s[23]; /* mean transmission time [ days ] */
   ppt->Tend = ppt->s[24]; /* time interval [ days ] */
   ppt->DltT = ppt->s[25]; /* time increment [ days ] */
/*............................................................................*/
/* normalize parameters: */

   ppt->tcin = ppt->Tcic/ppt->Ttrm; /* tcin: Tcic in natural units */
   ppt->trml = ppt->Trml/ppt->Ttrm; /* trml: Trml in natural units */
   ppt->trrd = ppt->Trrd/ppt->Ttrm; /* trrd: Trrd in natural units */
   ppt->tbln = ppt->Tbln/ppt->Ttrm; /* tbln: Tbln in natural units */
   ppt->tbps = ppt->Tbps/ppt->Ttrm; /* tbps: Tbps in natural units */
   ppt->timn = ppt->Timu/ppt->Ttrm; /* immunity half-life; natural units */
   ppt->timn /= LN2; /* immunity decay time; natural units [ LN2 = log(2) ] */
   ppt->tvcn = ppt->Tvac/ppt->Ttrm; /* vaccination half-life; natural units */
   ppt->tvcn /= LN2; /* vaccination decay time; natural units [ LN2 = log(2) ]*/

   ppt->kend = ( long )( ppt->Tend/ppt->DltT );
   ppt->kcic = ( long )( ppt->Tcic/ppt->DltT );
   ppt->ktrm = ( long )( ppt->Ttrm/ppt->DltT );

   ppt->mxictm = ppt->ktrm;

   if ( ppt->mxictm < ppt->kcic )
      ppt->mxictm = ppt->kcic;

   ppt->repr = ppt->Repr;

   ppt->rifc = ppt->Nifc/ppt->Nhrd;
   ppt->rinf = ppt->Ninf/ppt->Nhrd;
   ppt->rimn = ppt->Nimn/ppt->Nhrd;
   ppt->rvcd = ppt->Nvac/ppt->Nhrd;
   ppt->rlty = ppt->Nlty/ppt->Nhrd;
   ppt->rthr = ppt->Ithr/ppt->Nhrd;
   ppt->vrpc = ppt->Vacr/ppt->Nhrd; /* normalized vaccination rate */
   ppt->vrpc *= ppt->Ttrm;          /* vacc rate in natural nunits [ Ttrm scale ] */
/*............................................................................*/
/* weighting factors: */

   ppt->wght_imm = ( 100.*ppt->Ieff - ppt->Ltlt )/( 100. - ppt->Slnt );
   ppt->wght_ifc = ( 100./( 100. - ppt->Slnt ));
   ppt->wght_lty = ppt->Ltlt/( 100. - ppt->Slnt );
   ppt->wght_vac = ppt->Veff;
/*............................................................................*/
/* fix number of outer iterations: */

   if ( 100 < ppt->maxinn )
      ppt->maxinn = 100;
   else if ( ppt->maxinn < ONE )
      ppt->maxinn = 1;
      
   ppt->maxout = \
   ( long ) fminl(( ppt->kend/ppt->maxinn ), 100000. );
/*............................................................................*/
/* reweight recovery and vaccination history: */

# if AMD_CRRIMN == 1
   if (( ppt->wgtrec == ONE )
     &&( TINY_VALF < ppt->Nimn ))
      state = amdrcs( state );
# endif

# if AMD_CRRVAC == 1
   if (( ppt->wgtvac == ONE )
     &&( TINY_VALF < ppt->Nvac ))
      state = amdevs( state );
# endif
/*............................................................................*/
   hh = ppt->rimn + ppt->rvcd + ppt->rlty;
   scpt0 = 1. - hh;
/*............................................................................*/
   if ( scpt0 < SUSCPT_THR ) 
   {
      PRBLDCLR( "\n" );
      fprintf( stdout, "\n Initial parameters yield 100 percent "\
         "herd immunity\n [ No epidemic propagation ]" );
      PRNORMAL( "\n");

      fprintf( logfle, "\n%s",\
         "Initial_parameters yield 100 percent herd immunity"\
         "\n[ No epidemic propagation ]" );

      fclose( logfle );
      return stp;
   };
/*............................................................................*/
/* initial effective reproduction factor [ reff ] and initial base of         */
/* exponential increase [ in natural time scale: rrpd = reff^( 1./Ttrm ) ]    */

   if ( ppt->formula == null )    /* if Repr is basic reproduction number     */
      ppt->reff = scpt0*ppt->repr;
   else                           /* if Repr is effective reproduction number */
      ppt->reff = ppt->repr;      /* [ depending on ppt->formula; cf. above ] */

   lnrpd= log( ppt->reff );
   rrpd = exp( lnrpd/ppt->Ttrm ); /* = reff^( 1 / Ttrm ) */
/*............................................................................*/
/* store essential parameters in file <parmtr_fle> */

   fleptr_par = fopen( parmtr_fle, "w" ); 
   fprintf( fleptr_par, "PARAMETERS [ overview ]\n" );

   cpylne( outpstr,
      "\nHerd_size", "individuals", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Nhrd, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInitially_infected", "individuals", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Nifc, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInitially_recovered", "individuals", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( ppt->Nimn ), 4, "e" ));
   fprintf( fleptr_par, outpstr );

# if AMD_CRRIMN == 1
   cpylne( outpstr,
      "\nInitially_recovered_immune_(re-weighted)", "individuals", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( ppt->Nhrd*ppt->rimn ), 4, "e" ));
   fprintf( fleptr_par, outpstr );
# endif

   cpylne( outpstr,
      "\nInitially_vaccinated", "individuals", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( ppt->Nvac ), 4, "e" ));
   fprintf( fleptr_par, outpstr );

# if AMD_CRRVAC == 1
   cpylne( outpstr,
      "\nInitially_effectively_vaccinated_(re-weighted)", "individuals", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( ppt->Nhrd*ppt->rvcd ), 4, "e" ));
   fprintf( fleptr_par, outpstr );
# endif

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nMean_transmission_time","days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Ttrm, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nImmunity_half-life","days", 60 );
   strcat( outpstr, ": ");

   if ( ppt->Timu < 1.00e+05 )
      strcat( outpstr, dotos( ppt->Timu, 4, "e" ));
   else
      strcat( outpstr, "Infinite" );

   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nImmunisation_efficacy", "percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->Ieff, 4, "e" ));
   
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

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

   fprintf( fleptr_par, "\n" );

   if ( ppt->formula == null )      /* Repr is basic reproduction number */
   {
      cpylne( outpstr,
         "\nBasic_reproduction_factor","dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Repr, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nEffective_reproduction_factor_[estimate]",
	     "dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( scpt0*ppt->Repr, 4, "e" ));
      fprintf( fleptr_par, outpstr );
   }
   else
   {
      cpylne( outpstr,
         "\nInitial_reproduction_factor", "dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Repr, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      if ( TINY_VALF < scpt0 )
      {
         cpylne( outpstr,
            "\nBasic_reproduction_factor_[estimate]", "dimensionless", 60 );
         strcat( outpstr, ": ");
         strcat( outpstr, dotos( ppt->Repr/scpt0, 4, "e" ));
         fprintf( fleptr_par, outpstr );
      };
   };

   cpylne( outpstr,
      "\nInitial_base_of_exponential_increase", "dimensionless", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( rrpd, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nR_modulation_amplitude", "dimensionless", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Rmda, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nR_modulation_length", "days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Trml, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nR_modulation_delay", "days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Trrd, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nVaccination_rate", "number_of_vaccinations_per_day", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Nvac, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nVaccination_half-life", "days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Tvac, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nVaccination_efficacy", "percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->Veff, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   if ( ZERO < ppt->Bstf )
   {
      fprintf( fleptr_par, "\n" );

      cpylne( outpstr,
         "\nRandom_burst_level", "dimensionless", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Bstf, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nAverage_burst_length", "days", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Tbln, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nAverage_burst_pause", "days", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( ppt->Tbps, 4, "e" ));
      fprintf( fleptr_par, outpstr );
   };

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nTime_limit", "days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->Tend, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nTime_step", "days", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->DltT, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nInternal_time_step", "transmission_cycles", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( ppt->DltT/ppt->Ttrm ), 4, "e" ));
   fprintf( fleptr_par, outpstr );
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

   strcat( flname_rpd, "rpd_" );
   strcat( flname_rpd, longstr );
   strcat( pltfle_rpd, flname_rpd );

   strcat( flname_vac, "vac_" );
   strcat( flname_vac, longstr );
   strcat( pltfle_vac, flname_vac );

   strcat( flname_dcd, "dcd_" );
   strcat( flname_dcd, longstr );
   strcat( pltfle_dcd, flname_dcd );

   pltptr_cic = fopen( pltfle_cic, "w+" );
   pltptr_ifc = fopen( pltfle_ifc, "w+" );
   pltptr_imm = fopen( pltfle_imm, "w+" );
   pltptr_inc = fopen( pltfle_inc, "w+" );
   pltptr_rpd = fopen( pltfle_rpd, "w+" );
   pltptr_vac = fopen( pltfle_vac, "w+" );
   pltptr_dcd = fopen( pltfle_dcd, "w+" );
   
   if ( ppt->xunits == null )
      strcpy ( timestr, "transmission cycles" );
   else
      strcpy ( timestr, "days" );
/*............................................................................*/
   fprintf( pltptr_cic, "# %s", "Epidemic | " );
    
   strcpy( optnstr, lotos(( long ) ppt->Tcic, null, " " ));
   strcat( optnstr, " days incidence " );

   fprintf( pltptr_cic, "%s", optnstr );
   fprintf( pltptr_cic, "%s", "[ x-unit: " );
   fprintf( pltptr_cic, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_cic, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_cic, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_cic, "# %s\n", dline );
/*............................................................................*/
   fprintf( pltptr_ifc, "# %s",\
      "Epidemic | infected individuals [ x-unit: " );
   fprintf( pltptr_ifc, "%s", timestr );

   if (( ppt->yunits == null )
     ||( ppt->yunits == TWO ))
      fprintf( pltptr_ifc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_ifc, "%s", " | y-unit: percent ]\n" );

   fprintf( pltptr_ifc, "# %s\n", dline );
/*............................................................................*/
   fprintf( pltptr_imm, "# %s",\
      "Epidemic | recovered immune individuals [ x-unit: " );
   fprintf( pltptr_imm, "%s", timestr );

   if (( ppt->yunits == null )
     ||( ppt->yunits == TWO ))
      fprintf( pltptr_imm, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_imm, "%s", " | y-unit: percent ]\n" );
      
   fprintf( pltptr_imm, "# %s\n", dline );
/*............................................................................*/
   if ( ppt->xunits == null )
      fprintf( pltptr_inc, "# %s",\
         "Epidemic | incidence [ x-unit: " );
   else
      fprintf( pltptr_inc, "# %s",\
         "Epidemic | daily incidence [ x-unit: " );

   fprintf( pltptr_inc, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_inc, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_inc, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_inc, "# %s\n", dline );
/*............................................................................*/
   fprintf( pltptr_rpd, "# %s",\
      "Epidemic | reproduction number\n"
      "# [ x-unit: " );
   fprintf( pltptr_rpd, "%s", timestr );

   fprintf( pltptr_rpd, "%s", \
      " | y-unit: individuals infected by one sick member ]\n");

   fprintf( pltptr_rpd, "# %s\n", dline );
/*............................................................................*/
   fprintf( pltptr_vac, "# %s",\
      "Epidemic | Effectively vaccinated [ x-unit: " );
   fprintf( pltptr_vac, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2 ))
      fprintf( pltptr_vac, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_vac, "%s", " | y-unit: per 100000 ]\n" );

   fprintf( pltptr_vac, "# %s\n", dline );
/*............................................................................*/
   fprintf( pltptr_dcd, "# %s",\
      "Epidemic | deceased individuals [ x-unit: " );
   fprintf( pltptr_dcd, "%s", timestr );

   if (( ppt->yunits == null )||( ppt->yunits == 2))
      fprintf( pltptr_dcd, "%s", " | y-unit: ]\n" );
   else
      fprintf( pltptr_dcd, "%s", " | y-unit: percent ]\n" );

   fprintf( pltptr_dcd, "# %s\n", dline );
/*............................................................................*/
/* initialize extrem values and averages: */

   ppt->mincic =  1.00e+77;
   ppt->maxcic = -1.00e+77;
   ppt->mininc =  1.00e+77;
   ppt->maxinc = -1.00e+77;
   ppt->minifc =  1.00e+77;
   ppt->maxifc = -1.00e+77;
   ppt->minimn =  1.00e+77;
   ppt->maximn = -1.00e+77;
   ppt->minrpd =  1.00e+77;
   ppt->maxrpd = -1.00e+77;
   ppt->minvac =  1.00e+77;
   ppt->maxvac = -1.00e+77;
   ppt->minlty =  1.00e+77;
   ppt->maxlty = -1.00e+77;

   ppt->mean_imm = ZERO;
   ppt->mean_inc = ZERO;
   ppt->mean_cic = ZERO;
   ppt->mean_vac = ZERO;
/*............................................................................*/
/* initialize updated values: */

   upd->infctd = ppt->rifc;
   upd->incdnc = ppt->rinf;
   upd->immune = ppt->rimn;
   upd->vaccin = ppt->rvcd;
   upd->lethal = ppt->rlty;
   upd->reprod = ppt->reff;

   upd->nxtbst = ppt->tbps; /* next burst start */ 
   upd->stpbst = ppt->tbln; /* next burst stop */

   upd->dhdt[null] = upd->incdnc;
   
   ii = null;
   while( ii < ppt->mxictm )
   {
      ++ii;
      upd->dhdt[ii] = ZERO;
   };

   upd->burst = null;
   upd->incsum = ZERO;
   upd->incidc = upd->incdnc;
   upd->cmlinc = upd->incidc*ppt->Tcic/ppt->Ttrm;
/*...........................................................................*/
/* initialize time step and indices: */

   upd->tt = ZERO;
   upd->dt = ppt->DltT/ppt->Ttrm;   /* time step in natural units */
   upd->kk = null;
   upd->kinn = null;
   upd->kout = null;
   
   while ( upd->kout < ppt->maxout )
   {
/*...........................................................................*/
/* store values */

      if ( ppt->xunits == ONE ) /* [ xunits "days" ] */
         upd->incidc /= ppt->Ttrm;

      STOREVAL( ONE, AMD_INTRPL );
/*...........................................................................*/
/* update extrema in outer loop: set EXTREMA(1)  */

      EXTREMA( ONE );
/*...........................................................................*/
/* start inner loop */

      upd->kinn = null;
      while ( upd->kinn < ppt->maxinn )
      {
/*...........................................................................*/
/* update extrema in inner loop: set EXTREMA(1) */

         EXTREMA( null );
/*...........................................................................*/
         hh = upd->immune + upd->vaccin + upd->lethal;
         upd->suscpt = fmax(( 1. - hh ), SUSCPT_THR );

         if ( ppt->nmstop == ONE ) /* stop if no susceptible individuals remain */
	 {
	    if ( upd->suscpt < ppt->rthr )
            { 
/* susceptible fraction smaller than N = ppt->Tthr herd individuals */

	       upd->dhdt[null] = ZERO;
       	       ppt->timmun = upd->tt;
	       upd->incidc = ZERO;
	       ppt->kend = upd->kk;

               goto finish;
	    };
	 };
/*...........................................................................*/
/* update df/dt */

         if ( ppt->rthr < upd->suscpt )
	 {
            switch ( ppt->formula )
	    {
              default: 
              case 0:

	       upd->reprod = upd->suscpt*ppt->repr;

              break;
/*...........................................................................*/
              case 1:

               upd->suscpt /= scpt0;
	       upd->reprod = upd->suscpt*ppt->repr;
	       
              break;
/*...........................................................................*/
              case 2: /* R(t) = R(0) [ constant ] */

               upd->reprod = ppt->repr;

              break;
            };

            state = amdmdl( state ); 

            lnrpd= log( upd->reprod );
            upd->incdnc *= \
               exp( upd->dt*lnrpd );
         }
	 else /* upd->suscpt <= ppt->rthr */
            upd->incdnc = ZERO;
/*...........................................................................*/
         upd->incidc = upd->incdnc;

	 state = amdrnd( state );
	 
	 ppt->mean_inc += upd->incidc;
/*...........................................................................*/
/* integrate incidence */

         upd->incsum += ( upd->dt*upd->incidc );
/*...........................................................................*/
/* update herd infection, immunity and incidence */

         upd->infctd +=\
            ( upd->dt*ppt->wght_ifc*upd->incidc );

         if ( 1. < upd->infctd )
	    upd->infctd = 1.;

         upd->lethal +=\
            ( upd->dt*ppt->wght_lty*upd->incidc );
/*...........................................................................*/
/* the immune fraction */
	 
         upd->immune *= ( exp( - upd->dt / ppt->timn ));
         upd->immune +=\
            upd->dt*( ppt->wght_imm*upd->incidc );

         if ( 1. < upd->immune )
	    upd->immune = 1.;

	 ppt->mean_imm += upd->immune;
/*...........................................................................*/
/* the effectively vaccinated fraction */
	 
         upd->vaccin *= ( exp( - upd->dt / ppt->tvcn ));
         upd->vaccin +=\
            upd->dt*( ppt->wght_vac*ppt->vrpc );

         if ( 1. < upd->vaccin )
	    upd->vaccin = 1.;

	 ppt->mean_vac += upd->vaccin;
/*...........................................................................*/
/* n days accumulated incidence */

         upd->dhdt[null] = upd->incidc;
	 
         upd->cmlinc = ZERO;
         ii = ppt->kcic;
	 while( null < ii )
         {
            upd->dhdt[ii] = upd->dhdt[ii-ONE];
            upd->cmlinc += upd->dhdt[ii];
	    --ii;
         };
         upd->cmlinc *= upd->dt;

# if AMD_INTRPL == 1

         if ( upd->kk < ppt->kcic )
	    upd->cmlinc = upd->incidc*ppt->Tcic/ppt->Ttrm;
	 else if ( upd->kk < 3.*ppt->kcic )
         {
            uu = ( double )( upd->kk - ppt->kcic )/( 2.*ppt->kcic );
	    vv = 1. - uu;
	    upd->cmlinc = uu*upd->cmlinc + vv*upd->incidc*ppt->Tcic/ppt->Ttrm;
         }; 
# endif
	 ppt->mean_cic += upd->cmlinc;
/*...........................................................................*/
         upd->tt += upd->dt;
         upd->kinn++ ;
	 upd->kk++;
      }; /* while ( upd->kinn < ppt->maxinn ) */

/*.............................end inner loop................................*/
      upd->kout++;

   }; /* while ( upd->kout < ppt->maxout) */

   ppt->mean_imm /= upd->kk;
   ppt->mean_inc /= upd->kk;
   ppt->mean_cic /= upd->kk;
   ppt->mean_vac /= upd->kk;

/*............................end of outer loop ..............................*/
  finish:

   fclose( pltptr_cic );
   fclose( pltptr_ifc );
   fclose( pltptr_inc );
   fclose( pltptr_imm );
   fclose( pltptr_rpd );
   fclose( pltptr_vac );
   fclose( pltptr_dcd );

/*............................................................................*/
/* store maxima: */ 

   fprintf( fleptr_par, "\n" );
      
   cpylne( outpstr,
      "\nTotal_number_of_iterations","number", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, lotos( upd->kk, 9, " " ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nNumber_of_outer_iterations","number", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, lotos( upd->kout, 9, " " ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nNumber_of_inner_iterations","number", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, lotos( ppt->maxinn, 9, " " ));
   fprintf( fleptr_par, outpstr );
/*............................................................................*/
/* store means and maxima: */ 

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nIncidence_maximum_attained_at",
           "transmission_cycle", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( ppt->tmxinc, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   if ( ppt->xunits == null )
   {
      cpylne( outpstr,
         "\nMaximum_incidence", "percent", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( 100.*ppt->maxinc, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nMean_incidence", "percent", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( 100.*ppt->mean_inc, 4, "e" ));
      fprintf( fleptr_par, outpstr );
   }
   else
   {
      cpylne( outpstr,
         "\nMaximum_daily_incidence", "percent", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( 100.*ppt->maxinc/ppt->Ttrm, 4, "e" ));
      fprintf( fleptr_par, outpstr );

      cpylne( outpstr,
         "\nMean_daily_incidence", "percent", 60 );
      strcat( outpstr, ": ");
      strcat( outpstr, dotos( 100.*ppt->mean_inc, 4, "e" ));
      fprintf( fleptr_par, outpstr );
   };

   strcpy( inptstr, "\nMaximum_cumulative_incidence_(");
   strcat( inptstr, dotos( ppt->Tcic, 4, "f" ));
   strcat( inptstr, "_days)");
   cpylne( outpstr, inptstr, "percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->maxcic, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   strcpy( inptstr, "\nMean_cumulative_incidence_(");
   strcat( inptstr, dotos( ppt->Tcic, 4, "f" ));
   strcat( inptstr, "_days)");
   cpylne( outpstr, inptstr, "percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->mean_cic, 4, "e" ));
   fprintf( fleptr_par, outpstr );

   cpylne( outpstr,
      "\nTotal_herd_incidence_(sum_t=0->Tend)", "individuals", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos(( upd->incsum*ppt->Nhrd ), 4, "e" ));
   fprintf( fleptr_par, outpstr );

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nMean_immunity", "percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->mean_imm, 4, "e" ));
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

   fprintf( fleptr_par, "\n" );

   cpylne( outpstr,
      "\nMean_vaccinated", "percent", 60 );
   strcat( outpstr, ": ");
   strcat( outpstr, dotos( 100.*ppt->mean_vac, 4, "e" ));
   
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

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
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

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->minifc - frm, ZERO );
      upbnd = ppt->maxifc + frm;

      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr,
        " ", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Recovered immune" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maximn - ppt->minimn );

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
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

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->mininc - frm, ZERO );
      upbnd = ppt->maxinc + frm;

      GNUPLOT( gnuptr_inc, plot_inc, flname_inc, optnstr, timestr, 
        " ", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Effectively_vaccinated" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxvac - ppt->minvac );

      if ( frm < AMD_GNURNG )
         frm = 0.5;

      lwbnd = fmax( ppt->minvac - frm, ZERO );
      upbnd = ppt->maxvac + frm;

      GNUPLOT( gnuptr_vac, plot_vac, flname_vac, optnstr, timestr,
        " ", lwbnd, upbnd );\

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Deceased" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxlty - ppt->minlty );

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->minlty - frm, ZERO );
      upbnd = ppt->maxlty + frm;

      GNUPLOT( gnuptr_dcd, plot_dcd, flname_dcd, optnstr, timestr,
        " ", lwbnd, upbnd );\
   }
   else /* conventional yunits */
   {
      frm = AMD_FRAME*( ppt->maxcic - ppt->mincic );

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->mincic - frm, ZERO );
      upbnd = ppt->maxcic + frm;

      lwbnd *= 1.0e+05;
      upbnd *= 1.0e+05;

      GNUPLOT( gnuptr_cic, plot_cic, flname_cic, optnstr, timestr,
        "per 100000", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, \
            "Herd infection [ sum of recovered, "
	    "sick, asymptomatic, and lethal cases ]" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxifc - ppt->minifc );

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->minifc - frm, ZERO );
      upbnd = ppt->maxifc + frm;

      lwbnd *= 1.0e+02;
      upbnd *= 1.0e+02;

      GNUPLOT( gnuptr_ifc, plot_ifc, flname_ifc, optnstr, timestr,
        "percent", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Recovered immune" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maximn - ppt->minimn );

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->minimn - frm, ZERO );
      upbnd = ppt->maximn + frm;

      lwbnd *= 1.0e+02;
      upbnd *= 1.0e+02;

      GNUPLOT( gnuptr_imm, plot_imm, flname_imm, optnstr, timestr,
        "percent", lwbnd, upbnd );

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

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->mininc - frm, ZERO );
      upbnd = ppt->maxinc + frm;

      lwbnd *= 1.0e+05;
      upbnd *= 1.0e+05;

      GNUPLOT( gnuptr_inc, plot_inc, flname_inc, optnstr, timestr,
        "per 100000", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Effectively vaccinated" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxvac - ppt->minvac );

      if ( frm < AMD_GNURNG )
         frm = 0.5;

      lwbnd = fmax( ppt->minvac - frm, ZERO );
      upbnd = ppt->maxvac + frm;
      
      lwbnd *= 1.0e+05;
      upbnd *= 1.0e+05;

      GNUPLOT( gnuptr_vac, plot_vac, flname_vac, optnstr, timestr,
        "per 100000", lwbnd, upbnd );

      if ( ppt->titles == ONE )
         strcpy( optnstr, "Deceased" );
      else
         strcpy( optnstr, " " );

      frm = AMD_FRAME*( ppt->maxlty - ppt->minlty );

      if ( frm < AMD_GNURNG )
         frm = 0.5;
      
      lwbnd = fmax( ppt->minlty - frm, ZERO );
      upbnd = ppt->maxlty + frm;

      lwbnd *= ppt->Nhrd;
      upbnd *= ppt->Nhrd;

      GNUPLOT( gnuptr_dcd, plot_dcd, flname_dcd, optnstr, timestr,
        "individuals", lwbnd, upbnd );
   };

   if ( ppt->titles == ONE )
      strcpy( optnstr, "Reproduction number" );
   else
      strcpy( optnstr, " " );

   frm = AMD_FRAME*( ppt->maxrpd - ppt->minrpd );

   if ( frm < AMD_GNURNG )
      frm = 0.5;
     
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
      strncat(( dsp->messge ), " at ", 5 );
      strncat(( dsp->messge ), timeptr, 8 );
      strcat(( dsp->messge ), "\r" );
/*............................................................................*/
/* termination message - display on screen:                                   */

      dsp->option = 't'; /* terminated */
      dsplay( dsp );
   };

   return stp;
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
