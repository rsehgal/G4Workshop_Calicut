#ifndef EVENT_DETECTORCONSTRUCTION_HH
#define EVENT_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class Event_DetectorConstruction : public G4VUserDetectorConstruction {
public:
    Event_DetectorConstruction();
    virtual ~Event_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
