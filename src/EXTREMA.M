/* Update: January 10, 2022 */
# define EXTREMA(XX)\
{ \
   if ( XX == 1 ) \
   { \
      if ( ppt->maxinc < incidence_upd ) \
      { \
         ppt->maxinc = incidence_upd; \
         ppt->tmxinc = ppt->tt; \
      }; \
 \
      if ( incidence_upd < ppt->mininc ) \
         ppt->mininc = incidence_upd; \
 \
      if ( ppt->maxica < ndays_inc_upd ) \
      { \
         ppt->maxica = ndays_inc_upd; \
         ppt->tmxica = ppt->tt; \
      }; \
 \
      if ( ndays_inc_upd < ppt->minica ) \
         ppt->minica = ndays_inc_upd; \
 \
      if ( ppt->maximn < immune_upd ) \
      { \
         ppt->maximn = immune_upd; \
         ppt->tmximn = ppt->tt; \
      }; \
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
      if ( ppt->maxifc < infected_upd ) \
      { \
         ppt->maxifc = infected_upd; \
         ppt->tmxifc = ppt->tt; \
      }; \
 \
      if ( ppt->maxlty < lethal_upd ) \
         ppt->maxlty = lethal_upd; \
   }; \
}
