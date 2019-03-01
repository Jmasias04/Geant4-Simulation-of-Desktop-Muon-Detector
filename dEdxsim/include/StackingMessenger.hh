// ******************************************
// *************** HEP-PUCP ***************
// ******************************************
#ifndef StackingMessenger_h
#define StackingMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class StackingAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StackingMessenger: public G4UImessenger
{
  public:
    StackingMessenger(StackingAction*);
   ~StackingMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    StackingAction*        fStackAction;
    
    G4UIdirectory*         fStackDir;          
    G4UIcmdWithAnInteger*  fKillCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
