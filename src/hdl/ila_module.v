`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/01/15 19:16:06
// Design Name: 
// Module Name: ila_module
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ila_module
   (
    DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb);
 
  inout [14:0]DDR_addr;
  inout [2:0]DDR_ba;
  inout DDR_cas_n;
  inout DDR_ck_n;
  inout DDR_ck_p;
  inout DDR_cke;
  inout DDR_cs_n;
  inout [3:0]DDR_dm;
  inout [31:0]DDR_dq;
  inout [3:0]DDR_dqs_n;
  inout [3:0]DDR_dqs_p;
  inout DDR_odt;
  inout DDR_ras_n;
  inout DDR_reset_n;
  inout DDR_we_n;
  inout FIXED_IO_ddr_vrn;
  inout FIXED_IO_ddr_vrp;
  inout [53:0]FIXED_IO_mio;
  inout FIXED_IO_ps_clk;
  inout FIXED_IO_ps_porb;
  inout FIXED_IO_ps_srstb;


  wire CLK_dma;
  wire [14:0]DDR_addr;
  wire [2:0]DDR_ba;
  wire DDR_cas_n;
  wire DDR_ck_n;
  wire DDR_ck_p;
  wire DDR_cke;
  wire DDR_cs_n;
  wire [3:0]DDR_dm;
  wire [31:0]DDR_dq;
  wire [3:0]DDR_dqs_n;
  wire [3:0]DDR_dqs_p;
  wire DDR_odt;
  wire DDR_ras_n;
  wire DDR_reset_n;
  wire DDR_we_n;
  wire FIXED_IO_ddr_vrn;
  wire FIXED_IO_ddr_vrp;
  wire [53:0]FIXED_IO_mio;
  wire FIXED_IO_ps_clk;
  wire FIXED_IO_ps_porb;
  wire FIXED_IO_ps_srstb;
  wire [31:0]axis_HP0_read_data_tdata;
  wire [3:0]axis_HP0_read_data_tkeep;
  wire axis_HP0_read_data_tlast;
  wire axis_HP0_read_data_tready;
  wire axis_HP0_read_data_tvalid;
  wire [31:0]axis_HP0_write_data_tdata;
  wire [3:0]axis_HP0_write_data_tkeep;
  wire axis_HP0_write_data_tlast;
  wire axis_HP0_write_data_tready;
  wire axis_HP0_write_data_tvalid;
  wire [31:0]axis_HP1_read_data_tdata;
  wire [3:0]axis_HP1_read_data_tkeep;
  wire axis_HP1_read_data_tlast;
  wire axis_HP1_read_data_tready;
  wire axis_HP1_read_data_tvalid;
  wire [31:0]axis_HP1_write_data_tdata;
  wire [3:0]axis_HP1_write_data_tkeep;
  wire axis_HP1_write_data_tlast;
  wire axis_HP1_write_data_tready;
  wire axis_HP1_write_data_tvalid;
  wire [31:0]axis_HP2_read_data_tdata;
  wire [3:0]axis_HP2_read_data_tkeep;
  wire axis_HP2_read_data_tlast;
  wire axis_HP2_read_data_tready;
  wire axis_HP2_read_data_tvalid;
  wire [31:0]axis_HP2_write_data_tdata;
  wire [3:0]axis_HP2_write_data_tkeep;
  wire axis_HP2_write_data_tlast;
  wire axis_HP2_write_data_tready;
  wire axis_HP2_write_data_tvalid;
  wire [31:0]axis_HP3_read_data_tdata;
  wire [3:0]axis_HP3_read_data_tkeep;
  wire axis_HP3_read_data_tlast;
  wire axis_HP3_read_data_tready;
  wire axis_HP3_read_data_tvalid;
  wire [31:0]axis_HP3_write_data_tdata;
  wire [3:0]axis_HP3_write_data_tkeep;
  wire axis_HP3_write_data_tlast;
  wire axis_HP3_write_data_tready;
  wire axis_HP3_write_data_tvalid;
  wire [31:0]i_CMD_reg0_0;
  wire [31:0]i_CMD_reg1_0;
  wire [31:0]i_CMD_reg2_0;
  wire [31:0]i_CMD_reg3_0;
  wire [31:0]i_CMD_reg4_0;
  wire [31:0]i_CMD_reg5_0;
  wire [31:0]i_CMD_reg6_0;
  wire [31:0]i_CMD_reg7_0;
  wire [31:0]o_CMD_reg0_0;
  wire [31:0]o_CMD_reg1_0;
  wire [31:0]o_CMD_reg2_0;
  wire [31:0]o_CMD_reg3_0;
  wire [31:0]o_CMD_reg4_0;
  wire [31:0]o_CMD_reg5_0;
  wire [31:0]o_CMD_reg6_0;
  wire [31:0]o_CMD_reg7_0;
  wire [0:0]peripheral_aresetn;

  system system_i
       (.CLK_dma(CLK_dma),
        .DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
        .axis_HP0_read_data_tdata(2),
        .axis_HP0_read_data_tkeep(axis_HP0_read_data_tkeep),
        .axis_HP0_read_data_tlast(axis_HP0_read_data_tlast),
        .axis_HP0_read_data_tready(axis_HP0_read_data_tready),
        .axis_HP0_read_data_tvalid(1),
        .axis_HP0_write_data_tdata(axis_HP0_write_data_tdata),
        .axis_HP0_write_data_tkeep(axis_HP0_write_data_tkeep),
        .axis_HP0_write_data_tlast(axis_HP0_write_data_tlast),
        .axis_HP0_write_data_tready(1),
        .axis_HP0_write_data_tvalid(axis_HP0_write_data_tvalid),
        .axis_HP1_read_data_tdata(axis_HP1_read_data_tdata),
        .axis_HP1_read_data_tkeep(axis_HP1_read_data_tkeep),
        .axis_HP1_read_data_tlast(axis_HP1_read_data_tlast),
        .axis_HP1_read_data_tready(axis_HP1_read_data_tready),
        .axis_HP1_read_data_tvalid(axis_HP1_read_data_tvalid),
        .axis_HP1_write_data_tdata(axis_HP1_write_data_tdata),
        .axis_HP1_write_data_tkeep(axis_HP1_write_data_tkeep),
        .axis_HP1_write_data_tlast(axis_HP1_write_data_tlast),
        .axis_HP1_write_data_tready(1),
        .axis_HP1_write_data_tvalid(axis_HP1_write_data_tvalid),
        .axis_HP2_read_data_tdata(axis_HP2_read_data_tdata),
        .axis_HP2_read_data_tkeep(axis_HP2_read_data_tkeep),
        .axis_HP2_read_data_tlast(axis_HP2_read_data_tlast),
        .axis_HP2_read_data_tready(axis_HP2_read_data_tready),
        .axis_HP2_read_data_tvalid(axis_HP2_read_data_tvalid),
        .axis_HP2_write_data_tdata(axis_HP2_write_data_tdata),
        .axis_HP2_write_data_tkeep(axis_HP2_write_data_tkeep),
        .axis_HP2_write_data_tlast(axis_HP2_write_data_tlast),
        .axis_HP2_write_data_tready(1),
        .axis_HP2_write_data_tvalid(axis_HP2_write_data_tvalid),
        .axis_HP3_read_data_tdata(axis_HP3_read_data_tdata),
        .axis_HP3_read_data_tkeep(axis_HP3_read_data_tkeep),
        .axis_HP3_read_data_tlast(axis_HP3_read_data_tlast),
        .axis_HP3_read_data_tready(axis_HP3_read_data_tready),
        .axis_HP3_read_data_tvalid(axis_HP3_read_data_tvalid),
        .axis_HP3_write_data_tdata(axis_HP3_write_data_tdata),
        .axis_HP3_write_data_tkeep(axis_HP3_write_data_tkeep),
        .axis_HP3_write_data_tlast(axis_HP3_write_data_tlast),
        .axis_HP3_write_data_tready(1),
        .axis_HP3_write_data_tvalid(axis_HP3_write_data_tvalid),
        .i_CMD_reg0_0(1),
        .i_CMD_reg1_0(2),
        .i_CMD_reg2_0(3),
        .i_CMD_reg3_0(4),
        .i_CMD_reg4_0(5),
        .i_CMD_reg5_0(6),
        .i_CMD_reg6_0(7),
        .i_CMD_reg7_0(8),
        .o_CMD_reg0_0(o_CMD_reg0_0),
        .o_CMD_reg1_0(o_CMD_reg1_0),
        .o_CMD_reg2_0(o_CMD_reg2_0),
        .o_CMD_reg3_0(o_CMD_reg3_0),
        .o_CMD_reg4_0(o_CMD_reg4_0),
        .o_CMD_reg5_0(o_CMD_reg5_0),
        .o_CMD_reg6_0(o_CMD_reg6_0),
        .o_CMD_reg7_0(o_CMD_reg7_0),
        .peripheral_aresetn(peripheral_aresetn));
		
ila_HP0_write ila_HP0_write_ins (
	.clk(CLK_dma), // input wire clk


	.probe0(axis_HP0_write_data_tvalid), // input wire [0:0]  probe0  
	.probe1(axis_HP0_write_data_tdata) // input wire [31:0]  probe1
);

ila_HP0_write ila_HP1_write_ins (
	.clk(CLK_dma), // input wire clk


	.probe0(axis_HP1_write_data_tvalid), // input wire [0:0]  probe0  
	.probe1(axis_HP1_write_data_tdata) // input wire [31:0]  probe1
);

ila_HP0_write ila_HP2_write_ins (
	.clk(CLK_dma), // input wire clk


	.probe0(axis_HP2_write_data_tvalid), // input wire [0:0]  probe0  
	.probe1(axis_HP2_write_data_tdata) // input wire [31:0]  probe1
);

ila_HP0_write ila_HP3_write_ins (
	.clk(CLK_dma), // input wire clk


	.probe0(axis_HP3_write_data_tvalid), // input wire [0:0]  probe0  
	.probe1(axis_HP3_write_data_tdata) // input wire [31:0]  probe1
);

ila_cmd ila_cmd_ins (
	.clk(CLK_dma), // input wire clk


	.probe0(o_CMD_reg0_0), // input wire [31:0]  probe0  
	.probe1(o_CMD_reg1_0), // input wire [31:0]  probe1 
	.probe2(o_CMD_reg2_0), // input wire [31:0]  probe2 
	.probe3(o_CMD_reg3_0), // input wire [31:0]  probe3 
	.probe4(o_CMD_reg4_0), // input wire [31:0]  probe4 
	.probe5(o_CMD_reg5_0), // input wire [31:0]  probe5 
	.probe6(o_CMD_reg6_0), // input wire [31:0]  probe6 
	.probe7(o_CMD_reg7_0) // input wire [31:0]  probe7
);

endmodule


