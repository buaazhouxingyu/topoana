#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

void topoana::sortByPidAndPchrg(vector<int> &via,vector<int> &vib,vector<int> &vic,vector<int> &vid)
{
  if(via.size()!=vib.size()||vib.size()!=vic.size())
    {
      cerr<<"Error: The three vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<vib.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vic.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via.size()==0)
    {
      cerr<<"Infor: The sizes of the three vectors are zero!"<<endl<<endl;
      return;
    }

  /*cout<<"Before sort:"<<endl;
  for(unsigned int i=0;i<via.size();i++)
    { 
      if(i<(via.size()-1)) cout<<via[i]<<" ";
      else cout<<via[i]<<endl;
    }
  for(unsigned int i=0;i<vib.size();i++)
    {
      if(i<(vib.size()-1)) cout<<vib[i]<<" ";
      else cout<<vib[i]<<endl;
    }*/

  int iaTmp,ibTmp,icTmp;
  for(unsigned int i=0;i<(via.size()-1);i++)
    for(unsigned int j=i+1;j<via.size();j++)
      {
        if(abs(via[i])>abs(via[j]))
          {
            if(abs(via[j])!=22)
              {
                iaTmp=via[i];
                via[i]=via[j];
                via[j]=iaTmp;
                ibTmp=vib[i];
                vib[i]=vib[j];
                vib[j]=ibTmp;
                icTmp=vic[i];
                vic[i]=vic[j];
                vic[j]=icTmp;
              }
          }
        else if(abs(via[i])==abs(via[j]))
          {
            if(m_pid3PchrgMap.find(via[i])!=m_pid3PchrgMap.end()&&m_pid3PchrgMap.find(via[j])!=m_pid3PchrgMap.end())
              {              
                if(m_pid3PchrgMap[via[i]]<m_pid3PchrgMap[via[j]])
                  {
                    iaTmp=via[i];
                    via[i]=via[j];
                    via[j]=iaTmp;
                    ibTmp=vib[i];
                    vib[i]=vib[j];
                    vib[j]=ibTmp;
                    icTmp=vic[i];
                    vic[i]=vic[j];
                    vic[j]=icTmp;
                  }
                else if(m_pid3PchrgMap[via[i]]==m_pid3PchrgMap[via[j]])
                  {
                    if(via[i]<via[j])
                      {
                        iaTmp=via[i];
                        via[i]=via[j];
                        via[j]=iaTmp;
                        ibTmp=vib[i];
                        vib[i]=vib[j];
                        vib[j]=ibTmp;
                        icTmp=vic[i];
                        vic[i]=vic[j];
                        vic[j]=icTmp;
                      }  
                  }
              }
            else
              {
                if(m_pid3PchrgMap.find(via[i])==m_pid3PchrgMap.end()) writeErrInfOnPid3PchrgMap(via[i]);
                if(m_pid3PchrgMap.find(via[j])==m_pid3PchrgMap.end()) writeErrInfOnPid3PchrgMap(via[j]);
              }
          }
        else
          {
            if(abs(via[i])==22)
              {
                iaTmp=via[i];
                via[i]=via[j];
                via[j]=iaTmp;
                ibTmp=vib[i];
                vib[i]=vib[j];
                vib[j]=ibTmp;
                icTmp=vic[i];
                vic[i]=vic[j];
                vic[j]=icTmp;
              }
          }
      }


  /*cout<<"After sort:"<<endl;
  for(unsigned int i=0;i<via.size();i++)
    {
      if(i<(via.size()-1)) cout<<via[i]<<" ";
      else cout<<via[i]<<endl;
    }
  for(unsigned int i=0;i<vib.size();i++)
    {
      if(i<(vib.size()-1)) cout<<vib[i]<<" ";
      else cout<<vib[i]<<endl;
    }*/

  vid.clear();
  int nSmPids;
  for(unsigned int i=0;i<via.size();i++)
    {
      nSmPids=count(via.begin(),via.end(),via[i]);
      vid.push_back(nSmPids);
      i=i+(nSmPids-1);
    }
  /*for(unsigned int i=0;i<vid.size();i++)
    {
      if(i<(vid.size()-1)) cout<<vid[i]<<" ";
      else cout<<vid[i]<<endl;
    }*/
}

void topoana::sortByPidAndPchrg(list<int> &lia)
{
  if(lia.size()==0)
    {
      cerr<<"Infor: The size of the list is zero."<<endl<<endl;
      return;
    }
  int iaTmp;
  list<int>::iterator liait1;
  list<int>::iterator liait2;
  list<int>::iterator liaitLastButOne=lia.end();liaitLastButOne--;
  for(liait1=lia.begin();liait1!=liaitLastButOne;liait1++)
    for(liait2=liait1,liait2++;liait2!=lia.end();liait2++)
      {
        if(abs((*liait1))>abs((*liait2)))
          {
            if(abs((*liait2))!=22)
              {
                iaTmp=(*liait1);
                (*liait1)=(*liait2);
                (*liait2)=iaTmp;
              }
          }
        else if(abs((*liait1))==abs((*liait2)))
          {
            if(m_pid3PchrgMap.find((*liait1))!=m_pid3PchrgMap.end()&&m_pid3PchrgMap.find((*liait2))!=m_pid3PchrgMap.end())
              {
                if(m_pid3PchrgMap[(*liait1)]<m_pid3PchrgMap[(*liait2)])
                  {
                    iaTmp=(*liait1);
                    (*liait1)=(*liait2);
                    (*liait2)=iaTmp;
                  }
                else if(m_pid3PchrgMap[(*liait1)]==m_pid3PchrgMap[(*liait2)])
                  {
                    if((*liait1)<(*liait2))
                      {
                        iaTmp=(*liait1);
                        (*liait1)=(*liait2);
                        (*liait2)=iaTmp;
                      }
                  }
              }
            else
              {
                if(m_pid3PchrgMap.find((*liait1))==m_pid3PchrgMap.end()) writeErrInfOnPid3PchrgMap((*liait1)); 
                if(m_pid3PchrgMap.find((*liait2))==m_pid3PchrgMap.end()) writeErrInfOnPid3PchrgMap((*liait2));
              }
          }
        else
          {
            if(abs((*liait1))==22)
              {
                iaTmp=(*liait1);
                (*liait1)=(*liait2);
                (*liait2)=iaTmp;
              }
          }
      }
}
