#include "MuonDecay_SteppingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "MuonDecay_EventAction.h"
#include "G4AnalysisManager.hh"
MuonDecay_SteppingAction::MuonDecay_SteppingAction() {}

MuonDecay_SteppingAction::~MuonDecay_SteppingAction() {}

void MuonDecay_SteppingAction::UserSteppingAction(const G4Step *step)
{
  G4Track *track  = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  // G4cout << "Energy: " << energy / MeV << " MeV" << G4endl;

  // MuonDecay_EventAction::muonStopped = false;
  // MuonDecay_EventAction::muonDecayed = false;
  if (track->GetVolume()->GetName() == "PhysicalScint") {
    if (track->GetParentID() == 0 && !MuonDecay_EventAction::muonStopped) {
      if (track->GetKineticEnergy() < 1 * eV) {
        MuonDecay_EventAction::muonStopped  = true;
        MuonDecay_EventAction::muonStopTime = (track->GetGlobalTime() / ns);
#ifdef VERBOSE
        std::cout << "Particle : " << track->GetDefinition()->GetParticleName()
                  << " : TrackID : " << track->GetTrackID() << " : ParentID : " << track->GetParentID()
                  << " : Energy : " << (track->GetKineticEnergy() / MeV)
                  << " : Time : " << (track->GetGlobalTime() / ns) << " : Creator : RAMAN" << std::endl;
#endif
      }
    } else if (!MuonDecay_EventAction::muonDecayed && track->GetParentID() > 0) {
      // If the muon is stopped then detecting the decay time, by detecting the creator process is "Decay"
      // and the decayed product is e+ or e-
      if (track->GetCreatorProcess()->GetProcessName() == "Decay" &&
          (track->GetDefinition()->GetParticleName() == "e+" || track->GetDefinition()->GetParticleName() == "e-")) {
        MuonDecay_EventAction::muonDecayed   = true;
        MuonDecay_EventAction::muonDecayTime = (track->GetGlobalTime() / ns);
#ifdef VERBOSE
        std::cout << "Particle : " << track->GetDefinition()->GetParticleName()
                  << " : TrackID : " << track->GetTrackID() << " : ParentID : " << track->GetParentID()
                  << " : Energy : " << (track->GetKineticEnergy() / MeV)
                  << " : Time : " << (track->GetGlobalTime() / ns)
                  << " : Creator : " << track->GetCreatorProcess()->GetProcessName() << std::endl;
#endif
      }
    }

    G4AnalysisManager *analMan = G4AnalysisManager::Instance();
    if (MuonDecay_EventAction::muonStopped && MuonDecay_EventAction::muonDecayed) {
      analMan->FillNtupleDColumn(0, 0, MuonDecay_EventAction::muonStopTime);
      analMan->FillNtupleDColumn(0, 1, MuonDecay_EventAction::muonDecayTime);
      analMan->FillNtupleDColumn(0, 2, MuonDecay_EventAction::muonDecayTime - MuonDecay_EventAction::muonStopTime);
      analMan->AddNtupleRow(0);
    }
  }
}
