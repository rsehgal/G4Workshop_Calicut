void ftree(char *filename)
{
  TFile *f     = new TFile(filename, "r");
  TTree *ftree = (TTree *)f->Get("ftree");

  // Declaration of leaves types
  vector<int> *pulse = nullptr;

  // Set branch addresses.
  ftree->SetBranchAddress("pulse", &pulse);

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // ftree->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries = ftree->GetEntries();

  Long64_t nbytes      = 0;
  double meanDecayTime = 0.;
  int meanDecayCounter = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += ftree->GetEntry(i);
    // std::cout << "Pulse Size : " << pulse->size() << std::endl;
    if (pulse->size() < 4) continue;

    TH1F *hist = new TH1F("pulse", "pulse", 150, 0, 150);

    std::cout << "--------------------------------------" << std::endl;

    if (pulse->size() > 1) {
      for (unsigned int j = 0; j < pulse->size(); j++) {
        // std::cout << "Arrival Time : " << pulse->at(j) << std::endl;
        hist->Fill(pulse->at(j));
      }

      int maxBin    = hist->GetMaximumBin();
      double startX = hist->GetBinCenter(maxBin);
      std::cout << "STARTX : " << startX << std::endl;

      // 3. Define fit range: from max bin to the end of histogram
      double endX = 40;
      if (std::string(filename) == "neutron.root") endX = 140;
      // hist->GetBinLowEdge(hist->GetNbinsX() + 1); // upper edge of last bin

      // 4. Create exponential fit function (3 parameters: A*exp(-x/tau))
      TF1 *expo = new TF1("expo", "[0]*exp(-x/[1])", startX, endX);
      expo->SetParameters(hist->GetBinContent(maxBin), 5); // initial guess: amplitude, decay constant

      // 5. Fit
      hist->Fit(expo, "Rq"); // "R" = restrict fit to given range

      // Optional: Print result
      std::cout << "Fit result: A = " << expo->GetParameter(0) << ", tau = " << expo->GetParameter(1) << std::endl;

      meanDecayTime += expo->GetParameter(1);
      meanDecayCounter++;

      // break;
    }
  }

  std::cout << "=============================" << std::endl;
  meanDecayTime /= meanDecayCounter;
  std::cout << "Decay Constant of scintillator : " << meanDecayTime << std::endl;

  std::cout << "=============================" << std::endl;
  // hist->Draw("same");
}
