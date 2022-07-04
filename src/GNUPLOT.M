/* Update: June 23, 2022 */
# define GNUPLOT( STREAM, FLNAME, PLTFLE, OPTION, XUNIT, YUNIT, YMIN, YMAX ) \
{ \
/* gnuplot headers */ \
 \
   STREAM = fopen( FLNAME, "w+" ); \
 \
   fprintf( STREAM, "%s", \
      "set title '" ); \
   fprintf( STREAM, "%s", OPTION ); \
   fprintf( STREAM, "%s", "'\n" ); \
 \
   fprintf( STREAM, "%s", "set xlabel '" ); \
   fprintf( STREAM, "%s", XUNIT ); \
   fprintf( STREAM, "%s", "'\n" ); \
   fprintf( STREAM, "%s", "set xrange [ " ); \
   strcpy( longstr, dotos( ZERO, 7, "e" )); \
   fprintf( STREAM, "%s", longstr ); \
   fprintf( STREAM, "%s", " : " ); \
 \
   if ( ppt->xunits == null ) \
      strcpy( longstr, dotos( 1.0000*upd->tt, 7, "e" )); \
   else \
      strcpy( longstr, dotos( 1.0000*upd->tt*ppt->Ttrm, 7, "e" )); \
 \
   fprintf( STREAM, "%s", longstr ); \
   fprintf( STREAM, "%s", " ]\n" ); \
 \
   fprintf( STREAM, "%s", "set ylabel '" ); \
   fprintf( STREAM, "%s", YUNIT ); \
   fprintf( STREAM, "%s", "'\n" ); \
   fprintf( STREAM, "%s", "set format y '%10.2e'\n" ); \
 \
   if ( ppt->yscale == 1 ) /* y scale: logarithmic */ \
      fprintf( STREAM, "%s", "set logscale y 10\n" ); \
 \
   fprintf( STREAM, "%s", "set yrange [ " ); \
   strcpy( longstr, dotos( YMIN , 7, "e" )); \
   fprintf( STREAM, "%s", longstr ); \
   fprintf( STREAM, "%s", " : " ); \
   strcpy( longstr, dotos( YMAX, 7, "e" )); \
   fprintf( STREAM, "%s", longstr ); \
   fprintf( STREAM, "%s", " ]\n" ); \
 \
   fprintf( STREAM, "%s", "#\n" ); \
   fprintf( STREAM, "# set label '*****'%c\n", 92 ); \
   strcpy( longstr, "# at " ); \
   strcat( longstr, dotos(( 1.0e-01*upd->tt ), 7, "e" )); \
   strcat( longstr, ", "); \
   strcat( longstr, dotos(( YMIN + .95*( YMAX -YMIN )), 7, "e" )); \
   fprintf( STREAM, "%s\n", longstr ); \
 \
   fprintf( STREAM, "# set label '*****'%c\n", 92 ); \
   strcpy( longstr, "# at " ); \
   strcat( longstr, dotos(( 1.0e-01*upd->tt ), 7, "e" )); \
   strcat( longstr, ", "); \
   strcat( longstr, dotos(( YMIN + .9*( YMAX -YMIN )), 7, "e" )); \
   fprintf( STREAM, "%s\n", longstr ); \
 \
   fprintf( STREAM, "# set label '*****'%c\n", 92 ); \
   strcpy( longstr, "# at " ); \
   strcat( longstr, dotos(( 1.0e-01*upd->tt ), 7, "e" )); \
   strcat( longstr, ", "); \
   strcat( longstr, dotos(( YMIN + .85*( YMAX -YMIN )), 7, "e" )); \
   fprintf( STREAM, "%s\n", longstr ); \
 \
   fprintf( STREAM, "# set label '*****'%c\n", 92 ); \
   strcpy( longstr, "# at " ); \
   strcat( longstr, dotos(( 1.0e-01*upd->tt ), 7, "e" )); \
   strcat( longstr, ", "); \
   strcat( longstr, dotos(( YMIN + .8*( YMAX -YMIN )), 7, "e" )); \
   fprintf( STREAM, "%s\n", longstr ); \
   fprintf( STREAM, "%s", "#\n" ); \
 \
   fprintf( STREAM, "%s", "set grid\n" ); \
   fprintf( STREAM, "%s", "set border\n" ); \
   fprintf( STREAM, "%s", "set key box\n" ); \
   fprintf( STREAM, "%s", "set pointsize 0.2\n" ); \
   fprintf( STREAM, "%s", "plot \\\n" ); \
   fprintf( STREAM, "'%s'", PLTFLE ); \
   fprintf( STREAM, "%s", " with lines\n" ); \
   fprintf( STREAM, "%s", "pause -1 '[ hit return to continue ]'\n" ); \
 \
   fclose( STREAM ); \
};
