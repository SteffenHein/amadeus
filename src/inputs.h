/* [ file: input.h ] */
# define DO_INPUT "input(*)"
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A simple numerical Model Approximating the Development of Epidemics         *
*  Under varied conditions if Spread                                           *
*                                                                              *
*  Function input(*)                                                           *
*                                                                              *
*  This functions enters the operation modes and the model parameters.         *
*    In the first instance, the default parameters are entered from            *
*  functions deflt_operts( ) and deflt_params( ). These parameters can         *
*  then be overwritten by any parameters entered from a file                   *
*  [ for example par.init<N>, cf. below ], or modified on the console          *
*  [ this only if the program is started in the console input option ].        *
*    The parameters are subsequently checked and [ if inconsistencies          *
*  are found ] revised by functions rvise_operts( ) and rvise_params( ).       *
*    The final parameters are stored in files opr.log<N> [ operation           *
*  modes ] and par.log<N> [ all parameters ].                                  *
*    The file par.log<N> can be edited [ BUT DON'T CHANGE ITS TOPOLOGY,        *
*  i.e. connected strings must remain connected !!! ]. Then the edited         *
*  file can be used [ if wanted renamed 'par.init<N>' ] as parameter           *
*  input file.                                                                 *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: December 19, 2021 ]                            <contact@sfenx.de> *
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
/* 'my_terminal' configuration: */

   # include <termcap.h>     /* terminal type header */
   static char *term;        /* terminal type string */ 

# ifndef CLSCREEN
   # define CLSCREEN { \
     fprintf( stdout, "%s", tgetstr( "cl", null )); \
   }
# endif
# ifndef PRBLDCLR
   # define PRBLDCLR(a) {\
     fprintf( stdout, \
        "%s%s", tgetstr( "md", null ), (a)); /* bold clear output */ \
   }
# endif
# ifndef PRINVERS
   # define PRINVERS(a) {\
     fprintf( stdout, \
        "%s%s", tgetstr( "mr", null ), (a)); /* inverse */ \
   }
# endif
# ifndef PRNORMAL
   # define PRNORMAL(a) {\
     fprintf( stdout, \
        "%s%s", tgetstr( "me", null ), (a)); /* back to normal output */ \
   }
# endif
# else /* if USE_NCURSES != 1 */
# ifndef CLSCREEN
   # define CLSCREEN { \
     fprintf( stdout, "\f" ); \
   }
# endif
# ifndef PRBLDCLR
   # define PRBLDCLR(a) {\
     fprintf( stdout, "%s", (a));\
   }
# endif
# ifndef PRINVERS
   # define PRINVERS(a) {\
     fprintf( stdout, "%s", (a));\
   }
# endif
# ifndef PRNORMAL
   # define PRNORMAL(a) {\
     fprintf( stdout, "%s", (a));\
   }
# endif
# endif /* USE_NCURSES != 1 */
/*----------------------------------------------------------------------------*/
# if IPT_SCRFLS == 1
   # include <unistd.h>
# endif
/*----------------------------------------------------------------------------*/
# include "../tools/cpypar.h"
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

   static PARMTRS
     *par = &parmtrs;

   static TXCNSL
     *csp = &console;

   static short
      ii = null,
      ind = null,
      item = null,
      parameters = null;

   static char 
      ptr[2*STS_SIZE] = {null},
      fleptr[STS_SIZE] = {null},
      timeptr[STS_SIZE] = {null};

   const char
      items1 = SIX,
      items2 = SIX,
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
      init_params( void );

   void
      deflt_params( void );

   short 
      rvise_params( void );

   short 
      rread_params( char *filename, char mode );

   short 
      store_params( char *filename, char mode );

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
/* set buffer length = null: */

   ind = setvbuf( stdin, null, _IONBF, null );
   ind = setvbuf( stdout, null, _IONBF, null ); 
/*...........................................................................*/
/* memory allocations; initializations [explicit]: */

   ii = null; do
   {
      ptr[ii] = null;
      fleptr[ii] = null;
      timeptr[ii] = null;
   } while(( ++ii ) < STS_SIZE );
   do
   {
      ptr[ii] = null;
   } while(( ++ii ) < ( 2*STS_SIZE ));
/*...........................................................................*/
/* option "operations": */

   if ( *option == 'o' )
   {
   /* operations = ( short ) opr->n[null]; */
/*............................................................................*/
      ind = rvise_operts( );      /* revise/reconfigure default operations    */
/*..............................*/

      if ( ind == null )
      {
         if ( OPERATIONS < opr->n[null] )
         {
            printf( "\n\n Message from function %s :", DO_INPUT );
            printf( "\n\n Too many operation parameters !!!" );
            printf( "\n [ Number %10ld exceeds maximum %d = macro OPERATIONS",
               opr->n[null], OPERATIONS );
            printf( "\n   in file 'model.h'. ]" );
            printf( "\n   - Change macro in compliance with memory "
               "resources.\n" );

            exit( EXIT_FAILURE );
         };
      };
/*............................................................................*/
/* store the actually charged operations: */
# if defined ( IPT_OPRTMP )
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
      store_operts( tmpfle, 't' );          /* store divs on temporary file   */
/*.......................................,*/
# if IPT_OPRDEF == 1
      strcpy( ptr, AMD_PAGER );
      strcat( ptr, " " );
      strcat( ptr, tmpfle );
/*............................................................................*/
      system ( ptr );                  /* edit [evtlly modify] operations     */
      rread_operts( tmpfle, 't' );    /*                                      */
      rvise_operts( );             i /*                                       */
      store_operts( tmpfle, 't' );  /*  restore revised operatns on tmp file  */
/*................................*/
# endif
/*............................................................................*/
      csp = txcnsl( null ); /* initialize menu */

      item = items1;
      ( csp->clscr ) = 1; /* if !=0: clear screen; scroll that number of lines*/

   opr_menu:

      ( csp->items ) = items1;
      ( csp->dfopt ) = item;
      ( csp->dflnf ) = item; /* set line feed before that option line */

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      strcpy(( csp->title ), "Program AMADEUS: " );
      strncat(( csp->title ), timeptr, 24 );

      strcpy(( csp->envmt ), "INPUT" );
      strcpy(( csp->cmmnt ), "Select [ enter number ]" );
      strcpy(( csp->tasks ), "OPERATIONS" );
      strcpy(( csp->mline[1] ), "* Display presently defined operation modes" );
      strcpy(( csp->mline[2] ), "* Enter new operation modes from file" );
      strcpy(( csp->mline[3] ), "* Edit [ and evtly. modify ] operation modes" );
      strcpy(( csp->mline[4] ), "* Reload default operation modes" );
      strcpy(( csp->mline[5] ), "* Print operation modes" );
      strcpy(( csp->mline[6] ), "* Continue" );
      strcpy(( csp->escpe ), "End of program / escape" );
/*............................................................................*/
      csp = txcnsl( csp );   /* call the menu building function               */
/*.........................*/

      item = ( csp->option );

/*............................................................................*/
      switch ( item )
      {
        default: /* continue program [ e.g. item = items1 ] */
         break;

        case 1:  /* display the actual configuration [ on screen ] */

# if defined ( AMD_PAGER )
         strcpy( ptr, AMD_PAGER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
/*............................................................................*/
         system ( ptr );               /* edit [evtlly modify] divisions file */
/*...................................*/
# else
         printf( "\n\n %s", ( state->name ));
         printf( "\n %s", ( state->text ));

         printf( "\n\n %-d  %s\n", opr->n[null], opr->ntx[null] );

         for ( ii=ONE; ii<=opr->n[null]; ii++ )
            printf( "\n %-s:   %d", opr->ntx[ii], opr->n[ii] );
# endif
         item = items1;
         ( csp->clscr ) = 0; /* != 0: clear screen; scroll that num of lines */
	 
        goto opr_menu;
        break;

        case 2: /* enter another configuration from file */

         printf( "\n Please enter filename [ Continue/"
            "Escape: null ] >----> " );
         scanf( "%s", ptr );

         if( *ptr == '0' )
         { 
            remove( tmpfle );

            PRBLDCLR( "" );
            printf( "\r%*s", 79, "INPUT" );
            PRNORMAL( "" );
            printf( "\n ======================================="
                       "=======================================" );
            return -ONE;
         };
/*............................................................................*/
         rread_operts( ptr, 'f' );      /* enter the new configuration file   */
         rvise_operts( );              /*  revise/reconfigure ...             */
         store_operts( tmpfle, 't' ); /*   restore on tmp file                */
/*..................................*/
         item = items1;
         ( csp->clscr ) = 1; /* N != 0: clear screen; scroll that nbr of lines*/

        goto opr_menu;
        break;

        case 3:  /* edit and/or modify the actual configuration */
/*............................................................................*/
# if defined ( AMD_EDITOR )
         strcpy( ptr, AMD_EDITOR );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
/*............................................................................*/
         system ( ptr );                 /* edit [evtlly modify] tmp opr file */
         rread_operts( tmpfle, 't' );   /*  re-read temporary operations file */
         rvise_operts( );              /*   revise/reconfigure ...            */
         store_operts( tmpfle, 't' ); /*    restore on tmp file               */
/*..................................*/
# else
         printf( "\n No editor is defined for this option !" );
# endif
/*............................................................................*/
         item = items1;
         ( csp->clscr ) = 1; /* N != 0: clear screen; scroll that nbr of lines*/

        goto opr_menu;
        break;

        case 4:  /* reload the default configuration */

/*............................................................................*/
         deflt_operts( );               /* enter default divions              */
         rvise_operts( );              /*  revise/reconfigure ...             */
         store_operts( tmpfle, 't' ); /*   store on tmp file                  */
/*..................................*/
         item = items1;
         ( csp->clscr ) = 1; /* N != 0: clear screen; scroll that nbr of lines*/
	 
        goto opr_menu;
        break;

        case 5:

# if defined ( AMD_PRINTER )
         strcpy( ptr, AMD_PRINTER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
/*............................................................................*/
         system ( ptr );               /* print temporary operations file */
/*...................................*/
# else
         printf( "\n No printer is defined for this option !" );
# endif
         item = items1;
         ( csp->clscr ) = 1; /* N != 0: clear screen; scroll that nbr of lines*/

        goto opr_menu;
        break;

        case 0:  /* end of program / escape */

         remove( tmpfle );

         PRBLDCLR( "" );
         printf( "\r%*s", 79, "INPUT" );
         PRNORMAL( "" );
         return -ONE;
        break;
      }; /* end switch(*) */
/*............................................................................*/
      remove( tmpfle );

      strcpy( fleptr, oprlog );
      strcat( fleptr, lotos(( state->job ), null, " " ));

      printf( "\n opened: Operation logfile %s ", fleptr );
/*............................................................................*/
      store_operts( fleptr, 'o' );  /* save final configuration on log file   */
/*................................*/

      printf( CLEAR_LINE );

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      printf( "\r Operation logfile %s ", fleptr );
      printf( timefrm, timeptr );
      printf( CLEAR_LINE );

   } /* end if *option == 'o'[perations] */
   else if ( *option == 'p' )
/*............................................................................*/
/* option "parameters": */
   { 
      parameters = ( short ) par->s[null];
/*............................................................................*/
      ind = rvise_params( );      /*                                          */
/*..............................*/

      if ( ind == null )
      {
         if ( PARAMETERS < parameters )
         {
            printf( "\n\n Message from function %s :", DO_INPUT );
            printf( "\n\n Too many parameters !!!" );
            printf( "\n [ Number %d exceeds maximum %d ",
               parameters, PARAMETERS );
            printf( "\n   in file 'model.h'. ]" );
            printf( "\n   - Change macro in compliance with memory "
               "resources.\n" );

            exit( EXIT_FAILURE );
         };
      };
/*............................................................................*/
/* store the actually charged parameters: */
# if defined ( IPT_PARTMP )
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
      store_params( tmpfle, 't' );          /* store prmtrs on temporary file */
/*........................................*/

# if IPT_PARDEF == 1
      strcpy( ptr, AMD_PAGER );
      strcat( ptr, " " );
      strcat( ptr, tmpfle );
/*............................................................................*/
      system ( ptr );                  /* edit [evtlly modify] parameter file */
      rread_params( tmpfle, 't' );    /*  re-read parameters from tmp file    */
      rvise_params( );               /*   revise/reconfigure ...              */
      store_params( tmpfle, 't' );  /*  restore revised paramtrs on tmp file  */
/*................................*/
# endif
/*............................................................................*/
      csp = txcnsl( null ); /* initialize menu */
      
      item = items2;
      ( csp->clscr ) = 1; /* if !=0: clear screen; scroll that number of lines*/

   par_menu:

      ( csp->items ) = items2;
      ( csp->dfopt ) = item;
      ( csp->dflnf ) = item; /* set line feed before that option line */

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      strcpy(( csp->title ), "Program AMADEUS: " );
      strncat(( csp->title ), timeptr, 24 );

      strcpy(( csp->envmt ), "INPUT" );
      strcpy(( csp->cmmnt ), "Select [ enter number ]" );
      strcpy(( csp->tasks ), "PARAMETERS" );
      strcpy(( csp->mline[1] ), "* Display the presently charged parameters" );
      strcpy(( csp->mline[2] ), "* Enter new parameters from file" );
      strcpy(( csp->mline[3] ), "* Edit [ and evtly. modify ] the parameters" );
      strcpy(( csp->mline[4] ), "* Reload the default parameters" );
      strcpy(( csp->mline[5] ), "* Print the parameters" );
      strcpy(( csp->mline[6] ), "* Continue" );
      strcpy(( csp->escpe ), "End of program / escape" );
/*............................................................................*/
      csp = txcnsl( csp );   /* call the menu building function               */
/*.........................*/

      item = ( csp->option );

/*............................................................................*/
      
      switch ( item )
      {
        default: /* continue program [ e.g item = items2 ] */
        break;

        case 1:  /* display the actual configuration [ on screen ] */

# if defined ( AMD_PAGER )
         strcpy( ptr, AMD_PAGER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
/*............................................................................*/
         system ( ptr );               /* edit [evtlly modify] divisions file */
/*...................................*/
# else
         parameters = ( short ) par->s[null];

         printf( "\n\n %s", ( state->name ));
         printf( "\n %s", ( state->text ));
         printf( "\n\n %-3d %s\n", ( short ) par->s[null], par->stx[null] );

         for ( ii=ONE; ii<=parameters; ii++ )
            printf( "\n %-s:  % .12e ", par->stx[ii], par->s[ii] );
# endif
         item = items2;
         ( csp->clscr ) = 0; /* N !=0 : clear screen; scroll that nbr of lines*/

        goto par_menu;
        break;

        case 2: /* enter another configuration from file */

         printf( "\n Please enter filename [ Continue/"
         "Escape: null ] >----> " );
         scanf( "%s", ptr );

         if( *ptr == '0' )
         { 
            remove( tmpfle );

            PRBLDCLR( "" );
            printf( "\r%*s", 79, "INPUT" );
            PRNORMAL( "" );
            printf( "\n ==================================="
               "===========================================" );
            return -ONE; 
         };
/*............................................................................*/
         rread_params( ptr, 'f' );       /* read new parameters from file     */
         rvise_params( );               /*  revise/reconfigure ...            */
         store_params( tmpfle, 't' );  /*   restore parameters on tmp file    */
/*...................................*/
         item = items2;
         ( csp->clscr ) = 1; /* N !=0 : clear screen; scroll that nbr of lines*/

        goto par_menu;
        break;

        case 3:  /* edit and/or modify the actual configuration */

# if defined ( AMD_EDITOR )
         strcpy( ptr, AMD_EDITOR );
         strcat( ptr, " " );
         strncat( ptr, tmpfle, STS_SIZE );
/*............................................................................*/
         system ( ptr );                 /* edit [evtlly modify] tmp par file */
         rread_params( tmpfle, 't' );   /*  re-read parameters from tmp file  */
         rvise_params( );              /*   revise/reconfigure ...            */
         store_params( tmpfle, 't' ); /*    restore on temporary file         */
/*..................................*/
# else
         printf( "\n No editor is defined for this option !" );
# endif
         item = items2;
         ( csp->clscr ) = 1; /* N !=0 : clear screen; scroll that nbr of lines*/

        goto par_menu;
        break;

        case 4:  /* reload the default configuration */
/*............................................................................*/
         deflt_params( );               /* enter default parameters           */
         rvise_params( );              /*  revise/reconfigure parameters      */
         store_params( tmpfle, 't' ); /*   store on temporary file            */
/*...............................*/
         item = items2;
         ( csp->clscr ) = 1; /* N !=0 : clear screen; scroll that nbr of lines*/

        goto par_menu;
        break;

        case 5:

# if defined ( AMD_PRINTER )
         strcpy( ptr, AMD_PRINTER );
         strcat( ptr, " " );
         strcat( ptr, tmpfle );
/*............................................................................*/
         system ( ptr );               /* print file */
/*...................................*/
# else
         printf( "\n No printer is defined for this option !" );
# endif
         item = items2;
         ( csp->clscr ) = 1; /* N !=0 : clear screen; scroll that nbr of lines*/

        goto par_menu;
        break;

        case 0:  /* end of program / escape */

         remove( tmpfle );

         PRBLDCLR( "" );
         printf( "\r%*s", 79, "INPUT" );
         PRNORMAL( "" );
         return -ONE;

        break;
      }; /* end switch(*) */
/*............................................................................*/
      remove( tmpfle );

      strcpy( fleptr, parlog  );
      strcat( fleptr, lotos(( state->job ), null, " " ));

      printf( "\n opened: Parameters logfile %s ", fleptr );
/*............................................................................*/
      store_params( fleptr, 'p' );  /* save final parameters on log file      */
/*................................*/

      printf( CLEAR_LINE );

      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      printf( "\r Parameters logfile %s ", fleptr );
      printf( timefrm, timeptr );
   }; 
   return null;
}
# undef IPT_OPRDEF
# undef IPT_PARDEF
/*============================================================================*/
/***************** end of parameter input function input(*) *******************/
