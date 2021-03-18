#include "../include/topoana.h"

string topoana::replaceAllSubstr(string str, string oldSubstr, string newSubstr)     
{     
  string::size_type pos(0);
  while(true)
    { 
      pos=str.find(oldSubstr, pos);
      if(pos!=string::npos)
        {
          str.replace(pos, oldSubstr.length(), newSubstr);
          pos=pos+newSubstr.length();
        }
      else break;     
    }     
 return str;     
} 
