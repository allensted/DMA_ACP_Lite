`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/02/04 10:31:18
// Design Name: 
// Module Name: cnt0
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
parameter N=100;  // set it a small number just for the test

module cnt0(valid,clk,finish,tim,rst_n);
    input valid;
    input clk;
    input rst_n;
    output finish;
    output [31:0]tim;
        
        

    reg [31:0]val_r;
    reg [31:0]clk_r;
    reg finish_r;



    always @(posedge clk)
    begin
    if(!rst_n)
    begin       
        val_r <= 32'd0;
        clk_r <= 32'd0;
        finish_r <= 1'b0;
    end
    else
        begin
        if( (val_r > 0) && (val_r < N) )
            clk_r <= clk_r + 1'b1;
        
        else if(val_r >= N)      
            finish_r <= 1'b1;
        end
    end
   
    always@(posedge clk) 
    begin
    if(!rst_n)
            val_r <= 32'd0;
    else
        val_r <= val_r + 1'b1;
    end
    
    assign  finish = finish_r;
    assign  tim = clk_r;


endmodule