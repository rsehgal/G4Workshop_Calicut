#include <TApplication.h>
#include <TArrayS.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TLine.h>
#include <TTree.h>
#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

std::vector<float> t;
/*struct CFDResult {
    std::vector<float> bipolarPulse;
    float zeroCrossingSample; // Fractional sample index
};

CFDResult CalculateCFD(const std::vector<float>& signal, int delay, float
fraction) { CFDResult result; size_t n = signal.size();
    result.bipolarPulse.assign(n, 0.0f);

    // 1. Generate Bipolar Waveform: B(i) = (Signal[i] * fraction) - Signal[i -
delay] for (size_t i = delay; i < n; ++i) { result.bipolarPulse[i] = (signal[i]
* fraction) - signal[i - delay];
    }

    // 2. Find Zero Crossing
    // We look for the transition from positive to negative on the leading edge.
    // Note: Since your pulse is negative-going, the logic depends on polarity.
    result.zeroCrossingSample = -1.0f; // Default if not found

    for (size_t i = delay + 1; i < n; ++i) {
        // Looking for the zero-crossing point on the steep rise/fall
        if (result.bipolarPulse[i-1] > 0 && result.bipolarPulse[i] <= 0) {

            // Linear Interpolation for sub-sample precision:
            // y = mx + c -> solve for y=0
            float y1 = result.bipolarPulse[i-1];
            float y2 = result.bipolarPulse[i];
            float fractionalPart = y1 / (y1 - y2);

            result.zeroCrossingSample = static_cast<float>(i - 1) +
fractionalPart; break; // Capture the first valid crossing
        }
    }

    return result;
}*/

#include <algorithm>
#include <cmath>
#include <vector>

struct CFDResult {
  std::vector<float> bipolarPulse;
  float zeroCrossingSample;
};

CFDResult CalculateCFD(const std::vector<float> &smoothedSignal, int delay,
                       float fraction, float armingThreshold = 10) {
  CFDResult result;
  size_t n = smoothedSignal.size();
  result.bipolarPulse.assign(n, 0.0f);

  // 1. Generate Bipolar Waveform
  // Formula: B[i] = (Signal[i] * fraction) - Signal[i - delay]
  for (size_t i = delay; i < n; ++i) {
    result.bipolarPulse[i] =
        (smoothedSignal[i] * fraction) - smoothedSignal[i - delay];
  }

  // 2. Search for the valid Zero-Crossing
  result.zeroCrossingSample = -1.0f;

  for (size_t i = 1; i < n; ++i) {
    // A: Look for the Negative-to-Positive crossing
    if (result.bipolarPulse[i - 1] < 0 && result.bipolarPulse[i] >= 0) {

      // B: ARMING GATE - Crucial for Negative Pulses
      // Check if the original pulse is deep enough at this moment.
      // Since your pulse is negative, 'smoothedSignal[i]' will be a negative
      // value (e.g., -30). We use the absolute value to compare against your
      // positive arming threshold.
      if (std::abs(smoothedSignal[i]) > armingThreshold) {
        float y1 = result.bipolarPulse[i - 1];
        float y2 = result.bipolarPulse[i];

        // Linear Interpolation for sub-sample precision
        // The distance between samples is 1.0.
        // fractionalPart = distance from (i-1) to the zero point.
        float fractionalPart = (-y1) / (y2 - y1);

        result.zeroCrossingSample = static_cast<float>(i - 1) + fractionalPart;

        // We stop at the first valid crossing that passes the arming gate
        break;
      }
    }
  }
  return result;
}

TGraph *GetGraph(std::vector<float> pulse, char *title = "Sampled Pulse") {
  TGraph *gr = new TGraph(t.size(), &t[0], &pulse[0]);
  // gr->SetTitle(Form("Pulse %lld;Sample Index;Amplitude", i));
  gr->SetTitle(title);
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(0.5);

  return gr;
}
std::vector<float> BaselineSubtracted(std::vector<float> pulse, int ns) {
  int n = pulse.size();
  std::vector<float> bs(n);
  int accum = 0;
  for (unsigned int i = 0; i < ns; i++) {
    accum += pulse[i];
  }
  accum /= ns;

  for (int i = 0; i < n; i++) {
    bs[i] = pulse[i] - accum;
  }
  return bs;
}

std::vector<float> MedianFilter(std::vector<float> pulse, int windowSize) {
  int n = pulse.size();
  std::vector<float> cleaned(n);
  int edge = windowSize / 2;

  for (int i = 0; i < n; i++) {
    std::vector<float> window;
    for (int j = i - edge; j <= i + edge; j++) {
      if (j >= 0 && j < n)
        window.push_back(pulse[j]);
    }
    // Sort the window to find the median
    std::sort(window.begin(), window.end());
    cleaned[i] = window[window.size() / 2];
  }
  return cleaned;
}

std::vector<float> MovingAverage(std::vector<float> pulse, int ns) {
  int n = pulse.size();
  std::vector<float> smoothedPulse(n);
  int half = ns / 2;

  for (int i = 0; i < n; i++) {
    float sum = 0;
    int count = 0;
    // Centered window: i - half to i + half
    for (int j = i - half; j <= i + half; j++) {
      if (j >= 0 && j < n) {
        sum += pulse[j];
        count++;
      }
    }
    smoothedPulse[i] = sum / count;
  }
  return smoothedPulse;
}
#if (0)
std::vector<float> MovingAverage(std::vector<float> pulse, unsigned short ns) {
  int pulseLen = pulse.size();
  if (pulseLen > ns) {

    std::vector<float> smoothedPulse;
    for (unsigned int i = 0; i < pulse.size(); i++) {
      if (i < ns) {
        smoothedPulse.push_back(pulse[i]);
      } else {

        float smoothedValue = 0;
        for (unsigned int j = 0; j < ns; j++) {
          smoothedValue += pulse[i - j];
        }
        smoothedValue /= ns;
        smoothedPulse.push_back(smoothedValue);
      }
    }
    return smoothedPulse;
  } else {
    std::cout << "Pulse size is less than smoothing window size...."
              << std::endl;
    return pulse;
  }
}
#endif

int main(int argc, char *argv[]) {

  TApplication *fApp = new TApplication("fApp",NULL,NULL);
  TFile *fp = new TFile(argv[1], "r");
  TTree *Data_F = (TTree *)fp->Get("Data_F");
  // Declaration of leaves types
  UShort_t Channel;
  ULong64_t Timestamp;
  UShort_t Board;
  UShort_t Energy;
  UShort_t EnergyShort;
  UInt_t Flags;
  Int_t Probe;
  TArrayS *Samples;

  // Set branch addresses.
  Data_F->SetBranchAddress("Channel", &Channel);
  Data_F->SetBranchAddress("Timestamp", &Timestamp);
  Data_F->SetBranchAddress("Board", &Board);
  Data_F->SetBranchAddress("Energy", &Energy);
  Data_F->SetBranchAddress("EnergyShort", &EnergyShort);
  Data_F->SetBranchAddress("Flags", &Flags);
  Data_F->SetBranchAddress("Probe", &Probe);
  Data_F->SetBranchAddress("Samples", &Samples);

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // Data_F->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries = Data_F->GetEntries();

  // std::vector<float>t;
  int numOfSamples = 120;

  for (unsigned int i = 0; i < numOfSamples; i++) {

    t.push_back(i);
  }
  auto pulseNum = std::atoi(argv[2]); // 10;
  std::vector<float> pulse;
  Long64_t nbytes = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += Data_F->GetEntry(i);

    pulse.clear();
    for (unsigned int j = 0; j < Samples->GetSize(); j++) {
      pulse.push_back(Samples->GetAt(j));
    }

    /*if (i == pulseNum) {
      std::cout << "Pulse size : " << pulse.size() << std::endl;
*/

     std::vector<float> bs =
          BaselineSubtracted(MovingAverage(MedianFilter(pulse, 10), 6), 16);

      CFDResult res = CalculateCFD(bs, 5, 0.3);
      unsigned short preTrigger = 32;
      unsigned short timePeriod = 1;
      ULong64_t fineTs = Timestamp + (res.zeroCrossingSample - preTrigger) *
                                         timePeriod * 1000.;

      std::cout << "FineTs : " << fineTs << std::endl;
    //}
  }

//fApp->Run();
//return 0;
}
