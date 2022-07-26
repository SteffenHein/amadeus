#!/bin/sh
#------------------------------------------------------
REPR=".8600"
APX=""
#------------------------------------------------------
IDX="0"
RATE="0"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="1"
RATE="120"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="2"
RATE="200"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="3"
RATE="300"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="4"
RATE="400"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="5"
RATE="500"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
# current daily vaccination rate, Germany: 54/100000 [ May 20, 2022 ]
IDX="6"
RATE="54"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#------------------------------------------------------------------------------
