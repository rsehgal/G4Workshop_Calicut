#include "NaI_RunAction.h"
#include "G4Run.hh"

NaI_RunAction::NaI_RunAction()
{
  fAnalysisManager = G4AnalysisManager::Instance();
}

NaI_RunAction::~NaI_RunAction() {}

void NaI_RunAction::BeginOfRunAction(const G4Run *)
{
  fAnalysisManager->OpenFile("nai.root");
  fAnalysisManager->CreateNtuple("ftree", "A simple tree for NaI Data");
  fAnalysisManager->CreateNtupleDColumn("fEDep");
  fAnalysisManager->CreateNtupleDColumn("fEDepSmeared");
  fAnalysisManager->FinishNtuple();
}

void NaI_RunAction::EndOfRunAction(const G4Run *)
{
  fAnalysisManager->Write();
  fAnalysisManager->CloseFile();
}
