/*
**	Filename : EJ276D.cpp
**	2026-01-01
**	username : rsehgal
*/
#include "EJ276D.h"
#include <vector>
#include <G4SystemOfUnits.hh>
// Energies (eV) converted from your nm data, sorted in increasing order
std::vector<double> photonEnergyy = {
    2.3124*eV, 2.3494*eV, 2.3810*eV, 2.4134*eV, 2.4552*eV, 2.4955*eV, 
    2.5342*eV, 2.5709*eV, 2.5897*eV, 2.6281*eV, 2.6444*eV, 2.6677*eV, 
    2.6947*eV, 2.7293*eV, 2.7612*eV, 2.7938*eV, 2.8123*eV, 2.8310*eV, 
    2.8615*eV, 2.8887*eV, 2.9164*eV, 2.9365*eV, 2.9528*eV, 2.9610*eV, 
    2.9652*eV, 2.9818*eV, 2.9860*eV, 3.0113*eV, 3.0156*eV, 3.0458*eV, 
    3.0678*eV, 3.1241*eV
};

// Relative intensities matching the energy points above
std::vector<double> scintSpectrumm = {
    0.0060, 0.0060, 0.0060, 0.0340, 0.0450, 0.0730, 0.1170, 0.1510, 
    0.1960, 0.2680, 0.3350, 0.4020, 0.4530, 0.4920, 0.5640, 0.6650, 
    0.7210, 0.8040, 0.9160, 0.9720, 0.9940, 0.9830, 0.9110, 0.8040, 
    0.6980, 0.5980, 0.4920, 0.3850, 0.2910, 0.1560, 0.0390, 0.0110
};
