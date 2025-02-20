#ifndef EVENT_SENSITIVEDETECTOR_HH
#define EVENT_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"

class Event_SensitiveDetector : public G4VSensitiveDetector {
public:
    Event_SensitiveDetector(const G4String& name);
    virtual ~Event_SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};

#endif
