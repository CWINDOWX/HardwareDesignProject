module ShiftUnit (
    input  [31:0] rt_i,      // 来自rt寄存器的值
    input  [31:0] rs_i,      // 来自rs寄存器的值（变量移位用）
    input  [4:0]  shamt_i,   // 立即数移位量 (指令[10:6])
    input         var_shift, // 0:使用shamt, 1:使用rs
    input  [1:0]  shift_type,// 00:SLL, 01:SRL, 10:SRA
    output [31:0] result_o
);

    wire [4:0] shift_amount;
    assign shift_amount = var_shift ? rs_i[4:0] : shamt_i;

    reg [31:0] result;
    always @(*)
    begin
        case (shift_type)
            2'b00: // SLL - 逻辑左移
                result = rt_i << shift_amount;
            2'b01: // SRL - 逻辑右移
                result = rt_i >> shift_amount;
            2'b10: // SRA - 算术右移
                result = $signed(rt_i) >>> shift_amount;
            default:
                result = rt_i;
        endcase
    end

    assign result_o = result;

endmodule