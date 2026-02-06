#ifndef DT_STEPPINGACTION_HH
#define DT_STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class DT_SteppingAction : public G4UserSteppingAction {
public:
    DT_SteppingAction();
    virtual ~DT_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
