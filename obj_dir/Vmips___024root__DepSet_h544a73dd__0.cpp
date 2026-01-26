// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmips.h for the primary calling header

#include "verilated.h"

#include "Vmips___024root.h"

VL_INLINE_OPT void Vmips___024root___ico_sequent__TOP__0(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->ext_result = (((1U == (IData)(vlSelf->ext_type_i)) 
                           | (3U == (IData)(vlSelf->ext_type_i)))
                           ? (IData)(vlSelf->imm) : 
                          (((- (IData)((1U & ((IData)(vlSelf->imm) 
                                              >> 0xfU)))) 
                            << 0x10U) | (IData)(vlSelf->imm)));
    vlSelf->exception_o = ((IData)(vlSelf->break_i) 
                           | (IData)(vlSelf->syscall_i));
    vlSelf->DM__DOT__byte_we = ((0U == (IData)(vlSelf->mem_op_i))
                                 ? 0xfU : (0xfU & (
                                                   ((1U 
                                                     == (IData)(vlSelf->mem_op_i)) 
                                                    | ((4U 
                                                        == (IData)(vlSelf->mem_op_i)) 
                                                       | (5U 
                                                          == (IData)(vlSelf->mem_op_i))))
                                                    ? 
                                                   ((2U 
                                                     & vlSelf->addr_i)
                                                     ? 0xcU
                                                     : 3U)
                                                    : 
                                                   (((2U 
                                                      == (IData)(vlSelf->mem_op_i)) 
                                                     | ((6U 
                                                         == (IData)(vlSelf->mem_op_i)) 
                                                        | (7U 
                                                           == (IData)(vlSelf->mem_op_i))))
                                                     ? 
                                                    ((IData)(1U) 
                                                     << 
                                                     (3U 
                                                      & vlSelf->addr_i))
                                                     : 0U))));
    vlSelf->DM__DOT__wdata_ext = ((2U == (IData)(vlSelf->mem_op_i))
                                   ? (0xffU & vlSelf->wdata_i)
                                   : ((1U == (IData)(vlSelf->mem_op_i))
                                       ? (0xffffU & vlSelf->wdata_i)
                                       : vlSelf->wdata_i));
    vlSelf->rdata = ((0x10U & (IData)(vlSelf->addr))
                      ? 0U : ((8U & (IData)(vlSelf->addr))
                               ? ((4U & (IData)(vlSelf->addr))
                                   ? ((2U & (IData)(vlSelf->addr))
                                       ? ((1U & (IData)(vlSelf->addr))
                                           ? 0U : vlSelf->CP0_Reg__DOT__epc_reg)
                                       : ((1U & (IData)(vlSelf->addr))
                                           ? vlSelf->CP0_Reg__DOT__cause_reg
                                           : vlSelf->CP0_Reg__DOT__status_reg))
                                   : ((2U & (IData)(vlSelf->addr))
                                       ? 0U : ((1U 
                                                & (IData)(vlSelf->addr))
                                                ? vlSelf->CP0_Reg__DOT__count_reg
                                                : vlSelf->CP0_Reg__DOT__badvaddr_reg)))
                               : 0U));
    vlSelf->DM__DOT__rdata_raw = vlSelf->DM__DOT__data_mem
        [(0xfffU & (vlSelf->addr_i >> 2U))];
    vlSelf->DM__DOT__byte_sel = (0xffU & ((0U == (3U 
                                                  & vlSelf->addr_i))
                                           ? vlSelf->DM__DOT__rdata_raw
                                           : ((1U == 
                                               (3U 
                                                & vlSelf->addr_i))
                                               ? (vlSelf->DM__DOT__rdata_raw 
                                                  >> 8U)
                                               : ((2U 
                                                   == 
                                                   (3U 
                                                    & vlSelf->addr_i))
                                                   ? 
                                                  (vlSelf->DM__DOT__rdata_raw 
                                                   >> 0x10U)
                                                   : 
                                                  (vlSelf->DM__DOT__rdata_raw 
                                                   >> 0x18U)))));
    vlSelf->DM__DOT__halfword_sel = (0xffffU & ((2U 
                                                 & vlSelf->addr_i)
                                                 ? 
                                                (vlSelf->DM__DOT__rdata_raw 
                                                 >> 0x10U)
                                                 : vlSelf->DM__DOT__rdata_raw));
    vlSelf->rdata_o = ((4U & (IData)(vlSelf->mem_op_i))
                        ? ((2U & (IData)(vlSelf->mem_op_i))
                            ? ((1U & (IData)(vlSelf->mem_op_i))
                                ? (IData)(vlSelf->DM__DOT__byte_sel)
                                : (((- (IData)((1U 
                                                & ((IData)(vlSelf->DM__DOT__byte_sel) 
                                                   >> 7U)))) 
                                    << 8U) | (IData)(vlSelf->DM__DOT__byte_sel)))
                            : ((1U & (IData)(vlSelf->mem_op_i))
                                ? (IData)(vlSelf->DM__DOT__halfword_sel)
                                : (((- (IData)((1U 
                                                & ((IData)(vlSelf->DM__DOT__halfword_sel) 
                                                   >> 0xfU)))) 
                                    << 0x10U) | (IData)(vlSelf->DM__DOT__halfword_sel))))
                        : vlSelf->DM__DOT__rdata_raw);
}

void Vmips___024root___eval_ico(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vmips___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VlCoroutine Vmips___024root____Vfork_h6d8ad74a__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_hf050e82d__0);
VlCoroutine Vmips___024root____Vfork_h2576075f__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_hfd3834eb__0);
VlCoroutine Vmips___024root____Vfork_h1620e13b__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_h855142b1__0);

VL_INLINE_OPT void Vmips___024root___act_sequent__TOP__0(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___act_sequent__TOP__0\n"); );
    // Body
    vlSelf->mips__DOT__dp__DOT__h__DOT__lwstallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__lwstallD__0;
    vlSelf->mips__DOT__dp__DOT__h__DOT__branchstallD 
        = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__branchstallD__0;
    vlSelf->mips__DOT__dp__DOT__h__DOT__divstallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__divstallD__0;
    Vmips___024root____Vfork_h6d8ad74a__0__0(vlSelf, vlSelf->__Vintraval_hf050e82d__0);
    vlSelf->mips__DOT__dp__DOT__stallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallD__0;
    Vmips___024root____Vfork_h2576075f__0__0(vlSelf, vlSelf->__Vintraval_hfd3834eb__0);
    Vmips___024root____Vfork_h1620e13b__0__0(vlSelf, vlSelf->__Vintraval_h855142b1__0);
    vlSelf->mips__DOT__dp__DOT__stallF = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallF__0;
    vlSelf->mips__DOT__flushE = vlSelf->__VassignWtmp_mips__DOT__flushE__0;
}

VL_INLINE_OPT VlCoroutine Vmips___024root____Vfork_h1620e13b__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_h855142b1__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root____Vfork_h1620e13b__0__0\n"); );
    // Body
    __Vintraval_h855142b1__0 = vlSelf->mips__DOT__dp__DOT__stallD;
    co_await vlSelf->__VdlySched.delay(0x3e8U, "hazard.v", 97);
    vlSelf->__VassignWtmp_mips__DOT__flushE__0 = __Vintraval_h855142b1__0;
}

VL_INLINE_OPT VlCoroutine Vmips___024root____Vfork_h2576075f__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_hfd3834eb__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root____Vfork_h2576075f__0__0\n"); );
    // Body
    __Vintraval_hfd3834eb__0 = vlSelf->mips__DOT__dp__DOT__stallD;
    co_await vlSelf->__VdlySched.delay(0x3e8U, "hazard.v", 95);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallF__0 
        = __Vintraval_hfd3834eb__0;
}

VL_INLINE_OPT VlCoroutine Vmips___024root____Vfork_h6d8ad74a__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_hf050e82d__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root____Vfork_h6d8ad74a__0__0\n"); );
    // Body
    __Vintraval_hf050e82d__0 = (((IData)(vlSelf->mips__DOT__dp__DOT__h__DOT__lwstallD) 
                                 | (IData)(vlSelf->mips__DOT__dp__DOT__h__DOT__branchstallD)) 
                                | (IData)(vlSelf->mips__DOT__dp__DOT__h__DOT__divstallD));
    co_await vlSelf->__VdlySched.delay(0x3e8U, "hazard.v", 94);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallD__0 
        = __Vintraval_hf050e82d__0;
}

void Vmips___024root___eval_act(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_act\n"); );
    // Body
    if (vlSelf->__VactTriggered.at(5U)) {
        Vmips___024root___act_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vmips___024root___nba_sequent__TOP__0(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->CP0_Reg__02Erst) {
        vlSelf->CP0_Reg__DOT__count_reg = 0U;
        vlSelf->CP0_Reg__DOT__badvaddr_reg = 0U;
        vlSelf->CP0_Reg__DOT__status_reg = 0U;
        vlSelf->CP0_Reg__DOT__epc_reg = 0U;
        vlSelf->CP0_Reg__DOT__cause_reg = 0U;
    } else {
        vlSelf->CP0_Reg__DOT__count_reg = ((IData)(1U) 
                                           + vlSelf->CP0_Reg__DOT__count_reg);
        if (vlSelf->exception_o) {
            vlSelf->CP0_Reg__DOT__badvaddr_reg = vlSelf->epc_i;
            vlSelf->CP0_Reg__DOT__epc_reg = vlSelf->epc_i;
            vlSelf->CP0_Reg__DOT__cause_reg = ((IData)(vlSelf->syscall_i)
                                                ? 8U
                                                : ((IData)(vlSelf->break_i)
                                                    ? 9U
                                                    : (IData)(vlSelf->cause_i)));
        } else {
            if (((IData)(vlSelf->we) & (0xeU == (IData)(vlSelf->addr)))) {
                vlSelf->CP0_Reg__DOT__epc_reg = vlSelf->wdata;
            }
            if (((IData)(vlSelf->we) & (0xdU == (IData)(vlSelf->addr)))) {
                vlSelf->CP0_Reg__DOT__cause_reg = vlSelf->wdata;
            }
        }
        if (((IData)(vlSelf->we) & (0xcU == (IData)(vlSelf->addr)))) {
            vlSelf->CP0_Reg__DOT__status_reg = vlSelf->wdata;
        }
    }
    vlSelf->epc_o = vlSelf->CP0_Reg__DOT__epc_reg;
    vlSelf->cause_o = (0x3fU & vlSelf->CP0_Reg__DOT__cause_reg);
    vlSelf->rdata = ((0x10U & (IData)(vlSelf->addr))
                      ? 0U : ((8U & (IData)(vlSelf->addr))
                               ? ((4U & (IData)(vlSelf->addr))
                                   ? ((2U & (IData)(vlSelf->addr))
                                       ? ((1U & (IData)(vlSelf->addr))
                                           ? 0U : vlSelf->CP0_Reg__DOT__epc_reg)
                                       : ((1U & (IData)(vlSelf->addr))
                                           ? vlSelf->CP0_Reg__DOT__cause_reg
                                           : vlSelf->CP0_Reg__DOT__status_reg))
                                   : ((2U & (IData)(vlSelf->addr))
                                       ? 0U : ((1U 
                                                & (IData)(vlSelf->addr))
                                                ? vlSelf->CP0_Reg__DOT__count_reg
                                                : vlSelf->CP0_Reg__DOT__badvaddr_reg)))
                               : 0U));
}

VL_INLINE_OPT void Vmips___024root___nba_sequent__TOP__1(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_sequent__TOP__1\n"); );
    // Init
    SData/*11:0*/ __Vdlyvdim0__DM__DOT__data_mem__v0;
    CData/*4:0*/ __Vdlyvlsb__DM__DOT__data_mem__v0;
    CData/*7:0*/ __Vdlyvval__DM__DOT__data_mem__v0;
    CData/*0:0*/ __Vdlyvset__DM__DOT__data_mem__v0;
    SData/*11:0*/ __Vdlyvdim0__DM__DOT__data_mem__v1;
    CData/*4:0*/ __Vdlyvlsb__DM__DOT__data_mem__v1;
    CData/*7:0*/ __Vdlyvval__DM__DOT__data_mem__v1;
    CData/*0:0*/ __Vdlyvset__DM__DOT__data_mem__v1;
    SData/*11:0*/ __Vdlyvdim0__DM__DOT__data_mem__v2;
    CData/*4:0*/ __Vdlyvlsb__DM__DOT__data_mem__v2;
    CData/*7:0*/ __Vdlyvval__DM__DOT__data_mem__v2;
    CData/*0:0*/ __Vdlyvset__DM__DOT__data_mem__v2;
    SData/*11:0*/ __Vdlyvdim0__DM__DOT__data_mem__v3;
    CData/*4:0*/ __Vdlyvlsb__DM__DOT__data_mem__v3;
    CData/*7:0*/ __Vdlyvval__DM__DOT__data_mem__v3;
    CData/*0:0*/ __Vdlyvset__DM__DOT__data_mem__v3;
    // Body
    __Vdlyvset__DM__DOT__data_mem__v0 = 0U;
    __Vdlyvset__DM__DOT__data_mem__v1 = 0U;
    __Vdlyvset__DM__DOT__data_mem__v2 = 0U;
    __Vdlyvset__DM__DOT__data_mem__v3 = 0U;
    if (vlSelf->we_i) {
        if ((1U & (IData)(vlSelf->DM__DOT__byte_we))) {
            __Vdlyvval__DM__DOT__data_mem__v0 = (0xffU 
                                                 & vlSelf->DM__DOT__wdata_ext);
            __Vdlyvset__DM__DOT__data_mem__v0 = 1U;
            __Vdlyvlsb__DM__DOT__data_mem__v0 = 0U;
            __Vdlyvdim0__DM__DOT__data_mem__v0 = (0xfffU 
                                                  & (vlSelf->addr_i 
                                                     >> 2U));
        }
        if ((2U & (IData)(vlSelf->DM__DOT__byte_we))) {
            __Vdlyvval__DM__DOT__data_mem__v1 = (0xffU 
                                                 & (vlSelf->DM__DOT__wdata_ext 
                                                    >> 8U));
            __Vdlyvset__DM__DOT__data_mem__v1 = 1U;
            __Vdlyvlsb__DM__DOT__data_mem__v1 = 8U;
            __Vdlyvdim0__DM__DOT__data_mem__v1 = (0xfffU 
                                                  & (vlSelf->addr_i 
                                                     >> 2U));
        }
        if ((4U & (IData)(vlSelf->DM__DOT__byte_we))) {
            __Vdlyvval__DM__DOT__data_mem__v2 = (0xffU 
                                                 & (vlSelf->DM__DOT__wdata_ext 
                                                    >> 0x10U));
            __Vdlyvset__DM__DOT__data_mem__v2 = 1U;
            __Vdlyvlsb__DM__DOT__data_mem__v2 = 0x10U;
            __Vdlyvdim0__DM__DOT__data_mem__v2 = (0xfffU 
                                                  & (vlSelf->addr_i 
                                                     >> 2U));
        }
        if ((8U & (IData)(vlSelf->DM__DOT__byte_we))) {
            __Vdlyvval__DM__DOT__data_mem__v3 = (vlSelf->DM__DOT__wdata_ext 
                                                 >> 0x18U);
            __Vdlyvset__DM__DOT__data_mem__v3 = 1U;
            __Vdlyvlsb__DM__DOT__data_mem__v3 = 0x18U;
            __Vdlyvdim0__DM__DOT__data_mem__v3 = (0xfffU 
                                                  & (vlSelf->addr_i 
                                                     >> 2U));
        }
    }
    if (__Vdlyvset__DM__DOT__data_mem__v0) {
        vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v0))) 
                & vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v0]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__DM__DOT__data_mem__v0) 
                                   << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v0))));
    }
    if (__Vdlyvset__DM__DOT__data_mem__v1) {
        vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v1))) 
                & vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v1]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__DM__DOT__data_mem__v1) 
                                   << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v1))));
    }
    if (__Vdlyvset__DM__DOT__data_mem__v2) {
        vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v2))) 
                & vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v2]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__DM__DOT__data_mem__v2) 
                                   << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v2))));
    }
    if (__Vdlyvset__DM__DOT__data_mem__v3) {
        vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v3))) 
                & vlSelf->DM__DOT__data_mem[__Vdlyvdim0__DM__DOT__data_mem__v3]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__DM__DOT__data_mem__v3) 
                                   << (IData)(__Vdlyvlsb__DM__DOT__data_mem__v3))));
    }
    vlSelf->DM__DOT__rdata_raw = vlSelf->DM__DOT__data_mem
        [(0xfffU & (vlSelf->addr_i >> 2U))];
    vlSelf->DM__DOT__byte_sel = (0xffU & ((0U == (3U 
                                                  & vlSelf->addr_i))
                                           ? vlSelf->DM__DOT__rdata_raw
                                           : ((1U == 
                                               (3U 
                                                & vlSelf->addr_i))
                                               ? (vlSelf->DM__DOT__rdata_raw 
                                                  >> 8U)
                                               : ((2U 
                                                   == 
                                                   (3U 
                                                    & vlSelf->addr_i))
                                                   ? 
                                                  (vlSelf->DM__DOT__rdata_raw 
                                                   >> 0x10U)
                                                   : 
                                                  (vlSelf->DM__DOT__rdata_raw 
                                                   >> 0x18U)))));
    vlSelf->DM__DOT__halfword_sel = (0xffffU & ((2U 
                                                 & vlSelf->addr_i)
                                                 ? 
                                                (vlSelf->DM__DOT__rdata_raw 
                                                 >> 0x10U)
                                                 : vlSelf->DM__DOT__rdata_raw));
    vlSelf->rdata_o = ((4U & (IData)(vlSelf->mem_op_i))
                        ? ((2U & (IData)(vlSelf->mem_op_i))
                            ? ((1U & (IData)(vlSelf->mem_op_i))
                                ? (IData)(vlSelf->DM__DOT__byte_sel)
                                : (((- (IData)((1U 
                                                & ((IData)(vlSelf->DM__DOT__byte_sel) 
                                                   >> 7U)))) 
                                    << 8U) | (IData)(vlSelf->DM__DOT__byte_sel)))
                            : ((1U & (IData)(vlSelf->mem_op_i))
                                ? (IData)(vlSelf->DM__DOT__halfword_sel)
                                : (((- (IData)((1U 
                                                & ((IData)(vlSelf->DM__DOT__halfword_sel) 
                                                   >> 0xfU)))) 
                                    << 0x10U) | (IData)(vlSelf->DM__DOT__halfword_sel))))
                        : vlSelf->DM__DOT__rdata_raw);
}

VL_INLINE_OPT void Vmips___024root___nba_sequent__TOP__2(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_sequent__TOP__2\n"); );
    // Init
    CData/*4:0*/ __Vdlyvdim0__mips__DOT__dp__DOT__rf__DOT__rf__v0;
    IData/*31:0*/ __Vdlyvval__mips__DOT__dp__DOT__rf__DOT__rf__v0;
    CData/*0:0*/ __Vdlyvset__mips__DOT__dp__DOT__rf__DOT__rf__v0;
    // Body
    __Vdlyvset__mips__DOT__dp__DOT__rf__DOT__rf__v0 = 0U;
    if ((1U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4))) {
        __Vdlyvval__mips__DOT__dp__DOT__rf__DOT__rf__v0 
            = vlSelf->mips__DOT__dp__DOT__resultW;
        __Vdlyvset__mips__DOT__dp__DOT__rf__DOT__rf__v0 = 1U;
        __Vdlyvdim0__mips__DOT__dp__DOT__rf__DOT__rf__v0 
            = vlSelf->mips__DOT__dp__DOT__writeregW;
    }
    if (__Vdlyvset__mips__DOT__dp__DOT__rf__DOT__rf__v0) {
        vlSelf->mips__DOT__dp__DOT__rf__DOT__rf[__Vdlyvdim0__mips__DOT__dp__DOT__rf__DOT__rf__v0] 
            = __Vdlyvval__mips__DOT__dp__DOT__rf__DOT__rf__v0;
    }
}

VlCoroutine Vmips___024root____Vfork_hbe974bec__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_ha3f6fe5a__0);

VL_INLINE_OPT void Vmips___024root___nba_sequent__TOP__3(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_sequent__TOP__3\n"); );
    // Body
    if (vlSelf->mips__02Erst) {
        vlSelf->writedataM = 0U;
        vlSelf->mips__DOT__dp__DOT__srcaE = 0U;
        vlSelf->mips__DOT__dp__DOT__signimmE = 0U;
        vlSelf->mips__DOT__dp__DOT__srcbE = 0U;
        vlSelf->mips__DOT__dp__DOT__readdataW = 0U;
        vlSelf->mips__DOT__dp__DOT__rsE = 0U;
        vlSelf->mips__DOT__dp__DOT__rdE = 0U;
        vlSelf->mips__DOT__dp__DOT__rtE = 0U;
        vlSelf->mips__DOT__dp__DOT__aluoutW = 0U;
        vlSelf->mips__DOT__dp__DOT__writeregW = 0U;
        vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4 = 0U;
        vlSelf->aluoutM = 0U;
        vlSelf->mips__DOT__dp__DOT__writeregM = 0U;
        vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4 = 0U;
        vlSelf->mips__DOT__dp__DOT__lo_outE = 0U;
        vlSelf->mips__DOT__dp__DOT__hi_outE = 0U;
        vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5 = 0U;
    } else {
        vlSelf->writedataM = vlSelf->mips__DOT__dp__DOT__srcb2E;
        vlSelf->mips__DOT__dp__DOT__readdataW = vlSelf->readdataM;
        vlSelf->mips__DOT__dp__DOT__aluoutW = vlSelf->aluoutM;
        vlSelf->mips__DOT__dp__DOT__writeregW = vlSelf->mips__DOT__dp__DOT__writeregM;
        vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4 
            = ((2U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4) 
                      >> 1U)) | (1U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4)));
        vlSelf->aluoutM = ((0U == (3U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                         >> 1U))) ? vlSelf->mips__DOT__dp__DOT__lo_outE
                            : ((1U == (3U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                             >> 1U)))
                                ? vlSelf->mips__DOT__dp__DOT__hi_outE
                                : ((2U == (3U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                                 >> 1U)))
                                    ? vlSelf->mips__DOT__dp__DOT__aluresultE
                                    : vlSelf->mips__DOT__dp__DOT__lo_outE)));
        vlSelf->mips__DOT__dp__DOT__writeregM = vlSelf->mips__DOT__dp__DOT__writeregE;
        vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4 
            = ((6U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                      >> 0xbU)) | (1U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                         >> 9U)));
        if ((3U == (3U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                          >> 3U)))) {
            vlSelf->mips__DOT__dp__DOT__lo_outE = vlSelf->mips__DOT__dp__DOT__lo_inE;
            vlSelf->mips__DOT__dp__DOT__hi_outE = vlSelf->mips__DOT__dp__DOT__hi_inE;
        } else {
            if ((1U != (3U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                              >> 3U)))) {
                if ((0U == (3U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                  >> 3U)))) {
                    vlSelf->mips__DOT__dp__DOT__lo_outE 
                        = vlSelf->mips__DOT__dp__DOT__lo_inE;
                }
            }
            if ((1U == (3U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                              >> 3U)))) {
                vlSelf->mips__DOT__dp__DOT__hi_outE 
                    = vlSelf->mips__DOT__dp__DOT__hi_inE;
            }
        }
        if (vlSelf->mips__DOT__flushE) {
            vlSelf->mips__DOT__dp__DOT__srcaE = 0U;
            vlSelf->mips__DOT__dp__DOT__signimmE = 0U;
            vlSelf->mips__DOT__dp__DOT__srcbE = 0U;
            vlSelf->mips__DOT__dp__DOT__rsE = 0U;
            vlSelf->mips__DOT__dp__DOT__rdE = 0U;
            vlSelf->mips__DOT__dp__DOT__rtE = 0U;
            vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5 = 0U;
        } else {
            vlSelf->mips__DOT__dp__DOT__srcaE = vlSelf->mips__DOT__dp__DOT__srcaD;
            vlSelf->mips__DOT__dp__DOT__signimmE = vlSelf->mips__DOT__dp__DOT__signimmD;
            vlSelf->mips__DOT__dp__DOT__srcbE = vlSelf->mips__DOT__dp__DOT__srcbD;
            vlSelf->mips__DOT__dp__DOT__rsE = (0x1fU 
                                               & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                  >> 0x15U));
            vlSelf->mips__DOT__dp__DOT__rdE = (0x1fU 
                                               & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                  >> 0xbU));
            vlSelf->mips__DOT__dp__DOT__rtE = (0x1fU 
                                               & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                  >> 0x10U));
            vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5 
                = ((0x2000U & ((IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls) 
                               << 9U)) | ((0x1000U 
                                           & ((IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls) 
                                              << 7U)) 
                                          | ((0x800U 
                                              & ((IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls) 
                                                 << 4U)) 
                                             | ((0x400U 
                                                 & ((IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls) 
                                                    << 2U)) 
                                                | ((0x200U 
                                                    & (IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls)) 
                                                   | (((IData)(vlSelf->mips__DOT__c__DOT__alucontrolD) 
                                                       << 6U) 
                                                      | ((0x20U 
                                                          & (((IData)(vlSelf->mips__DOT__c__DOT__hassign_ad) 
                                                              | (IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls)) 
                                                             << 5U)) 
                                                         | (((IData)(vlSelf->mips__DOT__c__DOT__hilo_enD) 
                                                             << 3U) 
                                                            | (((IData)(vlSelf->mips__DOT__c__DOT__hilo_mfD) 
                                                                << 1U) 
                                                               | ((0U 
                                                                   == 
                                                                   (vlSelf->mips__DOT__dp__DOT__instrD 
                                                                    >> 0x1aU)) 
                                                                  & ((0x1aU 
                                                                      == 
                                                                      (0x3fU 
                                                                       & vlSelf->mips__DOT__dp__DOT__instrD)) 
                                                                     | (0x1bU 
                                                                        == 
                                                                        (0x3fU 
                                                                         & vlSelf->mips__DOT__dp__DOT__instrD)))))))))))));
        }
    }
    vlSelf->mips__DOT__dp__DOT__resultW = ((2U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4))
                                            ? vlSelf->mips__DOT__dp__DOT__readdataW
                                            : vlSelf->mips__DOT__dp__DOT__aluoutW);
    vlSelf->memwriteM = (1U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4) 
                               >> 1U));
    vlSelf->mips__DOT__dp__DOT__forwardaE = 0U;
    if ((0U != (IData)(vlSelf->mips__DOT__dp__DOT__rsE))) {
        if ((((IData)(vlSelf->mips__DOT__dp__DOT__rsE) 
              == (IData)(vlSelf->mips__DOT__dp__DOT__writeregM)) 
             & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4))) {
            vlSelf->mips__DOT__dp__DOT__forwardaE = 2U;
        } else if ((((IData)(vlSelf->mips__DOT__dp__DOT__rsE) 
                     == (IData)(vlSelf->mips__DOT__dp__DOT__writeregW)) 
                    & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4))) {
            vlSelf->mips__DOT__dp__DOT__forwardaE = 1U;
        }
    }
    vlSelf->mips__DOT__dp__DOT__forwardbE = 0U;
    if ((0U != (IData)(vlSelf->mips__DOT__dp__DOT__rtE))) {
        if ((((IData)(vlSelf->mips__DOT__dp__DOT__rtE) 
              == (IData)(vlSelf->mips__DOT__dp__DOT__writeregM)) 
             & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4))) {
            vlSelf->mips__DOT__dp__DOT__forwardbE = 2U;
        } else if ((((IData)(vlSelf->mips__DOT__dp__DOT__rtE) 
                     == (IData)(vlSelf->mips__DOT__dp__DOT__writeregW)) 
                    & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4))) {
            vlSelf->mips__DOT__dp__DOT__forwardbE = 1U;
        }
    }
    vlSelf->mips__DOT__dp__DOT__srca2E = ((0U == (IData)(vlSelf->mips__DOT__dp__DOT__forwardaE))
                                           ? vlSelf->mips__DOT__dp__DOT__srcaE
                                           : ((1U == (IData)(vlSelf->mips__DOT__dp__DOT__forwardaE))
                                               ? vlSelf->mips__DOT__dp__DOT__resultW
                                               : ((2U 
                                                   == (IData)(vlSelf->mips__DOT__dp__DOT__forwardaE))
                                                   ? vlSelf->aluoutM
                                                   : vlSelf->mips__DOT__dp__DOT__srcaE)));
    vlSelf->mips__DOT__dp__DOT__srcb2E = ((0U == (IData)(vlSelf->mips__DOT__dp__DOT__forwardbE))
                                           ? vlSelf->mips__DOT__dp__DOT__srcbE
                                           : ((1U == (IData)(vlSelf->mips__DOT__dp__DOT__forwardbE))
                                               ? vlSelf->mips__DOT__dp__DOT__resultW
                                               : ((2U 
                                                   == (IData)(vlSelf->mips__DOT__dp__DOT__forwardbE))
                                                   ? vlSelf->aluoutM
                                                   : vlSelf->mips__DOT__dp__DOT__srcbE)));
    vlSelf->mips__DOT__dp__DOT__srcb3E = ((0x800U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                           ? vlSelf->mips__DOT__dp__DOT__signimmE
                                           : vlSelf->mips__DOT__dp__DOT__srcb2E);
    Vmips___024root____Vfork_hbe974bec__0__0(vlSelf, vlSelf->__Vintraval_ha3f6fe5a__0);
    vlSelf->mips__DOT__dp__DOT__writeregE = ((0x400U 
                                              & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                              ? (IData)(vlSelf->mips__DOT__dp__DOT__rdE)
                                              : (IData)(vlSelf->mips__DOT__dp__DOT__rtE));
    vlSelf->mips__DOT__dp__DOT__aluresult_loE = 0U;
    if ((1U & (~ ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                  >> 7U)))) {
        if ((1U & (~ ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                      >> 6U)))) {
            if ((0x100U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))) {
                vlSelf->mips__DOT__dp__DOT__aluresult_loE 
                    = ((0x20U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                        ? (IData)(VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelf->mips__DOT__dp__DOT__srca2E), 
                                              VL_EXTENDS_QI(64,32, vlSelf->mips__DOT__dp__DOT__srcb3E)))
                        : (IData)(((QData)((IData)(vlSelf->mips__DOT__dp__DOT__srca2E)) 
                                   * (QData)((IData)(vlSelf->mips__DOT__dp__DOT__srcb3E)))));
            }
        }
    }
    vlSelf->mips__DOT__dp__DOT__alu__DOT__bout = ((0x100U 
                                                   & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                                   ? 
                                                  (~ vlSelf->mips__DOT__dp__DOT__srcb3E)
                                                   : vlSelf->mips__DOT__dp__DOT__srcb3E);
    vlSelf->mips__DOT__dp__DOT__alu__DOT__s = (vlSelf->mips__DOT__dp__DOT__srca2E 
                                               + (vlSelf->mips__DOT__dp__DOT__alu__DOT__bout 
                                                  + 
                                                  (1U 
                                                   & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                                      >> 8U))));
    vlSelf->mips__DOT__dp__DOT__aluresultE = ((0x80U 
                                               & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                               ? ((0x40U 
                                                   & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                                   ? 
                                                  ((0x20U 
                                                    & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                                    ? 
                                                   ((vlSelf->mips__DOT__dp__DOT__alu__DOT__s 
                                                     >> 0x1fU) 
                                                    ^ 
                                                    ((((~ 
                                                        (vlSelf->mips__DOT__dp__DOT__srca2E 
                                                         >> 0x1fU)) 
                                                       & (vlSelf->mips__DOT__dp__DOT__srcb3E 
                                                          >> 0x1fU)) 
                                                      & (vlSelf->mips__DOT__dp__DOT__alu__DOT__s 
                                                         >> 0x1fU)) 
                                                     | (((vlSelf->mips__DOT__dp__DOT__srca2E 
                                                          >> 0x1fU) 
                                                         & (~ 
                                                            (vlSelf->mips__DOT__dp__DOT__srcb3E 
                                                             >> 0x1fU))) 
                                                        & (~ 
                                                           (vlSelf->mips__DOT__dp__DOT__alu__DOT__s 
                                                            >> 0x1fU)))))
                                                    : 
                                                   (vlSelf->mips__DOT__dp__DOT__srca2E 
                                                    < vlSelf->mips__DOT__dp__DOT__srcb3E))
                                                   : vlSelf->mips__DOT__dp__DOT__alu__DOT__s)
                                               : ((0x40U 
                                                   & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                                   ? 
                                                  (vlSelf->mips__DOT__dp__DOT__srca2E 
                                                   | vlSelf->mips__DOT__dp__DOT__alu__DOT__bout)
                                                   : 
                                                  ((0x100U 
                                                    & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                                    ? 
                                                   ((0x20U 
                                                     & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                                     ? (IData)(
                                                               (VL_MULS_QQQ(64, 
                                                                            VL_EXTENDS_QI(64,32, vlSelf->mips__DOT__dp__DOT__srca2E), 
                                                                            VL_EXTENDS_QI(64,32, vlSelf->mips__DOT__dp__DOT__srcb3E)) 
                                                                >> 0x20U))
                                                     : (IData)(
                                                               (((QData)((IData)(vlSelf->mips__DOT__dp__DOT__srca2E)) 
                                                                 * (QData)((IData)(vlSelf->mips__DOT__dp__DOT__srcb3E))) 
                                                                >> 0x20U)))
                                                    : 
                                                   (vlSelf->mips__DOT__dp__DOT__srca2E 
                                                    & vlSelf->mips__DOT__dp__DOT__alu__DOT__bout))));
    if ((0x10U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))) {
        vlSelf->mips__DOT__dp__DOT__lo_inE = vlSelf->mips__DOT__dp__DOT__aluresult_loE;
        vlSelf->mips__DOT__dp__DOT__hi_inE = vlSelf->mips__DOT__dp__DOT__aluresultE;
    } else {
        vlSelf->mips__DOT__dp__DOT__lo_inE = vlSelf->mips__DOT__dp__DOT__srca2E;
        vlSelf->mips__DOT__dp__DOT__hi_inE = vlSelf->mips__DOT__dp__DOT__srca2E;
    }
}

VL_INLINE_OPT VlCoroutine Vmips___024root____Vfork_hbe974bec__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_ha3f6fe5a__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root____Vfork_hbe974bec__0__0\n"); );
    // Body
    __Vintraval_ha3f6fe5a__0 = (1U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5));
    co_await vlSelf->__VdlySched.delay(0x3e8U, "hazard.v", 92);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__divstallD__0 
        = __Vintraval_ha3f6fe5a__0;
}

extern const VlUnpacked<SData/*9:0*/, 64> Vmips__ConstPool__TABLE_h8b5122f1_0;
extern const VlUnpacked<CData/*0:0*/, 256> Vmips__ConstPool__TABLE_h2aff9509_0;
extern const VlUnpacked<CData/*1:0*/, 256> Vmips__ConstPool__TABLE_h8d474863_0;
extern const VlUnpacked<CData/*1:0*/, 256> Vmips__ConstPool__TABLE_h318e41b4_0;
extern const VlUnpacked<CData/*2:0*/, 256> Vmips__ConstPool__TABLE_hf91ec95b_0;

VL_INLINE_OPT void Vmips___024root___nba_sequent__TOP__4(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_sequent__TOP__4\n"); );
    // Body
    if (vlSelf->mips__02Erst) {
        vlSelf->mips__DOT__dp__DOT__pcplus4D = 0U;
        vlSelf->mips__DOT__dp__DOT__instrD = 0U;
    } else {
        if ((1U & (~ (IData)(vlSelf->mips__DOT__dp__DOT__stallD)))) {
            vlSelf->mips__DOT__dp__DOT__pcplus4D = 
                ((IData)(4U) + vlSelf->pcF);
        }
        if (vlSelf->mips__DOT__dp__DOT__flushD) {
            vlSelf->mips__DOT__dp__DOT__instrD = 0U;
        } else if ((1U & (~ (IData)(vlSelf->mips__DOT__dp__DOT__stallD)))) {
            vlSelf->mips__DOT__dp__DOT__instrD = vlSelf->instrF;
        }
    }
    vlSelf->mips__DOT__dp__DOT__signimmD = (((- (IData)(
                                                        (1U 
                                                         & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                            >> 0xfU)))) 
                                             << 0x10U) 
                                            | (0xffffU 
                                               & vlSelf->mips__DOT__dp__DOT__instrD));
    vlSelf->__Vtableidx1 = (vlSelf->mips__DOT__dp__DOT__instrD 
                            >> 0x1aU);
    vlSelf->mips__DOT__c__DOT__md__DOT__controls = 
        Vmips__ConstPool__TABLE_h8b5122f1_0[vlSelf->__Vtableidx1];
    vlSelf->__Vtableidx2 = ((0xfcU & (vlSelf->mips__DOT__dp__DOT__instrD 
                                      << 2U)) | (3U 
                                                 & ((IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls) 
                                                    >> 1U)));
    vlSelf->mips__DOT__c__DOT__hassign_ad = Vmips__ConstPool__TABLE_h2aff9509_0
        [vlSelf->__Vtableidx2];
    vlSelf->mips__DOT__c__DOT__hilo_enD = Vmips__ConstPool__TABLE_h8d474863_0
        [vlSelf->__Vtableidx2];
    vlSelf->mips__DOT__c__DOT__hilo_mfD = Vmips__ConstPool__TABLE_h318e41b4_0
        [vlSelf->__Vtableidx2];
    vlSelf->mips__DOT__c__DOT__alucontrolD = Vmips__ConstPool__TABLE_hf91ec95b_0
        [vlSelf->__Vtableidx2];
}

VL_INLINE_OPT void Vmips___024root___nba_comb__TOP__0(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_comb__TOP__0\n"); );
    // Body
    vlSelf->mips__DOT__dp__DOT__h__DOT__divstallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__divstallD__0;
}

VL_INLINE_OPT void Vmips___024root___nba_sequent__TOP__5(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_sequent__TOP__5\n"); );
    // Body
    if (vlSelf->mips__02Erst) {
        vlSelf->pcF = 0U;
    } else if ((1U & (~ (IData)(vlSelf->mips__DOT__dp__DOT__stallF)))) {
        vlSelf->pcF = vlSelf->mips__DOT__dp__DOT__pcnextFD;
    }
}

VL_INLINE_OPT void Vmips___024root___nba_comb__TOP__1(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_comb__TOP__1\n"); );
    // Body
    vlSelf->mips__DOT__dp__DOT__srcaD = ((0U == (0x1fU 
                                                 & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                    >> 0x15U)))
                                          ? 0U : vlSelf->mips__DOT__dp__DOT__rf__DOT__rf
                                         [(0x1fU & 
                                           (vlSelf->mips__DOT__dp__DOT__instrD 
                                            >> 0x15U))]);
    vlSelf->mips__DOT__dp__DOT__srcbD = ((0U == (0x1fU 
                                                 & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                    >> 0x10U)))
                                          ? 0U : vlSelf->mips__DOT__dp__DOT__rf__DOT__rf
                                         [(0x1fU & 
                                           (vlSelf->mips__DOT__dp__DOT__instrD 
                                            >> 0x10U))]);
}

VlCoroutine Vmips___024root____Vfork_hf3256427__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_ha53d58cb__0);
VlCoroutine Vmips___024root____Vfork_hda8f6c3d__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_h416f4670__0);

VL_INLINE_OPT void Vmips___024root___nba_comb__TOP__2(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_comb__TOP__2\n"); );
    // Body
    Vmips___024root____Vfork_hf3256427__0__0(vlSelf, vlSelf->__Vintraval_ha53d58cb__0);
    Vmips___024root____Vfork_hda8f6c3d__0__0(vlSelf, vlSelf->__Vintraval_h416f4670__0);
}

VL_INLINE_OPT VlCoroutine Vmips___024root____Vfork_hda8f6c3d__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_h416f4670__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root____Vfork_hda8f6c3d__0__0\n"); );
    // Body
    __Vintraval_h416f4670__0 = (((IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls) 
                                 >> 6U) & ((((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                             >> 9U) 
                                            & (((IData)(vlSelf->mips__DOT__dp__DOT__writeregE) 
                                                == 
                                                (0x1fU 
                                                 & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                    >> 0x15U))) 
                                               | ((IData)(vlSelf->mips__DOT__dp__DOT__writeregE) 
                                                  == 
                                                  (0x1fU 
                                                   & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                      >> 0x10U))))) 
                                           | (((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4) 
                                               >> 2U) 
                                              & (((IData)(vlSelf->mips__DOT__dp__DOT__writeregM) 
                                                  == 
                                                  (0x1fU 
                                                   & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                      >> 0x15U))) 
                                                 | ((IData)(vlSelf->mips__DOT__dp__DOT__writeregM) 
                                                    == 
                                                    (0x1fU 
                                                     & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                        >> 0x10U)))))));
    co_await vlSelf->__VdlySched.delay(0x3e8U, "hazard.v", 85);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__branchstallD__0 
        = __Vintraval_h416f4670__0;
}

VL_INLINE_OPT VlCoroutine Vmips___024root____Vfork_hf3256427__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_ha53d58cb__0) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root____Vfork_hf3256427__0__0\n"); );
    // Body
    __Vintraval_ha53d58cb__0 = (((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                 >> 0xdU) & (((IData)(vlSelf->mips__DOT__dp__DOT__rtE) 
                                              == (0x1fU 
                                                  & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                     >> 0x15U))) 
                                             | ((IData)(vlSelf->mips__DOT__dp__DOT__rtE) 
                                                == 
                                                (0x1fU 
                                                 & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                    >> 0x10U)))));
    co_await vlSelf->__VdlySched.delay(0x3e8U, "hazard.v", 84);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__lwstallD__0 
        = __Vintraval_ha53d58cb__0;
}

VL_INLINE_OPT void Vmips___024root___nba_comb__TOP__3(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_comb__TOP__3\n"); );
    // Body
    vlSelf->mips__DOT__dp__DOT__pcnextFD = ((8U & (IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls))
                                             ? ((0xf0000000U 
                                                 & vlSelf->mips__DOT__dp__DOT__pcplus4D) 
                                                | (0xffffffcU 
                                                   & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                      << 2U)))
                                             : ((((IData)(vlSelf->mips__DOT__c__DOT__md__DOT__controls) 
                                                  >> 6U) 
                                                 & ((((0U 
                                                       != 
                                                       (0x1fU 
                                                        & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                           >> 0x15U))) 
                                                      & (((0x1fU 
                                                           & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                              >> 0x15U)) 
                                                          == (IData)(vlSelf->mips__DOT__dp__DOT__writeregM)) 
                                                         & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4)))
                                                      ? vlSelf->aluoutM
                                                      : vlSelf->mips__DOT__dp__DOT__srcaD) 
                                                    == 
                                                    (((0U 
                                                       != 
                                                       (0x1fU 
                                                        & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                           >> 0x10U))) 
                                                      & (((0x1fU 
                                                           & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                              >> 0x10U)) 
                                                          == (IData)(vlSelf->mips__DOT__dp__DOT__writeregM)) 
                                                         & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4)))
                                                      ? vlSelf->aluoutM
                                                      : vlSelf->mips__DOT__dp__DOT__srcbD)))
                                                 ? 
                                                (vlSelf->mips__DOT__dp__DOT__pcplus4D 
                                                 + 
                                                 (vlSelf->mips__DOT__dp__DOT__signimmD 
                                                  << 2U))
                                                 : 
                                                ((IData)(4U) 
                                                 + vlSelf->pcF)));
}

VL_INLINE_OPT void Vmips___024root___nba_comb__TOP__4(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___nba_comb__TOP__4\n"); );
    // Body
    vlSelf->mips__DOT__dp__DOT__h__DOT__lwstallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__lwstallD__0;
    vlSelf->mips__DOT__dp__DOT__h__DOT__branchstallD 
        = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__branchstallD__0;
    Vmips___024root____Vfork_h6d8ad74a__0__0(vlSelf, vlSelf->__Vintraval_hf050e82d__0);
    vlSelf->mips__DOT__dp__DOT__stallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallD__0;
    Vmips___024root____Vfork_h2576075f__0__0(vlSelf, vlSelf->__Vintraval_hfd3834eb__0);
    Vmips___024root____Vfork_h1620e13b__0__0(vlSelf, vlSelf->__Vintraval_h855142b1__0);
    vlSelf->mips__DOT__dp__DOT__stallF = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallF__0;
    vlSelf->mips__DOT__flushE = vlSelf->__VassignWtmp_mips__DOT__flushE__0;
}

void Vmips___024root___eval_nba(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vmips___024root___nba_sequent__TOP__0(vlSelf);
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        Vmips___024root___nba_sequent__TOP__1(vlSelf);
    }
    if (vlSelf->__VnbaTriggered.at(3U)) {
        Vmips___024root___nba_sequent__TOP__2(vlSelf);
    }
    if (vlSelf->__VnbaTriggered.at(2U)) {
        Vmips___024root___nba_sequent__TOP__3(vlSelf);
    }
    if (vlSelf->__VnbaTriggered.at(4U)) {
        Vmips___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((vlSelf->__VnbaTriggered.at(2U) | vlSelf->__VnbaTriggered.at(5U))) {
        Vmips___024root___nba_comb__TOP__0(vlSelf);
    }
    if (vlSelf->__VnbaTriggered.at(2U)) {
        Vmips___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((vlSelf->__VnbaTriggered.at(3U) | vlSelf->__VnbaTriggered.at(4U))) {
        Vmips___024root___nba_comb__TOP__1(vlSelf);
    }
    if ((vlSelf->__VnbaTriggered.at(2U) | vlSelf->__VnbaTriggered.at(4U))) {
        Vmips___024root___nba_comb__TOP__2(vlSelf);
    }
    if (((vlSelf->__VnbaTriggered.at(2U) | vlSelf->__VnbaTriggered.at(3U)) 
         | vlSelf->__VnbaTriggered.at(4U))) {
        Vmips___024root___nba_comb__TOP__3(vlSelf);
    }
    if (((vlSelf->__VnbaTriggered.at(2U) | vlSelf->__VnbaTriggered.at(4U)) 
         | vlSelf->__VnbaTriggered.at(5U))) {
        Vmips___024root___nba_comb__TOP__4(vlSelf);
    }
}

void Vmips___024root___eval_triggers__ico(Vmips___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__ico(Vmips___024root* vlSelf);
#endif  // VL_DEBUG
void Vmips___024root___eval_triggers__act(Vmips___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__act(Vmips___024root* vlSelf);
#endif  // VL_DEBUG
void Vmips___024root___timing_resume(Vmips___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__nba(Vmips___024root* vlSelf);
#endif  // VL_DEBUG

void Vmips___024root___eval(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<6> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vmips___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if ((0x64U < vlSelf->__VicoIterCount)) {
#ifdef VL_DEBUG
                Vmips___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("ExtUnit.v", 8, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vmips___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vmips___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if ((0x64U < vlSelf->__VactIterCount)) {
#ifdef VL_DEBUG
                    Vmips___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("ExtUnit.v", 8, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vmips___024root___timing_resume(vlSelf);
                Vmips___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if ((0x64U < __VnbaIterCount)) {
#ifdef VL_DEBUG
                Vmips___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("ExtUnit.v", 8, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vmips___024root___eval_nba(vlSelf);
        }
    }
}

void Vmips___024root___timing_resume(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___timing_resume\n"); );
    // Body
    if (vlSelf->__VactTriggered.at(5U)) {
        vlSelf->__VdlySched.resume();
    }
}

#ifdef VL_DEBUG
void Vmips___024root___eval_debug_assertions(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->ext_type_i & 0xfcU))) {
        Verilated::overWidthError("ext_type_i");}
    if (VL_UNLIKELY((vlSelf->CP0_Reg__02Eclk & 0xfeU))) {
        Verilated::overWidthError("CP0_Reg.clk");}
    if (VL_UNLIKELY((vlSelf->CP0_Reg__02Erst & 0xfeU))) {
        Verilated::overWidthError("CP0_Reg.rst");}
    if (VL_UNLIKELY((vlSelf->we & 0xfeU))) {
        Verilated::overWidthError("we");}
    if (VL_UNLIKELY((vlSelf->addr & 0xe0U))) {
        Verilated::overWidthError("addr");}
    if (VL_UNLIKELY((vlSelf->eret & 0xfeU))) {
        Verilated::overWidthError("eret");}
    if (VL_UNLIKELY((vlSelf->cause_i & 0xc0U))) {
        Verilated::overWidthError("cause_i");}
    if (VL_UNLIKELY((vlSelf->syscall_i & 0xfeU))) {
        Verilated::overWidthError("syscall_i");}
    if (VL_UNLIKELY((vlSelf->break_i & 0xfeU))) {
        Verilated::overWidthError("break_i");}
    if (VL_UNLIKELY((vlSelf->DM__02Eclk & 0xfeU))) {
        Verilated::overWidthError("DM.clk");}
    if (VL_UNLIKELY((vlSelf->DM__02Erst & 0xfeU))) {
        Verilated::overWidthError("DM.rst");}
    if (VL_UNLIKELY((vlSelf->we_i & 0xfeU))) {
        Verilated::overWidthError("we_i");}
    if (VL_UNLIKELY((vlSelf->mem_op_i & 0xf8U))) {
        Verilated::overWidthError("mem_op_i");}
    if (VL_UNLIKELY((vlSelf->mips__02Eclk & 0xfeU))) {
        Verilated::overWidthError("mips.clk");}
    if (VL_UNLIKELY((vlSelf->mips__02Erst & 0xfeU))) {
        Verilated::overWidthError("mips.rst");}
}
#endif  // VL_DEBUG
