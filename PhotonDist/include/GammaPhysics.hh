// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef GammaPhysics_h
#define GammaPhysics_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"


class GammaPhysics : public G4VPhysicsConstructor
{
  public:
    GammaPhysics(const G4String& name="gamma");
   ~GammaPhysics();

  public:
    virtual void ConstructParticle() { };
    virtual void ConstructProcess();
};

#endif

