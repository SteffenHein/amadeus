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
*  [ Update: July 01, 2022 ]                                <contact@sfenx.de> *
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
     *parfle = NULL;

   static short 
      ii = null,
      jj = null,
      parameters;

   static char
      ptr[STS_SIZE+ONE] = {null},
      fleptr[STS_SIZE+ONE] = {null},
      txtstr[STS_SIZE+ONE] = {null},
    **endp = NULL;

   static const char 
     *scformat = "%s";
/*----------------------------------------------------------------------------*/
   state = &amdstat;
   par = &parmtrs;

   strcpy( fleptr, filename );

   while( *fleptr != '0' )
   {
      parfle = fopen( fleptr, "r+" );

      while ( parfle == null )
      {
         if ( state->uif == 't' )
         {
            if ( state->cpmrk < TWO )
	    {
               fprintf( stdout, "\n Parameter file '%s' "
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
	 else /* if ( state->uif != 't' ) */
         {
            fprintf( stderr, "\nParameters file '%s' "
	       "not found in working directory\n", fleptr );

            exit( EXIT_FAILURE );
         };
         parfle = fopen( fleptr, "r+" );
      };

      ii = null;
      while ( ii < IPT_MAXLBL )
      {
         fscanf( parfle, scformat, ptr );

         if ( null == strncmp( ptr, "PARAMETERS", 10 ))
         {
            fscanf( parfle, scformat, ptr ); /* string: program name */
            fscanf( parfle, scformat, ptr ); /* string: any comment,  
	                                        "Evolution of ...", e.g. */
            fscanf( parfle, scformat, ptr ); /* string "Init._values_and..."*/
            fscanf( parfle, scformat, ptr ); /* string "Do_not_change..." */
            fscanf( parfle, scformat, ptr ); /* string "[Leave_contiguous..." */

            parameters = ( short ) par->s[null];

            if ( mode == 't' )
            {
               jj = null;	
	       while ( jj < parameters )
               {
		  ++jj;
                  fscanf( parfle, scformat, ptr );

		  if ( null == strncmp( ptr, "Inf", THREE ))
                     par->s[jj] = HUGE_VALF;
                  else if ( null == strncmp( ptr, "HUGE", FOUR ))
                     par->s[jj] = HUGE_VALF;
                  else
                     par->s[jj] = strtod( ptr, endp );

                  fscanf( parfle, scformat, ptr ); /* string "<---" */
                  fscanf( parfle, scformat, ptr ); /* text string */
               };
            }
            else /* if mode != 't'emporary file */
            {
               jj = null;	
	       while ( jj < parameters )
               {
		  ++jj;
                  fscanf( parfle, scformat, ptr ); /* text string */
                  fscanf( parfle, scformat, ptr ); /* double string */

                  if ( null == strncmp( ptr, "Inf", THREE ))
                     par->s[jj] = HUGE_VALF;
                  else if ( null == strncmp( ptr, "HUGE", FOUR ))
                     par->s[jj] = HUGE_VALF;
                  else
                     par->s[jj] = strtod( ptr , endp );
               };
            };

            fclose( parfle );
            return ONE;
            break;
         }
         else /* if ( ptr != "PARAMETERS" ) */
         {
            ++ii;
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
         }; /* end if ( ptr != "PARAMETERS" ) */
      }; /* end while( ii < IPT_MAXLBL ) */
   }; /* end while( *flelbl == '0' ) */

   fclose( parfle );
   return ONE;
}
/*============================================================================*/
/********************* end of function rread_params(*) ************************/
