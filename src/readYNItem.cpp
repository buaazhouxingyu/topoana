#include "../include/topoana.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readYNItem(ifstream & fin, string & line, string prompt, bool & bvar)
{
  readOpenCurly(fin,line,prompt);
  read1stLineOrCloseCurly(fin,line,false,prompt);
  if(line!="}")
    {
      if(line=="Y")
        {
          bvar=true;
        }
      else if(line=="N")
        {
          bvar=false;
        }
      else
        {
          cerr<<"Error: The input \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
          cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
      readCloseCurly(fin,line,prompt);
    }
}
