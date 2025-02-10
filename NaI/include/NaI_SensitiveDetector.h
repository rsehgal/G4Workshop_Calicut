#ifndef NAI_SENSITIVEDETECTOR_HH
#define NAI_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "TFile.h"
#include "TF1.h"

class G4HCofThisEvent;
class G4LogicalVolume;

class NaI_SensitiveDetector : public G4VSensitiveDetector {

  double fEDep;
  TF1 *fResolFun;
public:
  NaI_SensitiveDetector(const G4String &name);
  NaI_SensitiveDetector(const G4String &name, G4LogicalVolume *sensitiveVolume);
  virtual ~NaI_SensitiveDetector();

  virtual void Initialize(G4HCofThisEvent *hce);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hce);
};

#endif
