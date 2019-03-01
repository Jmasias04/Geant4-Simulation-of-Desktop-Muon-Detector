// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include <iostream>
#include <fstream>
#include "SourceSimStackingAction.hh"
#include "SourceSimHistoManager.hh"
#include "G4VProcess.hh"
#include "G4SteppingManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "SourceSimSteppingVerbose.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4INCLThreeVector.hh"
#include <stdio.h>
#include <math.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SourceSimStackingAction::SourceSimStackingAction()
  : G4UserStackingAction(),
    fDetectorCounter(0), momentum(0), k(1), i(1)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SourceSimStackingAction::~SourceSimStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
SourceSimStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

std::ofstream logging;
const G4String name = "Detector";

G4int eventNumber = aTrack->GetTrackID ();

G4double pmom;
if(eventNumber == 1){
pmom  =aTrack->GetKineticEnergy();
if(pmom > momentum){
momentum=pmom;
}
}

if(k>1001 && i<34){
     i++;
     k=1;
    }

  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      G4VPhysicalVolume* volume = aTrack->GetVolume();
      if(volume->GetName()== "Detector")
      { 
        if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        {
	  fDetectorCounter++;
        }
        if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
        { 
	  fDetectorCounter++;
        }
      }
    }
   
  }
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SourceSimStackingAction::NewStage()
{
std::ofstream logging;
logging.open("detector_counts.txt", std::ios::app);

logging << fDetectorCounter;
logging << "		";
logging << momentum;
logging << "	\n";

  logging.close();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SourceSimStackingAction::PrepareNewEvent()
{

fDetectorCounter=0;
momentum=0;
k++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
