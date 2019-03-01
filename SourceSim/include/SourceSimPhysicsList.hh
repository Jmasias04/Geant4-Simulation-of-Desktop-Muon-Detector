// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef SourceSimPhysicsList_h
#define SourceSimPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"


class SourceSimPhysicsList: public G4VModularPhysicsList
{
public:
  SourceSimPhysicsList();
 ~SourceSimPhysicsList();

public:
  virtual void ConstructParticle();
  virtual void SetCuts();
};

#endif
