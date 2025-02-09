#ifndef TRACKING_SENSITIVEDETECTOR_HIT_HH
#define TRACKING_SENSITIVEDETECTOR_HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
class Tracking_SensitiveDetector_Hit : public G4VHit {
private:
    G4ThreeVector fPosition;
    G4String fVolumeName;
    G4ThreeVector fMomentumDirection;
    G4int fLayerNo;
public:
    Tracking_SensitiveDetector_Hit();
    Tracking_SensitiveDetector_Hit(G4ThreeVector pos, G4ThreeVector momDir, G4String name);
    virtual ~Tracking_SensitiveDetector_Hit();

    void SetPosition(G4ThreeVector pos);
    void SetMomentumDirection(G4ThreeVector momDir);
    void SetVolumeName(G4String name);
    void Set(G4ThreeVector pos, G4ThreeVector momDir, G4String name);
    void Set(G4ThreeVector pos, G4ThreeVector momDir, G4String name, G4int layerNo);

    G4ThreeVector GetPosition() const;
    G4ThreeVector GetMomentumDirection() const;
    G4String GetVolumeName() const;
    G4int GetLayerNo() const;

    void Print();
};

#endif
