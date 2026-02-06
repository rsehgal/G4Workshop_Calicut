#include "DT_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
DT_PrimaryGeneratorAction::DT_PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    //Default we have setup geantino particles
    /*G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("geantino");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(1.0 * MeV);
    */
    
    // TODO : Add your desired particles
}

DT_PrimaryGeneratorAction::~DT_PrimaryGeneratorAction() {
    delete fParticleGun;
}

void DT_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    
    // Define the Deuteron
    G4ParticleDefinition* particle = particleTable->FindParticle("deuteron");
    
    fParticleGun->SetParticleDefinition(particle);
    
    // Typical D-T resonance energy is around 100-110 keV
    fParticleGun->SetParticleEnergy(200.0 * keV);
    
    // Direction along the Z-axis
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    
    // Position (just in front of the target)
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -5.*cm));

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
/*void DT_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    
    //TODO :  Logic to change the particle position for each event
   
    fParticleGun->GeneratePrimaryVertex(anEvent);
}*/
