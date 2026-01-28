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
    input wire clk, rst,
    // --- Fetch Stage ---
    output wire[31:0] pcF,
    input wire[31:0] instrF,
    // --- Decode Stage ---
    input wire pcsrcD, branchD,
    input wire [2:0] branch_opD,
    input wire jumpD,
    input wire jumpregD,
    output wire equalD,
    output wire[5:0] opD, functD,
    output wire[4:0] rtD,
    // --- Execute Stage ---
    input wire memtoregE, alusrcE, regdstE, regwriteE,
    input wire linkE, jalrE,
    input wire[2:0] alucontrolE,
    input wire hassignE, isluiE, divE,
    input wire [1:0] hilo_enE, hilo_mfE, shiftE,
    output wire flushE,
    // --- Mem Stage ---
    input wire memtoregM, regwriteM,
    input wire linkM, jalrM,
    output wire[31:0] aluoutM, writedataM,
    input wire[31:0] readdataM,
    // --- Writeback Stage ---
    input wire memtoregW, regwriteW,
    input wire linkW, jalrW
);

    // --- 内部信号定义 ---
    wire stallF, stallD, flushD;
    wire [31:0] pcnextFD, pcnextbrFD, pcplus4F, pcplus4D, pcplus8D, pcbranchD, pcjumpD, pcjumpregD, pcnextbrjD;
    wire [31:0] instrD, signimmD, signimmshD, zeroimmD, luiimmD;
    wire [31:0] srcaD, srca2D, srcbD, srcb2D;
    wire [4:0] rsD, rdD, saD;
    wire forwardaD, forwardbD;

    wire [1:0] forwardaE, forwardbE;
    wire [4:0] rsE, rtE, rdE, saE, writeregE, writeregE_temp;
    wire [31:0] srcaE, srca2E, srca3E, srcbE, srcb2E, srcb3E, srcimmE;
    wire [31:0] aluoutE, aluresultE, aluresult_loE, finaloutE;
    wire [31:0] signimmE, zeroimmE, luiimmE, pcplus8E;
    wire [31:0] hi_inE, lo_inE, hi_outE, lo_outE, qE, rE;
    wire divbusyE, divdoneE;

    wire [4:0] writeregM;
    wire [31:0] pcplus8M;
    wire [4:0] writeregW;
    wire [31:0] aluoutW, readdataW, resultW, resultW_temp, pcplus8W;

    // --- Hazard Detection ---
    hazard h(
        .stallF(stallF), .rsD(rsD), .rtD(rtD), .branchD(branchD), .jumpregD(jumpregD),
        .forwardaD(forwardaD), .forwardbD(forwardbD), .stallD(stallD),
        .rsE(rsE), .rtE(rtE), .writeregE(writeregE), .regwriteE(regwriteE), .memtoregE(memtoregE),
        .divE(divE), .divbusyE(divbusyE), .forwardaE(forwardaE), .forwardbE(forwardbE), .flushE(flushE),
        .writeregM(writeregM), .regwriteM(regwriteM), .memtoregM(memtoregM),
        .writeregW(writeregW), .regwriteW(regwriteW)
    );

    // --- Fetch Stage Logic ---
    pc #(32) pcreg(clk, rst, ~stallF, pcnextFD, pcF);
    adder pcadd1(pcF, 32'h4, pcplus4F);

    // --- Decode Stage Logic ---
    flopenr #(32) r1D(clk, rst, ~stallD, pcplus4F, pcplus4D);
    // 【修改点 1】延迟槽下，跳转不再冲刷 Decode 级，除非发生异常（本项目暂无）
    assign flushD = 1'b0; 
    flopenrc #(32) r2D(clk, rst, ~stallD, flushD, instrF, instrD);
    
    assign opD = instrD[31:26];
    assign functD = instrD[5:0];
    assign rsD = instrD[25:21];
    assign rtD = instrD[20:16];
    assign rdD = instrD[15:11];
    assign saD = instrD[10:6];

    signext se(instrD[15:0], signimmD);
    sl2 immsh(signimmD, signimmshD);
    adder pcadd2(pcplus4D, signimmshD, pcbranchD);
    // 【修改点 2】返回地址计算。
    // 在延迟槽架构中，JAL 存入的应该是当前跳转指令地址 + 8。
    // 此时 pcplus4D 已经是跳转指令的 PC+4，所以再加 4 得到 PC+8。
    adder pcadd3(pcplus4D, 32'h4, pcplus8D); 

    mux2 #(32) forwardamux(srcaD, aluoutM, forwardaD, srca2D);
    mux2 #(32) forwardbmux(srcbD, aluoutM, forwardbD, srcb2D);

    Branch_Cmp branch_cmp(
        .a(srca2D), .b(srcb2D), .cmp_op(branch_opD), .cmp_result(equalD)
    );

    assign pcjumpD = {pcplus4D[31:28], instrD[25:0], 2'b00};
    assign pcjumpregD = srca2D;
    
    mux2 #(32) pcbrmux(pcplus4F, pcbranchD, pcsrcD, pcnextbrFD);
    mux2 #(32) pcjumpmux(pcjumpD, pcjumpregD, jumpregD, pcnextbrjD);
    mux2 #(32) pcfinalmux(pcnextbrFD, pcnextbrjD, jumpD | jumpregD, pcnextFD);

    assign zeroimmD = {16'b0, instrD[15:0]};
    assign luiimmD = {instrD[15:0], 16'b0};

    regfile rf(clk, regwriteW, rsD, rtD, writeregW, resultW, srcaD, srcbD);

    // --- Execute Stage Logic ---
    // 【修改点 3】由于不冲刷 Decode，我们需要把跳转后的那条指令（延迟槽指令）送入 Execute。
    // 注意：srca2D 和 srcb2D 已经包含了从 Memory 级前推的数据，这对于跳转指令本身很重要。
    // 延迟槽指令作为普通指令，流水线寄存器正常传递。
    floprc #(32) r1E(clk, rst, flushE, srcaD, srcaE);
    floprc #(32) r2E(clk, rst, flushE, srcbD, srcbE);
    floprc #(32) r3E(clk, rst, flushE, signimmD, signimmE);
    floprc #(5) r4E(clk, rst, flushE, rsD, rsE);
    floprc #(5) r5E(clk, rst, flushE, rtD, rtE);
    floprc #(5) r6E(clk, rst, flushE, rdD, rdE);
    floprc #(32) r7E(clk, rst, flushE, zeroimmD, zeroimmE);
    floprc #(32) r8E(clk, rst, flushE, luiimmD, luiimmE);
    floprc #(5) r9E(clk, rst, flushE, saD, saE);
    floprc #(32) r10E(clk, rst, flushE, pcplus8D, pcplus8E);

    mux3 #(32) forwardaemux(srcaE, resultW, aluoutM, forwardaE, srca2E);
    mux3 #(32) forwardbemux(srcbE, resultW, aluoutM, forwardbE, srcb2E);

    mux3 #(32) srcextmux(signimmE, zeroimmE, luiimmE, {isluiE, alucontrolE[0]}, srcimmE);
    mux2 #(32) srcamux(srca2E, {27'b0, saE}, shiftE[0], srca3E);
    mux2 #(32) srcbmux(srcb2E, srcimmE, alusrcE, srcb3E);

    alu alu(srca3E, srcb3E, alucontrolE, hassignE, shiftE[1], aluresultE, aluresult_loE);
    divider div_inst(clk, rst, divE, hassignE, srca3E, srcb3E, qE, rE, divbusyE, divdoneE);

    mux3 #(32) hiinmux(aluresultE, srca3E, rE, {divdoneE, hilo_enE[1]}, hi_inE);
    mux3 #(32) loinmux(aluresult_loE, srca3E, qE, {divdoneE, hilo_enE[1]}, lo_inE);
    hilo_reg hilo_reg(clk,rst,divdoneE,hilo_enE,hi_inE,lo_inE,hi_outE,lo_outE);	//写hi_lo寄存器堆，是在EX阶段做的

    mux3 #(32) aluoutmux(lo_outE, hi_outE, aluresultE, hilo_mfE, aluoutE);
    
    mux2 #(32) linkemux(aluoutE, pcplus8E, linkE | jalrE, finaloutE);
    
    mux2 #(5) wrmux(rtE, rdE, regdstE, writeregE_temp);
    mux2 #(5) linkregmux(writeregE_temp, 5'd31, linkE, writeregE); 

    // --- Memory Stage Logic ---
    flopr #(32) r1M(clk, rst, srcb2E, writedataM);
    flopr #(32) r2M(clk, rst, finaloutE, aluoutM);
    flopr #(5) r3M(clk, rst, writeregE, writeregM);
    flopr #(32) r4M(clk, rst, pcplus8E, pcplus8M);

    // --- Writeback Stage Logic ---
    flopr #(32) r1W(clk, rst, aluoutM, aluoutW);
    flopr #(32) r2W(clk, rst, readdataM, readdataW);
    flopr #(5) r3W(clk, rst, writeregM, writeregW);
    flopr #(32) r4W(clk, rst, pcplus8M, pcplus8W);

    mux2 #(32) resmux(aluoutW, readdataW, memtoregW, resultW_temp);
    mux2 #(32) linkwmux(resultW_temp, pcplus8W, linkW | jalrW, resultW);

endmodule
