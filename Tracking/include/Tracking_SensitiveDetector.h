#ifndef TRACKING_SENSITIVEDETECTOR_HH
#define TRACKING_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "HitsCollections.h"

class G4HCofThisEvent;

class Tracking_SensitiveDetector : public G4VSensitiveDetector {
private : 
    LayersHitsCollection *fLayersHitsCollection;
public:
    Tracking_SensitiveDetector(const G4String& name, const G4String collName);
    virtual void Initialize(G4HCofThisEvent *hcofThisEvent);
    virtual ~Tracking_SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
