#include <iostream>
#include <vector>
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"

void fitResolution() {
    TFile *fp = new TFile("responseFunc.root","RECREATE");
    // Data
    //std::vector<float> peakPos = {356., 662., 1172., 1330.};
    //std::vector<float> sigma = {51.95, 48.99, 60.72, 65.41};

    std::vector<float> peakPos = { 662., 1172., 1330.};
    std::vector<float> sigma = {48.99, 60.72, 65.41};

    int nPoints = peakPos.size();
    TGraph *graph = new TGraph(nPoints, &peakPos[0], &sigma[0]);

    // Define resolution function: sigma(E) = a*sqrt(E) + b
    //TF1 *resFunc = new TF1("resFunc", "[0]*sqrt(x) + [1]", 300, 1400);
    TF1 *resFunc = new TF1("resFunc", "[0] + [1]*sqrt(x) + [2]*x", 0, 3000); 
    resFunc->SetParameters(1.0, 0.1, 0.001); 
    //resFunc->SetParameters(1.0, 1.0); // Initial guess

    // Fit
    graph->Fit(resFunc, "R");
    fp->cd();
    resFunc->Write();
    fp->Close();

    // Draw
    TCanvas *c1 = new TCanvas("c1", "Resolution Fit", 800, 600);
    graph->SetMarkerStyle(20);
    graph->SetTitle("Energy Resolution Fit;Energy (keV);Sigma (keV)");
    graph->Draw("AP");
    resFunc->Draw("same");

    
    // Print fit parameters
    double a = resFunc->GetParameter(0);
    double b = resFunc->GetParameter(1);
    std::cout << "Fitted parameters: a = " << a << ", b = " << b << std::endl;
}

