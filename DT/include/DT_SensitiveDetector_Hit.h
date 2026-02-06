#ifndef DT_SENSITIVEDETECTOR_HIT_HH
#define DT_SENSITIVEDETECTOR_HIT_HH

#include "G4VHit.hh"

class DT_SensitiveDetector_Hit : public G4VHit {
public:
    DT_SensitiveDetector_Hit();
    virtual ~DT_SensitiveDetector_Hit();
};

#endif
