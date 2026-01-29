`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/07 10:58:03
// Design Name: 
// Module Name: mips
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


module mips(
	input wire clk,rst,
	output wire[31:0] pcF,
	input wire[31:0] instrF,
	output wire memwriteM,
	output wire[31:0] aluoutM,writedataM,
	input wire[31:0] readdataM 
);
	
	wire [5:0] opD,functD;
	wire [4:0] rtD;
	wire [2:0] branch_opD;
	wire regdstE,alusrcE,pcsrcD,memtoregE,memtoregM,memtoregW,
			regwriteE,regwriteM,regwriteW;
	wire [2:0] alucontrolE;
	wire flushE,equalD;
	wire branchD,jumpD,jumpregD;  // ← 添加 jumpregD
	wire linkE, linkM, linkW;
	wire jalrE, jalrM, jalrW;  // ← 添加

	controller c(
		clk,rst,
		//decode stage
		opD,functD,
		rtD,
		pcsrcD,branchD,
		branch_opD,
		equalD,jumpD,
		jumpregD,  // ← 添加输出
		
		//execute stage
		flushE,
		memtoregE,alusrcE,
		regdstE,regwriteE,	
		linkE,
		jalrE,  // ← 添加
		alucontrolE,

		//mem stage
		memtoregM,memwriteM,
		regwriteM,
		linkM,
		jalrM,  // ← 添加
		//write back stage
		memtoregW,regwriteW,
		linkW,
		jalrW  // ← 添加
	);
	
	datapath dp(
		clk,rst,
		//fetch stage
		pcF,
		instrF,
		//decode stage
		pcsrcD,branchD,
		branch_opD,
		jumpD,
		jumpregD,  // ← 添加输入
		equalD,
		opD,functD,
		rtD,
		//execute stage
		memtoregE,
		alusrcE,regdstE,
		regwriteE,
		linkE,
		jalrE,  // ← 添加
		alucontrolE,
		flushE,
		//mem stage
		memtoregM,
		regwriteM,
		linkM,
		jalrM,  // ← 添加
		aluoutM,writedataM,
		readdataM,
		//writeback stage
		memtoregW,
		regwriteW,
		linkW,
		jalrW  // ← 添加
	);
	
endmodule
