#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
int main()
{
  int pid,_3pchrg;
  string txtPnm,texPnm;
  int iccp;
  vector<int> vPid,v3Pchrg;
  vector<string> vTxtPnm,vTexPnm;
  ifstream fin("pid_3pchrg_txtpnm_texpnm_iccp.dat_temp2",ios::in);
  ofstream fout("pid_3pchrg_txtpnm_texpnm_iccp.dat",ios::out);
  while(fin>>pid>>_3pchrg>>txtPnm>>texPnm>>iccp)
  {
    vPid.push_back(pid);
    v3Pchrg.push_back(_3pchrg);
    vTxtPnm.push_back(txtPnm);
    vTexPnm.push_back(texPnm);
    fout<<setiosflags(ios::right)<<setw(16)<<pid<<setw(8)<<_3pchrg<<resetiosflags(ios::right)<<"\t"<<setiosflags(ios::left)<<setw(24)<<txtPnm<<setw(32)<<texPnm<<setiosflags(ios::right)<<setw(2)<<iccp<<endl;
  }
  return 0;
}
