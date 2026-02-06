#include "DT_RunAction.h"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

DT_RunAction::DT_RunAction()  {
}

DT_RunAction::~DT_RunAction() {}

void DT_RunAction::BeginOfRunAction(const G4Run*){

  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->OpenFile("output.root");
  analMan->CreateNtuple("ftree","A simple DT tree");
  analMan->CreateNtupleDColumn("eDep");
  analMan->FinishNtuple();
}

void DT_RunAction::EndOfRunAction(const G4Run*){
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->Write();
  analMan->CloseFile();
}

