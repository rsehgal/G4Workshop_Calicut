#ifndef PSD_USERPHYSICSLIST_HH
#define PSD_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class PSD_UserPhysicsList : public G4VUserPhysicsList {
public:
    PSD_UserPhysicsList();
    virtual ~PSD_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
