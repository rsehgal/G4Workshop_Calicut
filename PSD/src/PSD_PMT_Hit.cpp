#include "PSD_PMT_Hit.h"

PSD_PMT_Hit::PSD_PMT_Hit() : fPhotonArrivalTime(0) {}

PSD_PMT_Hit::~PSD_PMT_Hit() {}

void PSD_PMT_Hit::SetArrivalTime(unsigned long long tme)
{
  fPhotonArrivalTime = tme;
}

unsigned long long PSD_PMT_Hit::GetArrivalTime() const
{
  return fPhotonArrivalTime;
}

void PSD_PMT_Hit::Print()
{
  std::cout << "Photon Arrival Time : " << fPhotonArrivalTime << std::endl;
}
