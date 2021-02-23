// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
// Date        : Fri Jan 15 19:45:22 2021
// Host        : DESKTOP-P1D9NJ2 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               f:/verilog2018/DMA_HP4_ila/PL2PS_HP_DMA_Standalone/PL2PS_HP_DMA_Standalone/DMA_pl2ps/DMA_pl2ps.srcs/sources_1/ip/ila_cmd/ila_cmd_stub.v
// Design      : ila_cmd
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "ila,Vivado 2018.2" *)
module ila_cmd(clk, probe0, probe1, probe2, probe3, probe4, probe5, 
  probe6, probe7)
/* synthesis syn_black_box black_box_pad_pin="clk,probe0[31:0],probe1[31:0],probe2[31:0],probe3[31:0],probe4[31:0],probe5[31:0],probe6[31:0],probe7[31:0]" */;
  input clk;
  input [31:0]probe0;
  input [31:0]probe1;
  input [31:0]probe2;
  input [31:0]probe3;
  input [31:0]probe4;
  input [31:0]probe5;
  input [31:0]probe6;
  input [31:0]probe7;
endmodule
