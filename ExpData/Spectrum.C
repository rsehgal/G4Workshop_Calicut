#include <fstream>
#include <TH1F.h>
void Spectrum(char *filename)
{
  std::string rootFile=std::string(filename)+".root";
  TFile *fp = new TFile(rootFile.c_str(),"RECREATE");
  std::ifstream infile(filename);
  TH1F *hist = new TH1F("Data","Data",2048,0,2048);
  double channel=0, value=0;
  while (!infile.eof()) {
	infile >> channel >> value ;
	hist->SetBinContent(channel,value);
  }
  infile.close();
  fp->cd();
  hist->Write();
  fp->Close();
  //hist->Draw("hist");

  
}
