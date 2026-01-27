`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: CP0_Reg
// Description: CP0协处理器寄存器 - 异常处理和特权指令支持
//////////////////////////////////////////////////////////////////////////////////

module CP0_Reg (
    input         clk,
    input         rst,

    // 读写接口 (MFC0/MTCO指令)
    input         we,          // 写使能 <- MTC0
    input  [4:0]  addr,        // 寄存器地址
    input  [31:0] wdata,       // 写入数据
    output reg [31:0] rdata,       // 读取数据 -> MFC0

    // verilator lint_off UNUSEDSIGNAL
    // 异常处理接口
    input         eret,        // ERET信号 <- Control
    input  [31:0] epc_i,       // EPC输入 <- 流水线(异常指令地址)
    input  [5:0]  cause_i,     // 异常原因 <- Trap_Detect
    input         syscall_i,   // SYSCALL <- Trap_Detect
    input         break_i,     // BREAK <- Trap_Detect

    // 输出接口
    output [31:0] epc_o,       // EPC输出 -> PC_Mux
    output [5:0]  cause_o,     // 异常原因输出 (ExcCode字段)
    output        exception_o  // 异常发生信号 -> 流水线
);

    // CP0寄存器地址 (来自3-4对接_1.md)
    localparam ADDR_BADVADDR = 5'd8;   // BadVAddr - 错误虚拟地址
    localparam ADDR_COUNT    = 5'd9;   // Count - 计数器
    localparam ADDR_STATUS   = 5'd12;  // Status - 状态寄存器
    localparam ADDR_CAUSE    = 5'd13;  // Cause - 异常原因
    localparam ADDR_EPC      = 5'd14;  // EPC - 异常程序计数器

    // 异常发生条件
    wire exception = syscall_i || break_i;

    // 异常类型 (trap_cause)
    wire [5:0] trap_cause = syscall_i ? 6'd8 :   // Sys = 8
                           break_i  ? 6'd9 :    // Bp = 9
                           cause_i;              // 其他异常

    // EPC寄存器
    reg [31:0] epc_reg;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            epc_reg <= 32'd0;
        end else if (exception) begin
            epc_reg <= epc_i;  // 保存异常指令地址
        end else if (we && addr == ADDR_EPC) begin
            epc_reg <= wdata;  // MTC0手动写EPC
        end
    end

    // Cause寄存器 (只写，保存异常原因)
    reg [31:0] cause_reg;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            cause_reg <= 32'd0;
        end else if (exception) begin
            // Cause = {26'd0, trap_cause, 5'd0}
            cause_reg <= {26'd0, trap_cause};
        end else if (we && addr == ADDR_CAUSE) begin
            cause_reg <= wdata;  // MTC0手动写Cause
        end
    end

    // Status寄存器 (简化版)
    reg [31:0] status_reg;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            status_reg <= 32'd0;
        end else if (we && addr == ADDR_STATUS) begin
            status_reg <= wdata;  // MTC0手动写Status
        end
    end

    // Count寄存器 (简化计数器)
    reg [31:0] count_reg;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            count_reg <= 32'd0;
        end else begin
            count_reg <= count_reg + 32'd1;
        end
    end

    // BadVAddr寄存器 (简化，保存错误地址)
    reg [31:0] badvaddr_reg;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            badvaddr_reg <= 32'd0;
        end else if (exception) begin
            badvaddr_reg <= epc_i;  // 简化：保存PC
        end
    end

    // 读数据多路选择 (MFC0)
    always @(*) begin
        case (addr)
            ADDR_BADVADDR: rdata = badvaddr_reg;
            ADDR_COUNT:    rdata = count_reg;
            ADDR_STATUS:   rdata = status_reg;
            ADDR_CAUSE:    rdata = cause_reg;
            ADDR_EPC:      rdata = epc_reg;
            default:       rdata = 32'd0;
        endcase
    end

    // 输出信号
    assign epc_o = epc_reg;
    assign cause_o = cause_reg[5:0];  // ExcCode字段 (低6位)
    assign exception_o = exception;

endmodule
