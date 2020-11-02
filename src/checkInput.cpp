#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "TChain.h"
#include "TChainElement.h"
#include <unistd.h>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <sstream>

void topoana::checkInput()
{
  cout<<"The parameters set in the card file are as follows:"<<endl<<endl;

  if(m_nmsOfIptRootFls.size()==0)
    {
      cerr<<"Error: The names of input root files do not exist!"<<endl;
      exit(-1);
    }
  else
    {
      cout<<"Names of input root files:"<<endl<<endl;
      for(unsigned int i=0;i<m_nmsOfIptRootFls.size();i++)
        {
          cout<<"  "<<m_nmsOfIptRootFls[i]<<endl;
        }
      cout<<endl;

      bool hasWildcards=false;
      TString * nmOfIptRootFl;
      for(unsigned int i=0;i<m_nmsOfIptRootFls.size();i++)
        {

          // nmOfIptRootFl=new TString(m_nmsOfIptRootFls[i]); // This statement is changed to the following one according to the experience from Tianyu Qi to prevent the possible compiling failure with more advanced version of g++.
          nmOfIptRootFl=new TString(m_nmsOfIptRootFls[i].c_str());
          if(nmOfIptRootFl->MaybeWildcard())
            {
              hasWildcards=true;
              delete nmOfIptRootFl;
              break;
            }
          else
            {
              delete nmOfIptRootFl;
            }
        }
      if(hasWildcards==true)
        {
          cout<<"With the wildcards parsed:"<<endl<<endl;
          TChain * chn=new TChain(m_ttrNm.c_str());
          for(unsigned int i=0;i<m_nmsOfIptRootFls.size();i++)
            {
              chn->Add(m_nmsOfIptRootFls[i].c_str());
            }
          TObjArray * objArray=chn->GetListOfFiles();
          TIter next(objArray);
          TChainElement * chnElmt=0;
          unsigned int nCFls=0;
          string nmOfOptRootFl;
          vector<string> nmsOfIptRootFls;
          nmsOfIptRootFls.clear();
          while((chnElmt=(TChainElement *) next()))
            {
              cout<<"  "<<chnElmt->GetTitle()<<endl;
              nCFls++;
              if(m_oneOptRootFlByOneIptRootFl==true)
                {
                  nmOfOptRootFl=chnElmt->GetTitle();
                  size_t pos=nmOfOptRootFl.rfind(".root");
                  if(pos!=string::npos)
                    {
                      nmOfOptRootFl.replace(pos,5,"_ta.root");
                      if(access(nmOfOptRootFl.c_str(),0)==0)
                        {
                          cerr<<"Error: The output root file \""<<nmOfOptRootFl<<"\" already exists!"<<endl;
                          cerr<<"Infor: The program does not overwrite it by default."<<endl;
                          cerr<<"Infor: Please move or remove it if you want to ouput a new root file with the same name."<<endl;
                          exit(-1);
                        }
                    }
                  else
                    {
                      cerr<<"Error: The output root file name is identical to the input root file name!"<<endl;
                      cerr<<"Infor: There is no \".root\" found in the input root file name \""<<chnElmt->GetTitle()<<"\"."<<endl;
                      cerr<<"Infor: Please rename the input root file with the suffix \".root\"."<<endl;
                      exit(-1);
                    }
                  nmsOfIptRootFls.push_back(chnElmt->GetTitle());
                }
            }
          if(nCFls>0)
            {
              cout<<endl<<"In total, "<<nCFls<<" files match the names listed above."<<endl<<endl;
              if(m_oneOptRootFlByOneIptRootFl==true) m_nmsOfIptRootFls=nmsOfIptRootFls;
            }
          else
            {
              cerr<<"Error: No valid input root files match the names listed above!"<<endl;
              exit(-1);
            }
        }
    }

  if(m_ttrNm.empty())
    {
      cerr<<"Error: The TTree name is empty!"<<endl;
      exit(-1);
    }
  else
    {
      cout<<"TTree name: "<<m_ttrNm<<endl<<endl;
    }

  if(m_othTtrNms.size()==0)
    {
      if(m_vbsLevStdOut==true) cerr<<"No other TTree names are provided for the purpose of duplication."<<endl;
    }
  else
    {
      cout<<"Names of other TTrees to be copied to the output root files:"<<endl<<endl;
      for(unsigned int i=0;i<m_othTtrNms.size();i++)
        {
          cout<<"  "<<m_othTtrNms[i]<<endl;
        }
      cout<<endl;
    }

  if(m_strgTpOfRawIptTopoDat=="AOI")
    {
      if(m_vbsLevStdOut==true) cout<<"Storage type of input raw topology truth information: Array of integers (default)."<<endl<<endl;
    }
  else if(m_strgTpOfRawIptTopoDat=="VOI")
    {
      cout<<"Storage type of input raw topology truth information: Vector of integers."<<endl<<endl;
    }
  else if(m_strgTpOfRawIptTopoDat=="MSI")
    {
      cout<<"Storage type of input raw topology truth information: multiple scalar integers."<<endl<<endl;
    }
  else if(m_strgTpOfRawIptTopoDat=="MSD")
    {
      cout<<"Storage type of input raw topology truth information: multiple scalar double-precision numbers."<<endl<<endl;
    }

  if(m_tbrNmOfNps!="nMCGen")
    {
      if(m_strgTpOfRawIptTopoDat=="AOI"||m_strgTpOfRawIptTopoDat=="MSI"||m_strgTpOfRawIptTopoDat=="MSD") cout<<"TBranch name of the number of particles: "<<m_tbrNmOfNps<<endl<<endl;
      else cout<<"The item with the prompt \"% TBranch name of the number of particles (Default: nMCGen)\" is not used since the storage type of the input raw topology truth information is \"vector of integers\"."<<endl<<endl; 
    }
  else
    {
      if(m_strgTpOfRawIptTopoDat=="AOI"||m_strgTpOfRawIptTopoDat=="MSI"||m_strgTpOfRawIptTopoDat=="MSD") 
        {
          if(m_vbsLevStdOut==true) cout<<"TBranch name of the number of particles: "<<m_tbrNmOfNps<<" (default)"<<endl<<endl;
        }
      else cout<<"The item with the prompt \"% TBranch name of the number of particles (Default: nMCGen)\" is not used since the storage type of the input raw topology truth information is \"vector of integers\"."<<endl<<endl;
    }

  if(m_tbrNmOfPid!="MCGenPDG")
    {
      cout<<"TBranch name of the PDG codes of particles: "<<m_tbrNmOfPid<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"TBranch name of the PDG codes of particles: "<<m_tbrNmOfPid<<" (default)"<<endl<<endl;
    }

  if(m_tbrNmOfMidx!="MCGenMothIndex")
    {
      cout<<"TBranch name of the mother indices of particles: "<<m_tbrNmOfMidx<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"TBranch name of the mother indices of particles: "<<m_tbrNmOfMidx<<" (default)"<<endl<<endl;
    }

  if(m_avoidOverCounting==true)
    {
      cout<<"Over counting will be avoided for candidate based analysis."<<endl<<endl;
      if(m_tbrNmOfIcandi!="__candidate__")
        { 
          cout<<"TBranch name of the indices of candidates in an event: "<<m_tbrNmOfIcandi<<endl<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"TBranch name of the indices of candidates in an event: "<<m_tbrNmOfIcandi<<" (default)"<<endl<<endl;
        }
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Over counting will not be avoided for candidate based analysis (default)."<<endl<<endl;
    }

  if(m_tbrNmOfRidx!="MCGenRawIndex")
    {
      cout<<"TBranch name of the raw indices of particles: "<<m_tbrNmOfRidx<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"TBranch name of the raw indices of particles: "<<m_tbrNmOfRidx<<" (default)"<<endl<<endl;
    }

  if(m_useRidx==false&&m_vPid_compDcyBrP.size()>0) m_useRidx=useRidx(m_vTypeOfTagRec_compDcyBrP);
  if(m_useRidx==false&&m_vPid_compCascDcyBrP.size()>0) m_useRidx=useRidx(m_vTypeOfTagRec_compCascDcyBrP);
  if(m_useRidx==false&&m_vPid_compDcyFStP.size()>0) m_useRidx=useRidx(m_vTypeOfTagRec_compDcyFStP);
  if(m_useRidx==false&&m_vPid_compProdBrP.size()>0) m_useRidx=useRidx(m_vTypeOfTagRec_compProdBrP);
  if(m_useRidx==false&&m_vPid_compMP.size()>0) m_useRidx=useRidx(m_vTypeOfTagRec_compMP);

  if(m_useRidx==true)
    {
      cout<<"The raw indices of particles stored in the TBranch: "<<m_tbrNmOfRidx<<" will be used."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The raw indices of particles stored in the TBranch: "<<m_tbrNmOfRidx<<" will not be used (default)."<<endl<<endl;
    }

  TChain * chn=new TChain(m_ttrNm.c_str());
  for(unsigned int i=0;i<m_nmsOfIptRootFls.size();i++)
    {
      chn->Add(m_nmsOfIptRootFls[i].c_str());
    }

  bool allIptsAreOK=true;
  TObjArray * objArray=chn->GetListOfFiles();
  TIter next(objArray);
  TChainElement * chnElmt=0;
  while((chnElmt=(TChainElement *) next()))
    {
      TFile * fl=new TFile(chnElmt->GetTitle());
      if(fl->IsZombie())
        {
          cerr<<"Error: The input root file \""<<chnElmt->GetTitle()<<"\" is zombie!"<<endl<<endl;
          allIptsAreOK=false;
        }
      else
        {
          TTree * tr=(TTree *) fl->Get(m_ttrNm.c_str());
          if(!tr)
            {
              cerr<<"Error: The input root file \""<<chnElmt->GetTitle()<<"\" does not contain a tree named \""<<m_ttrNm<<"\"!"<<endl<<endl;
              allIptsAreOK=false;
            }
          else
            {
              if(m_strgTpOfRawIptTopoDat=="AOI"||m_strgTpOfRawIptTopoDat=="MSI"||m_strgTpOfRawIptTopoDat=="MSD")
                {
                  TBranch * br0=tr->FindBranch(m_tbrNmOfNps.c_str());
                  if(!br0)
                    {
                      cerr<<"Error: The tree \""<<m_ttrNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_tbrNmOfNps<<"\"!"<<endl<<endl;
                      allIptsAreOK=false;
                    }
                }
              if(m_strgTpOfRawIptTopoDat=="AOI"||m_strgTpOfRawIptTopoDat=="VOI")
                {
                  TBranch * br1=tr->FindBranch(m_tbrNmOfPid.c_str());
                  if(!br1)
                    {
                      cerr<<"Error: The tree \""<<m_ttrNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_tbrNmOfPid<<"\"!"<<endl<<endl;
                      allIptsAreOK=false;
                    }
                  TBranch * br2=tr->FindBranch(m_tbrNmOfMidx.c_str());
                  if(!br2)
                    {
                      cerr<<"Error: The tree \""<<m_ttrNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_tbrNmOfMidx<<"\"!"<<endl<<endl;
                      allIptsAreOK=false;
                    }
                  if(m_useRidx==true)
                    {
                      TBranch * br3=tr->FindBranch(m_tbrNmOfRidx.c_str());
                      if(!br3)
                        {
                          cerr<<"Error: The tree \""<<m_ttrNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_tbrNmOfRidx<<"\"!"<<endl<<endl;
                          allIptsAreOK=false;
                        }
                    }
                }
              else
                {
                  ostringstream oss;
                  unsigned int i=0;
                  string strI,m_tbrNmOfPid_i,m_tbrNmOfMidx_i,m_tbrNmOfRidx_i;
                  TBranch * br1, * br2, * br3;
                  while(1)
                    {
                      oss.str("");
                      oss<<i;
                      strI=oss.str();
                      m_tbrNmOfPid_i=m_tbrNmOfPid+"_"+strI;
                      m_tbrNmOfMidx_i=m_tbrNmOfMidx+"_"+strI;
                      if(m_strgTpOfRawIptTopoDat=="MSI"&&m_useRidx==true) m_tbrNmOfRidx_i=m_tbrNmOfRidx+"_"+strI;
                      br1=tr->FindBranch(m_tbrNmOfPid_i.c_str());
                      br2=tr->FindBranch(m_tbrNmOfMidx_i.c_str());
                      if(m_strgTpOfRawIptTopoDat=="MSI"&&m_useRidx==true) br3=tr->FindBranch(m_tbrNmOfRidx_i.c_str());
                      if((!br1)||(!br2)) break;
                      if(m_strgTpOfRawIptTopoDat=="MSI"&&m_useRidx==true&&(!br3)) break;
                      i++;
                    }
                  if(i==0)
                    {
                      cerr<<"Error: The tree \""<<m_ttrNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_tbrNmOfPid<<"_i\", ";
                      if(m_strgTpOfRawIptTopoDat=="MSI"&&m_useRidx==true) cerr<<"\""<<m_tbrNmOfMidx<<"_i\", or \""<<m_tbrNmOfRidx;
                      else cerr<<"or \""<<m_tbrNmOfMidx;
                      cerr<<"_i\"!"<<endl<<endl;
                      allIptsAreOK=false;                      
                    }
                  else
                    {
                      cout<<"The tree \""<<m_ttrNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" contains "<<i<<" branches named \""<<m_tbrNmOfPid<<"_i\"";
                      if(m_strgTpOfRawIptTopoDat=="MSI"&&m_useRidx==true) cout<<", "<<i<<" branches named \""<<m_tbrNmOfMidx<<"\", and "<<i<<" branches named \""<<m_tbrNmOfRidx;
                      else cout<<" and "<<i<<" branches named \""<<m_tbrNmOfMidx;
                      cout<<"_i\"!"<<endl<<endl;
                      if(i<m_nMinTbrOfPidMidx) m_nMinTbrOfPidMidx=i;
                    }
                }
              if(m_avoidOverCounting==true)
                {
                  TBranch * br4=tr->FindBranch(m_tbrNmOfIcandi.c_str());
                  if(!br4)
                    {
                      cerr<<"Error: The tree \""<<m_ttrNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_tbrNmOfIcandi<<"\"!"<<endl<<endl;
                      allIptsAreOK=false;
                    }
                }
              if(m_vPid_compDcyBrP.size()>0) findBranch(chnElmt->GetTitle(), m_ttrNm, tr, m_vTypeOfTagRec_compDcyBrP, m_vTBrNmOfTagRec_compDcyBrP, m_vTBrNmOfNRec_compDcyBrP, allIptsAreOK, "% Component analysis --- decay branches of particles");
              if(m_vPid_compCascDcyBrP.size()>0) findBranch(chnElmt->GetTitle(), m_ttrNm, tr, m_vTypeOfTagRec_compCascDcyBrP, m_vTBrNmOfTagRec_compCascDcyBrP, m_vTBrNmOfNRec_compCascDcyBrP, allIptsAreOK, "% Component analysis --- cascade decay branches of particles");
              if(m_vPid_compDcyFStP.size()>0) findBranch(chnElmt->GetTitle(), m_ttrNm, tr, m_vTypeOfTagRec_compDcyFStP, m_vTBrNmOfTagRec_compDcyFStP, m_vTBrNmOfNRec_compDcyFStP, allIptsAreOK, "% Component analysis --- decay final states of particles");
              if(m_vPid_compProdBrP.size()>0) findBranch(chnElmt->GetTitle(), m_ttrNm, tr, m_vTypeOfTagRec_compProdBrP, m_vTBrNmOfTagRec_compProdBrP, m_vTBrNmOfNRec_compProdBrP, allIptsAreOK, "% Component analysis --- production branches of particles");
              if(m_vPid_compMP.size()>0) findBranch(chnElmt->GetTitle(), m_ttrNm, tr, m_vTypeOfTagRec_compMP, m_vTBrNmOfTagRec_compMP, m_vTBrNmOfNRec_compMP, allIptsAreOK, "% Component analysis --- mothers of particles");
            }
          for(unsigned int i=0;i<m_othTtrNms.size();i++)
            {
              tr=(TTree *) fl->Get(m_othTtrNms[i].c_str());
              if(!tr)
                {
                  cerr<<"Error: The input root file \""<<chnElmt->GetTitle()<<"\" does not contain a tree named \""<<m_othTtrNms[i]<<"\"!"<<endl<<endl;
                  allIptsAreOK=false;
                }
            }
          delete fl;
        }
    }
  if(!allIptsAreOK) exit(-1);
  delete chn;

  if(m_fixMidxBESIII==true)
    {
      cout<<"The mother indices of particles in BESIII experiment will be fixed."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"No fix is set for the mother indices of particles in BESIII experiment (default)."<<endl<<endl;
    }


  if(m_nEtrMax!=ULONG_MAX)
    {
      cout<<"Maximum number of entries to be processed: "<<m_nEtrMax<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Maximum number of entries to be processed: ULONG_MAX (default)"<<endl<<endl;
    }

  if(m_cut.empty())
    {
      if(m_vbsLevStdOut==true) cout<<"No cut is used to select entries (default)."<<endl<<endl;
    }
  else
    {
      if(m_vCut.size()>1) for(unsigned int i=0;i<m_vCut.size();i++) cout<<"Cut segment in Line "<<i<<": "<<m_vCut[i]<<endl;
      cout<<"Cut to select entries: "<<m_cut<<endl<<endl;
      if(m_cutMethod==true)
        {
          cout<<"The method to apply cut to array variables: True as long as one instance is true."<<endl<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"The method to apply cut to array variables: False as long as one instance is false (default)."<<endl<<endl;
        }
    }

  if(m_hHdDcyBrsMax!=ULONG_MAX)
    {
      cout<<"Maximum hierarchy of heading decay branches to be processed in each event: "<<m_hHdDcyBrsMax<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Maximum hierarchy of heading decay branches to be processed in each event: ULONG_MAX (default)"<<endl<<endl;
    }

  if(m_vIdPid.size()==0)
    { 
      if(m_vbsLevStdOut==true) cout<<"No particles are specified to ignore their decay."<<endl<<endl;
    }
  else
    {
      cout<<"Ignore the decay of the following particles:"<<endl<<endl;
      for(unsigned int i=0;i<m_vIdPid.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vIdPid[i]);
          cout<<endl;
        }
      cout<<endl;

      m_vIdCcPid.clear();
      m_vIdICcPid.clear();
      for(unsigned int i=0;i<m_vIdPid.size();i++)
        {
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vIdPid[i]==m_vIdPid[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vIdICcPid[j]!=0&&m_vIdPid[i]==m_vIdCcPid[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }
          if(m_ccSwitch==true)
            {
              m_vIdCcPid.push_back(getCcPid(m_vIdPid[i]));
              if(m_vIdCcPid[i]==m_vIdPid[i]) m_vIdICcPid.push_back(0);
              else m_vIdICcPid.push_back(1);
            }          
        }

      if(m_ccSwitch==true)
        {
          for(unsigned int i=0;i<m_vIdCcPid.size();i++)
            {
              if(m_vIdICcPid[i]!=0) m_vIdPid.push_back(m_vIdCcPid[i]);
            }
        }
    }

  if(m_vIddPid.size()==0)
    { 
      if(m_vbsLevStdOut==true) cout<<"No particles are specified to ignore the decay of their daughters."<<endl<<endl;
    }
  else
    {
      cout<<"Ignore the decay of the daughters of the following particles:"<<endl<<endl;
      for(unsigned int i=0;i<m_vIddPid.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vIddPid[i]);
          cout<<endl;
        }
      cout<<endl;

      m_vIddCcPid.clear();
      m_vIddICcPid.clear();
      for(unsigned int i=0;i<m_vIddPid.size();i++)
        {
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vIddPid[i]==m_vIddPid[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vIddICcPid[j]!=0&&m_vIddPid[i]==m_vIddCcPid[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }
          if(m_ccSwitch==true)
            {
              m_vIddCcPid.push_back(getCcPid(m_vIddPid[i]));
              if(m_vIddCcPid[i]==m_vIddPid[i]) m_vIddICcPid.push_back(0);
              else m_vIddICcPid.push_back(1);
            }          
        }

      if(m_ccSwitch==true)
        {
          for(unsigned int i=0;i<m_vIddCcPid.size();i++)
            {
              if(m_vIddICcPid[i]!=0) m_vIddPid.push_back(m_vIddCcPid[i]);
            }
        }
    }

  if(m_retainPi02GamGam==true)
    {
      cout<<"The decay of pi0 to gamma gamma is retained."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The decay of pi0 to gamma gamma is removed (default)."<<endl<<endl;
    }

  if(m_vVPid_ignoreFDcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No final decay branches to be ignored are specified."<<endl<<endl;
    }
  else
    {
      cout<<"The following final decay branches to be ignored are specified:"<<endl<<endl;
      for(unsigned int i=0;i<m_vVPid_ignoreFDcyBr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_ignoreFDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_ignoreFDcyBr[i][j]);
              cout<<endl<<endl;
	    }
	}
      cout<<endl;

      m_vIgnoreFDcyBr.clear(); m_vCcIgnoreFDcyBr.clear();
      list<int> ignoreFDcyBr, ccIgnoreFDcyBr;
      m_vICcIgnoreFDcyBr.clear();
      for(unsigned int i=0;i<m_vVPid_ignoreFDcyBr.size();i++)
        {
          ignoreFDcyBr.clear();
          for(unsigned int j=1;j<m_vVPid_ignoreFDcyBr[i].size();j++) ignoreFDcyBr.push_back(m_vVPid_ignoreFDcyBr[i][j]);
          sortByPidAndPchrg(ignoreFDcyBr);
          ignoreFDcyBr.push_front(m_vVPid_ignoreFDcyBr[i][0]);

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vIgnoreFDcyBr.size();j++)
            {
              if(ignoreFDcyBr==m_vIgnoreFDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" final decay branch is same as the "<<j+1<<ordNumSufj<<" final decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcIgnoreFDcyBr[j]!=0&&ignoreFDcyBr==m_vCcIgnoreFDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" final decay branch is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" final decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vIgnoreFDcyBr.push_back(ignoreFDcyBr);
          if(m_ccSwitch==true)
            {
              ccIgnoreFDcyBr.clear();
              list<int>::iterator liit=ignoreFDcyBr.begin();
              for(liit++;liit!=ignoreFDcyBr.end();liit++) ccIgnoreFDcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccIgnoreFDcyBr);
              liit=ignoreFDcyBr.begin();
              ccIgnoreFDcyBr.push_back(getCcPid((*liit)));
              m_vCcIgnoreFDcyBr.push_back(ccIgnoreFDcyBr);
              if(ccIgnoreFDcyBr==ignoreFDcyBr) m_vICcIgnoreFDcyBr.push_back(0);
              else m_vICcIgnoreFDcyBr.push_back(1);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vIgnoreFDcyBr.size();i++)
        {
          ignoreFDcyBr.clear();
          ignoreFDcyBr=m_vIgnoreFDcyBr[i];
          cout<<" ";
          list<int>::iterator liit=ignoreFDcyBr.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<" -->";
          for(liit++;liit!=ignoreFDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl<<endl;
        }
    }

  if(m_pidOfSISRGamUser!=m_pidOfSISRGam)
    {
      cout<<"PDG code of ISR photons: "<<m_pidOfSISRGamUser<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"PDG code of ISR photons: "<<m_pidOfSISRGam<<" (default)"<<endl<<endl;
    }

  if(m_pidOfSFSRGamUser!=m_pidOfSFSRGam)
    {
      cout<<"PDG code of FSR photons: "<<m_pidOfSFSRGamUser<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"PDG code of FSR photons: "<<m_pidOfSFSRGam<<" (default)"<<endl<<endl;
    }

  if(m_ignoreISR=="Ys")
    {
      cout<<"Strict ISR photons will be ignored."<<endl<<endl;
    }
  else if(m_ignoreISR=="Yg")
    {
      cout<<"Generalized ISR photons will be ignored."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"ISR photons will not be ignored (default)."<<endl<<endl;
    }

  if(m_ignoreFSR=="Ys")
    {
      cout<<"Strict FSR photons will be ignored."<<endl<<endl;
    }
  else if(m_ignoreFSR=="Yg")
    {
      cout<<"Generalized FSR photons will be ignored."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"FSR photons will not be ignored (default)."<<endl<<endl;
    }

  if(m_compAnaOfDcyTrs==true)
    {
      cout<<"The component analysis over decay trees will be performed."<<endl;
      if(m_nDcyTrsToBePrtdMax!=ULONG_MAX)
        {
          cout<<"Maximum number of decay trees to be printed: "<<m_nDcyTrsToBePrtdMax<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"Maximum number of decay trees to be printed: ULONG_MAX (default)"<<endl;
        }
      if(m_dcyIFStsUnderDcyTr==true)
        {
          cout<<"The decay initial-final states in the output pdf file are put under their respective decay trees."<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"The decay final states in the output pdf file are put in a column next to that for decay trees (default)."<<endl;
        }
      if(m_optIdxAndMidxOfDcyBrInDcyTr==true)
        {
          cout<<"The indices and mother indices of the decay branches in the decay trees are output to the pdf file."<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"The indices and mother indices of the decay branches in the decay trees are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;
      m_vDcyTr.clear(); m_vCcDcyTr.clear();
      m_vIDcyTr.clear(); m_vICcDcyTr.clear();
      m_vNDcyTr.clear(); m_vNCcDcyTr.clear();
      m_uomDcyTr.clear(); m_uomCcDcyTr.clear();
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The component analysis over decay trees will not be performed (default)."<<endl<<endl;
    }

  if(m_compAnaOfDcyIFSts==true)
    {
      cout<<"The component analysis over decay initial-final states will be performed."<<endl;
      if(m_nDcyIFStsToBePrtdMax!=ULONG_MAX)
        {
          cout<<"Maximum number of decay initial-final states to be printed: "<<m_nDcyIFStsToBePrtdMax<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"Maximum number of decay initial-final states to be printed: ULONG_MAX (default)"<<endl;
        }
      cout<<endl;       
      m_vDcyIFSts.clear(); m_vCcDcyIFSts.clear();
      m_vIDcyIFSts.clear(); m_vICcDcyIFSts.clear();
      m_vNDcyIFSts.clear(); m_vNCcDcyIFSts.clear();
      m_uomDcyIFSts.clear(); m_uomCcDcyIFSts.clear();
    } 
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The component analysis over decay initial-final states will not be performed (default)."<<endl<<endl;
    }

  if(m_compAnaOfDcyTrs==true)
    {
      if(m_compAnaOfDcyIFSts==true)
        {
          m_iDcyTrIDcyIFStsMap.clear(); m_iDcyTrICcDcyIFStsMap.clear();
        }
      else
        {
          m_vDcyIFSts.clear(); m_vCcDcyIFSts.clear();
        }
    }

  if(m_vPid_compDcyBrP.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No particles are specified for the analysis of their decay branches."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the decay branches of the following particles:"<<endl<<endl;
      char nm_compDcyBrP[20];
      for(unsigned int i=0;i<m_vPid_compDcyBrP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compDcyBrP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compDcyBrP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compDcyBrP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compDcyBrP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNm_compDcyBrP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compDcyBrP[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compDcyBrP, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the particle is set to be \""<<nm_compDcyBrP<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_compDcyBrP[i]=nm_compDcyBrP;
            }
          if(m_vNDcyBrToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of decay branches to be printed: "<<m_vNDcyBrToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of decay branches to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vTypeOfTagRec_compDcyBrP[i]!="")
            {
              cout<<"  The reconstructed ";
              if(m_vTypeOfTagRec_compDcyBrP[i]=="c"||m_vTypeOfTagRec_compDcyBrP[i]=="C") cout<<"charge";
              else if(m_vTypeOfTagRec_compDcyBrP[i]=="n"||m_vTypeOfTagRec_compDcyBrP[i]=="N") cout<<"neutral tag";
              else if(m_vTypeOfTagRec_compDcyBrP[i]=="!n"||m_vTypeOfTagRec_compDcyBrP[i]=="!N") cout<<"reversed neutral tag";
              else if(m_vTypeOfTagRec_compDcyBrP[i]=="p"||m_vTypeOfTagRec_compDcyBrP[i]=="P") cout<<"PDG code";
              else if(m_vTypeOfTagRec_compDcyBrP[i]=="i"||m_vTypeOfTagRec_compDcyBrP[i]=="I") cout<<"index";
              cout<<" of the particle, stored in the ";
              if(m_vTypeOfTagRec_compDcyBrP[i]=="c"||m_vTypeOfTagRec_compDcyBrP[i]=="n"||m_vTypeOfTagRec_compDcyBrP[i]=="!n"||m_vTypeOfTagRec_compDcyBrP[i]=="p"||m_vTypeOfTagRec_compDcyBrP[i]=="i") cout<<"scalar";
              else if(m_vTypeOfTagRec_compDcyBrP[i]=="C"||m_vTypeOfTagRec_compDcyBrP[i]=="N"||m_vTypeOfTagRec_compDcyBrP[i]=="!N"||m_vTypeOfTagRec_compDcyBrP[i]=="P"||m_vTypeOfTagRec_compDcyBrP[i]=="I") cout<<"array";
              cout<<" TBranch \""<<m_vTBrNmOfTagRec_compDcyBrP[i]<<"\", is specified to restrict its truth instances."<<endl;
              if(m_vTypeOfTagRec_compDcyBrP[i]=="C"||m_vTypeOfTagRec_compDcyBrP[i]=="N"||m_vTypeOfTagRec_compDcyBrP[i]=="!N"||m_vTypeOfTagRec_compDcyBrP[i]=="P"||m_vTypeOfTagRec_compDcyBrP[i]=="I")
                {
                  cout<<"  In addition, the number of reconstructed instances of the particle is stored in the TBranch \""<<m_vTBrNmOfNRec_compDcyBrP[i]<<"\" as the length of the array."<<endl;
                }
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  No reconstruction information to restrict the truth instances of the particle is specified (default)."<<endl;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vPid_ccCompDcyBrP.clear();
      m_vICcCompDcyBrP.clear();
      m_vVDcyBrP.clear(); m_vVDcyBrCcP.clear();
      vector< list<int> > vDcyBrP, vDcyBrCcP;
      vDcyBrP.clear(); vDcyBrCcP.clear();
      m_vVIDcyBrP.clear(); m_vVIDcyBrCcP.clear();
      vector<int> vIDcyBrP, vIDcyBrCcP;
      vIDcyBrP.clear(); vIDcyBrCcP.clear();
      m_vVNDcyBrP.clear(); m_vVNDcyBrCcP.clear();
      vector<int> vNDcyBrP, vNDcyBrCcP;
      vNDcyBrP.clear(); vNDcyBrCcP.clear();
      for(unsigned int i=0;i<m_vPid_compDcyBrP.size();i++)
        {
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vPid_compDcyBrP[i]==m_vPid_compDcyBrP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcCompDcyBrP[j]!=0&&m_vPid_compDcyBrP[i]==m_vPid_ccCompDcyBrP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vVDcyBrP.push_back(vDcyBrP);
          m_vVIDcyBrP.push_back(vIDcyBrP);
          m_vVNDcyBrP.push_back(vNDcyBrP);
          if(m_ccSwitch==true)
            {
              m_vPid_ccCompDcyBrP.push_back(getCcPid(m_vPid_compDcyBrP[i]));
              if(m_vPid_ccCompDcyBrP[i]==m_vPid_compDcyBrP[i]) m_vICcCompDcyBrP.push_back(0);
              else m_vICcCompDcyBrP.push_back(1);
              m_vVDcyBrCcP.push_back(vDcyBrCcP);
              m_vVIDcyBrCcP.push_back(vIDcyBrCcP);
              m_vVNDcyBrCcP.push_back(vNDcyBrCcP);              
            }     
        }
    }

  if(m_vPid_compCascDcyBrP.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No particles are specified for the analysis of their cascade decay branches."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the cascade decay branches of the following particles:"<<endl<<endl;
      char nm_compCascDcyBrP[20];
      for(unsigned int i=0;i<m_vPid_compCascDcyBrP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compCascDcyBrP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compCascDcyBrP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compCascDcyBrP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compCascDcyBrP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNm_compCascDcyBrP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compCascDcyBrP[i]<<"\" for the cascade decay branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compCascDcyBrP, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the particle is set to be \""<<nm_compCascDcyBrP<<"\" for the cascade decay branch names of the topology tags (default)."<<endl;
              m_vNm_compCascDcyBrP[i]=nm_compCascDcyBrP;
            }
          if(m_vNCascDcyBrToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of cascade decay branches to be printed: "<<m_vNCascDcyBrToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of cascade decay branches to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vHCascDcyBrMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum hierarchy of cascade decay branches to be processed for the particle: "<<m_vHCascDcyBrMax[i]<<endl;         
            }
          else
            { 
              if(m_vbsLevStdOut==true) cout<<"  Maximum hierarchy of cascade decay branches to be processed for the particle: ULONG_MAX (default)"<<endl;
            }
          if(m_vTypeOfTagRec_compCascDcyBrP[i]!="")
            {
              cout<<"  The reconstructed ";
              if(m_vTypeOfTagRec_compCascDcyBrP[i]=="c"||m_vTypeOfTagRec_compCascDcyBrP[i]=="C") cout<<"charge";
              else if(m_vTypeOfTagRec_compCascDcyBrP[i]=="n"||m_vTypeOfTagRec_compCascDcyBrP[i]=="N") cout<<"neutral tag";
              else if(m_vTypeOfTagRec_compCascDcyBrP[i]=="!n"||m_vTypeOfTagRec_compCascDcyBrP[i]=="!N") cout<<"reversed neutral tag";
              else if(m_vTypeOfTagRec_compCascDcyBrP[i]=="p"||m_vTypeOfTagRec_compCascDcyBrP[i]=="P") cout<<"PDG code";
              else if(m_vTypeOfTagRec_compCascDcyBrP[i]=="i"||m_vTypeOfTagRec_compCascDcyBrP[i]=="I") cout<<"index";
              cout<<" of the particle, stored in the ";
              if(m_vTypeOfTagRec_compCascDcyBrP[i]=="c"||m_vTypeOfTagRec_compCascDcyBrP[i]=="n"||m_vTypeOfTagRec_compCascDcyBrP[i]=="!n"||m_vTypeOfTagRec_compCascDcyBrP[i]=="p"||m_vTypeOfTagRec_compCascDcyBrP[i]=="i") cout<<"scalar";
              else if(m_vTypeOfTagRec_compCascDcyBrP[i]=="C"||m_vTypeOfTagRec_compCascDcyBrP[i]=="N"||m_vTypeOfTagRec_compCascDcyBrP[i]=="!N"||m_vTypeOfTagRec_compCascDcyBrP[i]=="P"||m_vTypeOfTagRec_compCascDcyBrP[i]=="I") cout<<"array";
              cout<<" TBranch \""<<m_vTBrNmOfTagRec_compCascDcyBrP[i]<<"\", is specified to restrict its truth instances."<<endl;
              if(m_vTypeOfTagRec_compCascDcyBrP[i]=="C"||m_vTypeOfTagRec_compCascDcyBrP[i]=="N"||m_vTypeOfTagRec_compCascDcyBrP[i]=="!N"||m_vTypeOfTagRec_compCascDcyBrP[i]=="P"||m_vTypeOfTagRec_compCascDcyBrP[i]=="I")
                {
                  cout<<"  In addition, the number of reconstructed instances of the particle is stored in the TBranch \""<<m_vTBrNmOfNRec_compCascDcyBrP[i]<<"\" as the length of the array."<<endl;
                }
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  No reconstruction information to restrict the truth instances of the particle is specified (default)."<<endl;
            }
          if(m_vOptIdxAndMidxOfDcyBrInCascDcyBrP[i]==true)
            {
              cout<<"  The indices and mother indices of the decay branches in the cascade decay branches of the particle are output to the pdf file."<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the decay branches in the cascade decay branches of the particle are not output to the pdf file (default)."<<endl;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vPid_ccCompCascDcyBrP.clear();
      m_vICcCompCascDcyBrP.clear();
      m_vVCascDcyBrP.clear(); m_vVCascDcyBrCcP.clear();
      vector< vector< list<int> > > vCascDcyBrP, vCascDcyBrCcP;
      vCascDcyBrP.clear(); vCascDcyBrCcP.clear();
      m_vVICascDcyBrP.clear(); m_vVICascDcyBrCcP.clear();
      vector<int> vICascDcyBrP, vICascDcyBrCcP;
      vICascDcyBrP.clear(); vICascDcyBrCcP.clear();
      m_vVNCascDcyBrP.clear(); m_vVNCascDcyBrCcP.clear();
      vector<int> vNCascDcyBrP, vNCascDcyBrCcP;
      vNCascDcyBrP.clear(); vNCascDcyBrCcP.clear();
      m_vUomCascDcyBrP.clear(); m_vUomCascDcyBrCcP.clear();
      unordered_map<string,int> uomCascDcyBrP, uomCascDcyBrCcP;
      uomCascDcyBrP.clear(); uomCascDcyBrCcP.clear();      
      for(unsigned int i=0;i<m_vPid_compCascDcyBrP.size();i++)
        {
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vPid_compCascDcyBrP[i]==m_vPid_compCascDcyBrP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcCompCascDcyBrP[j]!=0&&m_vPid_compCascDcyBrP[i]==m_vPid_ccCompCascDcyBrP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vVCascDcyBrP.push_back(vCascDcyBrP);
          m_vVICascDcyBrP.push_back(vICascDcyBrP);
          m_vVNCascDcyBrP.push_back(vNCascDcyBrP);
          m_vUomCascDcyBrP.push_back(uomCascDcyBrP);
          if(m_ccSwitch==true)
            {
              m_vPid_ccCompCascDcyBrP.push_back(getCcPid(m_vPid_compCascDcyBrP[i]));
              if(m_vPid_ccCompCascDcyBrP[i]==m_vPid_compCascDcyBrP[i]) m_vICcCompCascDcyBrP.push_back(0);
              else m_vICcCompCascDcyBrP.push_back(1);
              m_vVCascDcyBrCcP.push_back(vCascDcyBrCcP);
              m_vVICascDcyBrCcP.push_back(vICascDcyBrCcP);
              m_vVNCascDcyBrCcP.push_back(vNCascDcyBrCcP);              
              m_vUomCascDcyBrCcP.push_back(uomCascDcyBrCcP);
            }     
        }
    }

  if(m_vPid_compDcyFStP.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No particles are specified for the analysis of their decay final states."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the decay final states of the following particles:"<<endl<<endl;
      char nm_compDcyFStP[20];
      for(unsigned int i=0;i<m_vPid_compDcyFStP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compDcyFStP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compDcyFStP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compDcyFStP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compDcyFStP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNm_compDcyFStP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compDcyFStP[i]<<"\" for the cascade branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compDcyFStP, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the particle is set to be \""<<nm_compDcyFStP<<"\" for the cascade branch names of the topology tags (default)."<<endl;
              m_vNm_compDcyFStP[i]=nm_compDcyFStP;
            }
          if(m_vNDcyFStToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of decay final states to be printed: "<<m_vNDcyFStToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of decay final states to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNDcyFStP[i]!=ULONG_MAX)
            {
              cout<<"  Number of decay final state particles to be processed for the particle: "<<m_vNDcyFStP[i]<<endl;         
            }
          else
            { 
              if(m_vbsLevStdOut==true) cout<<"  Number of decay final state particles to be processed for the particle: ULONG_MAX (default)"<<endl;
            }
          if(m_vTypeOfTagRec_compDcyFStP[i]!="")
            {
              cout<<"  The reconstructed ";
              if(m_vTypeOfTagRec_compDcyFStP[i]=="c"||m_vTypeOfTagRec_compDcyFStP[i]=="C") cout<<"charge";
              else if(m_vTypeOfTagRec_compDcyFStP[i]=="n"||m_vTypeOfTagRec_compDcyFStP[i]=="N") cout<<"neutral tag";
              else if(m_vTypeOfTagRec_compDcyFStP[i]=="!n"||m_vTypeOfTagRec_compDcyFStP[i]=="!N") cout<<"reversed neutral tag";
              else if(m_vTypeOfTagRec_compDcyFStP[i]=="p"||m_vTypeOfTagRec_compDcyFStP[i]=="P") cout<<"PDG code";
              else if(m_vTypeOfTagRec_compDcyFStP[i]=="i"||m_vTypeOfTagRec_compDcyFStP[i]=="I") cout<<"index";
              cout<<" of the particle, stored in the ";
              if(m_vTypeOfTagRec_compDcyFStP[i]=="c"||m_vTypeOfTagRec_compDcyFStP[i]=="n"||m_vTypeOfTagRec_compDcyFStP[i]=="!n"||m_vTypeOfTagRec_compDcyFStP[i]=="p"||m_vTypeOfTagRec_compDcyFStP[i]=="i") cout<<"scalar";
              else if(m_vTypeOfTagRec_compDcyFStP[i]=="C"||m_vTypeOfTagRec_compDcyFStP[i]=="N"||m_vTypeOfTagRec_compDcyFStP[i]=="!N"||m_vTypeOfTagRec_compDcyFStP[i]=="P"||m_vTypeOfTagRec_compDcyFStP[i]=="I") cout<<"array";
              cout<<" TBranch \""<<m_vTBrNmOfTagRec_compDcyFStP[i]<<"\", is specified to restrict its truth instances."<<endl;
              if(m_vTypeOfTagRec_compDcyFStP[i]=="C"||m_vTypeOfTagRec_compDcyFStP[i]=="N"||m_vTypeOfTagRec_compDcyFStP[i]=="!N"||m_vTypeOfTagRec_compDcyFStP[i]=="P"||m_vTypeOfTagRec_compDcyFStP[i]=="I")
                {
                  cout<<"  In addition, the number of reconstructed instances of the particle is stored in the TBranch \""<<m_vTBrNmOfNRec_compDcyFStP[i]<<"\" as the length of the array."<<endl;
                }
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  No reconstruction information to restrict the truth instances of the particle is specified (default)."<<endl;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vPid_ccCompDcyFStP.clear();
      m_vICcCompDcyFStP.clear();
      m_vVDcyFStP.clear(); m_vVDcyFStCcP.clear();
      vector< list<int> > vDcyFStP, vDcyFStCcP;
      vDcyFStP.clear(); vDcyFStCcP.clear();
      m_vVIDcyFStP.clear(); m_vVIDcyFStCcP.clear();
      vector<int> vIDcyFStP, vIDcyFStCcP;
      vIDcyFStP.clear(); vIDcyFStCcP.clear();
      m_vVNDcyFStP.clear(); m_vVNDcyFStCcP.clear();
      vector<int> vNDcyFStP, vNDcyFStCcP;
      vNDcyFStP.clear(); vNDcyFStCcP.clear();
      m_vUomDcyFStP.clear(); m_vUomDcyFStCcP.clear();
      unordered_map<string,int> uomDcyFStP, uomDcyFStCcP;
      uomDcyFStP.clear(); uomDcyFStCcP.clear();
      for(unsigned int i=0;i<m_vPid_compDcyFStP.size();i++)
        {
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vPid_compDcyFStP[i]==m_vPid_compDcyFStP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcCompDcyFStP[j]!=0&&m_vPid_compDcyFStP[i]==m_vPid_ccCompDcyFStP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vVDcyFStP.push_back(vDcyFStP);
          m_vVIDcyFStP.push_back(vIDcyFStP);
          m_vVNDcyFStP.push_back(vNDcyFStP);
          m_vUomDcyFStP.push_back(uomDcyFStP);
          if(m_ccSwitch==true)
            {
              m_vPid_ccCompDcyFStP.push_back(getCcPid(m_vPid_compDcyFStP[i]));
              if(m_vPid_ccCompDcyFStP[i]==m_vPid_compDcyFStP[i]) m_vICcCompDcyFStP.push_back(0);
              else m_vICcCompDcyFStP.push_back(1);
              m_vVDcyFStCcP.push_back(vDcyFStCcP);
              m_vVIDcyFStCcP.push_back(vIDcyFStCcP);
              m_vVNDcyFStCcP.push_back(vNDcyFStCcP);              
              m_vUomDcyFStCcP.push_back(uomDcyFStCcP);
            }     
        }
    }

  if(m_vPid_compProdBrP.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No particles are specified for the analysis of their production branches."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the production branches of the following particles:"<<endl<<endl;
      char nm_compProdBrP[20];
      for(unsigned int i=0;i<m_vPid_compProdBrP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compProdBrP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compProdBrP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compProdBrP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compProdBrP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNm_compProdBrP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compProdBrP[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compProdBrP, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the particle is set to be \""<<nm_compProdBrP<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_compProdBrP[i]=nm_compProdBrP;
            }
          if(m_vNProdBrToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of production branches to be printed: "<<m_vNProdBrToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of production branches to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vTypeOfTagRec_compProdBrP[i]!="")
            {
              cout<<"  The reconstructed ";
              if(m_vTypeOfTagRec_compProdBrP[i]=="c"||m_vTypeOfTagRec_compProdBrP[i]=="C") cout<<"charge";
              else if(m_vTypeOfTagRec_compProdBrP[i]=="n"||m_vTypeOfTagRec_compProdBrP[i]=="N") cout<<"neutral tag";
              else if(m_vTypeOfTagRec_compProdBrP[i]=="!n"||m_vTypeOfTagRec_compProdBrP[i]=="!N") cout<<"reversed neutral tag";
              else if(m_vTypeOfTagRec_compProdBrP[i]=="p"||m_vTypeOfTagRec_compProdBrP[i]=="P") cout<<"PDG code";
              else if(m_vTypeOfTagRec_compProdBrP[i]=="i"||m_vTypeOfTagRec_compProdBrP[i]=="I") cout<<"index";
              cout<<" of the particle, stored in the ";
              if(m_vTypeOfTagRec_compProdBrP[i]=="c"||m_vTypeOfTagRec_compProdBrP[i]=="n"||m_vTypeOfTagRec_compProdBrP[i]=="!n"||m_vTypeOfTagRec_compProdBrP[i]=="p"||m_vTypeOfTagRec_compProdBrP[i]=="i") cout<<"scalar";
              else if(m_vTypeOfTagRec_compProdBrP[i]=="C"||m_vTypeOfTagRec_compProdBrP[i]=="N"||m_vTypeOfTagRec_compProdBrP[i]=="!N"||m_vTypeOfTagRec_compProdBrP[i]=="P"||m_vTypeOfTagRec_compProdBrP[i]=="I") cout<<"array";
              cout<<" TBranch \""<<m_vTBrNmOfTagRec_compProdBrP[i]<<"\", is specified to restrict its truth instances."<<endl;
              if(m_vTypeOfTagRec_compProdBrP[i]=="C"||m_vTypeOfTagRec_compProdBrP[i]=="N"||m_vTypeOfTagRec_compProdBrP[i]=="!N"||m_vTypeOfTagRec_compProdBrP[i]=="P"||m_vTypeOfTagRec_compProdBrP[i]=="I")
                {
                  cout<<"  In addition, the number of reconstructed instances of the particle is stored in the TBranch \""<<m_vTBrNmOfNRec_compProdBrP[i]<<"\" as the length of the array."<<endl;
                }
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  No reconstruction information to restrict the truth instances of the particle is specified (default)."<<endl;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vPid_ccCompProdBrP.clear();
      m_vICcCompProdBrP.clear();
      m_vVProdBrP.clear(); m_vVProdBrCcP.clear();
      vector< list<int> > vProdBrP, vProdBrCcP;
      vProdBrP.clear(); vProdBrCcP.clear();
      m_vVIProdBrP.clear(); m_vVIProdBrCcP.clear();
      vector<int> vIProdBrP, vIProdBrCcP;
      vIProdBrP.clear(); vIProdBrCcP.clear();
      m_vVNProdBrP.clear(); m_vVNProdBrCcP.clear();
      vector<int> vNProdBrP, vNProdBrCcP;
      vNProdBrP.clear(); vNProdBrCcP.clear();
      for(unsigned int i=0;i<m_vPid_compProdBrP.size();i++)
        {
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vPid_compProdBrP[i]==m_vPid_compProdBrP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcCompProdBrP[j]!=0&&m_vPid_compProdBrP[i]==m_vPid_ccCompProdBrP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vVProdBrP.push_back(vProdBrP);
          m_vVIProdBrP.push_back(vIProdBrP);
          m_vVNProdBrP.push_back(vNProdBrP);
          if(m_ccSwitch==true)
            {
              m_vPid_ccCompProdBrP.push_back(getCcPid(m_vPid_compProdBrP[i]));
              if(m_vPid_ccCompProdBrP[i]==m_vPid_compProdBrP[i]) m_vICcCompProdBrP.push_back(0);
              else m_vICcCompProdBrP.push_back(1);
              m_vVProdBrCcP.push_back(vProdBrCcP);
              m_vVIProdBrCcP.push_back(vIProdBrCcP);
              m_vVNProdBrCcP.push_back(vNProdBrCcP);              
            }     
        }
    }

  if(m_vPid_compMP.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No particles are specified for the analysis of their mothers."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the mothers of the following particles:"<<endl<<endl;
      char nm_compMP[20];
      for(unsigned int i=0;i<m_vPid_compMP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compMP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compMP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compMP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compMP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNm_compMP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compMP[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compMP, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the particle is set to be \""<<nm_compMP<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_compMP[i]=nm_compMP;
            }
          if(m_vNMToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of mothers to be printed: "<<m_vNMToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of mothers to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vTypeOfTagRec_compMP[i]!="")
            {
              cout<<"  The reconstructed ";
              if(m_vTypeOfTagRec_compMP[i]=="c"||m_vTypeOfTagRec_compMP[i]=="C") cout<<"charge";
              else if(m_vTypeOfTagRec_compMP[i]=="n"||m_vTypeOfTagRec_compMP[i]=="N") cout<<"neutral tag";
              else if(m_vTypeOfTagRec_compMP[i]=="!n"||m_vTypeOfTagRec_compMP[i]=="!N") cout<<"reversed neutral tag";
              else if(m_vTypeOfTagRec_compMP[i]=="p"||m_vTypeOfTagRec_compMP[i]=="P") cout<<"PDG code";
              else if(m_vTypeOfTagRec_compMP[i]=="i"||m_vTypeOfTagRec_compMP[i]=="I") cout<<"index";
              cout<<" of the particle, stored in the ";
              if(m_vTypeOfTagRec_compMP[i]=="c"||m_vTypeOfTagRec_compMP[i]=="n"||m_vTypeOfTagRec_compMP[i]=="!n"||m_vTypeOfTagRec_compMP[i]=="p"||m_vTypeOfTagRec_compMP[i]=="i") cout<<"scalar";
              else if(m_vTypeOfTagRec_compMP[i]=="C"||m_vTypeOfTagRec_compMP[i]=="N"||m_vTypeOfTagRec_compMP[i]=="!N"||m_vTypeOfTagRec_compMP[i]=="P"||m_vTypeOfTagRec_compMP[i]=="I") cout<<"array";
              cout<<" TBranch \""<<m_vTBrNmOfTagRec_compMP[i]<<"\", is specified to restrict its truth instances."<<endl;
              if(m_vTypeOfTagRec_compMP[i]=="C"||m_vTypeOfTagRec_compMP[i]=="N"||m_vTypeOfTagRec_compMP[i]=="!N"||m_vTypeOfTagRec_compMP[i]=="P"||m_vTypeOfTagRec_compMP[i]=="I")
                {
                  cout<<"  In addition, the number of reconstructed instances of the particle is stored in the TBranch \""<<m_vTBrNmOfNRec_compMP[i]<<"\" as the length of the array."<<endl;
                }
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  No reconstruction information to restrict the truth instances of the particle is specified (default)."<<endl;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vPid_ccCompMP.clear();
      m_vICcCompMP.clear();
      m_vVMpidP.clear(); m_vVMpidCcP.clear();
      vector<int> vMpidP, vMpidCcP;
      vMpidP.clear(); vMpidCcP.clear();
      m_vVIMP.clear(); m_vVIMCcP.clear();
      vector<int> vIMP, vIMCcP;
      vIMP.clear(); vIMCcP.clear();
      m_vVNMP.clear(); m_vVNMCcP.clear();
      vector<int> vNMP, vNMCcP;
      vNMP.clear(); vNMCcP.clear();
      for(unsigned int i=0;i<m_vPid_compMP.size();i++)
        {
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vPid_compMP[i]==m_vPid_compMP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcCompMP[j]!=0&&m_vPid_compMP[i]==m_vPid_ccCompMP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vVMpidP.push_back(vMpidP);
          m_vVIMP.push_back(vIMP);
          m_vVNMP.push_back(vNMP);
          if(m_ccSwitch==true)
            {
              m_vPid_ccCompMP.push_back(getCcPid(m_vPid_compMP[i]));
              if(m_vPid_ccCompMP[i]==m_vPid_compMP[i]) m_vICcCompMP.push_back(0);
              else m_vICcCompMP.push_back(1);
              m_vVMpidCcP.push_back(vMpidCcP);
              m_vVIMCcP.push_back(vIMCcP);
              m_vVNMCcP.push_back(vNMCcP);              
            }     
        }
    }

  if(m_vVPid_compIncDcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No inclusive decay branches are specified for the analysis of their exclusive components."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the exclusive components of the following inclusive decay branches:"<<endl<<endl;
      char nm_compIncDcyBr[20];
      for(unsigned int i=0;i<m_vVPid_compIncDcyBr.size();i++)
        {
          for(unsigned int j=0;j<m_vVPid_compIncDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_compIncDcyBr[i][j]);
              cout<<endl;
	    }
          if(m_vNm_compIncDcyBr[i]!="")
            {
              cout<<"  Alias for the inclusive decay branch is set to be \""<<m_vNm_compIncDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compIncDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the inclusive decay branch is set to be \""<<nm_compIncDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          if(m_vNExcCompsToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNExcCompsToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vOption_compIncDcyBr[i]!="")
            {
              cout<<"  The remaining particles unspecified in the inclusive decay are restricted to ";
              if(m_vOption_compIncDcyBr[i]=="Is"||m_vOption_compIncDcyBr[i]=="Is-IRA") cout<<"strict ISR";
              else if(m_vOption_compIncDcyBr[i]=="Ig"||m_vOption_compIncDcyBr[i]=="Ig-IRA") cout<<"generalized ISR";
              else if(m_vOption_compIncDcyBr[i]=="Fs"||m_vOption_compIncDcyBr[i]=="Fs-IRA") cout<<"strict FSR";
              else if(m_vOption_compIncDcyBr[i]=="Fg"||m_vOption_compIncDcyBr[i]=="Fg-IRA") cout<<"generalized FSR";
              cout<<" photons."<<endl;
              if(m_vOption_compIncDcyBr[i].find("-IRA")!=string::npos) cout<<"  The specified decay branch is intermediate-resonance-allowed.";
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  No restrictions are placed on the remaining particles unspecified in the inclusive decay (default)."<<endl;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vCompIncDcyBr.clear(); m_vCompCcIncDcyBr.clear();
      list<int> compIncDcyBr, compCcIncDcyBr;
      m_vICcCompIncDcyBr.clear();
      m_vVDcyBrIncDcyBr.clear(); m_vVDcyBrCcIncDcyBr.clear();
      vector< list<int> > vDcyBrIncDcyBr, vDcyBrCcIncDcyBr;
      vDcyBrIncDcyBr.clear(); vDcyBrCcIncDcyBr.clear();
      m_vVIDcyBrIncDcyBr.clear(); m_vVIDcyBrCcIncDcyBr.clear();
      vector<int> vIDcyBrIncDcyBr, vIDcyBrCcIncDcyBr;
      vIDcyBrIncDcyBr.clear(); vIDcyBrCcIncDcyBr.clear();
      m_vVNDcyBrIncDcyBr.clear(); m_vVNDcyBrCcIncDcyBr.clear();
      vector<int> vNDcyBrIncDcyBr, vNDcyBrCcIncDcyBr;
      vNDcyBrIncDcyBr.clear(); vNDcyBrCcIncDcyBr.clear();
      for(unsigned int i=0;i<m_vVPid_compIncDcyBr.size();i++)
        {
          compIncDcyBr.clear();
          for(unsigned int j=1;j<m_vVPid_compIncDcyBr[i].size();j++) compIncDcyBr.push_back(m_vVPid_compIncDcyBr[i][j]);
          sortByPidAndPchrg(compIncDcyBr);
          if(m_vVPid_compIncDcyBr[i][0]!=m_pidOfISt)
            {
              compIncDcyBr.push_front(m_vVPid_compIncDcyBr[i][0]);
            }
          else
            {
              compIncDcyBr.push_front(m_pidOfISt1);
              compIncDcyBr.push_front(m_pidOfISt2);
            }

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vCompIncDcyBr.size();j++)
            {
              if(compIncDcyBr==m_vCompIncDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" inclusive decay is same as the "<<j+1<<ordNumSufj<<" inclusive decay!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcCompIncDcyBr[j]!=0&&compIncDcyBr==m_vCompCcIncDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" inclusive decay is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" inclusive decay!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vCompIncDcyBr.push_back(compIncDcyBr);
          m_vVDcyBrIncDcyBr.push_back(vDcyBrIncDcyBr);
          m_vVIDcyBrIncDcyBr.push_back(vIDcyBrIncDcyBr);
          m_vVNDcyBrIncDcyBr.push_back(vNDcyBrIncDcyBr);
          if(m_ccSwitch==true)
            {
              compCcIncDcyBr.clear();
              list<int>::iterator liit=compIncDcyBr.begin();
              if((*liit)==m_pidOfISt2) liit++;
              for(liit++;liit!=compIncDcyBr.end();liit++) compCcIncDcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(compCcIncDcyBr);
              liit=compIncDcyBr.begin();
              if((*liit)!=m_pidOfISt2)
                {
                  compCcIncDcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  compCcIncDcyBr.push_front(m_pidOfISt1);
                  compCcIncDcyBr.push_front(m_pidOfISt2);
                }
              m_vCompCcIncDcyBr.push_back(compCcIncDcyBr);
              if(compCcIncDcyBr==compIncDcyBr) m_vICcCompIncDcyBr.push_back(0);
              else m_vICcCompIncDcyBr.push_back(1);
              m_vVDcyBrCcIncDcyBr.push_back(vDcyBrCcIncDcyBr);
              m_vVIDcyBrCcIncDcyBr.push_back(vIDcyBrCcIncDcyBr);
              m_vVNDcyBrCcIncDcyBr.push_back(vNDcyBrCcIncDcyBr);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vCompIncDcyBr.size();i++)
        {
          compIncDcyBr.clear();
          compIncDcyBr=m_vCompIncDcyBr[i];
          cout<<" ";
          list<int>::iterator liit=compIncDcyBr.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=compIncDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<" + anything"<<endl;
          if(m_vNm_compIncDcyBr[i]!="")
            {
              cout<<"  Alias for the inclusive decay branch is set to be \""<<m_vNm_compIncDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compIncDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the inclusive decay branch is set to be \""<<nm_compIncDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_compIncDcyBr[i]=nm_compIncDcyBr;
            }
          if(m_vNExcCompsToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNExcCompsToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vOption_compIncDcyBr[i]!="")
            {
              cout<<"  The remaining particles unspecified in the inclusive decay are restricted to ";
              if(m_vOption_compIncDcyBr[i]=="Is"||m_vOption_compIncDcyBr[i]=="Is-IRA") cout<<"strict ISR";
              else if(m_vOption_compIncDcyBr[i]=="Ig"||m_vOption_compIncDcyBr[i]=="Ig-IRA") cout<<"generalized ISR";
              else if(m_vOption_compIncDcyBr[i]=="Fs"||m_vOption_compIncDcyBr[i]=="Fs-IRA") cout<<"strict FSR";
              else if(m_vOption_compIncDcyBr[i]=="Fg"||m_vOption_compIncDcyBr[i]=="Fg-IRA") cout<<"generalized FSR";
              cout<<" photons."<<endl;
              if(m_vOption_compIncDcyBr[i].find("-IRA")!=string::npos) cout<<"  The specified decay branch is intermediate-resonance-allowed.";
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  No restrictions are placed on the remaining particles unspecified in the inclusive decay (default)."<<endl;
            }
          cout<<endl;
        }
    }

  if(m_vVPid_compIRADcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No intermediate-resonance-allowed decay branches are specified for the analysis of the internal structures involved in them."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the internal structures involved in the following intermediate-resonance-allowed decay branches:"<<endl<<endl;
      char nm_compIRADcyBr[20];
      for(unsigned int i=0;i<m_vVPid_compIRADcyBr.size();i++)
        {
          for(unsigned int j=0;j<m_vVPid_compIRADcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_compIRADcyBr[i][j]);
              cout<<endl;
	    }
          if(m_vNm_compIRADcyBr[i]!="")
            {
              cout<<"  Alias for the intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_compIRADcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compIRADcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the intermediate-resonance-allowed decay branch is set to be \""<<nm_compIRADcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          if(m_vNIntStrusToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNIntStrusToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vCompIRADcyBr.clear(); m_vCompCcIRADcyBr.clear();
      list<int> compIRADcyBr, compCcIRADcyBr;
      m_vICcCompIRADcyBr.clear();
      m_vVDcyBrIRADcyBr.clear(); m_vVDcyBrCcIRADcyBr.clear();
      vector< vector< list<int> > > vDcyBrIRADcyBr, vDcyBrCcIRADcyBr;
      vDcyBrIRADcyBr.clear(); vDcyBrCcIRADcyBr.clear();
      m_vVIDcyBrIRADcyBr.clear(); m_vVIDcyBrCcIRADcyBr.clear();
      vector<int> vIDcyBrIRADcyBr, vIDcyBrCcIRADcyBr;
      vIDcyBrIRADcyBr.clear(); vIDcyBrCcIRADcyBr.clear();
      m_vVNDcyBrIRADcyBr.clear(); m_vVNDcyBrCcIRADcyBr.clear();
      vector<int> vNDcyBrIRADcyBr, vNDcyBrCcIRADcyBr;
      vNDcyBrIRADcyBr.clear(); vNDcyBrCcIRADcyBr.clear();
      for(unsigned int i=0;i<m_vVPid_compIRADcyBr.size();i++)
        {
          compIRADcyBr.clear();
          for(unsigned int j=1;j<m_vVPid_compIRADcyBr[i].size();j++) compIRADcyBr.push_back(m_vVPid_compIRADcyBr[i][j]);
          sortByPidAndPchrg(compIRADcyBr);
          if(m_vVPid_compIRADcyBr[i][0]!=m_pidOfISt)
            {
              compIRADcyBr.push_front(m_vVPid_compIRADcyBr[i][0]);
            }
          else
            {
              compIRADcyBr.push_front(m_pidOfISt1);
              compIRADcyBr.push_front(m_pidOfISt2);
            }

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vCompIRADcyBr.size();j++)
            {
              if(compIRADcyBr==m_vCompIRADcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" intermediate-resonance-allowed decay is same as the "<<j+1<<ordNumSufj<<" intermediate-resonance-allowed decay!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcCompIRADcyBr[j]!=0&&compIRADcyBr==m_vCompCcIRADcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" intermediate-resonance-allowed decay is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" intermediate-resonance-allowed decay!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vCompIRADcyBr.push_back(compIRADcyBr);
          m_vVDcyBrIRADcyBr.push_back(vDcyBrIRADcyBr);
          m_vVIDcyBrIRADcyBr.push_back(vIDcyBrIRADcyBr);
          m_vVNDcyBrIRADcyBr.push_back(vNDcyBrIRADcyBr);
          if(m_ccSwitch==true)
            {
              compCcIRADcyBr.clear();
              list<int>::iterator liit=compIRADcyBr.begin();
              if((*liit)==m_pidOfISt2) liit++;
              for(liit++;liit!=compIRADcyBr.end();liit++) compCcIRADcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(compCcIRADcyBr);
              liit=compIRADcyBr.begin();
              if((*liit)!=m_pidOfISt2)
                {
                  compCcIRADcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  compCcIRADcyBr.push_front(m_pidOfISt1);
                  compCcIRADcyBr.push_front(m_pidOfISt2);
                }
              m_vCompCcIRADcyBr.push_back(compCcIRADcyBr);
              if(compCcIRADcyBr==compIRADcyBr) m_vICcCompIRADcyBr.push_back(0);
              else m_vICcCompIRADcyBr.push_back(1);
              m_vVDcyBrCcIRADcyBr.push_back(vDcyBrCcIRADcyBr);
              m_vVIDcyBrCcIRADcyBr.push_back(vIDcyBrCcIRADcyBr);
              m_vVNDcyBrCcIRADcyBr.push_back(vNDcyBrCcIRADcyBr);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vCompIRADcyBr.size();i++)
        {
          compIRADcyBr.clear();
          compIRADcyBr=m_vCompIRADcyBr[i];
          cout<<" ";
          list<int>::iterator liit=compIRADcyBr.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=compIRADcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNm_compIRADcyBr[i]!="")
            {
              cout<<"  Alias for the intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_compIRADcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_compIRADcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the intermediate-resonance-allowed decay branch is set to be \""<<nm_compIRADcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_compIRADcyBr[i]=nm_compIRADcyBr;
            }
          if(m_vNIntStrusToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNIntStrusToBePrtdMax[i]<<endl;
            }
          else
            {
              if(m_vbsLevStdOut==true) cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          cout<<endl;
        }
    }

  if(m_vVPid_sigDcyTr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal decay trees are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal decay trees:"<<endl<<endl;
      char nm_sigDcyTr[20];
      for(unsigned int i=0;i<m_vVPid_sigDcyTr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigDcyTr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigDcyTr[i][j]);
              if(m_pidTxtPnmMap[m_vVPid_sigDcyTr[i][j]].size()<7)  cout<<"\t\t\t";
              else if(m_pidTxtPnmMap[m_vVPid_sigDcyTr[i][j]].size()<15) cout<<"\t\t";
              else cout<<"\t";
              cout<<setiosflags(ios::right)<<setw(3)<<m_vVMidx_sigDcyTr[i][j]<<resetiosflags(ios::adjustfield)<<endl;
	    }
          if(m_vNm_sigDcyTr[i]!="")
            {
              cout<<"  Alias for the signal decay tree is set to be \""<<m_vNm_sigDcyTr[i]<<"\" for the branch value of the topology tag \"nameSigDcyTr\"."<<endl;
            }
          else
            {
              sprintf(nm_sigDcyTr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal decay tree is set to be \""<<nm_sigDcyTr<<"\" for the branch value of the topology tag \"nameSigDcyTr\" (default)."<<endl;
            }
          cout<<endl;
	}
      if(m_sigDcyIFStsUnderSigDcyTr==true)
        {               
          cout<<"  The signal decay initial-final states in the output pdf file are put under their respective signal decay trees."<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The signal decay final states in the output pdf file are put in a column next to that for signal decay trees (default)."<<endl;
        }
      if(m_optIdxAndMidxOfSigDcyBrInSigDcyTr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal decay trees are output to the pdf file."<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal decay trees are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;

      m_vSigDcyTr.clear(); m_vCcSigDcyTr.clear();
      vector< list<int> > sigDcyTr, ccSigDcyTr;
      m_vISigDcyTr.clear(); m_vICcSigDcyTr.clear();
      m_vNSigDcyTr.clear(); m_vNCcSigDcyTr.clear(); 
      m_vSigDcyIFSts_tr.clear(); m_vCcSigDcyIFSts_tr.clear();
      list<int> sigDcyIFSts_tr, ccSigDcyIFSts_tr;
      m_vISigDcyIFSts_tr.clear(); m_vICcSigDcyIFSts_tr.clear();
      m_vNSigDcyIFSts_tr.clear(); m_vNCcSigDcyIFSts_tr.clear();
      m_iSigDcyTrISigDcyIFSts_trMap.clear(); m_iSigDcyTrICcSigDcyIFSts_trMap.clear();
      vector<int> vPid_ccSigDcyTr;
      vector<int> vMidx_ccSigDcyTr;
      int iSigDcyIFSts_tr, iCcSigDcyIFSts_tr;
      for(unsigned int i=0;i<m_vVPid_sigDcyTr.size();i++)
        {
          sortPs(m_vVPid_sigDcyTr[i],m_vVMidx_sigDcyTr[i]);
          sigDcyTr.clear();      
          getDcyTr(m_vVPid_sigDcyTr[i],m_vVMidx_sigDcyTr[i],sigDcyTr);
          sigDcyIFSts_tr.clear();
          getDcyIFSts(m_vVPid_sigDcyTr[i],m_vVMidx_sigDcyTr[i],sigDcyIFSts_tr);
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigDcyTr.size();j++)
            {
              if(sigDcyTr==m_vSigDcyTr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay tree is same as the "<<j+1<<ordNumSufj<<" signal decay tree!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);    
                }
              else if(m_ccSwitch==true&&m_vICcSigDcyTr[j]!=0&&sigDcyTr==m_vCcSigDcyTr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay tree is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal decay tree!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }
          m_vSigDcyTr.push_back(sigDcyTr);
          m_vISigDcyTr.push_back(m_vSigDcyTr.size()-1);
          m_vNSigDcyTr.push_back(0);          
          if(m_ccSwitch==true)
            {
              vPid_ccSigDcyTr.clear();
              vMidx_ccSigDcyTr.clear();
              for(unsigned int j=0;j<m_vVPid_sigDcyTr[i].size();j++) vPid_ccSigDcyTr.push_back(getCcPid(m_vVPid_sigDcyTr[i][j]));
              vMidx_ccSigDcyTr=m_vVMidx_sigDcyTr[i];
              sortPs(vPid_ccSigDcyTr,vMidx_ccSigDcyTr);
              ccSigDcyTr.clear();
              getDcyTr(vPid_ccSigDcyTr,vMidx_ccSigDcyTr,ccSigDcyTr);
              m_vCcSigDcyTr.push_back(ccSigDcyTr);
              if(ccSigDcyTr==sigDcyTr) m_vICcSigDcyTr.push_back(0);
              else m_vICcSigDcyTr.push_back(1);
              m_vNCcSigDcyTr.push_back(0);
            }

          iSigDcyIFSts_tr=-1; // If the variable is still equal to -1 after the following loop, then the signal decay initial-final states is a new signal decay initial-final states.
          for(unsigned int j=0;j<m_vSigDcyIFSts_tr.size();j++)
            {
              if(sigDcyIFSts_tr==m_vSigDcyIFSts_tr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Infor: The initial-final state of the "<<i+1<<ordNumSufi<<" signal decay tree is same as that of the "<<j+1<<ordNumSufj<<" signal decay tree."<<endl<<endl;
                  iSigDcyIFSts_tr=j;
                  if(m_ccSwitch==true) iCcSigDcyIFSts_tr=m_vICcSigDcyIFSts_tr[j];
                  break;
                }
              else if(m_ccSwitch==true&&m_vICcSigDcyIFSts_tr[j]!=0&&sigDcyIFSts_tr==m_vCcSigDcyIFSts_tr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Infor: The initial-final state of the "<<i+1<<ordNumSufi<<" signal decay tree is same as that of the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal decay tree."<<endl<<endl;
                  iSigDcyIFSts_tr=j;
                  iCcSigDcyIFSts_tr=-1;
                  break;
                }
            }
          if(iSigDcyIFSts_tr==-1)
            {
              iSigDcyIFSts_tr=m_vSigDcyIFSts_tr.size();
              m_vSigDcyIFSts_tr.push_back(sigDcyIFSts_tr);
              m_vISigDcyIFSts_tr.push_back(m_vSigDcyIFSts_tr.size()-1);
              m_vNSigDcyIFSts_tr.push_back(0);
              if(m_ccSwitch==true)
                {
                  ccSigDcyIFSts_tr.clear();
                  getDcyIFSts(vPid_ccSigDcyTr,vMidx_ccSigDcyTr,ccSigDcyIFSts_tr);
                  m_vCcSigDcyIFSts_tr.push_back(ccSigDcyIFSts_tr);
                  if(ccSigDcyIFSts_tr==sigDcyIFSts_tr) iCcSigDcyIFSts_tr=0;
                  else iCcSigDcyIFSts_tr=1;
                  m_vICcSigDcyIFSts_tr.push_back(iCcSigDcyIFSts_tr);
                  m_vNCcSigDcyIFSts_tr.push_back(0);
                }
            }
          m_iSigDcyTrISigDcyIFSts_trMap[m_vSigDcyTr.size()-1]=iSigDcyIFSts_tr;
          if(m_ccSwitch==true) m_iSigDcyTrICcSigDcyIFSts_trMap[m_vSigDcyTr.size()-1]=iCcSigDcyIFSts_tr;   
        }

      cout<<"i.e.:"<<endl<<endl;
      vector<int> vIMSigDcyBr;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigDcyTr.size();i++)
        { 
          sigDcyTr.clear();
          sigDcyTr=m_vSigDcyTr[i];
          getVIMDcyBr(sigDcyTr,vIMSigDcyBr);
          for(unsigned int j=0;j<sigDcyTr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigDcyTr[j];
              cout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              // The condition "j==0" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&(*liit)==m_pidOfISt2)||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(cout,"TxtPnm",(*liit));
                }
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              cout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }
          if(m_vNm_sigDcyTr[i]!="")
            {
              cout<<"  Alias for the signal decay tree is set to be \""<<m_vNm_sigDcyTr[i]<<"\" for the branch value of the topology tag \"nameSigDcyTr\"."<<endl;
            }
          else
            {
              sprintf(nm_sigDcyTr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal decay tree is set to be \""<<nm_sigDcyTr<<"\" for the branch value of the topology tag \"nameSigDcyTr\" (default)."<<endl;
              m_vNm_sigDcyTr[i]=nm_sigDcyTr;
            }
          cout<<endl;
        }
      if(m_sigDcyIFStsUnderSigDcyTr==true)
        {
          cout<<"  The signal decay initial-final states in the output pdf file are put under their respective signal decay trees."<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The signal decay final states in the output pdf file are put in a column next to that for signal decay trees (default)."<<endl;
        }   
      if(m_optIdxAndMidxOfSigDcyBrInSigDcyTr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal decay trees are output to the pdf file."<<endl;
        }   
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal decay trees are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;

      m_iSigDcyTrIDcyTrMap.clear();
      m_iSigDcyIFSts_trIDcyIFStsMap.clear();
    }

  if(m_vVPid_sigDcyIFSts.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal decay initial-final states are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal decay initial-final states:"<<endl<<endl;
      char nm_sigDcyIFSts[20];
      for(unsigned int i=0;i<m_vVPid_sigDcyIFSts.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigDcyIFSts[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigDcyIFSts[i][j]);
              cout<<endl;
	    }
          if(m_vNm_sigDcyIFSts[i]!="")
            {
              cout<<"  Alias for the signal decay initial-final states is set to be \""<<m_vNm_sigDcyIFSts[i]<<"\" for the branch value of the topology tag \"nameSigDcyIFSts\"."<<endl;
            }
          else
            {
              sprintf(nm_sigDcyIFSts, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal decay initial-final states is set to be \""<<nm_sigDcyIFSts<<"\" for the branch value of the topology tag \"nameSigDcyIFSts\" (default)."<<endl;
            }
          cout<<endl;
	}
      cout<<endl;

      m_vSigDcyIFSts.clear(); m_vCcSigDcyIFSts.clear();
      list<int> sigDcyIFSts, ccSigDcyIFSts;
      m_vISigDcyIFSts.clear(); m_vICcSigDcyIFSts.clear();
      m_vNSigDcyIFSts.clear(); m_vNCcSigDcyIFSts.clear();
      for(unsigned int i=0;i<m_vVPid_sigDcyIFSts.size();i++)
        {
          sigDcyIFSts.clear();
          for(unsigned int j=1;j<m_vVPid_sigDcyIFSts[i].size();j++) sigDcyIFSts.push_back(m_vVPid_sigDcyIFSts[i][j]);
          sortByPidAndPchrg(sigDcyIFSts);
          if(m_vVPid_sigDcyIFSts[i][0]!=m_pidOfISt)
            {
              sigDcyIFSts.push_front(m_vVPid_sigDcyIFSts[i][0]);
            }
          else
            {
              sigDcyIFSts.push_front(m_pidOfISt1);
              sigDcyIFSts.push_front(m_pidOfISt2);
            }
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigDcyIFSts.size();j++)
            {
              if(sigDcyIFSts==m_vSigDcyIFSts[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay initial-final state is same as the "<<j+1<<ordNumSufj<<" signal decay initial-final state!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcSigDcyIFSts[j]!=0&&sigDcyIFSts==m_vCcSigDcyIFSts[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay initial-final state is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal decay initial-final state!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }               
            }

          m_vSigDcyIFSts.push_back(sigDcyIFSts);
          m_vISigDcyIFSts.push_back(m_vSigDcyIFSts.size()-1);
          m_vNSigDcyIFSts.push_back(0);
          if(m_ccSwitch==true)
            {
              ccSigDcyIFSts.clear();
              list<int>::iterator liit=sigDcyIFSts.begin();
              if((*liit)==m_pidOfISt2) liit++;
              for(liit++;liit!=sigDcyIFSts.end();liit++) ccSigDcyIFSts.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigDcyIFSts);
              liit=sigDcyIFSts.begin();
              if((*liit)==m_pidOfISt2)
                {
                  ccSigDcyIFSts.push_front(m_pidOfISt1);
                  ccSigDcyIFSts.push_front(m_pidOfISt2);
                }
              else
                {
                  ccSigDcyIFSts.push_front(getCcPid((*liit)));
                }
              m_vCcSigDcyIFSts.push_back(ccSigDcyIFSts);
              if(ccSigDcyIFSts==sigDcyIFSts) m_vICcSigDcyIFSts.push_back(0);
              else m_vICcSigDcyIFSts.push_back(1);
              m_vNCcSigDcyIFSts.push_back(0);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vSigDcyIFSts.size();i++)
        {
          sigDcyIFSts.clear();
          sigDcyIFSts=m_vSigDcyIFSts[i];
          cout<<" ";
          list<int>::iterator liit=sigDcyIFSts.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=sigDcyIFSts.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNm_sigDcyIFSts[i]!="")
            {
              cout<<"  Alias for the signal decay initial-final states is set to be \""<<m_vNm_sigDcyIFSts[i]<<"\" for the branch value of the topology tag \"nameSigDcyIFSts\"."<<endl;
            }
          else
            { 
              sprintf(nm_sigDcyIFSts, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal decay initial-final states is set to be \""<<nm_sigDcyIFSts<<"\" for the branch value of the topology tag \"nameSigDcyIFSts\" (default)."<<endl;
              m_vNm_sigDcyIFSts[i]=nm_sigDcyIFSts;
            }
          cout<<endl;
        }

      m_iSigDcyIFStsIDcyIFStsMap.clear();
    }

  if(m_vPid_sigP.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal particles are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal particles:"<<endl<<endl;
      char nm_sigP[20];
      for(unsigned int i=0;i<m_vPid_sigP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_sigP[i]);
          // if(m_pidTxtPnmMap[m_vPid_sigP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_sigP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_sigP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNm_sigP[i]!="")
            {
              cout<<"  Alias for the signal particle is set to be \""<<m_vNm_sigP[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigP, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal particle is set to be \""<<nm_sigP<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_sigP[i]=nm_sigP;
            }
          cout<<endl;
        }
      cout<<endl;

      m_vISigP.clear();
      m_vNSigP.clear();
      if(m_ccSwitch==true)
        {
          m_vPid_ccSigP.clear();
          m_vICcSigP.clear();
          m_vNCcSigP.clear();
        }
      for(unsigned int i=0;i<m_vPid_sigP.size();i++)
        { 
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<i;j++)
            {
              if(m_vPid_sigP[i]==m_vPid_sigP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal particle is same as the "<<j+1<<ordNumSufj<<" signal particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcSigP[j]!=0&&m_vPid_sigP[i]==m_vPid_ccSigP[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal particle is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal particle!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vISigP.push_back(i);
          m_vNSigP.push_back(0);
          if(m_ccSwitch==true)
            {
              m_vPid_ccSigP.push_back(getCcPid(m_vPid_sigP[i]));
              if(m_vPid_ccSigP[i]==m_vPid_sigP[i]) m_vICcSigP.push_back(0);
              else m_vICcSigP.push_back(1);
              m_vNCcSigP.push_back(0);
            }
        }
    }

  if(m_vVPid_sigDcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal decay branches:"<<endl<<endl;
      char nm_sigDcyBr[20];
      for(unsigned int i=0;i<m_vVPid_sigDcyBr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigDcyBr[i][j]);
              cout<<endl;
	    }
          if(m_vNm_sigDcyBr[i]!="")
            {
              cout<<"  Alias for the signal decay branch is set to be \""<<m_vNm_sigDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal decay branch is set to be \""<<nm_sigDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          cout<<endl;
	}
      cout<<endl;

      m_vSigDcyBr.clear(); m_vCcSigDcyBr.clear();
      list<int> sigDcyBr, ccSigDcyBr;
      m_vISigDcyBr.clear(); m_vICcSigDcyBr.clear();
      m_vNSigDcyBr.clear(); m_vNCcSigDcyBr.clear();
      for(unsigned int i=0;i<m_vVPid_sigDcyBr.size();i++)
        {
          sigDcyBr.clear();
          for(unsigned int j=1;j<m_vVPid_sigDcyBr[i].size();j++) sigDcyBr.push_back(m_vVPid_sigDcyBr[i][j]);
          sortByPidAndPchrg(sigDcyBr);
          if(m_vVPid_sigDcyBr[i][0]!=m_pidOfISt)
            {
              sigDcyBr.push_front(m_vVPid_sigDcyBr[i][0]);
            }
          else
            {
              sigDcyBr.push_front(m_pidOfISt1);
              sigDcyBr.push_front(m_pidOfISt2);
            }

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigDcyBr.size();j++)
            {
              if(sigDcyBr==m_vSigDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay branch is same as the "<<j+1<<ordNumSufj<<" signal decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcSigDcyBr[j]!=0&&sigDcyBr==m_vCcSigDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay branch is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vSigDcyBr.push_back(sigDcyBr);
          m_vISigDcyBr.push_back(m_vSigDcyBr.size()-1);
          m_vNSigDcyBr.push_back(0);
          if(m_ccSwitch==true)
            {
              ccSigDcyBr.clear();
              list<int>::iterator liit=sigDcyBr.begin();
              if((*liit)==m_pidOfISt2) liit++;
              for(liit++;liit!=sigDcyBr.end();liit++) ccSigDcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigDcyBr);
              liit=sigDcyBr.begin();
              if((*liit)!=m_pidOfISt2)
                {
                  ccSigDcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  ccSigDcyBr.push_front(m_pidOfISt1);
                  ccSigDcyBr.push_front(m_pidOfISt2); 
                }
              m_vCcSigDcyBr.push_back(ccSigDcyBr);
              if(ccSigDcyBr==sigDcyBr) m_vICcSigDcyBr.push_back(0);
              else m_vICcSigDcyBr.push_back(1);
              m_vNCcSigDcyBr.push_back(0);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vSigDcyBr.size();i++)
        {
          sigDcyBr.clear();
          sigDcyBr=m_vSigDcyBr[i];
          cout<<" ";
          list<int>::iterator liit=sigDcyBr.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNm_sigDcyBr[i]!="")
            {
              cout<<"  Alias for the signal decay branch is set to be \""<<m_vNm_sigDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal decay branch is set to be \""<<nm_sigDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_sigDcyBr[i]=nm_sigDcyBr;
            }
          cout<<endl;
        }
    }

  if(m_vVPid_sigIncDcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal inclusive decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal inclusive decay branches:"<<endl<<endl;
      char nm_sigIncDcyBr[20];
      for(unsigned int i=0;i<m_vVPid_sigIncDcyBr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigIncDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigIncDcyBr[i][j]);
              cout<<endl;
	    }
          if(m_vNm_sigIncDcyBr[i]!="")
            {
              cout<<"  Alias for the signal inclusive decay branch is set to be \""<<m_vNm_sigIncDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIncDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal inclusive decay branch is set to be \""<<nm_sigIncDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          cout<<endl;
	}
      cout<<endl;

      m_vSigIncDcyBr.clear(); m_vCcSigIncDcyBr.clear();
      list<int> sigIncDcyBr, ccSigIncDcyBr;
      m_vISigIncDcyBr.clear(); m_vICcSigIncDcyBr.clear();
      m_vNSigIncDcyBr.clear(); m_vNCcSigIncDcyBr.clear();
      for(unsigned int i=0;i<m_vVPid_sigIncDcyBr.size();i++)
        {
          sigIncDcyBr.clear();
          for(unsigned int j=1;j<m_vVPid_sigIncDcyBr[i].size();j++) sigIncDcyBr.push_back(m_vVPid_sigIncDcyBr[i][j]);
          sortByPidAndPchrg(sigIncDcyBr);
          if(m_vVPid_sigIncDcyBr[i][0]!=m_pidOfISt)
            {
              sigIncDcyBr.push_front(m_vVPid_sigIncDcyBr[i][0]);
            }
          else
            {
              sigIncDcyBr.push_front(m_pidOfISt1);
              sigIncDcyBr.push_front(m_pidOfISt2);
            }

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigIncDcyBr.size();j++)
            {
              if(sigIncDcyBr==m_vSigIncDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive decay branch is same as the "<<j+1<<ordNumSufj<<" signal inclusive decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcSigIncDcyBr[j]!=0&&sigIncDcyBr==m_vCcSigIncDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive decay branch is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal inclusive decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vSigIncDcyBr.push_back(sigIncDcyBr);
          m_vISigIncDcyBr.push_back(m_vSigIncDcyBr.size()-1);
          m_vNSigIncDcyBr.push_back(0);
          if(m_ccSwitch==true)
            {
              ccSigIncDcyBr.clear();
              list<int>::iterator liit=sigIncDcyBr.begin();
              if((*liit)==m_pidOfISt2) liit++;
              for(liit++;liit!=sigIncDcyBr.end();liit++) ccSigIncDcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigIncDcyBr);
              liit=sigIncDcyBr.begin();
              if((*liit)!=m_pidOfISt2)
                {
                  ccSigIncDcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  ccSigIncDcyBr.push_front(m_pidOfISt1);
                  ccSigIncDcyBr.push_front(m_pidOfISt2); 
                }
              m_vCcSigIncDcyBr.push_back(ccSigIncDcyBr);
              if(ccSigIncDcyBr==sigIncDcyBr) m_vICcSigIncDcyBr.push_back(0);
              else m_vICcSigIncDcyBr.push_back(1);
              m_vNCcSigIncDcyBr.push_back(0);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vSigIncDcyBr.size();i++)
        {
          sigIncDcyBr.clear();
          sigIncDcyBr=m_vSigIncDcyBr[i];
          cout<<" ";
          list<int>::iterator liit=sigIncDcyBr.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=sigIncDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<" + anything";
          cout<<endl;
          if(m_vNm_sigIncDcyBr[i]!="")
            {
              cout<<"  Alias for the signal inclusive decay branch is set to be \""<<m_vNm_sigIncDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIncDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal inclusive decay branch is set to be \""<<nm_sigIncDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_sigIncDcyBr[i]=nm_sigIncDcyBr;
            }
          cout<<endl;
        }
    }

  if(m_vVPid_sigCascDcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal cascade decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal cascade decay branches:"<<endl<<endl;
      char nm_sigCascDcyBr[20];
      for(unsigned int i=0;i<m_vVPid_sigCascDcyBr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigCascDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigCascDcyBr[i][j]);
              if(m_pidTxtPnmMap[m_vVPid_sigCascDcyBr[i][j]].size()<7)  cout<<"\t\t\t";
              else if(m_pidTxtPnmMap[m_vVPid_sigCascDcyBr[i][j]].size()<15) cout<<"\t\t";
              else cout<<"\t";
              cout<<setiosflags(ios::right)<<setw(3)<<m_vVMidx_sigCascDcyBr[i][j]<<resetiosflags(ios::adjustfield)<<endl;
	    }
          if(m_vNm_sigCascDcyBr[i]!="")
            {
              cout<<"  Alias for the signal cascade decay branch is set to be \""<<m_vNm_sigCascDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigCascDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal cascade decay branch is set to be \""<<nm_sigCascDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          cout<<endl;
	}
      if(m_optIdxAndMidxOfSigDcyBrInSigCascDcyBr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal cascade decay branches are output to the pdf file."<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal cascade decay branches are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;

      m_vSigCascDcyBr.clear(); m_vCcSigCascDcyBr.clear();
      vector< list<int> > sigCascDcyBr, ccSigCascDcyBr;
      m_vVSigCascDcyBrIdxOfHead.clear(); m_vVCcSigCascDcyBrIdxOfHead.clear();
      vector<int> vSigCascDcyBrIdxOfHead, vCcSigCascDcyBrIdxOfHead; 
      m_vVSigCascDcyBrMidxOfHead.clear(); m_vVCcSigCascDcyBrMidxOfHead.clear();
      vector<int> vSigCascDcyBrMidxOfHead, vCcSigCascDcyBrMidxOfHead;
      m_vISigCascDcyBr.clear(); m_vICcSigCascDcyBr.clear();
      m_vNSigCascDcyBr.clear(); m_vNCcSigCascDcyBr.clear();
      vector<int> vPid_ccSigCascDcyBr, vMidx_ccSigCascDcyBr;
      for(unsigned int i=0;i<m_vVPid_sigCascDcyBr.size();i++)
        {
          sortPs(m_vVPid_sigCascDcyBr[i],m_vVMidx_sigCascDcyBr[i]);
          sigCascDcyBr.clear();      
          vSigCascDcyBrIdxOfHead.clear();
          vSigCascDcyBrMidxOfHead.clear();
          getDcyTr(m_vVPid_sigCascDcyBr[i],m_vVMidx_sigCascDcyBr[i],sigCascDcyBr,&vSigCascDcyBrIdxOfHead,&vSigCascDcyBrMidxOfHead);

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigCascDcyBr.size();j++)
            {
              if(sigCascDcyBr==m_vSigCascDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal cascade decay branch is same as the "<<j+1<<ordNumSufj<<" signal cascade decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);    
                }
              else if(m_ccSwitch==true&&m_vICcSigCascDcyBr[j]!=0&&sigCascDcyBr==m_vCcSigCascDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal cascade decay branch is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal cascade decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }                
            }

          m_vSigCascDcyBr.push_back(sigCascDcyBr);
          m_vVSigCascDcyBrIdxOfHead.push_back(vSigCascDcyBrIdxOfHead);
          m_vVSigCascDcyBrMidxOfHead.push_back(vSigCascDcyBrMidxOfHead);
          m_vISigCascDcyBr.push_back(m_vSigCascDcyBr.size()-1);
          m_vNSigCascDcyBr.push_back(0);
          if(m_ccSwitch==true)
            {
              vPid_ccSigCascDcyBr.clear();
              vMidx_ccSigCascDcyBr.clear();
              for(unsigned int j=0;j<m_vVPid_sigCascDcyBr[i].size();j++) vPid_ccSigCascDcyBr.push_back(getCcPid(m_vVPid_sigCascDcyBr[i][j])); 
              vMidx_ccSigCascDcyBr=m_vVMidx_sigCascDcyBr[i];
              sortPs(vPid_ccSigCascDcyBr,vMidx_ccSigCascDcyBr);
              ccSigCascDcyBr.clear();
              vCcSigCascDcyBrIdxOfHead.clear();
              vCcSigCascDcyBrMidxOfHead.clear();
              getDcyTr(vPid_ccSigCascDcyBr,vMidx_ccSigCascDcyBr,ccSigCascDcyBr,&vCcSigCascDcyBrIdxOfHead,&vCcSigCascDcyBrMidxOfHead);
              m_vCcSigCascDcyBr.push_back(ccSigCascDcyBr);
              m_vVCcSigCascDcyBrIdxOfHead.push_back(vCcSigCascDcyBrIdxOfHead);
              m_vVCcSigCascDcyBrMidxOfHead.push_back(vCcSigCascDcyBrMidxOfHead);
              if(ccSigCascDcyBr==sigCascDcyBr) m_vICcSigCascDcyBr.push_back(0);
              else m_vICcSigCascDcyBr.push_back(1);
              m_vNCcSigCascDcyBr.push_back(0);
            }          
        }

      cout<<"i.e.:"<<endl<<endl;
      vector<int> vIMSigDcyBr;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigCascDcyBr.size();i++)
        { 
          sigCascDcyBr.clear();
          sigCascDcyBr=m_vSigCascDcyBr[i];
          getVIMDcyBr(sigCascDcyBr,vIMSigDcyBr);
          vSigCascDcyBrIdxOfHead=m_vVSigCascDcyBrIdxOfHead[i];
          for(unsigned int j=0;j<sigCascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigCascDcyBr[j];
              cout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              if(j==0&&(*liit)==m_pidOfISt2)
              {
                liit++;
                writePnmFromPid(cout,"TxtPnm",(*liit));
              }
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              cout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }
          if(m_vNm_sigCascDcyBr[i]!="")
            {
              cout<<"  Alias for the signal cascade decay branch is set to be \""<<m_vNm_sigCascDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigCascDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal cascade decay branch is set to be \""<<nm_sigCascDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_sigCascDcyBr[i]=nm_sigCascDcyBr;
            }
          cout<<endl;
        }
      if(m_optIdxAndMidxOfSigDcyBrInSigCascDcyBr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal cascade decay branches are output to the pdf file."<<endl;
        } 
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal cascade decay branches are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;
    }

  if(m_vVPid_sigIncCascDcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal inclusive cascade decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal inclusive cascade decay branches:"<<endl<<endl;
      char nm_sigIncCascDcyBr[20];
      for(unsigned int i=0;i<m_vVPid_sigIncCascDcyBr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigIncCascDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigIncCascDcyBr[i][j]);
              if(m_pidTxtPnmMap[m_vVPid_sigIncCascDcyBr[i][j]].size()<7)  cout<<"\t\t\t";
              else if(m_pidTxtPnmMap[m_vVPid_sigIncCascDcyBr[i][j]].size()<15) cout<<"\t\t";
              else cout<<"\t";
              cout<<setiosflags(ios::right)<<setw(3)<<m_vVMidx_sigIncCascDcyBr[i][j]<<resetiosflags(ios::adjustfield)<<endl;
	    }
          if(m_vNm_sigIncCascDcyBr[i]!="")
            {
              cout<<"  Alias for the signal inclusive cascade decay branch is set to be \""<<m_vNm_sigIncCascDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIncCascDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal inclusive cascade decay branch is set to be \""<<nm_sigIncCascDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          cout<<endl;
	}
      if(m_optIdxAndMidxOfSigDcyBrInSigIncCascDcyBr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive cascade decay branches are output to the pdf file."<<endl;
        } 
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive cascade decay branches are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;

      m_vSigIncCascDcyBr.clear(); m_vCcSigIncCascDcyBr.clear();
      vector< list<int> > sigIncCascDcyBr, ccSigIncCascDcyBr;
      m_vVSigIncCascDcyBrIdxOfHead.clear(); m_vVCcSigIncCascDcyBrIdxOfHead.clear();
      vector<int> vSigIncCascDcyBrIdxOfHead, vCcSigIncCascDcyBrIdxOfHead; 
      m_vVSigIncCascDcyBrMidxOfHead.clear(); m_vVCcSigIncCascDcyBrMidxOfHead.clear();
      vector<int> vSigIncCascDcyBrMidxOfHead, vCcSigIncCascDcyBrMidxOfHead;
      m_vVIIncSigIncCascDcyBr.clear();
      vector<int> vIIncSigIncCascDcyBr;
      m_vISigIncCascDcyBr.clear(); m_vICcSigIncCascDcyBr.clear();
      m_vNSigIncCascDcyBr.clear(); m_vNCcSigIncCascDcyBr.clear();
      vector<int> vPid_ccSigIncCascDcyBr, vMidx_ccSigIncCascDcyBr;
      for(unsigned int i=0;i<m_vVPid_sigIncCascDcyBr.size();i++)
        {
          sortPs(m_vVPid_sigIncCascDcyBr[i],m_vVMidx_sigIncCascDcyBr[i]);
          sigIncCascDcyBr.clear();      
          vSigIncCascDcyBrIdxOfHead.clear();
          vSigIncCascDcyBrMidxOfHead.clear();
          vIIncSigIncCascDcyBr.clear(); 
          getDcyTr(m_vVPid_sigIncCascDcyBr[i],m_vVMidx_sigIncCascDcyBr[i],sigIncCascDcyBr,&vSigIncCascDcyBrIdxOfHead,&vSigIncCascDcyBrMidxOfHead,&vIIncSigIncCascDcyBr);

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigIncCascDcyBr.size();j++)
            {
              if(sigIncCascDcyBr==m_vSigIncCascDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive cascade decay branch is same as the "<<j+1<<ordNumSufj<<" signal inclusive cascade decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);    
                }
              else if(m_ccSwitch==true&&m_vICcSigIncCascDcyBr[j]!=0&&sigIncCascDcyBr==m_vCcSigIncCascDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive cascade decay branch is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal inclusive cascade decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }                
            }

          m_vSigIncCascDcyBr.push_back(sigIncCascDcyBr);
          m_vVSigIncCascDcyBrIdxOfHead.push_back(vSigIncCascDcyBrIdxOfHead);
          m_vVSigIncCascDcyBrMidxOfHead.push_back(vSigIncCascDcyBrMidxOfHead);
          m_vVIIncSigIncCascDcyBr.push_back(vIIncSigIncCascDcyBr);  
          m_vISigIncCascDcyBr.push_back(m_vSigIncCascDcyBr.size()-1);
          m_vNSigIncCascDcyBr.push_back(0);
          if(m_ccSwitch==true)
            {
              vPid_ccSigIncCascDcyBr.clear();
              vMidx_ccSigIncCascDcyBr.clear();
              for(unsigned int j=0;j<m_vVPid_sigIncCascDcyBr[i].size();j++) vPid_ccSigIncCascDcyBr.push_back(getCcPid(m_vVPid_sigIncCascDcyBr[i][j])); 
              vMidx_ccSigIncCascDcyBr=m_vVMidx_sigIncCascDcyBr[i];
              sortPs(vPid_ccSigIncCascDcyBr,vMidx_ccSigIncCascDcyBr);
              ccSigIncCascDcyBr.clear();
              vCcSigIncCascDcyBrIdxOfHead.clear();
              vCcSigIncCascDcyBrMidxOfHead.clear();
              getDcyTr(vPid_ccSigIncCascDcyBr,vMidx_ccSigIncCascDcyBr,ccSigIncCascDcyBr,&vCcSigIncCascDcyBrIdxOfHead,&vCcSigIncCascDcyBrMidxOfHead);
              m_vCcSigIncCascDcyBr.push_back(ccSigIncCascDcyBr);
              m_vVCcSigIncCascDcyBrIdxOfHead.push_back(vCcSigIncCascDcyBrIdxOfHead);
              m_vVCcSigIncCascDcyBrMidxOfHead.push_back(vCcSigIncCascDcyBrMidxOfHead);
              if(ccSigIncCascDcyBr==sigIncCascDcyBr) m_vICcSigIncCascDcyBr.push_back(0);
              else m_vICcSigIncCascDcyBr.push_back(1);
              m_vNCcSigIncCascDcyBr.push_back(0);
            }          
        }

      cout<<"i.e.:"<<endl<<endl;
      vector<int> vIMSigDcyBr;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigIncCascDcyBr.size();i++)
        { 
          sigIncCascDcyBr.clear();
          sigIncCascDcyBr=m_vSigIncCascDcyBr[i];
          getVIMDcyBr(sigIncCascDcyBr,vIMSigDcyBr);
          vSigIncCascDcyBrIdxOfHead=m_vVSigIncCascDcyBrIdxOfHead[i];
          for(unsigned int j=0;j<sigIncCascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncCascDcyBr[j];
              cout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(cout,"TxtPnm",(*liit));
                }
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncCascDcyBr[i][j]==1)
                {
                  cout<<" +";
                  writePnmFromPid(cout,"TxtPnm",m_pidOfAnything);
                }
              cout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }
          if(m_vNm_sigIncCascDcyBr[i]!="")
            {
              cout<<"  Alias for the signal inclusive cascade decay branch is set to be \""<<m_vNm_sigIncCascDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIncCascDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal inclusive cascade decay branch is set to be \""<<nm_sigIncCascDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_sigIncCascDcyBr[i]=nm_sigIncCascDcyBr;
            }
          cout<<endl;
        }
      if(m_optIdxAndMidxOfSigDcyBrInSigIncCascDcyBr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive cascade decay branches are output to the pdf file."<<endl;
        } 
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive cascade decay branches are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;
    }

  if(m_vVPid_sigIRADcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal intermediate-resonance-allowed decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal intermediate-resonance-allowed decay branches:"<<endl<<endl;
      char nm_sigIRADcyBr[20];
      for(unsigned int i=0;i<m_vVPid_sigIRADcyBr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigIRADcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigIRADcyBr[i][j]);
              cout<<endl;
	    }
          if(m_vNm_sigIRADcyBr[i]!="")
            {
              cout<<"  Alias for the signal intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_sigIRADcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIRADcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal intermediate-resonance-allowed decay branch is set to be \""<<nm_sigIRADcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          cout<<endl;
	}
      cout<<endl;

      m_vSigIRADcyBr.clear(); m_vCcSigIRADcyBr.clear();
      list<int> sigIRADcyBr, ccSigIRADcyBr;
      m_vISigIRADcyBr.clear(); m_vICcSigIRADcyBr.clear();
      m_vNSigIRADcyBr.clear(); m_vNCcSigIRADcyBr.clear();
      for(unsigned int i=0;i<m_vVPid_sigIRADcyBr.size();i++)
        {
          sigIRADcyBr.clear();
          for(unsigned int j=1;j<m_vVPid_sigIRADcyBr[i].size();j++) sigIRADcyBr.push_back(m_vVPid_sigIRADcyBr[i][j]);
          sortByPidAndPchrg(sigIRADcyBr);
          if(m_vVPid_sigIRADcyBr[i][0]!=m_pidOfISt)
            {
              sigIRADcyBr.push_front(m_vVPid_sigIRADcyBr[i][0]);
            }
          else
            {
              sigIRADcyBr.push_front(m_pidOfISt1);
              sigIRADcyBr.push_front(m_pidOfISt2);
            }

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigIRADcyBr.size();j++)
            {
              if(sigIRADcyBr==m_vSigIRADcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal intermediate-resonance-allowed decay branch is same as the "<<j+1<<ordNumSufj<<" signal intermediate-resonance-allowed decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcSigIRADcyBr[j]!=0&&sigIRADcyBr==m_vCcSigIRADcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal intermediate-resonance-allowed decay branch is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal intermediate-resonance-allowed decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
            }

          m_vSigIRADcyBr.push_back(sigIRADcyBr);
          m_vISigIRADcyBr.push_back(m_vSigIRADcyBr.size()-1);
          m_vNSigIRADcyBr.push_back(0);
          if(m_ccSwitch==true)
            {
              ccSigIRADcyBr.clear();
              list<int>::iterator liit=sigIRADcyBr.begin();
              if((*liit)==m_pidOfISt2) liit++;
              for(liit++;liit!=sigIRADcyBr.end();liit++) ccSigIRADcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigIRADcyBr);
              liit=sigIRADcyBr.begin();
              if((*liit)!=m_pidOfISt2)
                {
                  ccSigIRADcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  ccSigIRADcyBr.push_front(m_pidOfISt1);
                  ccSigIRADcyBr.push_front(m_pidOfISt2);
                }

              m_vCcSigIRADcyBr.push_back(ccSigIRADcyBr);
              if(ccSigIRADcyBr==sigIRADcyBr) m_vICcSigIRADcyBr.push_back(0);
              else m_vICcSigIRADcyBr.push_back(1);
              m_vNCcSigIRADcyBr.push_back(0);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vSigIRADcyBr.size();i++)
        {
          sigIRADcyBr.clear();
          sigIRADcyBr=m_vSigIRADcyBr[i];
          cout<<" ";
          list<int>::iterator liit=sigIRADcyBr.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=sigIRADcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNm_sigIRADcyBr[i]!="")
            {
              cout<<"  Alias for the signal intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_sigIRADcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIRADcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal intermediate-resonance-allowed decay branch is set to be \""<<nm_sigIRADcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_sigIRADcyBr[i]=nm_sigIRADcyBr;
            }
          cout<<endl;
        }
    }

  if(m_vVPid_sigIncOrIRACascDcyBr.size()==0)
    {
      if(m_vbsLevStdOut==true) cout<<"No signal inclusive or intermediate-resonance-allowed cascade decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal inclusive or intermediate-resonance-allowed cascade decay branches:"<<endl<<endl;
      char nm_sigIncOrIRACascDcyBr[20];
      for(unsigned int i=0;i<m_vVPid_sigIncOrIRACascDcyBr.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigIncOrIRACascDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigIncOrIRACascDcyBr[i][j]);
              if(m_pidTxtPnmMap[m_vVPid_sigIncOrIRACascDcyBr[i][j]].size()<7)  cout<<"\t\t\t";
              else if(m_pidTxtPnmMap[m_vVPid_sigIncOrIRACascDcyBr[i][j]].size()<15) cout<<"\t\t";
              else cout<<"\t";
              cout<<setiosflags(ios::right)<<setw(3)<<m_vVMidx_sigIncOrIRACascDcyBr[i][j]<<resetiosflags(ios::adjustfield)<<endl;
	    }
          if(m_vNm_sigIncOrIRACascDcyBr[i]!="")
            {
              cout<<"  Alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set to be \""<<m_vNm_sigIncOrIRACascDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIncOrIRACascDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set to be \""<<nm_sigIncOrIRACascDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
            }
          cout<<endl;
	}
      if(m_optIdxAndMidxOfSigDcyBrInSigIncOrIRACascDcyBr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive or intermediate-resonance-allowed cascade decay branches are output to the pdf file."<<endl;
        } 
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive or intermediate-resonance-allowed cascade decay branches are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;

      m_vSigIncOrIRACascDcyBr.clear(); m_vCcSigIncOrIRACascDcyBr.clear();
      vector< list<int> > sigIncOrIRACascDcyBr, ccSigIncOrIRACascDcyBr;
      m_vVSigIncOrIRACascDcyBrIdxOfHead.clear(); m_vVCcSigIncOrIRACascDcyBrIdxOfHead.clear();
      vector<int> vSigIncOrIRACascDcyBrIdxOfHead, vCcSigIncOrIRACascDcyBrIdxOfHead; 
      m_vVSigIncOrIRACascDcyBrMidxOfHead.clear(); m_vVCcSigIncOrIRACascDcyBrMidxOfHead.clear();
      vector<int> vSigIncOrIRACascDcyBrMidxOfHead, vCcSigIncOrIRACascDcyBrMidxOfHead;
      m_vVIIncSigIncOrIRACascDcyBr.clear();
      vector<int> vIIncSigIncOrIRACascDcyBr;
      m_vVIIRASigIncOrIRACascDcyBr.clear();
      vector<int> vIIRASigIncOrIRACascDcyBr;      
      m_vISigIncOrIRACascDcyBr.clear(); m_vICcSigIncOrIRACascDcyBr.clear();
      m_vNSigIncOrIRACascDcyBr.clear(); m_vNCcSigIncOrIRACascDcyBr.clear();
      vector<int> vPid_ccSigIncOrIRACascDcyBr, vMidx_ccSigIncOrIRACascDcyBr;
      for(unsigned int i=0;i<m_vVPid_sigIncOrIRACascDcyBr.size();i++)
        {
          sortPs(m_vVPid_sigIncOrIRACascDcyBr[i],m_vVMidx_sigIncOrIRACascDcyBr[i]);
          sigIncOrIRACascDcyBr.clear();
          vSigIncOrIRACascDcyBrIdxOfHead.clear();
          vSigIncOrIRACascDcyBrMidxOfHead.clear();
          vIIncSigIncOrIRACascDcyBr.clear();
          vIIRASigIncOrIRACascDcyBr.clear();
          getDcyTr(m_vVPid_sigIncOrIRACascDcyBr[i],m_vVMidx_sigIncOrIRACascDcyBr[i],sigIncOrIRACascDcyBr,&vSigIncOrIRACascDcyBrIdxOfHead,&vSigIncOrIRACascDcyBrMidxOfHead,&vIIncSigIncOrIRACascDcyBr,&vIIRASigIncOrIRACascDcyBr);

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigIncOrIRACascDcyBr.size();j++)
            {
              if(sigIncOrIRACascDcyBr==m_vSigIncOrIRACascDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive or intermediate-resonance-allowed cascade decay branch is same as the "<<j+1<<ordNumSufj<<" signal inclusive or intermediate-resonance-allowed cascade decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);    
                }
              else if(m_ccSwitch==true&&m_vICcSigIncOrIRACascDcyBr[j]!=0&&sigIncOrIRACascDcyBr==m_vCcSigIncOrIRACascDcyBr[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive or intermediate-resonance-allowed cascade decay branch is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal inclusive or intermediate-resonance-allowed cascade decay branch!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }                
            }

          m_vSigIncOrIRACascDcyBr.push_back(sigIncOrIRACascDcyBr);
          m_vVSigIncOrIRACascDcyBrIdxOfHead.push_back(vSigIncOrIRACascDcyBrIdxOfHead);
          m_vVSigIncOrIRACascDcyBrMidxOfHead.push_back(vSigIncOrIRACascDcyBrMidxOfHead);
          m_vVIIncSigIncOrIRACascDcyBr.push_back(vIIncSigIncOrIRACascDcyBr);
          m_vVIIRASigIncOrIRACascDcyBr.push_back(vIIRASigIncOrIRACascDcyBr);
          m_vISigIncOrIRACascDcyBr.push_back(m_vSigIncOrIRACascDcyBr.size()-1);
          m_vNSigIncOrIRACascDcyBr.push_back(0);
          if(m_ccSwitch==true)
            {
              vPid_ccSigIncOrIRACascDcyBr.clear();
              vMidx_ccSigIncOrIRACascDcyBr.clear();
              for(unsigned int j=0;j<m_vVPid_sigIncOrIRACascDcyBr[i].size();j++) vPid_ccSigIncOrIRACascDcyBr.push_back(getCcPid(m_vVPid_sigIncOrIRACascDcyBr[i][j])); 
              vMidx_ccSigIncOrIRACascDcyBr=m_vVMidx_sigIncOrIRACascDcyBr[i];
              sortPs(vPid_ccSigIncOrIRACascDcyBr,vMidx_ccSigIncOrIRACascDcyBr);
              ccSigIncOrIRACascDcyBr.clear();
              vCcSigIncOrIRACascDcyBrIdxOfHead.clear();
              vCcSigIncOrIRACascDcyBrMidxOfHead.clear();
              getDcyTr(vPid_ccSigIncOrIRACascDcyBr,vMidx_ccSigIncOrIRACascDcyBr,ccSigIncOrIRACascDcyBr,&vCcSigIncOrIRACascDcyBrIdxOfHead,&vCcSigIncOrIRACascDcyBrMidxOfHead);

              m_vCcSigIncOrIRACascDcyBr.push_back(ccSigIncOrIRACascDcyBr);
              m_vVCcSigIncOrIRACascDcyBrIdxOfHead.push_back(vCcSigIncOrIRACascDcyBrIdxOfHead);
              m_vVCcSigIncOrIRACascDcyBrMidxOfHead.push_back(vCcSigIncOrIRACascDcyBrMidxOfHead);
              if(ccSigIncOrIRACascDcyBr==sigIncOrIRACascDcyBr) m_vICcSigIncOrIRACascDcyBr.push_back(0);
              else m_vICcSigIncOrIRACascDcyBr.push_back(1);
              m_vNCcSigIncOrIRACascDcyBr.push_back(0);
            }          
        }

      cout<<"i.e.:"<<endl<<endl;
      vector<int> vIMSigDcyBr;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBr.size();i++)
        { 
          sigIncOrIRACascDcyBr.clear();
          sigIncOrIRACascDcyBr=m_vSigIncOrIRACascDcyBr[i];
          vSigIncOrIRACascDcyBrIdxOfHead=m_vVSigIncOrIRACascDcyBrIdxOfHead[i];
          getVIMDcyBr(sigIncOrIRACascDcyBr,vIMSigDcyBr);
          for(unsigned int j=0;j<sigIncOrIRACascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncOrIRACascDcyBr[j];
              cout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(cout,"TxtPnm",(*liit));
                }
              if(m_vVIIRASigIncOrIRACascDcyBr[i][j]==1) cout<<" (--> X)";
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncOrIRACascDcyBr[i][j]==1)
                {
                  cout<<" +";
                  writePnmFromPid(cout,"TxtPnm",m_pidOfAnything);
                }
              if(m_vVIIncSigIncOrIRACascDcyBr[i][j]==1&&m_vVIIRASigIncOrIRACascDcyBr[i][j]==1)
                {
                  cout<<endl<<endl;
                  cerr<<"Error: The Branch is not only inclusive but also . Such Branches are not supported in the current version of the \"TopoAna\" program!"<<endl;
                  cerr<<"Infor: If you really need the function, Please contact me (zhouxy@buaa.edu.cn) and then I will try to implement the function for you."<<endl;
                  exit(-1);
                }
              cout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }
          if(m_vNm_sigIncOrIRACascDcyBr[i]!="")
            {
              cout<<"  Alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set to be \""<<m_vNm_sigIncOrIRACascDcyBr[i]<<"\" for the branch names of the topology tags."<<endl;
            }
          else
            {
              sprintf(nm_sigIncOrIRACascDcyBr, "%d", i);
              if(m_vbsLevStdOut==true) cout<<"  Alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set to be \""<<nm_sigIncOrIRACascDcyBr<<"\" for the branch names of the topology tags (default)."<<endl;
              m_vNm_sigIncOrIRACascDcyBr[i]=nm_sigIncOrIRACascDcyBr;
            }
          cout<<endl;
        }
      if(m_optIdxAndMidxOfSigDcyBrInSigIncOrIRACascDcyBr==true)
        {
          cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive or intermediate-resonance-allowed cascade decay branches are output to the pdf file."<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"  The indices and mother indices of the signal decay branches in the signal inclusive or intermediate-resonance-allowed cascade decay branches are not output to the pdf file (default)."<<endl;
        }
      cout<<endl;
    }

  bool haveTopoAnaTasks=false;
  if((m_compAnaOfDcyTrs==true)||(m_compAnaOfDcyIFSts==true)||(m_vPid_compDcyBrP.size()!=0)||(m_vPid_compCascDcyBrP.size()!=0)||(m_vPid_compDcyFStP.size()!=0)||(m_vPid_compProdBrP.size()!=0)||(m_vPid_compMP.size()!=0)||(m_vVPid_compIncDcyBr.size()!=0)||(m_vVPid_compIRADcyBr.size()!=0)||(m_vVPid_sigDcyTr.size()!=0)||(m_vVPid_sigDcyIFSts.size()!=0)||(m_vPid_sigP.size()!=0)||(m_vVPid_sigDcyBr.size()!=0)||(m_vVPid_sigIncDcyBr.size()!=0)||(m_vVPid_sigCascDcyBr.size()!=0)||(m_vVPid_sigIncCascDcyBr.size()!=0)||(m_vVPid_sigIRADcyBr.size()!=0)||(m_vVPid_sigIncOrIRACascDcyBr.size()!=0)) haveTopoAnaTasks=true;
  if(haveTopoAnaTasks==false)
    { 
      cerr<<"Error: No topology analysis to be performed is set up!"<<endl;
      cerr<<"Infor: At least one sort of functionality items has to be specified explicitly in the card file."<<endl;
      cerr<<"Infor: Please check the input card!"<<endl;
      exit(-1);
    }

  if(m_ccSwitch==true)
    {
      cout<<"Charge conjugate objects are processed together."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Charge conjugate objects are not processed together (default)."<<endl<<endl;
    }

  if(m_anaTasksForSigIds=="TC")
    {
      if(m_vbsLevStdOut==true) cout<<"Analysis tasks for signal identifications: both tagging and counting (default)."<<endl<<endl;
    }
  else if(m_anaTasksForSigIds=="T")
    {
      cout<<"Analysis tasks for signal identifications: tagging only."<<endl<<endl;
    }
  else if(m_anaTasksForSigIds=="C")
    {
      cout<<"Analysis tasks for signal identifications: counting only."<<endl<<endl;
    }

  if(m_sortSigsInTopoMapsRltdToSigIds==true)
    {
      cout<<"The signals in the topology maps related to signal identifications will be sorted."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The signals in the topology maps related to signal identifications will not be sorted (default)."<<endl<<endl;
    }

  if((m_pidOfISt1!=m_pidOfE)||(m_pidOfISt2!=-1*m_pidOfE))
    {
      cout<<"The initial state particles are set to be";
      writePnmFromPid(cout,"TxtPnm",m_pidOfISt1);
      cout<<" and";
      writePnmFromPid(cout,"TxtPnm",m_pidOfISt2);
      cout<<"."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The initial state particles are e- and e+ (default)."<<endl<<endl;
    }

  if(m_iStPsSwitch==true)
    {
      cout<<"The initial state particles are required to be pushed front uniformly in all the events."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The initial state particles are not required to be pushed front uniformly in all the events (default)."<<endl<<endl;
    }

  if((m_cardFlNm.size()>5&&m_comNmOfOptFls!=m_cardFlNm.substr(0,(m_cardFlNm.size()-5)))&&(m_comNmOfOptFls!=m_cardFlNm))
    {
      cout<<"Common name of output files: "<<m_comNmOfOptFls<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Common name of output files: "<<m_comNmOfOptFls<<" (default)"<<endl<<endl;
    }

  if(m_cmpltHVLines==true)
    {
      cout<<"The horizontal and vertical lines in output pdf files are required to be completed."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The horizontal and vertical lines in output pdf files are not required to be completed (default)."<<endl<<endl;
    }

  if(m_centDcyObjs==true)
    {
      cout<<"The decay objects in output pdf files are required to be centered."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"The decay objects in output pdf files are not required to be centered (default)."<<endl<<endl;
    }

  if(m_oneOptRootFlByOneIptRootFl==true)
    {
      cout<<"Output mode of root files: one output root file by one input root file."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Output mode of root files: only one output root file by default. If oversize, it will be splitted into multiple files according to the size of the TTree object in memory by default. In addition, users can can specify the maximum number of entries to be saved in a single output root file by another item (default)."<<endl<<endl;

      if(m_nEtrMaxInASngOptRootFl!=ULONG_MAX)
        {
          cout<<"Maximum number of entries to be saved in a single output root file:"<<m_nEtrMaxInASngOptRootFl<<endl<<endl;
        }
      else
        {
          if(m_vbsLevStdOut==true) cout<<"Upper limit of the total bytes of the cloned TTree object of "<<m_ttrNm<<": 3 GB in memory (default)."<<endl<<endl;
        }
    }

  if(m_useArrayTBrsOpt==true)
    {
      cout<<"Array tbranches are used to store topology tags in output root files when possible."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Flat tbranches are used to store topology tags in output root files when possible (default)."<<endl<<endl;
    }

  if(m_rmIptTBrs==true)
    {
      cout<<"Input tbranches will be removed from output root files."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Input tbranches will not be removed from output root files (default)."<<endl<<endl;
    }

  if(m_convtMSIMSDIntoAOI==true)
    {
      if(m_strgTpOfRawIptTopoDat=="MSI"||m_strgTpOfRawIptTopoDat=="MSD")
        {
          cout<<"MSI/MSD input tbranches will be converted into AOI output tbranches."<<endl;

          m_rmIptTBrs=true;
          cerr<<"Infor: The item prompted with \"% Remove input tbranches from output root files (Two options: Y and N. Default: N)\" is set to Y in order to carry out the conversion."<<endl<<endl;
        }
      else
        {
          cerr<<"Warning: the setting with the item prompted with \"% Convert MSI/MSD input tbranches into AOI output tbranches (Two options: Y and N. Default: N)\" does not work for the current cases of AOI/VOI input tbranches."<<endl<<endl;
        }
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"MSI/MSD input tbranches will not be converted into AOI output tbranches (default)."<<endl<<endl;
    }

  if(m_supprOptRootFls==true)
    {
      cout<<"Output root files will be suppressed."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Output root files will not be suppressed (default)."<<endl<<endl;
    }

  if(m_flatArrayBrsLocally==true)
    {
      cout<<"Flat array tbranches locally in each output root file."<<endl<<endl;
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"Flat array tbranches globally in all the output root files (default)."<<endl<<endl;
    }

  if(m_vbsLevStdOut==true)
    {
      cout<<"The level of standard output is set to \"verbose\"."<<endl<<endl;
    }
}
