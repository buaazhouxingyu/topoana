#include "../include/topoana.h"
#include <cstdlib>

void topoana::getDcyTr(vector<int> vPid, vector<int> vMidx, vector< list<int> > & dcyTr, vector <int> * vIdxOfHead, vector<int> * vMidxOfHead, vector<int> * vIIncIncOrIRACascDcyBr, vector<int> * vIIRAIncOrIRACascDcyBr)
{
  dcyTr.clear();
  if(vIdxOfHead!=0) (*vIdxOfHead).clear();
  if(vMidxOfHead!=0) (*vMidxOfHead).clear();
  if(vIIncIncOrIRACascDcyBr!=0) (*vIIncIncOrIRACascDcyBr).clear();
  if(vIIRAIncOrIRACascDcyBr!=0) (*vIIRAIncOrIRACascDcyBr).clear();
  list<int> dcyBr;

  dcyBr.clear();
  int iIncIncOrIRACascDcyBr=0;
  int iIRAIncOrIRACascDcyBr=0;
  for(unsigned int i=0;i<vPid.size();i++)
    {
      if(i==0&&vPid[0]==m_pidOfISt)
        {
          for(unsigned int j=i+1;j<vPid.size();j++)
            {   
              if(((unsigned int) vMidx[j])==i)
                { 
                  if(vPid[j]==m_pidOfAnything) iIncIncOrIRACascDcyBr=1;
                  else if(vPid[j]==m_pidOfIRAFlag) iIRAIncOrIRACascDcyBr=1;
                  else dcyBr.push_back(vPid[j]);
                }
              else if(dcyBr.size()>0) break; // The statement is specially added here to save computing because the function sortPs has been run over vPid and vMidx.
            }
          break;
        }
      if(((unsigned int) vMidx[i])==i)
        {
          if(vPid[i]==m_pidOfAnything) iIncIncOrIRACascDcyBr=1;
          else if(vPid[i]==m_pidOfIRAFlag) iIRAIncOrIRACascDcyBr=1;
          else dcyBr.push_back(vPid[i]);
        }
      else break; // The statement is specially added here to save computing because the function sortPs has been run over vPid and vMidx.
    }
  if(dcyBr.size()>1||m_iStPsSwitch==true||vPid[0]==m_pidOfISt)
    {
      dcyBr.push_front(m_pidOfISt1);
      dcyBr.push_front(m_pidOfISt2);
      dcyTr.push_back(dcyBr);
      if(vIdxOfHead!=0) (*vIdxOfHead).push_back(-1);
      if(vMidxOfHead!=0) (*vMidxOfHead).push_back(-1);
      if(vIIncIncOrIRACascDcyBr!=0) (*vIIncIncOrIRACascDcyBr).push_back(iIncIncOrIRACascDcyBr);
      if(vIIRAIncOrIRACascDcyBr!=0) (*vIIRAIncOrIRACascDcyBr).push_back(iIRAIncOrIRACascDcyBr);
    }

  for(unsigned int i=0;i<vPid.size();i++)
    {
      if(i==0&&vPid[i]==m_pidOfISt) continue;
      dcyBr.clear();
      iIncIncOrIRACascDcyBr=0;
      iIRAIncOrIRACascDcyBr=0;
      for(unsigned int j=i+1;j<vPid.size();j++)
        {
          if(((unsigned int) vMidx[j])==i)
            {
              if(vPid[j]==m_pidOfAnything) iIncIncOrIRACascDcyBr=1;
              else if(vPid[j]==m_pidOfIRAFlag) iIRAIncOrIRACascDcyBr=1;
              else dcyBr.push_back(vPid[j]);
            }
          else if(dcyBr.size()>0) break; // The statement is specially added here to save computing because the function sortPs has been run over vPid and vMidx.
        }
      if(dcyBr.size()==0) continue; 
      if(abs(vPid[i])!=1&&abs(vPid[i])!=2&&abs(vPid[i])!=3&&abs(vPid[i])!=4&&abs(vPid[i])!=5&&abs(vPid[i])!=6)
        {
          dcyBr.push_front(vPid[i]);
        }
      else
        {
          dcyBr.push_front(-abs(vPid[i]));
          dcyBr.push_front(abs(vPid[i]));
        }
      dcyTr.push_back(dcyBr);
      if(vIdxOfHead!=0) (*vIdxOfHead).push_back(i);
      if(vMidxOfHead!=0) (*vMidxOfHead).push_back(vMidx[i]);
      if(vIIncIncOrIRACascDcyBr!=0) (*vIIncIncOrIRACascDcyBr).push_back(iIncIncOrIRACascDcyBr);
      if(vIIRAIncOrIRACascDcyBr!=0) (*vIIRAIncOrIRACascDcyBr).push_back(iIRAIncOrIRACascDcyBr);
    }
}
