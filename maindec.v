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
	output wire islui
    );
	reg[11:0] controls;
	assign {regwrite,regdst,alusrc,branch,memwrite,memtoreg,jump,aluop,hassign,islui} = controls;
	always @(*) begin
		case (op)
            6'b000000:controls <= 12'b110000001000;	//R-TYRE
            6'b100011:controls <= 12'b101001000000;	//LW
            6'b101011:controls <= 12'b001010000000;	//SW
            6'b000100:controls <= 12'b000100000100;	//BEQ
            6'b001000:controls <= 12'b101000000010;	//ADDI
            6'b001001:controls <= 12'b101000000000;	//ADDIU
            6'b001010:controls <= 12'b101000001110;	//SLTI
            6'b001011:controls <= 12'b101000001100;	//SLTIU
			6'b001100:controls <= 12'b101000010000;	//ANDI
			6'b001101:controls <= 12'b101000010100;	//ORI
			6'b001110:controls <= 12'b101000011000;	//XORI
			6'b001111:controls <= 12'b101000000001;	//lui
            
            6'b000010:controls <= 12'b000000100000;//J
            default:  controls <= 12'b000000000000;//illegal op
		endcase
	end
endmodule
