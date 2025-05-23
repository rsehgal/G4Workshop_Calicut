#ifndef PSD_RUNACTION_HH
#define PSD_RUNACTION_HH

class G4Run;

#include "G4UserRunAction.hh"
#include "G4Event.hh"
#include <vector>
class PSD_RunAction : public G4UserRunAction {
   char *fOutfileName;
   std::vector<int> fPulse;
public:
    PSD_RunAction();
    PSD_RunAction(char *filename);
    virtual ~PSD_RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
    void FillPulse(std::vector<int> pulse);
};

#endif
