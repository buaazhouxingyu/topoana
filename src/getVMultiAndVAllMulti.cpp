#include "../include/topoana.h"
#include <cstdlib>
#include <iostream>

void topoana::getVMultiAndVAllMulti(vector<int> vPid, vector<int> & vMulti, vector<int> & vAllMulti)
{
  for(unsigned int i=0;i<vPid.size();i++)
    {
      vMulti.push_back(0);
      vAllMulti.push_back(0);
      for(unsigned int j=0;j<vPid.size();j++)
        {
          if(vPid[j]==vPid[i]) vMulti[i]++;
          if(abs(vPid[j])==abs(vPid[i])) vAllMulti[i]++;
        }
      cout<<"vMulti["<<i<<"]="<<vMulti[i]<<endl;
      cout<<"vAllMulti["<<i<<"]="<<vAllMulti[i]<<endl;
    }
}
