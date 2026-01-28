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
	input wire[5:0] op,
	output reg[2:0] alucontrol,
	output reg hassign,
    output reg[1:0] hilo_en,
    output reg[1:0] hilo_mf,
    output reg div,
    // 移位相关控制信号
    output reg shift,
    output reg[1:0] shift_type,
    output reg var_shift
    );
	always @(*) begin
        hassign <= 1'b0;
        hilo_en <= 2'b10;   //10表示不写hilo寄存器，11表示写HI和LO，01表示写HI，00表示写LO
        hilo_mf <= 2'b10;   //01表示HI写寄存器，00表示LO写寄存器
        div <= 1'b0;
        // 初始化移位相关信号
        shift <= 1'b0;
        shift_type <= 2'b00;
        var_shift <= 1'b0;
        case (aluop)
            2'b00: begin
                // handle LUI (load upper immediate) specially: produce a dedicated ALU code
                if (op == 6'b001111) begin
                    alucontrol <= 3'b101; // custom code for LUI
                end else begin
                    alucontrol <= 3'b010; // add (for lw/sw/addi/addiu)
                end
            end
			2'b01: alucontrol <= 3'b110;//sub (for beq)
			2'b11: alucontrol <= 3'b111;//slt
			default : begin // aluop 10
                if (op == 6'b000000) begin // R-type instructions
                    case (funct)
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
                        6'b100110: begin    //XOR
                            alucontrol <= 3'b111; //xor
                        end
                        6'b100111: begin    //NOR
                            alucontrol <= 3'b011; //nor (custom code)
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
                        // 移位指令
                        6'b000000: begin    // SLL
                            alucontrol <= 3'b000;
                            shift <= 1'b1;
                            shift_type <= 2'b00; // SLL
                            var_shift <= 1'b0;  // 使用shamt
                        end
                        6'b000010: begin    // SRL
                            alucontrol <= 3'b000;
                            shift <= 1'b1;
                            shift_type <= 2'b01; // SRL
                            var_shift <= 1'b0;  // 使用shamt
                        end
                        6'b000011: begin    // SRA
                            alucontrol <= 3'b000;
                            shift <= 1'b1;
                            shift_type <= 2'b10; // SRA
                            var_shift <= 1'b0;  // 使用shamt
                        end
                        6'b000100: begin    // SLLV
                            alucontrol <= 3'b000;
                            shift <= 1'b1;
                            shift_type <= 2'b00; // SLL
                            var_shift <= 1'b1;  // 使用rs
                        end
                        6'b000110: begin    // SRLV
                            alucontrol <= 3'b000;
                            shift <= 1'b1;
                            shift_type <= 2'b01; // SRL
                            var_shift <= 1'b1;  // 使用rs
                        end
                        6'b000111: begin    // SRAV
                            alucontrol <= 3'b000;
                            shift <= 1'b1;
                            shift_type <= 2'b10; // SRA
                            var_shift <= 1'b1;  // 使用rs
                        end
                        default: begin 
                            alucontrol <= 3'b000;
                        end
                    endcase
                end else begin // I-type instructions
                    case (op)
                        6'b001100: alucontrol <= 3'b000; // ANDI
                        6'b001101: alucontrol <= 3'b001; // ORI
                        6'b001110: alucontrol <= 3'b111; // XORI
                        default: alucontrol <= 3'b000;
                    endcase
                end
            end
		endcase
	
	end
endmodule
