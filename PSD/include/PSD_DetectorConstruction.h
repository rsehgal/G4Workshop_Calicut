#ifndef PSD_DETECTORCONSTRUCTION_HH
#define PSD_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class PSD_DetectorConstruction : public G4VUserDetectorConstruction {
public:
    PSD_DetectorConstruction();
    virtual ~PSD_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
