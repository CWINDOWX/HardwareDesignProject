# MIPS CPU 仿真测试

## 目录结构

```
sim/member3/
├── instr_mem.v          # 指令存储器模块
├── data_mem.v           # 数据存储器模块
├── mips_tb.v            # Verilog测试平台
├── mips_test.cpp        # C++测试程序
├── run_test.sh          # 仿真运行脚本
├── instructions.coe     # 指令存储器初始化文件
├── data_memory.coe      # 数据存储器初始化文件
└── README.md            # 本说明文件
```

## COE 文件格式

### instructions.coe

```coe
memory_initialization_radix = 16
memory_initialization_vector =
    01284820,  ; 0x00400000  ADD  $s0, $t0, $t1
    01285822,  ; 0x00400004  SUB  $s1, $t0, $t1
    ...
```

**格式说明：**
- `memory_initialization_radix`: 数字进制 (16=十六进制)
- `memory_initialization_vector`: 初始化数据列表，以逗号分隔
- 每行可以添加注释（以分号开头）

### data_memory.coe

```coe
memory_initialization_radix = 16
memory_initialization_vector =
    12345678,  ; 0x00000000  测试数据1
    AABBCCDD,  ; 0x00000004  测试数据2
    ...
```

## 运行测试

### 方法1: 使用脚本（推荐）

```bash
cd sim/member3
chmod +x run_test.sh
./run_test.sh
```

### 方法2: 手动编译

```bash
# 编译Verilog模块
verilator -Wall --cc mips.v -o obj_dir/Vmips

# 编译测试程序
g++ -I. -I/usr/local/share/verilator/include \
    sim/member3/mips_test.cpp \
    obj_dir/Vmips__ALL.a \
    /usr/local/share/verilator/include/verilated.cpp \
    -o mips_test

# 运行测试
./mips_test
```

### 方法3: 使用Icarus Verilog

```bash
# 编译
iverilog -o mips_sim mips_tb.v mips.v instr_mem.v data_mem.v

# 运行
vvp mips_sim

# 查看波形
gtkwave mips_waveform.vcd
```

## 数据竞争(RAW Hazard)检测

### 什么是RAW冒险？

**Read After Write (RAW)** 是一种数据冒险，当一条指令需要读取某个寄存器的值，而前一条指令正好要写入同一个寄存器时发生。

```
指令1: ADD $s0, $t0, $t1   ; 写$s0
指令2: ADD $s1, $s0, $t2   ; 读$s0 <- RAW冒险!
```

### 测试用例

instructions.coe 中的"测试5"专门用于检测RAW冒险：

```coe
0x00400048,  ; ADD  $s0, $t0, $t1   (写$s0)
0x0040004C,  ; ADD  $s1, $s0, $t2   (读$s0, RAW!)
0x00400050   ; SUB  $s2, $s0, $t3   (读$s0, RAW!)
```

### 解决方案

1. **流水线停顿 (Stall)**: 插入气泡，直到数据可用
2. **转发 (Forwarding)**: 直接从ALU结果转发到执行阶段

## 波形分析

使用GTKWave查看生成的波形文件：

```bash
gtkwave mips_waveform.vcd
```

**关键信号：**
- `pcF`: 程序计数器
- `instrF`: 当前指令
- `aluoutM`: ALU运算结果
- `writedataM`: 写入存储器的数据
- `memwriteM`: 存储器写使能

## 支持的指令

| 类型 | 指令 | 编码 |
|------|------|------|
| R-type | ADD, SUB, AND, OR, SLT | funct |
| I-type | LW, SW, ADDI, BEQ | opcode |
| J-type | J | opcode |

## 常见问题

### Q: COE文件加载失败
A: 确保文件路径正确，且使用十六进制格式（无前缀）

### Q: 波形文件未生成
A: 在Verilog测试平台中添加:
```verilog
initial begin
    $dumpfile("waveform.vcd");
    $dumpvars(0, module_name);
end
```

### Q: 仿真卡住
A: 检查是否有无限循环或分支预测错误
