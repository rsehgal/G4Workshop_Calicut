#ifndef PSD_EVENTACTION_HH
#define PSD_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "PSD_RunAction.h"
class PSD_EventAction : public G4UserEventAction {
    PSD_RunAction *fRunAction;
public:
    PSD_EventAction();
    virtual ~PSD_EventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
};

#endif
