#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

unsigned int topoana::countIncLiaInVlib(list<int> & lia, vector< list<int> > & Vlib)
{
  unsigned int nCount=0;
  if(Vlib.size()==0)
    {
      cerr<<"Infor: The size of the vector is zero!"<<endl<<endl;
      return nCount;
    }

  list<int>::iterator liita;
  unsigned int ibegin;
  unsigned int iend;
  liita=lia.begin();
  // The following if statement is designed for the inclusive decays started directly from the initial e+ and e-.
  if((*liita)==-11)
    {
      ibegin=0;
      iend=1;
    }
  else
    {
      ibegin=1;
      iend=Vlib.size();
    }

  for(unsigned int i=ibegin;i<iend;i++) if(isLiaMatchedWithLib(lia,Vlib[i])) nCount++;

  return nCount;
}
