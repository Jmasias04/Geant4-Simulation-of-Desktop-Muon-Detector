// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "PhotonDistHistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
PhotonDistHistoManager::PhotonDistHistoManager()
  : fFileName("PhotonDistDetector")
{
  Book();
}

PhotonDistHistoManager::~PhotonDistHistoManager()
{
  delete G4AnalysisManager::Instance();
}

void PhotonDistHistoManager::Book()
{

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);  
    
               
  G4int nbins = 10000;
  G4double vmin = 0.*eV;
  G4double vmax = 100.*eV;

  

  analysisManager->SetHistoDirectoryName("PhotonDist");  
  analysisManager->SetFirstHistoId(1);
  
     
 G4int id = analysisManager->CreateH1("1","Energy deposit in the absorber", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);

id = analysisManager->CreateH1("2","Muon energy distribution", nbins, vmin, vmax);
  analysisManager->SetH1Activation(id, false);
    

}
