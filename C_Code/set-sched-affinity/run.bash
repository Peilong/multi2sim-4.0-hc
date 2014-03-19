#!/bin/bash
m2s --x86-sim detailed --x86-config cpu-config --mem-config mem-config --x86-debug-call debug.call.cpuaffinity --x86-debug-loader debug.loader.cpuaffinity --x86-debug-isa debug.isa.cpuaffinity --x86-debug-syscall debug.syscall.cpuaffinity --x86-report report.pipeline.cpuaffinity cpuaffinity
