module ExtUnit (
    input  [15:0] imm,
    input  [1:0]  ext_type,
    output [31:0] ext_result
);

    // 扩展类型：
    // 00: 符号扩展 (默认)
    // 01: 零扩展 (ANDI/ORI/XORI)
    // 10: 符号扩展 (LB/LH)
    // 11: 零扩展 (LBU/LHU)

    assign ext_result = (ext_type == 2'b00) ? {{16{imm[15]}}, imm} :  // 符号扩展
                        (ext_type == 2'b01) ? {16'b0, imm} :          // 零扩展
                        (ext_type == 2'b10) ? {{16{imm[15]}}, imm} :  // 符号扩展
                        {16'b0, imm};                                 // 零扩展

endmodule