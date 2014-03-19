#!/bin/bash
m2s --x86-sim detailed --x86-config cpu-config --mem-config mem-config --x86-debug-call debug.call.threadtest --x86-debug-loader debug.loader.threadtest --x86-debug-isa debug.isa.threadtest --x86-debug-syscall debug.syscall.threadtest --x86-report report.pipeline.threadtest  --trace trace.threadtest.gz threadtest

