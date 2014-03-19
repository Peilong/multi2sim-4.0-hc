#!/bin/bash

echo "m2s --x86-config 2-cpu-config --mem-config 2-mem-config --x86-report report.pipeline --mem-report report.mem --x86-sim detailed jacobi-smithwaterman"
m2s --x86-config 2-cpu-config --mem-config 2-mem-config --x86-report report.pipeline --mem-report report.mem --x86-sim detailed jacobi-smithwaterman
