`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/10/23 15:21:30
// Design Name: 
// Module Name: maindec
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


module maindec(
	input wire[5:0] op,

	output wire memtoreg,memwrite,
	output wire branch,alusrc,
	output wire regdst,regwrite,
	output wire jump,
	output wire[2:0] aluop,
	output wire hassign,
	output wire islui,
	output wire[2:0] mem_op
    );
	reg[14:0] controls;
	assign {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump,aluop,hassign,islui,mem_op} = controls;
	always @(*) begin
		case (op)
            // 标准指令
            6'b000000: controls <= 15'b1100000_010_0_0_000; // R-TYPE
            6'b100011: controls <= 15'b1010010_000_0_0_000; // LW (mem_op 000)
            6'b101011: controls <= 15'b0110100_000_0_0_000; // SW (mem_op 000)
            6'b000100: controls <= 15'b0001000_001_0_0_000; // BEQ
            6'b001000: controls <= 15'b1010000_000_0_0_000; // ADDI
            6'b001001: controls <= 15'b1010000_000_0_0_000; // ADDIU
            6'b001111: controls <= 15'b1010000_000_0_1_000; // LUI
            6'b000010: controls <= 15'b0000001_000_0_0_000; // J

            // 加载指令 (Load)
            6'b100000: controls <= 15'b1010010_000_0_0_110; // LB  (mem_op 110)
            6'b100100: controls <= 15'b1010010_000_0_0_111; // LBU (mem_op 111)
            6'b100001: controls <= 15'b1010010_000_0_0_100; // LH  (mem_op 100)
            6'b100101: controls <= 15'b1010010_000_0_0_101; // LHU (mem_op 101)

            // 存储指令 (Store)
            6'b101000: controls <= 15'b0010100_000_0_0_010; // SB  (mem_op 010)
            6'b101001: controls <= 15'b0010100_000_0_0_001; // SH  (mem_op 001)

            // I型指令
            6'b001010: controls <= 15'b1010000_011_1_0_000; // SLTI
            6'b001011: controls <= 15'b1010000_011_0_0_000; // SLTIU
            6'b001100: controls <= 15'b1010000_100_0_0_000; // ANDI
            6'b001101: controls <= 15'b1010000_101_0_0_000; // ORI
            6'b001110: controls <= 15'b1010000_110_0_0_000; // XORI

            default:   controls <= 15'b0000000_000_0_0_000; // illegal op
		endcase
	end
endmodule
