#ifndef NaI_SENSITIVEDETECTOR_HH
#define NaI_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class NaI_SensitiveDetector : public G4VSensitiveDetector {
public:
    NaI_SensitiveDetector(const G4String& name);
    virtual ~NaI_SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
