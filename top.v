`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/07 13:50:53
// Design Name: 
// Module Name: top
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


module top(
	input wire clk,rst,
	output wire[31:0] writedata,dataadr,
	output wire memwrite
    );

	wire[31:0] pc,instr,readdata,mem_op;

	mips mips(clk,rst,pc,instr,memwrite,dataadr,writedata,mem_op,readdata);
	inst_mem imem(~clk,pc[7:2],instr);
	dmem_wrapper dmem_wrapper(~clk,memwrite,dataadr,writedata,mem_op,readdata);
endmodule
