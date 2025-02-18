#include <vector>

void energyCalib(){
  TFile *fp = new TFile("energyCalib.root","RECREATE");
  std::vector<float> channel={288,507,866,974};
  std::vector<float> energy={356.,662.,1174.,1332.};
  TGraph *gr = new TGraph(energy.size(),&channel[0],&energy[0]);
  gr->Draw("ap");
  gr->SetMarkerStyle(8);

  TF1 *formula = new TF1("pol2","pol2",0,1500);
  gr->Fit(formula,"R");
  
  fp->cd();
  gr->Write();
  formula->Write();
  fp->Close();
}
