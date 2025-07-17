#ifndef PSD_CRYSTAL_SD_HH
#define PSD_CRYSTAL_SD_HH

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"

class PSD_Crystal_SD : public G4VSensitiveDetector {
   double fCrystalEDep;
public:
    PSD_Crystal_SD(const G4String& name, const G4String &collName);
    virtual ~PSD_Crystal_SD();
    virtual void Initialize(G4HCofThisEvent *hce);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent *hce);
    
};

#endif
