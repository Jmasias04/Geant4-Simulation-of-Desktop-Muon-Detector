// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef AttenuationSimPrimaryGeneratorAction_h
#define AttenuationSimPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;
class AttenuationSimPrimaryGeneratorMessenger;

class AttenuationSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
 AttenuationSimPrimaryGeneratorAction();    
   ~AttenuationSimPrimaryGeneratorAction();

  public:
    void SetDefaultKinematic();
    void SetAngleBeam(G4double val) {fZAngleBeam = val;};   
    virtual void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() {return fParticleGun;};
void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);
	private: 
		G4double	MuonAngularDist(G4double);
		G4double	MuonEnergyDist(G4double); 

		G4double	EIntegral(G4double,G4double);
		G4double	AIntegral(G4double,G4double);
		void 			SetNewPositionAndMomentum(G4ThreeVector);
		void			CreateEnergyArray();
		void			CreateCDFEnergy();
		void			CreateZenithArray();
		void			CreateCDFZenith();
		void			CreatePhiArray();
		void			CreateCDFPhi();

		G4double	GetEnergy();
		G4double	GetZAngle();
		G4double	GetPAngle();

  private:
    G4ParticleGun*         				fParticleGun;
    G4double               				fZAngleBeam;

    AttenuationSimPrimaryGeneratorMessenger* 	fGunMessenger;

		G4double *energy, *zenith, *phi;
		G4double *CDFE, *CDFZ, *CDFP;
	
		G4int nbins;
		G4double	exp;
		G4double	ratio;
		G4double	eps;
		G4double	E0; 
		G4double	emin, emax, zmin, zmax, pmin, pmax;
};
#endif
