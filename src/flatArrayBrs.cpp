#include "../include/topoana.h"
#include "TFile.h"
#include <iostream>
#include <cstdlib>
#include "TTree.h"
#include "TBranch.h"

void topoana::flatArrayBrs(string nmOfOptRootFl)
{
  unsigned int vAtdbPid_size=m_vPid_compDcyBrP.size();
  unsigned int vAtpbPid_size=m_vPid_compProdBrP.size();
  unsigned int vAtmPid_size=m_vPid_compMP.size();
  unsigned int vAtecIncDcyBr_size=m_vCompIncDcyBr.size(); 
  unsigned int vAtisIRADcyBr_size=m_vCompIRADcyBr.size();

  if(vAtdbPid_size<1&&vAtpbPid_size<1&&vAtmPid_size<1&&vAtecIncDcyBr_size<1&&vAtisIRADcyBr_size<1) return;

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

  char nm[20],nm2[20],specifier1[100],specifier2[100],specifier3[100],specifier4[100];

  if(vAtdbPid_size>0)
    {
      for(unsigned int i=0;i<vAtdbPid_size;i++)
        {
          if(m_vNm_compDcyBrP[i].empty())
            {
              sprintf(nm, "_P%d_DcyBr", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_DcyBr", m_vNm_compDcyBrP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compDcyBrP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompDcyBrP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm2);
                  sprintf(specifier3, "iCcDcyBr%s", nm2);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm2);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                  tr_old->SetBranchStatus(specifier4,0);
                }
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iDcyBr%s", nm2);
              tr_old->SetBranchStatus(specifier1,0);
              tr_old->SetBranchStatus(specifier2,0);
            }
        }
    }
  if(vAtpbPid_size>0)
    {
      for(unsigned int i=0;i<vAtpbPid_size;i++)
        {
          if(m_vNm_compProdBrP[i].empty())
            {
              sprintf(nm, "_P%d_ProdBr", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_ProdBr", m_vNm_compProdBrP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compProdBrP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompProdBrP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iProdBr%s", nm2);
                  sprintf(specifier3, "iCcProdBr%s", nm2);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iProdBr%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iProdBrCc%s", nm2);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                  tr_old->SetBranchStatus(specifier4,0);
                }
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iProdBr%s", nm2);
              tr_old->SetBranchStatus(specifier1,0);
              tr_old->SetBranchStatus(specifier2,0);
            }
        }
    }
  if(vAtmPid_size>0)
    {
      for(unsigned int i=0;i<vAtmPid_size;i++)
        {
          if(m_vNm_compMP[i].empty())
            {
              sprintf(nm, "_P%d_Moth", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_Moth", m_vNm_compMP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compMP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompMP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "MothPDG%s", nm2);
                  sprintf(specifier3, "iCcMoth%s", nm2);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "MothPDG%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "MothPDGCc%s", nm2);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                  tr_old->SetBranchStatus(specifier4,0);
                }
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "MothPDG%s", nm2);
              tr_old->SetBranchStatus(specifier1,0);
              tr_old->SetBranchStatus(specifier2,0);
            }
        }
    }
  if(vAtecIncDcyBr_size>0)
    {
      for(unsigned int i=0;i<vAtecIncDcyBr_size;i++)
        {
          if(m_vNm_compIncDcyBr[i].empty()) sprintf(nm, "IncDcyBr%d", i);
          else sprintf(nm, "_%s", m_vNm_compIncDcyBr[i].c_str());
          // else strcpy(nm, m_vNm_compIncDcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nm".
          if(m_ccSwitch==true)
            {
              if(m_vCompICcIncDcyBr[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "iCcDcyBr%s", nm);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                  tr_old->SetBranchStatus(specifier4,0);
                }
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iDcyBr%s", nm);
              tr_old->SetBranchStatus(specifier1,0);
              tr_old->SetBranchStatus(specifier2,0);
            }
        }
    }
  if(vAtisIRADcyBr_size>0)
    {
      for(unsigned int i=0;i<vAtisIRADcyBr_size;i++)
        {
          if(m_vNm_compIRADcyBr[i].empty()) sprintf(nm, "IRADcyBr%d", i);
          else sprintf(nm, "_%s", m_vNm_compIRADcyBr[i].c_str());
          // else strcpy(nm, m_vNm_compIRADcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nm".
          if(m_ccSwitch==true)
            {
              if(m_vCompICcIRADcyBr[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "iCcDcyBr%s", nm);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm);
                  tr_old->SetBranchStatus(specifier1,0);
                  tr_old->SetBranchStatus(specifier2,0);
                  tr_old->SetBranchStatus(specifier3,0);
                  tr_old->SetBranchStatus(specifier4,0);
                }
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iDcyBr%s", nm);
              tr_old->SetBranchStatus(specifier1,0);
              tr_old->SetBranchStatus(specifier2,0);
            }
        }
    }

  TTree *tr_new=tr_old->CloneTree(0);

  unsigned int nPIMax_DcyBr[vAtdbPid_size],nCcPIMax_DcyBr[vAtdbPid_size];
  unsigned int nPIMax_Max_DcyBr=0,nCcPIMax_Max_DcyBr=0;
  unsigned int nPIMax_ProdBr[vAtpbPid_size],nCcPIMax_ProdBr[vAtpbPid_size];
  unsigned int nPIMax_Max_ProdBr=0,nCcPIMax_Max_ProdBr=0;
  unsigned int nPIMax_Moth[vAtmPid_size],nCcPIMax_Moth[vAtmPid_size];
  unsigned int nPIMax_Max_Moth=0,nCcPIMax_Max_Moth=0;
  unsigned int nIncDcyBrIMax[vAtecIncDcyBr_size],nCcIncDcyBrIMax[vAtecIncDcyBr_size];
  unsigned int nIncDcyBrIMaxMax=0,nCcIncDcyBrIMaxMax=0;
  unsigned int nIRADcyBrIMax[vAtisIRADcyBr_size],nCcIRADcyBrIMax[vAtisIRADcyBr_size];
  unsigned int nIRADcyBrIMaxMax=0,nCcIRADcyBrIMaxMax=0;
  if(vAtdbPid_size>0)
    {
      for(unsigned int i=0;i<vAtdbPid_size;i++)
        {
          if(m_vNm_compDcyBrP[i].empty())
            {
              sprintf(nm, "_P%d_DcyBr", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_DcyBr", m_vNm_compDcyBrP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compDcyBrP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompDcyBrP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm2);
                  sprintf(specifier3, "iCcDcyBr%s", nm2);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  nPIMax_DcyBr[i]=tr_old->GetMaximum(specifier1);
                  if(nPIMax_DcyBr[i]>nPIMax_Max_DcyBr) nPIMax_Max_DcyBr=nPIMax_DcyBr[i];                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm2);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  tr_old->SetBranchStatus(specifier4, 1);
                  nPIMax_DcyBr[i]=tr_old->GetMaximum(specifier1);
                  if(nPIMax_DcyBr[i]>nPIMax_Max_DcyBr) nPIMax_Max_DcyBr=nPIMax_DcyBr[i];                
                  nCcPIMax_DcyBr[i]=tr_old->GetMaximum(specifier3);
                  if(nCcPIMax_DcyBr[i]>nCcPIMax_Max_DcyBr) nCcPIMax_Max_DcyBr=nCcPIMax_DcyBr[i];
                }
            }   
          else 
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iDcyBr%s", nm2);
              tr_old->SetBranchStatus(specifier1, 1);
              tr_old->SetBranchStatus(specifier2, 1);
              nPIMax_DcyBr[i]=tr_old->GetMaximum(specifier1);
              if(nPIMax_DcyBr[i]>nPIMax_Max_DcyBr) nPIMax_Max_DcyBr=nPIMax_DcyBr[i];
            }
        }
    }
  if(vAtpbPid_size>0)
    {
      for(unsigned int i=0;i<vAtpbPid_size;i++)
        {
          if(m_vNm_compProdBrP[i].empty())
            {
              sprintf(nm, "_P%d_ProdBr", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_ProdBr", m_vNm_compProdBrP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compProdBrP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompProdBrP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iProdBr%s", nm2);
                  sprintf(specifier3, "iCcProdBr%s", nm2);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  nPIMax_ProdBr[i]=tr_old->GetMaximum(specifier1);
                  if(nPIMax_ProdBr[i]>nPIMax_Max_ProdBr) nPIMax_Max_ProdBr=nPIMax_ProdBr[i];                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iProdBr%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iProdBrCc%s", nm2);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  tr_old->SetBranchStatus(specifier4, 1);
                  nPIMax_ProdBr[i]=tr_old->GetMaximum(specifier1);
                  if(nPIMax_ProdBr[i]>nPIMax_Max_ProdBr) nPIMax_Max_ProdBr=nPIMax_ProdBr[i];                
                  nCcPIMax_ProdBr[i]=tr_old->GetMaximum(specifier3);
                  if(nCcPIMax_ProdBr[i]>nCcPIMax_Max_ProdBr) nCcPIMax_Max_ProdBr=nCcPIMax_ProdBr[i];
                }
            }   
          else 
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iProdBr%s", nm2);
              tr_old->SetBranchStatus(specifier1, 1);
              tr_old->SetBranchStatus(specifier2, 1);
              nPIMax_ProdBr[i]=tr_old->GetMaximum(specifier1);
              if(nPIMax_ProdBr[i]>nPIMax_Max_ProdBr) nPIMax_Max_ProdBr=nPIMax_ProdBr[i];
            }
        }
    }
  if(vAtmPid_size>0)
    {
      for(unsigned int i=0;i<vAtmPid_size;i++)
        {
          if(m_vNm_compMP[i].empty())
            {
              sprintf(nm, "_P%d_Moth", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_Moth", m_vNm_compMP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compMP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompMP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "MothPDG%s", nm2);
                  sprintf(specifier3, "iCcMoth%s", nm2);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  nPIMax_Moth[i]=tr_old->GetMaximum(specifier1);
                  if(nPIMax_Moth[i]>nPIMax_Max_Moth) nPIMax_Max_Moth=nPIMax_Moth[i];                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "MothPDG%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "MothPDGCc%s", nm2);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  tr_old->SetBranchStatus(specifier4, 1);
                  nPIMax_Moth[i]=tr_old->GetMaximum(specifier1);
                  if(nPIMax_Moth[i]>nPIMax_Max_Moth) nPIMax_Max_Moth=nPIMax_Moth[i];                
                  nCcPIMax_Moth[i]=tr_old->GetMaximum(specifier3);
                  if(nCcPIMax_Moth[i]>nCcPIMax_Max_Moth) nCcPIMax_Max_Moth=nCcPIMax_Moth[i];
                }
            }   
          else 
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "MothPDG%s", nm2);
              tr_old->SetBranchStatus(specifier1, 1);
              tr_old->SetBranchStatus(specifier2, 1);
              nPIMax_Moth[i]=tr_old->GetMaximum(specifier1);
              if(nPIMax_Moth[i]>nPIMax_Max_Moth) nPIMax_Max_Moth=nPIMax_Moth[i];
            }
        }
    }
  if(vAtecIncDcyBr_size>0)
    {
      for(unsigned int i=0;i<vAtecIncDcyBr_size;i++)
        {
          if(m_vNm_compIncDcyBr[i].empty()) sprintf(nm, "IncDcyBr%d", i);
          else sprintf(nm, "_%s", m_vNm_compIncDcyBr[i].c_str());
          // else strcpy(nm, m_vNm_compIncDcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nm".
          if(m_ccSwitch==true)
            {
              if(m_vCompICcIncDcyBr[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "iCcDcyBr%s", nm);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  nIncDcyBrIMax[i]=tr_old->GetMaximum(specifier1);
                  if(nIncDcyBrIMax[i]>nIncDcyBrIMaxMax) nIncDcyBrIMaxMax=nIncDcyBrIMax[i];              
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  tr_old->SetBranchStatus(specifier4, 1);
                  nIncDcyBrIMax[i]=tr_old->GetMaximum(specifier1);
                  if(nIncDcyBrIMax[i]>nIncDcyBrIMaxMax) nIncDcyBrIMaxMax=nIncDcyBrIMax[i];
                  nCcIncDcyBrIMax[i]=tr_old->GetMaximum(specifier3);
                  if(nCcIncDcyBrIMax[i]>nCcIncDcyBrIMaxMax) nCcIncDcyBrIMaxMax=nCcIncDcyBrIMax[i];                
                }
            }   
          else 
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iDcyBr%s", nm);
              tr_old->SetBranchStatus(specifier1,1);
              tr_old->SetBranchStatus(specifier2,1);
              nIncDcyBrIMax[i]=tr_old->GetMaximum(specifier1);
              if(nIncDcyBrIMax[i]>nIncDcyBrIMaxMax) nIncDcyBrIMaxMax=nIncDcyBrIMax[i];
            }
        }
    }
  if(vAtisIRADcyBr_size>0)
    {
      for(unsigned int i=0;i<vAtisIRADcyBr_size;i++)
        {
          if(m_vNm_compIRADcyBr[i].empty()) sprintf(nm, "IRADcyBr%d", i);
          else sprintf(nm, "_%s", m_vNm_compIRADcyBr[i].c_str());
          // else strcpy(nm, m_vNm_compIRADcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nm".
          if(m_ccSwitch==true)
            {
              if(m_vCompICcIRADcyBr[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "iCcDcyBr%s", nm);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  nIRADcyBrIMax[i]=tr_old->GetMaximum(specifier1);
                  if(nIRADcyBrIMax[i]>nIRADcyBrIMaxMax) nIRADcyBrIMaxMax=nIRADcyBrIMax[i];                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm);
                  tr_old->SetBranchStatus(specifier1, 1);
                  tr_old->SetBranchStatus(specifier2, 1);
                  tr_old->SetBranchStatus(specifier3, 1);
                  tr_old->SetBranchStatus(specifier4, 1);
                  nIRADcyBrIMax[i]=tr_old->GetMaximum(specifier1);
                  if(nIRADcyBrIMax[i]>nIRADcyBrIMaxMax) nIRADcyBrIMaxMax=nIRADcyBrIMax[i];
                  nCcIRADcyBrIMax[i]=tr_old->GetMaximum(specifier3);
                  if(nCcIRADcyBrIMax[i]>nCcIRADcyBrIMaxMax) nCcIRADcyBrIMaxMax=nCcIRADcyBrIMax[i];                
                }
            }   
          else 
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iDcyBr%s", nm);
              tr_old->SetBranchStatus(specifier1,1);
              tr_old->SetBranchStatus(specifier2,1);
              nIRADcyBrIMax[i]=tr_old->GetMaximum(specifier1);
              if(nIRADcyBrIMax[i]>nIRADcyBrIMaxMax) nIRADcyBrIMaxMax=nIRADcyBrIMax[i];
            }
        }
    }

  int nPI_DcyBr[vAtdbPid_size],iDcyBrPI[vAtdbPid_size][nPIMax_Max_DcyBr],iCcDcyBrPI[vAtdbPid_size][nPIMax_Max_DcyBr],nCcPI_DcyBr[vAtdbPid_size],iDcyBrCcPI[vAtdbPid_size][nCcPIMax_Max_DcyBr];
  int nPI_ProdBr[vAtpbPid_size],iProdBrPI[vAtpbPid_size][nPIMax_Max_ProdBr],iCcProdBrPI[vAtpbPid_size][nPIMax_Max_ProdBr],nCcPI_ProdBr[vAtpbPid_size],iProdBrCcPI[vAtpbPid_size][nCcPIMax_Max_ProdBr];
  int nPI_Moth[vAtmPid_size],MothPDGPI[vAtmPid_size][nPIMax_Max_Moth],iCcMothPI[vAtmPid_size][nPIMax_Max_Moth],nCcPI_Moth[vAtmPid_size],MothPDGCcPI[vAtmPid_size][nCcPIMax_Max_Moth];
  int nIncDcyBrI[vAtecIncDcyBr_size],iDcyBrIncDcyBrI[vAtecIncDcyBr_size][nIncDcyBrIMaxMax],iCcDcyBrIncDcyBrI[vAtecIncDcyBr_size][nIncDcyBrIMaxMax],nCcIncDcyBrI[vAtecIncDcyBr_size],iDcyBrCcIncDcyBrI[vAtecIncDcyBr_size][nCcIncDcyBrIMaxMax];
  int nIRADcyBrI[vAtisIRADcyBr_size],iDcyBrIRADcyBrI[vAtisIRADcyBr_size][nIRADcyBrIMaxMax],iCcDcyBrIRADcyBrI[vAtisIRADcyBr_size][nIRADcyBrIMaxMax],nCcIRADcyBrI[vAtisIRADcyBr_size],iDcyBrCcIRADcyBrI[vAtisIRADcyBr_size][nCcIRADcyBrIMaxMax];
  if(vAtdbPid_size>0)
    {
      for(unsigned int i=0;i<vAtdbPid_size;i++)
        {
          if(m_vNm_compDcyBrP[i].empty())
            {
              sprintf(nm, "_P%d_DcyBr", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_DcyBr", m_vNm_compDcyBrP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compDcyBrP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompDcyBrP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm2);
                  sprintf(specifier3, "iCcDcyBr%s", nm2);
                  tr_old->SetBranchAddress(specifier1, &nPI_DcyBr[i]);
                  tr_old->SetBranchAddress(specifier2, &iDcyBrPI[i]);
                  tr_old->SetBranchAddress(specifier3, &iCcDcyBrPI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nPI_DcyBr[i], specifier2);
                  for(unsigned int j=0;j<nPIMax_DcyBr[i];j++)
                    {
                      sprintf(specifier1, "iDcyBr%s_%d", nm2, j);
                      sprintf(specifier2, "iDcyBr%s_%d/I", nm2, j);
                      sprintf(specifier3, "iCcDcyBr%s_%d", nm2, j);
                      sprintf(specifier4, "iCcDcyBr%s_%d/I", nm2, j);
                      tr_new->Branch(specifier1, &iDcyBrPI[i][j], specifier2);
                      tr_new->Branch(specifier3, &iCcDcyBrPI[i][j], specifier4);
                    }                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm2);
                  tr_old->SetBranchAddress(specifier1, &nPI_DcyBr[i]);
                  tr_old->SetBranchAddress(specifier2, &iDcyBrPI[i]);
                  tr_old->SetBranchAddress(specifier3, &nCcPI_DcyBr[i]);
                  tr_old->SetBranchAddress(specifier4, &iDcyBrCcPI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nPI_DcyBr[i], specifier2);
                  for(unsigned int j=0;j<nPIMax_DcyBr[i];j++)
                    {
                      sprintf(specifier1, "iDcyBr%s_%d", nm2, j);
                      sprintf(specifier2, "iDcyBr%s_%d/I", nm2, j);
                      tr_new->Branch(specifier1, &iDcyBrPI[i][j], specifier2);
                    }
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "nCc%s/I", nm);
                  tr_new->Branch(specifier3, &nCcPI_DcyBr[i], specifier4);
                  for(unsigned int j=0;j<nCcPIMax_DcyBr[i];j++)
                    {
                      sprintf(specifier3, "iDcyBrCc%s_%d", nm2, j);
                      sprintf(specifier4, "iDcyBrCc%s_%d/I", nm2, j);
                      tr_new->Branch(specifier3, &iDcyBrCcPI[i][j], specifier4);
                    }
                }
            }
          else 
            {
              sprintf(specifier1, "n%s", nm); 
              sprintf(specifier2, "iDcyBr%s", nm2);
              tr_old->SetBranchAddress(specifier1,&nPI_DcyBr[i]);
              tr_old->SetBranchAddress(specifier2,&iDcyBrPI[i]);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr_new->Branch(specifier1, &nPI_DcyBr[i], specifier2);
              for(unsigned int j=0;j<nPIMax_DcyBr[i];j++)
                {
                  sprintf(specifier1, "iDcyBr%s_%d", nm2, j);
                  sprintf(specifier2, "iDcyBr%s_%d/I", nm2, j);
                  tr_new->Branch(specifier1, &iDcyBrPI[i][j], specifier2);
                }
            }
        }
    }
  if(vAtpbPid_size>0)
    {
      for(unsigned int i=0;i<vAtpbPid_size;i++)
        {
          if(m_vNm_compProdBrP[i].empty())
            {
              sprintf(nm, "_P%d_ProdBr", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_ProdBr", m_vNm_compProdBrP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compProdBrP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompProdBrP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iProdBr%s", nm2);
                  sprintf(specifier3, "iCcProdBr%s", nm2);
                  tr_old->SetBranchAddress(specifier1, &nPI_ProdBr[i]);
                  tr_old->SetBranchAddress(specifier2, &iProdBrPI[i]);
                  tr_old->SetBranchAddress(specifier3, &iCcProdBrPI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nPI_ProdBr[i], specifier2);
                  for(unsigned int j=0;j<nPIMax_ProdBr[i];j++)
                    {
                      sprintf(specifier1, "iProdBr%s_%d", nm2, j);
                      sprintf(specifier2, "iProdBr%s_%d/I", nm2, j);
                      sprintf(specifier3, "iCcProdBr%s_%d", nm2, j);
                      sprintf(specifier4, "iCcProdBr%s_%d/I", nm2, j);
                      tr_new->Branch(specifier1, &iProdBrPI[i][j], specifier2);
                      tr_new->Branch(specifier3, &iCcProdBrPI[i][j], specifier4);
                    }                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iProdBr%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iProdBrCc%s", nm2);
                  tr_old->SetBranchAddress(specifier1, &nPI_ProdBr[i]);
                  tr_old->SetBranchAddress(specifier2, &iProdBrPI[i]);
                  tr_old->SetBranchAddress(specifier3, &nCcPI_ProdBr[i]);
                  tr_old->SetBranchAddress(specifier4, &iProdBrCcPI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nPI_ProdBr[i], specifier2);
                  for(unsigned int j=0;j<nPIMax_ProdBr[i];j++)
                    {
                      sprintf(specifier1, "iProdBr%s_%d", nm2, j);
                      sprintf(specifier2, "iProdBr%s_%d/I", nm2, j);
                      tr_new->Branch(specifier1, &iProdBrPI[i][j], specifier2);
                    }
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "nCc%s/I", nm);
                  tr_new->Branch(specifier3, &nCcPI_ProdBr[i], specifier4);
                  for(unsigned int j=0;j<nCcPIMax_ProdBr[i];j++)
                    {
                      sprintf(specifier3, "iProdBrCc%s_%d", nm2, j);
                      sprintf(specifier4, "iProdBrCc%s_%d/I", nm2, j);
                      tr_new->Branch(specifier3, &iProdBrCcPI[i][j], specifier4);
                    }
                }
            }
          else 
            {
              sprintf(specifier1, "n%s", nm); 
              sprintf(specifier2, "iProdBr%s", nm2);
              tr_old->SetBranchAddress(specifier1,&nPI_ProdBr[i]);
              tr_old->SetBranchAddress(specifier2,&iProdBrPI[i]);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr_new->Branch(specifier1, &nPI_ProdBr[i], specifier2);
              for(unsigned int j=0;j<nPIMax_ProdBr[i];j++)
                {
                  sprintf(specifier1, "iProdBr%s_%d", nm2, j);
                  sprintf(specifier2, "iProdBr%s_%d/I", nm2, j);
                  tr_new->Branch(specifier1, &iProdBrPI[i][j], specifier2);
                }
            }
        }
    }
  if(vAtmPid_size>0)
    {
      for(unsigned int i=0;i<vAtmPid_size;i++)
        {
          if(m_vNm_compMP[i].empty())
            {
              sprintf(nm, "_P%d_Moth", i);
              sprintf(nm2, "_P%d", i);
            }
          else
            {
              sprintf(nm, "_%s_Moth", m_vNm_compMP[i].c_str());
              sprintf(nm2, "_%s", m_vNm_compMP[i].c_str());
            }
          if(m_ccSwitch==true)
            {
              if(m_vICcCompMP[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "MothPDG%s", nm2);
                  sprintf(specifier3, "iCcMoth%s", nm2);
                  tr_old->SetBranchAddress(specifier1, &nPI_Moth[i]);
                  tr_old->SetBranchAddress(specifier2, &MothPDGPI[i]);
                  tr_old->SetBranchAddress(specifier3, &iCcMothPI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nPI_Moth[i], specifier2);
                  for(unsigned int j=0;j<nPIMax_Moth[i];j++)
                    {
                      sprintf(specifier1, "MothPDG%s_%d", nm2, j);
                      sprintf(specifier2, "MothPDG%s_%d/I", nm2, j);
                      sprintf(specifier3, "iCcMoth%s_%d", nm2, j);
                      sprintf(specifier4, "iCcMoth%s_%d/I", nm2, j);
                      tr_new->Branch(specifier1, &MothPDGPI[i][j], specifier2);
                      tr_new->Branch(specifier3, &iCcMothPI[i][j], specifier4);
                    }                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "MothPDG%s", nm2);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "MothPDGCc%s", nm2);
                  tr_old->SetBranchAddress(specifier1, &nPI_Moth[i]);
                  tr_old->SetBranchAddress(specifier2, &MothPDGPI[i]);
                  tr_old->SetBranchAddress(specifier3, &nCcPI_Moth[i]);
                  tr_old->SetBranchAddress(specifier4, &MothPDGCcPI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nPI_Moth[i], specifier2);
                  for(unsigned int j=0;j<nPIMax_Moth[i];j++)
                    {
                      sprintf(specifier1, "MothPDG%s_%d", nm2, j);
                      sprintf(specifier2, "MothPDG%s_%d/I", nm2, j);
                      tr_new->Branch(specifier1, &MothPDGPI[i][j], specifier2);
                    }
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "nCc%s/I", nm);
                  tr_new->Branch(specifier3, &nCcPI_Moth[i], specifier4);
                  for(unsigned int j=0;j<nCcPIMax_Moth[i];j++)
                    {
                      sprintf(specifier3, "MothPDGCc%s_%d", nm2, j);
                      sprintf(specifier4, "MothPDGCc%s_%d/I", nm2, j);
                      tr_new->Branch(specifier3, &MothPDGCcPI[i][j], specifier4);
                    }
                }
            }
          else 
            {
              sprintf(specifier1, "n%s", nm); 
              sprintf(specifier2, "MothPDG%s", nm2);
              tr_old->SetBranchAddress(specifier1,&nPI_Moth[i]);
              tr_old->SetBranchAddress(specifier2,&MothPDGPI[i]);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr_new->Branch(specifier1, &nPI_Moth[i], specifier2);
              for(unsigned int j=0;j<nPIMax_Moth[i];j++)
                {
                  sprintf(specifier1, "MothPDG%s_%d", nm2, j);
                  sprintf(specifier2, "MothPDG%s_%d/I", nm2, j);
                  tr_new->Branch(specifier1, &MothPDGPI[i][j], specifier2);
                }
            }
        }
    }
  if(vAtecIncDcyBr_size>0)
    { 
      for(unsigned int i=0;i<vAtecIncDcyBr_size;i++)
        {
          if(m_vNm_compIncDcyBr[i].empty()) sprintf(nm, "IncDcyBr%d", i);
          else sprintf(nm, "_%s", m_vNm_compIncDcyBr[i].c_str());
          // else strcpy(nm, m_vNm_compIncDcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nm".
          if(m_ccSwitch==true)
            {
              if(m_vCompICcIncDcyBr[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "iCcDcyBr%s", nm);
                  tr_old->SetBranchAddress(specifier1, &nIncDcyBrI[i]);
                  tr_old->SetBranchAddress(specifier2, &iDcyBrIncDcyBrI[i]);
                  tr_old->SetBranchAddress(specifier3, &iCcDcyBrIncDcyBrI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nIncDcyBrI[i], specifier2);
                  for(unsigned int j=0;j<nIncDcyBrIMax[i];j++)
                    {
                      sprintf(specifier1, "iDcyBr%s_%d", nm, j);
                      sprintf(specifier2, "iDcyBr%s_%d/I", nm, j);
                      sprintf(specifier3, "iCcDcyBr%s_%d", nm, j);
                      sprintf(specifier4, "iCcDcyBr%s_%d/I", nm, j);
                      tr_new->Branch(specifier1, &iDcyBrIncDcyBrI[i][j], specifier2);
                      tr_new->Branch(specifier3, &iCcDcyBrIncDcyBrI[i][j], specifier4);
                    }                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm);
                  tr_old->SetBranchAddress(specifier1, &nIncDcyBrI[i]);
                  tr_old->SetBranchAddress(specifier2, &iDcyBrIncDcyBrI[i]);
                  tr_old->SetBranchAddress(specifier3, &nCcIncDcyBrI[i]);
                  tr_old->SetBranchAddress(specifier4, &iDcyBrCcIncDcyBrI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nIncDcyBrI[i], specifier2);
                  for(unsigned int j=0;j<nIncDcyBrIMax[i];j++)
                    {
                      sprintf(specifier1, "iDcyBr%s_%d", nm, j);
                      sprintf(specifier2, "iDcyBr%s_%d/I", nm, j);
                      tr_new->Branch(specifier1, &iDcyBrIncDcyBrI[i][j], specifier2);
                    }
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "nCc%s/I", nm);
                  tr_new->Branch(specifier3, &nCcIncDcyBrI[i], specifier4);
                  for(unsigned int j=0;j<nCcIncDcyBrIMax[i];j++)
                    {
                      sprintf(specifier3, "iDcyBrCc%s_%d", nm, j);
                      sprintf(specifier4, "iDcyBrCc%s_%d/I", nm, j);
                      tr_new->Branch(specifier3, &iDcyBrCcIncDcyBrI[i][j], specifier4);
                    }                
                }
            }   
          else 
            {
              sprintf(specifier1, "n%s", nm); 
              sprintf(specifier2, "iDcyBr%s", nm);
              tr_old->SetBranchAddress(specifier1,&nIncDcyBrI[i]);
              tr_old->SetBranchAddress(specifier2,&iDcyBrIncDcyBrI[i]);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr_new->Branch(specifier1, &nIncDcyBrI[i], specifier2);
              for(unsigned int j=0;j<nIncDcyBrIMax[i];j++)
                {
                  sprintf(specifier1, "iDcyBr%s_%d", nm, j);
                  sprintf(specifier2, "iDcyBr%s_%d/I", nm, j);
                  tr_new->Branch(specifier1, &iDcyBrIncDcyBrI[i][j], specifier2);
                }
            }
        }
    }
  if(vAtecIncDcyBr_size>0)
    {
      for(unsigned int i=0;i<vAtisIRADcyBr_size;i++)
        {
          if(m_vNm_compIRADcyBr[i].empty()) sprintf(nm, "IRADcyBr%d", i);
          else sprintf(nm, "_%s", m_vNm_compIRADcyBr[i].c_str());
          // else strcpy(nm, m_vNm_compIRADcyBr[i].c_str()); // The statement is used for assign a value without the underscore "_" to the variable "nm".
          if(m_ccSwitch==true)
            {
              if(m_vCompICcIRADcyBr[i]==0)
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "iCcDcyBr%s", nm);
                  tr_old->SetBranchAddress(specifier1, &nIRADcyBrI[i]);
                  tr_old->SetBranchAddress(specifier2, &iDcyBrIRADcyBrI[i]);
                  tr_old->SetBranchAddress(specifier3, &iCcDcyBrIRADcyBrI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nIRADcyBrI[i], specifier2);
                  for(unsigned int j=0;j<nIRADcyBrIMax[i];j++)
                    {
                      sprintf(specifier1, "iDcyBr%s_%d", nm, j);
                      sprintf(specifier2, "iDcyBr%s_%d/I", nm, j);
                      sprintf(specifier3, "iCcDcyBr%s_%d", nm, j);
                      sprintf(specifier4, "iCcDcyBr%s_%d/I", nm, j);
                      tr_new->Branch(specifier1, &iDcyBrIRADcyBrI[i][j], specifier2);
                      tr_new->Branch(specifier3, &iCcDcyBrIRADcyBrI[i][j], specifier4);
                    }                
                }
              else
                {
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "iDcyBr%s", nm);
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "iDcyBrCc%s", nm);
                  tr_old->SetBranchAddress(specifier1, &nIRADcyBrI[i]);
                  tr_old->SetBranchAddress(specifier2, &iDcyBrIRADcyBrI[i]);
                  tr_old->SetBranchAddress(specifier3, &nCcIRADcyBrI[i]);
                  tr_old->SetBranchAddress(specifier4, &iDcyBrCcIRADcyBrI[i]);
                  sprintf(specifier1, "n%s", nm);
                  sprintf(specifier2, "n%s/I", nm);
                  tr_new->Branch(specifier1, &nIRADcyBrI[i], specifier2);
                  for(unsigned int j=0;j<nIRADcyBrIMax[i];j++)
                    {
                      sprintf(specifier1, "iDcyBr%s_%d", nm, j);
                      sprintf(specifier2, "iDcyBr%s_%d/I", nm, j);
                      tr_new->Branch(specifier1, &iDcyBrIRADcyBrI[i][j], specifier2);
                    }
                  sprintf(specifier3, "nCc%s", nm);
                  sprintf(specifier4, "nCc%s/I", nm);
                  tr_new->Branch(specifier3, &nCcIRADcyBrI[i], specifier4);
                  for(unsigned int j=0;j<nCcIRADcyBrIMax[i];j++)
                    {
                      sprintf(specifier3, "iDcyBrCc%s_%d", nm, j);
                      sprintf(specifier4, "iDcyBrCc%s_%d/I", nm, j);
                      tr_new->Branch(specifier3, &iDcyBrCcIRADcyBrI[i][j], specifier4);
                    }                
                }
            }   
          else 
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "iDcyBr%s", nm);
              tr_old->SetBranchAddress(specifier1,&nIRADcyBrI[i]);
              tr_old->SetBranchAddress(specifier2,&iDcyBrIRADcyBrI[i]);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr_new->Branch(specifier1, &nIRADcyBrI[i], specifier2);
              for(unsigned int j=0;j<nIRADcyBrIMax[i];j++)
                {
                  sprintf(specifier1, "iDcyBr%s_%d", nm, j);
                  sprintf(specifier2, "iDcyBr%s_%d/I", nm, j);
                  tr_new->Branch(specifier1, &iDcyBrIRADcyBrI[i][j], specifier2);
                }
            }
        }
    }

  unsigned long nentries = tr_old->GetEntries(); 
  for (unsigned long i=0;i<nentries;i++)
    {
      tr_old->GetEntry(i);
      if(vAtdbPid_size>0)
        {
          for(unsigned int j=0;j<vAtdbPid_size;j++)
            {
              if(m_ccSwitch==true)           
                {
                  if(m_vICcCompDcyBrP[i]==0)
                    {
                      for(unsigned int k=nPI_DcyBr[j];k<nPIMax_DcyBr[j];k++)
                        {
                          iDcyBrPI[j][k]=-1;
                          iCcDcyBrPI[j][k]=-9999;
                        }
                    }
                  else
                    {
                      for(unsigned int k=nPI_DcyBr[j];k<nPIMax_DcyBr[j];k++) iDcyBrPI[j][k]=-1;
                      for(unsigned int k=nCcPI_DcyBr[j];k<nCcPIMax_DcyBr[j];k++) iDcyBrCcPI[j][k]=-1;
                    }
                }
              else
                {
                  for(unsigned int k=nPI_DcyBr[j];k<nPIMax_DcyBr[j];k++) iDcyBrPI[j][k]=-1;
                }
            }
        }
      if(vAtpbPid_size>0)
        {
          for(unsigned int j=0;j<vAtpbPid_size;j++)
            {
              if(m_ccSwitch==true)           
                {
                  if(m_vICcCompProdBrP[i]==0)
                    {
                      for(unsigned int k=nPI_ProdBr[j];k<nPIMax_ProdBr[j];k++)
                        {
                          iProdBrPI[j][k]=-1;
                          iCcProdBrPI[j][k]=-9999;
                        }
                    }
                  else
                    {
                      for(unsigned int k=nPI_ProdBr[j];k<nPIMax_ProdBr[j];k++) iProdBrPI[j][k]=-1;
                      for(unsigned int k=nCcPI_ProdBr[j];k<nCcPIMax_ProdBr[j];k++) iProdBrCcPI[j][k]=-1;
                    }
                }
              else
                {
                  for(unsigned int k=nPI_ProdBr[j];k<nPIMax_ProdBr[j];k++) iProdBrPI[j][k]=-1;
                }
            }
        }
      if(vAtmPid_size>0)
        {
          for(unsigned int j=0;j<vAtmPid_size;j++)
            {
              if(m_ccSwitch==true)           
                {
                  if(m_vICcCompMP[i]==0)
                    {
                      for(unsigned int k=nPI_Moth[j];k<nPIMax_Moth[j];k++)
                        {
                          MothPDGPI[j][k]=0;
                          iCcMothPI[j][k]=-9999;
                        }
                    }
                  else
                    {
                      for(unsigned int k=nPI_Moth[j];k<nPIMax_Moth[j];k++) MothPDGPI[j][k]=0;
                      for(unsigned int k=nCcPI_Moth[j];k<nCcPIMax_Moth[j];k++) MothPDGCcPI[j][k]=0;
                    }
                }
              else
                {
                  for(unsigned int k=nPI_Moth[j];k<nPIMax_Moth[j];k++) MothPDGPI[j][k]=-1;
                }
            }
        }
      if(vAtecIncDcyBr_size>0)
        {
          for(unsigned int j=0;j<vAtecIncDcyBr_size;j++)
            {
              if(m_ccSwitch==true)
                {
                  if(m_vCompICcIncDcyBr[i]==0)
                    {
                      for(unsigned int k=nIncDcyBrI[j];k<nIncDcyBrIMax[j];k++)
                        {
                          iDcyBrIncDcyBrI[j][k]=-1;
                          iCcDcyBrIncDcyBrI[j][k]=-9999;
                        }
                    }
                  else
                    {
                      for(unsigned int k=nIncDcyBrI[j];k<nIncDcyBrIMax[j];k++) iDcyBrIncDcyBrI[j][k]=-1;
                      for(unsigned int k=nCcIncDcyBrI[j];k<nCcIncDcyBrIMax[j];k++) iDcyBrCcIncDcyBrI[j][k]=-1;
                    }
                }
              else
                {
                  for(unsigned int k=nIncDcyBrI[j];k<nIncDcyBrIMax[j];k++) iDcyBrIncDcyBrI[j][k]=-1;
                }
            }
        }
      if(vAtisIRADcyBr_size>0)
        {
          for(unsigned int j=0;j<vAtisIRADcyBr_size;j++)
            {
              if(m_ccSwitch==true)
                {
                  if(m_vCompICcIRADcyBr[i]==0)
                    {
                      for(unsigned int k=nIRADcyBrI[j];k<nIRADcyBrIMax[j];k++)
                        {
                          iDcyBrIRADcyBrI[j][k]=-1;
                          iCcDcyBrIRADcyBrI[j][k]=-9999;
                        }
                    }
                  else
                    {
                      for(unsigned int k=nIRADcyBrI[j];k<nIRADcyBrIMax[j];k++) iDcyBrIRADcyBrI[j][k]=-1;
                      for(unsigned int k=nCcIRADcyBrI[j];k<nCcIRADcyBrIMax[j];k++) iDcyBrCcIRADcyBrI[j][k]=-1;
                    }
                }
              else
                {
                  for(unsigned int k=nIRADcyBrI[j];k<nIRADcyBrIMax[j];k++) iDcyBrIRADcyBrI[j][k]=-1;
                }
            }
        }
      tr_new->Fill();
    }
  tr_new->Write("",TObject::kOverwrite); 
  delete fl;
}
