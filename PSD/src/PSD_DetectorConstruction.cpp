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
#include "PSD_Crystal_SD.h"
#include "PSD_SensitiveDetector.h"
#include "G4Tubs.hh"
//#include "G4EmSaturation.hh"
//#include "G4LossTableManager.hh"
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

    //G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
    //emSaturation->SetBirksConstant(myScintillatorMaterial, 0.0125 * mm/MeV);


  // TODO : Create your desired detectors here
  //  Crystal
  //G4Box *solidCrystal = new G4Box("Crystal", 1 * cm, 1 * cm, 2 * cm);

  double crystalDia = 2*2.54*cm;
  double crystalHei = 2*2.54*cm;
  double pmtHei = 2*2.54*cm;

  G4Tubs *solidCrystal = new G4Tubs("Crystal",0.,0.5*crystalDia,0.5*crystalHei,0.,2*M_PI);
  G4LogicalVolume *logicCrystal = new G4LogicalVolume(solidCrystal, crystalMat, "Crystal");
  G4VPhysicalVolume *phyCrystal =
      //new G4PVPlacement(0, G4ThreeVector(0, 0, -2 * cm), logicCrystal, "Crystal", logicWorld, false, 0);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicCrystal, "Crystal", logicWorld, false, 0);
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

#define SCINTILLATOR_TAU1 13 * ns
#define SCINTILLATOR_TAU2 35 * ns
#define SCINTILLATOR_TAU3 270 * ns
mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT1", SCINTILLATOR_TAU1);
mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT2", SCINTILLATOR_TAU2);
mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT3", SCINTILLATOR_TAU3);
//mptCrystal->AddConstProperty("BIRKS_CONSTANT_PROTON", 0.126*mm/MeV);


//mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3.0 * ns);   // Fast decay (Component 1)
//mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 250.0 * ns);
// For electrons (mostly gamma signal): Favor the FAST component (1)
//G4double particleEnergy[] = { 0.1*keV, 1.0*MeV, 10.0*MeV }; // Energy points
//G4double electronYield[] = { 1.0, 10000.0, 100000.0 };      // Yield at those points

// Add as a property vector (AddProperty), not a constant
//mptCrystal->AddProperty("ELECTRONSCINTILLATIONYIELD", particleEnergy, electronYield, 3);
//mptCrystal->AddProperty("PROTONSCINTILLATIONYIELD", particleEnergy, electronYield, 3);

//mptCrystal->AddConstProperty("ELECTRONSCINTILLATIONYIELD1", 0.95); // 95% fast
//mptCrystal->AddConstProperty("ELECTRONSCINTILLATIONYIELD2", 0.05); // 5% slow (tail)

// For protons (mostly neutron signal): Favor the SLOW component (2) 
// This is the key to creating the longer neutron tail!
//mptCrystal->AddConstProperty("PROTONSCINTILLATIONYIELD1", 0.30);  // 30% fast
//mptCrystal->AddConstProperty("PROTONSCINTILLATIONYIELD2", 0.70);  // 70% slow (tail)""""""""    
#ifdef FOR_GAMMA
    // Gamma: Higher fast/medium yield
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD1", 0.85);
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD2", 0.10);
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD3", 0.05); // Lower slow yield
#elif defined(FOR_NEUTRON)
    // Neutron: Higher slow yield for PSD
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD1", 0.60); // Lower fast yield
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD2", 0.15); // Similar medium yield
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD3", 0.25); // HIGHER slow yield
#endif

/*#ifdef FOR_GAMMA
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 13 * ns); 
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 35 * ns);  
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT3", 270 * ns);  
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD1", 0.8);  
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD2", 0.15);  
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD3", 0.05);  
#elif defined(FOR_NEUTRON)
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 13 * ns); 
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 59 * ns);  
    mptCrystal->AddConstProperty("SCINTILLATIONTIMECONSTANT3", 460 * ns);  
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD1", 0.4);  
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD2", 0.3);  
    mptCrystal->AddConstProperty("SCINTILLATIONYIELD3", 0.3);  

#endif
*/
    crystalMat->SetMaterialPropertiesTable(mptCrystal);
  }

  // PMT
  //G4Box *solidPMT           = new G4Box("PMT", 0.5 * cm, 0.5 * cm, 0.5 * cm);
  G4Tubs *solidPMT = new G4Tubs("PMT",0.,0.5*crystalDia,0.5*pmtHei,0.,2*M_PI);
  G4LogicalVolume *logicPMT = new G4LogicalVolume(solidPMT, pmtMat, "PMT");
  G4VPhysicalVolume *phyPMT =
      //new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5 * cm), logicPMT, "PMT", logicWorld, false, 0);
        new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5*crystalHei+0.5*pmtHei), logicPMT, "PMT", logicWorld, false, 0);

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

  PSD_Crystal_SD *sdCrystal = new PSD_Crystal_SD("SensitiveCrystal","Crystal");
  G4SDManager::GetSDMpointer()->AddNewDetector(sdCrystal);
  logicCrystal->SetSensitiveDetector(sdCrystal);

  return physWorld;
}
