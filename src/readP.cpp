#include "../include/topoana.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readP(string & line, string prompt, vector<int> & vPid, vector<string> & vNm, vector<unsigned long> * vNMax, vector<unsigned long> * vHMax, vector<string> * vTypeOfTagRec, vector<string> * vTBrNmOfTagRec, vector<string> * vTBrNmOfNRec, vector<bool> * vOpt)
{
  istringstream iss;
  string txtPnm;
  int pid;
  string nm;
  unsigned long nMax;
  unsigned long hMax;
  string typeOfTagRec;
  string tBrNmOfTagRec;
  string tBrNmOfNRec;
  bool opt;
  bool isTagRead=false;

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
          else if(txtPnm!="-")
            {
              cerr<<"Error: The third input parameter \""<<txtPnm<<"\" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
              cerr<<"Infor: It should be an unsigned long integer at which you want to set, or just a placeholder \"-\" as a default value \"ULONG_MAX\" and for the input of the fourth parameter."<<endl;
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
          else if(txtPnm!="-")
            {
              // The following statements are replaced with the if statement below them, in order to enable the fourth parameter can also be used to specify the reconstruction information of the  particle.
              /*cerr<<"Error: The fourth input parameter \""<<txtPnm<<"\" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
              cerr<<"Infor: It should be an unsigned long integer at which you want to set, or just a placeholder \"-\" as a default value \"ULONG_MAX\" and for the input of the fifth parameter."<<endl;
              cerr<<"Infor: Please check it."<<endl;
              exit(-1);*/
              if(vTypeOfTagRec!=0)
                {
                  typeOfTagRec="";
                  tBrNmOfTagRec="";
                  tBrNmOfNRec="";
                  parseIptStrIntoRecStrs(line,prompt,txtPnm,typeOfTagRec,tBrNmOfTagRec,tBrNmOfNRec);
                  (*vTypeOfTagRec).push_back(typeOfTagRec);
                  (*vTBrNmOfTagRec).push_back(tBrNmOfTagRec);
                  (*vTBrNmOfNRec).push_back(tBrNmOfNRec);
                  isTagRead=true;
                }
            }
        }
      (*vHMax).push_back(hMax);
    }
  if(vTypeOfTagRec!=0&&isTagRead==false)
    {
      typeOfTagRec="";
      tBrNmOfTagRec="";
      tBrNmOfNRec="";
      if(!iss.eof())
        {
          iss>>txtPnm;
          parseIptStrIntoRecStrs(line,prompt,txtPnm,typeOfTagRec,tBrNmOfTagRec,tBrNmOfNRec);
        }
      (*vTypeOfTagRec).push_back(typeOfTagRec);
      (*vTBrNmOfTagRec).push_back(tBrNmOfTagRec);
      (*vTBrNmOfNRec).push_back(tBrNmOfNRec);
    }
  if(vOpt!=0)
    {
      opt=false;
      if(!iss.eof())
        {
          iss>>txtPnm;
          if(txtPnm=="Y")
            {
              opt=true;
            }
          else if(txtPnm=="N")
            {
              opt=false;
            }          
          else
            {
              cerr<<"Error: The fifth or sixth input parameter \""<<txtPnm<<"\" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
              cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
              cerr<<"Infor: Please check it."<<endl;
              exit(-1);
            }
        }
      (*vOpt).push_back(opt);
    }
}
