#include "Event_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

Event_TrackingAction::Event_TrackingAction()  {
}

Event_TrackingAction::~Event_TrackingAction() {}

void Event_TrackingAction::PreUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action begin....." << std::endl;
}

void Event_TrackingAction::PostUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action ends....." << std::endl;
}

