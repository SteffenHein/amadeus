/* Update: February 15, 2022 */
# define STOREVAL( XX, YY )\
{ \
   if ( XX == 1 ) \
   { \
      if( ppt->xunits == null ) \
         strcpy( timestr, \
            dotos( ppt->tt, 5, "e" )); \
      else \
         strcpy( timestr, \
            dotos( ppt->tt*ppt->Ttrm, 5, "e" )); \
 \
      fprintf( pltptr_imm, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == null ) \
       ||( ppt->yunits == TWO )) \
         strcpy( longstr, \
            dotos( immune_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( 1.0e+02*immune_upd, 7, "e" )); \
 \
      fprintf( pltptr_imm, \
         "%12s\n", longstr ); \
 \
      fprintf( pltptr_ifc, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == null ) \
       ||( ppt->yunits == TWO )) \
         strcpy( longstr, \
            dotos( infctd_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( 1.0e+02*infctd_upd, 7, "e" )); \
 \
      fprintf( pltptr_ifc, \
         "%12s\n", longstr ); \
 \
      if (( YY == 1 ) \
        ||( ppt->kcic <= kk )) \
      { \
         fprintf( pltptr_cic, \
            "%12s     ", timestr ); \
 \
         if(( ppt->yunits == null ) \
          ||( ppt->yunits == TWO )) \
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
      fprintf( pltptr_dcd, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == null ) \
       ||( ppt->yunits == TWO )) \
         strcpy( longstr, \
            dotos( lethal_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( ppt->Nhrd*( lethal_upd ), 7, "e" )); \
 \
      fprintf( pltptr_dcd, \
         "%12s\n", longstr ); \
 \
      fprintf( pltptr_inc, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == null ) \
       ||( ppt->yunits == TWO )) \
         strcpy( longstr, \
               dotos( incidc_upd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( 1.0e+05*incidc_upd, 7, "e" )); \
 \
      fprintf( pltptr_inc, \
            "%12s\n", longstr ); \
 \
      fprintf( pltptr_rpd, \
         "%12s     ", timestr ); \
 \
      strcpy( longstr, \
         dotos( reprod_upd, 7, "e" )); \
      fprintf( pltptr_rpd, \
         "%12s\n", longstr ); \
   }; \
}
