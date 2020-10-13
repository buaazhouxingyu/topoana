#include "../include/topoana.h"
#include <cstdlib>
#include <iostream>

// The fourth argument is added for the special usage in the "countIncOrIRACascDcyBrInDcyTr" method, while the fifth and sixth arguments are appendied for the functionality of the component analysis over inclusive decay branches with the options "Is-IRA", "Ig-IRA", "Fs-IRA", or "Fg-IRA".

unsigned int topoana::countIRADcyBr(vector<int> & vPid, vector<int> & vMidx, list<int> IRADcyBr, bool areHeadsRequiredToBeMatched, vector< vector< list<int> > > * vDcyBrIRADcyBr,vector< list<int> > * vIRADcyBrWithRGam,string option)
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
      // The condition "(*liit)==m_pidOfISt2" is used for the special IRADcyBr started with the initial particles.
      if((*liit)==m_pidOfISt2) vIdx.push_back(-1);
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
  if(vIRADcyBrWithRGam!=0) (*vIRADcyBrWithRGam).clear();
  list<int> IRADcyBrWithRGam;
  for(unsigned int i=0;i<vIdx.size();i++)
    {
      IRADcyBrTmp.clear();
      if(vIRADcyBrWithRGam!=0) IRADcyBrWithRGam.clear();
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
                  // The condition "vIdx[i]==-1&&vMidx[k]!=k" is used for the special IRADcyBr started with the initial particles.
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
              // The condition "vIdx[i]==-1" is used for the special IRADcyBr started with the initial particles.
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
              // The following condition "abs(vPid[j])==m_pidOfGam" is exerted specially for the comparison without final state photons.
              if(fromTheP==true)
                {
                  if(vIRADcyBrWithRGam==0) IRADcyBrTmp.push_back(vPid[j]);
                  else
                    {
                      if(option=="Is-IRA"&&vPid[j]!=m_pidOfSISRGam) IRADcyBrTmp.push_back(vPid[j]);
                      else if(option=="Ig-IRA"&&vPid[j]!=m_pidOfGISRGam) IRADcyBrTmp.push_back(vPid[j]);
                      else if(option=="Fs-IRA"&&vPid[j]!=m_pidOfSFSRGam) IRADcyBrTmp.push_back(vPid[j]);
                      else if(option=="Fg-IRA"&&vPid[j]!=m_pidOfGFSRGam) IRADcyBrTmp.push_back(vPid[j]);
                      IRADcyBrWithRGam.push_back(vPid[j]);
                    }
                }
            } 
        }
     if(IRADcyBrTmp.size()>0)
       {
         sortByPidAndPchrg(IRADcyBrTmp);
         if(vIRADcyBrWithRGam!=0) sortByPidAndPchrg(IRADcyBrWithRGam);
         liit=IRADcyBr.begin();
         // The condition "(*liit)==m_pidOfISt2" is used for the special IRADcyBr started with the initial particles.
         if((*liit)!=m_pidOfISt2)
           {
             IRADcyBrTmp.push_front((*liit));
             if(vIRADcyBrWithRGam!=0) IRADcyBrWithRGam.push_front((*liit));
           }
         else
           {
             IRADcyBrTmp.push_front(m_pidOfISt1);
             IRADcyBrTmp.push_front(m_pidOfISt2);
             if(vIRADcyBrWithRGam!=0)
               {
                 IRADcyBrWithRGam.push_front(m_pidOfISt1);
                 IRADcyBrWithRGam.push_front(m_pidOfISt2);
               }
           }
         if(IRADcyBrTmp==IRADcyBr)
           {
             nCount++;
             if(vDcyBrIRADcyBr!=0)
               {
                 dcyBrIRADcyBr.clear();
                 subDcyBrIRADcyBr.clear();
                 for(unsigned int j=vIdx[i]+1;j<vPid.size();j++)
                   {
                     // The condition "vIdx[i]==-1&&((unsigned int) vMidx[j]==j)" is used for the special IRADcyBr started with the initial particles.
                     if((vIdx[i]==-1&&((unsigned int) vMidx[j]==j))||(vIdx[i]!=-1&&vMidx[j]==vIdx[i]))
                       {
                         subDcyBrIRADcyBr.push_back(vPid[j]);
                         vIdxOld.push_back(j);
                       }
                   }
                 // The condition "vIdx[i]!=-1" is used for the special IRADcyBr started with the initial particles.
                 if(vIdx[i]!=-1)
                   {
                     subDcyBrIRADcyBr.push_front(vPid[vIdx[i]]);
                   }
                 else
                   {
                     subDcyBrIRADcyBr.push_front(m_pidOfISt1);
                     subDcyBrIRADcyBr.push_front(m_pidOfISt2);
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
                                     subDcyBrIRADcyBr.push_back(vPid[k]);
                                     vIdxYng.push_back(k);
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
             if(vIRADcyBrWithRGam!=0) (*vIRADcyBrWithRGam).push_back(IRADcyBrWithRGam);
           }
       }
    }
  return nCount;
}
