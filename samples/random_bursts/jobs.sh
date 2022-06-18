#!/bin/sh
#
IDX="0"
REPR="3.000"
BRST="no_bursts"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="1"
REPR="3.000"
BRST="shift_25%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="2"
REPR="3.000"
BRST="shift_50%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="3"
REPR="3.000"
BRST="shift_75%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="4"
REPR="3.000"
BRST="shift_100%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="5"
REPR="3.000"
BRST="shift_125%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="6"
REPR="3.000"
BRST="slats_25%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="7"
REPR="3.000"
BRST="slats_50%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="8"
REPR="3.000"
BRST="slats_75%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="9"
REPR="3.000"
BRST="slats_100%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
#
IDX="10"
REPR="3.000"
BRST="slats_125%"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} ${BRST}
cp inc_R0=${REPR}_job_no_${IDX} inc_${BRST}
