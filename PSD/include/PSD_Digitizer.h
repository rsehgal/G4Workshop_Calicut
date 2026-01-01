#ifndef PSD_DIGITIZER_HH
#define PSD_DIGITIZER_HH

#include "G4VDigitizerModule.hh"
#include <vector>
#include "PSD_Global.h"
class PSD_Digitizer : public G4VDigitizerModule {
  /*short int fShort;
  short int fLong;*/
public:
  PSD_Digitizer(const G4String &name);
  //PSD_Digitizer(const G4String &name, const G4String &collName, short int sGate=shortGate, short int lGate=longGate);
  PSD_Digitizer(const G4String &name, const G4String &collName);
  virtual ~PSD_Digitizer();
  virtual void Digitize();
  double SinglePhotoelectronResponse(double dt);
/*  double Integral(std::vector<double> waveform,short int gateWidth);
  double Energy(std::vector<double> waveform);
  double EnergyShort(std::vector<double> waveform);*/
  
};

#endif
