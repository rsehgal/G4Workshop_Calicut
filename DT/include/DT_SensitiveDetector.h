#ifndef DT_SENSITIVEDETECTOR_HH
#define DT_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class DT_SensitiveDetector : public G4VSensitiveDetector {
public:
    DT_SensitiveDetector(const G4String& name);
    virtual ~DT_SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
