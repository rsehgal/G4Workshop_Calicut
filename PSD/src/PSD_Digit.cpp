#include "PSD_Digit.h"
#include "PSD_Global.h"
#include "TH1F.h"
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

double PSD_Digit::Integral(short int gateWidth)
{
  TH1F *hist = new TH1F("waveForm", "waveForm", fWaveform.size(), 0, fWaveform.size());

  for (unsigned int i = 0; i < fWaveform.size(); i++) {
    hist->SetBinContent(i, fWaveform[i]);
  }

  double integral = hist->Integral(0, gateWidth);
  delete hist;
  return integral;
}

double PSD_Digit::Energy()
{
  return Integral(longGate);
}

double PSD_Digit::EnergyShort()
{
  return Integral(shortGate);
}
