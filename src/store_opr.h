/* [ file: store_opr.h ] */
/*******************************************************************************
*                                                                              *
*  AMADEUS, release v1.0r2                                                     *
*                                                                              *
*  A numerical Model Approximating the Development of Epidemics                *
*  Under homogeneous conditions of Spread                                      *
*                                                                              *
*  Function store_opr(*)                                                       *
*  Stores final operation modes                                                *
*                                                                              *
*  (C) SHEIN; Munich, April 2020                               Steffen Hein    *
*  [ Update: July 04, 2022 ]                                <contact@sfenx.de> *
*                                                                              *
*******************************************************************************/
# include "./STOREOPR.M"
/*----------------------------------------------------------------------------*/
# define RELABEL 0
/*============================================================================*/

short store_opr( char *filename, char mode )
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
      ptr[STS_SIZE+ONE] = {null},
      fleptr[STS_SIZE+ONE] = {null};

   static const char /* dsplay(*) options */
     *scformat = "%80s";

   time_t 
      nseconds = null,
     *timer = NULL;
/*----------------------------------------------------------------------------*/
# if RELABEL == 1 
   static long 
      jj[20] = {null};
      
   static char
      line[20][STS_SIZE] = {{null}};
# endif
/*----------------------------------------------------------------------------*/
/* prototypes: */

   char
      *lotos( long mm, char cc, char *format );
/*----------------------------------------------------------------------------*/
   state = &amdstat;
   opr = &opertns;

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

# if RELABEL == 1
/* example: 

   ii = 12;
   do {
      opr->n[ii] = opr->n[ii-2];
      --ii;
   } while ( 6 < ii );

   jj[1] = opr->n[8];
   strcpy( line[1], opr->ntx[8] );

   jj[2] = opr->n[9];
   strcpy( line[2], opr->ntx[9] );

   jj[3] = opr->n[10];
   strcpy( line[3], opr->ntx[10] );
   
   jj[4] = opr->n[11];
   strcpy( line[4], opr->ntx[11] );

   jj[5] = opr->n[12];
   strcpy( line[5], opr->ntx[12] );

   jj[6] = opr->n[5];
   strcpy( line[6], opr->ntx[5] );

   jj[7] = opr->n[6];
   strcpy( line[7], opr->ntx[6] );

   jj[8] = opr->n[3];
   strcpy( line[8], opr->ntx[3] );

   jj[9] = opr->n[4];
   strcpy( line[9], opr->ntx[4] );

   jj[10] = opr->n[7];
   strcpy( line[10], opr->ntx[7] );

   jj[11] = opr->n[1];
   strcpy( line[11], opr->ntx[1] );

   jj[12] = opr->n[2];
   strcpy( line[12], opr->ntx[2] );

   ii = null; do
   {
      ++ii;
      opr->n[ii] = jj[ii];
      strcpy( opr->ntx[ii], line[ii] );
   } while ( ii < 12 );
*/
# endif
   
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
/*********************** end of function store_opr(*) ******i******************/
