#include "../include/topoana.h"
#include "TTree.h"
#include "TBranch.h"
#include <iostream>

void topoana::findBranch(string nmOfIptRootFl, string ttrNm, TTree * tr, vector<string> vTypeOfTagRec, vector<string> vTBrNmOfTagRec, vector<string> vTBrNmOfNRec, bool & allIptsAreOK, string prompt)
{
  for(unsigned int i=0;i<vTypeOfTagRec.size();i++)
    {
      if(vTypeOfTagRec[i]!="")
        {
          TBranch * br;
          if(vTypeOfTagRec[i]=="c"||vTypeOfTagRec[i]=="n"||vTypeOfTagRec[i]=="!n"||vTypeOfTagRec[i]=="p"||vTypeOfTagRec[i]=="i"||vTypeOfTagRec[i]=="C"||vTypeOfTagRec[i]=="N"||vTypeOfTagRec[i]=="!N"||vTypeOfTagRec[i]=="P"||vTypeOfTagRec[i]=="I")
            {
              br=tr->FindBranch(vTBrNmOfTagRec[i].c_str());
              if(!br)
                {
                  cerr<<"Error: The ttree \""<<ttrNm<<"\" in the input root file \""<<nmOfIptRootFl<<"\" does not contain a tbranch named \""<<vTBrNmOfTagRec[i]<<"\"!"<<endl;
                  cerr<<"Infor: The tbranch is filled in the setting item prompted with \""<<prompt<<"\"."<<endl;
                  cerr<<"Infor: It is expected to be ";
                  if(vTypeOfTagRec[i]=="c"||vTypeOfTagRec[i]=="n"||vTypeOfTagRec[i]=="!n"||vTypeOfTagRec[i]=="p"||vTypeOfTagRec[i]=="i") cerr<<"a scalar";
                  else if(vTypeOfTagRec[i]=="C"||vTypeOfTagRec[i]=="N"||vTypeOfTagRec[i]=="!N"||vTypeOfTagRec[i]=="P"||vTypeOfTagRec[i]=="I") cerr<<"an array";
                  cerr<<" tbranch, which stores the reconstructed ";
                  if(vTypeOfTagRec[i]=="c"||vTypeOfTagRec[i]=="C") cerr<<"charge";
                  else if(vTypeOfTagRec[i]=="n"||vTypeOfTagRec[i]=="N") cerr<<"neutral tag";
                  else if(vTypeOfTagRec[i]=="!n"||vTypeOfTagRec[i]=="!N") cerr<<"reversed neutral tag";
                  else if(vTypeOfTagRec[i]=="p"||vTypeOfTagRec[i]=="P") cerr<<"PDG code";
                  else if(vTypeOfTagRec[i]=="i"||vTypeOfTagRec[i]=="I") cerr<<"index";
                  cerr<<" of the particle, in order to restrict its truth instances."<<endl;
                  cerr<<"Infor: Please check it."<<endl<<endl;
                  allIptsAreOK=false;
                }
            }
          if(vTypeOfTagRec[i]=="C"||vTypeOfTagRec[i]=="N"||vTypeOfTagRec[i]=="!N"||vTypeOfTagRec[i]=="P"||vTypeOfTagRec[i]=="I")
            {
              br=tr->FindBranch(vTBrNmOfNRec[i].c_str());
              if(!br)
                {
                  cerr<<"Error: The ttree \""<<ttrNm<<"\" in the input root file \""<<nmOfIptRootFl<<"\" does not contain a tbranch named \""<<vTBrNmOfNRec[i]<<"\"!"<<endl;
                  cerr<<"Infor: The tbranch is filled in the setting item prompted with \""<<prompt<<"\"."<<endl;
                  cerr<<"Infor: It is expected to be a scalar tbranch, which stores the number of reconstructed instances of the particle, as the length of the array tbranch it follows."<<endl;
                  cerr<<"Infor: Please check it."<<endl<<endl;
                  allIptsAreOK=false;
                }
            }
        }
    }
}
