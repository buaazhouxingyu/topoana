#include "../include/topoana.h"
#include "TFile.h"
#include <iostream>
#include <cstdlib>
#include "TTree.h"

void topoana::rmIptBrs(string nmOfOptRootFl)
{ 
  TFile *fl=new TFile(nmOfOptRootFl.c_str(),"update");
  if(!fl)
    {
      cerr<<"Error: Can't open the root file \""<<nmOfOptRootFl<<"\"!"<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  TTree *tr_old=(TTree*) fl->Get(m_trNm.c_str());
  if(!tr_old)
    {
      cerr<<"Error: The root file \""<<nmOfOptRootFl<<"\" does not contain a tree named \""<<m_trNm<<"\"!"<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }  

  tr_old->SetBranchStatus(m_brNmOfNps.c_str(),0);
  if(m_strgTpOfRawIptTopoDat=="AI"||m_strgTpOfRawIptTopoDat=="VI")
    {
      tr_old->SetBranchStatus(m_brNmOfPid.c_str(),0);
      tr_old->SetBranchStatus(m_brNmOfMidx.c_str(),0); 
    }
  else
    {
      string specifier;
      specifier=m_brNmOfPid+"_*";
      tr_old->SetBranchStatus(specifier.c_str(),0);
      specifier=m_brNmOfMidx+"_*";
      tr_old->SetBranchStatus(specifier.c_str(),0);
    }
  
  TTree *tr_new=tr_old->CloneTree();

  tr_new->Write("",TObject::kOverwrite); 

  delete fl;
}
