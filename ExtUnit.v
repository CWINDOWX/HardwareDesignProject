module ExtUnit (
    input  [15:0] imm,       // 立即数
    input         sign_ext,  // 1:符号扩展, 0:零扩展
    output [31:0] ext_result
);

    assign ext_result = sign_ext ? {{16{imm[15]}}, imm} : {16'b0, imm};

endmodule