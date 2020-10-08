#include "../include/topoana.h"
#include "TBranch.h"

// This is the second subfuction that will be used in the new flatArrayBrs function.
void topoana::activateBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, vector<int> vICc, TTree * tr, unsigned int * nMax, unsigned int & nMax_Max, unsigned int * nCcMax, unsigned int & nCcMax_Max)
{
  char nm[50],nm2[50],specifier1[100],specifier2[100],specifier3[100],specifier4[100];
  if(m_flatArrayBrsLocally==true)
    {
      nMax_Max=0;
      nCcMax_Max=0;
    }
  for(unsigned int i=0;i<size;i++)
    {
      sprintf(nm, "%s_%s", NM1.c_str(), vNm[i].c_str());
      sprintf(nm2, "%s_%s",  NM2.c_str(), vNm[i].c_str());
      if(m_ccSwitch==true)
        {
          if(vICc[i]==0)
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
              sprintf(specifier3, "%s%s", NM4.c_str(), nm2);
              tr->SetBranchStatus(specifier1, 1);
              tr->SetBranchStatus(specifier2, 1);
              tr->SetBranchStatus(specifier3, 1);
              if(m_flatArrayBrsLocally==true) nMax[i]=tr->GetMaximum(specifier1);
              if(m_flatArrayBrsLocally==true) if(nMax[i]>nMax_Max) nMax_Max=nMax[i];
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
              sprintf(specifier3, "nCc%s", nm);
              sprintf(specifier4, "%s%s", NM5.c_str(), nm2);
              tr->SetBranchStatus(specifier1, 1);
              tr->SetBranchStatus(specifier2, 1);
              tr->SetBranchStatus(specifier3, 1);
              tr->SetBranchStatus(specifier4, 1);
              if(m_flatArrayBrsLocally==true) nMax[i]=tr->GetMaximum(specifier1);
              if(m_flatArrayBrsLocally==true) if(nMax[i]>nMax_Max) nMax_Max=nMax[i];
              if(m_flatArrayBrsLocally==true) nCcMax[i]=tr->GetMaximum(specifier3);
              if(m_flatArrayBrsLocally==true) if(nCcMax[i]>nCcMax_Max) nCcMax_Max=nCcMax[i];
            }
        }   
      else 
        {
          sprintf(specifier1, "n%s", nm);
          sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
          tr->SetBranchStatus(specifier1, 1);
          tr->SetBranchStatus(specifier2, 1);
          if(m_flatArrayBrsLocally==true) nMax[i]=tr->GetMaximum(specifier1);
          if(m_flatArrayBrsLocally==true) if(nMax[i]>nMax_Max) nMax_Max=nMax[i];
        }
    }
}
