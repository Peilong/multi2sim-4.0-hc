#!/bin/bash
m2s --x86-sim detailed --x86-config cpu-config --mem-config mem-config --x86-debug-call debug.call.pthreadaffinity --x86-debug-loader debug.loader.pthreadaffinity --x86-debug-isa debug.isa.pthreadaffinity --x86-debug-syscall debug.syscall.pthreadaffinity --x86-report report.pipeline.pthreadaffinity pthread-set-affinity
