open_project .
set_top des_crypt
add_file des.c
open_solution solution_fpga
add_library  { xilinx/virtex5/virtex5:xc5vlx330:ff1760:-2 }
add_library  { xilinx/virtex5/virtex5_fpv4 }
create_clock -period 10
set_clock_uncertainty 1.25
set_directive_pipeline -II 1 des_crypt/loop_inner
#auto_set_options cbcgen "1"
elaborate
autosyn
