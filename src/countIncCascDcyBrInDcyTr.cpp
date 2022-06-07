#include "../include/topoana.h"
#include <iostream>

unsigned int topoana::countIncCascDcyBrInDcyTr(vector<int> vIIncIncCascDcyBr, vector< list<int> > & incCascDcyBr, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2)
{
  unsigned int nCount=0;
  if(incCascDcyBr.size()==0)
    {
      cerr<<"Infor: The size of the vector for the inclusive cascade decay branches is zero!"<<endl<<endl;
      return nCount;
    }
  if(dcyTr.size()==0)
    {
      cerr<<"Infor: The size of the vector for the decay tree is zero!"<<endl<<endl;
      return nCount;
    }
  if(incCascDcyBr.size()<=dcyTr.size())
    {
      /*for(unsigned int i=0;i<incCascDcyBr.size();i++)
        {
          list<int>::iterator liit,liitTmp=incCascDcyBr[i].end();liitTmp--;
          for(liit=incCascDcyBr[i].begin();liit!=incCascDcyBr[i].end();liit++)
            {
              if(liit!=liitTmp) cout<<(*liit)<<"\t";
              else cout<<(*liit)<<endl;
            }
        }
      cout<<endl;
      for(unsigned int i=0;i<dcyTr.size();i++)
        {
          list<int>::iterator liit,liitTmp=dcyTr[i].end();liitTmp--;
          for(liit=dcyTr[i].begin();liit!=dcyTr[i].end();liit++)
            {
              if(liit!=liitTmp) cout<<(*liit)<<"\t";
              else cout<<(*liit)<<endl;
            }
        }
      cout<<endl;*/

      vector<int> vMIDcyBr1WRTIDcyBr1;
      vMIDcyBr1WRTIDcyBr1.push_back(-1);
      for(unsigned int i=1;i<incCascDcyBr.size();i++)
        {
          if(vIdxOfHead1[i]==vMidxOfHead1[i])
            {
              vMIDcyBr1WRTIDcyBr1.push_back(0);
            }
          else
            {
              for(unsigned int j=0;j<i;j++)
                {
                  if(vIdxOfHead1[j]==vMidxOfHead1[i])
                    {
                      vMIDcyBr1WRTIDcyBr1.push_back(j);
                      break;
                    }
                }
            }
        }

      vector< vector<int> > vVIDcyBr2WRTIDcyBr1;
      vVIDcyBr2WRTIDcyBr1.clear();
      vector<int> vIDcyBr2WRTIDcyBr1;
      if(vIIncIncCascDcyBr[0]==0)
        {
          for(unsigned int i=0;i<dcyTr.size();i++)
            {
              if(dcyTr[i]==incCascDcyBr[0])
                {
                  vIDcyBr2WRTIDcyBr1.clear();
                  vIDcyBr2WRTIDcyBr1.push_back(i);
                  vVIDcyBr2WRTIDcyBr1.push_back(vIDcyBr2WRTIDcyBr1);
                }
            }
        }
      else
        {
          for(unsigned int i=0;i<dcyTr.size();i++)
            {
              if(isLiaMatchedWithLib(incCascDcyBr[0],dcyTr[i]))
                {
                  vIDcyBr2WRTIDcyBr1.clear();
                  vIDcyBr2WRTIDcyBr1.push_back(i);
                  vVIDcyBr2WRTIDcyBr1.push_back(vIDcyBr2WRTIDcyBr1);
                }
            }
        } 

      for(unsigned int i=0;i<vVIDcyBr2WRTIDcyBr1.size();i++)
        {
          for(unsigned int j=1;j<incCascDcyBr.size();j++)
            {
              for(unsigned int k=vVIDcyBr2WRTIDcyBr1[i][j-1]+1;k<dcyTr.size();k++)
                {
                  if(vIIncIncCascDcyBr[j]==0)
                    {                  
                      if(dcyTr[k]==incCascDcyBr[j]&&(vMidxOfHead2[k]==vIdxOfHead2[k]||vMidxOfHead2[k]==vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]]))
                        {
                          vVIDcyBr2WRTIDcyBr1[i].push_back(k);
                          break;
                        }
                    }
                  else
                    {
                      if(isLiaMatchedWithLib(incCascDcyBr[j],dcyTr[k])&&(vMidxOfHead2[k]==vIdxOfHead2[k]||vMidxOfHead2[k]==vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]]))
                        {
                          vVIDcyBr2WRTIDcyBr1[i].push_back(k);
                          break;
                        }
                    }
                }
              if(vVIDcyBr2WRTIDcyBr1[i].size()!=j+1) break;
            }
          if(vVIDcyBr2WRTIDcyBr1[i].size()==incCascDcyBr.size()) nCount++;
        }
    }

  return nCount;
}
