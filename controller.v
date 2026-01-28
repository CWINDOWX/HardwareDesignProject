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
    input wire clk, rst,
    // --- Decode Stage ---
    input wire[5:0] opD, functD,
    input wire[4:0] rtD,
    input wire equalD,
    output wire pcsrcD, branchD, jumpD, jumpregD,
    output wire [2:0] branch_opD,
    
    // --- Execute Stage ---
    input wire flushE,
    output wire memtoregE, alusrcE, regdstE, regwriteE,
    output wire [2:0] alucontrolE,
    output wire hassignE, isluiE, divE,
    output wire [1:0] hilo_enE, hilo_mfE, shiftE,
    output wire linkE, jalrE,        

    // --- Memory Stage ---
    output wire memtoregM, memwriteM, regwriteM,
    output wire [2:0] mem_opM,
    output wire linkM, jalrM,        // 融合新增
    
    // --- Write Back Stage ---
    output wire memtoregW, regwriteW,
    output wire linkW, jalrW         // 融合新增
);

    // --- Decode Stage Internal Signals ---
    wire[2:0] aluopD;
    wire memtoregD, memwriteD, alusrcD, regdstD, regwriteD_raw, regwriteD;
    wire[2:0] alucontrolD;
    wire hassign_md, hassign_ad, hassignD;
    wire [1:0] hilo_enD, hilo_mfD, shiftD;
    wire divD, isluiD;
    wire [2:0] mem_opD;
    wire linkD, linkD_final, jalrD;
    wire is_jr, is_jalr;

    // --- 实例化融合后的 Main Decoder ---
    maindec md(
        .op(opD),
        .rt(rtD),
        .funct(functD),
        .memtoreg(memtoregD), .memwrite(memwriteD),
        .branch(branchD), .alusrc(alusrcD),
        .regdst(regdstD), .regwrite(regwriteD_raw),
        .jump(jumpD),
        .aluop(aluopD),
        .hassign(hassign_md),
        .islui(isluiD),
        .mem_op(mem_opD),
        .branch_op(branch_opD), // 融合信号
        .link(linkD)            // 融合信号
    );

    // --- 实例化原有的 ALU Decoder ---
    aludec ad(rst, functD, aluopD, alucontrolD, hassign_ad, hilo_enD, hilo_mfD, divD, shiftD);

    // --- 跳转逻辑处理 ---
    assign is_jr   = (opD == 6'b000000) && (functD == 6'b001000);
    assign is_jalr = (opD == 6'b000000) && (functD == 6'b001001);
    
    assign jumpregD = is_jr | is_jalr;
    assign jalrD    = is_jalr;
    assign pcsrcD   = branchD & equalD;
    
    // JR 指令不写寄存器，JALR 需要写寄存器
    assign regwriteD = regwriteD_raw & ~is_jr;
    
    // 只有在确定发生跳转或分支时才激活 Link
    assign linkD_final = linkD & (jumpD | pcsrcD);
    assign hassignD = hassign_md | hassign_ad;

    // --- Pipeline Registers ---

    // Execute Stage (E): 包含所有 ALU 和跳转 Link 信号
    // 位宽计算: 1(memtoreg)+1(memwrite)+1(alusrc)+1(regdst)+1(regwrite)+3(alucontrol)+1(hassign)+2(hilo_en)+2(hilo_mf)+1(div)+1(islui)+2(shift)+3(mem_op)+1(link)+1(jalr) = 22 bits
    wire [2:0] mem_opE;
    wire memwriteE;
    floprc #(22) regE(
        clk, rst, flushE,
        {memtoregD, memwriteD, alusrcD, regdstD, regwriteD, alucontrolD, hassignD, hilo_enD, hilo_mfD, divD, isluiD, shiftD, mem_opD, linkD_final, jalrD},
        {memtoregE, memwriteE, alusrcE, regdstE, regwriteE, alucontrolE, hassignE, hilo_enE, hilo_mfE, divE, isluiE, shiftE, mem_opE, linkE, jalrE}
    );

    // Memory Stage (M): 包含访存信号和 Link 信号
    // 位宽计算: 1(memtoreg)+1(memwrite)+1(regwrite)+3(mem_op)+1(link)+1(jalr) = 8 bits
    flopr #(8) regM(
        clk, rst,
        {memtoregE, memwriteE, regwriteE, mem_opE, linkE, jalrE},
        {memtoregM, memwriteM, regwriteM, mem_opM, linkM, jalrM}
    );

    // Write Back Stage (W):
    // 位宽计算: 1(memtoreg)+1(regwrite)+1(link)+1(jalr) = 4 bits
    flopr #(4) regW(
        clk, rst,
        {memtoregM, regwriteM, linkM, jalrM},
        {memtoregW, regwriteW, linkW, jalrW}
    );

endmodule
