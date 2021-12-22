/* [ file: store_opr.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r1                                                     *
*                                                                              *
*  A simple numerical Model Approximating the Development of Epidemics         *
*  Under varied conditions if Spread                                           *
*                                                                              *
*  Function store_opr(*)                                                       *
*  Stores final operation modes                                                *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: December 19, 2021 ]                            <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# include "./STOREOPR.M"
/*============================================================================*/

short store_operts( char *filename, char mode )
{
/* declarations: */

   static AMDSTATE
     *state = &amdstat;

   static OPERTNS
     *opr = &opertns;

   static FILE 
     *operatns = NULL;

   static long 
      ll = null;

   static short
      ii = null,
      operations = null;

   static char
     *timeptr = NULL,
      ptr[STS_SIZE] = {null},
      fleptr[STS_SIZE] = {null};

   static const char /* dsplay(*) options */
     *scformat = "%80s";

   time_t 
      nseconds = null,
     *timer = NULL;

   char
      *lotos( long mm, char cc, char *format );
/*----------------------------------------------------------------------------*/
   strcpy( fleptr, filename );
   operatns = fopen( fleptr, "w+" );  /* save actual options on log file */

   ii = null;
   while ( ii < IPT_MAXLBL )
   {
      fscanf( operatns, scformat, ptr );

      if ( null == strncmp( ptr, "OPERATIONS", FIVE ))
      {
         ll = ftell( operatns ) + ONE;
         break;
      }
      else
      {
         ii++;
         if ( ii == IPT_MAXLBL )
         {
            if ( mode == 't' ) /* temporary file */
            { 
               fprintf( operatns, "%s\n", "The actually charged" );
                 fprintf( operatns,
                  "%s%s\n", "--> OPERATIONS-", \
		   lotos(( state->job ), null, " " ));
            }
            else
               fprintf( operatns,
                  "%s%s\n", "OPERATIONS-", lotos(( state->job ), null, " " ));

            ll = ftell( operatns );
         };
      };
   };
   
   fseek( operatns, ll, SEEK_SET );
   operations = ( short ) opr->n[null]; /* the number of parameters */
/*............................................................................*/
   STOREOPR( operatns, mode );
/*............................................................................*/
   if ( mode == 'o' )
   {
      nseconds = time( timer );
      timeptr = ctime( &nseconds );

      fprintf( operatns, "\nAMADEUS operations logfile %s created:", fleptr );
      fprintf( operatns, "\n%.24s", timeptr );
      fprintf( operatns, "\n%c", EOF );
   };

   fclose( operatns );
   return null;
}
/*============================================================================*/
/********************* end of function store_operts(*) ************************/
