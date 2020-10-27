#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::getVCascDcyBrP(vector< vector< list<int> > > & vCascDcyBrP, vector<int> & vIdxOfHead_CascDcyBrP, vector< list<int> > & dcyTr, vector<int> & vIdxOfHead, vector<int> & vMidxOfHead, int pid, unsigned long hCascDcyBrMax)
{
  if(dcyTr.size()!=vIdxOfHead.size()||vIdxOfHead.size()!=vMidxOfHead.size())
    {
      cerr<<"Error: The three vectors dcyTr, vIdxOfHead, and vMidxOfHead have different sizes!"<<endl;
      cerr<<"Infor: The size of dcyTr is "<<dcyTr.size()<<"."<<endl;
      cerr<<"Infor: The size of vIdxOfHead is "<<vIdxOfHead.size()<<"."<<endl;
      cerr<<"Infor: The size of vMidxOfHead is "<<vMidxOfHead.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(dcyTr.size()==0)
    {
      cerr<<"Infor: The sizes of the three vectors dcyTr, vIdxOfHead, and vMidxOfHead are zero!"<<endl<<endl;
      return;
    }

  vCascDcyBrP.clear();
  vector< list<int> > cascDcyBrP;
  vIdxOfHead_CascDcyBrP.clear();
  unsigned long hCascDcyBr;
  vector<int> vIdxOfHeadOld;
  unsigned int iDcyBrP;
  vector<int> vIdxOfHeadYng;
  for(unsigned int i=0;i<dcyTr.size();i++)
    {
      if((*(dcyTr[i].begin()))==pid)
        {
          cascDcyBrP.clear();
          cascDcyBrP.push_back(dcyTr[i]);
          hCascDcyBr=1;
          vIdxOfHeadOld.clear();
          vIdxOfHeadOld.push_back(vIdxOfHead[i]);
          iDcyBrP=i;
          while(hCascDcyBr<hCascDcyBrMax&&vIdxOfHeadOld.size()>0)
            {
              vIdxOfHeadYng.clear();
              for(unsigned int j=0;j<vIdxOfHeadOld.size();j++)
                {
                  for(unsigned int k=iDcyBrP+1;k<vMidxOfHead.size();k++)
                    {
                      if(vMidxOfHead[k]==vIdxOfHeadOld[j])
                        {
                          cascDcyBrP.push_back(dcyTr[k]);
                          vIdxOfHeadYng.push_back(vIdxOfHead[k]);
                          iDcyBrP=k;        
                        }
                    }
                }
              hCascDcyBr++;
              vIdxOfHeadOld=vIdxOfHeadYng;
            }
          vCascDcyBrP.push_back(cascDcyBrP);
          vIdxOfHead_CascDcyBrP.push_back(vIdxOfHead[i]);
        }
    }
}
