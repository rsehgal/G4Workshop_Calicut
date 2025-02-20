#include "NaI_EventAction.h"
#include "G4AnalysisManager.hh"
#include "G4RandomTools.hh"
NaI_EventAction::NaI_EventAction() {}

NaI_EventAction::~NaI_EventAction() {}

void NaI_EventAction::BeginOfEventAction(const G4Event *event) {
  // TODO : All the required logic you want to do at the start
  //        of each event
  eDep = 0;
}

void NaI_EventAction::EndOfEventAction(const G4Event *event) {
  // TODO : All the required logic you want to do at the end
  //        of each event

  // std::cout << "Total Energy deposited in event : " << event->GetEventID() << " : " << eDep << std::endl;

  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  if (eDep > 0) {
    analMan->FillNtupleDColumn(0, 0, eDep * 1000.);
    analMan->FillNtupleDColumn(0, 1, G4RandGauss::shoot(eDep, 0.04385) * 1000.);
    analMan->AddNtupleRow(0);
  }
}

void NaI_EventAction::AddEnergy(double val) { eDep += val; }
