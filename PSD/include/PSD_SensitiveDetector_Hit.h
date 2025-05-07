#ifndef PSD_SENSITIVEDETECTOR_HIT_HH
#define PSD_SENSITIVEDETECTOR_HIT_HH

#include "G4VHit.hh"

class PSD_SensitiveDetector_Hit : public G4VHit {
public:
    PSD_SensitiveDetector_Hit();
    virtual ~PSD_SensitiveDetector_Hit();
};

#endif
