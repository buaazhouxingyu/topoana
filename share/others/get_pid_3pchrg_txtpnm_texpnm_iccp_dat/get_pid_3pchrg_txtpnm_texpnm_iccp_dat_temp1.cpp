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
  vector<int> vPid,v3Pchrg;
  vector<string> vTxtPnm,vTexPnm;
  ifstream fin("pid_3pchrg_txtpnm_texpnm.dat",ios::in);
  while(fin>>pid>>_3pchrg>>txtPnm>>texPnm)
  {
    vPid.push_back(pid);
    v3Pchrg.push_back(_3pchrg);
    vTxtPnm.push_back(txtPnm);
    vTexPnm.push_back(texPnm);
    //cout<<setiosflags(ios::right)<<setw(16)<<pid<<setw(8)<<_3pchrg<<resetiosflags(ios::right)<<"\t"<<setiosflags(ios::left)<<setw(24)<<txtPnm<<setw(32)<<texPnm<<endl;
  }
  ofstream fout("pid_3pchrg_txtpnm_texpnm_iccp.dat_temp1",ios::out);
  for(unsigned int i=0;i<vPid.size();i++)
  {
    if(vPid[i+1]==-vPid[i])
    {
      fout<<setiosflags(ios::right)<<setw(16)<<vPid[i]<<setw(8)<<v3Pchrg[i]<<resetiosflags(ios::right)<<"\t"<<setiosflags(ios::left)<<setw(24)<<vTxtPnm[i]<<setw(32)<<vTexPnm[i]<<setiosflags(ios::right)<<setw(2)<<1<<endl;      
      fout<<setiosflags(ios::right)<<setw(16)<<vPid[i+1]<<setw(8)<<v3Pchrg[i+1]<<resetiosflags(ios::right)<<"\t"<<setiosflags(ios::left)<<setw(24)<<vTxtPnm[i+1]<<setw(32)<<vTexPnm[i+1]<<setiosflags(ios::right)<<setw(2)<<-1<<endl;
      i++;
    }
    else
    {
      fout<<setiosflags(ios::right)<<setw(16)<<vPid[i]<<setw(8)<<v3Pchrg[i]<<resetiosflags(ios::right)<<"\t"<<setiosflags(ios::left)<<setw(24)<<vTxtPnm[i]<<setw(32)<<vTexPnm[i]<<setiosflags(ios::right)<<setw(2)<<0<<endl;
    }
  }
  return 0;
}
