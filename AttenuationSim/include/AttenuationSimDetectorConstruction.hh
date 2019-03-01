// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef AttenuationSimDetectorConstruction_h
#define AttenuationSimDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class AttenuationSimDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    AttenuationSimDetectorConstruction();
    virtual ~AttenuationSimDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

  private:
    G4double fworld_x;
    G4double fworld_y;
    G4double fworld_z;

    G4double fdetector_x;
    G4double fdetector_y;
    G4double fdetector_z;

    G4double fBubble_x;
    G4double fBubble_y;
    G4double fBubble_z;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*AttenuationSimDetectorConstruction_h*/
