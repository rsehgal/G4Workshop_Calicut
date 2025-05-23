#include "G4Box.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "PSD_DetectorConstruction.h"
#include "PSD_PMT_SD.h"
#include "PSD_SensitiveDetector.h"

PSD_DetectorConstruction::PSD_DetectorConstruction() {}

PSD_DetectorConstruction::~PSD_DetectorConstruction() {}

G4MaterialPropertiesTable *PSD_DetectorConstruction::GetMPT()
{

  G4MaterialPropertiesTable *mpt = nullptr;
  return mpt;
}

// Not working and hence not used
G4VPhysicalVolume *PSD_DetectorConstruction::Construct()
{
  G4NistManager *nist  = G4NistManager::Instance();
  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

  // Modify the world volume dimension as required
  G4Box *solidWorld            = new G4Box("World", 0.5 * m, 0.5 * m, 0.5 * m);
  G4LogicalVolume *logicWorld  = new G4LogicalVolume(solidWorld, worldMat, "World");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

  //G4Material *crystalMat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  G4Material *crystalMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  G4Material *pmtMat     = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

  // TODO : Create your desired detectors here
  //  Crystal
  G4Box *solidCrystal = new G4Box("Crystal", 1 * cm, 1 * cm, 2 * cm);
  G4LogicalVolume *logicCrystal = new G4LogicalVolume(solidCrystal, crystalMat, "Crystal");
  G4VPhysicalVolume *phyCrystal =
      new G4PVPlacement(0, G4ThreeVector(0, 0, -2 * cm), logicCrystal, "Crystal", logicWorld, false, 0);
  const G4int nEntries = 2;

  {
    const G4int nEntries            = 2;
    G4double photonEnergy[nEntries] = {1.5 * eV, 3.5 * eV};

    // Refractive index
    G4double rIndex[nEntries] = {1.8, 1.8};

    // Absorption length (how far photons travel before being absorbed)
    G4double absorption[nEntries] = {50 * cm, 50 * cm};

    // Scintillation emission spectrum (uniform for simplicity)
    G4double scintSpectrum[nEntries] = {1.0, 1.0};

    G4double scintYield[nEntries] = {10000. / MeV, 10000. / MeV};

    // Create MPT (Material Properties Table)
    G4MaterialPropertiesTable *mptCrystal = new G4MaterialPropertiesTable();
    mptCrystal->AddProperty("RINDEX", photonEnergy, rIndex, nEntries);
    mptCrystal->AddProperty("ABSLENGTH", photonEnergy, absorption, nEntries);
    mptCrystal->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scintSpectrum, nEntries);
    mptCrystal->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintSpectrum, nEntries);
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD", 10000. / MeV); 
    mptCrystal->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 35 * ns); 
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 1.0 * ns);  

    mptCrystal->AddConstProperty("ELECTRONSCINTILLATIONTIMECONSTANT1", 3.5 * ns); 
    mptCrystal->AddConstProperty("ELECTRONSCINTILLATIONTIMECONSTANT2", 10 * ns);  
    mptCrystal->AddConstProperty("PROTONSCINTILLATIONTIMECONSTANT1", 2.0 * ns);   
    mptCrystal->AddConstProperty("PROTONSCINTILLATIONTIMECONSTANT2", 35.0 * ns);  
    mptCrystal->AddConstProperty("IONSCINTILLATIONTIMECONSTANT1", 2.0 * ns);      
    mptCrystal->AddConstProperty("IONSCINTILLATIONTIMECONSTANT2", 35.0 * ns);     

    std::vector<double> electronEnergy = {0.1 * MeV, 0.5 * MeV, 1.0 * MeV, 2.0 * MeV, 5.0 * MeV};
    std::vector<double> electronYield  = {8000.0, 9500.0, 10000.0, 10200.0, 10500.0};
    mptCrystal->AddProperty("ELECTRONSCINTILLATIONYIELD", electronEnergy.data(), electronYield.data(),electronEnergy.size());
    //mptCrystal->AddProperty("ELECTRONSCINTILLATIONYIELD", photonEnergy,scintSpectrum,2);
    mptCrystal->AddConstProperty("ELECTRONSCINTILLATIONYIELD1", 0.95);
    mptCrystal->AddConstProperty("ELECTRONSCINTILLATIONYIELD2", 0.05);

    std::vector<double> ionEnergy = {1.0 * MeV, 5.0 * MeV, 10.0 * MeV, 20.0 * MeV, 50.0 * MeV};
    std::vector<double> ionYield  = {300., 800., 1200., 1500., 1800.};
    mptCrystal->AddProperty("IONSCINTILLATIONYIELD", ionEnergy.data(), ionYield.data(), ionEnergy.size());
    //mptCrystal->AddProperty("IONSCINTILLATIONYIELD", photonEnergy, scintSpectrum, 2);
    mptCrystal->AddConstProperty("IONSCINTILLATIONYIELD1", 0.05);
    mptCrystal->AddConstProperty("IONSCINTILLATIONYIELD2", 0.95);

    std::vector<double> pEnergy = {1.0 * MeV, 10.0 * MeV, 50.0 * MeV, 100.0 * MeV};
    std::vector<double> pYield  = {1000., 2000., 4000., 5000.};
    mptCrystal->AddProperty("PROTONSCINTILLATIONYIELD", pEnergy.data(), pYield.data(), pEnergy.size());
    //mptCrystal->AddProperty("PROTONSCINTILLATIONYIELD", photonEnergy,scintSpectrum,2);
    mptCrystal->AddConstProperty("PROTONSCINTILLATIONYIELD1", 0.05);
    mptCrystal->AddConstProperty("PROTONSCINTILLATIONYIELD2", 0.95);


    G4double deuteronE[nEntries] = {1.0 * keV, 10.0 * MeV};
    G4double deuteronYield[nEntries] = {2500. / MeV, 2500. / MeV};

    mptCrystal->AddProperty("DEUTERONSCINTILLATIONYIELD", deuteronE, deuteronYield, nEntries);
    mptCrystal->AddConstProperty("DEUTERONSCINTILLATIONYIELD1", 0.1);  // Fast component fraction (e.g.)
    mptCrystal->AddConstProperty("DEUTERONSCINTILLATIONYIELD2", 0.9);  // Slow component fraction
    mptCrystal->AddConstProperty("DEUTERONSCINTILLATIONTIMECONSTANT1", 3.0 * ns); 
    mptCrystal->AddConstProperty("DEUTERONSCINTILLATIONTIMECONSTANT2", 30.0 * ns);

    crystalMat->SetMaterialPropertiesTable(mptCrystal);
  }

  // PMT
  G4Box *solidPMT           = new G4Box("PMT", 0.5 * cm, 0.5 * cm, 0.5 * cm);
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
  const G4int num                       = 2;
  G4double ephoton[num]                 = {1.5 * eV, 3.5 * eV};
  G4double reflectivity[num]            = {1.0, 1.0};
  G4double efficiency[num]              = {0.0, 0.0};
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
  G4double reflectivity_zero[num]         = {1., 1.}; // {0.0, 0.0};
  G4double eff_pmt[num]                   = {1., 1.}; // {0.35, 0.35};
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
