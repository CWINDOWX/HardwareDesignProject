`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 2025/01/22
// Module Name: trap_detect_tb
// Description: Trap_Detect 模块的独立Testbench
//
//////////////////////////////////////////////////////////////////////////////////

module trap_detect_tb;
    reg  [31:0] instr;
    wire        is_syscall;
    wire        is_break;
    wire [5:0]  trap_type;

    integer test_count;
    integer pass_count;

    // 实例化DUT
    Trap_Detect uut (
        .instr(instr),
        .is_syscall(is_syscall),
        .is_break(is_break),
        .trap_type(trap_type)
    );

    // 测试激励
    initial begin
        test_count = 0;
        pass_count = 0;

        $display("========================================");
        $display("  Trap_Detect Module Testbench");
        $display("========================================");

        // 测试1: SYSCALL指令
        // 编码: opcode=0, rs=0, rt=0, rd=0, shamt=0, funct=12
        test_count = test_count + 1;
        instr = 32'b000000_00000_00000_00000_0000_001100;  // SYSCALL
        #10;
        if (is_syscall === 1'b1 && is_break === 1'b0 && trap_type === 6'd8) begin
            $display("Test %0d PASSED: SYSCALL detected", test_count);
            pass_count = pass_count + 1;
        end else begin
            $display("Test %0d FAILED: SYSCALL", test_count);
            $display("  is_syscall=%b (expected 1)", is_syscall);
            $display("  is_break=%b (expected 0)", is_break);
            $display("  trap_type=%0d (expected 8)", trap_type);
        end

        // 测试2: BREAK指令
        // 编码: opcode=0, rs=0, rt=0, rd=0, shamt=0, funct=13
        test_count = test_count + 1;
        instr = 32'b000000_00000_00000_00000_0000_001101;  // BREAK
        #10;
        if (is_syscall === 1'b0 && is_break === 1'b1 && trap_type === 6'd9) begin
            $display("Test %0d PASSED: BREAK detected", test_count);
            pass_count = pass_count + 1;
        end else begin
            $display("Test %0d FAILED: BREAK", test_count);
            $display("  is_syscall=%b (expected 0)", is_syscall);
            $display("  is_break=%b (expected 1)", is_break);
            $display("  trap_type=%0d (expected 9)", trap_type);
        end

        // 测试3: 普通ADD指令 (不应触发)
        // 编码: ADD $s1, $s2, $s3
        test_count = test_count + 1;
        instr = 32'b000000_10010_10011_01001_00000_100000;  // ADD
        #10;
        if (is_syscall === 1'b0 && is_break === 1'b0 && trap_type === 6'd0) begin
            $display("Test %0d PASSED: ADD (no trap)", test_count);
            pass_count = pass_count + 1;
        end else begin
            $display("Test %0d FAILED: ADD", test_count);
            $display("  is_syscall=%b (expected 0)", is_syscall);
            $display("  is_break=%b (expected 0)", is_break);
            $display("  trap_type=%0d (expected 0)", trap_type);
        end

        // 测试4: OR指令 (不应触发)
        test_count = test_count + 1;
        instr = 32'b000000_10001_10010_01001_00000_100101;  // OR
        #10;
        if (is_syscall === 1'b0 && is_break === 1'b0 && trap_type === 6'd0) begin
            $display("Test %0d PASSED: OR (no trap)", test_count);
            pass_count = pass_count + 1;
        end else begin
            $display("Test %0d FAILED: OR", test_count);
        end

        // 测试5: LW指令 (不应触发)
        test_count = test_count + 1;
        instr = 32'b100011_00001_00010_0000000000001000;  // LW
        #10;
        if (is_syscall === 1'b0 && is_break === 1'b0 && trap_type === 6'd0) begin
            $display("Test %0d PASSED: LW (no trap)", test_count);
            pass_count = pass_count + 1;
        end else begin
            $display("Test %0d FAILED: LW", test_count);
        end

        // 测试6: J指令 (不应触发)
        test_count = test_count + 1;
        instr = 32'b000010_00000000000000000000000000;  // J
        #10;
        if (is_syscall === 1'b0 && is_break === 1'b0 && trap_type === 6'd0) begin
            $display("Test %0d PASSED: J (no trap)", test_count);
            pass_count = pass_count + 1;
        end else begin
            $display("Test %0d FAILED: J", test_count);
        end

        // 总结
        $display("========================================");
        $display("  Test Summary");
        $display("========================================");
        $display("  Total Tests: %0d", test_count);
        $display("  Passed:      %0d", pass_count);
        $display("  Failed:      %0d", test_count - pass_count);
        $display("========================================");

        if (pass_count == test_count) begin
            $display("  ALL TESTS PASSED!");
        end else begin
            $display("  SOME TESTS FAILED!");
        end

        $finish;
    end
endmodule
