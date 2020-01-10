#include "../include/topoana.h"

// This is the fourth subfuction that will be used in the new flatArrayBrs function.
void topoana::assignDftVals(unsigned int size, vector<int> vICc, unsigned int * nMax, unsigned int nMax_Max, unsigned int * nCcMax, unsigned int nCcMax_Max, int * nq, int * iq, int * iCcq, int * nCcq, int * iqCc, bool isForMoth)
{
  for(unsigned int j=0;j<size;j++)
    {
      if(m_ccSwitch==true)           
        {
          if(vICc[j]==0)
            {
              for(unsigned int k=nq[j];k<nMax[j];k++)
                {
                  if(isForMoth==true) iq[j*nMax_Max+k]=0;
                  else iq[j*nMax_Max+k]=-1;
                  iCcq[j*nMax_Max+k]=-9999;
                }
            }
          else
            {
              for(unsigned int k=nq[j];k<nMax[j];k++)
                {
                  if(isForMoth==true) iq[j*nMax_Max+k]=0;
                  else iq[j*nMax_Max+k]=-1;
                }
              for(unsigned int k=nCcq[j];k<nCcMax[j];k++)
                {
                  if(isForMoth==true) iqCc[j*nCcMax_Max+k]=0;
                  else iqCc[j*nCcMax_Max+k]=-1;
                }
            }
        }
      else
        {
          for(unsigned int k=nq[j];k<nMax[j];k++)
            {
              if(isForMoth==true) iq[j*nMax_Max+k]=0;
              else iq[j*nMax_Max+k]=-1;
            }
        }
    }
}
