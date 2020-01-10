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
          nmOfIptRootFl=new TString(m_nmsOfIptRootFls[i]);
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
          TChain * chn=new TChain(m_trNm.c_str());
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
                      if(eaccess(nmOfOptRootFl.c_str(),0)==0)
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

  if(m_trNm.empty())
    {
      cerr<<"Error: The tree name is empty!"<<endl;
      exit(-1);
    }
  else
    {
      cout<<"Tree name: "<<m_trNm<<endl<<endl;
    }

  if(m_strgTpOfRawIptTopoDat=="AI")
    {
      cout<<"Storage type of the raw input topology data: Array of integers (default)."<<endl<<endl;
    }
  else if(m_strgTpOfRawIptTopoDat=="VI")
    {
      cout<<"Storage type of the raw input topology data: Vector of integers."<<endl<<endl;
    }
  else if(m_strgTpOfRawIptTopoDat=="MIV")
    {
      cout<<"Storage type of the raw input topology data: multiple integer variables."<<endl<<endl;
    }
  else if(m_strgTpOfRawIptTopoDat=="MDV")
    {
      cout<<"Storage type of the raw input topology data: multiple double variables."<<endl<<endl;
    }

  if(m_brNmOfNps!="nMCGen")
    {
      if(m_strgTpOfRawIptTopoDat=="AI"||m_strgTpOfRawIptTopoDat=="MIV"||m_strgTpOfRawIptTopoDat=="MDV") cout<<"Branch name of the number of particles: "<<m_brNmOfNps<<endl<<endl;
      else cout<<"The item with the prompt \"% Branch name of the number of particles (Default: nMCGen)\" is not used since the storage type of the raw input topology data is \"vector of integers\"."<<endl<<endl; 
    }
  else
    {
      if(m_strgTpOfRawIptTopoDat=="AI"||m_strgTpOfRawIptTopoDat=="MIV"||m_strgTpOfRawIptTopoDat=="MDV") cout<<"Branch name of the number of particles: "<<m_brNmOfNps<<" (default)"<<endl<<endl;
      else cout<<"The item with the prompt \"% Branch name of the number of particles (Default: nMCGen)\" is not used since the storage type of the raw input topology data is \"vector of integers\"."<<endl<<endl;
    }

  if(m_brNmOfPid!="MCGenPDG")
    {
      cout<<"Branch name of the PDG codes of particles: "<<m_brNmOfPid<<endl<<endl;
    }
  else
    {
      cout<<"Branch name of the PDG codes of particles: "<<m_brNmOfPid<<" (default)"<<endl<<endl;
    }

  if(m_brNmOfMidx!="MCGenMothIndex")
    {
      cout<<"Branch name of the mother indeces of particles: "<<m_brNmOfMidx<<endl<<endl;
    }
  else
    {
      cout<<"Branch name of the mother indeces of particles: "<<m_brNmOfMidx<<" (default)"<<endl<<endl;
    }

  TChain * chn=new TChain(m_trNm.c_str());
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
          TTree * tr=(TTree *) fl->Get(m_trNm.c_str());
          if(!tr)
            {
              cerr<<"Error: The input root file \""<<chnElmt->GetTitle()<<"\" does not contain a tree named \""<<m_trNm<<"\"!"<<endl<<endl;
              allIptsAreOK=false;
            }
          else
            {
              if(m_strgTpOfRawIptTopoDat=="AI"||m_strgTpOfRawIptTopoDat=="MIV"||m_strgTpOfRawIptTopoDat=="MDV")
                {
                  TBranch * br0=tr->FindBranch(m_brNmOfNps.c_str());
                  if(!br0)
                    {
                      cerr<<"Error: The tree \""<<m_trNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_brNmOfNps<<"\"!"<<endl<<endl;
                      allIptsAreOK=false;
                    }
                }
              if(m_strgTpOfRawIptTopoDat=="AI"||m_strgTpOfRawIptTopoDat=="VI")
                {
                  TBranch * br1=tr->FindBranch(m_brNmOfPid.c_str());
                  if(!br1)
                    {
                      cerr<<"Error: The tree \""<<m_trNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_brNmOfPid<<"\"!"<<endl<<endl;
                      allIptsAreOK=false;
                    }
                  TBranch * br2=tr->FindBranch(m_brNmOfMidx.c_str());
                  if(!br2)
                    {
                      cerr<<"Error: The tree \""<<m_trNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_brNmOfMidx<<"\"!"<<endl<<endl;
                      allIptsAreOK=false;
                    }
                }
              else
                {
                  ostringstream oss;
                  int i=0;
                  string strI,m_brNmOfPid_i,m_brNmOfMidx_i;
                  TBranch * br1, * br2;
                  while(1)
                    {
                      oss.str("");
                      oss<<i;
                      strI=oss.str();
                      m_brNmOfPid_i=m_brNmOfPid+"_"+strI;
                      m_brNmOfMidx_i=m_brNmOfMidx+"_"+strI;
                      br1=tr->FindBranch(m_brNmOfPid_i.c_str());
                      br2=tr->FindBranch(m_brNmOfMidx_i.c_str());
                      if((!br1)||(!br2)) break;
                      i++;
                    }
                  if(i==0)
                    {
                      cerr<<"Error: The tree \""<<m_trNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" does not contain a branch named \""<<m_brNmOfPid<<"_i\", or \""<<m_brNmOfMidx<<"_i\"!"<<endl<<endl;
                      allIptsAreOK=false;                      
                    }
                  else
                    {
                      cout<<"The tree \""<<m_trNm<<"\" in the input root file \""<<chnElmt->GetTitle()<<"\" contains "<<i<<" branches named \""<<m_brNmOfPid<<"_i\" and contains "<<i<<" branches named \""<<m_brNmOfMidx<<"_i\"!"<<endl<<endl;
                    }
                }
            }
          delete fl;
        }
    }
  if(!allIptsAreOK) exit(-1);
  delete chn;

  if(m_nEtrsMax!=ULONG_MAX)
    {
      cout<<"Maximum number of entries to be processed: "<<m_nEtrsMax<<endl<<endl;
    }
  else
    {
      cout<<"Maximum number of entries to be processed: ULONG_MAX (default)"<<endl<<endl;
    }

  if(m_cut.empty())
    {
      cout<<"No cut is used to select entries."<<endl<<endl;
    }
  else
    {
      cout<<"Cut to select entries: "<<m_cut<<endl<<endl;
      if(m_cutMethod==true)
        {
          cout<<"The method to apply cut to array variables: True as long as one instance is true."<<endl<<endl;
        }
      else
        {
          cout<<"The method to apply cut to array variables: False as long as one instance is false (default)."<<endl<<endl;
        }
    }

  if(m_hHdDcyBrsMax!=UINT_MAX)
    {
      cout<<"Maximum hierarchy of heading decay branches to be processed in each event: "<<m_hHdDcyBrsMax<<endl<<endl;
    }
  else
    {
      cout<<"Maximum hierarchy of heading decay branches to be processed in each event: UINT_MAX (default)"<<endl<<endl;
    }

  if(m_vIdPid.size()==0)
    { 
      cout<<"No particles are specified to ignore their decay."<<endl<<endl;
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
      cout<<"No particles are specified to ignore the decay of their daughters."<<endl<<endl;
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

  if(m_ignoreGISR==true)
    {
      cout<<"gISR photons are ignored."<<endl<<endl;
    }
  else
    {
      cout<<"gISR photons are not ignored (default)."<<endl<<endl;
    }

  if(m_ignoreGFSR==true)
    {
      cout<<"gFSR photons are ignored."<<endl<<endl;
    }
  else
    {
      cout<<"gFSR photons are not ignored (default)."<<endl<<endl;
    }

  if(m_compAnaOfDcyTrs==true)
    {
      cout<<"The component analysis of decay trees will be performed."<<endl;
      if(m_nDcyTrsToBePrtdMax!=ULONG_MAX)
        {
          cout<<"Maximum number of decay trees to be printed: "<<m_nDcyTrsToBePrtdMax<<endl<<endl;
        }
      else
        {
          cout<<"Maximum number of decay trees to be printed: ULONG_MAX (default)"<<endl<<endl;
        }
      if(m_adjDcyIFStsIntoACol==true)
        {
          cout<<"The decay initial-final states in the output pdf files are adjusted into a column next to that of decay trees."<<endl<<endl;
        }
      else
        {
          cout<<"The decay initial-final states in the output pdf files are not adjusted into a column next to that of decay trees (default)."<<endl<<endl;
        }
      m_vDcyTr.clear(); m_vCcDcyTr.clear();
      m_vIDcyTr.clear(); m_vICcDcyTr.clear();
      m_vNDcyTr.clear(); m_vNCcDcyTr.clear();
      m_uomDcyTr.clear(); m_uomCcDcyTr.clear();

      cout<<"The component analysis of decay initial-final states will be performed along with decay trees."<<endl;
      if(m_nDcyIFStsToBePrtdMax!=ULONG_MAX)
        {
          cout<<"Maximum number of decay initial-final states to be printed: "<<m_nDcyIFStsToBePrtdMax<<endl<<endl;       
        }
      else
        { 
          cout<<"Maximum number of decay initial-final states to be printed: ULONG_MAX (default)"<<endl<<endl;
        }
      m_vDcyIFSts.clear(); m_vCcDcyIFSts.clear();
      m_vIDcyIFSts.clear(); m_vICcDcyIFSts.clear();
      m_vNDcyIFSts.clear(); m_vNCcDcyIFSts.clear();
      m_uomDcyIFSts.clear(); m_uomCcDcyIFSts.clear();
      m_iDcyTrIDcyIFStsMap.clear(); m_iDcyTrICcDcyIFStsMap.clear();
    }
  else
    {
      cout<<"The component analysis of decay trees will not be performed (default)."<<endl<<endl;

      if(m_compAnaOfDcyIFSts==true)
        {
          cout<<"The component analysis of decay initial-final states will be performed."<<endl;
          if(m_nDcyIFStsToBePrtdMax!=ULONG_MAX)
            {
              cout<<"Maximum number of decay initial-final states to be printed: "<<m_nDcyIFStsToBePrtdMax<<endl<<endl;
            }
          else
            {
              cout<<"Maximum number of decay initial-final states to be printed: ULONG_MAX (default)"<<endl<<endl;
            }
          m_vDcyIFSts.clear(); m_vCcDcyIFSts.clear();
          m_vIDcyIFSts.clear(); m_vICcDcyIFSts.clear();
          m_vNDcyIFSts.clear(); m_vNCcDcyIFSts.clear();
          m_uomDcyIFSts.clear(); m_uomCcDcyIFSts.clear();
        } 
      else
        {
          cout<<"The component analysis of decay initial-final states will not be performed (default)."<<endl<<endl;
        }
    }

  if(m_vPid_compDcyBrP.size()==0)
    {
      cout<<"No particles are specified for the analysis of their decay branches."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the decay branches of the following particles:"<<endl<<endl;
      for(unsigned int i=0;i<m_vPid_compDcyBrP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compDcyBrP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compDcyBrP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compDcyBrP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compDcyBrP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNDcyBrsToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of decay branches to be printed: "<<m_vNDcyBrsToBePrtdMax[i]<<endl;
            }
          else
            {
              cout<<"  Maximum number of decay branches to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNm_compDcyBrP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compDcyBrP[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the particle is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
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

  if(m_vPid_compProdBrP.size()==0)
    {
      cout<<"No particles are specified for the analysis of their production branches."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the production branches of the following particles:"<<endl<<endl;
      for(unsigned int i=0;i<m_vPid_compProdBrP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compProdBrP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compProdBrP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compProdBrP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compProdBrP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNProdBrsToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of production branches to be printed: "<<m_vNProdBrsToBePrtdMax[i]<<endl;
            }
          else
            {
              cout<<"  Maximum number of production branches to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNm_compProdBrP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compProdBrP[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the particle is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
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
      cout<<"No particles are specified for the analysis of their mothers."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the mothers of the following particles:"<<endl<<endl;
      for(unsigned int i=0;i<m_vPid_compMP.size();i++)
        {
          cout<<" ";
          writePnmFromPid(cout,"TxtPnm",m_vPid_compMP[i]);
          // if(m_pidTxtPnmMap[m_vPid_compMP[i]].size()<=6) cout<<"\t\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compMP[i]].size()<=14) cout<<"\t\t";
          // else if(m_pidTxtPnmMap[m_vPid_compMP[i]].size()<=22) cout<<"\t";
          cout<<endl;
          if(m_vNMsToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of mothers to be printed: "<<m_vNMsToBePrtdMax[i]<<endl;
            }
          else
            {
              cout<<"  Maximum number of mothers to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNm_compMP[i]!="")
            {
              cout<<"  Alias for the particle is set to be \""<<m_vNm_compMP[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the particle is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
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
      cout<<"No inclusive decay branches are specified for the analysis of their exclusive components."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the exclusive components of the following inclusive decay branches:"<<endl<<endl;
      for(unsigned int i=0;i<m_vVPid_compIncDcyBr.size();i++)
        {
          for(unsigned int j=0;j<m_vVPid_compIncDcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_compIncDcyBr[i][j]);
              cout<<endl;
	    }
          if(m_vNExcCompsToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNExcCompsToBePrtdMax[i]<<endl;
            }
          else
            {
              cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNm_compIncDcyBr[i]!="")
            {
              cout<<"  Alias for the inclusive decay branch is set to be \""<<m_vNm_compIncDcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the inclusive decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
      cout<<endl;

      m_vCompIncDcyBr.clear(); m_vCompCcIncDcyBr.clear();
      list<int> compIncDcyBr, compCcIncDcyBr;
      m_vCompICcIncDcyBr.clear();
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
              compIncDcyBr.push_front(11);
              compIncDcyBr.push_front(-11);
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
              else if(m_ccSwitch==true&&m_vCompICcIncDcyBr[j]!=0&&compIncDcyBr==m_vCompCcIncDcyBr[j])
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
              if((*liit)==-11) liit++;
              for(liit++;liit!=compIncDcyBr.end();liit++) compCcIncDcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(compCcIncDcyBr);
              liit=compIncDcyBr.begin();
              if((*liit)!=-11)
                {
                  compCcIncDcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  compCcIncDcyBr.push_front(11);
                  compCcIncDcyBr.push_front(-11);
                }
              m_vCompCcIncDcyBr.push_back(compCcIncDcyBr);
              if(compCcIncDcyBr==compIncDcyBr) m_vCompICcIncDcyBr.push_back(0);
              else m_vCompICcIncDcyBr.push_back(1);
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
          cout<<" -->";
          for(liit++;liit!=compIncDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<" + anything"<<endl;
          if(m_vNExcCompsToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNExcCompsToBePrtdMax[i]<<endl;
            }
          else
            {
              cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNm_compIncDcyBr[i]!="")
            {
              cout<<"  Alias for the inclusive decay branch is set to be \""<<m_vNm_compIncDcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the inclusive decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  if(m_vVPid_compIRADcyBr.size()==0)
    {
      cout<<"No intermediate-resonance-allowed decay branches are specified for the analysis of the internal structures involved in them."<<endl<<endl;
    }
  else
    {
      cout<<"Analyze the internal structures involved in the following intermediate-resonance-allowed decay branches:"<<endl<<endl;
      for(unsigned int i=0;i<m_vVPid_compIRADcyBr.size();i++)
        {
          for(unsigned int j=0;j<m_vVPid_compIRADcyBr[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_compIRADcyBr[i][j]);
              cout<<endl;
	    }
          if(m_vNIntStrusToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNIntStrusToBePrtdMax[i]<<endl;
            }
          else
            {
              cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNm_compIRADcyBr[i]!="")
            {
              cout<<"  Alias for the intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_compIRADcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the intermediate-resonance-allowed decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
      cout<<endl;

      m_vCompIRADcyBr.clear(); m_vCompCcIRADcyBr.clear();
      list<int> compIRADcyBr, compCcIRADcyBr;
      m_vCompICcIRADcyBr.clear();
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
              compIRADcyBr.push_front(11);
              compIRADcyBr.push_front(-11);
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
              else if(m_ccSwitch==true&&m_vCompICcIRADcyBr[j]!=0&&compIRADcyBr==m_vCompCcIRADcyBr[j])
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
              if((*liit)==-11) liit++;
              for(liit++;liit!=compIRADcyBr.end();liit++) compCcIRADcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(compCcIRADcyBr);
              liit=compIRADcyBr.begin();
              if((*liit)!=-11)
                {
                  compCcIRADcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  compCcIRADcyBr.push_front(11);
                  compCcIRADcyBr.push_front(-11);
                }
              m_vCompCcIRADcyBr.push_back(compCcIRADcyBr);
              if(compCcIRADcyBr==compIRADcyBr) m_vCompICcIRADcyBr.push_back(0);
              else m_vCompICcIRADcyBr.push_back(1);
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
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=compIRADcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNIntStrusToBePrtdMax[i]!=ULONG_MAX)
            {
              cout<<"  Maximum number of exclusive components to be printed: "<<m_vNIntStrusToBePrtdMax[i]<<endl;
            }
          else
            {
              cout<<"  Maximum number of exclusive components to be printed: ULONG_MAX (default)"<<endl;
            }
          if(m_vNm_compIRADcyBr[i]!="")
            {
              cout<<"  Alias for the intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_compIRADcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the intermediate-resonance-allowed decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  if(m_vVPid_sigDcyTr.size()==0)
    {
      cout<<"No signal decay trees are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal decay trees:"<<endl<<endl;
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
              cout<<"  Alias for the signal decay tree is set to be \""<<m_vNm_sigDcyTr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal decay tree is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
	}
      cout<<endl;

      m_vSigDcyTr.clear(); m_vCcSigDcyTr.clear();
      vector< list<int> > sigDcyTr, ccSigDcyTr;
      m_vISigDcyTr.clear(); m_vICcSigDcyTr.clear();
      m_vNSigDcyTr.clear(); m_vNCcSigDcyTr.clear(); 
      m_vSigDcyIFSts.clear(); m_vCcSigDcyIFSts.clear();
      list<int> sigDcyIFSts, ccSigDcyIFSts;
      m_vISigDcyIFSts.clear(); m_vICcSigDcyIFSts.clear();
      m_vNSigDcyIFSts.clear(); m_vNCcSigDcyIFSts.clear();
      m_iSigDcyTrISigDcyIFStsMap.clear(); m_iSigDcyTrICcSigDcyIFStsMap.clear();
      vector<int> vCcSigPid;
      vector<int> vCcSigMidx;
      int iSigDcyIFSts, iCcSigDcyIFSts;
      for(unsigned int i=0;i<m_vVPid_sigDcyTr.size();i++)
        {
          sortPs(m_vVPid_sigDcyTr[i],m_vVMidx_sigDcyTr[i]);
          sigDcyTr.clear();      
          getDcyTr(m_vVPid_sigDcyTr[i],m_vVMidx_sigDcyTr[i],sigDcyTr);
          sigDcyIFSts.clear();
          getDcyIFSts(m_vVPid_sigDcyTr[i],m_vVMidx_sigDcyTr[i],sigDcyIFSts);
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
              vCcSigPid.clear();
              vCcSigMidx.clear();
              for(unsigned int j=0;j<m_vVPid_sigDcyTr[i].size();j++) vCcSigPid.push_back(getCcPid(m_vVPid_sigDcyTr[i][j]));
              vCcSigMidx=m_vVMidx_sigDcyTr[i];
              sortPs(vCcSigPid,vCcSigMidx);
              ccSigDcyTr.clear();
              getDcyTr(vCcSigPid,vCcSigMidx,ccSigDcyTr);
              m_vCcSigDcyTr.push_back(ccSigDcyTr);
              if(ccSigDcyTr==sigDcyTr) m_vICcSigDcyTr.push_back(0);
              else m_vICcSigDcyTr.push_back(1);
              m_vNCcSigDcyTr.push_back(0);
            }

          iSigDcyIFSts=-1; // If the variable is still equal to -1 after the following loop, then the signal decay initial-final states is a new signal decay initial-final states.
          for(unsigned int j=0;j<m_vSigDcyIFSts.size();j++)
            {
              if(sigDcyIFSts==m_vSigDcyIFSts[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Infor: The initial-final state of the "<<i+1<<ordNumSufi<<" signal decay tree is same as that of the "<<j+1<<ordNumSufj<<" signal decay tree."<<endl<<endl;
                  iSigDcyIFSts=j;
                  if(m_ccSwitch==true) iCcSigDcyIFSts=m_vICcSigDcyIFSts[j];
                  break;
                }
              else if(m_ccSwitch==true&&m_vICcSigDcyIFSts[j]!=0&&sigDcyIFSts==m_vCcSigDcyIFSts[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Infor: The initial-final state of the "<<i+1<<ordNumSufi<<" signal decay tree is same as that of the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal decay tree."<<endl<<endl;
                  iSigDcyIFSts=j;
                  iCcSigDcyIFSts=-1;
                  break;
                }
            }
          if(iSigDcyIFSts==-1)
            {
              iSigDcyIFSts=m_vSigDcyIFSts.size();
              m_vSigDcyIFSts.push_back(sigDcyIFSts);
              m_vISigDcyIFSts.push_back(m_vSigDcyIFSts.size()-1);
              m_vNSigDcyIFSts.push_back(0);
              if(m_ccSwitch==true)
                {
                  ccSigDcyIFSts.clear();
                  getDcyIFSts(vCcSigPid,vCcSigMidx,ccSigDcyIFSts);
                  m_vCcSigDcyIFSts.push_back(ccSigDcyIFSts);
                  if(ccSigDcyIFSts==sigDcyIFSts) iCcSigDcyIFSts=0;
                  else iCcSigDcyIFSts=1;
                  m_vICcSigDcyIFSts.push_back(iCcSigDcyIFSts);
                  m_vNCcSigDcyIFSts.push_back(0);
                }
            }
          m_iSigDcyTrISigDcyIFStsMap[m_vSigDcyTr.size()-1]=iSigDcyIFSts;
          if(m_ccSwitch==true) m_iSigDcyTrICcSigDcyIFStsMap[m_vSigDcyTr.size()-1]=iCcSigDcyIFSts;   
        }

      cout<<"i.e.:"<<endl<<endl;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigDcyTr.size();i++)
        { 
          sigDcyTr.clear();
          sigDcyTr=m_vSigDcyTr[i];
          for(unsigned int j=0;j<sigDcyTr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigDcyTr[j];
              cout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              // The condition "j==0" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if(j==0||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(cout,"TxtPnm",(*liit));
                }
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              cout<<endl;
            }
          if(m_vNm_sigDcyTr[i]!="")
            {
              cout<<"  Alias for the signal decay tree is set to be \""<<m_vNm_sigDcyTr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal decay tree is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }

      m_iSigDcyTrIDcyTrMap.clear();
      m_iSigDcyIFStsIDcyIFStsMap.clear();
    }

  if(m_vVPid_sigDcyIFSts2.size()==0)
    {
      cout<<"No signal decay initial-final states are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal decay initial-final states:"<<endl<<endl;
      for(unsigned int i=0;i<m_vVPid_sigDcyIFSts2.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigDcyIFSts2[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigDcyIFSts2[i][j]);
              cout<<endl;
	    }
          if(m_vNm_sigDcyIFSts2[i]!="")
            {
              cout<<"  Alias for the signal decay initial-final states is set to be \""<<m_vNm_sigDcyIFSts2[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal decay initial-final states is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
	}
      cout<<endl;

      m_vSigDcyIFSts2.clear(); m_vCcSigDcyIFSts2.clear();
      list<int> sigDcyIFSts2, ccSigDcyIFSts2;
      m_vISigDcyIFSts2.clear(); m_vICcSigDcyIFSts2.clear();
      m_vNSigDcyIFSts2.clear(); m_vNCcSigDcyIFSts2.clear();
      for(unsigned int i=0;i<m_vVPid_sigDcyIFSts2.size();i++)
        {
          sigDcyIFSts2.clear();
          for(unsigned int j=1;j<m_vVPid_sigDcyIFSts2[i].size();j++) sigDcyIFSts2.push_back(m_vVPid_sigDcyIFSts2[i][j]);
          sortByPidAndPchrg(sigDcyIFSts2);
          if(m_vVPid_sigDcyIFSts2[i][0]!=m_pidOfISt)
            {
              sigDcyIFSts2.push_front(m_vVPid_sigDcyIFSts2[i][0]);
            }
          else
            {
              sigDcyIFSts2.push_front(11);
              sigDcyIFSts2.push_front(-11);
            }
          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigDcyIFSts2.size();j++)
            {
              if(sigDcyIFSts2==m_vSigDcyIFSts2[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay initial-final state is same as the "<<j+1<<ordNumSufj<<" signal decay initial-final state!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }
              else if(m_ccSwitch==true&&m_vICcSigDcyIFSts2[j]!=0&&sigDcyIFSts2==m_vCcSigDcyIFSts2[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal decay initial-final state is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal decay initial-final state!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }               
            }

          m_vSigDcyIFSts2.push_back(sigDcyIFSts2);
          m_vISigDcyIFSts2.push_back(m_vSigDcyIFSts2.size()-1);
          m_vNSigDcyIFSts2.push_back(0);
          if(m_ccSwitch==true)
            {
              ccSigDcyIFSts2.clear();
              list<int>::iterator liit=sigDcyIFSts2.begin();
              if((*liit)==-11) liit++;
              for(liit++;liit!=sigDcyIFSts2.end();liit++) ccSigDcyIFSts2.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigDcyIFSts2);
              liit=sigDcyIFSts2.begin();
              if((*liit)==-11)
                {
                  ccSigDcyIFSts2.push_front(11);
                  ccSigDcyIFSts2.push_front(-11);
                }
              else
                {
                  ccSigDcyIFSts2.push_front(getCcPid((*liit)));
                }
              m_vCcSigDcyIFSts2.push_back(ccSigDcyIFSts2);
              if(ccSigDcyIFSts2==sigDcyIFSts2) m_vICcSigDcyIFSts2.push_back(0);
              else m_vICcSigDcyIFSts2.push_back(1);
              m_vNCcSigDcyIFSts2.push_back(0);
            }
        }

      cout<<"i.e.:"<<endl<<endl;
      for(unsigned int i=0;i<m_vSigDcyIFSts2.size();i++)
        {
          sigDcyIFSts2.clear();
          sigDcyIFSts2=m_vSigDcyIFSts2[i];
          cout<<" ";
          list<int>::iterator liit=sigDcyIFSts2.begin();
          writePnmFromPid(cout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=sigDcyIFSts2.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNm_sigDcyIFSts2[i]!="")
            {
              cout<<"  Alias for the signal decay initial-final states is set to be \""<<m_vNm_sigDcyIFSts2[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            { 
              cout<<"  No alias for the signal decay initial-final states is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }

      m_iSigDcyIFSts2IDcyIFStsMap.clear();
    }

  if(m_vPid_sigP.size()==0)
    {
      cout<<"No signal particles are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal particles:"<<endl<<endl;
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
              cout<<"  Alias for the signal particle is set to be \""<<m_vNm_sigP[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal particle is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
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
      cout<<"No signal decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal decay branches:"<<endl<<endl;
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
              cout<<"  Alias for the signal decay branch is set to be \""<<m_vNm_sigDcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
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
              sigDcyBr.push_front(11);
              sigDcyBr.push_front(-11);
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
              if((*liit)==-11) liit++;
              for(liit++;liit!=sigDcyBr.end();liit++) ccSigDcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigDcyBr);
              liit=sigDcyBr.begin();
              if((*liit)!=-11)
                {
                  ccSigDcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  ccSigDcyBr.push_front(11);
                  ccSigDcyBr.push_front(-11); 
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
          cout<<" -->";
          for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNm_sigDcyBr[i]!="")
            {
              cout<<"  Alias for the signal decay branch is set to be \""<<m_vNm_sigDcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  if(m_vVPid_sigIncDcyBr.size()==0)
    {
      cout<<"No signal inclusive decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal inclusive decay branches:"<<endl<<endl;
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
              cout<<"  Alias for the signal inclusive decay branch is set to be \""<<m_vNm_sigIncDcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal inclusive decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
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
              sigIncDcyBr.push_front(11);
              sigIncDcyBr.push_front(-11);
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
              if((*liit)==-11) liit++;
              for(liit++;liit!=sigIncDcyBr.end();liit++) ccSigIncDcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigIncDcyBr);
              liit=sigIncDcyBr.begin();
              if((*liit)!=-11)
                {
                  ccSigIncDcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  ccSigIncDcyBr.push_front(11);
                  ccSigIncDcyBr.push_front(-11); 
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
          cout<<" -->";
          for(liit++;liit!=sigIncDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<" + anything";
          cout<<endl;
          if(m_vNm_sigIncDcyBr[i]!="")
            {
              cout<<"  Alias for the signal inclusive decay branch is set to be \""<<m_vNm_sigIncDcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal inclusive decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  if(m_vVPid_sigCascDcyBrs.size()==0)
    {
      cout<<"No signal cascade decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal cascade decay branches:"<<endl<<endl;
      for(unsigned int i=0;i<m_vVPid_sigCascDcyBrs.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigCascDcyBrs[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigCascDcyBrs[i][j]);
              if(m_pidTxtPnmMap[m_vVPid_sigCascDcyBrs[i][j]].size()<7)  cout<<"\t\t\t";
              else if(m_pidTxtPnmMap[m_vVPid_sigCascDcyBrs[i][j]].size()<15) cout<<"\t\t";
              else cout<<"\t";
              cout<<setiosflags(ios::right)<<setw(3)<<m_vVMidx_sigCascDcyBrs[i][j]<<resetiosflags(ios::adjustfield)<<endl;
	    }
          if(m_vNm_sigCascDcyBrs[i]!="")
            {
              cout<<"  Alias for the signal cascade decay branch is set to be \""<<m_vNm_sigCascDcyBrs[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal cascade decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
	}
      cout<<endl;

      m_vSigCascDcyBrs.clear(); m_vCcSigCascDcyBrs.clear();
      vector< list<int> > sigCascDcyBrs, ccSigCascDcyBrs;
      m_vVSigCascDcyBrsIdxOfHead.clear(); m_vVCcSigCascDcyBrsIdxOfHead.clear();
      vector<int> vSigCascDcyBrsIdxOfHead, vCcSigCascDcyBrsIdxOfHead; 
      m_vVSigCascDcyBrsMidxOfHead.clear(); m_vVCcSigCascDcyBrsMidxOfHead.clear();
      vector<int> vSigCascDcyBrsMidxOfHead, vCcSigCascDcyBrsMidxOfHead;
      m_vISigCascDcyBrs.clear(); m_vICcSigCascDcyBrs.clear();
      m_vNSigCascDcyBrs.clear(); m_vNCcSigCascDcyBrs.clear();
      vector<int> vCcSigPid2, vCcSigMidx2;
      for(unsigned int i=0;i<m_vVPid_sigCascDcyBrs.size();i++)
        {
          sortPs(m_vVPid_sigCascDcyBrs[i],m_vVMidx_sigCascDcyBrs[i]);
          sigCascDcyBrs.clear();      
          vSigCascDcyBrsIdxOfHead.clear();
          vSigCascDcyBrsMidxOfHead.clear();
          getDcyTr(m_vVPid_sigCascDcyBrs[i],m_vVMidx_sigCascDcyBrs[i],sigCascDcyBrs,vSigCascDcyBrsIdxOfHead,vSigCascDcyBrsMidxOfHead);

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigCascDcyBrs.size();j++)
            {
              if(sigCascDcyBrs==m_vSigCascDcyBrs[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal cascade decay branches is same as the "<<j+1<<ordNumSufj<<" signal cascade decay branches!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);    
                }
              else if(m_ccSwitch==true&&m_vICcSigCascDcyBrs[j]!=0&&sigCascDcyBrs==m_vCcSigCascDcyBrs[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal cascade decay branches is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal cascade decay branches!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }                
            }

          m_vSigCascDcyBrs.push_back(sigCascDcyBrs);
          m_vVSigCascDcyBrsIdxOfHead.push_back(vSigCascDcyBrsIdxOfHead);
          m_vVSigCascDcyBrsMidxOfHead.push_back(vSigCascDcyBrsMidxOfHead);
          m_vISigCascDcyBrs.push_back(m_vSigCascDcyBrs.size()-1);
          m_vNSigCascDcyBrs.push_back(0);
          if(m_ccSwitch==true)
            {
              vCcSigPid2.clear();
              vCcSigMidx2.clear();
              for(unsigned int j=0;j<m_vVPid_sigCascDcyBrs[i].size();j++) vCcSigPid2.push_back(getCcPid(m_vVPid_sigCascDcyBrs[i][j])); 
              vCcSigMidx2=m_vVMidx_sigCascDcyBrs[i];
              sortPs(vCcSigPid2,vCcSigMidx2);
              ccSigCascDcyBrs.clear();
              vCcSigCascDcyBrsIdxOfHead.clear();
              vCcSigCascDcyBrsMidxOfHead.clear();
              getDcyTr(vCcSigPid2,vCcSigMidx2,ccSigCascDcyBrs,vCcSigCascDcyBrsIdxOfHead,vCcSigCascDcyBrsMidxOfHead);
              m_vCcSigCascDcyBrs.push_back(ccSigCascDcyBrs);
              m_vVCcSigCascDcyBrsIdxOfHead.push_back(vCcSigCascDcyBrsIdxOfHead);
              m_vVCcSigCascDcyBrsMidxOfHead.push_back(vCcSigCascDcyBrsMidxOfHead);
              if(ccSigCascDcyBrs==sigCascDcyBrs) m_vICcSigCascDcyBrs.push_back(0);
              else m_vICcSigCascDcyBrs.push_back(1);
              m_vNCcSigCascDcyBrs.push_back(0);
            }          
        }

      cout<<"i.e.:"<<endl<<endl;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigCascDcyBrs.size();i++)
        { 
          sigCascDcyBrs.clear();
          sigCascDcyBrs=m_vSigCascDcyBrs[i];
          vSigCascDcyBrsIdxOfHead=m_vVSigCascDcyBrsIdxOfHead[i];
          for(unsigned int j=0;j<sigCascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigCascDcyBrs[j];
              cout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              if(j==0&&vSigCascDcyBrsIdxOfHead[0]==-1)
              {
                liit++;
                writePnmFromPid(cout,"TxtPnm",(*liit));
              }
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              cout<<endl;
            }
          if(m_vNm_sigCascDcyBrs[i]!="")
            {
              cout<<"  Alias for the signal cascade decay branch is set to be \""<<m_vNm_sigCascDcyBrs[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal cascade decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  if(m_vVPid_sigIncCascDcyBrs.size()==0)
    {
      cout<<"No signal inclusive cascade decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal inclusive cascade decay branches:"<<endl<<endl;
      for(unsigned int i=0;i<m_vVPid_sigIncCascDcyBrs.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigIncCascDcyBrs[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigIncCascDcyBrs[i][j]);
              if(m_pidTxtPnmMap[m_vVPid_sigIncCascDcyBrs[i][j]].size()<7)  cout<<"\t\t\t";
              else if(m_pidTxtPnmMap[m_vVPid_sigIncCascDcyBrs[i][j]].size()<15) cout<<"\t\t";
              else cout<<"\t";
              cout<<setiosflags(ios::right)<<setw(3)<<m_vVMidx_sigIncCascDcyBrs[i][j]<<resetiosflags(ios::adjustfield)<<endl;
	    }
          if(m_vNm_sigIncCascDcyBrs[i]!="")
            {
              cout<<"  Alias for the signal inclusive cascade decay branch is set to be \""<<m_vNm_sigIncCascDcyBrs[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal inclusive cascade decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
	}
      cout<<endl;

      m_vSigIncCascDcyBrs.clear(); m_vCcSigIncCascDcyBrs.clear();
      vector< list<int> > sigIncCascDcyBrs, ccSigIncCascDcyBrs;
      m_vVSigIncCascDcyBrsIdxOfHead.clear(); m_vVCcSigIncCascDcyBrsIdxOfHead.clear();
      vector<int> vSigIncCascDcyBrsIdxOfHead, vCcSigIncCascDcyBrsIdxOfHead; 
      m_vVSigIncCascDcyBrsMidxOfHead.clear(); m_vVCcSigIncCascDcyBrsMidxOfHead.clear();
      vector<int> vSigIncCascDcyBrsMidxOfHead, vCcSigIncCascDcyBrsMidxOfHead;
      m_vVIIncSigIncCascDcyBrs.clear();
      vector<int> vIIncSigIncCascDcyBrs;
      m_vISigIncCascDcyBrs.clear(); m_vICcSigIncCascDcyBrs.clear();
      m_vNSigIncCascDcyBrs.clear(); m_vNCcSigIncCascDcyBrs.clear();
      vector<int> vCcSigPid12, vCcSigMidx12;
      for(unsigned int i=0;i<m_vVPid_sigIncCascDcyBrs.size();i++)
        {
          sortPs(m_vVPid_sigIncCascDcyBrs[i],m_vVMidx_sigIncCascDcyBrs[i]);
          sigIncCascDcyBrs.clear();      
          vSigIncCascDcyBrsIdxOfHead.clear();
          vSigIncCascDcyBrsMidxOfHead.clear();
          vIIncSigIncCascDcyBrs.clear(); 
          getDcyTr(m_vVPid_sigIncCascDcyBrs[i],m_vVMidx_sigIncCascDcyBrs[i],sigIncCascDcyBrs,vSigIncCascDcyBrsIdxOfHead,vSigIncCascDcyBrsMidxOfHead,vIIncSigIncCascDcyBrs);

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigIncCascDcyBrs.size();j++)
            {
              if(sigIncCascDcyBrs==m_vSigIncCascDcyBrs[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive cascade decay branches is same as the "<<j+1<<ordNumSufj<<" signal inclusive cascade decay branches!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);    
                }
              else if(m_ccSwitch==true&&m_vICcSigIncCascDcyBrs[j]!=0&&sigIncCascDcyBrs==m_vCcSigIncCascDcyBrs[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive cascade decay branches is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal inclusive cascade decay branches!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }                
            }

          m_vSigIncCascDcyBrs.push_back(sigIncCascDcyBrs);
          m_vVSigIncCascDcyBrsIdxOfHead.push_back(vSigIncCascDcyBrsIdxOfHead);
          m_vVSigIncCascDcyBrsMidxOfHead.push_back(vSigIncCascDcyBrsMidxOfHead);
          m_vVIIncSigIncCascDcyBrs.push_back(vIIncSigIncCascDcyBrs);  
          m_vISigIncCascDcyBrs.push_back(m_vSigIncCascDcyBrs.size()-1);
          m_vNSigIncCascDcyBrs.push_back(0);
          if(m_ccSwitch==true)
            {
              vCcSigPid12.clear();
              vCcSigMidx12.clear();
              for(unsigned int j=0;j<m_vVPid_sigIncCascDcyBrs[i].size();j++) vCcSigPid12.push_back(getCcPid(m_vVPid_sigIncCascDcyBrs[i][j])); 
              vCcSigMidx12=m_vVMidx_sigIncCascDcyBrs[i];
              sortPs(vCcSigPid12,vCcSigMidx12);
              ccSigIncCascDcyBrs.clear();
              vCcSigIncCascDcyBrsIdxOfHead.clear();
              vCcSigIncCascDcyBrsMidxOfHead.clear();
              getDcyTr(vCcSigPid12,vCcSigMidx12,ccSigIncCascDcyBrs,vCcSigIncCascDcyBrsIdxOfHead,vCcSigIncCascDcyBrsMidxOfHead);
              m_vCcSigIncCascDcyBrs.push_back(ccSigIncCascDcyBrs);
              m_vVCcSigIncCascDcyBrsIdxOfHead.push_back(vCcSigIncCascDcyBrsIdxOfHead);
              m_vVCcSigIncCascDcyBrsMidxOfHead.push_back(vCcSigIncCascDcyBrsMidxOfHead);
              if(ccSigIncCascDcyBrs==sigIncCascDcyBrs) m_vICcSigIncCascDcyBrs.push_back(0);
              else m_vICcSigIncCascDcyBrs.push_back(1);
              m_vNCcSigIncCascDcyBrs.push_back(0);
            }          
        }

      cout<<"i.e.:"<<endl<<endl;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigIncCascDcyBrs.size();i++)
        { 
          sigIncCascDcyBrs.clear();
          sigIncCascDcyBrs=m_vSigIncCascDcyBrs[i];
          vSigIncCascDcyBrsIdxOfHead=m_vVSigIncCascDcyBrsIdxOfHead[i];
          for(unsigned int j=0;j<sigIncCascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncCascDcyBrs[j];
              cout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              if(j==0&&vSigIncCascDcyBrsIdxOfHead[0]==-1)
                {
                  liit++;
                  writePnmFromPid(cout,"TxtPnm",(*liit));
                }
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncCascDcyBrs[i][j]==1)
                {
                  cout<<" +";
                  writePnmFromPid(cout,"TxtPnm",m_pidOfAnything);
                }
              cout<<endl;
            }
          if(m_vNm_sigIncCascDcyBrs[i]!="")
            {
              cout<<"  Alias for the signal inclusive cascade decay branch is set to be \""<<m_vNm_sigIncCascDcyBrs[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal inclusive cascade decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  if(m_vVPid_sigIRADcyBr.size()==0)
    {
      cout<<"No signal intermediate-resonance-allowed decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal intermediate-resonance-allowed decay branches:"<<endl<<endl;
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
              cout<<"  Alias for the signal intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_sigIRADcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal intermediate-resonance-allowed decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
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
              sigIRADcyBr.push_front(11);
              sigIRADcyBr.push_front(-11);
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
              if((*liit)==-11) liit++;
              for(liit++;liit!=sigIRADcyBr.end();liit++) ccSigIRADcyBr.push_back(getCcPid((*liit)));
              sortByPidAndPchrg(ccSigIRADcyBr);
              liit=sigIRADcyBr.begin();
              if((*liit)!=-11)
                {
                  ccSigIRADcyBr.push_front(getCcPid((*liit)));
                }
              else
                {
                  ccSigIRADcyBr.push_front(11);
                  ccSigIRADcyBr.push_front(-11);
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
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(cout,"TxtPnm",(*liit));
            }
          cout<<" -->";
          for(liit++;liit!=sigIRADcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
          cout<<endl;
          if(m_vNm_sigIRADcyBr[i]!="")
            {
              cout<<"  Alias for the signal intermediate-resonance-allowed decay branch is set to be \""<<m_vNm_sigIRADcyBr[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal intermediate-resonance-allowed decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  if(m_vVPid_sigIncOrIRACascDcyBrs.size()==0)
    {
      cout<<"No signal inclusive or intermediate-resonance-allowed cascade decay branches are specified."<<endl<<endl;
    }
  else
    {
      cout<<"Signal inclusive or intermediate-resonance-allowed cascade decay branches:"<<endl<<endl;
      for(unsigned int i=0;i<m_vVPid_sigIncOrIRACascDcyBrs.size();i++)
	{
          for(unsigned int j=0;j<m_vVPid_sigIncOrIRACascDcyBrs[i].size();j++)
	    {
	      cout<<"  "<<j<<"\t";
              writePnmFromPid(cout,"TxtPnm",m_vVPid_sigIncOrIRACascDcyBrs[i][j]);
              if(m_pidTxtPnmMap[m_vVPid_sigIncOrIRACascDcyBrs[i][j]].size()<7)  cout<<"\t\t\t";
              else if(m_pidTxtPnmMap[m_vVPid_sigIncOrIRACascDcyBrs[i][j]].size()<15) cout<<"\t\t";
              else cout<<"\t";
              cout<<setiosflags(ios::right)<<setw(3)<<m_vVMidx_sigIncOrIRACascDcyBrs[i][j]<<resetiosflags(ios::adjustfield)<<endl;
	    }
          if(m_vNm_sigIncOrIRACascDcyBrs[i]!="")
            {
              cout<<"  Alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set to be \""<<m_vNm_sigIncOrIRACascDcyBrs[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
	}
      cout<<endl;

      m_vSigIncOrIRACascDcyBrs.clear(); m_vCcSigIncOrIRACascDcyBrs.clear();
      vector< list<int> > sigIncOrIRACascDcyBrs, ccSigIncOrIRACascDcyBrs;
      m_vVSigIncOrIRACascDcyBrsIdxOfHead.clear(); m_vVCcSigIncOrIRACascDcyBrsIdxOfHead.clear();
      vector<int> vSigIncOrIRACascDcyBrsIdxOfHead, vCcSigIncOrIRACascDcyBrsIdxOfHead; 
      m_vVSigIncOrIRACascDcyBrsMidxOfHead.clear(); m_vVCcSigIncOrIRACascDcyBrsMidxOfHead.clear();
      vector<int> vSigIncOrIRACascDcyBrsMidxOfHead, vCcSigIncOrIRACascDcyBrsMidxOfHead;
      m_vVIIncSigIncOrIRACascDcyBrs.clear();
      vector<int> vIIncSigIncOrIRACascDcyBrs;
      m_vVIIRASigIncOrIRACascDcyBrs.clear();
      vector<int> vIIRASigIncOrIRACascDcyBrs;      
      m_vISigIncOrIRACascDcyBrs.clear(); m_vICcSigIncOrIRACascDcyBrs.clear();
      m_vNSigIncOrIRACascDcyBrs.clear(); m_vNCcSigIncOrIRACascDcyBrs.clear();
      vector<int> vCcSigPid123, vCcSigMidx123;
      for(unsigned int i=0;i<m_vVPid_sigIncOrIRACascDcyBrs.size();i++)
        {
          sortPs(m_vVPid_sigIncOrIRACascDcyBrs[i],m_vVMidx_sigIncOrIRACascDcyBrs[i]);
          sigIncOrIRACascDcyBrs.clear();
          vSigIncOrIRACascDcyBrsIdxOfHead.clear();
          vSigIncOrIRACascDcyBrsMidxOfHead.clear();
          vIIncSigIncOrIRACascDcyBrs.clear();
          vIIRASigIncOrIRACascDcyBrs.clear();
          getDcyTr(m_vVPid_sigIncOrIRACascDcyBrs[i],m_vVMidx_sigIncOrIRACascDcyBrs[i],sigIncOrIRACascDcyBrs,vSigIncOrIRACascDcyBrsIdxOfHead,vSigIncOrIRACascDcyBrsMidxOfHead,vIIncSigIncOrIRACascDcyBrs,vIIRASigIncOrIRACascDcyBrs);

          string ordNumSufi="th";
          string ordNumSufj="th";
          for(unsigned int j=0;j<m_vSigIncOrIRACascDcyBrs.size();j++)
            {
              if(sigIncOrIRACascDcyBrs==m_vSigIncOrIRACascDcyBrs[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive or intermediate-resonance-allowed cascade decay branches is same as the "<<j+1<<ordNumSufj<<" signal inclusive or intermediate-resonance-allowed cascade decay branches!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);    
                }
              else if(m_ccSwitch==true&&m_vICcSigIncOrIRACascDcyBrs[j]!=0&&sigIncOrIRACascDcyBrs==m_vCcSigIncOrIRACascDcyBrs[j])
                {
                  if(i==0) ordNumSufi="st"; else if(i==1) ordNumSufi="nd"; else if(i==2) ordNumSufi="rd";
                  if(j==0) ordNumSufj="st"; else if(j==1) ordNumSufj="nd"; else if(j==2) ordNumSufj="rd";
                  cerr<<"Error: The "<<i+1<<ordNumSufi<<" signal inclusive or intermediate-resonance-allowed cascade decay branches is same as the charge conjugate counterpart of "<<j+1<<ordNumSufj<<" signal inclusive or intermediate-resonance-allowed cascade decay branches!"<<endl;
                  cerr<<"Infor: Please check the input card and remove one of them."<<endl;
                  exit(-1);
                }                
            }

          m_vSigIncOrIRACascDcyBrs.push_back(sigIncOrIRACascDcyBrs);
          m_vVSigIncOrIRACascDcyBrsIdxOfHead.push_back(vSigIncOrIRACascDcyBrsIdxOfHead);
          m_vVSigIncOrIRACascDcyBrsMidxOfHead.push_back(vSigIncOrIRACascDcyBrsMidxOfHead);
          m_vVIIncSigIncOrIRACascDcyBrs.push_back(vIIncSigIncOrIRACascDcyBrs);
          m_vVIIRASigIncOrIRACascDcyBrs.push_back(vIIRASigIncOrIRACascDcyBrs);
          m_vISigIncOrIRACascDcyBrs.push_back(m_vSigIncOrIRACascDcyBrs.size()-1);
          m_vNSigIncOrIRACascDcyBrs.push_back(0);
          if(m_ccSwitch==true)
            {
              vCcSigPid123.clear();
              vCcSigMidx123.clear();
              for(unsigned int j=0;j<m_vVPid_sigIncOrIRACascDcyBrs[i].size();j++) vCcSigPid123.push_back(getCcPid(m_vVPid_sigIncOrIRACascDcyBrs[i][j])); 
              vCcSigMidx123=m_vVMidx_sigIncOrIRACascDcyBrs[i];
              sortPs(vCcSigPid123,vCcSigMidx123);
              ccSigIncOrIRACascDcyBrs.clear();
              vCcSigIncOrIRACascDcyBrsIdxOfHead.clear();
              vCcSigIncOrIRACascDcyBrsMidxOfHead.clear();
              getDcyTr(vCcSigPid123,vCcSigMidx123,ccSigIncOrIRACascDcyBrs,vCcSigIncOrIRACascDcyBrsIdxOfHead,vCcSigIncOrIRACascDcyBrsMidxOfHead);

              m_vCcSigIncOrIRACascDcyBrs.push_back(ccSigIncOrIRACascDcyBrs);
              m_vVCcSigIncOrIRACascDcyBrsIdxOfHead.push_back(vCcSigIncOrIRACascDcyBrsIdxOfHead);
              m_vVCcSigIncOrIRACascDcyBrsMidxOfHead.push_back(vCcSigIncOrIRACascDcyBrsMidxOfHead);
              if(ccSigIncOrIRACascDcyBrs==sigIncOrIRACascDcyBrs) m_vICcSigIncOrIRACascDcyBrs.push_back(0);
              else m_vICcSigIncOrIRACascDcyBrs.push_back(1);
              m_vNCcSigIncOrIRACascDcyBrs.push_back(0);
            }          
        }

      cout<<"i.e.:"<<endl<<endl;
      list<int> sigDcyBr;
      for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBrs.size();i++)
        { 
          sigIncOrIRACascDcyBrs.clear();
          sigIncOrIRACascDcyBrs=m_vSigIncOrIRACascDcyBrs[i];
          vSigIncOrIRACascDcyBrsIdxOfHead=m_vVSigIncOrIRACascDcyBrsIdxOfHead[i];
          for(unsigned int j=0;j<sigIncOrIRACascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncOrIRACascDcyBrs[j];
              cout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(cout,"TxtPnm",(*liit));
              if(j==0&&vSigIncOrIRACascDcyBrsIdxOfHead[0]==-1)
                {
                  liit++;
                  writePnmFromPid(cout,"TxtPnm",(*liit));
                }
              if(m_vVIIRASigIncOrIRACascDcyBrs[i][j]==1) cout<<" (--> X)";
              cout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(cout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncOrIRACascDcyBrs[i][j]==1)
                {
                  cout<<" +";
                  writePnmFromPid(cout,"TxtPnm",m_pidOfAnything);
                }
              if(m_vVIIncSigIncOrIRACascDcyBrs[i][j]==1&&m_vVIIRASigIncOrIRACascDcyBrs[i][j]==1)
                {
                  cout<<endl<<endl;
                  cerr<<"Error: The Branch is not only inclusive but also . Such Branches are not supported in the current version of the \"TopoAna\" program!"<<endl;
                  cerr<<"Infor: If you really need the function, Please contact me (zhouxy@buaa.edu.cn) and then I will try to implement the function for you."<<endl;
                  exit(-1);
                }
              cout<<endl;
            }
          if(m_vNm_sigIncOrIRACascDcyBrs[i]!="")
            {
              cout<<"  Alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set to be \""<<m_vNm_sigIncOrIRACascDcyBrs[i]<<"\" for the branch names of the topology tags"<<endl<<endl;
            }
          else
            {
              cout<<"  No alias for the signal inclusive or intermediate-resonance-allowed cascade decay branch is set for the branch names of the topology tags (default)"<<endl<<endl;
            }
        }
    }

  bool haveTopoAnaTasks=false;
  if((m_compAnaOfDcyTrs==true)||(m_compAnaOfDcyIFSts==true)||(m_vPid_compDcyBrP.size()!=0)||(m_vPid_compProdBrP.size()!=0)||(m_vPid_compMP.size()!=0)||(m_vVPid_compIncDcyBr.size()!=0)||(m_vVPid_compIRADcyBr.size()!=0)||(m_vVPid_sigDcyTr.size()!=0)||(m_vVPid_sigDcyIFSts2.size()!=0)||(m_vPid_sigP.size()!=0)||(m_vVPid_sigDcyBr.size()!=0)||(m_vVPid_sigIncDcyBr.size()!=0)||(m_vVPid_sigCascDcyBrs.size()!=0)||(m_vVPid_sigIncCascDcyBrs.size()!=0)||(m_vVPid_sigIRADcyBr.size()!=0)||(m_vVPid_sigIncOrIRACascDcyBrs.size()!=0)) haveTopoAnaTasks=true;
  if(haveTopoAnaTasks==false)
    { 
      cerr<<"Error: No topology analysis is set up to be performed!"<<endl;
      cerr<<"Infor: Please check the input card!"<<endl;
      exit(-1);
    }

  if(m_ccSwitch==true)
    {
      cout<<"Charge conjugate objects are processed together."<<endl<<endl;
    }
  else
    {
      cout<<"Charge conjugate objects are not processed together (default)."<<endl<<endl;
    }

  if(m_anaTasksForSigIds=="TC")
    {
      cout<<"Analysis tasks for signal identifications: both tagging and counting (default)."<<endl<<endl;
    }
  else if(m_anaTasksForSigIds=="T")
    {
      cout<<"Analysis tasks for signal identifications: tagging only."<<endl<<endl;
    }
  else if(m_anaTasksForSigIds=="C")
    {
      cout<<"Analysis tasks for signal identifications: counting only."<<endl<<endl;
    }

  if(m_sortTheToposForSigIds==true)
    {
      cout<<"The topologies for signal identifications will be sorted."<<endl<<endl;
    }
  else
    {
      cout<<"The topologies for signal identifications will not be sorted (default)."<<endl<<endl;
    }

  if(m_initEpEmSwitch==true)
    {
      cout<<"The initial e+ and e- are required to be involved uniformly in all the events."<<endl<<endl;
    }
  else
    {
      cout<<"The initial e+ and e- are not required to be involved uniformly in all the events (default)."<<endl<<endl;
    }

  if((m_cardFlNm.size()>5&&m_mainNmOfOptFls!=m_cardFlNm.substr(0,(m_cardFlNm.size()-5)))&&(m_mainNmOfOptFls!=m_cardFlNm))
    {
      cout<<"Main name of output files: "<<m_mainNmOfOptFls<<endl<<endl;
    }
  else
    {
      cout<<"Main name of output files: "<<m_mainNmOfOptFls<<" (default)"<<endl<<endl;
    }

  if(m_centDcyObjs==true)
    {
      cout<<"The decay objects in the output pdf files are required to be centered."<<endl<<endl;
    }
  else
    {
      cout<<"The decay objects in the output pdf files are not required to be centered (default)."<<endl<<endl;
    }

  if(m_sprTopoTags==true)
    {
      cout<<"The topology tags in the output pdf files are suppressed."<<endl<<endl;
    }
  else
    {
      cout<<"The topology tags in the output pdf files are not suppressed (default)."<<endl<<endl;
    }

  if(m_oneOptRootFlByOneIptRootFl==true)
    {
      cout<<"Output mode of root files: one output root file by one input root file."<<endl<<endl;
    }
  else
    {
      cout<<"Output mode of root files: only one output root file by default. If oversize, it will be splitted into multiple files according to the size of the TTree object in memory by default. In addition, users can can specify the maximum number of entries to be saved in a single output root file by another item (default)."<<endl<<endl;

      if(m_nEtrsMaxInASngOptRootFl!=ULONG_MAX)
        {
          cout<<"Maximum number of entries to be saved in a single output root file:"<<m_nEtrsMaxInASngOptRootFl<<endl<<endl;
        }
      else
        {
          cout<<"Upper limit of the total bytes of the cloned TTree object of "<<m_trNm<<": 3 GB in memory (default)."<<endl<<endl;
        }
    }

  if(m_useArrayBrsOpt==true)
    {
      cout<<"Array branches are used to store topology tags in the output root files when possible."<<endl<<endl;
    }
  else
    {
      cout<<"Flat branches are used to store topology tags in the output root files when possible (default)."<<endl<<endl;
    }

  if(m_cpIptBrs==true)
    {
      cout<<"The input branches will be copied to the output root files (default)."<<endl<<endl;
    }
  else
    {
      cout<<"The input branches will not be copied to the output root files."<<endl<<endl;
    }
}
