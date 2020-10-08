#include "../include/topoana.h"
#include "TFile.h"
#include <iostream>
#include <cstdlib>
#include "TTree.h"
#include "TBranch.h"

void topoana::flatArrayBrs(string nmOfOptRootFl, unsigned int * nPIMax_DcyBr, unsigned int * nCcPIMax_DcyBr, unsigned int nPIMax_Max_DcyBr, unsigned int nCcPIMax_Max_DcyBr, unsigned int * nPIMax_CascDcyBr, unsigned int * nCcPIMax_CascDcyBr, unsigned int nPIMax_Max_CascDcyBr, unsigned int nCcPIMax_Max_CascDcyBr, unsigned int * nPIMax_DcyFSt, unsigned int * nCcPIMax_DcyFSt, unsigned int nPIMax_Max_DcyFSt, unsigned int nCcPIMax_Max_DcyFSt, unsigned int * nPIMax_ProdBr, unsigned int * nCcPIMax_ProdBr, unsigned int nPIMax_Max_ProdBr, unsigned int nCcPIMax_Max_ProdBr, unsigned int * nPIMax_Moth, unsigned int * nCcPIMax_Moth, unsigned int nPIMax_Max_Moth, unsigned int nCcPIMax_Max_Moth, unsigned int * nIncDcyBrIMax, unsigned int * nCcIncDcyBrIMax, unsigned int nIncDcyBrIMaxMax, unsigned int nCcIncDcyBrIMaxMax, unsigned int * nIRADcyBrIMax, unsigned int * nCcIRADcyBrIMax, unsigned int nIRADcyBrIMaxMax, unsigned int nCcIRADcyBrIMaxMax)
{
  unsigned int vAtdbPid_size=m_vPid_compDcyBrP.size();
  unsigned int vAtcdbPid_size=m_vPid_compCascDcyBrP.size();
  unsigned int vAtdfstPid_size=m_vPid_compDcyFStP.size();
  unsigned int vAtpbPid_size=m_vPid_compProdBrP.size();
  unsigned int vAtmPid_size=m_vPid_compMP.size();
  unsigned int vAtecIncDcyBr_size=m_vCompIncDcyBr.size(); 
  unsigned int vAtisIRADcyBr_size=m_vCompIRADcyBr.size();

  if(vAtdbPid_size<1&&vAtcdbPid_size<1&&vAtdfstPid_size<1&&vAtpbPid_size<1&&vAtmPid_size<1&&vAtecIncDcyBr_size<1&&vAtisIRADcyBr_size<1) return;

  TFile *fl=new TFile(nmOfOptRootFl.c_str(),"update");
  if(!fl)
    {
      cerr<<"Error: Can't open the root file \""<<nmOfOptRootFl<<"\"!"<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }
  TTree *tr_old=(TTree*) fl->Get(m_ttrNm.c_str());
  if(!tr_old)
    {
      cerr<<"Error: The root file \""<<nmOfOptRootFl<<"\" does not contain a tree named \""<<m_ttrNm<<"\"!"<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }  

  if(vAtdbPid_size>0)
    {
      disableBrs(vAtdbPid_size, "PDcyBr", "P", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compDcyBrP, m_vICcCompDcyBrP, tr_old);
    }
  if(vAtcdbPid_size>0)
    {
      disableBrs(vAtcdbPid_size, "PCascDcyBr", "P", "iCascDcyBr", "iCcCascDcyBr", "iCascDcyBrCc", m_vNm_compCascDcyBrP, m_vICcCompCascDcyBrP, tr_old);
    }
  if(vAtdfstPid_size>0)
    {
      disableBrs(vAtdfstPid_size, "PDcyFSt", "P", "iDcyFSt", "iCcDcyFSt", "iDcyFStCc", m_vNm_compDcyFStP, m_vICcCompDcyFStP, tr_old);
    }
  if(vAtpbPid_size>0)
    {
      disableBrs(vAtpbPid_size, "PProdBr", "P", "iProdBr", "iCcProdBr", "iProdBrCc", m_vNm_compProdBrP, m_vICcCompProdBrP, tr_old);
    }
  if(vAtmPid_size>0)
    {
      disableBrs(vAtmPid_size, "PMoth", "P", "PDGMoth", "iCcMoth", "PDGMothCc", m_vNm_compMP, m_vICcCompMP, tr_old);
    }
  if(vAtecIncDcyBr_size>0)
    {
      disableBrs(vAtecIncDcyBr_size, "IncDcyBr", "IncDcyBr", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compIncDcyBr, m_vICcCompIncDcyBr, tr_old);
    }
  if(vAtisIRADcyBr_size>0)
    {
      disableBrs(vAtisIRADcyBr_size, "IRADcyBr", "IRADcyBr", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compIRADcyBr, m_vICcCompIRADcyBr, tr_old);
    }

  TTree *tr_new=tr_old->CloneTree(0);

  if(vAtdbPid_size>0)
    {
      activateBrs(vAtdbPid_size, "PDcyBr", "P", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compDcyBrP, m_vICcCompDcyBrP, tr_old, nPIMax_DcyBr, nPIMax_Max_DcyBr, nCcPIMax_DcyBr, nCcPIMax_Max_DcyBr);
    }
  if(vAtcdbPid_size>0)
    {
      activateBrs(vAtcdbPid_size, "PCascDcyBr", "P", "iCascDcyBr", "iCcCascDcyBr", "iCascDcyBrCc", m_vNm_compCascDcyBrP, m_vICcCompCascDcyBrP, tr_old, nPIMax_CascDcyBr, nPIMax_Max_CascDcyBr, nCcPIMax_CascDcyBr, nCcPIMax_Max_CascDcyBr);
    }
  if(vAtdfstPid_size>0)
    {
      activateBrs(vAtdfstPid_size, "PDcyFSt", "P", "iDcyFSt", "iCcDcyFSt", "iDcyFStCc", m_vNm_compDcyFStP, m_vICcCompDcyFStP, tr_old, nPIMax_DcyFSt, nPIMax_Max_DcyFSt, nCcPIMax_DcyFSt, nCcPIMax_Max_DcyFSt);
    }
  if(vAtpbPid_size>0)
    {
      activateBrs(vAtpbPid_size, "PProdBr", "P", "iProdBr", "iCcProdBr", "iProdBrCc", m_vNm_compProdBrP, m_vICcCompProdBrP, tr_old, nPIMax_ProdBr, nPIMax_Max_ProdBr, nCcPIMax_ProdBr, nCcPIMax_Max_ProdBr);
    }
  if(vAtmPid_size>0)
    {
      activateBrs(vAtmPid_size, "PMoth", "P", "PDGMoth", "iCcMoth", "PDGMothCc", m_vNm_compMP, m_vICcCompMP, tr_old, nPIMax_Moth, nPIMax_Max_Moth, nCcPIMax_Moth, nCcPIMax_Max_Moth);
    }
  if(vAtecIncDcyBr_size>0)
    {
      activateBrs(vAtecIncDcyBr_size, "IncDcyBr", "IncDcyBr", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compIncDcyBr, m_vICcCompIncDcyBr, tr_old, nIncDcyBrIMax, nIncDcyBrIMaxMax, nCcIncDcyBrIMax, nCcIncDcyBrIMaxMax);
    }
  if(vAtisIRADcyBr_size>0)
    {
      activateBrs(vAtisIRADcyBr_size, "IRADcyBr", "IRADcyBr", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compIRADcyBr, m_vICcCompIRADcyBr, tr_old, nIRADcyBrIMax, nIRADcyBrIMaxMax, nCcIRADcyBrIMax, nCcIRADcyBrIMaxMax);
    }

  int nPI_DcyBr[vAtdbPid_size],iDcyBrPI[vAtdbPid_size][nPIMax_Max_DcyBr],iCcDcyBrPI[vAtdbPid_size][nPIMax_Max_DcyBr],nCcPI_DcyBr[vAtdbPid_size],iDcyBrCcPI[vAtdbPid_size][nCcPIMax_Max_DcyBr];
  int nPI_CascDcyBr[vAtcdbPid_size],iCascDcyBrPI[vAtcdbPid_size][nPIMax_Max_CascDcyBr],iCcCascDcyBrPI[vAtcdbPid_size][nPIMax_Max_CascDcyBr],nCcPI_CascDcyBr[vAtcdbPid_size],iCascDcyBrCcPI[vAtcdbPid_size][nCcPIMax_Max_CascDcyBr];
  int nPI_DcyFSt[vAtdfstPid_size],iDcyFStPI[vAtdfstPid_size][nPIMax_Max_DcyFSt],iCcDcyFStPI[vAtdfstPid_size][nPIMax_Max_DcyFSt],nCcPI_DcyFSt[vAtdfstPid_size],iDcyFStCcPI[vAtdfstPid_size][nCcPIMax_Max_DcyFSt];
  int nPI_ProdBr[vAtpbPid_size],iProdBrPI[vAtpbPid_size][nPIMax_Max_ProdBr],iCcProdBrPI[vAtpbPid_size][nPIMax_Max_ProdBr],nCcPI_ProdBr[vAtpbPid_size],iProdBrCcPI[vAtpbPid_size][nCcPIMax_Max_ProdBr];
  int nPI_Moth[vAtmPid_size],PDGMothPI[vAtmPid_size][nPIMax_Max_Moth],iCcMothPI[vAtmPid_size][nPIMax_Max_Moth],nCcPI_Moth[vAtmPid_size],PDGMothCcPI[vAtmPid_size][nCcPIMax_Max_Moth];
  int nIncDcyBrI[vAtecIncDcyBr_size],iDcyBrIncDcyBrI[vAtecIncDcyBr_size][nIncDcyBrIMaxMax],iCcDcyBrIncDcyBrI[vAtecIncDcyBr_size][nIncDcyBrIMaxMax],nCcIncDcyBrI[vAtecIncDcyBr_size],iDcyBrCcIncDcyBrI[vAtecIncDcyBr_size][nCcIncDcyBrIMaxMax];
  int nIRADcyBrI[vAtisIRADcyBr_size],iDcyBrIRADcyBrI[vAtisIRADcyBr_size][nIRADcyBrIMaxMax],iCcDcyBrIRADcyBrI[vAtisIRADcyBr_size][nIRADcyBrIMaxMax],nCcIRADcyBrI[vAtisIRADcyBr_size],iDcyBrCcIRADcyBrI[vAtisIRADcyBr_size][nCcIRADcyBrIMaxMax];
  if(vAtdbPid_size>0)
    {
      createBrs(vAtdbPid_size, "PDcyBr", "P", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compDcyBrP, m_vICcCompDcyBrP, tr_old, tr_new, nPIMax_DcyBr, nPIMax_Max_DcyBr, nCcPIMax_DcyBr, nCcPIMax_Max_DcyBr, nPI_DcyBr, iDcyBrPI[0], iCcDcyBrPI[0], nCcPI_DcyBr, iDcyBrCcPI[0]);
    }
  if(vAtcdbPid_size>0)
    {
      createBrs(vAtcdbPid_size, "PCascDcyBr", "P", "iCascDcyBr", "iCcCascDcyBr", "iCascDcyBrCc", m_vNm_compCascDcyBrP, m_vICcCompCascDcyBrP, tr_old, tr_new, nPIMax_CascDcyBr, nPIMax_Max_CascDcyBr, nCcPIMax_CascDcyBr, nCcPIMax_Max_CascDcyBr, nPI_CascDcyBr, iCascDcyBrPI[0], iCcCascDcyBrPI[0], nCcPI_CascDcyBr, iCascDcyBrCcPI[0]);
    }
  if(vAtdfstPid_size>0)
    {
      createBrs(vAtdfstPid_size, "PDcyFSt", "P", "iDcyFSt", "iCcDcyFSt", "iDcyFStCc", m_vNm_compDcyFStP, m_vICcCompDcyFStP, tr_old, tr_new, nPIMax_DcyFSt, nPIMax_Max_DcyFSt, nCcPIMax_DcyFSt, nCcPIMax_Max_DcyFSt, nPI_DcyFSt, iDcyFStPI[0], iCcDcyFStPI[0], nCcPI_DcyFSt, iDcyFStCcPI[0]);
    }
  if(vAtpbPid_size>0)
    {
      createBrs(vAtpbPid_size, "PProdBr", "P", "iProdBr", "iCcProdBr", "iProdBrCc", m_vNm_compProdBrP, m_vICcCompProdBrP, tr_old, tr_new, nPIMax_ProdBr, nPIMax_Max_ProdBr, nCcPIMax_ProdBr, nCcPIMax_Max_ProdBr, nPI_ProdBr, iProdBrPI[0], iCcProdBrPI[0], nCcPI_ProdBr, iProdBrCcPI[0]);
    }
  if(vAtmPid_size>0)
    {
      createBrs(vAtmPid_size, "PMoth", "P", "PDGMoth", "iCcMoth", "PDGMothCc", m_vNm_compMP, m_vICcCompMP, tr_old, tr_new, nPIMax_Moth, nPIMax_Max_Moth, nCcPIMax_Moth, nCcPIMax_Max_Moth, nPI_Moth, PDGMothPI[0], iCcMothPI[0], nCcPI_Moth, PDGMothCcPI[0]);
    }
  if(vAtecIncDcyBr_size>0)
    {
      createBrs(vAtecIncDcyBr_size, "IncDcyBr", "IncDcyBr", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compIncDcyBr, m_vICcCompIncDcyBr, tr_old, tr_new, nIncDcyBrIMax, nIncDcyBrIMaxMax, nCcIncDcyBrIMax, nCcIncDcyBrIMaxMax, nIncDcyBrI, iDcyBrIncDcyBrI[0], iCcDcyBrIncDcyBrI[0], nCcIncDcyBrI, iDcyBrCcIncDcyBrI[0]);
    }
  if(vAtisIRADcyBr_size>0)
    {
      createBrs(vAtisIRADcyBr_size, "IRADcyBr", "IRADcyBr", "iDcyBr", "iCcDcyBr", "iDcyBrCc", m_vNm_compIRADcyBr, m_vICcCompIRADcyBr, tr_old, tr_new, nIRADcyBrIMax, nIRADcyBrIMaxMax, nCcIRADcyBrIMax, nCcIRADcyBrIMaxMax, nIRADcyBrI, iDcyBrIRADcyBrI[0], iCcDcyBrIRADcyBrI[0], nCcIRADcyBrI, iDcyBrCcIRADcyBrI[0]);
    }


  unsigned long nentries = tr_old->GetEntries(); 
  for (unsigned long i=0;i<nentries;i++)
    {
      tr_old->GetEntry(i);
      if(vAtdbPid_size>0)
        {
          assignDftVals(vAtdbPid_size, m_vICcCompDcyBrP, nPIMax_DcyBr, nPIMax_Max_DcyBr, nCcPIMax_DcyBr, nCcPIMax_Max_DcyBr, nPI_DcyBr, iDcyBrPI[0], iCcDcyBrPI[0], nCcPI_DcyBr, iDcyBrCcPI[0]);
        }
      if(vAtcdbPid_size>0)
        {
          assignDftVals(vAtcdbPid_size, m_vICcCompCascDcyBrP, nPIMax_CascDcyBr, nPIMax_Max_CascDcyBr, nCcPIMax_CascDcyBr, nCcPIMax_Max_CascDcyBr, nPI_CascDcyBr, iCascDcyBrPI[0], iCcCascDcyBrPI[0], nCcPI_CascDcyBr, iCascDcyBrCcPI[0]);
        }
      if(vAtdfstPid_size>0)
        {
          assignDftVals(vAtdfstPid_size, m_vICcCompDcyFStP, nPIMax_DcyFSt, nPIMax_Max_DcyFSt, nCcPIMax_DcyFSt, nCcPIMax_Max_DcyFSt, nPI_DcyFSt, iDcyFStPI[0], iCcDcyFStPI[0], nCcPI_DcyFSt, iDcyFStCcPI[0]);
        }
      if(vAtpbPid_size>0)
        {
          assignDftVals(vAtpbPid_size, m_vICcCompProdBrP, nPIMax_ProdBr, nPIMax_Max_ProdBr, nCcPIMax_ProdBr, nCcPIMax_Max_ProdBr, nPI_ProdBr, iProdBrPI[0], iCcProdBrPI[0], nCcPI_ProdBr, iProdBrCcPI[0]);
        }
      if(vAtmPid_size>0)
        {
          assignDftVals(vAtmPid_size, m_vICcCompMP, nPIMax_Moth, nPIMax_Max_Moth, nCcPIMax_Moth, nCcPIMax_Max_Moth, nPI_Moth, PDGMothPI[0], iCcMothPI[0], nCcPI_Moth, PDGMothCcPI[0], true);
        }
      if(vAtecIncDcyBr_size>0)
        {
          assignDftVals(vAtecIncDcyBr_size, m_vICcCompIncDcyBr, nIncDcyBrIMax, nIncDcyBrIMaxMax, nCcIncDcyBrIMax, nCcIncDcyBrIMaxMax, nIncDcyBrI, iDcyBrIncDcyBrI[0], iCcDcyBrIncDcyBrI[0], nCcIncDcyBrI, iDcyBrCcIncDcyBrI[0]);
        }
      if(vAtisIRADcyBr_size>0)
        {
          assignDftVals(vAtisIRADcyBr_size, m_vICcCompIRADcyBr, nIRADcyBrIMax, nIRADcyBrIMaxMax, nCcIRADcyBrIMax, nCcIRADcyBrIMaxMax, nIRADcyBrI, iDcyBrIRADcyBrI[0], iCcDcyBrIRADcyBrI[0], nCcIRADcyBrI, iDcyBrCcIRADcyBrI[0]);
        }
      tr_new->Fill();
    }
  tr_new->Write("",TObject::kOverwrite); 
  delete fl;
}

void topoana::flatArrayBrs(vector<string> nmsOfOptRootFls)
{
  unsigned int vAtdbPid_size=m_vPid_compDcyBrP.size();
  unsigned int vAtcdbPid_size=m_vPid_compCascDcyBrP.size();
  unsigned int vAtdfstPid_size=m_vPid_compDcyFStP.size();
  unsigned int vAtpbPid_size=m_vPid_compProdBrP.size();
  unsigned int vAtmPid_size=m_vPid_compMP.size();
  unsigned int vAtecIncDcyBr_size=m_vCompIncDcyBr.size();
  unsigned int vAtisIRADcyBr_size=m_vCompIRADcyBr.size();

  unsigned int nPIMax_DcyBr[vAtdbPid_size],nCcPIMax_DcyBr[vAtdbPid_size];
  unsigned int nPIMax_Max_DcyBr=0,nCcPIMax_Max_DcyBr=0;
  unsigned int nPIMax_CascDcyBr[vAtcdbPid_size],nCcPIMax_CascDcyBr[vAtcdbPid_size];
  unsigned int nPIMax_Max_CascDcyBr=0,nCcPIMax_Max_CascDcyBr=0;
  unsigned int nPIMax_DcyFSt[vAtdfstPid_size],nCcPIMax_DcyFSt[vAtdfstPid_size];
  unsigned int nPIMax_Max_DcyFSt=0,nCcPIMax_Max_DcyFSt=0;
  unsigned int nPIMax_ProdBr[vAtpbPid_size],nCcPIMax_ProdBr[vAtpbPid_size];
  unsigned int nPIMax_Max_ProdBr=0,nCcPIMax_Max_ProdBr=0;
  unsigned int nPIMax_Moth[vAtmPid_size],nCcPIMax_Moth[vAtmPid_size];
  unsigned int nPIMax_Max_Moth=0,nCcPIMax_Max_Moth=0;
  unsigned int nIncDcyBrIMax[vAtecIncDcyBr_size],nCcIncDcyBrIMax[vAtecIncDcyBr_size];
  unsigned int nIncDcyBrIMaxMax=0,nCcIncDcyBrIMaxMax=0;
  unsigned int nIRADcyBrIMax[vAtisIRADcyBr_size],nCcIRADcyBrIMax[vAtisIRADcyBr_size];
  unsigned int nIRADcyBrIMaxMax=0,nCcIRADcyBrIMaxMax=0;

  if(m_flatArrayBrsLocally==false)
    {
      TChain * chn=new TChain(m_ttrNm.c_str());
      for(unsigned int i=0;i<nmsOfOptRootFls.size();i++) chn->Add(nmsOfOptRootFls[i].c_str());

      if(vAtdbPid_size>0)
        {
          getMaxAndMax_Max(vAtdbPid_size, "PDcyBr", m_vNm_compDcyBrP, m_vICcCompDcyBrP, chn, nPIMax_DcyBr, nPIMax_Max_DcyBr, nCcPIMax_DcyBr, nCcPIMax_Max_DcyBr);
        }
      if(vAtcdbPid_size>0)
        {
          getMaxAndMax_Max(vAtcdbPid_size, "PCascDcyBr", m_vNm_compCascDcyBrP, m_vICcCompCascDcyBrP, chn, nPIMax_CascDcyBr, nPIMax_Max_CascDcyBr, nCcPIMax_CascDcyBr, nCcPIMax_Max_CascDcyBr);
        }
      if(vAtdfstPid_size>0)
        {
          getMaxAndMax_Max(vAtdfstPid_size, "PDcyFSt", m_vNm_compDcyFStP, m_vICcCompDcyFStP, chn, nPIMax_DcyFSt, nPIMax_Max_DcyFSt, nCcPIMax_DcyFSt, nCcPIMax_Max_DcyFSt);
        }
      if(vAtpbPid_size>0)
        {
          getMaxAndMax_Max(vAtpbPid_size, "PProdBr", m_vNm_compProdBrP, m_vICcCompProdBrP, chn, nPIMax_ProdBr, nPIMax_Max_ProdBr, nCcPIMax_ProdBr, nCcPIMax_Max_ProdBr);
        }
      if(vAtmPid_size>0)
        {
          getMaxAndMax_Max(vAtmPid_size, "PMoth", m_vNm_compMP, m_vICcCompMP, chn, nPIMax_Moth, nPIMax_Max_Moth, nCcPIMax_Moth, nCcPIMax_Max_Moth);
        }
      if(vAtecIncDcyBr_size>0)
        {
          getMaxAndMax_Max(vAtecIncDcyBr_size, "IncDcyBr", m_vNm_compIncDcyBr, m_vICcCompIncDcyBr, chn, nIncDcyBrIMax, nIncDcyBrIMaxMax, nCcIncDcyBrIMax, nCcIncDcyBrIMaxMax);
        }
      if(vAtisIRADcyBr_size>0)
        {
          getMaxAndMax_Max(vAtisIRADcyBr_size, "IRADcyBr", m_vNm_compIRADcyBr, m_vICcCompIRADcyBr, chn, nIRADcyBrIMax, nIRADcyBrIMaxMax, nCcIRADcyBrIMax, nCcIRADcyBrIMaxMax);
        }

    }

  for(unsigned int i=0;i<nmsOfOptRootFls.size();i++) flatArrayBrs(nmsOfOptRootFls[i], nPIMax_DcyBr, nCcPIMax_DcyBr, nPIMax_Max_DcyBr, nCcPIMax_Max_DcyBr, nPIMax_CascDcyBr, nCcPIMax_CascDcyBr, nPIMax_Max_CascDcyBr, nCcPIMax_Max_CascDcyBr, nPIMax_DcyFSt, nCcPIMax_DcyFSt, nPIMax_Max_DcyFSt, nCcPIMax_Max_DcyFSt, nPIMax_ProdBr, nCcPIMax_ProdBr, nPIMax_Max_ProdBr, nCcPIMax_Max_ProdBr, nPIMax_Moth, nCcPIMax_Moth, nPIMax_Max_Moth, nCcPIMax_Max_Moth, nIncDcyBrIMax, nCcIncDcyBrIMax, nIncDcyBrIMaxMax, nCcIncDcyBrIMaxMax, nIRADcyBrIMax, nCcIRADcyBrIMax, nIRADcyBrIMaxMax, nCcIRADcyBrIMaxMax);
}
