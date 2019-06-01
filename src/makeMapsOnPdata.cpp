#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

void topoana::makeMapsOnPdata()
{
  m_pid3PchrgMap.clear();
  m_pidTxtPnmMap.clear();
  m_pidTexPnmMap.clear();
  m_pidIccPMap.clear();
  int pid,i3pchrg; string txtpnm,texpnm; int iccp; // The character "i" in the variable name "i3pchrg" is inserted specially for avoiding the mistake of starting a variable name with a number.
  string DatFlNm=m_pkgPath+"share/pid_3pchrg_txtpnm_texpnm_iccp.dat";
  ifstream fin(DatFlNm.c_str(),ios::in);
  if(!fin)
    {
      cerr<<"Error: Can't open the data file \""<<DatFlNm<<"\"!"<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }
  while(fin>>pid>>i3pchrg>>txtpnm>>texpnm>>iccp)
    {
      m_pid3PchrgMap[pid]=i3pchrg;
      m_pidTxtPnmMap[pid]=txtpnm;
      m_pidTexPnmMap[pid]=texpnm;
      m_pidIccPMap[pid]=iccp;
      // cout<<setiosflags(ios::right)<<setw(16)<<pid<<setw(8)<<i3pchrg<<resetiosflags(ios::right)<<"\t"<<setiosflags(ios::left)<<setw(24)<<txtpnm<<setw(32)<<texpnm<<setiosflags(ios::right)<<setw(2)<<iccp<<endl; 
    }
  // cout<<endl; /* This cout statement goes along with the one above. */
}
