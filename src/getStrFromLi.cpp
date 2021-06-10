#include "../include/topoana.h"
#include <sstream>
#include <iostream>

void topoana::getStrFromLi(list<int> & dcyIFSts, string & strDcyIFSts, string opt)
{
  ostringstream oss;
  oss.str("");
  list<int>::iterator liit=dcyIFSts.begin();
  if(opt=="TxtPnm") writePnmFromPid(oss, "TxtPnm1", (*liit));
  else oss<<(*liit)<<" ";
  if((*liit)==m_pidOfISt2)
    {
      liit++;
      if(opt=="TxtPnm") writePnmFromPid(oss, "TxtPnm1", (*liit));
      else oss<<(*liit)<<" ";
    }
  if(opt=="TxtPnm") oss<<"--> ";
  else oss<<"> ";
  list<int>::iterator liitTmp=dcyIFSts.end();
  liitTmp--;
  for(liit++;liit!=liitTmp;liit++)
    {
      if(opt=="TxtPnm") writePnmFromPid(oss, "TxtPnm1", (*liit));
      else oss<<(*liit)<<" ";
    }
  if(opt=="TxtPnm") writePnmFromPid(oss, "TxtPnm2", (*liit));
  else oss<<(*liit);
  strDcyIFSts=oss.str();
  //cout<<i<<"\t"<<strDcyIFSts<<endl<<endl;
}
