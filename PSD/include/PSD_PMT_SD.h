#ifndef PSD_PMT_SD_HH
#define PSD_PMT_SD_HH

#include "G4HCofThisEvent.hh"
#include "G4VSensitiveDetector.hh"
#include "PSD_HitCollections.h"

class PSD_PMT_SD : public G4VSensitiveDetector {
  PmtHitCollection *fPmtHitCollection_1;
  int fPmtHitCollectionID_1;

public:
  PSD_PMT_SD(const G4String &name);
  PSD_PMT_SD(const G4String &name, const G4String &collName);
  virtual ~PSD_PMT_SD();
  virtual void Initialize(G4HCofThisEvent *hce);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hce);
};

#endif
