#ifndef DT_TRACKINGACTION_HH
#define DT_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class DT_TrackingAction : public G4UserTrackingAction {
public:
    DT_TrackingAction();
    virtual ~DT_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
