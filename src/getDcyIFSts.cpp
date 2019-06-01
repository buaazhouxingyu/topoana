#include "../include/topoana.h"
#include <cstdlib>

void  topoana::getDcyIFSts(vector<int> & vPid,vector<int> & vMidx,list<int> & dcyIFSts)
{
  dcyIFSts.clear();
  bool fsp;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      fsp=true;
      for(unsigned int j=i+1;j<vPid.size();j++)
        {
          if(((unsigned int) vMidx[j])==i)
            {
              fsp=false;
              break;
            }
        }
      if(fsp&&abs(vPid[i])!=1&&abs(vPid[i])!=2&&abs(vPid[i])!=3&&abs(vPid[i])!=4&&abs(vPid[i])!=5&&abs(vPid[i])!=6) dcyIFSts.push_back(vPid[i]);
    }
  sortByPidAndPchrg(dcyIFSts);

  list<int> dcyBr;
  dcyBr.clear();
  for(unsigned int i=0;i<vPid.size();i++)
    { 
      if(((unsigned int) vMidx[i])==i) dcyBr.push_back(vPid[i]);
    }
  if(dcyBr.size()>1||m_initEpEmSwitch==true)
    {
      dcyIFSts.push_front(11);
      dcyIFSts.push_front(-11);
    }
  else
    {
      dcyIFSts.push_front(*(dcyBr.begin()));
    }
}
