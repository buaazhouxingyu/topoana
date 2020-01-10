#include "../include/topoana.h"
#include "TBranch.h"

// This is the first subfuction that will be used in the new flatArrayBrs function.
void topoana::disableBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, vector<int> vICc, TTree * tr)
{
  char nm[50],nm2[50],specifier1[100],specifier2[100],specifier3[100],specifier4[100];
  for(unsigned int i=0;i<size;i++)
    {
      sprintf(nm, "%s_%s", NM1.c_str(), vNm[i].c_str());
      sprintf(nm2, "%s_%s", NM2.c_str(), vNm[i].c_str());
      if(m_ccSwitch==true)
        {
          if(vICc[i]==0)
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
              sprintf(specifier3, "%s%s", NM4.c_str(), nm2);
              tr->SetBranchStatus(specifier1,0);
              tr->SetBranchStatus(specifier2,0);
              tr->SetBranchStatus(specifier3,0);
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
              sprintf(specifier3, "nCc%s", nm);
              sprintf(specifier4, "%s%s", NM5.c_str(), nm2);
              tr->SetBranchStatus(specifier1,0);
              tr->SetBranchStatus(specifier2,0);
              tr->SetBranchStatus(specifier3,0);
              tr->SetBranchStatus(specifier4,0);
            }
        }
      else
        {
          sprintf(specifier1, "n%s", nm);
          sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
          tr->SetBranchStatus(specifier1,0);
          tr->SetBranchStatus(specifier2,0);
        }
    }
}
