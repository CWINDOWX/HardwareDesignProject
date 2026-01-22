`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/02 14:52:16
// Design Name: 
// Module Name: alu
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


module alu(
	input wire[31:0] a,b,
	input wire[2:0] op,
	input wire hassign, //判断是不是有符号的计算
	output reg[31:0] y,
	output reg overflow,
	output wire zero
    );

	wire[31:0] s,bout;
	assign bout = op[2] ? ~b : b;
	assign s = a + bout + op[2];
	always @(*) begin
		case (op[1:0])
			2'b00: begin        // 000做AND，100做乘法相关运算
                if(op[2]) begin
                    if(hassign) begin
                        y <= $signed(a) * $signed(b);
                    end
                    else begin
                        y <= {32'b0, a} * {32'b0, b};
                    end
                end
                else begin
                    y <= a & bout;
                end
            end

            2'b01: y <= a | bout;
            2'b10: y <= s;

            2'b11: begin    // 111做SLT，011做SLTU
                if(hassign) begin
                    y <= s[31] ^ ((~a[31] & b[31] & s[31] | a[31] & ~b[31] & ~s[31]));    // 不能直接用overflow，为了避免产生异常
                end
                else begin
                    y <= a < b;
                end
            end
		endcase	
	end
	assign zero = (y == 32'b0);

	always @(*) begin
		case (op)
			3'b010:overflow <= a[31] & b[31] & ~s[31] |
							~a[31] & ~b[31] & s[31];
			3'b110:overflow <= ~a[31] & b[31] & s[31] |
							a[31] & ~b[31] & ~s[31];
			default : overflow <= 1'b0;
		endcase	
	end
endmodule
