#include "PSD_EventAction.h"
#include "PSD_HitCollections.h"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UserRunAction.hh"
#include "PSD_RunAction.h"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "Randomize.hh"
#include "G4DigiManager.hh"
#include "PSD_Digitizer.h"

PSD_EventAction::PSD_EventAction()
{
  G4UserRunAction *userRunAction = const_cast<G4UserRunAction *>(G4RunManager::GetRunManager()->GetUserRunAction());
  fRunAction                     = static_cast<PSD_RunAction *>(userRunAction);
  G4DigiManager *fDM             = G4DigiManager::GetDMpointer();
  PSD_Digitizer *myDigitizer     = new PSD_Digitizer("V1730","TestDigits");
  fDM->AddNewModule(myDigitizer);
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
  G4AnalysisManager *analMan      = G4AnalysisManager::Instance();
  G4HCofThisEvent *hce            = event->GetHCofThisEvent();
  int hcID                        = G4SDManager::GetSDMpointer()->GetCollectionID("pmtHitCollection_1");
  PmtHitCollection *hitCollection = static_cast<PmtHitCollection *>(hce->GetHC(hcID));
  std::vector<int> pulse;
  for (unsigned int i = 0; i < hitCollection->entries(); i++) {
    //(*hitCollection)[i]->Print();
    int arrivalTime = (*hitCollection)[i]->GetArrivalTime();
    //pulse.push_back(G4RandGauss::shoot(arrivalTime,3));
    pulse.push_back(arrivalTime);
  }
  fRunAction->FillPulse(pulse);

  // Trying to fetch digitizer
  G4DigiManager *fDM         = G4DigiManager::GetDMpointer();
  PSD_Digitizer *myDigitizer = static_cast<PSD_Digitizer *>(fDM->FindDigitizerModule("V1730"));
  myDigitizer->Digitize();
  // delete fDM;
  // delete myDigitizer;

  G4int digiColID = fDM->GetDigiCollectionID("TestDigits");
  //std::cout <<"DigiCollection ID : " << digiColID << std::endl;

  DigiCollection *dc = (DigiCollection *)(fDM->GetDigiCollection(digiColID));

  if (dc) {
    //std::cout <<"DigiCollection found in EndOfEvent............" << std::endl;
    G4int n_digits = dc->entries();
    //std::cout << "Num of digits : " << n_digits << std::endl;
    for (G4int i = 0; i < n_digits; i++) {
      //(*dc)[i]->Print();
      std::vector<G4double> waveform = (*dc)[i]->GetWaveform();

      // Proceed to Step 2: Save this data!
      fRunAction->FillConvolvedPulse(waveform);
      //std::cout << "Energy long : " << (*dc)[i]->Energy() << std::endl;
      analMan->FillNtupleDColumn(0, 1,-1.*(*dc)[i]->Energy());
      analMan->FillNtupleDColumn(0, 2,-1.*(*dc)[i]->EnergyShort());
    }
  analMan->AddNtupleRow(0);
  }

  //---
}
