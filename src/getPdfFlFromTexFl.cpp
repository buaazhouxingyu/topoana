#include "../include/topoana.h"
#include <fstream>
#include <cstdlib>

void topoana::getPdfFlFromTexFl()
{
  if(m_anaTasksForSigIds=="T"&&m_vPid_compDcyBrP.size()==0&&m_vCompIncDcyBr.size()==0&&m_vCompIRADcyBr.size()==0&&m_compAnaOfDcyTrs==false&&m_compAnaOfDcyIFSts==false) return;

  string NmOfOptTexFl=m_comNmOfOptFls+".tex";

  //string pdflatexcmd="pdflatex "+NmOfOptTexFl;
  // The following eight lines of code is used to replace the statement above, in order to write the pdf file to the directory of the tex source file, in the cases where the tex source file is not in the current working directory.
  string optDir;
  string dirnamecmd="dirname "+NmOfOptTexFl+" > dirname.txt";
  system(dirnamecmd.c_str());
  ifstream fin("dirname.txt",ios::in);
  fin>>optDir;

  string pdflatexcmd;
  if(optDir==".") pdflatexcmd="pdflatex "+NmOfOptTexFl;
  else pdflatexcmd="pdflatex -output-directory="+optDir+" "+NmOfOptTexFl;
  system(pdflatexcmd.c_str());
  system(pdflatexcmd.c_str());
  system(pdflatexcmd.c_str());

  string NmOfOptAuxFl=m_comNmOfOptFls+".aux";
  string NmOfOptLogFl=m_comNmOfOptFls+".log";
  string NmOfOptLotFl=m_comNmOfOptFls+".lot";
  string NmOfOptOutFl=m_comNmOfOptFls+".out";
  string rmcmd="rm dirname.txt "+NmOfOptAuxFl+" "+NmOfOptLogFl+" "+NmOfOptLotFl+" "+NmOfOptOutFl;
  system(rmcmd.c_str());
}
