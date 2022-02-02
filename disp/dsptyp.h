/* [ file: dsptyp.h ] */
/* Update: December 19, 2021 */
/*----------------------------------------------------------------------------*/

typedef struct
{
   char 
      rtn;

   char 
      option,
      messge[LGS_SIZE];

   short
      rcsps; /* relative curser position */
   
   long
      fleps, /* file position pointer [ fleps = ftell(*) etc. ] */
      state,
      range;

   FILE 
     *display;

} DSPLAY;
/*************************** end of file dsptyp.h *****************************/
