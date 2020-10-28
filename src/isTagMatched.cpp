#include "../include/topoana.h"

// The last parameter "Tagtruth" is the PDG code of the current truth instance of the specified particle in the cases where the type of the reconstructed tag is "c", "n", "!n", "p", "C", "N", "!N", or "P", while it is the raw index of the current truth instance of the specified particle in the case where the type of the reconstructed tag is "i" or "I".
bool topoana::isTagMatched(string typeOfTagrec, int Tagrecs, int * Tagreca, int Nrec, int Tagtruth)
{
  bool isTagMatched=false;

  if(typeOfTagrec=="c"||typeOfTagrec=="n"||typeOfTagrec=="!n"||typeOfTagrec=="p"||typeOfTagrec=="i")
    {
      if(typeOfTagrec=="c")
        {
          if(m_pid3PchrgMap[Tagtruth]==3*Tagrecs) isTagMatched=true;
        }
      else if(typeOfTagrec=="n")
        {
          if(m_pidIccPMap[Tagtruth]==Tagrecs) isTagMatched=true;
        }
      else if(typeOfTagrec=="!n")
        {
          if(m_pidIccPMap[Tagtruth]==(-1)*Tagrecs) isTagMatched=true;
        }
      else if(typeOfTagrec=="p")
        {
          if(Tagtruth==Tagrecs) isTagMatched=true;
        }
      else if(typeOfTagrec=="i")
        {
          if(Tagtruth==Tagrecs) isTagMatched=true;
        }
    }
  else if(typeOfTagrec=="C"||typeOfTagrec=="N"||typeOfTagrec=="!N"||typeOfTagrec=="P"||typeOfTagrec=="I")
    {
      for(unsigned int i=0;i<((unsigned int) Nrec);i++)
        {
          if(typeOfTagrec=="C")
            {
              if(m_pid3PchrgMap[Tagtruth]==3*Tagreca[i]) isTagMatched=true;
            }
          else if(typeOfTagrec=="N")
            {
              if(m_pidIccPMap[Tagtruth]==Tagreca[i]) isTagMatched=true;
            }
          else if(typeOfTagrec=="!N")
            {
              if(m_pidIccPMap[Tagtruth]==(-1)*Tagreca[i]) isTagMatched=true;
            }
          else if(typeOfTagrec=="P")
            {
              if(Tagtruth==Tagreca[i]) isTagMatched=true;
            }
          else if(typeOfTagrec=="I")
            {
              if(Tagtruth==Tagreca[i]) isTagMatched=true;
            }
          if(isTagMatched==true) break;
        }
    }

  return isTagMatched;
}
