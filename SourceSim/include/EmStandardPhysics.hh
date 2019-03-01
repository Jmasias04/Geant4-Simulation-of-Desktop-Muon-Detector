// ********************************************
// ***************** HEP-PUCP *****************
// ******************************************** 

#ifndef EmStandardPhysics_h
#define EmStandardPhysics_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"


class EmStandardPhysics : public G4VPhysicsConstructor
{
  public: 
    EmStandardPhysics(const G4String& name = "standard");
   ~EmStandardPhysics();

  public: 
    // This method is dummy for physics
    virtual void ConstructParticle() {};
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    virtual void ConstructProcess();
};

#endif
