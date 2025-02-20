#include "NaI_DetectorConstruction.h"
#include "NaI_SensitiveDetector.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

NaI_DetectorConstruction::NaI_DetectorConstruction() {}

NaI_DetectorConstruction::~NaI_DetectorConstruction() {}

G4VPhysicalVolume *NaI_DetectorConstruction::Construct() {
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material *nai = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

  // Modify the world volume dimension as required
  G4Box *solidWorld = new G4Box("World", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

  // TODO : Create your desired detectors here
  double dia = 5.7 * cm;
  double height = 5.3 * cm;
  G4Tubs *solidNai = new G4Tubs("Nai", 0, dia / 2., height / 2, 0, 2 * M_PI);
  G4LogicalVolume *logicNai = new G4LogicalVolume(solidNai, nai, "LogicalNai");
  G4VPhysicalVolume *physNai =
      new G4PVPlacement(nullptr, G4ThreeVector(), logicNai, "PhysicalNaI", logicWorld, false, 0, true);

  // Logic to Attach sensitive detector to a logical volume
  // NaI_SensitiveDetector* detector = new NaI_SensitiveDetector("SensitiveDetector");
  // G4SDManager::GetSDMpointer()->AddNewDetector(detector);
  // logicWorld->SetSensitiveDetector(detector);

  return physWorld;
}
