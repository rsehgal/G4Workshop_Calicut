#include <fstream>
#include <TH1F.h>
void Calibrate(char *filename)
{
  TFile *fCali = new TFile("energyCalib.root","r");
  TF1 *calibFormula = (TF1*)fCali->Get("pol2");
  fCali->Close();

  std::string rootFile=std::string(filename)+"_calibrated.root";
  TFile *fp = new TFile(rootFile.c_str(),"RECREATE");
  std::ifstream infile(filename);
  TH1F *hist = new TH1F("Data","Data",2048,0,2048);
  double channel=0, value=0;
  while (!infile.eof()) {
	infile >> channel >> value ;
	hist->SetBinContent(calibFormula->Eval(channel+35),value);
  }
  infile.close();
  fp->cd();
  hist->Write();
  fp->Close();
  //hist->Draw("hist");

  
}
