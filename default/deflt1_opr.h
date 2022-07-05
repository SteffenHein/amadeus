/* [ file: deflt_opr.h ] */
/* Update: July 05, 2022 */
/*----------------------------------------------------------------------------*/
# ifndef LINELGTH
   # define LINELGTH 61
# endif
/*----------------------------------------------------------------------------*/
# include "../src/OPRSTRNGS.M"
/*============================================================================*/

void deflt_opr( void ) /* default operation modes */
{
/* declarations: - */

   static OPERTNS
     *opr = &opertns;

   static short
      lln = LINELGTH;

/* prototypes: */   

   char
      *lotos( long nn, char cc, char *format );

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   opr = &opertns;

   OPRSTRNGS( ); /* copy number of operation parameters and parameter strings */
/*............................................................................*/
/* defaults: structure/reference line; time/frequency domain: */

   opr->n[1] = 1 ; /* x units 0: transmission time | 1: days                  */
   opr->n[2] = 1 ; /* y units 0: normalized        | 1: conventional          */
/* more options:
                               0: normalized ( herd size = 1 )
                               1: conventional units 
		               2: normalized, scaled to community size
                               3: conventional, scaled to community size 
*/
   opr->n[3] = 0 ; /* y scale ( plot format ) 0: linear | 1: logarithmic      */
   
   opr->n[4] = 1 ; /* [0] 1: [don't] write titles on graphics */
   opr->n[5] = 0 ; /* [0] 1: [don't] stop when no sick persons remain */
   opr->n[6] = 1 ; /* [0] 1: [don't] reweight recovery history */
   opr->n[7] = 1 ; /* [0] 1: [don't] reweight vaccination history */

   opr->n[8] = 0 ; /* processing mode 0,1,2 [ 0: input is BASIC (else: INITIAL)
                                                        reproduction number ] */

   opr->n[9] = 0 ; /* reprod. factor modulation 0,1,...4 [ 0: rectangular, 
                      1: parabolic, 2: half wave sinus, 3: full wave sinus,   
                      4: half-wave sinus squared ]                            */
		      
   opr->n[10] = 0 ; /* burst mode [ 0: rectangular | 1: zigzag ]               */
                    
   opr->n[11] = 1.00e+05; /* maximum number of outer iterations */
   opr->n[12] = 10 ; /* number of inner iterations */

   return;
}
/*============================================================================*/
/************************ end of function deflt_opr(*) ************************/
