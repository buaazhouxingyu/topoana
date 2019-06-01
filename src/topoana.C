#include "../include/topoana.h"

int main(int argc,char *argv[])
{
  topoana ta;
  ta.makeMapsOnPdata();
  ta.readCard(ta.getCardFlNm0());
  if(argc>1) ta.setCardFlNmAndDftMainNmOfOptFls(argv[1]);
  else ta.setCardFlNmAndDftMainNmOfOptFls("topoana.card");
  ta.readCard(ta.getCardFlNm());
  ta.checkInput();
  ta.getRslt();
  ta.writeRsltIntoTxtFl();
  ta.writeRsltIntoTexFl();
  ta.getPdfFlFromTexFl();
  ta.writeInfOnRslt();
  return 0;
}
