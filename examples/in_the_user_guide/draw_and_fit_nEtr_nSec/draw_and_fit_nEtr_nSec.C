void draw_and_fit_nEtr_nSec()
{
  TCanvas * canvas=new TCanvas("canvas", "nEtr_nSec", 1);
  gStyle->SetOptTitle(0);
  gPad->SetBottomMargin(0.12);
  TMultiGraph * multigraph=new TMultiGraph();

  const Int_t n=20;

  Double_t nEtr1[n], nSec1[n];
  ifstream infile1("../ex_for_tb_01/get_nEtr_nSec/nEtr_nSec.dat", ios::in);
  for(Int_t i=0;i<n;i++)
    {
      infile1>>nEtr1[i]>>nSec1[i];
      // cout<<nEtr1[i]<<" "<<nSec1[i]<<endl;
    }

  TGraph * graph1=new TGraph(n, nEtr1, nSec1);
  graph1->SetMarkerStyle(20);
  graph1->SetMarkerSize(1);
  graph1->SetMarkerColor(kBlue);

  TF1 * f11=new TF1("f11", "[0]*x+[1]", -1, 200000);
  f11->SetParameter(0, nSec1[n-1]/nEtr1[n-1]);
  f11->SetParameter(1, 0);
  f11->SetLineColor(kBlue);
  f11->SetLineWidth(2);

  graph1->Fit("f11", "", "", 2500, 102500);


  Double_t nEtr2[n], nSec2[n];
  ifstream infile2("../ex_for_tb_02/get_nEtr_nSec/nEtr_nSec.dat", ios::in);
  for(Int_t i=0;i<n;i++)
    {
      infile2>>nEtr2[i]>>nSec2[i];
      // cout<<nEtr2[i]<<" "<<nSec2[i]<<endl;
    }

  TGraph * graph2=new TGraph(n, nEtr2, nSec2);
  graph2->SetMarkerStyle(20);
  graph2->SetMarkerSize(1);
  graph2->SetMarkerColor(kRed);

  TF1 * f12=new TF1("f12", "[0]*x+[1]", -1, 200000);
  f12->SetParameter(0, nSec2[n-1]/nEtr2[n-1]);
  f12->SetParameter(1, 0);
  f12->SetLineColor(kRed);
  f12->SetLineWidth(2);

  graph2->Fit("f12", "", "", 2500, 102500);


  multigraph->Add(graph1);
  multigraph->Add(graph2);
  multigraph->Draw("AP");
  multigraph->GetXaxis()->SetTitle("number of processed entries");
  multigraph->GetXaxis()->SetTitleSize(0.05);
  multigraph->GetXaxis()->SetLabelSize(0.04);
  multigraph->GetYaxis()->SetTitle("number of elapsed seconds");
  multigraph->GetYaxis()->SetTitleSize(0.05);
  multigraph->GetYaxis()->SetLabelSize(0.04);
  multigraph->GetYaxis()->SetTitleOffset(0.8);
  multigraph->GetYaxis()->SetNdivisions(505);

  cout<<endl;
  canvas->Print("nEtr_nSec.png");
  canvas->Print("nEtr_nSec.eps");
  canvas->Print("nEtr_nSec.pdf");
}
