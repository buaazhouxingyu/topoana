#include "../include/topoana.h"
#include <sstream>
#include <iostream>

void topoana::getStrFromVli(vector< list<int> > & dcyTr, string & strDcyTr)
{
  ostringstream oss;  
  oss.str("");
  list<int> dcyBr;
  for(unsigned int i=0;i<dcyTr.size();i++)
    {
      if(i==0&&m_iStPsSwitch==true&&dcyTr[0].size()==3) continue;
      dcyBr.clear();
      dcyBr=dcyTr[i];
      list<int>::iterator liit=dcyBr.begin();
      oss<<(*liit)<<" ";
      // The condition "i==0" is set for the initial state particle pair e+e-;the condition "(*liit)==1, 2, 3, 4, 5 or 6" is set for the intermediate state quark pair ddbar, uubar, ssbar, ccbar, bbbar or ttbar;
      if(i==0||(*liit)==1||(*liit)==2||(*liit)==3||(*liit)==4||(*liit)==5||(*liit)==6)
        {
          liit++;
          oss<<(*liit)<<" ";
        }
      oss<<"> ";
      list<int>::iterator liitTmp=dcyBr.end();
      liitTmp--;
      for(liit++;liit!=liitTmp;liit++) oss<<(*liit)<<" ";
      oss<<(*liit);
      if(i!=(dcyTr.size()-1)) oss<<", ";
    }
  strDcyTr=oss.str();
  //cout<<i<<"\t"<<strDcyTr<<endl<<endl;
}
