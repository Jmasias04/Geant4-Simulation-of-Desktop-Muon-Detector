// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistDetectorConstruction_h
#define PhotonDistDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhotonDistDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    PhotonDistDetectorConstruction();
    virtual ~PhotonDistDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();

  private:
    G4double fworld_x;
    G4double fworld_y;
    G4double fworld_z;

    G4double fDetector_x;
    G4double fDetector_y;
    G4double fDetector_z;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*PhotonDistDetectorConstruction_h*/
