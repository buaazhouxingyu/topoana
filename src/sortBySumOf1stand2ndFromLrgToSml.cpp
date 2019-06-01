#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector< vector< list<int> > > &vVLib1,vector< vector< list<int> > > &vVLib2,vector<int> &vic1,vector<int> &vic2)
{
  if(via1.size()!=via2.size()||via2.size()!=vVLib1.size()||vVLib1.size()!=vVLib2.size()||vVLib2.size()!=vic1.size()||vic1.size()!=vic2.size())
    {
      cerr<<"Error: The six vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via1.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<via2.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vVLib1.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vVLib2.size()<<"."<<endl;
      cerr<<"Infor: The size of the fifth vector is "<<vic1.size()<<"."<<endl;
      cerr<<"Infor: The size of the sixth vector is "<<vic2.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via1.size()==0)
    {
      cerr<<"Infor: The sizes of the six vectors are zero!"<<endl<<endl;
      return;
    }
  int iaTmp1,iaTmp2;vector< list<int> > vLibTmp1,vLibTmp2;int icTmp1,icTmp2;
  for(unsigned int i=0;i<(via1.size()-1);i++)
    for(unsigned int j=i+1;j<via1.size();j++)
      if(via1[i]+via2[i]<via1[j]+via2[j])
        {
          iaTmp1=via1[i];
          via1[i]=via1[j];
          via1[j]=iaTmp1;
          iaTmp2=via2[i];
          via2[i]=via2[j];
          via2[j]=iaTmp2;
          vLibTmp1=vVLib1[i];
          vVLib1[i]=vVLib1[j];
          vVLib1[j]=vLibTmp1;
          vLibTmp2=vVLib2[i];
          vVLib2[i]=vVLib2[j];
          vVLib2[j]=vLibTmp2;
          icTmp1=vic1[i];
          vic1[i]=vic1[j];
          vic1[j]=icTmp1;
          icTmp2=vic2[i];
          vic2[i]=vic2[j];
          vic2[j]=icTmp2;
        }
}

void topoana::sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector< vector< list<int> > > &vVLib1,vector< vector< list<int> > > &vVLib2,vector<int> &vic1,vector<int> &vic2,vector< vector<int> > &vVid1,vector< vector<int> > &vVid2,vector< vector<int> > &vVie1,vector< vector<int> > &vVie2)
{
  if(via1.size()!=via2.size()||via2.size()!=vVLib1.size()||vVLib1.size()!=vVLib2.size()||vVLib2.size()!=vic1.size()||vic1.size()!=vic2.size()||vic2.size()!=vVid1.size()||vVid1.size()!=vVid2.size()||vVid2.size()!=vVie1.size()||vVie1.size()!=vVie2.size())
    {
      cerr<<"Error: The ten vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via1.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<via2.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vVLib1.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vVLib2.size()<<"."<<endl;
      cerr<<"Infor: The size of the fifth vector is "<<vic1.size()<<"."<<endl;
      cerr<<"Infor: The size of the sixth vector is "<<vic2.size()<<"."<<endl;
      cerr<<"Infor: The size of the seventh vector is "<<vVid1.size()<<"."<<endl;
      cerr<<"Infor: The size of the eighth vector is "<<vVid2.size()<<"."<<endl;
      cerr<<"Infor: The size of the ninth vector is "<<vVie1.size()<<"."<<endl;
      cerr<<"Infor: The size of the tenth vector is "<<vVie2.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via1.size()==0)
    {
      cerr<<"Infor: The sizes of the ten vectors are zero!"<<endl<<endl;
      return;
    }
  int iaTmp1,iaTmp2;vector< list<int> > vLibTmp1,vLibTmp2;int icTmp1,icTmp2;vector<int> vidTmp1,vidTmp2,vieTmp1,vieTmp2;
  for(unsigned int i=0;i<(via1.size()-1);i++)
    for(unsigned int j=i+1;j<via1.size();j++)
      if(via1[i]+via2[i]<via1[j]+via2[j])
        {
          iaTmp1=via1[i];
          via1[i]=via1[j];
          via1[j]=iaTmp1;
          iaTmp2=via2[i];
          via2[i]=via2[j];
          via2[j]=iaTmp2;
          vLibTmp1=vVLib1[i];
          vVLib1[i]=vVLib1[j];
          vVLib1[j]=vLibTmp1;
          vLibTmp2=vVLib2[i];
          vVLib2[i]=vVLib2[j];
          vVLib2[j]=vLibTmp2;
          icTmp1=vic1[i];
          vic1[i]=vic1[j];
          vic1[j]=icTmp1;
          icTmp2=vic2[i];
          vic2[i]=vic2[j];
          vic2[j]=icTmp2;
          vidTmp1=vVid1[i];
          vVid1[i]=vVid1[j];
          vVid1[j]=vidTmp1;
          vidTmp2=vVid2[i];
          vVid2[i]=vVid2[j];
          vVid2[j]=vidTmp2;
          vieTmp1=vVie1[i];
          vVie1[i]=vVie1[j];
          vVie1[j]=vieTmp1;
          vieTmp2=vVie2[i];
          vVie2[i]=vVie2[j];
          vVie2[j]=vieTmp2;
        }
}

void topoana::sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector< list<int> > &vLib1,vector< list<int> > &vLib2,vector<int> &vic1,vector<int> &vic2)
{
  if(via1.size()!=via2.size()||via2.size()!=vLib1.size()||vLib1.size()!=vLib2.size()||vLib2.size()!=vic1.size()||vic1.size()!=vic2.size())
    {
      cerr<<"Error: The six vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via1.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<via2.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vLib1.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vLib2.size()<<"."<<endl;
      cerr<<"Infor: The size of the fifth vector is "<<vic1.size()<<"."<<endl;
      cerr<<"Infor: The size of the sixth vector is "<<vic2.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via1.size()==0)
    {
      cerr<<"Infor: The sizes of the six vectors are zero!"<<endl<<endl;
      return;
    }
  int iaTmp1,iaTmp2;list<int> libTmp1,libTmp2;int icTmp1,icTmp2;
  for(unsigned int i=0;i<(via1.size()-1);i++)
    for(unsigned int j=i+1;j<via1.size();j++)
      if(via1[i]+via2[i]<via1[j]+via2[j])
        {
          iaTmp1=via1[i];
          via1[i]=via1[j];
          via1[j]=iaTmp1;
          iaTmp2=via2[i];
          via2[i]=via2[j];
          via2[j]=iaTmp2;
          libTmp1=vLib1[i];
          vLib1[i]=vLib1[j];
          vLib1[j]=libTmp1;
          libTmp2=vLib2[i];
          vLib2[i]=vLib2[j];
          vLib2[j]=libTmp2;
          icTmp1=vic1[i];
          vic1[i]=vic1[j];
          vic1[j]=icTmp1;
          icTmp2=vic2[i];
          vic2[i]=vic2[j];
          vic2[j]=icTmp2;
        }
}

void topoana::sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector<int> &vib1,vector<int> &vib2,vector<int> &vic1,vector<int> &vic2)
{
  if(via1.size()!=via2.size()||via2.size()!=vib1.size()||vib1.size()!=vib2.size()||vib2.size()!=vic1.size()||vic1.size()!=vic2.size())
    {
      cerr<<"Error: The six vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via1.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<via2.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vib1.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vib2.size()<<"."<<endl;
      cerr<<"Infor: The size of the fifth vector is "<<vic1.size()<<"."<<endl;
      cerr<<"Infor: The size of the sixth vector is "<<vic2.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
  if(via1.size()==0)
    {
      cerr<<"Infor: The sizes of the six vectors are zero!"<<endl<<endl;
      return;
    }
  int iaTmp1,iaTmp2,ibTmp1,ibTmp2,icTmp1,icTmp2;
  for(unsigned int i=0;i<(via1.size()-1);i++)
    for(unsigned int j=i+1;j<via1.size();j++)
      if(via1[i]+via2[i]<via1[j]+via2[j])
        {
          iaTmp1=via1[i];
          via1[i]=via1[j];
          via1[j]=iaTmp1;
          iaTmp2=via2[i];
          via2[i]=via2[j];
          via2[j]=iaTmp2;
          ibTmp1=vib1[i];
          vib1[i]=vib1[j];
          vib1[j]=ibTmp1;
          ibTmp2=vib2[i];
          vib2[i]=vib2[j];
          vib2[j]=ibTmp2;
          icTmp1=vic1[i];
          vic1[i]=vic1[j];
          vic1[j]=icTmp1;
          icTmp2=vic2[i];
          vic2[i]=vic2[j];
          vic2[j]=icTmp2;
        }
}
