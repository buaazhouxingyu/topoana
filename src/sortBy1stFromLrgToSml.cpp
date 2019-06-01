#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::sortBy1stFromLrgToSml(vector<int> &via,vector< vector< list<int> > > &vVLib,vector<int> &vic)
{
  if(via.size()!=vVLib.size()||vVLib.size()!=vic.size())
    {
      cerr<<"Error: The three vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<vVLib.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vic.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via.size()==0)
    {
      cerr<<"Infor: The sizes of the three vectors are zero!"<<endl<<endl;
      return;
    }
  int iaTmp;vector< list<int> > vLibTmp;int icTmp;
  for(unsigned int i=0;i<(via.size()-1);i++)
    for(unsigned int j=i+1;j<via.size();j++)
      if(via[i]<via[j])
        {
          iaTmp=via[i];
          via[i]=via[j];
          via[j]=iaTmp;
          vLibTmp=vVLib[i];
          vVLib[i]=vVLib[j];
          vVLib[j]=vLibTmp;
          icTmp=vic[i];
          vic[i]=vic[j];
          vic[j]=icTmp;
        }
}

void topoana::sortBy1stFromLrgToSml(vector<int> &via,vector< vector< list<int> > > &vVLib,vector<int> &vic,vector< vector<int> > &vVid,vector< vector<int> > &vVie)
{
  if(via.size()!=vVLib.size()||vVLib.size()!=vic.size()||vic.size()!=vVid.size()||vVid.size()!=vVie.size())
    {
      cerr<<"Error: The three vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<vVLib.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vic.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vVid.size()<<"."<<endl;
      cerr<<"Infor: The size of the fifth vector is "<<vVie.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via.size()==0)
    {
      cerr<<"Infor: The sizes of the five vectors are zero!"<<endl<<endl;
      return;
    }
  int iaTmp;vector< list<int> > vLibTmp;int icTmp;vector<int> vidTmp,vieTmp;
  for(unsigned int i=0;i<(via.size()-1);i++)
    for(unsigned int j=i+1;j<via.size();j++)
      if(via[i]<via[j])
        {
          iaTmp=via[i];
          via[i]=via[j];
          via[j]=iaTmp;
          vLibTmp=vVLib[i];
          vVLib[i]=vVLib[j];
          vVLib[j]=vLibTmp;
          icTmp=vic[i];
          vic[i]=vic[j];
          vic[j]=icTmp;
          vidTmp=vVid[i];
          vVid[i]=vVid[j];
          vVid[j]=vidTmp;
          vieTmp=vVie[i];
          vVie[i]=vVie[j];
          vVie[j]=vieTmp;
        }
}

void topoana::sortBy1stFromLrgToSml(vector<int> &via,vector< list<int> > &vLib,vector<int> &vic)
{
  if(via.size()!=vLib.size()||vLib.size()!=vic.size())
    {
      cerr<<"Error: The three vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<vLib.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vic.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via.size()==0)
    {
      cerr<<"Infor: The sizes of the three vectors are zero!"<<endl<<endl;
      return;
    }
  int iaTmp;list<int> libTmp;int icTmp;
  for(unsigned int i=0;i<(via.size()-1);i++)
    for(unsigned int j=i+1;j<via.size();j++)
      if(via[i]<via[j])
        {
          iaTmp=via[i];
          via[i]=via[j];
          via[j]=iaTmp;
          libTmp=vLib[i];
          vLib[i]=vLib[j];
          vLib[j]=libTmp;
          icTmp=vic[i];
          vic[i]=vic[j];
          vic[j]=icTmp;
        }
}

void topoana::sortBy1stFromLrgToSml(vector<int> &via,vector<int> &vib,vector<int> &vic)
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
  int iaTmp,ibTmp,icTmp;
  for(unsigned int i=0;i<(via.size()-1);i++)
    for(unsigned int j=i+1;j<via.size();j++)
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
