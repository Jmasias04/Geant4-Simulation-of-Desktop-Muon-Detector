// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "PhotonDistDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"

#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4PhysicalConstants.hh"

#include "G4RotationMatrix.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistDetectorConstruction::PhotonDistDetectorConstruction()
 : G4VUserDetectorConstruction()
{
  fworld_x = 600*cm;
  fworld_y = fworld_z = 600.0*cm;
  fDetector_x    = 1.0*cm; 
  fDetector_y    = fDetector_z    =  5.0*cm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistDetectorConstruction::~PhotonDistDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* PhotonDistDetectorConstruction::Construct()
{

// ------------- Materials -------------

  G4double a, z, density;
  G4int nelements;

// Air
//
  G4Element* H  = new G4Element("Hydrogen","H",  z= 1, a=   1.01*g/mole);
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  G4Element* C = new G4Element("Carbon"  , "C", z=6 , a=12.01*g/mole);
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* silicon = nist->FindOrBuildMaterial("G4_Si");


G4int ncomponents;
G4double fractionmass;

// The plastic scintillator:
//

G4Material* PlasticSc = new G4Material("PLASTIC_SC", density = 1.043*g/cm3, ncomponents=2);
	PlasticSc->AddElement(H, fractionmass=0.077418);
  PlasticSc->AddElement(C, fractionmass=0.922582);

	const G4int NUMENTRIES = 12;
		
	G4double PhotonEnergy[NUMENTRIES] = 
		{	3.44*eV, 3.26*eV, 3.1*eV, 3.02*eV, 2.95*eV,
			2.92*eV, 2.82*eV, 2.76*eV, 2.7*eV, 2.58*eV,
			2.38*eV, 2.08*eV };
	
	G4double RINDEX_PlasticSc[NUMENTRIES] =
		{ 1.58, 1.58, 1.58, 1.58, 1.58,
			1.58, 1.58, 1.58, 1.58, 1.58,
			1.58, 1.58 };
	
	G4double ABSORPTION_PlasticSc[NUMENTRIES] =
		{ 210*cm, 210*cm, 210*cm, 210*cm, 210*cm,
			210*cm, 210*cm, 210*cm, 210*cm, 210*cm,
			210*cm, 210*cm }; 

	G4double SCINTILLATION_PlasticSc[NUMENTRIES] =
		{ 0.04, 0.07, 0.20, 0.49, 0.84,
			1.00, 0.83, 0.55, 0.40, 0.17,
			0.03, 0. };

	G4MaterialPropertiesTable *PlasticSc_mt = new G4MaterialPropertiesTable();
	PlasticSc_mt->AddProperty("RINDEX", PhotonEnergy, RINDEX_PlasticSc, NUMENTRIES)->SetSpline(true); //el SetSpline es interpolar
	PlasticSc_mt->AddProperty("ABSLENGTH", PhotonEnergy, ABSORPTION_PlasticSc, NUMENTRIES)->SetSpline(true); //para hacer tu funcioncita bonita
	PlasticSc_mt->AddProperty("FASTCOMPONENT", PhotonEnergy, SCINTILLATION_PlasticSc, NUMENTRIES)->SetSpline(true);
	PlasticSc_mt->AddConstProperty("SCINTILLATIONYIELD",500./MeV);
	PlasticSc_mt->AddConstProperty("RESOLUTIONSCALE",1.0);
	PlasticSc_mt->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
	//PlasticSc_mt->AddConstProperty("SLOWTIMECONSTANT",1.*ns);
	PlasticSc_mt->AddConstProperty("YIELDRATIO",1.);
//	PlasticSc->SetMaterialPropertiesTable(PlasticSc_mt);  

	const G4int NUMENTRIES2 = 42;
	G4double PhotonEnergy_WLS_ABS_core[NUMENTRIES2] =
		{ 3.539*eV, 3.477*eV, 3.340*eV, 3.321*eV, 3.291*eV,
			3.214*eV, 3.162*eV, 3.129*eV, 3.091*eV, 3.086*eV,
			3.049*eV, 3.008*eV, 2.982*eV, 2.958*eV, 2.928*eV,
			2.905*eV, 2.895*eV, 2.890*eV, 2.858*eV, 2.813*eV,
			2.774*eV, 2.765*eV, 2.752*eV, 2.748*eV, 2.739*eV,
			2.735*eV, 2.731*eV, 2.723*eV, 2.719*eV, 2.698*eV,
			2.674*eV, 2.626*eV, 2.610*eV, 2.583*eV, 2.556*eV,
			2.530*eV, 2.505*eV, 2.480*eV, 2.455*eV, 2.431*eV,
			2.407*eV, 2.384*eV };

	G4double WLS_ABSLENGTH_core[NUMENTRIES2] =
		{ 0.28*cm, 0.28*cm, 0.26*cm, 0.25*cm, 0.24*cm,
			0.21*cm, 0.19*cm, 0.16*cm, 0.13*cm, 0.13*cm,
			0.14*cm, 0.11*cm, 0.08*cm, 0.05*cm, 0.02*cm,
			0.05*cm, 0.08*cm, 0.10*cm, 0.13*cm, 0.10*cm,
			0.08*cm, 0.07*cm, 0.08*cm, 0.11*cm, 0.13*cm,
			0.16*cm, 0.19*cm, 0.21*cm, 0.24*cm, 0.27*cm,
			0.30*cm, 2.69*cm, 3.49*cm, 3.99*cm, 5.00*cm,
			11.6*cm, 21.6*cm, 33.1*cm, 175*cm, 393*cm,
			617*cm, 794*cm };

	const G4int NUMENTRIES3 = 24;
	G4double PhotonEnergy_WLS_EM_core[NUMENTRIES3] =
		{ 2.69*eV, 2.67*eV, 2.66*eV, 2.64*eV, 2.63*eV,
			2.61*eV, 2.58*eV, 2.56*eV, 2.55*eV, 2.53*eV,
			2.50*eV, 2.48*eV, 2.46*eV, 2.45*eV, 2.44*eV,
			2.43*eV, 2.41*eV, 2.37*eV, 2.33*eV, 2.25*eV,
			2.24*eV, 2.19*eV, 2.15*eV, 2.08*eV };

	G4double WLS_EMISSION_core[NUMENTRIES3] =
		{	0., 0.02, 0.09, 0.20, 0.29,
			0.40, 0.59, 0.70, 0.80, 0.89,
			1.00, 0.96, 0.88, 0.79, 0.69,
			0.59, 0.50, 0.40, 0.31, 0.22,
			0.19, 0.10, 0.06, 0. };

	PlasticSc_mt->AddProperty("WLSABSLENGTH", PhotonEnergy_WLS_ABS_core, WLS_ABSLENGTH_core, NUMENTRIES2);
	PlasticSc_mt->AddProperty("WLSCOMPONENT", PhotonEnergy_WLS_EM_core, WLS_EMISSION_core, NUMENTRIES3);
	PlasticSc_mt->AddConstProperty("WLSTIMECONSTANT", 0.5*ns);
	PlasticSc->SetMaterialPropertiesTable(PlasticSc_mt);

//
// ------------- Volumes --------------


// Definition of the world
//
  G4Box* world_box = new G4Box("World",fworld_x*1.5,fworld_y/1.0,fworld_z/1.0);

  G4LogicalVolume* world_log
    = new G4LogicalVolume(world_box,air,"World",0,0,0);

  G4VPhysicalVolume* world_phys
    = new G4PVPlacement(0,G4ThreeVector(),world_log,"World",0,false,0);


  G4double phi, x, y, w, theta;
    phi = 0*deg;
    theta = 0*deg;
    x = 6.4*cm;
    y = 0.*cm;
    w = 0.*cm;
    G4RotationMatrix rm;
    rm.rotateZ(phi);

// The Detector
//
  G4Box* Detector_box = new G4Box("Detector",fDetector_x/2.0,fDetector_y/2.0,fDetector_z/2.0);

  G4LogicalVolume* Detector_log
    = new G4LogicalVolume(Detector_box,PlasticSc,"Detector",0,0,0);

  G4VPhysicalVolume* Detector_phys
    = new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*0*cm,std::sin(phi)*0*cm,0)), Detector_log,"Detector",
                       world_log,false,0); 
  G4Box* sipm_box = new G4Box("sipm",(fDetector_x/2.0)/40.,(fDetector_y/2.0)*6/50.,(fDetector_z/2.0)*6/50.);

  G4LogicalVolume* sipm_log
    = new G4LogicalVolume(sipm_box,silicon,"sipm",0,0,0);

  G4VPhysicalVolume* silicon_phys
    = new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*0.51251*cm,std::sin(phi)*0.51251*cm,0)), sipm_log,"sipm",
                       world_log,false,0); 

  return world_phys;

}

