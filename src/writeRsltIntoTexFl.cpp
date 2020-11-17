#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

void topoana::writeRsltIntoTexFl()
{
  if(m_anaTasksForSigIds=="T"&&m_vPid_compDcyBrP.size()==0&&m_vPid_compCascDcyBrP.size()==0&&m_vPid_compDcyFStP.size()==0&&m_vPid_compProdBrP.size()==0&&m_vPid_compMP.size()==0&&m_vCompIncDcyBr.size()==0&&m_vCompIRADcyBr.size()==0&&m_compAnaOfDcyTrs==false&&m_compAnaOfDcyIFSts==false) return;

  string NmOfOptTexFl=m_comNmOfOptFls+".tex";
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
  fout<<"\\usepackage{amssymb} % The package is used for the \\dashrightarrow"<<endl; 
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
  if(m_cmpltHVLines==false)
    {
      fout<<"% The following command \\tableheaderP is developed as a substitute for \\tableheader, in cases that hlines are needed at the bottom of the pages (except for the last one) of the tables when \\EOL is defined and used as \\\\ with no \\hline followed. In the command \\tableheaderP, P is the initial of PRIME."<<endl;
      fout<<"\\newcommand{\\tableheaderP}[1]"<<endl;
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
      fout<<"  \\hline % This is the only difference between \\tableheader and \\tableheaderP."<<endl;
      fout<<"  \\endfoot"<<endl;
      fout<<endl;
      fout<<"  \\endlastfoot"<<endl;
      fout<<"}"<<endl;
    }
  fout<<"\\setcellgapes[t]{2pt}"<<endl;
  fout<<"\\makegapedcells"<<endl;
  fout<<"\\newcounter{rownumbers}"<<endl;
  fout<<"\\newcommand\\rn{\\stepcounter{rownumbers}\\arabic{rownumbers}}"<<endl;
  if(m_cmpltHVLines==false) fout<<"% ";
  fout<<"\\newcommand{\\EOL}{\\\\ \\hline} % Use this definition to retain hlines in the body part."<<endl;
  if(m_cmpltHVLines==true) fout<<"% ";
  fout<<"\\newcommand{\\EOL}{\\\\} % Use this definition to remove hlines in the body part."<<endl;
  if(m_cmpltHVLines==false)
    {
      fout<<"% The following command \\EOLP is developed as a supplementary to \\EOL, in cases that hlines are needed in some tables (nLineMean>2, the average number of lines occupied by one decay object is larger than two) when \\EOL is only defined as \\\\ with no \\hline followed for other tables. In the command \\EOLP, P is the initial of PRIME."<<endl;
      fout<<"\\newcommand{\\EOLP}{\\\\ \\hline} % Use this definition to retain hlines in the body part."<<endl;
      fout<<"% \\newcommand{\\EOLP}{\\\\} % Use this definition to remove hlines in the body part."<<endl;
    }
  fout<<"\\newcommand{\\topoTags}[1]{#1} % Use this definition to retain topology tags."<<endl;
  fout<<"% \\newcommand{\\topoTags}[1]{} % Use this definition to remove topology tags."<<endl;
  fout<<"\\begin{document}"<<endl;
  fout<<"\\title{Topology Analysis \\footnote{\\small{Xingyu Zhou, Beihang University, zhouxy@buaa.edu.cn}} \\footnote{\\small{This package is implemented referring to a program called {\\sc Topo}, which is first developed by Prof. Shuxian Du from Zhengzhou University and later extended and maintained by Prof. Gang Li from Institute of High Energy Physics, Chinese Academy of Sciences. The {\\sc Topo} program has been widely used by colleagues in BESIII collaboration. Several years ago, when I was a Ph.D. student working on the BESIII experiment, I learned the idea of topology analysis and a lot of programming techniques from the {\\sc Topo} program. So, I really appreciate the original works of Prof. Du and Prof. Li very much. To meet my own needs and to practice developing analysis tools with C++, ROOT, and LaTeX, I wrote the package from scratch. At that time, the package functioned well but was relatively simple. At the end of 2017, my co-supervisor, Prof. Chengping Shen reminded me that it could be a useful tool for the Belle II experiment as well. So, I revised and extended it, making it more well-rounded and suitable for the Belle II experiment. Now, it also applies to many other similar high energy physics experiments. Here, I would like to thank Prof. Du and Prof. Li for their original works, and Prof. Shen for his suggestion, guidance, support, and encouragement.}} \\footnote{\\small{Besides, I would like to thank all of the people who have helped me in the development of the program. I am particularly grateful to Prof. Xingtao Huang for his comments on the principles and styles of the program, to Remco de Boer for his suggestions on the tex output and the use of GitHub, and to Xi Chen for his discussions on the core algorithms. I am especially indebted to Prof. Xiqing Hao, Longke Li, Xiaoping Qin, Ilya Komarov, Yubo Li, Guanda Gong, Suxian Li, Junhao Yin, Prof. Xiaolong Wang, Yeqi Chen, Hannah Wakeling, Hongrong Qi, Hui Li, Ning Cao, Sanjeeda Bharati Das, Kazuki Kojima, Tingting Han, Fang Yan, and Lin Wang for their advice in extending and perfecting the program. Also, I thank Xi'an Xiong, Runqiu Ma, Wencheng Yan, Sen Jia, Lu Cao, Dong Liu, Hongpeng Wang, Jiawei Zhang, Jiajun Liu, Maoqiang Jing, Yi Zhang, Wei Shan, and Yadi Wang for their efforts in helping me test the program.}} \\footnote{\\small{The paper on the tool has been published by {\\it Computer Physics Communications}. You can find this paper and the preprint corresponding to it in the links \\href{https://doi.org/10.1016/j.cpc.2020.107540}{Comput. Phys. Commun. 258 (2021) 107540} and \\href{https://arxiv.org/abs/2001.04016}{arXiv:2001.04016}, respectively. If the tool really helps your researches, we would appreciate it very much if you could cite the paper in your publications.}} \\\\ \\vspace{1cm} \\Large{("<<m_verNum<<")}}"<<endl;
  fout<<"\\maketitle"<<endl;
  fout<<endl<<"\\clearpage"<<endl<<endl;
  fout<<"\\newgeometry{left=2.5cm,right=2.5cm,top=2.5cm,bottom=2.5cm}"<<endl<<endl;
  fout<<"\\listoftables"<<endl<<endl;
  fout<<"\\newgeometry{left=0.0cm,right=0.0cm,top=2.5cm,bottom=2.5cm}"<<endl;
  unsigned int nBrInALine;
  unsigned int nVldDcyBr;
  double nLineMean;
  unsigned long nCEtr;

  if(m_compAnaOfDcyTrs==true)
    {
      if(m_ccSwitch==true) nBrInALine=5;
      else nBrInALine=6;
      if(m_dcyIFStsUnderDcyTr==false) nBrInALine--;
      vector< list<int> > dcyTr;
      list<int> dcyBr;
      list<int> dcyIFSts;
      vector<int> vIMDcyBr;
      nCEtr=0;
      bool isSigDcyTr;
      unsigned int iSigDcyTr=0;
      unsigned long nDcyTrsToBePrtd=m_vDcyTr.size()<m_nDcyTrsToBePrtdMax?m_vDcyTr.size():m_nDcyTrsToBePrtdMax;
      nLineMean=0;
      for(unsigned long i=0;i<nDcyTrsToBePrtd;i++) nLineMean=nLineMean+m_vDcyTr[i].size();
      nLineMean=nLineMean/nDcyTrsToBePrtd/nBrInALine;
      if(m_dcyIFStsUnderDcyTr==true) nLineMean=nLineMean+1;
      for(unsigned long i=0;i<nDcyTrsToBePrtd;i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|";
              if(m_dcyIFStsUnderDcyTr==false)
                {
                  if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                }
              if(m_cmpltHVLines==true) fout<<"c|c|c|c|";
              else fout<<"cccc";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Decay trees and their respective ";
              if(m_dcyIFStsUnderDcyTr==false) fout<<"final";
              else fout<<"initial-final";
              fout<<" states.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false&&nLineMean<=2) fout<<"P";
              fout<<"{rowNo & ";
              if(m_dcyIFStsUnderDcyTr==false) fout<<"\\thead{decay tree} & \\thead{decay final state}";
              else fout<<"\\thead{decay tree \\\\ (decay initial-final states)}";
              fout<<" & \\topoTags{iDcyTr & ";
              if(m_compAnaOfDcyIFSts==true) fout<<"iDcyIFSts & ";
              fout<<"}nEtr & ";
              if(m_ccSwitch==true) fout<<"nCcEtr & nAllEtr & ";
              fout<<"nCEtr \\\\}"<<endl<<endl;
            }
          dcyTr.clear();
          dcyTr=m_vDcyTr[i];
          if(m_optIdxAndMidxOfDcyBrInDcyTr==true) getVIMDcyBr(dcyTr,vIMDcyBr);
          nVldDcyBr=0;
          fout<<"% \\rn = "<<i+1<<endl;
          isSigDcyTr=false;
          for(;iSigDcyTr<m_vISigDcyTr.size();iSigDcyTr++)
            {
              if(m_vIDcyTr[i]==m_iSigDcyTrIDcyTrMap[iSigDcyTr])
                {
                  isSigDcyTr=true;
                  iSigDcyTr++;
                  break;
                }
            }
          if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
          fout<<"\\rn ";
          if(isSigDcyTr==true) fout<<"}} ";
          fout<<"& ";
          if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
          fout<<"\\makecell[";
          if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<dcyTr.size();j++)
            {
              dcyBr.clear();
              dcyBr=dcyTr[j];
              list<int>::iterator liit=dcyBr.begin();
              nVldDcyBr++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              // The condition "j==0&&((*liit)==m_pidOfISt2)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==m_pidOfISt2))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=dcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(m_optIdxAndMidxOfDcyBrInDcyTr==true) fout<<"\\, {\\footnotesize ["<<j<<","<<vIMDcyBr[j]<<"]}"<<" ";
              if((j+1)!=dcyTr.size())
                {
                  fout<<","<<endl;
                  if(nVldDcyBr%nBrInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  if(m_dcyIFStsUnderDcyTr==false) 
                    {
                      fout<<endl<<"$ } ";
                      if(isSigDcyTr==true) fout<<"}} ";
                      fout<<"& ";
                      if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
                      fout<<"$"<<endl;
                    }
                  else fout<<endl<<"$ \\\\ ($"<<endl;
                  break;
                }
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
          list<int>::iterator liit=dcyIFSts.begin();
          if(m_dcyIFStsUnderDcyTr==true) writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              if(m_dcyIFStsUnderDcyTr==true) writePnmFromPid(fout,"TexPnm",(*liit));
            }
          if(m_dcyIFStsUnderDcyTr==true) fout<<"\\dashrightarrow ";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          if(m_dcyIFStsUnderDcyTr==false) fout<<endl<<"$ ";
          else fout<<endl<<"$) } ";
          if(isSigDcyTr==true) fout<<"}} ";
          fout<<"& \\topoTags{";
          if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
          fout<<m_vIDcyTr[i]<<" ";
          if(isSigDcyTr==true) fout<<"}} ";
          fout<<"& ";
          if(m_compAnaOfDcyIFSts==true) 
            {
              if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
              fout<<m_iDcyTrIDcyIFStsMap[m_vIDcyTr[i]]<<" ";
              if(isSigDcyTr==true) fout<<"}} ";
              fout<<"& ";
            }
          fout<<"}";
          if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
          fout<<m_vNDcyTr[i]<<" ";
          if(isSigDcyTr==true) fout<<"}} ";
          fout<<"& ";
          if(m_ccSwitch==true)
            {
              if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
              if(m_vICcDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcDcyTr[i];
              fout<<" ";
              if(isSigDcyTr==true) fout<<"}} ";
              fout<<"& ";
              if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
              fout<<m_vNDcyTr[i]+m_vNCcDcyTr[i]<<" ";
              if(isSigDcyTr==true) fout<<"}} ";
              fout<<"& ";
              nCEtr=nCEtr+m_vNDcyTr[i]+m_vNCcDcyTr[i];          
            }
          else
            {
              nCEtr=nCEtr+m_vNDcyTr[i];
            }
          if(isSigDcyTr==true) fout<<"{\\color{blue}{ ";
          fout<<nCEtr<<" ";
          if(isSigDcyTr==true) fout<<"}} ";
          if((i==nDcyTrsToBePrtd-1)&&(nDcyTrsToBePrtd==m_vDcyTr.size())) fout<<"\\\\ \\hline"<<endl<<endl;
          else
            {
              if(m_cmpltHVLines==false&&nLineMean>2) fout<<"\\EOLP"<<endl<<endl;
              else fout<<"\\EOL"<<endl<<endl;
            }
          if(i==nDcyTrsToBePrtd-1)
            {
              if(nDcyTrsToBePrtd<m_vDcyTr.size())
                {
                  fout<<"rest & \\makecell[";
                  if(m_centDcyObjs==false&&nDcyTrsToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  fout<<"]{ $ "<<endl;
                  if(m_iStPsSwitch==true)
                    {
                      writePnmFromPid(fout,"TexPnm",m_pidOfISt2);
                      writePnmFromPid(fout,"TexPnm",m_pidOfISt1);
                      fout<<"\\rightarrow \\rm{others \\  ("<<m_vDcyTr.size()-nDcyTrsToBePrtd<<" \\  in \\  total)}";
                      if(m_dcyIFStsUnderDcyTr==false) fout<<endl<<"$ } & $"<<endl;
                      else fout<<endl<<"$ \\\\ ($"<<endl;
                      if(m_dcyIFStsUnderDcyTr==true) writePnmFromPid(fout,"TexPnm",m_pidOfISt2);
                      if(m_dcyIFStsUnderDcyTr==true) writePnmFromPid(fout,"TexPnm",m_pidOfISt1);
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
                          writePnmFromPid(fout,"TexPnm",pid);
                          fout<<"\\rightarrow \\rm{others \\  ("<<m_vDcyTr.size()-nDcyTrsToBePrtd<<" \\  in \\  total)}";
                          if(m_dcyIFStsUnderDcyTr==false) fout<<endl<<"$ } & $"<<endl;
                          else fout<<endl<<"$ \\\\ ($"<<endl;
                          if(m_dcyIFStsUnderDcyTr==true) writePnmFromPid(fout,"TexPnm",pid);
                        }
                      else
                        {
                          writePnmFromPid(fout,"TexPnm",m_pidOfISt2);
                          writePnmFromPid(fout,"TexPnm",m_pidOfISt1);
                          fout<<"\\rightarrow \\rm{others \\  ("<<m_vDcyTr.size()-nDcyTrsToBePrtd<<" \\  in \\  total)}";
                          if(m_dcyIFStsUnderDcyTr==false) fout<<endl<<"$ } & $"<<endl;
                          else fout<<endl<<"$ \\\\ ($"<<endl;
                          if(m_dcyIFStsUnderDcyTr==true) writePnmFromPid(fout,"TexPnm",m_pidOfISt2);
                          if(m_dcyIFStsUnderDcyTr==true) writePnmFromPid(fout,"TexPnm",m_pidOfISt1);
                        }
                    }
                  if(m_dcyIFStsUnderDcyTr==true) fout<<"\\dashrightarrow ";
                  fout<<"\\rm{corresponding\\ to\\ others}"<<endl;
                  if(m_dcyIFStsUnderDcyTr==false) fout<<"$ & ";
                  else fout<<"$) } & ";
                  fout<<"\\topoTags{--- & ";
                  if(m_compAnaOfDcyIFSts==true) fout<<"--- & ";
                  fout<<"}";
                  unsigned long nCEtrOfRest=0;
                  if(m_ccSwitch==true)
                    {
                      fout<<"--- & --- & ";
                      for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyTr[i]+m_vNCcDcyTr[i];
                    }
                  else
                    {
                      for(unsigned long i=nDcyTrsToBePrtd;i<m_vDcyTr.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyTr[i];
                    }
                  nCEtr=nCEtr+nCEtrOfRest;
                  fout<<nCEtrOfRest<<" & "<<nCEtr<<" \\\\ \\hline"<<endl<<endl;
                }
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_compAnaOfDcyIFSts==true)
    {
      if(m_ccSwitch==true) nBrInALine=6;

      //list<int> dcyIFSts; The list<int> variable dcyIFSts has been previously declared.
      list<int> dcyIFSts;
      nCEtr=0;
      bool isSigDcyIFSts_tr;
      unsigned int iSigDcyIFSts_tr=0;
      unsigned long nDcyIFStsToBePrtd=m_vDcyIFSts.size()<m_nDcyIFStsToBePrtdMax?m_vDcyIFSts.size():m_nDcyIFStsToBePrtdMax;
      for(unsigned long i=0;i<nDcyIFStsToBePrtd;i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&nDcyIFStsToBePrtd>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|";
              else fout<<"ccc";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Decay initial-final states.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false) fout<<"P";
              fout<<"{rowNo & \\thead{decay initial-final states} & \\topoTags{iDcyIFSts & }nEtr & ";
              if(m_ccSwitch==true) fout<<"nCcEtr & nAllEtr & ";
              fout<<"nCEtr \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          isSigDcyIFSts_tr=false;
          for(;iSigDcyIFSts_tr<m_vISigDcyIFSts_tr.size();iSigDcyIFSts_tr++)
            {
              if(m_vIDcyIFSts[i]==m_iSigDcyIFStsIDcyIFStsMap[iSigDcyIFSts_tr])
                {
                  isSigDcyIFSts_tr=true;
                  iSigDcyIFSts_tr++;
                  break;
                }
            }
          if(isSigDcyIFSts_tr==true) fout<<"{\\color{blue}{ ";
          fout<<"\\rn ";
          if(isSigDcyIFSts_tr==true) fout<<"}} ";
          fout<<"& ";
          if(isSigDcyIFSts_tr==true) fout<<"{\\color{blue}{ ";
          fout<<"$ "; 
          dcyIFSts.clear();
          dcyIFSts=m_vDcyIFSts[i];
          list<int>::iterator liit=dcyIFSts.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\dashrightarrow ";
          for(liit++;liit!=dcyIFSts.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ ";
          if(isSigDcyIFSts_tr==true) fout<<"}} ";
          fout<<"& \\topoTags{";
          if(isSigDcyIFSts_tr==true) fout<<"{\\color{blue}{ ";
          fout<<m_vIDcyIFSts[i]<<" ";
          if(isSigDcyIFSts_tr==true) fout<<"}} ";
          fout<<"& }";
          if(isSigDcyIFSts_tr==true) fout<<"{\\color{blue}{ ";
          fout<<m_vNDcyIFSts[i]<<" ";
          if(isSigDcyIFSts_tr==true) fout<<"}} ";
          fout<<"& ";
          if(m_ccSwitch==true)
            {
              if(isSigDcyIFSts_tr==true) fout<<"{\\color{blue}{ ";
              if(m_vICcDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcDcyIFSts[i];
              fout<<" ";
              if(isSigDcyIFSts_tr==true) fout<<"}} ";
              fout<<"& ";
              if(isSigDcyIFSts_tr==true) fout<<"{\\color{blue}{ ";
              fout<<m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i]<<" ";
              if(isSigDcyIFSts_tr==true) fout<<"}} ";
              fout<<"& ";
              nCEtr=nCEtr+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
            }
          else
            {
              nCEtr=nCEtr+m_vNDcyIFSts[i];
            }
          if(isSigDcyIFSts_tr==true) fout<<"{\\color{blue}{ ";
          fout<<nCEtr<<" ";
          if(isSigDcyIFSts_tr==true) fout<<"}} ";
          if((i==nDcyIFStsToBePrtd-1)&&(nDcyIFStsToBePrtd==m_vDcyIFSts.size())) fout<<"\\\\ \\hline"<<endl<<endl;
          else fout<<"\\EOL"<<endl<<endl;
          if(i==nDcyIFStsToBePrtd-1)
            {
              if(nDcyIFStsToBePrtd<m_vDcyIFSts.size())
                {
                  fout<<"rest & $ ";
                  list<int>::iterator liit=dcyIFSts.begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==m_pidOfISt2)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\dashrightarrow \\rm{others \\  ("<<m_vDcyIFSts.size()-nDcyIFStsToBePrtd<<" \\  in \\  total)} $ & \\topoTags{--- & }";
                  unsigned long nCEtrOfRest=0;
                  if(m_ccSwitch==true)
                    {
                      fout<<"--- & --- & ";
                      for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyIFSts[i]+m_vNCcDcyIFSts[i];
                    }
                  else
                    {
                      for(unsigned long i=nDcyIFStsToBePrtd;i<m_vDcyIFSts.size();i++) nCEtrOfRest=nCEtrOfRest+m_vNDcyIFSts[i];
                    }
                  nCEtr=nCEtr+nCEtrOfRest;
                  fout<<nCEtrOfRest<<" & "<<nCEtr<<" \\\\ \\hline"<<endl<<endl;
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
          unsigned long nCCase=0;
          unsigned long nDcyBrPToBePrtd=m_vVDcyBrP[i].size()<m_vNDcyBrToBePrtdMax[i]?m_vVDcyBrP[i].size():m_vNDcyBrToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_centDcyObjs==false&&nDcyBrPToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|c|c|c|";
                  else fout<<"ccc";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Decay branches of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compDcyBrP[i]);
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false) fout<<"P";
                  fout<<"{rowNo & \\thead{decay branch of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compDcyBrP[i]);
                  fout<<"$} & \\topoTags{iDcyBrP & }nCase & ";
                  if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
                  fout<<"nCCase \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              dcyBrP.clear();
              dcyBrP=m_vVDcyBrP[i][j];
              list<int>::iterator liit=dcyBrP.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"\\rightarrow ";
              for(liit++;liit!=dcyBrP.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"$ & \\topoTags{"<<m_vVIDcyBrP[i][j]<<" & }"<<m_vVNDcyBrP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompDcyBrP[i]==0&&m_vVIDcyBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcP[i][j];
                  fout<<" & "<<m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j]<<" & ";
                  nCCase=nCCase+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyBrP[i][j];
                }
              if((j==nDcyBrPToBePrtd-1)&&(nDcyBrPToBePrtd==m_vVDcyBrP[i].size())) fout<<nCCase<<" \\\\ \\hline"<<endl<<endl;
              else fout<<nCCase<<" \\EOL"<<endl<<endl;
              if(j==nDcyBrPToBePrtd-1)
                {
                  if(nDcyBrPToBePrtd<m_vVDcyBrP[i].size())
                    {
                      fout<<"rest & $ ";
                      dcyBrP.clear();
                      dcyBrP=m_vVDcyBrP[i][j];
                      list<int>::iterator liit=dcyBrP.begin();
                      writePnmFromPid(fout,"TexPnm",(*liit));
                      fout<<"\\rightarrow \\rm{others \\  ("<<m_vVDcyBrP[i].size()-nDcyBrPToBePrtd<<" \\  in \\  total)} $ & \\topoTags{--- & }";
                      unsigned long nCCaseOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompDcyBrP[i]==0)
                            {
                              fout<<"--- & --- & ";
                            }
                          else
                            {
                              unsigned long nCCaseOfRestTemp1=0;
                              unsigned long nCCaseOfRestTemp2=0;
                              for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyBrP[i][j];
                              for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyBrCcP[i][j];
                              fout<<nCCaseOfRestTemp1<<" & "<<nCCaseOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrP[i][j]+m_vVNDcyBrCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nDcyBrPToBePrtd;j<m_vVDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrP[i][j];
                        }
                      nCCase=nCCase+nCCaseOfRest;
                      fout<<nCCaseOfRest<<" & "<<nCCase<<" \\\\ \\hline"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vVCascDcyBrP.size()>0)
    {
      if(m_ccSwitch==true) nBrInALine=4;
      else nBrInALine=5;
      for(unsigned int i=0;i<m_vVCascDcyBrP.size();i++)
        {
          vector< list<int> > cascDcyBrP;
          // vector<int> vCascDcyBrIdxOfHead;
          list<int> dcyBrP;
          vector<int> vIMDcyBr;
          unsigned long nCCase=0;
          unsigned long nCascDcyBrPToBePrtd=m_vVCascDcyBrP[i].size()<m_vNCascDcyBrToBePrtdMax[i]?m_vVCascDcyBrP[i].size():m_vNCascDcyBrToBePrtdMax[i];
          nLineMean=0;
          for(unsigned long j=0;j<nCascDcyBrPToBePrtd;j++) nLineMean=nLineMean+m_vVCascDcyBrP[i][j].size();
          nLineMean=nLineMean/nCascDcyBrPToBePrtd/nBrInALine;
          for(unsigned int j=0;j<nCascDcyBrPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_centDcyObjs==false&&nCascDcyBrPToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|c|c|c|";
                  else fout<<"ccc";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Cascade decay branches of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compCascDcyBrP[i]);
                  fout<<"$";
                  if(m_vHCascDcyBrMax[i]!=ULONG_MAX)
                    {
                      fout<<" (only the first ";
                      if(m_nNmMap.find(m_vHCascDcyBrMax[i])!=m_nNmMap.end()) fout<<m_nNmMap[m_vHCascDcyBrMax[i]];
                      else fout<<m_vHCascDcyBrMax[i];
                      fout<<" hierarchies are involved)";
                    }
                  fout<<".}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false&&nLineMean<=2) fout<<"P";
                  fout<<"{rowNo & \\thead{cascade decay branch of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compCascDcyBrP[i]);
                  fout<<"$} & \\topoTags{iCascDcyBrP & }nCase & ";
                  if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
                  fout<<"nCCase \\\\}"<<endl<<endl;
                }
              cascDcyBrP.clear();
              cascDcyBrP=m_vVCascDcyBrP[i][j];
              if(m_vOptIdxAndMidxOfDcyBrInCascDcyBrP[i]==true) getVIMDcyBr(cascDcyBrP,vIMDcyBr);
              nVldDcyBr=0;
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & \\makecell[";
              if(m_centDcyObjs==false&&m_vVCascDcyBrP[i].size()>1) fout<<"l";
              else fout<<"c";
              fout<<"]{ $ "<<endl;
              for(unsigned int k=0;k<cascDcyBrP.size();k++)
                {
                  dcyBrP.clear();
                  dcyBrP=cascDcyBrP[k];              
                  list<int>::iterator liit=dcyBrP.begin();
                  nVldDcyBr++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"\\rightarrow ";
                  for(liit++;liit!=dcyBrP.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  if(m_vOptIdxAndMidxOfDcyBrInCascDcyBrP[i]==true) fout<<"\\, {\\footnotesize ["<<k<<","<<vIMDcyBr[k]<<"]}"<<" ";
                  if(k<(cascDcyBrP.size()-1))
                    {
                      fout<<","<<endl;
                      if(nVldDcyBr%nBrInALine==0) fout<<"$ \\\\ $"<<endl;
                    }
                  else
                    {
                      fout<<endl<<"$ }";
                      break;
                    }
                }

              fout<<" & \\topoTags{"<<m_vVICascDcyBrP[i][j]<<" & }"<<m_vVNCascDcyBrP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompCascDcyBrP[i]==0&&m_vVICascDcyBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNCascDcyBrCcP[i][j];
                  fout<<" & "<<m_vVNCascDcyBrP[i][j]+m_vVNCascDcyBrCcP[i][j]<<" & ";
                  nCCase=nCCase+m_vVNCascDcyBrP[i][j]+m_vVNCascDcyBrCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNCascDcyBrP[i][j];
                }
              if((j==nCascDcyBrPToBePrtd-1)&&(nCascDcyBrPToBePrtd==m_vVCascDcyBrP[i].size())) fout<<nCCase<<" \\\\ \\hline"<<endl<<endl;
              else
                {
                  if(m_cmpltHVLines==false&&nLineMean>2) fout<<nCCase<<" \\EOLP"<<endl<<endl;
                  else fout<<nCCase<<" \\EOL"<<endl<<endl;
                }
              if(j==nCascDcyBrPToBePrtd-1)
                {
                  if(nCascDcyBrPToBePrtd<m_vVCascDcyBrP[i].size())
                    {
                      fout<<"rest & $ ";
                      writePnmFromPid(fout,"TexPnm",m_vPid_compCascDcyBrP[i]);
                      fout<<"\\rightarrow \\rm{others \\  ("<<m_vVCascDcyBrP[i].size()-nCascDcyBrPToBePrtd<<" \\  in \\  total)} $ & \\topoTags{--- & }";
                      unsigned long nCCaseOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompCascDcyBrP[i]==0)
                            {
                              fout<<"--- & --- & ";
                            }
                          else
                            {
                              unsigned long nCCaseOfRestTemp1=0;
                              unsigned long nCCaseOfRestTemp2=0;
                              for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNCascDcyBrP[i][j];
                              for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNCascDcyBrCcP[i][j];
                              fout<<nCCaseOfRestTemp1<<" & "<<nCCaseOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNCascDcyBrP[i][j]+m_vVNCascDcyBrCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nCascDcyBrPToBePrtd;j<m_vVCascDcyBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNCascDcyBrP[i][j];
                        }
                      nCCase=nCCase+nCCaseOfRest;
                      fout<<nCCaseOfRest<<" & "<<nCCase<<" \\\\ \\hline"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vVDcyFStP.size()>0)
    {
      for(unsigned int i=0;i<m_vVDcyFStP.size();i++)
        {
          list<int> dcyFStP;
          unsigned long nCCase=0;
          unsigned long nDcyFStPToBePrtd=m_vVDcyFStP[i].size()<m_vNDcyFStToBePrtdMax[i]?m_vVDcyFStP[i].size():m_vNDcyFStToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyFStPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_centDcyObjs==false&&nDcyFStPToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|c|c|c|";
                  else fout<<"ccc";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Decay final states of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compDcyFStP[i]);
                  fout<<"$";
                  if(m_vNDcyFStP[i]!=ULONG_MAX)
                    {
                      fout<<" (only ";
                      if(m_nNmMap.find(m_vNDcyFStP[i])!=m_nNmMap.end()) fout<<m_nNmMap[m_vNDcyFStP[i]];
                      else fout<<m_vNDcyFStP[i];
                      fout<<"-body final states are involved)";
                    }
                  fout<<".}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false) fout<<"P";
                  fout<<"{rowNo & \\thead{decay final state of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compDcyFStP[i]);
                  fout<<"$} & \\topoTags{iDcyFStP & }nCase & ";
                  if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
                  fout<<"nCCase \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              dcyFStP.clear();
              dcyFStP=m_vVDcyFStP[i][j];
              list<int>::iterator liit=dcyFStP.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"\\dashrightarrow ";
              for(liit++;liit!=dcyFStP.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"$ & \\topoTags{"<<m_vVIDcyFStP[i][j]<<" & }"<<m_vVNDcyFStP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompDcyFStP[i]==0&&m_vVIDcyFStCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyFStCcP[i][j];
                  fout<<" & "<<m_vVNDcyFStP[i][j]+m_vVNDcyFStCcP[i][j]<<" & ";
                  nCCase=nCCase+m_vVNDcyFStP[i][j]+m_vVNDcyFStCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyFStP[i][j];
                }
              if((j==nDcyFStPToBePrtd-1)&&(nDcyFStPToBePrtd==m_vVDcyFStP[i].size())) fout<<nCCase<<" \\\\ \\hline"<<endl<<endl;
              else fout<<nCCase<<" \\EOL"<<endl<<endl;
              if(j==nDcyFStPToBePrtd-1)
                {
                  if(nDcyFStPToBePrtd<m_vVDcyFStP[i].size())
                    {
                      fout<<"rest & $ ";
                      dcyFStP.clear();
                      dcyFStP=m_vVDcyFStP[i][j];
                      list<int>::iterator liit=dcyFStP.begin();
                      writePnmFromPid(fout,"TexPnm",(*liit));
                      fout<<"\\dashrightarrow \\rm{others \\  ("<<m_vVDcyFStP[i].size()-nDcyFStPToBePrtd<<" \\  in \\  total)} $ & \\topoTags{--- & }";
                      unsigned long nCCaseOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompDcyFStP[i]==0)
                            {
                              fout<<"--- & --- & ";
                            }
                          else
                            {
                              unsigned long nCCaseOfRestTemp1=0;
                              unsigned long nCCaseOfRestTemp2=0;
                              for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyFStP[i][j];
                              for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyFStCcP[i][j];
                              fout<<nCCaseOfRestTemp1<<" & "<<nCCaseOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyFStP[i][j]+m_vVNDcyFStCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nDcyFStPToBePrtd;j<m_vVDcyFStP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyFStP[i][j];
                        }
                      nCCase=nCCase+nCCaseOfRest;
                      fout<<nCCaseOfRest<<" & "<<nCCase<<" \\\\ \\hline"<<endl<<endl;
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
          unsigned long nCCase=0;
          unsigned long nProdBrPToBePrtd=m_vVProdBrP[i].size()<m_vNProdBrToBePrtdMax[i]?m_vVProdBrP[i].size():m_vNProdBrToBePrtdMax[i];
          for(unsigned int j=0;j<nProdBrPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_centDcyObjs==false&&nProdBrPToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|c|c|c|";
                  else fout<<"ccc";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Production branches of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compProdBrP[i]);
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false) fout<<"P";
                  fout<<"{rowNo & \\thead{production branch of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compProdBrP[i]);
                  fout<<"$} & \\topoTags{iProdBrP & }nCase & ";
                  if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
                  fout<<"nCCase \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              prodBrP.clear();
              prodBrP=m_vVProdBrP[i][j];
              list<int>::iterator liit=prodBrP.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=prodBrP.end();liit++)
                {
                  if(((*liit)==m_vPid_compProdBrP[i])||((m_ccSwitch==true)&&((*liit)==m_vPid_ccCompProdBrP[i]))) fout<<"{\\color{blue}{ ";
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if(((*liit)==m_vPid_compProdBrP[i])||((m_ccSwitch==true)&&((*liit)==m_vPid_ccCompProdBrP[i]))) fout<<"}} ";
                }
              fout<<"$ & \\topoTags{"<<m_vVIProdBrP[i][j]<<" & }"<<m_vVNProdBrP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompProdBrP[i]==0&&m_vVIProdBrCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNProdBrCcP[i][j];
                  fout<<" & "<<m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j]<<" & ";
                  nCCase=nCCase+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNProdBrP[i][j];
                }
              if((j==nProdBrPToBePrtd-1)&&(nProdBrPToBePrtd==m_vVProdBrP[i].size())) fout<<nCCase<<" \\\\ \\hline"<<endl<<endl;
              else fout<<nCCase<<" \\EOL"<<endl<<endl;
              if(j==nProdBrPToBePrtd-1)
                {
                  if(nProdBrPToBePrtd<m_vVProdBrP[i].size())
                    {
                      fout<<"rest & others \\  ("<<m_vVProdBrP[i].size()-nProdBrPToBePrtd<<" \\  in \\  total) & \\topoTags{--- & }";
                      unsigned long nCCaseOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompProdBrP[i]==0)
                            {
                              fout<<"--- & --- & ";
                            }
                          else
                            {
                              unsigned long nCCaseOfRestTemp1=0;
                              unsigned long nCCaseOfRestTemp2=0;
                              for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNProdBrP[i][j];
                              for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNProdBrCcP[i][j];
                              fout<<nCCaseOfRestTemp1<<" & "<<nCCaseOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNProdBrP[i][j]+m_vVNProdBrCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nProdBrPToBePrtd;j<m_vVProdBrP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNProdBrP[i][j];
                        }
                      nCCase=nCCase+nCCaseOfRest;
                      fout<<nCCaseOfRest<<" & "<<nCCase<<" \\\\ \\hline"<<endl<<endl;
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
          unsigned long nCCase=0;
          unsigned long nMPToBePrtd=m_vVMpidP[i].size()<m_vNMToBePrtdMax[i]?m_vVMpidP[i].size():m_vNMToBePrtdMax[i];
          for(unsigned int j=0;j<nMPToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|c|c|c|c|";
                  else fout<<"ccccc";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Mothers of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compMP[i]);
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false) fout<<"P";
                  fout<<"{rowNo & \\thead{mother of $ ";
                  writePnmFromPid(fout,"TexPnm",m_vPid_compMP[i]);
                  fout<<"$} & \\topoTags{PDGMoth & }nCase & ";
                  if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
                  fout<<"nCCase \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              writePnmFromPid(fout,"TexPnm",m_vVMpidP[i][j]);
              fout<<"$ & \\topoTags{$ "<<m_vVMpidP[i][j]<<" $ & }"<<m_vVNMP[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompMP[i]==0&&m_vVIMCcP[i][j]==0) fout<<"---";
                  else fout<<m_vVNMCcP[i][j];
                  fout<<" & "<<m_vVNMP[i][j]+m_vVNMCcP[i][j]<<" & ";
                  nCCase=nCCase+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNMP[i][j];
                }
              if((j==nMPToBePrtd-1)&&(nMPToBePrtd==m_vVMpidP[i].size())) fout<<nCCase<<" \\\\ \\hline"<<endl<<endl;
              else fout<<nCCase<<" \\EOL"<<endl<<endl;
              if(j==nMPToBePrtd-1)
                {
                  if(nMPToBePrtd<m_vVMpidP[i].size())
                    {
                      fout<<"rest & others \\  ("<<m_vVMpidP[i].size()-nMPToBePrtd<<" \\  in \\  total) & \\topoTags{--- & }";
                      unsigned long nCCaseOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompMP[i]==0)
                            {
                              fout<<"--- & --- & ";
                            }
                          else
                            {
                              unsigned long nCCaseOfRestTemp1=0;
                              unsigned long nCCaseOfRestTemp2=0;
                              for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNMP[i][j];
                              for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNMCcP[i][j];
                              fout<<nCCaseOfRestTemp1<<" & "<<nCCaseOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNMP[i][j]+m_vVNMCcP[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nMPToBePrtd;j<m_vVMpidP[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNMP[i][j];
                        }
                      nCCase=nCCase+nCCaseOfRest;
                      fout<<nCCaseOfRest<<" & "<<nCCase<<" \\\\ \\hline"<<endl<<endl;
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
          unsigned long nCCase=0;
          unsigned long nDcyBrIncDcyBrToBePrtd=m_vVDcyBrIncDcyBr[i].size()<m_vNExcCompsToBePrtdMax[i]?m_vVDcyBrIncDcyBr[i].size():m_vNExcCompsToBePrtdMax[i];
          for(unsigned int j=0;j<nDcyBrIncDcyBrToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_centDcyObjs==false&&nDcyBrIncDcyBrToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|c|c|c|";
                  else fout<<"ccc";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Exclusive components of $ ";
                  list<int>::iterator liit=m_vCompIncDcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==m_pidOfISt2)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  if(m_vOption_compIncDcyBr[i].find("-IRA")==string::npos) fout<<"\\rightarrow ";
                  else fout<<"\\dashrightarrow ";
                  for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"+ ";
                  if(m_vOption_compIncDcyBr[i]=="") fout<<"anything ";
                  else
                    {
                      fout<<"n ";
                      if(m_vOption_compIncDcyBr[i]=="Is"||m_vOption_compIncDcyBr[i]=="Is-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfSISRGam);
                      else if(m_vOption_compIncDcyBr[i]=="Ig"||m_vOption_compIncDcyBr[i]=="Ig-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfGISRGam);
                      else if(m_vOption_compIncDcyBr[i]=="Fs"||m_vOption_compIncDcyBr[i]=="Fs-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfSFSRGam);
                      else if(m_vOption_compIncDcyBr[i]=="Fg"||m_vOption_compIncDcyBr[i]=="Fg-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfGFSRGam);
                    }
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false) fout<<"P";
                  fout<<"{rowNo & \\thead{exclusive component of $ ";
                  liit=m_vCompIncDcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==m_pidOfISt2)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  if(m_vOption_compIncDcyBr[i].find("-IRA")==string::npos) fout<<"\\rightarrow ";
                  else fout<<"\\dashrightarrow ";
                  for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"+ ";
                  if(m_vOption_compIncDcyBr[i]=="") fout<<"anything ";
                  else
                    {
                      fout<<"n ";
                      if(m_vOption_compIncDcyBr[i]=="Is"||m_vOption_compIncDcyBr[i]=="Is-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfSISRGam);
                      else if(m_vOption_compIncDcyBr[i]=="Ig"||m_vOption_compIncDcyBr[i]=="Ig-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfGISRGam);
                      else if(m_vOption_compIncDcyBr[i]=="Fs"||m_vOption_compIncDcyBr[i]=="Fs-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfSFSRGam);
                      else if(m_vOption_compIncDcyBr[i]=="Fg"||m_vOption_compIncDcyBr[i]=="Fg-IRA") writePnmFromPid(fout,"TexPnm",m_pidOfGFSRGam);
                    }
                  fout<<"$} & \\topoTags{iDcyBrIncDcyBr & }nCase & ";
                  if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
                  fout<<"nCCase \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & $ "; 
              dcyBrIncDcyBr.clear();
              dcyBrIncDcyBr=m_vVDcyBrIncDcyBr[i][j];
              list<int>::iterator liit=dcyBrIncDcyBr.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              if(m_vOption_compIncDcyBr[i].find("-IRA")==string::npos) fout<<"\\rightarrow ";
              else fout<<"\\dashrightarrow ";
              for(liit++;liit!=dcyBrIncDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"$ & \\topoTags{"<<m_vVIDcyBrIncDcyBr[i][j]<<" & }"<<m_vVNDcyBrIncDcyBr[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  // Note that "(m_vICcCompIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])" is used here for a very special case where the inclusive decay branch is not self-charge-conjugate but the exclusive decay branch is self-charge-conjugate. 
                  if((m_vICcCompIncDcyBr[i]==0&&m_vVIDcyBrCcIncDcyBr[i][j]==0)||(m_vICcCompIncDcyBr[i]==1&&m_vVDcyBrIncDcyBr[i][j]==m_vVDcyBrCcIncDcyBr[i][j])) fout<<"---";
                  else fout<<m_vVNDcyBrCcIncDcyBr[i][j];
                  fout<<" & "<<m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j]<<" & ";
                  nCCase=nCCase+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyBrIncDcyBr[i][j];
                }
              if((j==nDcyBrIncDcyBrToBePrtd-1)&&(nDcyBrIncDcyBrToBePrtd==m_vVDcyBrIncDcyBr[i].size())) fout<<nCCase<<" \\\\ \\hline"<<endl<<endl;
              else fout<<nCCase<<" \\EOL"<<endl<<endl;
              if(j==nDcyBrIncDcyBrToBePrtd-1)
                {
                  if(nDcyBrIncDcyBrToBePrtd<m_vVDcyBrIncDcyBr[i].size())
                    {
                      fout<<"rest & $ ";
                      list<int>::iterator liit=m_vCompIncDcyBr[i].begin();
                      writePnmFromPid(fout,"TexPnm",(*liit));
                      if((*liit)==m_pidOfISt2)
                        {
                          liit++;
                          writePnmFromPid(fout,"TexPnm",(*liit));
                        }
                      if(m_vOption_compIncDcyBr[i].find("-IRA")==string::npos) fout<<"\\rightarrow ";
                      else fout<<"\\dashrightarrow ";
                      for(liit++;liit!=m_vCompIncDcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                      fout<<"+ \\rm{others \\  ("<<m_vVDcyBrIncDcyBr[i].size()-nDcyBrIncDcyBrToBePrtd<<" \\  in \\  total)} $ & \\topoTags{--- & }";
                      unsigned long nCCaseOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompIncDcyBr[i]==0)
                            {
                              fout<<"--- & --- & ";
                            }
                          else
                            {
                              unsigned long nCCaseOfRestTemp1=0;
                              unsigned long nCCaseOfRestTemp2=0;
                              for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyBrIncDcyBr[i][j];
                              for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyBrCcIncDcyBr[i][j];
                              fout<<nCCaseOfRestTemp1<<" & "<<nCCaseOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIncDcyBr[i][j]+m_vVNDcyBrCcIncDcyBr[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nDcyBrIncDcyBrToBePrtd;j<m_vVDcyBrIncDcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIncDcyBr[i][j];
                        }
                      nCCase=nCCase+nCCaseOfRest;
                      fout<<nCCaseOfRest<<" & "<<nCCase<<" \\\\ \\hline"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vVDcyBrIRADcyBr.size()>0)
    {
      if(m_ccSwitch==true) nBrInALine=4;
      else nBrInALine=5;
      for(unsigned int i=0;i<m_vVDcyBrIRADcyBr.size();i++)
        {
          vector< list<int> > dcyBrIRADcyBr;
          list<int> subdcyBrIRADcyBr;
          unsigned long nCCase=0;
          unsigned long nDcyBrIRADcyBrToBePrtd=m_vVDcyBrIRADcyBr[i].size()<m_vNIntStrusToBePrtdMax[i]?m_vVDcyBrIRADcyBr[i].size():m_vNIntStrusToBePrtdMax[i];
          nLineMean=0;
          for(unsigned long j=0;j<nDcyBrIRADcyBrToBePrtd;j++) nLineMean=nLineMean+m_vVDcyBrIRADcyBr[i][j].size();
          nLineMean=nLineMean/nDcyBrIRADcyBrToBePrtd/nBrInALine;
          for(unsigned long j=0;j<nDcyBrIRADcyBrToBePrtd;j++)
            {
              if(j==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_centDcyObjs==false&&nDcyBrIRADcyBrToBePrtd>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|c|c|c|";
                  else fout<<"ccc";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Exclusive components of $ ";
                  list<int>::iterator liit=m_vCompIRADcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==m_pidOfISt2)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\dashrightarrow ";
                  for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"$.}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false&&nLineMean<=2) fout<<"P";
                  fout<<"{rowNo & \\thead{exclusive component of $ ";
                  liit=m_vCompIRADcyBr[i].begin();
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((*liit)==m_pidOfISt2)
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\dashrightarrow ";
                  for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  fout<<"$} & \\topoTags{iDcyBrIRADcyBr & }nCase & ";
                  if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
                  fout<<"nCCase \\\\}"<<endl<<endl;
                }
              dcyBrIRADcyBr.clear();
              dcyBrIRADcyBr=m_vVDcyBrIRADcyBr[i][j];
              nVldDcyBr=0;
              fout<<"% \\rn = "<<j+1<<endl;
              fout<<"\\rn & \\makecell[";
              if(m_centDcyObjs==false&&m_vVDcyBrIRADcyBr[i].size()>1) fout<<"l";
              else fout<<"c";
              fout<<"]{ $ "<<endl;
              for(unsigned int k=0;k<dcyBrIRADcyBr.size();k++)
                {
                  subdcyBrIRADcyBr.clear();
                  subdcyBrIRADcyBr=dcyBrIRADcyBr[k];
                  list<int>::iterator liit=subdcyBrIRADcyBr.begin();
                  nVldDcyBr++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                  if((k==0)&&((*liit)==m_pidOfISt2))
                    {
                      liit++;
                      writePnmFromPid(fout,"TexPnm",(*liit));
                    }
                  fout<<"\\rightarrow ";
                  for(liit++;liit!=subdcyBrIRADcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                  if(k!=(dcyBrIRADcyBr.size()-1))
                    {
                      fout<<","<<endl;
                      if(nVldDcyBr%nBrInALine==0) fout<<"$ \\\\ $"<<endl;
                    }
                }
              fout<<endl<<"$ } & \\topoTags{"<<m_vVIDcyBrIRADcyBr[i][j]<<" & }"<<m_vVNDcyBrIRADcyBr[i][j]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcCompIRADcyBr[i]==0&&m_vVIDcyBrCcIRADcyBr[i][j]==0) fout<<"---";
                  else fout<<m_vVNDcyBrCcIRADcyBr[i][j];
                  fout<<" & "<<m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j]<<" & ";
                  nCCase=nCCase+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                }
              else
                {
                  nCCase=nCCase+m_vVNDcyBrIRADcyBr[i][j];
                }
              if((j==nDcyBrIRADcyBrToBePrtd-1)&&(nDcyBrIRADcyBrToBePrtd==m_vVDcyBrIRADcyBr[i].size())) fout<<nCCase<<" \\\\ \\hline"<<endl<<endl;
              else
                {
                  if(m_cmpltHVLines==false&&nLineMean>2) fout<<nCCase<<" \\EOLP"<<endl<<endl;
                  else fout<<nCCase<<" \\EOL"<<endl<<endl;
                }
              if(j==nDcyBrIRADcyBrToBePrtd-1)
                {
                  if(nDcyBrIRADcyBrToBePrtd<m_vVDcyBrIRADcyBr[i].size())
                    {
                      fout<<"rest & $ ";
                      list<int>::iterator liit=m_vCompIRADcyBr[i].begin();
                      writePnmFromPid(fout,"TexPnm",(*liit));
                      if((*liit)==m_pidOfISt2)
                        {
                          liit++;
                          writePnmFromPid(fout,"TexPnm",(*liit));
                        }
                      fout<<"\\rightarrow \\rm{others \\  ("<<m_vVDcyBrIRADcyBr[i].size()-nDcyBrIRADcyBrToBePrtd<<" \\  in \\  total)} \\rightarrow ";
                      for(liit++;liit!=m_vCompIRADcyBr[i].end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
                      fout<<"$ & \\topoTags{--- & }";
                      unsigned long nCCaseOfRest=0;
                      if(m_ccSwitch==true)
                        {
                          if(m_vICcCompIRADcyBr[i]==0)
                            {
                              fout<<"--- & --- & ";
                            }
                          else
                            {
                              unsigned long nCCaseOfRestTemp1=0;
                              unsigned long nCCaseOfRestTemp2=0;
                              for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRestTemp1=nCCaseOfRestTemp1+m_vVNDcyBrIRADcyBr[i][j];
                              for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRestTemp2=nCCaseOfRestTemp2+m_vVNDcyBrCcIRADcyBr[i][j];
                              fout<<nCCaseOfRestTemp1<<" & "<<nCCaseOfRestTemp2<<" & ";
                            }
                          for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIRADcyBr[i][j]+m_vVNDcyBrCcIRADcyBr[i][j];
                        }
                      else
                        {
                          for(unsigned int j=nDcyBrIRADcyBrToBePrtd;j<m_vVDcyBrIRADcyBr[i].size();j++) nCCaseOfRest=nCCaseOfRest+m_vVNDcyBrIRADcyBr[i][j];
                        }
                      nCCase=nCCase+nCCaseOfRest;
                      fout<<nCCaseOfRest<<" & "<<nCCase<<" \\\\ \\hline"<<endl<<endl;
                    }
                  fout<<"\\end{longtable}"<<endl;
                }
            }
        }
    }

  if(m_vSigDcyTr.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrInALine=4;
      else nBrInALine=5;
      if(m_sigDcyIFStsUnderSigDcyTr==false) nBrInALine--;
      vector< list<int> > sigDcyTr;
      list<int> sigDcyBr;
      list<int> sigDcyIFSts_tr;
      vector<int> vIMSigDcyBr;
      nCEtr=0;
      nLineMean=0;
      for(unsigned long i=0;i<m_vSigDcyTr.size();i++) nLineMean=nLineMean+m_vSigDcyTr[i].size();
      nLineMean=nLineMean/m_vSigDcyTr.size()/nBrInALine;
      if(m_sigDcyIFStsUnderSigDcyTr==true) nLineMean=nLineMean+1;
      for(unsigned int i=0;i<m_vSigDcyTr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigDcyTr.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|";
              if(m_sigDcyIFStsUnderSigDcyTr==false)
                {
                  if(m_centDcyObjs==false&&m_vSigDcyTr.size()>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                }
              fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|";
              if(m_sigDcyIFSts_tr==true)
                {
                  fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                }
              if(m_compAnaOfDcyTrs==true)
                {
                  fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                }
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
                {
                  fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                }               
              fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal decay trees and their respective initial-final states.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false&&nLineMean<=2) fout<<"P";
              fout<<"{rowNo & ";
              if(m_sigDcyIFStsUnderSigDcyTr==false) fout<<"\\thead{signal decay tree} & \\thead{signal decay initial-final states}";
              else fout<<"\\thead{signal decay tree \\\\ (signal decay initial-final states)}";
              fout<<" & \\topoTags{iSigDcyTr & ";
              if(m_sigDcyIFSts_tr==true) fout<<"iSigDcyIFSts\\_tr & ";
              if(m_compAnaOfDcyTrs==true) fout<<"iDcyTr & ";
              if(m_compAnaOfDcyIFSts==true) fout<<"iDcyIFSts & ";
              fout<<"}nEtr & ";
              if(m_ccSwitch==true) fout<<"nCcEtr & nAllEtr & ";
              fout<<"nCEtr \\\\}"<<endl<<endl;
            }
          sigDcyTr.clear();
          sigDcyTr=m_vSigDcyTr[i];
          if(m_optIdxAndMidxOfSigDcyBrInSigDcyTr==true) getVIMDcyBr(sigDcyTr,vIMSigDcyBr);
          nVldDcyBr=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigDcyTr.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigDcyTr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigDcyTr[j];              
              list<int>::iterator liit=sigDcyBr.begin();
              nVldDcyBr++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              // The condition "j==0&&((*liit)==m_pidOfISt2)" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
              if((j==0&&((*liit)==m_pidOfISt2))||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(m_optIdxAndMidxOfSigDcyBrInSigDcyTr==true) fout<<"\\, {\\footnotesize ["<<j<<","<<vIMSigDcyBr[j]<<"]}"<<" ";
              if((j+1)!=sigDcyTr.size())
                {
                  fout<<","<<endl;
                  if(nVldDcyBr%nBrInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  if(m_sigDcyIFStsUnderSigDcyTr==false) fout<<endl<<"$ } & $"<<endl;
                  else fout<<endl<<"$ \\\\ ($"<<endl;
                  break;
                }
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
          list<int>::iterator liit=sigDcyIFSts_tr.begin();
          if(m_sigDcyIFStsUnderSigDcyTr==true) writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              if(m_sigDcyIFStsUnderSigDcyTr==true) writePnmFromPid(fout,"TexPnm",(*liit));
            }
          if(m_sigDcyIFStsUnderSigDcyTr==true) fout<<"\\dashrightarrow ";
          for(liit++;liit!=sigDcyIFSts_tr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          if(m_sigDcyIFStsUnderSigDcyTr==false) fout<<endl<<"$ & ";
          else fout<<endl<<"$) } & ";
          fout<<"\\topoTags{"<<m_vISigDcyTr[i]<<" & ";
          if(m_sigDcyIFSts_tr==true)
            {
              if(m_iSigDcyTrICcSigDcyIFSts_trMap[m_vISigDcyTr[i]]>=0) fout<<m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]];
              else fout<<"$ "<<m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]<<"_{\\rm cc} $";
              fout<<" & ";
            }
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
              if(m_iSigDcyIFSts_trIDcyIFStsMap.find(m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]])!=m_iSigDcyIFSts_trIDcyIFStsMap.end())
                {
                  if(m_iSigDcyIFSts_trICcDcyIFStsMap[m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]]>=0) fout<<m_iSigDcyIFSts_trIDcyIFStsMap[m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]];
                  else fout<<"$ "<<m_iSigDcyIFSts_trIDcyIFStsMap[m_iSigDcyTrISigDcyIFSts_trMap[m_vISigDcyTr[i]]]<<"_{\\rm cc} $";
                }
              else fout<<"---";
              fout<<" & ";
            }
          fout<<"}"<<m_vNSigDcyTr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigDcyTr[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyTr[i];
              fout<<" & "<<m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i]<<" & ";
              nCEtr=nCEtr+m_vNSigDcyTr[i]+m_vNCcSigDcyTr[i];          
            }
          else
            {
              nCEtr=nCEtr+m_vNSigDcyTr[i];
            }
          fout<<nCEtr<<" ";
          if(i<(m_vSigDcyTr.size()-1))
            {
              if(m_cmpltHVLines==false&&nLineMean>2) fout<<"\\EOLP"<<endl<<endl;
              else fout<<"\\EOL"<<endl<<endl;
            }
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }

      if(m_sigDcyIFSts_tr==true)
        {
          //list<int> sigDcyIFSts_tr; The list<int> variable sigDcyIFSts_tr has been previously declared.
          nCEtr=0;
          for(unsigned int i=0;i<m_vSigDcyIFSts_tr.size();i++)
            {
              if(i==0)
                {
                  fout<<endl<<"\\clearpage"<<endl<<endl;
                  fout<<"\\small"<<endl;
                  fout<<"\\centering"<<endl;
                  fout<<"\\setcounter{rownumbers}{0}"<<endl;
                  fout<<"\\begin{longtable}{";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_centDcyObjs==false&&m_vSigDcyIFSts_tr.size()>1) fout<<"l";
                  else fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|c|";
                  else fout<<"c";
                  if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
                    {
                      fout<<"c";
                      if(m_cmpltHVLines==true) fout<<"|";
                    }
                  fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                  if(m_ccSwitch==true)
                    {
                      if(m_cmpltHVLines==true) fout<<"c|c|";
                      else fout<<"cc";
                    }
                  fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                  fout<<"}"<<endl;
                  fout<<"\\tablecaption{Signal decay initial-final states corresponding to signal decay trees.}"<<endl;
                  fout<<"\\tableheader";
                  if(m_cmpltHVLines==false) fout<<"P";
                  fout<<"{rowNo & \\thead{signal decay initial-final states} & \\topoTags{iSigDcyIFSts\\_tr & ";
                  if(m_compAnaOfDcyIFSts==true) fout<<"iDcyIFSts & ";
                  fout<<"}nEtr & ";
                  if(m_ccSwitch==true) fout<<"nCcEtr & nAllEtr & ";
                  fout<<"nCEtr \\\\}"<<endl<<endl;
                }
              fout<<"% \\rn = "<<i+1<<endl;
              fout<<"\\rn & $ "; 
              sigDcyIFSts_tr.clear();
              sigDcyIFSts_tr=m_vSigDcyIFSts_tr[i];
              list<int>::iterator liit=sigDcyIFSts_tr.begin();
              writePnmFromPid(fout,"TexPnm",(*liit));
              if((*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\dashrightarrow ";
              for(liit++;liit!=sigDcyIFSts_tr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              fout<<"$ & \\topoTags{"<<m_vISigDcyIFSts_tr[i]<<" & ";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
                {
                  if(m_iSigDcyIFSts_trIDcyIFStsMap.find(m_vISigDcyIFSts_tr[i])!=m_iSigDcyIFSts_trIDcyIFStsMap.end())
                    {
                      if(m_iSigDcyIFSts_trICcDcyIFStsMap[m_vISigDcyIFSts_tr[i]]>=0) fout<<m_iSigDcyIFSts_trIDcyIFStsMap[m_vISigDcyIFSts_tr[i]];
                      else fout<<"$ "<<m_iSigDcyIFSts_trIDcyIFStsMap[m_vISigDcyIFSts_tr[i]]<<"_{\\rm cc} $";
                    }
                  else fout<<"---";
                  fout<<" & ";
                }
              fout<<"}"<<m_vNSigDcyIFSts_tr[i]<<" & ";
              if(m_ccSwitch==true)
                {
                  if(m_vICcSigDcyIFSts_tr[i]==0) fout<<"---";
                  else fout<<m_vNCcSigDcyIFSts_tr[i];
                  fout<<" & "<<m_vNSigDcyIFSts_tr[i]+m_vNCcSigDcyIFSts_tr[i]<<" & ";
                  nCEtr=nCEtr+m_vNSigDcyIFSts_tr[i]+m_vNCcSigDcyIFSts_tr[i];
                }
              else
                {
                  nCEtr=nCEtr+m_vNSigDcyIFSts_tr[i];
                }
              fout<<nCEtr<<" ";
              if(i<(m_vSigDcyIFSts_tr.size()-1)) fout<<"\\EOL"<<endl<<endl;
              else
                {
                  fout<<"\\\\ \\hline"<<endl<<endl;
                  fout<<"\\end{longtable}"<<endl;
                }           
            }
        }
    }

  if(m_vSigDcyIFSts.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigDcyIFSts;
      nCEtr=0;
      for(unsigned int i=0;i<m_vSigDcyIFSts.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigDcyIFSts.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_compAnaOfDcyTrs==true||m_compAnaOfDcyIFSts==true)
                {
                  fout<<"c";
                  if(m_cmpltHVLines==true) fout<<"|";
                }
              fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|";
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal decay initial-final states.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false) fout<<"P";
              fout<<"{rowNo & \\thead{signal decay initial-final states} & \\topoTags{iSigDcyIFSts & }";
              if(m_compAnaOfDcyIFSts==true) fout<<"iDcyIFSts & ";
              fout<<"nEtr & ";
              if(m_ccSwitch==true) fout<<"nCcEtr & nAllEtr & ";
              fout<<"nCEtr \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigDcyIFSts.clear();
          sigDcyIFSts=m_vSigDcyIFSts[i];
          list<int>::iterator liit=sigDcyIFSts.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\dashrightarrow ";
          for(liit++;liit!=sigDcyIFSts.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & \\topoTags{"<<m_vISigDcyIFSts[i]<<" & ";
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
          fout<<"}"<<m_vNSigDcyIFSts[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigDcyIFSts[i]==0) fout<<"---";
              else fout<<m_vNCcSigDcyIFSts[i];
              fout<<" & "<<m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i]<<" & ";
              nCEtr=nCEtr+m_vNSigDcyIFSts[i]+m_vNCcSigDcyIFSts[i];
            }
          else
            {
              nCEtr=nCEtr+m_vNSigDcyIFSts[i];
            }
          fout<<nCEtr<<" ";
          if(i<(m_vSigDcyIFSts.size()-1)) fout<<"\\EOL"<<endl<<endl;
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_vPid_sigP.size()>0&&m_anaTasksForSigIds!="T")
    {
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vNSigP.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|c|c|";
              else fout<<"ccccc";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal particles.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false) fout<<"P";
              fout<<"{rowNo & \\thead{signal particle} & \\topoTags{iSigP & }nCase & ";
              if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & ";
              fout<<"nCCase \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ ";
          writePnmFromPid(fout,"TexPnm",m_vPid_sigP[i]);
          fout<<"$ & \\topoTags{"<<m_vISigP[i]<<" & }"<<m_vNSigP[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigP[i]>0) fout<<m_vNCcSigP[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigP[i]+m_vNCcSigP[i]<<" & ";
              nCCase=nCCase+m_vNSigP[i]+m_vNCcSigP[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigP[i];
            }
          fout<<nCCase<<" ";
          if(i<(m_vNSigP.size()-1)) fout<<"\\EOL"<<endl<<endl;
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_vSigDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigDcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigDcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigDcyBr.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|";
              else fout<<"ccc";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal decay branches.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false) fout<<"P";
              fout<<"{rowNo & \\thead{signal decay branch} & \\topoTags{iSigDcyBr & }nCase & ";
              if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & "<<endl;
              fout<<"nCCase \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigDcyBr.clear();
          sigDcyBr=m_vSigDcyBr[i];
          list<int>::iterator liit=sigDcyBr.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }          
          fout<<"\\rightarrow ";
          for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & \\topoTags{"<<m_vISigDcyBr[i]<<" & }"<<m_vNSigDcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigDcyBr[i]>0) fout<<m_vNCcSigDcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i]<<" & ";
              nCCase=nCCase+m_vNSigDcyBr[i]+m_vNCcSigDcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigDcyBr[i];
            }
          fout<<nCCase<<" ";
          if(i<(m_vSigDcyBr.size()-1)) fout<<"\\EOL"<<endl<<endl;
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_vSigIncDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigIncDcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigIncDcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigIncDcyBr.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|";
              else fout<<"ccc";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal inclusive decay branches.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false) fout<<"P";
              fout<<"{rowNo & \\thead{signal inclusive decay branch} & \\topoTags{iSigIncDcyBr & }"<<"nCase & ";
              if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & "<<endl;
              fout<<"nCCase \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigIncDcyBr.clear();
          sigIncDcyBr=m_vSigIncDcyBr[i];
          list<int>::iterator liit=sigIncDcyBr.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }          
          fout<<"\\rightarrow ";
          for(liit++;liit!=sigIncDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<" + anything $ & \\topoTags{"<<m_vISigIncDcyBr[i]<<" & }"<<m_vNSigIncDcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIncDcyBr[i]>0) fout<<m_vNCcSigIncDcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i]<<" & ";
              nCCase=nCCase+m_vNSigIncDcyBr[i]+m_vNCcSigIncDcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigIncDcyBr[i];
            }
          fout<<nCCase<<" ";
          if(i<(m_vSigIncDcyBr.size()-1)) fout<<"\\EOL"<<endl<<endl;
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_vSigCascDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrInALine=4;
      else nBrInALine=5;
      vector< list<int> > sigCascDcyBr;
      vector<int> vSigCascDcyBrIdxOfHead;
      list<int> sigDcyBr;
      vector<int> vIMSigDcyBr;
      unsigned long nCCase=0;
      nLineMean=0;
      for(unsigned long i=0;i<m_vSigCascDcyBr.size();i++) nLineMean=nLineMean+m_vSigCascDcyBr[i].size();
      nLineMean=nLineMean/m_vSigCascDcyBr.size()/nBrInALine;
      for(unsigned long i=0;i<m_vSigCascDcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigCascDcyBr.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|";
              else fout<<"ccc";
              if(m_ccSwitch==true)
                { 
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal cascade decay branches.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false&&nLineMean<=2) fout<<"P";
              fout<<"{rowNo & \\thead{signal cascade decay branch} & \\topoTags{iSigCascDcyBr & }nCase & ";
              if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & "<<endl;
              fout<<"nCCase \\\\}"<<endl<<endl;
            }
          sigCascDcyBr.clear();
          sigCascDcyBr=m_vSigCascDcyBr[i];
          vSigCascDcyBrIdxOfHead=m_vVSigCascDcyBrIdxOfHead[i];
          if(m_optIdxAndMidxOfSigDcyBrInSigCascDcyBr==true) getVIMDcyBr(sigCascDcyBr,vIMSigDcyBr);
          nVldDcyBr=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigCascDcyBr.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigCascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigCascDcyBr[j];              
              list<int>::iterator liit=sigDcyBr.begin();
              nVldDcyBr++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              // if(j==0&&vSigCascDcyBrIdxOfHead[0]==-1)
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(m_optIdxAndMidxOfSigDcyBrInSigCascDcyBr==true) fout<<"\\, {\\footnotesize ["<<j<<","<<vIMSigDcyBr[j]<<"]}"<<" ";
              if(j<(sigCascDcyBr.size()-1))
                {
                  fout<<","<<endl;
                  if(nVldDcyBr%nBrInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  fout<<endl<<"$ }";
                  break;
                }
            }

          fout<<" & \\topoTags{"<<m_vISigCascDcyBr[i]<<" & }"<<m_vNSigCascDcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigCascDcyBr[i]>0) fout<<m_vNCcSigCascDcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigCascDcyBr[i]+m_vNCcSigCascDcyBr[i]<<" & ";
              nCCase=nCCase+m_vNSigCascDcyBr[i]+m_vNCcSigCascDcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigCascDcyBr[i];
            }
          fout<<nCCase<<" ";
          if(i<(m_vSigCascDcyBr.size()-1))
            {
              if(m_cmpltHVLines==false&&nLineMean>2) fout<<"\\EOLP"<<endl<<endl;
              else fout<<"\\EOL"<<endl<<endl;
            }
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
      if(m_ccSwitch==true) nBrInALine=5;   
    }

  if(m_vSigIncCascDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrInALine=4;
      else nBrInALine=5;
      vector< list<int> > sigIncCascDcyBr;
      vector<int> vSigIncCascDcyBrIdxOfHead;
      list<int> sigDcyBr;
      vector<int> vIMSigDcyBr;
      unsigned long nCCase=0;
      nLineMean=0;
      for(unsigned long i=0;i<m_vSigIncCascDcyBr.size();i++) nLineMean=nLineMean+m_vSigIncCascDcyBr[i].size();
      nLineMean=nLineMean/m_vSigIncCascDcyBr.size()/nBrInALine;
      for(unsigned long i=0;i<m_vSigIncCascDcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigIncCascDcyBr.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|";
              else fout<<"ccc";
              if(m_ccSwitch==true)
                { 
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal inclusive cascade decay branches.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false&&nLineMean<=2) fout<<"P";
              fout<<"{rowNo & \\thead{signal inclusive cascade decay branch} & \\topoTags{iSigIncCascDcyBr & }nCase & ";
              if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & "<<endl;
              fout<<"nCCase \\\\}"<<endl<<endl;
            }
          sigIncCascDcyBr.clear();
          sigIncCascDcyBr=m_vSigIncCascDcyBr[i];
          vSigIncCascDcyBrIdxOfHead=m_vVSigIncCascDcyBrIdxOfHead[i];
          if(m_optIdxAndMidxOfSigDcyBrInSigIncCascDcyBr==true) getVIMDcyBr(sigIncCascDcyBr,vIMSigDcyBr);
          nVldDcyBr=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigIncCascDcyBr.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigIncCascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncCascDcyBr[j];              
              list<int>::iterator liit=sigDcyBr.begin();
              nVldDcyBr++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              // if(j==0&&vSigIncCascDcyBrIdxOfHead[0]==-1)
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(m_vVIIncSigIncCascDcyBr[i][j]==1) writePnmFromPid(fout,"TexPnm",m_pidOfAnything);
              if(m_optIdxAndMidxOfSigDcyBrInSigIncCascDcyBr==true) fout<<"\\, {\\footnotesize ["<<j<<","<<vIMSigDcyBr[j]<<"]}"<<" ";
              if(j<(sigIncCascDcyBr.size()-1))
                {
                  fout<<","<<endl;
                  if(nVldDcyBr%nBrInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  fout<<endl<<"$ }";
                  break;
                }
            }

          fout<<" & \\topoTags{"<<m_vISigIncCascDcyBr[i]<<" & }"<<m_vNSigIncCascDcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIncCascDcyBr[i]>0) fout<<m_vNCcSigIncCascDcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIncCascDcyBr[i]+m_vNCcSigIncCascDcyBr[i]<<" & ";
              nCCase=nCCase+m_vNSigIncCascDcyBr[i]+m_vNCcSigIncCascDcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigIncCascDcyBr[i];
            }
          fout<<nCCase<<" ";
          if(i<(m_vSigIncCascDcyBr.size()-1))
            {
              if(m_cmpltHVLines==false&&nLineMean>2) fout<<"\\EOLP"<<endl<<endl;
              else fout<<"\\EOL"<<endl<<endl;
            }
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
      if(m_ccSwitch==true) nBrInALine=5;   
    }

  if(m_vSigIRADcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      list<int> sigIRADcyBr;
      unsigned long nCCase=0;
      for(unsigned int i=0;i<m_vSigIRADcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigIRADcyBr.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|";
              else fout<<"ccc";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal intermediate-resonance-allowed (IRA) decay branches.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false) fout<<"P";
              fout<<"{rowNo & \\thead{signal IRA decay branch} & \\topoTags{iSigIRADcyBr & }nCase & ";
              if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & "<<endl;
              fout<<"nCCase \\\\}"<<endl<<endl;
            }
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & $ "; 
          sigIRADcyBr.clear();
          sigIRADcyBr=m_vSigIRADcyBr[i];
          list<int>::iterator liit=sigIRADcyBr.begin();
          writePnmFromPid(fout,"TexPnm",(*liit));
          if((*liit)==m_pidOfISt2)
            {
              liit++;
              writePnmFromPid(fout,"TexPnm",(*liit));
            }
          fout<<"\\dashrightarrow ";
          for(liit++;liit!=sigIRADcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
          fout<<"$ & \\topoTags{"<<m_vISigIRADcyBr[i]<<" & }"<<m_vNSigIRADcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIRADcyBr[i]>0) fout<<m_vNCcSigIRADcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i]<<" & ";
              nCCase=nCCase+m_vNSigIRADcyBr[i]+m_vNCcSigIRADcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigIRADcyBr[i];
            }
          fout<<nCCase<<" ";
          if(i<(m_vSigIRADcyBr.size()-1)) fout<<"\\EOL"<<endl<<endl;
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
    }

  if(m_vSigIncOrIRACascDcyBr.size()>0&&m_anaTasksForSigIds!="T")
    {
      if(m_ccSwitch==true) nBrInALine=4;
      else nBrInALine=5;
      vector< list<int> > sigIncOrIRACascDcyBr;
      vector<int> vSigIncOrIRACascDcyBrIdxOfHead;
      list<int> sigDcyBr;
      vector<int> vIMSigDcyBr;
      unsigned long nCCase=0;
      nLineMean=0;
      for(unsigned long i=0;i<m_vSigIncOrIRACascDcyBr.size();i++) nLineMean=nLineMean+m_vSigIncOrIRACascDcyBr[i].size();
      nLineMean=nLineMean/m_vSigIncOrIRACascDcyBr.size()/nBrInALine;
      for(unsigned int i=0;i<m_vSigIncOrIRACascDcyBr.size();i++)
        {
          if(i==0)
            {
              fout<<endl<<"\\clearpage"<<endl<<endl;
              fout<<"\\small"<<endl;
              fout<<"\\centering"<<endl;
              fout<<"\\setcounter{rownumbers}{0}"<<endl;
              fout<<"\\begin{longtable}{";
              if(m_cmpltHVLines==true) fout<<"|c|";
              else fout<<"c";
              if(m_centDcyObjs==false&&m_vSigIncOrIRACascDcyBr.size()>1) fout<<"l";
              else fout<<"c";
              if(m_cmpltHVLines==true) fout<<"|c|c|c|";
              else fout<<"ccc";
              if(m_ccSwitch==true)
                {
                  if(m_cmpltHVLines==true) fout<<"c|c|";
                  else fout<<"cc";
                }
              fout<<"}"<<endl;
              fout<<"\\tablecaption{Signal inclusive or intermediate-resonance-allowed (IRA) cascade decay branches.}"<<endl;
              fout<<"\\tableheader";
              if(m_cmpltHVLines==false&&nLineMean<=2) fout<<"P";
              fout<<"{rowNo & \\thead{signal inclusive or IRA \\\\ cascade decay branch} & \\topoTags{iSigIncOrIRACascDcyBr & }nCase & ";
              if(m_ccSwitch==true) fout<<"nCcCase & nAllCase & "<<endl;
              fout<<"nCCase \\\\}"<<endl<<endl;
            }
          sigIncOrIRACascDcyBr.clear();
          sigIncOrIRACascDcyBr=m_vSigIncOrIRACascDcyBr[i];
          vSigIncOrIRACascDcyBrIdxOfHead=m_vVSigIncOrIRACascDcyBrIdxOfHead[i];
          if(m_optIdxAndMidxOfSigDcyBrInSigIncOrIRACascDcyBr==true) getVIMDcyBr(sigIncOrIRACascDcyBr,vIMSigDcyBr);
          nVldDcyBr=0;
          fout<<"% \\rn = "<<i+1<<endl;
          fout<<"\\rn & \\makecell[";
          if(m_centDcyObjs==false&&m_vSigIncOrIRACascDcyBr.size()>1) fout<<"l";
          else fout<<"c";
          fout<<"]{ $ "<<endl;
          for(unsigned int j=0;j<sigIncOrIRACascDcyBr.size();j++)
            {
              sigDcyBr.clear();
              sigDcyBr=sigIncOrIRACascDcyBr[j];              
              list<int>::iterator liit=sigDcyBr.begin();
              nVldDcyBr++;
              writePnmFromPid(fout,"TexPnm",(*liit));
              // if(j==0&&vSigIncOrIRACascDcyBrIdxOfHead[0]==-1)
              if(j==0&&(*liit)==m_pidOfISt2)
                {
                  liit++;
                  writePnmFromPid(fout,"TexPnm",(*liit));
                }
              if(m_vVIIRASigIncOrIRACascDcyBr[i][j]==1) fout<<"\\; ( \\rightarrow X ) ";
              fout<<"\\rightarrow ";
              for(liit++;liit!=sigDcyBr.end();liit++) writePnmFromPid(fout,"TexPnm",(*liit));
              if(m_vVIIncSigIncOrIRACascDcyBr[i][j]==1) writePnmFromPid(fout,"TexPnm",m_pidOfAnything);
              if(m_optIdxAndMidxOfSigDcyBrInSigIncOrIRACascDcyBr==true) fout<<"\\, {\\footnotesize ["<<j<<","<<vIMSigDcyBr[j]<<"]}"<<" ";
              // The following bool variable is used to judge whether the current branch is the last one outputed or not.
              if(j<(sigIncOrIRACascDcyBr.size()-1))
                {
                  fout<<","<<endl;
                  if(nVldDcyBr%nBrInALine==0) fout<<"$ \\\\ $"<<endl;
                }
              else
                {
                  fout<<endl<<"$ }";
                  break;
                }
            }

          fout<<" & \\topoTags{"<<m_vISigIncOrIRACascDcyBr[i]<<" & }"<<m_vNSigIncOrIRACascDcyBr[i]<<" & ";
          if(m_ccSwitch==true)
            {
              if(m_vICcSigIncOrIRACascDcyBr[i]>0) fout<<m_vNCcSigIncOrIRACascDcyBr[i];
              else fout<<"---";
              fout<<" & "<<m_vNSigIncOrIRACascDcyBr[i]+m_vNCcSigIncOrIRACascDcyBr[i]<<" & ";
              nCCase=nCCase+m_vNSigIncOrIRACascDcyBr[i]+m_vNCcSigIncOrIRACascDcyBr[i];
            }
          else
            {
              nCCase=nCCase+m_vNSigIncOrIRACascDcyBr[i];
            }
          fout<<nCCase<<" ";
          if(i<(m_vSigIncOrIRACascDcyBr.size()-1))
            {
              if(m_cmpltHVLines==false&&nLineMean>2) fout<<"\\EOLP"<<endl<<endl;
              else fout<<"\\EOL"<<endl<<endl;
            }
          else
            {
              fout<<"\\\\ \\hline"<<endl<<endl;
              fout<<"\\end{longtable}"<<endl;
            }
        }
      if(m_ccSwitch==true) nBrInALine=5;   
    }

  fout<<"\\end{document}"<<endl;

}
