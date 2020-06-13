#include "../include/topoana.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

void topoana::readCmplxDcyNew(string & line, string prompt, vector< vector<int> > & vDcyBr, vector<int> & vIMDcyBr, vector<int> & vPid, vector<int> & vMidx, vector<string> & vNm, bool & bvar1, bool & bvar2, bool useAsterisk)
{
  int nArrow=countSubstr(line,"-->");
  if(nArrow!=1)
    {
      cerr<<"Error: "<<nArrow<<" arrows (-->) are found in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: Only one arrow is allowed in the line."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  int nAnd=countSubstr(line,"&");
  if(nAnd<2||nAnd>5)
    {
      cerr<<"Error: "<<nAnd<<" \"and\" (&) symbols are found in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: Two, three, four, or five \"and\" (&) symbols are allowed in one line."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  size_t nPos=line.find("-->");
  line.replace(nPos,3," --> ");
  nPos=line.find("&");
  line.replace(nPos,1," & ");
  nPos=line.find("&",nPos+3);
  line.replace(nPos,1," & ");
  nPos=line.find("&",nPos+3);
  if(nPos!=string::npos)
    {
      line.replace(nPos,1," & ");
      nPos=line.find("&",nPos+3);
      if(nPos!=string::npos) line.replace(nPos,1," & ");
    }

  istringstream iss;
  iss.clear();
  int iDcyBr;
  string txtPnm,asterisk="*"; // The asterisk symbol "*" is used as a short version of the word "anything" in order to simplify the user's input.
  unsigned long nP;
  int pid;
  vector<int> dcyBr;
  dcyBr.clear();
  int iMDcyBr;
  string nm="";  

  iss.str(line);
  iss>>txtPnm;
  if(txtPnm.find_first_not_of("0123456789")==string::npos)
    {
      iDcyBr=strtoul(txtPnm.c_str(),NULL,10);
      if((iDcyBr!=(int) vDcyBr.size())&&(iDcyBr!=0))
        {
          cerr<<"Error: The index of the decay branch: "<<iDcyBr<<" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is wrong!"<<endl;
          if(vDcyBr.size()!=0) cerr<<"Infor: It should be "<<vDcyBr.size()<<" to continue the current group of decay branches, or 0 to start a new group of decay branches."<<endl;
          else cerr<<"Infor: It should be 0 for the first decay branch."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }      
    }
  else
    {
      cerr<<"Error: The first parameter: "<<txtPnm<<" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is not an unsigned int integer!"<<endl;
      cerr<<"Infor: It should be an unsigned int integer denoting the index of the decay branch."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }          

  if((iDcyBr==0)&&(vDcyBr.size()>0)) getVPidandVMidx(vDcyBr,vIMDcyBr,vPid,vMidx);

  iss>>txtPnm;
  if(txtPnm!="&")
    {
      cerr<<"Error: The second parameter: "<<txtPnm<<" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is not an and (&) symbol!"<<endl;
      cerr<<"Infor: It should be an and (&) symbol as an separator."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }

  int iarrow=-1;
  while(!iss.eof())
    {
      iss>>txtPnm;
      if(txtPnm=="-->") iarrow=dcyBr.size();
      else if(txtPnm=="&")
        {
          if(!iss.eof())
            {
              iss>>txtPnm;
              if(txtPnm=="-1"||txtPnm.find_first_not_of("0123456789")==string::npos)
                {
                  iMDcyBr=strtoul(txtPnm.c_str(),NULL,10);
                  if(iMDcyBr>=iDcyBr)
                    {
                      cerr<<"Error: The index of the mother decay branch: "<<iMDcyBr<<" in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is ";
                      if(iMDcyBr>iDcyBr) cerr<<"greater than";
                      else cerr<<"equal to";
                      cerr<<" the the index of the current decay branch: "<<iDcyBr<<"!"<<endl;
                      cerr<<"Infor: The former must be less than the latter, that is to say, the decay branch must be input after its mother decay branch."<<endl;
                      cerr<<"Infor: Please check it."<<endl;
                      exit(-1);
                    }
                  else
                    {
                      vIMDcyBr.push_back(iMDcyBr);
                      if(iDcyBr==0)
                        {
                          if(!iss.eof())
                            {
                              iss>>txtPnm;
                              if(txtPnm=="&")
                                {
                                  if(!iss.eof())
                                    {
                                      iss>>nm;
                                      if(nm=="-") nm="";
                                      if(!iss.eof())
                                        {
                                          iss>>txtPnm;
                                          if(txtPnm=="&")
                                            {
                                              if(!iss.eof())
                                                {
                                                  txtPnm="";
                                                  iss>>txtPnm;
                                                  if(txtPnm=="Y") bvar1=true;
                                                  else if(txtPnm=="N") bvar1=false;
                                                  else if(txtPnm=="")
                                                    {
                                                      cerr<<"Error: There is no input parameter after the fourth \"and\" (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"! There should be an input parameter after the fourth \"and\" (&) symbol!"<<endl;
                                                      cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                                                      cerr<<"Infor: Please check it."<<endl;
                                                      exit(-1);                                             
                                                    }
                                                  else
                                                    {                                                       cerr<<"Error: The input parameter \""<<txtPnm<<"\", after the fourth \"and\" (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is invalid!"<<endl;                                               
                                                      cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                                                      cerr<<"Infor: Please check it."<<endl;
                                                      exit(-1);
                                                    }
                                                }
                                            }
                                          else
                                            {
                                              cerr<<"Error: The input parameter \""<<txtPnm<<"\", after the index of the alias of the current decay branch in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is not an \"and\" (&) symbol!"<<endl;
                                              cerr<<"Infor: It should be an \"and\" (&) symbol prompting the input of the alias of the decay branch in the line."<<endl;
                                              cerr<<"Infor: Please check it."<<endl;
                                              exit(-1);                                              
                                            }
                                        }
                                      if(!iss.eof())
                                        {
                                          iss>>txtPnm;
                                          if(txtPnm=="&")
                                            {
                                              if(!iss.eof())
                                                {
                                                  txtPnm="";
                                                  iss>>txtPnm;
                                                  if(txtPnm=="Y") bvar2=true;
                                                  else if(txtPnm=="N") bvar2=false;
                                                  else if(txtPnm=="")
                                                    {
                                                      cerr<<"Error: There is no input parameter after the fifth \"and\" (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"! There should be an input parameter after the fifth \"and\" (&) symbol!"<<endl;
                                                      cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                                                      cerr<<"Infor: Please check it."<<endl;
                                                      exit(-1);                                             
                                                    }
                                                  else
                                                    {                                                       cerr<<"Error: The input parameter \""<<txtPnm<<"\", after the fifth \"and\" (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is invalid!"<<endl;                                               
                                                      cerr<<"Infor: It should be \"Y\" or \"N\"."<<endl;
                                                      cerr<<"Infor: Please check it."<<endl;
                                                      exit(-1);
                                                    }
                                                }
                                            }
                                          else
                                            {
                                              cerr<<"Error: The input parameter \""<<txtPnm<<"\", after the index of the alias of the current decay branch in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is not an \"and\" (&) symbol!"<<endl;
                                              cerr<<"Infor: It should be an \"and\" (&) symbol prompting the input of the alias of the decay branch in the line."<<endl;
                                              cerr<<"Infor: Please check it."<<endl;
                                              exit(-1);                                              
                                            }
                                        }
                                    }
                                }
                              else
                                {
                                  cerr<<"Error: The input parameter after the index of the mother decay branch of the current decay branch in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is not an \"and\" (&) symbol!"<<endl;
                                  cerr<<"Infor: It should be an \"and\" (&) symbol prompting the input of the alias of the decay branch in the line."<<endl;
                                  cerr<<"Infor: Please check it."<<endl;
                                  exit(-1);
                                }
                            }
                          vNm.push_back(nm);
                        }
                    }
                }
              else
                {
                  cerr<<"Error: The input parameter after the second and (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" is not \"-1\" or an unsigned int integer!"<<endl;
                  cerr<<"Infor: It should be \"-1\" or an unsigned int integer denoting the index of the mother decay branch of the current decay branch."<<endl;
                  cerr<<"Infor: Please check it."<<endl;
                  exit(-1);
                }                       
            }
          else
            {
              cerr<<"Error: No input parameter exists after the second and (&) symbol in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
              cerr<<"Infor: It should be an unsigned int integer denoting the index of the mother decay branch of the current decay branch."<<endl;                
              cerr<<"Infor: Please check it."<<endl;
              exit(-1);
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
                  if(txtPnm=="&"||(useAsterisk==true&&txtPnm==asterisk))
                    {
                      cerr<<"Error: The number \""<<nP<<"\", in the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\", is used in front of \""<<txtPnm<<"\". This is not allowed!"<<endl;
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
                      for(unsigned int i=0;i<nP;i++) dcyBr.push_back(pid);
                    }
                }
            }
          else
            {
              if(useAsterisk==true&&txtPnm==asterisk) txtPnm="anything";
              pid=getPidFromTxtPnm(txtPnm);
              dcyBr.push_back(pid);
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
      cerr<<"Error: The arrow (-->) is found at the beginning of the decay branch part of the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: It seems that you forgot the initial-state particle(s)."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }
  else if(iarrow==1)
    {
      if(dcyBr.size()==1)
        {
          cerr<<"Error: No final-state particle is found after the arrow (-->) in the decay branch part of the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
          cerr<<"Infor: There should be at least one final-state particle."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
    }
  else if(iarrow==2)
    {
      if(!((dcyBr[0]==m_pidOfISt1&&dcyBr[1]==m_pidOfISt2)||(dcyBr[0]==m_pidOfISt2&&dcyBr[1]==m_pidOfISt1)))
        {
          cerr<<"Error: The two initial-state particles in the decay branch part of the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\" are not the electron and positron pair!"<<endl;
          cerr<<"Infor: If two initial-state particles exist in the line, they should be the electron and positron pair."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
      else if(dcyBr[0]==m_pidOfISt1&&dcyBr[1]==m_pidOfISt2)
        {
          // dcyBr[0]=m_pidOfISt2;
          // dcyBr[1]=m_pidOfISt1;
          dcyBr.erase(dcyBr.begin());
          dcyBr[0]=m_pidOfISt;
        }
      if(dcyBr.size()==2)
        {
          cerr<<"Error: No final-state particle is found after the arrow (-->) in the decay branch part of the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
          cerr<<"Infor: There should be at least one final-state particle."<<endl;
          cerr<<"Infor: Please check it."<<endl;
          exit(-1);
        }
    }
  else
    {
      cerr<<"Error: "<<iarrow<<" (more than 2) initial-state particles are found after the arrow (-->) in the decay branch part of the line \""<<line<<"\" for the item with the prompt \""<<prompt<<"\"!"<<endl;
      cerr<<"Infor: There should be at most two initial-state particles."<<endl;
      cerr<<"Infor: Please check it."<<endl;
      exit(-1);
    }
  
  vDcyBr.push_back(dcyBr);
}
