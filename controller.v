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
	output wire divE,        // 除法指令标志 (成员1)

	//mem stage
	output wire memtoregM,memwriteM,
				regwriteM,
	//write back stage
	output wire memtoregW,regwriteW,

	// ========== 成员3接口 ==========
	// 输出到DM (mem_op_o)
	output wire [2:0] mem_op_o,     // 访存操作类型 -> DM
	// 输出到ExtUnit (ext_type_o)
	output wire [1:0] ext_type_o,   // 立即数扩展类型 -> ExtUnit
	// 输入自陷检测 (Trap_Detect -> Control)
	input  wire syscall_i,          // SYSCALL异常 <- Trap_Detect
	input  wire break_i,            // BREAK异常 <- Trap_Detect
	// 异常处理输出 (Control -> CP0_Reg)
	output wire exception_o,        // 异常发生 -> datapath/CP0_Reg
	output wire eret_o,             // ERET指令 -> CP0_Reg
	output wire [5:0] cause_o       // 异常原因 -> CP0_Reg
    );
	
	//decode stage
	wire[1:0] aluopD;
	wire memtoregD,memwriteD,alusrcD,
		regdstD,regwriteD;
	wire[2:0] alucontrolD;
	wire hassign_md,hassign_ad,hassignD;
	wire [1:0] hilo_enD;
	wire [1:0] hilo_mfD;
	wire divD;

	//execute stage
	wire memwriteE;

	// ========== 成员3接口内部信号 ==========
	wire exceptionD;       // 异常发生信号
	wire [5:0] trap_type;  // 异常类型 (来自Trap_Detect)
	wire [1:0] ext_typeD;  // 扩展类型

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

	// DIV/DIVU指令检测
	assign divD = (opD == 6'b000000) && (functD == 6'b011010 || functD == 6'b011011);

	// ========== 成员3接口逻辑 ==========
	// mem_op_o: 访存操作类型
	// 000: LW/SW (字), 001: SH, 010: SB, 100: LH, 101: LHU, 110: LB, 111: LBU
	assign mem_op_o = memwriteD ? 3'b000 :    // SW
	                  (opD == 6'b100011) ? 3'b000 :  // LW
	                  3'b000;  // 默认字访问

	// ext_type_o: 立即数扩展类型
	// 00: 符号扩展, 01: 零扩展, 10: Load符号扩展, 11: Load零扩展
	assign ext_type_o = (opD == 6'b001100 ||   // ANDI
	                     opD == 6'b001101 ||   // ORI
	                     opD == 6'b001110) ? 2'b01 :  // XORI (零扩展)
	                    2'b00;  // 默认符号扩展

	// 异常检测
	assign exceptionD = syscall_i || break_i;
	assign trap_type = syscall_i ? 6'd8 :   // Sys
	                   break_i  ? 6'd9 :    // Bp
	                   6'd0;

	// 异常处理输出
	assign exception_o = exceptionD;
	assign cause_o = trap_type;
	assign eret_o = 1'b0;  // 暂未实现ERET

	//pipeline registers
	floprc #(14) regE(
		clk,
		rst,
		flushE,
		{memtoregD,memwriteD,alusrcD,regdstD,regwriteD,alucontrolD,hassignD,hilo_enD,hilo_mfD,divD},
		{memtoregE,memwriteE,alusrcE,regdstE,regwriteE,alucontrolE,hassignE,hilo_enE,hilo_mfE,divE}
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
