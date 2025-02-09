#ifndef TRACKING_USERPHYSICSLIST_HH
#define TRACKING_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class Tracking_UserPhysicsList : public G4VUserPhysicsList {
public:
    Tracking_UserPhysicsList();
    virtual ~Tracking_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
