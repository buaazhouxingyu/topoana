#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::cpBrVals2(vector<string> vTBrNmOfTagRec, vector<string> vTypeOfTagRec, int * Nrec, int Tagreca[][20], int * Tagrecsi, float * Tagrecsf, double * Tagrecsd)
{
  for(unsigned int i=0;i<vTBrNmOfTagRec.size();i++)
    {
      for(unsigned int j=vTBrNmOfTagRec.size()-1;j>i;j--)
        {
          if(vTBrNmOfTagRec[i]==vTBrNmOfTagRec[j]&&vTypeOfTagRec[i]==vTypeOfTagRec[j])
            {
              if(vTypeOfTagRec[i]=="c"||vTypeOfTagRec[i]=="n"||vTypeOfTagRec[i]=="!n"||vTypeOfTagRec[i]=="p"||vTypeOfTagRec[i]=="i")
                {
                  if(m_strgTpOfRawIptTopoDat=="AOI"||m_strgTpOfRawIptTopoDat=="VOI"||m_strgTpOfRawIptTopoDat=="MSI") Tagrecsi[i]=Tagrecsi[j];
                  else if(m_strgTpOfRawIptTopoDat=="MSF") Tagrecsf[i]=Tagrecsf[j];
                  else if(m_strgTpOfRawIptTopoDat=="MSD"||m_strgTpOfRawIptTopoDat=="MSID") Tagrecsd[i]=Tagrecsd[j];
                }
              else if(vTypeOfTagRec[i]=="C"||vTypeOfTagRec[i]=="N"||vTypeOfTagRec[i]=="!N"||vTypeOfTagRec[i]=="P"||vTypeOfTagRec[i]=="I")
                {
                  if(m_strgTpOfRawIptTopoDat=="AOI"||m_strgTpOfRawIptTopoDat=="VOI"||m_strgTpOfRawIptTopoDat=="MSI")
                    {
                      Nrec[i]=Nrec[j];
                      for(unsigned int k=0;k<((unsigned int) Nrec[j]);k++) Tagreca[i][k]=Tagreca[j][k];
                    }
                  else
                    {
                      cerr<<"Error: The reconstruction tags are not supported to be stored in the arrays of float numbers and the arrays of double precision numbers in the current version of the program!"<<endl; 
                      cerr<<"Infor: Please contact me (zhouxy@lnnu.edu.cn) if you have to store the reconstruction tags in the arrays of float numbers and the arrays of double precision numbers and use them in the TopoAna program."<<endl;
                      exit(-1);
                    }
                }
              break;
            }
        }
    }
}
