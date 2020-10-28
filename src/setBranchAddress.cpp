#include "../include/topoana.h"
#include "TChain.h"

void topoana::setBranchAddress(vector<string> vTypeOfTagRec, vector<string> vTBrNmOfTagRec, vector<string> vTBrNmOfNRec, TChain * chn, double * Tagrecsd, int * Tagrecsi, int Tagreca[][20], int * Nrec)
{
  for(unsigned int i=0;i<vTypeOfTagRec.size();i++)
    {
      if(vTypeOfTagRec[i]!="")
        {
          if(vTypeOfTagRec[i]=="c"||vTypeOfTagRec[i]=="n"||vTypeOfTagRec[i]=="!n"||vTypeOfTagRec[i]=="p"||vTypeOfTagRec[i]=="i")
            {
              if(m_strgTpOfRawIptTopoDat=="MSD") chn->SetBranchAddress(vTBrNmOfTagRec[i].c_str(), &Tagrecsd[i]); 
              else chn->SetBranchAddress(vTBrNmOfTagRec[i].c_str(), &Tagrecsi[i]);
            }
          else if(vTypeOfTagRec[i]=="C"||vTypeOfTagRec[i]=="N"||vTypeOfTagRec[i]=="!N"||vTypeOfTagRec[i]=="P"||vTypeOfTagRec[i]=="I")
            {
              chn->SetBranchAddress(vTBrNmOfTagRec[i].c_str(), &Tagreca[i]);
              chn->SetBranchAddress(vTBrNmOfNRec[i].c_str(), &Nrec[i]);
            }
        }
    }
}
