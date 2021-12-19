/* [ file: STOREPAR.M ] */
/* Update: December 19, 2021 */
/*----------------------------------------------------------------------------*/
# define STOREPAR( FN, MD ) \
{ \
   fprintf((FN), "%s\n", ( state->name )); \
   fprintf((FN), "%s\n", ( state->text )); \
   fprintf((FN), "\n%s\n", par->stx[null] ); \
 \
   if (( MD ) == 't' ) \
   { \
      for ( ii=ONE; ii<=parameters; ii++ ) \
      { \
         fprintf((FN), "\n%10.5e  <---  s%03d=%-s", \
            par->s[ii], ii, par->stx[ii] ); \
      }; \
   }  \
   else \
   { \
      for ( ii=ONE; ii<=parameters; ii++ ) \
      { \
         fprintf((FN), "\ns%03d=%s:  % .5e", \
            ii, par->stx[ii], par->s[ii] ); \
      }; \
   }; \
   fprintf((FN), "\n" ); \
}
