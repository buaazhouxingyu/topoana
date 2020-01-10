#include "../include/topoana.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readSmpDcyOld(string & line, string prompt, vector<int> & vPid, vector< vector<int> > & vVPid, vector<string> * vNm, vector<unsigned long> * vNMax)
{
  istringstream iss;
  iss.clear();
  int idx;
  string txtPnm;
  int pid;
  string nm;
  unsigned long nMax;

  iss.str(line);
  iss>>idx>>txtPnm;
  if(idx==0&&vPid.size()>0)
    {
      vVPid.push_back(vPid);
      vPid.clear();
    }
  pid=getPidFromTxtPnm(txtPnm);
  vPid.push_back(pid);
  if(idx==0)
    {
      if(vNm!=0)
        {
          nm="";
          if(!iss.eof())
            {
              iss>>nm;
              if(nm=="-") nm=""; // Here, the symbol \"-\" is used as a place holder denoting the default second parameter in order to input the third parameter following it.
            }
          (*vNm).push_back(nm);
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
        }
    }
}
