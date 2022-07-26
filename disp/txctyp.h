/* [ file: txctyp.h ] */
/* Update: January 27, 2022 */
/*----------------------------------------------------------------------------*/
/* The structure type header of text console function txcnsl(*) */

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
/************************** end of file txctyp.h ******************************/
