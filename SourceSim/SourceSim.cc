// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "SourceSimPhysicsList.hh"
#include "SourceSimDetectorConstruction.hh"

#include "SourceSimActionInitialization.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " SourceSim [-m macro ] [-u UIsession] [-t nThreads] [-r seed] "
           << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Evaluate arguments
  //
  if ( argc > 9 ) {
    PrintUsage();
    return 1;
  }

  G4String macro;
  G4String session;
#ifdef G4MULTITHREADED
  G4int nThreads = 0;
#endif

  G4long myseed = 345354;
  for ( G4int i=1; i<argc; i=i+2 ) {
     if      ( G4String(argv[i]) == "-m" ) macro   = argv[i+1];
     else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
     else if ( G4String(argv[i]) == "-r" ) myseed  = atoi(argv[i+1]);
#ifdef G4MULTITHREADED
     else if ( G4String(argv[i]) == "-t" ) {
                    nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
    }
#endif
    else {
      PrintUsage();
      return 1;
    }
  }

  // Instantiate G4UIExecutive if interactive mode
  G4UIExecutive* ui = nullptr;
  if ( macro.size() == 0 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  if ( nThreads > 0 ) runManager->SetNumberOfThreads(nThreads);
#else
  G4RunManager * runManager = new G4RunManager;
#endif

  // Seed the random number generator manually
  G4Random::setTheSeed(myseed);

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager-> SetUserInitialization(new SourceSimDetectorConstruction());
  // Physics list
  runManager-> SetUserInitialization(new SourceSimPhysicsList());
  // User action initialization
  runManager->SetUserInitialization(new SourceSimActionInitialization());

  // Initialize G4 kernel
  //
  runManager->Initialize();

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( macro.size() ) {
     // Batch mode
     G4String command = "/control/execute ";
     UImanager->ApplyCommand(command+macro);
  }
  else // Define UI session for interactive mode
  {
     UImanager->ApplyCommand("/control/execute vis.mac");
     if (ui->IsGUI())
        UImanager->ApplyCommand("/control/execute gui.mac");
     ui->SessionStart();
     delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete visManager;
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
