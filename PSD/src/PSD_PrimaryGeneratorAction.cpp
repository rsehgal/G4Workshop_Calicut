#include "PSD_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

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

  double radius = G4RandFlat::shoot(0.,5.*cm);
  double angle = G4RandFlat::shoot(0.,2*M_PI);
  double xval = radius*cos(angle);
  double yval = radius*sin(angle);
  double zval = 0.;
  G4ThreeVector currentPos = fParticleGun->GetParticlePosition();
  G4ThreeVector endPos=G4ThreeVector(xval,yval,zval);
  G4ThreeVector dir = (endPos-currentPos).unit();
  fParticleGun->SetParticleMomentumDirection(dir);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
