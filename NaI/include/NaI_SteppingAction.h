#ifndef NaI_STEPPINGACTION_HH
#define NaI_STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class NaI_SteppingAction : public G4UserSteppingAction {
public:
    NaI_SteppingAction();
    virtual ~NaI_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
