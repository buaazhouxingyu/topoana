#include "../include/topoana.h"
#include <iostream>

void topoana::writeErrInfOnPid3PchrgMap(int pid)
{
  string evtPdlFlNm="evt.pdl";
  string pidPsymbPdfFlNm=m_pkgPath+"docs/pid_psymb.pdf";
  string DatFlNm=m_pkgPath+"share/pid_3pchrg_txtpnm_texpnm_iccp.dat";
  cerr<<"Error: The 3 times charge, txt name, tex name and index for the charge conjugate property of the particle of the PDG code \""<<pid<<"\" does not exist!"<<endl;
  cerr<<"Infor: 1) Please refer to the pdl file \""<<evtPdlFlNm<<"\" in the related release of your experiment software, find the 3 times charge and txt name of the particle."<<endl;
  cerr<<"Infor: 2) Please refer to the pdf file \""<<pidPsymbPdfFlNm<<"\", find the symbol of the particle, and then convert the symbol into the tex name."<<endl;
  cerr<<"Infor: 3) Please confirm whether the particle is self-charge-conjugate or not. If yes, please assign 0 to the index for the charge conjugate property. If no, please assign 1 to the index for the charge conjugate property."<<endl;
  cerr<<"Infor: 4) Please add the tuple of the PDG code, 3 times charge, txt name, tex name and index for the charge conjugate property of the particle to the data file \""<<DatFlNm<<"\"."<<endl;
  cerr<<"Infor: Please contact me (zhouxy@buaa.edu.cn), if you still have questions about the problem."<<endl<<endl;
}
