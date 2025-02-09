#include "Tracking_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"

short Tracking_PrimaryGeneratorAction::fGunType = 0;

Tracking_PrimaryGeneratorAction::Tracking_PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //Default we have setup geantino particles
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0 * GeV);
    
    
    // TODO : Add your desired particles
}

Tracking_PrimaryGeneratorAction::~Tracking_PrimaryGeneratorAction() {
    delete fParticleGun;
}

void Tracking_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    
    //TODO :  Logic to change the particle position for each event
    //Changing particle position within a square of 5 cm x 5 cm
    G4double randX = -5.0 * cm + 10.0 * cm * G4UniformRand();
    G4double randY = -5.0 * cm + 10.0 * cm * G4UniformRand();
    G4ThreeVector pos(randX,randY,-200*cm);
    if(fGunType==0){
	fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("mu-"));
        fGunType = 1;
    }
    else{
	fParticleGun->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("mu+"));
	fGunType = 0;
    }
    fParticleGun->SetParticlePosition(pos);
       
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
