#ifndef DT_DETECTORCONSTRUCTION_HH
#define DT_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class DT_DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DT_DetectorConstruction();
    virtual ~DT_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
