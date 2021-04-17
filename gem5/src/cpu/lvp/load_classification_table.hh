/*
 * Robert Viramontes
 * Created March 25, 2021
 * Based on the 2bit_local branch predictor provided with the gem5 source. 
 * 
 * 
 */

#ifndef __CPU_LVP_LOADCLASSIFICATIONTABLE_HH__
#define __CPU_LVP_LOADCLASSIFICATIONTABLE_HH__

#include <vector>

#include "base/sat_counter.hh"
#include "base/types.hh"
#include "cpu/static_inst.hh"
#include "sim/sim_object.hh"

#include "enums.hh"
#include "params/LoadClassificationTable.hh"

/**
 * Implements a local predictor that uses the PC to index into a table of
 * counters.  Note that any time a pointer to the bp_history is given, it
 * should be NULL using this predictor because it does not have any branch
 * predictor state that needs to be recorded or updated; the update can be
 * determined solely by the branch being taken or not taken.
 */
class LoadClassificationTable : public SimObject
{
  public:
    /**
     * Build load classfication table.
     */
    LoadClassificationTable(const LoadClassificationTableParams *params);

    /**
     * Looks up the given instruction address in the LCT and returns
     * a LctResult that indicates unpredictable, predictable, or constant.
     * @param inst_addr The address of the instruction to look up.
     * @param bp_history Pointer to any bp history state.
     * @return Whether or not the branch is taken.
     */
    LVPType lookup(ThreadID tid, Addr inst_addr);

    /**
     * Updates the branch predictor with the actual result of a branch.
     * @param inst_addr The address of the instruction to update.
     * @param taken Whether or not the branch was taken.
     * @return Updated LVPType of the location
     */
    LVPType update(ThreadID tid, Addr inst_addr, LVPType prediction, bool prediction_correct);

    // void squash(ThreadID tid, void *bp_history)
    // { assert(bp_history == NULL); }

    /**
     * @brief Resets all saturating counters in LCT.
     */
    void reset();

  private:
    /**
     *  Returns the unpredictable/predictable/constant prediction given 
     *  the value of the counter.
     *  @param count The value of the counter.
     *  @return The prediction based on the counter value.
     */
    inline LVPType getPrediction(uint8_t &count);

    /** Calculates the local index based on the PC. */
    inline unsigned getLocalIndex(Addr &PC);

    /** Size of the local predictor. */
    const unsigned localPredictorSize;

    /** Number of bits of the local predictor's counters. */
    const unsigned localCtrBits;

    /** Number of sets. */
    const unsigned localPredictorSets;

    /** Array of counters that make up the local predictor. */
    std::vector<SatCounter> localCtrs;

    /** Mask to get index bits. */
    const unsigned indexMask;

    /** Number of bits to shift instructions by for predictor addresses. */
    const unsigned instShiftAmt;

    const bool invalidateConstToZero;
};

#endif // __CPU_LVP_LOADCLASSIFICATIONTABLE_HH__
