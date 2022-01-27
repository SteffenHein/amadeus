#!/bin/sh
gnuplot gpl_n_days_incidence_job.$1
gnuplot gpl_incidence_job.$1
gnuplot gpl_immunity_job.$1
gnuplot gpl_reproduction_job.$1
gnuplot gpl_infection_job.$1
gnuplot gpl_lethality_job.$1
