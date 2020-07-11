#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::getVIMDcyBr(vector< list<int> > & vDcyBr, vector<int> & vIMDcyBr)
{
  if(vDcyBr.size()==0)
    {
      cerr<<"Error: The size of the vector vDcyBr is 0."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1); 
    }

  vIMDcyBr.clear();

  vIMDcyBr.push_back(-1);
  vIMDcyBr.push_back(0);

  unsigned int iMDcyBr=0;
  list<int>::iterator liit=vDcyBr[0].begin();
  for(unsigned int i=2;i<vDcyBr.size();i++)
    {
      for(unsigned int j=iMDcyBr;j<vDcyBr.size();j++,liit=vDcyBr[j].begin())
        {
          for(liit++;liit!=vDcyBr[j].end();liit++)
            {
              if((*liit)==(*(vDcyBr[i].begin())))
                {
                  iMDcyBr=j;
                  break;
                }
            }
          if(liit!=vDcyBr[j].end()) break;
        }
      vIMDcyBr.push_back(iMDcyBr);
    }
}
