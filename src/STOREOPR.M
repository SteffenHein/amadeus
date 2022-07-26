/* [ file: STOREOPR.M ] */
/* Update: June 18, 2021 */
/*============================================================================*/
# define STOREOPR( FN, MD ) \
{ \
   fprintf((FN), "%s\n", ( state->name )); \
   fprintf((FN), "%s\n", ( state->text )); \
   fprintf((FN), "\n%s\n", opr->ntx[null] ); \
 \
   if (( MD ) == 't' ) \
   { \
      for ( ii=ONE; ii<=operations; ii++ ) \
      { \
         fprintf(( FN ), "\n%11ld  <---  %s", \
            opr->n[ii], opr->ntx[ii] ); \
      }; \
   } \
   else \
   { \
      for ( ii=ONE; ii<=operations; ii++ ) \
      { \
         fprintf(( FN ), "\nn%02d=%s:  %12ld", ii,\
            opr->ntx[ii], opr->n[ii] ); \
      }; \
   }; \
 \
   fprintf((FN), "\n" ); \
}
/*============================================================================*/
