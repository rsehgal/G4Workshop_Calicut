#ifndef TRACKING_RUNACTION_HH
#define TRACKING_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

class Tracking_RunAction : public G4UserRunAction {
private:
    G4AnalysisManager *fAnalMan;
public:
    Tracking_RunAction();
    virtual ~Tracking_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif
