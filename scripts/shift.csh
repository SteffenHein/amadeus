#!/bin/csh
set init1=10
set init2=20
set final=1

set COPIED_FILE="par.init"
set TARGET_FILE="par.init"
set SUFFIX=""
# now iterate

@ i = $init1
@ j = $init2
while ( $final <= $i )
	if (-f ./$COPIED_FILE$i) then
		echo "copying file $COPIED_FILE$i to $TARGET_FILE$j$SUFFIX"
		cp $COPIED_FILE$i $TARGET_FILE$j$SUFFIX
	endif
	@ i --
	@ j --
end
echo "Done"
