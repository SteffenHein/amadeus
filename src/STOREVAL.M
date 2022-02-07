/* Update: January 22, 2022 */
# define STOREVAL( XX )\
{ \
   if ( XX == 1 ) \
   { \
      if( ppt->xunits == 0 ) \
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
            dotos( infctd_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos(( 1.0e+2 )*( infctd_upd ), 7, "e" )); \
 \
      fprintf( pltptr_ifc, \
         "%12s\n", longstr ); \
 \
      if ( ppt->kcic <= kk ) \
      { \
         fprintf( pltptr_cic, \
            "%12s     ", timestr ); \
 \
         if(( ppt->yunits == 0 ) \
          ||( ppt->yunits == 2 )) \
            strcpy( longstr, \
               dotos( cmlinc_upd, 7, "e" )); \
         else \
            strcpy( longstr, \
               dotos(( 1.0e+5 )*( cmlinc_upd ), 7, "e" )); \
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
            dotos( incidc_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos(( 1.0e+5 )*( incidc_upd ), 7, "e" )); \
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
