`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/10/23 15:21:30
// Design Name: 
// Module Name: controller
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


module controller(
	input wire clk,rst,
	//decode stage
	input wire[5:0] opD,functD,
	output wire pcsrcD,branchD,equalD,jumpD,
	
	//execute stage
	input wire flushE,
	output wire memtoregE,alusrcE,
	output wire regdstE,regwriteE,	
	output wire[2:0] alucontrolE,
	output wire hassignE,    // 判断是不是有符号的计算
	output wire [1:0] hilo_enE,
	output wire [1:0] hilo_mfE,

	//mem stage
	output wire memtoregM,memwriteM,
				regwriteM,
	//write back stage
	output wire memtoregW,regwriteW

    );
	
	//decode stage
	wire[1:0] aluopD;
	wire memtoregD,memwriteD,alusrcD,
		regdstD,regwriteD;
	wire[2:0] alucontrolD;
	wire hassign_md,hassign_ad,hassignD;
	wire [1:0] hilo_enD;
	wire [1:0] hilo_mfD;

	//execute stage
	wire memwriteE;

	maindec md(
		opD,
		memtoregD,memwriteD,
		branchD,alusrcD,
		regdstD,regwriteD,
		jumpD,
		aluopD,
		hassign_md
		);
	aludec ad(functD,aluopD,alucontrolD,hassign_ad,hilo_enD,hilo_mfD);

	assign hassignD = hassign_md | hassign_ad;
	assign pcsrcD = branchD & equalD;

	//pipeline registers
	floprc #(13) regE(
		clk,
		rst,
		flushE,
		{memtoregD,memwriteD,alusrcD,regdstD,regwriteD,alucontrolD,hassignD,hilo_enD,hilo_mfD},
		{memtoregE,memwriteE,alusrcE,regdstE,regwriteE,alucontrolE,hassignE,hilo_enE,hilo_mfE}
		);
	flopr #(8) regM(
		clk,rst,
		{memtoregE,memwriteE,regwriteE},
		{memtoregM,memwriteM,regwriteM}
		);
	flopr #(8) regW(
		clk,rst,
		{memtoregM,regwriteM},
		{memtoregW,regwriteW}
		);
endmodule
