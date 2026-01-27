`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: instr_mem
// Description: 指令存储器 - 从COE文件初始化，支持10条指令测试
//////////////////////////////////////////////////////////////////////////////////

module instr_mem (
    input  [31:0] addr,    // 指令地址 (PC)
    output [31:0] instr    // 指令输出
);

    // 64字指令存储器 (256字节)
    reg [31:0] instr_rom [0:63];

    // 初始化：读取COE文件
    initial begin
        $readmemh("instructions.coe", instr_rom);
    end

    // 组合逻辑：地址[9:2]用于字索引
    // 假设PC是字节地址，需要转换为字地址
    assign instr = instr_rom[addr[9:2]];

endmodule
