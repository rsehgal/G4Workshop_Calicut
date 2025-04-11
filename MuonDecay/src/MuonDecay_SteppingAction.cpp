#include "MuonDecay_SteppingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "MuonDecay_EventAction.h"
MuonDecay_SteppingAction::MuonDecay_SteppingAction() {}

MuonDecay_SteppingAction::~MuonDecay_SteppingAction() {}

void MuonDecay_SteppingAction::UserSteppingAction(const G4Step *step)
{
  G4Track *track  = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  // G4cout << "Energy: " << energy / MeV << " MeV" << G4endl;

  //MuonDecay_EventAction::muonStopped = false;
  //MuonDecay_EventAction::muonDecayed = false;
  if (track->GetVolume()->GetName() == "PhysicalScint") {
    if (track->GetParentID() == 0 && !MuonDecay_EventAction::muonStopped) {
      if (track->GetKineticEnergy() < 1 * eV) {
        MuonDecay_EventAction::muonStopped = true;
        std::cout << "Particle : " << track->GetDefinition()->GetParticleName()
                  << " : TrackID : " << track->GetTrackID() << " : ParentID : " << track->GetParentID()
                  << " : Energy : " << (track->GetKineticEnergy() / MeV)
                  << " : Time : " << (track->GetGlobalTime() / ns) << " : Creator : RAMAN" << std::endl;
      }
    } else if (!MuonDecay_EventAction::muonDecayed && track->GetParentID()>0) {
      if (track->GetCreatorProcess()->GetProcessName() == "Decay" &&
          (track->GetDefinition()->GetParticleName() == "e+" || track->GetDefinition()->GetParticleName() == "e-")) {
	MuonDecay_EventAction::muonDecayed = true;
        std::cout << "Particle : " << track->GetDefinition()->GetParticleName()
                  << " : TrackID : " << track->GetTrackID() << " : ParentID : " << track->GetParentID()
                  << " : Energy : " << (track->GetKineticEnergy() / MeV)
                  << " : Time : " << (track->GetGlobalTime() / ns)
                  << " : Creator : " << track->GetCreatorProcess()->GetProcessName() << std::endl;
      }
    }
  }
}
