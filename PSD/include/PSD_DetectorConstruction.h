#ifndef PSD_DETECTORCONSTRUCTION_HH
#define PSD_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"

class PSD_DetectorConstruction : public G4VUserDetectorConstruction {
public:
    PSD_DetectorConstruction();
    virtual ~PSD_DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    G4Material* GetScintillatorWithPSD();

    G4MaterialPropertiesTable* GetMPT();
};

#endif
