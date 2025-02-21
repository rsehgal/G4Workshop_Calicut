/*
**	Filename : BgSub.C
**	2025-02-18
**	username : rsehgal
*/

void CalibrateBgSub(){

TFile *fCali = new TFile("energyCalib.root","r");
TF1 *calibFormula = (TF1*)fCali->Get("pol2");
fCali->Close();


TFile *fpBgSub = new TFile("BackgroundSubtracted.root","r");
TH1F *histCsBgSub = (TH1F*)fpBgSub->Get("histCsBgSub");
TH1F *histCoBgSub = (TH1F*)fpBgSub->Get("histCoBgSub");
TH1F *histBaBgSub = (TH1F*)fpBgSub->Get("histBaBgSub");

TFile *fp = new TFile("BackgroundSubtracted_Calibrated.root","RECREATE");
unsigned int nbinsX = histCsBgSub->GetNbinsX();

TH1F *histCalibCsBgSub = new TH1F("histCalibCsBgSub","histCalibCsBgSub",2048,0,2048);
TH1F *histCalibCoBgSub = new TH1F("histCalibCoBgSub","histCalibCoBgSub",2048,0,2048);
TH1F *histCalibBaBgSub = new TH1F("histCalibBaBgSub","histCalibBaBgSub",2048,0,2048);


for(unsigned int i = 0 ; i < nbinsX ; i++){
   histCalibCsBgSub->SetBinContent(calibFormula->Eval(histCsBgSub->GetBinCenter(i)),histCsBgSub->GetBinContent(i));
   histCalibCoBgSub->SetBinContent(calibFormula->Eval(histCoBgSub->GetBinCenter(i)),histCoBgSub->GetBinContent(i));
   histCalibBaBgSub->SetBinContent(calibFormula->Eval(histBaBgSub->GetBinCenter(i)),histBaBgSub->GetBinContent(i));
}


fp->cd();
histCalibCsBgSub->Write();
histCalibCoBgSub->Write();
histCalibBaBgSub->Write();
fp->Close();
fpBgSub->Close();

}
