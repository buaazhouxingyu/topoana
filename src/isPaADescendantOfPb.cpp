#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

bool topoana::isPaADescendantOfPb(vector<int> vMidx, int idxA, int idxB)
{
  if(idxA<0||((unsigned int) idxA)>=vMidx.size())
    {
      cerr<<"Error: The integer \"idxA\" is not a reasonable index for the vector \"vMidx\"!"<<endl;
      cerr<<"Infor: The integer \"idxA\" is "<<idxA<<"."<<endl;
      cerr<<"Infor: The size of the vector \"vMidx\" is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(idxB<0||((unsigned int) idxB)>=vMidx.size())
    {
      cerr<<"Error: The integer \"idxB\" is not a reasonable index for the vector \"vMidx\"!"<<endl;
      cerr<<"Infor: The integer \"idxB\" is "<<idxB<<"."<<endl;
      cerr<<"Infor: The size of the vector \"vMidx\" is "<<vMidx.size()<<"."<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(idxA<idxB)
    {
      cerr<<"Error: The integer \"idxA\" is less than the integer \"idxB\"!"<<endl;
      cerr<<"Infor: The integer \"idxA\" is "<<idxA<<"."<<endl;
      cerr<<"Infor: The integer \"idxB\" is "<<idxB<<"."<<endl;
      cerr<<"Infor: The integer \"idxA\" should be greater than the integer \"idxB\"!"<<endl;
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  while(vMidx[idxA]!=idxA)
    {
      if(vMidx[idxA]==idxB) return true;
      else idxA=vMidx[idxA];
    }

  return false;
}
