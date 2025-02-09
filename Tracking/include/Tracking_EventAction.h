#ifndef TRACKING_EVENTACTION_HH
#define TRACKING_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class Tracking_EventAction : public G4UserEventAction {
public:
    Tracking_EventAction();
    virtual ~Tracking_EventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
