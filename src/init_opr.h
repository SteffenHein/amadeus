# ifndef OPERATIONS
   # define OPERATIONS 20
# endif
/*============================================================================*/
void init_operts( void )
{
   static OPERTNS
     *opr = &opertns;

   static short 
      ii = null,
      jj = null;
      
   void deflt_operts( void );
   short rvise_operts( void );
/*............................................................................*/
   if ( opr->n[null] == null )
   {
/* initialize; enter default divisions */

      for ( ii=null; ii<=OPERATIONS; ii++ )
         for ( jj=null; jj<STS_SIZE; jj++ )
            opr->ntx[ii][jj] = ( char ) null;
/*............................................................................*/
      deflt_operts( );        /* enter default operations                     */
      rvise_operts( );       /*  revise default parameters                    */
/*.........................*/
   };
   return;
}
