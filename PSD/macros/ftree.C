void ftree(char *filename, int neutron = 0)
{
  TH2F *psd = new TH2F("psd", "psd", 1000, 0, 1000, 1000, 0, 1);

  TFile *f     = new TFile(filename, "r");
  TTree *ftree = (TTree *)f->Get("ftree");

  vector<int> *pulse = nullptr;

  ftree->SetBranchAddress("pulse", &pulse);

  Long64_t nentries = ftree->GetEntries();

  Long64_t nbytes      = 0;
  double meanDecayTime = 0.;
  int meanDecayCounter = 0;
  int breakCounter     = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += ftree->GetEntry(i);
    // std::cout << "Pulse Size : " << pulse->size() << std::endl;
    if (pulse->size() < 4) continue;

    TH1F *hist = new TH1F("pulse", "pulse", 150, 0, 150);

    std::cout << "--------------------------------------" << std::endl;

    if (pulse->size() > 4) {
      for (unsigned int j = 0; j < pulse->size(); j++) {
        // std::cout << "Arrival Time : " << pulse->at(j) << std::endl;
        hist->Fill(pulse->at(j));
      }
	
      int maxBin    = hist->GetMaximumBin();
      double startX = hist->GetBinCenter(maxBin);
      std::cout << "STARTX : " << startX << std::endl;

      // 3. Define fit range: from max bin to the end of histogram
      double longWindow  = 140;
      double shortWindow = 15.;
      double endX        = shortWindow;
      // if (std::string(filename) == "neutron.root")
      if (neutron) endX = longWindow;
      // hist->GetBinLowEdge(hist->GetNbinsX() + 1); // upper edge of last bin

      // 4. Create exponential fit function (3 parameters: A*exp(-x/tau))
      TF1 *expo = new TF1("expo", "[0]*exp(-x/[1])", startX, endX);
      expo->SetParameters(hist->GetBinContent(maxBin), 5); // initial guess: amplitude, decay constant
                                                                 // 5. Fit

      hist->Fit(expo, "Rq"); // "R" = restrict fit to given range

      if (expo->GetParameter(1) > 35) continue;

      // Optional: Print result
      std::cout << "Fit result: A = " << expo->GetParameter(0) << ", tau = " << expo->GetParameter(1) << std::endl;

      meanDecayTime += expo->GetParameter(1);
      meanDecayCounter++;

      double qlong  = hist->Integral(hist->FindBin(0), hist->FindBin(longWindow));
      double qshort = hist->Integral(hist->FindBin(0), hist->FindBin(shortWindow));
      std::cout << "QLong : " << qlong << " : QShort : " << qshort << std::endl;
      double PSD = (qlong - qshort) / qlong;
      std::cout << "PSD : " << PSD << std::endl;
      psd->Fill(qlong, PSD);

      std::cout << "Pulse size : " << pulse->size() << std::endl;

      /*if(breakCounter < 10)
    breakCounter++;
    else
        break;*/
    }
      else
      {
        continue;
      }

  }

  std::cout << "=============================" << std::endl;
  meanDecayTime /= meanDecayCounter;
  std::cout << "Decay Constant of scintillator : " << meanDecayTime << std::endl;
  std::cout << "Number of Pulses used : " << meanDecayCounter << std::endl;

  std::cout << "=============================" << std::endl;
  psd->Draw("colz");
  // hist->Draw("same");
}
