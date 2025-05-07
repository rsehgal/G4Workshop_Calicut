#ifndef PSD_PMT_HIT_HH
#define PSD_PMT_HIT_HH

#include "G4VHit.hh"

class PSD_PMT_Hit : public G4VHit {
  unsigned long long fPhotonArrivalTime;

public:
  PSD_PMT_Hit();
  virtual ~PSD_PMT_Hit();
  void SetArrivalTime(unsigned long long tme);
  unsigned long long GetArrivalTime() const;
  void Print();
};

#endif
