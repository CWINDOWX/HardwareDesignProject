// 成员3可独立测试模块聚合顶层（Verilator）
`timescale 1ns/1ps

module top (
    // ExtUnit
    input  wire [15:0] ext_imm,
    input  wire [1:0]  ext_type,
    output wire [31:0] ext_result,

    // DM
    input  wire        dm_clk,
    input  wire        dm_rst,
    input  wire [31:0] dm_addr,
    input  wire [31:0] dm_wdata,
    input  wire        dm_we,
    input  wire [2:0]  dm_mem_op,
    output wire [31:0] dm_rdata,
    output wire        dm_adel,
    output wire        dm_ades,

    // Trap_Detect
    input  wire [31:0] trap_instr,
    output wire        trap_syscall,
    output wire        trap_break,
    output wire [5:0]  trap_type,

    // CP0_Reg
    input  wire        cp0_clk,
    input  wire        cp0_rst,
    input  wire        cp0_we,
    input  wire [4:0]  cp0_addr,
    input  wire [31:0] cp0_wdata,
    input  wire        cp0_exc_valid,
    input  wire [4:0]  cp0_exc_code,
    input  wire [31:0] cp0_pc_i,
    input  wire        cp0_in_delay_slot,
    input  wire [31:0] cp0_badvaddr_i,
    input  wire        cp0_eret,
    input  wire [5:0]  cp0_hw_int,
    output wire [31:0] cp0_rdata,
    output wire [31:0] cp0_epc_o,
    output wire        cp0_exl_o,
    output wire [31:0] cp0_status_o,
    output wire [31:0] cp0_cause_o,
    output wire [31:0] cp0_badvaddr_o
);

    ExtUnit u_extunit (
        .imm(ext_imm),
        .ext_type_i(ext_type),
        .ext_result(ext_result)
    );

    DM u_dm (
        .clk(dm_clk),
        .rst(dm_rst),
        .addr_i(dm_addr),
        .wdata_i(dm_wdata),
        .we_i(dm_we),
        .mem_op_i(dm_mem_op),
        .rdata_o(dm_rdata),
        .adel_o(dm_adel),
        .ades_o(dm_ades)
    );

    Trap_Detect u_trap_detect (
        .instr(trap_instr),
        .is_syscall(trap_syscall),
        .is_break(trap_break),
        .trap_type(trap_type)
    );

    CP0_Reg u_cp0 (
        .clk(cp0_clk),
        .rst(cp0_rst),
        .we(cp0_we),
        .waddr(cp0_addr),
        .raddr(cp0_addr),
        .wdata(cp0_wdata),
        .rdata(cp0_rdata),
        .exc_valid_i(cp0_exc_valid),
        .exc_code_i(cp0_exc_code),
        .pc_i(cp0_pc_i),
        .in_delay_slot_i(cp0_in_delay_slot),
        .badvaddr_i(cp0_badvaddr_i),
        .eret_i(cp0_eret),
        .hw_int_i(cp0_hw_int),
        .epc_o(cp0_epc_o),
        .exl_o(cp0_exl_o),
        .status_o(cp0_status_o),
        .cause_o(cp0_cause_o),
        .badvaddr_o(cp0_badvaddr_o)
    );

endmodule
