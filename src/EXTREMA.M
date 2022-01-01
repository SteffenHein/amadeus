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
            ppt->Tmxinc = ppt->tt; \
         else \
            ppt->Tmxinc = ppt->tt*ppt->Ttrm; \
      }; \
 \
      if ( incidence_upd < ppt->mininc ) \
         ppt->mininc = incidence_upd; \
 \
      if ( ppt->maxacu < acute_upd ) \
      { \
         ppt->maxacu = acute_upd; \
 \
         if ( ppt->xscale == 0 ) \
            ppt->Tmxacu = ppt->tt; \
         else \
            ppt->Tmxacu = ppt->tt*ppt->Ttrm; \
      }; \
 \
      if ( acute_upd < ppt->minacu ) \
         ppt->minacu = acute_upd; \
 \
      if ( ppt->maximn < immune_upd ) \
      { \
         ppt->maximn = immune_upd; \
 \
         if ( ppt->xscale == 0 ) \
            ppt->Tmximn = ppt->tt; \
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
