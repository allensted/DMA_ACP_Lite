// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
// Date        : Thu Jan 14 18:13:40 2021
// Host        : DESKTOP-P1D9NJ2 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               f:/verilog2018/PL2PS_HP_DMA_Standalone/PL2PS_HP_DMA_Standalone/DMA_pl2ps/DMA_pl2ps.srcs/sources_1/ip/ila_HP0_write/ila_HP0_write_stub.v
// Design      : ila_HP0_write
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "ila,Vivado 2018.2" *)
module ila_HP0_write(clk, probe0, probe1)
/* synthesis syn_black_box black_box_pad_pin="clk,probe0[0:0],probe1[31:0]" */;
  input clk;
  input [0:0]probe0;
  input [31:0]probe1;
endmodule
