#include "../include/topoana.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readCmplxDcyItem(ifstream & fin, string & line, string prompt, vector< vector<int> > & vVPid, vector< vector<int> > & vVMidx, vector<string> & vNm, bool & bvar1, bool & bvar2, vector<string> * vTypeOfTagRec, vector<string> * vTBrNmOfTagRec, vector<string> * vTBrNmOfNRec, bool useAsterisk)
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
          vector<int> vMidx;
          vMidx.clear();
          readCmplxDcyOld(line,vPid,vVPid,vMidx,vVMidx,vNm,useAsterisk);
          while(1)
            {
              readExtraLinesOrCloseCurly(fin,line,prompt);
              if(line=="}")
                {
                  vVPid.push_back(vPid);
                  vPid.clear();
                  vVMidx.push_back(vMidx);
                  vMidx.clear();
                  break;
                }
              else readCmplxDcyOld(line,vPid,vVPid,vMidx,vVMidx,vNm,useAsterisk);
            }
        }
      else
        {
          vector< vector<int> > vDcyBr;
          vDcyBr.clear();
          vector<int> vIMDcyBr;
          vIMDcyBr.clear();
          vector<int> vPid;
          vPid.clear();
          vector<int> vMidx;
          vMidx.clear();
          string typeOfTagRec;
          string tBrNmOfTagRec;
          string tBrNmOfNRec;
          readCmplxDcyNew(line,prompt,vDcyBr,vIMDcyBr,vPid,vMidx,vNm,bvar1,bvar2,typeOfTagRec,tBrNmOfTagRec,tBrNmOfNRec,useAsterisk);
          while(1)
            {
              readExtraLinesOrCloseCurly(fin,line,prompt);
              if(line=="}")
                {
                  // Don't leave out the following if statement! It is added here for the cases where the last decay tree or cascade decay branch only consists of one regular decay branch.
                  if(vPid.size()>0)
                    {
                      vVPid.push_back(vPid);
                      vVMidx.push_back(vMidx);
                      vPid.clear();
                      vMidx.clear();
                      if(vTypeOfTagRec!=0) (*vTypeOfTagRec).push_back(typeOfTagRec);
                      if(vTBrNmOfTagRec!=0) (*vTBrNmOfTagRec).push_back(tBrNmOfTagRec);
                      if(vTBrNmOfNRec!=0) (*vTBrNmOfNRec).push_back(tBrNmOfNRec);
                    }
                  getVPidandVMidx(vDcyBr,vIMDcyBr,vPid,vMidx);
                  vVPid.push_back(vPid);
                  vVMidx.push_back(vMidx); 
                  vPid.clear();
                  vMidx.clear();
                  if(vTypeOfTagRec!=0) (*vTypeOfTagRec).push_back(typeOfTagRec);
                  if(vTBrNmOfTagRec!=0) (*vTBrNmOfTagRec).push_back(tBrNmOfTagRec);
                  if(vTBrNmOfNRec!=0) (*vTBrNmOfNRec).push_back(tBrNmOfNRec);
                  break;
                }
              else
                {
                  if(vPid.size()>0)
                    {
                      vVPid.push_back(vPid);
                      vVMidx.push_back(vMidx);
                      vPid.clear();
                      vMidx.clear();
                      if(vTypeOfTagRec!=0) (*vTypeOfTagRec).push_back(typeOfTagRec);
                      if(vTBrNmOfTagRec!=0) (*vTBrNmOfTagRec).push_back(tBrNmOfTagRec);
                      if(vTBrNmOfNRec!=0) (*vTBrNmOfNRec).push_back(tBrNmOfNRec);
                    }
                  readCmplxDcyNew(line,prompt,vDcyBr,vIMDcyBr,vPid,vMidx,vNm,bvar1,bvar2,typeOfTagRec,tBrNmOfTagRec,tBrNmOfNRec,useAsterisk);
                }
            }
        }
    }
}
