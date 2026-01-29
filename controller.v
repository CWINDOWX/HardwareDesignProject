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
	input wire[4:0] rtD,
	output wire pcsrcD,branchD,
	output wire[2:0] branch_opD,
	output wire equalD,
	output wire jumpD,
	output wire jumpregD,
	
	//execute stage
	input wire flushE,
	output wire memtoregE,alusrcE,
	output wire regdstE,regwriteE,
	output wire linkE,
	output wire jalrE,  // ← 新增：JALR 专用信号
	output wire[2:0] alucontrolE,

	//mem stage
	output wire memtoregM,memwriteM,
				regwriteM,
	output wire linkM,
	output wire jalrM,  // ← 新增
	
	//write back stage
	output wire memtoregW,regwriteW,
	output wire linkW,
	output wire jalrW  // ← 新增
);
	
	//decode stage
	wire[1:0] aluopD;
    wire memtoregD,memwriteD,alusrcD,
        regdstD,regwriteD_raw;  // 改：添加 _raw
    wire regwriteD;  // 改：添加单独的定义
    wire[2:0] alucontrolD;
    wire linkD;
    wire jalrD;  // 新 增加

	//execute stage
	wire memwriteE;

	maindec md(
		opD,
		rtD,
		functD,
		memtoregD,memwriteD,
		branchD,alusrcD,
		regdstD,regwriteD_raw,
		jumpD,
		aluopD,
		branch_opD,
		linkD
	);
	
	aludec ad(functD,aluopD,alucontrolD);

	assign pcsrcD = branchD & equalD;
	
	// 检测 JR 和 JALR
	wire is_jr, is_jalr;
	assign is_jr = (opD == 6'b000000) && (functD == 6'b001000);
	assign is_jalr = (opD == 6'b000000) && (functD == 6'b001001);
	assign jumpregD = is_jr | is_jalr;
	assign jalrD = is_jalr;
	
	// JR 不写寄存器（JALR 需要写）
    assign regwriteD = regwriteD_raw & ~is_jr;
	
	// 条件链接逻辑（只用于 JAL, BGEZAL, BLTZAL，不包括 JALR）
	wire linkD_final;
	assign linkD_final = linkD & (jumpD | pcsrcD);  // ← 移除 jumpregD

	//pipeline registers（扩展为 10 位，添加 jalr）
	floprc #(10) regE(
		clk,
		rst,
		flushE,
		{memtoregD,memwriteD,alusrcD,regdstD,regwriteD,alucontrolD,linkD_final,jalrD},
		{memtoregE,memwriteE,alusrcE,regdstE,regwriteE,alucontrolE,linkE,jalrE}
	);
	flopr #(5) regM(
		clk,rst,
		{memtoregE,memwriteE,regwriteE,linkE,jalrE},
		{memtoregM,memwriteM,regwriteM,linkM,jalrM}
	);
	flopr #(4) regW(
		clk,rst,
		{memtoregM,regwriteM,linkM,jalrM},
		{memtoregW,regwriteW,linkW,jalrW}
	);
endmodule