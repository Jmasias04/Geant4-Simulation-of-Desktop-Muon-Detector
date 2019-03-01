// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include <iostream>
#include <fstream>
#include "PhotonDistStackingAction.hh"
#include "PhotonDistHistoManager.hh"
#include "G4VProcess.hh"
#include "G4SteppingManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "PhotonDistSteppingVerbose.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4INCLThreeVector.hh"
#include <stdio.h>
#include <math.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistStackingAction::PhotonDistStackingAction()
  : G4UserStackingAction(),
    fDetectorCounter(0), momentum(0), k(1), i(1)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistStackingAction::~PhotonDistStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
PhotonDistStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

std::ofstream logging;
const G4String name = "Detector";

//get primary particle energy
G4int eventNumber = aTrack->GetTrackID (); 
G4double pmom;
if(eventNumber == 1){
pmom  =aTrack->GetKineticEnergy();
if(pmom > momentum){
momentum=pmom;
}
}


  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0) //Parent is Primary Particle
    { // particle is secondary
      G4VPhysicalVolume* volume = aTrack->GetVolume(); //Volumen that generates photon
      if(volume->GetName()== "Detector")
      { // particles originates in Detector
        if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")//scintillation events
        {
	  fDetectorCounter++;
 	}
        if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")//cerenkov events
        { 
	 fDetectorCounter++;
	}
      }
    }  
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonDistStackingAction::NewStage()// Print results
{

std::ofstream logging;
logging.open("ga_10M_energy_momentum.txt", std::ios::app);

logging << fDetectorCounter;
logging << "		";
logging << momentum;

logging << "	\n";

  logging.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonDistStackingAction::PrepareNewEvent()
{
fDetectorCounter=0;
momentum=0;
k++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
