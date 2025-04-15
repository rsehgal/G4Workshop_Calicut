#include "MuonDecay_EventAction.h"

bool MuonDecay_EventAction::muonStopped = false;
bool MuonDecay_EventAction::muonDecayed = false;
unsigned long long MuonDecay_EventAction::muonStopTime = 0;
unsigned long long MuonDecay_EventAction::muonDecayTime = 0;


MuonDecay_EventAction::MuonDecay_EventAction()  {
}

MuonDecay_EventAction::~MuonDecay_EventAction() {}

void MuonDecay_EventAction::BeginOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the start
    //       of each event
    muonStopped = false;
    muonDecayed = false;
    muonStopTime = 0;
    muonDecayTime = 0;
}

void MuonDecay_EventAction::EndOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the end
    //       of each event
}
