/* Update: January 20, 2022 */
# define FPRINTF( XX )\
{ \
   if ( XX == 1 ) \
   { \
      if( ppt->xscale == 0 ) \
         strcpy( timestr, \
            dotos( ppt->tt, 5, "e" )); \
      else \
         strcpy( timestr, \
            dotos( ppt->tt*ppt->Ttrm, 5, "e" )); \
 \
      fprintf( pltptr_imn, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == 0 )||( ppt->yunits == 2 )) \
         strcpy( longstr, \
            dotos( immune_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos(( 1.0e+2 )*( immune_upd ), 7, "e" )); \
 \
      fprintf( pltptr_imn, \
         "%12s\n", longstr ); \
 \
      fprintf( pltptr_ifc, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == 0 )||( ppt->yunits == 2 )) \
         strcpy( longstr, \
            dotos( infected_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos(( 1.0e+2 )*( infected_upd ), 7, "e" )); \
 \
      fprintf( pltptr_ifc, \
         "%12s\n", longstr ); \
 \
      if ( ppt->kcic <= kk ) \
      { \
         fprintf( pltptr_cic, \
            "%12s     ", timestr ); \
 \
         if(( ppt->yunits == 0 )||( ppt->yunits == 2 )) \
            strcpy( longstr, \
               dotos( ndays_cic_upd, 7, "e" )); \
         else \
            strcpy( longstr, \
               dotos(( 1.0e+5 )*( ndays_cic_upd ), 7, "e" )); \
 \
         fprintf( pltptr_cic, \
            "%12s\n", longstr ); \
 \
      }; \
 \
      fprintf( pltptr_lty, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == 0 )||( ppt->yunits == 2 )) \
         strcpy( longstr, \
            dotos( lethal_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( ppt->Nhrd*( lethal_upd ), 7, "e" )); \
 \
      fprintf( pltptr_lty, \
         "%12s\n", longstr ); \
 \
      fprintf( pltptr_inc, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == 0 )||( ppt->yunits == 2 )) \
         strcpy( longstr, \
            dotos( ppt->dudt[null], 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos(( 1.0e+5 )*( ppt->dudt[null] ), 7, "e" )); \
 \
      fprintf( pltptr_inc, \
            "%12s\n", longstr ); \
 \
      fprintf( pltptr_rpd, \
         "%12s     ", timestr ); \
 \
      strcpy( longstr, \
         dotos(( reprod_upd ), 7, "e" )); \
      fprintf( pltptr_rpd, \
         "%12s\n", longstr ); \
   }; \
}
