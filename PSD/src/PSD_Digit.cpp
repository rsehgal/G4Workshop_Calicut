#include "PSD_Digit.h"

PSD_Digit::PSD_Digit() {}

PSD_Digit::~PSD_Digit() {}

void PSD_Digit::SetWaveform(const std::vector<double> &wf)
{
  if (fWaveform.size()) fWaveform.clear();

  for (unsigned int i = 0; i < wf.size(); i++) {
    fWaveform.push_back(wf[i]);
  }
  //  fWaveform = wf;
}

std::vector<double> PSD_Digit::GetWaveform() const
{
  return fWaveform;
}

void PSD_Digit::Print()
{

  for (unsigned int i = 0; i < fWaveform.size(); i++) {
    std::cout << fWaveform[i] << " , ";
  }
  std::cout << std::endl;
}
