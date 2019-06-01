#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::writePnmFromPid(ostream & out,string pnmType,int pid)
{
  if(pnmType=="TxtPnm")
    {
      if(m_pidTxtPnmMap.find(pid)!=m_pidTxtPnmMap.end())
        { 
          out<<" "<<m_pidTxtPnmMap[pid];
        }
      else
        {
          out<<" "<<"??";
          string evtPdlFlNm="evt.pdl";
          string pidPsymbPdfFlNm=m_pkgPath+"docs/pid_psymb.pdf";
          string DatFlNm=m_pkgPath+"share/pid_3pchrg_txtpnm_texpnm_iccp.dat";
          cerr<<"Error: The 3 times charge, txt name, tex name and index for the charge conjugate property of the particle of the PDG code \""<<pid<<"\" does not exist!"<<endl;
          cerr<<"Infor: 1) Please refer to the pdl file \""<<evtPdlFlNm<<"\" related to your basf2 release, find the 3 times charge and txt name of the particle."<<endl;
          cerr<<"Infor: 2) Please refer to the pdf file \""<<pidPsymbPdfFlNm<<"\", find the symbol of the particle, and then convert the symbol into the tex name."<<endl;
          cerr<<"Infor: 3) Please confirm whether the particle is self-charge-conjugate or not. If yes, please assign 0 to the index for the charge conjugate property. If no, please assign 1 to the index for the charge conjugate property."<<endl; 
          cerr<<"Infor: 4) Please add the tuple of the PDG code, 3 times charge, txt name, tex name and index for the charge conjugate property of the particle to the data file \""<<DatFlNm<<"\"."<<endl;
          cerr<<"Infor: Please contact me (zhouxy@buaa.edu.cn), if you still have questions about the problem."<<endl<<endl;
        }
    }
  else if(pnmType=="TexPnm")
    {
      if(m_pidTexPnmMap.find(pid)!=m_pidTexPnmMap.end())
        {
          out<<m_pidTexPnmMap[pid]<<" ";
        }
      else
        {
          out<<"{\\color{red}{??}}"<<" ";
          string evtPdlFlNm="evt.pdl";
          string pidPsymbPdfFlNm=m_pkgPath+"docs/pid_psymb.pdf";
          string DatFlNm=m_pkgPath+"share/pid_3pchrg_txtpnm_texpnm_iccp.dat";
          cerr<<"Error: The 3 times charge, txt name, tex name and index for the charge conjugate property of the particle of the PDG code \""<<pid<<"\" does not exist!"<<endl;
          cerr<<"Infor: 1) Please refer to the pdl file \""<<evtPdlFlNm<<"\" related to your basf2 release, find the 3 times charge and txt name of the particle."<<endl;
          cerr<<"Infor: 2) Please refer to the pdf file \""<<pidPsymbPdfFlNm<<"\", find the symbol of the particle, and then convert the symbol into the tex name."<<endl;
          cerr<<"Infor: 3) Please confirm whether the particle is self-charge-conjugate or not. If yes, please assign 0 to the index for the charge conjugate property. If no, please assign 1 to the index for the charge conjugate property."<<endl;
          cerr<<"Infor: 4) Please add the tuple of the PDG code, 3 times charge, txt name, tex name and index for the charge conjugate property of the particle to the data file \""<<DatFlNm<<"\"."<<endl;               cerr<<"Infor: Please contact me (zhouxy@buaa.edu.cn), if you still have questions about the problem."<<endl<<endl;
        }
    }
  else
    {
      cerr<<"Error: The particle name type \""<<pnmType<<"\" does not exist!"<<endl;
      cerr<<"Infor: Please check it in the cpp source file \"topoana.cpp\"."<<endl;
      exit(-1);
    }
}
