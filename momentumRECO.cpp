#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <TApplication.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>
#include <TVector3.h>
const double TeslaToGeV = 0.3; // Conversion factor for B field (T*m to GeV/c)

// const double TeslaToGeV = 300;  // Conversion factor for B field (T*m to MeV/c)

struct Hit {
  double x, y, z;
};

TVector3 GetVector3D(Hit hit)
{
  return TVector3(hit.x, hit.y, hit.z);
}

double PerpendicularDistance(TVector3 P, TVector3 A, TVector3 B)
{
  TVector3 u = P - A;
  TVector3 v = B - A;
  return (u.Cross(v).Mag() / v.Mag());
}

double GetMomentumSagitta_V2(std::vector<TVector3> hits, double B)
{

  TVector3 first = hits[0];
  TVector3 last  = hits[hits.size() - 1];
  double L       = (last - first).Mag();
  double sMax    = 0;
  for (unsigned int i = 1; i < hits.size() - 1; i++) {
    double s = PerpendicularDistance(hits[i], first, last);
    if (s > sMax) sMax = s;
  }

  if (L == 0 || sMax == 0) return 0.0; // to avoid division by zero

  return (TeslaToGeV * B * L * L) / (8.0 * sMax); // Momentum estimation
}

void AnalyzeMomentumSagitta()
{
  double B = 1.0; // Magnetic field in Tesla

  // Open ROOT file
  TFile *file = new TFile("tracking.root", "READ");

  TTree *tree;
  file->GetObject("Tracking", tree);

  double posX, posY, posZ, smearedPosX, smearedPosY, smearedPosZ;
  double momentumX, momentumY, momentumZ;
  double layerNo, eventNo;

  tree->SetBranchAddress("posX", &posX);
  tree->SetBranchAddress("posY", &posY);
  tree->SetBranchAddress("posZ", &posZ);
  tree->SetBranchAddress("smearedPosX", &smearedPosX);
  tree->SetBranchAddress("smearedPosY", &smearedPosY);
  tree->SetBranchAddress("smearedPosZ", &smearedPosZ);
  tree->SetBranchAddress("momentumX", &momentumX);
  tree->SetBranchAddress("momentumY", &momentumY);
  tree->SetBranchAddress("momentumZ", &momentumZ);
  tree->SetBranchAddress("layerNo", &layerNo);
  tree->SetBranchAddress("eventNo", &eventNo);

  TH1D *hMomentumG4 = new TH1D("hMomentumG4", "Momentum Distribution in MeV from Geant4", 200, 1050, 1150);
  hMomentumG4->SetLineColor(1);
  hMomentumG4->SetTitle("Geant4");
  hMomentumG4->SetLineWidth(2);
  TH1D *hMomentumSagitta = new TH1D("hMomentumSagitta", "Momentum Distribution in MeV from Sagitta", 200, 1050, 1150);
  hMomentumSagitta->SetLineColor(2);
  hMomentumSagitta->SetTitle("Sagitta");
  hMomentumSagitta->SetLineWidth(2);

  TH1D *hMomentumResidual = new TH1D("hMomentumResidual", "Residual Distribution in MeV from Two Methods", 200, -10, 10);
  hMomentumResidual->SetLineColor(4);
  hMomentumResidual->SetTitle("Residual Distribution");
  hMomentumResidual->SetLineWidth(2);

  TCanvas *can = new TCanvas;
  can->Divide(2, 2);
  // store hits grouped by event number
  std::map<int, std::vector<TVector3>> tracks;
  std::map<int, std::vector<TVector3>> momentumMap;

  Long64_t nEntries = tree->GetEntries();
  for (Long64_t i = 0; i < nEntries; i++) {
    tree->GetEntry(i);

    TVector3 hit      = 0.001 * TVector3(posX, posY, posZ); // mm to m
    TVector3 momentum = 0.001 * TVector3(momentumX, momentumY, momentumZ); //MeV to GeV

    tracks[(int)eventNo].push_back(hit);
    momentumMap[(int)eventNo].push_back(momentum);
  }

  // calculating momentum using sagitta
  for (unsigned int eventId = 0; eventId < tracks.size(); eventId++) {

    const std::vector<TVector3> hits        = tracks[eventId];
    const std::vector<TVector3> momentumVec = momentumMap[eventId];
    std::cout << "----------- Event No : " << eventId << " ---------------" << std::endl;

    if (hits.size() < 3) {
      continue;
    }
    /*for (unsigned int i = 0; i < hits.size(); i++) {
      std::cout << hits[i].X() << "," << hits[i].Y() << "," << hits[i].Z() << std::endl;
    }*/

    double momentumSagitta = GetMomentumSagitta_V2(hits, B);

    // getting momentum from G4 from the last layer
    double momentumG4 = momentumVec[momentumVec.size() - 1].Mag();
    std::cout << "G4Momentum : " << momentumG4 << " : Sagitta Momentum : " << momentumSagitta << std::endl;
    if (momentumG4*1000. > 1.) {
      hMomentumG4->Fill(momentumG4*1000.);
      hMomentumSagitta->Fill(momentumSagitta*1000.);
      hMomentumResidual->Fill(momentumG4*1000.-momentumSagitta*1000.);
    }
  }
  can->cd(1);
  hMomentumG4->Draw("hist");
  can->cd(2);
  hMomentumSagitta->Draw("hist");
  can->cd(3);
  hMomentumResidual->Draw("hist");
  can->SaveAs("Momentum_Comparison.png");

  TFile *outputFile = new TFile("MomentumComparison.root", "RECREATE");
    hMomentumG4->Write();
    hMomentumSagitta->Write();
    hMomentumResidual->Write();
    outputFile->Close();
}

int main(int argc, char **argv)
{

  TApplication app("app", &argc, argv);
  AnalyzeMomentumSagitta();
  app.Run();

  return 0;
}

// g++ momentumRECO.cpp `root-config --cflags --libs` -o momentumRECO
