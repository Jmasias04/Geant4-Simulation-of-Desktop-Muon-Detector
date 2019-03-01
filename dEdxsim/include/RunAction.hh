// ******************************************
// *************** HEP-PUCP ***************
// ******************************************
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Run;
class DetectorConstruction;
class PrimaryGeneratorAction;
class HistoManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunAction : public G4UserRunAction
{

public:

    RunAction(DetectorConstruction* det, PrimaryGeneratorAction* prim=0);
   ~RunAction();
   
    virtual G4Run* GenerateRun();    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    DetectorConstruction*   fDetector;
    PrimaryGeneratorAction* fPrimary;
    Run*                    fRun;        
    HistoManager*           fHistoManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

