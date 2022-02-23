/* Update: February 23, 2022 */
# define EXTREMA(XX)\
{ \
   if ( XX == 1 ) \
   { \
      if ( ppt->maxinc < incidc_upd ) \
      { \
         ppt->maxinc = incidc_upd; \
         ppt->tmxinc = ppt->tt; \
      }; \
 \
      if ( incidc_upd < ppt->mininc ) \
         ppt->mininc = incidc_upd; \
 \
      if ( ppt->maxcic < cmlinc_upd ) \
      { \
         ppt->maxcic = cmlinc_upd; \
         ppt->tmxcic = ppt->tt; \
      }; \
 \
      if (( ppt->kcic <= kk ) \
        &&( cmlinc_upd < ppt->mincic )) \
         ppt->mincic = cmlinc_upd; \
 \
      if ( ppt->maximn < immune_upd ) \
      { \
         ppt->maximn = immune_upd; \
         ppt->tmximn = ppt->tt; \
      }; \
 \
      if ( immune_upd < ppt->minimn ) \
         ppt->minimn = immune_upd; \
 \
      if ( ppt->maxrpd < reprod_upd ) \
      { \
         ppt->maxrpd = reprod_upd; \
         ppt->tmxrpd = ppt->tt; \
      }; \
 \
      if ( reprod_upd < ppt->minrpd ) \
         ppt->minrpd = reprod_upd; \
 \
      if ( ppt->maxifc < infctd_upd ) \
      { \
         ppt->maxifc = infctd_upd; \
         ppt->tmxifc = ppt->tt; \
      }; \
 \
      if ( infctd_upd < ppt->minifc ) \
         ppt->minifc = infctd_upd; \
 \
      if ( ppt->maxlty < lethal_upd ) \
         ppt->maxlty = lethal_upd; \
 \
      if ( lethal_upd < ppt->minlty ) \
         ppt->minlty = lethal_upd; \
   }; \
}
