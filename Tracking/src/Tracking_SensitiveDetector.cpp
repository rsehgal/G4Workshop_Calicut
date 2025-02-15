#include "Tracking_SensitiveDetector.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4StepPoint.hh"
#include "Tracking_SensitiveDetector_Hit.h"
#include "HitsCollections.h"

Tracking_SensitiveDetector::Tracking_SensitiveDetector(const G4String& name, const G4String collName) : G4VSensitiveDetector(name) {
    collectionName.insert(collName);
}

Tracking_SensitiveDetector::~Tracking_SensitiveDetector() {}

void Tracking_SensitiveDetector::Initialize(G4HCofThisEvent *hcofThisEvent){
    G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    fLayersHitsCollection  = new LayersHitsCollection(SensitiveDetectorName,collectionName[0]);
    hcofThisEvent->AddHitsCollection(hcID,fLayersHitsCollection);
}

G4bool Tracking_SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4double energy = track->GetKineticEnergy();
    //G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;
    G4StepPoint *preStepPt = step->GetPreStepPoint();
    G4StepPoint *postStepPt = step->GetPostStepPoint();
    Tracking_SensitiveDetector_Hit *hit = new Tracking_SensitiveDetector_Hit;

       if(preStepPt->GetStepStatus()==fGeomBoundary){
    	    G4ThreeVector pos = preStepPt->GetPosition();
	    G4ThreeVector momDir = preStepPt->GetMomentum();//Direction();
   	    G4String name = track->GetVolume()->GetName();
            G4int layerNo = track->GetVolume()->GetCopyNo();
	    //std::cout << name << " : Pos : " << pos << " : Momentum Direction : " << momDir  <<  std::endl;

    	    hit->Set(pos,momDir,name,layerNo);
	    
  	    fLayersHitsCollection->insert(hit);
    }
    //TODO :  Add Whatall information you want to get from steps
    return true;
}
