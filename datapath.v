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
	input wire[2:0] branch_opD,
	input wire jumpD,
	input wire jumpregD,  // ← 新增
	output wire equalD,
	output wire[5:0] opD,functD,
	output wire[4:0] rtD,
	//execute stage
	input wire memtoregE,
	input wire alusrcE,regdstE,
	input wire regwriteE,
	input wire linkE,
	input wire jalrE,  // ← 新增
	input wire[2:0] alucontrolE,
	output wire flushE,
	//mem stage
	input wire memtoregM,
	input wire regwriteM,
	input wire linkM,
	input wire jalrM,  // ← 新增
	output wire[31:0] aluoutM,writedataM,
	input wire[31:0] readdataM,
	//writeback stage
	input wire memtoregW,
	input wire regwriteW,
	input wire linkW,
	input wire jalrW  // ← 新增
);
	
	//fetch stage
	wire stallF;
	//FD
	wire [31:0] pcnextFD,pcnextbrFD,pcplus4F,pcbranchD;
	//decode stage
	wire [31:0] pcplus4D,instrD;
	wire forwardaD,forwardbD;
	wire [4:0] rsD,rdD;
	wire flushD,stallD; 
	wire [31:0] signimmD,signimmshD;
	wire [31:0] pcplus8D;
	wire [31:0] srcaD,srca2D,srcbD,srcb2D;
	//execute stage
	wire [1:0] forwardaE,forwardbE;
	wire [4:0] rsE,rtE,rdE;
	wire [4:0] writeregE;
	wire [4:0] writeregE_temp;
	wire [31:0] signimmE;
	wire [31:0] pcplus8E;
	wire [31:0] srcaE,srca2E,srcbE,srcb2E,srcb3E;
	wire [31:0] aluoutE;
	wire [31:0] shiftoutE;
	wire [4:0] shamtE;
	//mem stage
	wire [4:0] writeregM;
	wire [31:0] pcplus8M;
	//writeback stage
	wire [4:0] writeregW;
	wire [31:0] aluoutW,readdataW,resultW;
	wire [31:0] pcplus8W;
	wire [31:0] resultW_temp;

	//hazard detection
	hazard h(
		//fetch stage
		stallF,
		//decode stage
		rsD,rtD,
		branchD,
		jumpregD,  // 新增这一行
		forwardaD,forwardbD,
		stallD,
		//execute stage
		rsE,rtE,
		writeregE,
		regwriteE,
		memtoregE,
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
	
	// 立即数跳转地址（J/JAL）
	wire [31:0] pcjumpD;
	assign pcjumpD = {pcplus4D[31:28],instrD[25:0],2'b00};
	
	// 寄存器跳转地址（JR/JALR）
	wire [31:0] pcjumpregD;
	assign pcjumpregD = srca2D;  // 从 rs 读取，经过 forwarding
	
	// 三级选择：分支 > 立即数跳转 > 寄存器跳转
	wire [31:0] pcnextbrjD;
	mux2 #(32) pcjumpmux(pcjumpD, pcjumpregD, jumpregD, pcnextbrjD);
	mux2 #(32) pcjumpmux2(pcnextbrFD, pcnextbrjD, jumpD | jumpregD, pcnextFD);

	//regfile (operates in decode and writeback)
	regfile rf(clk,regwriteW,rsD,rtD,writeregW,resultW,srcaD,srcbD);

	//fetch stage logic
	pc #(32) pcreg(clk,rst,~stallF,pcnextFD,pcF);
	adder pcadd1(pcF,32'b100,pcplus4F);
	
	//decode stage
	flopenr #(32) r1D(clk,rst,~stallD,pcplus4F,pcplus4D);
	flopenrc #(32) r2D(clk,rst,~stallD,flushD,instrF,instrD);
	assign flushD = pcsrcD;  // 改回原来的
	signext se(instrD[15:0],signimmD);
	
	// 零扩展（用于ORI/ANDI/XORI）
	wire [31:0] zeroextD;
	assign zeroextD = {16'b0, instrD[15:0]};
	wire use_zeroext;
	assign use_zeroext = (opD == 6'b001101) | (opD == 6'b001100) | (opD == 6'b001110);
	wire [31:0] immD;
	mux2 #(32) extmux(signimmD, zeroextD, use_zeroext, immD);
	
	sl2 immsh(signimmD,signimmshD);
	adder pcadd2(pcplus4D,signimmshD,pcbranchD);
	adder pcadd3(pcplus4D,32'd4,pcplus8D);
	mux2 #(32) forwardamux(srcaD,aluoutM,forwardaD,srca2D);
	mux2 #(32) forwardbmux(srcbD,aluoutM,forwardbD,srcb2D);
	
	Branch_Cmp branch_cmp(
		.a(srca2D),
		.b(srcb2D),
		.cmp_op(branch_opD),
		.cmp_result(equalD)
	);

	assign opD = instrD[31:26];
	assign functD = instrD[5:0];
	assign rsD = instrD[25:21];
	assign rtD = instrD[20:16];
	assign rdD = instrD[15:11];

	//execute stage
	floprc #(32) r1E(clk,rst,flushE,srcaD,srcaE);
	floprc #(32) r2E(clk,rst,flushE,srcbD,srcbE);
	floprc #(32) r3E(clk,rst,flushE,immD,signimmE);
	floprc #(5) r4E(clk,rst,flushE,rsD,rsE);
	floprc #(5) r5E(clk,rst,flushE,rtD,rtE);
	floprc #(5) r6E(clk,rst,flushE,rdD,rdE);
	floprc #(32) r7E(clk,rst,flushE,pcplus8D,pcplus8E);
	floprc #(5) r8E(clk,rst,flushE,instrD[10:6],shamtE);

	mux3 #(32) forwardaemux(srcaE,resultW,aluoutM,forwardaE,srca2E);
	mux3 #(32) forwardbemux(srcbE,resultW,aluoutM,forwardbE,srcb2E);
	mux2 #(32) srcbmux(srcb2E,signimmE,alusrcE,srcb3E);
	alu alu(srca2E,srcb3E,alucontrolE,aluoutE);
	
	// 移位器
	assign shiftoutE = srcb2E << shamtE;
	wire is_sll;
	assign is_sll = (alucontrolE == 3'b010) && (rsE == 5'b00000);
	
	// 三级选择最终结果
	wire [31:0] alu_or_shift;
	mux2 #(32) resultmux1(aluoutE, shiftoutE, is_sll, alu_or_shift);
	// 2. 再选择是否用 pcplus8（JAL/JALR 链接指令）
    wire need_pcplus8;
    assign need_pcplus8 = linkE | jalrE;  // ← 关键：JALR 也需要 pcplus8
	wire [31:0] finaloutE;
	mux2 #(32) resultmux2(alu_or_shift, pcplus8E, need_pcplus8, finaloutE);
	
	mux2 #(5) wrmux(rtE,rdE,regdstE,writeregE_temp);
	mux2 #(5) linkmux(writeregE_temp,5'd31,linkE,writeregE);

	//mem stage
	flopr #(32) r1M(clk,rst,srcb2E,writedataM);
	flopr #(32) r2M(clk,rst,finaloutE,aluoutM);
	flopr #(5) r3M(clk,rst,writeregE,writeregM);
	flopr #(32) r4M(clk,rst,pcplus8E,pcplus8M);

	//writeback stage
	flopr #(32) r1W(clk,rst,aluoutM,aluoutW);
	flopr #(32) r2W(clk,rst,readdataM,readdataW);
	flopr #(5) r3W(clk,rst,writeregM,writeregW);
	flopr #(32) r4W(clk,rst,pcplus8M,pcplus8W);
	
	mux2 #(32) resmux(aluoutW,readdataW,memtoregW,resultW_temp);
	
	// 链接指令结果选择（JAL 和 JALR 都需要）
    wire need_pcplus8_W;
    assign need_pcplus8_W = linkW | jalrW;
	
	mux2 #(32) linkmux2(resultW_temp,pcplus8W,need_pcplus8_W,resultW);
endmodule
