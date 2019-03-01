// ******************************************
// *************** HEP-PUCP ***************
// ******************************************

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class RunAction;
class EventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingAction : public G4UserSteppingAction
{
  public:
   SteppingAction(DetectorConstruction*,EventAction*);
  ~SteppingAction();

   virtual void UserSteppingAction(const G4Step*);

  private:
    DetectorConstruction* fDetector;
    EventAction*          fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
