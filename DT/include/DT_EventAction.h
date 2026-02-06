#ifndef DT_EVENTACTION_HH
#define DT_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class DT_EventAction : public G4UserEventAction {
public:
    DT_EventAction();
    virtual ~DT_EventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
