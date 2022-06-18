/* [ file: deflt_opr.h ] */
/* Update: June 16, 2022 */
/*----------------------------------------------------------------------------*/
# ifndef LINLEN
   # define LINLEN 66
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
      ll = LINLEN;

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

   opr->n[1] = 1.00e+05; /* maximum number of outer iterations */
   opr->n[2] = 10 ; /* number of inner iterations */
   opr->n[3] = 0 ; /* processing mode 0,1,2 [ 0: input is BASIC (else: INITIAL)
                                                        reproduction number ] */

   opr->n[4] = 0 ; /* reprod. factor modulation 0,1,...4 [ 0: rectangular, 
                      1: parabolic, 2: half wave sinus, 3: full wave sinus,   
                      4: half-wave sinus squared ]                            */
		      
   opr->n[5] = 0 ; /* burst mode [ 0: rectangular | 1: zigzag ]               */
                    
   opr->n[6] = 0 ; /* x units 0: transmission time | 1: days                  */
   opr->n[7] = 1 ; /* y units 0: normalized        | 1: conventional          */
/* more options:
                               0: normalized ( herd size = 1 )
                               1: conventional units 
		               2: normalized, scaled to community size
                               3: conventional, scaled to community size 
*/
   opr->n[8] = 0 ; /* y scale ( plot format ) 0: linear | 1: logarithmic      */
   opr->n[9] = 1 ; /* [0] 1: [don't] write titles on graphics */
   opr->n[10] = 1 ; /* [0] 1: [don't] stop when no sick persons remain */

   return;
}
/*============================================================================*/
/************************ end of function deflt_opr(*) ************************/
