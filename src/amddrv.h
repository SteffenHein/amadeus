/* [ file: amddrv.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Body of driver function amddrv(*)                                           *
*  Coordinates the parameter input, corrections and computational steps        *
*  by subsequently calling the respective functions                            *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 01, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/

/*============================================================================*/
short amddrv( int argn, char **args )
{
/* allusions: */

   static AMDSTATE
     *state = &amdstat;

/* declarations: */

   static FILE
     *logfle = NULL;

# if USE_NCURSES == 1
   static FILE
     *errfle;
# endif

   static TXCNSL
     *csp = &cns;

   static char 
      fleptr[STS_SIZE] = {'\0'},
      lnestr[STS_SIZE] = {'\0'},
      ptr[STS_SIZE] = {'\0'},           
    **endp = null;

   static const char 
     *logptr = "amd.log",
     *errptr = "amd.err",
     *dline = "========================================"\
              "========================================";

   static short 
      ii = null,
      job = null;

   static long 
      kk = null;
/*............................................................................*/
/* time_t types: */

   time_t nseconds = null;
   time_t   *timer = null;
   time_t time( time_t *timer );

   static char
      timeptr[STS_SIZE] = {null};

/* prototypes: */

# ifndef _CCBUG
   char
      *strcpy( char *ptr1, const char *ptr2 ),  
      *strcat( char *ptr1, const char *ptr2 ),
      *strncat( char *ptr1, const char *ptr2, size_t n );
# endif

   char
      *lotos( long mm, char cc, char *format );

   char
      *dotos( double x, char precision, char *format );

   TXCNSL 
     *txcnsl( TXCNSL *csp );

   AMDSTATE
     *amdwrk( AMDSTATE *state );

   short
      input ( char *option );

   void
      init_opr( void );
      
   void
      deflt_opr( void );

   short
      rvise_opr( void );

   short 
      rread_opr( char *filename, char mode );

   short 
      store_opr( char *filename, char mode );

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
/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
/* get the terminal info: */

   term = ( char *) getenv( "TERM" ); /* get the terminal */
   kk = tgetent( null, term );

   if( kk != ONE )
   {
      errfle = fopen( errptr, "a+" );

      fprintf( errfle, \
         "\nError message from job %s, function %s :", \
         lotos ( state->job, null, " " ), __func__ ); \
      fprintf( errfle, "\nCan't get the termcap info\n" );

      fclose ( errfle );

      fprintf( stderr, \
         "\n Error message from job %s, function %s :", \
         lotos ( state->job, null, " " ), __func__ ); \
      fprintf( stderr, "\n Can't get the termcap info\n" );

      exit( EXIT_FAILURE );
   };
# endif
/*............................................................................*/
/* set buffer length = null: */

   kk = setvbuf( stdin, null, _IONBF, null );
   kk = setvbuf( stdout, null, _IONBF, null ); 
/*............................................................................*/
/* initialize file pointers: */

   ii = null; do
   {
      tmpfle[ii] = '\0';
      fleptr[ii] = '\0';
      ++ii;
   } while( ii < STS_SIZE );
/*...........................................................................*/
/* bind structure pointers */

   state->opr = &opertns;
   state->par = &parmtrs;
   state->upd = &updates;
   state->csp = &cns;

   ii = null; do
   {
      state->logfle[ii] = null;
      state->errfle[ii] = null;
      ++ii;
   } while( ii < STS_SIZE );

   state->fleps = null;
   
   strcpy( state->name, "AMADEUS" );
   strcpy( state->text, "Evolution_of_spreading_diseases" );
   strcpy( state->logfle, logptr );
   strcpy( state->errfle, errptr );
/*............................................................................*/
/* read command line: */

   job = null;

   if( argn )
   {
      do
      {
         strcpy( ptr, *( args++ ));

         if ( null == strncmp( ptr, "--file", 6 )) /* paramater file */
            state->uif = 'f';                      /* input mode */

         if ( null == strncmp( ptr, "--init-job", 9 ))
         {
            if ( --argn )
            {
               strcpy ( ptr, *( args++ ));
               job = strtol( ptr, endp, DEC );
            };
         };

         if ( null == strncmp( ptr, "--init-fle", 9 ))
         {                                         /* parameter file */
            state->uif = 'f';                      /* input mode */

            if ( --argn )
            {
               strcpy ( fleptr, *( args++ ));
            };
         };
      } while ( --argn );
   };
/*............................................................................*/
   state->fstjob = job; /* the 1st job index */
   state->job = job;    /* the running job index */

   strcpy( tmpfle, "/tmp/temp.XXXXX" );
/*............................................................................*/
   init_opr( );
   init_par( );
/*............................................................................*/
/* 't'ext mode: */

   if (( state->uif != 'g' )
     &&( state->uif != 'b' )
     &&( state->uif != 'f' ))
   {
      csp = txcnsl( null ); /* initialize the text console */
      csp->dfopt = 2; /* the initial default menu option */

     first_console:

      state->uif = 't'; /* user interface: 't'ext console */
      state->cpmrk = null;
      
      csp->option = 3; do
      {
         if ( state->job == job )
            strcpy( csp->cmmnt, "Welcome to AMADEUS !" );
         else
            strcpy( csp->cmmnt, "Welcome back to AMADEUS !" );

         csp->clscr = - ONE;
         csp->items = 3;
         csp->dflnf = csp->dfopt; /* set line feed before this option */

         strcpy( csp->envmt, "AMADEUS" );
         strcpy( csp->tasks, "Select [enter number]:" );

/* menu options */

         strcpy( lnestr, "* parameter input file \"" );
	 strcat( lnestr, IPT_PARINIT );
	 strcat( lnestr, lotos( state->job, null, " " ));
	 strcat( lnestr, "\"");

         strcpy( csp->mline[1], lnestr );
         strcpy( csp->mline[2], "* text console input " );
         strcpy( csp->mline[3], "* support" );

         strcpy( csp->escpe, "End of program / escape" );

         if ( state->job == job )
            strcpy( csp->cnfrm, "Nothing done! Do you really want to quit ?" );
         else
            strcpy( csp->cnfrm, "Do you really want to quit ?" );

/*............................................................................*/
         csp = txcnsl( csp );   /* build the [ start ] menu                   */
/*............................*/

         switch( csp->option )
	 {
           default: case 0: case 'y': case 'Y': case 'j': case 'J':

            return null;
           break;
/*............................................................................*/
	   case 1:
/* clear screen: */

         /* fprintf( stdout, CLEAR_LINE ); */
            fprintf( stdout, "\n %s",\
	       "======================================="
               "=======================================" );
            nseconds = time( timer );
            strcpy( timeptr, ctime( &nseconds ));
            fprintf( stdout, "\n ");
            PRBLDCLR( "AMADEUS started:");
            fprintf( stdout, "\n %s", timeptr );
            PRNORMAL( "" );

            state->cpmrk = TWO;
	   break;
/*............................................................................*/
           case 2:
	   break;
/*............................................................................*/
	   case 3:

            fprintf( stdout, "\n %s",\
	       "======================================="\
	       "=======================================" );
            PRBLDCLR( "" );
	    fprintf( stdout, "\n Call: +49+8061.936362 or" );
            fprintf( stdout, "\n email: contact@sfenx.de" );
	    fprintf( stdout, "\n [ Don't hesitate to ask your questions.]" );
            PRNORMAL( "\n");

            csp->dfopt = 2; /* next default: text console input */
	   break;
         };
      } while( csp->option == 3 );
   };

   if (( state->cpmrk < TWO )
     &&( state->uif == 't' )) /* text console input */
   {
      strcpy( csp->cmmnt, "Welcome back to AMADEUS !" );

      csp->dfopt = 3; /* next default: complete configuration */
      csp->clscr = 1;
      
      state->cpmrk = null; 

     second_console:

      csp->items = 5;
      csp->dflnf = csp->dfopt; /* set special line feed before */
                               /* that option line */
      nseconds = time( timer );
      strcpy( timeptr, ctime( &nseconds ));
      strcpy( csp->title, "\n Program AMADEUS: " );
      strncat( csp->title, timeptr, 24 );

      strcpy( csp->envmt, "AMADEUS" );
      strcpy( csp->tasks, "Select [enter number]:" );

      strcpy( csp->mline[1], "* computation modes" );
      strcpy( csp->mline[2], "* parameters" );
      strcpy( csp->mline[3], "* the complete configuration" );
      strcpy( csp->mline[4], "* start computation" );
      strcpy( csp->mline[5], "* support" );

      strcpy( csp->escpe, "End of program / escape" );

      if ( state->job == null )
         strcpy( csp->cnfrm, "Nothing done! Do you really want to quit ?" );
      else
         strcpy( csp->cnfrm, "Do you really want to quit ?" );
/*............................................................................*/
      csp = txcnsl( csp );      /* build the [ start ] menu                   */
/*............................*/

      state->act = null; /* the current prog stage [ null = par input ] */

      switch( csp->option )
      {
        default:
         break;
/*...........................................................................*/
        case 0: case 'y': case 'Y': case 'j': case 'J':

        return null;
        break;
/*...........................................................................*/
        case 1:

         ii = input( "operations" ); 
	 
         if ( ii == -ONE ) 
	   return null;
         else if ( ii == ONE ) /*start computation */
	 {
           state->cpmrk = ONE;
	   break;
         };

         csp->dfopt = 2; /* the next default menu option */
         csp->clscr = 1; /* N != 0: clear screen; scroll N lines */

        break;
/*...........................................................................*/
        case 2:

         ii = input( "parameters" );  
	 
         if ( ii == -ONE )
	   return null;
         else if ( ii == ONE ) /*start computation */
	 {
           state->cpmrk = ONE;
	   break;
         };

         csp->dfopt = 4; /* the next default menu option */
         csp->clscr = 1; /* N != 0: clear screen; scroll N lines */

        break;
/*...........................................................................*/
        case 3:

         ii = input( "operations" );

         if ( ii == -ONE ) 
	    return null;
         else if ( ii == ONE ) /* start computation */
	 {
            state->cpmrk = ONE;
           break;
         };

         ii = input( "parameters" );

         if ( ii == -ONE ) 
	    return null;
         else if ( ii == ONE ) /* start computation */
	 {
            state->cpmrk = ONE;
	   break;
         };

         csp->dfopt = 4; /* the next default menu option */
         csp->clscr = 1; /* N != 0: clear screen; scroll N lines */

        break;
/*...........................................................................*/
        case 4:

        if ( state->cpmrk == null )
	{
           PRBLDCLR( "");
	   fprintf( stdout, "\n\n No new parameters defined !"
	                      "\n [ Processing default parameters ]\n" );
           PRNORMAL( "" ); 
        };
        state->cpmrk = ONE;

        break;
/*...........................................................................*/
        case 5:

         PRBLDCLR( "" );
	 fprintf( stdout, "\n Call: +49+8061.936362 or" );
         fprintf( stdout, "\n email: contact@sfenx.de" );
         fprintf( stdout, "\n [ Don't hesitate to ask your questions.]" );
         PRNORMAL( "\n");

         csp->dfopt = 4; /* the initial default menu option */
	 
        break;
      };

      if (( null < csp->option )
        &&( state->cpmrk == null ))
      {
         strcpy( csp->cmmnt, "Welcome back to AMADEUS !" );
         goto second_console;
      }
      else if ( null < state->cpmrk )
      {
         rvise_par( );
/*............................................................................*/
/* clear screen: */

         fprintf( stdout, CLEAR_LINE );
         fprintf( stdout, "\n %s",\
	    "======================================="
            "=======================================" );
         nseconds = time( timer );
         strcpy( timeptr, ctime( &nseconds ));
         fprintf( stdout, "\n ");
         PRBLDCLR( "AMADEUS started:");
         fprintf( stdout, "\n %s", timeptr );
         PRNORMAL( "" );
	 
      }; /* end if state->cpmrk == ONE */
   }; /* end if ( state->uif != 'f','g','b' ) */

   if (( state->cpmrk == TWO )
     ||( state->uif != 't' )) /* parameter 'f'ile input */
   {                          /* or graphical mode, e.g. */
/*............................................................................*/
/* enter computation modes: */

      if (( '\0' == fleptr[null] )
        ||( state->cpmrk == TWO ))
      {
         strcpy( fleptr, IPT_PARINIT );
         strcat( fleptr, lotos( state->job, null, " " ));
      };

      rvise_opr( ); /* revise and reconfigure ...*/
      
      ii = rread_opr( fleptr, 'f' );

      if (( state->cpmrk == TWO )
        &&( ii == null )) 
         goto first_console;

      rvise_opr( ); /* revise and reconfigure ...*/
/*............................................................................*/
/* enter parameters: */

      rvise_par( ); /* revise and reconfigure */

      ii = rread_par( fleptr, 'f' );
      
      if (( state->cpmrk == TWO )
        &&( ii == null )) 
         goto first_console;

      rvise_par( );            
   };
/*............................................................................*/
/* open process log file: */

   logfle = fopen( logptr , "a+" );
   setvbuf( logfle, null, _IONBF, null );

   nseconds = time( timer );
   strcpy( timeptr, ( ctime( &nseconds ) + 11 ));

   fprintf( logfle, "\nJob no " );
   fprintf( logfle, "%s ", lotos( state->job, null," " ));
   fprintf( logfle, "launched at " );
   fprintf( logfle, "%-.8s", timeptr );

   state->fleps = ftell( logfle );

   fclose( logfle );
/*............................................................................*/
/* create final logs: */

   state->act = ONE; /* the actual program stage [ ONE = computation ] */

   rvise_opr( ); /* final operations */
   
   strcpy( fleptr, IPT_OPRLOG );
   strcat( fleptr, lotos( state->job, null, " " ));
   store_opr( fleptr, 'o' ); /* restore revised file as log file */

   rvise_par( ); /* final parameters */

   strcpy( fleptr, IPT_PARLOG );
   strcat( fleptr, lotos( state->job, null, " " ));
   store_par( fleptr, 'p' ); /* restore revised file as log file */

/* here starts the proper algorithm */
/*.................................*/
   state = amdwrk( state );        /*                                         */
/*...............................*/
/* ... it's terminated [ continue ? ] */

   logfle = fopen( logptr, "a+" );

   nseconds = time( timer );
   strcpy( timeptr, ( ctime( &nseconds ) + 4 ));

   fprintf( logfle, "\nJob no %d terminated ", state->job );
   fprintf( logfle, "%-.20s", timeptr );
   fprintf( logfle, "\n%s", dline );

   state->fleps = ftell( logfle );
   fclose( logfle );

   ++( state->job ); /* next job label */

   if ( state->uif == 't' ) /* text input */
   {
      strcpy( csp->cmmnt, "Welcome back to AMADEUS !" );

      csp->dfopt = 0; /* default menu option: it's terminated, end of prog */

      if ( state->cpmrk == TWO )
        goto first_console;
      else
        goto second_console;
   };
   return null;
}  
/*============================================================================*/
/**************************** end of function amddrv(*) ***********************/
