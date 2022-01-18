#!/bin/csh
set init=1
set final=100

set COPIED_FILE="par.log"
set TARGET_FILE="par.init"
set SUFFIX=""
# now iterate

@ i = $init
@ j = $init
while ( $i <= $final )
	if (-f ./$COPIED_FILE$i) then
		echo "copying file $COPIED_FILE$i to $TARGET_FILE$j$SUFFIX"
		cp $COPIED_FILE$i $TARGET_FILE$i$SUFFIX
	endif
	@ i ++
	@ j ++
end
echo "Done"
