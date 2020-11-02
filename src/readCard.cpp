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
          cerr<<"Infor: If yes, please specify it along with the executable by the command line \"[path/]topoana.exe nameOfYourOwnCardFile\""<<endl;
          cerr<<"Infor: For the details on the usage of the command, please execute \"[path/]topoana.exe --help\""<<endl;
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
          m_nmsOfIptRootFls.clear();
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
      else if(line=="% TTree name")
        {
          readOpenCurly(fin,line,"% TTree name");
          read1stLineOrCloseCurly(fin,line,true,"No tree name is found in the item with the prompt \"% TTree name");
          m_ttrNm=line;
          readCloseCurly(fin,line,"% TTree name");
        }
      else if(line=="% Storage type of input raw topology truth information (Four options: AOI, VOI, MSI, and MSD. Default: AOI)")
        {
          readOpenCurly(fin,line,"% Storage type of input raw topology truth information (Four options: AOI, VOI, MSI, and MSD. Default: AOI)");
          m_strgTpOfRawIptTopoDat="AOI";
          read1stLineOrCloseCurly(fin,line,false,"% Storage type of input raw topology truth information (Four options: AOI, VOI, MSI, and MSD. Default: AOI)");
          if(line!="}")
            {
              if(line=="AOI"||line=="VOI"||line=="MSI"||line=="MSD")
                {
                  m_strgTpOfRawIptTopoDat=line;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Storage type of input raw topology truth information\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"AI\", \"VI\", \"MSI\" or \"MSD\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Storage type of input raw topology truth information (Four options: AOI, VOI, MSI, and MSD. Default: AOI)");
            }
        }
      else if(line=="% TBranch name of the number of particles (Default: nMCGen)")
        {
          readOpenCurly(fin,line,"% TBranch name of the number of particles (Default: nMCGen)");
          read1stLineOrCloseCurly(fin,line,false,"No tbranch name of the number of particles is found in the item with the prompt \"% TBranch name of the number of particles (Default: nMCGen)");
          if(line!="}")
            {
              m_tbrNmOfNps=line;
              readCloseCurly(fin,line,"% TBranch name of the number of particles (Default: nMCGen)");
            }
        }
      else if(line=="% TBranch name of the PDG codes of particles (Default: MCGenPDG)")
        {
          readOpenCurly(fin,line,"% TBranch name of the PDG codes of particles (Default: MCGenPDG)");
          read1stLineOrCloseCurly(fin,line,false,"No tbranch name of the PDG codes of particles is found in the item with the prompt \"% TBranch name of the PDG codes of particles (Default: MCGenPDG)");
          if(line!="}")
            {
              m_tbrNmOfPid=line;
              readCloseCurly(fin,line,"% TBranch name of the PDG codes of particles (Default: MCGenPDG)");     
            }
        }
      else if(line=="% TBranch name of the mother indices of particles (Default: MCGenMothIndex)")
        {
          readOpenCurly(fin,line,"% TBranch name of the mother indices of particles (Default: MCGenMothIndex)");
          read1stLineOrCloseCurly(fin,line,false,"No tbranch name of the mother indices of particles is found in the item with the prompt \"% TBranch name of the mother indices of particles (Default: MCGenMothIndex)");
          if(line!="}")
            {
              m_tbrNmOfMidx=line;
              readCloseCurly(fin,line,"% TBranch name of the mother indices of particles (Default: MCGenMothIndex)");  
            }
        }
      else if(line=="% Avoid over counting for candidate based analysis (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Avoid over counting for candidate based analysis (Two options: Y and N. Default: N)", m_avoidOverCounting);
        }
      else if(line=="% TBranch name of the indices of candidates in an event (Default: __candidate__)")
        {
          readOpenCurly(fin,line,"% TBranch name of the indices of candidates in an event (Default: __candidate__)");
          read1stLineOrCloseCurly(fin,line,false,"No tbranch name of the indices of candidates in an event is found in the item with the prompt \"% TBranch name of the indices of candidates in an event (Default: __candidate__)");
          if(line!="}")
            { 
              m_tbrNmOfIcandi=line;
              readCloseCurly(fin,line,"% TBranch name of the indices of candidates in an event (Default: __candidate__)");   
            }
        }
      else if(line=="% TBranch name of the raw indices of particles (Default: MCGenRawIndex)")
        {
          readOpenCurly(fin,line,"% TBranch name of the raw indices of particles (Default: MCGenRawIndex)");
          read1stLineOrCloseCurly(fin,line,false,"No tbranch name of the raw indices of particles is found in the item with the prompt \"% TBranch name of the raw indices of particles (Default: MCGenRawIndex)");
          if(line!="}")
            {
              m_tbrNmOfRidx=line;
              readCloseCurly(fin,line,"% TBranch name of the raw indices of particles (Default: MCGenRawIndex)");
            }
        }
      else if(line=="% Fix the mother indices of particles in BESIII experiment (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Fix the mother indices of particles in BESIII experiment (Two options: Y and N. Default: N)", m_fixMidxBESIII);
        }
      else if(line=="% Maximum number of entries to be processed")
        {
          readNumItem(fin, line, "% Maximum number of entries to be processed", m_nEtrMax);
        }
      else if(line=="% Cut to select entries")
        {
          readOpenCurly(fin,line,"% Cut to select entries");
          m_vCut.clear();
          while(1)
            {
              readExtraLinesOrCloseCurly(fin,line,"% Cut to select entries");
              if(line=="}")
                {
                  break;
                }
              else
                {
                  m_vCut.push_back(line);
                }
            }
          m_cut.clear();
          for(unsigned int i=0;i<m_vCut.size();i++) m_cut=m_cut+m_vCut[i];
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
          readNumItem(fin, line, "% Maximum hierarchy of heading decay branches to be processed in each event", m_hHdDcyBrsMax);
        }
      else if(line=="% Ignore the decay of the following particles")
        {
          readVPItem(fin, line, "% Ignore the decay of the following particles", m_vIdPid);
        }
      else if(line=="% Ignore the decay of the daughters of the following particles")
        {
          readVPItem(fin, line, "% Ignore the decay of the daughters of the following particles", m_vIddPid);
        }
      else if(line=="% Retain the decay of pi0 to gamma gamma (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Retain the decay of pi0 to gamma gamma (Two options: Y and N. Default: N)", m_retainPi02GamGam);
        }
      else if(line=="% Ignore the following final decay branches")
        {
          readSmpDcyItem(fin, line, "% Ignore the following final decay branches", m_vVPid_ignoreFDcyBr);
        }
      else if(line=="% PDG code of ISR photons (Default: 222222222)")
        {
          readNumItem(fin, line, "% PDG code of ISR photons (Default: 222222222)", m_pidOfSISRGamUser, 222222222);
        }
      else if(line=="% PDG code of FSR photons (Default: -22)")
        {
          readNumItem(fin, line, "% PDG code of FSR photons (Default: -22)", m_pidOfSFSRGamUser, -22);
        }
      else if(line=="% Ignore ISR photons (Three options: Ys, Yg and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Ignore ISR photons (Three options: Ys, Yg and N. Default: N)");  
          read1stLineOrCloseCurly(fin,line,false,"% Ignore ISR photons (Three options: Ys, Yg and N. Default: N)");
          if(line!="}")
            { 
              if(line=="Ys"||line=="Yg"||line=="N")
                { 
                  m_ignoreISR=line;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Ignore ISR photons\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Ys\", \"Yg\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Ignore ISR photons (Three options: Ys, Yg and N. Default: N)");
            }
        }
      else if(line=="% Ignore FSR photons (Three options: Ys, Yg and N. Default: N)")
        {
          readOpenCurly(fin,line,"% Ignore FSR photons (Three options: Ys, Yg and N. Default: N)");
          read1stLineOrCloseCurly(fin,line,false,"% Ignore FSR photons (Three options: Ys, Yg and N. Default: N)");
          if(line!="}")
            {
              if(line=="Ys"||line=="Yg"||line=="N")
                {
                  m_ignoreFSR=line;
                }
              else
                {
                  cerr<<"Error: The input \""<<line<<"\" for the item \"Ignore FSR photons\" is invalid!"<<endl;
                  cerr<<"Infor: It should be \"Ys\", \"Yg\" or \"N\"."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
              readCloseCurly(fin,line,"% Ignore FSR photons (Three options: Ys, Yg and N. Default: N)");
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
                  if(line=="Y")
                    {
                      m_dcyIFStsUnderDcyTr=true;
                    }
                  else if(line=="N")
                    {
                      m_dcyIFStsUnderDcyTr=false;
                    }
                  else
                    {
                      cerr<<"Error: The third input parameter \""<<line<<"\" for the item \"Component analysis --- decay trees\" is invalid!"<<endl;
                      cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }                  
                }
              if(!iss.eof())
                {
                  iss>>line;
                  if(line=="Y")
                    {
                      m_optIdxAndMidxOfDcyBrInDcyTr=true;
                    }
                  else if(line=="N")
                    {
                      m_optIdxAndMidxOfDcyBrInDcyTr=false;
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
      else if(line=="% Component analysis --- decay branches of particles")
        {
          readPItem(fin,line, "% Component analysis --- decay branches of particles", m_vPid_compDcyBrP, m_vNm_compDcyBrP, &m_vNDcyBrToBePrtdMax, &m_vNDcyBrP, &m_vTypeOfTagRec_compDcyBrP, &m_vTBrNmOfTagRec_compDcyBrP, &m_vTBrNmOfNRec_compDcyBrP);
        }
      else if(line=="% Component analysis --- cascade decay branches of particles")
        {
          readPItem(fin,line, "% Component analysis --- cascade decay branches of particles", m_vPid_compCascDcyBrP, m_vNm_compCascDcyBrP, &m_vNCascDcyBrToBePrtdMax, &m_vHCascDcyBrMax, &m_vTypeOfTagRec_compCascDcyBrP, &m_vTBrNmOfTagRec_compCascDcyBrP, &m_vTBrNmOfNRec_compCascDcyBrP, &m_vOptIdxAndMidxOfDcyBrInCascDcyBrP);
        }
      else if(line=="% Component analysis --- decay final states of particles")
        {
          readPItem(fin,line, "% Component analysis --- decay final states of particles", m_vPid_compDcyFStP, m_vNm_compDcyFStP, &m_vNDcyFStToBePrtdMax, &m_vNDcyFStP, &m_vTypeOfTagRec_compDcyFStP, &m_vTBrNmOfTagRec_compDcyFStP, &m_vTBrNmOfNRec_compDcyFStP);
        }
      else if(line=="% Component analysis --- production branches of particles")
        {
          readPItem(fin, line, "% Component analysis --- production branches of particles", m_vPid_compProdBrP, m_vNm_compProdBrP, &m_vNProdBrToBePrtdMax, &m_vNProdBrP, &m_vTypeOfTagRec_compProdBrP, &m_vTBrNmOfTagRec_compProdBrP, &m_vTBrNmOfNRec_compProdBrP);
        }
      else if(line=="% Component analysis --- mothers of particles")
        {
          readPItem(fin, line, "% Component analysis --- mothers of particles", m_vPid_compMP, m_vNm_compMP, &m_vNMToBePrtdMax, &m_vNMP, &m_vTypeOfTagRec_compMP, &m_vTBrNmOfTagRec_compMP, &m_vTBrNmOfNRec_compMP);
        }
      else if(line=="% Component analysis --- inclusive decay branches")
        {
          readSmpDcyItem(fin, line, "% Component analysis --- inclusive decay branches", m_vVPid_compIncDcyBr, &m_vNm_compIncDcyBr, &m_vNExcCompsToBePrtdMax, &m_vOption_compIncDcyBr);
	}
      else if(line=="% Component analysis --- intermediate-resonance-allowed decay branches")
        {
          readSmpDcyItem(fin, line, "% Component analysis --- intermediate-resonance-allowed decay branches", m_vVPid_compIRADcyBr, &m_vNm_compIRADcyBr, &m_vNIntStrusToBePrtdMax);
	}
      else if(line=="% Signal identification --- decay trees")
        {
          readCmplxDcyItem(fin, line, "% Signal identification --- decay trees", m_vVPid_sigDcyTr, m_vVMidx_sigDcyTr, m_vNm_sigDcyTr, m_sigDcyIFStsUnderSigDcyTr, m_optIdxAndMidxOfSigDcyBrInSigDcyTr);
	}
      else if(line=="% Signal identification --- decay initial-final states related to decay trees (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Signal identification --- decay initial-final states related to decay trees (Two options: Y and N. Default: N)", m_sigDcyIFSts_tr);
        }
      else if(line=="% Signal identification --- decay initial-final states")
        {
          readSmpDcyItem(fin, line, "% Signal identification --- decay initial-final states", m_vVPid_sigDcyIFSts, &m_vNm_sigDcyIFSts);
	}
      else if(line=="% Signal identification --- particles")
        {
          readPItem(fin, line, "% Signal identification --- particles", m_vPid_sigP, m_vNm_sigP);
	}
      else if(line=="% Signal identification --- decay branches")
        {
          readSmpDcyItem(fin, line, "% Signal identification --- decay branches", m_vVPid_sigDcyBr, &m_vNm_sigDcyBr);
	} 
      else if(line=="% Signal identification --- inclusive decay branches")
        {
          readSmpDcyItem(fin, line, "% Signal identification --- inclusive decay branches", m_vVPid_sigIncDcyBr, &m_vNm_sigIncDcyBr);
	}
      else if(line=="% Signal identification --- cascade decay branches")
        {
          bool bvartemp;
          readCmplxDcyItem(fin, line, "% Signal identification --- cascade decay branches", m_vVPid_sigCascDcyBr, m_vVMidx_sigCascDcyBr, m_vNm_sigCascDcyBr, m_optIdxAndMidxOfSigDcyBrInSigCascDcyBr, bvartemp);
	}
      else if(line=="% Signal identification --- inclusive cascade decay branches")
        {
          bool bvartemp;
          readCmplxDcyItem(fin, line, "% Signal identification --- inclusive cascade decay branches", m_vVPid_sigIncCascDcyBr, m_vVMidx_sigIncCascDcyBr, m_vNm_sigIncCascDcyBr, m_optIdxAndMidxOfSigDcyBrInSigIncCascDcyBr, bvartemp, true);
	}
      else if(line=="% Signal identification --- intermediate-resonance-allowed decay branches")
        {
          readSmpDcyItem(fin, line, "% Signal identification --- intermediate-resonance-allowed decay branches", m_vVPid_sigIRADcyBr, &m_vNm_sigIRADcyBr);
	}
      else if(line=="% Signal identification --- inclusive or intermediate-resonance-allowed cascade decay branches")
        {
          bool bvartemp;
          readCmplxDcyItem(fin, line, "% Signal identification --- inclusive or intermediate-resonance-allowed cascade decay branches", m_vVPid_sigIncOrIRACascDcyBr, m_vVMidx_sigIncOrIRACascDcyBr, m_vNm_sigIncOrIRACascDcyBr, m_optIdxAndMidxOfSigDcyBrInSigIncOrIRACascDcyBr, bvartemp, true);
	}
      else if(line=="% Process charge conjugate objects together (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Process charge conjugate objects together (Two options: Y and N. Default: N)", m_ccSwitch);
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
      else if(line=="% Sort the signals in the topology maps related to signal identifications (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Sort the signals in the topology maps related to signal identifications (Two options: Y and N. Default: N)", m_sortSigsInTopoMapsRltdToSigIds);
        }
      else if(line=="% Initial state particles (Default: e- e+)")
        {
          readOpenCurly(fin,line,"% Initial state particles (Default: e- e+)");
          read1stLineOrCloseCurly(fin,line,false,"% Initial state particles (Default: e- e+)");
          if(line!="}")
            {
              istringstream iss;
              iss.clear();
              iss.str(line);
              iss>>line;
              m_pidOfISt1=getPidFromTxtPnm(line);
              if(!iss.eof())
                {
                  iss>>line;
                  m_pidOfISt2=getPidFromTxtPnm(line);
                }
              else m_pidOfISt2=getCcPid(m_pidOfISt1);
              readCloseCurly(fin,line,"% Initial state particles (Default: e- e+)");
            }
        }
      else if(line=="% Push front the initial state particles uniformly in all the events (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Push front the initial state particles uniformly in all the events (Two options: Y and N. Default: N)", m_iStPsSwitch);
        }
      else if(line=="% Main name of output files (Default: Main name of the card file)")
        {
          // This else if statement should be replaced with the next else if statement. It is retained here for the convenience of old users.
          readOpenCurly(fin,line,"% Main name of output files (Default: Main name of the card file)");
          read1stLineOrCloseCurly(fin,line,false,"No main file name is found in the item with the prompt \"% Main name of output files (Default: Main name of the card file)");
          if(line!="}")
            {
              m_comNmOfOptFls=line;
              readCloseCurly(fin,line,"% Main name of output files (Default: Main name of the card file)");
            }
        }
      else if(line=="% Common name of output files (Default: Name of the card file)")
        {
          readOpenCurly(fin,line,"% Common name of output files (Default: Name of the card file)");
          read1stLineOrCloseCurly(fin,line,false,"No common file name is found in the item with the prompt \"% Common name of output files (Default: Name of the card file)");
          if(line!="}")
            {
              m_comNmOfOptFls=line;
              readCloseCurly(fin,line,"% Common name of output files (Default: Name of the card file)");
            }
        }
      else if(line=="% Complete horizontal and vertical lines in output pdf files (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Complete horizontal and vertical lines in output pdf files (Two options: Y and N. Default: N)", m_cmpltHVLines);
        }
      else if(line=="% Center decay objects in output pdf files (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Center decay objects in output pdf files (Two options: Y and N. Default: N)", m_centDcyObjs);
        }
      else if(line=="% One output root file by one input root file (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% One output root file by one input root file (Two options: Y and N. Default: N)", m_oneOptRootFlByOneIptRootFl);
        }
      else if(line=="% Maximum number of entries to be saved in a single output root file")
        {
          readNumItem(fin, line, "% Maximum number of entries to be saved in a single output root file", m_nEtrMaxInASngOptRootFl);
        }
      else if(line=="% Use array tbranches to store topology tags in output root files when possible (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Use array tbranches to store topology tags in output root files when possible (Two options: Y and N. Default: N)", m_useArrayTBrsOpt);
        }
      else if(line=="% Remove input tbranches from output root files (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Remove input tbranches from output root files (Two options: Y and N. Default: N)", m_rmIptTBrs);
        }
      else if(line=="% Convert MSI/MSD input tbranches into AOI output tbranches (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Convert MSI/MSD input tbranches into AOI output tbranches (Two options: Y and N. Default: N)", m_convtMSIMSDIntoAOI);
        }
      else if(line=="% Other TTree names")
        {
          readOpenCurly(fin,line,"% Other TTree names");
          m_othTtrNms.clear();
          while(1)
            {
              readExtraLinesOrCloseCurly(fin,line,"% Other TTree names");
              if(line=="}")
                {
                  break;
                }
              else
                {
                  m_othTtrNms.push_back(line);
                }
            }
        }
      else if(line=="% Suppress output root files (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Suppress output root files (Two options: Y and N. Default: N)", m_supprOptRootFls);
        }
      else if(line=="% Flat array tbranches locally in each output root file (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Flat array tbranches locally in each output root file (Two options: Y and N. Default: N)", m_flatArrayBrsLocally);
        }
      else if(line=="% Verbose level of standard output (Two options: Y and N. Default: N)")
        {
          readYNItem(fin, line, "% Verbose level of standard output (Two options: Y and N. Default: N)", m_vbsLevStdOut);
        }
      else
        {
          cerr<<"Error: The input line \""<<line<<"\" is invalid!"<<endl;
          string TempCardFlNm=m_pkgPath+"share/template_topoana.card";
          cerr<<"Infor: If you have ever used the item prompted with the input line successfully but it doesn't work now, this is probably because I updated the prompt of the item in order to make it clearer and more concise. In this case, I apologize for the inconvenience and appreciate your understanding and support."<<endl;
          cerr<<"Infor: There is also a probability that the input line is wrongly typed due to some reasons. Please note that the input line must be identical with the prompt of one item defined in the program."<<endl;
          cerr<<"Infor: In both of the two cases, to find the updated/right version of the item you desire, please check and see the template card file in the following path: "<<TempCardFlNm<<". Please contact me (zhouxy@buaa.edu.cn), if you could not find it."<<endl;
          exit(-1);
        }
    }
}
