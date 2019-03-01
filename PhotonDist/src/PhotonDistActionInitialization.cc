// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "PhotonDistActionInitialization.hh"
#include "PhotonDistPrimaryGeneratorAction.hh"
#include "PhotonDistRunAction.hh"
#include "PhotonDistSteppingAction.hh"
#include "PhotonDistStackingAction.hh"
#include "PhotonDistSteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistActionInitialization::PhotonDistActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistActionInitialization::~PhotonDistActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonDistActionInitialization::BuildForMaster() const
{
  SetUserAction(new PhotonDistRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonDistActionInitialization::Build() const
{
  SetUserAction(new PhotonDistPrimaryGeneratorAction());
  SetUserAction(new PhotonDistRunAction());
  SetUserAction(new PhotonDistSteppingAction());
  SetUserAction(new PhotonDistStackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose*
               PhotonDistActionInitialization::InitializeSteppingVerbose() const
{
  return new PhotonDistSteppingVerbose();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
