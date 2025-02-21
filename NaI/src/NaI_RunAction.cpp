#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "NaI_RunAction.h"
NaI_RunAction::NaI_RunAction() {}

NaI_RunAction::~NaI_RunAction() {}

void NaI_RunAction::BeginOfRunAction(const G4Run *) {
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->OpenFile("output.root");
  analMan->CreateH1("edep", "Energy Deposited", 50, 0, 1000);
  analMan->CreateH1("edepSmeared", "Energy Deposited with Detector resolution", 50, 0, 1000);
  analMan->CreateNtuple("ftree", "A simple tree for NaI Data");
  analMan->CreateNtupleDColumn("eDep");
  analMan->CreateNtupleDColumn("eDepSmeared");
  analMan->FinishNtuple();
}

void NaI_RunAction::EndOfRunAction(const G4Run *) {

  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->Write();
  analMan->CloseFile();
}
