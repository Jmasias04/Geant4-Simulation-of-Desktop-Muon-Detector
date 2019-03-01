// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef AttenuationSimStackingAction_H
#define AttenuationSimStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class AttenuationSimStackingAction : public G4UserStackingAction
{
  public:
    AttenuationSimStackingAction();
    virtual ~AttenuationSimStackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4int fdetector_counter;
    G4int fdetector2_counter;
    G4double momentum;
G4double theta1;
G4double theta2;
G4double phi1;
G4double phi2;
    G4int i;
    G4int k;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
