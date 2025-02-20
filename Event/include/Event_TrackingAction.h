#ifndef EVENT_TRACKINGACTION_HH
#define EVENT_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class Event_TrackingAction : public G4UserTrackingAction {
public:
    Event_TrackingAction();
    virtual ~Event_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
