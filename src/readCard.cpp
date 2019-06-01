#include "../include/topoana.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>

void topoana::readCard(string cardFlNm)
{
  ifstream fin(cardFlNm.c_str(),ios::in);
  if(!fin)
    {
      cerr<<"Error: Can't open the card file \""<<m_cardFlNm<<"\"!"<<endl;
      if(m_cardFlNm=="topoana.card")
        {
          cerr<<"Infor: The card file name is the default one."<<endl;
          cerr<<"Infor: Do you forget to append the name of your own card file to the end of the executable?"<<endl;
          cerr<<"Infor: If yes, please specify it along with the executable by the command line \"(pathOfTheExecutable/)topoana.exe nameOfYourOwnCardFile\""<<endl;
        }
      else
        {
          cerr<<"Infor: Please check it."<<endl;
        }
      exit(-1);
    }  

  cout<<endl<<"Reading the card file: "<<cardFlNm<<" ..."<<endl<<endl;

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
      else if(line=="% Names of input root files")
        {
          readOpenCurly(fin,line,"% Names of input root files");
          read1stLineOrCloseCurly(fin,line,true,"No root file names are found in the item with the prompt \"% Names of input root files");
          m_nmsOfIptRootFls.push_back(line);
          while(1)
            {
              readExtraLinesOrCloseCurly(fin,line,"% Names of input root files");
              if(line=="}")
                {
                  break;
                }
              else 
                {
                  m_nmsOfIptRootFls.push_back(line);
                }
            }
	}
      else if(line=="% Tree name")
        {
          readOpenCurly(fin,line,"% Tree name");
          read1stLineOrCloseCurly(fin,line,true,"No tree name is found in the item with the prompt \"% Tree name");
          m_trNm=line;
          readCloseCurly(fin,line,"% Tree name");
        }
      else if(line=="% Storage type of the raw input topology data (Four options: AI, VI, MIV, and MDV. Default: AI)")
        {
          readOpenCurly(fin,line,"% Storage type of the raw input topology data (Four options: AI, VI, MIV, and MDV. Default: AI)");
          m_strgTpOfRawIptTopoDat="AI";
          read1stLineOrCloseCurly(fin,line,false,"% Storage type of the raw input topology data (Four options: AI, VI, MIV, and MDV. Default: AI)");
          if(line!="}")
            {
              if(line=="AI"||line=="VI"||line=="MIV"||line=="MDV")
                {
                  m_strgTpOfRawIptTopoDat=line;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Storage type of the raw input topology data\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"AI\", \"VI\", \"MIV\" or \"MDV\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Storage type of the raw input topology data (Four options: AI, VI, MIV, and MDV. Default: AI)");
            }
        }
      else if(line=="% Branch name of the number of particles (Default: nMCGen)")
        {
          readOpenCurly(fin,line,"% Branch name of the number of particles (Default: nMCGen)");
          read1stLineOrCloseCurly(fin,line,false,"No branch name of the number of particles is found in the item with the prompt \"% Branch name of the number of particles (Default: nMCGen)");
          if(line!="}")
            {
              m_brNmOfNps=line;
              readCloseCurly(fin,line,"% Branch name of the number of particles (Default: nMCGen)");
            }
        }
      else if(line=="% Branch name of the PDG codes of particles (Default: MCGenPDG)")
        {
          readOpenCurly(fin,line,"% Branch name of the PDG codes of particles (Default: MCGenPDG)");
          read1stLineOrCloseCurly(fin,line,false,"No branch name of the PDG codes of particles is found in the item with the prompt \"% Branch name of the PDG codes of particles (Default: MCGenPDG)");
          if(line!="}")
            {
              m_brNmOfPid=line;
              readCloseCurly(fin,line,"% Branch name of the PDG codes of particles (Default: MCGenPDG)");     
            }
        }
      else if(line=="% Branch name of the mother indeces of particles (Default: MCGenMothIndex)")
        {
          readOpenCurly(fin,line,"% Branch name of the mother indeces of particles (Default: MCGenMothIndex)");
          read1stLineOrCloseCurly(fin,line,false,"No branch name of the mother indeces of particles is found in the item with the prompt \"% Branch name of the mother indeces of particles (Default: MCGenMothIndex)");
          if(line!="}")
            {
              m_brNmOfMidx=line;
              readCloseCurly(fin,line,"% Branch name of the mother indeces of particles (Default: MCGenMothIndex)");  
            }
        }
      else if(line=="% Maximum number of entries to be processed")
        {
          readOpenCurly(fin,line,"% Maximum number of entries to be processed");
          m_nEtrsMax=ULONG_MAX;
          read1stLineOrCloseCurly(fin,line,false,"% Maximum number of entries to be processed");
          if(line!="}")
            {
              if(line.find_first_not_of("0123456789")==string::npos) m_nEtrsMax=strtoul(line.c_str(),NULL,10);
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Maximum number of entries to be processed\" is invalid!"<<endl;
                  cerr<<"Infor: It should be an unsigned long integer if it is not left empty."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Maximum number of entries to be processed");
            }
        }
      else if(line=="% Cut to select entries")
        {
          readOpenCurly(fin,line,"% Cut to select entries");
          read1stLineOrCloseCurly(fin,line,false,"% Cut to select entries");
          if(line!="}")
            {
              m_cut=line;
              readCloseCurly(fin,line,"% Cut to select entries");
            }
        }
      else if(line=="% Method to apply cut to array variables (Two options: T and F. Default: F)")
        {
          readOpenCurly(fin,line,"% Method to apply cut to array variables (Two options: T and F. Default: F)");
          read1stLineOrCloseCurly(fin,line,false,"% Method to apply cut to array variables (Two options: T and F. Default: F)");
          if(line!="}")
            {
              if(line=="T")
                {
                  m_cutMethod=true;
                }
              else if(line=="F")
                {
                  m_cutMethod=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Method to apply cut to array variables\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"T\" or \"F\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                } 
              readCloseCurly(fin,line,"% Method to apply cut to array variables (Two options: T and F. Default: F)");
            }
        }
      else if(line=="% Maximum hierarchy of heading decay branches to be processed in each event")
        {
          readOpenCurly(fin,line,"% Maximum hierarchy of heading decay branches to be processed in each event");
          m_hHdDcyBrsMax=UINT_MAX;
          read1stLineOrCloseCurly(fin,line,false,"% Maximum hierarchy of heading decay branches to be processed in each event");
          if(line!="}")
            {
              if(line.find_first_not_of("0123456789")==string::npos) m_hHdDcyBrsMax=strtoul(line.c_str(),NULL,10);
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Maximum hierarchy of heading decay branches to be processed in each event\" is invalid!"<<endl;
                  cerr<<"Infor: It should be an unsigned integer if it is not left empty."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Maximum hierarchy of heading decay branches to be processed in each event");
            }
        }
      else if(line=="% Ignore the decay of the following particles")
        {
          readOpenCurly(fin,line,"% Ignore the decay of the following particles");
          read1stLineOrCloseCurly(fin,line,false,"% Ignore the decay of the following particles");
          if(line!="}")
            {
              int pid=getPidFromTxtPnm(line);
              m_vIdPid.push_back(pid);
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Ignore the decay of the following particles");
                  if(line=="}")
                    {
                      break;
                    }
                  else
                    {
                      pid=getPidFromTxtPnm(line);
                      m_vIdPid.push_back(pid);
                    }
                }
            }
        }
      else if(line=="% Ignore the decay of the daughters of the following particles")
        {
          readOpenCurly(fin,line,"% Ignore the decay of the daughters of the following particles");
          read1stLineOrCloseCurly(fin,line,false,"% Ignore the decay of the daughters of the following particles");
          if(line!="}")
            {
              int pid=getPidFromTxtPnm(line);
              m_vIddPid.push_back(pid);
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Ignore the decay of the daughters of the following particles");
                  if(line=="}")
                    {
                      break;
                    }
                  else
                    {
                      pid=getPidFromTxtPnm(line);
                      m_vIddPid.push_back(pid);
                    }
                }
            }
        }
      else if(line=="% Ignore gISR photons (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Ignore gISR photons (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Ignore gISR photons (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_ignoreGISR=true;
                }
              else if(line=="N")
                {
                  m_ignoreGISR=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Ignore gISR photons\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Ignore gISR photons (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Ignore gFSR photons (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Ignore gFSR photons (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Ignore gFSR photons (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_ignoreGFSR=true;
                }
              else if(line=="N")
                {
                  m_ignoreGFSR=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Ignore gFSR photons\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                } 
              readCloseCurly(fin,line,"% Ignore gFSR photons (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Component analysis --- decay trees")
        {
          readOpenCurly(fin,line,"% Component analysis --- decay trees");
          read1stLineOrCloseCurly(fin,line,false,"% Component analysis --- decay trees");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              iss.str(line);
              iss>>line;
              if(line=="Y")
                {
                  m_compAnaOfDcyTrs=true;
                }
              else if(line=="N")
                {
                  m_compAnaOfDcyTrs=false;
                }
              else
                {
                  cerr<<"Error: The first input parameter \""<<line<<"\" for the item \"Component analysis --- decay trees\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              if(!iss.eof())
                {
                  iss>>line;
                  if(line.find_first_not_of("0123456789")==string::npos) m_nDcyTrsToBePrtdMax=strtoul(line.c_str(),NULL,10);
                  else if(line=="-") m_nDcyTrsToBePrtdMax=ULONG_MAX;
                  else
                    {
                      cerr<<"Error: The second input parameter \""<<line<<"\" for the item \"Component analysis --- decay trees\" is invalid!"<<endl;
                      cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                      cerr<<"Infor: It can also be \"-\" as a place holder if there is a third input parameter following it."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                }
              else m_nDcyTrsToBePrtdMax=ULONG_MAX;
              if(!iss.eof()) 
                {
                  iss>>line;
                  if(line.find_first_not_of("0123456789")==string::npos) m_nDcyIFStsToBePrtdMax=strtoul(line.c_str(),NULL,10);        
                  else if(line=="-") m_nDcyIFStsToBePrtdMax=ULONG_MAX;
                  else
                    { 
                      cerr<<"Error: The third input parameter \""<<line<<"\" for the item \"Component analysis --- decay trees\" is invalid!"<<endl;
                      cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                      cerr<<"Infor: It can also be \"-\" as a place holder if there is a fourth input parameter following it."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                }
              else m_nDcyIFStsToBePrtdMax=ULONG_MAX;
              if(!iss.eof()) 
                {
                  iss>>line;
                  if(line=="Y")
                    {
                      m_adjDcyIFStsIntoACol=true;
                    }
                  else if(line=="N")
                    {
                      m_adjDcyIFStsIntoACol=false;
                    }
                  else
                    {
                      cerr<<"Error: The fourth input parameter \""<<line<<"\" for the item \"Component analysis --- decay trees\" is invalid!"<<endl;
                      cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }                  
                }
              readCloseCurly(fin,line,"% Component analysis --- decay trees");
            }
        }
      else if(line=="% Component analysis --- decay initial-final states")
        {
          readOpenCurly(fin,line,"% Component analysis --- decay initial-final states");
          read1stLineOrCloseCurly(fin,line,false,"% Component analysis --- decay initial-final states");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              iss.str(line);
              iss>>line;
              if(line=="Y")
                {
                  m_compAnaOfDcyIFSts=true;
                }
              else if(line=="N")
                {
                  m_compAnaOfDcyIFSts=false;
                }
              else
                {
                  cerr<<"Error: The first input parameter \""<<line<<"\" for the item \"Component analysis --- decay initial-final states\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              if(!iss.eof())
                {
                  iss>>line;
                  if(line.find_first_not_of("0123456789")==string::npos) m_nDcyIFStsToBePrtdMax=strtoul(line.c_str(),NULL,10);
                  else
                    {
                      cerr<<"Error: The second input parameter \""<<line<<"\" for the item \"Component analysis --- decay initial-final states\" is invalid!"<<endl;
                      cerr<<"Infor: It should be an unsigned long integer if it is not left empty."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                }
              else m_nDcyIFStsToBePrtdMax=ULONG_MAX;
              readCloseCurly(fin,line,"% Component analysis --- decay initial-final states");
            }
        }
      else if(line=="% Component analysis --- particles")
        {
          readOpenCurly(fin,line,"% Component analysis --- particles");
          read1stLineOrCloseCurly(fin,line,false,"% Component analysis --- particles");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              string txtPnm;
              int pid;
              unsigned long nMax;
              string nm;

              iss.str(line);
              iss>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              m_vPid_compP.push_back(pid);
              if(!iss.eof())
                { 
                  iss>>line;
                  if(line.find_first_not_of("0123456789")==string::npos) nMax=strtoul(line.c_str(),NULL,10);        
                  else if(line=="-") nMax=ULONG_MAX;
                  else
                    {                       
                      cerr<<"Error: The second column input parameter \""<<line<<"\" for the item \"Component analysis --- particles\" is invalid!"<<endl;
                      cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                      cerr<<"Infor: It can also be \"-\" as a place holder if there is a third input parameter following it."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                }
              else nMax=ULONG_MAX;
              m_vNDcyBrsToBePrtdMax.push_back(nMax);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_compP.push_back(nm);
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Component analysis --- particles");
                  if(line=="}")
                    {
                      break;
                    }
                  else
                    {
                      iss.clear();
                      iss.str(line);
                      iss>>txtPnm;
                      pid=getPidFromTxtPnm(txtPnm);
                      m_vPid_compP.push_back(pid);
                      if(!iss.eof())
                        {
                          iss>>line;
                          if(line.find_first_not_of("0123456789")==string::npos) nMax=strtoul(line.c_str(),NULL,10);                        else if(line=="-") nMax=ULONG_MAX;
                          else
                            {
                              cerr<<"Error: The second column input parameter \""<<line<<"\" for the item \"Component analysis --- particles\" is invalid!"<<endl;
                              cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                              cerr<<"Infor: It can also be \"-\" as a place holder if there is a third input parameter following it."<<endl;
                              cerr<<"Infor: Please check it."<<endl;
                              exit(-1);
                            }
                        }
                      else nMax=ULONG_MAX;
                      m_vNDcyBrsToBePrtdMax.push_back(nMax);
                      if(!iss.eof()) iss>>nm;
                      else nm="";
                      m_vNm_compP.push_back(nm);
                    }
                }
            }
        }
      else if(line=="% Component analysis --- inclusive decay branches")
        {
          readOpenCurly(fin,line,"% Component analysis --- inclusive decay branches");
          read1stLineOrCloseCurly(fin,line,false,"% Component analysis --- inclusive decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int pid;
              vector<int> vPid;
              vPid.clear();
              unsigned long nMax;
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              if(!iss.eof())
                { 
                  iss>>line;
                  if(line.find_first_not_of("0123456789")==string::npos) nMax=strtoul(line.c_str(),NULL,10);        
                  else if(line=="-") nMax=ULONG_MAX;
                  else
                    {                       
                      cerr<<"Error: The second column input parameter \""<<line<<"\" for the item \"Component analysis --- inclusive decay branches\" is invalid!"<<endl;
                      cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                      cerr<<"Infor: It can also be \"-\" as a place holder if there is a third input parameter following it."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                }
              else nMax=ULONG_MAX;
              m_vNExcCompsToBePrtdMax.push_back(nMax);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_compIncDcyBr.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Component analysis --- inclusive decay branches");
                  if(line=="}")
                    {
                      m_vVPid_compIncDcyBr.push_back(vPid);
                      vPid.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm;
                      if(idx==0)
                        {
                          m_vVPid_compIncDcyBr.push_back(vPid);
                          vPid.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      if(idx==0)
                        {
                          if(!iss.eof())
                            {
                              iss>>line;
                              if(line.find_first_not_of("0123456789")==string::npos) nMax=strtoul(line.c_str(),NULL,10);                        else if(line=="-") nMax=ULONG_MAX;
                              else
                                {
                                  cerr<<"Error: The second column input parameter \""<<line<<"\" for the item \"Component analysis --- inclusive decay branches\" is invalid!"<<endl;
                                  cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                                  cerr<<"Infor: It can also be \"-\" as a place holder if there is a third input parameter following it."<<endl;
                                  cerr<<"Infor: Please check it."<<endl;
                                  exit(-1);
                                }
                            }
                          else nMax=ULONG_MAX;
                          m_vNExcCompsToBePrtdMax.push_back(nMax);
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_compIncDcyBr.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Component analysis --- intermediate-resonance-allowed decay branches")
        {
          readOpenCurly(fin,line,"% Component analysis --- intermediate-resonance-allowed decay branches");
          read1stLineOrCloseCurly(fin,line,false,"% Component analysis --- intermediate-resonance-allowed decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int pid;
              vector<int> vPid;
              vPid.clear();
              unsigned long nMax;
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              if(!iss.eof())
                { 
                  iss>>line;
                  if(line.find_first_not_of("0123456789")==string::npos) nMax=strtoul(line.c_str(),NULL,10);        
                  else if(line=="-") nMax=ULONG_MAX;
                  else
                    {                       
                      cerr<<"Error: The second column input parameter \""<<line<<"\" for the item \"Component analysis --- intermediate-resonance-allowed decay branches\" is invalid!"<<endl;
                      cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                      cerr<<"Infor: It can also be \"-\" as a place holder if there is a third input parameter following it."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                }
              else nMax=ULONG_MAX;
              m_vNIntStrusToBePrtdMax.push_back(nMax);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_compIRADcyBr.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Component analysis --- intermediate-resonance-allowed decay branches");
                  if(line=="}")
                    {
                      m_vVPid_compIRADcyBr.push_back(vPid);
                      vPid.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm;
                      if(idx==0)
                        {
                          m_vVPid_compIRADcyBr.push_back(vPid);
                          vPid.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      if(idx==0)
                        {
                          if(!iss.eof())
                            {
                              iss>>line;
                              if(line.find_first_not_of("0123456789")==string::npos) nMax=strtoul(line.c_str(),NULL,10);                        else if(line=="-") nMax=ULONG_MAX;
                              else
                                {
                                  cerr<<"Error: The second column input parameter \""<<line<<"\" for the item \"Component analysis --- intermediate-resonance-allowed decay branches\" is invalid!"<<endl;
                                  cerr<<"Infor: It should be an unsigned long integer at which you want to set."<<endl;
                                  cerr<<"Infor: It can also be \"-\" as a place holder if there is a third input parameter following it."<<endl;
                                  cerr<<"Infor: Please check it."<<endl;
                                  exit(-1);
                                }
                            }
                          else nMax=ULONG_MAX;
                          m_vNIntStrusToBePrtdMax.push_back(nMax);
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_compIRADcyBr.push_back(nm);
                        } 
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Signal identification --- decay trees")
        {
          readOpenCurly(fin,line,"% Signal identification --- decay trees");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- decay trees");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int midx;
              int pid;
              vector<int> vPid;
              vPid.clear();
              vector<int> vMidx;
              vMidx.clear();
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm>>midx;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              vMidx.push_back(midx);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigDcyTr.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- decay trees");
                  if(line=="}")
                    {
                      m_vVPid_sigDcyTr.push_back(vPid);
                      vPid.clear();
                      m_vVMidx_sigDcyTr.push_back(vMidx);
                      vMidx.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm>>midx;
                      if(idx==0)
                        {
                          m_vVPid_sigDcyTr.push_back(vPid);
                          vPid.clear();
                          m_vVMidx_sigDcyTr.push_back(vMidx);
                          vMidx.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      vMidx.push_back(midx);
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigDcyTr.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Signal identification --- decay initial-final states")
        {
          readOpenCurly(fin,line,"% Signal identification --- decay initial-final states");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- decay initial-final states");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int pid;
              vector<int> vPid;
              vPid.clear();
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigDcyIFSts2.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- decay initial-final states");
                  if(line=="}")
                    {
                      m_vVPid_sigDcyIFSts2.push_back(vPid);
                      vPid.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm;
                      if(idx==0)
                        {
                          m_vVPid_sigDcyIFSts2.push_back(vPid);
                          vPid.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigDcyIFSts2.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Signal identification --- particles")
        {
          readOpenCurly(fin,line,"% Signal identification --- particles");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- particles");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              string txtPnm;
              int pid;
              string nm;

              iss.str(line);
              iss>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              m_vPid_sigP.push_back(pid);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigP.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- particles");
                  if(line=="}")
                    {
                      break;
                    }
                  else 
                    {
                      iss.str(line);
                      iss>>txtPnm;
                      pid=getPidFromTxtPnm(txtPnm);
                      m_vPid_sigP.push_back(pid);
                      if(!iss.eof()) iss>>nm;
                      else nm="";
                      m_vNm_sigP.push_back(nm);
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Signal identification --- decay branches")
        {
          readOpenCurly(fin,line,"% Signal identification --- decay branches");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int pid;
              vector<int> vPid;
              vPid.clear();
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigDcyBr.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- decay branches");
                  if(line=="}")
                    {
                      m_vVPid_sigDcyBr.push_back(vPid);
                      vPid.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm;
                      if(idx==0)
                        {
                          m_vVPid_sigDcyBr.push_back(vPid);
                          vPid.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigDcyBr.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	} 
      else if(line=="% Signal identification --- inclusive decay branches")
        {
          readOpenCurly(fin,line,"% Signal identification --- inclusive decay branches");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- inclusive decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int pid;
              vector<int> vPid;
              vPid.clear();
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigIncDcyBr.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- inclusive decay branches");
                  if(line=="}")
                    {
                      m_vVPid_sigIncDcyBr.push_back(vPid);
                      vPid.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm;
                      if(idx==0)
                        {
                          m_vVPid_sigIncDcyBr.push_back(vPid);
                          vPid.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigIncDcyBr.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Signal identification --- cascade decay branches")
        {
          readOpenCurly(fin,line,"% Signal identification --- cascade decay branches");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- cascade decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int midx;
              int pid;
              vector<int> vPid;
              vPid.clear();
              vector<int> vMidx;
              vMidx.clear();
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm>>midx;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              vMidx.push_back(midx);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigCascDcyBrs.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- cascade decay branches");
                  if(line=="}")
                    {
                      m_vVPid_sigCascDcyBrs.push_back(vPid);
                      vPid.clear();
                      m_vVMidx_sigCascDcyBrs.push_back(vMidx);
                      vMidx.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm>>midx;
                      if(idx==0)
                        {
                          m_vVPid_sigCascDcyBrs.push_back(vPid);
                          vPid.clear();
                          m_vVMidx_sigCascDcyBrs.push_back(vMidx);
                          vMidx.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      vMidx.push_back(midx);
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigCascDcyBrs.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Signal identification --- inclusive cascade decay branches")
        {
          readOpenCurly(fin,line,"% Signal identification --- inclusive cascade decay branches");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- inclusive cascade decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              // The asterisk symbol "*" is used as a short version of the word "anything" in order to simplify the user's input.
              string txtPnm,asterisk="*";
              int midx;
              int pid;
              vector<int> vPid;
              vPid.clear();
              vector<int> vMidx;
              vMidx.clear();
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm>>midx;
              // Pay attention to that if txtPnm==asterisk, then 1 is returned. Please do not get this wrong.
              if(txtPnm==asterisk) txtPnm="anything";
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              vMidx.push_back(midx);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigIncCascDcyBrs.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- inclusive cascade decay branches");
                  if(line=="}")
                    {
                      m_vVPid_sigIncCascDcyBrs.push_back(vPid);
                      vPid.clear();
                      m_vVMidx_sigIncCascDcyBrs.push_back(vMidx);
                      vMidx.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm>>midx;
                      if(idx==0)
                        {
                          m_vVPid_sigIncCascDcyBrs.push_back(vPid);
                          vPid.clear();
                          m_vVMidx_sigIncCascDcyBrs.push_back(vMidx);
                          vMidx.clear();
                        }
                      // Pay attention to that if txtPnm==asterisk, then 1 is returned. Please do not get this wrong.
                      if(txtPnm==asterisk) txtPnm="anything";
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      vMidx.push_back(midx);
                      iss.clear();
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigIncCascDcyBrs.push_back(nm);
                        }
                    }
                }
            }
	}
      else if(line=="% Signal identification --- intermediate-resonance-allowed decay branches")
        {
          readOpenCurly(fin,line,"% Signal identification --- intermediate-resonance-allowed decay branches");          
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- intermediate-resonance-allowed decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              string txtPnm;
              int pid;
              vector<int> vPid;
              vPid.clear();
              string nm;

              iss.str(line);
              iss>>idx>>txtPnm;
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigIRADcyBr.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- intermediate-resonance-allowed decay branches");
                  if(line=="}")
                    {
                      m_vVPid_sigIRADcyBr.push_back(vPid);
                      vPid.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm;
                      if(idx==0)
                        {
                          m_vVPid_sigIRADcyBr.push_back(vPid);
                          vPid.clear();
                        }
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigIRADcyBr.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Signal identification --- inclusive or intermediate-resonance-allowed cascade decay branches")
        {
          readOpenCurly(fin,line,"% Signal identification --- inclusive or intermediate-resonance-allowed cascade decay branches");
          read1stLineOrCloseCurly(fin,line,false,"% Signal identification --- inclusive or intermediate-resonance-allowed cascade decay branches");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              int idx;
              // The asterisk symbol "*" is used as a short version of the word "anything" in order to simplify the user's input.
              string txtPnm,asterisk="*";
              int midx;
              int pid;
              vector<int> vPid;
              vPid.clear();
              vector<int> vMidx;
              vMidx.clear();
              string nm;
              
              iss.str(line);
              iss>>idx>>txtPnm>>midx;
              // Pay attention to that if txtPnm==asterisk, then 1 is returned. Please do not get this wrong.
              if(txtPnm==asterisk) txtPnm="anything";
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
              vMidx.push_back(midx);
              if(!iss.eof()) iss>>nm;
              else nm="";
              m_vNm_sigIncOrIRACascDcyBrs.push_back(nm);
              iss.clear();
              while(1)
                {
                  readExtraLinesOrCloseCurly(fin,line,"% Signal identification --- inclusive or intermediate-resonance-allowed cascade decay branches");
                  if(line=="}")
                    {
                      m_vVPid_sigIncOrIRACascDcyBrs.push_back(vPid);
                      vPid.clear();
                      m_vVMidx_sigIncOrIRACascDcyBrs.push_back(vMidx);
                      vMidx.clear();
                      break;
                    }
                  else
                    {
                      iss.str(line);
                      iss>>idx>>txtPnm>>midx;
                      if(idx==0)
                        {
                          m_vVPid_sigIncOrIRACascDcyBrs.push_back(vPid);
                          vPid.clear();
                          m_vVMidx_sigIncOrIRACascDcyBrs.push_back(vMidx);
                          vMidx.clear();
                        }
                      // Pay attention to that if txtPnm==asterisk, then 1 is returned. Please do not get this wrong.
                      if(txtPnm==asterisk) txtPnm="anything";
                      pid=getPidFromTxtPnm(txtPnm);
                      vPid.push_back(pid);
                      vMidx.push_back(midx);
                      if(idx==0)
                        {
                          if(!iss.eof()) iss>>nm;
                          else nm="";
                          m_vNm_sigIncOrIRACascDcyBrs.push_back(nm);
                        }
                      iss.clear();
                    }
                }
            }
	}
      else if(line=="% Process charge conjugate objects together (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Process charge conjugate objects together (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Process charge conjugate objects together (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_ccSwitch=true;
                }
              else if(line=="N")
                {
                  m_ccSwitch=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Process charge conjugate objects together\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                } 
              readCloseCurly(fin,line,"% Process charge conjugate objects together (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Analysis tasks for signal identifications (Three options: TC, T and C. Default: TC)")
        {
          readOpenCurly(fin,line,"% Analysis tasks for signal identifications (Three options: TC, T and C. Default: TC)");
          read1stLineOrCloseCurly(fin,line,false,"% Analysis tasks for signal identifications (Three options: TC, T and C. Default: TC)");
          if(line!="}")
            {
              if(line=="TC"||line=="T"||line=="C")
                {
                  m_anaTasksForSigIds=line;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Analysis tasks for signal identifications\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"TC\", \"T\" or \"C\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Analysis tasks for signal identifications (Three options: TC, T and C. Default: TC)");
            }
        }
      else if(line=="% Sort the topology structures for signal identifications (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Sort the topology structures for signal identifications (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Sort the topology structures for signal identifications (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_sortTheToposForSigIds=true;
                }
              else if(line=="N")
                {
                  m_sortTheToposForSigIds=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Sort the topology structures for signal identifications\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Sort the topology structures for signal identifications (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Involve the initial e+ and e- uniformly in all the events (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Involve the initial e+ and e- uniformly in all the events (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Involve the initial e+ and e- uniformly in all the events (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_initEpEmSwitch=true;
                }
              else if(line=="N")
                {
                  m_initEpEmSwitch=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Involve the initial e+ and e- uniformly in all the events\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Involve the initial e+ and e- uniformly in all the events (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Main name of output files (Default: Main name of the card file)")
        {
          readOpenCurly(fin,line,"% Main name of output files (Default: Main name of the card file)");
          read1stLineOrCloseCurly(fin,line,false,"No main file name is found in the item with the prompt \"% Main name of output files (Default: Main name of the card file)");
          if(line!="}")
            {
              m_mainNmOfOptFls=line;
              readCloseCurly(fin,line,"% Main name of output files (Default: Main name of the card file)");
            }
        }
      else if(line=="% Center decay objects in the output pdf files (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Center decay objects in the output pdf files (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Center decay objects in the output pdf files (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_centDcyObjs=true;
                }
              else if(line=="N")
                {
                  m_centDcyObjs=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Center decay objects in the output pdf files\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Center decay objects in the output pdf files (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Suppress the topology tags in the output pdf files (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Suppress the topology tags in the output pdf files (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Suppress the topology tags in the output pdf files (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_sprTopoTags=true;
                }
              else if(line=="N")
                {
                  m_sprTopoTags=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Suppress the topology tags in the output pdf files\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Suppress the topology tags in the output pdf files (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% One output root file by one input root file (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% One output root file by one input root file (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% One output root file by one input root file (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_oneOptRootFlByOneIptRootFl=true;
                }
              else if(line=="N")
                {
                  m_oneOptRootFlByOneIptRootFl=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"One output root file by one input root file\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% One output root file by one input root file (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Maximum number of entries to be saved in a single output root file")
        {
          readOpenCurly(fin,line,"% Maximum number of entries to be saved in a single output root file");
          m_nEtrsMaxInASngOptRootFl=ULONG_MAX;
          read1stLineOrCloseCurly(fin,line,false,"% Maximum number of entries to be saved in a single output root file");
          if(line!="}")
            {
              if(line.find_first_not_of("0123456789")==string::npos) m_nEtrsMaxInASngOptRootFl=strtoul(line.c_str(),NULL,10);
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Maximum number of entries to be saved in a single output root file\" is invalid!"<<endl;
                  cerr<<"Infor: It should be an unsigned long integer if it is not left empty."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Maximum number of entries to be saved in a single output root file");
            }
        }
      else if(line=="% Use array branches to store topology tags in the output root files when possible (Two options: Y and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Use array branches to store topology tags in the output root files when possible (Two options: Y and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Use array branches to store topology tags in the output root files when possible (Two options: Y and N. Default: N)");
          if(line!="}")
            {
              if(line=="Y")
                {
                  m_useArrayBrsOpt=true;
                }
              else if(line=="N")
                {
                  m_useArrayBrsOpt=false;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Use array branches to store topology tags in the output root files when possible\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Use array branches to store topology tags in the output root files when possible (Two options: Y and N. Default: N)");
            }
        }
      else if(line=="% Copy the input branches to the output root files (Two options: Y and N. Default: Y)")
        {
          readOpenCurly(fin,line,"% Copy the input branches to the output root files (Two options: Y and N. Default: Y)");
          read1stLineOrCloseCurly(fin,line,false,"% Copy the input branches to the output root files (Two options: Y and N. Default: Y)");
          if(line!="}")
            {
              if(line=="N")
                {
                  m_cpIptBrs=false;
                }
              else if(line=="Y")
                {
                  m_cpIptBrs=true;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Copy the input branches to the output root files\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Copy the input branches to the output root files (Two options: Y and N. Default: Y)");
            }
        }
      else
        {
          cerr<<"Error: The input line "<<line<<"\" is invalid!"<<endl;
          exit(-1);
        }
    }
}
