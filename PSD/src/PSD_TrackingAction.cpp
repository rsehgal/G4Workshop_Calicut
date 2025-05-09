#include "PSD_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4TrackingManager.hh"
#include "G4OpticalPhoton.hh"
PSD_TrackingAction::PSD_TrackingAction() {}

PSD_TrackingAction::~PSD_TrackingAction() {}

void PSD_TrackingAction::PreUserTrackingAction(const G4Track *track)
{
  //  std::cout << "Tracking Action begin....." << std::endl;
}

void PSD_TrackingAction::PostUserTrackingAction(const G4Track *track)
{
  /*const auto *secondaries = fpTrackingManager->GimmeSecondaries();
  std::cout << "Total Number of Secondaries created : " << secondaries->size() << std::endl;
  for (unsigned int i = 0; i < secondaries->size(); i++) {
    std::cout << "Particle : " << secondaries->at(i)->GetDefinition()->GetParticleName() << std::endl;
  }*/

  // std::cout << "Tracking Action ends....." << std::endl;

  if (track->GetTrackID() == 1) {
    int photonCounter       = 0;
    const auto *secondaries = fpTrackingManager->GimmeSecondaries();
    std::cout << "Total Number of Secondaries created : " << secondaries->size() << std::endl;

    for (unsigned int i = 0; i < secondaries->size(); i++) {

      if (secondaries->at(i)->GetParentID() == 1 &&
          secondaries->at(i)->GetDefinition() == G4OpticalPhoton::Definition()) {
        //std::cout << "Optical Photon created by :  " << secondaries->at(i)->GetCreatorProcess()->GetProcessName() << std::endl;
        photonCounter++;
      }
    }
    std::cout << "Total Number of Optical photons created : " << photonCounter << std::endl;
  }
}
