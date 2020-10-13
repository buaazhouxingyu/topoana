#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

void topoana::writeRsltIntoTxtFl()
{
  if(m_anaTasksForSigIds=="T"&&m_vPid_compDcyBrP.size()==0&&m_vPid_compCascDcyBrP.size()==0&&m_vPid_compDcyFStP.size()==0&&m_vPid_compProdBrP.size()==0&&m_vPid_compMP.size()==0&&m_vCompIncDcyBr.size()==0&&m_vCompIRADcyBr.size()==0&&m_compAnaOfDcyTrs==false&&m_compAnaOfDcyIFSts==false) return;

  string NmOfOptTxtFl=m_comNmOfOptFls+".txt";
  ofstream fout(NmOfOptTxtFl.c_str(),ios::out);
  if(!fout)
    {
      cerr<<"Error: Can't create the output txt file \""<<NmOfOptTxtFl<<"\"!"<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  if(m_compAnaOfDcyTrs==true)
    {
      fout<<endl;

      fout<<"Decay trees and their respective initial-final states:"<<endl<<endl;
      vector< list<int> > dcyTr;
      list<int> dcyBr;
      list<int> dcyIFSts;
      vector<int> vIMDcyBr;
      unsigned long nCEtr=0;
      unsigned long nDcyTrsToBePrtd=m_vDcyTr.size()<m_nDcyTrsToBePrtdMax?m_vDcyTr.size():m_nDcyTrsToBePrtdMax; 
      for(unsigned long i=0;i<nDcyTrsToBePrtd;i++)
        { 
          dcyTr.clear();
          dcyTr=m_vDcyTr[i];
          getVIMDcyBr(dcyTr,vIMDcyBr);
          fout<<"rowNo:  "<<i+1<<"\tiDcyTr:  "<<m_vIDcyTr[i];
          if(m_compAnaOfDcyIFSts==true) fout<<"\tiDcyIFSts:  "<<m_iDcyTrIDcyIFStsMap[m_vIDcyTr[i]];
          fout<<"\tnEtr:  "<<m_vNDcyTr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtr:  ";
              if(m_vICcDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcDcyTr[i];
              fout<<"\tnAllEtr:  "<<m_vNDcyTr[i]+m_vNCcDcyTr[i];
              nCEtr=nCEtr+m_vNDcyTr[i]+m_vNCcDcyTr[i];
            }
          else
            {
              nCEtr=nCEtr+m_vNDcyTr[i];
            }
          fout<<"\tnCEtr:  "<<nCEtr<<endl;

          for(unsigned int j=0;j<dcyTr.size();j++)
            {
              dcyBr.clear();
              dcyBr=dcyTr[j];
              fout<<"  "<<j<<"  & ";
              list<int>::iterator liit=dcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              // The condition "j==0&&((*liit)==m_pidOfISt2)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==m_pidOfISt2))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=dcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<"  &  "<<vIMDcyBr[j]<<endl;
            }

          dcyIFSts.clear();
          if(m_compAnaOfDcyIFSts==true)
            {
              for(unsigned int j=0;j<m_vDcyIFSts.size();j++)
                {
                  if(m_vIDcyIFSts[j]==m_iDcyTrIDcyIFStsMap[m_vIDcyTr[i]])
                    {
                      if(m_iDcyTrICcDcyIFStsMap[m_vIDcyTr[i]]!=-1) dcyIFSts=m_vDcyIFSts[j];
                      else dcyIFSts=m_vCcDcyIFSts[j];
                      break;
                    }
                }
            }
          else
            {
              dcyIFSts=m_vDcyIFSts[m_vIDcyTr[i]];
            }
          fout<<"(";
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" --->";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<" )"<<endl; 

          fout<<endl;
        }
      if(nDcyTrsToBePrtd<m_vDcyTr.size())
        {
          fout<<"rowNo:  rest\tiDcyTr:  ---";
          if(m_compAnaOfDcyIFSts==true) fout<<"\tiDcyIFSts:  ---";
          fout<<"\tnEtr:  ";
          unsigned long nCEtrOfRest=0;
          if(m_ccSwitch==true)
            {
              fout<<"---\tnCcEtr:  ---\tnAllEtr:  ";
              for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyTr[i]+m_vNCcDcyTr[i];
            }
          else
            {
              for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyTr[i];
            }
          nCEtr=nCEtr+nCEtrOfRest;
          fout<<nCEtrOfRest<<"\tnCEtr:  "<<nCEtr<<endl;    

          fout<<" ";
          if(m_iStPsSwitch==true)
            {
              writePnmFromPid(fout,"TxtPnm",m_pidOfISt2);
              writePnmFromPid(fout,"TxtPnm",m_pidOfISt1);
              fout<<" --> others ("<<m_vDcyTr.size()-nDcyTrsToBePrtd<<" in total)"<<endl;

              fout<<"(";
              writePnmFromPid(fout,"TxtPnm",m_pidOfISt2);
              writePnmFromPid(fout,"TxtPnm",m_pidOfISt1);
            }
          else
            {
              bool isASameInitPInAllOtherDcyTrs=true;
              list<int>::iterator liit=m_vDcyTr[nDcyTrsToBePrtd][0].begin();
              int pid=(*liit);
              for(unsigned long i=nDcyTrsToBePrtd+1;i<m_vDcyTr.size();i++)
                { 
                  if(isASameInitPInAllOtherDcyTrs==true)
                    { 
                      liit=m_vDcyTr[i][0].begin();
                      if((*liit)!=pid) isASameInitPInAllOtherDcyTrs=false;
                    }
                }
              if(isASameInitPInAllOtherDcyTrs==true&&(pid!=m_pidOfISt2))
                {
                  writePnmFromPid(fout,"TxtPnm",pid);
                  fout<<" --> others ("<<m_vDcyTr.size()-nDcyTrsToBePrtd<<" in total)"<<endl;

                  fout<<"(";
                  writePnmFromPid(fout,"TxtPnm",pid);           
                }
              else
                {
                  writePnmFromPid(fout,"TxtPnm",m_pidOfISt2);
                  writePnmFromPid(fout,"TxtPnm",m_pidOfISt1);
                  fout<<" --> others ("<<m_vDcyTr.size()-nDcyTrsToBePrtd<<" in total)"<<endl;

                  fout<<"(";
                  writePnmFromPid(fout,"TxtPnm",m_pidOfISt2);
                  writePnmFromPid(fout,"TxtPnm",m_pidOfISt1);
                }
            }
          fout<<" ---> corresponding to others )"<<endl;

          fout<<endl;    
        }
    }

  if(m_compAnaOfDcyIFSts==true)
    {
      fout<<endl;

      fout<<"Decay initial-final states:"<<endl<<endl;
      //list<int> dcyIFSts; The list<int> variable dcyIFSts has been previously declared.
      list<int> dcyIFSts;
      unsigned long nCEtr=0;
      unsigned long nDcyIFStsToBePrtd=m_vDcyIFSts.size()<m_nDcyIFStsToBePrtdMax?m_vDcyIFSts.size():m_nDcyIFStsToBePrtdMax;
      for(unsigned long i=0;i<nDcyIFStsToBePrtd;i++)
        {
          dcyIFSts.clear();
          dcyIFSts=m_vDcyIFSts[i];
          fout<<"rowNo:  "<<i+1<<"\tiDcyIFSts:  "<<m_vIDcyIFSts[i]<<"\tnEtr:  "<<m_vNDcyIFSts[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtr:  ";
              if(m_vICcDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcDcyIFSts[i];
              fout<<"\tnAllEtr:  "<<m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i]; 
              nCEtr=nCEtr+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
            }
          else
            {
              nCEtr=nCEtr+m_vNDcyIFSts[i];
            }
          fout<<"\tnCEtr:  "<<nCEtr<<endl;
          fout<<" ";
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" --->";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
      if(nDcyIFStsToBePrtd<m_vDcyIFSts.size())
        {
          fout<<"rowNo:  rest\tiDcyIFSts:  ---\tnEtr:  ";
          unsigned long nCEtrOfRest=0;
          if(m_ccSwitch==true)
            {
              fout<<"---\tnCcEtr:  ---\tnAllEtr:  ";  
              for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
            }
          else
            {
              for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyIFSts[i];
            }
          nCEtr=nCEtr+nCEtrOfRest;
          fout<<nCEtrOfRest<<"\tnCEtr:  "<<nCEtr<<endl;

          fout<<" ";
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" ---> others ("<<m_vDcyIFSts.size()-nDcyIFStsToBePrtd<<" in total)"<<endl;
          
          fout<<endl;
        }
    }

  if(m_vVDcyBrP.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyBrP.size();i++)
        {
          fout<<endl;

          fout<<"Decay branches of";
          writePnmFromPid(fout,"TxtPnm",m_vPid_compDcyBrP[i]);
          fout<<":"<<endl<<endl;

          list<int> dcyBrP;
          unsigned long nCCase=0;
          unsigned long nDcyBrPToBePrtd=m_vVDcyBrP[i].size()<m_vNDcyBrToBePrtdMax[i]?m_vVDcyBrP[i].size():m_vNDcyBrToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrPToBePrtd;j++)
            {
              dcyBrP.clear();
              dcyBrP=m_vVDcyBrP[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiDcyBrP:  "<<m_vVIDcyBrP[i][j]<<"\tnCase:  "<<m_vVNDcyBrP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCase:  ";
                  if(m_vICcCompDcyBrP[i]==0&&m_vVIDcyBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcP[i][j];
                  fout<<"\tnAllCase:  "<<m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j]; 
                  nCCase=nCCase+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyBrP[i][j];
                }
              fout<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" -->";
              for(liit++;liit!=dcyBrP.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
          if(nDcyBrPToBePrtd<m_vVDcyBrP[i].size())
            {
              fout<<"rowNo:  rest\tiDcyBrP:  ---\tnCase:  ";
              unsigned long nCCaseOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompDcyBrP[i]==0)
                    {
                      fout<<"---\tnCcCase:  ---\tnAllCase:  ";
                    }
                  else
                    {
                      unsigned long nCCaseOfRestTemp1=0;
                      unsigned long nCCaseOfRestTemp2=0;
                      for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyBrP[i][j];
                      for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyBrCcP[i][j];
                      fout<<nCCaseOfRestTemp1<<"\tnCcCase:  "<<nCCaseOfRestTemp2<<"\tnAllCase:  ";
                    }
                  for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrP[i][j];
                }
              nCCase=nCCase+nCCaseOfRest;
              fout<<nCCaseOfRest<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" --> others ("<<m_vVDcyBrP[i].size()-nDcyBrPToBePrtd<<" in total)";
              fout<<endl<<endl;
            }
        }
    }

  if(m_vVCascDcyBrP.size()>0)
    {
      for(unsigned int i=0;i<m_vVCascDcyBrP.size();i++)
        {
          fout<<endl;

          fout<<"Cascade decay branches of";
          writePnmFromPid(fout,"TxtPnm",m_vPid_compCascDcyBrP[i]);
          if(m_vHCascDcyBrMax[i]!=ULONG_MAX)
            {
              fout<<" (only the first ";
              if(m_nNmMap.find(m_vHCascDcyBrMax[i])!=m_nNmMap.end()) fout<<m_nNmMap[m_vHCascDcyBrMax[i]];
              else fout<<m_vHCascDcyBrMax[i];
              fout<<" hierarchies are involved)";
            }
          fout<<":"<<endl<<endl;

          vector< list<int> > cascDcyBrP;
          vector<int> vIMDcyBr;
          // vector<int> vCascDcyBrIdxOfHead;
          list<int> dcyBrP;
          unsigned long nCCase=0;
          unsigned long nCascDcyBrPToBePrtd=m_vVCascDcyBrP[i].size()<m_vNCascDcyBrToBePrtdMax[i]?m_vVCascDcyBrP[i].size():m_vNCascDcyBrToBePrtdMax[i];
          for(unsigned int j=0;j<nCascDcyBrPToBePrtd;j++)
            {
              cascDcyBrP.clear();
              cascDcyBrP=m_vVCascDcyBrP[i][j];
              getVIMDcyBr(cascDcyBrP,vIMDcyBr);
              fout<<"rowNo:  "<<j+1<<"\tiCascDcyBrP:  "<<m_vVICascDcyBrP[i][j]<<"\tnCase:  "<<m_vVNCascDcyBrP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCase:  ";
                  if(m_vICcCompCascDcyBrP[i]==0&&m_vVICascDcyBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNCascDcyBrCcP[i][j];
                  fout<<"\tnAllCase:  "<<m_vVNCascDcyBrP[i][j]+m_vVNCascDcyBrCcP[i][j]; 
                  nCCase=nCCase+m_vVNCascDcyBrP[i][j]+m_vVNCascDcyBrCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNCascDcyBrP[i][j];
                }
              fout<<"\tnCCase:  "<<nCCase<<endl;
              for(unsigned int k=0;k<cascDcyBrP.size();k++)
                {
                  dcyBrP.clear();
                  dcyBrP=cascDcyBrP[k];
                  fout<<"  "<<k<<"  & ";
                  list<int>::iterator liit=dcyBrP.begin();
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                  fout<<" -->";
                  for(liit++;liit!=dcyBrP.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
                  fout<<"  &  "<<vIMDcyBr[k]<<endl;
                }
              fout<<endl;
            }
          if(nCascDcyBrPToBePrtd<m_vVCascDcyBrP[i].size())
            {
              fout<<"rowNo:  rest\tiCascDcyBrP:  ---\tnCase:  ";
              unsigned long nCCaseOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompCascDcyBrP[i]==0)
                    {
                      fout<<"---\tnCcCase:  ---\tnAllCase:  ";
                    }
                  else
                    {
                      unsigned long nCCaseOfRestTemp1=0;
                      unsigned long nCCaseOfRestTemp2=0;
                      for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNCascDcyBrP[i][j];
                      for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNCascDcyBrCcP[i][j];
                      fout<<nCCaseOfRestTemp1<<"\tnCcCase:  "<<nCCaseOfRestTemp2<<"\tnAllCase:  ";
                    }
                  for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNCascDcyBrP[i][j]+m_vVNCascDcyBrCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNCascDcyBrP[i][j];
                }
              nCCase=nCCase+nCCaseOfRest;
              fout<<nCCaseOfRest<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              writePnmFromPid(fout,"TxtPnm",m_vPid_compCascDcyBrP[i]);
              fout<<" --> others ("<<m_vVCascDcyBrP[i].size()-nCascDcyBrPToBePrtd<<" in total)";
              fout<<endl<<endl;
            }
        }
    }

  if(m_vVDcyFStP.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyFStP.size();i++)
        {
          fout<<endl;

          fout<<"Decay final states of";
          writePnmFromPid(fout,"TxtPnm",m_vPid_compDcyFStP[i]);
          if(m_vNDcyFStP[i]!=ULONG_MAX)
            {
              fout<<" (only ";
              if(m_nNmMap.find(m_vNDcyFStP[i])!=m_nNmMap.end()) fout<<m_nNmMap[m_vNDcyFStP[i]];
              else fout<<m_vNDcyFStP[i];
              fout<<"-body final states are involved)";
            }
          fout<<":"<<endl<<endl;

          list<int> dcyFStP;
          unsigned long nCCase=0;
          unsigned long nDcyFStPToBePrtd=m_vVDcyFStP[i].size()<m_vNDcyFStToBePrtdMax[i]?m_vVDcyFStP[i].size():m_vNDcyFStToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyFStPToBePrtd;j++)
            {
              dcyFStP.clear();
              dcyFStP=m_vVDcyFStP[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiDcyFStP:  "<<m_vVIDcyFStP[i][j]<<"\tnCase:  "<<m_vVNDcyFStP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCase:  ";
                  if(m_vICcCompDcyFStP[i]==0&&m_vVIDcyFStCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyFStCcP[i][j];
                  fout<<"\tnAllCase:  "<<m_vVNDcyFStP[i][j]+m_vVNDcyFStCcP[i][j]; 
                  nCCase=nCCase+m_vVNDcyFStP[i][j]+m_vVNDcyFStCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyFStP[i][j];
                }
              fout<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyFStP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" --->";
              for(liit++;liit!=dcyFStP.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
          if(nDcyFStPToBePrtd<m_vVDcyFStP[i].size())
            {
              fout<<"rowNo:  rest\tiDcyFStP:  ---\tnCase:  ";
              unsigned long nCCaseOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompDcyFStP[i]==0)
                    {
                      fout<<"---\tnCcCase:  ---\tnAllCase:  ";
                    }
                  else
                    {
                      unsigned long nCCaseOfRestTemp1=0;
                      unsigned long nCCaseOfRestTemp2=0;
                      for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyFStP[i][j];
                      for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyFStCcP[i][j];
                      fout<<nCCaseOfRestTemp1<<"\tnCcCase:  "<<nCCaseOfRestTemp2<<"\tnAllCase:  ";
                    }
                  for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyFStP[i][j]+m_vVNDcyFStCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyFStP[i][j];
                }
              nCCase=nCCase+nCCaseOfRest;
              fout<<nCCaseOfRest<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyFStP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" ---> others ("<<m_vVDcyFStP[i].size()-nDcyFStPToBePrtd<<" in total)";
              fout<<endl<<endl;
            }
        }
    }

  if(m_vVProdBrP.size()>0)
    {
      for(unsigned int i=0;i<m_vVProdBrP.size();i++)
        {
          fout<<endl;

          fout<<"Production branches of";
          writePnmFromPid(fout,"TxtPnm",m_vPid_compProdBrP[i]);
          fout<<":"<<endl<<endl;

          list<int> prodBrP;
          unsigned long nCCase=0;
          unsigned long nProdBrPToBePrtd=m_vVProdBrP[i].size()<m_vNProdBrToBePrtdMax[i]?m_vVProdBrP[i].size():m_vNProdBrToBePrtdMax[i];
          for(unsigned int j=0;j<nProdBrPToBePrtd;j++)
            {
              prodBrP.clear();
              prodBrP=m_vVProdBrP[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiProdBrP:  "<<m_vVIProdBrP[i][j]<<"\tnCase:  "<<m_vVNProdBrP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCase:  ";
                  if(m_vICcCompProdBrP[i]==0&&m_vVIProdBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNProdBrCcP[i][j];
                  fout<<"\tnAllCase:  "<<m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j]; 
                  nCCase=nCCase+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNProdBrP[i][j];
                }
              fout<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=prodBrP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=prodBrP.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
          if(nProdBrPToBePrtd<m_vVProdBrP[i].size())
            {
              fout<<"rowNo:  rest\tiProdBrP:  ---\tnCase:  ";
              unsigned long nCCaseOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompProdBrP[i]==0)
                    {
                      fout<<"---\tnCcCase:  ---\tnAllCase:  ";
                    }
                  else
                    {
                      unsigned long nCCaseOfRestTemp1=0;
                      unsigned long nCCaseOfRestTemp2=0;
                      for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNProdBrP[i][j];
                      for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNProdBrCcP[i][j];
                      fout<<nCCaseOfRestTemp1<<"\tnCcCase:  "<<nCCaseOfRestTemp2<<"\tnAllCase:  ";
                    }
                  for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNProdBrP[i][j];
                }
              nCCase=nCCase+nCCaseOfRest;
              fout<<nCCaseOfRest<<"\tnCCase:  "<<nCCase<<endl;
              fout<<"  others ("<<m_vVProdBrP[i].size()-nProdBrPToBePrtd<<" in total)"<<endl<<endl;
            }
        }
    }

  if(m_vVMpidP.size()>0)
    {
      for(unsigned int i=0;i<m_vVMpidP.size();i++)
        {
          fout<<endl;

          fout<<"Mothers of";
          writePnmFromPid(fout,"TxtPnm",m_vPid_compMP[i]);
          fout<<":"<<endl;

          unsigned long nCCase=0;
          unsigned long nMPToBePrtd=m_vVMpidP[i].size()<m_vNMToBePrtdMax[i]?m_vVMpidP[i].size():m_vNMToBePrtdMax[i];
          for(unsigned int j=0;j<nMPToBePrtd;j++)
            {
              fout<<"rowNo:  "<<j+1<<"\tMother:  ";
              writePnmFromPid(fout,"TxtPnm",m_vVMpidP[i][j]);
              fout<<"\tPDGMoth:  "<<m_vVMpidP[i][j]<<"\tnCase:  "<<m_vVNMP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCase:  ";
                  if(m_vICcCompMP[i]==0&&m_vVIMCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNMCcP[i][j];
                  fout<<"\tnAllCase:  "<<m_vVNMP[i][j]+m_vVNMCcP[i][j]; 
                  nCCase=nCCase+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNMP[i][j];
                }
              fout<<"\tnCCase:  "<<nCCase<<endl;
            }
          if(nMPToBePrtd<m_vVMpidP[i].size())
            {
              fout<<"rowNo:  rest\tMother:  others ("<<m_vVMpidP[i].size()-nMPToBePrtd<<" in total)\tPDGMoth:  Corresponding to others\tnCase:  ";
              unsigned long nCCaseOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompMP[i]==0)
                    {
                      fout<<"---\tnCcCase:  ---\tnAllCase:  ";
                    }
                  else
                    {
                      unsigned long nCCaseOfRestTemp1=0;
                      unsigned long nCCaseOfRestTemp2=0;
                      for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNMP[i][j];
                      for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNMCcP[i][j];
                      fout<<nCCaseOfRestTemp1<<"\tnCcCase:  "<<nCCaseOfRestTemp2<<"\tnAllCase:  ";
                    }
                  for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNMP[i][j];
                }
              nCCase=nCCase+nCCaseOfRest;
              fout<<nCCaseOfRest<<"\tnCCase:  "<<nCCase<<endl<<endl;
            }
        }
    }

  if(m_vVDcyBrIncDcyBr.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyBrIncDcyBr.size();i++)
        {
          fout<<endl;

          fout<<"Exclusive components of";
          list<int>::iterator liit=m_vCompIncDcyBr[i].begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          if(m_vOption_compIncDcyBr[i].find("-IRA")==string::npos) fout<<" -->";
          else fout<<" --->";
          for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<" +";
          if(m_vOption_compIncDcyBr[i]=="") fout<<" anything";
          else
            {
              fout<<" n";
              if(m_vOption_compIncDcyBr[i]=="Is"||m_vOption_compIncDcyBr[i]=="Is-IRA") writePnmFromPid(fout,"TxtPnm",m_pidOfSISRGam);
              else if(m_vOption_compIncDcyBr[i]=="Ig"||m_vOption_compIncDcyBr[i]=="Ig-IRA") writePnmFromPid(fout,"TxtPnm",m_pidOfGISRGam);
              else if(m_vOption_compIncDcyBr[i]=="Fs"||m_vOption_compIncDcyBr[i]=="Fs-IRA") writePnmFromPid(fout,"TxtPnm",m_pidOfSFSRGam);
              else if(m_vOption_compIncDcyBr[i]=="Fg"||m_vOption_compIncDcyBr[i]=="Fg-IRA") writePnmFromPid(fout,"TxtPnm",m_pidOfGFSRGam);
            }
          fout<<":"<<endl<<endl;

          list<int> dcyBrIncDcyBr;
          unsigned long nCCase=0;
          unsigned long nDcyBrIncDcyBrToBePrtd=m_vVDcyBrIncDcyBr[i].size()<m_vNExcCompsToBePrtdMax[i]?m_vVDcyBrIncDcyBr[i].size():m_vNExcCompsToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrIncDcyBrToBePrtd;j++)
            {
              dcyBrIncDcyBr.clear();
              dcyBrIncDcyBr=m_vVDcyBrIncDcyBr[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiDcyBrIncDcyBr:  "<<m_vVIDcyBrIncDcyBr[i][j]<<"\tnCase:  "<<m_vVNDcyBrIncDcyBr[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCase:  ";
                  // Note that "(m_vICcCompIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])" is used here for a very special case where the inclusive decay branch is not self-charge-conjugate but the exclusive decay branch is self-charge-conjugate.
                  if((m_vICcCompIncDcyBr[i]==0&&m_vVIDcyBrCcIncDcyBr[i][j]==0)||(m_vICcCompIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])) fout<<"---";
                  else fout<<m_vVNDcyBrCcIncDcyBr[i][j];
                  fout<<"\tnAllCase:  "<<m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j]; 
                  nCCase=nCCase+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyBrIncDcyBr[i][j];
                }
              fout<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrIncDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              if(m_vOption_compIncDcyBr[i].find("-IRA")==string::npos) fout<<" -->";
              else fout<<" --->";
              for(liit++;liit!=dcyBrIncDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
          if(nDcyBrIncDcyBrToBePrtd<m_vVDcyBrIncDcyBr[i].size())
            {
              fout<<"rowNo:  rest\tiDcyBrIncDcyBr:  ---\tnCase:  ";
              unsigned long nCCaseOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompIncDcyBr[i]==0)
                    {
                      fout<<"---\tnCcCase:  ---\tnAllCase:  ";
                    }
                  else
                    {
                      unsigned long nCCaseOfRestTemp1=0;
                      unsigned long nCCaseOfRestTemp2=0;
                      for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyBrIncDcyBr[i][j];
                      for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyBrCcIncDcyBr[i][j];
                      fout<<nCCaseOfRestTemp1<<"\tnCcCase:  "<<nCCaseOfRestTemp2<<"\tnAllCase:  ";
                    }
                  for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                }
              else
                {
                  for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIncDcyBr[i][j];
                }
              nCCase=nCCase+nCCaseOfRest;
              fout<<nCCaseOfRest<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=m_vCompIncDcyBr[i].begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              if(m_vOption_compIncDcyBr[i].find("-IRA")==string::npos) fout<<" -->";
              else fout<<" --->";
              for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" + others ("<<m_vVDcyBrIncDcyBr[i].size()-nDcyBrIncDcyBrToBePrtd<<" in total)";
              fout<<endl<<endl;
            }
        }
    }

  if(m_vVDcyBrIRADcyBr.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyBrIRADcyBr.size();i++)
        {
          fout<<endl;

          fout<<"Exclusive components of";
          list<int>::iterator liit=m_vCompIRADcyBr[i].begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" ---> ";
          for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;

          vector< list<int> > dcyBrIRADcyBr;
          vector<int> vIMDcyBr;
          list<int> subdcyBrIRADcyBr;
          unsigned long nCCase=0;
          unsigned long nDcyBrIRADcyBrToBePrtd=m_vVDcyBrIRADcyBr[i].size()<m_vNIntStrusToBePrtdMax[i]?m_vVDcyBrIRADcyBr[i].size():m_vNIntStrusToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrIRADcyBrToBePrtd;j++)
            {
              dcyBrIRADcyBr.clear();
              dcyBrIRADcyBr=m_vVDcyBrIRADcyBr[i][j];
              getVIMDcyBr(dcyBrIRADcyBr,vIMDcyBr);
              fout<<"rowNo:  "<<j+1<<"\tiDcyBrIRADcyBr:  "<<m_vVIDcyBrIRADcyBr[i][j]<<"\tnCase:  "<<m_vVNDcyBrIRADcyBr[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCase:  ";
                  if(m_vICcCompIRADcyBr[i]==0&&m_vVIDcyBrCcIRADcyBr[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcIRADcyBr[i][j];
                  fout<<"\tnAllCase:  "<<m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j]; 
                  nCCase=nCCase+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyBrIRADcyBr[i][j];
                }
              fout<<"\tnCCase:  "<<nCCase<<endl;
              for(unsigned int k=0;k<dcyBrIRADcyBr.size();k++)
                {
                  fout<<"  "<<k<<"  & ";
                  subdcyBrIRADcyBr.clear();
                  subdcyBrIRADcyBr=dcyBrIRADcyBr[k];
                  list<int>::iterator liit=subdcyBrIRADcyBr.begin();
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                  if((k==0)&&((*liit)==m_pidOfISt2))
                    {
                      liit++;
                      writePnmFromPid(fout,"TxtPnm",(*liit));
                    }
                  fout<<" -->";
                  for(liit++;liit!=subdcyBrIRADcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
                  fout<<"  &  "<<vIMDcyBr[k]<<endl;
                }
              fout<<endl;
            }
          if(nDcyBrIRADcyBrToBePrtd<m_vVDcyBrIRADcyBr[i].size())
            {
              fout<<"rowNo:  rest\tiDcyBrIRADcyBr:  ---\tnCase:  ";
              unsigned long nCCaseOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompIRADcyBr[i]==0)
                    {
                      fout<<"---\tnCcCase:  ---\tnAllCase:  ";
                    }
                  else
                    {
                      unsigned long nCCaseOfRestTemp1=0;
                      unsigned long nCCaseOfRestTemp2=0;
                      for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyBrIRADcyBr[i][j];
                      for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyBrCcIRADcyBr[i][j];
                      fout<<nCCaseOfRestTemp1<<"\tnCcCase:  "<<nCCaseOfRestTemp2<<"\tnAllCase:  ";
                    }
                  for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                }
              else
                {
                  for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIRADcyBr[i][j];
                }
              nCCase=nCCase+nCCaseOfRest;
              fout<<nCCaseOfRest<<"\tnCCase:  "<<nCCase<<endl;
              fout<<" ";
              list<int>::iterator liit=m_vCompIRADcyBr[i].begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" --> others ("<<m_vVDcyBrIRADcyBr[i].size()-nDcyBrIRADcyBrToBePrtd<<" in total) --> ";
              for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
        }
    }

  if(m_vSigDcyTr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal decay trees and their respective initial-final states:"<<endl<<endl;
      vector< list<int> > sigDcyTr;
      list<int> sigDcyBr;
      list<int> sigDcyIFSts_tr;
      vector<int> vIMSigDcyBr;
      unsigned long nCEtr=0;
      for(unsigned int i=0;i<m_vSigDcyTr.size();i++)
        { 
          sigDcyTr.clear();
          sigDcyTr=m_vSigDcyTr[i];
          getVIMDcyBr(sigDcyTr,vIMSigDcyBr);
          fout<<"rowNo:  "<<i+1<<"\tiSigDcyTr:  "<<m_vISigDcyTr[i];
          if(m_sigDcyIFSts_tr==true)
            {
              fout<<"\tiSigDcyIFSts_tr:  ";
              if(m_iSigDcyTrICcSigDcyIFSts_trMap[m_vISigDcyTr[i]]>=0) fout<<m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]];
              else fout<<m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]<<"_cc";
            }
          if(m_compAnaOfDcyTrs==true)
            {
              fout<<"\tiDcyTr:  ";
              if(m_iSigDcyTrIDcyTrMap.find(m_vISigDcyTr[i])!=m_iSigDcyTrIDcyTrMap.end())
                {
                  if(m_iSigDcyTrICcDcyTrMap[m_vISigDcyTr[i]]>=0) fout<<m_iSigDcyTrIDcyTrMap[m_vISigDcyTr[i]];
                  else fout<<m_iSigDcyTrIDcyTrMap[m_vISigDcyTr[i]]<<"_cc";
                }
              else fout<<"---";
            }
          if(m_compAnaOfDcyIFSts==true)
            {
              fout<<"\tiDcyIFSts:  ";
              if(m_iSigDcyIFSts_trIDcyIFStsMap.find(m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]])!=m_iSigDcyIFSts_trIDcyIFStsMap.end()) 
                {
                  if(m_iSigDcyIFSts_trICcDcyIFStsMap[m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]]>=0) fout<<m_iSigDcyIFSts_trIDcyIFStsMap[m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]];
                  else fout<<m_iSigDcyIFSts_trIDcyIFStsMap[m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]]<<"_cc";
                }
              else fout<<"---";
            }
          fout<<"\tnEtr:  "<<m_vNSigDcyTr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtr:  ";
              if(m_vICcSigDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyTr[i];
              fout<<"\tnAllEtr:  "<<m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i];
              nCEtr=nCEtr+m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i];
            }
          else
            {
              nCEtr=nCEtr+m_vNSigDcyTr[i];
            }
          fout<<"\tnCEtr:  "<<nCEtr<<endl;
          for(unsigned int j=0;j<sigDcyTr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigDcyTr[j];
              fout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              // The condition "j==0&&((*liit)==m_pidOfISt2)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==m_pidOfISt2))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }

          for(unsigned int j=0;j<m_vSigDcyIFSts_tr.size();j++)
            {
              if(m_vISigDcyIFSts_tr[j]==m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]])
                {
                  sigDcyIFSts_tr.clear();
                  sigDcyIFSts_tr=m_vSigDcyIFSts_tr[j];
                  break;
                }
            }
          fout<<"(";
          list<int>::iterator liit=sigDcyIFSts_tr.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }          
          fout<<" --->";
          for(liit++;liit!=sigDcyIFSts_tr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<" )"<<endl;

          fout<<endl;
        }

      fout<<endl;

      if(m_sigDcyIFSts_tr==true)
        {
          fout<<"Signal decay initial-final states corresponding to signal decay trees:"<<endl<<endl;
          //list<int> sigDcyIFSts_tr; The list<int> variable sigDcyIFSts_tr has been previously declared.
          nCEtr=0;
          for(unsigned int i=0;i<m_vSigDcyIFSts_tr.size();i++)
            {
              sigDcyIFSts_tr.clear();
              sigDcyIFSts_tr=m_vSigDcyIFSts_tr[i];
              fout<<"rowNo:  "<<i+1<<"\tiSigDcyIFSts_tr:  "<<m_vISigDcyIFSts_tr[i];
              if(m_compAnaOfDcyIFSts==true)
                {
                  fout<<"\tiDcyIFSts:  ";
                  if(m_iSigDcyIFSts_trIDcyIFStsMap.find(m_vISigDcyIFSts_tr[i])!=m_iSigDcyIFSts_trIDcyIFStsMap.end())
                    {
                      if(m_iSigDcyIFSts_trICcDcyIFStsMap[m_vISigDcyIFSts_tr[i]]>=0) fout<<m_iSigDcyIFSts_trIDcyIFStsMap[m_vISigDcyIFSts_tr[i]];
                      else fout<<m_iSigDcyIFSts_trIDcyIFStsMap[m_vISigDcyIFSts_tr[i]]<<"_cc";
                    }
                  else fout<<"---";
                }
              fout<<"\tnEtr:  "<<m_vNSigDcyIFSts_tr[i];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcEtr:  ";
                  if(m_vICcSigDcyIFSts_tr[i]==0) fout<<"---";
                  else fout<<m_vNCcSigDcyIFSts_tr[i];
                  fout<<"\tnAllEtr:  "<<m_vNSigDcyIFSts_tr[i]+m_vNCcSigDcyIFSts_tr[i]; 
                  nCEtr=nCEtr+m_vNSigDcyIFSts_tr[i]+m_vNCcSigDcyIFSts_tr[i];
                }
              else
                {
                  nCEtr=nCEtr+m_vNSigDcyIFSts_tr[i];
                }
              fout<<"\tnCEtr:  "<<nCEtr<<endl;
              fout<<" ";
              list<int>::iterator liit=sigDcyIFSts_tr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" --->";
              for(liit++;liit!=sigDcyIFSts_tr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
        }
    }

  if(m_vSigDcyIFSts.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal decay initial-final states:"<<endl<<endl;

      list<int> sigDcyIFSts;
      unsigned long nCEtr=0;
      for(unsigned int i=0;i<m_vSigDcyIFSts.size();i++)
        {
          sigDcyIFSts.clear();
          sigDcyIFSts=m_vSigDcyIFSts[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigDcyIFSts:  "<<m_vISigDcyIFSts[i];
          if(m_compAnaOfDcyIFSts==true)
            {
              fout<<"\tiDcyIFSts:  ";
              if(m_iSigDcyIFStsIDcyIFStsMap.find(m_vISigDcyIFSts[i])!=m_iSigDcyIFStsIDcyIFStsMap.end())      
                {
                  if(m_iSigDcyIFStsICcDcyIFStsMap[m_vISigDcyIFSts[i]]>=0) fout<<m_iSigDcyIFStsIDcyIFStsMap[m_vISigDcyIFSts[i]];
                  else fout<<m_iSigDcyIFStsIDcyIFStsMap[m_vISigDcyIFSts[i]]<<"_cc";
                }
              else fout<<"---";
            }
          fout<<"\tnEtr:  "<<m_vNSigDcyIFSts[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtr:  ";
              if(m_vICcSigDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyIFSts[i];
              fout<<"\tnAllEtr:  "<<m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i];
              nCEtr=nCEtr+m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i];
            }
          else
            {
              nCEtr=nCEtr+m_vNSigDcyIFSts[i];
            }
          fout<<"\tnCEtr:  "<<nCEtr<<endl;
          fout<<" ";
          list<int>::iterator liit=sigDcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" --->";
          for(liit++;liit!=sigDcyIFSts.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
    }

  if(m_vPid_sigP.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal particles:"<<endl<<endl;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vNSigP.size();i++)
        {
          fout<<"rowNo:  "<<i+1<<"\tSigP: ";
          writePnmFromPid(fout,"TxtPnm",m_vPid_sigP[i]);
          fout<<"\tiSigP:  "<<m_vISigP[i]<<"\tnCase:   "<<m_vNSigP[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcCase:   ";
              if(m_vICcSigP[i]>0) fout<<m_vNCcSigP[i];
              else fout<<"---";
              fout<<"\tnAllCase:   "<<m_vNSigP[i]+m_vNCcSigP[i];
              nCCase=nCCase+m_vNSigP[i]+m_vNCcSigP[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigP[i];
            }
          fout<<"\tnCCase:  "<<nCCase<<endl<<endl;
        }
    }

  if(m_vSigDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal decay branches:"<<endl<<endl;

      list<int> sigDcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigDcyBr.size();i++)
        {
          sigDcyBr.clear();
          sigDcyBr=m_vSigDcyBr[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigDcyBr:  "<<m_vISigDcyBr[i]<<"\tnCase:  "<<m_vNSigDcyBr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcCase:  ";
              if(m_vICcSigDcyBr[i]>0) fout<<m_vNCcSigDcyBr[i];
              else fout<<"---";
              fout<<"\tnAllCase:  "<<m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i];
              nCCase=nCCase+m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigDcyBr[i];
            }
          fout<<"\tnCCase:  "<<nCCase<<endl;
          fout<<" ";
          list<int>::iterator liit=sigDcyBr.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" -->";
          for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
    }

  if(m_vSigIncDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal inclusive decay branches:"<<endl<<endl;

      list<int> sigIncDcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigIncDcyBr.size();i++)
        {
          sigIncDcyBr.clear();
          sigIncDcyBr=m_vSigIncDcyBr[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIncDcyBr:  "<<m_vISigIncDcyBr[i]<<"\tnCase:  "<<m_vNSigIncDcyBr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcCase:  ";
              if(m_vICcSigIncDcyBr[i]>0) fout<<m_vNCcSigIncDcyBr[i];
              else fout<<"---";
              fout<<"\tnAllCase:  "<<m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i];
              nCCase=nCCase+m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigIncDcyBr[i];
            }
          fout<<"\tnCCase:  "<<nCCase<<endl;
          fout<<" ";
          list<int>::iterator liit=sigIncDcyBr.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" -->";
          for(liit++;liit!=sigIncDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<" + anything";
          fout<<endl<<endl;
        }
    }

  if(m_vSigCascDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal cascade decay branches:"<<endl<<endl;
      vector< list<int> > sigCascDcyBr;
      vector<int> vSigCascDcyBrIdxOfHead;
      vector<int> vIMSigDcyBr;
      list<int> sigDcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigCascDcyBr.size();i++)
        { 
          sigCascDcyBr.clear();
          sigCascDcyBr=m_vSigCascDcyBr[i];
          getVIMDcyBr(sigCascDcyBr,vIMSigDcyBr);
          vSigCascDcyBrIdxOfHead=m_vVSigCascDcyBrIdxOfHead[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigCascDcyBr:  "<<m_vISigCascDcyBr[i]<<"\tnCase:  "<<m_vNSigCascDcyBr[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCase:  ";
              if(m_vICcSigCascDcyBr[i]>0) fout<<m_vNCcSigCascDcyBr[i];
              else fout<<"---";
              fout<<"\tnAllCase:  "<<m_vNSigCascDcyBr[i]+m_vNCcSigCascDcyBr[i];
              nCCase=nCCase+m_vNSigCascDcyBr[i]+m_vNCcSigCascDcyBr[i];
            }
          else
            { 
              nCCase=nCCase+m_vNSigCascDcyBr[i];
            }
          fout<<"\tnCCase:  "<<nCCase<<endl;
          for(unsigned int j=0;j<sigCascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigCascDcyBr[j];
              fout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              // if(j==0&&vSigCascDcyBrIdxOfHead[0]==-1)
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }
          fout<<endl;
        }
    }

  if(m_vSigIncCascDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal inclusive cascade decay branches:"<<endl<<endl;
      vector< list<int> > sigIncCascDcyBr;
      vector<int> vSigIncCascDcyBrIdxOfHead;
      vector<int> vIMSigDcyBr;
      list<int> sigDcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigIncCascDcyBr.size();i++)
        { 
          sigIncCascDcyBr.clear();
          sigIncCascDcyBr=m_vSigIncCascDcyBr[i];
          getVIMDcyBr(sigIncCascDcyBr,vIMSigDcyBr);
          vSigIncCascDcyBrIdxOfHead=m_vVSigIncCascDcyBrIdxOfHead[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIncCascDcyBr:  "<<m_vISigIncCascDcyBr[i]<<"\tnCase:  "<<m_vNSigIncCascDcyBr[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCase:  ";
              if(m_vICcSigIncCascDcyBr[i]>0) fout<<m_vNCcSigIncCascDcyBr[i];
              else fout<<"---";
              fout<<"\tnAllCase:  "<<m_vNSigIncCascDcyBr[i]+m_vNCcSigIncCascDcyBr[i];
              nCCase=nCCase+m_vNSigIncCascDcyBr[i]+m_vNCcSigIncCascDcyBr[i];
            }
          else
            { 
              nCCase=nCCase+m_vNSigIncCascDcyBr[i];
            }
          fout<<"\tnCCase:  "<<nCCase<<endl;
          for(unsigned int j=0;j<sigIncCascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncCascDcyBr[j];
              fout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              // if(j==0&&vSigIncCascDcyBrIdxOfHead[0]==-1)
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncCascDcyBr[i][j]==1) writePnmFromPid(fout,"TxtPnm",m_pidOfAnything);
              fout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }
          fout<<endl;
        }
    }

  if(m_vSigIRADcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal intermediate-resonance-allowed decay branches:"<<endl<<endl;

      list<int> sigIRADcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigIRADcyBr.size();i++)
        {
          sigIRADcyBr.clear();
          sigIRADcyBr=m_vSigIRADcyBr[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIRADcyBr:  "<<m_vISigIRADcyBr[i]<<"\tnCase:  "<<m_vNSigIRADcyBr[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCase:  ";
              if(m_vICcSigIRADcyBr[i]>0) fout<<m_vNCcSigIRADcyBr[i];
              else fout<<"---";
              fout<<"\tnAllCase:  "<<m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i];
              nCCase=nCCase+m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i];
            }
          else
            { 
              nCCase=nCCase+m_vNSigIRADcyBr[i];
            }
          fout<<"\tnCCase:  "<<nCCase<<endl;
          fout<<" ";
          list<int>::iterator liit=sigIRADcyBr.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }           
          fout<<" --->";
          for(liit++;liit!=sigIRADcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
    }

  if(m_vSigIncOrIRACascDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal inclusive or intermediate-resonance-allowed cascade decay branches:"<<endl<<endl;
      vector< list<int> > sigIncOrIRACascDcyBr;
      vector<int> vSigIncOrIRACascDcyBrIdxOfHead;
      vector<int> vIMSigDcyBr;
      list<int> sigDcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBr.size();i++)
        { 
          sigIncOrIRACascDcyBr.clear();
          sigIncOrIRACascDcyBr=m_vSigIncOrIRACascDcyBr[i];
          getVIMDcyBr(sigIncOrIRACascDcyBr,vIMSigDcyBr);
          vSigIncOrIRACascDcyBrIdxOfHead=m_vVSigIncOrIRACascDcyBrIdxOfHead[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIncOrIRACascDcyBr:  "<<m_vISigIncOrIRACascDcyBr[i]<<"\tnCase:  "<<m_vNSigIncOrIRACascDcyBr[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCase:  ";
              if(m_vICcSigIncOrIRACascDcyBr[i]>0) fout<<m_vNCcSigIncOrIRACascDcyBr[i];
              else fout<<"---";
              fout<<"\tnAllCase:  "<<m_vNSigIncOrIRACascDcyBr[i]+m_vNCcSigIncOrIRACascDcyBr[i];
              nCCase=nCCase+m_vNSigIncOrIRACascDcyBr[i]+m_vNCcSigIncOrIRACascDcyBr[i];
            }
          else
            { 
              nCCase=nCCase+m_vNSigIncOrIRACascDcyBr[i];
            }
          fout<<"\tnCCase:  "<<nCCase<<endl;
          for(unsigned int j=0;j<sigIncOrIRACascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncOrIRACascDcyBr[j];
              fout<<"  "<<j<<"  & ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              // if(j==0&&vSigIncOrIRACascDcyBrIdxOfHead[0]==-1)
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              if(m_vVIIRASigIncOrIRACascDcyBr[i][j]==1) fout<<" (--> X)";
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncOrIRACascDcyBr[i][j]==1)
                {
                  writePnmFromPid(fout,"TxtPnm",m_pidOfAnything);
                }
              fout<<"  &  "<<vIMSigDcyBr[j]<<endl;
            }
          fout<<endl;
        }
    }
}
