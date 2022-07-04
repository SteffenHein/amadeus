/* [ file: STOREPAR.M ] */
/* Update: June 29, 2022 */
/*============================================================================*/
# define STOREPAR( FN, MD ) \
{ \
   fprintf((FN), "%s\n", ( state->name )); \
   fprintf((FN), "%s\n", ( state->text )); \
   fprintf((FN), "\n%s", "Initial_values_and_constants" ); \
   fprintf((FN), "\n%s\n", par->stx[null] ); \
 \
   if ((MD) == 't' ) \
   { \
      ii = null; \
      while ( ii < parameters ) \
      { \
         ++ii; \
         fprintf((FN), "\n%10.6e  <--- %-s", \
            par->s[ii], par->stx[ii] ); \
      }; \
   } \
   else \
   { \
      ii = null; \
      while ( ii < parameters ) \
      { \
         ++ii; \
         fprintf((FN), "\ns%02d=%s:  % .5e", \
            ii, par->stx[ii], par->s[ii] ); \
      }; \
   }; \
   fprintf((FN), "\n" ); \
}
/*============================================================================*/
