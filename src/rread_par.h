/* [ file: rread_par.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function rread_par(*)                                                       *
*  Reads parameter file [ type par.log<N> ]                                    *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: February 01, 2022 ]                            <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/

/*============================================================================*/

short rread_par( char *filename, char mode )
{
/* declarations: */

   static AMDSTATE 
     *state = &amdstat;

   static PARMTRS
     *par = &parmtrs;

   static FILE
     *paramtrs = NULL;

   static short 
      ii = null,
      jj = null,
      parameters;

   static char
      ptr[STS_SIZE] = {null},
      fleptr[STS_SIZE] = {null},
      txtstr[STS_SIZE] = {null},
    **endp = NULL;

   static const char 
     *scformat = "%s";
/*----------------------------------------------------------------------------*/
   state = &amdstat;
   par = &parmtrs;

   strcpy( fleptr, filename );

   while( *fleptr != '0' )
   {
      paramtrs = fopen( fleptr, "r+" );

      while ( paramtrs == null )
      {
         if (( state->uif ) == 't' )
         {
            if ( state->cpmrk < TWO )
	    {
               fprintf( stdout, "\n Parameter file \"%s\" "
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
	          "\n Parameter file '" );
               strcat( txtstr, fleptr );
               strcat( txtstr, "' not found in present directory !" );

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

         paramtrs = fopen( fleptr, "r+" );
      };

      ii = null;
      while ( ii < IPT_MAXLBL )
      {
         fscanf( paramtrs, scformat, ptr );

         if ( null == strncmp( ptr, "PARAMETERS", 10 ))
         {
            fscanf( paramtrs, scformat, ptr ); /* string: program name */
            fscanf( paramtrs, scformat, ptr ); /* string: any comment */

            parameters = ( short ) par->s[null];

            fscanf( paramtrs, scformat, ptr ); /* string "Parameters" */
            fscanf( paramtrs, scformat, ptr ); /* string "anything" */

            if ( mode == 't' )
            {
               for ( jj=ONE; jj<=parameters; jj++ )
               {
                  fscanf( paramtrs, scformat, ptr );

		  if ( null == strncmp( ptr, "Inf", THREE ))
                     par->s[jj] = HUGE_VALF;
                  else if ( null == strncmp( ptr, "HUGE", FOUR ))
                     par->s[jj] = HUGE_VALF;
                  else
                     par->s[jj] = strtod( ptr, endp );

                  fscanf( paramtrs, scformat, ptr ); /* string "<---" */
                  fscanf( paramtrs, scformat, ptr ); /* text string */
               };
            }
            else /* if mode != 't'emporary file */
            {
               for ( jj=ONE; jj<=parameters; jj++ )
               {
                  fscanf( paramtrs, scformat, ptr ); /* text string */
                  fscanf( paramtrs, scformat, ptr ); /* double string */

                  if ( null == strncmp( ptr, "Inf", THREE ))
                     par->s[jj] = HUGE_VALF;
                  else if ( null == strncmp( ptr, "HUGE", FOUR ))
                     par->s[jj] = HUGE_VALF;
                  else
                     par->s[jj] = strtod( ptr , endp );
               };
            };

            fclose( paramtrs );
            return ONE;
            break;
         }
         else
         {
            ii++;
            if ( ii == IPT_MAXLBL )
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
	                "\n Parameters not found in file <" );
                     strcat( txtstr, fleptr );
                     strcat( txtstr, "> !" ); 

                     PRBLDCLR( txtstr );
                     PRNORMAL( "" );

	             return null;
                  };
               }
               else
               {
                  fprintf( stderr, "\nparameters not found "
                     "in file \"%s\" !\n", fleptr );
                  exit( EXIT_FAILURE );
               };
            };
         }; /* end if( ptr != "PARAMETERS" ) */
      }; /* end while( ii < IPT_MAXLBL ) */
   }; /* end while( *flelbl == '0' ) */

   fclose( paramtrs );
   return ONE;
}
/*============================================================================*/
/********************* end of function rread_params(*) ************************/
