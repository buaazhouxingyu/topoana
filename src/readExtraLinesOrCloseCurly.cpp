#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

void topoana::readExtraLinesOrCloseCurly(ifstream & fin, string & line, string prompt)
{
  line="";
  while(!fin.eof())
    {
      getline(fin,line);
      trim(line);
      if(!line.empty()&&line[0]!='#') break;
    }
  if(line.empty()||line[0]=='#'||line.substr(0,2)=="% ")
    {
      cerr<<"Error: The close curly \"}\" related to the prompt \""<<prompt<<"\" is missing!"<<endl;
      exit(-1);
    }
}
