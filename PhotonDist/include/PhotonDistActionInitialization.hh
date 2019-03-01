// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistActionInitialization_h
#define PhotonDistActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class B4DetectorConstruction;

/// Action initialization class.
///

class PhotonDistActionInitialization : public G4VUserActionInitialization
{
  public:
    PhotonDistActionInitialization();
    virtual ~PhotonDistActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
   virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
};

#endif
