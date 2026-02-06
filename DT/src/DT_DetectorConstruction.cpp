#include "DT_DetectorConstruction.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "DT_SensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserLimits.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
DT_DetectorConstruction::DT_DetectorConstruction() {}

DT_DetectorConstruction::~DT_DetectorConstruction() {}

G4VPhysicalVolume *DT_DetectorConstruction::Construct()
{
  G4NistManager *nist  = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

  // Modify the world volume dimension as required
  G4Box *solidWorld            = new G4Box("World", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld  = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

  // 1. Define Isotopes
  G4Isotope *iso_H3 = new G4Isotope("Tritium_Iso", 1, 3, 3.016 * g / mole);

  // 2. Define Element from Isotope
  G4Element *elTritium = new G4Element("Tritium_Element", "T", 1);
  elTritium->AddIsotope(iso_H3, 100 * perCent);

  // 3. Define Titanium Element (Standard)
  G4Element *elTi     = nist->FindOrBuildElement("Ti");

  // 4. Create Tritiated Titanium (TiT2)
  G4double density = 4.5 * g / cm3; // Approximated for TiT2
  G4Material *TiT2 = new G4Material("Tritium_Target", density, 2);
  TiT2->AddElement(elTi, 1);
  TiT2->AddElement(elTritium, 2); // Stoichiometric ratio 1:2

  G4Material *targetMat = TiT2;// worldMat;
  G4Material *cuFlangeMat = worldMat;
  G4Material *ssFlangeMat = worldMat;

  G4Box *target            = new G4Box("Target", 7.5 * mm, 7.5 * mm, 0.005 * mm);
  G4LogicalVolume *logicalTarget  = new G4LogicalVolume(target, targetMat, "LogicalTarget");
  logicalTarget->SetUserLimits(new G4UserLimits(0.001*mm));
  G4VPhysicalVolume *physicalTarget = new G4PVPlacement(nullptr, G4ThreeVector(), logicalTarget, "PhysicalTarget", logicWorld, false, 0,true);

  G4Box *cuFlange            = new G4Box("CuFlange", 50 * mm, 50 * mm, 2.5 * mm);
  G4LogicalVolume *logicalCuFlange  = new G4LogicalVolume(cuFlange, cuFlangeMat, "LogicalCuFlange");
  G4VPhysicalVolume *physicalCuFlange = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,2*cm), logicalCuFlange, "PhysicalCuFlange", logicWorld, false, 0,true);

  G4Box *ssFlange            = new G4Box("ssFlange", 50 * mm, 50 * mm, 2.5 * mm);
  G4LogicalVolume *logicalSSFlange  = new G4LogicalVolume(ssFlange, ssFlangeMat, "LogicalSSFlange");
  G4VPhysicalVolume *physicalSSFlange = new G4PVPlacement(nullptr, G4ThreeVector(0.,0.,5*cm), logicalSSFlange, "PhysicalSSFlange", logicWorld, false, 0,true);

  G4RotationMatrix* rot = new G4RotationMatrix();
  rot->rotateX(90.*deg);
  G4Tubs *scorer            = new G4Tubs("scorer", 12 * cm, 14 * cm, 5*cm,0. , 2*M_PI);
  G4LogicalVolume *logicalScorer  = new G4LogicalVolume(scorer, worldMat, "LogicalScorer");
  G4VPhysicalVolume *physicalScorer = new G4PVPlacement(rot, G4ThreeVector(0.,0.,0*cm), logicalScorer, "PhysicalScorer", logicWorld, false, 0,true);

  G4Tubs *dete            = new G4Tubs("Dete", 0, 4 * mm, 8*mm,0. , 2*M_PI);
  G4LogicalVolume *logicalDete  = new G4LogicalVolume(dete, worldMat, "LogicalDete");

int N=5;
for (G4int i = 0; i < N; i++) {
    G4double angle = i * 360./N * deg;

    // 1. Define Rotation: 
    // We rotate around Y to tilt the tube axis away from the global Z
    G4RotationMatrix* rot = new G4RotationMatrix();
    rot->rotateY(-1.*angle);
    double hz=18*cm;
    G4double x = hz * std::sin(angle);
    G4double z = hz * std::cos(angle);
    G4ThreeVector pos = G4ThreeVector(x, 0, z);
    //G4ThreeVector pos = G4ThreeVector(hz * std::sin(angle), 0, hz * std::cos(angle));
  new G4PVPlacement(rot, pos, logicalDete, "PhysicalDete", logicWorld, false, i,true);
}  
  // TODO : Create your desired detectors here

  // Logic to Attach sensitive detector to a logical volume
  DT_SensitiveDetector* detector = new DT_SensitiveDetector("SensitiveDetector");
  G4SDManager::GetSDMpointer()->AddNewDetector(detector);
  logicalScorer->SetSensitiveDetector(detector);

  return physWorld;
}
