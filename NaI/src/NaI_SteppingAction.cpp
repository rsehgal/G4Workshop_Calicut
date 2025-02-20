#include "NaI_EventAction.h"
#include "NaI_SteppingAction.h"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4UserEventAction.hh"

NaI_SteppingAction::NaI_SteppingAction() {}

NaI_SteppingAction::~NaI_SteppingAction() {}

void NaI_SteppingAction::UserSteppingAction(const G4Step *step) {
  G4Track *track = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  // G4cout << "Energy: " << energy / MeV << " MeV" << G4endl;

  G4UserEventAction *evAction = const_cast<G4UserEventAction *>(G4RunManager::GetRunManager()->GetUserEventAction());
  NaI_EventAction *myEvAction = static_cast<NaI_EventAction *>(evAction);
  if (track->GetVolume()->GetName() == "PhysicalNaI") {
    myEvAction->AddEnergy(step->GetTotalEnergyDeposit());
  }
}
