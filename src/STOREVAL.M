/* Update: Jun 19, 2022 */
# define STOREVAL( XX, YY )\
{ \
   if ((XX) == 1 ) \
   { \
      if( ppt->xunits == null ) \
         strcpy( timestr, \
            dotos( upd->tt, 5, "e" )); \
      else \
         strcpy( timestr, \
            dotos( upd->tt*ppt->Ttrm, 5, "e" )); \
 \
      fprintf( pltptr_imm, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == null ) \
       ||( ppt->yunits == TWO )) \
         strcpy( longstr, \
            dotos( upd->immune, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( 1.0e+02*upd->immune, 7, "e" )); \
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
            dotos( upd->infctd, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( 1.0e+02*upd->infctd, 7, "e" )); \
 \
      fprintf( pltptr_ifc, \
         "%12s\n", longstr ); \
 \
      if (((YY) == 1 ) \
        ||( ppt->kcic <= upd->kk )) \
      { \
         fprintf( pltptr_cic, \
            "%12s     ", timestr ); \
 \
         if(( ppt->yunits == null ) \
          ||( ppt->yunits == TWO )) \
            strcpy( longstr, \
               dotos( upd->cmlinc, 7, "e" )); \
         else \
            strcpy( longstr, \
               dotos( 1.0e+05*upd->cmlinc, 7, "e" )); \
 \
         fprintf( pltptr_cic, \
            "%12s\n", longstr ); \
 \
      }; \
 \
      fprintf( pltptr_vac, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == null ) \
       ||( ppt->yunits == TWO )) \
         strcpy( longstr, \
            dotos( upd->vaccin, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( 1.0e+05*upd->vaccin, 7, "e" )); \
 \
      fprintf( pltptr_vac, \
         "%12s\n", longstr ); \
 \
      fprintf( pltptr_dcd, \
         "%12s     ", timestr ); \
 \
      if(( ppt->yunits == null ) \
       ||( ppt->yunits == TWO )) \
         strcpy( longstr, \
            dotos( upd->lethal, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( ppt->Nhrd*( upd->lethal ), 7, "e" )); \
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
               dotos( upd->incidc, 7, "e" )); \
      else \
         strcpy( longstr, \
            dotos( 1.0e+05*upd->incidc, 7, "e" )); \
 \
      fprintf( pltptr_inc, \
            "%12s\n", longstr ); \
 \
      fprintf( pltptr_rpd, \
         "%12s     ", timestr ); \
 \
      strcpy( longstr, \
         dotos( upd->reprod, 7, "e" )); \
      fprintf( pltptr_rpd, \
         "%12s\n", longstr ); \
   }; \
}
