set TOP [file rootname [info script]]
# Project settings
delete_project ${TOP}
open_project ${TOP}
add_file segmentation_acc.c
set_top segmentation_acc
# Solution settings
open_solution solution1
config_array_partition -throughput_driven
add_library xilinx/virtex6/virtex6:xc6vlx240t:ff1156:-1
add_library xilinx/virtex6/virtex6_fpv5:xc6vlx240t:ff1156:-1
add_library xilinx/interface/fsl
add_library xilinx/interface/plb46
create_clock -period 10.0ns
set_clock_uncertainty 1.25ns
#############
# SYNTHESIS #
#############
elaborate
autosyn
##############
# SIMULATION #
##############
#autosim -tool riviera -rtl vhdl
#autosim -tb ${TOP}.c -use_gcc -rtl systemc
#####################
# MODULE GENERATION #
#####################
automg --export
