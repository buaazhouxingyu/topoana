#include "../include/topoana.h"
#include <cstdlib>

void topoana::getPdfFlFromTexFl()
{
  if(m_anaTasksForSigIds=="T"&&m_vPid_compDcyBrP.size()==0&&m_vCompIncDcyBr.size()==0&&m_vCompIRADcyBr.size()==0&&m_compAnaOfDcyTrs==false&&m_compAnaOfDcyIFSts==false) return;

  string NmOfOptTexFl=m_comNmOfOptFls+".tex";
  string pdflatexcmd="pdflatex "+NmOfOptTexFl;
  system(pdflatexcmd.c_str());
  system(pdflatexcmd.c_str());
  system(pdflatexcmd.c_str());

  string NmOfOptAuxFl=m_comNmOfOptFls+".aux";
  string NmOfOptLogFl=m_comNmOfOptFls+".log";
  string NmOfOptLotFl=m_comNmOfOptFls+".lot";
  string NmOfOptOutFl=m_comNmOfOptFls+".out";
  string rmcmd="rm "+NmOfOptAuxFl+" "+NmOfOptLogFl+" "+NmOfOptLotFl+" "+NmOfOptOutFl;
  system(rmcmd.c_str());
}
