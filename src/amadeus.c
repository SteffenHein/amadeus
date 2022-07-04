/*[ file: amadeus.c ] */
# define PROGRAM "AMADEUS"
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Main program amadeus(*)                                                     *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 01, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# define _POSIX_SOURCE 1 /* some headers of the POSIX.1 standard will be used */
# define _ISOC99_SOURCE 1
/*----------------------------------------------------------------------------*/
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <string.h>
# include <ctype.h>
# include <time.h>            /* cf. time( ),ctime( ),asctime( ),localtime( ) */
/*----------------------------------------------------------------------------*/
# if _ISOC99_SOURCE == 1
   # include <fenv.h>
   # include <iso646.h>
# endif
/*----------------------------------------------------------------------------*/
# include "../math/maths.h"
# include "../math/consts.h"
/*----------------------------------------------------------------------------*/
/* Edit and customize this general configuration header: */
# include "../CONFIG.H"
/*----------------------------------------------------------------------------*/
/* Edit and customize this general configuration header: */
# include "../src//types.h"
/*----------------------------------------------------------------------------*/
# ifndef USE_NCURSES
   # define USE_NCURSES 1
# endif
# include "../src/PRNTCRS.M"
/*----------------------------------------------------------------------------*/
/* covid program release */
# ifndef AMADEUS_RELEASE
   # define AMADEUS_RELEASE "v1.0r2"
# endif
/*----------------------------------------------------------------------------*/
# ifndef AMADEUS_UPDATE
   # define AMADEUS_UPDATE "2022-07-01"
# endif
/*----------------------------------------------------------------------------*/
/* This may yet be defined in the general configuration header CONFIG.H: */
/*
*//* # define SYS_TIMES 0 *//* 2: use function times(*)                       */
                            /* 1: use function difftime(*) [ ANSI C standard ]*/
                            /* 0: use function clock(*)    [ ANSI C standard ]*/
# if SYS_TIMES == 2
   # include <sys/times.h>  /* system time: cf. times(*)                      */
# endif
/*----------------------------------------------------------------------------*/
/* operational constants: */

# define DISP 1              /* set DISP 1 for displaying intermediate results*/
# define EXTENDED 0          /* EXTENDED (0) 1 for (reduced) extended files   */
# define CLEAR 0             /* CLEAR    (0) 1 for parameter clearing         */
# define BUFFER 1024
/*----------------------------------------------------------------------------*/
                                       /*=== system orientated declarations =>*/
                                       /*--- file pointers ------------------>*/
                                       /*--- system functions --------------->*/
time_t time( time_t *timer );                
char *ctime( const time_t *timer );          

struct tm *localtime( const time_t *timer ); 
char *asctime( const struct tm *lt_ptr );

# if SYS_TIMES == 2
   long sysconf(int s_name); 
   clock_t times( struct tms *cl_ptr );
# elif SYS_TIMES == 1
   double difftime( time_t time1, time_t time0 );
# else
   clock_t clock( void );
# endif

int setvbuf( FILE *display, char *buff, int unbuff, size_t bufsize );
 
                                       /*--- global structures -------------->*/
/*
static struct tm loct    = {null};
static struct tm *lt_ptr = &loct;
*/

# if SYS_TIMES == 2
static struct tms cpu    = {null};
static struct tms *cl_ptr= &cpu;
# endif
                                       /*--- global variables --------------->*/
static int unbuff     = _IONBF;
static size_t bufsize =  null;
/*----------------------------------------------------------------------------*/
/* text console program mode: set type of your terminal */
/* and enhance its capabilities */
/*............................................................................*/
# if USE_NCURSES == 1
/* 'my_terminal' configuration: */

   # include <ncurses.h>
   # include <curses.h>
   # include <term.h>        /* terminal type header */
# endif
/*============================================================================*/

int main( int argc, char **argv )
{
/*--- system function prototypes -------------------------------------------->*/

   FILE *fopen( const char *restrict filename, const char *restrict mode );
   int fprintf( FILE *restrict stream, const char *restrict format,...);

   long   strtol( const char *ptr, char **endp, int base );
   double strtod( const char *ptr, char **endp );

   char *strcpy( char *dest, const char *src );
   char *strcat( char *dest, const char *src );
   char *strncpy( char *dest, const char *src, size_t N );

   time_t time( time_t *timer );
   char *ctime( const time_t *timer );

   struct tm *localtime( const time_t *timer );
   char *asctime ( const struct tm *lt_ptr );
/*............................................................................*/
# if SYS_TIMES == 2
   long sysconf(int s_name); 
   clock_t times( struct tms *cl_ptr );
# elif SYS_TIMES == 1
   double difftime( time_t t1, time_t t0 );
# endif
/*............................................................................*/
   int setvbuf( FILE *display, char *buff, int mode, size_t bfsize );
                        /*--- system  orientated declarations and allusions ->*/
   static FILE
     *logfile = null;

   int
      ii = null,
      argn = null;
/*
   static short 
      hrs = null,
      min = null,
      job = null;
*/
   static time_t
      nseconds = null,
     *timer    = null;
/*............................................................................*/
# if SYS_TIMES == 2
   static clock_t
      ticks = null,
      usr_time = null;
# elif SYS_TIMES == 1
   static time_t
      time0 = null,
      time1 = null;

   static double
      usr_time = ZERO;
# endif
/*............................................................................*/
# if USE_NCURSES == 1

# if defined ( _BSD )
   int setupterm( NCURSES_CONST char *term, int fildes, int *errret );
# endif
# if defined ( _GNU_Linux )
   int setupterm( NCURSES_CONST char *term, int fildes, int *errret );
# endif
# if defined ( _Linux )
   int setupterm( NCURSES_CONST char *term, int fildes, int *errret );
# endif
# if defined ( _SuSE )
   int setupterm( NCURSES_CONST char *term, int fildes, int *errret );
# endif
# endif /* USE_NCURSES == 1 */
/*............................................................................*/
/* user orientated declarations and allusions: */

   static char 
      ptr[STS_SIZE] = {null},
     *args[SHS_SIZE],
     *tmeptr;

   static const char 
     *logname = "amd.log",
     *ptlne = "----------------------------------------"\
              "----------------------------------------",
     *dline = "========================================"\
              "========================================";

   static TXCNSL
     *csp;

   static unsigned char
      ind = null;

/*--- user function prototypes -------------------------------------------->*/

   short 
      amddrv( int argn, char **args );

   char 
     *lotos ( long lngint, char length, char *format );

   char 
     *dotos ( double lngdbl, char precision, char *format );

   TXCNSL 
     *txcnsl( TXCNSL *csp );

/*----------------------------------------------------------------------------*/
/*------------------ end of user oriented declaration part -------------------*/
/*----------------------------------------------------------------------------*/
/* set buffer length = null: */

   ind = setvbuf( stdin, null, unbuff, bufsize ); /*set buffer length = null*/
   ind = setvbuf( stdout, null, unbuff, bufsize ); 
/*............................................................................*/
/* allocate memory: */

   tmeptr = ( char * ) calloc( STS_SIZE, ONE );

   argn = null; 
   while ( argn < SHS_SIZE )
      args[(argn++)] = ( char * ) calloc( STS_SIZE, ONE );
/*............................................................................*/
/* read the command line: */

   argn = null;
   if( null < --argc )
   {
      do
      {
         strcpy( ptr, *( ++argv ));

         if (( null == strcmp( ptr, "v" ))
           ||( null == strcmp( ptr, "-v" ))
           ||( null == strcmp( ptr, "V" ))
           ||( null == strcmp( ptr, "-V" )))
         {
            fprintf( stdout, "\nAMADEUS program version %s", AMADEUS_RELEASE );
            fprintf( stdout, " %s\n", AMADEUS_UPDATE );
	    exit( EXIT_SUCCESS );
         }
         else if (( null == strcmp( ptr, "f" ))
                ||( null == strcmp( ptr, "-f" ))
                ||( null == strcmp( ptr, "F" ))
                ||( null == strcmp( ptr, "-F" )))
         {
            if ( --argc )
	    {
               strcpy( ptr, *( ++argv ));
               strcpy( args[(argn++)], "--init-fle" );
               strcpy( args[(argn++)], ptr );
            }
	    else
            {
               fprintf( stderr,
                  "\nundefined parameter input file in call 'covid %s' !",
                  ptr );
               fprintf( stderr,
                  "\nUSAGE: covid [-g] [%s inputfile] [-n jobindex]\n",
                  ptr );
               exit( EXIT_FAILURE );
            };
         }
         else if (( null == strcmp( ptr, "b" ))
                ||( null == strcmp( ptr, "-b" ))
                ||( null == strcmp( ptr, "B" ))
                ||( null == strcmp( ptr, "-B" ))
                ||( null == strcmp( ptr, "g" ))
                ||( null == strcmp( ptr, "-g" ))
                ||( null == strcmp( ptr, "G" ))
                ||( null == strcmp( ptr, "-G" )))
         {
            strcpy( args[(argn++)], "--file" );
         }
         else if (( null == strcmp( ptr, "n" ))
                ||( null == strcmp( ptr, "-n" ))
                ||( null == strcmp( ptr, "N" ))
                ||( null == strcmp( ptr, "-N" ))
                ||( null == strcmp( ptr, "j" ))
                ||( null == strcmp( ptr, "-j" ))
                ||( null == strcmp( ptr, "J" ))
                ||( null == strcmp( ptr, "-J" )))
         {
            if ( --argc )
	    {
               strcpy( ptr, *( ++argv ));
               strcpy( args[(argn++)], "--init-job" );
               strcpy( args[(argn++)], ptr );
            }
	    else
            {
               fprintf( stderr,
                  "\nundefined job index in call 'covid %s' !", ptr );
               fprintf( stderr,
                  "\nUSAGE: covid [-g] [-f inputfile] [%s jobindex]\n",
                  ptr );
               exit( EXIT_FAILURE );
            };
         }
	 else
	 {
            fprintf( stderr,
               "\nunknown program option covid '%s'", ptr );
            fprintf( stderr,
               "\nUSAGE: covid [-g] [-f inputfile] [-n jobindex]\n" );
            exit( EXIT_FAILURE );
         };
      } while ( null < ( --argc ));
   }; /* end if ( null < argc ) */
/*............................................................................*/
/* read the startup time: */

   nseconds = time( timer );
   tmeptr = ctime( &nseconds );

/* [ same as 'tmeptr = asctime(localtime(&nseconds));' ] */
/*............................................................................*/
/* open log file: */

# if CVD_RMLOGS == 1 /* remove former files */
   remove( logname );
# endif

   logfile = fopen( logname , "a+" );
   setvbuf( logfile, null, _IONBF, null );

   fprintf( logfile,
      "\nProgram %s ", PROGRAM ); /* start message: */
   fprintf( logfile,
      "- Evolution of spreading diseases\n" );

   if ( null < argn )
   {
      fprintf( logfile,
         "started in option(s) ' " );
      ii = null; do
      {
         fprintf( logfile,
             "%s ", args[ii] );
      } while (( ++ii ) < argn );
      fprintf( logfile,
         "'\n" );
   } /* end if ( null < argc ) */
   else
      fprintf( logfile, "started: " );

   fprintf( logfile, "%.24s", tmeptr );
   fprintf( logfile, "\n%s", ptlne );
/*............................................................................*/
/* text console program mode: set type of your terminal */
/* and enhance its capabilities */
/*............................................................................*/
# if USE_NCURSES == 1

# if defined ( _BSD )
   setupterm( "cons25", ONE, ( int* ) null );
# endif
# if defined ( _GNU_Linux )
   setupterm( "linux", ONE, ( int* ) null );
# endif
# if defined ( _Linux )
   setupterm( "linux", ONE, ( int* ) null );
# endif
# if defined ( _SuSE )
   setupterm( "linux", ONE, ( int* ) null );
# endif

/* get the terminal info: */

   term = ( char *) getenv( "TERM" ); /* get the terminal */
   ind = tgetent( null, term );

   if( ONE != ind )
   {
      fprintf( stderr, "Error on getting the termcap info\n" ); 
      exit( EXIT_FAILURE );
   };
# endif /* USE_NCURSES == 1 */
/*............................................................................*/
/* display | menu: */

   csp = txcnsl( null ); /* initialize the text console */

   CLSCREEN;
   PRNORMAL( "" );

   ( csp->clscr ) = 1; /* clear screen; scroll that number of lines */
   strcpy(( csp->title ), "Program " );
   strcat(( csp->title ), PROGRAM );
   strcat(( csp->title ), " started:\n " );
   strncat(( csp->title ), tmeptr, 24 );
/*............................................................................*/
   csp = txcnsl( csp );   /*                                                  */
/*......................*/
/* the function should start writing something like that: */
/*
   fprintf( stdout, "XYZ program %s started: ", PROGRAM );
   PRNORMAL( "" );
   fprintf( stdout, " %s", tmeptr );
   fprintf( stdout, "\n %s",\
      "======================================="
      "=======================================" );
*/
/*............................................................................*/
/* set_time: */

# if SYS_TIMES == 2
   cl_ptr   = &cpu;
   ind      = times( cl_ptr );
   usr_time = ( cl_ptr->tms_utime );
# elif SYS_TIMES == 1
   time0 = time( timer );
# endif
/*............................................................................*/
# if CLEAR == 1
   fprintf( stdout, "\n initializing parameters" );
   ind = clear( ); 
   fprintf( stdout, "\r                         \r" );
# endif 
/*............................................................................*/
/*
   nseconds = time(timer);
   lt_ptr = localtime(&nseconds);
      hrs = ( short ) ( lt_ptr->tm_hour );
      min = ( short ) ( lt_ptr->tm_min  );
      ind = ( short ) ( lt_ptr->tm_wday );
*/
/*============================================================================*/
/* now call the driver function: */

/*............................................................................*/
   ind = amddrv( argn, args );     /* call covid driver function            */
/*.................................*/
/* the job is done, check for error return */

# if DISP == 1
   if ( ind == ONE ) 
   {
      fprintf( stderr, " \n Abnormal job termination.  " );
# if CLEAR == 1
      ind = clear ( );           
# endif
      fprintf( stderr, "\n -------------------------- error: job overridden"
         " ----------------------------\n" );
      exit( EXIT_FAILURE );
   };
# endif
/*...........................................................................*/
/*
   nseconds = time(timer); 
   lt_ptr = localtime(&nseconds);
      hrs = ( short ) ( lt_ptr->tm_hour );
      min = ( short ) ( lt_ptr->tm_min  );
      ind = ( short ) ( lt_ptr->tm_wday );
*/
/*...........................................................................*/
# if CLEAR == 1 
      ind = clear( );
# endif

   fprintf( stdout, "\n ======================================"
           "========================================\n" );

   nseconds = time( timer );
   tmeptr = ctime( &nseconds );

   fprintf( stdout, " Program %s terminated:  %s\n", PROGRAM, tmeptr );

   freopen( logname, "a+", logfile );

/* fprintf( logfile, "\n%s", ptlne ); */
   fprintf( logfile,
      "\nProgram %s terminated:\n", PROGRAM );
   fprintf( logfile, "%.24s", tmeptr );
   fprintf( logfile, "\n%s", dline );
   
   fclose( logfile );
/*...........................................................................*/

   exit( EXIT_SUCCESS );
}
/*============================================================================*/
/************************* end of program 'amadeos.c' *************************/
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
