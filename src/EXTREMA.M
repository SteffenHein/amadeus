/* Update: March 16, 2022 */
# define EXTREMA(XX)\
{ \
   if ( XX == 1 ) \
   { \
      if ( ppt->maxinc < upd->incidc ) \
      { \
         ppt->maxinc = upd->incidc; \
         ppt->tmxinc = upd->tt; \
      }; \
 \
      if ( upd->incidc < ppt->mininc ) \
         ppt->mininc = upd->incidc; \
 \
      if ( ppt->maxcic < upd->cmlinc ) \
      { \
         ppt->maxcic = upd->cmlinc; \
         ppt->tmxcic = upd->tt; \
      }; \
 \
      if (( ppt->kcic <= upd->kk ) \
        &&( upd->cmlinc < ppt->mincic )) \
         ppt->mincic = upd->cmlinc; \
 \
      if ( ppt->maximn < upd->immune ) \
      { \
         ppt->maximn = upd->immune; \
         ppt->tmximn = upd->tt; \
      }; \
 \
      if ( upd->immune < ppt->minimn ) \
         ppt->minimn = upd->immune; \
 \
      if ( ppt->maxrpd < upd->reprod ) \
      { \
         ppt->maxrpd = upd->reprod; \
         ppt->tmxrpd = upd->tt; \
      }; \
 \
      if ( upd->reprod < ppt->minrpd ) \
         ppt->minrpd = upd->reprod; \
 \
      if ( ppt->maxifc < upd->infctd ) \
      { \
         ppt->maxifc = upd->infctd; \
         ppt->tmxifc = upd->tt; \
      }; \
 \
      if ( upd->infctd < ppt->minifc ) \
         ppt->minifc = upd->infctd; \
 \
      if ( ppt->maxlty < upd->lethal ) \
         ppt->maxlty = upd->lethal; \
 \
      if ( upd->lethal < ppt->minlty ) \
         ppt->minlty = upd->lethal; \
   }; \
}
