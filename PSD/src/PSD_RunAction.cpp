#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "PSD_RunAction.h"
PSD_RunAction::PSD_RunAction():fOutfileName(nullptr) {}
PSD_RunAction::PSD_RunAction(char *filename) : fOutfileName(filename) {
}

PSD_RunAction::~PSD_RunAction() {}

void PSD_RunAction::BeginOfRunAction(const G4Run *)
{
  // std::vector<ULong64_t> *pulse = new std::vector<ULong64_t>;
  // std::vector<int> pulse;
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  //analMan->OpenFile("output.root");
  analMan->OpenFile(fOutfileName);
  analMan->CreateNtuple("ftree", "A Tree to store pulse and PSD data");
  analMan->CreateNtupleIColumn("pulse", fPulse);
  analMan->FinishNtuple();
}

void PSD_RunAction::FillPulse(std::vector<int> pulse)
{
  if(fPulse.size())
  fPulse.clear();
  for (unsigned int i = 0; i < pulse.size(); i++) {
    fPulse.push_back(pulse[i]);
  }
}

void PSD_RunAction::EndOfRunAction(const G4Run *)
{
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->Write();
  analMan->CloseFile();
}
