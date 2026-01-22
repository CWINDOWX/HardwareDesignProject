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
	output wire[1:0] aluop,
	output wire hassign
    );
	reg[9:0] controls;
	assign {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump,aluop,hassign} = controls;
	always @(*) begin
		case (op)
            6'b000000:controls <= 10'b1100000100;//R-TYRE
            6'b100011:controls <= 10'b1010010000;//LW
            6'b101011:controls <= 10'b0010100000;//SW
            6'b000100:controls <= 10'b0001000010;//BEQ
            6'b001000:controls <= 10'b1010000001;//ADDI
            6'b001001:controls <= 10'b1010000000;//ADDIU
            6'b001010:controls <= 10'b1010000111;//SLTI
            6'b001011:controls <= 10'b1010000110;//SLTIU
            
            6'b000010:controls <= 10'b0000001000;//J
            default:  controls <= 10'b0000000000;//illegal op
		endcase
	end
endmodule
