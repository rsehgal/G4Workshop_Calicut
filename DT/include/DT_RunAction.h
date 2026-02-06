#ifndef DT_RUNACTION_HH
#define DT_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
class DT_RunAction : public G4UserRunAction {
public:
    DT_RunAction();
    virtual ~DT_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
