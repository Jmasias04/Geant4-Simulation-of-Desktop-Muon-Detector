// ******************************************
// *************** HEP-PUCP ***************
// ******************************************

#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class DetectorConstruction;
class EventAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class TrackingAction : public G4UserTrackingAction {

  public:  
    TrackingAction(DetectorConstruction*,EventAction*);
   ~TrackingAction() {};
   
    virtual void  PreUserTrackingAction(const G4Track*);   
    virtual void PostUserTrackingAction(const G4Track*);
    
  private:
    DetectorConstruction* fDetector;
    EventAction*          fEventAction;
    
    G4double fXstartAbs, fXendAbs;
    G4double fPrimaryCharge;
    G4double fDirX;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
