// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmips.h for the primary calling header

#include "verilated.h"

#include "Vmips___024root.h"

VL_ATTR_COLD void Vmips___024root___eval_static(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vmips___024root___eval_initial__TOP(Vmips___024root* vlSelf);

VL_ATTR_COLD void Vmips___024root___eval_initial(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_initial\n"); );
    // Body
    Vmips___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Eclk = vlSelf->CP0_Reg__02Eclk;
    vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Erst = vlSelf->CP0_Reg__02Erst;
    vlSelf->__Vtrigrprev__TOP__DM__02Eclk = vlSelf->DM__02Eclk;
    vlSelf->__Vtrigrprev__TOP__mips__02Eclk = vlSelf->mips__02Eclk;
    vlSelf->__Vtrigrprev__TOP__mips__02Erst = vlSelf->mips__02Erst;
}

VL_ATTR_COLD void Vmips___024root___eval_initial__TOP(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_initial__TOP\n"); );
    // Init
    IData/*31:0*/ DM__DOT__j;
    // Body
    DM__DOT__j = 0U;
    while (VL_GTS_III(32, 0x1000U, DM__DOT__j)) {
        vlSelf->DM__DOT__data_mem[(0xfffU & DM__DOT__j)] = 0U;
        DM__DOT__j = ((IData)(1U) + DM__DOT__j);
    }
}

VL_ATTR_COLD void Vmips___024root___eval_final(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vmips___024root___eval_triggers__stl(Vmips___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__stl(Vmips___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vmips___024root___eval_stl(Vmips___024root* vlSelf);

VL_ATTR_COLD void Vmips___024root___eval_settle(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        Vmips___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if ((0x64U < vlSelf->__VstlIterCount)) {
#ifdef VL_DEBUG
                Vmips___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("ExtUnit.v", 8, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            Vmips___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__stl(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VlCoroutine Vmips___024root____Vfork_hbe974bec__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_ha3f6fe5a__0);
VlCoroutine Vmips___024root____Vfork_hf3256427__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_ha53d58cb__0);
extern const VlUnpacked<SData/*9:0*/, 64> Vmips__ConstPool__TABLE_h8b5122f1_0;
extern const VlUnpacked<CData/*0:0*/, 256> Vmips__ConstPool__TABLE_h2aff9509_0;
extern const VlUnpacked<CData/*1:0*/, 256> Vmips__ConstPool__TABLE_h8d474863_0;
extern const VlUnpacked<CData/*1:0*/, 256> Vmips__ConstPool__TABLE_h318e41b4_0;
extern const VlUnpacked<CData/*2:0*/, 256> Vmips__ConstPool__TABLE_hf91ec95b_0;
VlCoroutine Vmips___024root____Vfork_hda8f6c3d__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_h416f4670__0);
VlCoroutine Vmips___024root____Vfork_h6d8ad74a__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_hf050e82d__0);
VlCoroutine Vmips___024root____Vfork_h2576075f__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_hfd3834eb__0);
VlCoroutine Vmips___024root____Vfork_h1620e13b__0__0(Vmips___024root* vlSelf, CData/*0:0*/ __Vintraval_h855142b1__0);

VL_ATTR_COLD void Vmips___024root___stl_sequent__TOP__0(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->epc_o = vlSelf->CP0_Reg__DOT__epc_reg;
    vlSelf->cause_o = (0x3fU & vlSelf->CP0_Reg__DOT__cause_reg);
    vlSelf->memwriteM = (1U & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4) 
                               >> 1U));
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
    vlSelf->mips__DOT__dp__DOT__signimmD = (((- (IData)(
                                                        (1U 
                                                         & (vlSelf->mips__DOT__dp__DOT__instrD 
                                                            >> 0xfU)))) 
                                             << 0x10U) 
                                            | (0xffffU 
                                               & vlSelf->mips__DOT__dp__DOT__instrD));
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
    vlSelf->DM__DOT__rdata_raw = vlSelf->DM__DOT__data_mem
        [(0xfffU & (vlSelf->addr_i >> 2U))];
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
    Vmips___024root____Vfork_hbe974bec__0__0(vlSelf, vlSelf->__Vintraval_ha3f6fe5a__0);
    Vmips___024root____Vfork_hf3256427__0__0(vlSelf, vlSelf->__Vintraval_ha53d58cb__0);
    vlSelf->mips__DOT__dp__DOT__writeregE = ((0x400U 
                                              & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                              ? (IData)(vlSelf->mips__DOT__dp__DOT__rdE)
                                              : (IData)(vlSelf->mips__DOT__dp__DOT__rtE));
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
    vlSelf->__Vtableidx1 = (vlSelf->mips__DOT__dp__DOT__instrD 
                            >> 0x1aU);
    vlSelf->mips__DOT__c__DOT__md__DOT__controls = 
        Vmips__ConstPool__TABLE_h8b5122f1_0[vlSelf->__Vtableidx1];
    vlSelf->mips__DOT__dp__DOT__resultW = ((2U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4))
                                            ? vlSelf->mips__DOT__dp__DOT__readdataW
                                            : vlSelf->mips__DOT__dp__DOT__aluoutW);
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
    vlSelf->mips__DOT__dp__DOT__h__DOT__divstallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__divstallD__0;
    vlSelf->mips__DOT__dp__DOT__h__DOT__lwstallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__lwstallD__0;
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
    Vmips___024root____Vfork_hda8f6c3d__0__0(vlSelf, vlSelf->__Vintraval_h416f4670__0);
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
    vlSelf->mips__DOT__dp__DOT__h__DOT__branchstallD 
        = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__branchstallD__0;
    vlSelf->mips__DOT__dp__DOT__srcb3E = ((0x800U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                           ? vlSelf->mips__DOT__dp__DOT__signimmE
                                           : vlSelf->mips__DOT__dp__DOT__srcb2E);
    Vmips___024root____Vfork_h6d8ad74a__0__0(vlSelf, vlSelf->__Vintraval_hf050e82d__0);
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
    vlSelf->mips__DOT__dp__DOT__stallD = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallD__0;
    vlSelf->mips__DOT__dp__DOT__alu__DOT__s = (vlSelf->mips__DOT__dp__DOT__srca2E 
                                               + (vlSelf->mips__DOT__dp__DOT__alu__DOT__bout 
                                                  + 
                                                  (1U 
                                                   & ((IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5) 
                                                      >> 8U))));
    vlSelf->mips__DOT__dp__DOT__lo_inE = ((0x10U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                           ? vlSelf->mips__DOT__dp__DOT__aluresult_loE
                                           : vlSelf->mips__DOT__dp__DOT__srca2E);
    Vmips___024root____Vfork_h2576075f__0__0(vlSelf, vlSelf->__Vintraval_hfd3834eb__0);
    Vmips___024root____Vfork_h1620e13b__0__0(vlSelf, vlSelf->__Vintraval_h855142b1__0);
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
    vlSelf->mips__DOT__dp__DOT__hi_inE = ((0x10U & (IData)(vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5))
                                           ? vlSelf->mips__DOT__dp__DOT__aluresultE
                                           : vlSelf->mips__DOT__dp__DOT__srca2E);
    vlSelf->mips__DOT__dp__DOT__stallF = vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallF__0;
    vlSelf->mips__DOT__flushE = vlSelf->__VassignWtmp_mips__DOT__flushE__0;
}

VL_ATTR_COLD void Vmips___024root___eval_stl(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        Vmips___024root___stl_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__ico(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__act(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge CP0_Reg.clk or posedge CP0_Reg.rst)\n");
    }
    if (vlSelf->__VactTriggered.at(1U)) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge DM.clk)\n");
    }
    if (vlSelf->__VactTriggered.at(2U)) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @(posedge mips.clk or posedge mips.rst)\n");
    }
    if (vlSelf->__VactTriggered.at(3U)) {
        VL_DBG_MSGF("         'act' region trigger index 3 is active: @(negedge mips.clk)\n");
    }
    if (vlSelf->__VactTriggered.at(4U)) {
        VL_DBG_MSGF("         'act' region trigger index 4 is active: @(posedge mips.clk)\n");
    }
    if (vlSelf->__VactTriggered.at(5U)) {
        VL_DBG_MSGF("         'act' region trigger index 5 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vmips___024root___dump_triggers__nba(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge CP0_Reg.clk or posedge CP0_Reg.rst)\n");
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge DM.clk)\n");
    }
    if (vlSelf->__VnbaTriggered.at(2U)) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @(posedge mips.clk or posedge mips.rst)\n");
    }
    if (vlSelf->__VnbaTriggered.at(3U)) {
        VL_DBG_MSGF("         'nba' region trigger index 3 is active: @(negedge mips.clk)\n");
    }
    if (vlSelf->__VnbaTriggered.at(4U)) {
        VL_DBG_MSGF("         'nba' region trigger index 4 is active: @(posedge mips.clk)\n");
    }
    if (vlSelf->__VnbaTriggered.at(5U)) {
        VL_DBG_MSGF("         'nba' region trigger index 5 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vmips___024root___ctor_var_reset(Vmips___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmips__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmips___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->imm = VL_RAND_RESET_I(16);
    vlSelf->ext_type_i = VL_RAND_RESET_I(2);
    vlSelf->ext_result = VL_RAND_RESET_I(32);
    vlSelf->CP0_Reg__02Eclk = VL_RAND_RESET_I(1);
    vlSelf->CP0_Reg__02Erst = VL_RAND_RESET_I(1);
    vlSelf->we = VL_RAND_RESET_I(1);
    vlSelf->addr = VL_RAND_RESET_I(5);
    vlSelf->wdata = VL_RAND_RESET_I(32);
    vlSelf->rdata = VL_RAND_RESET_I(32);
    vlSelf->eret = VL_RAND_RESET_I(1);
    vlSelf->epc_i = VL_RAND_RESET_I(32);
    vlSelf->cause_i = VL_RAND_RESET_I(6);
    vlSelf->syscall_i = VL_RAND_RESET_I(1);
    vlSelf->break_i = VL_RAND_RESET_I(1);
    vlSelf->epc_o = VL_RAND_RESET_I(32);
    vlSelf->cause_o = VL_RAND_RESET_I(6);
    vlSelf->exception_o = VL_RAND_RESET_I(1);
    vlSelf->DM__02Eclk = VL_RAND_RESET_I(1);
    vlSelf->DM__02Erst = VL_RAND_RESET_I(1);
    vlSelf->addr_i = VL_RAND_RESET_I(32);
    vlSelf->wdata_i = VL_RAND_RESET_I(32);
    vlSelf->we_i = VL_RAND_RESET_I(1);
    vlSelf->mem_op_i = VL_RAND_RESET_I(3);
    vlSelf->rdata_o = VL_RAND_RESET_I(32);
    vlSelf->mips__02Eclk = VL_RAND_RESET_I(1);
    vlSelf->mips__02Erst = VL_RAND_RESET_I(1);
    vlSelf->pcF = VL_RAND_RESET_I(32);
    vlSelf->instrF = VL_RAND_RESET_I(32);
    vlSelf->memwriteM = VL_RAND_RESET_I(1);
    vlSelf->aluoutM = VL_RAND_RESET_I(32);
    vlSelf->writedataM = VL_RAND_RESET_I(32);
    vlSelf->readdataM = VL_RAND_RESET_I(32);
    vlSelf->CP0_Reg__DOT__epc_reg = VL_RAND_RESET_I(32);
    vlSelf->CP0_Reg__DOT__cause_reg = VL_RAND_RESET_I(32);
    vlSelf->CP0_Reg__DOT__status_reg = VL_RAND_RESET_I(32);
    vlSelf->CP0_Reg__DOT__count_reg = VL_RAND_RESET_I(32);
    vlSelf->CP0_Reg__DOT__badvaddr_reg = VL_RAND_RESET_I(32);
    vlSelf->DM__DOT__byte_we = VL_RAND_RESET_I(4);
    vlSelf->DM__DOT__wdata_ext = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 4096; ++__Vi0) {
        vlSelf->DM__DOT__data_mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->DM__DOT__rdata_raw = VL_RAND_RESET_I(32);
    vlSelf->DM__DOT__byte_sel = VL_RAND_RESET_I(8);
    vlSelf->DM__DOT__halfword_sel = VL_RAND_RESET_I(16);
    vlSelf->mips__DOT__flushE = VL_RAND_RESET_I(1);
    vlSelf->mips__DOT__c__DOT__alucontrolD = VL_RAND_RESET_I(3);
    vlSelf->mips__DOT__c__DOT__hassign_ad = VL_RAND_RESET_I(1);
    vlSelf->mips__DOT__c__DOT__hilo_enD = VL_RAND_RESET_I(2);
    vlSelf->mips__DOT__c__DOT__hilo_mfD = VL_RAND_RESET_I(2);
    vlSelf->mips__DOT__c__DOT____Vcellout__regE____pinNumber5 = VL_RAND_RESET_I(14);
    vlSelf->mips__DOT__c__DOT____Vcellout__regM____pinNumber4 = VL_RAND_RESET_I(8);
    vlSelf->mips__DOT__c__DOT____Vcellout__regW____pinNumber4 = VL_RAND_RESET_I(8);
    vlSelf->mips__DOT__c__DOT__md__DOT__controls = VL_RAND_RESET_I(10);
    vlSelf->mips__DOT__dp__DOT__stallF = VL_RAND_RESET_I(1);
    vlSelf->mips__DOT__dp__DOT__pcnextFD = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__pcplus4D = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__instrD = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__flushD = VL_RAND_RESET_I(1);
    vlSelf->mips__DOT__dp__DOT__stallD = VL_RAND_RESET_I(1);
    vlSelf->mips__DOT__dp__DOT__signimmD = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__srcaD = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__srcbD = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__forwardaE = VL_RAND_RESET_I(2);
    vlSelf->mips__DOT__dp__DOT__forwardbE = VL_RAND_RESET_I(2);
    vlSelf->mips__DOT__dp__DOT__rsE = VL_RAND_RESET_I(5);
    vlSelf->mips__DOT__dp__DOT__rtE = VL_RAND_RESET_I(5);
    vlSelf->mips__DOT__dp__DOT__rdE = VL_RAND_RESET_I(5);
    vlSelf->mips__DOT__dp__DOT__writeregE = VL_RAND_RESET_I(5);
    vlSelf->mips__DOT__dp__DOT__signimmE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__srcaE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__srca2E = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__srcbE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__srcb2E = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__srcb3E = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__aluresult_loE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__aluresultE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__hi_outE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__lo_outE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__hi_inE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__lo_inE = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__writeregM = VL_RAND_RESET_I(5);
    vlSelf->mips__DOT__dp__DOT__writeregW = VL_RAND_RESET_I(5);
    vlSelf->mips__DOT__dp__DOT__aluoutW = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__readdataW = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__resultW = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__h__DOT__lwstallD = VL_RAND_RESET_I(1);
    vlSelf->mips__DOT__dp__DOT__h__DOT__branchstallD = VL_RAND_RESET_I(1);
    vlSelf->mips__DOT__dp__DOT__h__DOT__divstallD = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->mips__DOT__dp__DOT__rf__DOT__rf[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->mips__DOT__dp__DOT__alu__DOT__s = VL_RAND_RESET_I(32);
    vlSelf->mips__DOT__dp__DOT__alu__DOT__bout = VL_RAND_RESET_I(32);
    vlSelf->__Vtableidx1 = 0;
    vlSelf->__Vtableidx2 = 0;
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__lwstallD__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_ha53d58cb__0 = VL_RAND_RESET_I(1);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__branchstallD__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_h416f4670__0 = VL_RAND_RESET_I(1);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__h__DOT__divstallD__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_ha3f6fe5a__0 = VL_RAND_RESET_I(1);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallD__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_hf050e82d__0 = VL_RAND_RESET_I(1);
    vlSelf->__VassignWtmp_mips__DOT__dp__DOT__stallF__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_hfd3834eb__0 = VL_RAND_RESET_I(1);
    vlSelf->__VassignWtmp_mips__DOT__flushE__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vintraval_h855142b1__0 = VL_RAND_RESET_I(1);
    vlSelf->__VstlIterCount = 0;
    vlSelf->__VicoIterCount = 0;
    vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Eclk = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigrprev__TOP__CP0_Reg__02Erst = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigrprev__TOP__DM__02Eclk = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigrprev__TOP__mips__02Eclk = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigrprev__TOP__mips__02Erst = VL_RAND_RESET_I(1);
    vlSelf->__VactIterCount = 0;
    vlSelf->__VactContinue = 0;
}
