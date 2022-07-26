#!/bin/csh
set init=0
set final=100

set LOG_FILE="par.log"
set INIT_FILE="par.init"
set APX="r"
# now iterate

@ i = ${init}
while ( $i <= ${final} )
	if (-f ./${INIT_FILE}$i${APX}) then
		echo "calling amadeus ""$i"
		amadeus -n $i -f ${INIT_FILE}$i${APX}
		cp ${LOG_FILE}$i ${INIT_FILE}$i${APX}
		mv ${LOG_FILE}$i ${LOG_FILE}$i${APX}
	endif
	@ i ++
end
#
echo "Done"
