// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmips.h for the primary calling header

#include "verilated.h"

#include "Vmips__Syms.h"
#include "Vmips___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__ico(Vmips___024root* vlSelf);
#endif  // VL_DEBUG

void Vmips___024root___eval_triggers__ico(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.at(0U) = (0U == vlSelf->__VicoIterCount);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmips___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__act(Vmips___024root* vlSelf);
#endif  // VL_DEBUG

void Vmips___024root___eval_triggers__act(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.at(0U) = (((IData)(vlSelf->CP0_Reg__02Eclk) 
                                       & (~ (IData)(vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Eclk))) 
                                      | ((IData)(vlSelf->CP0_Reg__02Erst) 
                                         & (~ (IData)(vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Erst))));
    vlSelf->__VactTriggered.at(1U) = ((IData)(vlSelf->DM__02Eclk) 
                                      & (~ (IData)(vlSelf->__Vtrigrprev__TOP__DM__02Eclk)));
    vlSelf->__VactTriggered.at(2U) = (((IData)(vlSelf->mips__02Eclk) 
                                       & (~ (IData)(vlSelf->__Vtrigrprev__TOP__mips__02Eclk))) 
                                      | ((IData)(vlSelf->mips__02Erst) 
                                         & (~ (IData)(vlSelf->__Vtrigrprev__TOP__mips__02Erst))));
    vlSelf->__VactTriggered.at(3U) = ((~ (IData)(vlSelf->mips__02Eclk)) 
                                      & (IData)(vlSelf->__Vtrigrprev__TOP__mips__02Eclk));
    vlSelf->__VactTriggered.at(4U) = ((IData)(vlSelf->mips__02Eclk) 
                                      & (~ (IData)(vlSelf->__Vtrigrprev__TOP__mips__02Eclk)));
    vlSelf->__VactTriggered.at(5U) = vlSelf->__VdlySched.awaitingCurrentTime();
    vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Eclk = vlSelf->CP0_Reg__02Eclk;
    vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Erst = vlSelf->CP0_Reg__02Erst;
    vlSelf->__Vtrigrprev__TOP__DM__02Eclk = vlSelf->DM__02Eclk;
    vlSelf->__Vtrigrprev__TOP__mips__02Eclk = vlSelf->mips__02Eclk;
    vlSelf->__Vtrigrprev__TOP__mips__02Erst = vlSelf->mips__02Erst;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmips___024root___dump_triggers__act(vlSelf);
    }
#endif
}
