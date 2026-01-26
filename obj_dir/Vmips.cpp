// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmips.h"
#include "Vmips__Syms.h"

//============================================================
// Constructors

Vmips::Vmips(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmips__Syms(contextp(), _vcname__, this)}
    , CP0_Reg__02Eclk{vlSymsp->TOP.CP0_Reg__02Eclk}
    , CP0_Reg__02Erst{vlSymsp->TOP.CP0_Reg__02Erst}
    , DM__02Eclk{vlSymsp->TOP.DM__02Eclk}
    , mips__02Eclk{vlSymsp->TOP.mips__02Eclk}
    , mips__02Erst{vlSymsp->TOP.mips__02Erst}
    , ext_type_i{vlSymsp->TOP.ext_type_i}
    , we{vlSymsp->TOP.we}
    , addr{vlSymsp->TOP.addr}
    , eret{vlSymsp->TOP.eret}
    , cause_i{vlSymsp->TOP.cause_i}
    , syscall_i{vlSymsp->TOP.syscall_i}
    , break_i{vlSymsp->TOP.break_i}
    , cause_o{vlSymsp->TOP.cause_o}
    , exception_o{vlSymsp->TOP.exception_o}
    , DM__02Erst{vlSymsp->TOP.DM__02Erst}
    , we_i{vlSymsp->TOP.we_i}
    , mem_op_i{vlSymsp->TOP.mem_op_i}
    , memwriteM{vlSymsp->TOP.memwriteM}
    , imm{vlSymsp->TOP.imm}
    , ext_result{vlSymsp->TOP.ext_result}
    , wdata{vlSymsp->TOP.wdata}
    , rdata{vlSymsp->TOP.rdata}
    , epc_i{vlSymsp->TOP.epc_i}
    , epc_o{vlSymsp->TOP.epc_o}
    , addr_i{vlSymsp->TOP.addr_i}
    , wdata_i{vlSymsp->TOP.wdata_i}
    , rdata_o{vlSymsp->TOP.rdata_o}
    , pcF{vlSymsp->TOP.pcF}
    , instrF{vlSymsp->TOP.instrF}
    , aluoutM{vlSymsp->TOP.aluoutM}
    , writedataM{vlSymsp->TOP.writedataM}
    , readdataM{vlSymsp->TOP.readdataM}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmips::Vmips(const char* _vcname__)
    : Vmips(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmips::~Vmips() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmips___024root___eval_debug_assertions(Vmips___024root* vlSelf);
#endif  // VL_DEBUG
void Vmips___024root___eval_static(Vmips___024root* vlSelf);
void Vmips___024root___eval_initial(Vmips___024root* vlSelf);
void Vmips___024root___eval_settle(Vmips___024root* vlSelf);
void Vmips___024root___eval(Vmips___024root* vlSelf);

void Vmips::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmips::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmips___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmips___024root___eval_static(&(vlSymsp->TOP));
        Vmips___024root___eval_initial(&(vlSymsp->TOP));
        Vmips___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmips___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
}

//============================================================
// Events and timing
bool Vmips::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vmips::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vmips::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmips___024root___eval_final(Vmips___024root* vlSelf);

VL_ATTR_COLD void Vmips::final() {
    Vmips___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmips::hierName() const { return vlSymsp->name(); }
const char* Vmips::modelName() const { return "Vmips"; }
unsigned Vmips::threads() const { return 1; }
