#include "NaI_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"

NaI_PrimaryGeneratorAction::NaI_PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
    fGunPos = G4ThreeVector(0.,0.,-6*cm);
    //Default we have setup geantino particles
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticlePosition(fGunPos);
    fParticleGun->SetParticleEnergy(1.0 * MeV);
    
    
    // TODO : Add your desired particles
}

NaI_PrimaryGeneratorAction::~NaI_PrimaryGeneratorAction() {
    delete fParticleGun;
}

void NaI_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {


    //TODO :  Logic to change the particle position for each event
    double fullRadius = 2.85*cm;
    double randomRad = G4UniformRand()*fullRadius;
    double randomPhi = G4UniformRand()*2*M_PI;
    double xposOnDis = randomRad*cos(randomPhi);
    double yposOnDis = randomRad*sin(randomPhi);
    double zposOnDis = -2.8*cm;
    G4ThreeVector randPosOnDis(xposOnDis,yposOnDis,zposOnDis);
    G4ThreeVector dir = (randPosOnDis-fGunPos).unit();
         
    //fParticleGun->SetParticleMomentumDirection(dir);
        
   
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
