#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "PSD_RunAction.h"

PSD_RunAction::PSD_RunAction() {}

PSD_RunAction::~PSD_RunAction() {}

void PSD_RunAction::BeginOfRunAction(const G4Run *) {
  std::vector<ULong64_t> *pulse = new std::vector<ULong64_t>;
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->OpenFile("output.root");
  analMan->CreateNtuple("ftree");
  analMan->CreateNtupleIColumn("pulse", pulse);
  analMan->FinishNtuple();
}

void PSD_RunAction::EndOfRunAction(const G4Run *) {
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->Write();
  analMan->CloseFile();
}
