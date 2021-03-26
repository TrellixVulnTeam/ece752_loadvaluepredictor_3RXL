/*
 * Robert Viramontes
 * Created March 26, 2021
 * Based on the learning/part2/simpleobject 
 * 
 * 
 */

#ifndef __CPU_LVP_LOADVALUEPREDICTIONUNIT_HH__
#define __CPU_LVP_LOADVALUEPREDICTIONUNIT_HH__

#include <string>

#include "cpu/lvp/load_classification_table.hh"
#include "params/LoadValuePredictionUnit.hh"
#include "sim/sim_object.hh"

class LoadValuePredictionUnit : public SimObject
{
  private:
    /// Pointer to the corresponding GoodbyeObject. Set via Python
    LoadClassificationTable* loadClassificationTable;

  public:
    LoadValuePredictionUnit(LoadValuePredictionUnitParams *p);

    /**
     * Part of a SimObject's initilaization. Startup is called after all
     * SimObjects have been constructed. It is called after the user calls
     * simulate() for the first time.
     */
    void startup();
};

#endif // __CPU_LVP_LOADVALUEPREDICTIONUNIT_HH__
