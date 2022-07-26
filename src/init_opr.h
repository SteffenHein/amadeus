# ifndef OPERATIONS
   # define OPERATIONS 20
# endif
/*============================================================================*/
void init_opr( void )
{
   static OPERTNS
     *opr = &opertns;

   static short 
      ii = null,
      jj = null;
      
   void deflt_opr( void );
   short rvise_opr( void );
/*............................................................................*/
   opr = &opertns;

   if ( opr->n[null] == null )
   {
/* reset operation parameters and enter default divisions */

      ii = null;
      while( ii <= OPERATIONS )
      {
	 jj = null;
	 while( jj < STS_SIZE )
         {
            opr->ntx[ii][jj] = ( char ) null;
	    ++jj;
         };
         ++ii;
      };
/*............................................................................*/
      deflt_opr( );           /* enter default operations                     */
      rvise_opr( );          /*  revise default parameters                    */
/*.........................*/
   };
   return;
}
/*============================================================================*/
