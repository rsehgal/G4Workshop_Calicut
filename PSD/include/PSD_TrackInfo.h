/*
**	Filename : PSD_TrackInfo.h
**	2025-12-26
**	username : rsehgal
*/
#ifndef PSD_TrackInfo_h
#define PSD_TrackInfo_h

#include "G4VUserTrackInformation.hh"
#include "G4String.hh"

class PSD_TrackInfo : public G4VUserTrackInformation {
public:
    PSD_TrackInfo() : triggerProcess("") {}
    
    // The Copy Constructor
    PSD_TrackInfo(const PSD_TrackInfo& other) 
        :G4VUserTrackInformation(), triggerProcess(other.triggerProcess) {}

    virtual ~PSD_TrackInfo() {}

    // Methods to store/get the process name
    void SetTriggerProcess(G4String name) { triggerProcess = name; }
    G4String GetTriggerProcess() const { return triggerProcess; }

    // Required by Geant4 to print info (optional but good practice)
    virtual void Print() const override {
        G4cout << "Triggered by: " << triggerProcess << G4endl;
    }

private:
    G4String triggerProcess;
};
#endif
