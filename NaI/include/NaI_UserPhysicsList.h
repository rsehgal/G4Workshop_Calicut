#ifndef NaI_USERPHYSICSLIST_HH
#define NaI_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class NaI_UserPhysicsList : public G4VUserPhysicsList {
public:
    NaI_UserPhysicsList();
    virtual ~NaI_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
