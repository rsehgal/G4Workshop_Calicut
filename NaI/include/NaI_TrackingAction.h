#ifndef NAI_TRACKINGACTION_HH
#define NAI_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class NaI_TrackingAction : public G4UserTrackingAction {
public:
    NaI_TrackingAction();
    virtual ~NaI_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
