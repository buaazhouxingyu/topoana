#include "../include/topoana.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readVPItem(ifstream & fin, string & line, string prompt, vector<int> & vPid)
{
  readOpenCurly(fin,line,prompt);
  read1stLineOrCloseCurly(fin,line,false,prompt);
  if(line!="}")
    {
      int pid=getPidFromTxtPnm(line);
      vPid.push_back(pid);
      while(1)
        {
          readExtraLinesOrCloseCurly(fin,line,prompt);
          if(line=="}")
            {
              break;
            }
          else
            {
              pid=getPidFromTxtPnm(line);
              vPid.push_back(pid);
            }
        }
    }
}
