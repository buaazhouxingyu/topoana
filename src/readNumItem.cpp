#include "../include/topoana.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readNumItem(ifstream & fin, string & line, string prompt, unsigned long & ulvar)
{
  readOpenCurly(fin,line,prompt);
  ulvar=ULONG_MAX;
  read1stLineOrCloseCurly(fin,line,false,prompt);
  if(line!="}")
    {
      if(line.find_first_not_of("0123456789")==string::npos) ulvar=strtoul(line.c_str(),NULL,10);
      else
        {
          cerr<<"Error: The input \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
          cerr<<"Infor: It should be an unsigned long integer if it is not left empty."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
      readCloseCurly(fin,line,prompt);
    }
}

// The method below is implemented based on the method above. Their differences are as follows:
// (1) unsigned long --> int
// (2) ulvar --> ivar
// (3) ULONG_MAX --> INT_MAX
// (4) strtoul(line.c_str(),NULL,10) --> atoi
// (5) should be an unsigned long integer --> should be an integer

void topoana::readNumItem(ifstream & fin, string & line, string prompt, int & ivar, int ivarDft)
{
  readOpenCurly(fin,line,prompt);
  ivar=ivarDft;
  read1stLineOrCloseCurly(fin,line,false,prompt);
  if(line!="}")
    {
      // Don't forget the character '-' for a signed integer!
      if(line.find_first_not_of("-0123456789")==string::npos&&line.find_first_not_of("0123456789",1)==string::npos) ivar=atoi(line.c_str());
      else
        {
          cerr<<"Error: The input \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
          cerr<<"Infor: It should be an integer if it is not left empty."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
      readCloseCurly(fin,line,prompt);
    }
}
