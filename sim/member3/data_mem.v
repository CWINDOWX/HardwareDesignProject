`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: data_mem
// Description: 数据存储器 - 从COE文件初始化，支持字节/半字/字访存
//////////////////////////////////////////////////////////////////////////////////

module data_mem (
    input         clk,
    input  [31:0] addr,       // 访存地址
    input  [31:0] wdata,      // 写入数据
    input         we,         // 写使能
    input  [2:0]  mem_op,     // 访存操作类型 (000=LW/SW, 001=SH, 010=SB, 100=LH, 101=LHU, 110=LB, 111=LBU)
    output [31:0] rdata       // 读出数据
);

    // 64字数据存储器 (256字节)
    reg [31:0] data_ram [0:63];

    // 初始化：读取COE文件
    initial begin
        $readmemh("data_memory.coe", data_ram);
    end

    // 写操作：时钟上升沿
    wire [5:0] word_addr = addr[7:2];
    wire [3:0] byte_we;

    // 字节写使能生成
    assign byte_we = (mem_op == 3'b000) ? 4'b1111 :                    // SW: 全部4字节
                     (mem_op == 3'b001 || mem_op == 3'b100 || mem_op == 3'b101) ?
                       (addr[1] ? 4'b1100 : 4'b0011) :               // SH/LH/LHU: 半字
                     (mem_op == 3'b010 || mem_op == 3'b110 || mem_op == 3'b111) ?
                       (4'b0001 << addr[1:0]) :                       // SB/LB/LBU: 单字节
                     4'b0000;

    always @(posedge clk) begin
        if (we) begin
            if (byte_we[0]) data_ram[word_addr][7:0]   <= wdata[7:0];
            if (byte_we[1]) data_ram[word_addr][15:8]  <= wdata[15:8];
            if (byte_we[2]) data_ram[word_addr][23:16] <= wdata[23:16];
            if (byte_we[3]) data_ram[word_addr][31:24] <= wdata[31:24];
        end
    end

    // 读操作：组合逻辑 + 字节/半字选择
    wire [31:0] raw_data = data_ram[word_addr];
    wire [7:0] byte_sel;
    wire [15:0] halfword_sel;

    assign byte_sel = (addr[1:0] == 2'b00) ? raw_data[7:0] :
                      (addr[1:0] == 2'b01) ? raw_data[15:8] :
                      (addr[1:0] == 2'b10) ? raw_data[23:16] :
                                             raw_data[31:24];

    assign halfword_sel = addr[1] ? raw_data[31:16] : raw_data[15:0];

    // 读数据扩展
    assign rdata = (mem_op == 3'b000) ? raw_data :                                      // LW
                   (mem_op == 3'b110) ? {{24{byte_sel[7]}}, byte_sel} :                 // LB
                   (mem_op == 3'b111) ? {24'b0, byte_sel} :                             // LBU
                   (mem_op == 3'b100) ? {{16{halfword_sel[15]}}, halfword_sel} :        // LH
                   (mem_op == 3'b101) ? {16'b0, halfword_sel} :                         // LHU
                   raw_data;                                                             // SW或其他

endmodule
