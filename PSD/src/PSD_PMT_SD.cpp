#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "PSD_HitCollections.h"
#include "PSD_PMT_Hit.h"
#include "PSD_PMT_SD.h"
PSD_PMT_SD::PSD_PMT_SD(const G4String &name)
    : G4VSensitiveDetector(name), fPmtHitCollection_1(nullptr), fPmtHitCollectionID_1(-1) {
  collectionName.insert("pmtHitCollection_1");
}
PSD_PMT_SD::PSD_PMT_SD(const G4String &name, const G4String &collName) : G4VSensitiveDetector(name) {
  collectionName.insert(collName);
}

PSD_PMT_SD::~PSD_PMT_SD() {}

void PSD_PMT_SD::Initialize(G4HCofThisEvent *hce) {
  fPmtHitCollection_1 = new PmtHitCollection(SensitiveDetectorName, collectionName[0]);
  fPmtHitCollectionID_1 = GetCollectionID(0);
  hce->AddHitsCollection(fPmtHitCollectionID_1, fPmtHitCollection_1);
}

G4bool PSD_PMT_SD::ProcessHits(G4Step *step, G4TouchableHistory *) {
  G4Track *track = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  PSD_PMT_Hit *newHit = new PSD_PMT_Hit;
  newHit->SetArrivalTime(track->GetGlobalTime());
  // G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
  fPmtHitCollection_1->insert(newHit);
  newHit->Print();
  // track->SetTrackStatus(fStopAndKill);
  return true;
}

void PSD_PMT_SD::EndOfEvent(G4HCofThisEvent *hce) {
  std::cout << "No. of Photon detected in PMT : " << fPmtHitCollection_1->entries() << std::endl;
}
