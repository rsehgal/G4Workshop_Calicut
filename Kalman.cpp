//g++ Kalman.cpp `root-config --cflags --libs` -o kalman

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

// ROOT includes
#include "TFile.h"
#include "TF1.h"
#include "TTree.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TApplication.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TROOT.h"


// Detector resolution (in cm)
const double sigma_meas = 10; //0.01;  // 0.01 cm resolution
const double sigma2 = sigma_meas * sigma_meas;
//  distance between two detector 
const double layerSpacing = 10.0; // 10 cm

// Structure to hold a hit.
struct Hit {
    double x;
    double y;
    double z;
};

// state vector: (x, y, dx/dz, dy/dz, q/p)
class KalmanFilter {
public:
    TVectorD state; // 5-element state vector
    TMatrixD cov;   // 5x5 covariance matrix

    KalmanFilter() : state(5), cov(5,5) {
        state.Zero();
        cov.Zero();
    }

    // Initialize kalman 
  
    void Initialize(const std::vector<Hit>& hits, double q_over_p_nominal = 1.0) {
        // Use the first hit for position.
        state[0] = hits[0].x;
        state[1] = hits[0].y;
        // Estimate slopes if possible.
        if (hits.size() >= 2) {
            double dz = hits[1].z - hits[0].z;
            if (std::fabs(dz) > 1e-6) {
                state[2] = (hits[1].x - hits[0].x) / dz;
                state[3] = (hits[1].y - hits[0].y) / dz;
            } else {
                state[2] = 0.0;
                state[3] = 0.0;
            }
        } else {
            state[2] = 0.0;
            state[3] = 0.0;
        }
        // Set q/p from nominal value.
        state[4] = q_over_p_nominal;

        // Initialize the covariance matrix.
        cov(0,0) = sigma2;
        cov(1,1) = sigma2;
        cov(2,2) = 0.01;
        cov(3,3) = 0.01;
        cov(4,4) = 0.01;
    }

    // Predict the state at the next measurement plane.
    // use the fixed layer spacing (dz = 10 cm).
    void Predict() {
        double dz = layerSpacing;  // Fixed 10 cm between layers
        TVectorD newState(5);
        newState[0] = state[0] + state[2] * dz;
        newState[1] = state[1] + state[3] * dz;
        newState[2] = state[2];
        newState[3] = state[3];
        newState[4] = state[4];

        TMatrixD F(5,5);
        F.UnitMatrix();
        F(0,2) = dz;
        F(1,3) = dz;
        
        TMatrixD Q(5,5);
        Q.UnitMatrix();
        Q *= 0.01; //tune Q
        
        TMatrixD newCov = F * cov * TMatrixD(TMatrixD::kTransposed, F) + Q;   

        state = newState;
        cov = newCov;
    }

    // Update the state with a new measurement.
    // Measurement: (x, y).
    void Update(const Hit &hit) {
        TVectorD meas(2); //zk
        meas[0] = hit.x;
        meas[1] = hit.y;

        TVectorD h(2); //xk
        h[0] = state[0];
        h[1] = state[1];

        TVectorD r = meas - h; // r=yk

        TMatrixD H(2,5); 
        H.Zero();
        H(0,0) = 1.0;
        H(1,1) = 1.0;

        TMatrixD R(2,2);
        R.Zero();
        R(0,0) = sigma2;
        R(1,1) = sigma2;

        TMatrixD Ht(TMatrixD::kTransposed, H);
        TMatrixD S = H * cov * Ht + R;
        TMatrixD K = cov * Ht;
        S.Invert();
        K *= S;  //kalman Gain

        state = state + K * r; // updated state estimate

        TMatrixD I(5,5);
        I.UnitMatrix();
        cov = (I - K * H) * cov; //updated error covariance
    }
};

int main(int argc, char **argv) {
	
	TApplication app("app", &argc, argv);
    // Open the ROOT file.
    TFile *file = TFile::Open("tracking.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file tracking.root" << std::endl;
        return 1;
    }

    // Get the TTree (assumed to be named "tree")
    TTree *tree = (TTree*)file->Get("Tracking");
    if (!tree) {
        std::cerr << "Error: TTree 'tree' not found in file" << std::endl;
        return 1;
    }
    
   // TH1D *hPosX = new TH1D("hPosX", "Position X Distribution; X (cm); Events", 100, -1000., 1000.);
    TH1D *hPosX = new TH1D("hPosX", " ActualX - SmearedX; X (cm); Events", 200, -100., 100.);
    TH1D *hSmearedX = new TH1D("hSmearedX", "Smeared X Distribution; X (cm); Events", 100, -1000., 1000.);
    TH1D *hKalmanX = new TH1D("hKalmanX", "Kalman X Distribution; X (cm); Events", 100, -1000., 1000.);
    
    
  TH1D *hMomentumResidual = new TH1D("xpositionResidual", "ActualX-KalmanX", 200, -100, 100);
  hMomentumResidual->SetLineColor(4);
  hMomentumResidual->SetTitle("ActualX-KalmanX");
  hMomentumResidual->SetLineWidth(2);
    

 
    double posX, posY, posZ, smearedPosX,smearedPosY,smearedPosZ;
    double momentumX, momentumY, momentumZ;
    double eventNo,layerNo;
    
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

    std::map<int, std::vector<Hit>> eventHits;
    
    std::map<int, std::map<int, double>> truePosX; // Store true posX by eventNo and layerNo

    
    
    
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        Hit hit;
        
        hit.x = smearedPosX;
        hit.y = smearedPosY;
        hit.z = smearedPosZ;
        
     
        
        hPosX->Fill(posX-smearedPosX);
    
        truePosX[eventNo][layerNo] = posX; // Store true posX per event and layer
        
        eventHits[eventNo].push_back(hit);
    }


    // Loop over events; for demonstration, process event 0.
    bool drawEvent0 = true;
    for (auto &entry : eventHits) {
        int evt = entry.first;
        std::vector<Hit> &hits = entry.second;
        std::sort(hits.begin(), hits.end(), [](const Hit &a, const Hit &b) {
            return a.z < b.z;
        });
        if (hits.size() < 2)
            continue;
        
        // Estimate q/p using momentum information from branches (using a nominal value here).
        double p = std::sqrt(momentumX * momentumX + momentumY * momentumY + momentumZ * momentumZ);
        double q_over_p = (p > 1e-6) ? (1.0 / p) : 1.0;

        KalmanFilter kf;
        kf.Initialize(hits, q_over_p);

        // Vectors for reconstructed (filtered) positions.
        std::vector<double> kf_x, kf_y;
        // Vectors for raw measured positions.
        std::vector<double> raw_x, raw_y;

        kf_x.push_back(kf.state[0]);
        kf_y.push_back(kf.state[1]);
        raw_x.push_back(hits[0].x);
        raw_y.push_back(hits[0].y);

        // For each subsequent layer, use the fixed dz = 10 cm.
        for (size_t i = 1; i < hits.size(); i++) {
            kf.Predict();      // Uses dz = 10 cm (layerSpacing)
            kf.Update(hits[i]);
            kf_x.push_back(kf.state[0]);
            kf_y.push_back(kf.state[1]);
            raw_x.push_back(hits[i].x);
            raw_y.push_back(hits[i].y);
            
            double kalman_x = kf.state[0]; // Fitted x from Kalman filter
            double true_x = truePosX[evt][i]; // True posX from stored values
            double smeared_x = hits[i].x; // Measured x (smeared)

             hMomentumResidual->Fill(true_x - kalman_x);
            // hPosX->Fill(true_x - smeared_x);
            
           // hKalmanX->Fill(kf.state[0]);
            
          //  hSmearedX->Fill(hits[i].x);
            
          //  hMomentumResidual->Fill(orighits[i].x-kf.state[0]);
          
            
          
        }

        std::cout << "Event " << evt << " final state:" << std::endl;
        std::cout << " x = " << kf.state[0] << ", y = " << kf.state[1] << std::endl;
        std::cout << " dx/dz = " << kf.state[2] << ", dy/dz = " << kf.state[3] << std::endl;
        std::cout << " q/p = " << kf.state[4] << std::endl;

    }
    

  TCanvas *c1 = new TCanvas("c1", "Residuals", 1920, 1080);
  c1->Divide(2, 1);


    // Set styles for PosX histogram
hPosX->SetLineColor(kBlue);  // Blue color
hPosX->SetLineWidth(2);
hPosX->SetLineStyle(2);      // Dashed line
hPosX->SetMarkerColor(kBlack);



    
    // Set styles for smearedPosX histogram
hSmearedX->SetLineColor(kBlue);  // Blue color
hSmearedX->SetLineWidth(2);
hSmearedX->SetLineStyle(2);      // Dashed line
hSmearedX->SetMarkerStyle(21);
hSmearedX->SetMarkerColor(kBlue);

// Set styles for Kalman-filtered X histogram
hKalmanX->SetLineColor(kGreen);  // Green color
hKalmanX->SetLineWidth(2);
hKalmanX->SetLineStyle(3);       // Dotted line
hKalmanX->SetMarkerStyle(22);
hKalmanX->SetMarkerColor(kGreen);

c1->cd(1);
hPosX->Draw("hist");
//c1->cd(1);
//hSmearedX->Draw("hist");
//c1->cd(1);
//hKalmanX->Draw("hist");
c1->cd(2);
hMomentumResidual->Draw("hist");

c1->SaveAs("HistogramComparison.png");

    file->Close();
    app.Run();
    return 0;
}
