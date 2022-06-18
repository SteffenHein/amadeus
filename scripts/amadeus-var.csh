#!/bin/csh
set init=0
set final=100

set LOG_FILE="par.log"
set INIT_FILE="par.init"
set IDX="r"
# now iterate

@ i = ${init}
while ( $i <= ${final} )
	if (-f ./${INIT_FILE}$i${IDX}) then
		echo "calling amadeus ""$i"
		amadeus -n $i -f ${INIT_FILE}$i${IDX}
		cp ${LOG_FILE}$i ${INIT_FILE}$i${IDX}
	endif
	@ i ++
end
#
echo "Done"
