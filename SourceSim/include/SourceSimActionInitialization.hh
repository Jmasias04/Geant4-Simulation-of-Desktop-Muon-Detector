// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef SourceSimActionInitialization_h
#define SourceSimActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class B4DetectorConstruction;

/// Action initialization class.
///

class SourceSimActionInitialization : public G4VUserActionInitialization
{
  public:
    SourceSimActionInitialization();
    virtual ~SourceSimActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
   virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
};

#endif
