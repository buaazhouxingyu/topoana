#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::cpBrVals(vector<string> vTypeOfTagRec1, vector<string> vTBrNmOfTagRec1, vector<string> vTBrNmOfNRec1, double * Tagrecsd1, int * Tagrecsi1, int Tagreca1[][20], int * Nrec1, string prompt1, vector<string> vTypeOfTagRec2, vector<string> vTBrNmOfTagRec2, vector<string> vTBrNmOfNRec2, double * Tagrecsd2, int * Tagrecsi2, int Tagreca2[][20], int * Nrec2, string prompt2)
{
  for(unsigned int j=0;j<vTypeOfTagRec1.size();j++)
    {
      if(vTypeOfTagRec1[j]=="c"||vTypeOfTagRec1[j]=="n"||vTypeOfTagRec1[j]=="!n"||vTypeOfTagRec1[j]=="p"||vTypeOfTagRec1[j]=="i")
        {
          if(m_strgTpOfRawIptTopoDat=="MSD")
            {
              for(unsigned int k=0;k<vTypeOfTagRec2.size();k++)
                if(vTBrNmOfTagRec2[k]==vTBrNmOfTagRec1[j])
                  {
                    if(vTypeOfTagRec2[k]==vTypeOfTagRec1[j]) Tagrecsd2[k]=Tagrecsd1[j];
                    else
                      {
                        cerr<<"Error: The same one scalar TBranch \""<<vTBrNmOfTagRec1[j]<<"\" filled in the two setting items prompted with \""<<prompt1<<"\" and \""<<prompt2<<"\" follows two different prompts \""<<vTypeOfTagRec1[k]<<"\" and \""<<vTypeOfTagRec2[j]<<"\", which indicates two different types of reconstruction tags."<<endl;
                        cerr<<"Infor: This is an obvious mistake. Are there any typos in these TBranch names and the prompts before them? Please check them."<<endl<<endl;
                        exit(-1);
                      }
                  }
            }
          else
            {
              for(unsigned int k=0;k<m_vPid_compDcyBrP.size();k++)
                if(vTBrNmOfTagRec2[k]==vTBrNmOfTagRec1[j])
                  {
                    if(vTypeOfTagRec2[k]==vTypeOfTagRec1[j]) Tagrecsi2[k]=Tagrecsi1[j];
                    else
                      {
                        cerr<<"Error: The same one scalar TBranch \""<<vTBrNmOfTagRec1[j]<<"\" filled in the two setting items prompted with \""<<prompt1<<"\" and \""<<prompt2<<"\" follows two different prompts \""<<vTypeOfTagRec1[k]<<"\" and \""<<vTypeOfTagRec2[j]<<"\", which indicates two different types of reconstruction tags."<<endl;
                        cerr<<"Infor: This is an obvious mistake. Are there any typos in these TBranch names and the prompts before them? Please check them."<<endl<<endl;
                        exit(-1);
                      }
                  }
            }
        }
      else if(vTypeOfTagRec1[j]=="C"||vTypeOfTagRec1[j]=="N"||vTypeOfTagRec1[j]=="!N"||vTypeOfTagRec1[j]=="P"||vTypeOfTagRec1[j]=="I")
        {
          for(unsigned int k=0;k<m_vPid_compDcyBrP.size();k++)
            {
              if(vTBrNmOfTagRec2[k]==vTBrNmOfTagRec1[j])
                {
                  if(vTypeOfTagRec2[k]==vTypeOfTagRec1[j])
                    {
                      if(vTBrNmOfNRec2[k]==vTBrNmOfNRec1[j])
                        {
                          Nrec2[k]=Nrec1[j];
                          for(unsigned int l=0;l<((unsigned int) Nrec1[j]);l++) Tagreca2[k][l]=Tagreca1[j][l];
                        }
                      else
                        {
                          cerr<<"Error: The same one array TBranch \""<<vTBrNmOfTagRec1[j]<<"\" filled in the two setting items prompted with \""<<prompt1<<"\" and \""<<prompt2<<"\" is followed by two different scalar TBranches \""<<vTBrNmOfNRec1[k]<<"\" and \""<<vTBrNmOfNRec2[j]<<"\" as its length."<<endl;
                          cerr<<"Infor: This is an obvious mistake. Are there any typos in these TBranch names? Please check them."<<endl<<endl;
                          exit(-1);
                        }
                    }
                  else
                    {
                      cerr<<"Error: The same one array TBranch \""<<vTBrNmOfTagRec1[j]<<"\" filled in the two setting items prompted with \""<<prompt1<<"\" and \""<<prompt2<<"\" follows two different prompts \""<<vTypeOfTagRec1[k]<<"\" and \""<<vTypeOfTagRec2[j]<<"\", which indicates two different types of reconstruction tags."<<endl;
                      cerr<<"Infor: This is an obvious mistake. Are there any typos in these TBranch names and the prompts before them? Please check them."<<endl<<endl;
                      exit(-1);
                    }
                }
              else if(vTBrNmOfNRec2[k]==vTBrNmOfNRec1[j])
                {
                  if(vTypeOfTagRec2[k]==vTypeOfTagRec1[j]) Nrec2[k]=Nrec1[j];
                  else
                    {
                      cerr<<"Error: The same one scalar TBranch \""<<vTBrNmOfNRec1[j]<<"\" filled in the two setting items prompted with \""<<prompt1<<"\" and \""<<prompt2<<"\" follows two different prompts \""<<vTypeOfTagRec1[k]<<"\" and \""<<vTypeOfTagRec2[j]<<"\", which indicates two different types of reconstruction tags."<<endl;
                      cerr<<"Infor: This is an obvious mistake. Are there any typos in these TBranch names and the prompts before them? Please check them."<<endl<<endl;
                      exit(-1);
                    }
                }
            }
        }
    }
}
