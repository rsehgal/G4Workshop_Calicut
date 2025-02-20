#ifndef NaI_EVENTACTION_HH
#define NaI_EVENTACTION_HH

#include "G4Event.hh"
#include "G4UserEventAction.hh"
class NaI_EventAction : public G4UserEventAction {
  double eDep;

public:
  NaI_EventAction();
  virtual ~NaI_EventAction();
  virtual void BeginOfEventAction(const G4Event *event);
  virtual void EndOfEventAction(const G4Event *event);
  void AddEnergy(double val);
};

#endif
