# ifndef PARAMETERS
   # define PARAMETERS 50
# endif
/*============================================================================*/
void init_par( void )
{
   static PARMTRS
     *par = &parmtrs;

   short
      ii = null,
      jj = null;

   void deflt_par( void );
   short rvise_par( void );
/*----------------------------------------------------------------------------*/
   par = &parmtrs;

   if (( short ) par->s[null] == null )
   {
/* reset and enter default parameters: */

      ii = null;
      while( ii <= PARAMETERS )
      {
         par->s[ii] = ZERO;

	 jj = null;
	 while(jj < STS_SIZE )
	 {
            par->stx[ii][jj] = ( char ) null;
            jj++;
	 };
	 ii++;
      };
/*............................................................................*/
      deflt_par( );        /*                                                 */
      rvise_par( );       /*                                                  */
/*......................*/
   };
   return;
}
/*============================================================================*/
