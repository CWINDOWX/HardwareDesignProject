`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/01/25 18:57:35
// Design Name: 
// Module Name: divider
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


module divider(
    input clk,rst,en,hassign,
    input wire [31:0] a,    //被除数
    input wire [31:0] b,    //除数
    output reg [31:0] q,    //商
    output reg [31:0] r,    //余数
    output reg busy,done   //结束和忙碌
    );

    // 状态定义
    localparam IDLE = 1'b0;
    localparam CALC = 1'b1;

    wire [32:0] res = {1'b0,s[62:31]} - {1'b0,divisor}; 

    reg state;
    reg [63:0] s;          //存储被除数和商
    reg [31:0] divisor;    //除数
    reg [5:0]cnt;
    reg sign_q,sign_r;

    always @(posedge clk,posedge rst) begin
		if(rst) begin
            state <= IDLE;
            busy <= 1'b0;
			q <= 32'b0;
            r <= 32'b0;
		end else begin
            case(state)
                IDLE: begin
                    done <= 1'b0;
                    if(en) begin
                        if(hassign) begin
                            s <= {32'b0, (a[31] ? (~a + 1'b1) : a)};
                            divisor <= (b[31] ? (~b + 1'b1) : b);
                            sign_q <= a[31] ^ b[31];
                            sign_r <= a[31];
                        end else begin
                            s <= {32'b0, a};
                            divisor <= b;
                            sign_q <= 1'b0;
                            sign_r <= 1'b0;
                        end
                        busy  <= 1'b1;
                        cnt   <= 6'b0;
                        state <= CALC;
                    end
                end

                CALC: begin
                        if (cnt < 32) begin
                            if (res[32]) begin
                                s <= {s[62:0],1'b0};
                            end else begin
                                s <= {res[31:0],s[30:0],1'b1}; 
                            end
                            cnt <= cnt + 1'b1;
                            
                        end 
                        else begin     
                            done <= 1'b1;
                            busy <= 1'b0;
                            state <= IDLE;
                        end
                    end
            endcase
         
		end
	end

    always @(*) begin
        if (done) begin
            q = (sign_q) ? (~s[31:0] + 1'b1) : s[31:0];
            r = (sign_r) ? (~s[63:32] + 1'b1) : s[63:32];
        end else begin
            q = 32'b0;
            r = 32'b0;
        end
    end

endmodule
