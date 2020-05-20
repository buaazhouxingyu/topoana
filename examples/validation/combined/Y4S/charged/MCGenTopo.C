void MCGenTopo()
{
  TChain * chain=new TChain("MCGenTopo");
  chain->Add("../../../standalone/Y4S/charged/01/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/02/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/03/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/04/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/05/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/06/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/07/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/08/MCGenTopo.root");
  chain->Add("../../../standalone/Y4S/charged/09/MCGenTopo.root");

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
