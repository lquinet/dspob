onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /top_level/AUDIO_LENGTH
add wave -noupdate /top_level/adc_left_reg_i
add wave -noupdate /top_level/adc_right_reg_i
add wave -noupdate /top_level/adcdat_in
add wave -noupdate /top_level/adclrc_in
add wave -noupdate /top_level/bclk_in
add wave -noupdate /top_level/clk_in
add wave -noupdate /top_level/dacdat_out
add wave -noupdate /top_level/daclrc_in
add wave -noupdate /top_level/reset_in
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {30132000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 154
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {29754780 ps} {42682380 ps}
