#include "../include/topoana.h"
#include "TBranch.h"

// This is the fifth subfuction that will be used in the new flatArrayBrs function.
void topoana::getMaxAndMax_Max(unsigned int size, string NM, vector<string> vNm, vector<int> vICc, TChain * chn, unsigned int * nMax, unsigned int & nMax_Max, unsigned int * nCcMax, unsigned int & nCcMax_Max)
{
  char nm[50],specifier1[100],specifier2[100];
  for(unsigned int i=0;i<size;i++)
    {
      sprintf(nm, "%s_%s", NM.c_str(), vNm[i].c_str());
      if(m_ccSwitch==true)
        {
          if(vICc[i]==0)
            {
              sprintf(specifier1, "n%s", nm);
              nMax[i]=chn->GetMaximum(specifier1);
              if(nMax[i]>nMax_Max) nMax_Max=nMax[i];                
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "nCc%s", nm);
              nMax[i]=chn->GetMaximum(specifier1);
              if(nMax[i]>nMax_Max) nMax_Max=nMax[i];                
              nCcMax[i]=chn->GetMaximum(specifier2);
              if(nCcMax[i]>nCcMax_Max) nCcMax_Max=nCcMax[i];
            }
        }   
      else 
        {
          sprintf(specifier1, "n%s", nm);
          nMax[i]=chn->GetMaximum(specifier1);
          if(nMax[i]>nMax_Max) nMax_Max=nMax[i];
        }
    }
}
