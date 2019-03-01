// ******************************************
// *************** HEP-PUCP ***************
// ******************************************
#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(
                                             PrimaryGeneratorAction* Gun)
:G4UImessenger(),fAction(Gun),
 fGunDir(0),      
 fDefaultCmd(0),
 fRndmCmd(0)
{
 fGunDir = new G4UIdirectory("/testem/gun/");
 fGunDir->SetGuidance("gun control");
 
 fDefaultCmd = new G4UIcmdWithoutParameter("/testem/gun/setDefault",this);
 fDefaultCmd->SetGuidance("set/reset the kinematic defined in PrimaryGenerator");
 fDefaultCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
 fRndmCmd = new G4UIcmdWithADouble("/testem/gun/rndm",this);
 fRndmCmd->SetGuidance("random lateral extension on the beam");
 fRndmCmd->SetGuidance("in fraction of 0.5*sizeYZ");
 fRndmCmd->SetParameterName("rBeam",false);
 fRndmCmd->SetRange("rBeam>=0.&&rBeam<=1.");
 fRndmCmd->AvailableForStates(G4State_Idle);   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fDefaultCmd;
  delete fRndmCmd;
  delete fGunDir;    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue)
{ 
  if (command == fDefaultCmd)
    {fAction->SetDefaultKinematic();}
   
  if (command == fRndmCmd)
   { fAction->SetRndmBeam(fRndmCmd->GetNewDoubleValue(newValue));}       
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

