// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistSteppingAction_h
#define PhotonDistSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

/// Stepping action class
/// 

class PhotonDistSteppingAction : public G4UserSteppingAction
{
  public:
    PhotonDistSteppingAction();
    virtual ~PhotonDistSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    G4int fScintillationCounter;
    G4int fCerenkovCounter;
    G4int fEventNumber;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
