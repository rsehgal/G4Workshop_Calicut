#ifndef PSD_PMT_HIT_HH
#define PSD_PMT_HIT_HH

#include "G4VHit.hh"
class PSD_PMT_Hit : public G4VHit {
  int fPhotonArrivalTime;

public:
  PSD_PMT_Hit();
  virtual ~PSD_PMT_Hit();
  void SetArrivalTime(int tme);
  int GetArrivalTime() const;
  void Print();
};

#endif
