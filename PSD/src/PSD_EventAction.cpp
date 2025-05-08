#include "PSD_EventAction.h"
#include "PSD_HitCollections.h"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UserRunAction.hh"
#include "PSD_RunAction.h"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
PSD_EventAction::PSD_EventAction()
{
  G4UserRunAction *userRunAction = const_cast<G4UserRunAction *>(G4RunManager::GetRunManager()->GetUserRunAction());
  fRunAction                     = static_cast<PSD_RunAction *>(userRunAction);
}

PSD_EventAction::~PSD_EventAction() {}

void PSD_EventAction::BeginOfEventAction(const G4Event *event)
{
  // TODO : All the required logic you want to do at the start
  //        of each event
}

void PSD_EventAction::EndOfEventAction(const G4Event *event)
{
  // TODO : All the required logic you want to do at the end
  //        of each event
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  G4HCofThisEvent *hce            = event->GetHCofThisEvent();
  int hcID                        = G4SDManager::GetSDMpointer()->GetCollectionID("pmtHitCollection_1");
  PmtHitCollection *hitCollection = static_cast<PmtHitCollection *>(hce->GetHC(hcID));
  std::vector<int> pulse;
  for (unsigned int i = 0; i < hitCollection->entries(); i++) {
    //(*hitCollection)[i]->Print();
    pulse.push_back((*hitCollection)[i]->GetArrivalTime());
  }
    fRunAction->FillPulse(pulse);
    analMan->AddNtupleRow(0);
    
}
