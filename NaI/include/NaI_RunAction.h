#ifndef NAI_RUNACTION_HH
#define NAI_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
class NaI_RunAction : public G4UserRunAction {
   G4AnalysisManager *fAnalysisManager;
public:
    NaI_RunAction();
    virtual ~NaI_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
