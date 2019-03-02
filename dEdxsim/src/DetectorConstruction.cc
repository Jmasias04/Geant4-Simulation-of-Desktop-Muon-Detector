// ******************************************
// *************** HEP-PUCP ***************
// ******************************************

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnitsTable.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fAbsorberMaterial(0),fWorldMaterial(0),fDefaultWorld(true),
 fSolidWorld(0),fLogicWorld(0),fPhysiWorld(0),
 fSolidAbsorber(0),fLogicAbsorber(0),fPhysiAbsorber(0),
 fDetectorMessenger(0)
{
  // default parameter values of the calorimeter
  fAbsorberThickness = 1.*cm;
  fAbsorberSizeYZ    = 5.*cm;
  fXposAbs           = 0.*cm;
  ComputeCalorParameters();
  
  // materials  
  DefineMaterials();

G4String symbol;             //a=mass of a mole;
  G4double a, z, density;      //z=mean number of protons;  

  G4int ncomponents, natoms;
  G4double fractionmass;
  G4double temperature, pressure;

  G4Element* H  = new G4Element("Hydrogen","H",  z= 1, a=   1.01*g/mole);
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  G4Element* C = new G4Element("Carbon"  , "C", z=6 , a=12.01*g/mole);


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
	PlasticSc_mt->AddProperty("RINDEX", PhotonEnergy, RINDEX_PlasticSc, NUMENTRIES)->SetSpline(true);
	PlasticSc_mt->AddProperty("ABSLENGTH", PhotonEnergy, ABSORPTION_PlasticSc, NUMENTRIES)->SetSpline(true);
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

  SetWorldMaterial   ("G4_AIR");
  SetAbsorberMaterial("PLASTIC_SC");

 
  // create commands for interactive definition of the calorimeter  
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ 
  delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructCalorimeter();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
  //This function illustrates the possible ways to define materials
 

  
  
  }

void DetectorConstruction::ComputeCalorParameters()
{
  // Compute derived parameters of the calorimeter
  fXstartAbs = fXposAbs-0.5*fAbsorberThickness; 
  fXendAbs   = fXposAbs+0.5*fAbsorberThickness;

  G4double xmax = std::max(std::abs(fXstartAbs), std::abs(fXendAbs));
     
  // change world size by the flag or if the absorber is large 
  if (fDefaultWorld || 2*xmax >=  fWorldSizeX ||
      fAbsorberSizeYZ >= fWorldSizeYZ) 
    {
      fWorldSizeX = 3*xmax; 
      fWorldSizeYZ= 1.2*fAbsorberSizeYZ;
    }         
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
G4VPhysicalVolume* DetectorConstruction::ConstructCalorimeter()
{ 
  // World
  //

 
 fSolidWorld = 	new G4Box("World",                       //its name
       			70.0*cm, 20.0*cm, 20.0*cm);     //its size
                         
  fLogicWorld = new G4LogicalVolume(fSolidWorld,          //its solid
                        fWorldMaterial,           //its material
                        "World");            //its name
                                   
  fPhysiWorld = new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      fLogicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0);        //overlaps checking   

   G4double phi, x, y, w, theta;
    phi = 0*deg;
    theta = 0*deg;
    x = 6.4*cm;
    y = 0.*cm;
    w = 0.*cm;
    G4RotationMatrix rm;
    rm.rotateZ(phi);
                          
  // Absorber
  // 
  fSolidAbsorber = new G4Box("Shape1",                   //its name
        (fAbsorberThickness/2.0), (fAbsorberSizeYZ/2.0), (fAbsorberSizeYZ/2.0)); //its size
                          
  fLogicAbsorber = new G4LogicalVolume(fSolidAbsorber,    //its solid
                                       fAbsorberMaterial, //its material
                                       "Absorber");       //its name
                                                
  fPhysiAbsorber = new G4PVPlacement(0,                   //no rotation
                        G4ThreeVector(0.,0.,0.),    //its position
                                fLogicAbsorber,     //its logical volume
                                "Absorber",         //its name
                                fLogicWorld,        //its mother
                                false,              //no boulean operat
                                0);                 //copy number

G4NistManager* nist = G4NistManager::Instance();
G4Material* concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
G4Material* aluminum = nist->FindOrBuildMaterial("G4_Al");
G4Material* silicon = nist->FindOrBuildMaterial("G4_Si");

 G4Box* sipm_box = new G4Box("sipm",(fAbsorberThickness/2.0)/40.,(fAbsorberSizeYZ/2.0)*6/50.,(fAbsorberSizeYZ/2.0)*6/50.);

  G4LogicalVolume* sipm_log
    = new G4LogicalVolume(sipm_box,silicon,"sipm",0,0,0);

  G4VPhysicalVolume* silicon_phys
    = new G4PVPlacement(G4Transform3D(rm,G4ThreeVector(std::cos(phi)*0.51251*cm,std::sin(phi)*0.51251*cm,0)), sipm_log,"sipm",
                       fLogicWorld,false,0); 



/*
G4Box* concreto =
    new G4Box("concreto",                   //its name
        20.*cm, 20*cm, 0.85*m); //its size
     
  G4LogicalVolume* LogicalConcrete =                         
    new G4LogicalVolume(concreto,           //its solid
                        concrete,             //its material
                        "LogicalConcrete");         //its name
     G4double cheight = 5.7*m;    
G4double n = 1;


new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  
 new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  
 new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  
 new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  
 new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  
 new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  
 new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  
 new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;   new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,n*cheight),         //at (0,0,0)
                    LogicalConcrete,                //its logical volume
                    "Concrete",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0); 
n=n+1.0;  

G4Box* aluminio =
    new G4Box("aluminio",                   //its name
        20.*cm, 20*cm, 0.35*cm); //its size
     
  G4LogicalVolume* LogicalAluminum =                         
    new G4LogicalVolume(aluminio,           //its solid
                        aluminum,             //its material
                        "LogicalAluminum");         //its name

new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0.,0.,0.86*cm),         //at (0,0,0)
                    LogicalAluminum,                //its logical volume
                    "Aluminum",              //its name
                fLogicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    0);
*/
  PrintCalorParameters();         
  
  //always return the physical World
  //
  return fPhysiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintCalorParameters()
{
  G4cout << "\n" << fWorldMaterial    << G4endl;
  G4cout << "\n" << fAbsorberMaterial << G4endl;
    
  G4cout << "\n The  WORLD   is made of "  << G4BestUnit(fWorldSizeX,"Length")
         << " of " << fWorldMaterial->GetName();
  G4cout << ". The transverse size (YZ) of the world is " 
         << G4BestUnit(fWorldSizeYZ,"Length") << G4endl;
  G4cout << " The ABSORBER is made of " 
         <<G4BestUnit(fAbsorberThickness,"Length")
         << " of " << fAbsorberMaterial->GetName();
  G4cout << ". The transverse size (YZ) is " 
         << G4BestUnit(fAbsorberSizeYZ,"Length") << G4endl;
  G4cout << " X position of the middle of the absorber "
         << G4BestUnit(fXposAbs,"Length");
  G4cout << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);

  if (pttoMaterial && fAbsorberMaterial != pttoMaterial) {
    fAbsorberMaterial = pttoMaterial;                  
    if(fLogicAbsorber) { fLogicAbsorber->SetMaterial(fAbsorberMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetWorldMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);

  if (pttoMaterial && fWorldMaterial != pttoMaterial) {
    fWorldMaterial = pttoMaterial; 
    if(fLogicWorld) { fLogicWorld->SetMaterial(fWorldMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberThickness(G4double val)
{
  fAbsorberThickness = val;
  ComputeCalorParameters();
  if(fPhysiWorld) { ChangeGeometry(); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberSizeYZ(G4double val)
{
  fAbsorberSizeYZ = val;
  ComputeCalorParameters();
  if(fPhysiWorld) { ChangeGeometry(); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetWorldSizeX(G4double val)
{
  fWorldSizeX = val;
  fDefaultWorld = false;
  ComputeCalorParameters();
  if(fPhysiWorld) { ChangeGeometry(); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetWorldSizeYZ(G4double val)
{
  fWorldSizeYZ = val;
  fDefaultWorld = false;
  ComputeCalorParameters();
  if(fPhysiWorld) { ChangeGeometry(); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetAbsorberXpos(G4double val)
{
  if(!fPhysiWorld) { fXposAbs = val; }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void DetectorConstruction::ConstructSDandField()
{
  if ( fFieldMessenger.Get() == 0 ) {
    // Create global magnetic field messenger.
    // Uniform magnetic field is then created automatically if
    // the field value is not zero.
    G4ThreeVector fieldValue = G4ThreeVector();
    G4GlobalMagFieldMessenger* msg =
      new G4GlobalMagFieldMessenger(fieldValue);
    //msg->SetVerboseLevel(1);
    G4AutoDelete::Register(msg);
    fFieldMessenger.Put( msg );        
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ChangeGeometry()
{
  fSolidWorld->SetXHalfLength(fWorldSizeX*0.5);
  fSolidWorld->SetYHalfLength(fWorldSizeYZ*0.5);
  fSolidWorld->SetZHalfLength(fWorldSizeYZ*0.5);

  fSolidAbsorber->SetXHalfLength(fAbsorberThickness*0.5);
  fSolidAbsorber->SetYHalfLength(fAbsorberSizeYZ*0.5);
  fSolidAbsorber->SetZHalfLength(fAbsorberSizeYZ*0.5);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

