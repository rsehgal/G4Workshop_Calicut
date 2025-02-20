#ifndef EVENT_SENSITIVEDETECTOR_HIT_HH
#define EVENT_SENSITIVEDETECTOR_HIT_HH

#include "G4VHit.hh"

class Event_SensitiveDetector_Hit : public G4VHit {
public:
    Event_SensitiveDetector_Hit();
    virtual ~Event_SensitiveDetector_Hit();
};

#endif
