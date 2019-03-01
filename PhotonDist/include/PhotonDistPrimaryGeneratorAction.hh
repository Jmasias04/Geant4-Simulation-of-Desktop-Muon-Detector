// ********************************************
// ***************** HEP-PUCP *****************
// ********************************************

#ifndef PhotonDistPrimaryGeneratorAction_h
#define PhotonDistPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;
class PhotonDistPrimaryGeneratorMessenger;

class PhotonDistPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
 PhotonDistPrimaryGeneratorAction();    
   ~PhotonDistPrimaryGeneratorAction();

  public:
    void SetDefaultKinematic();
    void SetAngleBeam(G4double val) {fZAngleBeam = val;};   
    virtual void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() {return fParticleGun;};
void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);
	private: 

		G4double	GetEnergy();
		void 			SetNewPositionAndMomentum(G4ThreeVector);

  private:
    G4ParticleGun*         				fParticleGun;
    G4double               				fZAngleBeam;

    PhotonDistPrimaryGeneratorMessenger* 	fGunMessenger;

};
#endif
