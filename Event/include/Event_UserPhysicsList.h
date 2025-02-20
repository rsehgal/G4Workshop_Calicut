#ifndef EVENT_USERPHYSICSLIST_HH
#define EVENT_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class Event_UserPhysicsList : public G4VUserPhysicsList {
public:
    Event_UserPhysicsList();
    virtual ~Event_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
