/*
**	Filename : Tracking_MagneticField.h
**	2025-02-01
**	username : rsehgal
*/
#ifndef Tracking_MagneticField_h
#define Tracking_MagneticField_h

#include "G4MagneticField.hh"
#include "G4SystemOfUnits.hh"

class Tracking_MagneticField : public G4MagneticField {
public:
    Tracking_MagneticField(G4ThreeVector field) : fFieldValue(field) {}
    virtual ~Tracking_MagneticField() {}

    void GetFieldValue(const G4double[4], G4double *Bfield) const override {
        Bfield[0] = fFieldValue.x();
        Bfield[1] = fFieldValue.y();
        Bfield[2] = fFieldValue.z();
    }

private:
    G4ThreeVector fFieldValue;
};


#endif
