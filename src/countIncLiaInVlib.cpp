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
  unsigned int iend;
  liita=lia.begin();
  // The following if statement is designed for the inclusive decays started directly from the initial particles.
  if((*liita)==m_pidOfISt2) iend=1;
  else iend=Vlib.size();

  for(unsigned int i=0;i<iend;i++) if(isLiaMatchedWithLib(lia,Vlib[i])) nCount++;

  return nCount;
}
