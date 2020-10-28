#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::sortPs(vector<int> & vPid, vector<int> & vMidx, vector<int> * vIdxOrg)
{
  if(vPid.size()!=vMidx.size())
    {
      cerr<<"Error: The two vectors vPid and vMidx have different sizes!"<<endl;
      cerr<<"Infor: The size of the vector vPid is "<<vPid.size()<<"."<<endl;
      cerr<<"Infor: The size of the vector vMidx is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  /*cout<<"Before sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl;
    }*/

  if(m_pidOfSISRGamUser!=m_pidOfSISRGam) 
    for(unsigned int i=0;i<vPid.size();i++) 
      if(vPid[i]==m_pidOfSISRGamUser) vPid[i]=m_pidOfSISRGam;

  if(m_pidOfSFSRGamUser!=m_pidOfSFSRGam) 
    for(unsigned int i=0;i<vPid.size();i++) 
      if(vPid[i]==m_pidOfSFSRGamUser) vPid[i]=m_pidOfSFSRGam;

  vector<int> vPidFnl,vMidxFnl,vIdxFnl;
  vector<int> vPidOld,vMidxOld,vIdxOld,vNSmPidsOld;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      //if(((unsigned int) vMidx[i])==i) Sometimes, users may set Midx[i] at -1 rather than i when the pid of the mother of the partilce i does not appear in the array Pid. Note that the arrays Pid and Midx are the branches stored in the tree of the input root files. In order to make the program can handle such cases as well, this statement is revised to be the following one.
      if((((unsigned int) vMidx[i])==i)||(vMidx[i]==-1))
	{
          if(vPid[i]==m_pidOfSISRGam)
            {
              if(m_ignoreISR=="N") vPidOld.push_back(m_pidOfSISRGam);
              else continue;
            }
          else if(vPid[i]==m_pidOfGam)
            {
              if(m_ignoreISR!="Yg")
                {
                  if((m_pidOfISt1==m_pidOfE)&&(m_pidOfISt2==-1*m_pidOfE)) vPidOld.push_back(m_pidOfGISRGam);
                  else vPidOld.push_back(vPid[i]);
                }
              else continue;
            }
          else vPidOld.push_back(vPid[i]);

          //vMidxOld.push_back(vMidx[i]); Sometimes, users may set Midx[i] at -1 rather than i when the pid of the mother of the partilce i does not appear in the array Pid. Note that the arrays Pid and Midx are the branches stored in the tree of the input root files. In order to make the program can handle such cases as well, this statement is revised to be the following one. Then, the following parts of the program do not have to change any more.
          vMidxOld.push_back(i);
          vIdxOld.push_back(i);
	}
    }
  sortByPidAndPchrg(vPidOld,vMidxOld,vIdxOld,vNSmPidsOld);
  for(unsigned int i=0;i<vPidOld.size();i++)
    {
      vPidFnl.push_back(vPidOld[i]);
      vMidxFnl.push_back(vMidxOld[i]);
      vIdxFnl.push_back(vIdxOld[i]);
    }

  unsigned int hHdDcyBrs; // Codes related to the variable is used to contol maximum hierarchy of heading decay branches to be processed in each event. 
  if(vPidOld.size()==1) hHdDcyBrs=0;
  else hHdDcyBrs=1; 
  bool isIdPid; // Codes related to the variable is used to ignore the decay of the particles specified in the input card and stored in the vector m_vIdPid.
  bool isIddPid; // Codes related to the variable is used to ignore the decay of the daughters of the particles specified in the input card and stored in the vector m_vIddPid. 
 
  unsigned int nCSmPids;
  vector<int> vIdxYng, vNSmPidsYng;
  vector< vector<int> > vVPidYngSbst,vVMidxYngSbst,vVIdxYngSbst,vVNSmPidsYngSbst;
  vector<int> vPidYngSbst,vMidxYngSbst,vIdxYngSbst,vNSmPidsYngSbst;
  while(hHdDcyBrs<m_hHdDcyBrsMax&&vIdxOld.size()!=0)
    {
      vIdxYng.clear();
      vNSmPidsYng.clear();
      nCSmPids=0;
      for(unsigned int i=0;i<vNSmPidsOld.size();i++)
        {
          isIdPid=false;
          for(unsigned int j=0;j<m_vIdPid.size();j++)
            {
              if(vPid[vIdxOld[nCSmPids]]==m_vIdPid[j])
                {
                  isIdPid=true;
                  break;
                }
            }
          if(isIdPid==true)
            {
              nCSmPids=nCSmPids+vNSmPidsOld[i]; // Don't miss out the statement. Otherwise, the program will go wrong where the variable nCSmPids is used. 
              continue;
            }

          isIddPid=false;
          for(unsigned int j=0;j<m_vIddPid.size();j++)
            {
              if(vPid[vIdxOld[nCSmPids]]==m_vIddPid[j])
                {
                  isIddPid=true;
                  break;
                }
            }

          vVPidYngSbst.clear();
          vVMidxYngSbst.clear();
          vVIdxYngSbst.clear();
          vVNSmPidsYngSbst.clear();
          for(unsigned int j=0;j<((unsigned int) vNSmPidsOld[i]);j++)
            {
              vPidYngSbst.clear();
              vMidxYngSbst.clear();
              vIdxYngSbst.clear();
              vNSmPidsYngSbst.clear();
              for(unsigned int k=0;k<vPid.size();k++)
	        {
                  //if((((unsigned int) vMidx[k])!=k)&&vMidx[k]==vIdxOld[nCSmPids+j]) Sometimes, users may set Midx[i] at -1 rather than i when the pid of the mother of the partilce i does not appear in the array Pid. Note that the arrays Pid and Midx are the branches stored in the tree of the input root files. In order to make the program can handle such cases as well, this statement is revised to be the following one.
                  if(((((unsigned int) vMidx[k])!=k)&&(vMidx[k]!=-1))&&(vMidx[k]==vIdxOld[nCSmPids+j]))
	            {
                      if(abs(vPid[k])!=m_pidOfGam)
                        {
                          vPidYngSbst.push_back(vPid[k]);
                        }
                      else if(vPid[k]==m_pidOfSFSRGam)
                        {
                          if(m_ignoreFSR=="N") vPidYngSbst.push_back(m_pidOfSFSRGam);
                          else continue;
                        }
                      else
                        { 
                          bool isGFSR=false;
                          // The following two variables are defined and used in order to avoid mistaking photons in decays like rho+ --> pi+ gamma as generalized FSR photons.
                          unsigned int nSister=0;
                          bool hasAemupiKpSister=false; 

                          // In the following conditions, (k-l) is necessary to be converted from (unsigned int) type to (int) type. Or, the condition will lose its effectiveness when k<l.
                          for(unsigned int l=1;((k+l)<vPid.size()||((int)(k-l))>=0);l++)
                            {
                              if((k+l)<vPid.size())
                                {
                                  if(vMidx[k+l]==vMidx[k])
                                    {
                                      if(vPid[k+l]!=m_pidOfGam) nSister++;
                                      if(abs(vPid[k+l])==m_pidOfE||abs(vPid[k+l])==m_pidOfMu||abs(vPid[k+l])==m_pidOfPi||abs(vPid[k+l])==m_pidOfK||abs(vPid[k+l])==m_pidOfP) hasAemupiKpSister=true;
                                      if(nSister>=2&&hasAemupiKpSister==true)
                                        {
                                          isGFSR=true;
                                          break;
                                        }
                                    }
                                }
                              if(((int)(k-l))>=0)
                                {
                                  if(vMidx[k-l]==vMidx[k])
                                    {
                                      if(vPid[k-l]!=m_pidOfGam) nSister++;
                                      if(abs(vPid[k-l])==m_pidOfE||abs(vPid[k-l])==m_pidOfMu||abs(vPid[k-l])==m_pidOfPi||abs(vPid[k-l])==m_pidOfK||abs(vPid[k-l])==m_pidOfP) hasAemupiKpSister=true;
                                      if(nSister>=2&&hasAemupiKpSister==true)
                                        {
                                          isGFSR=true;
                                          break;
                                        }
                                    }
                                }                                      
                            }
                          if(isGFSR==true)
                            {
                              if(m_ignoreFSR!="Yg") vPidYngSbst.push_back(m_pidOfGFSRGam);
                              else continue;
                            }
                          else
                            {
                              vPidYngSbst.push_back(vPid[k]);
                            }
                        }
	              vMidxYngSbst.push_back(vMidx[k]); // Note that vMidx[k] is equal to vIdxOld[nCSmPids+j].
	              vIdxYngSbst.push_back(k);
	            }
	        }
              if(vPidYngSbst.size()>0)
                {
                  if((m_retainPi02GamGam==false)&&(vPid[vMidxYngSbst[0]]==m_pidOfPi0)&&(vPidYngSbst.size()==2)&&(vPidYngSbst[0]==m_pidOfGam)&&(vPidYngSbst[1]==m_pidOfGam)) continue; // This statement is added to remove the decay of pi0 to gamma gamma. Here, note that vMidxYngSbst[0] is equal to vIdxOld[nCSmPids+j], which has the same mother with vIdxOld[nCSmPids]. 
                  sortByPidAndPchrg(vPidYngSbst,vMidxYngSbst,vIdxYngSbst,vNSmPidsYngSbst);
                  if(isIgnoreFDcyBr(vPid[vMidxYngSbst[0]],vPidYngSbst,m_vIgnoreFDcyBr)==true) continue;
                  // The following four statements should be put in the scope of the if statement, otherwise empty vectors might be pushed back to these vectors of vector. 
                  vVPidYngSbst.push_back(vPidYngSbst);
                  vVMidxYngSbst.push_back(vMidxYngSbst);
                  vVIdxYngSbst.push_back(vIdxYngSbst);
                  vVNSmPidsYngSbst.push_back(vNSmPidsYngSbst);
                }
            }
          if(vVPidYngSbst.size()>1) sortBySzPidAndPchrg(vVPidYngSbst,vVMidxYngSbst,vVIdxYngSbst,vVNSmPidsYngSbst);
          for(unsigned int j=0;j<vVPidYngSbst.size();j++)
            {
              for(unsigned int k=0;k<vVPidYngSbst[j].size();k++)
	        {
	          vPidFnl.push_back(vVPidYngSbst[j][k]);
	          vMidxFnl.push_back(vVMidxYngSbst[j][k]);
                  vIdxFnl.push_back(vVIdxYngSbst[j][k]);
                }
              if(isIddPid==false)
                {
                  for(unsigned int k=0;k<vVPidYngSbst[j].size();k++)
                    {
	              vIdxYng.push_back(vVIdxYngSbst[j][k]);
	            }
                  for(unsigned int k=0;k<vVNSmPidsYngSbst[j].size();k++)
                    {
                      vNSmPidsYng.push_back(vVNSmPidsYngSbst[j][k]);
                    }
                }            
            }
          nCSmPids=nCSmPids+vNSmPidsOld[i];
        }
      vIdxOld.clear();
      vIdxOld=vIdxYng;
      vNSmPidsOld.clear();
      vNSmPidsOld=vNSmPidsYng;
      hHdDcyBrs++;
    }

  for(unsigned int i=0;i<vMidxFnl.size();i++)
    {
      for(unsigned int j=0;j<vIdxFnl.size();j++)
        {
          if(vIdxFnl[j]==vMidxFnl[i])
            {
              vMidxFnl[i]=j;
              break;
            }
        }
    }
  vPid.clear();
  vMidx.clear();
  vPid=vPidFnl;
  vMidx=vMidxFnl;
  if(vIdxOrg!=0) (*vIdxOrg)=vIdxFnl;

  vector<int> vPidYngi, vPidYngj;
  vector<int> vIdxYngi, vIdxYngj;
  for(unsigned int i=0;i<vPid.size();i++)
    for(unsigned int j=i+1;j<vPid.size();j++)
      {
        if(vPid[j]==vPid[i]&&vMidx[j]==vMidx[i])
          {
            vPidYngi.clear(); vPidYngj.clear();
            vIdxYngi.clear(); vIdxYngj.clear();
            for(unsigned int k=j+1;k<vPid.size();k++)
              {
                if(((unsigned int) vMidx[k])==i)
                  {
                    vPidYngi.push_back(vPid[k]);
                    vIdxYngi.push_back(k);
                  }
                else if(((unsigned int) vMidx[k])==j)
                  {
                    vPidYngj.push_back(vPid[k]);
                    vIdxYngj.push_back(k);
                  }
                else if(((unsigned int) vMidx[k])>j)
                  {
                    break;
                  }
              }
            if((vPidYngi.size()!=0)&&(vPidYngi==vPidYngj)) recurHighHierExchOrd(vIdxYngi, vIdxYngj, vPid, vMidx, vIdxOrg);
          }
      }

  /*cout<<"After sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl; 
    }*/
}
