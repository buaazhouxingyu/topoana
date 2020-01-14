#include "../include/topoana.h"
#include <sstream>
#include <iostream>

void topoana::getStrFromLi(list<int> & dcyIFSts, string & strDcyIFSts)
{
  ostringstream oss;
  oss.str("");
  list<int>::iterator liit=dcyIFSts.begin();
  oss<<(*liit)<<" ";
  if((*liit)==m_pidOfISt2)
    {
      liit++;
      oss<<(*liit)<<" ";
    }
  oss<<"> ";
  list<int>::iterator liitTmp=dcyIFSts.end();
  liitTmp--;
  for(liit++;liit!=liitTmp;liit++) oss<<(*liit)<<" ";
  oss<<(*liit);
  strDcyIFSts=oss.str();
  //cout<<i<<"\t"<<strDcyIFSts<<endl<<endl;
}
