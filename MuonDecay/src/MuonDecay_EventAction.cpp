#include "MuonDecay_EventAction.h"

bool MuonDecay_EventAction::muonStopped = false;
bool MuonDecay_EventAction::muonDecayed = false;


MuonDecay_EventAction::MuonDecay_EventAction()  {
}

MuonDecay_EventAction::~MuonDecay_EventAction() {}

void MuonDecay_EventAction::BeginOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the start
    //       of each event
    MuonDecay_EventAction::muonStopped = false;
    MuonDecay_EventAction::muonDecayed = false;

}

void MuonDecay_EventAction::EndOfEventAction(const G4Event *event){
    //TODO : All the required logic you want to do at the end
    //       of each event
}
