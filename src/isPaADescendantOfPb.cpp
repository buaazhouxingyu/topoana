#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

bool topoana::isPaADescendantOfPb(vector<int> vMidx, unsigned int idxA, unsigned int idxB)
{
  if(idxA<0||idxA>=vMidx.size())
    {
      cerr<<"Error: The unsigned integer \"idxA\" is not a reasonable index for the vector \"vMidx\"!"<<endl;
      cerr<<"Infor: The unsigned integer \"idxA\" is "<<idxA<<"."<<endl;
      cerr<<"Infor: The size of the vector \"vMidx\" is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(idxB<0||idxB>=vMidx.size())
    {
      cerr<<"Error: The unsigned integer \"idxB\" is not a reasonable index for the vector \"vMidx\"!"<<endl;
      cerr<<"Infor: The unsigned integer \"idxB\" is "<<idxB<<"."<<endl;
      cerr<<"Infor: The size of the vector \"vMidx\" is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(idxA<idxB)
    {
      cerr<<"Error: The unsigned integer \"idxA\" is less than the unsigned integer \"idxB\"!"<<endl;
      cerr<<"Infor: The unsigned integer \"idxA\" is "<<idxA<<"."<<endl;
      cerr<<"Infor: The unsigned integer \"idxB\" is "<<idxB<<"."<<endl;
      cerr<<"Infor: The unsigned integer \"idxA\" should be greater than the unsigned integer \"idxB\"!"<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  while(((unsigned int) vMidx[idxA])!=idxA)
    {
      if(((unsigned int) vMidx[idxA])==idxB) return true;
      else idxA=vMidx[idxA];
    }

  return false;
}
