// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "AttenuationSimActionInitialization.hh"
#include "AttenuationSimPrimaryGeneratorAction.hh"
#include "AttenuationSimRunAction.hh"
#include "AttenuationSimSteppingAction.hh"
#include "AttenuationSimStackingAction.hh"
#include "AttenuationSimSteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AttenuationSimActionInitialization::AttenuationSimActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AttenuationSimActionInitialization::~AttenuationSimActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AttenuationSimActionInitialization::BuildForMaster() const
{
  SetUserAction(new AttenuationSimRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AttenuationSimActionInitialization::Build() const
{
  SetUserAction(new AttenuationSimPrimaryGeneratorAction());
  SetUserAction(new AttenuationSimRunAction());
  SetUserAction(new AttenuationSimSteppingAction());
  SetUserAction(new AttenuationSimStackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose*
               AttenuationSimActionInitialization::InitializeSteppingVerbose() const
{
  return new AttenuationSimSteppingVerbose();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
