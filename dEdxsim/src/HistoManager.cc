// ******************************************
// *************** HEP-PUCP ***************
// ******************************************

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("dedxsim")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);    // enable inactivation of histograms

  // Define histograms start values
  const G4int kMaxHisto = 50;
  const G4String id[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                         "10","11","12","13","14","15","16","17","18","19",
                         "20","21","22","23","24","25","26","27","28","29",
                         "30","31","32","33","34","35","36","37","38","39",
                         "40","41","42","43","44","45","46","47","48","49" 
                        };
                        
  const G4String title[] =
                { "dummy",                                                //0
                  "energy deposit in absorber",                           //1
                  "energy of charged secondaries at creation",            //2
                  "energy of neutral secondaries at creation",            //3
                  "energy of charged at creation (log scale)",            //4
                  "energy of neutral at creation (log scale)",            //5
                  "x_vertex of charged secondaries (all)",                //6
                  "x_vertex of charged secondaries (not absorbed)",       //7
                  "dummy","dummy",                                        //8-9
                  "(transmit, charged) : kinetic energy at exit",         //10
                  "(transmit, charged) : ener fluence: dE(MeV)/dOmega",   //11
                  "(transmit, charged) : space angle: dN/dOmega",         //12
                  "(transmit, charged) : projected angle at exit",        //13
                  "(transmit, charged) : projected position at exit",     //14
                  "(transmit, charged) : radius at exit",                 //15
                  "energy of Auger e- at creation",                       //16
                  "energy of fluorescence gamma at creation",             //17
                  "energy of Auger e- at creation (log scale)",           //18
                  "energy of fluorescence gamma at creation (log scale)", //19
                  "(transmit, neutral) : kinetic energy at exit",         //20
                  "(transmit, neutral) : ener fluence: dE(MeV)/dOmega",   //21
                  "(transmit, neutral) : space angle: dN/dOmega",         //22
                  "(transmit, neutral) : projected angle at exit",        //23
                  "dummy","dummy","dummy","dummy","dummy","dummy",       //24-29
                  "(reflect , charged) : kinetic energy at exit",         //30
                  "(reflect , charged) : ener fluence: dE(MeV)/dOmega",   //31
                  "(reflect , charged) : space angle: dN/dOmega",         //32
                  "(reflect , charged) : projected angle at exit",        //33
                  "dummy","dummy","dummy","dummy","dummy","dummy",       //34-39
                  "(reflect , neutral) : kinetic energy at exit",         //40
                  "(reflect , neutral) : ener fluence: dE(MeV)/dOmega",   //41
                  "(reflect , neutral) : space angle: dN/dOmega",         //42
                  "(reflect , neutral) : projected angle at exit",        //43
                  "energy of PIXE Auger e- at creation",                  //44
                  "energy of PIXE gamma at creation",                     //45
                  "energy of PIXE Auger e- at creation (log scale)",      //46
                  "energy of PIXE gamma at creation (log scale)",         //47
                  "dummy","dummy"                                        //48-49
                 };

  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) {
    G4int ih = analysisManager->CreateH1("h"+id[k], title[k], nbins,vmin,vmax);
    analysisManager->SetH1Activation(ih, false);
  }
}
