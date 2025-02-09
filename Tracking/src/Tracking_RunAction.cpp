#include "Tracking_RunAction.h"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
Tracking_RunAction::Tracking_RunAction()  {
 fAnalMan = G4AnalysisManager::Instance();
}

Tracking_RunAction::~Tracking_RunAction() {}

void Tracking_RunAction::BeginOfRunAction(const G4Run*){
    fAnalMan->OpenFile("tracking.root");
    fAnalMan->CreateNtuple("Tracking","A simple Tracking Tree for Kalmann filtering example");
    fAnalMan->CreateNtupleDColumn("posX");
    fAnalMan->CreateNtupleDColumn("posY");
    fAnalMan->CreateNtupleDColumn("posZ");
    fAnalMan->CreateNtupleDColumn("smearedPosX");
    fAnalMan->CreateNtupleDColumn("smearedPosY");
    fAnalMan->CreateNtupleDColumn("smearedPosZ");

    fAnalMan->CreateNtupleDColumn("momentumX");
    fAnalMan->CreateNtupleDColumn("momentumY");
    fAnalMan->CreateNtupleDColumn("momentumZ");
    fAnalMan->CreateNtupleDColumn("layerNo");
    fAnalMan->CreateNtupleDColumn("eventNo");
    fAnalMan->FinishNtuple();

}

void Tracking_RunAction::EndOfRunAction(const G4Run*){

    fAnalMan->Write();
    fAnalMan->CloseFile();
}

