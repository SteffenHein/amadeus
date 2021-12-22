/* [ file: rread_opr.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A simple numerical Model Approximating the Development of Epidemics         *
*  Under varied conditions if Spread                                           *
*                                                                              *
*  Function rread_opr.h(*)                                                     *
*  Reads operation modes from a file [ type opr.log<N> ]                       *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: December 19, 2021 ]                            <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/

/*============================================================================*/

short rread_operts( char *filename, char mode )
{
/* declarations: */

   static AMDSTATE 
     *state = &amdstat;

   static OPERTNS
     *opr = &opertns;

   static FILE
     *operatns = NULL;

   static short 
      ii = null,
      jj = null,
      operations;

   static char
      ptr[STS_SIZE] = {null},
      fleptr[STS_SIZE] = {null},
    **endp = NULL;

   static const char
     *scformat = "%80s";
/*----------------------------------------------------------------------------*/
   ( state->opr ) = &opertns;

   strcpy( fleptr, filename );

   while( *fleptr != '0' )
   {
      operatns = fopen( fleptr, "r+" );

      while ( operatns == null )
      {
         if (( state->uif ) == 't' )
         {
            printf( "\n operations file %s not found "
               "in present directory:\n", fleptr );
            printf( "\n please re-enter filename [ Escape: "
               "enter null ] >----> " );

            scanf( "%s", fleptr );

            if ( *fleptr == '0' )
               return null;
         }
	 else
         {
            fprintf( stderr, "\noperations file %s not found "
	       "in working directory\n", fleptr );
            exit( EXIT_FAILURE );
         };

         operatns = fopen( fleptr, "r+" );
      };

      ii = null;
      while ( ii < IPT_MAXLBL )
      {
         fscanf( operatns, scformat, ptr );

         if ( null == strncmp( ptr, "OPERATIONS", 10 ))
         { 
            fscanf( operatns, scformat, ptr ); /* string spt->name */
            fscanf( operatns, scformat, ptr ); /* string spt->text */
            fscanf( operatns, scformat, ptr ); /* string opr->ntx[null] */

	    operations = opr->n[null];
            if ( mode == 't' ) /* read from temporary file */
	    {
               for ( jj=ONE; jj<=operations; jj++)
               {
                  fscanf( operatns, scformat, ptr ); /* parameter [string] */
                  opr->n[jj] = strtod( ptr, endp );  /* a number */
                  fscanf( operatns, scformat, ptr ); /* string "<---", e.g. */
                  fscanf( operatns, scformat, ptr ); /* parameter name: opr->ntx[jj]*/
               };
            }
	    else /* parameter log file, e.g. */
	    {
               for ( jj=ONE; jj<=operations; jj++)
               {
                  fscanf( operatns, scformat, ptr ); /* parameter name */
                  fscanf( operatns, scformat, ptr ); /* parameter */
                  opr->n[jj] = strtod( ptr, endp ); /* option */
               };
            };

            fclose( operatns );
            return null;
	    break;
         }
         else
         {
            ii++;

            if( ii == IPT_MAXLBL )
            {
               if (( state->uif ) == 't' )
	       {
                  printf( "\n operation parameters not found "
                     "in file '%s':\n", fleptr );
                  printf( "\n please re-enter filename [ Escape: "
                     "enter null ] >----> " );

                  scanf( "%s", fleptr );

                  if ( *fleptr == '0' )
                     return null;
               }
	       else
	       {
                  fprintf( stderr, "\noperation parameters not found "
	             "in file '%s'\n", fleptr );
                  exit( EXIT_FAILURE );
               };
            };
         }; /* end if( ptr != "OPERATIONS" ) */
      }; /* end while( ii < IPT_MAXLBL ) */
   }; /* end while( *fleptr != '0' */

   return null;
}
/*============================================================================*/
/********************* end of function rread_operts(*) ************************/
