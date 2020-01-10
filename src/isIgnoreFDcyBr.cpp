#include "../include/topoana.h"

bool topoana::isIgnoreFDcyBr(int mPid, vector<int> vPidYngSbst, vector< list<int> > vIgnoreFDcyBr)
{
  bool isIgnoreFDcyBr=false;
  list<int>::iterator liit;
  unsigned int j;
  for(unsigned int i=0;i<vIgnoreFDcyBr.size();i++)
    {
      liit=vIgnoreFDcyBr[i].begin();
      if((*liit)!=mPid) continue;
      else if(vPidYngSbst.size()+1!=vIgnoreFDcyBr[i].size()) continue; 
      else
        {
          for(j=0;j<vPidYngSbst.size();j++)
            {
              liit++;
              if(vPidYngSbst[j]!=(*liit)) break;
            }
          if(j!=vPidYngSbst.size()) continue;
          else
            {
              isIgnoreFDcyBr=true;
              break;
            }
        }
    } 
  if(isIgnoreFDcyBr==true) return isIgnoreFDcyBr;
  else if(m_ccSwitch==true)
    {
      for(unsigned int i=0;i<m_vCcIgnoreFDcyBr.size();i++)
        { 
          if(m_vICcIgnoreFDcyBr[i]==0) continue;
          liit=m_vCcIgnoreFDcyBr[i].begin();
          if((*liit)!=mPid) continue;
          else if(vPidYngSbst.size()+1!=m_vCcIgnoreFDcyBr[i].size()) continue;
          else
            { 
              for(j=0;j<vPidYngSbst.size();j++)
                { 
                  liit++;
                  if(vPidYngSbst[j]!=(*liit)) break;
                }
              if(j!=vPidYngSbst.size()) continue;
              else
                { 
                  isIgnoreFDcyBr=true;
                  break;
                }
            }
        }
      return isIgnoreFDcyBr; 
    }
  else return isIgnoreFDcyBr;
}
