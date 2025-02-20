#include "NaI_SensitiveDetector.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

NaI_SensitiveDetector::NaI_SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {}

NaI_SensitiveDetector::~NaI_SensitiveDetector() {}

G4bool NaI_SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
    
    //TODO :  Add Whatall information you want to get from steps
    return true;
}
