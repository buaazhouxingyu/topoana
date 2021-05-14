#include "../include/topoana.h"
#include <iostream>

void topoana::writeInputRecInfo(string typeOfTagRec, string tBrNmOfTagRec, string tBrNmOfNRec, string object)
{
  if(typeOfTagRec!="")
    {
      cout<<"  The reconstructed ";
      if(typeOfTagRec=="c"||typeOfTagRec=="C") cout<<"charge";
      else if(typeOfTagRec=="n"||typeOfTagRec=="N") cout<<"neutral tag";
      else if(typeOfTagRec=="!n"||typeOfTagRec=="!N") cout<<"reversed neutral tag";
      else if(typeOfTagRec=="p"||typeOfTagRec=="P") cout<<"PDG code";
      else if(typeOfTagRec=="i"||typeOfTagRec=="I") cout<<"index";
      cout<<" of the "<<object<<", stored in the ";
      if(typeOfTagRec=="c"||typeOfTagRec=="n"||typeOfTagRec=="!n"||typeOfTagRec=="p"||typeOfTagRec=="i") cout<<"scalar";
      else if(typeOfTagRec=="C"||typeOfTagRec=="N"||typeOfTagRec=="!N"||typeOfTagRec=="P"||typeOfTagRec=="I") cout<<"array";
      cout<<" TBranch \""<<tBrNmOfTagRec<<"\", is specified to restrict its truth instances."<<endl;
      if(typeOfTagRec=="C"||typeOfTagRec=="N"||typeOfTagRec=="!N"||typeOfTagRec=="P"||typeOfTagRec=="I")
        {
          cout<<"  In addition, the number of reconstructed instances of the "<<object<<" is stored in the TBranch \""<<tBrNmOfNRec<<"\" as the length of the array."<<endl;
        }
    }
  else
    {
      if(m_vbsLevStdOut==true) cout<<"  No reconstruction information to restrict the truth instances of the "<<object<<" is specified (default)."<<endl;
    }
}
