// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef AttenuationSimHistoManager_h
#define AttenuationSimHistoManager_h 1

#include "globals.hh"

#include "g4root.hh"
//#include "g4xml.hh"


class AttenuationSimHistoManager
{
  public:
    AttenuationSimHistoManager();
   ~AttenuationSimHistoManager();

  private:
    void Book();
    G4String fFileName;
};

#endif

