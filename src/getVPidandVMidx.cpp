#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::getVPidandVMidx(vector< vector<int> > & vDcyBr, vector<int> & vIMDcyBr, vector<int> & vPid, vector<int> & vMidx)
{
  vector<int> vIdxOfHeadInMDcyBr;
  vIdxOfHeadInMDcyBr.clear();
  vector< vector<bool> >  vVStatusP;
  vVStatusP.clear();
  vector<bool> vStatusP;
  for(unsigned int i=0;i<vDcyBr.size();i++)
    {
      vIdxOfHeadInMDcyBr.push_back(-1);
      vStatusP.clear();
      for(unsigned int j=0;j<vDcyBr[i].size();j++) vStatusP.push_back(true);
      vVStatusP.push_back(vStatusP); 
    }
  vIdxOfHeadInMDcyBr.push_back(-9999);
  for(unsigned int i=1;i<vDcyBr.size();i++)
    {
      for(unsigned int j=0;j<vDcyBr[vIMDcyBr[i]].size();j++)
        {
          if(vVStatusP[vIMDcyBr[i]][j]==true&&vDcyBr[vIMDcyBr[i]][j]==vDcyBr[i][0])
            {
              vIdxOfHeadInMDcyBr[i]=j;
              vVStatusP[vIMDcyBr[i]][j]=false;
              break;
            }
        }
      if(vIdxOfHeadInMDcyBr[i]==-1)
        {
          cerr<<"Error: Can't find the head of decay branch "<<i<<" in the right side of its mother decay branch, that is decay branch "<<vIMDcyBr[i]<<"."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
    }

  vPid.clear();
  vMidx.clear();
  vector< vector<int> > vVIdx;
  vVIdx.clear();
  vector<int> vIdx;
  vPid.push_back(vDcyBr[0][0]);
  vMidx.push_back(-1);
  for(unsigned int i=0;i<vDcyBr.size();i++)
    {
      vIdx.clear();
      vIdx.push_back(0); // The value won't be used later. It can be any integer, not limited to 0.
      for(unsigned int j=1;j<vDcyBr[i].size();j++) 
        {
          vIdx.push_back(vPid.size());
          vPid.push_back(vDcyBr[i][j]);
          if(i==0) vMidx.push_back(0);
          else vMidx.push_back(vVIdx[vIMDcyBr[i]][vIdxOfHeadInMDcyBr[i]]);
        }
      vVIdx.push_back(vIdx);
    }
  vDcyBr.clear();
  vIMDcyBr.clear();
}
