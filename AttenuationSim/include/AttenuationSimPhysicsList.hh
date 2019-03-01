// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef AttenuationSimPhysicsList_h
#define AttenuationSimPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"


class AttenuationSimPhysicsList: public G4VModularPhysicsList
{
public:
  AttenuationSimPhysicsList();
 ~AttenuationSimPhysicsList();

public:
  virtual void ConstructParticle();
  virtual void SetCuts();
};

#endif
