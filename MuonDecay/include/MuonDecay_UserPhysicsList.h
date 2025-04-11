#ifndef MUONDECAY_USERPHYSICSLIST_HH
#define MUONDECAY_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class MuonDecay_UserPhysicsList : public G4VUserPhysicsList {
public:
    MuonDecay_UserPhysicsList();
    virtual ~MuonDecay_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
