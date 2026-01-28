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
	input wire hassignE,    // 判断是不是有符号的计�?
	input wire [1:0] hilo_enE,
	input wire [1:0] hilo_mfE,
	input wire divE,
	// 移位相关控制信号
	input wire shiftE,
	input wire [1:0] shift_typeE,
	input wire var_shiftE,
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
	wire [4:0] rsD,rtD,rdD;
	wire flushD,stallD; 
	wire [31:0] signimmD,signimmshD;
	wire [31:0] srcaD,srca2D,srcbD,srcb2D;
	//execute stage
	wire [1:0] forwardaE,forwardbE;
	wire [4:0] rsE,rtE,rdE;
	wire [4:0] writeregE;
	wire [31:0] signimmE;
	wire [31:0] srcaE,srca2E,srcbE,srcb2E,srcb3E;
	wire [31:0] aluoutE,aluresult_loE,aluresultE,aluresult_finalE;
	wire [31:0] hi_outE,lo_outE;
	wire [31:0] hi_inE,lo_inE;
	wire [31:0] qE,rE;	
	wire divbusyE,divdoneE;
	//shift related signals
	wire [4:0] shamtD,shamtE;
	wire [31:0] shift_resultE;
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

	assign opD = instrD[31:26];
	assign functD = instrD[5:0];
	assign rsD = instrD[25:21];
	assign rtD = instrD[20:16];
	assign rdD = instrD[15:11];
	assign shamtD = instrD[10:6];

	// Use ExtUnit instead of signext for zero extension support
	wire [1:0] ext_typeD;
	assign ext_typeD = (opD == 6'b001100 || opD == 6'b001101 || opD == 6'b001110) ? 2'b01 : 2'b00; // Zero extend for ANDI/ORI/XORI
	ExtUnit eu(instrD[15:0], ext_typeD, signimmD);
	sl2 immsh(signimmD,signimmshD);
	adder pcadd2(pcplus4D,signimmshD,pcbranchD);
	mux2 #(32) forwardamux(srcaD,aluoutM,forwardaD,srca2D);
	mux2 #(32) forwardbmux(srcbD,aluoutM,forwardbD,srcb2D);
	eqcmp comp(srca2D,srcb2D,equalD);

	//execute stage
	floprc #(32) r1E(clk,rst,flushE,srca2D,srcaE);
	floprc #(32) r2E(clk,rst,flushE,srcb2D,srcbE);
	floprc #(32) r3E(clk,rst,flushE,signimmD,signimmE);
	floprc #(5) r4E(clk,rst,flushE,rsD,rsE);
	floprc #(5) r5E(clk,rst,flushE,rtD,rtE);
	floprc #(5) r6E(clk,rst,flushE,rdD,rdE);
	floprc #(5) r7E(clk,rst,flushE,shamtD,shamtE);
	// 执行阶段的写数据信号
	wire [31:0] writedataE;
	// 移位相关控制信号从controller直接传递

	mux3 #(32) forwardaemux(srcaE,resultW,aluoutM,forwardaE,srca2E);
	mux3 #(32) forwardbemux(srcbE,resultW,aluoutM,forwardbE,srcb2E);
	mux2 #(32) srcbmux(srcb2E,signimmE,alusrcE,srcb3E);

	// 实例化ShiftUnit模块
	ShiftUnit shift_unit(
		.rt_i(srcb2E),      // 来自rt寄存器的值（经过前向选择器）
		.rs_i(srca2E),      // 来自rs寄存器的值（变量移位用，经过前向选择器）
		.shamt_i(shamtE),   // 立即数移位量
		.var_shift(var_shiftE), // 0:使用shamt, 1:使用rs
		.shift_type(shift_typeE),// 00:SLL, 01:SRL, 10:SRA
		.result_o(shift_resultE)  // 移位结果
	);

	alu alu(srca2E,srcb3E,alucontrolE,hassignE,aluresultE,aluresult_loE);

	divider divider(clk,rst,divE,hassignE,srca2E,srcb3E,qE,rE,divbusyE,divdoneE);

	mux3 #(32) hiinmux(srca2E,aluresultE,rE,{divdoneE,hilo_enE[1]},hi_inE);
	mux3 #(32) loinmux(srca2E,aluresult_loE,qE,{divdoneE,hilo_enE[1]},lo_inE);

	hilo_reg hilo_reg(clk,rst,divdoneE,hilo_enE,hi_inE,lo_inE,hi_outE,lo_outE);	//写hi_lo寄存器堆，是在EX阶段做的

	mux2 #(5) wrmux(rtE,rdE,regdstE,writeregE);

	// 添加移位结果选择
	mux2 #(32) shiftmux(aluresultE,shift_resultE,shiftE,aluresult_finalE);
	mux3 #(32) aluoutmux(lo_outE,hi_outE,aluresult_finalE,hilo_mfE,aluoutE);

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
