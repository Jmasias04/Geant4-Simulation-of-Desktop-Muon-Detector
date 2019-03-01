// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef SourceSimPrimaryGeneratorAction_h
#define SourceSimPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

class SourceSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    SourceSimPrimaryGeneratorAction();
   ~SourceSimPrimaryGeneratorAction();

	public:
    virtual void GeneratePrimaries(G4Event*);
		G4GeneralParticleSource* GetParticleGun() {return fParticleGun;};

  private:
    G4GeneralParticleSource* fParticleGun;
};

#endif


