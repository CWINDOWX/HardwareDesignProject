// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VMIPS_H_
#define VERILATED_VMIPS_H_  // guard

#include "verilated.h"

class Vmips__Syms;
class Vmips___024root;

// This class is the main interface to the Verilated model
class Vmips VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vmips__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&CP0_Reg__02Eclk,0,0);
    VL_IN8(&CP0_Reg__02Erst,0,0);
    VL_IN8(&DM__02Eclk,0,0);
    VL_IN8(&mips__02Eclk,0,0);
    VL_IN8(&mips__02Erst,0,0);
    VL_IN8(&ext_type_i,1,0);
    VL_IN8(&we,0,0);
    VL_IN8(&addr,4,0);
    VL_IN8(&eret,0,0);
    VL_IN8(&cause_i,5,0);
    VL_IN8(&syscall_i,0,0);
    VL_IN8(&break_i,0,0);
    VL_OUT8(&cause_o,5,0);
    VL_OUT8(&exception_o,0,0);
    VL_IN8(&DM__02Erst,0,0);
    VL_IN8(&we_i,0,0);
    VL_IN8(&mem_op_i,2,0);
    VL_OUT8(&memwriteM,0,0);
    VL_IN16(&imm,15,0);
    VL_OUT(&ext_result,31,0);
    VL_IN(&wdata,31,0);
    VL_OUT(&rdata,31,0);
    VL_IN(&epc_i,31,0);
    VL_OUT(&epc_o,31,0);
    VL_IN(&addr_i,31,0);
    VL_IN(&wdata_i,31,0);
    VL_OUT(&rdata_o,31,0);
    VL_OUT(&pcF,31,0);
    VL_IN(&instrF,31,0);
    VL_OUT(&aluoutM,31,0);
    VL_OUT(&writedataM,31,0);
    VL_IN(&readdataM,31,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vmips___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vmips(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vmips(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vmips();
  private:
    VL_UNCOPYABLE(Vmips);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
