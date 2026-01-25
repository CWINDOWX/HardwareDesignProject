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
	output reg hassign,
    output reg[1:0] hilo_en,
    output reg[1:0] hilo_mf,
    output reg div
    );
	always @(*) begin
        hassign <= 1'b0;
        hilo_en <= 2'b10;   //10表示不写hilo寄存器，11表示写HI和LO，01表示写HI，00表示写LO
        hilo_mf <= 2'b10;   //01表示HI写寄存器，00表示LO写寄存器
        div <= 1'b0;
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
                end
                6'b100010: begin    //SUB
                    alucontrol <= 3'b110; //sub
                    hassign <= 1'b1;
                end
                6'b100011: begin    //SUBU
                    alucontrol <= 3'b110; //sub
                end
                6'b100100: begin    //AND
                    alucontrol <= 3'b000; //and
                end
                6'b100101: begin    //OR
                    alucontrol <= 3'b001; //or
                end
                6'b101010: begin    //SLT
                    alucontrol <= 3'b111; //slt
                    hassign <= 1'b1;    
                end
                6'b101011: begin    //SLTU
                    alucontrol <= 3'b111; //slt
                end
                6'b011000: begin    //MULT
                    alucontrol <= 3'b100; //mult
                    hassign <= 1'b1;
                    hilo_en <= 2'b11;
                end
                6'b011001:begin     //MULTU
                    alucontrol <= 3'b100; //mult
                    hilo_en <= 2'b11;
                end
                6'b010000:begin     //MFHI
                    alucontrol <= 3'b000; //不做计算
                    hilo_mf <= 2'b01;
                end
                6'b010010:begin     //MFLO
                    alucontrol <= 3'b000; //不做计算
                    hilo_mf <= 2'b00;      
                end
                6'b010001:begin     //MTHI
                    alucontrol <= 3'b000;
                    hilo_en <= 2'b01;
                end
                6'b010011:begin     //MTLO
                    alucontrol <= 3'b000;
                    hilo_en <= 2'b00;
                end
                6'b011010:begin     //DIV
                    alucontrol <= 3'b000;
                    div <= 1'b1;
                    hassign <= 1'b1;
                end
                6'b011011:begin     //DIVU
                    alucontrol <= 3'b000;
                    div <= 1'b1;
                    hassign <= 1'b0;
                end
                default: begin 
                    alucontrol <= 3'b000;
                end
			endcase
		endcase
	
	end
endmodule
