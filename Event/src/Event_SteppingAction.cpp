#include "Event_EventAction.h"
#include "Event_SteppingAction.h"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4UserEventAction.hh"
Event_SteppingAction::Event_SteppingAction() {}

Event_SteppingAction::~Event_SteppingAction() {}

void Event_SteppingAction::UserSteppingAction(const G4Step *step) {
  G4Track *track = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  // G4cout << "Energy: " << energy / MeV << " MeV" << G4endl;

  G4UserEventAction *evAction = const_cast<G4UserEventAction *>(G4RunManager::GetRunManager()->GetUserEventAction());
  Event_EventAction *myEvAction = static_cast<Event_EventAction *>(evAction);
  myEvAction->AddEnergy(step->GetTotalEnergyDeposit());
}
