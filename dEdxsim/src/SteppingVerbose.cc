// ******************************************
// *************** HEP-PUCP ***************
// ******************************************

#include "SteppingVerbose.hh"

#include "G4SteppingManager.hh"
#include "G4ParticleTypes.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingVerbose::SteppingVerbose()
 : G4SteppingVerbose()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingVerbose::~SteppingVerbose()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingVerbose::TrackingStarted()
{  
  CopyState();
  
  G4int prec = G4cout.precision(3);
  
  //Step zero
  //  
  if( verboseLevel > 0 ){
    G4cout << std::setw( 5) << "Step#"      << " "
           << std::setw( 6) << "X"          << "    "
           << std::setw( 6) << "Y"          << "    "  
           << std::setw( 6) << "Z"          << "    "
           << std::setw( 9) << "KineE"      << " "
           << std::setw(11) << "dEStep"     << " "  
           << std::setw(11) << "StepLeng"  
           << std::setw(12) << "TrakLeng"
           << std::setw(10) << "Volume"     << "    "
           << "Process"    << G4endl;             

    G4cout << std::setw(5) << fTrack->GetCurrentStepNumber() << " "
        << std::setw(6) << G4BestUnit(fTrack->GetPosition().x(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetPosition().y(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetPosition().z(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
        << std::setw(9) << G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
        << std::setw(9) << G4BestUnit(fStep->GetStepLength(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetTrackLength(),"Length")
        << std::setw(10) << fTrack->GetVolume()->GetName()
        << "  initStep" << G4endl;        
  }
  G4cout.precision(prec);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingVerbose::StepInfo()
{  
  CopyState();
    
  G4int prec = G4cout.precision(3);

  if( verboseLevel >= 1 ){
    if( verboseLevel >= 4 ) VerboseTrack();
    if( verboseLevel >= 3 ){
      G4cout << G4endl;    
      G4cout << std::setw( 5) << "#Step#"     << " "
             << std::setw( 6) << "X"          << "    "
             << std::setw( 6) << "Y"          << "    "  
             << std::setw( 6) << "Z"          << "    "
             << std::setw( 9) << "KineE"      << " "
             << std::setw(11) << "dEStep"     << " "  
             << std::setw(11) << "StepLeng"     
             << std::setw(12) << "TrakLeng" 
             << std::setw(10) << "Volume"    << "  "
             << "Process"   << G4endl;                  
    }

    G4cout << std::setw( 5) << fTrack->GetCurrentStepNumber() << " "
        << std::setw(6) << G4BestUnit(fTrack->GetPosition().x(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetPosition().y(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetPosition().z(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
        << std::setw(9) << G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
        << std::setw(9) << G4BestUnit(fStep->GetStepLength(),"Length")
        << std::setw(6) << G4BestUnit(fTrack->GetTrackLength(),"Length")
        << std::setw(10) << fTrack->GetVolume()->GetName();

    const G4VProcess* process 
                      = fStep->GetPostStepPoint()->GetProcessDefinedStep();
    G4String procName = "UserLimit";
    if (process) procName = process->GetProcessName();
    if (fStepStatus == fWorldBoundary) procName = "OutOfWorld";
    G4cout << "  " << procName;
    G4cout << G4endl;

    if (verboseLevel == 2) {
      const std::vector<const G4Track*>* secondary 
                                    = fStep->GetSecondaryInCurrentStep();
      size_t nbtrk = (*secondary).size();
      if (nbtrk) {
        G4cout << "\n    :----- List of secondaries ----------------" << G4endl;
        G4cout.precision(4);
        for (size_t lp=0; lp<(*secondary).size(); lp++) {
          G4cout << "   "
                 << std::setw(13)                 
                 << (*secondary)[lp]->GetDefinition()->GetParticleName()
                 << ":  energy ="
                 << std::setw(6)
                 << G4BestUnit((*secondary)[lp]->GetKineticEnergy(),"Energy")
                 << "  time ="
                 << std::setw(6)
                 << G4BestUnit((*secondary)[lp]->GetGlobalTime(),"Time");
          G4cout << G4endl;
        }
              
        G4cout << "    :------------------------------------------\n" << G4endl;
      }
    }
    
  }
  G4cout.precision(prec);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
