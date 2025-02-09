#include "Tracking_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

Tracking_TrackingAction::Tracking_TrackingAction()  {
}

Tracking_TrackingAction::~Tracking_TrackingAction() {}

void Tracking_TrackingAction::PreUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action begin....." << std::endl;
}

void Tracking_TrackingAction::PostUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action ends....." << std::endl;
}

