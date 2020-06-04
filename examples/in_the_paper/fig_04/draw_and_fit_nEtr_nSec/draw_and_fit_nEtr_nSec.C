void draw_and_fit_nEtr_nSec()
{
  TCanvas * canvas=new TCanvas("canvas", "nEtr_nSec", 1);
  gStyle->SetOptTitle(0);
  gPad->SetBottomMargin(0.12);
  TMultiGraph * multigraph=new TMultiGraph();

  const Int_t n1=8, n2=20;
  Double_t nEtr[n1][n2], nSec[n1][n2];
  string fileName[8];
  fileName[0]="../../ex_for_tb_01/get_nEtr_nSec/nEtr_nSec.dat";
  fileName[1]="../../others/taupair/get_nEtr_nSec/nEtr_nSec.dat";
  fileName[2]="../../others/ddbar/get_nEtr_nSec/nEtr_nSec.dat";
  fileName[3]="../../others/uubar/get_nEtr_nSec/nEtr_nSec.dat";
  fileName[4]="../../others/ssbar/get_nEtr_nSec/nEtr_nSec.dat";
  fileName[5]="../../others/ccbar/get_nEtr_nSec/nEtr_nSec.dat";
  fileName[6]="../../others/charged/get_nEtr_nSec/nEtr_nSec.dat";
  fileName[7]="../../ex_for_tb_02/get_nEtr_nSec/nEtr_nSec.dat";
  ifstream infile;
  for(Int_t i=0;i<n1;i++)
    {
      infile.open(fileName[i].c_str(), ios::in);
      for(Int_t j=0;j<n2;j++)
        {
          infile>>nEtr[i][j]>>nSec[i][j];
          // cout<<nEtr[i][j]<<" "<<nSec[i][j]<<endl;
        }
      infile.close();
    }

  TGraph * graph[n1];
  TF1 * f1[n1];
  Int_t markerStyle[n1]={20, 21, 23, 22, 5, 31, 33, 34};
  Int_t color[n1]={36, 46, 9, 8, 7, 6, 4, 2};
  string f1Name[n1]={"f10", "f11", "f12", "f13", "f14", "f15", "f16", "f17"};
  for(Int_t i=0;i<n1;i++)
    {
      graph[i]=new TGraph(n2, nEtr[i], nSec[i]);
      graph[i]->SetMarkerStyle(markerStyle[i]);
      if(i!=6) graph[i]->SetMarkerSize(1);
      else graph[i]->SetMarkerSize(4./3.);
      graph[i]->SetMarkerColor(color[i]);

      f1[i]=new TF1(f1Name[i].c_str(), "[0]*x+[1]", -1, 200000);
      f1[i]->SetParameter(0, nSec[i][n2-1]/nEtr[i][n2-1]);
      f1[i]->SetParameter(1, 0);
      f1[i]->SetLineColor(color[i]);
      f1[i]->SetLineWidth(2);

      graph[i]->Fit(f1Name[i].c_str(), "", "", 2500, 102500);
      multigraph->Add(graph[i]);
    }

  multigraph->Draw("AP");
  gPad->SetLeftMargin(0.1);
  gPad->SetRightMargin(0.1);
  gPad->SetBottomMargin(0.125);
  gPad->SetTopMargin(0.1);
  multigraph->GetXaxis()->SetTitle("Number of processed entries");
  multigraph->GetXaxis()->SetTitleSize(0.06);
  multigraph->GetXaxis()->SetLabelSize(0.04);
  multigraph->GetXaxis()->SetTitleOffset(0.95);
  multigraph->GetYaxis()->SetRangeUser(0, 26);
  multigraph->GetYaxis()->SetTitle("Number of elapsed seconds");
  multigraph->GetYaxis()->SetTitleSize(0.06);
  multigraph->GetYaxis()->SetLabelSize(0.04);
  multigraph->GetYaxis()->SetTitleOffset(0.75);
  multigraph->GetYaxis()->SetNdivisions(503);

  TLegend *legend=new TLegend(0.1525,0.4825,0.4825,0.8425);
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
  canvas->Print("nEtr_nSec.png");
  canvas->Print("nEtr_nSec.eps");
  canvas->Print("nEtr_nSec.pdf");
}
