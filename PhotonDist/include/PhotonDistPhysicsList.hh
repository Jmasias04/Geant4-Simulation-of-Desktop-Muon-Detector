// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistPhysicsList_h
#define PhotonDistPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"


class PhotonDistPhysicsList: public G4VModularPhysicsList
{
public:
  PhotonDistPhysicsList();
 ~PhotonDistPhysicsList();

public:
  virtual void ConstructParticle();
  virtual void SetCuts();
};

#endif
