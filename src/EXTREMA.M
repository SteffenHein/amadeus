/* Update: January 20, 2022 */
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
      if ( cmlinc_upd < ppt->mincic ) \
         ppt->mincic = cmlinc_upd; \
 \
      if ( ppt->maximn < immune_upd ) \
      { \
         ppt->maximn = immune_upd; \
         ppt->tmximn = ppt->tt; \
      }; \
 \
      if ( ppt->minimn > immune_upd ) \
         ppt->minimn = immune_upd; \
 \
      if ( ppt->maxrpd < reprod_upd ) \
      { \
         ppt->maxrpd = reprod_upd; \
         ppt->tmxrpd = ppt->tt; \
      }; \
 \
      if ( ppt->minrpd > reprod_upd ) \
         ppt->minrpd = reprod_upd; \
 \
      if ( ppt->maxifc < infctd_upd ) \
      { \
         ppt->maxifc = infctd_upd; \
         ppt->tmxifc = ppt->tt; \
      }; \
 \
      if ( ppt->maxlty < lethal_upd ) \
         ppt->maxlty = lethal_upd; \
   }; \
}
