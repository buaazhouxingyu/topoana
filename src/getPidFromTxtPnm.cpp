#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

int topoana::getPidFromTxtPnm(string pnm)
{
  int pid;
  bool inTheMap=false;
  map<int,string>::iterator misit;
  for(misit=m_pidTxtPnmMap.begin();misit!=m_pidTxtPnmMap.end();misit++)
    {
      if((misit->second)==pnm)
        {
          pid=(misit->first);
          inTheMap=true;
          break;
        }
    }
  if(inTheMap)
    {
      return pid;
    }
  else
    {
      string evtPdlFlNm="evt.pdl";
      string pidPsymbPdfFlNm=m_pkgPath+"docs/pid_psymb.pdf";
      string DatFlNm=m_pkgPath+"share/pid_3pchrg_txtpnm_texpnm_iccp.dat";
      cerr<<"Error: The PDG code of the particle of the txt name \""<<pnm<<"\" does not exist!"<<endl;
      cerr<<"Infor: Please check whether the txt name \""<<pnm<<"\" written in your card file is right."<<endl;
      cerr<<"Infor: If no, please correct it to the right one."<<endl;
      cerr<<"Infor: If yes, please follow the steps below to supplement the data file \""<<DatFlNm<<"\"."<<endl;
      cerr<<"Infor: 1) Please refer to the pdl file \""<<evtPdlFlNm<<"\" related to your basf2 release, find the PDG code and 3 times charge of the particle."<<endl;
      cerr<<"Infor: 2) Please refer to the pdf file \""<<pidPsymbPdfFlNm<<"\", find the symbol of the particle, and then convert the symbol into the tex name."<<endl;
      cerr<<"Infor: 3) Please confirm whether the particle is self-charge-conjugate or not. If yes, please assign 0 to the index for the charge conjugate property. If no, please assign 1 to the index for the charge conjugate property."<<endl;
      cerr<<"Infor: 4) Please add the tuple of the PDG code, 3 times charge, txt name, tex name and index for the charge conjugate property of the particle to the data file \""<<DatFlNm<<"\"."<<endl;
      cerr<<"Infor: Please contact me (zhouxy@buaa.edu.cn), if you still have questions about the problem."<<endl<<endl;
      exit(-1);
    }
}
