#!/bin/csh
#
set init=0
set final=100
#
set PLOTFILE="gpl_incidence_job_no_"
# 
@ i = ${init}
while ( $i <= ${final} )
	if (-f ./${PLOTFILE}$i) then
		echo "JOB_no_"$i
#		gnuplot ${PLOTFILE}$i
		gnuplot gpl_n_days_incidence_job_no_$i
		gnuplot gpl_incidence_job_no_$i
		gnuplot gpl_immunity_job_no_$i
		gnuplot gpl_vaccination_job_no_$i
		gnuplot gpl_reproduction_job_no_$i
		gnuplot gpl_deceased_job_no_$i
	endif
	@ i ++
end
#
echo "Done"
