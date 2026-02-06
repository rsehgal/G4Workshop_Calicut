#include "DT_SensitiveDetector.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
DT_SensitiveDetector::DT_SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {}

DT_SensitiveDetector::~DT_SensitiveDetector() {}

G4bool DT_SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4AnalysisManager *analMan = G4AnalysisManager::Instance();
    G4double energy = track->GetKineticEnergy();
    G4cout << "DetectedNeutron energy: " << energy / MeV << " MeV" << G4endl;
    analMan->FillNtupleDColumn(0,0,energy);
    analMan->AddNtupleRow(0);
    track->SetTrackStatus(fStopAndKill);
    //TODO :  Add Whatall information you want to get from steps
    return true;
}
