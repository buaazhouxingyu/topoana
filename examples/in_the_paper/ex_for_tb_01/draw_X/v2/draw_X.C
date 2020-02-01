void draw_X()
{
  TCanvas * canvas=new TCanvas("canvas","canvas",1);
  gStyle->SetOptTitle(0);
  //gStyle->SetTitleAlign(23);
  //gStyle->SetTitleH(0.1);
  //gStyle->SetTitleW(0.8);

  TChain * chain=new TChain("evt");
  chain->Add("../../jpsi_ta.root");
  THStack * hs=new THStack("hs","#bf{Distribution of X accumulated over the top ten decay trees}");
  const unsigned int nHist=10;
  TH1D *h[nHist];
  char hname[5];
  char varexp[10];
  char selection[20];
  Int_t iDcyTr[nHist]={6,4,0,2,20,19,70,127,234,43};
  Int_t hFillColor[nHist]={2,3,4,6,7,8,9,46,36,1};
  for(Int_t i=nHist-1;i>=0;i--)
    {
      sprintf(hname,"h%i",i);
      sprintf(varexp,"X>>h%i",i);
      sprintf(selection,"iDcyTr==%i",iDcyTr[i]);
      h[i]=new TH1D(hname,hname,120,-4,8);
      chain->Draw(varexp,selection);
      h[i]->SetFillColor(hFillColor[i]); 
      hs->Add(h[i]);
    }  
  hs->Draw();
  hs->SetMaximum(1000);
  hs->GetXaxis()->SetTitle("X");
  hs->GetXaxis()->SetTitleSize(0.05);
  hs->GetXaxis()->SetLabelSize(0.04);
  hs->GetYaxis()->SetTitle("events / (0.1)");
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetLabelSize(0.04);
  hs->GetYaxis()->SetTitleOffset(1.1);
  gPad->SetLeftMargin(0.11);
  gPad->SetRightMargin(0.11);

  TLegend *legend=new TLegend(0.6175,0.3725,0.8825,0.8825);
  TLegendEntry *hLegendEntry[nHist];
  char hLegendEntryTitle[nHist][200]={
  "J/#psi #rightarrow #mu^{#plus} #mu^{#minus}",
  "J/#psi #rightarrow e^{#plus} e^{#minus}",
  "J/#psi #rightarrow #pi^{0} 2#pi^{#plus} 2#pi^{#minus}",
  "J/#psi #rightarrow #pi^{0} 3#pi^{#plus} 3#pi^{#minus}",
  "J/#psi #rightarrow #pi^{0} #pi^{#plus} #pi^{#minus} K^{#plus} K^{#minus}",
  "J/#psi #rightarrow #rho^{#plus} #rho^{#minus} #omega, ...",
  "J/#psi #rightarrow e^{#plus} e^{#minus} #gamma^{f}",
  "J/#psi #rightarrow 2#pi^{0} 2#pi^{#plus} 2#pi^{#minus}",
  "J/#psi #rightarrow #pi^{0} 4#pi^{#plus} 4#pi^{#minus}",
  "J/#psi #rightarrow #pi^{0} #pi^{#plus} #pi^{#minus} #gamma^{F}"
  };
  for(Int_t i=0;i<nHist;i++)
    {
      hLegendEntry[i]=legend->AddEntry(h[i],hLegendEntryTitle[i],"F");
      hLegendEntry[i]->SetTextColor(hFillColor[i]);
      hLegendEntry[i]->SetTextSize(0.035);
    }    
  legend->SetFillColor(kWhite);
  legend->SetBorderSize(0);
  legend->Draw();

  canvas->Print("Distribution_of_X_accumulated_over_the_top_ten_decay_trees.png");
  canvas->Print("Distribution_of_X_accumulated_over_the_top_ten_decay_trees.eps");
  canvas->Print("Distribution_of_X_accumulated_over_the_top_ten_decay_trees.pdf");
}
