#include "PSD_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
PSD_PrimaryGeneratorAction::PSD_PrimaryGeneratorAction()
{
  G4int n_particle               = 1;
  fParticleGun                   = new G4ParticleGun(n_particle);
  G4ParticleDefinition *particle = nullptr;
#ifdef FOR_GAMMA
  // Default we have setup geantino particles
  particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
#elif defined(FOR_NEUTRON)
  particle = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
#endif

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
  fParticleGun->SetParticleEnergy(1.0 * MeV);

  // TODO : Add your desired particles
}

PSD_PrimaryGeneratorAction::~PSD_PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PSD_PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{

  // TODO :  Logic to change the particle position for each event

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
