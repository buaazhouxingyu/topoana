#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

string topoana::cutToSelect(string strDcyBr, string aliasMP, string ccType, int nTBrs, int nCcTBrs, string topoType, string lang)
{
  int nArrow=countSubstr(strDcyBr, "-->");
  if(nArrow!=1)
    {
      cerr<<"Error: "<<nArrow<<" arrows (-->) are found in the first argument \""<<strDcyBr<<"\" of the function \"cutToSelect\"!"<<endl;
      cerr<<"Infor: Only one arrow is allowed in the argument."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }
  size_t nPos=strDcyBr.find("-->");
  strDcyBr.replace(nPos, 3, " --> ");

  if(ccType!=""&&ccType!="cc"&&ccType!="all")
    {
      cerr<<"Error: \""<<ccType<<"\" is not a valid value for the third argument of the function \"cutToSelect\"!"<<endl;
      cerr<<"Infor: Only \"\", \"cc\", and \"all\" is valid for the argument."<<endl;
      cerr<<"Infor: Please correct it to the right one you want."<<endl;
      exit(-1);
    }

  if(nTBrs<1)
    {
      cerr<<"Error: "<<nTBrs<<" is not a valid value for the fourth argument of the function \"cutToSelect\"!"<<endl;
      cerr<<"Infor: Only integers greater than 0 is valid for the argument."<<endl;
      cerr<<"Infor: Please correct it to the right value you want."<<endl;
      exit(-1);
    }

  if(nCcTBrs<1)
    {
      cerr<<"Error: "<<nCcTBrs<<" is not a valid value for the fifth argument of the function \"cutToSelect\"!"<<endl;
      cerr<<"Infor: Only integers greater than 0 is valid for the argument."<<endl;
      cerr<<"Infor: Please correct it to the right value you want."<<endl;
      exit(-1);
    }

  if(topoType!="dcyBr"&&topoType!="prodBr")
    {
      cerr<<"Error: \""<<topoType<<"\" is not a valid value for the sixth argument of the function \"cutToSelect\"!"<<endl;
      cerr<<"Infor: For the time being, only \"dcyBr\" and \"prodBr\" is valid for the argument."<<endl;
      cerr<<"Infor: Please correct it to the right one you want."<<endl;
      exit(-1);
    }

  if(lang!="python"&&lang!="c++")
    {
      cerr<<"Error: \""<<lang<<"\" is not a valid value for the seventh argument of the function \"cutToSelect\"!"<<endl;
      cerr<<"Infor: For the time being, only \"python\" and \"c++\" is valid for the argument."<<endl;
      cerr<<"Infor: Please correct it to the right one you want."<<endl;
      exit(-1);
    }

  trim(strDcyBr);
  istringstream iss;
  iss.clear();
  iss.str(strDcyBr);

  string txtPnm;
  int pid;
  list<int> dcyBr;
  dcyBr.clear();
  list<int> ccDcyBr;
  ccDcyBr.clear();
  string strDcyBrNew;
  string strCcDcyBrNew;

  while(!iss.eof())
    {
      iss>>txtPnm;
      if(txtPnm!="-->")
        {
          pid=getPidFromTxtPnm(txtPnm);
          dcyBr.push_back(pid);
        }
    }

  if(dcyBr.size()<2)
    {
      cerr<<"Error: "<<nArrow<<" arrows (-->) are found in the first argument \""<<strDcyBr<<"\" of the function \"cutToSelect\"!"<<endl;
      exit(-1);
    }

  pid=(*dcyBr.begin());
  dcyBr.erase(dcyBr.begin());
  sortByPidAndPchrg(dcyBr);
  dcyBr.push_front(pid);
  getStrFromLi(dcyBr,strDcyBrNew,"TxtPnm");

  if(ccType=="cc"||ccType=="all")
    {
      list<int>::iterator liit=dcyBr.begin();
      for(liit++;liit!=dcyBr.end();liit++) ccDcyBr.push_back(getCcPid((*liit)));
      sortByPidAndPchrg(ccDcyBr);
      liit=dcyBr.begin();
      ccDcyBr.push_front(getCcPid((*liit)));
      getStrFromLi(ccDcyBr,strCcDcyBrNew,"TxtPnm");
    }

  string result;
  char strI[10];
  if(ccType=="")
    {
      if(lang=="python") result = "'";
      else if(lang=="c++") result = "\"";
      if(topoType=="dcyBr") result = result + "(sDcyBrP_";
      else if(topoType=="prodBr") result = result + "(sProdBrP_";
      result = result + aliasMP + "_0 == ";
      if(lang=="c++") result = result + "\\";
      result = result + "\"" + strDcyBrNew;
      if(lang=="c++") result = result + "\\";
      result = result + "\")";
      for(unsigned int i=1;i<((unsigned int) nTBrs);i++)
        {
          sprintf(strI, "%d", i);
          if(lang=="python") result = result + " or ";
          else result = result + " || ";
          if(topoType=="dcyBr") result = result + "(sDcyBrP_";
          else if(topoType=="prodBr") result = result + "(sProdBrP_";
          result = result + aliasMP + "_" + strI + " == ";
          if(lang=="c++") result = result + "\\";
          result = result + "\"" + strDcyBrNew;
          if(lang=="c++") result = result + "\\";
          result = result + "\")";
        }
      if(lang=="python") result = result + "'";
      else if(lang=="c++") result = result + "\"";
    }
  else if(ccType=="cc")
    {
      if(lang=="python") result = "'";
      else if (lang=="c++") result = "\"";
      if(getCcPid(pid)!=pid)
        {
          if(topoType=="dcyBr") result = result + "(sDcyBrCcP_";
          else if(topoType=="prodBr") result = result + "(sProdBrCcP_";
        }
      else
        {
          if(topoType=="dcyBr") result = result + "(sDcyBrP_";
          else if(topoType=="prodBr") result = result + "(sProdBrP_";
        }
      result = result + aliasMP + "_0 == ";
      if(lang=="c++") result = result + "\\";
      result = result + "\"" + strCcDcyBrNew;
      if(lang=="c++") result = result + "\\";
      result = result + "\")";
      for(unsigned int i=1;i<((unsigned int) nCcTBrs);i++)
        {
          sprintf(strI, "%d", i);
          if(lang=="python") result = result + " or ";
          else result = result + " || ";
          if(getCcPid(pid)!=pid)
            {
              if(topoType=="dcyBr") result = result + "(sDcyBrCcP_";
              else if(topoType=="prodBr") result = result + "(sProdBrCcP_";
            }
          else
            {
              if(topoType=="dcyBr") result = result + "(sDcyBrP_";
              else if(topoType=="prodBr") result = result + "(sProdBrP_";
            }
          result = result + aliasMP + "_" + strI + " == ";
          if(lang=="c++") result = result + "\\";
          result = result + "\"" + strCcDcyBrNew;
          if(lang=="c++") result = result + "\\";
          result = result + "\")";
        }
      if(lang=="python") result = result + "'";
      else if(lang=="c++") result = result + "\"";
    }
  else if(ccType=="all")
    {
      if(lang=="python") result = "'";
      else if (lang=="c++") result = "\"";
      if(topoType=="dcyBr") result = result + "(sDcyBrP_";
      else if(topoType=="prodBr") result = result + "(sProdBrP_";
      result = result + aliasMP + "_0 == ";
      if(lang=="c++") result = result + "\\";
      result = result + "\"" + strDcyBrNew;
      if(lang=="c++") result = result + "\\";
      result = result + "\")";
      for(unsigned int i=1;i<((unsigned int) nTBrs);i++)
        {
          sprintf(strI, "%d", i);
          if(lang=="python") result = result + " or ";
          else result = result + " || ";
          if(topoType=="dcyBr") result = result + "(sDcyBrP_";
          else if(topoType=="prodBr") result = result + "(sProdBrP_";
          result = result + aliasMP + "_" + strI + " == ";
          if(lang=="c++") result = result + "\\";
          result = result + "\"" + strDcyBrNew;
          if(lang=="c++") result = result + "\\";
          result = result + "\")";
        }
      if(ccDcyBr!=dcyBr)
        {
          for(unsigned int i=0;i<((unsigned int) nCcTBrs);i++)
            {
              sprintf(strI, "%d", i);
              if(lang=="python") result = result + " or ";
              else result = result + " || ";
              if(getCcPid(pid)!=pid)
                {
                  if(topoType=="dcyBr") result = result + "(sDcyBrCcP_";
                  else if(topoType=="prodBr") result = result + "(sProdBrCcP_";
                }
              else
                {
                  if(topoType=="dcyBr") result = result + "(sDcyBrP_";
                  else if(topoType=="prodBr") result = result + "(sProdBrP_";
                }
              result = result + aliasMP + "_" + strI + " == ";
              if(lang=="c++") result = result + "\\";
              result = result + "\"" + strCcDcyBrNew;
              if(lang=="c++") result = result + "\\";
              result = result + "\")";
            }
        }
      if(lang=="python") result = result + "'";
      else if (lang=="c++") result = result + "\"";
    }

  return result;
}
