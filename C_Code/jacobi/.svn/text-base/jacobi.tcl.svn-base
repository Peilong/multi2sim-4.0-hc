#===-- enc83/autopilot.tcl --
# 
# Description: A script for demo autopilot simple project.
# 
# Copyright (C) 2006-2007 AutoESL Design Technologies, Inc.
# AutoESL Confidential. All rights reserved.
#
#===--
open_project .
set_top jacob
add_file jacobi.c
open_solution jacobi
add_library  { xilinx/virtex5/virtex5:xc5vsx240t:ff1738:-2 }
add_library  { xilinx/virtex5/virtex5_fpv4 }
create_clock -period 7.5
set_clock_uncertainty 1.25
#config_autosim  
#config_chip_info  -resource "{SLICE 24320} {LUT 48640 } {FF 48640 } {DSP48E 128 } {BRAM 192}" -speed "slow" 

######   PLEASE DO NOT EDIT ABOVE THIS LINE   ###################

######   Insert your constraints / commands here #########
#add_library "/common/software/autopilot/autopilot_2010.02.ft_Linux/common/technology/xilinx/interface/plb46"
#add_library "xilinx/interface/plb46"
set_directive_dependence -class array -dependent false do_rotate/ROTATE_L2
set_directive_dependence -class array -dependent false do_rotate/ROTATE_L3
set_directive_pipeline -II 1  do_rotate/ROTATE_L1
set_directive_pipeline -II 1  do_rotate/ROTATE_L2
set_directive_pipeline -II 1  do_rotate/ROTATE_L3
set_directive_pipeline -II 1  do_rotate/ROTATE_L4


######   PLEASE DO NOT EDIT BELOW THIS LINE   ###################
#set_directive_interface -mode ap_bus burst_top x0
#auto_set_options cbcgen "1"
elaborate
autosyn



