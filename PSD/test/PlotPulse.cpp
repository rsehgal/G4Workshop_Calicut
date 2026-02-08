#include <TApplication.h>
#include <TArrayS.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TTree.h>
#include <iostream>
#include <vector>

std::vector<float> t;

TGraph *GetGraph(std::vector<float> pulse) {
  TGraph *gr = new TGraph(t.size(), &t[0], &pulse[0]);
  // gr->SetTitle(Form("Pulse %lld;Sample Index;Amplitude", i));
  gr->SetTitle("Sampled Pulse");
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(0.5);

  return gr;
}
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

int main(int argc, char *argv[]) {

  TApplication *fApp = new TApplication("fApp", NULL, NULL);
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
  auto pulseNum = 10;
  std::vector<float> pulse;
  Long64_t nbytes = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += Data_F->GetEntry(i);

    pulse.clear();
    for (unsigned int j = 0; j < Samples->GetSize(); j++) {
      pulse.push_back(Samples->GetAt(j));
    }

    if (i == pulseNum) {
      // 1. Explicitly create a canvas
      TCanvas *can = new TCanvas("can", "Pulse Plot", 800, 600);
      can->Divide(2, 1);

      std::cout << "Pulse size : " << pulse.size() << std::endl;

      // 2. Create the graph

      // 3. Draw and Force Update
      can->cd(1);
      TGraph *gr = GetGraph(pulse);
      gr->Draw("ACP"); // A=Axes, L=Line, P=Points


      can->cd(2);
      TGraph *gr2 = GetGraph(MovingAverage(pulse,6));
      gr2->Draw("ACP"); // A=Axes, L=Line, P=Points


      can->Update();
      can->Modified();

      break; // Exit loop to keep this pulse on screen
    }
  }

  fApp->Run();
}
