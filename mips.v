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
	wire regdstE,alusrcE,pcsrcD,memtoregE,memtoregM,memtoregW,
			regwriteE,regwriteM,regwriteW;
	wire [2:0] alucontrolE;
	wire hassignE;
	wire [1:0] hilo_enE;
	wire [1:0] hilo_mfE;
	wire divE;
	wire flushE,equalD;

	// ========== 成员3接口信号 ==========
	wire [2:0] mem_op_o;      // -> DM
	wire [1:0] ext_type_o;    // -> ExtUnit
	wire syscall_i;           // <- Trap_Detect
	wire break_i;             // <- Trap_Detect
	wire exception_o;         // 异常发生信号
	wire eret_o;              // ERET指令
	wire [5:0] cause_o;       // 异常原因

	controller c(
		clk,rst,
		//decode stage
		opD,functD,
		pcsrcD,branchD,equalD,jumpD,

		//execute stage
		flushE,
		memtoregE,alusrcE,
		regdstE,regwriteE,	
		alucontrolE,hassignE,hilo_enE,hilo_mfE,divE,

		//mem stage
		memtoregM,memwriteM,
		regwriteM,
		//write back stage
		memtoregW,regwriteW,

		// ========== 成员3接口 ==========
		.mem_op_o(mem_op_o),        // -> DM
		.ext_type_o(ext_type_o),    // -> ExtUnit
		.syscall_i(syscall_i),      // <- Trap_Detect
		.break_i(break_i),          // <- Trap_Detect
		.exception_o(exception_o),  // -> datapath/CP0_Reg
		.eret_o(eret_o),            // -> CP0_Reg
		.cause_o(cause_o)           // -> CP0_Reg
		);

	// Trap_Detect实例化 (成员3)
	Trap_Detect trap_detect(
		.instr(instrF),
		.is_syscall(syscall_i),
		.is_break(break_i),
		.trap_type()  // 暂未使用
	);

	datapath dp(
		clk,rst,
		//fetch stage
		pcF,
		instrF,
		//decode stage
		pcsrcD,branchD,
		jumpD,
		equalD,
		opD,functD,
		//execute stage
		memtoregE,
		alusrcE,regdstE,
		regwriteE,
		alucontrolE,
		hassignE,
		hilo_enE,hilo_mfE,divE,
		flushE,
		//mem stage
		memtoregM,
		regwriteM,
		aluoutM,writedataM,
		readdataM,
		//writeback stage
		memtoregW,
		regwriteW,

		// ========== 成员3接口 (未来扩展) ==========
		// .mem_op_i(),      // 等待成员1
		// .ext_type_i(),    // 等待成员1
		.exception_i(exception_o)  // 异常输入
	    );

endmodule
