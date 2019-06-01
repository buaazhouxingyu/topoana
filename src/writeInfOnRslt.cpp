#include "../include/topoana.h"
#include <iostream>

void topoana::writeInfOnRslt()
{
  if(m_anaTasksForSigIds!="T")
    {
      cout<<endl;
      unsigned int Nasterisks=89; 
      for(unsigned int i=0;i<Nasterisks;i++) cout<<"*";
      cout<<endl<<endl;
    }
  cout<<"Tips on the results:"<<endl<<endl;
  string NmOfOptPdfFl=m_mainNmOfOptFls+".pdf";
  string NmOfOptTexFl=m_mainNmOfOptFls+".tex";
  string NmOfOptTxtFl=m_mainNmOfOptFls+".txt";
  string NmOfOptRootFl1st=m_mainNmOfOptFls+".root";
  string NmOfOptRootFlRest=m_mainNmOfOptFls+"_n.root";
  if(m_anaTasksForSigIds=="TC")
    {
      cout<<"1. Statistics of topology are summarized in the following three files: "<<NmOfOptPdfFl<<", "<<NmOfOptTexFl<<" and "<<NmOfOptTxtFl<<". Although they are in different formats, they have the same information. The pdf file is the easiest to read. It is converted from the tex file by the \"pdflatex\" command. If necessary, you could check and see the txt file (with text processing commands)."<<endl<<endl;
      cout<<"2. Tags of topology are inserted in all the entries of the TTree \""<<m_trNm<<"\" of the output root file (files): "<<NmOfOptRootFl1st<<"(and "<<NmOfOptRootFlRest<<" if any)"<<". Except for this, the TTree \""<<m_trNm<<"\" of The output root file is entirely the same as that (those) of the input root file (files). Besides, the topology tags are identical with those listed in the txt/tex/pdf files."<<endl;
    }
  else if(m_anaTasksForSigIds=="T")
    {
      cout<<"    Tags of topology are inserted in all the entries of the TTree \""<<m_trNm<<"\" of the output root file (files): "<<NmOfOptRootFl1st<<"(and "<<NmOfOptRootFlRest<<" if any)."<<endl;
    }
  else if(m_anaTasksForSigIds=="C")
    {
      cout<<"    Statistics of topology are summarized in the following three files: "<<NmOfOptPdfFl<<", "<<NmOfOptTexFl<<" and "<<NmOfOptTxtFl<<". Although they are in different formats, they have the same information. The pdf file is the easiest to read. It is converted from the tex file by the \"pdflatex\" command. If necessary, you could check and see the txt file (with text processing commands)."<<endl<<endl;
    }
}
