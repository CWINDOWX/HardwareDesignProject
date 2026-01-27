// Verilator Testbench for Trap_Detect (自陷检测)
#include <verilated.h>
#include "VTrap_Detect.h"

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    VTrap_Detect *dut = new VTrap_Detect;

    int test_count = 0;
    int pass_count = 0;

    printf("========================================\n");
    printf("  Trap_Detect Module Test (Verilator)\n");
    printf("========================================\n\n");

    // 测试1: SYSCALL指令
    // 编码: opcode=0, rs=0, rt=0, rd=0, shamt=0, funct=12
    test_count++;
    dut->instr = 0x0000000C;  // SYSCALL: 000000_00000_00000_00000_0000_001100
    dut->eval();
    if (dut->is_syscall && !dut->is_break && dut->trap_type == 8) {
        printf("Test %d PASSED: SYSCALL detected\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: SYSCALL\n", test_count);
        printf("  is_syscall=%d (expected 1), is_break=%d (expected 0), trap_type=%d (expected 8)\n",
               (int)dut->is_syscall, (int)dut->is_break, (int)dut->trap_type);
    }

    // 测试2: BREAK指令
    // 编码: opcode=0, rs=0, rt=0, rd=0, shamt=0, funct=13
    test_count++;
    dut->instr = 0x0000000D;  // BREAK: 000000_00000_00000_00000_0000_001101
    dut->eval();
    if (!dut->is_syscall && dut->is_break && dut->trap_type == 9) {
        printf("Test %d PASSED: BREAK detected\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: BREAK\n", test_count);
        printf("  is_syscall=%d (expected 0), is_break=%d (expected 1), trap_type=%d (expected 9)\n",
               (int)dut->is_syscall, (int)dut->is_break, (int)dut->trap_type);
    }

    // 测试3: 普通ADD指令 (不应触发)
    // 编码: ADD $s1, $s2, $s3
    test_count++;
    dut->instr = 0x02329020;  // ADD $s1, $s2, $s3
    dut->eval();
    if (!dut->is_syscall && !dut->is_break && dut->trap_type == 0) {
        printf("Test %d PASSED: ADD (no trap)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: ADD\n", test_count);
    }

    // 测试4: OR指令 (不应触发)
    test_count++;
    dut->instr = 0x02329025;  // OR $s1, $s2, $s3
    dut->eval();
    if (!dut->is_syscall && !dut->is_break && dut->trap_type == 0) {
        printf("Test %d PASSED: OR (no trap)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: OR\n", test_count);
    }

    // 测试5: LW指令 (不应触发)
    test_count++;
    dut->instr = 0x8C420010;  // LW $v0, 0x10($s2)
    dut->eval();
    if (!dut->is_syscall && !dut->is_break && dut->trap_type == 0) {
        printf("Test %d PASSED: LW (no trap)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: LW\n", test_count);
    }

    // 测试6: J指令 (不应触发)
    test_count++;
    dut->instr = 0x08000000;  // J 0x00000000
    dut->eval();
    if (!dut->is_syscall && !dut->is_break && dut->trap_type == 0) {
        printf("Test %d PASSED: J (no trap)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: J\n", test_count);
    }

    printf("\n========================================\n");
    printf("  Test Summary\n");
    printf("========================================\n");
    printf("  Total:  %d\n", test_count);
    printf("  Passed: %d\n", pass_count);
    printf("  Failed: %d\n", test_count - pass_count);
    printf("========================================\n");

    if (pass_count == test_count) {
        printf("  ALL TESTS PASSED!\n");
    } else {
        printf("  SOME TESTS FAILED!\n");
    }

    delete dut;
    return 0;
}
