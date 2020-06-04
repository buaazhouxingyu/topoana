void draw_and_fit_nP_nSec()
{
  TCanvas * canvas=new TCanvas("canvas", "nP_nSec", 1);
  gStyle->SetOptTitle(0);
  gPad->SetBottomMargin(0.12);
  TMultiGraph * multigraph=new TMultiGraph();

  const Int_t n1=8, n2=1;
  Double_t nP[n1][n2], nSec[n1][n2], NP[n1], NSec[n1];
  string fileName[8];
  fileName[0]="../../ex_for_tb_01/get_nP_nSec/nP_nSec.dat";
  fileName[1]="../../others/taupair/get_nP_nSec/nP_nSec.dat";
  fileName[2]="../../others/ddbar/get_nP_nSec/nP_nSec.dat";
  fileName[3]="../../others/uubar/get_nP_nSec/nP_nSec.dat";
  fileName[4]="../../others/ssbar/get_nP_nSec/nP_nSec.dat";
  fileName[5]="../../others/ccbar/get_nP_nSec/nP_nSec.dat";
  fileName[6]="../../others/charged/get_nP_nSec/nP_nSec.dat";
  fileName[7]="../../ex_for_tb_02/get_nP_nSec/nP_nSec.dat";
  ifstream infile;
  for(Int_t i=0;i<n1;i++)
    {
      infile.open(fileName[i].c_str(), ios::in);
      for(Int_t j=0;j<n2;j++)
        {
          infile>>nP[i][j]>>nSec[i][j];
          // cout<<nP[i][j]<<" "<<nSec[i][j]<<endl;
        }
      infile.close();
      NP[i]=nP[i][0];
      NSec[i]=nSec[i][0];
    }

  TGraph * Graph=new TGraph(n1, NP, NSec);
  Graph->SetMarkerStyle(20);
  Graph->SetMarkerSize(0);
  Graph->SetMarkerColor(1);
  multigraph->Add(Graph);

  TF1 * f1=new TF1("f1", "[0]*x+[1]", -1, 51);
  f1->SetParameter(0, 0.5);
  f1->SetParameter(1, 0);
  f1->SetLineColor(1);
  f1->SetLineWidth(2);

  Graph->Fit("f1", "", "", 5, 45);

  TGraph * graph[n1];
  Int_t markerStyle[n1]={20, 21, 23, 22, 5, 31, 33, 34};
  Int_t color[n1]={36, 46, 9, 8, 7, 6, 4, 2};
  string f1Name[n1]={"f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17"};
  for(Int_t i=0;i<n1;i++)
    {
      graph[i]=new TGraph(n2, nP[i], nSec[i]);
      graph[i]->SetMarkerStyle(markerStyle[i]);
      if(i!=6) graph[i]->SetMarkerSize(1.5);
      else graph[i]->SetMarkerSize(2);
      graph[i]->SetMarkerColor(color[i]);
      multigraph->Add(graph[i]);
    }

  multigraph->Draw("AP");
  gPad->SetLeftMargin(0.1);
  gPad->SetRightMargin(0.1);
  gPad->SetBottomMargin(0.125);
  gPad->SetTopMargin(0.1);
  multigraph->GetXaxis()->SetLimits(0, 50);
  multigraph->GetYaxis()->SetRangeUser(0, 26);
  multigraph->GetXaxis()->SetTitle("Number of particles");
  multigraph->GetXaxis()->SetTitleSize(0.06);
  multigraph->GetXaxis()->SetLabelSize(0.04);
  multigraph->GetXaxis()->SetTitleOffset(0.95);
  multigraph->GetXaxis()->SetNdivisions(505);
  multigraph->GetYaxis()->SetTitle("Number of elapsed seconds");
  multigraph->GetYaxis()->SetTitleSize(0.06);
  multigraph->GetYaxis()->SetLabelSize(0.04);
  multigraph->GetYaxis()->SetTitleOffset(0.75);
  multigraph->GetYaxis()->SetNdivisions(503);

  TLegend *legend=new TLegend(0.135,0.50,0.465,0.86);
  TLegendEntry *legendEntry[8];
  char legendEntryTitle[8][30]={"J/#psi","#tau^{#plus}#tau^{#minus}","d#bar{d}","u#bar{u}","s#bar{s}","c#bar{c}","B^{#plus}B^{#minus}","B^{0}#bar{B}^{0}"};
  for(Int_t i=0;i<8;i++)
    {
      legendEntry[i]=legend->AddEntry(graph[i],legendEntryTitle[i],"P");
      legendEntry[i]->SetTextColor(color[i]);
      legendEntry[i]->SetTextSize(0.065);
    }    
  legend->SetFillColor(kWhite);
  legend->SetBorderSize(0);
  legend->SetNColumns(2);
  legend->Draw();

  cout<<endl;
  canvas->Print("nP_nSec.png");
  canvas->Print("nP_nSec.eps");
  canvas->Print("nP_nSec.pdf");
}
