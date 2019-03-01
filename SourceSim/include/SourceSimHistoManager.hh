// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef SourceSimHistoManager_h
#define SourceSimHistoManager_h 1

#include "globals.hh"

#include "g4root.hh"
//#include "g4xml.hh"


class SourceSimHistoManager
{
  public:
    SourceSimHistoManager();
   ~SourceSimHistoManager();

  private:
    void Book();
    G4String fFileName;
};

#endif

