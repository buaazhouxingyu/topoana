#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

void topoana::writeRsltIntoTxtFl()
{
  if(m_anaTasksForSigIds=="T"&&m_vPid_compDcyBrP.size()==0&&m_vCompIncDcyBr.size()==0&&m_vCompIRADcyBr.size()==0&&m_compAnaOfDcyTrs==false&&m_compAnaOfDcyIFSts==false) return;

  string NmOfOptTxtFl=m_mainNmOfOptFls+".txt";
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
      unsigned long nCEtrs=0;
      unsigned long nDcyTrsToBePrtd=m_vDcyTr.size()<m_nDcyTrsToBePrtdMax?m_vDcyTr.size():m_nDcyTrsToBePrtdMax; 
      for(unsigned long i=0;i<nDcyTrsToBePrtd;i++)
        { 
          dcyTr.clear();
          dcyTr=m_vDcyTr[i];
          fout<<"rowNo:  "<<i+1<<"\tiDcyTr:  "<<m_vIDcyTr[i]<<"\tiDcyIFSts:  "<<m_iDcyTrIDcyIFStsMap[m_vIDcyTr[i]]<<"\tnEtrs:  "<<m_vNDcyTr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtrs:  ";
              if(m_vICcDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcDcyTr[i];
              fout<<"\tnTotEtrs:  "<<m_vNDcyTr[i]+m_vNCcDcyTr[i];
              nCEtrs=nCEtrs+m_vNDcyTr[i]+m_vNCcDcyTr[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNDcyTr[i];
            }
          fout<<"\tnCEtrs:  "<<nCEtrs<<endl;

          for(unsigned int j=0;j<dcyTr.size();j++)
            {
              dcyBr.clear();
              dcyBr=dcyTr[j];
              fout<<" ";
              list<int>::iterator liit=dcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              // The condition "j==0&&((*liit)==-11)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==-11))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=dcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl;
            }

          for(unsigned int j=0;j<m_vDcyIFSts.size();j++)
            {
              if(m_vIDcyIFSts[j]==m_iDcyTrIDcyIFStsMap[m_vIDcyTr[i]])
                {
                  dcyIFSts.clear();
                  if(m_iDcyTrICcDcyIFStsMap[m_vIDcyTr[i]]!=-1) dcyIFSts=m_vDcyIFSts[j];
                  else dcyIFSts=m_vCcDcyIFSts[j];
                  break;
                }
            }
          fout<<"(";
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" -->";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<" )"<<endl; 

          fout<<endl;
        }
      if(nDcyTrsToBePrtd<m_vDcyTr.size())
        {
          fout<<"rowNo:  "<<"rest"<<"\tiDcyTr:  "<<"---"<<"\tiDcyIFSts:  "<<"---"<<"\tnEtrs:  ";
          unsigned long nCEtrsOfRest=0;
          if(m_ccSwitch==true)
            {
              fout<<"---"<<"\tnCcEtrs:  "<<"---"<<"\tnTotEtrs:  ";
              for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyTr[i]+m_vNCcDcyTr[i];
            }
          else
            {
              for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyTr[i];
            }
          nCEtrs=nCEtrs+nCEtrsOfRest;
          fout<<nCEtrsOfRest<<"\tnCEtrs:  "<<nCEtrs<<endl;    

          fout<<" ";
          if(m_initEpEmSwitch==true)
            {
              writePnmFromPid(fout,"TxtPnm",-11);
              writePnmFromPid(fout,"TxtPnm",11);
              fout<<" --> others"<<endl;

              fout<<"(";
              writePnmFromPid(fout,"TxtPnm",-11);
              writePnmFromPid(fout,"TxtPnm",11);
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
              if(isASameInitPInAllOtherDcyTrs==true&&(pid!=-11))
                {
                  writePnmFromPid(fout,"TxtPnm",pid);
                  fout<<" --> others"<<endl;

                  fout<<"(";
                  writePnmFromPid(fout,"TxtPnm",pid);           
                }
              else
                {
                  writePnmFromPid(fout,"TxtPnm",-11);
                  writePnmFromPid(fout,"TxtPnm",11);
                  fout<<" --> others"<<endl;

                  fout<<"(";
                  writePnmFromPid(fout,"TxtPnm",-11);
                  writePnmFromPid(fout,"TxtPnm",11);
                }
            }
          fout<<" --> corresponding to others )"<<endl;

          fout<<endl;    
        }
    }

  if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
    {
      fout<<endl;

      fout<<"Decay initial-final states:"<<endl<<endl;
      //list<int> dcyIFSts; The list<int> variable dcyIFSts has been previously declared.
      list<int> dcyIFSts;
      unsigned long nCEtrs=0;
      unsigned long nDcyIFStsToBePrtd=m_vDcyIFSts.size()<m_nDcyIFStsToBePrtdMax?m_vDcyIFSts.size():m_nDcyIFStsToBePrtdMax;
      for(unsigned long i=0;i<nDcyIFStsToBePrtd;i++)
        {
          dcyIFSts.clear();
          dcyIFSts=m_vDcyIFSts[i];
          fout<<"rowNo:  "<<i+1<<"\tiDcyIFSts:  "<<m_vIDcyIFSts[i]<<"\tnEtrs:  "<<m_vNDcyIFSts[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtrs:  ";
              if(m_vICcDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcDcyIFSts[i];
              fout<<"\tnTotEtrs:  "<<m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i]; 
              nCEtrs=nCEtrs+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNDcyIFSts[i];
            }
          fout<<"\tnCEtrs:  "<<nCEtrs<<endl;
          fout<<" ";
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" -->";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
      if(nDcyIFStsToBePrtd<m_vDcyIFSts.size())
        {
          fout<<"rowNo:  "<<"rest"<<"\tiDcyIFSts:  "<<"---"<<"\tnEtrs:  ";
          unsigned long nCEtrsOfRest=0;
          if(m_ccSwitch==true)
            {
              fout<<"---"<<"\tnCcEtrs:  "<<"---"<<"\tnTotEtrs:  ";  
              for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
            }
          else
            {
              for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyIFSts[i];
            }
          nCEtrs=nCEtrs+nCEtrsOfRest;
          fout<<nCEtrsOfRest<<"\tnCEtrs:  "<<nCEtrs<<endl;

          fout<<" ";
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" --> others"<<endl;
          
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
          unsigned long nCCases=0;
          unsigned long nDcyBrPToBePrtd=m_vVDcyBrP[i].size()<m_vNDcyBrsToBePrtdMax[i]?m_vVDcyBrP[i].size():m_vNDcyBrsToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrPToBePrtd;j++)
            {
              dcyBrP.clear();
              dcyBrP=m_vVDcyBrP[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiDcyBrP"<<i+1<<":  "<<m_vVIDcyBrP[i][j]<<"\tnCases:  "<<m_vVNDcyBrP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCases:  ";
                  if(m_vICcCompDcyBrP[i]==0&&m_vVIDcyBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcP[i][j];
                  fout<<"\tnTotCases:  "<<m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j]; 
                  nCCases=nCCases+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNDcyBrP[i][j];
                }
              fout<<"\tnCCases:  "<<nCCases<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" -->";
              for(liit++;liit!=dcyBrP.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
          if(nDcyBrPToBePrtd<m_vVDcyBrP[i].size())
            {
              fout<<"rowNo:  "<<"rest"<<"\tiDcyBrP"<<i+1<<":  "<<"---"<<"\tnCases:  ";
              unsigned long nCCasesOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompDcyBrP[i]==0)
                    {
                      fout<<"---"<<"\tnCcCases:  "<<"---"<<"\tnTotCases:  ";
                    }
                  else
                    {
                      unsigned long nCCasesOfRestTemp1=0;
                      unsigned long nCCasesOfRestTemp2=0;
                      for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNDcyBrP[i][j];
                      for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNDcyBrCcP[i][j];
                      fout<<nCCasesOfRestTemp1<<"\tnCcCases:  "<<nCCasesOfRestTemp2<<"\tnTotCases:  ";
                    }
                  for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrP[i][j];
                }
              nCCases=nCCases+nCCasesOfRest;
              fout<<nCCasesOfRest<<"\tnCCases:  "<<nCCases<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" --> others";
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
          unsigned long nCCases=0;
          unsigned long nProdBrPToBePrtd=m_vVProdBrP[i].size()<m_vNProdBrsToBePrtdMax[i]?m_vVProdBrP[i].size():m_vNProdBrsToBePrtdMax[i];
          for(unsigned int j=0;j<nProdBrPToBePrtd;j++)
            {
              prodBrP.clear();
              prodBrP=m_vVProdBrP[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiProdBr_P"<<i<<":  "<<m_vVIProdBrP[i][j]<<"\tnCases:  "<<m_vVNProdBrP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCases:  ";
                  if(m_vICcCompProdBrP[i]==0&&m_vVIProdBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNProdBrCcP[i][j];
                  fout<<"\tnTotCases:  "<<m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j]; 
                  nCCases=nCCases+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNProdBrP[i][j];
                }
              fout<<"\tnCCases:  "<<nCCases<<endl;
              fout<<" ";
              list<int>::iterator liit=prodBrP.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<" -->";
              for(liit++;liit!=prodBrP.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
          if(nProdBrPToBePrtd<m_vVProdBrP[i].size())
            {
              fout<<"rowNo:  "<<"rest"<<"\tiProdBr_P"<<i<<":  "<<"---"<<"\tnCases:  ";
              unsigned long nCCasesOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompProdBrP[i]==0)
                    {
                      fout<<"---"<<"\tnCcCases:  "<<"---"<<"\tnTotCases:  ";
                    }
                  else
                    {
                      unsigned long nCCasesOfRestTemp1=0;
                      unsigned long nCCasesOfRestTemp2=0;
                      for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNProdBrP[i][j];
                      for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNProdBrCcP[i][j];
                      fout<<nCCasesOfRestTemp1<<"\tnCcCases:  "<<nCCasesOfRestTemp2<<"\tnTotCases:  ";
                    }
                  for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNProdBrP[i][j];
                }
              nCCases=nCCases+nCCasesOfRest;
              fout<<nCCasesOfRest<<"\tnCCases:  "<<nCCases<<endl;
              fout<<"  others"<<endl<<endl;
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

          unsigned long nCCases=0;
          unsigned long nMPToBePrtd=m_vVMpidP[i].size()<m_vNMsToBePrtdMax[i]?m_vVMpidP[i].size():m_vNMsToBePrtdMax[i];
          for(unsigned int j=0;j<nMPToBePrtd;j++)
            {
              fout<<"rowNo:  "<<j+1<<"\tMother:  ";
              writePnmFromPid(fout,"TxtPnm",m_vVMpidP[i][j]);
              char brNmofMothPDGVar[100];
              if(m_vNm_compMP[i].empty()) sprintf(brNmofMothPDGVar, "MothPDG_P%d", i);
              else sprintf(brNmofMothPDGVar, "MothPDG_%s", m_vNm_compMP[i].c_str());
              fout<<"\t"<<brNmofMothPDGVar<<":  "<<m_vVMpidP[i][j]<<"\tnCases:  "<<m_vVNMP[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCases:  ";
                  if(m_vICcCompMP[i]==0&&m_vVIMCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNMCcP[i][j];
                  fout<<"\tnTotCases:  "<<m_vVNMP[i][j]+m_vVNMCcP[i][j]; 
                  nCCases=nCCases+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNMP[i][j];
                }
              fout<<"\tnCCases:  "<<nCCases<<endl;
            }
          if(nMPToBePrtd<m_vVMpidP[i].size())
            {
              char brNmofMothPDGVar[100];
              if(m_vNm_compMP[i].empty()) sprintf(brNmofMothPDGVar, "MothPDG_P%d", i);
              else sprintf(brNmofMothPDGVar, "MothPDG_%s", m_vNm_compMP[i].c_str());
              fout<<"rowNo:  "<<"rest"<<"\tMother:  "<<"others"<<"\t"<<brNmofMothPDGVar<<":  "<<"Corresponding to others"<<"\tnCases:  ";
              unsigned long nCCasesOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompMP[i]==0)
                    {
                      fout<<"---"<<"\tnCcCases:  "<<"---"<<"\tnTotCases:  ";
                    }
                  else
                    {
                      unsigned long nCCasesOfRestTemp1=0;
                      unsigned long nCCasesOfRestTemp2=0;
                      for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNMP[i][j];
                      for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNMCcP[i][j];
                      fout<<nCCasesOfRestTemp1<<"\tnCcCases:  "<<nCCasesOfRestTemp2<<"\tnTotCases:  ";
                    }
                  for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                }
              else
                {
                  for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNMP[i][j];
                }
              nCCases=nCCases+nCCasesOfRest;
              fout<<nCCasesOfRest<<"\tnCCases:  "<<nCCases<<endl<<endl;
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
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" -->";
          for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<" + anything:"<<endl<<endl;

          list<int> dcyBrIncDcyBr;
          unsigned long nCCases=0;
          unsigned long nDcyBrIncDcyBrToBePrtd=m_vVDcyBrIncDcyBr[i].size()<m_vNExcCompsToBePrtdMax[i]?m_vVDcyBrIncDcyBr[i].size():m_vNExcCompsToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrIncDcyBrToBePrtd;j++)
            {
              dcyBrIncDcyBr.clear();
              dcyBrIncDcyBr=m_vVDcyBrIncDcyBr[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiDcyBrIncDcyBr"<<i+1<<":  "<<m_vVIDcyBrIncDcyBr[i][j]<<"\tnCases:  "<<m_vVNDcyBrIncDcyBr[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCases:  ";
                  // Note that "(m_vCompICcIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])" is used here for a very special case where the inclusive decay branch is not self-charge-conjugate but the exclusive decay branch is self-charge-conjugate.
                  if((m_vCompICcIncDcyBr[i]==0&&m_vVIDcyBrCcIncDcyBr[i][j]==0)||(m_vCompICcIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])) fout<<"---";
                  else fout<<m_vVNDcyBrCcIncDcyBr[i][j];
                  fout<<"\tnTotCases:  "<<m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j]; 
                  nCCases=nCCases+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNDcyBrIncDcyBr[i][j];
                }
              fout<<"\tnCCases:  "<<nCCases<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrIncDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==-11)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=dcyBrIncDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl<<endl;
            }
          if(nDcyBrIncDcyBrToBePrtd<m_vVDcyBrIncDcyBr[i].size())
            {
              fout<<"rowNo:  "<<"rest"<<"\tiDcyBrIncDcyBr"<<i+1<<":  "<<"---"<<"\tnCases:  ";
              unsigned long nCCasesOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vCompICcIncDcyBr[i]==0)
                    {
                      fout<<"---"<<"\tnCcCases:  "<<"---"<<"\tnTotCases:  ";
                    }
                  else
                    {
                      unsigned long nCCasesOfRestTemp1=0;
                      unsigned long nCCasesOfRestTemp2=0;
                      for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNDcyBrIncDcyBr[i][j];
                      for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNDcyBrCcIncDcyBr[i][j];
                      fout<<nCCasesOfRestTemp1<<"\tnCcCases:  "<<nCCasesOfRestTemp2<<"\tnTotCases:  ";
                    }
                  for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                }
              else
                {
                  for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIncDcyBr[i][j];
                }
              nCCases=nCCases+nCCasesOfRest;
              fout<<nCCasesOfRest<<"\tnCCases:  "<<nCCases<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrIncDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==-11)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" --> others";
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
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" ---> ";
          for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;

          vector< list<int> > dcyBrIRADcyBr;
          list<int> subdcyBrIRADcyBr;
          unsigned long nCCases=0;
          unsigned long nDcyBrIRADcyBrToBePrtd=m_vVDcyBrIRADcyBr[i].size()<m_vNIntStrusToBePrtdMax[i]?m_vVDcyBrIRADcyBr[i].size():m_vNIntStrusToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrIRADcyBrToBePrtd;j++)
            {
              dcyBrIRADcyBr.clear();
              dcyBrIRADcyBr=m_vVDcyBrIRADcyBr[i][j];
              fout<<"rowNo:  "<<j+1<<"\tiDcyBrIRADcyBr"<<i+1<<":  "<<m_vVIDcyBrIRADcyBr[i][j]<<"\tnCases:  "<<m_vVNDcyBrIRADcyBr[i][j];
              if(m_ccSwitch==true)
                {
                  fout<<"\tnCcCases:  ";
                  if(m_vCompICcIRADcyBr[i]==0&&m_vVIDcyBrCcIRADcyBr[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcIRADcyBr[i][j];
                  fout<<"\tnTotCases:  "<<m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j]; 
                  nCCases=nCCases+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNDcyBrIRADcyBr[i][j];
                }
              fout<<"\tnCCases:  "<<nCCases<<endl;
              for(unsigned int k=0;k<dcyBrIRADcyBr.size();k++)
                {
                  fout<<" ";
                  subdcyBrIRADcyBr.clear();
                  subdcyBrIRADcyBr=dcyBrIRADcyBr[k];
                  list<int>::iterator liit=subdcyBrIRADcyBr.begin();
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                  if((k==0)&&((*liit)==-11))
                    {
                      liit++;
                      writePnmFromPid(fout,"TxtPnm",(*liit));
                    }
                  fout<<" -->";
                  for(liit++;liit!=subdcyBrIRADcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
                  fout<<endl;
                }
              fout<<endl;
            }
          if(nDcyBrIRADcyBrToBePrtd<m_vVDcyBrIRADcyBr[i].size())
            {
              fout<<"rowNo:  "<<"rest"<<"\tiDcyBrIRADcyBr"<<i+1<<":  "<<"---"<<"\tnCases:  ";
              unsigned long nCCasesOfRest=0;
              if(m_ccSwitch==true)
                {
                  if(m_vCompICcIRADcyBr[i]==0)
                    {
                      fout<<"---"<<"\tnCcCases:  "<<"---"<<"\tnTotCases:  ";
                    }
                  else
                    {
                      unsigned long nCCasesOfRestTemp1=0;
                      unsigned long nCCasesOfRestTemp2=0;
                      for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNDcyBrIRADcyBr[i][j];
                      for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNDcyBrCcIRADcyBr[i][j];
                      fout<<nCCasesOfRestTemp1<<"\tnCcCases:  "<<nCCasesOfRestTemp2<<"\tnTotCases:  ";
                    }
                  for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                }
              else
                {
                  for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIRADcyBr[i][j];
                }
              nCCases=nCCases+nCCasesOfRest;
              fout<<nCCasesOfRest<<"\tnCCases:  "<<nCCases<<endl;
              fout<<" ";
              list<int>::iterator liit=dcyBrIRADcyBr[0].begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if((*liit)==-11)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" --> others";
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
      list<int> sigDcyIFSts;
      unsigned long nCEtrs=0;
      for(unsigned int i=0;i<m_vSigDcyTr.size();i++)
        { 
          sigDcyTr.clear();
          sigDcyTr=m_vSigDcyTr[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigDcyTr:  "<<m_vISigDcyTr[i]<<"\tiSigDcyIFSts:  ";
          if(m_iSigDcyTrICcSigDcyIFStsMap[m_vISigDcyTr[i]]>=0) fout<<m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]];
          else fout<<m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]<<"_cc";
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
          if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
            {
              fout<<"\tiDcyIFSts:  ";
              if(m_iSigDcyIFStsIDcyIFStsMap.find(m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]])!=m_iSigDcyIFStsIDcyIFStsMap.end()) 
                {
                  if(m_iSigDcyIFStsICcDcyIFStsMap[m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]]>=0) fout<<m_iSigDcyIFStsIDcyIFStsMap[m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]];
                  else fout<<m_iSigDcyIFStsIDcyIFStsMap[m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]]<<"_cc";
                }
              else fout<<"---";
            }
          fout<<"\tnEtrs:  "<<m_vNSigDcyTr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtrs:  ";
              if(m_vICcSigDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyTr[i];
              fout<<"\tnTotEtrs:  "<<m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i];
              nCEtrs=nCEtrs+m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNSigDcyTr[i];
            }
          fout<<"\tnCEtrs:  "<<nCEtrs<<endl;
          for(unsigned int j=0;j<sigDcyTr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigDcyTr[j];
              fout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              // The condition "j==0&&((*liit)==-11)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==-11))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TxtPnm",(*liit));
                }
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl;
            }

          for(unsigned int j=0;j<m_vSigDcyIFSts.size();j++)
            {
              if(m_vISigDcyIFSts[j]==m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]])
                {
                  sigDcyIFSts.clear();
                  sigDcyIFSts=m_vSigDcyIFSts[j];
                  break;
                }
            }
          fout<<"(";
          list<int>::iterator liit=sigDcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }          
          fout<<" -->";
          for(liit++;liit!=sigDcyIFSts.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<" )"<<endl;

          fout<<endl;
        }

      fout<<endl;

      fout<<"Signal decay initial-final states corresponding to signal decay trees:"<<endl<<endl;
      //list<int> sigDcyIFSts; The list<int> variable sigDcyIFSts has been previously declared.
      nCEtrs=0;
      for(unsigned int i=0;i<m_vSigDcyIFSts.size();i++)
        {
          sigDcyIFSts.clear();
          sigDcyIFSts=m_vSigDcyIFSts[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigDcyIFSts:  "<<m_vISigDcyIFSts[i];
          if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
            {
              fout<<"\tiDcyIFSts:  ";
              if(m_iSigDcyIFStsIDcyIFStsMap.find(m_vISigDcyIFSts[i])!=m_iSigDcyIFStsIDcyIFStsMap.end())
                {
                  if(m_iSigDcyIFStsICcDcyIFStsMap[m_vISigDcyIFSts[i]]>=0) fout<<m_iSigDcyIFStsIDcyIFStsMap[m_vISigDcyIFSts[i]];
                  else fout<<m_iSigDcyIFStsIDcyIFStsMap[m_vISigDcyIFSts[i]]<<"_cc";
                }
              else fout<<"---";
            }
          fout<<"\tnEtrs:  "<<m_vNSigDcyIFSts[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtrs:  ";
              if(m_vICcSigDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyIFSts[i];
              fout<<"\tnTotEtrs:  "<<m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i]; 
              nCEtrs=nCEtrs+m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNSigDcyIFSts[i];
            }
          fout<<"\tnCEtrs:  "<<nCEtrs<<endl;
          fout<<" ";
          list<int>::iterator liit=sigDcyIFSts.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" -->";
          for(liit++;liit!=sigDcyIFSts.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
    }

  if(m_vSigDcyIFSts2.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal decay initial-final states:"<<endl<<endl;

      list<int> sigDcyIFSts2;
      unsigned long nCEtrs=0;
      for(unsigned int i=0;i<m_vSigDcyIFSts2.size();i++)
        {
          sigDcyIFSts2.clear();
          sigDcyIFSts2=m_vSigDcyIFSts2[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigDcyIFSts2:  "<<m_vISigDcyIFSts2[i];
          if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
            {
              fout<<"\tiDcyIFSts2:  ";
              if(m_iSigDcyIFSts2IDcyIFStsMap.find(m_vISigDcyIFSts2[i])!=m_iSigDcyIFSts2IDcyIFStsMap.end())      
                {
                  if(m_iSigDcyIFSts2ICcDcyIFStsMap[m_vISigDcyIFSts2[i]]>=0) fout<<m_iSigDcyIFSts2IDcyIFStsMap[m_vISigDcyIFSts2[i]];
                  else fout<<m_iSigDcyIFSts2IDcyIFStsMap[m_vISigDcyIFSts2[i]]<<"_cc";
                }
              else fout<<"---";
            }
          fout<<"\tnEtrs:  "<<m_vNSigDcyIFSts2[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcEtrs:  ";
              if(m_vICcSigDcyIFSts2[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyIFSts2[i];
              fout<<"\tnTotEtrs:  "<<m_vNSigDcyIFSts2[i]+m_vNCcSigDcyIFSts2[i];
              nCEtrs=nCEtrs+m_vNSigDcyIFSts2[i]+m_vNCcSigDcyIFSts2[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNSigDcyIFSts2[i];
            }
          fout<<"\tnCEtrs:  "<<nCEtrs<<endl;
          fout<<" ";
          list<int>::iterator liit=sigDcyIFSts2.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }
          fout<<" -->";
          for(liit++;liit!=sigDcyIFSts2.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
    }

  if(m_vPid_sigP.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal particles:"<<endl<<endl;
      unsigned long nCPs=0;
      for(unsigned int i=0;i<m_vNSigP.size();i++)
        {
          fout<<"rowNo:  "<<i+1<<"\tSigP: ";
          writePnmFromPid(fout,"TxtPnm",m_vPid_sigP[i]);
          fout<<"\tiSigP:  "<<m_vISigP[i]<<"\tnPs:   "<<m_vNSigP[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcPs:   ";
              if(m_vICcSigP[i]>0) fout<<m_vNCcSigP[i];
              else fout<<"---";
              fout<<"\tnTotPs:   "<<m_vNSigP[i]+m_vNCcSigP[i];
              nCPs=nCPs+m_vNSigP[i]+m_vNCcSigP[i];
            }
          else
            {
              nCPs=nCPs+m_vNSigP[i];
            }
          fout<<"\tnCPs:  "<<nCPs<<endl<<endl;
        }
    }

  if(m_vSigDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal decay branches:"<<endl<<endl;

      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigDcyBr.size();i++)
        {
          sigDcyBr.clear();
          sigDcyBr=m_vSigDcyBr[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigDcyBr:  "<<m_vISigDcyBr[i]<<"\tnCases:  "<<m_vNSigDcyBr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcCases:  ";
              if(m_vICcSigDcyBr[i]>0) fout<<m_vNCcSigDcyBr[i];
              else fout<<"---";
              fout<<"\tnTotCases:  "<<m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i];
              nCCases=nCCases+m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigDcyBr[i];
            }
          fout<<"\tnCCases:  "<<nCCases<<endl;
          fout<<" ";
          list<int>::iterator liit=sigDcyBr.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
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
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIncDcyBr.size();i++)
        {
          sigIncDcyBr.clear();
          sigIncDcyBr=m_vSigIncDcyBr[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIncDcyBr:  "<<m_vISigIncDcyBr[i]<<"\tnCases:  "<<m_vNSigIncDcyBr[i];
          if(m_ccSwitch==true)
            {
              fout<<"\tnCcCases:  ";
              if(m_vICcSigIncDcyBr[i]>0) fout<<m_vNCcSigIncDcyBr[i];
              else fout<<"---";
              fout<<"\tnTotCases:  "<<m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i];
              nCCases=nCCases+m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigIncDcyBr[i];
            }
          fout<<"\tnCCases:  "<<nCCases<<endl;
          fout<<" ";
          list<int>::iterator liit=sigIncDcyBr.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
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

  if(m_vSigCascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal cascade decay branches:"<<endl<<endl;
      vector< list<int> > sigCascDcyBrs;
      vector<int> vSigCascDcyBrsIdxOfHead;
      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigCascDcyBrs.size();i++)
        { 
          sigCascDcyBrs.clear();
          sigCascDcyBrs=m_vSigCascDcyBrs[i];
          vSigCascDcyBrsIdxOfHead=m_vVSigCascDcyBrsIdxOfHead[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigCascDcyBrs:  "<<m_vISigCascDcyBrs[i]<<"\tnCases:  "<<m_vNSigCascDcyBrs[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCases:  ";
              if(m_vICcSigCascDcyBrs[i]>0) fout<<m_vNCcSigCascDcyBrs[i];
              else fout<<"---";
              fout<<"\tnTotCases:  "<<m_vNSigCascDcyBrs[i]+m_vNCcSigCascDcyBrs[i];
              nCCases=nCCases+m_vNSigCascDcyBrs[i]+m_vNCcSigCascDcyBrs[i];
            }
          else
            { 
              nCCases=nCCases+m_vNSigCascDcyBrs[i];
            }
          fout<<"\tnCCases:  "<<nCCases<<endl;
          for(unsigned int j=0;j<sigCascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigCascDcyBrs[j];
              fout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if(j==0&&vSigCascDcyBrsIdxOfHead[0]==-1)
              {
                liit++;
                writePnmFromPid(fout,"TxtPnm",(*liit));
              }
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              fout<<endl;
            }
          fout<<endl;
        }
    }

  if(m_vSigIncCascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal inclusive cascade decay branches:"<<endl<<endl;
      vector< list<int> > sigIncCascDcyBrs;
      vector<int> vSigIncCascDcyBrsIdxOfHead;
      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIncCascDcyBrs.size();i++)
        { 
          sigIncCascDcyBrs.clear();
          sigIncCascDcyBrs=m_vSigIncCascDcyBrs[i];
          vSigIncCascDcyBrsIdxOfHead=m_vVSigIncCascDcyBrsIdxOfHead[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIncCascDcyBrs:  "<<m_vISigIncCascDcyBrs[i]<<"\tnCases:  "<<m_vNSigIncCascDcyBrs[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCases:  ";
              if(m_vICcSigIncCascDcyBrs[i]>0) fout<<m_vNCcSigIncCascDcyBrs[i];
              else fout<<"---";
              fout<<"\tnTotCases:  "<<m_vNSigIncCascDcyBrs[i]+m_vNCcSigIncCascDcyBrs[i];
              nCCases=nCCases+m_vNSigIncCascDcyBrs[i]+m_vNCcSigIncCascDcyBrs[i];
            }
          else
            { 
              nCCases=nCCases+m_vNSigIncCascDcyBrs[i];
            }
          fout<<"\tnCCases:  "<<nCCases<<endl;
          for(unsigned int j=0;j<sigIncCascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncCascDcyBrs[j];
              fout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if(j==0&&vSigIncCascDcyBrsIdxOfHead[0]==-1)
              {
                liit++;
                writePnmFromPid(fout,"TxtPnm",(*liit));
              }
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncCascDcyBrs[i][j]==1) writePnmFromPid(fout,"TxtPnm",m_pidOfAnything);
              fout<<endl;
            }
          fout<<endl;
        }
    }

  if(m_vSigIRADcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal intermediate-resonance-allowed decay branches:"<<endl<<endl;

      list<int> sigIRADcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIRADcyBr.size();i++)
        {
          sigIRADcyBr.clear();
          sigIRADcyBr=m_vSigIRADcyBr[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIRADcyBr:  "<<m_vISigIRADcyBr[i]<<"\tnCases:  "<<m_vNSigIRADcyBr[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCases:  ";
              if(m_vICcSigIRADcyBr[i]>0) fout<<m_vNCcSigIRADcyBr[i];
              else fout<<"---";
              fout<<"\tnTotCases:  "<<m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i];
              nCCases=nCCases+m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i];
            }
          else
            { 
              nCCases=nCCases+m_vNSigIRADcyBr[i];
            }
          fout<<"\tnCCases:  "<<nCCases<<endl;
          fout<<" ";
          list<int>::iterator liit=sigIRADcyBr.begin();
          writePnmFromPid(fout,"TxtPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TxtPnm",(*liit));
            }           
          fout<<" --->";
          for(liit++;liit!=sigIRADcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
          fout<<endl<<endl;
        }
    }

  if(m_vSigIncOrIRACascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      fout<<endl;

      fout<<"Signal inclusive or intermediate-resonance-allowed cascade decay branches:"<<endl<<endl;
      vector< list<int> > sigIncOrIRACascDcyBrs;
      vector<int> vSigIncOrIRACascDcyBrsIdxOfHead;
      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBrs.size();i++)
        { 
          sigIncOrIRACascDcyBrs.clear();
          sigIncOrIRACascDcyBrs=m_vSigIncOrIRACascDcyBrs[i];
          vSigIncOrIRACascDcyBrsIdxOfHead=m_vVSigIncOrIRACascDcyBrsIdxOfHead[i];
          fout<<"rowNo:  "<<i+1<<"\tiSigIncOrIRACascDcyBrs:  "<<m_vISigIncOrIRACascDcyBrs[i]<<"\tnCases:  "<<m_vNSigIncOrIRACascDcyBrs[i];
          if(m_ccSwitch==true)
            { 
              fout<<"\tnCcCases:  ";
              if(m_vICcSigIncOrIRACascDcyBrs[i]>0) fout<<m_vNCcSigIncOrIRACascDcyBrs[i];
              else fout<<"---";
              fout<<"\tnTotCases:  "<<m_vNSigIncOrIRACascDcyBrs[i]+m_vNCcSigIncOrIRACascDcyBrs[i];
              nCCases=nCCases+m_vNSigIncOrIRACascDcyBrs[i]+m_vNCcSigIncOrIRACascDcyBrs[i];
            }
          else
            { 
              nCCases=nCCases+m_vNSigIncOrIRACascDcyBrs[i];
            }
          fout<<"\tnCCases:  "<<nCCases<<endl;
          for(unsigned int j=0;j<sigIncOrIRACascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncOrIRACascDcyBrs[j];
              fout<<" ";
              list<int>::iterator liit=sigDcyBr.begin();
              writePnmFromPid(fout,"TxtPnm",(*liit));
              if(j==0&&vSigIncOrIRACascDcyBrsIdxOfHead[0]==-1)
              {
                liit++;
                writePnmFromPid(fout,"TxtPnm",(*liit));
              }
              if(m_vVIIRASigIncOrIRACascDcyBrs[i][j]==1) fout<<" (--> X)";
              fout<<" -->";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TxtPnm",(*liit));
              if(m_vVIIncSigIncOrIRACascDcyBrs[i][j]==1)
                {
                  writePnmFromPid(fout,"TxtPnm",m_pidOfAnything);
                }
              fout<<endl;
            }
          fout<<endl;
        }
    }
}
