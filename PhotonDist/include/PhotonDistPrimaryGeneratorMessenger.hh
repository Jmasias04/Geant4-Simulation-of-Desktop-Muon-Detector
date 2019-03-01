// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistPrimaryGeneratorMessenger_h
#define PhotonDistPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PhotonDistPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhotonDistPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    PhotonDistPrimaryGeneratorMessenger(PhotonDistPrimaryGeneratorAction* );
    virtual ~PhotonDistPrimaryGeneratorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:
    PhotonDistPrimaryGeneratorAction* fPhotonDistAction;
    G4UIdirectory*                  fGunDir;
    G4UIcmdWithADoubleAndUnit*      fPolarCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
