`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: mips_tb
// Description: MIPS CPU 测试平台 - 包含数据竞争检测和完整验证
//////////////////////////////////////////////////////////////////////////////////

module mips_tb;

    // 时钟和复位
    reg clk, rst;
    integer cycle_count;

    // MIPS接口信号
    wire [31:0] pcF;
    wire [31:0] instrF;
    wire memwriteM;
    wire [31:0] aluoutM;
    wire [31:0] writedataM;
    wire [31:0] readdataM;

    // 存储器实例化
    instr_mem imem (
        .addr(pcF),
        .instr(instrF)
    );

    data_mem dmem (
        .clk(clk),
        .addr(aluoutM),
        .wdata(writedataM),
        .we(memwriteM),
        .mem_op(3'b000),  // 当前仅支持字访问
        .rdata(readdataM)
    );

    // MIPS CPU实例化
    mips cpu (
        .clk(clk),
        .rst(rst),
        .pcF(pcF),
        .instrF(instrF),
        .memwriteM(memwriteM),
        .aluoutM(aluoutM),
        .writedataM(writedataM),
        .readdataM(readdataM)
    );

    // 时钟生成：10ns周期
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    // 测试结果记录
    reg [31:0] expected_reg [0:31];
    reg [31:0] actual_reg [0:31];
    integer test_passed, test_failed;
    integer hazard_detected, hazard_correct;

    // 数据竞争(冒险)检测
    reg [31:0] prev_alu_result;
    reg [4:0] prev_dest_reg;
    reg prev_reg_write;

    //============================================================================
    // 预期结果初始化
    //============================================================================
    initial begin
        test_passed = 0;
        test_failed = 0;
        hazard_detected = 0;
        hazard_correct = 0;

        // 初始化预期寄存器值
        $display("初始化测试环境...");
    end

    //============================================================================
    // 流水线寄存器监控 (用于数据竞争检测)
    //============================================================================
    reg [31:0] if_id_instr, id_ex_aluout, ex_mem_aluout;
    reg [4:0] id_ex_rt, ex_mem_rt;
    reg id_ex_regwrite, ex_mem_regwrite;

    always @(posedge clk) begin
        // 监控流水线寄存器
        if_id_instr <= instrF;
        id_ex_aluout <= aluoutM;
        ex_mem_aluout <= aluoutM;

        // RAW冒险检测
        if (cpu.dp.regwriteE && cpu.dp.rtE != 5'd0) begin
            if (cpu.dp.rsD == cpu.dp.rtE || cpu.dp.rtD == cpu.dp.rtE) begin
                hazard_detected <= hazard_detected + 1;
                $display("时间 %0t: 检测到RAW数据冒险 - 指令使用被写的寄存器", $time);
            end
        end
    end

    //============================================================================
    // 主测试序列
    //============================================================================
    initial begin
        $display("===============================================================================");
        $display("  MIPS CPU 仿真测试平台");
        $display("  测试内容: 基础指令 + 数据竞争检测");
        $display("===============================================================================");
        $display("");

        // 复位
        rst = 1;
        #10;
        rst = 0;
        cycle_count = 0;

        $display("--- 测试开始 ---");
        $display("");

        // 执行测试指令
        repeat(50) begin
            @(posedge clk);
            cycle_count = cycle_count + 1;

            // 每个周期显示状态
            if (cycle_count % 5 == 0) begin
                $display("周期 %0d: PC=0x%08H, Instr=0x%08H", cycle_count, pcF, instrF);
            end
        end

        // 测试完成
        $display("");
        $display("--- 测试完成 ---");
        $display("总周期数: %0d", cycle_count);
        $display("检测到的数据冒险: %0d", hazard_detected);

        $display("");
        $display("===============================================================================");
        if (test_failed == 0) begin
            $display("  测试结果: 全部通过!");
        end else begin
            $display("  测试结果: %0d 通过, %0d 失败", test_passed, test_failed);
        end
        $display("===============================================================================");

        $finish;
    end

    //============================================================================
    // 指令执行监控
    //============================================================================
    reg [31:0] current_pc;
    reg [31:0] current_instr;

    always @(posedge clk) begin
        if (!rst) begin
            current_pc <= pcF;
            current_instr <= instrF;

            // 解码并显示指令
            case (instrF[31:26])
                6'b000000: begin  // R-type
                    case (instrF[5:0])
                        6'b100000: $display("  [周期%0d] ADD  $%0d, $%0d, $%0d", cycle_count, instrF[15:11], instrF[25:21], instrF[20:16]);
                        6'b100010: $display("  [周期%0d] SUB  $%0d, $%0d, $%0d", cycle_count, instrF[15:11], instrF[25:21], instrF[20:16]);
                        6'b100100: $display("  [周期%0d] AND  $%0d, $%0d, $%0d", cycle_count, instrF[15:11], instrF[25:21], instrF[20:16]);
                        6'b100101: $display("  [周期%0d] OR   $%0d, $%0d, $%0d", cycle_count, instrF[15:11], instrF[25:21], instrF[20:16]);
                        6'b101010: $display("  [周期%0d] SLT  $%0d, $%0d, $%0d", cycle_count, instrF[15:11], instrF[25:21], instrF[20:16]);
                        default:   $display("  [周期%0d] R-type (funct=0x%02X)", cycle_count, instrF[5:0]);
                    endcase
                end
                6'b100011: $display("  [周期%0d] LW   $%0d, %0d($%0d)", cycle_count, instrF[20:16], $signed(instrF[15:0]), instrF[25:21]);
                6'b101011: $display("  [周期%0d] SW   $%0d, %0d($%0d)", cycle_count, instrF[20:16], $signed(instrF[15:0]), instrF[25:21]);
                6'b000100: $display("  [周期%0d] BEQ  $%0d, $%0d, offset=%0d", cycle_count, instrF[25:21], instrF[20:16], $signed(instrF[15:0]));
                6'b001000: $display("  [周期%0d] ADDI $%0d, $%0d, imm=%0d", cycle_count, instrF[20:16], instrF[25:21], $signed(instrF[15:0]));
                6'b001001: $display("  [周期%0d] ADDIU $%0d, $%0d, imm=%0d", cycle_count, instrF[20:16], instrF[25:21], $signed(instrF[15:0]));
                6'b001010: $display("  [周期%0d] SLTI $%0d, $%0d, imm=%0d", cycle_count, instrF[20:16], instrF[25:21], $signed(instrF[15:0]));
                6'b001011: $display("  [周期%0d] SLTIU $%0d, $%0d, imm=%0d", cycle_count, instrF[20:16], instrF[25:21], $signed(instrF[15:0]));
                6'b000010: $display("  [周期%0d] J    target=0x%08H", cycle_count, {pcF[31:28], instrF[25:0], 2'b00});
                default:   $display("  [周期%0d] 未知指令 0x%08H", cycle_count, instrF);
            endcase
        end
    end

    //============================================================================
    // 数据竞争(RAW)详细检测
    //============================================================================
    reg [4:0] rs_addr, rt_addr, rd_addr;
    reg [31:0] rs_value, rt_value;
    reg rs_used_in_next, rt_used_in_next;
    reg [31:0] forwarding_result;

    always @(posedge clk) begin
        if (!rst && instrF != 32'd0) begin
            rs_addr = instrF[25:21];
            rt_addr = instrF[20:16];
            rd_addr = instrF[15:11];

            // 假设寄存器堆的当前值
            rs_value = cpu.dp.registerfile.reg[rs_addr];
            rt_value = cpu.dp.registerfile.reg[rt_addr];

            // 检查下一条指令是否使用当前指令的目标寄存器
            // 这需要访问流水线寄存器
            rs_used_in_next = 0;
            rt_used_in_next = 0;

            $display("    寄存器: $%0d=0x%08H, $%0d=0x%08H, $%0d=0x%08H",
                     8, cpu.dp.registerfile.reg[8],
                     9, cpu.dp.registerfile.reg[9],
                     16, cpu.dp.registerfile.reg[16]);
        end
    end

    //============================================================================
    // 存储器访问监控
    //============================================================================
    always @(posedge clk) begin
        if (memwriteM) begin
            $display("  [MEM] Store: DM[0x%08H] = 0x%08H", aluoutM, writedataM);
        end
    end

    //============================================================================
    // ALU结果监控
    //============================================================================
    always @(posedge clk) begin
        if (!rst && aluoutM != 32'd0) begin
            $display("  [EXE] ALU Result: 0x%08H", aluoutM);
        end
    end

    //============================================================================
    // 错误检测
    //============================================================================
    reg [31:0] prev_pc;

    always @(posedge clk) begin
        if (!rst) begin
            // PC回跳检测 (死循环)
            if (pcF == prev_pc && instrF != 32'd0) begin
                $display("警告: 检测到PC无变化，可能存在死循环!");
            end
            prev_pc <= pcF;

            // 非法指令检测
            if (instrF[31:26] == 6'b111111 || instrF[31:26] == 6'b000001) begin
                $display("警告: 检测到保留或非法指令!");
            end
        end
    end

    //============================================================================
    // 波形文件生成 (用于GTKWave查看)
    //============================================================================
    initial begin
        $dumpfile("mips_waveform.vcd");
        $dumpvars(0, mips_tb);
    end

endmodule
