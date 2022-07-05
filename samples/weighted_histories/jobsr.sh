#!/bin/sh
#----------------------------------------------------
REPR="1.060"
APX="r"
#----------------------------------------------------
IDX="0"
RATE="0"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} Vr=${RATE}
#
IDX="1"
RATE="18000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} Vr=${RATE}
#
IDX="2"
RATE="36162"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} Vr=${RATE}
#
IDX="3"
RATE="60000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} Vr=${RATE}
#
IDX="4"
RATE="80000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} Vr=${RATE}
#
IDX="5"
RATE="100000"
#
amadeus -n ${IDX} -f par.init${IDX}${APX}
mv par.log${IDX} par.log${IDX}${APX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} Vr=${RATE}
#
# current daily vaccination rate, Germany: 54/100000 [ May 20, 2022 ]
#
