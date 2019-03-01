// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

class PhotonDistSteppingVerbose;

#ifndef PhotonDistSteppingVerbose_h
#define PhotonDistSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhotonDistSteppingVerbose : public G4SteppingVerbose
{
 public:

   PhotonDistSteppingVerbose();
   virtual ~PhotonDistSteppingVerbose();
   
   virtual void StepInfo();
   virtual void TrackingStarted();
   G4double kenergy;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
