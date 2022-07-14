/* [ file: types.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  The typedef header of program AMADEUS                                       *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 11, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
/* The type definition structure of the operation modes transfer functions    */
/*----------------------------------------------------------------------------*/
# define TP_UPDATES 1
typedef struct
{
   char
      burst;

   long
      kk,
      kout,      /* outer iteration index */ 
      kinn;      /* inner iteration index */

   double
      tt,
      dt, 
      suscpt,
      incdnc,
      incidc,
      incsum,
      infctd,
      cmlinc,
      immune,
      vaccin,
      lethal,
      reprod,
      nxtbst,
      stpbst;

   double
      dhdt[100000+ONE];

} UPDATES;
/*----------------------------------------------------------------------------*/
/* The type definition structure of the parameter transfer functions          */
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
      ntx[OPERATIONS+ONE][STS_SIZE+ONE];

   long
      n[OPERATIONS+ONE];

} OPERTNS;
/*----------------------------------------------------------------------------*/
/* The type definition structure of the parameter transfer functions          */
/*----------------------------------------------------------------------------*/
# ifndef PARAMETERS
   # define PARAMETERS 50
# endif
/*----------------------------------------------------------------------------*/
# define TP_PARMTRS 1
/*----------------------------------------------------------------------------*/
typedef struct
{
   char 
      xunits,
      yunits,
      yscale,
      nmstop, 
      titles,
      rfmmde, /* reproduction factor modulation mode */
      bstmde, /* burst mode [ 0: shift, 1: slates ] */
      wgtrec, /* operation mark [ 0/1: don't/do weight recovery history ] */ 
      wgtvac, /* operation mark [ 0/1: don't/do weight vaccination history ] */
      rtn;

   char
     stx[PARAMETERS+ONE][STS_SIZE+ONE];

   double
      s[100+ONE];

   long
      kend,
      kcic,
      ktrm,

      maxout,    /* the maximum number of outer iterations */
      maxinn,    /* the maximum number of inner iterations */
      mxictm,    /* maximum ( kinc, ktrm ) */
      formula;   /* the immunity differential formula */

   double
      yy,      
      dy,      
      DltT,      /* time increment [ days ] */

      Nhrd,      /* herd size [ number of members ] */
      Nifc,      /* initial number of infected members */
      Nimn,      /* initial number immune members */
      Ninf,      /* initial number of infective ['sick'] members */
      Nlty,      /* initial number of deceased members */
      Nvac,      /* initial number of vaccinated members */

      Repr,      /* initial reproduction number */
      Ithr,      /* incidence "threshold" [ stop computation when incidence  */
                                      /* lower than that number of persons ] */
      Ieff,      /* immunisation efficacy [ ratio; 0 < Immc <= 1 ] */
      Veff,      /* vaccination efficacy [ ratio; 0 < Veff <= 1 ] */
      Slnt,      /* percentage of "silent" [ asymptomatic ] cases */
      Ltlt,      /* lethality [ percent ] */
      Rmda,      /* R modulation amplitude [ 0 < Rmda; default: 1 ] */
      Bstf,      /* random burst factor */
      
      rifc,      /* initially infected fraction [ ratio ] */
      rinf,      /* initially infective fraction [ ratio ] */
      rimn,      /* initially immune fraction [ ratio ] */
      rvcd,      /* initially vaccinated fraction [ ratio ] */
      rlty,      /* initially deceased fraction [ ratio ] */
      reff,      /* initial effective reproduction factor */
      repr,      /* reproduction rate */
      rthr,      /* incidence threshold [ Ithr/Tinf ] */

      Vacr,      /* vaccination rate [ vaccinations per day ] */
      vrpc,      /* vaccination ratio per cycle */

      wght_ifc,  /* infection weight: 100/( 100-Slnt ) */
      wght_imm,  /* immunisation weight: ( 100+Ltlt )/( 100-Slnt ) */
      wght_lty,  /* lethality weight: Ltlt/( 100-Slnt ) */
      wght_vac,  /* vaccination efficiency [ ratio ] */
      
      Ttrm,      /* mean transmission time [ Tinc+Till, e.g. ] */
      Timu,      /* mean immunity duration [ days ] */
      timn,      /* Timu in natural units [ Ttrm scale ] */
      Tvac,      /* mean vaccination duration [ days ] */
      tvcn,      /* Tvac in natural units [ Trm scale ] */
      Tcic,      /* n days incidence */
      tcin,      /* Tcic in natural units [ Ttrm scale ] */
      Trml,      /* R modulation length [ days ] */
      trml,      /* R modulation length [ Ttrm scale ] */
      Trrd,      /* R modulation retard [ delay in days ] */
      trrd,      /* R modulation retard [ Ttrm scale ] */
      Tbln,      /* Average burst length [ days ] */
      tbln,      /* Tbln in natural units [ Ttrm scale ] */
      Tbps,      /* Average burst pause [ days ] */
      tbps,      /* Tbps in natural units [ Ttrm scale ] */
      Tend,      /* time intervall [ days ] */

      timmun,    /* time of attained group immunity */
      tmxinc,    /* time of maximum incidence */
      tmxcic,    /* time of maximum N days incidence */
      tmximn,    /* time of maximum immunity */
      tmxrpd,    /* time of maximum reproduction number */
      tmxifc,    /* time of maximum infections */
      tmxicr,    /* time of maximum increase */
      tmmicr,    /* time of maximum decrease */

      mincic,    /* minimum N days incidence */
      maxcic,    /* maximum N days incidence */
      mininc,    /* minimum incidence */
      maxinc,    /* maximum incidence */
      minifc,    /* initial infection [= minimum] */
      maxifc,    /* maximum infection */
      minimn,    /* minimum immunity */
      maximn,    /* maximum immunity */
      minrpd,    /* minimum reproduction number */
      maxrpd,    /* maximum reproduction number */
      minvac,    /* minimum vaccinated fraction */
      maxvac,    /* maximum vaccinated fraction */
      minlty,    /* initial lethality [= minimum] */
      maxlty,    /* maximum lethality */

      mean_imm,  /* mean effectively immune */
      mean_inc,  /* mean incidence */
      mean_cic,  /* mean n days accumulated incidence */
      mean_vac;  /* mean effectively vaccinated */

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
/* The type definition structure of the text console function txcnsl(*)       */

# ifndef TP_TXCNSL
    # define TP_TXCNSL 1
# endif
/*----------------------------------------------------------------------------*/
# define CNS_ITEMS 10 /* maximum number of menu items                         */
# define CNS_LNLEN 79 /* number of characters in menu line                    */
# define CNS_LNINT  1 /* number of characters in menu line                    */
# define CNS_POSIT 67 /* position of menu items [labels] in line              */
/*----------------------------------------------------------------------------*/
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
# define TP_AMDSTATE 1
typedef struct
{
   signed char
      cpmrk,
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
      name[STS_SIZE+ONE],
      text[STS_SIZE+ONE],
      logfle[STS_SIZE+ONE],
      errfle[STS_SIZE+ONE];

   short
      job,   /* running job index */
      fstjob;/* initial job index */

   long
      fleps; /* file position pointer */

   double
      scale;

   FILE 
     *display;

   TXCNSL
     *csp;

   OPERTNS
     *opr;

   PARMTRS
     *par;

   UPDATES 
     *upd;

} AMDSTATE;
/*************************** end of file types.h ******************************/
