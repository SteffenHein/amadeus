#!/bin/csh
set init=0
set final=100

set LOG_FILE="par.log"
set INIT_FILE="par.init"
# now iterate

@ i = ${init}
while ( $i <= ${final} )
	if (-f ./${LOG_FILE}$i) then
		echo "copying ${LOG_FILE}$i to ${INIT_FILE}$i" 
#		helios -g -n $i 
 		cp ${LOG_FILE}$i ${INIT_FILE}$i
	endif
	@ i ++
end
#
echo "Done"
