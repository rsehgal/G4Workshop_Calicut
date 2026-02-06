#ifndef DT_USERPHYSICSLIST_HH
#define DT_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class DT_UserPhysicsList : public G4VUserPhysicsList {
public:
    DT_UserPhysicsList();
    virtual ~DT_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
