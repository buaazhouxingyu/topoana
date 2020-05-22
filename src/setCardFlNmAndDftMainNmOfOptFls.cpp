#include "../include/topoana.h"

void topoana::setCardFlNmAndDftComNmOfOptFls(string cardFlNm)
{
  m_cardFlNm=cardFlNm;

  if(m_cardFlNm.size()>5&&m_cardFlNm.substr(m_cardFlNm.size()-5,5)==".card") m_comNmOfOptFls=m_cardFlNm.substr(0,(m_cardFlNm.size()-5));
  else m_comNmOfOptFls=m_cardFlNm;
}
