#include "../include/topoana.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readSmpDcyNew(string & line, string prompt, vector< vector<int> > & vVPid, vector<string> * vNm, vector<unsigned long> * vNMax, vector<string> * vOption)
{
  int nArrow=countSubstr(line,"-->");
  if(nArrow!=1)
    {
      cerr<<"Error: "<<nArrow<<" arrows (-->) are found in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: Only one arrow is allowed in the line."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  size_t nPos=line.find("-->");
  line.replace(nPos,3," --> ");
  nPos=line.find("&");
  if(vNMax!=0)
    {
      if(nPos!=string::npos)
        {
          line.replace(nPos,1," & ");
          nPos=line.find("&",nPos+3);
        }
    }
  if(nPos!=string::npos) line.replace(nPos,1," & ");

  istringstream iss;
  iss.clear();
  string txtPnm;
  unsigned long nP;
  int pid;
  vector<int> vPid;
  vPid.clear();
  string nm;
  unsigned long nMax;
  string option;

  iss.str(line);
  int iarrow=-1;
  if(vNm!=0) nm="";
  if(vNMax!=0) nMax=ULONG_MAX;
  if(vOption!=0) option="";
  while(!iss.eof())
    {
      iss>>txtPnm;
      if(txtPnm=="-->") iarrow=vPid.size();
      else if(txtPnm=="&")
        {
          if(!iss.eof())
            {
              if(vNm!=0)
                {
                  iss>>nm;
                  if(nm=="-") nm=""; // Here, the symbol \"-\" is used as a place holder denoting the default second parameter in order to input the third parameter following it.
                  if(vNMax!=0)
                    {
                      if(!iss.eof())
                        {
                          iss>>txtPnm;
                          if(txtPnm=="&")
                            {
                              if(!iss.eof())
                                {
                                  iss>>txtPnm;
                                  if(txtPnm.find_first_not_of("0123456789")==string::npos) nMax=strtoul(txtPnm.c_str(),NULL,10);
                                  else if(txtPnm!="-")
                                    {
                                      cerr<<"Error: The input parameter \""<<txtPnm<<"\" after the second \"and\" (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
                                      cerr<<"Infor: It should be an unsigned long integer at which you want to set, or just a placeholder \"-\" as a default value \"ULONG_MAX\" and for the input of the fourth parameter."<<endl;
                                      cerr<<"Infor: Please check it."<<endl;
                                      exit(-1);
                                    }
                                  if(vOption!=0)
                                    {
                                      if(!iss.eof())
                                        {
                                          iss>>txtPnm;
                                          if(txtPnm=="&")
                                            {
                                              if(!iss.eof())
                                                {
                                                  iss>>txtPnm;
                                                  if(txtPnm=="Is"||txtPnm=="Ig"||txtPnm=="Fs"||txtPnm=="Fg"||txtPnm=="Is-IRA"||txtPnm=="Ig-IRA"||txtPnm=="Fs-IRA"||txtPnm=="Fg-IRA") option=txtPnm;
                                                  else
                                                    {
                                                      cerr<<"Error: The input parameter \""<<txtPnm<<"\" after the third \"and\" (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
                                                      cerr<<"Infor: It should be \"Is\", \"Ig\", \"Fs\", or \"Fg\", which stand for \"strict ISR photons\", \"generalized ISR photons\", \"strict FSR photons\", or \"generalized FSR photons\", respectively."<<endl;
                                                      cerr<<"Infor: It can also be \"Is-IRA\", \"Ig-IRA\", \"Fs-IRA\", or \"Fg-IRA\", where the suffix \"-IRA\" is added to indicate that the specified decay branch is intermediate-resonance-allowed."<<endl;
                                                      cerr<<"Infor: Please check it."<<endl;
                                                      exit(-1);
                                                    }
                                                }
                                            }
                                          else
                                            {
                                              cerr<<"Error: The input \""<<txtPnm<<"\" after the third parameter in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
                                              cerr<<"Infor: It should be an \"and\" (&) symbol prompting the input of the fourth parameter."<<endl;
                                              cerr<<"Infor: Please check it."<<endl;
                                              exit(-1);
                                            }
                                        }
                                    }
                                }
                            }
                          else
                            {
                              cerr<<"Error: The input \""<<txtPnm<<"\" after the second parameter in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is invalid!"<<endl;
                              cerr<<"Infor: It should be an \"and\" (&) symbol prompting the input of the third parameter."<<endl;
                              cerr<<"Infor: Please check it."<<endl;
                              exit(-1);
                            }
                        }
                    }
                }
            }
        }
      else
        {
          if(txtPnm.find_first_not_of("0123456789")==string::npos) 
            {
              nP=strtoul(txtPnm.c_str(),NULL,10);
              if(!iss.eof())
                {
                  iss>>txtPnm;
                  if(txtPnm=="&")
                    {
                      cerr<<"Error: The number \""<<nP<<"\", in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is used in front of \"&\". This is not allowed!"<<endl;
                      cerr<<"Infor: A number is only allowed to be used in front of a text particle name to specify the number of the particles."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                  else if(txtPnm.find_first_not_of("0123456789")==string::npos)
                    {
                      cerr<<"Error: The number \""<<nP<<"\", in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is used in front of another number \""<<strtoul(txtPnm.c_str(),NULL,10)<<"\". This is not allowed!"<<endl;
                      cerr<<"Infor: A number is only allowed to be used in front of a text particle name to specify the number of the particles."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                  else
                    {
                      pid=getPidFromTxtPnm(txtPnm);
                      for(unsigned int i=0;i<nP;i++) vPid.push_back(pid);
                    }
                }
              else
                {
                  cerr<<"Error: The last papameter \""<<nP<<"\", in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is a number. This is not allowed!"<<endl;
                  cerr<<"Infor: A number is only allowed to be used in front of a text particle name to specify the number of the particles."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }
            }
          else
            {
              pid=getPidFromTxtPnm(txtPnm);
              vPid.push_back(pid);
            }
        }
    }

  if(iarrow==-1)
    {
      cerr<<"Error: No arrow (-->) is found in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: It should be a problem of the program."<<endl;                             
      cerr<<"Infor: Please contact the author Xing-Yu Zhou via the email zhouxy@buaa.edu.cn"<<endl;
      exit(-1);
    }
  else if(iarrow==0)
    {
      cerr<<"Error: The arrow (-->) is found at the beginning of the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: It seems that you forgot the initial-state particle(s)."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }
  else if(iarrow==1)
    {
      if(vPid.size()==1)
        {
          cerr<<"Error: No final-state particle is found after the arrow (-->) in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
          cerr<<"Infor: There should be at least one final-state particle."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
    }
  else if(iarrow==2)
    {
      if(!((vPid[0]==m_pidOfISt1&&vPid[1]==m_pidOfISt2)||(vPid[0]==m_pidOfISt2&&vPid[1]==m_pidOfISt1)))
        {
          cerr<<"Error: The two initial-state particles in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" are not";
          writePnmFromPid(cerr,"TxtPnm",m_pidOfISt2);
          cerr<<" and";
          writePnmFromPid(cerr,"TxtPnm",m_pidOfISt1);
          cerr<<"!"<<endl;
          cerr<<"Infor: If two initial-state particles exist in the line, they should be";
          writePnmFromPid(cerr,"TxtPnm",m_pidOfISt2);
          cerr<<" and";
          writePnmFromPid(cerr,"TxtPnm",m_pidOfISt1);
          cerr<<"!"<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
      else if(vPid[0]==m_pidOfISt1&&vPid[1]==m_pidOfISt2)
        {
          vPid.erase(vPid.begin());
          vPid[0]=m_pidOfISt;
        }
      if(vPid.size()==2)
        {
          cerr<<"Error: No final-state particle is found after the arrow (-->) in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
          cerr<<"Infor: There should be at least one final-state particle."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
    }
  else
    {
      cerr<<"Error: "<<iarrow<<" (more than 2) initial-state particles are found after the arrow (-->) in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: There should be at most two initial-state particles."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    } 

  vVPid.push_back(vPid);
  if(vNm!=0) (*vNm).push_back(nm);
  if(vNMax!=0) (*vNMax).push_back(nMax);
  if(vOption!=0) (*vOption).push_back(option);
}
