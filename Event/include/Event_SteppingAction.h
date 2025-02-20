#ifndef EVENT_STEPPINGACTION_HH
#define EVENT_STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class Event_SteppingAction : public G4UserSteppingAction {
public:
    Event_SteppingAction();
    virtual ~Event_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
