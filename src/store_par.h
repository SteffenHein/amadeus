/* [ file: store_par.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function store_par(*)                                                       *
*  Stores the model parameters                                                 *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 21, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/

/*============================================================================*/
/*
# define EXCHANGE(M,N)\
{ \
   ii = (M); \
   jj = (N); \
   xx = par->s[ii]; \
   par->s[ii] = par->s[jj]; \
   par->s[jj] = xx; \
}
*/

short store_par( char *filename, char mode )
{
/* declarations: */

   static AMDSTATE
     *state = &amdstat;

   static PARMTRS
     *par = &parmtrs;

   static OPERTNS
     *opr = &opertns;

   static FILE 
     *paramtrs = NULL;

   static long 
      ll = null;

   static short
      ii = null,
      operations = null,
      parameters = null;

   static char
     *timeptr = NULL,
      ptr[STS_SIZE+ONE] = {null},
      fleptr[STS_SIZE+ONE] = {null};

   static const char /* dsplay(*) options */
     *scformat = "%80s",
     *dline = "========================================"\
              "========================================";
   time_t 
      nseconds = null,
     *timer = NULL;

   char
      *lotos( long mm, char cc, char *format );
/*----------------------------------------------------------------------------*/
   state = &amdstat;
   par = &parmtrs;
   opr = &opertns;
   
   strcpy( fleptr, filename );
   paramtrs = fopen( fleptr, "w+" );  /* save coordinates on log file */

   ii = null;
   while ( ii < IPT_MAXLBL )
   {
      fscanf( paramtrs, scformat, ptr );

      if ( null == strncmp( ptr, "PARAMETERS", FIVE ))
      {
         ll = ftell( paramtrs ) + ONE;
         break;
      }
      else
      {
         ii++;
         if ( ii == IPT_MAXLBL )
         {
            if ( mode == 't' ) /* temporary file */
            { 
               fprintf( paramtrs, "%s\n", "The actually charged" );
               fprintf( paramtrs,
                  "%s%s\n", "--> PARAMETERS-", \
		   lotos(( state->job ), null, " " ));
            }
            else
               fprintf( paramtrs,
                  "%s%s\n", "PARAMETERS-", lotos(( state->job ), null, " " ));

            ll = ftell( paramtrs );
         };
      };
   };

   fseek( paramtrs, ll, SEEK_SET );
   parameters = ( short ) par->s[null]; /* the number of parameters */
/*............................................................................*/
   STOREPAR( paramtrs, mode );
/*............................................................................*/
   if( mode != 't' )
   { 
/* append operation parameters file: */

      operations = ( short ) opr->n[null]; /* the number of operations */
      
      fprintf( paramtrs,
         "\n%s\n", dline );

      fprintf( paramtrs,
         "\n%s%s\n", "OPERATIONS-", lotos(( state->job ), null, " " ));
/*............................................................................*/
      STOREOPR( paramtrs, 'o' );
/*............................................................................*/

      nseconds = time( timer );
      timeptr = ctime( &nseconds );

      fprintf( paramtrs, "\nAMADEUS input parameter file %s created:", fleptr );
      fprintf( paramtrs, "\n%.24s", timeptr );
      fprintf( paramtrs, "\n%c", EOF );
   };
   fclose( paramtrs );
   return null;
}
/*============================================================================*/
/*********************** end of function store_par(*) *************************/
