#ifndef PSD_PRIMARYGENERATORACTION_HH
#define PSD_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class PSD_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PSD_PrimaryGeneratorAction();
    virtual ~PSD_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
