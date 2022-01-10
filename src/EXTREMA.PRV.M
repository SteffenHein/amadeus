/* Update: January 01, 2022 */
# define EXTREMA(XX)\
{ \
   if ( XX == 1 ) \
   { \
      if ( ppt->maxinc < incidence_upd ) \
      { \
         ppt->maxinc = incidence_upd; \
 \
         if ( ppt->xscale == 0 ) \
            ppt->tmxinc = ppt->tt; \
         else \
            ppt->tmxinc = ppt->tt*ppt->Ttrm; \
      }; \
 \
      if ( incidence_upd < ppt->mininc ) \
         ppt->mininc = incidence_upd; \
 \
      if ( ppt->maxica < ndays_inc_upd ) \
      { \
         ppt->maxica = ndays_inc_upd; \
 \
         if ( ppt->xscale == 0 ) \
            ppt->tmxica = ppt->tt; \
         else \
            ppt->tmxica = ppt->tt*ppt->Ttrm; \
      }; \
 \
      if ( ndays_inc_upd < ppt->minica ) \
         ppt->minica = ndays_inc_upd; \
 \
      if ( ppt->maximn < immune_upd ) \
      { \
         ppt->maximn = immune_upd; \
 \
         if ( ppt->xscale == 0 ) \
            ppt->tmximn = ppt->tt; \
         else \
            ppt->Tmximn = ppt->tt*ppt->Ttrm; \
      }; \
 \
      if ( ppt->maxrpd < reprod_upd ) \
      { \
         ppt->maxrpd = reprod_upd; \
 \
         if ( ppt->xscale == 0 ) \
            ppt->Tmxrpd = ppt->tt; \
         else \
            ppt->Tmxrpd = ppt->tt*ppt->Ttrm; \
      }; \
 \
      if ( ppt->minrpd > reprod_upd ) \
      { \
         ppt->minrpd = reprod_upd; \
      }; \
 \
      if ( ppt->maxifc < infected_upd ) \
      { \
         ppt->maxifc = infected_upd; \
 \
         if ( ppt->xscale == 0 ) \
            ppt->Tmxifc = ppt->tt; \
         else \
            ppt->Tmxifc = ppt->tt*ppt->Ttrm; \
      }; \
 \
      if ( ppt->maxlty < lethal_upd ) \
      { \
         ppt->maxlty = lethal_upd; \
      }; \
   }; \
}
