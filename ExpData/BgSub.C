/*
**	Filename : BgSub.C
**	2025-02-18
**	username : rsehgal
*/

void BgSub(){
TFile *bg = new TFile("bg.org.root","r");
TFile *ba = new TFile("ba.org.root","r");
TFile *cs = new TFile("cs.org.root","r");
TFile *co = new TFile("co.org.root","r");
TH1F *histBg = (TH1F*)bg->Get("Data");
TH1F *histBa = (TH1F*)ba->Get("Data");
TH1F *histCs = (TH1F*)cs->Get("Data");
TH1F *histCo = (TH1F*)co->Get("Data");

unsigned int nbinsX = histBg->GetNbinsX();

TH1F *histCsBgSub = new TH1F("histCsBgSub","histCsBgSub",2048,0,2048);
TH1F *histCoBgSub = new TH1F("histCoBgSub","histCoBgSub",2048,0,2048);
TH1F *histBaBgSub = new TH1F("histBaBgSub","histBaBgSub",2048,0,2048);


for(unsigned int i = 0 ; i < nbinsX ; i++){
   histCsBgSub->SetBinContent(i,histCs->GetBinContent(i)-histBg->GetBinContent(i));
   histCoBgSub->SetBinContent(i,histCo->GetBinContent(i)-histBg->GetBinContent(i));
   histBaBgSub->SetBinContent(i,histBa->GetBinContent(i)-histBg->GetBinContent(i));
}

histCs->SetLineColor(2);
histCs->SetLineWidth(2);

TCanvas *canCs = new TCanvas("Cesium","Cesium");
canCs->cd();
histCs->Draw("hist");
histCsBgSub->SetLineColor(1);
histCsBgSub->Draw("histsame");
histBg->SetLineColor(4);
histBg->Draw("histsame");

TCanvas *canCo=new TCanvas("Cobalt","Cobalt");
canCo->cd();
histCoBgSub->Draw("hist");

TCanvas *canBa=new TCanvas("Barium","Barium");
canBa->cd();
histBaBgSub->Draw("hist");
}
