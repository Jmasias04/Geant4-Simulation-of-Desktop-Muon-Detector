// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "SourceSimPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"


SourceSimPrimaryGeneratorAction::SourceSimPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
   fParticleGun = new G4GeneralParticleSource();
}

SourceSimPrimaryGeneratorAction::~SourceSimPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void SourceSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
