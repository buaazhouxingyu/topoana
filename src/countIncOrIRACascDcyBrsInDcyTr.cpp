#include "../include/topoana.h"
#include <iostream>

unsigned int topoana::countIncOrIRACascDcyBrsInDcyTr(vector<int> vIIncIncOrIRACascDcyBrs, vector<int> vIIRAIncOrIRACascDcyBrs, vector< list<int> > & incOrIRACascDcyBrs, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2, vector<int> vPid, vector<int> vMidx)
{
  unsigned int nCount=0;

  if(incOrIRACascDcyBrs.size()==0)
    {
      cerr<<"Infor: The size of the vector for the inclusive or intermediate-resonance-allowed cascade decay branches is zero!"<<endl<<endl;
      return nCount;
    }

  if(dcyTr.size()==0)
    {
      cerr<<"Infor: The size of the vector for the decay tree is zero!"<<endl<<endl;
      return nCount;
    }

  if(incOrIRACascDcyBrs.size()<=dcyTr.size())
    {
      /*for(unsigned int i=0;i<incOrIRACascDcyBrs.size();i++)
        {
          list<int>::iterator liit,liitTmp=incOrIRACascDcyBrs[i].end();liitTmp--;
          for(liit=incOrIRACascDcyBrs[i].begin();liit!=incOrIRACascDcyBrs[i].end();liit++)
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
      for(unsigned int i=1;i<incOrIRACascDcyBrs.size();i++)
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
      vector<int> subsetOfVPidFromAP;
      vector<int> subsetOfVMidxFromAP; 
      bool headsAreRequiredToBeMatched=true;
      if(vIIncIncOrIRACascDcyBrs[0]==0)
        {
          for(unsigned int i=0;i<dcyTr.size();i++)
            {
              if(dcyTr[i]==incOrIRACascDcyBrs[0])
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
              if(isLiaMatchedWithLib(incOrIRACascDcyBrs[0],dcyTr[i]))
                {
                  vIDcyBr2WRTIDcyBr1.clear();
                  vIDcyBr2WRTIDcyBr1.push_back(i);
                  vVIDcyBr2WRTIDcyBr1.push_back(vIDcyBr2WRTIDcyBr1);
                }
            }
        } 

      for(unsigned int i=0;i<vVIDcyBr2WRTIDcyBr1.size();i++)
        {
          for(unsigned int j=1;j<incOrIRACascDcyBrs.size();j++)
            {
              for(unsigned int k=vVIDcyBr2WRTIDcyBr1[i][j-1]+1;k<dcyTr.size();k++)
                {
                  if(vIIncIncOrIRACascDcyBrs[j]==0)
                    {                  
                      if(vIIRAIncOrIRACascDcyBrs[j]==0)
                        {
                          if(dcyTr[k]==incOrIRACascDcyBrs[j]&&(vMidxOfHead2[k]==vIdxOfHead2[k]||(vIIRAIncOrIRACascDcyBrs[j-1]==0&&vMidxOfHead2[k]==vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]])||(vIIRAIncOrIRACascDcyBrs[j-1]==1&&isPaADescendantOfPb(vMidx,vIdxOfHead2[k],vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]]))))
                            {
                              vVIDcyBr2WRTIDcyBr1[i].push_back(k);
                              break;
                            }
                        }
                      else
                        {
                          if((*(dcyTr[k].begin()))==(*(incOrIRACascDcyBrs[j].begin())))
                            {
                              subsetOfVPidFromAP=vPid;
                              subsetOfVMidxFromAP=vMidx;
                              getSubsetsOfVPidandVMidxFromAP(subsetOfVPidFromAP,subsetOfVMidxFromAP,vIdxOfHead2[k]);
                              if(countIRADcyBr(subsetOfVPidFromAP,subsetOfVMidxFromAP,incOrIRACascDcyBrs[j],headsAreRequiredToBeMatched)&&(vMidxOfHead2[k]==vIdxOfHead2[k]||(vIIRAIncOrIRACascDcyBrs[j-1]==0&&vMidxOfHead2[k]==vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]])||(vIIRAIncOrIRACascDcyBrs[j-1]==1&&isPaADescendantOfPb(vMidx,vIdxOfHead2[k],vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]]))))
                                {
                                  vVIDcyBr2WRTIDcyBr1[i].push_back(k);
                                  break;
                                }
                            }                    
                        }
                    }
                  else
                    {
                      if(isLiaMatchedWithLib(incOrIRACascDcyBrs[j],dcyTr[k])&&(vMidxOfHead2[k]==vIdxOfHead2[k]||(vIIRAIncOrIRACascDcyBrs[j-1]==0&&vMidxOfHead2[k]==vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]])||(vIIRAIncOrIRACascDcyBrs[j-1]==1&&isPaADescendantOfPb(vMidx,vIdxOfHead2[k],vIdxOfHead2[(unsigned int) vVIDcyBr2WRTIDcyBr1[i][(unsigned int) vMIDcyBr1WRTIDcyBr1[j]]]))))
                        {
                          vVIDcyBr2WRTIDcyBr1[i].push_back(k);
                          break;
                        }
                    }
                }
              if(vVIDcyBr2WRTIDcyBr1[i].size()!=j+1) break;
            }
          if(vVIDcyBr2WRTIDcyBr1[i].size()==incOrIRACascDcyBrs.size()) nCount++;
        }
    }

  return nCount;
}
