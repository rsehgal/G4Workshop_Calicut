#ifndef EVENT_EVENTACTION_HH
#define EVENT_EVENTACTION_HH

#include "G4Event.hh"
#include "G4UserEventAction.hh"
class Event_EventAction : public G4UserEventAction {
  double eDep;

public:
  Event_EventAction();
  virtual ~Event_EventAction();
  virtual void BeginOfEventAction(const G4Event *event);
  virtual void EndOfEventAction(const G4Event *event);
  void AddEnergy(double val);
};

#endif
