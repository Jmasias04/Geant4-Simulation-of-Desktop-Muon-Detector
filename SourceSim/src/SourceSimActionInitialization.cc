// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "SourceSimActionInitialization.hh"
#include "SourceSimPrimaryGeneratorAction.hh"
#include "SourceSimRunAction.hh"
#include "SourceSimSteppingAction.hh"
#include "SourceSimStackingAction.hh"
#include "SourceSimSteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SourceSimActionInitialization::SourceSimActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SourceSimActionInitialization::~SourceSimActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SourceSimActionInitialization::BuildForMaster() const
{
  SetUserAction(new SourceSimRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SourceSimActionInitialization::Build() const
{
  SetUserAction(new SourceSimPrimaryGeneratorAction());
  SetUserAction(new SourceSimRunAction());
  SetUserAction(new SourceSimSteppingAction());
  SetUserAction(new SourceSimStackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose*
               SourceSimActionInitialization::InitializeSteppingVerbose() const
{
  return new SourceSimSteppingVerbose();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
