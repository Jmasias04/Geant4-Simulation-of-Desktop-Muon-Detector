// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistRunAction_h
#define PhotonDistRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;
class HistoManager;

class PhotonDistRunAction : public G4UserRunAction
{
  public:
    PhotonDistRunAction();
    virtual ~PhotonDistRunAction();

  public:
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);

  private:
    G4Timer* fTimer;
    HistoManager*           fHistoManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*PhotonDistRunAction_h*/
