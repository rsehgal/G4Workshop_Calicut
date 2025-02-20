#ifndef NaI_DETECTORCONSTRUCTION_HH
#define NaI_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class NaI_DetectorConstruction : public G4VUserDetectorConstruction {
public:
    NaI_DetectorConstruction();
    virtual ~NaI_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
