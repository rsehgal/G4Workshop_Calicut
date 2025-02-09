#ifndef TRACKING_DETECTORCONSTRUCTION_HH
#define TRACKING_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class Tracking_DetectorConstruction : public G4VUserDetectorConstruction {
private:
  static G4bool fieldIsInitialized;
  G4LogicalVolume* GetLogicalVolumeByName(const G4String& name);

public:
    Tracking_DetectorConstruction();
    virtual ~Tracking_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
};

#endif
