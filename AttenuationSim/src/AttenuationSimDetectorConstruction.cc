// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "AttenuationSimDetectorConstruction.hh"

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

AttenuationSimDetectorConstruction::AttenuationSimDetectorConstruction()
 : G4VUserDetectorConstruction()
{
	//These are the dimensions of the World
	fworld_x = 9000*cm; 
	fworld_y = fworld_z = 7000.0*cm;
	//These are the dimensions of the detector
	fdetector_x    = 1.0*cm; 
	fdetector_y    = fdetector_z    =  5.0*cm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AttenuationSimDetectorConstruction::~AttenuationSimDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* AttenuationSimDetectorConstruction::Construct()
{

// ------------- Materials -------------

  G4double a, z, density;
  G4int nelements;

  G4Element* H  = new G4Element("Hydrogen","H",  z= 1, a=   1.01*g/mole);
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  G4Element* C = new G4Element("Carbon"  , "C", z=6 , a=12.01*g/mole);
  
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Lead = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* concrete = nist->FindOrBuildMaterial("G4_CONCRETE");

G4int ncomponents;
G4double fractionmass;

//Definition of the materials for the building
G4Material* Concrete_roof = new G4Material("Concrete_roof", density = 2.1*g/cm3, ncomponents=1);
Concrete_roof->AddMaterial(concrete, fractionmass=1.0);

G4Material* Concrete_wall = new G4Material("Concrete_wall", density = 1.5*g/cm3, ncomponents=1);
Concrete_wall->AddMaterial(concrete, fractionmass=1.0);

//Definition of a new material: the plastic scintillator
G4Material* Bc408 = new G4Material("PLASTIC_SC_Bc408", density = 1.043*g/cm3, ncomponents=2); 
	Bc408->AddElement(H, fractionmass=0.077418);
  Bc408->AddElement(C, fractionmass=0.922582);

	const G4int NUMENTRIES = 12;
		
	G4double PhotonEnergy[NUMENTRIES] = 
		{	3.44*eV, 3.26*eV, 3.1*eV, 3.02*eV, 2.95*eV,
			2.92*eV, 2.82*eV, 2.76*eV, 2.7*eV, 2.58*eV,
			2.38*eV, 2.08*eV };
	
	G4double RINDEX_Bc408[NUMENTRIES] =
		{ 1.58, 1.58, 1.58, 1.58, 1.58,
			1.58, 1.58, 1.58, 1.58, 1.58,
			1.58, 1.58 };
	
	G4double ABSORPTION_Bc408[NUMENTRIES] =
		{ 210*cm, 210*cm, 210*cm, 210*cm, 210*cm,
			210*cm, 210*cm, 210*cm, 210*cm, 210*cm,
			210*cm, 210*cm }; 

	G4double SCINTILLATION_Bc408[NUMENTRIES] =
		{ 0.04, 0.07, 0.20, 0.49, 0.84,
			1.00, 0.83, 0.55, 0.40, 0.17,
			0.03, 0. };

	G4MaterialPropertiesTable *Bc408_mt = new G4MaterialPropertiesTable();
	Bc408_mt->AddProperty("RINDEX", PhotonEnergy, RINDEX_Bc408, NUMENTRIES)->SetSpline(true);
	Bc408_mt->AddProperty("ABSLENGTH", PhotonEnergy, ABSORPTION_Bc408, NUMENTRIES)->SetSpline(true);
	Bc408_mt->AddProperty("FASTCOMPONENT", PhotonEnergy, SCINTILLATION_Bc408, NUMENTRIES)->SetSpline(true);
	Bc408_mt->AddConstProperty("SCINTILLATIONYIELD",500./MeV);
	Bc408_mt->AddConstProperty("RESOLUTIONSCALE",1.0);
	Bc408_mt->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
	//Bc408_mt->AddConstProperty("SLOWTIMECONSTANT",1.*ns);
	Bc408_mt->AddConstProperty("YIELDRATIO",1.);
	//Bc408->SetMaterialPropertiesTable(Bc408_mt);  

	const G4int NUMENTRIES2 = 42;
	G4double PhotonEnergy_WLS_ABS_Bcf91a_core[NUMENTRIES2] =
		{ 3.539*eV, 3.477*eV, 3.340*eV, 3.321*eV, 3.291*eV,
			3.214*eV, 3.162*eV, 3.129*eV, 3.091*eV, 3.086*eV,
			3.049*eV, 3.008*eV, 2.982*eV, 2.958*eV, 2.928*eV,
			2.905*eV, 2.895*eV, 2.890*eV, 2.858*eV, 2.813*eV,
			2.774*eV, 2.765*eV, 2.752*eV, 2.748*eV, 2.739*eV,
			2.735*eV, 2.731*eV, 2.723*eV, 2.719*eV, 2.698*eV,
			2.674*eV, 2.626*eV, 2.610*eV, 2.583*eV, 2.556*eV,
			2.530*eV, 2.505*eV, 2.480*eV, 2.455*eV, 2.431*eV,
			2.407*eV, 2.384*eV };

	G4double WLS_ABSLENGTH_Bcf91a_core[NUMENTRIES2] =
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
	G4double PhotonEnergy_WLS_EM_Bcf91a_core[NUMENTRIES3] =
		{ 2.69*eV, 2.67*eV, 2.66*eV, 2.64*eV, 2.63*eV,
			2.61*eV, 2.58*eV, 2.56*eV, 2.55*eV, 2.53*eV,
			2.50*eV, 2.48*eV, 2.46*eV, 2.45*eV, 2.44*eV,
			2.43*eV, 2.41*eV, 2.37*eV, 2.33*eV, 2.25*eV,
			2.24*eV, 2.19*eV, 2.15*eV, 2.08*eV };

	G4double WLS_EMISSION_Bcf91a_core[NUMENTRIES3] =
		{	0., 0.02, 0.09, 0.20, 0.29,
			0.40, 0.59, 0.70, 0.80, 0.89,
			1.00, 0.96, 0.88, 0.79, 0.69,
			0.59, 0.50, 0.40, 0.31, 0.22,
			0.19, 0.10, 0.06, 0. };

	Bc408_mt->AddProperty("WLSABSLENGTH", PhotonEnergy_WLS_ABS_Bcf91a_core, WLS_ABSLENGTH_Bcf91a_core, NUMENTRIES2);
	Bc408_mt->AddProperty("WLSCOMPONENT", PhotonEnergy_WLS_EM_Bcf91a_core, WLS_EMISSION_Bcf91a_core, NUMENTRIES3);
	Bc408_mt->AddConstProperty("WLSTIMECONSTANT", 0.5*ns);
	Bc408->SetMaterialPropertiesTable(Bc408_mt);


//
// ------------- Volumes --------------

G4double thiccness;
thiccness = 1*cm;
G4double position;
position = thiccness/2.0 + 3.45*cm;


// Definition of the world
//
  G4Box* world_box = new G4Box("World",fworld_x/2.0,fworld_y/2.0,fworld_z/2.0);

  G4LogicalVolume* world_log
    = new G4LogicalVolume(world_box,air,"World",0,0,0);

  G4VPhysicalVolume* world_phys
    = new G4PVPlacement(0,G4ThreeVector(),world_log,"World",0,false,0);

//For changing the zenith angle (the rientation of the detector), change the value of phi
  G4double phi, x, y, w, theta;
    phi = 0*deg;
    theta = 0*deg;
    x = 6.4*cm;
    y = 0.*cm;
    w = 0.*cm;
    G4RotationMatrix rm;
    rm.rotateZ(phi);

// ---------The Detector---------
//
  G4Box* Detector_box = new G4Box("Detector",fdetector_x/2.0,fdetector_y/2.0,fdetector_z/2.0);

  G4LogicalVolume* Detector_log
    = new G4LogicalVolume(Detector_box,Bc408,"Detector",0,0,0);

  G4VPhysicalVolume* Detector_phys
    = new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*0*cm,std::sin(phi)*0*cm,0)), Detector_log,"Detector",
                       world_log,false,0); 

//For a second detector:
//This detector is above the firs one, the rotation is always about zero so the two detectors are always aligned.
 G4Box* Detector2_box = new G4Box("Detector2",fdetector_x/2.0,fdetector_y/2.0,fdetector_z/2.0); 

  G4LogicalVolume* Detector2_log
    = new G4LogicalVolume(Detector2_box,Bc408,"Detector2",0,0,0);

G4VPhysicalVolume* Detector2_phys
    = new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*(7)*cm,std::sin(phi)*(7)*cm,0)), Detector2_log,"Detector2",
                       world_log,false,0);

//------------The building:------------
//
//Rooftop:
G4Box* concrete_box = new G4Box("concrete",25/2*cm,200*cm,200*cm);

G4LogicalVolume* concrete_log
    = new G4LogicalVolume(concrete_box,Concrete_roof,"Concrete",0,0,0);

G4VPhysicalVolume* concrete1_phys
    = new G4PVPlacement(0,G4ThreeVector(250*cm,0.0*cm,0.0),concrete_log,"concrete1",
                       world_log,false,0);
G4VPhysicalVolume* concrete2_phys
    = new G4PVPlacement(0,G4ThreeVector(250*cm+300*cm,0.0*cm,0.0),concrete_log,"concrete2",
                       world_log,false,0);
G4VPhysicalVolume* concrete3_phys
    = new G4PVPlacement(0,G4ThreeVector(250*cm+600*cm,0.0*cm,0.0),concrete_log,"concrete3",
                       world_log,false,0);
G4VPhysicalVolume* concrete4_phys
    = new G4PVPlacement(0,G4ThreeVector(250*cm+900*cm,0.0*cm,0.0),concrete_log,"concrete4",
                       world_log,false,0);

//walls:
G4Box* walls_1_box = new G4Box("walls_1",1150/2*cm,200*cm,15/2*cm);

G4LogicalVolume* walls_1_log
    = new G4LogicalVolume(walls_1_box,Concrete_wall,"Wall_1",0,0,0);

G4VPhysicalVolume* wall1_phys
    = new G4PVPlacement(0,G4ThreeVector(1150/2*cm,0.0*cm,207.5*cm),walls_1_log,"wall1",
                       world_log,false,0);
G4VPhysicalVolume* wall2_phys
    = new G4PVPlacement(0,G4ThreeVector(1150/2*cm,0.0*cm,-207.5*cm),walls_1_log,"wall2",
                       world_log,false,0);

G4Box* walls_2_box = new G4Box("walls_2",1150/2*cm,15/2*cm,200*cm);

G4LogicalVolume* walls_2_log
    = new G4LogicalVolume(walls_2_box,Concrete_wall,"Wall_2",0,0,0);

G4VPhysicalVolume* wall3_phys
    = new G4PVPlacement(0,G4ThreeVector(1150/2*cm,207.5*cm,0.0*cm),walls_2_log,"wall3",
                       world_log,false,0);
G4VPhysicalVolume* wall4_phys
    = new G4PVPlacement(0,G4ThreeVector(1150/2*cm,-207.5*cm,0.0*cm),walls_2_log,"wall4",
                       world_log,false,0);

//----------Lead Plate-----------
G4double distance=0.05*cm;
G4double width=1*cm;

  G4Box* Lead_box1 = new G4Box("Lead_box1",fdetector_x/2.0+0.5/2*cm+distance/2,fdetector_y/2.0+0.5/2*cm+distance/2,fdetector_z/2.0+0.5/2*cm+distance/2);

  G4Box* Lead_box2 = new G4Box("Lead_box2",fdetector_x/2.0+0.5/2*cm+distance/2+width,fdetector_y/2.0+0.5/2*cm+distance/2+width,fdetector_z/2.0+0.5/2*cm+distance/2+width);

  G4SubtractionSolid* subtraction_Lead =
    new G4SubtractionSolid("Box-Lead", Lead_box2, Lead_box1);

  G4LogicalVolume* LogicalLead =                         
    new G4LogicalVolume(subtraction_Lead,       //its solid
                        Lead,                   //its material
                        "LogicalAluminum");     //its name

    new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*(0)*cm,std::sin(phi)*(0)*cm,0.)),         //at (0,0,0)
                    LogicalLead,                //its logical volume
                    "Lead",                     //its name
                    world_log,                  //its mother  volume
                    false,                      //no boolean operation
                    0,                          //copy number
                    0);
         		


// ----------Aluminum------------
  G4Box* aluminum_box =
    new G4Box("Aluminum", 0.25*cm, fdetector_y, fdetector_z); //its size

  G4Box* box1 =
    new G4Box("box1", 5.0/2.0*cm, fdetector_y/1.2, fdetector_z/1.2);

  G4Box* box2 =
    new G4Box("box2", (5.0/2.0-1.0)*cm, fdetector_y/1.2-1.0*cm, fdetector_z/1.2-1.0*cm);  

  G4Box* box3 = 
    new G4Box("box3",fdetector_x/2.0+0.5/2*cm,fdetector_y/2.0+0.5/2*cm,fdetector_z/2.0+0.5/2*cm);

  G4Box* box4 = 
    new G4Box("box4",fdetector_x/2.0+0.05*cm,fdetector_y/2.0+0.05*cm,fdetector_z/2.0+0.05*cm);

  G4SubtractionSolid* subtraction1 =
    new G4SubtractionSolid("Box-Cylinder", box1, box2);

  G4SubtractionSolid* subtraction2 =
    new G4SubtractionSolid("Box-Cylinder", box3, box4);

  G4LogicalVolume* LogicalAluminum =                         
    new G4LogicalVolume(subtraction1,           //its solid
                        Lead,                   //its material
                        "LogicalAluminum");     //its name

  G4LogicalVolume* Logicalbar =                         
    new G4LogicalVolume(subtraction2,           //its solid
                        aluminum,               //its material
                        "Logicalbar");  





new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*7*cm,std::sin(phi)*7*cm,0.)),         //at (0,0,0)
                    Logicalbar,                //its logical volume
                    "rba",                     //its name
                    world_log,                 //its mother  volume
                    false,                     //no boolean operation
                    0,                         //copy number
                    0); 


new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*(0)*cm,std::sin(phi)*(0)*cm,0.)),         //at (0,0,0)
                    Logicalbar,                //its logical volume
                    "rba",              //its name
                world_log,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0);



  return world_phys;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
