// Verilator Testbench for CP0_Reg (协处理器寄存器)
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VCP0_Reg.h"

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    VCP0_Reg *dut = new VCP0_Reg;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("cp0_reg_waveform.vcd");

    int test_count = 0;
    int pass_count = 0;

    printf("========================================\n");
    printf("  CP0_Reg Module Test (Verilator)\n");
    printf("========================================\n\n");

    // 初始化
    dut->rst = 1;
    dut->clk = 0;
    dut->we = 0;
    dut->addr = 0;
    dut->wdata = 0;
    dut->eret = 0;
    dut->epc_i = 0;
    dut->cause_i = 0;
    dut->syscall_i = 0;
    dut->break_i = 0;
    dut->eval();
    tfp->dump(0);

    // 释放复位
    dut->rst = 0;
    dut->eval();
    tfp->dump(5);

    // ========================================
    // 测试1: SYSCALL 异常
    // ========================================
    test_count++;
    dut->syscall_i = 1;
    dut->break_i = 0;
    dut->epc_i = 32'h00400020;
    dut->clk = 1;
    dut->eval();
    tfp->dump(10);
    dut->clk = 0;
    dut->eval();
    tfp->dump(15);

    if (dut->exception_o && dut->epc_o == 32'h00400020) {
        printf("Test %d PASSED: SYSCALL exception, EPC saved\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: SYSCALL exception\n", test_count);
        printf("  exception_o: %d (expected 1), epc_o: 0x%08X (expected 0x00400020)\n",
               dut->exception_o, dut->epc_o);
    }

    // ========================================
    // 测试2: BREAK 异常
    // ========================================
    test_count++;
    dut->syscall_i = 0;
    dut->break_i = 1;
    dut->epc_i = 32'h00400030;
    dut->clk = 1;
    dut->eval();
    tfp->dump(20);
    dut->clk = 0;
    dut->eval();
    tfp->dump(25);

    if (dut->exception_o && dut->epc_o == 32'h00400030) {
        printf("Test %d PASSED: BREAK exception, EPC saved\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: BREAK exception\n", test_count);
        printf("  exception_o: %d (expected 1), epc_o: 0x%08X (expected 0x00400030)\n",
               dut->exception_o, dut->epc_o);
    }

    // ========================================
    // 测试3: Cause 寄存器 ExcCode
    // ========================================
    test_count++;
    // SYSCALL -> ExcCode = 8, BREAK -> ExcCode = 9
    dut->syscall_i = 1;
    dut->break_i = 0;
    dut->clk = 1;
    dut->eval();
    tfp->dump(30);
    dut->clk = 0;
    dut->eval();
    tfp->dump(35);

    if (dut->cause_o == 5'd8) {  // Sys = 8
        printf("Test %d PASSED: Cause ExcCode = 8 (Sys)\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: Cause ExcCode\n", test_count);
        printf("  Expected: 8, Got: %d\n", dut->cause_o);
    }

    // ========================================
    // 测试4: MTC0 写 EPC 寄存器
    // ========================================
    test_count++;
    dut->syscall_i = 0;
    dut->break_i = 0;
    dut->we = 1;
    dut->addr = 5'd14;  // EPC address
    dut->wdata = 32'h12345678;
    dut->clk = 1;
    dut->eval();
    tfp->dump(40);
    dut->clk = 0;
    dut->eval();
    tfp->dump(45);

    if (dut->epc_o == 32'h12345678) {
        printf("Test %d PASSED: MTC0 write EPC\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: MTC0 write EPC\n", test_count);
        printf("  Expected: 0x12345678, Got: 0x%08X\n", dut->epc_o);
    }

    // ========================================
    // 测试5: MFC0 读 Count 寄存器
    // ========================================
    test_count++;
    // Count寄存器会递增，需要读取当前值
    dut->we = 0;
    dut->addr = 5'd9;  // Count address
    dut->eval();
    tfp->dump(50);

    // Count应该已经自增多次，确保非0
    if (dut->rdata != 32'd0) {
        printf("Test %d PASSED: MFC0 read Count\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: MFC0 read Count\n", test_count);
    }

    // ========================================
    // 测试6: 无异常时 exception_o = 0
    // ========================================
    test_count++;
    dut->syscall_i = 0;
    dut->break_i = 0;
    dut->eval();
    tfp->dump(60);

    if (!dut->exception_o) {
        printf("Test %d PASSED: No exception, exception_o=0\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: No exception\n", test_count);
    }

    // ========================================
    // 测试7: Status 寄存器写
    // ========================================
    test_count++;
    dut->we = 1;
    dut->addr = 5'd12;  // Status address
    dut->wdata = 32'h00000001;  // IEc = 1
    dut->clk = 1;
    dut->eval();
    tfp->dump(70);
    dut->clk = 0;
    dut->eval();
    tfp->dump(75);

    // 读取Status
    dut->we = 0;
    dut->addr = 5'd12;
    dut->eval();
    tfp->dump(80);

    if (dut->rdata == 32'h00000001) {
        printf("Test %d PASSED: MTC0 write Status\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: MTC0 write Status\n", test_count);
        printf("  Expected: 0x00000001, Got: 0x%08X\n", dut->rdata);
    }

    // ========================================
    // 测试8: Cause 寄存器写
    // ========================================
    test_count++;
    dut->we = 1;
    dut->addr = 5'd13;  // Cause address
    dut->wdata = 32'h00001234;
    dut->clk = 1;
    dut->eval();
    tfp->dump(90);
    dut->clk = 0;
    dut->eval();
    tfp->dump(95);

    // 读取Cause
    dut->we = 0;
    dut->addr = 5'd13;
    dut->eval();
    tfp->dump(100);

    if (dut->rdata == 32'h00001234) {
        printf("Test %d PASSED: MTC0 write Cause\n", test_count);
        pass_count++;
    } else {
        printf("Test %d FAILED: MTC0 write Cause\n", test_count);
        printf("  Expected: 0x00001234, Got: 0x%08X\n", dut->rdata);
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
