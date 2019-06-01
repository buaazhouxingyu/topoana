#include "../include/topoana.h"
#include <cstdlib>
#include <iostream>

// The fourth argument is appended for the special usage in the "countIncOrIRACascDcyBrsInDcyTr" method. 
unsigned int topoana::countIRADcyBr(vector<int> & vPid, vector<int> & vMidx, list<int> IRADcyBr, bool areHeadsRequiredToBeMatched, vector< vector< list<int> > > * vDcyBrIRADcyBr)
{
  vector<int> vIdx;
  vIdx.clear();
  list<int>::iterator liit=IRADcyBr.begin();
  if(areHeadsRequiredToBeMatched==true)
    {
      if(vPid.size()>0&&vPid[0]==(*liit)) vIdx.push_back(0);
    }
  else
    {
      // The condition "(*liit)==-11" is used for the special IRADcyBr started with the initial e+ and e-.
      if((*liit)==-11) vIdx.push_back(-1);
      else
        { 
          for(unsigned int i=0;i<vPid.size();i++)
            {
              if(vPid[i]==(*liit)) vIdx.push_back(i);
            }
        }
    }
  unsigned int nCount=0;
  list<int> IRADcyBrTmp;
  if(vDcyBrIRADcyBr!=0) (*vDcyBrIRADcyBr).clear();
  vector< list<int> > dcyBrIRADcyBr;
  list<int> subDcyBrIRADcyBr;
  vector<int> vIdxOld;
  vector<int> vIdxYng;
  for(unsigned int i=0;i<vIdx.size();i++)
    {
      IRADcyBrTmp.clear();
      for(unsigned int j=vIdx[i]+1;j<vPid.size();j++)
        {
          bool specifiedP=false;
          for(liit++;liit!=IRADcyBr.end();liit++)
            {
              if(vPid[j]==(*liit))
                {
                  specifiedP=true;
                  break;
                }
            }
          liit=IRADcyBr.begin();
          bool fsp=true;
          if(specifiedP==false)
            {
              for(unsigned int k=j+1;k<vPid.size();k++)
                {
                  if(((unsigned int) vMidx[k])==j)
                    {
                      fsp=false;
                      break;
                    }
                }
            }
          bool descendantOfOneSpecifiedP=false;
          for(liit++;liit!=IRADcyBr.end();liit++)
            {
              int k=j;
              while(1)
                {                     
                  // The condition "vIdx[i]==-1&&vMidx[k]!=k" is used for the special IRADcyBr started with the initial e+ and e-.
                  if(((vIdx[i]==-1&&vMidx[k]!=k)||(vIdx[i]!=-1))&&vPid[vMidx[k]]==(*liit))
                    {
                      descendantOfOneSpecifiedP=true;
                      break;
                    }
                  else if(vMidx[k]==k||vMidx[k]==-1)
                    {
                      break;
                    }
                  else
                    {
                      k=vMidx[k];
                    }
                }
              if(descendantOfOneSpecifiedP==true) break;
            }
          liit=IRADcyBr.begin();
          if((specifiedP==true||fsp==true)&&(descendantOfOneSpecifiedP==false))
            {
              bool fromTheP;
              // The condition "vIdx[i]==-1" is used for the special IRADcyBr started with the initial e+ and e-.
              if(vIdx[i]==-1) fromTheP=true;
              else 
                {
                  fromTheP=false;
                  int k=j;
                  while(1)
                    {
                      if(vMidx[k]==vIdx[i])
                        {
                          fromTheP=true;
                          break;
                        }
                      else if(vMidx[k]==k||vMidx[k]==-1)
                        {
                          break;
                        }
                      else
                        {
                          k=vMidx[k];
                        }
                    }
                }
              // The following condition "abs(vPid[j])==22" is exerted specially for the comparison without final state photons.
              if(fromTheP==true)
                {
                  // If the gFSR photons are ignored, then they don't show themselves up here. If they are not ignored, then their PDG codes are modified to be -22 or m_pidOfGFSRGam in the "sortPs" function.
                  if(m_ignoreGFSR==true) IRADcyBrTmp.push_back(vPid[j]);
                  else if(abs(vPid[j])!=-22&&vPid[j]!=m_pidOfGFSRGam) IRADcyBrTmp.push_back(vPid[j]);
                }
            } 
        }
     if(IRADcyBrTmp.size()>0)
       {
         sortByPidAndPchrg(IRADcyBrTmp);
         liit=IRADcyBr.begin();
         // The condition "(*liit)==-11" is used for the special IRADcyBr started with the initial e+ and e-.
         if((*liit)!=-11)
           {
             IRADcyBrTmp.push_front((*liit));
           }
         else
           {
             IRADcyBrTmp.push_front(11);
             IRADcyBrTmp.push_front(-11);
           }
         if(IRADcyBrTmp==IRADcyBr)
           {
             nCount++;
             if(m_vCompIRADcyBr.size()>0)
               {
                 dcyBrIRADcyBr.clear();
                 subDcyBrIRADcyBr.clear();
                 for(unsigned int j=vIdx[i]+1;j<vPid.size();j++)
                   {
                     // The condition "vIdx[i]==-1&&((unsigned int) vMidx[j]==j)" is used for the special IRADcyBr started with the initial e+ and e-.
                     if((vIdx[i]==-1&&((unsigned int) vMidx[j]==j))||(vIdx[i]!=-1&&vMidx[j]==vIdx[i]))
                       {
                         if(m_ignoreGFSR==true)
                           {
                             subDcyBrIRADcyBr.push_back(vPid[j]);
                             vIdxOld.push_back(j);
                           }
                         else if(abs(vPid[j])!=-22&&vPid[j]!=m_pidOfGFSRGam)
                           {
                             subDcyBrIRADcyBr.push_back(vPid[j]);
                             vIdxOld.push_back(j);
                           }
                       }
                   }
                 // The condition "vIdx[i]!=-1" is used for the special IRADcyBr started with the initial e+ and e-.
                 if(vIdx[i]!=-1)
                   {
                     subDcyBrIRADcyBr.push_front(vPid[vIdx[i]]);
                   }
                 else
                   {
                     subDcyBrIRADcyBr.push_front(11);
                     subDcyBrIRADcyBr.push_front(-11);
                   }
                 dcyBrIRADcyBr.push_back(subDcyBrIRADcyBr);
                 bool specifiedP;
                 while(vIdxOld.size()>0)
                   {
                     for(unsigned int j=0;j<vIdxOld.size();j++)
                       {
                         specifiedP=false;
                         liit=IRADcyBr.begin();
                         for(liit++;liit!=IRADcyBr.end();liit++)
                           {
                             if(vPid[vIdxOld[j]]==(*liit))
                               {
                                 specifiedP=true;
                                 break;
                               }
                           }
                         if(specifiedP==false)
                           {
                             subDcyBrIRADcyBr.clear();
                             subDcyBrIRADcyBr.push_back(vPid[vIdxOld[j]]);
                             for(unsigned int k=vIdxOld[j]+1;k<vPid.size();k++)
                               {
                                 if(vMidx[k]==vIdxOld[j])
                                   {
                                     if(m_ignoreGFSR==true)
                                       {
                                         subDcyBrIRADcyBr.push_back(vPid[k]);
                                         vIdxYng.push_back(k);
                                       }
                                     else if(abs(vPid[k])!=-22&&vPid[k]!=m_pidOfGFSRGam)
                                       {
                                         subDcyBrIRADcyBr.push_back(vPid[k]);
                                         vIdxYng.push_back(k);
                                       }
                                   }
                               }
                             dcyBrIRADcyBr.push_back(subDcyBrIRADcyBr);
                           }
                       }
                     vIdxOld=vIdxYng;
                     vIdxYng.clear();
                   } 
                 (*vDcyBrIRADcyBr).push_back(dcyBrIRADcyBr);
               }
           }
       }
    }
  return nCount;
}
