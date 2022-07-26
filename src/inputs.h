/* [ file: input.h ] */
# define DO_INPUT "input(*)"
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function input(*)                                                           *
*                                                                              *
*  This functions enters the operation modes and the model parameters.         *
*    In the first instance, the default parameters are entered from            *
*  functions deflt_opr( ) and deflt_par( ). These parameters can then          *
*  be overwritten by any parameters entered from a file                        *
*  [ for example par.init<N>, cf. below ], or modified on the console          *
*  [ this only if the program is started in the console input option ].        *
*    The parameters are subsequently checked and [ if inconsistencies          *
*  are found ] revised by functions rvise_opr( ) and rvise_par( ).             *
*    The final parameters are stored in files opr.log<N> [ operation           *
*  modes ] and par.log<N> [ all parameters ].                                  *
*    The file par.log<N> can be edited [ BUT DON'T CHANGE ITS TOPOLOGY,        *
*  i.e. connected strings must remain connected !!! ]. Then the edited         *
*  file can be used [ if wanted renamed 'par.init<N>' ] as parameter           *
*  input file.                                                                 *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 01, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/

/*============================================================================*/
/* display tool: "more -e", e.g. */
# ifndef AMD_PAGER
   # define AMD_PAGER "more" 
# endif
/* editor command: "vi", "vim", "vile", "ed", "joe", "emacs", e.g. */
# ifndef AMD_EDITOR
   # define AMD_EDITOR "vile"
# endif
/* printer: "lp", e.g. */
# ifndef AMD_PRINTER
   # define AMD_PRINTER "lp"
# endif
/*----------------------------------------------------------------------------*/
/* maximum number of [connected] strings to be read from file */
# ifndef IPT_MAXLBL
   # define IPT_MAXLBL 500
# endif
/* [don't] display default operations: [0] 1 */
# ifndef IPT_OPRDEF
   # define IPT_OPRDEF 0
# endif
/* [don't] display default parameters: [0] 1 */
# ifndef IPT_PARDEF
   # define IPT_PARDEF 0
# endif
/*----------------------------------------------------------------------------*/
/* name of operations log file: */

# ifndef IPT_OPRLOG
   # define IPT_OPRLOG "opr.log"
# endif
/*----------------------------------------------------------------------------*/
/* name of parameter log file: */

# ifndef IPT_PARLOG
   # define IPT_PARLOG "par.log"
# endif
/*----------------------------------------------------------------------------*/
# define IPT_SCRFLS 1 /* 0: use insecure temporary file names [ tmpnam(*) ] */
                      /* 1: use secure temporary file names [ mkstemp(*) ] */
# if defined ( _Ansi )
   # undef IPT_SCRFLS
   # define IPT_SCRFLS 1
# elif defined ( _Unix )
   # undef IPT_SCRFLS
   # define IPT_SCRFLS 1
# elif defined ( _BSD )
   # undef IPT_SCRFLS
   # define IPT_SCRFLS 1
# elif defined ( _Linux )
   # undef IPT_SCRFLS
   # define IPT_SCRFLS 1
# elif defined ( _GNU_Linux )
   # undef IPT_SCRFLS
   # define IPT_SCRFLS 1
# elif defined ( _SuSE )
   # undef IPT_SCRFLS
   # define IPT_SCRFLS 1
# elif defined ( _Wine )
   # undef IPT_SCRFLS
   # define IPT_SCRFLS 1 
# endif
/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
   static char *term;        /* terminal type string */ 
# endif
/*----------------------------------------------------------------------------*/
# include "../src/STOREPAR.M"
/*----------------------------------------------------------------------------*/
# include "../default/deflt_opr.h"
# include "../default/deflt_par.h"
/*----------------------------------------------------------------------------*/
# include "init_opr.h"
# include "rvise_opr.h"
# include "rread_opr.h"
# include "store_opr.h"

# include "init_par.h"
# include "rvise_par.h"
# include "rread_par.h"
# include "store_par.h"
/*============================================================================*/

short input ( char *option )
{
/* declarations: */

   static AMDSTATE
     *state = &amdstat;

   static OPERTNS 
     *opr = &opertns;

   static PARMTRS 
     *par = &parmtrs;

   static TXCNSL
     *csp= &cns;

   static short
      ii = null,
      ind = null,
      prmtrs = null;

   static char 
      ptr[2*STS_SIZE] = {null},
      fleptr[STS_SIZE] = {null},
      timeptr[STS_SIZE] = {null};

   const char
     *oprlog = IPT_OPRLOG,
     *parlog = IPT_PARLOG,
     *timefrm = " created: %.24s  ";

   time_t
      nseconds = null,
     *timer = null;

# ifndef AMD_PAGER
   static AMDPAR *amd = NULL;
# endif

/* prototypes: */

   time_t
      time( time_t *timer );

   char
      *ctime( const time_t *timer );

# if IPT_SCRFLS == 1
   int mkstemp( char *s );
# else
   char *tmpnam( char *s );
# endif

   void
      init_opr( void );

   void
      deflt_opr( void );

   short 
      rvise_opr( void );

   short 
      rread_opr( char *filename, char mode );

   short 
      store_par( char *filename, char mode );

   void
      init_par( void );

   void
      deflt_par( void );

   short 
      rvise_par( void );

   short 
      rread_par( char *filename, char mode );

   short 
      store_par( char *filename, char mode );

   TXCNSL 
     *txcnsl( TXCNSL *csp );

   char
     *lotos( long mm, char cc, char *format );
/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
/* get the terminal info: */

   term = ( char *) getenv( "TERM" ); /* get the terminal */

   ind = tgetent( null, term );

   if( ONE != ind )
   {
      fprintf( stderr, "Error on getting the termcap info\n" ); 
      exit( EXIT_FAILURE );
   };
# endif
/*............................................................................*/
   state = &amdstat;
   opr = &opertns;
   par = &parmtrs;
   csp = &cns;
   
   csp = txcnsl( null ); /* clear text console */
/*............................................................................*/
/* set buffer length = null: */

   ind = setvbuf( stdin, null, _IONBF, null );
   ind = setvbuf( stdout, null, _IONBF, null ); 
/*...........................................................................*/
/* memory allocations; initializations [ explicit ]: */

   ii = null; do
   {
      ptr[ii] = null;
      fleptr[ii] = null;
      timeptr[ii] = null;
      ++ii;
   } while( ii < STS_SIZE );
   do
   {
      ptr[ii] = null;
      ++ii;
   } while( ii < ( 2*STS_SIZE ));
/*...........................................................................*/
/* option "operations": */

   if ( *option == 'o' )
   {
/*................................*/
      ind = rvise_opr( );         /* revise/reconfigure stored opr parameters */
/*..............................*/

      if ( ind == null )
      {
         if ( OPERATIONS < opr->n[null] )
         {
            fprintf( stdout, "\n\n Message from function %s :", DO_INPUT );
            fprintf( stdout, "\n\n Too many operation parameters !!!" );
            fprintf( stdout, "\n [ Number %10ld exceeds maximum %d = "
	       "macro OPERATIONS", opr->n[null], OPERATIONS );
            fprintf( stdout, "\n   in file 'CONFIG.H'. ]" );
            fprintf( stdout, "\n   - Change macro in compliance with memory "
               "resources.\n" );

            exit( EXIT_FAILURE );
         };
      };
/*............................................................................*/
/* store the currently charged operation parameters on temporary file: */

# if defined IPT_OPRTMP 
      strcpy( tmpfle, IPT_OPRTMP );
# else
/*............................................................................*/
/* assign a temporary file name: */

   # if IPT_SCRFLS == 1
      mkstemp( tmpfle ); /* [ secure ] */
   # else
      tmpnam( tmpfle ); /* [ insecure ] */
   # endif                                                        
/*............................................................................*/
# endif
/*............................................................................*/

/*..........................................*/
      store_opr( tmpfle, 't' );             /* store ops on temporary file   */
/*.......................................,*/

/*............................................................................*/
# if IPT_OPRDEF == 1
      strcpy( ptr, AMD_PAGER );
      strcat( ptr, " " );
      strcat( ptr, tmpfle );
/*.....................................*/
      system( ptr );                   /* edit operation parameters           */
      rread_opr( tmpfle, 't' );       /*                                      */
      rvise_opr( );                  /*                                       */
      store_opr( tmpfle, 't' );     /* restore revised parameters in tmp file */
/*................................*/
# endif
/*............................................................................*/
      csp = txcnsl( null ); /* clear text console */
      csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
      csp->dfopt = 3;

   opr_menu:

      csp->items = 7;
      csp->dflnf = csp->dfopt; /* set line feed before defaut line */

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      strcpy( csp->title, "Program AMADEUS: " );
      strncat( csp->title, timeptr, 24 );

      strcpy( csp->envmt, "INPUT" );
      strcpy( csp->cmmnt, "Select [ enter number ]" );
      strcpy( csp->tasks, "OPERATIONS" );

      strcpy( csp->mline[1], "* Display presently defined operation modes" );
      strcpy( csp->mline[2], "* Enter new operation modes from file" );
      strcpy( csp->mline[3], "* Edit [ and evtly. modify ] operation modes" );
      strcpy( csp->mline[4], "* Reload default operation modes" );
      strcpy( csp->mline[5], "* Print operation modes" );
      strcpy( csp->mline[6], "* Start computation" );
      strcpy( csp->mline[7], "* Continue" );

      strcpy( csp->escpe, "End of program / escape" );

      if ( state->job == null )
         strcpy( csp->cnfrm, "Nothing done! Do you really want to quit ?" );
      else
         strcpy( csp->cnfrm, "Do you really want to quit ?" );

/*...........................*/
      csp = txcnsl( csp );   /* menu building function */
/*.........................*/

      switch(csp->option )
      {
/* end of program / escape: */

        case 0: case 'y': case 'Y': case 'j': case 'J':

         PRBLDCLR( "" );
         PRNORMAL( "" );

         remove( tmpfle );
         return -ONE;
        break;
/*............................................................................*/
        case 1:  /* display the actual configuration [ on screen ] */

/*............................................................................*/
# if defined ( AMD_PAGER )
         strcpy( ptr, AMD_PAGER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );

/*.....................................*/
         system( ptr );                /* edit [evtlly modify] divisions file */
/*...................................*/

# else
         fprintf( stdout, "\n\n %s", state->name );
         fprintf( stdout, "\n %s", state->text );
         fprintf( stdout, "\n\n %-d  %s\n", opr->n[null], opr->ntx[null] );

	 ii = null;
	 while( ii < opr->n[null] )
	 {
	    ++ii;
            fprintf( stdout, "\n %-s:   %d", opr->ntx[ii], opr->n[ii] );
         };
# endif
/*............................................................................*/
         csp->option = 7;
         csp->clscr = 0; /* 0 / N: clear screen / scroll N lines */
	 
         goto opr_menu;
        break;
/*............................................................................*/
        case 2: /* enter another configuration from file */

         fprintf( stdout, "\n Please enter filename [ Continue/"
            "Escape: null ] >----> " );
         scanf( "%s", ptr );

         if( *ptr == '0' )
         { 
            remove( tmpfle );

            PRBLDCLR( "" );
            fprintf( stdout, "\r%*s", 79, "INPUT" );
            PRNORMAL( "" );
            fprintf( stdout, "\n %s",\
	       "======================================="
               "=======================================" );
            return -ONE;
         };
/*......................................*/
         rread_opr( ptr, 'f' );         /* enter the new configuration file   */
         rvise_opr( );                 /*  revise/reconfigure ...             */
         store_opr( tmpfle, 't' );    /*   store on temporary file            */
/*..................................*/
         csp->dfopt = 7; 
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */

         goto opr_menu;
        break;
/*............................................................................*/
        case 3:  /* edit and/or modify the actual configuration */

/*............................................................................*/
# if defined ( AMD_EDITOR )
	 strcpy( ptr, AMD_EDITOR );
	 strcat( ptr, " " );
	 strcat( ptr, tmpfle );
/*.......................................*/
	 system( ptr );                  /* edit operation parameters in tmp file  */
	 rread_opr( tmpfle, 't' );      /*  re-read temporary operations from file */
	 rvise_opr( );                 /*   revise/reconfigure ...                 */
	 store_opr( tmpfle, 't' );    /*    restore on tmp file                    */
/*..................................*/
# else
	 fprintf( stdout, "\n No editor defined to perform this option !" );
# endif
/*............................................................................*/
         csp->dfopt = 7; 
	 csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */

         goto opr_menu;
        break;
/*............................................................................*/
        case 4:  /* reload the default configuration */

/*......................................*/
         deflt_opr( );                  /* enter default divions              */
         rvise_opr( );                 /*  revise/reconfigure ...             */
         store_opr( tmpfle, 't' );    /*   store on temporary file            */
/*..................................*/
         csp->dfopt = 7; 
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
	 
         goto opr_menu;
        break;
/*............................................................................*/
        case 5:

/*............................................................................*/
# if defined ( AMD_PRINTER )

         strcpy( ptr, AMD_PRINTER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
/*.....................................*/
         system( ptr );                /* print temporary operations file */
/*...................................*/
# else
         fprintf( stdout,
	    "\n No printer defined in file 'CONFIG.H' !" );
# endif
/*............................................................................*/
         csp->dfopt = 7;
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */

         goto opr_menu;
        break;
/*............................................................................*/
        case 6:  /* start computation */

         remove( tmpfle );

         PRBLDCLR( "" );
         PRNORMAL( "" );

        return ONE;
        break;
/*............................................................................*/
	case 7:

         PRBLDCLR( "" );
         fprintf( stdout, "\r%*s", 79, "INPUT" );
         PRNORMAL( "" );

         csp->dfopt = 5; 
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
	 
        break;
      }; /* end switch(*) */
/*............................................................................*/
      remove( tmpfle );

      strcpy( fleptr, oprlog );
      strcat( fleptr, lotos( state->job, null, "" ));

      fprintf( stdout, "\n opened: Operation logfile %s ", fleptr );

/*..................................*/
      store_opr( fleptr, 'o' );     /* save final configuration on log file */
/*................................*/

      fprintf( stdout, CLEAR_LINE );

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      fprintf( stdout, "\r Operation logfile %s ", fleptr );
      fprintf( stdout, timefrm, timeptr );
      fprintf( stdout, CLEAR_LINE );

   } /* end if *option == 'o'[perations] */
/*............................................................................*/
   else if ( *option == 'p' )
/*............................................................................*/
/* option "parameters": */
   { 
      prmtrs = ( short ) par->s[null];
/*................................*/
      ind = rvise_par( );         /*                                          */
/*..............................*/

      if ( ind == null )
      {
         if ( PARAMETERS < prmtrs )
         {
            fprintf( stdout, "\n\n Message from function %s :", DO_INPUT );
            fprintf( stdout, "\n\n Too many parameters !!!" );
            fprintf( stdout, "\n [ Number %d exceeds maximum %d ",
               prmtrs, PARAMETERS );
            fprintf( stdout, "\n   in file 'CONFIG.H'. ]" );
            fprintf( stdout, "\n   - Change macro in compliance with memory "
               "resources.\n" );

            exit( EXIT_FAILURE );
         };
      };
/*............................................................................*/
/* store the currently charged parameters on temporary file: */

# if defined IPT_PARTMP
      strcpy( tmpfle, IPT_PARTMP );
# else
/*............................................................................*/
/* assign a temporary file name: */

   # if IPT_SCRFLS == 1
      mkstemp( tmpfle ); /* [ secure ] */
   # else
      tmpnam( tmpfle ); /* [ insecure ] */
   # endif                                                        
/*............................................................................*/
# endif
/*............................................................................*/

/*..........................................*/
      store_par( tmpfle, 't' );             /* store params on temporary file */
/*........................................*/

# if IPT_PARDEF == 1
      strcpy( ptr, AMD_PAGER );
      strcat( ptr, " " );
      strcat( ptr, tmpfle );
/*.....................................*/
      system( ptr );                   /* edit parameter file                 */
      rread_par( tmpfle, 't' );       /*  re-read parameters from tmp file    */
      rvise_par( );                  /*   revise/reconfigure ...              */
      store_par( tmpfle, 't' );     /*    restore revised parmtr in tmp file  */
/*................................*/
# endif
/*............................................................................*/
      csp = txcnsl( null ); /* clear text console */
      csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
      csp->dfopt = 4;

   par_menu:

      csp->items = 7;
      csp->dflnf = csp->dfopt; /* set line feed before that option line */

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      strcpy( csp->title, "Program AMADEUS: " );
      strncat( csp->title, timeptr, 24 );

      strcpy( csp->envmt, "INPUT" );
      strcpy( csp->cmmnt, "Select [ enter number ]" );
      strcpy( csp->tasks, "PARAMETERS" );

      strcpy( csp->mline[1], "* Return to previous menu" );
      strcpy( csp->mline[2], "* Display the presently charged parameters" );
      strcpy( csp->mline[3], "* Enter new parameters from file" );
      strcpy( csp->mline[4], "* Edit [ and evtly. modify ] the parameters" );
      strcpy( csp->mline[5], "* Reload the default parameters" );
      strcpy( csp->mline[6], "* Print the parameters" );
      strcpy( csp->mline[7], "* Start computation" );

      strcpy( csp->escpe, "End of program / escape" );

      if ( state->job == null )
         strcpy( csp->cnfrm, "Nothing done! Do you really want to quit ?" );
      else
         strcpy( csp->cnfrm, "Do you really want to quit ?" );

/*...........................*/
      csp = txcnsl( csp );   /* menu building function */
/*.........................*/

      switch(csp->option )
      {
/*............................................................................*/
        case 0: case 'y': case 'Y': case 'j': case 'J':

/* end of program / escape */

         remove( tmpfle ); 

         PRBLDCLR( "" );
         PRNORMAL( "" );

         return -ONE;
        break;
/*............................................................................*/
        case 1:  /* return to previous menu [ opr_menu ] */

         remove( tmpfle );
         goto opr_menu;
	break; 
/*............................................................................*/
        case 2:  /* display the actual configuration [ on screen ] */

/*............................................................................*/
# if defined ( AMD_PAGER )

         strcpy( ptr, AMD_PAGER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
	 
/*.....................................*/
         system( ptr );                /* edit [ evtlly modify ] params file */
/*...................................*/
# else
         prmtrs = ( short ) par->s[null];
	 
         fprintf( stdout, "\n\n %s", ( state->name ));
         fprintf( stdout, "\n %s", ( state->text ));
         fprintf( stdout, "\n\n %-3d %s\n", 
	    prmtrs, par->stx[null] );

	 ii = null;
	 while( ii < prmtrs )
	 {
	    ++ii;
            fprintf( stdout, "\n %-s:  % .12e ", par->stx[ii], par->s[ii] );
         };
# endif
/*............................................................................*/
         csp->clscr = 0; /* 0 / N: clear screen / scroll N lines */
         csp->dfopt = 7;

         goto par_menu;
        break;
/*............................................................................*/
        case 3: /* enter another configuration from file */

         fprintf( stdout, "\n Please enter filename [ Continue/"
            "Escape: null ] >----> " );
         scanf( "%s", ptr );

         if( *ptr == '0' )
         { 
            remove( tmpfle ); 

            PRBLDCLR( "" );
            fprintf( stdout, "\r%*s", 79, "INPUT" );
            PRNORMAL( "" );
            fprintf( stdout, "\n %s",\
	       "======================================="
               "=======================================" );
            return -ONE; 
         };
/*.......................................*/
         rread_par( ptr, 'f' );          /* read new parameters from file     */
         rvise_par( );                  /*  revise/reconfigure ...            */
         store_par( tmpfle, 't' );     /*   store parameters on temporary fle */
/*...................................*/
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
         csp->dfopt = 7;

         goto par_menu;
        break;
/*............................................................................*/
        case 4:  /* edit and/or modify the actual configuration */

/*............................................................................*/
# if defined ( AMD_EDITOR )
         strcpy( ptr, AMD_EDITOR );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
/*.......................................*/
         system( ptr );                  /* edit parameters in temporarry file */
         rread_par( tmpfle, 't' );      /*  re-read parameters from tmp file   */
         rvise_par( );                 /*   revise/reconfigure ...             */
         store_par( tmpfle, 't' );    /*    restore on temporary file          */
/*..................................*/
# else
	 fprintf( stdout, "\n No editor defined in file 'CONFIG.H' !" );
# endif
/*............................................................................*/
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
         csp->dfopt = 7;

         goto par_menu;
        break;
/*............................................................................*/
        case 5:  /* reload the default configuration */

/*......................................*/
         deflt_par( );                  /* enter default parameters           */
         rvise_par( );                 /*  revise/reconfigure parameters      */
         store_par( tmpfle, 't' );    /*   store on temporary file            */
/*..................................*/
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
         csp->dfopt = 7;

         goto par_menu;
        break;
/*............................................................................*/
        case 6:

/*............................................................................*/
# if defined ( AMD_PRINTER )

         strcpy( ptr, AMD_PRINTER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );

/*.....................................*/
         system( ptr );                /* print file */
/*...................................*/
# else
         fprintf( stdout, "\n No printer defined for this option !" );
# endif
/*............................................................................*/
         csp->clscr = 1; /* 0 / N: clear screen / scroll N lines */
         csp->dfopt = 7;

         goto par_menu;
        break;
/*............................................................................*/
        default: case 7:  /* start computation */

         remove( tmpfle );

         PRBLDCLR( "" );
         PRNORMAL( "" );

         return ONE;
        break;
      }; /* end switch(*) */
/*............................................................................*/
      remove( tmpfle ); 

      strcpy( fleptr, parlog  );
      strcat( fleptr, lotos( state->job, null, " " ));

      fprintf( stdout, "\n opened: Parameters logfile %s ", fleptr );

/*..................................*/
      store_par( fleptr, 'p' );     /* store final parameters in log file     */
/*................................*/

      fprintf( stdout, CLEAR_LINE );

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      fprintf( stdout, "\r Parameters logfile %s ", fleptr );
      fprintf( stdout, timefrm, timeptr );
   }; 
   return null;
}
# undef IPT_OPRDEF
# undef IPT_PARDEF
/*============================================================================*/
/***************** end of parameter input function input(*) *******************/
