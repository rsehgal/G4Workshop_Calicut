#include "NaI_DetectorConstruction.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "NaI_SensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

NaI_DetectorConstruction::NaI_DetectorConstruction() {}

NaI_DetectorConstruction::~NaI_DetectorConstruction() {}

G4VPhysicalVolume *NaI_DetectorConstruction::Construct()
{
  G4NistManager *nist  = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  // Modify the world volume dimension as required
  G4Box *solidWorld            = new G4Box("World", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld  = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

  

  // TODO : Create your desired detectors here
  double crystalDia = 5.7 * cm;
  double crystalHeight = 8 * cm;
  G4Material *naiMaterial = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4Tubs *naiCrystal   = new G4Tubs("NaiCrystal", 0., crystalDia/2., crystalHeight / 2., 0, 2 * M_PI);
  G4LogicalVolume *logicalNaiCrystal = new G4LogicalVolume(naiCrystal,naiMaterial,"LogicalNaiCrystal");
  new G4PVPlacement(nullptr,G4ThreeVector(),logicalNaiCrystal,"PhysicalNaiCrystal",logicWorld,false,0,true); 
  //Lets also create encasing of crystal
  G4Material *naiCasingMaterial = nist->FindOrBuildMaterial("G4_Al");
  G4Tubs *naiCrystalCasing   = new G4Tubs("NaiCrystalCasing", crystalDia/2.+0.5*mm, crystalDia/2.+1.5*mm, crystalHeight / 2., 0, 2 * M_PI);
  G4LogicalVolume *logicalNaiCrystalCasing = new G4LogicalVolume(naiCrystalCasing,naiCasingMaterial,"LogicalNaiCrystalCasing");
  new G4PVPlacement(nullptr,G4ThreeVector(),logicalNaiCrystalCasing,"PhysicalNaiCrystalCasing",logicWorld,false,0,true); 

  //End Caps
  double endCapHeight=1.*mm;
 G4Tubs *naiCrystalCasingEndCap   = new G4Tubs("NaiCrystalCasing",0. , crystalDia/2.+1.5*mm, endCapHeight / 2., 0, 2 * M_PI);
  G4LogicalVolume *logicalNaiCrystalCasingEndCap = new G4LogicalVolume(naiCrystalCasingEndCap,naiCasingMaterial,"LogicalNaiCrystalCasingEndCap");
  new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,-1.*(crystalHeight/2.+endCapHeight/2.+0.00001)),logicalNaiCrystalCasingEndCap,"PhysicalNaiCrystalCasingEndCap",logicWorld,false,0,true); 
  new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,(crystalHeight/2.+endCapHeight/2.+0.00001)),logicalNaiCrystalCasingEndCap,"PhysicalNaiCrystalCasingEndCap",logicWorld,false,1,true); 


  // Logic to Attach sensitive detector to a logical volume
  // NaI_SensitiveDetector* detector = new NaI_SensitiveDetector("SensitiveDetector");
  // G4SDManager::GetSDMpointer()->AddNewDetector(detector);
  // logicWorld->SetSensitiveDetector(detector);

  NaI_SensitiveDetector *naiSD = new NaI_SensitiveDetector("SodiumIodide");
  G4SDManager::GetSDMpointer()->AddNewDetector(naiSD);
  logicalNaiCrystal->SetSensitiveDetector(naiSD);
  
  return physWorld;
}
