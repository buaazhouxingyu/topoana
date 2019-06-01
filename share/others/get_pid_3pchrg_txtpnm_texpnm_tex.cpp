#include <fstream>
#include <string>
using namespace std;
string & replace(string & str, const string & old_value, const string & new_value)     
{     
  for(string::size_type pos(0);pos!=string::npos;pos+=new_value.length())
  {     
    if((pos=str.find(old_value,pos))!=string::npos) str.replace(pos,old_value.length(),new_value);     
    else break;     
  }     
  return str;     
}     
int main()
{
  int i=0;
  string pid,_3pchrg,txtPnm,texPnm;
  ifstream fin("../pid_3pchrg_txtpnm_texpnm.dat",ios::in);
  ofstream fout("pid_3pchrg_txtpnm_texpnm.tex",ios::out);
  fout<<"\\documentclass{article}"<<endl;
  fout<<"\\begin{document}"<<endl;
  fout<<endl;
  string old_value1="_";
  string new_value1="\\underline{\\hspace{0.6em}}";
  string old_value2="+";
  string new_value2="$+$";
  string old_value3="-";
  string new_value3="$-$";
  string old_value4="''";
  string new_value4="$^{\\prime\\prime}$";
  string old_value5="'";
  string new_value5="$^{\\prime}$";
  while(fin>>pid>>_3pchrg>>txtPnm>>texPnm)
  {
    pid=replace(pid,old_value3,new_value3);
    _3pchrg=replace(_3pchrg,old_value3,new_value3);
    txtPnm=replace(txtPnm,old_value1,new_value1);
    txtPnm=replace(txtPnm,old_value2,new_value2);
    txtPnm=replace(txtPnm,old_value3,new_value3);
    txtPnm=replace(txtPnm,old_value4,new_value4);
    txtPnm=replace(txtPnm,old_value5,new_value5);
    if(i%40==0)
    {
      fout<<"\\begin{table}[!htbp]"<<endl;
      fout<<"\\centering"<<endl;
      if(i==0) fout<<"\\caption{XYZ}"<<endl;
      fout<<"\\begin{tabular}{|c|c|c|c|c|}"<<endl;
      fout<<"\\hline"<<endl;
      fout<<"index & PDG code & 3 $\\times$ charge & text name & symbol \\\\"<<endl;
      fout<<"\\hline"<<endl;
    }
    fout<<i+1<<" & "<<pid<<" & "<<_3pchrg<<" & "<<txtPnm<<" & $"<<texPnm<<"$ \\\\"<<endl;
    fout<<"\\hline"<<endl;
    if(i%40==39)
    {
      fout<<"\\end{tabular}"<<endl;
      fout<<"\\end{table}"<<endl;
      fout<<endl;
      fout<<"\\clearpage"<<endl;
      fout<<endl;
    }
    i++;
  }
  if(i%40!=0)
  {
    fout<<"\\end{tabular}"<<endl;
    fout<<"\\end{table}"<<endl;
    fout<<endl;

    fout<<"\\clearpage"<<endl;
    fout<<endl;

  }
  fout<<endl;
  fout<<"\\end{document}"<<endl;
  return 0;
}
