/* Update: January 20, 2022 */
# define EXTREMA(XX)\
{ \
   if ( XX == 1 ) \
   { \
      if ( ppt->maxinc < ppt->dudt[null] ) \
      { \
         ppt->maxinc = ppt->dudt[null]; \
         ppt->tmxinc = ppt->tt; \
      }; \
 \
      if ( ppt->dudt[null] < ppt->mininc ) \
         ppt->mininc = ppt->dudt[null]; \
 \
      if ( ppt->maxcic < ndays_cic_upd ) \
      { \
         ppt->maxcic = ndays_cic_upd; \
         ppt->tmxcic = ppt->tt; \
      }; \
 \
      if ( ndays_cic_upd < ppt->mincic ) \
         ppt->mincic = ndays_cic_upd; \
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
