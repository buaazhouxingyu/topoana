#include "../include/topoana.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readCmplxDcyOld(string & line, string prompt, vector<int> & vPid, vector< vector<int> > & vVPid, vector<int> & vMidx, vector< vector<int> > & vVMidx, vector<string> & vNm, bool useAsterisk)
{
  istringstream iss;
  iss.clear();
  int idx;
  string txtPnm,asterisk="*"; // The asterisk symbol "*" is used as a short version of the word "anything" in order to simplify the user's input.
  int midx;
  int pid;
  string nm;

  iss.str(line);
  iss>>idx>>txtPnm>>midx;
  if(idx==0&&vPid.size()>0)
    {
      vVPid.push_back(vPid);
      vPid.clear();
      vVMidx.push_back(vMidx);
      vMidx.clear();
    }
  if(useAsterisk==true&&txtPnm==asterisk) txtPnm="anything"; // Pay attention to that if txtPnm==asterisk, then 1 is returned. Please do not get this wrong.
  pid=getPidFromTxtPnm(txtPnm);
  vPid.push_back(pid);
  vMidx.push_back(midx);
  if(idx==0)
    {
      if(!iss.eof()) iss>>nm;
      else nm="";
      vNm.push_back(nm);
    }
}
