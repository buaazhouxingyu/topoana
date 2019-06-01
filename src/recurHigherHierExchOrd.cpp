#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::recurHigherHierExchOrd(vector<int> & vNewIdx,vector<int> & vOldIdx,vector<int> & vPid,vector<int> & vMidx)
{
  if(vNewIdx.size()!=vOldIdx.size())
    {
      cerr<<"Error: The two vectors vNewIdx and vOldIdx have different sizes!"<<endl;
      cerr<<"Infor: The size of the vector vNewIdx is "<<vNewIdx.size()<<"."<<endl;
      cerr<<"Infor: The size of the vector vOldIdx is "<<vOldIdx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(vPid.size()!=vMidx.size())
    {
      cerr<<"Error: The two vectors vPid and vMidx have different sizes!"<<endl;
      cerr<<"Infor: The size of the vector vPid is "<<vPid.size()<<"."<<endl;
      cerr<<"Infor: The size of the vector vMidx is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  /*cout<<"Before sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl;
    }*/

  vector<int> vNewIdxOld=vNewIdx,vOldIdxOld=vOldIdx;
  vector<int> vNewIdxYng,vOldIdxYng;
  vector<int> vPidYng,vNewMidxYng;
  int newIdxYng;  
  while(vNewIdxOld.size()!=0)
    {
      vNewIdxYng.clear();vOldIdxYng.clear();
      vPidYng.clear();vNewMidxYng.clear();
      newIdxYng=INT_MAX;  
      for(unsigned int i=0;i<vNewIdxOld.size();i++)
        {
          for(unsigned int j=vNewIdxOld[vNewIdxOld.size()-1]+1;j<vPid.size();j++)
            {
              if(vMidx[j]==vOldIdxOld[i])
                {
                  vOldIdxYng.push_back(j);
                  vPidYng.push_back(vPid[j]);
                  vNewMidxYng.push_back(vNewIdxOld[i]);
                  if(j<((unsigned int) newIdxYng)) newIdxYng=j;
                }
              else if(vMidx[j]>vNewIdxOld[vNewIdxOld.size()-1])
                {
                  break;
                }
            }          
        }
      for(unsigned int i=0;i<vPidYng.size();i++)
        {
          vPid[newIdxYng]=vPidYng[i];
          vMidx[newIdxYng]=vNewMidxYng[i];
          vNewIdxYng.push_back(newIdxYng);
          newIdxYng++;
        }
      vNewIdxOld=vNewIdxYng;
      vOldIdxOld=vOldIdxYng;
    }

  /*cout<<"After sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl; 
    }*/
}
