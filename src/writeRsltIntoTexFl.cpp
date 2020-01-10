#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

void topoana::writeRsltIntoTexFl()
{
  if(m_anaTasksForSigIds=="T"&&m_vPid_compDcyBrP.size()==0&&m_vCompIncDcyBr.size()==0&&m_vCompIRADcyBr.size()==0&&m_compAnaOfDcyTrs==false&&m_compAnaOfDcyIFSts==false) return;

  string NmOfOptTexFl=m_mainNmOfOptFls+".tex";
  ofstream fout(NmOfOptTexFl.c_str(),ios::out);
  if(!fout)
    {
      cerr<<"Error: Can't create the output tex file \""<<NmOfOptTexFl<<"\"!"<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  fout<<"\\documentclass[landscape]{article}"<<endl;
  string pathOfGeometryStyFl=m_pkgPath+"share/";
  fout<<"\\usepackage{"<<pathOfGeometryStyFl<<"geometry}"<<endl;
  fout<<"\\usepackage[colorlinks,linkcolor=blue]{hyperref}"<<endl;
  //fout<<"\\usepackage{array}"<<endl;
  fout<<"\\usepackage{longtable}"<<endl;
  string pathOfMakeCellStyFl=m_pkgPath+"share/";
  fout<<"\\usepackage{"<<pathOfMakeCellStyFl<<"makecell}"<<endl;
  fout<<"\\usepackage{color}"<<endl;
  if((m_vSigIRADcyBr.size()>0&&m_anaTasksForSigIds!="T")||m_vVDcyBrIRADcyBr.size()>0) fout<<"\\usepackage{amssymb}"<<endl;
  fout<<"\\newcommand{\\tablecaption}[1]{\\caption{#1} \\\\}"<<endl;
  fout<<"\\usepackage{caption}"<<endl;
  fout<<"\\captionsetup{font=normalsize}"<<endl;
  fout<<"\\newcommand{\\tableheader}[1]"<<endl;
  fout<<"{"<<endl;
  fout<<"  \\hline"<<endl;
  fout<<"  #1"<<endl;
  fout<<"  \\hline"<<endl;
  fout<<"  \\endfirsthead"<<endl;
  fout<<endl;
  fout<<"  \\hline"<<endl;
  fout<<"  #1"<<endl;
  fout<<"  \\hline"<<endl;
  fout<<"  \\endhead"<<endl;
  fout<<endl;
  fout<<"  \\endfoot"<<endl;
  fout<<endl;
  fout<<"  \\endlastfoot"<<endl;
  fout<<"}"<<endl;
  fout<<"\\setcellgapes[t]{2pt}"<<endl;
  fout<<"\\makegapedcells"<<endl;
  fout<<"\\newcounter{rownumbers}"<<endl;
  fout<<"\\newcommand\\rn{\\stepcounter{rownumbers}\\arabic{rownumbers}}"<<endl;
  fout<<"\\newcommand{\\EOL}{\\\\ \\hline}"<<endl;
  fout<<"\\begin{document}"<<endl;
  fout<<"\\title{Topology Analysis \\footnote{\\normalsize{This package is implemented with reference to a program called {\\sc Topo}, which is developed by Prof. Shuxian Du from Zhengzhou University in China and has been widely used by people in BESIII collaboration. Several years ago, when I was a PhD student working on BESIII experiment, I learned the idea of topology analysis and a lot of programming techniques from the {\\sc Topo} program. So, I really appreciate Prof. Du's original work very much. To meet my own needs and to practice developing analysis tools with C++, ROOT and LaTex, I wrote the package from scratch. At that time, the package functioned well but was relatively simple. At the end of last year (2017), my co-supervisor, Prof. Chengping Shen reminded me that it could be a useful tool for Belle II experiment as well. So, I revised and extended it, making it more well-rounded and suitable for Belle II experiment. Here, I would like to thank Prof. Du for his orignial work, Prof. Shen for his suggestion and encouragement, and Xian Xiong, Wencheng Yan, Sen Jia, Yubo Li, Suxian Li, Longke Li, Guanda Gong, Junhao Yin, Xiaoping Qin, Xiqing Hao, HongPeng Wang, JiaWei Zhang, Yeqi Chen and Runqiu Ma for their efforts in helping me test the program. I would also like to thank my good friend Xi Chen, a professional programmer, for his suggestion in core algrithm and efficiency.}} \\\\ \\vspace{0.1cm} \\Large{("<<m_verNum<<")}}"<<endl;
  fout<<"\\author{Xingyu Zhou \\footnote{\\normalsize{Email: zhouxy@buaa.edu.cn}} \\\\ \\vspace{0.1cm} Beihang University}"<<endl;
  fout<<"\\maketitle"<<endl;
  fout<<endl<<"\\clearpage"<<endl<<endl;
  fout<<"\\newgeometry{left=2.5cm,right=2.5cm,top=2.5cm,bottom=2.5cm}"<<endl<<endl;
  fout<<"\\listoftables"<<endl<<endl;
  fout<<"\\newgeometry{left=0.0cm,right=0.0cm,top=2.5cm,bottom=2.5cm}"<<endl;
  unsigned int nBrsInALine;
  if(m_adjDcyIFStsIntoACol==true) nBrsInALine=4;
  else nBrsInALine=6; // The value of this variable is changed to 5 for the case of the table titled signal decay trees and their respective initial-final states.
  unsigned long nCEtrs;

  if(m_compAnaOfDcyTrs==true)
    {
      if(m_ccSwitch==true) nBrsInALine=5;
      vector< list<int> > dcyTr;
      list<int> dcyBr;
      list<int> dcyIFSts;
      nCEtrs=0;
      unsigned long nDcyTrsToBePrtd=m_vDcyTr.size()<m_nDcyTrsToBePrtdMax?m_vDcyTr.size():m_nDcyTrsToBePrtdMax;
      for(unsigned long i=0;i<nDcyTrsToBePrtd;i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l|";
              else fout<<"c|";
              if(m_adjDcyIFStsIntoACol==true)
                {
                  if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l|";
                  else fout<<"c|";
                }
              fout<<"c|c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Decay trees and their respective initial-final states.}"<<endl;
              fout<<"\\tableheader{rowNo & ";
              if(m_adjDcyIFStsIntoACol==true) fout<<"\\thead{decay tree} & \\thead{decay initial-final states}";
              else fout<<"\\thead{decay tree \\\\ (decay initial-final states)}";
              fout<<" & ";
              if(m_sprTopoTags==false) fout<<"iDcyTr & iDcyIFSts & ";
              fout<<"nEtrs & ";
              if(m_ccSwitch==true) fout<<"nCcEtrs & nTotEtrs & ";
              fout<<"nCEtrs \\\\}"<<endl<<endl;
            }
          dcyTr.clear();
          dcyTr=m_vDcyTr[i];
          unsigned int nVldDcyBrs=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<dcyTr.size();j++)
            {
              dcyBr.clear();
              dcyBr=dcyTr[j];
              // Since a lot of pi0s are produced and almost all of them decay to gammma pairs, to save paper and for convenience of readers, all branches of pi0 to gamma pairs are not outputted into the tex file, and hence not printed in the pdf file.
              list<int>::iterator liit=dcyBr.begin();
              list<int>::iterator liit1=dcyBr.begin();
              liit1++;
              list<int>::iterator liit2=dcyBr.begin();
              liit2++;
              liit2++;
              if(((*liit)==111)&&(dcyBr.size()==3)&&((*liit1)==22)&&((*liit2)==22)) continue;
              nVldDcyBrs++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              // The condition "j==0&&((*liit)==-11)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==-11))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=dcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              // The following bool variable is used to judge whether the current branch is the last one outputed or not.
              bool lastOneOrAllPi0sToGamPairsBehind=true;
              list<int> dcyBrTmp;
              for(unsigned int k=j+1;k<dcyTr.size();k++)
                {
                  dcyBrTmp.clear();
                  dcyBrTmp=dcyTr[k];
                  list<int>::iterator liitTmp=dcyBrTmp.begin();
                  list<int>::iterator liitTmp1=dcyBrTmp.begin();
                  liitTmp1++;
                  list<int>::iterator liitTmp2=dcyBrTmp.begin();
                  liitTmp2++;
                  liitTmp2++;
                  if(((*liitTmp)!=111)||(dcyBrTmp.size()!=3)||((*liitTmp1)!=22)||((*liitTmp2)!=22))
                    {
                      lastOneOrAllPi0sToGamPairsBehind=false;
                      break;
                    }
                }
              if(!lastOneOrAllPi0sToGamPairsBehind)
                {
                  fout<<","<<endl;
                  if(nVldDcyBrs%nBrsInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  if(m_adjDcyIFStsIntoACol==true) fout<<endl<<"$ } & $"<<endl;
                  else fout<<endl<<"$ \\\\ ($"<<endl;
                  break;
                }
            }

          for(unsigned int j=0;j<m_vDcyIFSts.size();j++)
            {
              if(m_vIDcyIFSts[j]==m_iDcyTrIDcyIFStsMap[m_vIDcyTr[i]])
                {
                  dcyIFSts.clear();
                  dcyIFSts=m_vDcyIFSts[j];
                  break;
                }
            }
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          //if(m_adjDcyIFStsIntoACol==false) writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              //if(m_adjDcyIFStsIntoACol==false) writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\rightarrow ";
          //if(m_adjDcyIFStsIntoACol==false) fout<<"\\rightarrow ";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          if(m_adjDcyIFStsIntoACol==true) fout<<endl<<"$ & ";
          else fout<<endl<<"$) } & ";
          if(m_sprTopoTags==false) fout<<m_vIDcyTr[i]<<" & "<<m_iDcyTrIDcyIFStsMap[m_vIDcyTr[i]]<<" & ";
          fout<<m_vNDcyTr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcDcyTr[i];
              fout<<" & "<<m_vNDcyTr[i]+m_vNCcDcyTr[i]<<" & ";
              nCEtrs=nCEtrs+m_vNDcyTr[i]+m_vNCcDcyTr[i];          
            }
          else
            {
              nCEtrs=nCEtrs+m_vNDcyTr[i];
            }
          fout<<nCEtrs<<" \\EOL"<<endl<<endl;
          if(i==nDcyTrsToBePrtd-1)
            {
              if(nDcyTrsToBePrtd<m_vDcyTr.size())
                {
                  fout<<"rest"<<" & \\makecell[";
                  if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  fout<<"]{ $ "<<endl;
                  if(m_initEpEmSwitch==true)
                    {
                      writePnmFromPid(fout,"TexPnm",-11);
                      writePnmFromPid(fout,"TexPnm",11);
                      fout<<"\\rightarrow \\rm{others}";
                      if(m_adjDcyIFStsIntoACol==true) fout<<endl<<"$ } & $"<<endl;
                      else fout<<endl<<"$ \\\\ ($"<<endl;
                      writePnmFromPid(fout,"TexPnm",-11);
                      writePnmFromPid(fout,"TexPnm",11);
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
                          writePnmFromPid(fout,"TexPnm",pid);
                          fout<<"\\rightarrow \\rm{others}";
                          if(m_adjDcyIFStsIntoACol==true) fout<<endl<<"$ } & $"<<endl;
                          else fout<<endl<<"$ \\\\ ($"<<endl;
                          writePnmFromPid(fout,"TexPnm",pid);
                        }
                      else
                        {
                          writePnmFromPid(fout,"TexPnm",-11);
                          writePnmFromPid(fout,"TexPnm",11);
                          fout<<"\\rightarrow \\rm{others}";
                          if(m_adjDcyIFStsIntoACol==true) fout<<endl<<"$ } & $"<<endl;
                          else fout<<endl<<"$ \\\\ ($"<<endl;
                          writePnmFromPid(fout,"TexPnm",-11);
                          writePnmFromPid(fout,"TexPnm",11);
                        }
                    }
                  fout<<"\\rightarrow \\rm{corresponding\\ to\\ others}"<<endl;
                  if(m_adjDcyIFStsIntoACol==true) fout<<"$ & ";
                  else fout<<"$) } & ";
                  if(m_sprTopoTags==false) fout<<"---"<<" & "<<"---"<<" & ";
                  unsigned long nCEtrsOfRest=0;
                  if(m_ccSwitch==true)
                    {
                      fout<<"---"<<" & "<<"---"<<" & ";
                      for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyTr[i]+m_vNCcDcyTr[i];
                    }
                  else
                    {
                      for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyTr[i];
                    }
                  nCEtrs=nCEtrs+nCEtrsOfRest;
                  fout<<nCEtrsOfRest<<" & "<<nCEtrs<<" \\EOL"<<endl<<endl;
                }
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
    {
      if(m_ccSwitch==true) nBrsInALine=6;

      //list<int> dcyIFSts; The list<int> variable dcyIFSts has been previously declared.
      list<int> dcyIFSts;
      nCEtrs=0;
      unsigned long nDcyIFStsToBePrtd=m_vDcyIFSts.size()<m_nDcyIFStsToBePrtdMax?m_vDcyIFSts.size():m_nDcyIFStsToBePrtdMax;
      for(unsigned long i=0;i<nDcyIFStsToBePrtd;i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&nDcyIFStsToBePrtd>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Decay initial-final states.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{decay initial-final states} & ";
              if(m_sprTopoTags==false) fout<<"iDcyIFSts & ";
              fout<<"nEtrs & ";
              if(m_ccSwitch==true) fout<<"nCcEtrs & nTotEtrs & ";
              fout<<"nCEtrs \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          dcyIFSts.clear();
          dcyIFSts=m_vDcyIFSts[i];
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\rightarrow ";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & ";
          if(m_sprTopoTags==false) fout<<m_vIDcyIFSts[i]<<" & ";
          fout<<m_vNDcyIFSts[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcDcyIFSts[i];
              fout<<" & "<<m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i]<<" & ";
              nCEtrs=nCEtrs+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNDcyIFSts[i];
            }
          fout<<nCEtrs<<" \\EOL"<<endl<<endl;
          if(i==nDcyIFStsToBePrtd-1)
            {
              if(nDcyIFStsToBePrtd<m_vDcyIFSts.size())
                {
                  fout<<"rest"<<" & $ ";
                  list<int>::iterator liit=dcyIFSts.begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==-11)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\rightarrow \\rm{others}";
                  fout<<" $ & ";
                  if(m_sprTopoTags==false) fout<<"---"<<" & ";
                  unsigned long nCEtrsOfRest=0;
                  if(m_ccSwitch==true)
                    {
                      fout<<"---"<<" & "<<"---"<<" & ";
                      for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
                    }
                  else
                    {
                      for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrsOfRest=nCEtrsOfRest+m_vNDcyIFSts[i];
                    }
                  nCEtrs=nCEtrs+nCEtrsOfRest;
                  fout<<nCEtrsOfRest<<" & "<<nCEtrs<<" \\EOL"<<endl<<endl;
                }
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_vVDcyBrP.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyBrP.size();i++)
        {
          list<int> dcyBrP;
          unsigned long nCCases=0;
          unsigned long nDcyBrPToBePrtd=m_vVDcyBrP[i].size()<m_vNDcyBrsToBePrtdMax[i]?m_vVDcyBrP[i].size():m_vNDcyBrsToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{|c|";
                  if(m_centDcyObjs==false&&nDcyBrPToBePrtd>1) fout<<"l|";
                  else fout<<"c|";
                  fout<<"c|c|c|";
                  if(m_ccSwitch==true) fout<<"c|c|";
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Decay branches of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compDcyBrP[i]);
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader{rowNo & \\thead{decay branch of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compDcyBrP[i]);
                  fout<<"$} & ";
                  if(m_sprTopoTags==false) fout<<"iDcyBrP"<<i+1<<" & ";
                  fout<<"nCases & ";
                  if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & ";
                  fout<<"nCCases \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              dcyBrP.clear();
              dcyBrP=m_vVDcyBrP[i][j];
              list<int>::iterator liit=dcyBrP.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"\\rightarrow ";
              for(liit++;liit!=dcyBrP.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"$ & ";
              if(m_sprTopoTags==false) fout<<m_vVIDcyBrP[i][j]<<" & ";
              fout<<m_vVNDcyBrP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompDcyBrP[i]==0&&m_vVIDcyBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcP[i][j];
                  fout<<" & "<<m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j]<<" & ";
                  nCCases=nCCases+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNDcyBrP[i][j];
                }
              fout<<nCCases<<" \\EOL"<<endl<<endl;
              if(j==nDcyBrPToBePrtd-1)
                {
                  if(nDcyBrPToBePrtd<m_vVDcyBrP[i].size())
                    {
                      fout<<"rest"<<" & $ ";
                      dcyBrP.clear();
                      dcyBrP=m_vVDcyBrP[i][j];
                      list<int>::iterator liit=dcyBrP.begin();
                      writePnmFromPid(fout,"TexPnm",(*liit));
                      fout<<"\\rightarrow \\rm{others}";
                      fout<<" $ & ";
                      if(m_sprTopoTags==false) fout<<"---"<<" & ";
                      unsigned long nCCasesOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompDcyBrP[i]==0)
                            {
                              fout<<"---"<<" & "<<"---"<<" & ";
                            }
                          else
                            {
                              unsigned long nCCasesOfRestTemp1=0;
                              unsigned long nCCasesOfRestTemp2=0;
                              for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNDcyBrP[i][j];
                              for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNDcyBrCcP[i][j];
                              fout<<nCCasesOfRestTemp1<<" & "<<nCCasesOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrP[i][j];
                        }
                      nCCases=nCCases+nCCasesOfRest;
                      fout<<nCCasesOfRest<<" & "<<nCCases<<" \\EOL"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vVProdBrP.size()>0)
    {
      for(unsigned int i=0;i<m_vVProdBrP.size();i++)
        {
          list<int> prodBrP;
          unsigned long nCCases=0;
          unsigned long nProdBrPToBePrtd=m_vVProdBrP[i].size()<m_vNProdBrsToBePrtdMax[i]?m_vVProdBrP[i].size():m_vNProdBrsToBePrtdMax[i];
          for(unsigned int j=0;j<nProdBrPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{|c|";
                  if(m_centDcyObjs==false&&nProdBrPToBePrtd>1) fout<<"l|";
                  else fout<<"c|";
                  fout<<"c|c|c|";
                  if(m_ccSwitch==true) fout<<"c|c|";
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Production branches of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compProdBrP[i]);
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader{rowNo & \\thead{production branch of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compProdBrP[i]);
                  fout<<"$} & ";
                  if(m_sprTopoTags==false) fout<<"iProdBr\\_P"<<i<<" & ";
                  fout<<"nCases & ";
                  if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & ";
                  fout<<"nCCases \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              prodBrP.clear();
              prodBrP=m_vVProdBrP[i][j];
              list<int>::iterator liit=prodBrP.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"\\rightarrow ";
              for(liit++;liit!=prodBrP.end();liit++)
                {
                  if((*liit)==m_vPid_compProdBrP[i]) fout<<"{\\color{blue}{ ";
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==m_vPid_compProdBrP[i]) fout<<"}} ";
                }
              fout<<"$ & ";
              if(m_sprTopoTags==false) fout<<m_vVIProdBrP[i][j]<<" & ";
              fout<<m_vVNProdBrP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompProdBrP[i]==0&&m_vVIProdBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNProdBrCcP[i][j];
                  fout<<" & "<<m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j]<<" & ";
                  nCCases=nCCases+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNProdBrP[i][j];
                }
              fout<<nCCases<<" \\EOL"<<endl<<endl;
              if(j==nProdBrPToBePrtd-1)
                {
                  if(nProdBrPToBePrtd<m_vVProdBrP[i].size())
                    {
                      fout<<"rest"<<" & others & ";
                      if(m_sprTopoTags==false) fout<<"---"<<" & ";
                      unsigned long nCCasesOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompProdBrP[i]==0)
                            {
                              fout<<"---"<<" & "<<"---"<<" & ";
                            }
                          else
                            {
                              unsigned long nCCasesOfRestTemp1=0;
                              unsigned long nCCasesOfRestTemp2=0;
                              for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNProdBrP[i][j];
                              for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNProdBrCcP[i][j];
                              fout<<nCCasesOfRestTemp1<<" & "<<nCCasesOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNProdBrP[i][j];
                        }
                      nCCases=nCCases+nCCasesOfRest;
                      fout<<nCCasesOfRest<<" & "<<nCCases<<" \\EOL"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vVMpidP.size()>0)
    {
      for(unsigned int i=0;i<m_vVMpidP.size();i++)
        {
          unsigned long nCCases=0;
          unsigned long nMPToBePrtd=m_vVMpidP[i].size()<m_vNMsToBePrtdMax[i]?m_vVMpidP[i].size():m_vNMsToBePrtdMax[i];
          for(unsigned int j=0;j<nMPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{|c|c|c|c|c|";
                  if(m_ccSwitch==true) fout<<"c|c|";
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Mothers of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compMP[i]);
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader{rowNo & \\thead{mother of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compMP[i]);
                  fout<<"$} & ";
                  char brNmofMothPDGVar[100];
                  if(m_vNm_compMP[i].empty()) sprintf(brNmofMothPDGVar, "MothPDG\\_P%d", i);
                  else sprintf(brNmofMothPDGVar, "MothPDG\\_%s", m_vNm_compMP[i].c_str());
                  if(m_sprTopoTags==false) fout<<brNmofMothPDGVar<<" & ";
                  fout<<"nCases & ";
                  if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & ";
                  fout<<"nCCases \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              writePnmFromPid(fout,"TexPnm",m_vVMpidP[i][j]);
              fout<<"$ & ";
              if(m_sprTopoTags==false) fout<<m_vVMpidP[i][j]<<" & ";
              fout<<m_vVNMP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompMP[i]==0&&m_vVIMCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNMCcP[i][j];
                  fout<<" & "<<m_vVNMP[i][j]+m_vVNMCcP[i][j]<<" & ";
                  nCCases=nCCases+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNMP[i][j];
                }
              fout<<nCCases<<" \\EOL"<<endl<<endl;
              if(j==nMPToBePrtd-1)
                {
                  if(nMPToBePrtd<m_vVMpidP[i].size())
                    {
                      fout<<"rest"<<" & others & ";
                      if(m_sprTopoTags==false) fout<<"---"<<" & ";
                      unsigned long nCCasesOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompMP[i]==0)
                            {
                              fout<<"---"<<" & "<<"---"<<" & ";
                            }
                          else
                            {
                              unsigned long nCCasesOfRestTemp1=0;
                              unsigned long nCCasesOfRestTemp2=0;
                              for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNMP[i][j];
                              for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNMCcP[i][j];
                              fout<<nCCasesOfRestTemp1<<" & "<<nCCasesOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNMP[i][j];
                        }
                      nCCases=nCCases+nCCasesOfRest;
                      fout<<nCCasesOfRest<<" & "<<nCCases<<" \\EOL"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vVDcyBrIncDcyBr.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyBrIncDcyBr.size();i++)
        {
          list<int> dcyBrIncDcyBr;
          unsigned long nCCases=0;
          unsigned long nDcyBrIncDcyBrToBePrtd=m_vVDcyBrIncDcyBr[i].size()<m_vNExcCompsToBePrtdMax[i]?m_vVDcyBrIncDcyBr[i].size():m_vNExcCompsToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrIncDcyBrToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{|c|";
                  if(m_centDcyObjs==false&&nDcyBrIncDcyBrToBePrtd>1) fout<<"l|";
                  else fout<<"c|";
                  fout<<"c|c|c|";
                  if(m_ccSwitch==true) fout<<"c|c|";
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Exclusive components of $ ";
                  list<int>::iterator liit=m_vCompIncDcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==-11)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\rightarrow ";
                  for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"+ \\rm{anything} ";
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader{rowNo & \\thead{exclusive component of $ ";
                  liit=m_vCompIncDcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==-11)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\rightarrow ";
                  for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"+ \\rm{anything} ";
                  fout<<"$} & ";
                  if(m_sprTopoTags==false) fout<<"iDcyBrIncDcyBr"<<i+1<<" & ";
                  fout<<"nCases & ";
                  if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & ";
                  fout<<"nCCases \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              dcyBrIncDcyBr.clear();
              dcyBrIncDcyBr=m_vVDcyBrIncDcyBr[i][j];
              list<int>::iterator liit=dcyBrIncDcyBr.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              if((*liit)==-11)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=dcyBrIncDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"$ & ";
              if(m_sprTopoTags==false) fout<<m_vVIDcyBrIncDcyBr[i][j]<<" & ";
              fout<<m_vVNDcyBrIncDcyBr[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  // Note that "(m_vCompICcIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])" is used here for a very special case where the inclusive decay branch is not self-charge-conjugate but the exclusive decay branch is self-charge-conjugate. 
                  if((m_vCompICcIncDcyBr[i]==0&&m_vVIDcyBrCcIncDcyBr[i][j]==0)||(m_vCompICcIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])) fout<<"---";
                  else fout<<m_vVNDcyBrCcIncDcyBr[i][j];
                  fout<<" & "<<m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j]<<" & ";
                  nCCases=nCCases+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNDcyBrIncDcyBr[i][j];
                }
              fout<<nCCases<<" \\EOL"<<endl<<endl;
              if(j==nDcyBrIncDcyBrToBePrtd-1)
                {
                  if(nDcyBrIncDcyBrToBePrtd<m_vVDcyBrIncDcyBr[i].size())
                    {
                      fout<<"rest"<<" & $ ";
                      dcyBrIncDcyBr.clear();
                      dcyBrIncDcyBr=m_vVDcyBrIncDcyBr[i][j];
                      list<int>::iterator liit=dcyBrIncDcyBr.begin();
                      writePnmFromPid(fout,"TexPnm",(*liit));
                      if((*liit)==-11)
                        {
                          liit++;
                          writePnmFromPid(fout,"TexPnm",(*liit));
                        }
                      fout<<"\\rightarrow \\rm{others}";
                      fout<<" $ & ";
                      if(m_sprTopoTags==false) fout<<"---"<<" & ";
                      unsigned long nCCasesOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vCompICcIncDcyBr[i]==0)
                            {
                              fout<<"---"<<" & "<<"---"<<" & ";
                            }
                          else
                            {
                              unsigned long nCCasesOfRestTemp1=0;
                              unsigned long nCCasesOfRestTemp2=0;
                              for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNDcyBrIncDcyBr[i][j];
                              for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNDcyBrCcIncDcyBr[i][j];
                              fout<<nCCasesOfRestTemp1<<" & "<<nCCasesOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIncDcyBr[i][j];
                        }
                      nCCases=nCCases+nCCasesOfRest;
                      fout<<nCCasesOfRest<<" & "<<nCCases<<" \\EOL"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vVDcyBrIRADcyBr.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyBrIRADcyBr.size();i++)
        {
          vector< list<int> > dcyBrIRADcyBr;
          list<int> subdcyBrIRADcyBr;
          unsigned long nCCases=0;
          unsigned long nDcyBrIRADcyBrToBePrtd=m_vVDcyBrIRADcyBr[i].size()<m_vNIntStrusToBePrtdMax[i]?m_vVDcyBrIRADcyBr[i].size():m_vNIntStrusToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrIRADcyBrToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{|c|";
                  if(m_centDcyObjs==false&&nDcyBrIRADcyBrToBePrtd>1) fout<<"l|";
                  else fout<<"c|";
                  fout<<"c|c|c|";
                  if(m_ccSwitch==true) fout<<"c|c|";
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Exclusive components of $ ";
                  list<int>::iterator liit=m_vCompIRADcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==-11)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\dashrightarrow ";
                  for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader{rowNo & \\thead{exclusive component of $ ";
                  liit=m_vCompIRADcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==-11)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\dashrightarrow ";
                  for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"$} & ";
                  if(m_sprTopoTags==false) fout<<"iDcyBrIRADcyBr"<<i+1<<" & ";
                  fout<<"nCases & ";
                  if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & ";
                  fout<<"nCCases \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              dcyBrIRADcyBr.clear();
              dcyBrIRADcyBr=m_vVDcyBrIRADcyBr[i][j];
              for(unsigned int k=0;k<dcyBrIRADcyBr.size();k++)
                {
                  subdcyBrIRADcyBr.clear();
                  subdcyBrIRADcyBr=dcyBrIRADcyBr[k];
                  list<int>::iterator liit=subdcyBrIRADcyBr.begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((k==0)&&((*liit)==-11))
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\rightarrow ";
                  for(liit++;liit!=subdcyBrIRADcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  if(k!=(dcyBrIRADcyBr.size()-1)) fout<<", ";
                }
              fout<<"$ & ";
              if(m_sprTopoTags==false) fout<<m_vVIDcyBrIRADcyBr[i][j]<<" & ";
              fout<<m_vVNDcyBrIRADcyBr[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vCompICcIRADcyBr[i]==0&&m_vVIDcyBrCcIRADcyBr[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcIRADcyBr[i][j];
                  fout<<" & "<<m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j]<<" & ";
                  nCCases=nCCases+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                }
              else
                {
                  nCCases=nCCases+m_vVNDcyBrIRADcyBr[i][j];
                }
              fout<<nCCases<<" \\EOL"<<endl<<endl;
              if(j==nDcyBrIRADcyBrToBePrtd-1)
                {
                  if(nDcyBrIRADcyBrToBePrtd<m_vVDcyBrIRADcyBr[i].size())
                    {
                      fout<<"rest"<<" & $ ";
                      dcyBrIRADcyBr.clear();
                      dcyBrIRADcyBr=m_vVDcyBrIRADcyBr[i][j];
                      list<int>::iterator liit=dcyBrIRADcyBr[0].begin();
                      writePnmFromPid(fout,"TexPnm",(*liit));
                      if((*liit)==-11)
                        {
                          liit++;
                          writePnmFromPid(fout,"TexPnm",(*liit));
                        }
                      fout<<"\\rightarrow \\rm{others}";
                      fout<<" $ & ";
                      if(m_sprTopoTags==false) fout<<"---"<<" & ";
                      unsigned long nCCasesOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vCompICcIRADcyBr[i]==0)
                            {
                              fout<<"---"<<" & "<<"---"<<" & ";
                            }
                          else
                            {
                              unsigned long nCCasesOfRestTemp1=0;
                              unsigned long nCCasesOfRestTemp2=0;
                              for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRestTemp1=nCCasesOfRestTemp1+m_vVNDcyBrIRADcyBr[i][j];
                              for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRestTemp2=nCCasesOfRestTemp2+m_vVNDcyBrCcIRADcyBr[i][j];
                              fout<<nCCasesOfRestTemp1<<" & "<<nCCasesOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCasesOfRest=nCCasesOfRest+m_vVNDcyBrIRADcyBr[i][j];
                        }
                      nCCases=nCCases+nCCasesOfRest;
                      fout<<nCCasesOfRest<<" & "<<nCCases<<" \\EOL"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vSigDcyTr.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrsInALine=4;
      else nBrsInALine=5;
      if(m_adjDcyIFStsIntoACol==true) nBrsInALine--;
      vector< list<int> > sigDcyTr;
      list<int> sigDcyBr;
      list<int> sigDcyIFSts;
      nCEtrs=0;
      for(unsigned int i=0;i<m_vSigDcyTr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigDcyTr.size()>1) fout<<"l|";
              else fout<<"c|";
              if(m_adjDcyIFStsIntoACol==true)
                {
                  if(m_centDcyObjs==false&&m_vSigDcyTr.size()>1) fout<<"l|";
                  else fout<<"c|";
                }
              fout<<"c|c|";
              if(m_compAnaOfDcyTrs==true) fout<<"c|";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true) fout<<"c|";
              fout<<"c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal decay trees and their respective initial-final states.}"<<endl;
              fout<<"\\tableheader{rowNo & ";
              if(m_adjDcyIFStsIntoACol==true) fout<<"\\thead{signal decay tree} & \\thead{signal decay initial-final states}";
              else fout<<"\\thead{signal decay tree \\\\ (signal decay initial-final states)}";
              fout<<" & ";
              if(m_sprTopoTags==false) fout<<"iSigDcyTr & iSigDcyIFSts & ";
              if(m_compAnaOfDcyTrs==true) fout<<"iDcyTr & ";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true) fout<<"iDcyIFSts & ";
              fout<<"nEtrs & ";
              if(m_ccSwitch==true) fout<<"nCcEtrs & nTotEtrs & ";
              fout<<"nCEtrs \\\\}"<<endl<<endl;
            }
          sigDcyTr.clear();
          sigDcyTr=m_vSigDcyTr[i];
          unsigned int nVldSigDcyTr=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigDcyTr.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigDcyTr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigDcyTr[j];              
              // Since a lot of pi0s are produced and almost all of them decay to gammma pairs, to save paper and for convenience of readers, all branches of pi0 to gamma pairs are not outputted into the tex file, and hence not printed in the pdf file.
              list<int>::iterator liit=sigDcyBr.begin();
              list<int>::iterator liit1=sigDcyBr.begin();
              liit1++;
              list<int>::iterator liit2=sigDcyBr.begin();
              liit2++;
              liit2++;
              if(((*liit)==111)&&(sigDcyBr.size()==3)&&((*liit1)==22)&&((*liit2)==22)) continue;
              nVldSigDcyTr++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              // The condition "j==0&&((*liit)==-11)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==-11))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              // The following bool variable is used to judge whether the current branch is the last one outputed or not.
              bool lastOneOrAllPi0sToGamPairsBehind=true;
              list<int> sigDcyBrTmp;
              for(unsigned int k=j+1;k<sigDcyTr.size();k++)
                {
                  sigDcyBrTmp.clear();
                  sigDcyBrTmp=sigDcyTr[k];
                  list<int>::iterator liitTmp=sigDcyBrTmp.begin();
                  list<int>::iterator liitTmp1=sigDcyBrTmp.begin();
                  liitTmp1++;
                  list<int>::iterator liitTmp2=sigDcyBrTmp.begin();
                  liitTmp2++;
                  liitTmp2++;
                  if(((*liitTmp)!=111)||(sigDcyBrTmp.size()!=3)||((*liitTmp1)!=22)||((*liitTmp2)!=22))
                    {
                      lastOneOrAllPi0sToGamPairsBehind=false;
                      break;
                    }
                }
              if(!lastOneOrAllPi0sToGamPairsBehind)
                {
                  fout<<","<<endl;
                  if(nVldSigDcyTr%nBrsInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  if(m_adjDcyIFStsIntoACol==true) fout<<endl<<"$ } & $"<<endl;
                  else fout<<endl<<"$ \\\\ ($"<<endl;
                  break;
                }
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
          list<int>::iterator liit=sigDcyIFSts.begin();
          if(m_adjDcyIFStsIntoACol==false) writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              if(m_adjDcyIFStsIntoACol==false) writePnmFromPid(fout,"TexPnm",(*liit));
            }
          if(m_adjDcyIFStsIntoACol==false) fout<<"\\rightarrow ";
          for(liit++;liit!=sigDcyIFSts.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          if(m_adjDcyIFStsIntoACol==true) fout<<endl<<"$ & ";
          else fout<<endl<<"$) } & ";
          if(m_sprTopoTags==false)
            {
              fout<<m_vISigDcyTr[i]<<" & ";
              if(m_iSigDcyTrICcSigDcyIFStsMap[m_vISigDcyTr[i]]>=0) fout<<m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]];
              else fout<<"$ "<<m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]<<"_{\\rm cc} $";
              fout<<" & ";
              if(m_compAnaOfDcyTrs==true)
                {
                  if(m_iSigDcyTrIDcyTrMap.find(m_vISigDcyTr[i])!=m_iSigDcyTrIDcyTrMap.end())
                    {
                      if(m_iSigDcyTrICcDcyTrMap[m_vISigDcyTr[i]]>=0) fout<<m_iSigDcyTrIDcyTrMap[m_vISigDcyTr[i]];
                      else fout<<"$ "<<m_iSigDcyTrIDcyTrMap[m_vISigDcyTr[i]]<<"_{\\rm cc} $";
                    }
                  else fout<<"---";
                  fout<<" & ";
                }
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
                {
                  if(m_iSigDcyIFStsIDcyIFStsMap.find(m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]])!=m_iSigDcyIFStsIDcyIFStsMap.end())
                    {
                      if(m_iSigDcyIFStsICcDcyIFStsMap[m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]]>=0) fout<<m_iSigDcyIFStsIDcyIFStsMap[m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]];
                      else fout<<"$ "<<m_iSigDcyIFStsIDcyIFStsMap[m_iSigDcyTrISigDcyIFStsMap[m_vISigDcyTr[i]]]<<"_{\\rm cc} $";
                    }
                  else fout<<"---";
                  fout<<" & ";
                }
            }
          fout<<m_vNSigDcyTr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyTr[i];
              fout<<" & "<<m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i]<<" & ";
              nCEtrs=nCEtrs+m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i];          
            }
          else
            {
              nCEtrs=nCEtrs+m_vNSigDcyTr[i];
            }
          fout<<nCEtrs<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigDcyTr.size()-1)) fout<<"\\end{longtable}"<<endl;
        }

      //list<int> sigDcyIFSts; The list<int> variable sigDcyIFSts has been previously declared.
      nCEtrs=0;
      for(unsigned int i=0;i<m_vSigDcyIFSts.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigDcyIFSts.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true) fout<<"c|";
              fout<<"c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal decay initial-final states corresponding to signal decay trees.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal decay initial-final states} & ";
              if(m_sprTopoTags==false) fout<<"iSigDcyIFSts & ";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true) fout<<"iDcyIFSts & ";
              fout<<"nEtrs & ";
              if(m_ccSwitch==true) fout<<"nCcEtrs & nTotEtrs & ";
              fout<<"nCEtrs \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigDcyIFSts.clear();
          sigDcyIFSts=m_vSigDcyIFSts[i];
          list<int>::iterator liit=sigDcyIFSts.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\rightarrow ";
          for(liit++;liit!=sigDcyIFSts.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & ";
          if(m_sprTopoTags==false)
            {
              fout<<m_vISigDcyIFSts[i]<<" & ";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
                {
                  if(m_iSigDcyIFStsIDcyIFStsMap.find(m_vISigDcyIFSts[i])!=m_iSigDcyIFStsIDcyIFStsMap.end())
                    {
                      if(m_iSigDcyIFStsICcDcyIFStsMap[m_vISigDcyIFSts[i]]>=0) fout<<m_iSigDcyIFStsIDcyIFStsMap[m_vISigDcyIFSts[i]];
                      else fout<<"$ "<<m_iSigDcyIFStsIDcyIFStsMap[m_vISigDcyIFSts[i]]<<"_{\\rm cc} $";
                    }
                  else fout<<"---";
                  fout<<" & ";
                }
            }
          fout<<m_vNSigDcyIFSts[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyIFSts[i];
              fout<<" & "<<m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i]<<" & ";
              nCEtrs=nCEtrs+m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNSigDcyIFSts[i];
            }
          fout<<nCEtrs<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigDcyIFSts.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
    }

  if(m_vSigDcyIFSts2.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigDcyIFSts2;
      nCEtrs=0;
      for(unsigned int i=0;i<m_vSigDcyIFSts2.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigDcyIFSts2.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true) fout<<"c|";
              fout<<"c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal decay initial-final states.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal decay initial-final states} & ";
              if(m_sprTopoTags==false) fout<<"iSigDcyIFSts2 & ";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true) fout<<"iDcyIFSts & ";
              fout<<"nEtrs & ";
              if(m_ccSwitch==true) fout<<"nCcEtrs & nTotEtrs & ";
              fout<<"nCEtrs \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigDcyIFSts2.clear();
          sigDcyIFSts2=m_vSigDcyIFSts2[i];
          list<int>::iterator liit=sigDcyIFSts2.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\rightarrow ";
          for(liit++;liit!=sigDcyIFSts2.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & ";
          if(m_sprTopoTags==false)
            {
              fout<<m_vISigDcyIFSts2[i]<<" & ";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
                {
                  if(m_iSigDcyIFSts2IDcyIFStsMap.find(m_vISigDcyIFSts2[i])!=m_iSigDcyIFSts2IDcyIFStsMap.end())
                    {
                      if(m_iSigDcyIFSts2ICcDcyIFStsMap[m_vISigDcyIFSts2[i]]>=0) fout<<m_iSigDcyIFSts2IDcyIFStsMap[m_vISigDcyIFSts2[i]];
                      else fout<<"$ "<<m_iSigDcyIFSts2IDcyIFStsMap[m_vISigDcyIFSts2[i]]<<"_{\\rm cc} $";
                    }
                  else fout<<"---";
                  fout<<" & ";
                }
            }
          fout<<m_vNSigDcyIFSts2[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigDcyIFSts2[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyIFSts2[i];
              fout<<" & "<<m_vNSigDcyIFSts2[i]+m_vNCcSigDcyIFSts2[i]<<" & ";
              nCEtrs=nCEtrs+m_vNSigDcyIFSts2[i]+m_vNCcSigDcyIFSts2[i];
            }
          else
            {
              nCEtrs=nCEtrs+m_vNSigDcyIFSts2[i];
            }
          fout<<nCEtrs<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigDcyIFSts2.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
    }

  if(m_vPid_sigP.size()>0&&m_anaTasksForSigIds!="T")
    {
      unsigned long nCPs=0;
      for(unsigned int i=0;i<m_vNSigP.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|c|c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal particles.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal particle} & ";
              if(m_sprTopoTags==false) fout<<"iSigP & ";
              fout<<"nPs & ";
              if(m_ccSwitch==true) fout<<"nCcPs & nTotPs & ";
              fout<<"nCPs \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ ";
          writePnmFromPid(fout,"TexPnm",m_vPid_sigP[i]);
          fout<<"$ & ";
          if(m_sprTopoTags==false) fout<<m_vISigP[i]<<" & ";
          fout<<m_vNSigP[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigP[i]>0) fout<<m_vNCcSigP[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigP[i]+m_vNCcSigP[i]<<" & ";
              nCPs=nCPs+m_vNSigP[i]+m_vNCcSigP[i];
            }
          else
            {
              nCPs=nCPs+m_vNSigP[i];
            }
          fout<<nCPs<<" \\EOL"<<endl<<endl;
          if(i==(m_vNSigP.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
    }

  if(m_vSigDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigDcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigDcyBr.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal decay branches.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal decay branch} & ";
              if(m_sprTopoTags==false) fout<<"iSigDcyBr & ";
              fout<<"nCases & ";
              if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & "<<endl;
              fout<<"nCCases \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigDcyBr.clear();
          sigDcyBr=m_vSigDcyBr[i];
          list<int>::iterator liit=sigDcyBr.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }          
          fout<<"\\rightarrow ";
          for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & ";
          if(m_sprTopoTags==false) fout<<m_vISigDcyBr[i]<<" & ";
          fout<<m_vNSigDcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigDcyBr[i]>0) fout<<m_vNCcSigDcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i]<<" & ";
              nCCases=nCCases+m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigDcyBr[i];
            }
          fout<<nCCases<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigDcyBr.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
    }

  if(m_vSigIncDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigIncDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIncDcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigIncDcyBr.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal inclusive decay branches.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal inclusive decay branch} & ";
              if(m_sprTopoTags==false) fout<<"iSigIncDcyBr & ";
              fout<<"nCases & ";
              if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & "<<endl;
              fout<<"nCCases \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigIncDcyBr.clear();
          sigIncDcyBr=m_vSigIncDcyBr[i];
          list<int>::iterator liit=sigIncDcyBr.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }          
          fout<<"\\rightarrow ";
          for(liit++;liit!=sigIncDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<" + \\rm{anything}";
          fout<<"$ & ";
          if(m_sprTopoTags==false) fout<<m_vISigIncDcyBr[i]<<" & ";
          fout<<m_vNSigIncDcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIncDcyBr[i]>0) fout<<m_vNCcSigIncDcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i]<<" & ";
              nCCases=nCCases+m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigIncDcyBr[i];
            }
          fout<<nCCases<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigIncDcyBr.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
    }

  if(m_vSigCascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrsInALine=4;
      else nBrsInALine=5;
      vector< list<int> > sigCascDcyBrs;
      vector<int> vSigCascDcyBrsIdxOfHead;
      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigCascDcyBrs.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigCascDcyBrs.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal cascade decay branches.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal cascade decay branches} & ";
              if(m_sprTopoTags==false) fout<<"iSigCascDcyBrs & ";
              fout<<"nCases & ";
              if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & "<<endl;
              fout<<"nCCases \\\\}"<<endl<<endl;
            }
          sigCascDcyBrs.clear();
          sigCascDcyBrs=m_vSigCascDcyBrs[i];
          vSigCascDcyBrsIdxOfHead=m_vVSigCascDcyBrsIdxOfHead[i];
          unsigned int nVldSigCascDcyBrs=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigCascDcyBrs.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigCascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigCascDcyBrs[j];              
              list<int>::iterator liit=sigDcyBr.begin();
              nVldSigCascDcyBrs++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              if(j==0&&vSigCascDcyBrsIdxOfHead[0]==-1)
              {
                liit++;
                writePnmFromPid(fout,"TexPnm",(*liit));
              }
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(j<(sigCascDcyBrs.size()-1))
                {
                  fout<<","<<endl;
                  if(nVldSigCascDcyBrs%nBrsInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  fout<<endl<<"$ }";
                  break;
                }
            }

          fout<<" & ";
          if(m_sprTopoTags==false) fout<<m_vISigCascDcyBrs[i]<<" & ";
          fout<<m_vNSigCascDcyBrs[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigCascDcyBrs[i]>0) fout<<m_vNCcSigCascDcyBrs[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigCascDcyBrs[i]+m_vNCcSigCascDcyBrs[i]<<" & ";
              nCCases=nCCases+m_vNSigCascDcyBrs[i]+m_vNCcSigCascDcyBrs[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigCascDcyBrs[i];
            }
          fout<<nCCases<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigCascDcyBrs.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
      if(m_ccSwitch==true) nBrsInALine=5;   
    }

  if(m_vSigIncCascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrsInALine=4;
      else nBrsInALine=5;
      vector< list<int> > sigIncCascDcyBrs;
      vector<int> vSigIncCascDcyBrsIdxOfHead;
      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIncCascDcyBrs.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigIncCascDcyBrs.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal inclusive cascade decay branches.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal inclusive cascade decay branches} & ";
              if(m_sprTopoTags==false) fout<<"iSigIncCascDcyBrs & ";
              fout<<"nCases & ";
              if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & "<<endl;
              fout<<"nCCases \\\\}"<<endl<<endl;
            }
          sigIncCascDcyBrs.clear();
          sigIncCascDcyBrs=m_vSigIncCascDcyBrs[i];
          vSigIncCascDcyBrsIdxOfHead=m_vVSigIncCascDcyBrsIdxOfHead[i];
          unsigned int nVldSigIncCascDcyBrs=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigIncCascDcyBrs.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigIncCascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncCascDcyBrs[j];              
              list<int>::iterator liit=sigDcyBr.begin();
              nVldSigIncCascDcyBrs++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              if(j==0&&vSigIncCascDcyBrsIdxOfHead[0]==-1)
              {
                liit++;
                writePnmFromPid(fout,"TexPnm",(*liit));
              }
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(m_vVIIncSigIncCascDcyBrs[i][j]==1) writePnmFromPid(fout,"TexPnm",m_pidOfAnything);
              if(j<(sigIncCascDcyBrs.size()-1))
                {
                  fout<<","<<endl;
                  if(nVldSigIncCascDcyBrs%nBrsInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  fout<<endl<<"$ }";
                  break;
                }
            }

          fout<<" & ";
          if(m_sprTopoTags==false) fout<<m_vISigIncCascDcyBrs[i]<<" & ";
          fout<<m_vNSigIncCascDcyBrs[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIncCascDcyBrs[i]>0) fout<<m_vNCcSigIncCascDcyBrs[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIncCascDcyBrs[i]+m_vNCcSigIncCascDcyBrs[i]<<" & ";
              nCCases=nCCases+m_vNSigIncCascDcyBrs[i]+m_vNCcSigIncCascDcyBrs[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigIncCascDcyBrs[i];
            }
          fout<<nCCases<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigIncCascDcyBrs.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
      if(m_ccSwitch==true) nBrsInALine=5;   
    }

  if(m_vSigIRADcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigIRADcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIRADcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigIRADcyBr.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal intermediate-resonance-allowed decay branches.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal intermediate-resonance-allowed decay branch} & ";
              if(m_sprTopoTags==false) fout<<"iSigIRADcyBr & ";
              fout<<"nCases & ";
              if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & "<<endl;
              fout<<"nCCases \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigIRADcyBr.clear();
          sigIRADcyBr=m_vSigIRADcyBr[i];
          list<int>::iterator liit=sigIRADcyBr.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==-11)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\dashrightarrow ";
          for(liit++;liit!=sigIRADcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & ";
          if(m_sprTopoTags==false) fout<<m_vISigIRADcyBr[i]<<" & ";
          fout<<m_vNSigIRADcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIRADcyBr[i]>0) fout<<m_vNCcSigIRADcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i]<<" & ";
              nCCases=nCCases+m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigIRADcyBr[i];
            }
          fout<<nCCases<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigIRADcyBr.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
    }

  if(m_vSigIncOrIRACascDcyBrs.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrsInALine=4;
      else nBrsInALine=5;
      vector< list<int> > sigIncOrIRACascDcyBrs;
      vector<int> vSigIncOrIRACascDcyBrsIdxOfHead;
      list<int> sigDcyBr;
      unsigned long nCCases=0;
      for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBrs.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{|c|";
              if(m_centDcyObjs==false&&m_vSigIncOrIRACascDcyBrs.size()>1) fout<<"l|";
              else fout<<"c|";
              fout<<"c|c|c|";
              if(m_ccSwitch==true) fout<<"c|c|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal inclusive or intermediate-resonance-allowed cascade decay branches.}"<<endl;
              fout<<"\\tableheader{rowNo & \\thead{signal inclusive or intermediate-resonance-allowed \\\\ cascade decay branches} & ";
              if(m_sprTopoTags==false) fout<<"iSigIncOrIRACascDcyBrs & ";
              fout<<"nCases & ";
              if(m_ccSwitch==true) fout<<"nCcCases & nTotCases & "<<endl;
              fout<<"nCCases \\\\}"<<endl<<endl;
            }
          sigIncOrIRACascDcyBrs.clear();
          sigIncOrIRACascDcyBrs=m_vSigIncOrIRACascDcyBrs[i];
          vSigIncOrIRACascDcyBrsIdxOfHead=m_vVSigIncOrIRACascDcyBrsIdxOfHead[i];
          unsigned int nVldSigIncOrIRACascDcyBrs=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigIncOrIRACascDcyBrs.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigIncOrIRACascDcyBrs.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncOrIRACascDcyBrs[j];              
              list<int>::iterator liit=sigDcyBr.begin();
              nVldSigIncOrIRACascDcyBrs++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              if(j==0&&vSigIncOrIRACascDcyBrsIdxOfHead[0]==-1)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              if(m_vVIIRASigIncOrIRACascDcyBrs[i][j]==1) fout<<"\\; ( \\rightarrow X ) ";
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(m_vVIIncSigIncOrIRACascDcyBrs[i][j]==1) writePnmFromPid(fout,"TexPnm",m_pidOfAnything);
              // The following bool variable is used to judge whether the current branch is the last one outputed or not.
              if(j<(sigIncOrIRACascDcyBrs.size()-1))
                {
                  fout<<","<<endl;
                  if(nVldSigIncOrIRACascDcyBrs%nBrsInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  fout<<endl<<"$ }";
                  break;
                }
            }

          fout<<" & ";
          if(m_sprTopoTags==false) fout<<m_vISigIncOrIRACascDcyBrs[i]<<" & ";
          fout<<m_vNSigIncOrIRACascDcyBrs[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIncOrIRACascDcyBrs[i]>0) fout<<m_vNCcSigIncOrIRACascDcyBrs[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIncOrIRACascDcyBrs[i]+m_vNCcSigIncOrIRACascDcyBrs[i]<<" & ";
              nCCases=nCCases+m_vNSigIncOrIRACascDcyBrs[i]+m_vNCcSigIncOrIRACascDcyBrs[i];
            }
          else
            {
              nCCases=nCCases+m_vNSigIncOrIRACascDcyBrs[i];
            }
          fout<<nCCases<<" \\EOL"<<endl<<endl;
          if(i==(m_vSigIncOrIRACascDcyBrs.size()-1)) fout<<"\\end{longtable}"<<endl;
        }
      if(m_ccSwitch==true) nBrsInALine=5;   
    }

  fout<<"\\end{document}"<<endl;

}
