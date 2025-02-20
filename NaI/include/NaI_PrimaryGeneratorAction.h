#ifndef NaI_PRIMARYGENERATORACTION_HH
#define NaI_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class NaI_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    NaI_PrimaryGeneratorAction();
    virtual ~NaI_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
