// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

class SourceSimSteppingVerbose;

#ifndef SourceSimSteppingVerbose_h
#define SourceSimSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SourceSimSteppingVerbose : public G4SteppingVerbose
{
 public:

   SourceSimSteppingVerbose();
   virtual ~SourceSimSteppingVerbose();
   
   virtual void StepInfo();
   virtual void TrackingStarted();
   G4double kenergy;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
