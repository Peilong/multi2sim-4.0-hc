#!/bin/bash

echo "m2s --x86-config 1-cpu-config --mem-config 1-mem-config --x86-report report.pipeline --mem-report report.mem --x86-sim detailed smithwaterman-only"
m2s --x86-config 1-cpu-config --mem-config 1-mem-config --x86-report report.pipeline --mem-report report.mem --x86-sim detailed smithwaterman-only
