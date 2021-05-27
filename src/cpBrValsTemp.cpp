#include "../include/topoana.h"

void topoana::cpBrValsTemp(vector<string> vTBrNmOfTagRec, int * Tagrecsi, float * Tagrecsf, double * Tagrecsd)
{
  for(unsigned int i=0;i<vTBrNmOfTagRec.size();i++)
    {
      for(unsigned int j=vTBrNmOfTagRec.size()-1;j>i;j--)
        {
          if(vTBrNmOfTagRec[i]==vTBrNmOfTagRec[j])
            {
              if(m_strgTpOfRawIptTopoDat=="MSI") Tagrecsi[i]=Tagrecsi[j];
              else if(m_strgTpOfRawIptTopoDat=="MSF") Tagrecsf[i]=Tagrecsf[j];
              else if(m_strgTpOfRawIptTopoDat=="MSD") Tagrecsd[i]=Tagrecsd[j];
              break;
            }
        }
    }

}
