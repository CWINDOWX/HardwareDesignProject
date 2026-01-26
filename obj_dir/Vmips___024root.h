// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vmips.h for the primary calling header

#ifndef VERILATED_VMIPS___024ROOT_H_
#define VERILATED_VMIPS___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"

class Vmips__Syms;

class Vmips___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(CP0_Reg__02Eclk,0,0);
        VL_IN8(CP0_Reg__02Erst,0,0);
        VL_IN8(DM__02Eclk,0,0);
        VL_IN8(mips__02Eclk,0,0);
        VL_IN8(mips__02Erst,0,0);
        VL_IN8(ext_type_i,1,0);
        VL_IN8(we,0,0);
        VL_IN8(addr,4,0);
        VL_IN8(eret,0,0);
        VL_IN8(cause_i,5,0);
        VL_IN8(syscall_i,0,0);
        VL_IN8(break_i,0,0);
        VL_OUT8(cause_o,5,0);
        VL_OUT8(exception_o,0,0);
        VL_IN8(DM__02Erst,0,0);
        VL_IN8(we_i,0,0);
        VL_IN8(mem_op_i,2,0);
        VL_OUT8(memwriteM,0,0);
        CData/*3:0*/ DM__DOT__byte_we;
        CData/*7:0*/ DM__DOT__byte_sel;
        CData/*0:0*/ mips__DOT__flushE;
        CData/*2:0*/ mips__DOT__c__DOT__alucontrolD;
        CData/*0:0*/ mips__DOT__c__DOT__hassign_ad;
        CData/*1:0*/ mips__DOT__c__DOT__hilo_enD;
        CData/*1:0*/ mips__DOT__c__DOT__hilo_mfD;
        CData/*7:0*/ mips__DOT__c__DOT____Vcellout__regM____pinNumber4;
        CData/*7:0*/ mips__DOT__c__DOT____Vcellout__regW____pinNumber4;
        CData/*0:0*/ mips__DOT__dp__DOT__stallF;
        CData/*0:0*/ mips__DOT__dp__DOT__flushD;
        CData/*0:0*/ mips__DOT__dp__DOT__stallD;
        CData/*1:0*/ mips__DOT__dp__DOT__forwardaE;
        CData/*1:0*/ mips__DOT__dp__DOT__forwardbE;
        CData/*4:0*/ mips__DOT__dp__DOT__rsE;
        CData/*4:0*/ mips__DOT__dp__DOT__rtE;
        CData/*4:0*/ mips__DOT__dp__DOT__rdE;
        CData/*4:0*/ mips__DOT__dp__DOT__writeregE;
        CData/*4:0*/ mips__DOT__dp__DOT__writeregM;
        CData/*4:0*/ mips__DOT__dp__DOT__writeregW;
        CData/*0:0*/ mips__DOT__dp__DOT__h__DOT__lwstallD;
        CData/*0:0*/ mips__DOT__dp__DOT__h__DOT__branchstallD;
        CData/*0:0*/ mips__DOT__dp__DOT__h__DOT__divstallD;
        CData/*5:0*/ __Vtableidx1;
        CData/*7:0*/ __Vtableidx2;
        CData/*0:0*/ __VassignWtmp_mips__DOT__dp__DOT__h__DOT__lwstallD__0;
        CData/*0:0*/ __Vintraval_ha53d58cb__0;
        CData/*0:0*/ __VassignWtmp_mips__DOT__dp__DOT__h__DOT__branchstallD__0;
        CData/*0:0*/ __Vintraval_h416f4670__0;
        CData/*0:0*/ __VassignWtmp_mips__DOT__dp__DOT__h__DOT__divstallD__0;
        CData/*0:0*/ __Vintraval_ha3f6fe5a__0;
        CData/*0:0*/ __VassignWtmp_mips__DOT__dp__DOT__stallD__0;
        CData/*0:0*/ __Vintraval_hf050e82d__0;
        CData/*0:0*/ __VassignWtmp_mips__DOT__dp__DOT__stallF__0;
        CData/*0:0*/ __Vintraval_hfd3834eb__0;
        CData/*0:0*/ __VassignWtmp_mips__DOT__flushE__0;
        CData/*0:0*/ __Vintraval_h855142b1__0;
        CData/*0:0*/ __Vtrigrprev__TOP__CP0_Reg__02Eclk;
        CData/*0:0*/ __Vtrigrprev__TOP__CP0_Reg__02Erst;
        CData/*0:0*/ __Vtrigrprev__TOP__DM__02Eclk;
        CData/*0:0*/ __Vtrigrprev__TOP__mips__02Eclk;
        CData/*0:0*/ __Vtrigrprev__TOP__mips__02Erst;
        CData/*0:0*/ __VactContinue;
        VL_IN16(imm,15,0);
        SData/*15:0*/ DM__DOT__halfword_sel;
        SData/*13:0*/ mips__DOT__c__DOT____Vcellout__regE____pinNumber5;
    };
    struct {
        SData/*9:0*/ mips__DOT__c__DOT__md__DOT__controls;
        VL_OUT(ext_result,31,0);
        VL_IN(wdata,31,0);
        VL_OUT(rdata,31,0);
        VL_IN(epc_i,31,0);
        VL_OUT(epc_o,31,0);
        VL_IN(addr_i,31,0);
        VL_IN(wdata_i,31,0);
        VL_OUT(rdata_o,31,0);
        VL_OUT(pcF,31,0);
        VL_IN(instrF,31,0);
        VL_OUT(aluoutM,31,0);
        VL_OUT(writedataM,31,0);
        VL_IN(readdataM,31,0);
        IData/*31:0*/ CP0_Reg__DOT__epc_reg;
        IData/*31:0*/ CP0_Reg__DOT__cause_reg;
        IData/*31:0*/ CP0_Reg__DOT__status_reg;
        IData/*31:0*/ CP0_Reg__DOT__count_reg;
        IData/*31:0*/ CP0_Reg__DOT__badvaddr_reg;
        IData/*31:0*/ DM__DOT__wdata_ext;
        IData/*31:0*/ DM__DOT__rdata_raw;
        IData/*31:0*/ mips__DOT__dp__DOT__pcnextFD;
        IData/*31:0*/ mips__DOT__dp__DOT__pcplus4D;
        IData/*31:0*/ mips__DOT__dp__DOT__instrD;
        IData/*31:0*/ mips__DOT__dp__DOT__signimmD;
        IData/*31:0*/ mips__DOT__dp__DOT__srcaD;
        IData/*31:0*/ mips__DOT__dp__DOT__srcbD;
        IData/*31:0*/ mips__DOT__dp__DOT__signimmE;
        IData/*31:0*/ mips__DOT__dp__DOT__srcaE;
        IData/*31:0*/ mips__DOT__dp__DOT__srca2E;
        IData/*31:0*/ mips__DOT__dp__DOT__srcbE;
        IData/*31:0*/ mips__DOT__dp__DOT__srcb2E;
        IData/*31:0*/ mips__DOT__dp__DOT__srcb3E;
        IData/*31:0*/ mips__DOT__dp__DOT__aluresult_loE;
        IData/*31:0*/ mips__DOT__dp__DOT__aluresultE;
        IData/*31:0*/ mips__DOT__dp__DOT__hi_outE;
        IData/*31:0*/ mips__DOT__dp__DOT__lo_outE;
        IData/*31:0*/ mips__DOT__dp__DOT__hi_inE;
        IData/*31:0*/ mips__DOT__dp__DOT__lo_inE;
        IData/*31:0*/ mips__DOT__dp__DOT__aluoutW;
        IData/*31:0*/ mips__DOT__dp__DOT__readdataW;
        IData/*31:0*/ mips__DOT__dp__DOT__resultW;
        IData/*31:0*/ mips__DOT__dp__DOT__alu__DOT__s;
        IData/*31:0*/ mips__DOT__dp__DOT__alu__DOT__bout;
        IData/*31:0*/ __VstlIterCount;
        IData/*31:0*/ __VicoIterCount;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<IData/*31:0*/, 4096> DM__DOT__data_mem;
        VlUnpacked<IData/*31:0*/, 32> mips__DOT__dp__DOT__rf__DOT__rf;
    };
    VlDelayScheduler __VdlySched;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<6> __VactTriggered;
    VlTriggerVec<6> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vmips__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vmips___024root(Vmips__Syms* symsp, const char* name);
    ~Vmips___024root();
    VL_UNCOPYABLE(Vmips___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
