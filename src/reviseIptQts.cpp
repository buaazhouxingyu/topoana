#include "../include/topoana.h"
#include <cmath>
void topoana::reviseIptQts(double & Npsd, double Pidd[], double Midxd[], int & Nps, int Pid[], int Midx[])
{
  int idx=0;
  const unsigned int Npsi=Npsd;
  int Idx[Npsi];
  for(unsigned int i=0;i<Npsi;i++)
    {
      if(isnormal(Pidd[i]))
        {
          Idx[i]=idx;
          idx++;
        }
      else
        {
          Idx[i]=-1;
        }
    }
  Nps=idx;
  for(unsigned int i=0;i<Npsi;i++)
    {
      if(Idx[i]!=-1)
        {
          idx=Idx[i];
          Pid[idx]=Pidd[i];
          if(Midxd[i]!=i&&Idx[int(Midxd[i])]!=-1) Midx[idx]=Idx[int(Midxd[i])];
          else Midx[idx]=-1;
        }
    }  
} 
