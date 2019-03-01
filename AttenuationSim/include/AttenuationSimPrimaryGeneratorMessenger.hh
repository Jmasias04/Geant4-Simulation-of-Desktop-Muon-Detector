// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef AttenuationSimPrimaryGeneratorMessenger_h
#define AttenuationSimPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class AttenuationSimPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class AttenuationSimPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    AttenuationSimPrimaryGeneratorMessenger(AttenuationSimPrimaryGeneratorAction* );
    virtual ~AttenuationSimPrimaryGeneratorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:
    AttenuationSimPrimaryGeneratorAction* fAttenuationSimAction;
    G4UIdirectory*                  fGunDir;
    G4UIcmdWithADoubleAndUnit*      fPolarCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
