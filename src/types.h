/* [ file: types.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A plain numerical Model Approximating the Development of Epidemics          *
*  Under varied conditions if Spread                                           *
*                                                                              *
*  The typedef header of program AMADEUS                                       *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: January 12, 2022 ]                             <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
/* The type definition structure of the operation modes transfer functions    */
/*----------------------------------------------------------------------------*/
# ifndef OPERATIONS
   # define OPERATIONS 20
# endif
/*----------------------------------------------------------------------------*/
# define TP_OPERTNS 1
typedef struct
{
   signed char
      rtn;

   char
      opt[SHS_SIZE];

   char
      ntx[OPERATIONS+ONE][STS_SIZE];

   long
      n[OPERATIONS+ONE];

} OPERTNS;
/*----------------------------------------------------------------------------*/
/* The type definition structure of the parameter transfer functions          */
/*----------------------------------------------------------------------------*/
# ifndef PARAMETERS
   # define PARAMETERS 100
# endif
/*----------------------------------------------------------------------------*/
# define TP_PARMTRS
/*----------------------------------------------------------------------------*/
typedef struct
{
/*
   static struct PARMTRS
     *ppt;
*/   
   char 
      xscale,
      yscale,
      yunits,
      nmstop, 
      titles,
      rtn;

   char
     *ntx[PARAMETERS+ONE],
     *stx[PARAMETERS+ONE];

   double
      s[100+ONE];

   long
      kend,
      kcic,
      ktrm,

      nout,      /* outer iteration index */ 
      ninn,      /* inner iteration index */
      
      maxout,    /* the maximum number of outer iterations */
      maxinn,    /* the maximum number of inner iterations */
      mxictm,    /* maximum ( kinc, ktrm ) */
      formula;   /* the immunity differential formula */

   double
      yy,      
      dy,      
      tt,        /* time [ Ttrm scale ] */
      dt,        /* internal time step [ Ttrm scale ] */
      DltT,      /* time increment [ days ] */

      Ncom,      /* community size [ number of members ] */
      Nhrd,      /* herd size [ number of members ] */
      Nifc,      /* initial number of infected persons */
      Nimn,      /* initial number immune persons */
      Ninf,      /* initial number infective [sick] persons */
      Nlty,      /* initial number of dead persons */
      Nthr,      /* incidence "threshold" [ stop computation when incidence  */
                                      /* lower than that number of persons ] */
      Immc,      /* immunisation coefficient [ 0 < Immc <= 1 ] */
      Repr,      /* initial reproduction number */
      Slnt,      /* percentage of "silent" (asymptomatic) cases */
      Ltlt,      /* lethality [ percent ] */
      
      rifc,      /* initial group infecion [ ratio ] */
      rimn,      /* initial group immunity [ ratio ] */
      rinf,      /* initial group infectivity [ ratio ] */
      rlty,      /* initial group lethality [ ratio ] */
      repr,      /* reproduction rate [ log(Nrpd)/Tinf ] */
      rthr,      /* incidence threshold [ Nthr/Tinf ] */

      ffct,      /* form factor */

      wght_ifc,  /* infection weight: 100/( 100-Slnt ) */
      wght_imm,  /* immunisation weight: ( 100+Ltlt )/( 100-Slnt ) */
      wght_lty,  /* lethality weight: Ltlt/( 100-Slnt ) */
      
      Ttrm,      /* mean transmission time [ Tinc+Till, e.g. ] */
      Timu,      /* mean immunity duration [ days ] */
      timn,      /* Timu in natural units [ Ttrm scale ] */
      Tinc,      /* N [=Tacu] days incidence */
      ticn,      /* Tinc in natural units [ Ttrm scale ] */
      Tend,      /* time intervall [ length ] */

      timmun,    /* time of attained group immunity */
      tmxinc,    /* time of maximum incidence */
      tmxcic,    /* time of maximum N days incidence */
      tmximn,    /* time of maximum immunity */
      tmxrpd,    /* time of maximum reproduction number */
      tmxifc,    /* time of maximum infections */
      tmxicr,    /* time of maximum increase */
      tmmicr,    /* time of maximum decrease */

      mincic,    /* minimum averaged incidence */
      maxcic,    /* maximum averaged incidence */
      maxifc,    /* maximum infection */
      maximn,    /* maximum immunity */
      mininc,    /* minimum incidence */
      maxinc,    /* maximum incidence */
      maxlty,    /* maximum lethal cases */
      minrpd,    /* minimum reproduction number */
      maxrpd;    /* maximum reproduction number */

   double
      dudt[100000+ONE];

} PARMTRS;
/*----------------------------------------------------------------------------*/
# define TP_DSPLAY
/* The type definition structure of the running pointer function dsplay(*)    */
/*----------------------------------------------------------------------------*/
typedef struct
{
   char 
      rtn;

   char 
      option,
      messge[LGS_SIZE];

   short
      rcsps; /* relative curser position */
   
   long
      fleps, /* file position pointer [ fleps = ftell(*) etc. ] */
      state,
      range;

   FILE 
     *display;

} DSPLAY;
/*----------------------------------------------------------------------------*/
# define TP_TXCNSL 1

# define CNS_ITEMS 10 /* maximum number of menu items                         */
# define CNS_LNLEN 79 /* number of characters in menu line                    */
# define CNS_LNINT  1 /* number of characters in menu line                    */
# define CNS_POSIT 67 /* position of menu items [labels] in line              */
/*----------------------------------------------------------------------------*/
/* The type definition structure of the text console function txcnsl(*)       */

typedef struct
{
   signed char 
      clscr,
      rtn; 

   int
      items, dfopt, dflnf,
      lnlen, posit, lnint,
      lglen, dblen, stlen,
      option;

   char
      title[LGS_SIZE],
      rqfrm[SHS_SIZE],
      tasks[CNS_LNLEN],
      flags[CNS_LNLEN],
      cmmnt[CNS_LNLEN],
      envmt[CNS_LNLEN],
      escpe[CNS_LNLEN],
      cnfrm[CNS_LNLEN],
      instr[CNS_LNLEN],
      dfstr[CNS_LNLEN],
      rqdbl[CNS_LNLEN],
      rqlng[CNS_LNLEN],
      rqstr[CNS_LNLEN],
      mflag[CNS_ITEMS],
      mflin[CNS_ITEMS],
      mline[CNS_ITEMS][CNS_LNLEN];

   long
      dflng, inlng;

   double
      dfdbl, indbl;
   
} TXCNSL;
/*----------------------------------------------------------------------------*/
/* driver function amddrv(*) state structure */
/* [ reflects actually charged topology, parameter, boundary conditions, ..., */
/*   file names, file labels etc.]: */
/*----------------------------------------------------------------------------*/
# define AMDTP_AMDSTATE 1
typedef struct
{
   signed char
      onerr,
      rtn;

/* if 'skp[N] = S'or's': skip message <N> next time [ debugging purposes ] */
   char
      ctl, /* control parameter, set to null during initialization */
      amd_skp[VSS_SIZE],
      wrk_skp[VSS_SIZE],
      ini_skp[VSS_SIZE];

   unsigned char
      uif, /* user interface [ 'g'raphical, or 't'ext console, e.g. ] */
      act; /* actual program stage */

   char
      name[STS_SIZE],
      text[STS_SIZE],
      logfle[STS_SIZE],
      errfle[STS_SIZE];

   short
      job,   /* running job index */
      fstjob;/* initial job index */

   long
      fleps; /* file position pointer */

   double
      upd, /* update coefficient [ transferred to any function ] */
      uexp, /* initial update coefficient */
      scale;

   FILE 
     *display;

   TXCNSL
     *cns;

   OPERTNS
     *opr;

   PARMTRS
     *par;

} AMDSTATE;
/*************************** end of file types.h ******************************/
