/* [ file: rread_opr.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function rread_opr(*)                                                       *
*  Reads operation modes from a file [ type opr.log<N> ]                       *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 04, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/

/*============================================================================*/

short rread_opr( char *filename, char mode )
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
      ptr[STS_SIZE+ONE] = {null},
      fleptr[STS_SIZE+ONE] = {null},
      txtstr[STS_SIZE+ONE] = {null},
    **endp = NULL;

   static const char
     *scformat = "%80s";
/*----------------------------------------------------------------------------*/
   state = &amdstat;
   opr = &opertns; 

   strcpy( fleptr, filename );

   while( *fleptr != '0' )
   {
      operatns = fopen( fleptr, "r+" );

      while ( operatns == null )
      {
         if ( state->uif == 't' )
         {
            if ( state->cpmrk < TWO )
	    {
               fprintf( stdout, "\n Operation parameter file \"%s\" "
                  "not found in present directory:\n", fleptr );

               fprintf( stdout, "\n Please re-enter filename "
                  "[ Escape: enter null ] >----> " );

               scanf( "%s", fleptr );

               if ( *fleptr == '0' )
                  return null;
            }
	    else if ( state->cpmrk == TWO )
            { 
               fprintf( stdout, CLEAR_LINE );

               strcpy( txtstr, 
	          "\n Parameter file \"" );
               strcat( txtstr, fleptr );
               strcat( txtstr, "\" not found in present directory !" );

               PRBLDCLR( txtstr );
               PRNORMAL( "" );

	       return null;
            };
         }
	 else
         {
            fprintf( stderr, "\nOperation parameters file \"%s\" "
	       "not found in working directory\n", fleptr );
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
                  fscanf( operatns, scformat, ptr ); 
		                             /* parameter name: opr->ntx[jj]*/
               };
            }
	    else /* parameter log file, e.g. */
	    {
               for ( jj=ONE; jj<=operations; jj++)
               {
                  fscanf( operatns, scformat, ptr ); /* parameter name */
                  fscanf( operatns, scformat, ptr ); /* parameter */
                  opr->n[jj] = strtod( ptr, endp );  /* option */
               };
            };

            fclose( operatns );
            return ONE;
	    
	    break;
         }
         else
         {
            ++ii;
            if( ii == IPT_MAXLBL )
            {
               if ( state->uif == 't' )
	       {
                  if ( state->cpmrk < TWO )
	          {
                     fprintf( stdout, 
		        "\n Operation parameters not found "
                           "in in file \"%s\" :\n", fleptr );

                     fprintf( stdout,
		        "\n Please re-enter filename "
                           "[ Escape: enter null ] >----> " );
                     scanf( "%s", fleptr );

                     if ( *fleptr == '0' )
                        return null;
                  }
	          else if ( state->cpmrk == TWO )
                  { 
                     fprintf( stdout, CLEAR_LINE );

                     strcpy( txtstr, 
	                "\n Operation parameters not found in file \"" );
                     strcat( txtstr, fleptr );
                     strcat( txtstr, "\" !" ); 

                     PRBLDCLR( txtstr );
                     PRNORMAL( "" );

	             return null;
                  };
               }
	       else
	       {
                  fprintf( stderr, 
		     "\nOperation parameters not found "
	             "in file \"%s\"\n", fleptr );
                  exit( EXIT_FAILURE );
               };
            };
         }; /* end if( ptr != "OPERATIONS" ) */
      }; /* end while( ii < IPT_MAXLBL ) */
   }; /* end while( *fleptr != '0' */

   fclose( operatns );
   return ONE;
}
/*============================================================================*/
/********************* end of function rread_operts(*) ************************/
