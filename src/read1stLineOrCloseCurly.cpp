#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

void topoana::read1stLineOrCloseCurly(ifstream & fin, string & line, bool essential=true, string errinforprompt="")
{
  line="";
  while(!fin.eof())
    {
      getline(fin,line);
      trim(line);
      if(!line.empty()&&line[0]!='#') break;
    }       
  if(essential==true)
    {
      if(line.empty()||line[0]=='#'||line=="}"||line.substr(0,2)=="% ")
        {
          cerr<<"Error: "<<errinforprompt<<"\"!"<<endl;
          exit(-1);
        }
    }  
  else
    {
      if(line.empty()||line[0]=='#'||line.substr(0,2)=="% ")
        {
          cerr<<"Error: The close curly \"}\" related to the prompt \""<<errinforprompt<<"\" is missing!"<<endl;
        }
    }
}
