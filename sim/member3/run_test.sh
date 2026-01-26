#===============================================================================
# MIPS 仿真测试脚本
# 使用Verilator进行仿真
#===============================================================================

#!/bin/bash

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}===============================================================================${NC}"
echo -e "${YELLOW}  MIPS CPU 仿真测试${NC}"
echo -e "${YELLOW}===============================================================================${NC}"
echo ""

# 检查Verilator
if ! command -v verilator &> /dev/null; then
    echo -e "${RED}错误: 未找到Verilator，请先安装${NC}"
    echo "安装: sudo apt-get install verilator"
    exit 1
fi

# 检查测试文件
if [ ! -f "mips.v" ]; then
    echo -e "${RED}错误: 未找到mips.v文件${NC}"
    echo "请从项目根目录运行: cd ~/term5/HardwareDesignProject && ./sim/member3/run_test.sh"
    exit 1
fi

echo -e "${GREEN}[1/4] 编译MIPS CPU模块...${NC}"
verilator --timing --cc mips.v --exe sim/member3/mips_test.cpp -o Vmips 2>&1 | grep -v "syntax error" | tail -5

echo ""
echo -e "${GREEN}[2/4] 构建测试程序...${NC}"
cd obj_dir
make -f Vmips.mk -j1 2>&1 | tail -20
cd ..

if [ ! -f "obj_dir/Vmips" ]; then
    echo -e "${RED}错误: 构建失败${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}[3/4] 运行仿真...${NC}"
./obj_dir/Vmips 2>&1

echo ""
echo -e "${GREEN}[4/4] 生成波形文件...${NC}"
if [ -f "mips_waveform.vcd" ]; then
    echo "波形文件已生成: mips_waveform.vcd"
    echo "使用GTKWave查看: gtkwave mips_waveform.vcd"
else
    echo -e "${YELLOW}警告: 未生成波形文件${NC}"
fi

echo ""
echo -e "${YELLOW}===============================================================================${NC}"
echo -e "${YELLOW}  测试完成${NC}"
echo -e "${YELLOW}===============================================================================${NC}"
