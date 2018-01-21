# sim.tcl : ISIM simulation script
# Copyright (C) 2011 Brno University of Technology,
#                    Faculty of Information Technology
# Author(s): Michal Bidlo
#
# LICENSE TERMS
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. All advertising materials mentioning features or use of this software
#    or firmware must display the following acknowledgement:
#
#      This product includes software developed by the University of
#      Technology, Faculty of Information Technology, Brno and its
#      contributors.
#
# 4. Neither the name of the Company nor the names of its contributors
#    may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# This software or firmware is provided ``as is'', and any express or implied
# warranties, including, but not limited to, the implied warranties of
# merchantability and fitness for a particular purpose are disclaimed.
# In no event shall the company or contributors be liable for any
# direct, indirect, incidental, special, exemplary, or consequential
# damages (including, but not limited to, procurement of substitute
# goods or services; loss of use, data, or profits; or business
# interruption) however caused and on any theory of liability, whether
# in contract, strict liability, or tort (including negligence or
# otherwise) arising in any way out of the use of this software, even
# if advised of the possibility of such damage.
#

#Project setup
#========================================
#set TESTBENCH_ENTITY "testbench"
#set ISIM_PRECISION "1 ps"

#Run simulation
#========================================
proc isim_script {} {

   add_divider "8x8 LED CONTROL"
   add_wave_label "" "RESET" /testbench/uut/reset
   add_wave_label "-color #ff8000" "SMCLK" /testbench/uut/smclk
   add_wave_label "" "ROW" /testbench/uut/row
   add_wave_label "" "LED" /testbench/uut/led

   # S timto se odsimuluje postupna aktivace vsech radku displeje po resetu,
   # pro f(SMCLK) = 7.3728 MHz, delic(SMCLK) = 256 pro aktivaci jednoho radku,
   # mame 8 radku displeje, tj. t(sim) = 1/f(SMCLK) * 256 * 8 = 277,7777... us.
   run 278 us
}
