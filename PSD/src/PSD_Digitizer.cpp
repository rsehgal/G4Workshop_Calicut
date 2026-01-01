#include "PSD_Digitizer.h"
#include "G4DigiManager.hh"
#include "PSD_HitCollections.h"
#include "PSD_Digit.h"
#include "G4SystemOfUnits.hh"
#include "PSD_Global.h"
#include "Randomize.hh"
#include "TH1F.h"
PSD_Digitizer::PSD_Digitizer(const G4String &name) : G4VDigitizerModule(name)//, fShort(shortGate), fLong(longGate)
{
  collectionName.push_back("MyDigiCollection");
}

/*PSD_Digitizer::PSD_Digitizer(const G4String &name, const G4String &collName, short int sGate, short int lGate)
    : G4VDigitizerModule(name), fShort(sGate), fLong(lGate)*/
PSD_Digitizer::PSD_Digitizer(const G4String &name, const G4String &collName)
    : G4VDigitizerModule(name)

{
  collectionName.push_back(collName);
}

PSD_Digitizer::~PSD_Digitizer() {}

double PSD_Digitizer::SinglePhotoelectronResponse(double dt)
{
  double tauRise  = 14 * ns; // 1.0 * ns;
  double tauDecay = 3 * ns;  // 10.0 * ns;
  /*double tauRise  = 3*ns;//1.0 * ns;
  double tauDecay = 14*ns;//10.0 * ns;*/

  if (dt < 0) return 0;
  return (exp(-dt / tauDecay) - exp(-dt / tauRise));
}

void PSD_Digitizer::Digitize()
{
  // std::cout << "Digitize function called........." << std::endl;
  G4DigiManager *digiMgr          = G4DigiManager::GetDMpointer();
  G4int hitCollectionID           = digiMgr->GetHitsCollectionID("pmtHitCollection_1");
  PmtHitCollection *hitCollection = (PmtHitCollection *)(digiMgr->GetHitsCollection(hitCollectionID));
  DigiCollection *digiCollection  = new DigiCollection("V1730", "TestDigits");
  if (hitCollection) {
    // Define sampling parameters
    // const G4double binSize = 0.5 * ns;
    // const G4int numBins    = 10;
    std::vector<double> waveform(numBins, 0.0);

    //  Loop through hits (photons)
    /*    for (G4int i = 0; i < hitCollection->entries(); i++) {
          G4double t_hit = (*hitCollection)[i]->GetArrivalTime();

          // 4. Convolve hit with response function S(t)
          for (G4int j = 0; j < numBins; j++) {
            G4double t_current = j * binSize;
            if (t_current > t_hit) {
              waveform[j] += SinglePhotoelectronResponse(t_current - t_hit);
            }
          }
        }
    */
    for (G4int i = 0; i < hitCollection->entries(); i++) {
      G4double t_hit     = (*hitCollection)[i]->GetArrivalTime();
      G4double gainScale = G4RandGauss::shoot(1.0, 0.3);

      // Find exactly where this photon starts in our waveform
      G4int startBin = std::floor(t_hit / binSize);

      // If the photon arrives after our recording window, skip it
      if (startBin >= numBins) continue;

      // Only loop from the startBin forward to save CPU time
      for (G4int j = startBin; j < numBins; j++) {
        G4double t_current = j * binSize;
        G4double dt        = t_current - t_hit; // Time since photon arrived

        // Add the SPE response to the existing waveform
        if (j < 0 || j > numBins) {
          // std::cerr << "Unexpected Arrival time detected..... Hence skipping the Hit......." << std::endl;
          break;
        }
        waveform[j] += gainScale * SinglePhotoelectronResponse(dt);
      }
    }

    PSD_Digit *digit = new PSD_Digit();
    digit->SetWaveform(waveform);
    // digit->Print();

    //std::cout <<"Qlong : " << Energy(waveform) << " :: QShort : " << EnergyShort(waveform) << std::endl;
    digiCollection->insert(digit);
  }
  StoreDigiCollection(digiCollection);
}

/*double PSD_Digitizer::Integral(std::vector<double> waveform, short int gateWidth)
{
  TH1F *hist = new TH1F("waveForm", "waveForm", waveform.size(), 0, waveform.size());

  for (unsigned int i = 0; i < waveform.size(); i++) {
    hist->SetBinContent(i, waveform[i]);
  }

  double integral = hist->Integral(0, gateWidth);
  delete hist;
  return integral;
}

double PSD_Digitizer::Energy(std::vector<double> waveform)
{
  return Integral(waveform, fLong);
}

double PSD_Digitizer::EnergyShort(std::vector<double> waveform)
{
  return Integral(waveform, fShort);
}*/
