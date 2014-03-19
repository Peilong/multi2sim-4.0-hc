#!/bin/bash
m2s --x86-sim detailed --x86-config cpu-config --mem-config mem-config --x86-debug-call debug.call.threadaffinity --x86-debug-loader debug.loader.threadaffinity --x86-debug-isa debug.isa.threadaffinity --x86-debug-syscall debug.syscall.threadaffinity --x86-report report.pipeline.threadaffinity --trace trace.threadaffinity.gz threadaffinity

