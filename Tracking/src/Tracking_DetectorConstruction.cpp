#include "Tracking_DetectorConstruction.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "Tracking_SensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "string"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4SystemOfUnits.hh"
#include "Tracking_MagneticField.h"
#include "G4LogicalVolumeStore.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
G4bool Tracking_DetectorConstruction::fieldIsInitialized = false;

Tracking_DetectorConstruction::Tracking_DetectorConstruction() {}

Tracking_DetectorConstruction::~Tracking_DetectorConstruction() {}

G4VPhysicalVolume* Tracking_DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* magneticEnveopMat = nist->FindOrBuildMaterial("G4_Galactic");

    //Modify the world volume dimension as required
    double worldXYZ = 4*m;
    G4Box* solidWorld = new G4Box("World", 0.5*worldXYZ, 0.5*worldXYZ, 0.5*worldXYZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

    //TODO : Create your desired detectors here
    //Envelop to create local magnetic field
    G4Box *envelop = new G4Box("MagneticEnvelop", 60.*cm, 60.*cm, 160.*cm);
    G4LogicalVolume *logicalEnvelop = new G4LogicalVolume(envelop,magneticEnveopMat,"LogicalEnvelop");
    new G4PVPlacement(nullptr,G4ThreeVector(),logicalEnvelop,"PhysicalEnvelop",logicWorld,false,0,true);

    G4Material *layerMat = worldMat;    
    G4Box *layer = new G4Box("Layer", 50.*cm,50.*cm,0.5*mm);
    G4LogicalVolume *logicalLayer = new G4LogicalVolume(layer,layerMat,"LogicalLayer");
    G4VisAttributes *visLayer = new G4VisAttributes(G4Color(1.,0.5,1.,0.5));
    visLayer->SetForceSolid(true);
    logicalLayer->SetVisAttributes(visLayer);

    G4VisAttributes *visScatterer = new G4VisAttributes(G4Color(0.,1.0,0.,0.5));
    visScatterer->SetForceSolid(true);
 
    double scattererThickness = 10.*cm;

    G4Material *pb = nist->FindOrBuildMaterial("G4_Pb");//    
    G4Box *scatterer = new G4Box("Scatterer", 50.*cm,50.*cm,scattererThickness/2.);
    G4LogicalVolume *logicalScatterer = new G4LogicalVolume(layer,layerMat,"LogicalScatterer");
    logicalScatterer->SetVisAttributes(visScatterer);
    
    G4bool checkOverlaps = true;
    
    G4int numOfLayers = 15;
    for(unsigned int i = 0 ; i < numOfLayers ; i++){
	double zpos = -140.*cm + (i+1)*scattererThickness+1;
        double scattererZPos = zpos+ scattererThickness/2. + 0.25;
 	G4String layerName = "PhysicalLayer_"+std::to_string(i);
 	G4String scattererName = "PhysicalScatterer_"+std::to_string(i);
	new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,zpos),logicalLayer,layerName,logicalEnvelop,false,i,checkOverlaps);
	if(i< (numOfLayers-1))
	new G4PVPlacement(nullptr,G4ThreeVector(0.,0.,scattererZPos),logicalScatterer,scattererName,logicalEnvelop,false,i,checkOverlaps);
    } 
        
    

    // Logic to Attach sensitive detector to a logical volume
    Tracking_SensitiveDetector* detector = new Tracking_SensitiveDetector("LayerSensitiveDetector","LayersHitsCollection");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector);
    logicalLayer->SetSensitiveDetector(detector);

    //ConstructSDandField();

    return physWorld;
}

G4LogicalVolume* Tracking_DetectorConstruction::GetLogicalVolumeByName(const G4String& name) {
    G4LogicalVolumeStore* lvStore = G4LogicalVolumeStore::GetInstance();
    for (auto* lv : *lvStore) {
        if (lv->GetName() == name) {
            return lv; // Found the logical volume
        }
    }
    return nullptr; // Return nullptr if not found
}

void Tracking_DetectorConstruction::ConstructSDandField() {
    //return;
    if (!fieldIsInitialized) {
        fieldIsInitialized = true;

        // Define a uniform magnetic field (1 Tesla along Y-axis)
        G4ThreeVector fieldValue = G4ThreeVector(0.0, 1. * tesla, 0.0);
        Tracking_MagneticField* magField = new Tracking_MagneticField(fieldValue);

        // Get the global field manager
        G4FieldManager* fieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
        
        // Set the field - Geant4 will automatically create a chord finder
        fieldManager->SetDetectorField(magField);
        fieldManager->CreateChordFinder(magField);

	GetLogicalVolumeByName("LogicalEnvelop")->SetFieldManager(fieldManager,true);
    }
}

