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
	input wire[4:0] rt,
	input wire[5:0] funct,  // ← 新增：用于检测 JR/JALR

	output wire memtoreg,memwrite,
	output wire branch,alusrc,
	output wire regdst,regwrite,
	output wire jump,
	output wire[1:0] aluop,
	output wire[2:0] branch_op,
	output wire link
);

	reg[12:0] controls;
	assign {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump,aluop,branch_op,link} = controls;
	
	always @(*) begin
		case (op)
			// R-Type 指令
			6'b000000: controls <= 13'b110000010_000_0; // R-TYPE
			
			// 访存指令
			6'b100011: controls <= 13'b101001000_000_0; // LW
			6'b101011: controls <= 13'b001010000_000_0; // SW
			
			// 分支指令
			6'b000100: controls <= 13'b000100001_000_0; // BEQ
			6'b000101: controls <= 13'b000100001_001_0; // BNE
			6'b000111: controls <= 13'b000100001_010_0; // BGTZ
			6'b000110: controls <= 13'b000100001_011_0; // BLEZ
			
			// REGIMM 指令族
			6'b000001: begin
				case (rt)
					5'b00000: controls <= 13'b000100001_100_0; // BLTZ
					5'b00001: controls <= 13'b000100001_101_0; // BGEZ
					5'b10000: controls <= 13'b100100001_100_1; // BLTZAL
					5'b10001: controls <= 13'b100100001_101_1; // BGEZAL
					default:  controls <= 13'b000000000_000_0;
				endcase
			end
			
			// I-type 算术/逻辑指令
			6'b001000: controls <= 13'b101000000_000_0; // ADDI
			6'b001001: controls <= 13'b101000000_000_0; // ADDIU
			6'b001100: controls <= 13'b101000011_000_0; // ANDI
			6'b001101: controls <= 13'b101000011_000_0; // ORI
			6'b001110: controls <= 13'b101000011_000_0; // XORI
			6'b001010: controls <= 13'b101000000_000_0; // SLTI
			6'b001011: controls <= 13'b101000000_000_0; // SLTIU
			6'b001111: controls <= 13'b101000000_000_0; // LUI
			
			// 跳转指令
			6'b000010: controls <= 13'b000000100_000_0; // J
			6'b000011: controls <= 13'b100000100_000_1; // JAL
			
			default:   controls <= 13'b000000000_000_0;
		endcase
	end
endmodule