#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TMath.h>
#include "TApplication.h"

struct Hit {
    double x, y;
};

// Hough Transform Parameters
const int thetaBins = 180;
const int rhoBins = 200;
const double rhoMax = 1.0;
const double thetaMax = TMath::Pi();

void HoughTransformTrackFinding() {
  
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
    
    std::map<int, std::vector<Hit>> tracks;
    Long64_t nEntries = tree->GetEntries();
    
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        Hit hit = {posX * 0.001, posY * 0.001}; // Convert mm to meters
        tracks[(int)eventNo].push_back(hit);
    }
    
    // Create Hough space histogram
    TH2D *hHough = new TH2D("hHough", "Hough Transform; Theta (rad); Rho (m)", 
                             thetaBins, 0, thetaMax, rhoBins, -rhoMax, rhoMax);
    
    for (const auto &track : tracks) {
        const std::vector<Hit> &hits = track.second;
        
        for (const auto &hit : hits) {
            for (int t = 0; t < thetaBins; t++) {
                double theta = t * (thetaMax / thetaBins);
                double rho = hit.x * cos(theta) + hit.y * sin(theta);
                hHough->Fill(theta, rho);
            }
        }
    }
    
    // drawing histogram (hough transform)
    TCanvas *c1 = new TCanvas("c1", "Hough Transform", 800, 600);
    hHough->Draw("COLZ");
    c1->SaveAs("HoughTransform.png");
    
  
    file->Close();
    //delete file;
   // delete c1;
}

int main(int argc, char **argv) {
	
	TApplication app("app", &argc, argv);
	
    HoughTransformTrackFinding();
    
    app.Run();
    return 0;
}

