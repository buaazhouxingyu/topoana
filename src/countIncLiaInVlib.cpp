#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

unsigned int topoana::countIncLiaInVlib(list<int> & lia, vector< list<int> > & Vlib, vector<int> vIdxOfHead, int * Ridx, vector<int> vIdxOrg, string typeOfTagRec, int tagrecsi, int * tagreca, int nrec)
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

  bool _isTagMatched;
  for(unsigned int i=0;i<iend;i++)
    {
      if(typeOfTagRec!="")
        {
          if(typeOfTagRec!="i"&&typeOfTagRec!="I") _isTagMatched=isTagMatched(typeOfTagRec, tagrecsi, tagreca, nrec, (*liita));
          else _isTagMatched=isTagMatched(typeOfTagRec, tagrecsi, tagreca, nrec, Ridx[vIdxOrg[vIdxOfHead[i]]]);
          if(_isTagMatched==false) continue;
        }
      if(isLiaMatchedWithLib(lia,Vlib[i])) nCount++;
    }

  return nCount;
}
