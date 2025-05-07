#ifndef PSD_RUNACTION_HH
#define PSD_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
class PSD_RunAction : public G4UserRunAction {
public:
    PSD_RunAction();
    virtual ~PSD_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
