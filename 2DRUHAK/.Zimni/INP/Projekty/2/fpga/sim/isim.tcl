#========================================
# Skript pro simulaci
#========================================

# Spusteni simulace
#========================================
proc isim_script {} {
   # Postupne vlozeni signalu do okna
   add_wave_label "-color #FFFF00" "reset" /testbench/uut/fpga_inst/reset
   add_wave_label "-color #ff8000" "clk" /testbench/uut/fpga_inst/clk
	
   add_divider "RAM"
   add_wave_label "-color #ff8000" "clk" /testbench/uut/fpga_inst/ram_mem/clk
   add_wave_label "-radix hex" "ADDR" /testbench/uut/fpga_inst/ram_mem/addr
   add_wave_label "-radix hex" "WDATA" /testbench/uut/fpga_inst/ram_mem/wdata
   add_wave_label "-radix hex" "RDATA" /testbench/uut/fpga_inst/ram_mem/rdata
   add_wave_label "" "EN" /testbench/uut/fpga_inst/ram_mem/en
   add_wave_label "" "RD/WR" /testbench/uut/fpga_inst/ram_mem/rdwr

   add_divider "ROM"
   add_wave_label "-color #ff8000" "clk" /testbench/uut/fpga_inst/rom_mem/clk
   add_wave_label "-radix hex" "ADDR" /testbench/uut/fpga_inst/rom_mem/addr
   add_wave_label "-radix ascii" "DATA" /testbench/uut/fpga_inst/rom_mem/data
   add_wave_label "" "EN" /testbench/uut/fpga_inst/rom_mem/en
  
   add_divider "I/O - KB"
   add_wave_label "" "REQ" /testbench/uut/fpga_inst/kb_u/data_req
   add_wave_label "" "DATA" /testbench/uut/fpga_inst/kb_u/data
   add_wave_label "" "VLD" /testbench/uut/fpga_inst/kb_u/data_vld

   add_divider "I/O - LCD"
   add_wave_label "" "Display" /testbench/lcd/display

   add_divider "CPU"
   # Vlozeni vsech signalu procesoru
   add_wave "" /testbench/uut/fpga_inst/bfcpu


   # Spusteni simulace
   # Delku simulace lze upravit dle potreb
   run 20 ms
} 


