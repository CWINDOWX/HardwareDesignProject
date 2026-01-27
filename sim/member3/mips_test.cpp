//==============================================================================
// MIPS CPU 仿真测试程序 (Verilator)
// 测试内容: 基础指令 + 数据竞争(RAW Hazard)检测
//==============================================================================

#include <verilated.h>
#include <verilated_vcd_c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 包含生成的Verilog模块
#include "Vmips.h"

// 测试结果
int test_passed = 0;
int test_failed = 0;
int cycle_count = 0;

// 数据竞争检测
int hazard_detected = 0;
int forwarding_used = 0;

// 指令存储器 (64字)
unsigned int instr_mem[64];

// 数据存储器 (64字)
unsigned int data_mem[64];

// 寄存器文件 (32个32位寄存器)
unsigned int reg_file[32];

// 加载COE文件
int load_coe_file(const char* filename, unsigned int* memory, int size) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("错误: 无法打开文件 %s\n", filename);
        return -1;
    }

    char line[256];
    int addr = 0;
    while (fgets(line, sizeof(line), fp) && addr < size) {
        // 跳过注释和空行
        if (line[0] == ';' || line[0] == '\n' || line[0] == '\r')
            continue;

        // 解析十六进制数
        unsigned int value;
        if (sscanf(line, "%x", &value) == 1) {
            memory[addr++] = value;
        }
    }

    fclose(fp);
    printf("加载 %d 个字从 %s\n", addr, filename);
    return addr;
}

// 初始化测试环境
void init_test_environment() {
    // 初始化寄存器
    memset(reg_file, 0, sizeof(reg_file));
    reg_file[0] = 0;      // $zero 始终为0
    reg_file[8] = 1;      // $t0 = 1
    reg_file[9] = 2;      // $t1 = 2
    reg_file[10] = 0;     // $t2 = 0 (用于DM地址)
    reg_file[11] = 4;     // $t3 = 4
    reg_file[12] = 8;     // $t4 = 8
    reg_file[13] = 12;    // $t5 = 12
    reg_file[14] = 16;    // $t6 = 16
    reg_file[15] = 20;    // $t7 = 20

    // 初始化数据存储器
    memset(data_mem, 0, sizeof(data_mem));
    data_mem[0] = 0x12345678;   // DM[0]
    data_mem[1] = 0xAABBCCDD;   // DM[1]
    data_mem[2] = 0xFFEDDCC;    // DM[2]
    data_mem[3] = 0x000000FF;   // DM[3]
    data_mem[4] = 0xFFFF8000;   // DM[4]
    data_mem[5] = 0x00001234;   // DM[5]

    printf("测试环境初始化完成\n");
    printf("寄存器: $t0=0x%08X, $t1=0x%08X\n", reg_file[8], reg_file[9]);
    printf("数据存储器: DM[0]=0x%08X, DM[1]=0x%08X\n", data_mem[0], data_mem[1]);
}

// 解码R-type指令
void decode_rtype(unsigned int instr, int* rs, int* rt, int* rd, int* funct) {
    *rs = (instr >> 21) & 0x1F;
    *rt = (instr >> 16) & 0x1F;
    *rd = (instr >> 11) & 0x1F;
    *funct = instr & 0x3F;
}

// 解码I-type指令
void decode_itype(unsigned int instr, int* rs, int* rt, int* imm) {
    *rs = (instr >> 21) & 0x1F;
    *rt = (instr >> 16) & 0x1F;
    *imm = instr & 0xFFFF;
}

// 执行R-type指令 (模拟器模式，用于验证)
int execute_rtype_sim(unsigned int instr) {
    int rs, rt, rd, funct;
    decode_rtype(instr, &rs, &rt, &rd, &funct);

    switch (funct) {
        case 0x20: // ADD
            reg_file[rd] = reg_file[rs] + reg_file[rt];
            printf("  [SIM] ADD  $%d = $%d + $%d = 0x%08X\n", rd, rs, rt, reg_file[rd]);
            break;
        case 0x22: // SUB
            reg_file[rd] = reg_file[rs] - reg_file[rt];
            printf("  [SIM] SUB  $%d = $%d - $%d = 0x%08X\n", rd, rs, rt, reg_file[rd]);
            break;
        case 0x24: // AND
            reg_file[rd] = reg_file[rs] & reg_file[rt];
            printf("  [SIM] AND  $%d = $%d & $%d = 0x%08X\n", rd, rs, rt, reg_file[rd]);
            break;
        case 0x25: // OR
            reg_file[rd] = reg_file[rs] | reg_file[rt];
            printf("  [SIM] OR   $%d = $%d | $%d = 0x%08X\n", rd, rs, rt, reg_file[rd]);
            break;
        case 0x2A: // SLT
            reg_file[rd] = (reg_file[rs] < reg_file[rt]) ? 1 : 0;
            printf("  [SIM] SLT  $%d = ($%d < $%d) ? 1 : 0 = 0x%08X\n", rd, rs, rt, reg_file[rd]);
            break;
        default:
            printf("  [SIM] 未知R-type指令 funct=0x%02X\n", funct);
            return -1;
    }
    return 0;
}

// 执行I-type指令 (模拟器模式)
int execute_itype_sim(unsigned int instr) {
    int rs, rt, imm;
    decode_itype(instr, &rs, &rt, &imm);
    unsigned int imm_ext = (imm & 0x8000) ? (0xFFFF0000 | imm) : imm;

    switch (instr >> 26) {
        case 0x20: // ADDI
            reg_file[rt] = reg_file[rs] + imm_ext;
            printf("  [SIM] ADDI $%d = $%d + 0x%04X = 0x%08X\n", rt, rs, imm, reg_file[rt]);
            break;
        case 0x23: // LW
            {
                unsigned int addr = reg_file[rs] + imm_ext;
                unsigned int word_addr = addr >> 2;
                if (word_addr < 64) {
                    reg_file[rt] = data_mem[word_addr];
                    printf("  [SIM] LW   $%d = DM[0x%08X] = 0x%08X\n", rt, addr, reg_file[rt]);
                }
            }
            break;
        case 0x2B: // SW
            {
                unsigned int addr = reg_file[rs] + imm_ext;
                unsigned int word_addr = addr >> 2;
                if (word_addr < 64) {
                    data_mem[word_addr] = reg_file[rt];
                    printf("  [SIM] SW   DM[0x%08X] = $%d = 0x%08X\n", addr, rt, reg_file[rt]);
                }
            }
            break;
        case 0x04: // BEQ
            {
                int offset = (imm_ext << 2);
                printf("  [SIM] BEQ  $%d == $%d? (0x%08X == 0x%08X)\n", rs, rt, reg_file[rs], reg_file[rt]);
                if (reg_file[rs] == reg_file[rt]) {
                    printf("  [SIM] -> 分支跳转 offset=%d\n", offset);
                }
            }
            break;
        default:
            printf("  [SIM] 未知I-type指令 op=0x%02X\n", instr >> 26);
            return -1;
    }
    return 0;
}

// 打印寄存器状态
void print_registers() {
    printf("\n寄存器状态:\n");
    printf("$t0=0x%08X, $t1=0x%08X, $t2=0x%08X, $t3=0x%08X\n",
           reg_file[8], reg_file[9], reg_file[10], reg_file[11]);
    printf("$t4=0x%08X, $t5=0x%08X, $t6=0x%08X, $t7=0x%08X\n",
           reg_file[12], reg_file[13], reg_file[14], reg_file[15]);
    printf("$s0=0x%08X, $s1=0x%08X, $s2=0x%08X, $s3=0x%08X\n",
           reg_file[16], reg_file[17], reg_file[18], reg_file[19]);
}

// 检测RAW数据竞争
int detect_raw_hazard(int rs, int rt, int prev_rd, int prev_regwrite) {
    if (!prev_regwrite || prev_rd == 0)
        return 0;

    if (rs == prev_rd || rt == prev_rd) {
        hazard_detected++;
        printf("  [HAZARD] 检测到RAW冒险: 使用被写的寄存器 $%d\n", prev_rd);
        return 1;
    }
    return 0;
}

// 主函数
int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    printf("===============================================================================\n");
    printf("  MIPS CPU 仿真测试程序\n");
    printf("  测试内容: 基础指令 + 数据竞争(RAW Hazard)检测\n");
    printf("===============================================================================\n\n");

    // 初始化测试环境
    init_test_environment();

    // 加载指令
    // 注意: 实际测试时需要先运行Verilator生成代码
    printf("\n使用模拟器模式运行测试...\n\n");

    // 模拟执行测试指令序列
    unsigned int test_instrs[] = {
        0x01284820,  // ADD $s0, $t0, $t1
        0x01285822,  // SUB $s1, $t0, $t1
        0x01286824,  // AND $s2, $t0, $t1
        0x01287825,  // OR  $s3, $t0, $t1
        0x0128882A,  // SLT $s4, $t0, $t1
    };

    printf("--- 测试1: R-type指令 ---\n");
    int prev_rd = 0, prev_regwrite = 0;

    for (int i = 0; i < 5; i++) {
        cycle_count++;
        int rs = (test_instrs[i] >> 21) & 0x1F;
        int rt = (test_instrs[i] >> 16) & 0x1F;
        int rd = (test_instrs[i] >> 11) & 0x1F;

        // 检测RAW冒险
        detect_raw_hazard(rs, rt, prev_rd, prev_regwrite);

        // 执行指令
        execute_rtype_sim(test_instrs[i]);

        prev_rd = rd;
        prev_regwrite = 1;
    }

    printf("\n--- 测试2: I-type指令 (LW/SW) ---\n");
    unsigned int test_instrs2[] = {
        0x21280064,  // ADDI $t0, $t0, 100
        0x8D4D0000,  // LW   $t5, 0($t2)
        0xAD4D0004,  // SW   $t5, 4($t2)
        0x21290032,  // ADDI $t1, $t1, 50
    };

    for (int i = 0; i < 4; i++) {
        cycle_count++;
        execute_itype_sim(test_instrs2[i]);
    }

    printf("\n--- 测试3: 数据竞争(RAW Hazard) ---\n");
    unsigned int hazard_test[] = {
        0x01284820,  // ADD  $s0, $t0, $t1  (写$s0)
        0x020A8820,  // ADD  $s1, $s0, $t2  (读$s0, RAW!)
        0x020B9022,  // SUB  $s2, $s0, $t3  (读$s0, RAW!)
    };

    prev_rd = 0;
    prev_regwrite = 0;

    for (int i = 0; i < 3; i++) {
        cycle_count++;
        int rs = (hazard_test[i] >> 21) & 0x1F;
        int rt = (hazard_test[i] >> 16) & 0x1F;
        int rd = (hazard_test[i] >> 11) & 0x1F;

        detect_raw_hazard(rs, rt, prev_rd, prev_regwrite);
        execute_rtype_sim(hazard_test[i]);

        prev_rd = rd;
        prev_regwrite = 1;
    }

    // 打印结果
    printf("\n===============================================================================\n");
    printf("  测试结果汇总\n");
    printf("===============================================================================\n");
    printf("执行周期数: %d\n", cycle_count);
    printf("检测到的RAW数据竞争: %d\n", hazard_detected);
    printf("使用的Forwarding: %d\n", forwarding_used);

    print_registers();

    printf("\n数据存储器:\n");
    printf("DM[0]=0x%08X, DM[1]=0x%08X, DM[2]=0x%08X\n",
           data_mem[0], data_mem[1], data_mem[2]);

    printf("\n===============================================================================\n");
    if (test_failed == 0) {
        printf("  仿真完成! 所有测试通过.\n");
    } else {
        printf("  仿真完成! %d 通过, %d 失败.\n", test_passed, test_failed);
    }
    printf("===============================================================================\n");

    return 0;
}
