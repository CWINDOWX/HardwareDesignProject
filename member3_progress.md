# 成员3进度说明（基于 new分工.md）

仓库：`hwd_full_v0.1`  
当前工作分支：`member3_on_job1`（后续会把必要改动同步到 `job3`）  

## 1. 当前对拍进度（官方 func_test：类 SRAM SoC）

- 套件：`test/func_test_v0.03/soc_sram_func`
- 现象：目前可跑通 **64 个 Functional Test Point**；在 **第 65 点（异常/特权相关）** 处仍可能出现 mismatch（示例：异常向量入口 `0xBFC0_0380` 附近、或异常处理流程中 `0xBFC0_038C` 的 `lw` 返回值异常等）。
- 备注：本分支的改动目标是“在不修改官方测试文件”的前提下，把成员3职责相关的异常/访存行为补齐到可对拍。

## 2. 已完成（成员3职责）

### 2.1 52 条指令阶段：访存扩展（成员3）

- `LB/LBU/LH/LHU/SB/SH`：已接入并通过当前官方对拍前 64 点覆盖的相关用例。

### 2.2 57 条指令阶段：自陷（成员3）

- `SYSCALL/BREAK`：已加入本核的异常识别与提交路径（异常向量 `0xBFC0_0380`），用于支撑官方 `func_test` 的异常用例对拍。

## 3. 为支撑对拍引入的“成员3最小补丁集”（仅 Verilog）

以下提交均只改动 `HardwareDesignProject/**.v`（不改官方 `test/**`）：

1. `9582354`：`feat(member3): integrate CP0/exception for func_test`
   - 将异常/CP0/ERET 的最小闭环接入流水线（用于跑通官方异常相关测试点）。
2. `633e5d1`：`fix(exc): squash younger inst after exception`
   - 异常/ERET 提交时，squash 更年轻指令，避免“非精确异常”带来的副作用。
3. `a95f6f5`：`fix(member3): make HI/LO and divider precise on exception`
   - 异常/ERET 提交周期，禁止 EX 级更年轻指令写 `HI/LO`（以及 divider 完成写回），修复异常入口 `mfhi/mflo` 取值被污染的问题。

## 4. 未完成 / 风险点（需要继续定位，但不越权推进）

- 官方 `func_test` 第 65 点及之后仍可能失败：表现为异常处理入口或异常处理流程中的寄存器写回/访存结果与 reference 不一致。
- 该类问题可能来自：
  - 异常精确性仍有遗漏的“副作用源”（除 `HI/LO` 外的其它状态更新）；
  - 或与其他成员负责模块（如成员1 的 `HI/LO`/除法器实现细节、成员4 的 CP0 语义一致性）耦合。

**约束**：如果进一步修复需要修改其他成员负责的核心实现（超出成员3职责），将停止继续推进并回报依赖点与最小复现信息。

