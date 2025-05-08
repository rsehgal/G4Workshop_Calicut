#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "PSD_DetectorConstruction.h"
#include "PSD_PMT_SD.h"
#include "PSD_SensitiveDetector.h"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"


PSD_DetectorConstruction::PSD_DetectorConstruction() {}

PSD_DetectorConstruction::~PSD_DetectorConstruction() {}

//Not working and hence not used
G4Material* PSD_DetectorConstruction::GetScintillatorWithPSD(){
    // 1. Define the scintillator material (simplified EJ-301)
    G4double density = 0.874 * g/cm3;
    G4Material* EJ301 = new G4Material("EJ301", density, 2);
    EJ301->AddElement(G4NistManager::Instance()->FindOrBuildElement("H"), 10); // Hydrogen
    EJ301->AddElement(G4NistManager::Instance()->FindOrBuildElement("C"), 9);  // Carbon

    // 2. Create a material properties table
    auto mpt = new G4MaterialPropertiesTable();

    // 3. Define photon energy range (optical)
    const G4int nEntries = 2;
    G4double photonEnergy[nEntries]    = {2.0 * eV, 3.5 * eV};
    G4double refractiveIndex[nEntries] = {1.50, 1.50};
    G4double absorption[nEntries]      = {3.5 * m, 3.5 * m};
    G4double scintilFast[nEntries]     = {1.0, 1.0};

    mpt->AddProperty("RINDEX",        photonEnergy, refractiveIndex, nEntries);
    mpt->AddProperty("ABSLENGTH",     photonEnergy, absorption,      nEntries);
    //mpt->AddProperty("FASTCOMPONENT", photonEnergy, scintilFast,     nEntries);
    mpt->AddConstProperty("SCINTILLATIONYIELD", 10000. / MeV);
    mpt->AddConstProperty("RESOLUTIONSCALE", 1.0);
    //mpt->AddConstProperty("YIELDRATIO", 1.0); // fallback if particle-type not defined

    // 4. Particle-dependent scintillation parameters
    // --- Electrons (gamma interaction)
    mpt->AddConstProperty("ELECTRONSCINTILLATIONYIELD", 10000. / MeV);
    mpt->AddConstProperty("ELECTRONFASTTIMECONSTANT", 3.2 * ns);
    mpt->AddConstProperty("ELECTRONSLOWTIMECONSTANT", 32.0 * ns);
    mpt->AddConstProperty("ELECTRONYIELDRATIO", 0.85);  // Mostly fast component

    // --- Protons (neutron interaction)
    mpt->AddConstProperty("PROTONSCINTILLATIONYIELD", 9500. / MeV);
    mpt->AddConstProperty("PROTONFASTTIMECONSTANT", 4.5 * ns);
    mpt->AddConstProperty("PROTONSLOWTIMECONSTANT", 55.0 * ns);
    mpt->AddConstProperty("PROTONYIELDRATIO", 0.45);  // More slow component

    // 5. Assign MPT to the material
    EJ301->SetMaterialPropertiesTable(mpt);
    return EJ301;
}

G4VPhysicalVolume *PSD_DetectorConstruction::Construct() {
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  // Modify the world volume dimension as required
  G4Box *solidWorld = new G4Box("World", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

  G4Material *crystalMat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  G4Material *pmtMat = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

  //G4Material *psdMaterial = GetScintillatorWithPSD();

  // TODO : Create your desired detectors here
  //  Crystal
  G4Box *solidCrystal = new G4Box("Crystal", 1 * cm, 1 * cm, 2 * cm);
  //G4LogicalVolume *logicCrystal = new G4LogicalVolume(solidCrystal, psdMaterial, "Crystal");
  G4LogicalVolume *logicCrystal = new G4LogicalVolume(solidCrystal, pmtMat, "Crystal");
  G4VPhysicalVolume *phyCrystal =
      new G4PVPlacement(0, G4ThreeVector(0, 0, -2 * cm), logicCrystal, "Crystal", logicWorld, false, 0);
  const G4int nEntries = 2;

  {
    const G4int nEntries = 2;
    G4double photonEnergy[nEntries] = {1.5 * eV, 3.5 * eV};

    // Refractive index
    G4double rIndex[nEntries] = {1.8, 1.8};

    // Absorption length (how far photons travel before being absorbed)
    G4double absorption[nEntries] = {50 * cm, 50 * cm};

    // Scintillation emission spectrum (uniform for simplicity)
    G4double scintSpectrum[nEntries] = {1.0, 1.0};

    // Create MPT (Material Properties Table)
    G4MaterialPropertiesTable *mptCrystal = new G4MaterialPropertiesTable();
    mptCrystal->AddProperty("RINDEX", photonEnergy, rIndex, nEntries);
    mptCrystal->AddProperty("ABSLENGTH", photonEnergy, absorption, nEntries);
    mptCrystal->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scintSpectrum, nEntries);
    mptCrystal->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintSpectrum, nEntries);
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD", 10000. / MeV); // Example yield
    mptCrystal->AddConstProperty("RESOLUTIONSCALE", 1.0);
    //mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 10. * ns);
    //mptCrystal->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3.5*ns);  // fast
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 35.0*ns); // slow
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD1", 0.85); // 85% fast
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD2", 0.15); // 15% slow""""""""

    // mptCrystal->AddConstProperty("FASTSCINTILLATIONRISETIME", 1. * ns);

    // Attach to material
    crystalMat->SetMaterialPropertiesTable(mptCrystal);
  }

  // PMT
  G4Box *solidPMT = new G4Box("PMT", 0.5 * cm, 0.5 * cm, 0.5 * cm);
  G4LogicalVolume *logicPMT = new G4LogicalVolume(solidPMT, pmtMat, "PMT");
  G4VPhysicalVolume *phyPMT =
      new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5 * cm), logicPMT, "PMT", logicWorld, false, 0);

  G4double photonEnergy[nEntries] = {1.5 * eV, 3.5 * eV};

  // Refractive index
  G4double rIndex[nEntries] = {1.9, 1.9};

  G4MaterialPropertiesTable *glassMPT = new G4MaterialPropertiesTable();
  glassMPT->AddProperty("RINDEX", photonEnergy, rIndex, nEntries);
  pmtMat->SetMaterialPropertiesTable(glassMPT);

  // Define optical surface for side reflection
  G4OpticalSurface *surfaceCrystal = new G4OpticalSurface("CrystalSurface");
  surfaceCrystal->SetModel(unified);
  surfaceCrystal->SetType(dielectric_dielectric);
  surfaceCrystal->SetFinish(groundfrontpainted); // or polished

  // Reflective properties
  G4MaterialPropertiesTable *mptSurface = new G4MaterialPropertiesTable();
  const G4int num = 2;
  G4double ephoton[num] = {1.5 * eV, 3.5 * eV};
  G4double reflectivity[num] = {1.0, 1.0};
  G4double efficiency[num] = {0.0, 0.0};
  mptSurface->AddProperty("REFLECTIVITY", ephoton, reflectivity, num);
  mptSurface->AddProperty("EFFICIENCY", ephoton, efficiency, num);
  surfaceCrystal->SetMaterialPropertiesTable(mptSurface);

  // Apply skin surface to entire crystal (reflect on sides)
  new G4LogicalSkinSurface("CrystalSkinSurface", logicCrystal, surfaceCrystal);

  // Define interface between crystal and PMT — allow transmission
  G4OpticalSurface *crystalToPMTSurface = new G4OpticalSurface("CrystalToPMT");
  crystalToPMTSurface->SetType(dielectric_dielectric);
  crystalToPMTSurface->SetModel(unified);
  crystalToPMTSurface->SetFinish(polished);

  // Perfect transmission (no reflectivity)
  G4MaterialPropertiesTable *mptInterface = new G4MaterialPropertiesTable();
  G4double reflectivity_zero[num] = {1., 1.}; // {0.0, 0.0};
  G4double eff_pmt[num] = {1., 1.};           // {0.35, 0.35};
  // G4double eff_pmt[num]         = {1.0,1.0};
  // mptInterface->AddProperty("REFLECTIVITY", ephoton, reflectivity_zero, num);
  // mptInterface->AddProperty("EFFICIENCY", ephoton, eff_pmt, num);
  crystalToPMTSurface->SetMaterialPropertiesTable(mptInterface);

  // Apply border surface only at the shared face
#if (1)
  new G4LogicalBorderSurface("CrystalToPMT_Surface", phyCrystal, phyPMT, crystalToPMTSurface);
#endif

  // Logic to Attach sensitive detector to a logical volume
  // PSD_SensitiveDetector* detector = new PSD_SensitiveDetector("SensitiveDetector");
  // G4SDManager::GetSDMpointer()->AddNewDetector(detector);
  // logicWorld->SetSensitiveDetector(detector);

  PSD_PMT_SD *sdDetector = new PSD_PMT_SD("PMT_1");
  G4SDManager::GetSDMpointer()->AddNewDetector(sdDetector);
  logicPMT->SetSensitiveDetector(sdDetector);
  return physWorld;
}
