// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef AttenuationSimActionInitialization_h
#define AttenuationSimActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class B4DetectorConstruction;

/// Action initialization class.
///

class AttenuationSimActionInitialization : public G4VUserActionInitialization
{
  public:
    AttenuationSimActionInitialization();
    virtual ~AttenuationSimActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
   virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
};

#endif
