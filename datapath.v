`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/02 15:12:22
// Design Name: 
// Module Name: datapath
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


module datapath(
	input wire clk,rst,
	//fetch stage
	output wire[31:0] pcF,
	input wire[31:0] instrF,
	//decode stage
	input wire pcsrcD,branchD,
	input wire jumpD,
	output wire equalD,
	output wire[5:0] opD,functD,
	//execute stage
	input wire memtoregE,
	input wire alusrcE,regdstE,
	input wire regwriteE,
	input wire[2:0] alucontrolE,
	input wire hassignE,    // 判断是不是有符号的计算
	input wire [1:0] hilo_enE,
	input wire [1:0] hilo_mfE,
	input wire divE,
	input wire isluiE,
	input wire [1:0] shiftE,
	output wire flushE,
	//mem stage
	input wire memtoregM,
	input wire regwriteM,
	output wire[31:0] aluoutM,writedataM,
	input wire[31:0] readdataM,
	//writeback stage
	input wire memtoregW,
	input wire regwriteW
    );
	
	//fetch stage
	wire stallF;
	//FD
	wire [31:0] pcnextFD,pcnextbrFD,pcplus4F,pcbranchD;
	//decode stage
	wire [31:0] pcplus4D,instrD;
	wire forwardaD,forwardbD;
	wire [4:0] rsD,rtD,rdD,saD;
	wire flushD,stallD; 
	wire [31:0] signimmD,signimmshD;
	wire [31:0] srcaD,srca2D,srcbD,srcb2D;
	wire [31:0] zeroimmD;
	wire [31:0] luiimmD;
	//execute stage
	wire [1:0] forwardaE,forwardbE;
	wire [4:0] rsE,rtE,rdE,saE;
	wire [4:0] writeregE;
	wire [31:0] signimmE;
	wire [31:0] srcaE,srca2E,srca3E,srcbE,srcb2E,srcb3E;
	wire [31:0] aluoutE,aluresult_loE,aluresultE;
	wire [31:0] hi_outE,lo_outE;
	wire [31:0] hi_inE,lo_inE;
	wire [31:0] qE,rE;	
	wire divbusyE,divdoneE;
	wire [31:0] srcimmE;
	wire [31:0] zeroimmE;
	wire [31:0] luiimmE;
	//mem stage
	wire [4:0] writeregM;
	//writeback stage
	wire [4:0] writeregW;
	wire [31:0] aluoutW,readdataW,resultW;

	//hazard detection
	hazard h(
		//fetch stage
		stallF,
		//decode stage
		rsD,rtD,
		branchD,
		forwardaD,forwardbD,
		stallD,
		//execute stage
		rsE,rtE,
		writeregE,
		regwriteE,
		memtoregE,
		divE,divbusyE,
		forwardaE,forwardbE,
		flushE,
		//mem stage
		writeregM,
		regwriteM,
		memtoregM,
		//write back stage
		writeregW,
		regwriteW
		);

	//next PC logic (operates in fetch an decode)
	mux2 #(32) pcbrmux(pcplus4F,pcbranchD,pcsrcD,pcnextbrFD);
	mux2 #(32) pcmux(pcnextbrFD,
		{pcplus4D[31:28],instrD[25:0],2'b00},
		jumpD,pcnextFD);

	//regfile (operates in decode and writeback)
	regfile rf(clk,regwriteW,rsD,rtD,writeregW,resultW,srcaD,srcbD);

	//fetch stage logic
	pc #(32) pcreg(clk,rst,~stallF,pcnextFD,pcF);
	adder pcadd1(pcF,32'b100,pcplus4F);
	//decode stage
	flopenr #(32) r1D(clk,rst,~stallD,pcplus4F,pcplus4D);
	flopenrc #(32) r2D(clk,rst,~stallD,flushD,instrF,instrD);

	// 成员3：ExtUnit 接入（替代 signext），后续可扩展到更多指令类型
	wire [1:0] ext_typeD;
	assign ext_typeD = (opD == 6'b001100 ||  // ANDI
	                    opD == 6'b001101 ||  // ORI
	                    opD == 6'b001110) ?  // XORI
	                   2'b01 :               // 零扩展
	                   2'b00;                // 符号扩展
	ExtUnit extu(instrD[15:0], ext_typeD, signimmD);

	// 成员3：Trap_Detect 预接入（目前主流水线未使用，供后续例外模块对接）
	// verilator lint_off UNUSEDSIGNAL
	wire trap_syscallD, trap_breakD;
	wire [5:0] trap_typeD;
	Trap_Detect u_trap_detect(.instr(instrD), .is_syscall(trap_syscallD), .is_break(trap_breakD), .trap_type(trap_typeD));
	// verilator lint_on UNUSEDSIGNAL

	sl2 immsh(signimmD,signimmshD);
	adder pcadd2(pcplus4D,signimmshD,pcbranchD);
	mux2 #(32) forwardamux(srcaD,aluoutM,forwardaD,srca2D);
	mux2 #(32) forwardbmux(srcbD,aluoutM,forwardbD,srcb2D);
	eqcmp comp(srca2D,srcb2D,equalD);

	assign opD = instrD[31:26];
	assign functD = instrD[5:0];
	assign rsD = instrD[25:21];
	assign rtD = instrD[20:16];
	assign rdD = instrD[15:11];
	assign saD = instrD[10:6];
	assign zeroimmD = {16'b0,instrD[15:0]};
	assign luiimmD = {instrD[15:0],16'b0};

	//execute stage
	floprc #(32) r1E(clk,rst,flushE,srcaD,srcaE);
	floprc #(32) r2E(clk,rst,flushE,srcbD,srcbE);
	floprc #(32) r3E(clk,rst,flushE,signimmD,signimmE);
	floprc #(5) r4E(clk,rst,flushE,rsD,rsE);
	floprc #(5) r5E(clk,rst,flushE,rtD,rtE);
	floprc #(5) r6E(clk,rst,flushE,rdD,rdE);
	floprc #(32) r7E(clk,rst,flushE,zeroimmD,zeroimmE);
	floprc #(32) r8E(clk,rst,flushE,luiimmD,luiimmE);
	floprc #(5) r9E(clk,rst,flushE,saD,saE);

	mux3 #(32) forwardaemux(srcaE,resultW,aluoutM,forwardaE,srca2E);
	mux3 #(32) forwardbemux(srcbE,resultW,aluoutM,forwardbE,srcb2E);

	mux3 #(32) srcextmux(signimmE,zeroimmE,luiimmE,{isluiE,alucontrolE[0]},srcimmE);
	mux2 #(32) srcamux(srca2E,{27'b0,saE},shiftE[0],srca3E);
	mux2 #(32) srcbmux(srcb2E,srcimmE,alusrcE,srcb3E);

	// 补齐 ALU 输出端口（为后续例外/分支扩展预留）
	// verilator lint_off UNUSEDSIGNAL
	wire alu_overflowE;
	wire alu_zeroE;
	// verilator lint_on UNUSEDSIGNAL
	alu alu(
		.a(srca3E),
		.b(srcb3E),
		.op(alucontrolE),
		.hassign(hassignE),
		.shift(shiftE[1]),
		.y(aluresultE),
		.y_lo(aluresult_loE),
		.overflow(alu_overflowE),
		.zero(alu_zeroE)
	);

	// verilator lint_off UNUSEDSIGNAL
	wire div_overflowE;
	// verilator lint_on UNUSEDSIGNAL
	divider divider(
		.clk(clk),
		.rst(rst),
		.en(divE),
		.hassign(hassignE),
		.a(srca3E),
		.b(srcb3E),
		.q(qE),
		.r(rE),
		.busy(divbusyE),
		.done(divdoneE),
		.overflow(div_overflowE)
	);

	mux3 #(32) hiinmux(aluresultE,srca3E,rE,{divdoneE,hilo_enE[1]},hi_inE);
	mux3 #(32) loinmux(aluresult_loE,srca3E,qE,{divdoneE,hilo_enE[1]},lo_inE);

	hilo_reg hilo_reg(clk,rst,divdoneE,hilo_enE,hi_inE,lo_inE,hi_outE,lo_outE);	//写hi_lo寄存器堆，是在EX阶段做的

	mux2 #(5) wrmux(rtE,rdE,regdstE,writeregE);

	mux3 #(32) aluoutmux(lo_outE,hi_outE,aluresultE,hilo_mfE,aluoutE);//即使出现flushE，导致00变成LO写寄存器，但因为此时writeregE也是0，所以没有问题。

	//mem stage
	flopr #(32) r1M(clk,rst,srcb2E,writedataM);
	flopr #(32) r2M(clk,rst,aluoutE,aluoutM);
	flopr #(5) r3M(clk,rst,writeregE,writeregM);

	//writeback stage
	flopr #(32) r1W(clk,rst,aluoutM,aluoutW);
	flopr #(32) r2W(clk,rst,readdataM,readdataW);
	flopr #(5) r3W(clk,rst,writeregM,writeregW);
	mux2 #(32) resmux(aluoutW,readdataW,memtoregW,resultW);
endmodule
