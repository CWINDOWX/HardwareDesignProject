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
	output wire [2:0] alucontrolE,
	output wire hassignE,    // 判断是不是有符号的计算
	output wire [1:0] hilo_enE,
	output wire [1:0] hilo_mfE,
	output wire divE,
	output wire isluiE,
	output wire [1:0] shiftE,

	//mem stage
	output wire memtoregM,memwriteM,
				regwriteM,
	output wire [2:0] mem_opM,
	//write back stage
	output wire memtoregW,regwriteW

    );
	
	//decode stage
	wire[2:0] aluopD;
	wire memtoregD,memwriteD,alusrcD,
		regdstD,regwriteD;
	wire[2:0] alucontrolD;
	wire hassign_md,hassign_ad,hassignD;
	wire [1:0] hilo_enD;
	wire [1:0] hilo_mfD;
	wire divD;
	wire isluiD;
	wire [1:0] shiftD;
	wire [2:0] mem_opD,mem_opE;

	//execute stage
	wire memwriteE;

	maindec md(
		opD,
		memtoregD,memwriteD,
		branchD,alusrcD,
		regdstD,regwriteD,
		jumpD,
		aluopD,
		hassign_md,
		isluiD,
		mem_opD
		);
	aludec ad(rst,functD,aluopD,alucontrolD,hassign_ad,hilo_enD,hilo_mfD,divD,shiftD);

	assign hassignD = hassign_md | hassign_ad;
	assign pcsrcD = branchD & equalD;

	//pipeline registers
	floprc #(20) regE(
		clk,
		rst,
		flushE,
		{memtoregD,memwriteD,alusrcD,regdstD,regwriteD,alucontrolD,hassignD,hilo_enD,hilo_mfD,divD,isluiD,shiftD,mem_opD},
		{memtoregE,memwriteE,alusrcE,regdstE,regwriteE,alucontrolE,hassignE,hilo_enE,hilo_mfE,divE,isluiE,shiftE,mem_opE}
		);
	flopr #(6) regM(
		clk,rst,
		{memtoregE,memwriteE,regwriteE,mem_opE},
		{memtoregM,memwriteM,regwriteM,mem_opM}
		);
	flopr #(8) regW(
		clk,rst,
		{memtoregM,regwriteM},
		{memtoregW,regwriteW}
		);
endmodule
