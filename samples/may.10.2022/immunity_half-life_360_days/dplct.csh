#!/bin/csh
set ii_init=0
set jj_init=0
set final=100

set COPIED_FILE="par.log"
set TARGET_FILE="par.init"
set SUFFIX=""
# now iterate

@ ii = $ii_init
@ jj = $jj_init
while ( ${ii} <= $final )
   if (-f ./$COPIED_FILE${ii}) then
      echo "copying file $COPIED_FILE${ii} to $TARGET_FILE${jj}$SUFFIX"
      cp $COPIED_FILE${ii} $TARGET_FILE${jj}$SUFFIX
   endif
   @ ii ++
   @ jj ++
end
echo "Done"
