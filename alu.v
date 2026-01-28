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
	input wire hassign, //判断是不是有符号的计�?
	output reg[31:0] y,
	output reg[31:0] y_lo, //做乘除法时需要用到，结果的低32�?
	output reg overflow,
	output wire zero
    );

	wire[31:0] s,bout;
	assign bout = op[2] ? ~b : b;
	assign s = a + bout + op[2];
	always @(*) begin
		y_lo <= 32'b0;
		// special ALU operation: 3'b101 means LUI (load upper immediate)
		if (op == 3'b101) begin
			y <= {b[15:0], 16'b0};
		end
		// special NOR operation assigned to 3'b011
		else if (op == 3'b011) begin
			y <= ~(a | b);
		end else begin
		case (op[1:0])
			2'b00: begin        // 000做AND�?100做乘法相关运�?
                if(op[2]) begin
                    if(hassign) begin
                        {y,y_lo} <= $signed(a) * $signed(b);
                    end
                    else begin
                        {y,y_lo} <= {32'b0, a} * {32'b0, b};
                    end
                end
                else begin
                    y <= a & bout;
                end
            end

            2'b01: y <= a | bout;
            2'b10: y <= s;

            2'b11: begin 
				if(op[2]) begin
					y <= a ^ b; // XOR operation (use original b, not bout)
                end
                else if(hassign) begin
                    y <= s[31] ^ ((~a[31] & b[31] & s[31] | a[31] & ~b[31] & ~s[31]));    // 不能直接用overflow，为了避免产生异�?
                end
                else begin
                    y <= a < b;
                end
            end
		endcase	
		end
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
