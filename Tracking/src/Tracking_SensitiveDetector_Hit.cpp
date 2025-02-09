#include "Tracking_SensitiveDetector_Hit.h"

Tracking_SensitiveDetector_Hit::Tracking_SensitiveDetector_Hit()  {
}

Tracking_SensitiveDetector_Hit::Tracking_SensitiveDetector_Hit(G4ThreeVector pos, G4ThreeVector momDir, G4String name) : fPosition(pos), fMomentumDirection(momDir), fVolumeName(name),fLayerNo(-1){

}

Tracking_SensitiveDetector_Hit::~Tracking_SensitiveDetector_Hit() {}

G4ThreeVector Tracking_SensitiveDetector_Hit::GetPosition() const {
    return fPosition;
}

G4ThreeVector Tracking_SensitiveDetector_Hit::GetMomentumDirection() const {
    return fMomentumDirection;
}

G4String Tracking_SensitiveDetector_Hit::GetVolumeName() const {
    return fVolumeName;
}

G4int Tracking_SensitiveDetector_Hit::GetLayerNo() const{
    return fLayerNo;
}

void Tracking_SensitiveDetector_Hit::SetPosition(G4ThreeVector pos){
    fPosition = pos;
}

void Tracking_SensitiveDetector_Hit::SetMomentumDirection(G4ThreeVector momDir){
    fMomentumDirection = momDir;
}

void Tracking_SensitiveDetector_Hit::SetVolumeName(G4String name){
    fVolumeName = name;
}

void Tracking_SensitiveDetector_Hit::Set(G4ThreeVector pos, G4ThreeVector momDir, G4String name){
    fPosition = pos;
    fMomentumDirection = momDir;
    fVolumeName = name;
}
void Tracking_SensitiveDetector_Hit::Set(G4ThreeVector pos, G4ThreeVector momDir, G4String name,G4int layerNo){
    fPosition = pos;
    fMomentumDirection = momDir;
    fVolumeName = name;
    fLayerNo = layerNo;
}

void Tracking_SensitiveDetector_Hit::Print(){
   std::cout << "Position : " << fPosition << " : Momentum Direction : " << fMomentumDirection << " : VolumeName : " << fVolumeName << std::endl;
}
