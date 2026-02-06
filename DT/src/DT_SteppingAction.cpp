#include "DT_SteppingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
DT_SteppingAction::DT_SteppingAction() {}

DT_SteppingAction::~DT_SteppingAction() {}

void DT_SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    //G4cout << "Energy: " << energy / MeV << " MeV" << G4endl;
}
