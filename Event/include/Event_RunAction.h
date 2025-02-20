#ifndef EVENT_RUNACTION_HH
#define EVENT_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
class Event_RunAction : public G4UserRunAction {
public:
    Event_RunAction();
    virtual ~Event_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
