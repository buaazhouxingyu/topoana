#include "../include/topoana.h"
#include "TBranch.h"

void topoana::createBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, int * aICc, TTree * tr, unsigned int nMax, int * nq, int * iq, int * iCcq, int * nCcq, int * iqCc, int * nAllq)
{
  char nm1[50],nm2[50];
  char specifier1[100],specifier2[120];
  for(unsigned int i=0;i<size;i++)
    {
      sprintf(nm1, "%s_%s", NM1.c_str(), vNm[i].c_str());
      sprintf(nm2, "%s_%s", NM2.c_str(), vNm[i].c_str());
      if(m_ccSwitch==true)
        {
          sprintf(specifier1, "iCc%s", nm1);
          sprintf(specifier2, "iCc%s/I", nm1);
          tr->Branch(specifier1, &aICc[i], specifier2);
          if(aICc[i]==0)
            {
              sprintf(specifier1, "n%s", nm1);
              sprintf(specifier2, "n%s/I", nm1);
              tr->Branch(specifier1, &nq[i], specifier2);
              sprintf(specifier1, "%s%s", NM3.c_str(), nm2);
              sprintf(specifier2, "%s%s[n%s]/I", NM3.c_str(), nm2, nm1);
              tr->Branch(specifier1, &iq[i*nMax], specifier2);
              sprintf(specifier1, "%s%s", NM4.c_str(), nm2);
              sprintf(specifier2, "%s%s[n%s]/I", NM4.c_str(), nm2, nm1);
              tr->Branch(specifier1, &iCcq[i*nMax], specifier2);                  
            }
          else
            {
              sprintf(specifier1, "n%s", nm1);
              sprintf(specifier2, "n%s/I", nm1);
              tr->Branch(specifier1, &nq[i], specifier2);
              sprintf(specifier1, "%s%s", NM3.c_str(), nm2);
              sprintf(specifier2, "%s%s[n%s]/I", NM3.c_str(), nm2, nm1);
              tr->Branch(specifier1, &iq[i*nMax], specifier2);
              sprintf(specifier1, "nCc%s", nm1);
              sprintf(specifier2, "nCc%s/I", nm1);
              tr->Branch(specifier1, &nCcq[i], specifier2);
              sprintf(specifier1, "%s%s", NM5.c_str(), nm2);
              sprintf(specifier2, "%s%s[nCc%s]/I", NM5.c_str(), nm2, nm1);
              tr->Branch(specifier1, &iqCc[i*nMax], specifier2);              
              sprintf(specifier1, "nAll%s", nm1);
              sprintf(specifier2, "nAll%s/I", nm1);
              tr->Branch(specifier1, &nAllq[i], specifier2);
            }
        }
      else
        {
          sprintf(specifier1, "n%s", nm1);
          sprintf(specifier2, "n%s/I", nm1);
          tr->Branch(specifier1, &nq[i], specifier2);
          sprintf(specifier1, "%s%s", NM3.c_str(), nm2);
          sprintf(specifier2, "%s%s[n%s]/I", NM3.c_str(), nm2, nm1);
          tr->Branch(specifier1, &iq[i*nMax], specifier2);
        }
    }
}

void topoana::createBrs(unsigned int size, string NM, vector<string> vNm, int * aICc, TTree * tr, int * nq, int * nCcq, int * nAllq)
{
  if(m_useArrayTBrsOpt==true)
    {
      char specifier1[100],specifier2[120];
      if(m_ccSwitch==true)
        {
          sprintf(specifier1, "iCc%s", NM.c_str());
          sprintf(specifier2, "iCc%s[%d]/I", NM.c_str(), int(size));
          tr->Branch(specifier1, &aICc, specifier2);
          sprintf(specifier1, "n%s", NM.c_str());
          sprintf(specifier2, "n%s[%d]/I", NM.c_str(), int(size));
          tr->Branch(specifier1, &nq, specifier2);
          sprintf(specifier1, "nCc%s", NM.c_str());
          sprintf(specifier2, "nCc%s[%d]/I", NM.c_str(), int(size));
          tr->Branch(specifier1, &nCcq, specifier2);
          sprintf(specifier1, "nAll%s", NM.c_str());
          sprintf(specifier2, "nAll%s[%d]/I", NM.c_str(), int(size));
          tr->Branch(specifier1, &nAllq, specifier2);
        }
      else
        {
          sprintf(specifier1, "n%s", NM.c_str());
          sprintf(specifier2, "n%s[%d]/I", NM.c_str(), int(size));
          tr->Branch(specifier1, &nq, specifier2);
        }
    }
  else
    {
      char nm[50];
      char specifier1[100],specifier2[120];
      for(unsigned int i=0;i<size;i++)
        {
          sprintf(nm, "%s_%s", NM.c_str(), vNm[i].c_str());
          if(m_ccSwitch==true)
            {
              sprintf(specifier1, "iCc%s", nm);
              sprintf(specifier2, "iCc%s/I", nm);
              tr->Branch(specifier1, &aICc[i], specifier2);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr->Branch(specifier1, &nq[i], specifier2);
              if(aICc[i]!=0)
                {
                  sprintf(specifier1, "nCc%s", nm);
                  sprintf(specifier2, "nCc%s/I", nm);
                  tr->Branch(specifier1, &nCcq[i], specifier2);
                  sprintf(specifier1, "nAll%s", nm);
                  sprintf(specifier2, "nAll%s/I", nm);
                  tr->Branch(specifier1, &nAllq[i], specifier2);
                }
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr->Branch(specifier1, &nq[i], specifier2);
            }
        }
    }
}

// This is the third subfuction that will be used in the new flatArrayBrs function.
void topoana::createBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, vector<int> vICc, TTree * tr_old, TTree * tr_new, unsigned int * nMax, unsigned int nMax_Max, unsigned int * nCcMax, unsigned int nCcMax_Max, int * nq, int * iq, int * iCcq, int * nCcq, int * iqCc)
{
  char nm[50],nm2[50],specifier1[100],specifier2[100],specifier3[100],specifier4[100];
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
              tr_old->SetBranchAddress(specifier1, &nq[i]);
              tr_old->SetBranchAddress(specifier2, &iq[i*nMax_Max]);
              tr_old->SetBranchAddress(specifier3, &iCcq[i*nMax_Max]);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr_new->Branch(specifier1, &nq[i], specifier2);
              for(unsigned int j=0;j<nMax[i];j++)
                {
                  sprintf(specifier1, "%s%s_%d", NM3.c_str(), nm2, j);
                  sprintf(specifier2, "%s%s_%d/I", NM3.c_str(), nm2, j);
                  sprintf(specifier3, "%s%s_%d", NM4.c_str(), nm2, j);
                  sprintf(specifier4, "%s%s_%d/I", NM4.c_str(), nm2, j);
                  tr_new->Branch(specifier1, &iq[i*nMax_Max+j], specifier2);
                  tr_new->Branch(specifier3, &iCcq[i*nMax_Max+j], specifier4);
                }                
            }
          else
            {
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
              sprintf(specifier3, "nCc%s", nm);
              sprintf(specifier4, "%s%s", NM5.c_str(), nm2);
              tr_old->SetBranchAddress(specifier1, &nq[i]);
              tr_old->SetBranchAddress(specifier2, &iq[i*nMax_Max]);
              tr_old->SetBranchAddress(specifier3, &nCcq[i]);
              tr_old->SetBranchAddress(specifier4, &iqCc[i*nCcMax_Max]);
              sprintf(specifier1, "n%s", nm);
              sprintf(specifier2, "n%s/I", nm);
              tr_new->Branch(specifier1, &nq[i], specifier2);
              for(unsigned int j=0;j<nMax[i];j++)
                {
                  sprintf(specifier1, "%s%s_%d", NM3.c_str(), nm2, j);
                  sprintf(specifier2, "%s%s_%d/I", NM3.c_str(), nm2, j);
                  tr_new->Branch(specifier1, &iq[i*nMax_Max+j], specifier2);
                }
              sprintf(specifier3, "nCc%s", nm);
              sprintf(specifier4, "nCc%s/I", nm);
              tr_new->Branch(specifier3, &nCcq[i], specifier4);
              for(unsigned int j=0;j<nCcMax[i];j++)
                {
                  sprintf(specifier3, "%s%s_%d", NM5.c_str(), nm2, j);
                  sprintf(specifier4, "%s%s_%d/I", NM5.c_str(), nm2, j);
                  tr_new->Branch(specifier3, &iqCc[i*nCcMax_Max+j], specifier4);
                }
            }
        }
      else 
        {
          sprintf(specifier1, "n%s", nm); 
          sprintf(specifier2, "%s%s", NM3.c_str(), nm2);
          tr_old->SetBranchAddress(specifier1,&nq[i]);
          tr_old->SetBranchAddress(specifier2,&iq[i*nMax_Max]);
          sprintf(specifier1, "n%s", nm);
          sprintf(specifier2, "n%s/I", nm);
          tr_new->Branch(specifier1, &nq[i], specifier2);
          for(unsigned int j=0;j<nMax[i];j++)
            {
              sprintf(specifier1, "%s%s_%d", NM3.c_str(), nm2, j);
              sprintf(specifier2, "%s%s_%d/I", NM3.c_str(), nm2, j);
              tr_new->Branch(specifier1, &iq[i*nMax_Max+j], specifier2);
            }
        }
    }
}
