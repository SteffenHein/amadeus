/* [ file: CONFIG.H ] */
/*----------------------------------------------------------------------------*/
/* AMADEUS, release v1.0r2                                                    */
/*                                                                            */
/* A numerical Model Approximating the Development of Epidemics               */
/* Under homogeneous conditions of Spread                                     */
/*                                                                            */
/* (C) SHEIN; Munich, April 2020                             Steffen Hein     */
/* [ Update: June 09, 2022 ]                              <contact@sfenx.de>  */
/*----------------------------------------------------------------------------*/
# ifndef AMD_PAGER
   # define AMD_PAGER "more" 
# endif
/* editor command: "vi", "vim", "ed", "joe", "emacs", e.g. */
# ifndef AMD_EDITOR
   # define AMD_EDITOR "vi"
# endif
/* printer: "lp", e.g. */
# ifndef AMD_PRINTER
   # define AMD_PRINTER "lp"
# endif
# ifndef AMD_RESULTS
/* # define AMD_RESULTS "./work/" */
/* # define AMD_RESULTS "../work/" */
/* # define AMD_RESULTS "/home/sfenx/work/" */
   # define AMD_RESULTS "" 
# endif
/*----------------------------------------------------------------------------*/
# define USE_UNICODE 1 
# define USE_NCURSES 1 
/*----------------------------------------------------------------------------*/
/* different 'my_terminal' configurations [ for ANSI C compiler, */
/* generic Unix, etc. ] */
# if defined ( _Wine )
   # undef USE_NCURSES
   # define USE_NCURSES 0 
# elif defined ( _Unix )
   # undef USE_NCURSES
   # define USE_NCURSES 0
# elif defined ( _BSD )
   # undef USE_NCURSES
   # define USE_NCURSES 0
# elif defined ( _GNU_Linux )
   # undef USE_NCURSES
   # define USE_NCURSES 0
# elif defined ( _Linux )
   # undef USE_NCURSES
   # define USE_NCURSES 0
# elif defined ( _Ansi )
   # undef USE_NCURSES
   # define USE_NCURSES 0
# elif defined ( _HPUX )
   # undef USE_NCURSES
   # define USE_NCURSES 0 
# elif defined ( _SuSE )
   # undef USE_NCURSES
   # define USE_NCURSES 0
# endif
/*----------------------------------------------------------------------------*/
# ifndef AMD_RMLOGS
   # define AMD_RMLOGS 0  /* 1: initially remove old log file */
# endif
/*----------------------------------------------------------------------------*/
/* used in various functions: */
# define GIANT_VAL ( 1.e+277 )
# define SMALL_VAL ( 1.e-277 )
/*============================================================================*/
/* CPU time stopping mode: */
# define SYS_TIMES 0 /* 2: use function times(*)                           */
                     /* 1: use function difftime(*)    [ ANSI C standard ] */
                     /* 0: use function clock(*)       [ ANSI C standard ] */
/*----------------------------------------------------------------------------*/
/* macros used in plot fuction graphp(*): */

# define PLOT_FORMAT "gnuplot_2D" /*plot file format: "SPLINE" or "gnuplot" */
# define GPH_DATFLE "dat"    /* the data file suffix */
# define GPH_USCALE 0        /* 1: take uniform scales on xy axes */
# define GPH_CURVES 20       /* maximum number of graphics */
# define GPH_POINTS 500      /* maximum number of abscissae ( x-values ) */
# define GPH_RNDOFF 4        /* roundoff to that number of digits */
# define GPH_MXRNGE (9.e+00) /* The max. range of abs.values in gnuplot is */
                             /* interval [1.e-GPH_MXRNGE, 1.e+GPH_MXRNGE]. */
                             /* Beyond this range all values are rescaled. */
/*----------------------------------------------------------------------------*/
# define IPT_MAXLBL 500
/****************************** end of file CONFIG.H **************************/
