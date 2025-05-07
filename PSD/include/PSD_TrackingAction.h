#ifndef PSD_TRACKINGACTION_HH
#define PSD_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class PSD_TrackingAction : public G4UserTrackingAction {
public:
    PSD_TrackingAction();
    virtual ~PSD_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
