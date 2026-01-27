// Verilator Testbench for DM (Data Memory)
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VDM.h"

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    VDM *dut = new VDM;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("dm_waveform.vcd");

    int test_count = 0;
    int pass_count = 0;

    printf("========================================\n");
    printf("  DM Module Test (Verilator)\n");
    printf("========================================\n\n");

    // 初始化
    dut->rst = 1;
    dut->clk = 0;
    dut->addr_i = 0;
    dut->wdata_i = 0;
    dut->we_i = 0;
    dut->mem_op_i = 0;
    dut->eval();
    tfp->dump(0);

    // 释放复位
    dut->rst = 0;
    dut->eval();
    tfp->dump(5);

    // ========================================
    // 测试1: SW (Store Word) - 字存储
    // ========================================
    test_count++;
    dut->addr_i = 0x00000000;           // 地址0 (字对齐)
    dut->wdata_i = 0x12345678;          // 测试数据
    dut->mem_op_i = 0b000;             // SW
    dut->we_i = 1;
    dut->clk = 1;
    dut->eval();
    tfp->dump(10);
    dut->clk = 0;
    dut->we_i = 0;
    dut->eval();
    tfp->dump(15);

    // 读回验证
    dut->addr_i = 0x00000000;
    dut->mem_op_i = 0b000;             // LW
    dut->we_i = 0;
    dut->eval();
    tfp->dump(20);

    if (dut->rdata_o == 0x12345678) {
        printf("Test %d PASSED: SW/LW (word store/load)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: SW/LW\n", test_count);
        printf("  Expected: 0x12345678, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试2: SB (Store Byte) - 字节存储
    // ========================================
    test_count++;
    dut->addr_i = 0x00000004;           // 地址4
    dut->wdata_i = 0xAABBCCDD;          // 数据
    dut->mem_op_i = 0b010;             // SB
    dut->we_i = 1;
    dut->clk = 1;
    dut->eval();
    tfp->dump(30);
    dut->clk = 0;
    dut->we_i = 0;
    dut->eval();
    tfp->dump(35);

    // 读回验证
    dut->addr_i = 0x00000004;
    dut->mem_op_i = 0b111;             // LBU
    dut->eval();
    tfp->dump(40);

    if (dut->rdata_o == 0x000000DD) {
        printf("Test %d PASSED: SB (store byte at addr+4)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: SB\n", test_count);
        printf("  Expected: 0x000000DD, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试3: LB (Load Byte Signed) - 字节读取符号扩展
    // ========================================
    test_count++;
    dut->addr_i = 0x00000004;
    dut->mem_op_i = 0b110;             // LB (符号扩展)
    dut->eval();
    tfp->dump(50);

    // 注意: 0xDD = 221, 但MSB=1，所以是负数(-35)，符号扩展为0xFFFFFFDD
    if (dut->rdata_o == 0xFFFFFFDD) {
        printf("Test %d PASSED: LB (byte load sign-extend, MSB=1)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: LB (sign-extend)\n", test_count);
        printf("  Expected: 0xFFFFFFDD, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试4: LB 符号扩展负数
    // ========================================
    test_count++;
    // 存储一个负数字节 (0x80 = -128)
    dut->addr_i = 0x00000008;
    dut->wdata_i = 0xFFFFFF80;
    dut->mem_op_i = 0b010;             // SB
    dut->we_i = 1;
    dut->clk = 1;
    dut->eval();
    tfp->dump(60);
    dut->clk = 0;
    dut->we_i = 0;
    dut->eval();
    tfp->dump(65);

    // 读回并符号扩展
    dut->addr_i = 0x00000008;
    dut->mem_op_i = 0b110;             // LB
    dut->eval();
    tfp->dump(70);

    if (dut->rdata_o == 0xFFFFFF80) {
        printf("Test %d PASSED: LB (byte load sign-extend, negative)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: LB (negative)\n", test_count);
        printf("  Expected: 0xFFFFFF80, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试5: LBU (Load Byte Unsigned) - 字节零扩展
    // ========================================
    test_count++;
    dut->addr_i = 0x00000008;
    dut->mem_op_i = 0b111;             // LBU
    dut->eval();
    tfp->dump(80);

    if (dut->rdata_o == 0x00000080) {
        printf("Test %d PASSED: LBU (byte load zero-extend)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: LBU\n", test_count);
        printf("  Expected: 0x00000080, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试6: SH (Store Halfword) - 半字存储
    // SH只存储低16位，0xABCD1234存储后，低2字节是0x1234
    // ========================================
    test_count++;
    dut->addr_i = 0x00000014;          // 新地址14 (避免之前测试干扰)
    dut->wdata_i = 0xABCD1234;
    dut->mem_op_i = 0b001;             // SH
    dut->we_i = 1;
    dut->clk = 1;
    dut->eval();
    tfp->dump(90);
    dut->clk = 0;
    dut->we_i = 0;
    dut->eval();
    tfp->dump(95);

    // 读回验证 - SH存储低16位，所以读回0x1234
    dut->addr_i = 0x00000014;
    dut->mem_op_i = 0b101;             // LHU
    dut->eval();
    tfp->dump(100);

    if (dut->rdata_o == 0x00001234) {
        printf("Test %d PASSED: SH (store halfword, lower 16 bits)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: SH\n", test_count);
        printf("  Expected: 0x00001234, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试7: LH (Load Halfword Signed) - 半字符号扩展
    // ========================================
    test_count++;
    dut->addr_i = 0x00000014;
    dut->mem_op_i = 0b100;             // LH (符号扩展)
    dut->eval();
    tfp->dump(110);

    // 0x1234的MSB是0，正数，符号扩展不变
    if (dut->rdata_o == 0x00001234) {
        printf("Test %d PASSED: LH (halfword load sign-extend, positive)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: LH (positive)\n", test_count);
        printf("  Expected: 0x00001234, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试8: LH 符号扩展负数
    // ========================================
    test_count++;
    // 存储0xFF80 (-128)
    dut->addr_i = 0x00000018;          // 新地址18 (半字对齐)
    dut->wdata_i = 0xFFFF8000;
    dut->mem_op_i = 0b001;             // SH
    dut->we_i = 1;
    dut->clk = 1;
    dut->eval();
    tfp->dump(120);
    dut->clk = 0;
    dut->we_i = 0;
    dut->eval();
    tfp->dump(125);

    // 读回并符号扩展
    dut->addr_i = 0x00000018;
    dut->mem_op_i = 0b100;             // LH
    dut->eval();
    tfp->dump(130);

    // SH只存低16位，0xFFFF8000 -> wdata_ext = 0x00008000
    // LH读取0x8000，符号扩展为0xFFFF8000
    if (dut->rdata_o == 0xFFFF8000) {
        printf("Test %d PASSED: LH (halfword load sign-extend, negative)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: LH (negative)\n", test_count);
        printf("  Expected: 0xFFFF8000, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试9: SH 存储高16位
    // ========================================
    test_count++;
    // 使用SH在高地址存储 (addr[1]=1)，使用新的字地址避免冲突
    dut->addr_i = 0x00000024;          // 地址36 (字地址9，避免冲突)
    dut->wdata_i = 0xBEEFABCD;
    dut->mem_op_i = 0b001;             // SH
    dut->we_i = 1;
    dut->clk = 1;
    dut->eval();
    tfp->dump(140);
    dut->clk = 0;
    dut->we_i = 0;
    dut->eval();
    tfp->dump(145);

    // 读回 - addr[1]=1时，byte_we=4'b1100，只修改高16位
    dut->addr_i = 0x00000024;          // 同一个字地址
    dut->mem_op_i = 0b101;             // LHU
    dut->eval();
    tfp->dump(150);

    // wdata_ext = {16'b0, 0xABCD} = 0x0000ABCD
    // addr[1]=1，byte_we=4'b1100，修改[31:24]和[23:16]
    // 低16位保持0，所以读回0x0000ABCD
    if (dut->rdata_o == 0x0000ABCD) {
        printf("Test %d PASSED: SH (store at addr[1]=1, high 16 bits)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: SH at high 16 bits\n", test_count);
        printf("  Expected: 0x0000ABCD, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试10: 边界测试 - 字对齐
    // ========================================
    test_count++;
    dut->addr_i = 0x00000000;
    dut->wdata_i = 0xDEADBEEF;
    dut->mem_op_i = 0b000;             // SW
    dut->we_i = 1;
    dut->clk = 1;
    dut->eval();
    tfp->dump(160);
    dut->clk = 0;
    dut->we_i = 0;
    dut->eval();
    tfp->dump(165);

    // 读回
    dut->addr_i = 0x00000000;
    dut->mem_op_i = 0b000;             // LW
    dut->eval();
    tfp->dump(170);

    if (dut->rdata_o == 0xDEADBEEF) {
        printf("Test %d PASSED: Word boundary test (0xDEADBEEF)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Word boundary\n", test_count);
        printf("  Expected: 0xDEADBEEF, Got: 0x%08X\n", dut->rdata_o);
    }

    // ========================================
    // 测试11: LBU 验证零扩展
    // ========================================
    test_count++;
    // 用LBU读之前存储的0xDD
    dut->addr_i = 0x00000004;
    dut->mem_op_i = 0b111;             // LBU
    dut->eval();
    tfp->dump(180);

    if (dut->rdata_o == 0x000000DD) {
        printf("Test %d PASSED: LBU (zero-extend 0xDD to 0x000000DD)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: LBU zero-extend\n", test_count);
        printf("  Expected: 0x000000DD, Got: 0x%08X\n", dut->rdata_o);
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
