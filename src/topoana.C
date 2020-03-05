#include "../include/topoana.h"

int main(int argc,char *argv[])
{
  topoana ta;
  ta.makeMapsOnPdata();
  ta.makeNNmMap();
  ta.readCard(ta.getCardFlNm0());
  if(argc>1&&argv[1][0]!='-') ta.setCardFlNmAndDftMainNmOfOptFls(argv[1]);
  else ta.setCardFlNmAndDftMainNmOfOptFls("topoana.card");
  ta.readCard(ta.getCardFlNm());
  // The following loop offers a mechanism to reset the names of input root files and the main name of output files with the arguments provided in the command line.
  for(int i=1;i<argc;i++)
    {
      if(strcmp(argv[i],"-i")==0)
        {
          if(i+1<argc&&argv[i+1][0]!='-')
            {
              ta.clearNmsOfIptRootFls();
              for(i++;i<argc;i++)
                {
                  if(argv[i][0]!='-') ta.pushBackNmOfIptRootFl(argv[i]);
                  else
                    {
                      i--;
                      break;
                    }
                }
            }
          else
            {
              cerr<<"Error: The argument \"-i\" is specified without the names of input root files following it!"<<endl;
              cerr<<"Infor: Please specify the names of input root files or remove the argument \"-i\" according to your needs."<<endl;
              exit(-1);
            }
        }
      else if(strcmp(argv[i],"-o")==0)
        {
          if(i+1<argc&&argv[i+1][0]!='-')
            { 
              ta.resetMainNmOfOptFls(argv[i+1]);
            }
          else
            {
               cerr<<"Error: The argument \"-o\" is specified without the main name of output files following it!"<<endl;
               cerr<<"Infor: Please specify the main name of output files or remove the argument \"-o\" according to your needs."<<endl;
               exit(-1);
            }
        }
    }
  ta.checkInput();
  ta.getRslt();
  ta.writeRsltIntoTxtFl();
  ta.writeRsltIntoTexFl();
  ta.getPdfFlFromTexFl();
  ta.writeInfOnRslt();
  return 0;
}
