#include "../include/topoana.h"
#include <fstream>

void topoana::readSmpDcyItem(ifstream & fin, string & line, string prompt, vector< vector<int> > & vVPid, vector<string> * vNm, vector<unsigned long> * vNMax, vector<string> * vOption)
{
  readOpenCurly(fin,line,prompt);
  read1stLineOrCloseCurly(fin,line,false,prompt);
  if(line!="}")
    {
      int nArrow=countSubstr(line,"-->");
      if(nArrow==0)
        {
          vector<int> vPid;
          vPid.clear();
          readSmpDcyOld(line,prompt,vPid,vVPid,vNm,vNMax);
          while(1)
            {
              readExtraLinesOrCloseCurly(fin,line,prompt);
              if(line=="}")
                {
                  vVPid.push_back(vPid);
                  vPid.clear();
                  break;
                }
              else readSmpDcyOld(line,prompt,vPid,vVPid,vNm,vNMax);
            }
        }
      else
        {
          readSmpDcyNew(line,prompt,vVPid,vNm,vNMax,vOption);
          while(1)
            {
              readExtraLinesOrCloseCurly(fin,line,prompt);
              if(line=="}") break;
              else readSmpDcyNew(line,prompt,vVPid,vNm,vNMax,vOption);
            }
        }
    }
}
