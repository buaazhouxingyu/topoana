#include "../include/topoana.h"
#include <fstream>

void topoana::readPItem(ifstream & fin, string & line, string prompt, vector<int> & vPid, vector<string> & vNm, vector<unsigned long> * vNMax, vector<unsigned long> * vHMax, vector<bool> * vOpt)
{
  readOpenCurly(fin,line,prompt);
  read1stLineOrCloseCurly(fin,line,false,prompt);
  if(line!="}")
    {
      readP(line,prompt,vPid,vNm,vNMax,vHMax,vOpt);
      while(1)
        {
          readExtraLinesOrCloseCurly(fin,line,prompt);
          if(line=="}") break;
          else readP(line,prompt,vPid,vNm,vNMax,vHMax,vOpt);
        }
    }
}
