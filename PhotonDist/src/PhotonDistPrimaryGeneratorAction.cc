// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "PhotonDistPrimaryGeneratorAction.hh"
#include "PhotonDistPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistPrimaryGeneratorAction::PhotonDistPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(), 
   fParticleGun(0)
{

//
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  SetDefaultKinematic();
  
  //create a messenger for this class
 fGunMessenger = new PhotonDistPrimaryGeneratorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhotonDistPrimaryGeneratorAction::~PhotonDistPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonDistPrimaryGeneratorAction::SetDefaultKinematic()
{    
  // default particle kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
                    = particleTable->FindParticle("gamma");//set particle, can be changed with a macro afterwards
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(4.*GeV);

	G4double psi = 0.;
	G4double phi_ang = 0.;
//distance from detector to source
	G4double r = 1.01*cm;
	
	G4double px0 =	cos(psi);
	G4double py0 =	sin(psi)*sin(phi_ang);
	G4double pz0 =	sin(psi)*cos(phi_ang);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.*px0,-1.*py0,-1.*pz0));
  fParticleGun->SetParticlePosition(G4ThreeVector(r*px0,r*py0,r*pz0));  

}

void PhotonDistPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ThreeVector oldPosition = fParticleGun->GetParticlePosition();

	G4double ene = GetEnergy();	
	fParticleGun->SetParticleEnergy(ene);
	SetNewPositionAndMomentum(oldPosition);
	

  fParticleGun->GeneratePrimaryVertex(anEvent);
  fParticleGun->SetParticlePosition(oldPosition);  
}

//This defines the energy distribution for the particle, in this case is exponential, startpow is the lowest power and endpow is the highest.
G4double PhotonDistPrimaryGeneratorAction::GetEnergy() 
{
	G4double rand = G4UniformRand();
	G4double ene = 0.;
	G4double startpow = -2.;
	G4double endpow =1.;
	G4double power=startpow+(endpow-startpow)*rand;
	ene=pow(10,power)*MeV;
	return ene;
}

void PhotonDistPrimaryGeneratorAction::SetNewPositionAndMomentum(G4ThreeVector oldPosition)
{
	
	G4ThreeVector position = G4ThreeVector(0.0,0.0,0.0); //particles pass through the detector center

	G4double r = sqrt(pow(oldPosition.x(),2)+pow(oldPosition.y(),2)+pow(oldPosition.z(),2));	
	G4double theta =0;
	fZAngleBeam = theta;
	G4double phi_ang = 0;

	G4double px =	cos(theta)*cos(phi_ang);
	G4double py =	cos(theta)*sin(phi_ang);
	G4double pz =	sin(theta);

	fParticleGun->SetParticlePosition(G4ThreeVector(r*px,r*py,r*pz)); 

	px	=	r*px	-	position.x();
	py 	=	r*py	-	position.y();
	pz 	=	r*pz	-	position.z();
	r 	= sqrt(pow(px,2)+pow(py,2)+pow(pz,2));	
	px	=	px/r;
	py	=	py/r;
	pz	=	pz/r;

	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.*px,-1.*py,-1.*pz)); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonDistPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhotonDistPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (fParticleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }

 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton);
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 fParticleGun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
