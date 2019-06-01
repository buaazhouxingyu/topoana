#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include <ctime>
#include "TTreeFormula.h"
#include <sstream>

void topoana::getRslt()
{
  unsigned int Nasterisks=89;
  for(unsigned int i=0;i<Nasterisks;i++) cout<<"*";
  cout<<endl<<endl;

  TChain * chn=new TChain(m_trNm.c_str());
  vector<unsigned long> vNEtrs;
  vNEtrs.clear();
  for(unsigned int i=0;i<m_nmsOfIptRootFls.size();i++)
    {
      chn->Add(m_nmsOfIptRootFls[i].c_str());
      if(m_oneOptRootFlByOneIptRootFl==true) vNEtrs.push_back(chn->GetEntries());
    }
  unsigned long nEtrs=chn->GetEntries();
  cout<<"There are "<<nEtrs<<" entries in total in the input root files."<<endl<<endl;

  // The following statement instead of the one next to it ought to be used along with the Ntuple Tool MCGenKinematics with the option [200].
  const unsigned int NpsMax=200;
  // const unsigned int NpsMax=chn->GetMaximum(m_brNmOfNps.c_str());
  int Nps,Pid[NpsMax],Midx[NpsMax];
  double Npsd,Pidd[NpsMax],Midxd[NpsMax];
  vector<int> *pVPid=0, *pVMidx=0;
  if(m_strgTpOfRawIptTopoDat=="AI"||m_strgTpOfRawIptTopoDat=="MIV") chn->SetBranchAddress(m_brNmOfNps.c_str(), &Nps);
  else if(m_strgTpOfRawIptTopoDat=="MDV") chn->SetBranchAddress(m_brNmOfNps.c_str(), &Npsd);
  if(m_strgTpOfRawIptTopoDat=="AI")
    {
      chn->SetBranchAddress(m_brNmOfPid.c_str(), &Pid);
      chn->SetBranchAddress(m_brNmOfMidx.c_str(), &Midx);
    }
  else if(m_strgTpOfRawIptTopoDat=="VI")
    {
      chn->SetBranchAddress(m_brNmOfPid.c_str(), &pVPid);
      chn->SetBranchAddress(m_brNmOfMidx.c_str(), &pVMidx);
    }
  else
    {
      const unsigned int NpsMaxTmp=chn->GetMaximum(m_brNmOfNps.c_str());
      char strI[10]; string specifierPid,specifierMidx;
      for(unsigned int i=0;i<NpsMaxTmp;i++)
        {
          sprintf(strI, "_%d", i);
          specifierPid=m_brNmOfPid+strI;
          if(m_strgTpOfRawIptTopoDat=="MDV") chn->SetBranchAddress(specifierPid.c_str(), &Pidd[i]);
          else chn->SetBranchAddress(specifierPid.c_str(), &Pid[i]);
          specifierMidx=m_brNmOfMidx+strI;
          if(m_strgTpOfRawIptTopoDat=="MDV") chn->SetBranchAddress(specifierMidx.c_str(), &Midxd[i]);
          else chn->SetBranchAddress(specifierMidx.c_str(), &Midx[i]);
        }
    }

  bool openANewOptRootFl=true;
  unsigned int iOptRootFls=0;
  string NmOfOptRootFl;
  TFile * fl;
  TTree * tr;
  bool closeTheOptRootFl1;
  bool closeTheOptRootFl2;
  bool closeTheOptRootFl3;
  const unsigned long nTotBytesMaxOfASngOptRootFl=(unsigned long) 3*1024*1024*1024; // The size of a single output root file in memory is 3G.

  const unsigned int sSigP=m_vPid_sigP.size()>0?m_vPid_sigP.size():1;
  int nSigP[sSigP],nCcSigP[sSigP],nTotSigP[sSigP],iCcSigP[sSigP];
  const unsigned int sSigDcyBr=m_vSigDcyBr.size()>0?m_vSigDcyBr.size():1;
  int nSigDcyBr[sSigDcyBr],nCcSigDcyBr[sSigDcyBr],nTotSigDcyBr[sSigDcyBr],iCcSigDcyBr[sSigDcyBr];
  const unsigned int sSigIncDcyBr=m_vSigIncDcyBr.size()>0?m_vSigIncDcyBr.size():1;
  int nSigIncDcyBr[sSigIncDcyBr],nCcSigIncDcyBr[sSigIncDcyBr],nTotSigIncDcyBr[sSigIncDcyBr],iCcSigIncDcyBr[sSigIncDcyBr];
  const unsigned int sSigCascDcyBrs=m_vSigCascDcyBrs.size()>0?m_vSigCascDcyBrs.size():1;
  int nSigCascDcyBrs[sSigCascDcyBrs],nCcSigCascDcyBrs[sSigCascDcyBrs],nTotSigCascDcyBrs[sSigCascDcyBrs],iCcSigCascDcyBrs[sSigCascDcyBrs];
  const unsigned int sSigIncCascDcyBrs=m_vSigIncCascDcyBrs.size()>0?m_vSigIncCascDcyBrs.size():1;
  int nSigIncCascDcyBrs[sSigIncCascDcyBrs],nCcSigIncCascDcyBrs[sSigIncCascDcyBrs],nTotSigIncCascDcyBrs[sSigIncCascDcyBrs],iCcSigIncCascDcyBrs[sSigIncCascDcyBrs];
  const unsigned int sSigIRADcyBr=m_vSigIRADcyBr.size()>0?m_vSigIRADcyBr.size():1;
  int nSigIRADcyBr[sSigIRADcyBr],nCcSigIRADcyBr[sSigIRADcyBr],nTotSigIRADcyBr[sSigIRADcyBr],iCcSigIRADcyBr[sSigIRADcyBr];
  const unsigned int sSigIncOrIRACascDcyBrs=m_vSigIncOrIRACascDcyBrs.size()>0?m_vSigIncOrIRACascDcyBrs.size():1;
  int nSigIncOrIRACascDcyBrs[sSigIncOrIRACascDcyBrs],nCcSigIncOrIRACascDcyBrs[sSigIncOrIRACascDcyBrs],nTotSigIncOrIRACascDcyBrs[sSigIncOrIRACascDcyBrs],iCcSigIncOrIRACascDcyBrs[sSigIncOrIRACascDcyBrs];
  char nmSigDcyTr[200]; int iSigDcyTr,iCcSigDcyTr,iSigDcyIFSts,iCcSigDcyIFSts;
  char nmSigDcyIFSts2[200]; int iSigDcyIFSts2,iCcSigDcyIFSts2;
  const unsigned int sAtdbPid=m_vPid_compP.size()>0?m_vPid_compP.size():1;
  int nP[sAtdbPid],iCcP[sAtdbPid],nCcP[sAtdbPid],nTotP[sAtdbPid];
  int iDcyBrP[sAtdbPid][200],iCcDcyBrP[sAtdbPid][200],iDcyBrCcP[sAtdbPid][200];
  const unsigned int sVAtecIncDcyBr=m_vCompIncDcyBr.size()>0?m_vCompIncDcyBr.size():1;
  int nIncDcyBr[sVAtecIncDcyBr],iCcIncDcyBr[sVAtecIncDcyBr],nCcIncDcyBr[sVAtecIncDcyBr],nTotIncDcyBr[sVAtecIncDcyBr];
  int iDcyBrIncDcyBr[sVAtecIncDcyBr][200],iCcDcyBrIncDcyBr[sVAtecIncDcyBr][200],iDcyBrCcIncDcyBr[sVAtecIncDcyBr][200];
  const unsigned int sVAtecIRADcyBr=m_vCompIRADcyBr.size()>0?m_vCompIRADcyBr.size():1;
  int nIRADcyBr[sVAtecIRADcyBr],iCcIRADcyBr[sVAtecIRADcyBr],nCcIRADcyBr[sVAtecIRADcyBr],nTotIRADcyBr[sVAtecIRADcyBr];
  int iDcyBrIRADcyBr[sVAtecIRADcyBr][200],iCcDcyBrIRADcyBr[sVAtecIRADcyBr][200],iDcyBrCcIRADcyBr[sVAtecIRADcyBr][200];
  int iDcyTr,iCcDcyTr,iDcyIFSts,iCcDcyIFSts;

  TTreeFormula * trfml;
  unsigned int nInsts=1;
  if(!m_cut.empty())
    {
      trfml=new TTreeFormula("trfml",m_cut.c_str(),chn);
      chn->SetNotify(trfml); // This statement is indispensible if more than one root file is added to the object of the TChain class.
    }
  unsigned long nEtrsThroughTheCut=0;

  vector<int> vPid, vCcPid;
  vector<int> vMidx, vCcMidx;
  vector< list<int> > dcyTr, ccDcyTr;
  vector<int> vIdxOfHead, vCcIdxOfHead;
  vector<int> vMidxOfHead, vCcMidxOfHead;
  string strDcyTr, strCcDcyTr;
  list<int> dcyIFSts,ccDcyIFSts;
  string strDcyIFSts, strCcDcyIFSts;
  ostringstream oss;

  unsigned long nEtrsToBePrcsd=nEtrs<m_nEtrsMax?nEtrs:m_nEtrsMax;
  if(m_anaTasksForSigIds!="C")
    {
      unsigned long nEtrsForTiming=5000;
      clock_t starttime=clock();
      for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
        {
          if(openANewOptRootFl==true)
            {
              openANewOptRootFl=false;
              if(m_oneOptRootFlByOneIptRootFl==true)
                {
                  NmOfOptRootFl=m_nmsOfIptRootFls[iOptRootFls].replace(m_nmsOfIptRootFls[iOptRootFls].rfind(".root"),5,"_ta.root");
                }
              else
                {
                  if(iOptRootFls==0)
                    {
                      NmOfOptRootFl=m_mainNmOfOptFls+".root";
                    }
                  else
                    {
                      ostringstream oss;
                      oss<<iOptRootFls;
                      string strIOptRootFls=oss.str();
                      NmOfOptRootFl=m_mainNmOfOptFls+"_"+strIOptRootFls+".root";
                    }
                }
              fl=new TFile(NmOfOptRootFl.c_str(),"recreate");
              if(!fl)
                {
                  cerr<<"Error: Can't create the output root file \""<<NmOfOptRootFl<<"\"!"<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }

              tr=chn->CloneTree(0);

              if(m_compAnaOfDcyTrs==true)
                {
                  tr->Branch("iDcyTr", &iDcyTr, "iDcyTr/I");
                  tr->Branch("iDcyIFSts", &iDcyIFSts, "iDcyIFSts/I");
                  if(m_ccSwitch==true)
                    {
                      tr->Branch("iCcDcyTr", &iCcDcyTr, "iCcDcyTr/I");
                      tr->Branch("iCcDcyIFSts", &iCcDcyIFSts, "iCcDcyIFSts/I");
                    }
                }
              else if(m_compAnaOfDcyIFSts==true)
                {
                  tr->Branch("iDcyIFSts", &iDcyIFSts, "iDcyIFSts/I");
                  if(m_ccSwitch==true) tr->Branch("iCcDcyIFSts", &iCcDcyIFSts, "iCcDcyIFSts/I");
                }
              if(m_vPid_compP.size()>0)
                {
                  char nmCompP[20];
                  char specifier1[100],specifier2[100];
                  for(unsigned int i=0;i<m_vPid_compP.size();i++)
                    {
                      if(m_vNm_compP[i].empty()) sprintf(nmCompP, "CompP%d", i);
                      else sprintf(nmCompP, "_%s", m_vNm_compP[i].c_str());
                      // else strcpy(nmCompP, m_vNm_compP[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmCompP".
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier1, "iCc%s", nmCompP);
                          sprintf(specifier2, "iCc%s/I", nmCompP);
                          tr->Branch(specifier1, &iCcP[i], specifier2);
                          iCcP[i]=m_vICcCompP[i];
                          if(iCcP[i]==0)
                            {
                              sprintf(specifier1, "n%s", nmCompP);
                              sprintf(specifier2, "n%s/I", nmCompP);
                              tr->Branch(specifier1, &nP[i], specifier2);
                              sprintf(specifier1, "iDcyBr%s", nmCompP);
                              sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompP, nmCompP);
                              tr->Branch(specifier1, &iDcyBrP[i], specifier2);
                              sprintf(specifier1, "iCcDcyBr%s", nmCompP);
                              sprintf(specifier2, "iCcDcyBr%s[n%s]/I", nmCompP, nmCompP);
                              tr->Branch(specifier1, &iCcDcyBrP[i], specifier2);                  
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmCompP);
                              sprintf(specifier2, "n%s/I", nmCompP);
                              tr->Branch(specifier1, &nP[i], specifier2);
                              sprintf(specifier1, "iDcyBr%s", nmCompP);
                              sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompP, nmCompP);
                              tr->Branch(specifier1, &iDcyBrP[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmCompP);
                              sprintf(specifier2, "nCc%s/I", nmCompP);
                              tr->Branch(specifier1, &nCcP[i], specifier2);
                              sprintf(specifier1, "iDcyBrCc%s", nmCompP);
                              sprintf(specifier2, "iDcyBrCc%s[nCc%s]/I", nmCompP, nmCompP);
                              tr->Branch(specifier1, &iDcyBrCcP[i], specifier2);              
                              sprintf(specifier1, "nTot%s", nmCompP);
                              sprintf(specifier2, "nTot%s/I", nmCompP);
                              tr->Branch(specifier1, &nTotP[i], specifier2);
                            }
                        }
                      else
                        {
                          sprintf(specifier1, "n%s", nmCompP);
                          sprintf(specifier2, "n%s/I", nmCompP);
                          tr->Branch(specifier1, &nP[i], specifier2);
                          sprintf(specifier1, "iDcyBr%s", nmCompP);
                          sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompP, nmCompP);
                          tr->Branch(specifier1, &iDcyBrP[i], specifier2);
                        }
                    }
                }
              if(m_vCompIncDcyBr.size()>0)
                {
                  char nmCompIncDcyBr[20];
                  char specifier1[100],specifier2[100];
                  list<int>::iterator liit;
                  for(unsigned int i=0;i<m_vCompIncDcyBr.size();i++)
                    {
                      if(m_vNm_compIncDcyBr[i].empty()) sprintf(nmCompIncDcyBr, "CompIncDcyBr%d", i);
                      else sprintf(nmCompIncDcyBr, "_%s", m_vNm_compIncDcyBr[i].c_str());
                      // else strcpy(nmCompIncDcyBr, m_vNm_compIncDcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmCompIncDcyBr".
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier1, "iCc%s", nmCompIncDcyBr);
                          sprintf(specifier2, "iCc%s/I", nmCompIncDcyBr);
                          tr->Branch(specifier1, &iCcIncDcyBr[i], specifier2);
                          iCcIncDcyBr[i]=m_vCompICcIncDcyBr[i];
                          if(iCcIncDcyBr[i]==0)
                            {
                              sprintf(specifier1, "n%s", nmCompIncDcyBr);
                              sprintf(specifier2, "n%s/I", nmCompIncDcyBr);
                              tr->Branch(specifier1, &nIncDcyBr[i], specifier2);
                              sprintf(specifier1, "iDcyBr%s", nmCompIncDcyBr);
                              sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompIncDcyBr, nmCompIncDcyBr);
                              tr->Branch(specifier1, &iDcyBrIncDcyBr[i], specifier2);
                              sprintf(specifier1, "iCcDcyBr%s", nmCompIncDcyBr);
                              sprintf(specifier2, "iCcDcyBr%s[n%s]/I", nmCompIncDcyBr, nmCompIncDcyBr);
                              tr->Branch(specifier1, &iCcDcyBrIncDcyBr[i], specifier2);                  
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmCompIncDcyBr);
                              sprintf(specifier2, "n%s/I", nmCompIncDcyBr);
                              tr->Branch(specifier1, &nIncDcyBr[i], specifier2);
                              sprintf(specifier1, "iDcyBr%s", nmCompIncDcyBr);
                              sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompIncDcyBr, nmCompIncDcyBr);
                              tr->Branch(specifier1, &iDcyBrIncDcyBr[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmCompIncDcyBr);
                              sprintf(specifier2, "nCc%s/I", nmCompIncDcyBr);
                              tr->Branch(specifier1, &nCcIncDcyBr[i], specifier2);
                              sprintf(specifier1, "iDcyBrCc%s", nmCompIncDcyBr);
                              sprintf(specifier2, "iDcyBrCc%s[nCc%s]/I", nmCompIncDcyBr, nmCompIncDcyBr);
                              tr->Branch(specifier1, &iDcyBrCcIncDcyBr[i], specifier2);              
                              sprintf(specifier1, "nTot%s", nmCompIncDcyBr);
                              sprintf(specifier2, "nTot%s/I", nmCompIncDcyBr);
                              tr->Branch(specifier1, &nTotIncDcyBr[i], specifier2);
                            }
                        }
                      else
                        {
                          sprintf(specifier1, "n%s", nmCompIncDcyBr);
                          sprintf(specifier2, "n%s/I", nmCompIncDcyBr);
                          tr->Branch(specifier1, &nIncDcyBr[i], specifier2);
                          sprintf(specifier1, "iDcyBr%s", nmCompIncDcyBr);
                          sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompIncDcyBr, nmCompIncDcyBr);
                          tr->Branch(specifier1, &iDcyBrIncDcyBr[i], specifier2);
                        }
                    }
                }
              if(m_vCompIRADcyBr.size()>0)
                {
                  char nmCompIRADcyBr[20];
                  char specifier1[100],specifier2[100];
                  for(unsigned int i=0;i<m_vCompIRADcyBr.size();i++)
                    {
                      if(m_vNm_compIRADcyBr[i].empty()) sprintf(nmCompIRADcyBr, "CompIRADcyBr%d", i);
                      else sprintf(nmCompIRADcyBr, "_%s", m_vNm_compIRADcyBr[i].c_str());
                      // else strcpy(nmCompIRADcyBr, m_vNm_compIRADcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmCompIRADcyBr".
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier1, "iCc%s", nmCompIRADcyBr);
                          sprintf(specifier2, "iCc%s/I", nmCompIRADcyBr);
                          tr->Branch(specifier1, &iCcIRADcyBr[i], specifier2);
                          iCcIRADcyBr[i]=m_vCompICcIRADcyBr[i];
                          if(iCcIRADcyBr[i]==0)
                            {
                              sprintf(specifier1, "n%s", nmCompIRADcyBr);
                              sprintf(specifier2, "n%s/I", nmCompIRADcyBr);
                              tr->Branch(specifier1, &nIRADcyBr[i], specifier2);
                              sprintf(specifier1, "iDcyBr%s", nmCompIRADcyBr);
                              sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompIRADcyBr, nmCompIRADcyBr);
                              tr->Branch(specifier1, &iDcyBrIRADcyBr[i], specifier2);
                              sprintf(specifier1, "iCcDcyBr%s", nmCompIRADcyBr);
                              sprintf(specifier2, "iCcDcyBr%s[n%s]/I", nmCompIRADcyBr, nmCompIRADcyBr);
                              tr->Branch(specifier1, &iCcDcyBrIRADcyBr[i], specifier2);                  
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmCompIRADcyBr);
                              sprintf(specifier2, "n%s/I", nmCompIRADcyBr);
                              tr->Branch(specifier1, &nIRADcyBr[i], specifier2);
                              sprintf(specifier1, "iDcyBr%s", nmCompIRADcyBr);
                              sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompIRADcyBr, nmCompIRADcyBr);
                              tr->Branch(specifier1, &iDcyBrIRADcyBr[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmCompIRADcyBr);
                              sprintf(specifier2, "nCc%s/I", nmCompIRADcyBr);
                              tr->Branch(specifier1, &nCcIRADcyBr[i], specifier2);
                              sprintf(specifier1, "iDcyBrCc%s", nmCompIRADcyBr);
                              sprintf(specifier2, "iDcyBrCc%s[nCc%s]/I", nmCompIRADcyBr, nmCompIRADcyBr);
                              tr->Branch(specifier1, &iDcyBrCcIRADcyBr[i], specifier2);              
                              sprintf(specifier1, "nTot%s", nmCompIRADcyBr);
                              sprintf(specifier2, "nTot%s/I", nmCompIRADcyBr);
                              tr->Branch(specifier1, &nTotIRADcyBr[i], specifier2);
                            }
                        }
                      else
                        {
                          sprintf(specifier1, "n%s", nmCompIRADcyBr);
                          sprintf(specifier2, "n%s/I", nmCompIRADcyBr);
                          tr->Branch(specifier1, &nIRADcyBr[i], specifier2);
                          sprintf(specifier1, "iDcyBr%s", nmCompIRADcyBr);
                          sprintf(specifier2, "iDcyBr%s[n%s]/I", nmCompIRADcyBr, nmCompIRADcyBr);
                          tr->Branch(specifier1, &iDcyBrIRADcyBr[i], specifier2);
                        }
                    }
                }
              if(m_vSigDcyTr.size()>0)
                {
                  tr->Branch("nameSigDcyTr", &nmSigDcyTr, "nameSigDcyTr/C");
                  tr->Branch("iSigDcyTr", &iSigDcyTr, "iSigDcyTr/I");
                  tr->Branch("iSigDcyIFSts", &iSigDcyIFSts, "iSigDcyIFSts/I");
                  if(m_ccSwitch==true)
                    {
                      tr->Branch("iCcSigDcyTr", &iCcSigDcyTr, "iCcSigDcyTr/I");
                      tr->Branch("iCcSigDcyIFSts", &iCcSigDcyIFSts, "iCcSigDcyIFSts/I");
                    }
                }
              if(m_vSigDcyIFSts2.size()>0)
                {
                  tr->Branch("nameSigDcyIFSts2", &nmSigDcyIFSts2, "nameSigDcyIFSts2/C");
                  tr->Branch("iSigDcyIFSts2", &iSigDcyIFSts2, "iSigDcyIFSts2/I");
                  if(m_ccSwitch==true)
                    {
                      tr->Branch("iCcSigDcyIFSts2", &iCcSigDcyIFSts2, "iCcSigDcyIFSts2/I");
                    }
                }
              if(m_vPid_sigP.size()>0)
                {
                  if(m_useArrayBrsOpt==true)
                    {
                      char specifier[30];
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier, "iCcSigP[%d]/I", int(sSigP));
                          tr->Branch("iCcSigP", &iCcSigP, specifier);
                          for(unsigned int i=0;i<sSigP;i++) iCcSigP[i]=m_vICcSigP[i];
                          sprintf(specifier, "nSigP[%d]/I", int(sSigP));
                          tr->Branch("nSigP", &nSigP, specifier);
                          sprintf(specifier, "nCcSigP[%d]/I", int(sSigP));
                          tr->Branch("nCcSigP", &nCcSigP, specifier);
                          sprintf(specifier, "nTotSigP[%d]/I", int(sSigP));
                          tr->Branch("nTotSigP", &nTotSigP, specifier);
                        }
                      else
                        {
                          sprintf(specifier, "nSigP[%d]/I", int(sSigP));
                          tr->Branch("nSigP", &nSigP, specifier);
                        }
                    }
                  else
                    {
                      char nmSigP[20];
                      char specifier1[30],specifier2[30];
                      for(unsigned int i=0;i<m_vPid_sigP.size();i++)
                        {
                          if(m_vNm_sigP[i].empty()) sprintf(nmSigP, "SigP%d", i);
                          else sprintf(nmSigP, "_%s", m_vNm_sigP[i].c_str());
                          // else strcpy(nmSigP,m_vNm_sigP[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmSigP".
                          if(m_ccSwitch==true)
                            {
                              sprintf(specifier1, "iCc%s", nmSigP);
                              sprintf(specifier2, "iCc%s/I", nmSigP);
                              tr->Branch(specifier1, &iCcSigP[i], specifier2);
                              iCcSigP[i]=m_vICcSigP[i];
                              sprintf(specifier1, "n%s", nmSigP);
                              sprintf(specifier2, "n%s/I", nmSigP);
                              tr->Branch(specifier1, &nSigP[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmSigP);
                              sprintf(specifier2, "nCc%s/I", nmSigP);
                              tr->Branch(specifier1, &nCcSigP[i], specifier2);
                              sprintf(specifier1, "nTot%s", nmSigP);
                              sprintf(specifier2, "nTot%s/I", nmSigP);
                              tr->Branch(specifier1, &nTotSigP[i], specifier2);
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmSigP);
                              sprintf(specifier2, "n%s/I", nmSigP);
                              tr->Branch(specifier1, &nSigP[i], specifier2);        
                            }
                        }
                    }
                }
              if(m_vSigIncDcyBr.size()>0)
                {
                  if(m_useArrayBrsOpt==true)
                    {
                      char specifier[30];
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier, "iCcSigIncDcyBr[%d]/I", int(sSigIncDcyBr));
                          tr->Branch("iCcSigIncDcyBr", &iCcSigIncDcyBr, specifier);
                          for(unsigned int i=0;i<sSigIncDcyBr;i++) iCcSigIncDcyBr[i]=m_vICcSigIncDcyBr[i];
                          sprintf(specifier, "nSigIncDcyBr[%d]/I", int(sSigIncDcyBr));
                          tr->Branch("nSigIncDcyBr", &nSigIncDcyBr, specifier);
                          sprintf(specifier, "nCcSigIncDcyBr[%d]/I", int(sSigIncDcyBr));
                          tr->Branch("nCcSigIncDcyBr", &nCcSigIncDcyBr, specifier);
                          sprintf(specifier, "nTotSigIncDcyBr[%d]/I", int(sSigIncDcyBr));
                          tr->Branch("nTotSigIncDcyBr", &nTotSigIncDcyBr, specifier);
                        }
                      else
                        {
                          sprintf(specifier, "nSigIncDcyBr[%d]/I", int(sSigIncDcyBr));
                          tr->Branch("nSigIncDcyBr", &nSigIncDcyBr, specifier);
                        }
                    }
                  else
                    {
                      char nmSigIncDcyBr[20];
                      char specifier1[30], specifier2[30];
                      list<int>::iterator liit;
                      for(unsigned int i=0;i<m_vSigIncDcyBr.size();i++)
                        {
                          if(m_vNm_sigIncDcyBr[i].empty()) sprintf(nmSigIncDcyBr, "SigIncDcyBr%d", i);
                          else sprintf(nmSigIncDcyBr, "_%s", m_vNm_sigIncDcyBr[i].c_str());
                          // else strcpy(nmSigIncDcyBr,m_vNm_sigIncDcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmSigIncDcyBr".
                          if(m_ccSwitch==true)
                            {
                              sprintf(specifier1, "iCc%s", nmSigIncDcyBr);
                              sprintf(specifier2, "iCc%s/I", nmSigIncDcyBr);
                              tr->Branch(specifier1, &iCcSigIncDcyBr[i], specifier2);
                              iCcSigIncDcyBr[i]=m_vICcSigIncDcyBr[i];
                              sprintf(specifier1, "n%s", nmSigIncDcyBr);
                              sprintf(specifier2, "n%s/I", nmSigIncDcyBr);
                              tr->Branch(specifier1, &nSigIncDcyBr[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmSigIncDcyBr);
                              sprintf(specifier2, "nCc%s/I", nmSigIncDcyBr);
                              tr->Branch(specifier1, &nCcSigIncDcyBr[i], specifier2);
                              sprintf(specifier1, "nTot%s", nmSigIncDcyBr);
                              sprintf(specifier2, "nTot%s/I", nmSigIncDcyBr);
                              tr->Branch(specifier1, &nTotSigIncDcyBr[i], specifier2);
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmSigIncDcyBr);
                              sprintf(specifier2, "n%s/I", nmSigIncDcyBr);
                              tr->Branch(specifier1, &nSigIncDcyBr[i], specifier2);
                            }
                        }
                    }
                }
              if(m_vSigDcyBr.size()>0)
                {
                  if(m_useArrayBrsOpt==true)
                    {
                      char specifier[30];
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier, "iCcSigDcyBr[%d]/I", int(sSigDcyBr));
                          tr->Branch("iCcSigDcyBr", &iCcSigDcyBr, specifier);
                          for(unsigned int i=0;i<sSigDcyBr;i++) iCcSigDcyBr[i]=m_vICcSigDcyBr[i];
                          sprintf(specifier, "nSigDcyBr[%d]/I", int(sSigDcyBr));
                          tr->Branch("nSigDcyBr", &nSigDcyBr, specifier);
                          sprintf(specifier, "nCcSigDcyBr[%d]/I", int(sSigDcyBr));
                          tr->Branch("nCcSigDcyBr", &nCcSigDcyBr, specifier);
                          sprintf(specifier, "nTotSigDcyBr[%d]/I", int(sSigDcyBr));
                          tr->Branch("nTotSigDcyBr", &nTotSigDcyBr, specifier);
                        }
                      else
                        {
                          sprintf(specifier, "nSigDcyBr[%d]/I", int(sSigDcyBr));
                          tr->Branch("nSigDcyBr", &nSigDcyBr, specifier);
                        }
                    }
                  else
                    {
                      char nmSigDcyBr[20];
                      char specifier1[30], specifier2[30];
                      list<int>::iterator liit;
                      for(unsigned int i=0;i<m_vSigDcyBr.size();i++)
                        {
                          if(m_vNm_sigDcyBr[i].empty()) sprintf(nmSigDcyBr, "SigDcyBr%d", i);
                          else sprintf(nmSigDcyBr, "_%s", m_vNm_sigDcyBr[i].c_str());
                          // else strcpy(nmSigDcyBr,m_vNm_sigDcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmSigDcyBr".
                          if(m_ccSwitch==true)
                            {
                              sprintf(specifier1, "iCc%s", nmSigDcyBr);
                              sprintf(specifier2, "iCc%s/I", nmSigDcyBr);
                              tr->Branch(specifier1, &iCcSigDcyBr[i], specifier2);
                              iCcSigDcyBr[i]=m_vICcSigDcyBr[i];
                              sprintf(specifier1, "n%s", nmSigDcyBr);
                              sprintf(specifier2, "n%s/I", nmSigDcyBr);
                              tr->Branch(specifier1, &nSigDcyBr[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmSigDcyBr);
                              sprintf(specifier2, "nCc%s/I", nmSigDcyBr);
                              tr->Branch(specifier1, &nCcSigDcyBr[i], specifier2);
                              sprintf(specifier1, "nTot%s", nmSigDcyBr);
                              sprintf(specifier2, "nTot%s/I", nmSigDcyBr);
                              tr->Branch(specifier1, &nTotSigDcyBr[i], specifier2);
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmSigDcyBr);
                              sprintf(specifier2, "n%s/I", nmSigDcyBr);
                              tr->Branch(specifier1, &nSigDcyBr[i], specifier2);
                            }
                        }
                    }
                }
              if(m_vSigCascDcyBrs.size()>0)
                {
                  if(m_useArrayBrsOpt==true)
                    {
                      char specifier[30];
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier, "iCcSigCascDcyBrs[%d]/I", int(sSigCascDcyBrs));
                          tr->Branch("iCcSigCascDcyBrs", &iCcSigCascDcyBrs, specifier);
                          for(unsigned int i=0;i<sSigCascDcyBrs;i++) iCcSigCascDcyBrs[i]=m_vICcSigCascDcyBrs[i];
                          sprintf(specifier, "nSigCascDcyBrs[%d]/I", int(sSigCascDcyBrs));
                          tr->Branch("nSigCascDcyBrs", &nSigCascDcyBrs, specifier);
                          sprintf(specifier, "nCcSigCascDcyBrs[%d]/I", int(sSigCascDcyBrs));
                          tr->Branch("nCcSigCascDcyBrs", &nCcSigCascDcyBrs, specifier);
                          sprintf(specifier, "nTotSigCascDcyBrs[%d]/I", int(sSigCascDcyBrs));
                          tr->Branch("nTotSigCascDcyBrs", &nTotSigCascDcyBrs, specifier);
                        }
                      else
                        {
                          sprintf(specifier, "nSigCascDcyBrs[%d]/I", int(sSigCascDcyBrs));
                          tr->Branch("nSigCascDcyBrs", &nSigCascDcyBrs, specifier);
                        }
                    }
                  else
                    {
                      char nmSigCascDcyBrs[20];
                      char specifier1[30], specifier2[30];
                      for(unsigned int i=0;i<m_vSigCascDcyBrs.size();i++)
                        {
                          if(m_vNm_sigCascDcyBrs[i].empty()) sprintf(nmSigCascDcyBrs, "SigCascDcyBrs%d", i);
                          else sprintf(nmSigCascDcyBrs, "_%s", m_vNm_sigCascDcyBrs[i].c_str());
                          // else strcpy(nmSigCascDcyBrs,m_vNm_sigCascDcyBrs[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmSigCascDcyBrs".
                          if(m_ccSwitch==true)
                            {
                              sprintf(specifier1, "iCc%s", nmSigCascDcyBrs);
                              sprintf(specifier2, "iCc%s/I", nmSigCascDcyBrs);
                              tr->Branch(specifier1, &iCcSigCascDcyBrs[i], specifier2);
                              iCcSigCascDcyBrs[i]=m_vICcSigCascDcyBrs[i];
                              sprintf(specifier1, "n%s", nmSigCascDcyBrs);
                              sprintf(specifier2, "n%s/I", nmSigCascDcyBrs);
                              tr->Branch(specifier1, &nSigCascDcyBrs[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmSigCascDcyBrs);
                              sprintf(specifier2, "nCc%s/I", nmSigCascDcyBrs);
                              tr->Branch(specifier1, &nCcSigCascDcyBrs[i], specifier2);
                              sprintf(specifier1, "nTot%s", nmSigCascDcyBrs);
                              sprintf(specifier2, "nTot%s/I", nmSigCascDcyBrs);
                              tr->Branch(specifier1, &nTotSigCascDcyBrs[i], specifier2);
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmSigCascDcyBrs);
                              sprintf(specifier2, "n%s/I", nmSigCascDcyBrs);
                              tr->Branch(specifier1, &nSigCascDcyBrs[i], specifier2);
                            }
                        }
                    }
                }
              if(m_vSigIncCascDcyBrs.size()>0)
                {
                  if(m_useArrayBrsOpt==true)
                    {
                      char specifier[30];
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier, "iCcSigIncCascDcyBrs[%d]/I", int(sSigIncCascDcyBrs));
                          tr->Branch("iCcSigIncCascDcyBrs", &iCcSigIncCascDcyBrs, specifier);
                          for(unsigned int i=0;i<sSigIncCascDcyBrs;i++) iCcSigIncCascDcyBrs[i]=m_vICcSigIncCascDcyBrs[i];
                          sprintf(specifier, "nSigIncCascDcyBrs[%d]/I", int(sSigIncCascDcyBrs));
                          tr->Branch("nSigIncCascDcyBrs", &nSigIncCascDcyBrs, specifier);
                          sprintf(specifier, "nCcSigIncCascDcyBrs[%d]/I", int(sSigIncCascDcyBrs));
                          tr->Branch("nCcSigIncCascDcyBrs", &nCcSigIncCascDcyBrs, specifier);
                          sprintf(specifier, "nTotSigIncCascDcyBrs[%d]/I", int(sSigIncCascDcyBrs));
                          tr->Branch("nTotSigIncCascDcyBrs", &nTotSigIncCascDcyBrs, specifier);
                        }
                      else
                        {
                          sprintf(specifier, "nSigIncCascDcyBrs[%d]/I", int(sSigIncCascDcyBrs));
                          tr->Branch("nSigIncCascDcyBrs", &nSigIncCascDcyBrs, specifier);
                        }
                    }
                  else
                    {
                      char nmSigIncCascDcyBrs[20];
                      char specifier1[30], specifier2[30];
                      for(unsigned int i=0;i<m_vSigIncCascDcyBrs.size();i++)
                        {          
                          if(m_vNm_sigIncCascDcyBrs[i].empty()) sprintf(nmSigIncCascDcyBrs, "SigIncCascDcyBrs%d", i);
                          else sprintf(nmSigIncCascDcyBrs, "_%s", m_vNm_sigIncCascDcyBrs[i].c_str());
                          // else strcpy(nmSigIncCascDcyBrs,m_vNm_sigIncCascDcyBrs[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmSigIncCascDcyBrs".
                          if(m_ccSwitch==true)
                            {
                              sprintf(specifier1, "iCc%s", nmSigIncCascDcyBrs);
                              sprintf(specifier2, "iCc%s/I", nmSigIncCascDcyBrs);
                              tr->Branch(specifier1, &iCcSigIncCascDcyBrs[i], specifier2);
                              iCcSigIncCascDcyBrs[i]=m_vICcSigIncCascDcyBrs[i];
                              sprintf(specifier1, "n%s", nmSigIncCascDcyBrs);
                              sprintf(specifier2, "n%s/I", nmSigIncCascDcyBrs);
                              tr->Branch(specifier1, &nSigIncCascDcyBrs[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmSigIncCascDcyBrs);
                              sprintf(specifier2, "nCc%s/I", nmSigIncCascDcyBrs);
                              tr->Branch(specifier1, &nCcSigIncCascDcyBrs[i], specifier2);
                              sprintf(specifier1, "nTot%s", nmSigIncCascDcyBrs);
                              sprintf(specifier2, "nTot%s/I", nmSigIncCascDcyBrs);
                              tr->Branch(specifier1, &nTotSigIncCascDcyBrs[i], specifier2);
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmSigIncCascDcyBrs);
                              sprintf(specifier2, "n%s/I", nmSigIncCascDcyBrs);
                              tr->Branch(specifier1, &nSigIncCascDcyBrs[i], specifier2);
                            }
                        }
                    }
                }
              if(m_vSigIRADcyBr.size()>0)
                {
                  if(m_useArrayBrsOpt==true)
                    {
                      char specifier[30];
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier, "iCcSigIRADcyBr[%d]/I", int(sSigIRADcyBr));
                          tr->Branch("iCcSigIRADcyBr", &iCcSigIRADcyBr, specifier);
                          for(unsigned int i=0;i<sSigIRADcyBr;i++) iCcSigIRADcyBr[i]=m_vICcSigIRADcyBr[i];
                          sprintf(specifier, "nSigIRADcyBr[%d]/I", int(sSigIRADcyBr));
                          tr->Branch("nSigIRADcyBr", &nSigIRADcyBr, specifier);
                          sprintf(specifier, "nCcSigIRADcyBr[%d]/I", int(sSigIRADcyBr));
                          tr->Branch("nCcSigIRADcyBr", &nCcSigIRADcyBr, specifier);
                          sprintf(specifier, "nTotSigIRADcyBr[%d]/I", int(sSigIRADcyBr));
                          tr->Branch("nTotSigIRADcyBr", &nTotSigIRADcyBr, specifier);
                        }
                      else
                        {
                          sprintf(specifier, "nSigIRADcyBr[%d]/I", int(sSigIRADcyBr));
                          tr->Branch("nSigIRADcyBr", &nSigIRADcyBr, specifier);
                        }
                    }
                  else
                    {
                      char nmSigIRADcyBr[20];
                      char specifier1[30], specifier2[30];
                      for(unsigned int i=0;i<m_vSigIRADcyBr.size();i++)
                        {
                          if(m_vNm_sigIRADcyBr[i].empty()) sprintf(nmSigIRADcyBr, "SigIRADcyBr%d", i);
                          else sprintf(nmSigIRADcyBr, "_%s", m_vNm_sigIRADcyBr[i].c_str());
                          // else strcpy(nmSigIRADcyBr,m_vNm_sigIRADcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmSigIRADcyBr".
                          if(m_ccSwitch==true)
                            {
                              sprintf(specifier1, "iCc%s", nmSigIRADcyBr);
                              sprintf(specifier2, "iCc%s/I", nmSigIRADcyBr);
                              tr->Branch(specifier1, &iCcSigIRADcyBr[i], specifier2);
                              iCcSigIRADcyBr[i]=m_vICcSigIRADcyBr[i];
                              sprintf(specifier1, "n%s", nmSigIRADcyBr);
                              sprintf(specifier2, "n%s/I", nmSigIRADcyBr);
                              tr->Branch(specifier1, &nSigIRADcyBr[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmSigIRADcyBr);
                              sprintf(specifier2, "nCc%s/I", nmSigIRADcyBr);
                              tr->Branch(specifier1, &nCcSigIRADcyBr[i], specifier2);
                              sprintf(specifier1, "nTot%s", nmSigIRADcyBr);
                              sprintf(specifier2, "nTot%s/I", nmSigIRADcyBr);
                              tr->Branch(specifier1, &nTotSigIRADcyBr[i], specifier2);
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmSigIRADcyBr);
                              sprintf(specifier2, "n%s/I", nmSigIRADcyBr);
                              tr->Branch(specifier1, &nSigIRADcyBr[i], specifier2);
                            }
                        }
                    }
                }
              if(m_vSigIncOrIRACascDcyBrs.size()>0)
                {
                  if(m_useArrayBrsOpt==true)
                    {
                      char specifier[50];
                      if(m_ccSwitch==true)
                        {
                          sprintf(specifier, "iCcSigIncOrIRACascDcyBrs[%d]/I", int(sSigIncOrIRACascDcyBrs));
                          tr->Branch("iCcSigIncOrIRACascDcyBrs", &iCcSigIncOrIRACascDcyBrs, specifier);
                          for(unsigned int i=0;i<sSigIncOrIRACascDcyBrs;i++) iCcSigIncOrIRACascDcyBrs[i]=m_vICcSigIncOrIRACascDcyBrs[i];
                          sprintf(specifier, "nSigIncOrIRACascDcyBrs[%d]/I", int(sSigIncOrIRACascDcyBrs));
                          tr->Branch("nSigIncOrIRACascDcyBrs", &nSigIncOrIRACascDcyBrs, specifier);
                          sprintf(specifier, "nCcSigIncOrIRACascDcyBrs[%d]/I", int(sSigIncOrIRACascDcyBrs));
                          tr->Branch("nCcSigIncOrIRACascDcyBrs", &nCcSigIncOrIRACascDcyBrs, specifier);
                          sprintf(specifier, "nTotSigIncOrIRACascDcyBrs[%d]/I", int(sSigIncOrIRACascDcyBrs));
                          tr->Branch("nTotSigIncOrIRACascDcyBrs", &nTotSigIncOrIRACascDcyBrs, specifier);
                        }
                      else
                        {
                          sprintf(specifier, "nSigIncOrIRACascDcyBrs[%d]/I", int(sSigIncOrIRACascDcyBrs));
                          tr->Branch("nSigIncOrIRACascDcyBrs", &nSigIncOrIRACascDcyBrs, specifier);
                        }
                    }
                  else
                    {
                      char nmSigIncOrIRACascDcyBrs[40];
                      char specifier1[50], specifier2[50];
                      for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBrs.size();i++)
                        {
                          if(m_vNm_sigIncOrIRACascDcyBrs[i].empty()) sprintf(nmSigIncOrIRACascDcyBrs, "SigIncOrIRACascDcyBrs%d", i);
                          else sprintf(nmSigIncOrIRACascDcyBrs, "_%s", m_vNm_sigIncOrIRACascDcyBrs[i].c_str());
                          // else strcpy(nmSigIncOrIRACascDcyBrs,m_vNm_sigIncOrIRACascDcyBrs[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nmSigIncOrIRACascDcyBrs".
                          if(m_ccSwitch==true)
                            {
                              sprintf(specifier1, "iCc%s", nmSigIncOrIRACascDcyBrs);
                              sprintf(specifier2, "iCc%s/I", nmSigIncOrIRACascDcyBrs);
                              tr->Branch(specifier1, &iCcSigIncOrIRACascDcyBrs[i], specifier2);
                              iCcSigIncOrIRACascDcyBrs[i]=m_vICcSigIncOrIRACascDcyBrs[i];
                              sprintf(specifier1, "n%s", nmSigIncOrIRACascDcyBrs);
                              sprintf(specifier2, "n%s/I", nmSigIncOrIRACascDcyBrs);
                              tr->Branch(specifier1, &nSigIncOrIRACascDcyBrs[i], specifier2);
                              sprintf(specifier1, "nCc%s", nmSigIncOrIRACascDcyBrs);
                              sprintf(specifier2, "nCc%s/I", nmSigIncOrIRACascDcyBrs);
                              tr->Branch(specifier1, &nCcSigIncOrIRACascDcyBrs[i], specifier2);
                              sprintf(specifier1, "nTot%s", nmSigIncOrIRACascDcyBrs);
                              sprintf(specifier2, "nTot%s/I", nmSigIncOrIRACascDcyBrs);
                              tr->Branch(specifier1, &nTotSigIncOrIRACascDcyBrs[i], specifier2);
                            }
                          else
                            {
                              sprintf(specifier1, "n%s", nmSigIncOrIRACascDcyBrs);
                              sprintf(specifier2, "n%s/I", nmSigIncOrIRACascDcyBrs);
                              tr->Branch(specifier1, &nSigIncOrIRACascDcyBrs[i], specifier2);
                            }
                        }
                    }
                }
            }

          chn->GetEntry(i);

          if(!m_cut.empty())
            { 
              // The following four statements are used to handle the cases where array variables are used in the cut.
              nInsts=trfml->GetNdata(); // This statement is indispensable if multiple instances have to be evaluated by the object of the TTreeFormula class.
              bool passTheCut;
              if(m_cutMethod==true)
                {
                  passTheCut=false; 
                  for(unsigned int j=0;j<nInsts;j++) if(trfml->EvalInstance(j)) {passTheCut=true; break;}
                }
              else
                {
                  passTheCut=true; 
                  for(unsigned int j=0;j<nInsts;j++) if(!(trfml->EvalInstance(j))) {passTheCut=false; break;}
                }
              if(!passTheCut)
                {
                  if((i+1>=nEtrsForTiming)&&(((i+1)%nEtrsForTiming==0)||((i+1)==nEtrsToBePrcsd)))
                    {
                      if((i+1)==nEtrsForTiming) cout<<"Number of entries processed\tNumber of seconds elapsed"<<endl<<endl;
                      cout<<setiosflags(ios::right)<<setw(14)<<i+1<<"\t\t\t"<<setiosflags(ios::fixed)<<setprecision(2)<<setw(14)<<(clock()-starttime)/((double) CLOCKS_PER_SEC)<<resetiosflags(ios::adjustfield)<<endl;
                      if((i+1)==nEtrsToBePrcsd) cout<<endl;
                    }

                  if(m_oneOptRootFlByOneIptRootFl==true) closeTheOptRootFl2=((i+1)==vNEtrs[iOptRootFls]);
                  else closeTheOptRootFl2=((m_nEtrsMaxInASngOptRootFl!=ULONG_MAX)&&((i+1)%m_nEtrsMaxInASngOptRootFl==0));
                  closeTheOptRootFl3=((i+1)==nEtrsToBePrcsd);
                  if(closeTheOptRootFl2||closeTheOptRootFl3)
                    {
                      fl->Write();
                      delete tr; // Pay attention to that replacing the "delete tr" by "tr->Delete()" will result in a problem of "*** Break *** segmentation violation".
                      fl->Close();
                      delete fl;
                      if(m_cpIptBrs==false) rmIptBrs(NmOfOptRootFl);
                      if(m_useArrayBrsOpt==false) flatArrayBrs(NmOfOptRootFl);
                      openANewOptRootFl=true;
                      iOptRootFls++;
                    }

                  continue;
                }   
              else
                {
                  nEtrsThroughTheCut++;
                }
            }
     
          if(m_strgTpOfRawIptTopoDat=="MDV") reviseIptQts(Npsd,Pidd,Midxd,Nps,Pid,Midx);

          vPid.clear();
          vMidx.clear();
          if(m_strgTpOfRawIptTopoDat=="AI"||m_strgTpOfRawIptTopoDat=="MIV"||m_strgTpOfRawIptTopoDat=="MDV")
            {
              for(int j=0;j<Nps;j++)
                {
                  vPid.push_back(Pid[j]);
                  vMidx.push_back(Midx[j]);
                  //cout<<j<<"\t"<<Pid[j]<<"\t"<<Midx[j]<<endl; 
                }
            }
          else
            {
              for(unsigned int j=0;j<pVPid->size();j++)
                {
                  vPid.push_back(pVPid->at(j));
                  vMidx.push_back(pVMidx->at(j));
                  //cout<<j<<"\t"<<Pid[j]<<"\t"<<Midx[j]<<endl;
                }
            }
          //cout<<endl;
          /*for(unsigned int j=0;j<vPid.size();j++)
            {
              cout<<j<<"\t"<<vPid[j]<<"\t"<<vMidx[j]<<endl;
            }
          cout<<endl;*/
          sortPs(vPid,vMidx);
          dcyTr.clear();
          vIdxOfHead.clear();
          vMidxOfHead.clear();
          getDcyTr(vPid,vMidx,dcyTr,vIdxOfHead,vMidxOfHead);
          oss.str("");
          list<int> dcyBr;
          for(unsigned int j=0;j<dcyTr.size();j++)
            {
              if(j==0&&m_initEpEmSwitch==true&&dcyTr[0].size()==3) continue; 
              dcyBr.clear();
              dcyBr=dcyTr[j];
              list<int>::iterator liit=dcyBr.begin();
              oss<<(*liit)<<" ";
              // The condition "j==0" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if(j==0||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  oss<<(*liit)<<" ";
                }
              oss<<"> ";
              list<int>::iterator liitTmp=dcyBr.end();
              liitTmp--;
              for(liit++;liit!=liitTmp;liit++) oss<<(*liit)<<" ";
              oss<<(*liit);
              if(j!=(dcyTr.size()-1)) oss<<", ";
            }
          strDcyTr=oss.str();
          //cout<<i<<"\t"<<strDcyTr<<endl<<endl; 
          dcyIFSts.clear();
          getDcyIFSts(vPid,vMidx,dcyIFSts);
          oss.str("");
          list<int>::iterator liit;
          if(m_initEpEmSwitch==true&&dcyTr[0].size()==3)
            {
              liit=dcyTr[0].begin();
              liit++;
              liit++;
              oss<<(*liit)<<" ";
              liit=dcyIFSts.begin();
              liit++;
            }
          else
            {
              liit=dcyIFSts.begin();
              oss<<(*liit)<<" ";   
              liit++;
              oss<<(*liit)<<" ";
            }
          oss<<"> ";
          list<int>::iterator liitTmp=dcyIFSts.end();
          liitTmp--;
          for(liit++;liit!=liitTmp;liit++) oss<<(*liit)<<" ";
          oss<<(*liit);
          strDcyIFSts=oss.str();
          //cout<<i<<"\t"<<strDcyIFSts<<endl<<endl;
          if(m_ccSwitch==true)
            { 
              vCcPid.clear(); 
              vCcMidx.clear(); 
              for(unsigned int j=0;j<vPid.size();j++) vCcPid.push_back(getCcPid(vPid[j]));
              vCcMidx=vMidx;
              sortPs(vCcPid,vCcMidx);
              ccDcyTr.clear();
              vCcIdxOfHead.clear();
              vCcMidxOfHead.clear();
              getDcyTr(vCcPid,vCcMidx,ccDcyTr,vCcIdxOfHead,vCcMidxOfHead);
              oss.str("");
              list<int> ccDcyBr;
              for(unsigned int j=0;j<ccDcyTr.size();j++)
                {
                  if(j==0&&m_initEpEmSwitch==true&&ccDcyTr[0].size()==3) continue;
                  ccDcyBr.clear();
                  ccDcyBr=ccDcyTr[j];
                  list<int>::iterator liit=ccDcyBr.begin();
                  oss<<(*liit)<<" ";
                  // The condition "j==0" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
                  if(j==0||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                    {
                      liit++;
                      oss<<(*liit)<<" ";
                    }
                  oss<<"> ";
                  list<int>::iterator liitTmp=ccDcyBr.end();
                  liitTmp--;
                  for(liit++;liit!=liitTmp;liit++) oss<<(*liit)<<" ";
                  oss<<(*liit);
                  if(j!=(ccDcyTr.size()-1)) oss<<", ";
                }
              strCcDcyTr=oss.str();
              //cout<<i<<"\t"<<strCcDcyTr<<endl<<endl;
              ccDcyIFSts.clear();
              getDcyIFSts(vCcPid,vCcMidx,ccDcyIFSts);
              oss.str("");
              list<int>::iterator liit;
              if(m_initEpEmSwitch==true&&ccDcyTr[0].size()==3)
                {
                  liit=ccDcyTr[0].begin();
                  liit++;
                  liit++;
                  oss<<(*liit)<<" ";
                  liit=ccDcyIFSts.begin();
                  liit++;
                }
              else
                {
                  liit=ccDcyIFSts.begin();
                  oss<<(*liit)<<" ";
                  liit++;
                  oss<<(*liit)<<" ";
                }
              oss<<"> ";
              list<int>::iterator liitTmp=ccDcyIFSts.end();
              liitTmp--;
              for(liit++;liit!=liitTmp;liit++) oss<<(*liit)<<" ";
              oss<<(*liit);
              strCcDcyIFSts=oss.str();
              //cout<<i<<"\t"<<strCcDcyIFSts<<endl<<endl;
            }

         if(m_compAnaOfDcyTrs==true)
           {
             iDcyTr=-1; // If the variable is still equal to -1 after the following loop, then the decay tree is a new decay tree.
             // To get a higher search efficiency, the following code segment is replaced by the next one, which is featured by the use of "unordered_map".
             /*for(unsigned int j=0;j<m_vDcyTr.size();j++)
               {
                 if(dcyTr==m_vDcyTr[j])
                   {
                     iDcyTr=j;
                     iDcyIFSts=m_iDcyTrIDcyIFStsMap[iDcyTr];
                     if(m_ccSwitch==true)
                       {
                         iCcDcyTr=m_vICcDcyTr[j];
                         iCcDcyIFSts=m_iDcyTrICcDcyIFStsMap[iDcyTr];
                       }
                     break;
                   }
                 else if(m_ccSwitch==true&&m_vICcDcyTr[j]!=0&&dcyTr==m_vCcDcyTr[j])
                   {
                     iDcyTr=j;
                     iDcyIFSts=m_iDcyTrIDcyIFStsMap[iDcyTr];
                     iCcDcyTr=-1;
                     iCcDcyIFSts=-1*m_iDcyTrICcDcyIFStsMap[iDcyTr];
                     break;
                   }
               }*/
             if(m_uomDcyTr.find(strDcyTr)!=m_uomDcyTr.end())
               { 
                 iDcyTr=m_uomDcyTr[strDcyTr];
                 iDcyIFSts=m_iDcyTrIDcyIFStsMap[iDcyTr];
                 if(m_ccSwitch==true)
                   { 
                     iCcDcyTr=m_vICcDcyTr[iDcyTr];
                     iCcDcyIFSts=m_iDcyTrICcDcyIFStsMap[iDcyTr];
                   }
               }
             else if(m_ccSwitch==true&&m_uomCcDcyTr.find(strDcyTr)!=m_uomCcDcyTr.end())
               { 
                 iDcyTr=m_uomCcDcyTr[strDcyTr];
                 iDcyIFSts=m_iDcyTrIDcyIFStsMap[iDcyTr];
                 iCcDcyTr=-1;
                 iCcDcyIFSts=-1*m_iDcyTrICcDcyIFStsMap[iDcyTr];
               }
             if(iDcyTr==-1)
               {
                 iDcyTr=m_vDcyTr.size();
                 m_vDcyTr.push_back(dcyTr);
                 m_vIDcyTr.push_back(iDcyTr);
                 m_vNDcyTr.push_back(1);
                 m_uomDcyTr[strDcyTr]=iDcyTr;
                 if(m_ccSwitch==true)
                   {
                     if(ccDcyTr==dcyTr) iCcDcyTr=0;
                     else iCcDcyTr=1;
                     m_vCcDcyTr.push_back(ccDcyTr);
                     m_vICcDcyTr.push_back(iCcDcyTr);
                     m_vNCcDcyTr.push_back(0);
                     m_uomCcDcyTr[strCcDcyTr]=iDcyTr;
                   }

                 iDcyIFSts=-1; // If the variable is still equal to -1 after the following loop, then the decay initial-final states is a new decay initial-final states.
                 // To get a higher search efficiency, the following code segment is replaced by the next one, which is featured by the use of "unordered_map".
                 /*for(unsigned int j=0;j<m_vDcyIFSts.size();j++)
                   {
                     if(dcyIFSts==m_vDcyIFSts[j])
                       {
                         iDcyIFSts=j;
                         if(m_ccSwitch==true) iCcDcyIFSts=m_vICcDcyIFSts[j];
                         break;
                       }
                     else if(m_ccSwitch==true&&m_vICcDcyIFSts[j]!=0&&dcyIFSts==m_vCcDcyIFSts[j])
                       {
                         iDcyIFSts=j;
                         iCcDcyIFSts=-1;
                         break;
                       }              
                   }*/
                 if(m_uomDcyIFSts.find(strDcyIFSts)!=m_uomDcyIFSts.end())
                   {
                     iDcyIFSts=m_uomDcyIFSts[strDcyIFSts];
                     if(m_ccSwitch==true) iCcDcyIFSts=m_vICcDcyIFSts[iDcyIFSts];
                   }
                 else if(m_ccSwitch==true&&m_uomCcDcyIFSts.find(strDcyIFSts)!=m_uomCcDcyIFSts.end())
                   {
                     iDcyIFSts=m_uomCcDcyIFSts[strDcyIFSts];
                     iCcDcyIFSts=-1;
                   }
                 if(iDcyIFSts==-1)
                   {
                     iDcyIFSts=m_vDcyIFSts.size();
                     m_vDcyIFSts.push_back(dcyIFSts);
                     m_vIDcyIFSts.push_back(iDcyIFSts);
                     m_vNDcyIFSts.push_back(1);
                     m_uomDcyIFSts[strDcyIFSts]=iDcyIFSts;
                     if(m_ccSwitch==true)
                       {
                         if(ccDcyIFSts==dcyIFSts) iCcDcyIFSts=0;
                         else iCcDcyIFSts=1;
                         m_vCcDcyIFSts.push_back(ccDcyIFSts);
                         m_vICcDcyIFSts.push_back(iCcDcyIFSts);
                         m_vNCcDcyIFSts.push_back(0);
                         m_uomCcDcyIFSts[strCcDcyIFSts]=iDcyIFSts;
                       } 
                   }
                 else
                   {
                     if(m_ccSwitch==true)
                       {
                         if(iCcDcyIFSts==-1) m_vNCcDcyIFSts[iDcyIFSts]++;
                         else m_vNDcyIFSts[iDcyIFSts]++;
                       }
                     else m_vNDcyIFSts[iDcyIFSts]++;             
                   }
                 m_iDcyTrIDcyIFStsMap[iDcyTr]=iDcyIFSts;
                 if(m_ccSwitch==true) m_iDcyTrICcDcyIFStsMap[iDcyTr]=iCcDcyIFSts;
               }
             else
               {
                 if(m_ccSwitch==true)
                   {
                     if(iCcDcyTr==-1) m_vNCcDcyTr[iDcyTr]++;
                     else m_vNDcyTr[iDcyTr]++;
                     if(iCcDcyIFSts==-1) m_vNCcDcyIFSts[iDcyIFSts]++;
                     else m_vNDcyIFSts[iDcyIFSts]++;
                   }
                 else
                   {
                     m_vNDcyTr[iDcyTr]++;
                     m_vNDcyIFSts[iDcyIFSts]++;
                   }
               }
            }
          else if(m_compAnaOfDcyIFSts==true)
            {
              iDcyIFSts=-1; // If the variable is still equal to -1 after the following loop, then the decay initial-final states is a new decay initial-final states.
              // To get a higher search efficiency, the following code segment is replaced by the next one, which is featured by the use of "unordered_map".
              /*for(unsigned int j=0;j<m_vDcyIFSts.size();j++)
                {
                  if(dcyIFSts==m_vDcyIFSts[j])
                    {
                      iDcyIFSts=j;
                      if(m_ccSwitch==true) iCcDcyIFSts=m_vICcDcyIFSts[j];
                      break;
                    }
                  else if(m_ccSwitch==true&&m_vICcDcyIFSts[j]!=0&&dcyIFSts==m_vCcDcyIFSts[j])
                    {
                      iDcyIFSts=j;
                      iCcDcyIFSts=-1;
                      break;
                    }              
                }*/
              if(m_uomDcyIFSts.find(strDcyIFSts)!=m_uomDcyIFSts.end())
                {
                  iDcyIFSts=m_uomDcyIFSts[strDcyIFSts];
                  if(m_ccSwitch==true) iCcDcyIFSts=m_vICcDcyIFSts[iDcyIFSts];
                }
              else if(m_ccSwitch==true&&m_uomCcDcyIFSts.find(strDcyIFSts)!=m_uomCcDcyIFSts.end())
                {
                  iDcyIFSts=m_uomCcDcyIFSts[strDcyIFSts];
                  iCcDcyIFSts=-1;
                }
              if(iDcyIFSts==-1)
                {
                  iDcyIFSts=m_vDcyIFSts.size();
                  m_vDcyIFSts.push_back(dcyIFSts);
                  m_vIDcyIFSts.push_back(iDcyIFSts);
                  m_vNDcyIFSts.push_back(1);
                  m_uomDcyIFSts[strDcyIFSts]=iDcyIFSts;
                  if(m_ccSwitch==true)
                    {
                      if(ccDcyIFSts==dcyIFSts) iCcDcyIFSts=0;
                      else iCcDcyIFSts=1;
                      m_vCcDcyIFSts.push_back(ccDcyIFSts);
                      m_vICcDcyIFSts.push_back(iCcDcyIFSts);
                      m_vNCcDcyIFSts.push_back(0);
                      m_uomCcDcyIFSts[strCcDcyIFSts]=iDcyIFSts;
                    } 
                }
              else
                {
                  if(m_ccSwitch==true)
                    {
                      if(iCcDcyIFSts==-1) m_vNCcDcyIFSts[iDcyIFSts]++;
                      else m_vNDcyIFSts[iDcyIFSts]++;
                    }
                  else m_vNDcyIFSts[iDcyIFSts]++;             
                }
            }

          if(m_vPid_compP.size()>0)
            {
              // Pay attention to that dcyBrCcP equate to ccDcyBrP for self-charge-conjugate particles.
              list<int> dcyBrP, dcyBrCcP;
              dcyBrP.clear(); dcyBrCcP.clear();
              for(unsigned int j=0;j<m_vPid_compP.size();j++)
                {
                  nP[j]=0;
                  if(m_ccSwitch==true&&m_vICcCompP[j]!=0)
                    {
                      nCcP[j]=0;
                      nTotP[j]=0;
                    }
                }     
              for(unsigned int j=0;j<dcyTr.size();j++)
                {
                  list<int>::iterator liit=dcyTr[j].begin();
                  for(unsigned int k=0;k<m_vPid_compP.size();k++)
                    {
                      if((*liit)==m_vPid_compP[k])
                        {
                          dcyBrP=dcyTr[j];
                          int _iDcyBrP=-1; // If the variable is still equal to -1 after the following loop, then the decay branch of the particle is a new decay branch of the particle.
                          int _iCcDcyBrP=-9999;
                          for(unsigned int l=0;l<m_vVDcyBrP[k].size();l++)
                            {
                              if(dcyBrP==m_vVDcyBrP[k][l])
                                {
                                  _iDcyBrP=l;
                                  if(m_ccSwitch==true&&m_vICcCompP[k]==0) _iCcDcyBrP=m_vVIDcyBrCcP[k][l];
                                  break;
                                }
                              else if(m_ccSwitch==true&&m_vICcCompP[k]==0&&m_vVIDcyBrCcP[k][l]!=0&&dcyBrP==m_vVDcyBrCcP[k][l])
                                {
                                  _iDcyBrP=l;
                                  _iCcDcyBrP=-1;
                                  break;
                                }
                            }
                          if(_iDcyBrP==-1)
                            {
                              _iDcyBrP=m_vVDcyBrP[k].size();
                              iDcyBrP[k][(unsigned int) (nP[k])]=_iDcyBrP;
                              m_vVDcyBrP[k].push_back(dcyBrP);
                              m_vVIDcyBrP[k].push_back(_iDcyBrP);
                              m_vVNDcyBrP[k].push_back(1);
                              if(m_ccSwitch==true)
                                {
                                  dcyBrCcP.clear();
                                  list<int>::iterator liit=dcyBrP.begin();
                                  for(liit++;liit!=dcyBrP.end();liit++) dcyBrCcP.push_back(getCcPid((*liit)));
                                  sortByPidAndPchrg(dcyBrCcP); 
                                  liit=dcyBrP.begin();
                                  if(m_vICcCompP[k]!=0)
                                    {
                                      dcyBrCcP.push_front(getCcPid((*liit))); // Here, (*liit) is not equal to getCcPid((*liit)).
                                      m_vVDcyBrCcP[k].push_back(dcyBrCcP);
                                      m_vVIDcyBrCcP[k].push_back(_iDcyBrP);
                                      m_vVNDcyBrCcP[k].push_back(0);
                                    }    
                                  else
                                    {
                                      dcyBrCcP.push_front((*liit)); // Here, (*liit) is equal to getCcPid((*liit)).
                                      if(dcyBrCcP==dcyBrP) _iCcDcyBrP=0;
                                      else _iCcDcyBrP=1;
                                      iCcDcyBrP[k][(unsigned int) (nP[k])]=_iCcDcyBrP;
                                      m_vVDcyBrCcP[k].push_back(dcyBrCcP);
                                      m_vVIDcyBrCcP[k].push_back(_iCcDcyBrP);
                                      m_vVNDcyBrCcP[k].push_back(0);
                                    }
                                }
                            }
                          else
                            {
                              iDcyBrP[k][(unsigned int) (nP[k])]=_iDcyBrP;
                              if(m_ccSwitch==true&&m_vICcCompP[k]==0)
                                {
                                  iCcDcyBrP[k][(unsigned int) (nP[k])]=_iCcDcyBrP;
                                  if(_iCcDcyBrP==-1) m_vVNDcyBrCcP[k][_iDcyBrP]++;
                                  else m_vVNDcyBrP[k][_iDcyBrP]++;
                                }
                              else
                                {
                                  m_vVNDcyBrP[k][_iDcyBrP]++;
                                }
                            }
                          nP[k]++;
                          break;
                        } // Here, "&&m_vICcCompP[k]!=0" in the following condition can be removed.
                      else if(m_ccSwitch==true&&m_vICcCompP[k]!=0&&(*liit)==m_vPid_ccCompP[k])
                        {
                          dcyBrCcP=dcyTr[j];
                          int _iDcyBrP=-1; // If the variable is still equal to -1 after the following loop, then the decay branch of the particle is a new decay branch of the particle.
                          for(unsigned int l=0;l<m_vVDcyBrCcP[k].size();l++)
                            {
                              if(dcyBrCcP==m_vVDcyBrCcP[k][l])
                                {
                                  _iDcyBrP=l;
                                  break;
                                }
                            }
                          if(_iDcyBrP==-1)
                            {
                              _iDcyBrP=m_vVDcyBrP[k].size();
                              iDcyBrCcP[k][(unsigned int) (nCcP[k])]=_iDcyBrP;
                              m_vVDcyBrCcP[k].push_back(dcyBrCcP);
                              m_vVIDcyBrCcP[k].push_back(_iDcyBrP);
                              m_vVNDcyBrCcP[k].push_back(1);

                              dcyBrP.clear();
                              list<int>::iterator liit=dcyBrCcP.begin();
                              for(liit++;liit!=dcyBrCcP.end();liit++) dcyBrP.push_back(getCcPid((*liit)));
                              sortByPidAndPchrg(dcyBrP);
                              liit=dcyBrCcP.begin();
                              dcyBrP.push_front(getCcPid((*liit))); // Here, (*liit) is not equal to getCcPid((*liit)).
                              m_vVDcyBrP[k].push_back(dcyBrP);
                              m_vVIDcyBrP[k].push_back(_iDcyBrP);
                              m_vVNDcyBrP[k].push_back(0);
                            }
                          else
                            {
                              iDcyBrCcP[k][(unsigned int) (nCcP[k])]=_iDcyBrP;
                              m_vVNDcyBrCcP[k][_iDcyBrP]++;
                            }
                          nCcP[k]++;
                          break;                                    
                        }
                    }
                }
              if(m_ccSwitch==true) for(unsigned int j=0;j<m_vPid_compP.size();j++) if(m_vICcCompP[j]!=0) nTotP[j]=nP[j]+nCcP[j];
            }

          if(m_vCompIncDcyBr.size()>0)
            {
              // Pay attention to that dcyBrCcIncDcyBr equate to ccDcyBrIncDcyBr for self-charge-conjugate inclusive decays.
              list<int> dcyBrIncDcyBr, dcyBrCcIncDcyBr;
              dcyBrIncDcyBr.clear(); dcyBrCcIncDcyBr.clear();
              for(unsigned int j=0;j<m_vCompIncDcyBr.size();j++)
                {
                  nIncDcyBr[j]=0;
                  if(m_ccSwitch==true&&m_vCompICcIncDcyBr[j]!=0)
                    {
                      nCcIncDcyBr[j]=0;
                      nTotIncDcyBr[j]=0;
                    }
                }     
              for(unsigned int j=0;j<dcyTr.size();j++)
                {
                  for(unsigned int k=0;k<m_vCompIncDcyBr.size();k++)
                    {
                      if(isLiaMatchedWithLib(m_vCompIncDcyBr[k],dcyTr[j]))
                        {
                          dcyBrIncDcyBr=dcyTr[j];
                          int _iDcyBrIncDcyBr=-1; // If the variable is still equal to -1 after the following loop, then the decay branch of the inclusive decay branch is a new exclusive decay branch of the inclusive decay branch.
                          int _iCcDcyBrIncDcyBr=-9999;
                          for(unsigned int l=0;l<m_vVDcyBrIncDcyBr[k].size();l++)
                            {
                              if(dcyBrIncDcyBr==m_vVDcyBrIncDcyBr[k][l])
                                {
                                  _iDcyBrIncDcyBr=l;
                                  if(m_ccSwitch==true&&m_vCompICcIncDcyBr[k]==0) _iCcDcyBrIncDcyBr=m_vVIDcyBrCcIncDcyBr[k][l];
                                  break;
                                }
                              else if(m_ccSwitch==true&&m_vCompICcIncDcyBr[k]==0&&m_vVIDcyBrCcIncDcyBr[k][l]!=0&&dcyBrIncDcyBr==m_vVDcyBrCcIncDcyBr[k][l])
                                {
                                  _iDcyBrIncDcyBr=l;
                                  _iCcDcyBrIncDcyBr=-1;
                                  break;
                                }
                            }
                          if(_iDcyBrIncDcyBr==-1)
                            {
                              _iDcyBrIncDcyBr=m_vVDcyBrIncDcyBr[k].size();
                              iDcyBrIncDcyBr[k][(unsigned int) (nIncDcyBr[k])]=_iDcyBrIncDcyBr;
                              m_vVDcyBrIncDcyBr[k].push_back(dcyBrIncDcyBr);
                              m_vVIDcyBrIncDcyBr[k].push_back(_iDcyBrIncDcyBr);
                              m_vVNDcyBrIncDcyBr[k].push_back(1);
                              if(m_ccSwitch==true)
                                {
                                  dcyBrCcIncDcyBr.clear();
                                  list<int>::iterator liit=dcyBrIncDcyBr.begin();
                                  if((*liit)==-11) liit++;
                                  for(liit++;liit!=dcyBrIncDcyBr.end();liit++) dcyBrCcIncDcyBr.push_back(getCcPid((*liit)));
                                  sortByPidAndPchrg(dcyBrCcIncDcyBr); 
                                  liit=dcyBrIncDcyBr.begin();
                                  if(m_vCompICcIncDcyBr[k]!=0)
                                    {
                                      if((*liit)!=-11)
                                        {
                                          dcyBrCcIncDcyBr.push_front(getCcPid((*liit))); // Here, (*liit) is not equal to getCcPid((*liit)).
                                        }
                                      else
                                        {
                                          dcyBrCcIncDcyBr.push_front(11);
                                          dcyBrCcIncDcyBr.push_front(-11);
                                        }
                                      m_vVDcyBrCcIncDcyBr[k].push_back(dcyBrCcIncDcyBr);
                                      m_vVIDcyBrCcIncDcyBr[k].push_back(_iDcyBrIncDcyBr);
                                      m_vVNDcyBrCcIncDcyBr[k].push_back(0);
                                    }    
                                  else
                                    {
                                      if((*liit)!=-11)
                                        {
                                          dcyBrCcIncDcyBr.push_front((*liit)); // Here, (*liit) is equal to getCcPid((*liit)).
                                        }
                                      else
                                        {
                                          dcyBrCcIncDcyBr.push_front(11);
                                          dcyBrCcIncDcyBr.push_front(-11);
                                        }
                                      if(dcyBrCcIncDcyBr==dcyBrIncDcyBr) _iCcDcyBrIncDcyBr=0;
                                      else _iCcDcyBrIncDcyBr=1;
                                      iCcDcyBrIncDcyBr[k][(unsigned int) (nIncDcyBr[k])]=_iCcDcyBrIncDcyBr;
                                      m_vVDcyBrCcIncDcyBr[k].push_back(dcyBrCcIncDcyBr);
                                      m_vVIDcyBrCcIncDcyBr[k].push_back(_iCcDcyBrIncDcyBr);
                                      m_vVNDcyBrCcIncDcyBr[k].push_back(0);
                                    }
                                }
                            }
                          else
                            {
                              iDcyBrIncDcyBr[k][(unsigned int) (nIncDcyBr[k])]=_iDcyBrIncDcyBr;
                              if(m_ccSwitch==true&&m_vCompICcIncDcyBr[k]==0)
                                {
                                  iCcDcyBrIncDcyBr[k][(unsigned int) (nIncDcyBr[k])]=_iCcDcyBrIncDcyBr;
                                  if(_iCcDcyBrIncDcyBr==-1) m_vVNDcyBrCcIncDcyBr[k][_iDcyBrIncDcyBr]++;
                                  else m_vVNDcyBrIncDcyBr[k][_iDcyBrIncDcyBr]++;
                                }
                              else
                                {
                                  m_vVNDcyBrIncDcyBr[k][_iDcyBrIncDcyBr]++;
                                }
                            }
                          nIncDcyBr[k]++;
                          break;
                        } // Here, "&&m_vCompICcIncDcyBr[k]!=0" in the following condition can be removed.
                      else if(m_ccSwitch==true&&m_vCompICcIncDcyBr[k]!=0&&isLiaMatchedWithLib(m_vCompCcIncDcyBr[k],dcyTr[j]))
                        {
                          dcyBrCcIncDcyBr=dcyTr[j];
                          int _iDcyBrIncDcyBr=-1; // If the variable is still equal to -1 after the following loop, then the decay branch of the inclusive decay branch is a new exclusive decay branch of the inclusive decay branch.
                          for(unsigned int l=0;l<m_vVDcyBrCcIncDcyBr[k].size();l++)
                            {
                              if(dcyBrCcIncDcyBr==m_vVDcyBrCcIncDcyBr[k][l])
                                {
                                  _iDcyBrIncDcyBr=l;
                                  break;
                                }
                            }
                          if(_iDcyBrIncDcyBr==-1)
                            {
                              _iDcyBrIncDcyBr=m_vVDcyBrIncDcyBr[k].size();
                              iDcyBrCcIncDcyBr[k][(unsigned int) (nCcIncDcyBr[k])]=_iDcyBrIncDcyBr;
                              m_vVDcyBrCcIncDcyBr[k].push_back(dcyBrCcIncDcyBr);
                              m_vVIDcyBrCcIncDcyBr[k].push_back(_iDcyBrIncDcyBr);
                              m_vVNDcyBrCcIncDcyBr[k].push_back(1);

                              dcyBrIncDcyBr.clear();
                              list<int>::iterator liit=dcyBrCcIncDcyBr.begin();
                              if((*liit)==-11) liit++;
                              for(liit++;liit!=dcyBrCcIncDcyBr.end();liit++) dcyBrIncDcyBr.push_back(getCcPid((*liit)));
                              sortByPidAndPchrg(dcyBrIncDcyBr);
                              liit=dcyBrCcIncDcyBr.begin();
                              if((*liit)!=-11)
                                {
                                  dcyBrIncDcyBr.push_front(getCcPid((*liit))); // Here, (*liit) is not equal to getCcPid((*liit)).
                                }
                              else
                                {
                                  dcyBrIncDcyBr.push_front(11);
                                  dcyBrIncDcyBr.push_front(-11);
                                }
                              m_vVDcyBrIncDcyBr[k].push_back(dcyBrIncDcyBr);
                              m_vVIDcyBrIncDcyBr[k].push_back(_iDcyBrIncDcyBr);
                              m_vVNDcyBrIncDcyBr[k].push_back(0);
                            }
                          else
                            {
                              iDcyBrCcIncDcyBr[k][(unsigned int) (nCcIncDcyBr[k])]=_iDcyBrIncDcyBr;
                              m_vVNDcyBrCcIncDcyBr[k][_iDcyBrIncDcyBr]++;
                            }
                          nCcIncDcyBr[k]++;
                          break;                                    
                        }
                    }
                }
              if(m_ccSwitch==true) for(unsigned int j=0;j<m_vCompIncDcyBr.size();j++) if(m_vCompICcIncDcyBr[j]!=0) nTotIncDcyBr[j]=nIncDcyBr[j]+nCcIncDcyBr[j];
            }

          if(m_vCompIRADcyBr.size()>0)
            {
              // Pay attention to that dcyBrCcIRADcyBr equate to ccDcyBrIRADcyBr for self-charge-conjugate intermediate-resonance-allowed decays.
              vector< list<int> > dcyBrIRADcyBr, dcyBrCcIRADcyBr;
              dcyBrIRADcyBr.clear(); dcyBrCcIRADcyBr.clear();
              for(unsigned int j=0;j<m_vCompIRADcyBr.size();j++)
                {
                  nIRADcyBr[j]=0;
                  if(m_ccSwitch==true&&m_vCompICcIRADcyBr[j]!=0)
                    {
                      nCcIRADcyBr[j]=0;
                      nTotIRADcyBr[j]=0;
                    }
                }     
              vector< vector< list<int> > > vDcyBrIRADcyBr,vDcyBrCcIRADcyBr;
              for(unsigned int j=0;j<m_vCompIRADcyBr.size();j++)
                {
                  vDcyBrIRADcyBr.clear();
                  if(countIRADcyBr(vPid,vMidx,m_vCompIRADcyBr[j],false,&vDcyBrIRADcyBr)>0)
                    {
                      for(unsigned int k=0;k<vDcyBrIRADcyBr.size();k++)
                        {
                          dcyBrIRADcyBr=vDcyBrIRADcyBr[k];
                          int _iDcyBrIRADcyBr=-1; // If the variable is still equal to -1 after the following loop, then the decay branch of the intermediate-resonance-allowed decay branch is a new exclusive decay branch of the intermediate-resonance-allowed decay branch.
                          int _iCcDcyBrIRADcyBr=-9999;
                          for(unsigned int l=0;l<m_vVDcyBrIRADcyBr[j].size();l++)
                            {
                              if(dcyBrIRADcyBr==m_vVDcyBrIRADcyBr[j][l])
                                {
                                  _iDcyBrIRADcyBr=l;
                                  if(m_ccSwitch==true&&m_vCompICcIRADcyBr[j]==0) _iCcDcyBrIRADcyBr=m_vVIDcyBrCcIRADcyBr[j][l];
                                  break;
                                }
                              else if(m_ccSwitch==true&&m_vCompICcIRADcyBr[j]==0&&m_vVIDcyBrCcIRADcyBr[j][l]!=0&&dcyBrIRADcyBr==m_vVDcyBrCcIRADcyBr[j][l])
                                {
                                  _iDcyBrIRADcyBr=l;
                                  _iCcDcyBrIRADcyBr=-1;
                                  break;
                                }
                            }
                          if(_iDcyBrIRADcyBr==-1)
                            {
                              _iDcyBrIRADcyBr=m_vVDcyBrIRADcyBr[j].size();
                              iDcyBrIRADcyBr[j][(unsigned int) (nIRADcyBr[j])]=_iDcyBrIRADcyBr;
                              m_vVDcyBrIRADcyBr[j].push_back(dcyBrIRADcyBr);
                              m_vVIDcyBrIRADcyBr[j].push_back(_iDcyBrIRADcyBr);
                              m_vVNDcyBrIRADcyBr[j].push_back(1);
                              if(m_ccSwitch==true)
                                {
                                  dcyBrCcIRADcyBr.clear();
                                  list<int> subDcyBrCcIRADcyBr;
                                  list<int>::iterator liit;
                                  for(unsigned int l=0;l<dcyBrIRADcyBr.size();l++)
                                    {
                                      subDcyBrCcIRADcyBr.clear();
                                      liit=dcyBrIRADcyBr[l].begin();
                                      if(l==0&&(*liit)==-11) liit++;
                                      for(liit++;liit!=dcyBrIRADcyBr[l].end();liit++) subDcyBrCcIRADcyBr.push_back(getCcPid((*liit)));
                                      sortByPidAndPchrg(subDcyBrCcIRADcyBr);
                                      liit=dcyBrIRADcyBr[l].begin();
                                      if(l==0&&(*liit)==-11)
                                        {
                                          subDcyBrCcIRADcyBr.push_front(11);
                                          subDcyBrCcIRADcyBr.push_front(-11);
                                        }
                                      else
                                        {
                                          subDcyBrCcIRADcyBr.push_front(getCcPid((*liit)));
                                        }
                                      dcyBrCcIRADcyBr.push_back(subDcyBrCcIRADcyBr);
                                    }
                                  if(m_vCompICcIRADcyBr[j]!=0)
                                    {
                                      m_vVDcyBrCcIRADcyBr[j].push_back(dcyBrCcIRADcyBr);
                                      m_vVIDcyBrCcIRADcyBr[j].push_back(_iDcyBrIRADcyBr);
                                      m_vVNDcyBrCcIRADcyBr[j].push_back(0);
                                    }    
                                  else
                                    {
                                      if(dcyBrCcIRADcyBr==dcyBrIRADcyBr) _iCcDcyBrIRADcyBr=0;
                                      else _iCcDcyBrIRADcyBr=1;
                                      iCcDcyBrIRADcyBr[j][(unsigned int) (nIRADcyBr[j])]=_iCcDcyBrIRADcyBr;
                                      m_vVDcyBrCcIRADcyBr[j].push_back(dcyBrCcIRADcyBr);
                                      m_vVIDcyBrCcIRADcyBr[j].push_back(_iCcDcyBrIRADcyBr);
                                      m_vVNDcyBrCcIRADcyBr[j].push_back(0);
                                    }
                                }
                            }
                          else
                            {
                              iDcyBrIRADcyBr[j][(unsigned int) (nIRADcyBr[j])]=_iDcyBrIRADcyBr;
                              if(m_ccSwitch==true&&m_vCompICcIRADcyBr[j]==0)
                                {
                                  iCcDcyBrIRADcyBr[j][(unsigned int) (nIRADcyBr[j])]=_iCcDcyBrIRADcyBr;
                                  if(_iCcDcyBrIRADcyBr==-1) m_vVNDcyBrCcIRADcyBr[j][_iDcyBrIRADcyBr]++;
                                  else m_vVNDcyBrIRADcyBr[j][_iDcyBrIRADcyBr]++;
                                }
                              else
                                {
                                  m_vVNDcyBrIRADcyBr[j][_iDcyBrIRADcyBr]++;
                                }
                            }
                          nIRADcyBr[j]++;
                          break; 
                        }
                    }
                  vDcyBrCcIRADcyBr.clear();
                  // Here, "&&m_vCompICcIRADcyBr[k]!=0" in the following condition can not be removed. Besides, "if" here can not be replaced by "else if".
                  if(m_ccSwitch==true&&m_vCompICcIRADcyBr[j]!=0&&countIRADcyBr(vPid,vMidx,m_vCompCcIRADcyBr[j],false,&vDcyBrCcIRADcyBr)>0)
                    {
                      for(unsigned int k=0;k<vDcyBrCcIRADcyBr.size();k++)
                        {
                          dcyBrCcIRADcyBr=vDcyBrCcIRADcyBr[k];
                          int _iDcyBrIRADcyBr=-1; // If the variable is still equal to -1 after the following loop, then the decay branch of the intermediate-resonance-allowed decay branch is a new exclusive decay branch of the intermediate-resonance-allowed decay branch.
                          for(unsigned int l=0;l<m_vVDcyBrCcIRADcyBr[j].size();l++)
                            {
                              if(dcyBrCcIRADcyBr==m_vVDcyBrCcIRADcyBr[j][l])
                                {
                                  _iDcyBrIRADcyBr=l;
                                  break;
                                }
                            }
                          if(_iDcyBrIRADcyBr==-1)
                            {
                              _iDcyBrIRADcyBr=m_vVDcyBrIRADcyBr[j].size();
                              iDcyBrCcIRADcyBr[j][(unsigned int) (nCcIRADcyBr[j])]=_iDcyBrIRADcyBr;
                              m_vVDcyBrCcIRADcyBr[j].push_back(dcyBrCcIRADcyBr);
                              m_vVIDcyBrCcIRADcyBr[j].push_back(_iDcyBrIRADcyBr);
                              m_vVNDcyBrCcIRADcyBr[j].push_back(1);

                              dcyBrIRADcyBr.clear();
                              list<int> subDcyBrIRADcyBr;
                              list<int>::iterator liit;
                              for(unsigned int l=0;l<dcyBrCcIRADcyBr.size();l++)
                                {
                                  subDcyBrIRADcyBr.clear();
                                  liit=dcyBrCcIRADcyBr[l].begin();
                                  if(l==0&&(*liit)==-11) liit++;
                                  for(liit++;liit!=dcyBrCcIRADcyBr[l].end();liit++) subDcyBrIRADcyBr.push_back(getCcPid((*liit)));
                                  sortByPidAndPchrg(subDcyBrIRADcyBr);
                                  liit=dcyBrCcIRADcyBr[l].begin();
                                  if(l==0&&(*liit)==-11)
                                    {
                                      subDcyBrIRADcyBr.push_front(11);
                                      subDcyBrIRADcyBr.push_front(-11);
                                    }
                                  else
                                    {
                                      subDcyBrIRADcyBr.push_front(getCcPid((*liit))); // Here, (*liit) is not equal to getCcPid((*liit)).
                                    }
                                  dcyBrIRADcyBr.push_back(subDcyBrIRADcyBr);
                                }
                              m_vVDcyBrIRADcyBr[j].push_back(dcyBrIRADcyBr);
                              m_vVIDcyBrIRADcyBr[j].push_back(_iDcyBrIRADcyBr);
                              m_vVNDcyBrIRADcyBr[j].push_back(0);
                            }
                          else
                            {
                              iDcyBrCcIRADcyBr[j][(unsigned int) (nCcIRADcyBr[j])]=_iDcyBrIRADcyBr;
                              m_vVNDcyBrCcIRADcyBr[j][_iDcyBrIRADcyBr]++;
                            }
                          nCcIRADcyBr[j]++;
                          break;
                        }
                      if(m_ccSwitch==true&&m_vCompICcIRADcyBr[j]!=0) nTotIRADcyBr[j]=nIRADcyBr[j]+nCcIRADcyBr[j];
                    }             
                }               
            }

          if(m_vSigDcyTr.size()>0)
            {
              iSigDcyTr=-1;
              iSigDcyIFSts=-1;
              if(m_ccSwitch==true)
                {
                  iCcSigDcyTr=-9999;
                  iCcSigDcyIFSts=-9999;
                }
              for(unsigned int j=0;j<m_vSigDcyTr.size();j++)
                {
                  
                  if(dcyTr==m_vSigDcyTr[j])
                    {
                      iSigDcyTr=j;
                      strcpy(nmSigDcyTr,m_vNm_sigDcyTr[iSigDcyTr].c_str());
                      iSigDcyIFSts=m_iSigDcyTrISigDcyIFStsMap[iSigDcyTr]; 
                      if(m_anaTasksForSigIds=="TC") m_vNSigDcyTr[iSigDcyTr]++;
                      if(m_anaTasksForSigIds=="TC") m_vNSigDcyIFSts[iSigDcyIFSts]++;
                      if(m_ccSwitch==true)
                        {
                          if(m_vNSigDcyTr[iSigDcyTr]+m_vNCcSigDcyTr[iSigDcyTr]==1) m_iSigDcyTrIDcyTrMap[iSigDcyTr]=iDcyTr;
                          if(m_vNSigDcyIFSts[iSigDcyIFSts]+m_vNCcSigDcyIFSts[iSigDcyIFSts]==1) m_iSigDcyIFStsIDcyIFStsMap[iSigDcyIFSts]=iDcyIFSts;
                          iCcSigDcyTr=m_vICcSigDcyTr[j];
                          iCcSigDcyIFSts=m_iSigDcyTrICcSigDcyIFStsMap[iSigDcyTr];
                          if(m_vNSigDcyTr[iSigDcyTr]+m_vNCcSigDcyTr[iSigDcyTr]==1) m_iSigDcyTrICcDcyTrMap[iSigDcyTr]=iCcDcyTr;
                          if(m_vNSigDcyIFSts[iSigDcyIFSts]+m_vNCcSigDcyIFSts[iSigDcyIFSts]==1) m_iSigDcyIFStsICcDcyIFStsMap[iSigDcyIFSts]=iCcDcyIFSts;
                        }
                      else
                        {
                          if(m_vNSigDcyTr[iSigDcyTr]==1) m_iSigDcyTrIDcyTrMap[iSigDcyTr]=iDcyTr;
                          if(m_vNSigDcyIFSts[iSigDcyIFSts]==1) m_iSigDcyIFStsIDcyIFStsMap[iSigDcyIFSts]=iDcyIFSts;
                        }
                      break;
                    }
                  else if(m_ccSwitch==true&&m_vICcSigDcyTr[j]!=0&&dcyTr==m_vCcSigDcyTr[j])
                    {
                      iSigDcyTr=j;
                      strcpy(nmSigDcyTr,m_vNm_sigDcyTr[iSigDcyTr].c_str());
                      iSigDcyIFSts=m_iSigDcyTrISigDcyIFStsMap[iSigDcyTr];
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigDcyTr[iSigDcyTr]++;
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigDcyIFSts[iSigDcyIFSts]++;
                      if(m_vNSigDcyTr[iSigDcyTr]+m_vNCcSigDcyTr[iSigDcyTr]==1) m_iSigDcyTrIDcyTrMap[iSigDcyTr]=iDcyTr;
                      if(m_vNSigDcyIFSts[iSigDcyIFSts]+m_vNCcSigDcyIFSts[iSigDcyIFSts]==1) m_iSigDcyIFStsIDcyIFStsMap[iSigDcyIFSts]=iDcyIFSts;
                      iCcSigDcyTr=-1;
                      iCcSigDcyIFSts=-1*m_iSigDcyTrICcSigDcyIFStsMap[iSigDcyTr];
                      if(m_vNSigDcyTr[iSigDcyTr]+m_vNCcSigDcyTr[iSigDcyTr]==1) m_iSigDcyTrICcDcyTrMap[iSigDcyTr]=-1*iCcDcyTr;
                      if(m_vNSigDcyIFSts[iSigDcyIFSts]+m_vNCcSigDcyIFSts[iSigDcyIFSts]==1) m_iSigDcyIFStsICcDcyIFStsMap[iSigDcyIFSts]=-1*iCcDcyIFSts;
                      break;
                    }
                }
            }

          if(m_vSigDcyIFSts2.size()>0)
            {
              iSigDcyIFSts2=-1;
              iCcSigDcyIFSts2=-9999;
              for(unsigned int j=0;j<m_vSigDcyIFSts2.size();j++)
                {
                  if(dcyIFSts==m_vSigDcyIFSts2[j])
                    {
                      iSigDcyIFSts2=j;
                      strcpy(nmSigDcyIFSts2,m_vNm_sigDcyIFSts2[iSigDcyIFSts2].c_str());
                      if(m_anaTasksForSigIds=="TC") m_vNSigDcyIFSts2[iSigDcyIFSts2]++;
                      if(m_ccSwitch==true)
                        {
                          if(m_vNSigDcyIFSts2[iSigDcyIFSts2]+m_vNCcSigDcyIFSts2[iSigDcyIFSts2]==1) m_iSigDcyIFSts2IDcyIFStsMap[iSigDcyIFSts2]=iDcyIFSts;
                          iCcSigDcyIFSts2=m_vICcSigDcyIFSts2[iSigDcyIFSts2];
                          if(m_vNSigDcyIFSts2[j]+m_vNCcSigDcyIFSts2[j]==1) m_iSigDcyIFSts2ICcDcyIFStsMap[iSigDcyIFSts2]=iCcDcyIFSts;
                        }
                      else
                        {
                          if(m_vNSigDcyIFSts2[iSigDcyIFSts2]==1) m_iSigDcyIFSts2IDcyIFStsMap[iSigDcyIFSts2]=iDcyIFSts;
                        }
                      break;
                    }
                  else if(m_ccSwitch==true&&m_vICcSigDcyIFSts2[j]!=0&&dcyIFSts==m_vCcSigDcyIFSts2[j])
                    {
                      iSigDcyIFSts2=j;
                      strcpy(nmSigDcyIFSts2,m_vNm_sigDcyIFSts2[iSigDcyIFSts2].c_str());
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigDcyIFSts2[iSigDcyIFSts2]++;
                      if(m_vNSigDcyIFSts2[iSigDcyIFSts2]+m_vNCcSigDcyIFSts2[iSigDcyIFSts2]==1) m_iSigDcyIFSts2IDcyIFStsMap[iSigDcyIFSts2]=iDcyIFSts;
                      iCcSigDcyIFSts2=-1*m_vICcSigDcyIFSts2[iSigDcyIFSts2];
                      if(m_vNSigDcyIFSts2[j]+m_vNCcSigDcyIFSts2[j]==1) m_iSigDcyIFSts2ICcDcyIFStsMap[iSigDcyIFSts2]=-1*iCcDcyIFSts;
                      break;                 
                    }
                }
            }

          if(m_vPid_sigP.size()>0)
            {
              for(unsigned int j=0;j<m_vPid_sigP.size();j++)
                {
                  nSigP[j]=0;
                  nCcSigP[j]=0;
                }
              for(unsigned int j=0;j<vPid.size();j++)
                {
                  for(unsigned int k=0;k<m_vPid_sigP.size();k++)
                    {
                      if(vPid[j]==m_vPid_sigP[k])
                        {
                          if(m_anaTasksForSigIds=="TC") m_vNSigP[k]++;
                          nSigP[k]++;
                          break;
                        }
                      else if(m_ccSwitch==true&&m_vICcSigP[k]!=0&&vPid[j]==m_vPid_ccSigP[k])
                        {
                          if(m_anaTasksForSigIds=="TC") m_vNCcSigP[k]++;
                          nCcSigP[k]++;
                          break;
                        }
                    }
                }
              if(m_ccSwitch==true) for(unsigned int j=0;j<m_vPid_sigP.size();j++) nTotSigP[j]=nSigP[j]+nCcSigP[j];
            }

          if(m_vSigDcyBr.size()>0)
            {
              for(unsigned int j=0;j<m_vSigDcyBr.size();j++)
                {
                  nSigDcyBr[j]=0;
                  for(unsigned int k=0;k<dcyTr.size();k++) if(dcyTr[k]==m_vSigDcyBr[j]) nSigDcyBr[j]++;
                  if(m_anaTasksForSigIds=="TC") m_vNSigDcyBr[j]=m_vNSigDcyBr[j]+nSigDcyBr[j];
                  if(m_ccSwitch==true)
                    {
                      nCcSigDcyBr[j]=0;
                      for(unsigned int k=0;k<dcyTr.size();k++) if(dcyTr[k]==m_vCcSigDcyBr[j]) nCcSigDcyBr[j]++;
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigDcyBr[j]=m_vNCcSigDcyBr[j]+nCcSigDcyBr[j];
                      nTotSigDcyBr[j]=nSigDcyBr[j]+nCcSigDcyBr[j];
                    }
                }
            }

          if(m_vSigIncDcyBr.size()>0)
            {
              for(unsigned int j=0;j<m_vSigIncDcyBr.size();j++)
                {
                  nSigIncDcyBr[j]=countIncLiaInVlib(m_vSigIncDcyBr[j],dcyTr);
                  if(m_anaTasksForSigIds=="TC") m_vNSigIncDcyBr[j]=m_vNSigIncDcyBr[j]+nSigIncDcyBr[j];
                  if(m_ccSwitch==true)
                    {
                      nCcSigIncDcyBr[j]=countIncLiaInVlib(m_vCcSigIncDcyBr[j],dcyTr);
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigIncDcyBr[j]=m_vNCcSigIncDcyBr[j]+nCcSigIncDcyBr[j];
                      nTotSigIncDcyBr[j]=nSigIncDcyBr[j]+nCcSigIncDcyBr[j];
                    }
                }
            }

          if(m_vSigCascDcyBrs.size()>0)
            {
              for(unsigned int j=0;j<m_vSigCascDcyBrs.size();j++)
                {
                  nSigCascDcyBrs[j]=countCascDcyBrsInDcyTr(m_vSigCascDcyBrs[j],m_vVSigCascDcyBrsIdxOfHead[j],m_vVSigCascDcyBrsMidxOfHead[j],dcyTr,vIdxOfHead,vMidxOfHead);
                  if(m_anaTasksForSigIds=="TC") m_vNSigCascDcyBrs[j]=m_vNSigCascDcyBrs[j]+nSigCascDcyBrs[j];
                  if(m_ccSwitch==true)
                    {
                      nCcSigCascDcyBrs[j]=countCascDcyBrsInDcyTr(m_vCcSigCascDcyBrs[j],m_vVCcSigCascDcyBrsIdxOfHead[j],m_vVCcSigCascDcyBrsMidxOfHead[j],dcyTr,vIdxOfHead,vMidxOfHead);
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigCascDcyBrs[j]=m_vNCcSigCascDcyBrs[j]+nCcSigCascDcyBrs[j];
                      nTotSigCascDcyBrs[j]=nSigCascDcyBrs[j]+nCcSigCascDcyBrs[j];
                    }
                }
            }

          if(m_vSigIncCascDcyBrs.size()>0)
            {
              for(unsigned int j=0;j<m_vSigIncCascDcyBrs.size();j++)
                {
                  nSigIncCascDcyBrs[j]=countIncCascDcyBrsInDcyTr(m_vVIIncSigIncCascDcyBrs[j],m_vSigIncCascDcyBrs[j],m_vVSigIncCascDcyBrsIdxOfHead[j],m_vVSigIncCascDcyBrsMidxOfHead[j],dcyTr,vIdxOfHead,vMidxOfHead);
                  if(m_anaTasksForSigIds=="TC") m_vNSigIncCascDcyBrs[j]=m_vNSigIncCascDcyBrs[j]+nSigIncCascDcyBrs[j];
                  if(m_ccSwitch==true)
                    {
                      nCcSigIncCascDcyBrs[j]=countIncCascDcyBrsInDcyTr(m_vVIIncSigIncCascDcyBrs[j],m_vCcSigIncCascDcyBrs[j],m_vVCcSigIncCascDcyBrsIdxOfHead[j],m_vVCcSigIncCascDcyBrsMidxOfHead[j],dcyTr,vIdxOfHead,vMidxOfHead);
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigIncCascDcyBrs[j]=m_vNCcSigIncCascDcyBrs[j]+nCcSigIncCascDcyBrs[j];
                      nTotSigIncCascDcyBrs[j]=nSigIncCascDcyBrs[j]+nCcSigIncCascDcyBrs[j];
                    }
                }
            }

          if(m_vSigIRADcyBr.size()>0)
            {
              for(unsigned int j=0;j<m_vSigIRADcyBr.size();j++)
                {
                  nSigIRADcyBr[j]=countIRADcyBr(vPid,vMidx,m_vSigIRADcyBr[j]);
                  if(m_anaTasksForSigIds=="TC") m_vNSigIRADcyBr[j]=m_vNSigIRADcyBr[j]+nSigIRADcyBr[j];
                  if(m_ccSwitch==true)
                    {
                      nCcSigIRADcyBr[j]=countIRADcyBr(vPid,vMidx,m_vCcSigIRADcyBr[j]);
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigIRADcyBr[j]=m_vNCcSigIRADcyBr[j]+nCcSigIRADcyBr[j];
                      nTotSigIRADcyBr[j]=nSigIRADcyBr[j]+nCcSigIRADcyBr[j];
                    }
                }
            }

          if(m_vSigIncOrIRACascDcyBrs.size()>0)
            {
              for(unsigned int j=0;j<m_vSigIncOrIRACascDcyBrs.size();j++)
                {
                  nSigIncOrIRACascDcyBrs[j]=countIncOrIRACascDcyBrsInDcyTr(m_vVIIncSigIncOrIRACascDcyBrs[j],m_vVIIRASigIncOrIRACascDcyBrs[j],m_vSigIncOrIRACascDcyBrs[j],m_vVSigIncOrIRACascDcyBrsIdxOfHead[j],m_vVSigIncOrIRACascDcyBrsMidxOfHead[j],dcyTr,vIdxOfHead,vMidxOfHead,vPid,vMidx);
                  if(m_anaTasksForSigIds=="TC") m_vNSigIncOrIRACascDcyBrs[j]=m_vNSigIncOrIRACascDcyBrs[j]+nSigIncOrIRACascDcyBrs[j];
                  if(m_ccSwitch==true)
                    {
                      nCcSigIncOrIRACascDcyBrs[j]=countIncOrIRACascDcyBrsInDcyTr(m_vVIIncSigIncOrIRACascDcyBrs[j],m_vVIIRASigIncOrIRACascDcyBrs[j],m_vCcSigIncOrIRACascDcyBrs[j],m_vVCcSigIncOrIRACascDcyBrsIdxOfHead[j],m_vVCcSigIncOrIRACascDcyBrsMidxOfHead[j],dcyTr,vIdxOfHead,vMidxOfHead,vPid,vMidx);
                      if(m_anaTasksForSigIds=="TC") m_vNCcSigIncOrIRACascDcyBrs[j]=m_vNCcSigIncOrIRACascDcyBrs[j]+nCcSigIncOrIRACascDcyBrs[j];
                      nTotSigIncOrIRACascDcyBrs[j]=nSigIncOrIRACascDcyBrs[j]+nCcSigIncOrIRACascDcyBrs[j];
                    }
                }
            }

          tr->Fill();

          if((i+1>=nEtrsForTiming)&&(((i+1)%nEtrsForTiming==0)||((i+1)==nEtrsToBePrcsd)))
            {
              if((i+1)==nEtrsForTiming) cout<<"Number of entries processed\tNumber of seconds elapsed"<<endl<<endl;
              cout<<setiosflags(ios::right)<<setw(14)<<i+1<<"\t\t\t"<<setiosflags(ios::fixed)<<setprecision(2)<<setw(14)<<(clock()-starttime)/((double) CLOCKS_PER_SEC)<<resetiosflags(ios::adjustfield)<<endl;
              if((i+1)==nEtrsToBePrcsd) cout<<endl;
            }

          if(m_oneOptRootFlByOneIptRootFl==true)
            {
              closeTheOptRootFl1=((i+1)==vNEtrs[iOptRootFls]);
              closeTheOptRootFl2=false;
            }
          else
            {
              closeTheOptRootFl1=((m_nEtrsMaxInASngOptRootFl==ULONG_MAX)&&(((unsigned long) tr->GetTotBytes())>nTotBytesMaxOfASngOptRootFl));
              closeTheOptRootFl2=((m_nEtrsMaxInASngOptRootFl!=ULONG_MAX)&&((i+1)%m_nEtrsMaxInASngOptRootFl==0));
            }
          closeTheOptRootFl3=((i+1)==nEtrsToBePrcsd);
          if(closeTheOptRootFl1||closeTheOptRootFl2||closeTheOptRootFl3)
            {
              fl->Write();
              delete tr; // Pay attention to that replacing the "delete tr" by "tr->Delete()" will result in a problem of "*** Break *** segmentation violation".
              fl->Close();
              delete fl;
              if(m_cpIptBrs==false) rmIptBrs(NmOfOptRootFl);
              if(m_useArrayBrsOpt==false) flatArrayBrs(NmOfOptRootFl);
              openANewOptRootFl=true;
              iOptRootFls++;
            }
        }
      if(!m_cut.empty()) cout<<"Note that only "<<nEtrsThroughTheCut<<" entries passed the cut."<<endl<<endl;
    }

  if(m_compAnaOfDcyTrs==true)
    {
      if(m_ccSwitch==true)
        {
          sortBySumOf1stAnd2ndFromLrgToSml(m_vNDcyTr,m_vNCcDcyTr,m_vDcyTr,m_vCcDcyTr,m_vIDcyTr,m_vICcDcyTr);
          sortBySumOf1stAnd2ndFromLrgToSml(m_vNDcyIFSts,m_vNCcDcyIFSts,m_vDcyIFSts,m_vCcDcyIFSts,m_vIDcyIFSts,m_vICcDcyIFSts);
        }
      else
        {
          sortBy1stFromLrgToSml(m_vNDcyTr,m_vDcyTr,m_vIDcyTr);
          sortBy1stFromLrgToSml(m_vNDcyIFSts,m_vDcyIFSts,m_vIDcyIFSts);
        }
    }
  else if(m_compAnaOfDcyIFSts==true)
    {
      if(m_ccSwitch==true)
        {
          sortBySumOf1stAnd2ndFromLrgToSml(m_vNDcyIFSts,m_vNCcDcyIFSts,m_vDcyIFSts,m_vCcDcyIFSts,m_vIDcyIFSts,m_vICcDcyIFSts);
        }
      else
        {
          sortBy1stFromLrgToSml(m_vNDcyIFSts,m_vDcyIFSts,m_vIDcyIFSts);
        }
    }

  if(m_vPid_compP.size()>0)
    {
      for(unsigned int i=0;i<m_vPid_compP.size();i++)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vVNDcyBrP[i],m_vVNDcyBrCcP[i],m_vVDcyBrP[i],m_vVDcyBrCcP[i],m_vVIDcyBrP[i],m_vVIDcyBrCcP[i]);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vVNDcyBrP[i],m_vVDcyBrP[i],m_vVIDcyBrP[i]);
            }
        }      
    }

  if(m_vCompIncDcyBr.size()>0)
    {
      for(unsigned int i=0;i<m_vCompIncDcyBr.size();i++)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vVNDcyBrIncDcyBr[i],m_vVNDcyBrCcIncDcyBr[i],m_vVDcyBrIncDcyBr[i],m_vVDcyBrCcIncDcyBr[i],m_vVIDcyBrIncDcyBr[i],m_vVIDcyBrCcIncDcyBr[i]);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vVNDcyBrIncDcyBr[i],m_vVDcyBrIncDcyBr[i],m_vVIDcyBrIncDcyBr[i]);
            }
        }
    }

  if(m_vCompIRADcyBr.size()>0)
    {
      for(unsigned int i=0;i<m_vCompIRADcyBr.size();i++)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vVNDcyBrIRADcyBr[i],m_vVNDcyBrCcIRADcyBr[i],m_vVDcyBrIRADcyBr[i],m_vVDcyBrCcIRADcyBr[i],m_vVIDcyBrIRADcyBr[i],m_vVIDcyBrCcIRADcyBr[i]);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vVNDcyBrIRADcyBr[i],m_vVDcyBrIRADcyBr[i],m_vVIDcyBrIRADcyBr[i]);
            }
        }
    }

  if(m_vSigDcyTr.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_anaTasksForSigIds=="C")
        {
          char cut[50];
          for(unsigned int i=0;i<m_vSigDcyTr.size();i++)
            {
              if(m_ccSwitch==true)
                {
                  if(m_vICcSigDcyTr[i]==1)
                    {
                      sprintf(cut, "iSigDcyTr==%d&&iCcSigDcyTr==1", m_vISigDcyTr[i]);
                      m_vNSigDcyTr[i]=chn->GetEntries(cut);
                      sprintf(cut, "iSigDcyTr==%d&&iCcSigDcyTr==-1", m_vISigDcyTr[i]);
                      m_vNCcSigDcyTr[i]=chn->GetEntries(cut);
                    }
                  else
                    {
                      sprintf(cut, "iSigDcyTr==%d&&iCcSigDcyTr==0", m_vISigDcyTr[i]);
                      m_vNSigDcyTr[i]=chn->GetEntries(cut);
                      m_vNCcSigDcyTr[i]=0;
                    }
                }
              else
                {
                  sprintf(cut, "iSigDcyTr==%d", m_vISigDcyTr[i]);
                  m_vNSigDcyTr[i]=chn->GetEntries(cut);
                }
            }

          for(unsigned int i=0;i<m_vSigDcyIFSts.size();i++)
            {
              if(m_ccSwitch==true)
                {
                  if(m_vICcSigDcyIFSts[i]==1)
                    {
                      sprintf(cut, "iSigDcyIFSts==%d&&iCcSigDcyIFSts==1", m_vISigDcyIFSts[i]);
                      m_vNSigDcyIFSts[i]=chn->GetEntries(cut);
                      sprintf(cut, "iSigDcyIFSts==%d&&iCcSigDcyIFSts==-1", m_vISigDcyIFSts[i]);
                      m_vNCcSigDcyIFSts[i]=chn->GetEntries(cut);
                    }
                  else
                    {
                      sprintf(cut, "iSigDcyIFSts==%d&&iCcSigDcyIFSts==0", m_vISigDcyIFSts[i]);
                      m_vNSigDcyIFSts[i]=chn->GetEntries(cut);
                      m_vNCcSigDcyIFSts[i]=0;
                    }
                }
              else
                {
                  sprintf(cut, "iSigDcyIFSts==%d", m_vISigDcyIFSts[i]);
                  m_vNSigDcyIFSts[i]=chn->GetEntries(cut);
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigDcyTr,m_vNCcSigDcyTr,m_vSigDcyTr,m_vCcSigDcyTr,m_vISigDcyTr,m_vICcSigDcyTr);
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigDcyIFSts,m_vNCcSigDcyIFSts,m_vSigDcyIFSts,m_vCcSigDcyIFSts,m_vISigDcyIFSts,m_vICcSigDcyIFSts);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigDcyTr,m_vSigDcyTr,m_vISigDcyTr);
              sortBy1stFromLrgToSml(m_vNSigDcyIFSts,m_vSigDcyIFSts,m_vISigDcyIFSts);
            }
        }
    }

  if(m_vSigDcyIFSts2.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_anaTasksForSigIds=="C")
        {
          char cut[50];
          for(unsigned int i=0;i<m_vSigDcyIFSts2.size();i++)
            {
              if(m_ccSwitch==true)
                {
                  if(m_vICcSigDcyIFSts2[i]==1)
                    {
                      sprintf(cut, "iSigDcyIFSts2==%d&&iCcSigDcyIFSts2==1", m_vISigDcyIFSts2[i]);
                      m_vNSigDcyIFSts2[i]=chn->GetEntries(cut);
                      sprintf(cut, "iSigDcyIFSts2==%d&&iCcSigDcyIFSts2==-1", m_vISigDcyIFSts2[i]);
                      m_vNCcSigDcyIFSts2[i]=chn->GetEntries(cut);
                    }
                  else
                    {
                      sprintf(cut, "iSigDcyIFSts2==%d&&iCcSigDcyIFSts2==0", m_vISigDcyIFSts2[i]);
                      m_vNSigDcyIFSts2[i]=chn->GetEntries(cut);
                      m_vNCcSigDcyIFSts2[i]=0;
                    }
                }
              else
                {
                  sprintf(cut, "iSigDcyIFSts2==%d", m_vISigDcyIFSts2[i]);
                  m_vNSigDcyIFSts2[i]=chn->GetEntries(cut);
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigDcyIFSts2,m_vNCcSigDcyIFSts2,m_vSigDcyIFSts2,m_vCcSigDcyIFSts2,m_vISigDcyIFSts2,m_vICcSigDcyIFSts2);
            }
          else
            {      
              sortBy1stFromLrgToSml(m_vNSigDcyIFSts2,m_vSigDcyIFSts2,m_vISigDcyIFSts2);
            }
        }
    }

  if(m_vPid_sigP.size()>0&&m_anaTasksForSigIds!="T")
    {  
      if(m_anaTasksForSigIds=="C")
        {
          if(m_useArrayBrsOpt==true)
            {
              chn->SetBranchAddress("nSigP", &nSigP);
              if(m_ccSwitch==true) chn->SetBranchAddress("nCcSigP", &nCcSigP);
            }
          else
            {
              char specifier[30];
              for(unsigned int i=0;i<m_vPid_sigP.size();i++)
                {
                  sprintf(specifier, "nSigP%d", i);
                  chn->SetBranchAddress(specifier, &nSigP[i]);
                  if(m_ccSwitch==true)
                    {
                      sprintf(specifier, "nCcSigP%d", i);
                      chn->SetBranchAddress(specifier, &nCcSigP[i]);
                    }
                }
            }
          for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
            {
              chn->GetEntry(i);
              for(unsigned int j=0;j<m_vPid_sigP.size();j++)
                {
                  m_vNSigP[j]=m_vNSigP[j]+nSigP[j];
                  if(m_ccSwitch==true) m_vNCcSigP[j]=m_vNCcSigP[j]+nCcSigP[j];
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigP,m_vNCcSigP,m_vPid_sigP,m_vPid_ccSigP,m_vISigP,m_vICcSigP);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigP,m_vPid_sigP,m_vISigP);
            }
        }
    }

  if(m_vSigDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    { 
      if(m_anaTasksForSigIds=="C")
        { 
          if(m_useArrayBrsOpt==true)
            { 
              chn->SetBranchAddress("nSigDcyBr", &nSigDcyBr);
              if(m_ccSwitch==true) chn->SetBranchAddress("nCcSigDcyBr", &nCcSigDcyBr);
            }
          else
            { 
              char specifier[30];
              for(unsigned int i=0;i<m_vSigDcyBr.size();i++)
                { 
                  sprintf(specifier, "nSigDcyBr%d", i);
                  chn->SetBranchAddress(specifier, &nSigDcyBr[i]);
                  if(m_ccSwitch==true)
                    { 
                      sprintf(specifier, "nCcSigDcyBr%d", i);
                      chn->SetBranchAddress(specifier, &nCcSigDcyBr[i]);
                    }
                }
            }
          for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
            { 
              chn->GetEntry(i);
              for(unsigned int j=0;j<m_vSigDcyBr.size();j++)
                { 
                  m_vNSigDcyBr[j]=m_vNSigDcyBr[j]+nSigDcyBr[j];
                  if(m_ccSwitch==true) m_vNCcSigDcyBr[j]=m_vNCcSigDcyBr[j]+nCcSigDcyBr[j];
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigDcyBr,m_vNCcSigDcyBr,m_vSigDcyBr,m_vCcSigDcyBr,m_vISigDcyBr,m_vICcSigDcyBr);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigDcyBr,m_vSigDcyBr,m_vISigDcyBr);
            }
        }
    }

  if(m_vSigIncDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    { 
      if(m_anaTasksForSigIds=="C")
        { 
          if(m_useArrayBrsOpt==true)
            { 
              chn->SetBranchAddress("nSigIncDcyBr", &nSigIncDcyBr);
              if(m_ccSwitch==true) chn->SetBranchAddress("nCcSigIncDcyBr", &nCcSigIncDcyBr);
            }
          else
            { 
              char specifier[30];
              for(unsigned int i=0;i<m_vSigIncDcyBr.size();i++)
                { 
                  sprintf(specifier, "nSigIncDcyBr%d", i);
                  chn->SetBranchAddress(specifier, &nSigIncDcyBr[i]);
                  if(m_ccSwitch==true)
                    { 
                      sprintf(specifier, "nCcSigIncDcyBr%d", i);
                      chn->SetBranchAddress(specifier, &nCcSigIncDcyBr[i]);
                    }
                }
            }
          for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
            { 
              chn->GetEntry(i);
              for(unsigned int j=0;j<m_vSigIncDcyBr.size();j++)
                { 
                  m_vNSigIncDcyBr[j]=m_vNSigIncDcyBr[j]+nSigIncDcyBr[j];
                  if(m_ccSwitch==true) m_vNCcSigIncDcyBr[j]=m_vNCcSigIncDcyBr[j]+nCcSigIncDcyBr[j];
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigIncDcyBr,m_vNCcSigIncDcyBr,m_vSigIncDcyBr,m_vCcSigIncDcyBr,m_vISigIncDcyBr,m_vICcSigIncDcyBr);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigIncDcyBr,m_vSigIncDcyBr,m_vISigIncDcyBr);
            }
        }
    }

  if(m_vSigCascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_anaTasksForSigIds=="C")
        {
          if(m_useArrayBrsOpt==true)
            {
              chn->SetBranchAddress("nSigCascDcyBrs", &nSigCascDcyBrs);
              if(m_ccSwitch==true) chn->SetBranchAddress("nCcSigCascDcyBrs", &nCcSigCascDcyBrs);
            }
          else
            {
              char specifier[30];
              for(unsigned int i=0;i<m_vSigCascDcyBrs.size();i++)
                {
                  sprintf(specifier, "nSigCascDcyBrs%d", i);
                  chn->SetBranchAddress(specifier, &nSigCascDcyBrs[i]);
                  if(m_ccSwitch==true)
                    {
                      sprintf(specifier, "nCcSigCascDcyBrs%d", i);
                      chn->SetBranchAddress(specifier, &nCcSigCascDcyBrs[i]);
                    }
                }
            }
          for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
            {
              chn->GetEntry(i);
              for(unsigned int j=0;j<m_vSigCascDcyBrs.size();j++)
                {
                  m_vNSigCascDcyBrs[j]=m_vNSigCascDcyBrs[j]+nSigCascDcyBrs[j];
                  if(m_ccSwitch==true) m_vNCcSigCascDcyBrs[j]=m_vNCcSigCascDcyBrs[j]+nCcSigCascDcyBrs[j];
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigCascDcyBrs,m_vNCcSigCascDcyBrs,m_vSigCascDcyBrs,m_vCcSigCascDcyBrs,m_vISigCascDcyBrs,m_vICcSigCascDcyBrs,m_vVSigCascDcyBrsIdxOfHead,m_vVCcSigCascDcyBrsIdxOfHead,m_vVSigCascDcyBrsMidxOfHead,m_vVCcSigCascDcyBrsMidxOfHead);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigCascDcyBrs,m_vSigCascDcyBrs,m_vISigCascDcyBrs,m_vVSigCascDcyBrsIdxOfHead,m_vVSigCascDcyBrsMidxOfHead);
            }
        }
    }

  if(m_vSigIncCascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_anaTasksForSigIds=="C")
        {
          if(m_useArrayBrsOpt==true)
            {
              chn->SetBranchAddress("nSigIncCascDcyBrs", &nSigIncCascDcyBrs);
              if(m_ccSwitch==true) chn->SetBranchAddress("nCcSigIncCascDcyBrs", &nCcSigIncCascDcyBrs);
            }
          else
            {
              char specifier[30];
              for(unsigned int i=0;i<m_vSigIncCascDcyBrs.size();i++)
                {
                  sprintf(specifier, "nSigIncCascDcyBrs%d", i);
                  chn->SetBranchAddress(specifier, &nSigIncCascDcyBrs[i]);
                  if(m_ccSwitch==true)
                    {
                      sprintf(specifier, "nCcSigIncCascDcyBrs%d", i);
                      chn->SetBranchAddress(specifier, &nCcSigIncCascDcyBrs[i]);
                    }
                }
            }
          for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
            {
              chn->GetEntry(i);
              for(unsigned int j=0;j<m_vSigIncCascDcyBrs.size();j++)
                {
                  m_vNSigIncCascDcyBrs[j]=m_vNSigIncCascDcyBrs[j]+nSigIncCascDcyBrs[j];
                  if(m_ccSwitch==true) m_vNCcSigIncCascDcyBrs[j]=m_vNCcSigIncCascDcyBrs[j]+nCcSigIncCascDcyBrs[j];
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigIncCascDcyBrs,m_vNCcSigIncCascDcyBrs,m_vSigIncCascDcyBrs,m_vCcSigIncCascDcyBrs,m_vISigIncCascDcyBrs,m_vICcSigIncCascDcyBrs,m_vVSigIncCascDcyBrsIdxOfHead,m_vVCcSigIncCascDcyBrsIdxOfHead,m_vVSigIncCascDcyBrsMidxOfHead,m_vVCcSigIncCascDcyBrsMidxOfHead);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigIncCascDcyBrs,m_vSigIncCascDcyBrs,m_vISigIncCascDcyBrs,m_vVSigIncCascDcyBrsIdxOfHead,m_vVSigIncCascDcyBrsMidxOfHead);
            }
        }
    }

  if(m_vSigIRADcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_anaTasksForSigIds=="C")
        {
          if(m_useArrayBrsOpt==true)
            {
              chn->SetBranchAddress("nSigIRADcyBr", &nSigIRADcyBr);
              if(m_ccSwitch==true) chn->SetBranchAddress("nCcSigIRADcyBr", &nCcSigIRADcyBr);
            }
          else
            {
              char specifier[30];
              for(unsigned int i=0;i<m_vSigIRADcyBr.size();i++)
                {
                  sprintf(specifier, "nSigIRADcyBr%d", i);
                  chn->SetBranchAddress(specifier, &nSigIRADcyBr[i]);
                  if(m_ccSwitch==true)
                    {
                      sprintf(specifier, "nCcSigIRADcyBr%d", i);
                      chn->SetBranchAddress(specifier, &nCcSigIRADcyBr[i]);
                    }
                }
            }
          for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
            {
              chn->GetEntry(i);
              for(unsigned int j=0;j<m_vSigIRADcyBr.size();j++)
                {
                  m_vNSigIRADcyBr[j]=m_vNSigIRADcyBr[j]+nSigIRADcyBr[j];
                  if(m_ccSwitch==true) m_vNCcSigIRADcyBr[j]=m_vNCcSigIRADcyBr[j]+nCcSigIRADcyBr[j];
                }
            }
        }

      if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigIRADcyBr,m_vNCcSigIRADcyBr,m_vSigIRADcyBr,m_vCcSigIRADcyBr,m_vISigIRADcyBr,m_vICcSigIRADcyBr);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigIRADcyBr,m_vSigIRADcyBr,m_vISigIRADcyBr);
            }
        }
    }

  if(m_vSigIncOrIRACascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_anaTasksForSigIds=="C")
        {
          if(m_useArrayBrsOpt==true)
            {
              chn->SetBranchAddress("nSigIncOrIRACascDcyBrs", &nSigIncOrIRACascDcyBrs);
              if(m_ccSwitch==true) chn->SetBranchAddress("nCcSigIncOrIRACascDcyBrs", &nCcSigIncOrIRACascDcyBrs);
            }
          else
            {
              char specifier[30];
              for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBrs.size();i++)
                {
                  sprintf(specifier, "nSigIncOrIRACascDcyBrs%d", i);
                  chn->SetBranchAddress(specifier, &nSigIncOrIRACascDcyBrs[i]);
                  if(m_ccSwitch==true)
                    {
                      sprintf(specifier, "nCcSigIncOrIRACascDcyBrs%d", i);
                      chn->SetBranchAddress(specifier, &nCcSigIncOrIRACascDcyBrs[i]);
                    }
                }
            }
          for(unsigned int i=0;i<nEtrsToBePrcsd;i++)
            {
              chn->GetEntry(i);
              for(unsigned int j=0;j<m_vSigIncOrIRACascDcyBrs.size();j++)
                {
                  m_vNSigIncOrIRACascDcyBrs[j]=m_vNSigIncOrIRACascDcyBrs[j]+nSigIncOrIRACascDcyBrs[j];
                  if(m_ccSwitch==true) m_vNCcSigIncOrIRACascDcyBrs[j]=m_vNCcSigIncOrIRACascDcyBrs[j]+nCcSigIncOrIRACascDcyBrs[j];
                }
            }
        }

      /*if(m_sortTheToposForSigIds==true)
        {
          if(m_ccSwitch==true)
            {
              sortBySumOf1stAnd2ndFromLrgToSml(m_vNSigIncOrIRACascDcyBrs,m_vNCcSigIncOrIRACascDcyBrs,m_vSigIncOrIRACascDcyBrs,m_vCcSigIncOrIRACascDcyBrs,m_vVIIncSigIncOrIRACascDcyBrs,m_vVICcIncSigIncOrIRACascDcyBrs,m_vVIIRASigIncOrIRACascDcyBrs,m_vVICcIRASigIncOrIRACascDcyBrs,m_vVSigIncOrIRACascDcyBrsIdxOfHead,m_vVCcSigIncOrIRACascDcyBrsIdxOfHead,m_vVSigIncOrIRACascDcyBrsMidxOfHead,m_vVCcSigIncOrIRACascDcyBrsMidxOfHead);
            }
          else
            {
              sortBy1stFromLrgToSml(m_vNSigIncOrIRACascDcyBrs,m_vSigIncOrIRACascDcyBrs,m_vVIIncSigIncOrIRACascDcyBrs,m_vVIIRASigIncOrIRACascDcyBrs,m_vVSigIncOrIRACascDcyBrsIdxOfHead,m_vVSigIncOrIRACascDcyBrsMidxOfHead);
            }
        }*/
    }

  delete chn; // This statement is indispensable, or a tough problem will arise before the "return 0;" statement in the main function.

  for(unsigned int j=0;j<Nasterisks;j++) cout<<"*";
  cout<<endl<<endl;
}
