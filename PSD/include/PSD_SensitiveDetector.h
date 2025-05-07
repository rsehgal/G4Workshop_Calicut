#ifndef PSD_SENSITIVEDETECTOR_HH
#define PSD_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class PSD_SensitiveDetector : public G4VSensitiveDetector {
public:
    PSD_SensitiveDetector(const G4String& name);
    virtual ~PSD_SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
