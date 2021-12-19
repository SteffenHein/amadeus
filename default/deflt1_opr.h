/* [ file: deflt_opr.h ] */
/* Update: December 6, 2021 */
/*----------------------------------------------------------------------------*/
# ifndef LINLEN
   # define LINLEN 61
# endif
/*----------------------------------------------------------------------------*/
# include "../src/OPRSTRNGS.M"
/*============================================================================*/

void deflt_operts( void ) /* default operation modes */
{
/* declarations: - */

   static short
      ll = LINLEN;

/* prototypes: */   

   char
      *lotos( long nn, char cc, char *format );

   void
      cpylne( char lne[], const char *txt, const char *brc, short linlen );
/*----------------------------------------------------------------------------*/
   OPRSTRNGS( ); /* copy the operation options strings */
/*............................................................................*/
/* number of parameters: */

   opr->n[0] = 8 ; /* number M of parameters opr->n[1],...,opr->n[M] */

/*............................................................................*/
/* defaults: structure/reference line; time/frequency domain: */

   opr->n[1] = 1.00e+05; /* maximum number of outer iterations */
   opr->n[2] = 3 ; /* number of inner iterations */
   opr->n[3] = 0 ; /* formula 0,1,2  [ 0: input is BASIC (else: INITIAL)
                                                        reproduction number ] */
   opr->n[4] = 2 ; /* x scale ( time unit ) 1:transmission time | 2:days */
   opr->n[5] = 1 ; /* y scale ( plot format ) 1:linear | 2:logarithmic */
   opr->n[6] = 2 ; /* y units 1:normalized; herd size=1 | 2:conventional units */
   opr->n[7] = 0 ; /* [0] 1: [don't] write titles on graphics */
   opr->n[8] = 1 ; /* [0] 1: [don't] stop when no sick persons remain */

   return;
}
/*============================================================================*/
/************************ end of function deflt_opr(*) ************************/
