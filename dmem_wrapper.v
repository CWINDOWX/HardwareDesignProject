`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/01/28 21:07:42
// Design Name: 
// Module Name: dmem_wrapper
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


module dmem_wrapper (
    input             clk,
    input             we_i,        // 写使能
    input      [31:0] addr_i,      // CPU 传来的 32 位地址
    input      [31:0] wdata_i,     // CPU 传来的 32 位写入数据
    input      [2:0]  mem_op_i,    // 访存操作类型
    output     [31:0] rdata_o,     // 最终给 CPU 的 32 位数据
    output            adel_o,      // 地址错例外（读）
    output            ades_o       // 地址错例外（写）
);

    // 例外检查与操作解码 ---
    wire is_word_op = (mem_op_i == 3'b000);
    wire is_half_op = (mem_op_i == 3'b001) || (mem_op_i == 3'b100) || (mem_op_i == 3'b101);
    wire is_byte_op = (mem_op_i == 3'b010) || (mem_op_i == 3'b110) || (mem_op_i == 3'b111);

    wire is_store = we_i && (is_word_op || (mem_op_i == 3'b001) || (mem_op_i == 3'b010));
    wire is_load  = (~we_i) && (is_word_op || (mem_op_i == 3'b100) || (mem_op_i == 3'b101) || (mem_op_i == 3'b110) || (mem_op_i == 3'b111));

    wire word_misalign = is_word_op && (addr_i[1:0] != 2'b00);
    wire half_misalign = is_half_op && (addr_i[0] != 1'b0);

    assign adel_o = is_load  && (word_misalign || half_misalign);
    assign ades_o = is_store && (word_misalign || half_misalign);

    // 字节写使能逻辑 (生成 IP 核所需的 4-bit wea) ---
    wire [3:0] byte_we;
    assign byte_we = (mem_op_i == 3'b000) ? 4'b1111 :                                  // SW
                 (mem_op_i == 3'b001) ? (addr_i[1] ? 4'b0011 : 4'b1100) :          // SH
                 (mem_op_i == 3'b010) ? (4'b1000 >> addr_i[1:0]) :                 // SB
                 4'b0000;

    wire [3:0] final_wea = (we_i && ~ades_o) ? byte_we : 4'b0000;

    // 写数据对齐逻辑 ---
    wire [31:0] wdata_aligned;
    assign wdata_aligned = (mem_op_i == 3'b010) ? {4{wdata_i[7:0]}} :  // SB
                       (mem_op_i == 3'b001) ? {2{wdata_i[15:0]}} : // SH
                       wdata_i;                                    // SW                               // SW: 直接写

    // 实例化 IP 核 
    wire [31:0] rdata_raw;

    data_mem dmem (
        .clka  (clk),
        .wea   (final_wea),           // 4-bit 写使能
        .addra (addr_i[17:2]),        // 字节地址
        .dina  (wdata_aligned),       // 移位/复制后的数据
        .douta (rdata_raw)            // IP 核读出的原始 32 位数据
    );

    // 读数据后处理---
    // 字节选择逻辑
    wire [7:0] byte_sel = (addr_i[1:0] == 2'b00) ? rdata_raw[31:24] :
                      (addr_i[1:0] == 2'b01) ? rdata_raw[23:16] :
                      (addr_i[1:0] == 2'b10) ? rdata_raw[15:8] :
                                               rdata_raw[7:0];

    // 半字选择逻辑
    wire [15:0] halfword_sel = addr_i[1] ? rdata_raw[15:0] : rdata_raw[31:16];

    // 根据指令类型进行符号/零扩展
    reg [31:0] rdata_ext;
    always @(*) begin
        case (mem_op_i)
            3'b000:  rdata_ext = rdata_raw;                                  // LW
            3'b110:  rdata_ext = {{24{byte_sel[7]}}, byte_sel};             // LB
            3'b111:  rdata_ext = {24'b0, byte_sel};                         // LBU
            3'b100:  rdata_ext = {{16{halfword_sel[15]}}, halfword_sel};    // LH
            3'b101:  rdata_ext = {16'b0, halfword_sel};                     // LHU
            default: rdata_ext = rdata_raw;
        endcase
    end

    assign rdata_o = rdata_ext;

endmodule
