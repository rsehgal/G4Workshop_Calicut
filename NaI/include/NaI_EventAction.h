#ifndef NAI_EVENTACTION_HH
#define NAI_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class NaI_EventAction : public G4UserEventAction {
public:
    NaI_EventAction();
    virtual ~NaI_EventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
