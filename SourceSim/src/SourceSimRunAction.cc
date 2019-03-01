// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

// Make this appear first!
#include "G4Timer.hh"

#include "SourceSimRunAction.hh"


#include "SourceSimHistoManager.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SourceSimRunAction::SourceSimRunAction()
 : G4UserRunAction(),
   fTimer(0)
{
  fTimer = new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SourceSimRunAction::~SourceSimRunAction()
{
  delete fTimer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SourceSimRunAction::BeginOfRunAction(const G4Run* aRun)
{
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

   if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  } 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SourceSimRunAction::EndOfRunAction(const G4Run* aRun)
{

 
  fTimer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent()
         << " " << *fTimer << G4endl;
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();  
 if ( analysisManager->IsActive() ) {    
    analysisManager->Write();
    analysisManager->CloseFile();}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
