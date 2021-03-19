#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

// This method is specially added for the setting item with the prompt "% Use the particle list from Belle for the B2BII analyses (Two options: Y and N. Default: N)", because this setting item should be read before the makeMapsOnPdata method.

void topoana::readCard0(string cardFlNm)
{
  ifstream fin(cardFlNm.c_str(),ios::in);
  if(!fin)
    {
      cerr<<"Error: Can't open the card file \""<<m_cardFlNm<<"\"!"<<endl;
      if(m_cardFlNm=="topoana.card")
        {
          cerr<<"Infor: The card file name is the default one."<<endl;
          cerr<<"Infor: Do you forget to append the name of your own card file to the end of the executable?"<<endl;
          cerr<<"Infor: If yes, please specify it along with the executable by the command line \"[path/]topoana.exe nameOfYourOwnCardFile\""<<endl;
          cerr<<"Infor: For the details on the usage of the command, please execute \"[path/]topoana.exe --help\""<<endl;
        }
      else
        {
          cerr<<"Infor: Please check it."<<endl;
        }
      exit(-1);
    }  

  cout<<endl<<"Reading the card file: "<<cardFlNm<<" for the setting item for the B2BII analyses."<<endl<<endl;

  string line="";
  while(!fin.eof())      
    {
      while(!fin.eof())
        {
          getline(fin,line);
          trim(line);
          if(!line.empty()&&line[0]!='#') break;
        }
      if(line.empty()||line[0]=='#')
        {
          break;
        }
      else if(line=="% Use the particle list from Belle for the B2BII analyses (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Use the particle list from Belle for the B2BII analyses (Two options: Y and N. Default: N)", m_usePlistFromBelle);
        }
    }
}
