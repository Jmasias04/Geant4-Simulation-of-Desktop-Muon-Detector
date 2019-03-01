// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include <iostream>
#include <fstream>
#include "AttenuationSimStackingAction.hh"
#include "AttenuationSimHistoManager.hh"
#include "G4VProcess.hh"
#include "G4SteppingManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "AttenuationSimSteppingVerbose.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4INCLThreeVector.hh"
#include <stdio.h>
#include <math.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AttenuationSimStackingAction::AttenuationSimStackingAction()
  : G4UserStackingAction(),
    fdetector2_counter(0), fdetector_counter(0), momentum(0), k(1), i(1)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AttenuationSimStackingAction::~AttenuationSimStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
AttenuationSimStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{

std::ofstream logging;
const G4String name = "Detector"; //assignates the detector

G4int eventNumber = aTrack->GetTrackID (); //if the ID is 1 -> it is a muon (particle generated)

G4double pmom;


if(eventNumber == 1){
pmom  =aTrack->GetKineticEnergy();
if(pmom > momentum){
momentum=pmom;
}
}


if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
{ // particle is optical photon
  if(aTrack->GetParentID()>0) 
  { // particle is secondary
    G4VPhysicalVolume* volume = aTrack->GetVolume(); //looks for the volume where the particle was when generated the photon
    if(volume->GetName()== "Detector")// particles originates in Detector
    { 
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
      {
	fdetector_counter++;
      }
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
      { 
	fdetector_counter++;
      }
    }    
    if(volume->GetName()== "Detector2") // particles originates in Detector2
    { 
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation") //if the photon has been created by scintillation
      {
	fdetector2_counter++;
      }
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov") //si el foton ha sido generado por cherenkov
      { 
	fdetector2_counter++;
      }
    }
  }
}
return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AttenuationSimStackingAction::NewStage()
{
//Prints a txt with coincidences
if((fdetector2_counter>1)&&(fdetector_counter>1)){ 
std::ofstream logging;
logging.open("coincidences.txt", std::ios::app);

logging << fdetector2_counter;
logging << "		";
logging << fdetector_counter;

logging << "	\n";

  logging.close();
}

//Prints txts with counts
if((fdetector2_counter>1)){ 
std::ofstream logging;
logging.open("counts_detector2.txt", std::ios::app);

logging << fdetector2_counter;

logging << "	\n";

  logging.close();
}

if((fdetector_counter>1)){ 
std::ofstream logging;
logging.open("counts_detector.txt", std::ios::app);

logging << fdetector_counter;

logging << "	\n";

  logging.close();
}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AttenuationSimStackingAction::PrepareNewEvent()
{

fdetector2_counter=0;
fdetector_counter=0;
momentum=0;
k++;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
