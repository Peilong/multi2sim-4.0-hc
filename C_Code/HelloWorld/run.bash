#!/bin/bash

echo "m2s --x86-config 1-cpu-config --mem-config 1-mem-config --x86-report report.pipeline --mem-report report.mem --mem-debug debug.mem --x86-sim detailed hello"
m2s --x86-config 1-cpu-config --mem-config 1-mem-config --x86-report report.pipeline --mem-report report.mem --mem-debug debug.mem --x86-sim detailed hello
