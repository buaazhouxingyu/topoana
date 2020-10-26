#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::getVDcyFStP(vector< list<int> > & vDcyFStP, vector<int> & vIdxOfHead_DcyFStP, vector<int> & vPid, vector<int> & vMidx, int pid, unsigned long nDcyFStP)
{
  if(vPid.size()!=vMidx.size())
    {
      cerr<<"Error: The two vectors vPid and vMidx have different sizes!"<<endl;
      cerr<<"Infor: The size of vPid is "<<vPid.size()<<"."<<endl;
      cerr<<"Infor: The size of vMidx is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(vPid.size()==0)
    {
      cerr<<"Infor: The sizes of the two vectors vPid and vMidx are zero!"<<endl<<endl;
      return;
    }

  vDcyFStP.clear();
  list<int> dcyFStP;
  vIdxOfHead_DcyFStP.clear();
  bool fromP;
  unsigned int J; // Here, J stands for j or its ancestors.
  bool fStP;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      if(vPid[i]==pid)
        {
          dcyFStP.clear();

          for(unsigned int j=i+1;j<vPid.size();j++)
            {
              fromP=false;
              J=j;
              while(1)
                {
                  if(vMidx[J]<((int) i)) break;
                  else if(vMidx[J]==((int) i))
                    {
                      fromP=true;
                      break;
                    }
                  else if(vMidx[J]==((int) J)) break;
                  else J=vMidx[J];
                }
              if(fromP==true)
                {
                  fStP=true;
                  for(unsigned int k=j+1;k<vPid.size();k++)
                    {
                      if(vMidx[k]==((int) j))
                        {
                          fStP=false;
                          break;
                        }
                    }
                  if(fStP==true) dcyFStP.push_back(vPid[j]);
                }
            }
  
          if(dcyFStP.size()>0)
            {
              if(nDcyFStP==ULONG_MAX||dcyFStP.size()==nDcyFStP)
                {
                  sortByPidAndPchrg(dcyFStP);
                  dcyFStP.push_front(pid);
                  vDcyFStP.push_back(dcyFStP);
                  vIdxOfHead_DcyFStP.push_back(i);
                }
            }
        }
    }
}
