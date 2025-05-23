#include "G4OpticalPhoton.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "PSD_TrackingAction.h"
PSD_TrackingAction::PSD_TrackingAction() {}

PSD_TrackingAction::~PSD_TrackingAction() {}

void PSD_TrackingAction::PreUserTrackingAction(const G4Track *track)
{
  //  std::cout << "Tracking Action begin....." << std::endl;
  /*if (track->GetTrackID() > 1 && track->GetDefinition()->GetParticleName() != "opticalphoton") {
    G4Track *nonconstTrack = (G4Track *)track;
    nonconstTrack->SetTrackStatus(fStopAndKill);
  }*/

/*  if(track->GetDefinition()->GetParticleName()=="deuteron"){
G4Track *nonconstTrack = (G4Track *)track;
//nonconstTrack->SetTrackStatus(fStopAndKill);
}*/
}

void PSD_TrackingAction::PostUserTrackingAction(const G4Track *track)
{
  /*const auto *secondaries = fpTrackingManager->GimmeSecondaries();
  std::cout << "Total Number of Secondaries created : " << secondaries->size() << std::endl;
  for (unsigned int i = 0; i < secondaries->size(); i++) {
    std::cout << "Particle : " << secondaries->at(i)->GetDefinition()->GetParticleName() << std::endl;
  }*/

  // std::cout << "Tracking Action ends....." << std::endl;
#if(1)
  if (track->GetTrackID() == 1) {
    int photonCounter       = 0;
    const auto *secondaries = fpTrackingManager->GimmeSecondaries();
    //std::cout << "TRACKING : Total Number of Secondaries created : " << secondaries->size() << std::endl;

    for (unsigned int i = 0; i < secondaries->size(); i++) {

      if ( // secondaries->at(i)->GetParentID() == 1 &&
          secondaries->at(i)->GetDefinition() == G4OpticalPhoton::Definition()) {
        // std::cout << "Optical Photon created by :  " << secondaries->at(i)->GetCreatorProcess()->GetProcessName() <<
        // std::endl;
        photonCounter++;
      } else {

        //std::cout << "Particle Name : " << secondaries->at(i)->GetDefinition()->GetParticleName() << std::endl;
      }
    }
    if (photonCounter)
      std::cout << "TRACKING : Total Number of Optical photons created : " << photonCounter << std::endl;
  }
#endif
}
