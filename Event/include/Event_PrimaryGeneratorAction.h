#ifndef EVENT_PRIMARYGENERATORACTION_HH
#define EVENT_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class Event_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    Event_PrimaryGeneratorAction();
    virtual ~Event_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
