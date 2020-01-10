#include "../include/topoana.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readP(string & line, string prompt, vector<int> & vPid, vector<string> & vNm, vector<unsigned long> * vNMax, vector<unsigned long> * vHMax)
{
  istringstream iss;
  string txtPnm;
  int pid;
  string nm;
  unsigned long nMax;
  unsigned long hMax;

  iss.clear();
  iss.str(line);
  iss>>txtPnm;
  pid=getPidFromTxtPnm(txtPnm);
  vPid.push_back(pid);
  nm="";
  if(!iss.eof())
    {
      iss>>nm;
      if(nm=="-") nm=""; // Here, the symbol \"-\" is used as a place holder denoting the default second parameter in order to input the third parameter following it.
    }
  vNm.push_back(nm);
  if(vNMax!=0)
    {
      nMax=ULONG_MAX;
      if(!iss.eof())
        {
          iss>>txtPnm;
          if(txtPnm.find_first_not_of("0123456789")==string::npos) nMax=strtoul(txtPnm.c_str(),NULL,10);
          else
            {
              cerr<<"Error: The third input parameter \""<<txtPnm<<"\" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
              cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
              cerr<<"Infor: Please check it."<<endl;
              exit(-1);
            }
        }
      (*vNMax).push_back(nMax);
    }
  if(vHMax!=0)
    {
      hMax=ULONG_MAX;
      if(!iss.eof())
        {
          iss>>txtPnm;
          if(txtPnm.find_first_not_of("0123456789")==string::npos) hMax=strtoul(txtPnm.c_str(),NULL,10);
          else
            {
              cerr<<"Error: The fourth input parameter \""<<txtPnm<<"\" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
              cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
              cerr<<"Infor: Please check it."<<endl;
              exit(-1);
            }
        }
      (*vHMax).push_back(hMax);
    }
}
