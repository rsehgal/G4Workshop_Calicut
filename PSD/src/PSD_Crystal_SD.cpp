#include "PSD_Crystal_SD.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

PSD_Crystal_SD::PSD_Crystal_SD(const G4String &name, const G4String &collName)
    : G4VSensitiveDetector(name), fCrystalEDep(0)
{
  collectionName.insert(collName);
}

PSD_Crystal_SD::~PSD_Crystal_SD() {}

void PSD_Crystal_SD::Initialize(G4HCofThisEvent *hce)
{
  fCrystalEDep = 0.;
}

G4bool PSD_Crystal_SD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  G4Track *track  = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  G4double edep   = step->GetTotalEnergyDeposit();
  fCrystalEDep += edep;
  // G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
  #ifdef VERBOSE
  if (track->GetTrackID() == 1) std::cout << "Particle : " << track->GetDefinition()->GetParticleName() << " : Energy : " << track->GetVertexKineticEnergy() << std::endl;
  #endif
  return true;
}

void PSD_Crystal_SD::EndOfEvent(G4HCofThisEvent *hce)
{
#ifdef VERBOSE
  std::cout << "======================================" << std::endl;
#endif
  // std::cout << "Total energy deposited in crystal : " << fCrystalEDep << std::endl;
}
