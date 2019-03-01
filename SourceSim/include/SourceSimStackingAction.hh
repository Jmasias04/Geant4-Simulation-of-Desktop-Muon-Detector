// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef SourceSimStackingAction_H
#define SourceSimStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SourceSimStackingAction : public G4UserStackingAction
{
  public:
    SourceSimStackingAction();
    virtual ~SourceSimStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4int fDetectorCounter;
    G4double momentum;
    G4int i;
    G4int k;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
