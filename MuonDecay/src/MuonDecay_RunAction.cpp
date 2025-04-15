#include "MuonDecay_RunAction.h"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
MuonDecay_RunAction::MuonDecay_RunAction() {}

MuonDecay_RunAction::~MuonDecay_RunAction() {}

void MuonDecay_RunAction::BeginOfRunAction(const G4Run *)
{
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->OpenFile("DecayData.root");
  analMan->CreateNtuple("ftree", "Muon Decay Data Tree");
  analMan->CreateNtupleDColumn("muonStopTime");
  analMan->CreateNtupleDColumn("muonDecayTime");
  analMan->CreateNtupleDColumn("diffTime");
  analMan->FinishNtuple();
}

void MuonDecay_RunAction::EndOfRunAction(const G4Run *)
{
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->Write();
  analMan->CloseFile();
}
