#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

bool topoana::cmprBySzPidAndPchrg(vector<int> & via, vector<int> & vib)
{
  bool exchOrd=false;
  if(via.size()>vib.size()) exchOrd=true;
  else if(via.size()==vib.size())
    {
      for(unsigned int k=0;k<via.size();k++)
        {
          if(abs(via[k])>abs(vib[k]))
            {
              if(abs(vib[k])!=m_pidOfGam)
                {                    
                  exchOrd=true;
                  break;
                }
              else
                {
                  break;
                }
            }
          else if(abs(via[k])==abs(vib[k]))
            {
              if(m_pid3PchrgMap.find(via[k])!=m_pid3PchrgMap.end()&&m_pid3PchrgMap.find(vib[k])!=m_pid3PchrgMap.end())
                {              
                  if(m_pid3PchrgMap[via[k]]<m_pid3PchrgMap[vib[k]])
                    {
                      exchOrd=true;        
                      break;
                    }
                  else if(m_pid3PchrgMap[via[k]]>m_pid3PchrgMap[vib[k]])
                    {
                      break;
                    }
                  else
                    {
                      if(via[k]<vib[k])
                        {
                          exchOrd=true;
                          break;
                        }
                      else if(via[k]>vib[k])
                        {
                          break;
                        }
                    }                        
                }
              else
                {
                  if(m_pid3PchrgMap.find(via[k])==m_pid3PchrgMap.end()) writeErrInfOnPid3PchrgMap(via[k]);
                  if(m_pid3PchrgMap.find(vib[k])==m_pid3PchrgMap.end()) writeErrInfOnPid3PchrgMap(vib[k]);
                }                    
            }
          else // Please don't forget this part of the if statement.
            { 
              if(abs(via[k])==m_pidOfGam)
                {
                  exchOrd=true;
                  break;
                }
              else
                {
                  break;
                }
            }
        }
    }
  return exchOrd;
}
