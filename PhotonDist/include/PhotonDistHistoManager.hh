// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistHistoManager_h
#define PhotonDistHistoManager_h 1

#include "globals.hh"

#include "g4root.hh"
//#include "g4xml.hh"


class PhotonDistHistoManager
{
  public:
    PhotonDistHistoManager();
   ~PhotonDistHistoManager();

  private:
    void Book();
    G4String fFileName;
};

#endif

