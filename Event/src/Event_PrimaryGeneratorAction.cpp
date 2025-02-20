#include "Event_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
Event_PrimaryGeneratorAction::Event_PrimaryGeneratorAction() {
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // Default we have setup geantino particles
  G4ParticleDefinition *particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -10 * cm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleEnergy(662 * keV);

  // TODO : Add your desired particles
}

Event_PrimaryGeneratorAction::~Event_PrimaryGeneratorAction() { delete fParticleGun; }

void Event_PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {

  // TODO :  Logic to change the particle position for each event

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
