#ifndef PSD_EVENTACTION_HH
#define PSD_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class PSD_EventAction : public G4UserEventAction {
public:
    PSD_EventAction();
    virtual ~PSD_EventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
