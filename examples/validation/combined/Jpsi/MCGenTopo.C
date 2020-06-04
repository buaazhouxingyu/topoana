void MCGenTopo()
{
  TChain * chain=new TChain("MCGenTopo");
  chain->Add("../../standalone/Jpsi/01/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/02/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/03/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/04/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/05/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/06/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/07/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/08/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/09/MCGenTopo.root");
  chain->Add("../../standalone/Jpsi/10/MCGenTopo.root");

  TFile * file=new TFile("MCGenTopo.root", "recreate");
  TTree * tree=chain->CloneTree(0);
  Int_t iDcyTrOld;
  tree->Branch("iDcyTrOld", &iDcyTrOld, "iDcyTrOld/I");

  const Int_t nOldEntries=chain->GetEntries();
  vector<int> VNDcyTrOld;
  VNDcyTrOld.clear();
  for(Int_t i=0;i<nOldEntries;i++) VNDcyTrOld.push_back(0);

  const Int_t nNewEntries=100000;
  TRandom3 r3;
  for(Int_t i=0;i<nNewEntries;i++)
    {
      iDcyTrOld=r3.Integer(nOldEntries);  
      chain->GetEntry(iDcyTrOld);
      tree->Fill();
      VNDcyTrOld[iDcyTrOld]++;
    }

  file->Write();

  for(Int_t i=0;i<nOldEntries;i++) cout<<i<<"\t"<<VNDcyTrOld[i]<<endl;
}
