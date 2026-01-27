// Verilator Testbench for ExtUnit (立即数扩展单元)
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VExtUnit.h"

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    VExtUnit *dut = new VExtUnit;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("extunit_waveform.vcd");

    int test_count = 0;
    int pass_count = 0;

    printf("========================================\n");
    printf("  ExtUnit Module Test (Verilator)\n");
    printf("========================================\n\n");

    // 测试1: 符号扩展 (ext_type=00) - 正数
    test_count++;
    dut->imm = 16'h1234;
    dut->ext_type_i = 2'b00;
    dut->eval();
    tfp->dump(0);
    if (dut->ext_result == 32'h00001234) {
        printf("Test %d PASSED: Sign-extend positive (00)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Sign-extend positive (00)\n", test_count);
        printf("  Expected: 0x00001234, Got: 0x%08X\n", dut->ext_result);
    }

    // 测试2: 符号扩展 (ext_type=00) - 负数
    test_count++;
    dut->imm = 16'hFFFF;  // -1
    dut->ext_type_i = 2'b00;
    dut->eval();
    tfp->dump(10);
    if (dut->ext_result == 32'hFFFFFFFF) {
        printf("Test %d PASSED: Sign-extend negative (00)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Sign-extend negative (00)\n", test_count);
        printf("  Expected: 0xFFFFFFFF, Got: 0x%08X\n", dut->ext_result);
    }

    // 测试3: 零扩展 (ext_type=01) - ANDI/ORI/XORI
    test_count++;
    dut->imm = 16'hABCD;
    dut->ext_type_i = 2'b01;
    dut->eval();
    tfp->dump(20);
    if (dut->ext_result == 32'h0000ABCD) {
        printf("Test %d PASSED: Zero-extend (01)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Zero-extend (01)\n", test_count);
        printf("  Expected: 0x0000ABCD, Got: 0x%08X\n", dut->ext_result);
    }

    // 测试4: Load符号扩展 (ext_type=10) - LB/LH
    test_count++;
    dut->imm = 16'h8000;  // 负数边界
    dut->ext_type_i = 2'b10;
    dut->eval();
    tfp->dump(30);
    if (dut->ext_result == 32'hFFFF8000) {
        printf("Test %d PASSED: Load sign-extend negative (10)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Load sign-extend negative (10)\n", test_count);
        printf("  Expected: 0xFFFF8000, Got: 0x%08X\n", dut->ext_result);
    }

    // 测试5: Load零扩展 (ext_type=11) - LBU/LHU
    test_count++;
    dut->imm = 16'h00FF;
    dut->ext_type_i = 2'b11;
    dut->eval();
    tfp->dump(40);
    if (dut->ext_result == 32'h000000FF) {
        printf("Test %d PASSED: Load zero-extend (11)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Load zero-extend (11)\n", test_count);
        printf("  Expected: 0x000000FF, Got: 0x%08X\n", dut->ext_result);
    }

    // 测试6: 符号扩展 (ext_type=10) - 正数
    test_count++;
    dut->imm = 16'h1234;
    dut->ext_type_i = 2'b10;
    dut->eval();
    tfp->dump(50);
    if (dut->ext_result == 32'h00001234) {
        printf("Test %d PASSED: Load sign-extend positive (10)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Load sign-extend positive (10)\n", test_count);
        printf("  Expected: 0x00001234, Got: 0x%08X\n", dut->ext_result);
    }

    // 测试7: 零扩展 (ext_type=11) - 大数值
    test_count++;
    dut->imm = 16'hFFFF;
    dut->ext_type_i = 2'b11;
    dut->eval();
    tfp->dump(60);
    if (dut->ext_result == 32'h0000FFFF) {
        printf("Test %d PASSED: Load zero-extend max value (11)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Load zero-extend max value (11)\n", test_count);
        printf("  Expected: 0x0000FFFF, Got: 0x%08X\n", dut->ext_result);
    }

    // 测试8: 零扩展 (ext_type=01) - 全0
    test_count++;
    dut->imm = 16'h0000;
    dut->ext_type_i = 2'b01;
    dut->eval();
    tfp->dump(70);
    if (dut->ext_result == 32'h00000000) {
        printf("Test %d PASSED: Zero-extend zero (01)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Zero-extend zero (01)\n", test_count);
        printf("  Expected: 0x00000000, Got: 0x%08X\n", dut->ext_result);
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

    tfp->close();
    delete tfp;
    delete dut;
    return 0;
}
