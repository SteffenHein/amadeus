#!/bin/sh
#----------------------------------------------------
REPR=".8600"
IDX="0"
RATE="0"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="1"
RATE="30"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="2"
RATE="40"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="3"
RATE="50"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="4"
RATE="60"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="5"
RATE="80"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="6"
RATE="100"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="7"
RATE="120"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="8"
RATE="140"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="9"
RATE="150"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="10"
RATE="160"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="11"
RATE="175"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="12"
RATE="180"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="13"
RATE="200"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
#
IDX="14"
RATE="225"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="15"
RATE="250"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="16"
RATE="275"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="17"
RATE="300"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="18"
RATE="350"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="19"
RATE="400"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
IDX="20"
RATE="500"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#
# current daily vaccination rate, Germany: 54/100000 [ May 20, 2022 ]
IDX="21"
RATE="54"
#
amadeus -n ${IDX} -f par.init${IDX}
cp 7_days_incidence_R0=${REPR}_job_no_${IDX} VR=${RATE}
#------------------------------------------------------------------------------
