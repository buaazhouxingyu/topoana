#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::sortBySzPidAndPchrg(vector< vector<int> > &vVia,vector< vector<int> > &vVib,vector< vector<int> >&vVic,vector< vector<int> > &vVid)
{
  if(vVia.size()!=vVib.size()||vVib.size()!=vVic.size()||vVic.size()!=vVid.size())
    { 
      cerr<<"Error: The four vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<vVia.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<vVib.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vVic.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vVid.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(vVia.size()==0)
    { 
      cerr<<"Infor: The sizes of the four vectors are zero!"<<endl<<endl;
      return;
    }

  /*cout<<"Before sort:"<<endl;
  for(unsigned int i=0;i<vVia.size();i++)
    for(unsigned int j=0;j<vVia[i].size();j++)
      {
        if(j<(vVia[i].size()-1)) cout<<vVia[i][j]<<" ";
        else cout<<vVia[i][j]<<endl; 
      }*/

  bool exchOrd;
  vector<int> viaTmp,vibTmp,vicTmp,vidTmp;
  int ibTmp;
  for(unsigned int i=0;i<(vVia.size()-1);i++)
    for(unsigned int j=i+1;j<vVia.size();j++)
      {
        exchOrd=cmprBySzPidAndPchrg(vVia[i],vVia[j]);
        if(exchOrd==true)
          {
            viaTmp=vVia[i];
            vVia[i]=vVia[j];
            vVia[j]=viaTmp;

            ibTmp=vVib[i][0];
            for(unsigned int k=0;k<vVib[i].size();k++) vVib[i][k]=vVib[j][0];
            for(unsigned int k=0;k<vVib[j].size();k++) vVib[j][k]=ibTmp;

            vibTmp=vVib[i];
            vVib[i]=vVib[j];
            vVib[j]=vibTmp;

            vicTmp=vVic[i];
            vVic[i]=vVic[j];
            vVic[j]=vicTmp;

            vidTmp=vVid[i];
            vVid[i]=vVid[j];
            vVid[j]=vidTmp;             
          }        
      }
  
  /*cout<<"After sort:"<<endl;
  for(unsigned int i=0;i<vVia.size();i++)
    for(unsigned int j=0;j<vVia[i].size();j++)
      { 
        if(j<(vVia[i].size()-1)) cout<<vVia[i][j]<<" ";
        else cout<<vVia[i][j]<<endl;
      }*/
}
