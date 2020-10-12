#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

bool topoana::isLiaMatchedWithLib(list<int> & lia, list<int> & lib, string option)
{
  if(lia.size()<2)
    {
      cerr<<"Infor: The size of the first list is less than two!"<<endl<<endl;
      exit(-1);
    }
  if(lib.size()<2)
    {
      cerr<<"Infor: The size of the second list is less than two!"<<endl<<endl;
      exit(-1);
    }

  /*cout<<"The first list:"<<endl;
  for(list<int>::iterator liita=lia.begin();liita!=lia.end();liita++) cout<<(*liita)<<endl;
  cout<<"The second list:"<<endl;
  for(list<int>::iterator liitb=lib.begin();liitb!=lib.end();liitb++) cout<<(*liitb)<<endl;*/
  
  list<int>::iterator liita=lia.begin();
  list<int>::iterator liitb=lib.begin();
  if((*liitb)!=(*liita))
    {
      return false;
    }
  else
    {
      // The following if statement is designed for the inclusive decays started directly from the initial particles.
      if((*liita)==m_pidOfISt2)
        {
          liita++;
          liitb++;
          if((*liitb)!=(*liita)) return false;
        }
      // The logic in the block should be considered seriously again!
      for(liita++;(liita!=lia.end())&&(liitb!=lib.end());liita++)
        {
          for(liitb++;liitb!=lib.end();liitb++)
            {
              if((*liitb)==(*liita)) break; 
              else if(option=="Is"&&(*liitb)!=m_pidOfSISRGam) return false;
              else if(option=="Ig"&&(*liitb)!=m_pidOfGISRGam) return false;
              else if(option=="Fs"&&(*liitb)!=m_pidOfSFSRGam) return false;
              else if(option=="Fg"&&(*liitb)!=m_pidOfGFSRGam) return false;
              // The four else if statements above are added to restrict the remaining particles unspecified in the inclusive decay to strict ISR, generalized ISR, strict FSR, and generalized FSR photons, respectively. The logic involved here is somewhat complicated, please think it carefully.
            }
        }
      if(liitb==lib.end()) return false;
      else return true;
    }
}
