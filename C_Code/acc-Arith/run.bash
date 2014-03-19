#!/bin/bash

echo "m2s --x86-sim detailed --x86-config 2-cpu-config --mem-config 2-mem-config --x86-report report.pipeline.acc.2 --mem-report report.mem.acc.2 whetstone"
m2s --x86-sim detailed --x86-config 2-cpu-config --mem-config 2-mem-config --x86-report report.pipeline.acc.2 --mem-report report.mem.acc.2 whetstone
