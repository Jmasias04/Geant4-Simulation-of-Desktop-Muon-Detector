// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef SourceSimRunAction_h
#define SourceSimRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;
class HistoManager;

class SourceSimRunAction : public G4UserRunAction
{
  public:
    SourceSimRunAction();
    virtual ~SourceSimRunAction();

  public:
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);

  private:
    G4Timer* fTimer;
    HistoManager*           fHistoManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*SourceSimRunAction_h*/
