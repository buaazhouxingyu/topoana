#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::recurHighHierExchOrd(vector<int> & vIdxYngi,vector<int> & vIdxYngj,vector<int> & vPid,vector<int> & vMidx)
{
  if(vIdxYngi.size()!=vIdxYngj.size())
    {
      cerr<<"Error: The two vectors vIdxYngi and vIdxYngj have different sizes!"<<endl;
      cerr<<"Infor: The size of the vector vIdxYngi is "<<vIdxYngi.size()<<"."<<endl;
      cerr<<"Infor: The size of the vector vIdxYngj is "<<vIdxYngj.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

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

  vector< vector<int> > vVPidYngYngi, vVPidYngYngj;
  vector<int> vPidYngYngi, vPidYngYngj;
  vector<int> vPidYngYngMid, vMidxYngYngMid, vIdxYngYngMid;
  vector<int> vIdxYngYngi, vIdxYngYngj;
  int idxYngYng;
  bool exchOrd;
  while(vIdxYngi.size()!=0)
    {
      vVPidYngYngi.clear(); vVPidYngYngj.clear();
      vIdxYngYngi.clear(); vIdxYngYngj.clear();
      unsigned int l=vIdxYngj[vIdxYngj.size()-1]+1;
      for(unsigned int k=0;k<vIdxYngi.size();k++)
        {
          vPidYngYngi.clear();
          for(;l<vPid.size();l++)
            {
              if(vMidx[l]==vIdxYngi[k])
                {
                  vPidYngYngi.push_back(vPid[l]);
                  vIdxYngYngi.push_back(l);
                }
              else if(vMidx[l]>vIdxYngi[k])
                {
                  l--;
                  break;
                }
            }
          vVPidYngYngi.push_back(vPidYngYngi);
        }
      l++;
      for(unsigned int k=0;k<vIdxYngj.size();k++)
        { 
          vPidYngYngj.clear();
          for(;l<vPid.size();l++)
            { 
              if(vMidx[l]==vIdxYngj[k])
                {
                  vPidYngYngj.push_back(vPid[l]);
                  vIdxYngYngj.push_back(l);
                }
              else if(vMidx[l]>vIdxYngj[k])
                { 
                  l--;
                  break;
                }
            }
          vVPidYngYngj.push_back(vPidYngYngj);
        }
      if((vIdxYngYngi.size()!=0)&&(vIdxYngYngj.size()!=0))
        {
          vPidYngYngMid.clear(); vMidxYngYngMid.clear(); vIdxYngYngMid.clear();
          for(unsigned int k=((unsigned int) (vIdxYngYngi[(vIdxYngYngi.size()-1)]+1));k<((unsigned int) (vIdxYngYngj[0]));k++)
            {
              vPidYngYngMid.push_back(vPid[k]);
              vMidxYngYngMid.push_back(vMidx[k]);
              vIdxYngYngMid.push_back(k);
            }
          if(vVPidYngYngi!=vVPidYngYngj)
            {
              exchOrd=false;      
              for(unsigned int k=0;k<vVPidYngYngi.size();k++)
                {
                  if(cmprBySzPidAndPchrg(vVPidYngYngi[k],vVPidYngYngj[k]))
                    {
                      exchOrd=true;
                      break;
                    }
                }
              if(exchOrd==true)
                {
/*cout<<"Before sort1:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl;
    }*/
                  vector<int> vNewIdxYngYng, vOldIdxYngYng;
                  vNewIdxYngYng.clear(); vOldIdxYngYng.clear();
                  idxYngYng=vIdxYngYngi[0];
                  for(unsigned int k=0;k<vVPidYngYngj.size();k++)
                    for(unsigned int l1=0;l1<vVPidYngYngj[k].size();l1++) 
                      {
                        vPid[idxYngYng]=vVPidYngYngj[k][l1];
                        vMidx[idxYngYng]=vIdxYngi[k];
                        vNewIdxYngYng.push_back(idxYngYng);
                        idxYngYng++;
                      }
                  for(unsigned int k=0;k<vPidYngYngMid.size();k++)
                    {
                      vPid[idxYngYng]=vPidYngYngMid[k];
                      vMidx[idxYngYng]=vMidxYngYngMid[k];
                      vNewIdxYngYng.push_back(idxYngYng);
                      idxYngYng++;
                    }
                  for(unsigned int k=0;k<vVPidYngYngi.size();k++)
                    for(unsigned int l2=0;l2<vVPidYngYngi[k].size();l2++)
                      {
                        vPid[idxYngYng]=vVPidYngYngi[k][l2];
                        vMidx[idxYngYng]=vIdxYngj[k];
                        vNewIdxYngYng.push_back(idxYngYng);
                        idxYngYng++;
                      }
                  for(unsigned int k=0;k<vIdxYngYngj.size();k++) vOldIdxYngYng.push_back(vIdxYngYngj[k]);
                  for(unsigned int k=0;k<vIdxYngYngMid.size();k++) vOldIdxYngYng.push_back(vIdxYngYngMid[k]);
                  for(unsigned int k=0;k<vIdxYngYngi.size();k++) vOldIdxYngYng.push_back(vIdxYngYngi[k]);
/*cout<<"Before sort2:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl;
    }
                  recurHigherHierExchOrd(vNewIdxYngYng,vOldIdxYngYng,vPid,vMidx);
cout<<"Before sort3:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl;
    }*/
                  break;
                }
              else
                {
                  break;
                }
            }
          else
            {
              vIdxYngi=vIdxYngYngi;
              vIdxYngj=vIdxYngYngj;
            }
        }
      else
        {
          break;
        }
    }

  /*cout<<"After sort:"<<endl;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      cout<<"Idx: "<<i<<"\t"<<"Pid: "<<vPid[i]<<"\t"<<"Midx: "<<vMidx[i]<<endl; 
    }*/
}
