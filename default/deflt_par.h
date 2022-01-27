/* [ file: deflt_par.h ] */
/* Update: January 25, 2022 */
/*----------------------------------------------------------------------------*/
# ifndef LINLEN
   # define LINLEN 61
# endif
/*----------------------------------------------------------------------------*/
# include "../src/PARSTRNGS.M"
/*============================================================================*/

void deflt_par( void ) /* default model parameters */
{
   static PARMTRS
     *par = &parmtrs;

   static short
      ll = LINLEN;

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   par = &parmtrs;

   PARSTRNGS( );  /* copy number of parameters and parameter strings */
/*............................................................................*/
/* default parameters: */
                                                                               
   par->s[1]  = 1.000e+05; /* Nhrd; herd size [(real) number of members]  */
   par->s[2]  = 1.000e+00; /* Ninf; Initially transmissive members [number] */ 
   par->s[3]  = 1.000e+00; /* Nifc; Initially infected members [number] */
   par->s[4]  = 1.000e+00; /* Nimn; Initially immune members [number] */
   par->s[5]  = 0.000e+00; /* Nlty; Init. already deceased members [number] */
   par->s[6]  = 3.000e+00; /* Nrpd; The reproduction factor */
   par->s[7]  = 1.000e+00; /* Immc; The immunization coefficient */
   par->s[8]  = 2.000e+01; /* Percentage of asymptomatic ('silent') cases */
   par->s[9]  = 2.000e-02; /* Percentage of lethal cases */
   par->s[10] = 1.400e+01; /* Ttrm; The mean tansmission time [days] */
   par->s[11] = 9.000e+01; /* Timu; The mean duration of immunity [days] */
   par->s[12] = 7.000e+00; /* Tinc; Cumulative incidence over time [days] */
   par->s[13] = 0.000e+00; /* Ithr; The incidence threshold [0<=Ithr] */
   par->s[14] = 0.000e+00; /* Lvlb; Burst level, on average [0<=Lvlb] */
   par->s[15] = 0.000e+00; /* Tmeb; Burst length, on average [days] */
   par->s[16] = 0.000e+00; /* Tbst; Burst every T-th day on average [days] */
   par->s[17] = 7.300e+02; /* Tend; Time limit [days] */
   par->s[18] = 1.000e-01; /* DltT; Time step [days] */

   return;
}
/*============================================================================*/
/************************ end of function deflt_par(*) ************************/
