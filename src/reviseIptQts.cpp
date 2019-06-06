#include "../include/topoana.h"
#include <cmath>
void topoana::reviseIptQts(double & Npsd, double Pidd[], double Midxd[], int & Nps, int Pid[], int Midx[])
{
  const unsigned int Npsi=Npsd;
  int newIdx=0;
  int NewIdx[Npsi];
  for(unsigned int i=0;i<Npsi;i++)
    {
      if(isnormal(Pidd[i])||(Pidd[i]==-999))
        {
          NewIdx[i]=newIdx;
          newIdx++;
        }
      else
        {
          NewIdx[i]=-1;
        }
    }
  Nps=newIdx;
  for(unsigned int i=0;i<Npsi;i++)
    {
      if(NewIdx[i]!=-1)
        {
          newIdx=NewIdx[i];
          Pid[newIdx]=Pidd[i];
          if((Midxd[i]!=-999)&&(Midxd[i]!=i)&&(NewIdx[int(Midxd[i])]!=-1)) Midx[newIdx]=NewIdx[int(Midxd[i])];
          else Midx[newIdx]=-1;
        }
    }  
}
