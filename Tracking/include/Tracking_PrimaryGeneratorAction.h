#ifndef TRACKING_PRIMARYGENERATORACTION_HH
#define TRACKING_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class Tracking_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    Tracking_PrimaryGeneratorAction();
    virtual ~Tracking_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;

    static short fGunType;
};

#endif
