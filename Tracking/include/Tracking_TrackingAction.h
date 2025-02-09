#ifndef TRACKING_TRACKINGACTION_HH
#define TRACKING_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class Tracking_TrackingAction : public G4UserTrackingAction {
public:
    Tracking_TrackingAction();
    virtual ~Tracking_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
