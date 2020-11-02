#include "../include/topoana.h"

bool topoana::useRidx(vector<string> vTypeOfTagRec)
{
  bool useRidx=false;
  for(unsigned int i=0;i<vTypeOfTagRec.size();i++)
    {
      if(vTypeOfTagRec[i]=="i"||vTypeOfTagRec[i]=="I")
        {
          useRidx=true;
          break;
        }
    }
  return useRidx;
}
