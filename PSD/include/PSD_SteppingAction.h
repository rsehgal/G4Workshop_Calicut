#ifndef PSD_STEPPINGACTION_HH
#define PSD_STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class PSD_SteppingAction : public G4UserSteppingAction {
public:
    PSD_SteppingAction();
    virtual ~PSD_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
