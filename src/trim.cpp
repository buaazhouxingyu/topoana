#include "../include/topoana.h"
string & topoana::trim(string & line)
{
  if(line.empty())
    {
      return line;
    }
  line.erase(0,line.find_first_not_of(" "));
  line.erase(line.find_last_not_of(" ")+1);
  line.erase(0,line.find_first_not_of("\t"));
  line.erase(line.find_last_not_of("\t")+1);
  return line;
}
