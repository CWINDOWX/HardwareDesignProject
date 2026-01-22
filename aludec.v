`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/10/23 15:27:24
// Design Name: 
// Module Name: aludec
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


module aludec(
	input wire[5:0] funct,
	input wire[1:0] aluop,
	output reg[2:0] alucontrol,
	output reg hassign
    );
	always @(*) begin
		case (aluop)
			2'b00: alucontrol <= 3'b010;//add (for lw/sw/addi/addiu)
			2'b01: alucontrol <= 3'b110;//sub (for beq)
			2'b11: alucontrol <= 3'b111;//slt
			default : case (funct)
                6'b100000:    begin    //ADD
                    alucontrol <= 3'b010; //add
                    hassign <= 1'b1;
                end
                6'b100001: begin    //ADDU
                    alucontrol <= 3'b010; //add
                    hassign <= 1'b0;
                end
                6'b100010: begin    //SUB
                    alucontrol <= 3'b110; //sub
                    hassign <= 1'b1;
                end
                6'b100011: begin    //SUBU
                    alucontrol <= 3'b110; //sub
                    hassign <= 1'b0;
                end
                6'b100100: begin    //AND
                    alucontrol <= 3'b000; //and
                    hassign <= 1'b0;
                end
                6'b100101: begin    //OR
                    alucontrol <= 3'b001; //or
                    hassign <= 1'b0;
                end
                6'b101010: begin    //SLT
                    alucontrol <= 3'b111; //slt
                    hassign <= 1'b1;    
                end
                6'b101011: begin    //SLTU
                    alucontrol <= 3'b011; //slt
                    hassign <= 1'b0;
                end
                6'b011000: begin    //MULT
                    alucontrol <= 3'b100; //mult
                    hassign <= 1'b1;
                end
                6'b011001:begin        //MULTU
                    alucontrol <= 3'b100; //mult
                    hassign <= 1'b0;
                end
                default: begin 
                    alucontrol <= 3'b000;
                    hassign <= 1'b0;
                end
			endcase
		endcase
	
	end
endmodule
