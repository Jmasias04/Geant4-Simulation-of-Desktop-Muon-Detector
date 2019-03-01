// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#include "AttenuationSimPrimaryGeneratorAction.hh"
#include "AttenuationSimPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AttenuationSimPrimaryGeneratorAction::AttenuationSimPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(), 
   fParticleGun(0)
{
  nbins = 1000000; //Divisions of the angular distribution
	exp = 3.09;
	ratio = 174.;
	eps = 854.;
	E0 = 4.28;

	emin = 0.;
	emax = 1000.;
	//theta angles (0-pi)
	zmin = 0.; 
	zmax = halfpi;
	//phi angles (0-2pi)
	pmin = 0.; 
	pmax = 4.*halfpi;

	CreateEnergyArray();
	CreateCDFEnergy();
	CreateZenithArray();
	CreateCDFZenith();
	CreatePhiArray();
	CreateCDFPhi();

//
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  SetDefaultKinematic();
  
//create a messenger for this class
  fGunMessenger = new AttenuationSimPrimaryGeneratorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

AttenuationSimPrimaryGeneratorAction::~AttenuationSimPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AttenuationSimPrimaryGeneratorAction::SetDefaultKinematic()
{    
  // default particle kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
                    = particleTable->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(4.*GeV);

	G4double psi = 0.; // psi = 90*deg-theta
	G4double phi_ang = 0.;
	G4double r = 500.0*cm;
	
	G4double px0 =	cos(psi);
	G4double py0 =	sin(psi)*sin(phi_ang);
	G4double pz0 =	sin(psi)*cos(phi_ang);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1.*px0,-1.*py0,-1.*pz0));
  fParticleGun->SetParticlePosition(G4ThreeVector(r*px0,r*py0,r*pz0));  

}

void AttenuationSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ThreeVector oldPosition = fParticleGun->GetParticlePosition();

	G4double ene = GetEnergy();	
	fParticleGun->SetParticleEnergy(ene);
	SetNewPositionAndMomentum(oldPosition);
	

  fParticleGun->GeneratePrimaryVertex(anEvent);
  fParticleGun->SetParticlePosition(oldPosition);  
}

G4double AttenuationSimPrimaryGeneratorAction::MuonEnergyDist(G4double ene) 
{
	G4double MED;
	MED = pow(1+ene/eps,-1.)*pow(E0+ene,-1.*exp);
	return MED;
}

G4double AttenuationSimPrimaryGeneratorAction::MuonAngularDist(G4double theta)
{
	G4double PR;
	PR = sqrt(pow(ratio*cos(theta),2)+2*ratio+1)-ratio*cos(theta);
	PR = pow(PR,-1.*(exp-1));
	return PR;
}

void AttenuationSimPrimaryGeneratorAction::CreateEnergyArray()
{
	G4double *ene = new G4double[nbins];
	G4int i;
	G4double de = (emax-emin)/nbins;

	ene[0] = emin;
	for (i = 1; i < nbins; i++){
		ene[i] = ene[i-1] + de;
	}
	energy = ene;
}

void AttenuationSimPrimaryGeneratorAction::CreateZenithArray()
{
	G4double *ang = new G4double[nbins];
	G4int i;
	G4double da = (zmax-zmin)/nbins;

	ang[0] = zmin;
	for (i = 1; i < nbins; i++){
		ang[i] = ang[i-1] + da;
	}
	zenith = ang;
}

void AttenuationSimPrimaryGeneratorAction::CreatePhiArray()
{
	G4double *ang = new G4double[nbins];
	G4int i;
	G4double da = (pmax-pmin)/nbins;

	ang[0] = pmin;
	for (i = 1; i < nbins; i++){
		ang[i] = ang[i-1] + da;
	}
	phi = ang;
}

G4double AttenuationSimPrimaryGeneratorAction::EIntegral(G4double a, G4double b)
{
	G4double sum = 0;
	const G4int n = 3;
	G4double de = (b-a)/n;
	sum = MuonEnergyDist(a)+3.*MuonEnergyDist(a+de)+3.*MuonEnergyDist(a+2.*de)+MuonEnergyDist(a+3.*de); 
	sum = 0.375*de*sum;
	return sum;
}

G4double AttenuationSimPrimaryGeneratorAction::AIntegral(G4double a, G4double b)
{
	G4double sum = 0;
	const G4int n = 3;
	G4double de = (b-a)/n;
	sum = MuonAngularDist(a)+3.*MuonAngularDist(a+de)+3.*MuonAngularDist(a+2.*de)+MuonAngularDist(a+3.*de);
	sum = 0.375*de*sum;
	return sum;
}

void AttenuationSimPrimaryGeneratorAction::CreateCDFEnergy()
{
	G4double *prob = new G4double[nbins];
	G4int i;

	prob[0] = EIntegral(energy[0],energy[1]);
	for (i = 1; i < nbins-1; i++){
		prob[i] = prob[i-1] + EIntegral(energy[i],energy[i+1]);
	}
	prob[nbins-1] = prob[nbins-2] + EIntegral(energy[nbins-1],emax);
	for (i = 0; i < nbins; i++){
		prob[i] = prob[i]/prob[nbins-1];
	}
	CDFE = prob;
}

void AttenuationSimPrimaryGeneratorAction::CreateCDFZenith()
{
	G4double *prob = new G4double[nbins];
	G4int i;

	prob[0] = AIntegral(zenith[0],zenith[1]);
	for (i = 1; i < nbins-1; i++){
		prob[i] = prob[i-1] + AIntegral(zenith[i],zenith[i+1]);
	}
	prob[nbins-1] = prob[nbins-2] + AIntegral(zenith[nbins-1],zmax);
	for (i = 0; i < nbins; i++){
		prob[i] = prob[i]/prob[nbins-1];
	}
	CDFZ = prob;
}

void AttenuationSimPrimaryGeneratorAction::CreateCDFPhi()
{
	G4double *prob = new G4double[nbins];
	G4int i;

	prob[0] = AIntegral(phi[0],phi[1]);
	for (i = 1; i < nbins-1; i++){
		prob[i] = prob[i-1] + AIntegral(phi[i],phi[i+1]);
	}
	prob[nbins-1] = prob[nbins-2] + AIntegral(phi[nbins-1],pmax);
	for (i = 0; i < nbins; i++){
		prob[i] = prob[i]/prob[nbins-1];
	}
	CDFP = prob;
}

G4double AttenuationSimPrimaryGeneratorAction::GetEnergy() 
{
	G4double rand = G4UniformRand();
	G4double ene = 0.;

	G4int i;

	if (rand<CDFE[0]) {ene = energy[0]*GeV;}
	for (i = 1; i < nbins-1; i++){
		if (rand>=CDFE[i] && rand<CDFE[i+1]) {ene = energy[i]*GeV;}
	}
	if (rand==CDFE[nbins-1]) {ene = energy[nbins-1]*GeV;}
	return ene;
}

G4double AttenuationSimPrimaryGeneratorAction::GetZAngle()
{
	G4double rand = G4UniformRand();
	G4double ang = 0.;

	G4int i;

	if (rand<CDFZ[0]) {ang = zenith[0]*rad;}
	for (i = 1; i < nbins-1; i++){
		if (rand>=CDFZ[i] && rand<CDFZ[i+1]) {ang = zenith[i]*rad;}
	}
	if (rand==CDFZ[nbins-1]) {ang = zenith[nbins-1]*rad;}
	return ang;
}

G4double AttenuationSimPrimaryGeneratorAction::GetPAngle()
{
	G4double rand = G4UniformRand();
	G4double ang = 0.;

	G4int i;

	if (rand<CDFP[0]) {ang = phi[0]*rad;}
	for (i = 1; i < nbins-1; i++){
		if (rand>=CDFP[i] && rand<CDFP[i+1]) {ang = phi[i]*rad;}
	}
	if (rand==CDFP[nbins-1]) {ang = phi[nbins-1]*rad;}
	return ang;
}

void AttenuationSimPrimaryGeneratorAction::SetNewPositionAndMomentum(G4ThreeVector oldPosition)
{
	//This defines the area where the particles arrive
	G4ThreeVector position = G4ThreeVector(0.5*(2*G4UniformRand()-1.)*(0.5*cm)+(0.0), 0.5*(2*G4UniformRand()-1.)*(0.25*m), 0.5*(2*G4UniformRand()-1.)*(0.25*m));

	G4double r = sqrt(pow(oldPosition.x(),2)+pow(oldPosition.y(),2)+pow(oldPosition.z(),2));	
	G4double theta = GetZAngle();
	fZAngleBeam = theta;
	G4double phi_ang = GetPAngle();

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

void AttenuationSimPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void AttenuationSimPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
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
