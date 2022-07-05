#!/bin/sh
#----------------------------------------------------
REPR="1.060"
APX=""
#----------------------------------------------------
#
IDX="0"
RATE="0"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="1"
RATE="18000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="2"
RATE="36162"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="3"
RATE="60000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="4"
RATE="80000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="5"
RATE="100000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="6"
RATE="120000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="7"
RATE="140000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="8"
RATE="160000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
# mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
