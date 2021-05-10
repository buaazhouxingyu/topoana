#include "../include/topoana.h"

void topoana::cpBrValsTemp(vector<string> vTBrNmOfTagRec, double * Tagrecsd)
{
  for(unsigned int i=0;i<vTBrNmOfTagRec.size();i++)
    {
      for(unsigned int j=vTBrNmOfTagRec.size()-1;j>i;j--)
        {
          if(vTBrNmOfTagRec[i]==vTBrNmOfTagRec[j])
            {
              Tagrecsd[i]=Tagrecsd[j];
              break;
            }
        }
    }

}
