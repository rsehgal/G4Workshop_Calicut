#ifndef NAI_PRIMARYGENERATORACTION_HH
#define NAI_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
class NaI_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
  G4ThreeVector fGunPos;
public:
    NaI_PrimaryGeneratorAction();
    virtual ~NaI_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
