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
  for(unsigned int i=0;i<vPid.size();i++)
  {
    for(unsigned int j=i+1;j<vPid.size();j++)
    {
      if(abs(vPid[i])>abs(vPid[j])||(abs(vPid[i])==abs(vPid[j])&&vPid[i]<vPid[j]))
      {
        pid=vPid[i];
        _3pchrg=v3Pchrg[i];
        txtPnm=vTxtPnm[i];
        texPnm=vTexPnm[i];
        vPid[i]=vPid[j];
        v3Pchrg[i]=v3Pchrg[j];
        vTxtPnm[i]=vTxtPnm[j];
        vTexPnm[i]=vTexPnm[j];
        vPid[j]=pid;
        v3Pchrg[j]=_3pchrg;
        vTxtPnm[j]=txtPnm;
        vTexPnm[j]=texPnm;
      }
    }
  }
  ofstream fout("pid_3pchrg_txtpnm_texpnm.dat_new",ios::out);
  for(unsigned int i=0;i<vPid.size();i++)
  {
    fout<<setiosflags(ios::right)<<setw(16)<<vPid[i]<<setw(8)<<v3Pchrg[i]<<resetiosflags(ios::right)<<"\t"<<setiosflags(ios::left)<<setw(24)<<vTxtPnm[i]<<setw(32)<<vTexPnm[i]<<endl;
  }
  return 0;
}
