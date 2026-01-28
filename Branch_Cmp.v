`timescale 1ns / 1ps

/*
 * Branch_Cmp.v
 * 分支比较器 - 比较两个寄存器的值，判断分支是否成立
 * Member 4: 成员4
 */

module Branch_Cmp(
    input  [31:0] a,          // 第一个操作数（rs）
    input  [31:0] b,          // 第二个操作数（rt）
    input  [2:0]  cmp_op,     // 比较操作类型
    output reg    cmp_result  // 比较结果（1:分支, 0:不分支）
);

// 比较操作定义：
// 000: BEQ  - 相等则分支 (a == b)
// 001: BNE  - 不等则分支 (a != b)
// 010: BGTZ - 大于0则分支 (a > 0)
// 011: BLEZ - 小于等于0则分支 (a <= 0)
// 100: BLTZ - 小于0则分支 (a < 0)
// 101: BGEZ - 大于等于0则分支 (a >= 0)

always @(*) begin
    case (cmp_op)
        3'b000:  cmp_result = (a == b);                           // BEQ
        3'b001:  cmp_result = (a != b);                           // BNE
        3'b010:  cmp_result = (~a[31]) & (a != 32'h00000000);    // BGTZ: 正数且非0
        3'b011:  cmp_result = a[31] | (a == 32'h00000000);       // BLEZ: 负数或0
        3'b100:  cmp_result = a[31];                             // BLTZ: 符号位=1
        3'b101:  cmp_result = ~a[31];                            // BGEZ: 符号位=0
        default: cmp_result = 1'b0;
    endcase
end

endmodule