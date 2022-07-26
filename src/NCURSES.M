/*----------------------------------------------------------------------------*/
# if USE_NCURSES == 1
   # include <ncurses.h>
   # include <termcap.h>     /* terminal type header */

   # ifndef CLSCREEN
      # define CLSCREEN { \
        fprintf( stdout, "%s", tgetstr( "cl", null )); \
      }
   # endif
   # ifndef PRBLDCLR
      # define PRBLDCLR(a) {\
        fprintf( stdout, \
           "%s%s", tgetstr( "md", null ), (a)); /* bold clear output */ \
      }
   # endif
   # ifndef PRINVERS
      # define PRINVERS(a) {\
        fprintf( stdout, \
           "%s%s", tgetstr( "mr", null ), (a)); /* inverse */ \
      }
   # endif
   # ifndef PRNORMAL
      # define PRNORMAL(a) {\
        fprintf( stdout, \
           "%s%s", tgetstr( "me", null ), (a)); /* back to normal output */ \
      }
   # endif
# else /* if USE_NCURSES != 1 */
   # ifndef CLSCREEN
      # define CLSCREEN { \
        fprintf( stdout, "\f" ); \
      }
   # endif
   # ifndef PRBLDCLR
      # define PRBLDCLR(a) {\
        fprintf( stdout, "%s", (a));\
      }
   # endif
   # ifndef PRINVERS
      # define PRINVERS(a) {\
        fprintf( stdout, "%s", (a));\
      }
   # endif
   # ifndef PRNORMAL
      # define PRNORMAL(a) {\
        fprintf( stdout, "%s", (a));\
      }
   # endif
# endif /* USE_NCURSES != 1 */
