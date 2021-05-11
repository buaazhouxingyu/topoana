#include "../include/topoana.h"
#include <iostream>

unsigned int topoana::countCascDcyBrInDcyTr(vector< list<int> > & cascDcyBr, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2, int * Ridx, vector<int> vIdxOrg, string typeOfTagRec, int tagrecsi, int * tagreca, int nrec)
{
  unsigned int nCount=0;
  if(cascDcyBr.size()==0)
    {
      cerr<<"Infor: The size of the vector for the cascade decay branches is zero!"<<endl<<endl;
      return nCount;
    }
  if(dcyTr.size()==0)
    {
      cerr<<"Infor: The size of the vector for the decay tree is zero!"<<endl<<endl;
      return nCount;
    }
  if(cascDcyBr.size()<=dcyTr.size())
    {
      /*for(unsigned int i=0;i<cascDcyBr.size();i++)
        {
          list<int>::iterator liit,liitTmp=cascDcyBr[i].end();liitTmp--;
          for(liit=cascDcyBr[i].begin();liit!=cascDcyBr[i].end();liit++)
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
      for(unsigned int i=1;i<cascDcyBr.size();i++)
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
      bool _isTagMatched;
      for(unsigned int i=0;i<dcyTr.size();i++)
        {
          if(typeOfTagRec!="")
            {
              if(typeOfTagRec!="i"&&typeOfTagRec!="I") _isTagMatched=isTagMatched(typeOfTagRec, tagrecsi, tagreca, nrec, (*cascDcyBr[0].begin()));
              else _isTagMatched=isTagMatched(typeOfTagRec, tagrecsi, tagreca, nrec, Ridx[vIdxOrg[vIdxOfHead2[i]]]);
              if(_isTagMatched==false) continue;
            }
          if(dcyTr[i]==cascDcyBr[0])
            {
              vIDcyBr2WRTIDcyBr1.clear();
              vIDcyBr2WRTIDcyBr1.push_back(i);
              vVIDcyBr2WRTIDcyBr1.push_back(vIDcyBr2WRTIDcyBr1);
            }
        }

      for(unsigned int i=0;i<vVIDcyBr2WRTIDcyBr1.size();i++)
        {
          for(unsigned int j=1;j<cascDcyBr.size();j++)
            {
              for(unsigned int k=vVIDcyBr2WRTIDcyBr1[i][j-1]+1;k<dcyTr.size();k++)
                {
                  if(dcyTr[k]==cascDcyBr[j]&&(vMidxOfHead2[k]==vIdxOfHead2[k]||vMidxOfHead2[k]==vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]]))
                    {
                      vVIDcyBr2WRTIDcyBr1[i].push_back(k);
                      break;
                    }
                }
              if(vVIDcyBr2WRTIDcyBr1[i].size()!=j+1) break;
            }
          if(vVIDcyBr2WRTIDcyBr1[i].size()==cascDcyBr.size()) nCount++;
        }
    }

  return nCount;
}
