// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

class AttenuationSimSteppingVerbose;

#ifndef AttenuationSimSteppingVerbose_h
#define AttenuationSimSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class AttenuationSimSteppingVerbose : public G4SteppingVerbose
{
 public:

   AttenuationSimSteppingVerbose();
   virtual ~AttenuationSimSteppingVerbose();
   
   virtual void StepInfo();
   virtual void TrackingStarted();
   G4double kenergy;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
