// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef SourceSimDetectorConstruction_h
#define SourceSimDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SourceSimDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SourceSimDetectorConstruction();
    virtual ~SourceSimDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

  private:
    G4double fworld_x;
    G4double fworld_y;
    G4double fworld_z;

    G4double fDetector_x;
    G4double fDetector_y;
    G4double fDetector_z;

    G4double fBubble_x;
    G4double fBubble_y;
    G4double fBubble_z;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*SourceSimDetectorConstruction_h*/
