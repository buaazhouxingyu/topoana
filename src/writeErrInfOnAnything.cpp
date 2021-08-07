#include "../include/topoana.h"
#include <iostream>
#include <cstdlib>

void topoana::writeErrInfOnAnything(int pid, string typeOfTagRec)
{
  if(pid==m_pidOfAnything)
    {
      if(typeOfTagRec!="i"&&typeOfTagRec!="I")
        {
          cerr<<"  Error: \"*\" denoting \"anything\" presents in the first argument position as a particle name!"<<endl;
          cerr<<"  Error: This is not allowed unless the reconstruction tag type is index (\"i\" or \"I\")."<<endl;
          cerr<<"  Infor: Please check and correct it."<<endl;
          exit(-1);
        }
      if(m_ccSwitch==true)
        {
          cerr<<"  Warning: Since the particle name is unspecific, the setting item on charge conjugation does not work for this setting."<<endl;
          cerr<<"  Infor: If not used for other settings, the setting item on charge conjugation is better to be removed, in order to make the tables listed in the txt, tex, and pdf files more concise."<<endl;
        }
    }
}
