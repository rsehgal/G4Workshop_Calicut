#ifndef DT_PRIMARYGENERATORACTION_HH
#define DT_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class DT_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    DT_PrimaryGeneratorAction();
    virtual ~DT_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
