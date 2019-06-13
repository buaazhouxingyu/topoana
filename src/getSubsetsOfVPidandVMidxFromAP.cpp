#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::getSubsetsOfVPidandVMidxFromAP(vector<int> & vPid,vector<int> & vMidx, int idx)
{
  if(vPid.size()!=vMidx.size())
    {
      cerr<<"Error: The two vectors vPid and vMidx have different sizes!"<<endl;
      cerr<<"Infor: The size of the vector vPid is "<<vPid.size()<<"."<<endl;
      cerr<<"Infor: The size of the vector vMidx is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(idx<0||((unsigned int) idx)>=vPid.size())
    {
      cerr<<"Error: The integer is not a reasonable index for the two vectors vPid and vMidx!"<<endl;
      cerr<<"Infor: The integer is "<<idx<<"."<<endl;
      cerr<<"Infor: The sizes of the two vectors vPid and vMidx are "<<vPid.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  /*cout<<"Before sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl;
    }*/

  vector<int> vPidFnl,vMidxFnl,vIdxFnl;
  vector<int> vIdxOld,vIdxYng;

  vPidFnl.push_back(vPid[idx]);
  vMidxFnl.push_back(0);
  vIdxFnl.push_back(idx);
  vIdxOld.push_back(idx);

  // The logic in the block should be considered seriously again!  
  for(unsigned int i=idx+1;i<vPid.size();i++)
    {
      if(vIdxOld.size()>0)
        {
          if(vMidx[i]>=vIdxOld[0]&&vMidx[i]<=vIdxOld[vIdxOld.size()-1])
            {
              vPidFnl.push_back(vPid[i]);
              vMidxFnl.push_back(vMidx[i]);
              vIdxFnl.push_back(i);
              vIdxYng.push_back(i);
            }
          else if(vMidx[i]>vIdxOld[vIdxOld.size()-1])
            {
              vIdxOld=vIdxYng;
              vIdxYng.clear();
              i--;
            }
        }
      else
        {
          break;
        }
    }

  for(unsigned int i=1;i<vMidxFnl.size();i++)
    {
      for(unsigned int j=0;j<i;j++)
        {
          if(vIdxFnl[j]==vMidxFnl[i])
            {
              vMidxFnl[i]=j;
              break;
            }
        }
    }
  vPid.clear();
  vMidx.clear();
  vPid=vPidFnl;
  vMidx=vMidxFnl;

  /*cout<<"After sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl; 
    }*/
}
