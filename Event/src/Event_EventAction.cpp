#include "Event_EventAction.h"

Event_EventAction::Event_EventAction() {}

Event_EventAction::~Event_EventAction() {}

void Event_EventAction::BeginOfEventAction(const G4Event *event) {
  // TODO : All the required logic you want to do at the start
  //        of each event
  eDep = 0;
}

void Event_EventAction::EndOfEventAction(const G4Event *event) {
  // TODO : All the required logic you want to do at the end
  //        of each event

  std::cout << "Total Energy deposited in event : " << event->GetEventID() << " : " << eDep << std::endl;
}

void Event_EventAction::AddEnergy(double val) { eDep += val; }
