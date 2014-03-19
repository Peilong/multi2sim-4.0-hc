#!/bin/bash
echo "1. Type in a # (You can choose from [2, 4, 8] to set # of CPUs)"
echo "2. Then, press [ENTER]"
echo "Waiting for your input ..."
read -e num
echo "m2s --x86-sim detailed --x86-config $num-cpu-config --mem-config $num-mem-config --x86-report report.pipeline.acc.$num --mem-report report.mem.acc.$num acc"
m2s --x86-sim detailed --x86-config $num-cpu-config --mem-config $num-mem-config --x86-report report.pipeline.acc.$num --mem-report report.mem.acc.$num acc
