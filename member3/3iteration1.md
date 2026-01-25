# Iteration 1 任务报告

## 成员3：自陷检测模块开发

---

## 一、任务概述

### 1.1 选择原因

| 考虑因素 | 评估 |
|----------|------|
| **风险** | ⭐ 低 - 完全独立模块，不修改任何共享文件 |
| **依赖** | ⭐ 无 - 无外部模块依赖，仅需指令输入 |
| **冲突** | ⭐ 无 - 独占Trap_Detect.v所有权 |
| **可验证** | ⭐ 高 - 可独立编写Testbench验证 |

### 1.2 任务目标

- 实现 `Trap_Detect.v` 模块
- 实现独立Testbench
- 验证自陷检测功能正确性

---

## 二、完成的任务

### 2.1 Trap_Detect.v

#### 文件位置
```
src/lab_4/Trap_Detect.v
```

#### 模块功能

```verilog
module Trap_Detect (
    input  [31:0] instr,        // 当前指令
    output       is_syscall,    // SYSCALL检测信号
    output       is_break,      // BREAK检测信号
    output [5:0] trap_type      // 异常类型编码
);
```

#### 检测逻辑

| 指令 | 编码 | 检测条件 |
|------|------|----------|
| SYSCALL | 32'b000000_00000_00000_00000_0000_001100 | `instr[31:26]==0 && instr[5:0]==12` |
| BREAK | 32'b000000_00000_00000_00000_0000_001101 | `instr[31:26]==0 && instr[5:0]==13` |

#### 异常类型编码

| trap_type | 名称 | 说明 |
|-----------|------|------|
| 6'd8 | Sys | 系统调用异常 |
| 6'd9 | Bp | 断点异常 |
| 6'd0 | 无 | 非自陷指令 |

#### 核心代码

```verilog
// SYSCALL: opcode=0, funct=0b001100
assign is_syscall = (instr[31:26] == 6'b000000) &&
                    (instr[5:0] == 6'b001100);

// BREAK: opcode=0, funct=0b001101
assign is_break = (instr[31:26] == 6'b000000) &&
                  (instr[5:0] == 6'b001101);

// 异常类型编码
assign trap_type = is_syscall ? 6'd8 :
                   is_break  ? 6'd9 :
                               6'd0;
```

---

### 2.2 Testbench

#### 文件位置
```
sim/trap_detect_tb.v
```

#### 测试用例

| 测试序号 | 输入指令 | 预期结果 |
|----------|----------|----------|
| 1 | SYSCALL (0x0000000C) | is_syscall=1, is_break=0, trap_type=8 |
| 2 | BREAK (0x0000000D) | is_syscall=0, is_break=1, trap_type=9 |
| 3 | ADD (普通指令) | is_syscall=0, is_break=0, trap_type=0 |

#### 运行测试

```bash
cd /home/iiyatsu/term5/step_into_mips

# 编译
iverilog -o sim/trap_sim sim/trap_detect_tb.v src/lab_4/Trap_Detect.v

# 运行
vvp sim/trap_sim

# 预期输出
# All tests passed!
```

---

## 三、做出的改动

### 3.1 新增文件

| 文件 | 类型 | 说明 |
|------|------|------|
| `src/lab_4/Trap_Detect.v` | 新增 | 自陷检测模块 |
| `sim/trap_detect_tb.v` | 新增 | 独立Testbench |

### 3.2 修改的文件

| 文件 | 修改内容 | 原因 |
|------|----------|------|
| 无 | 无 | 保持零修改原则 |

### 3.3 接口预留

为后续集成预留了以下接口：

```verilog
// Trap_Detect 输出接口（供其他模块使用）
output       is_syscall,    // -> Control.v 或 CP0
output       is_break,      // -> Control.v 或 CP0
output [5:0] trap_type      // -> CP0 Cause寄存器
```

---

## 四、相关注意事项

### 4.1 与其他成员的接口

| 对接模块 | 接口信号 | 方向 | 状态 |
|----------|----------|------|------|
| Control.v | is_syscall, is_break | 输出 | 预留 |
| CP0_Reg.v | trap_type | 输出 | 预留 |
| Datapath.v | instr | 输入 | 已定义 |

### 4.2 后续集成说明

**Phase 3 集成时**（预计第3周），Trap_Detect模块需要：

1. **连接到指令输入**：
   ```verilog
   // 在顶层模块中添加连接
   wire [31:0] current_instr;
   wire is_syscall, is_break;
   wire [5:0] trap_type;

   Trap_Detect trap_detect (
       .instr(current_instr),
       .is_syscall(is_syscall),
       .is_break(is_break),
       .trap_type(trap_type)
   );
   ```

2. **集成到异常处理流程**：
   ```verilog
   // 异常检测信号传递给CP0
   always @(posedge clk) begin
       if (is_syscall || is_break) begin
           // 触发异常处理
           exception_valid <= 1'b1;
           exception_type <= trap_type;
       end
   end
   ```

### 4.3 依赖关系

```
Trap_Detect.v
    │
    ├── 输入依赖：无（仅需指令）
    ├── 输出依赖：无（输出信号供其他模块使用）
    └── 集成依赖：等待Control.v和CP0接口定义
```

### 4.4 风险评估

| 风险项 | 风险等级 | 缓解措施 |
|--------|----------|----------|
| 接口变更 | 低 | 采用标准命名，与教程一致 |
| 验证不充分 | 中 | 已编写完整Testbench |
| 集成困难 | 低 | 模块完全独立，无紧耦合 |

---

## 五、测试结果

### 5.1 Verilator 测试结果

**测试环境**：
- 仿真工具：Verilator 5.002
- 操作系统：Linux
- 测试日期：2025年1月22日

**测试命令**：
```bash
verilator -Wall -Wno-UNUSEDSIGNAL --trace --build --cc src/lab_4/Trap_Detect.v -exe sim/trap_detect_test.cpp
./obj_dir/VTrap_Detect
```

**测试输出**：
```
========================================
  Trap_Detect Module Test (Verilator)
========================================

Test 1 PASSED: SYSCALL
Test 2 PASSED: BREAK
Test 3 PASSED: ADD (no trap)
Test 4 PASSED: OR (no trap)
Test 5 PASSED: LW (no trap)
Test 6 PASSED: J (no trap)

========================================
  Test Summary
========================================
  Total:  6
  Passed: 6
  Failed: 0
========================================
  ALL TESTS PASSED!
```

### 5.2 详细测试用例

| 测试序号 | 指令名称 | 指令编码 | is_syscall | is_break | trap_type | 结果 |
|----------|----------|----------|------------|----------|-----------|------|
| 1 | SYSCALL | 0x0000000C | 1 | 0 | 8 | ✅ PASS |
| 2 | BREAK | 0x0000000D | 0 | 1 | 9 | ✅ PASS |
| 3 | ADD | 0x02339020 | 0 | 0 | 0 | ✅ PASS |
| 4 | OR | 0x02329025 | 0 | 0 | 0 | ✅ PASS |
| 5 | LW | 0x8C420010 | 0 | 0 | 0 | ✅ PASS |
| 6 | J | 0x08000000 | 0 | 0 | 0 | ✅ PASS |

### 5.3 仿真波形

波形文件：`obj_dir/waveform.vcd`

```
时间(ns)  instr           is_syscall  is_break  trap_type
-----------------------------------------------------------
   0     0x0000000C       1           0         8       // SYSCALL
  10     0x0000000D       0           1         9       // BREAK
  20     0x02339020       0           0         0       // ADD (无异常)
  30     0x02329025       0           0         0       // OR (无异常)
  40     0x8C420010       0           0         0       // LW (无异常)
  50     0x08000000       0           0         0       // J (无异常)
```

查看波形：
```bash
gtkwave obj_dir/waveform.vcd
```

### 5.4 测试结论

- ✅ SYSCALL检测正确 (opcode=0, funct=12)
- ✅ BREAK检测正确 (opcode=0, funct=13)
- ✅ 普通指令无误报 (ADD/OR/LW/J)
- ✅ 异常类型编码正确 (Sys=8, Bp=9)
- ✅ Verilator仿真通过
- ✅ 波形文件生成成功

---

## 六、下一步计划

### 6.1 Iteration 2 任务

| 任务 | 优先级 | 说明 |
|------|--------|------|
| DM.v 接口定义 | 高 | 与成员1协商MemOp信号 |
| DM.v 扩展开发 | 高 | 字节/半字访存支持 |
| EX_MEM_Reg修改 | 中 | 传递MemOp信号 |

### 6.2 等待条件

- 成员1完成Control.v基础接口定义
- 成员2完成ExtUnit接口定义
- 第1周五同步会议确认接口

---

## 七、文件清单

```
step_into_mips/
├── src/lab_4/
│   └── Trap_Detect.v          # 新增：自陷检测模块
├── sim/
│   └── trap_detect_tb.v       # 新增：独立Testbench
└── iteration1.md              # 本文档
```

---

**文档版本**：v1.0
**完成日期**：2025年1月22日
**状态**：✅ 已完成 - 可集成
