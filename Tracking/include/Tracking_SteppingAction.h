#ifndef TRACKING_STEPPINGACTION_HH
#define TRACKING_STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class Tracking_SteppingAction : public G4UserSteppingAction {
public:
    Tracking_SteppingAction();
    virtual ~Tracking_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
