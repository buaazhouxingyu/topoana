#include "../include/topoana.h"
#include <iostream>
#include <string>

int topoana::countSubstr(const string & str, const string & substr)
{
  if(substr.length()==0) return 0;
  int count=0;
  size_t nPos=str.find(substr);
  while(nPos!=string::npos)
    {
      count++;
      nPos=str.find(substr,nPos+substr.length());
    }
  return count;
}
