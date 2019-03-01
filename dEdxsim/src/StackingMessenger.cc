// ******************************************
// *************** HEP-PUCP ***************
// ******************************************

#include "StackingMessenger.hh"

#include "StackingAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingMessenger::StackingMessenger(StackingAction* stack)
:G4UImessenger(),fStackAction(stack),
 fStackDir(0),          
 fKillCmd(0)
{
  fStackDir = new G4UIdirectory("/testem/stack/");
  fStackDir->SetGuidance("stacking control");
   
  fKillCmd = new G4UIcmdWithAnInteger("/testem/stack/killSecondaries",this);
  fKillCmd->SetGuidance(" Choice: 0=no kill; 1=kill and record; 2=kill only");
  fKillCmd->SetParameterName("choice",true);
  fKillCmd->SetRange("choice>=0");
  fKillCmd->SetDefaultValue(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingMessenger::~StackingMessenger()
{
  delete fKillCmd;
  delete fStackDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void StackingMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{     
  if(command == fKillCmd)
    {fStackAction->SetKillStatus(fKillCmd->GetNewIntValue(newValue));}               
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
