#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

void topoana::parseIptStrIntoRecStrs(string line, string prompt, string str, string & typeOfTagRec, string & tBrNmOfTagRec, string & tBrNmOfNRec)
{
  typeOfTagRec="";
  tBrNmOfTagRec="";
  tBrNmOfNRec="";

  if(str=="-") return;

  unsigned int nColon=countSubstr(str,":");

  if(nColon<1&&nColon>2)
    {
      cerr<<"Error: ";
      if(nColon==0) cerr<<"No colon (:) is";
      else cerr<<nColon<<" colons (:) are";
      cerr<<" found in the string \""<<str<<"\" from the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: Only one or two colons are allowed in the string. Besides, the string can be just a placeholder \"-\" for the input of the sixth parameter."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  string strbak=str;
  for(unsigned int i=0;i<nColon;i++)
    {
      size_t nPos=str.find(":");
      str.replace(nPos,1," ");
    }

  istringstream iss;
  iss.clear();
  iss.str(str);
  iss>>typeOfTagRec;
  bool isAValidType=false;
  if(nColon==1)
    {
      if(typeOfTagRec=="c"||typeOfTagRec=="n"||typeOfTagRec=="!n"||typeOfTagRec=="p"||typeOfTagRec=="i") isAValidType=true;
    }
  else
    {
      if(typeOfTagRec=="C"||typeOfTagRec=="N"||typeOfTagRec=="!N"||typeOfTagRec=="P"||typeOfTagRec=="I") isAValidType=true;
    }
  if(isAValidType==false)
    {
      cerr<<"Error: The substring \""<<typeOfTagRec<<"\" before the ";
      if(nColon==2) cerr<<"first ";
      cerr<<"colon in the string \""<<strbak<<"\" from the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is not valid!"<<endl<<endl;
      cerr<<"Infor: In the case of one colon in the string, it is allowed to be one of the following five substrings \"c\", \"n\", \"!n\", \"p\", and \"i\", which are designed to restrict the truth instances of the specified particle with its reconstructed \"charge\", \"neutral tag\", \"reversed neutral tag\", \"PDG code\", and \"index\", respectively. In this case, only the TBranch name for the scalar variable of the reconstructed tag is allowed to be put closely after the colon."<<endl<<endl;
      cerr<<"Infor: In the case of two colons in the string, it is allowed to be one of the following five substrings \"C\", \"N\", \"!N\", \"P\", and \"I\", which are designed to restrict the truth instances of the specified particle with its reconstructed \"charge\", \"neutral tag\", \"reversed neutral tag\", \"PDG code\", and \"index\", respectively. In this case, the TBranch name for the array variable of the reconstructed tag should be put closely after the first colon, and the TBranch name for the scalar variable of the number of reconstructed instances of the particle should be put closely after the second colon."<<endl;
      exit(-1);
    }
  iss>>tBrNmOfTagRec;
  if(!iss.eof()) iss>>tBrNmOfNRec;
}
