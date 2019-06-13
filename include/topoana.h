#ifndef TOPOANA_H
#define TOPOANA_H

#include <vector>
#include <string>
#include <list>
#include <map>
#include <climits>
#include <unordered_map>
using namespace std;

class topoana
{
  private:
    string m_pkgPath;
    string m_verNum;
    string m_cardFlNm0;
    string m_cardFlNm;

    map<int,int> m_pid3PchrgMap;
    map<int,string> m_pidTxtPnmMap;
    map<int,string> m_pidTexPnmMap;
    map<int,int> m_pidIccPMap;

    vector<string> m_nmsOfIptRootFls;
    string m_trNm;
    string m_brNmOfNps;
    string m_brNmOfPid;
    string m_brNmOfMidx;
    string m_strgTpOfRawIptTopoDat;
    unsigned long m_nEtrsMax;
    string m_cut;
    bool m_cutMethod;
    unsigned int m_hHdDcyBrsMax;
    vector<int> m_vIdPid;
    vector<int> m_vIddPid;
    bool m_ignoreGISR;
    bool m_ignoreGFSR;

    bool m_compAnaOfDcyTrs;
    unsigned long m_nDcyTrsToBePrtdMax;
    bool m_adjDcyIFStsIntoACol;
    bool m_compAnaOfDcyIFSts;
    unsigned long m_nDcyIFStsToBePrtdMax;
    vector<int> m_vPid_compP;
    vector<unsigned long> m_vNDcyBrsToBePrtdMax;
    vector<string> m_vNm_compP;
    vector< vector<int> > m_vVPid_compIncDcyBr;
    vector<unsigned long> m_vNExcCompsToBePrtdMax;
    vector<string> m_vNm_compIncDcyBr;
    vector< vector<int> > m_vVPid_compIRADcyBr;
    vector<unsigned long> m_vNIntStrusToBePrtdMax;
    vector<string> m_vNm_compIRADcyBr;

    vector< vector<int> > m_vVPid_sigDcyTr;
    vector< vector<int> > m_vVMidx_sigDcyTr;
    vector<string> m_vNm_sigDcyTr;
    vector< vector<int> > m_vVPid_sigDcyIFSts2;
    vector<string> m_vNm_sigDcyIFSts2;
    vector<int> m_vPid_sigP;
    vector<string> m_vNm_sigP;
    vector< vector<int> > m_vVPid_sigDcyBr;
    vector<string> m_vNm_sigDcyBr;
    vector< vector<int> > m_vVPid_sigIncDcyBr;
    vector<string> m_vNm_sigIncDcyBr;
    vector< vector<int> > m_vVPid_sigCascDcyBrs;
    vector< vector<int> > m_vVMidx_sigCascDcyBrs;
    vector<string> m_vNm_sigCascDcyBrs;
    vector< vector<int> > m_vVPid_sigIncCascDcyBrs;
    vector< vector<int> > m_vVMidx_sigIncCascDcyBrs;
    vector<string> m_vNm_sigIncCascDcyBrs;
    vector< vector<int> > m_vVPid_sigIRADcyBr;
    vector<string> m_vNm_sigIRADcyBr;
    vector< vector<int> > m_vVPid_sigIncOrIRACascDcyBrs;
    vector< vector<int> > m_vVMidx_sigIncOrIRACascDcyBrs;
    vector<string> m_vNm_sigIncOrIRACascDcyBrs;

    bool m_ccSwitch;
    string m_anaTasksForSigIds;
    bool m_sortTheToposForSigIds;
    bool m_initEpEmSwitch;

    string m_mainNmOfOptFls;
    bool m_centDcyObjs;
    bool m_sprTopoTags;
    bool m_oneOptRootFlByOneIptRootFl;
    unsigned long m_nEtrsMaxInASngOptRootFl;
    bool m_useArrayBrsOpt;
    bool m_cpIptBrs;

    vector<int> m_vIdCcPid;
    vector<int> m_vIdICcPid;
    vector<int> m_vIddCcPid;
    vector<int> m_vIddICcPid;

    vector< vector< list<int> > > m_vDcyTr, m_vCcDcyTr;
    vector<int> m_vIDcyTr, m_vICcDcyTr;
    vector<int> m_vNDcyTr, m_vNCcDcyTr;
    unordered_map<string,int> m_uomDcyTr, m_uomCcDcyTr;
    vector< list<int> > m_vDcyIFSts, m_vCcDcyIFSts;
    vector<int> m_vIDcyIFSts, m_vICcDcyIFSts;
    vector<int> m_vNDcyIFSts, m_vNCcDcyIFSts;
    unordered_map<string,int> m_uomDcyIFSts, m_uomCcDcyIFSts;
    map<int,int> m_iDcyTrIDcyIFStsMap, m_iDcyTrICcDcyIFStsMap;
    vector<int> m_vPid_ccCompP;
    vector<int> m_vICcCompP;
    // Pay attention to that m_vVDcyBrCcP, m_vVIDcyBrCcP and m_vVNDcyBrCcP equate to m_vVCcDcyBrP, m_vVICcDcyBrP and m_vVNCcDcyBrP for self-charge-conjugate particles.
    vector< vector< list<int> > > m_vVDcyBrP, m_vVDcyBrCcP;
    vector< vector<int> > m_vVIDcyBrP, m_vVIDcyBrCcP;
    vector< vector<int> > m_vVNDcyBrP, m_vVNDcyBrCcP;
    vector< list<int> > m_vCompIncDcyBr,m_vCompCcIncDcyBr;
    vector<int> m_vCompICcIncDcyBr;
    // Pay attention to that m_vVDcyBrCcIncDcyBr, m_vVIDcyBrCcIncDcyBr and m_vVNDcyBrCcIncDcyBr equate to m_vVCcDcyBrIncDcyBr, m_vVICcDcyBrIncDcyBr and m_vVNCcDcyBrIncDcyBr for self-charge-conjugate inclusive decays.
    vector< vector< list<int> > > m_vVDcyBrIncDcyBr, m_vVDcyBrCcIncDcyBr;
    vector< vector<int> > m_vVIDcyBrIncDcyBr, m_vVIDcyBrCcIncDcyBr;
    vector< vector<int> > m_vVNDcyBrIncDcyBr, m_vVNDcyBrCcIncDcyBr;
    vector< list<int> > m_vCompIRADcyBr,m_vCompCcIRADcyBr;
    vector<int> m_vCompICcIRADcyBr;
    // Pay attention to that m_vVDcyBrCcIRADcyBr, m_vVIDcyBrCcIRADcyBr and m_vVNDcyBrCcIRADcyBr equate to m_vVCcDcyBrIRADcyBr, m_vVICcDcyBrIRADcyBr and m_vVNCcDcyBrIRADcyBr for self-charge-conjugate inclusive decays.
    vector< vector< vector< list<int> > > > m_vVDcyBrIRADcyBr, m_vVDcyBrCcIRADcyBr;
    vector< vector<int> > m_vVIDcyBrIRADcyBr, m_vVIDcyBrCcIRADcyBr;
    vector< vector<int> > m_vVNDcyBrIRADcyBr, m_vVNDcyBrCcIRADcyBr;

    vector< vector< list<int> > > m_vSigDcyTr, m_vCcSigDcyTr;
    vector<int> m_vISigDcyTr, m_vICcSigDcyTr;
    vector<int> m_vNSigDcyTr, m_vNCcSigDcyTr;
    vector< list<int> > m_vSigDcyIFSts, m_vCcSigDcyIFSts;
    vector<int> m_vISigDcyIFSts, m_vICcSigDcyIFSts;
    vector<int> m_vNSigDcyIFSts, m_vNCcSigDcyIFSts;
    map<int,int> m_iSigDcyTrISigDcyIFStsMap, m_iSigDcyTrICcSigDcyIFStsMap;
    vector< list<int> > m_vSigDcyIFSts2, m_vCcSigDcyIFSts2;
    vector<int> m_vISigDcyIFSts2, m_vICcSigDcyIFSts2;
    vector<int> m_vNSigDcyIFSts2, m_vNCcSigDcyIFSts2;
    map<int,int> m_iSigDcyTrIDcyTrMap, m_iSigDcyTrICcDcyTrMap;
    map<int,int> m_iSigDcyIFStsIDcyIFStsMap, m_iSigDcyIFStsICcDcyIFStsMap;
    map<int,int> m_iSigDcyIFSts2IDcyIFStsMap, m_iSigDcyIFSts2ICcDcyIFStsMap;
    vector<int> m_vPid_ccSigP;
    vector<int> m_vISigP, m_vICcSigP;              
    vector<int> m_vNSigP, m_vNCcSigP;
    vector< list<int> > m_vSigDcyBr, m_vCcSigDcyBr;
    vector<int> m_vISigDcyBr, m_vICcSigDcyBr;
    vector<int> m_vNSigDcyBr, m_vNCcSigDcyBr;
    vector< list<int> > m_vSigIncDcyBr, m_vCcSigIncDcyBr;
    vector<int> m_vISigIncDcyBr, m_vICcSigIncDcyBr;
    vector<int> m_vNSigIncDcyBr, m_vNCcSigIncDcyBr;
    vector< vector< list<int> > > m_vSigCascDcyBrs, m_vCcSigCascDcyBrs;
    vector< vector<int> > m_vVSigCascDcyBrsIdxOfHead, m_vVCcSigCascDcyBrsIdxOfHead;
    vector< vector<int> > m_vVSigCascDcyBrsMidxOfHead, m_vVCcSigCascDcyBrsMidxOfHead;
    vector<int> m_vISigCascDcyBrs, m_vICcSigCascDcyBrs;
    vector<int> m_vNSigCascDcyBrs, m_vNCcSigCascDcyBrs;
    vector< vector< list<int> > > m_vSigIncCascDcyBrs, m_vCcSigIncCascDcyBrs;
    vector< vector<int> > m_vVSigIncCascDcyBrsIdxOfHead, m_vVCcSigIncCascDcyBrsIdxOfHead;
    vector< vector<int> > m_vVSigIncCascDcyBrsMidxOfHead, m_vVCcSigIncCascDcyBrsMidxOfHead;
    vector< vector<int> > m_vVIIncSigIncCascDcyBrs;
    vector<int> m_vISigIncCascDcyBrs, m_vICcSigIncCascDcyBrs;
    vector<int> m_vNSigIncCascDcyBrs, m_vNCcSigIncCascDcyBrs;
    vector< list<int> > m_vSigIRADcyBr, m_vCcSigIRADcyBr;
    vector<int> m_vISigIRADcyBr, m_vICcSigIRADcyBr;
    vector<int> m_vNSigIRADcyBr, m_vNCcSigIRADcyBr;
    vector< vector< list<int> > > m_vSigIncOrIRACascDcyBrs, m_vCcSigIncOrIRACascDcyBrs;
    vector< vector<int> > m_vVSigIncOrIRACascDcyBrsIdxOfHead, m_vVCcSigIncOrIRACascDcyBrsIdxOfHead;
    vector< vector<int> > m_vVSigIncOrIRACascDcyBrsMidxOfHead, m_vVCcSigIncOrIRACascDcyBrsMidxOfHead;
    vector< vector<int> > m_vVIIncSigIncOrIRACascDcyBrs;
    vector< vector<int> > m_vVIIRASigIncOrIRACascDcyBrs;
    vector<int> m_vISigIncOrIRACascDcyBrs, m_vICcSigIncOrIRACascDcyBrs;
    vector<int> m_vNSigIncOrIRACascDcyBrs, m_vNCcSigIncOrIRACascDcyBrs;

    int m_pidOfGISRGam;
    int m_pidOfGFSRGam;
    int m_pidOfISt;
    int m_pidOfAnything;
    int m_pidOfIRAFlag;
  public:
    topoana()
    {
      m_pkgPath="/home/belle2/zhouxy/workarea/repositories/topoana/";
      m_verNum="1.8.7";
      m_cardFlNm0=m_pkgPath+"share/topoana.card_with_preconfigured_items";

      m_nmsOfIptRootFls.clear();
      m_brNmOfNps="nMCGen";
      m_brNmOfPid="MCGenPDG";
      m_brNmOfMidx="MCGenMothIndex";
      m_strgTpOfRawIptTopoDat="AI";
      m_nEtrsMax=ULONG_MAX; // ULONG_MAX=9223372036854775807 is the maximum unsigned long int number. 
      m_cutMethod=false;
      m_hHdDcyBrsMax=UINT_MAX;
      m_vIdPid.clear();
      m_vIddPid.clear();
      m_ignoreGISR=false;
      m_ignoreGFSR=false;

      m_compAnaOfDcyTrs=false;
      m_nDcyTrsToBePrtdMax=ULONG_MAX;
      m_adjDcyIFStsIntoACol=false;
      m_compAnaOfDcyIFSts=false;
      m_nDcyIFStsToBePrtdMax=ULONG_MAX;

      m_vPid_compP.clear();
      m_vNDcyBrsToBePrtdMax.clear();
      m_vNm_compP.clear();
      m_vVPid_compIncDcyBr.clear();
      m_vNExcCompsToBePrtdMax.clear();
      m_vNm_compIncDcyBr.clear();
      m_vVPid_compIRADcyBr.clear();
      m_vNIntStrusToBePrtdMax.clear();
      m_vNm_compIRADcyBr.clear();

      m_vVPid_sigDcyTr.clear();
      m_vVMidx_sigDcyTr.clear();
      m_vNm_sigDcyTr.clear();
      m_vVPid_sigDcyIFSts2.clear();
      m_vNm_sigDcyIFSts2.clear();
      m_vPid_sigP.clear();
      m_vNm_sigP.clear();
      m_vVPid_sigDcyBr.clear();
      m_vNm_sigDcyBr.clear();
      m_vVPid_sigIncDcyBr.clear();
      m_vNm_sigIncDcyBr.clear();
      m_vVPid_sigCascDcyBrs.clear();
      m_vVMidx_sigCascDcyBrs.clear();
      m_vNm_sigCascDcyBrs.clear();
      m_vVPid_sigIncCascDcyBrs.clear();
      m_vVMidx_sigIncCascDcyBrs.clear();
      m_vNm_sigIncCascDcyBrs.clear();
      m_vVPid_sigIRADcyBr.clear();
      m_vNm_sigIRADcyBr.clear();
      m_vVPid_sigIncOrIRACascDcyBrs.clear();
      m_vVMidx_sigIncOrIRACascDcyBrs.clear();
      m_vNm_sigIncOrIRACascDcyBrs.clear();

      m_ccSwitch=false;
      m_anaTasksForSigIds="TC";
      m_sortTheToposForSigIds=false;
      m_initEpEmSwitch=false;

      m_centDcyObjs=false;
      m_sprTopoTags=false;
      m_oneOptRootFlByOneIptRootFl=false;
      m_nEtrsMaxInASngOptRootFl=ULONG_MAX;
      m_useArrayBrsOpt=false;
      m_cpIptBrs=true;

      m_pidOfGISRGam=22222222;
      m_pidOfGFSRGam=-22222222;
      m_pidOfISt=99999999;
      m_pidOfAnything=-99999999;
      m_pidOfIRAFlag=100000000;
    }
    ~topoana(){}
    string         getCardFlNm0() {return m_cardFlNm0;};
    void           setCardFlNmAndDftMainNmOfOptFls(string cardFlNm);
    string         getCardFlNm() {return m_cardFlNm;};
    string &       trim(string & line);
    void           makeMapsOnPdata();
    int 	   getPidFromTxtPnm(string pnm);
    void           writeErrInfOnPid3PchrgMap(int pid);
    void           writePnmFromPid(ostream & out,string pnmType,int pid);
    void           reviseIptQts(double & Npsd, double Pidd[], double Midxd[], int & Nps, int Pid[], int Midx[]);
    void           sortByPidAndPchrg(vector<int> &via,vector<int> &vib,vector<int> &vic,vector<int> &vid);
    void           sortBySzPidAndPchrg(vector< vector<int> > &vVia,vector< vector<int> > &vVib,vector< vector<int> >&vVic,vector< vector<int> > &vVid);
    bool           cmprBySzPidAndPchrg(vector<int> & via, vector<int> & vib);
    void           recurHigherHierExchOrd(vector<int> & vNewIdx, vector<int> & vOldIdx, vector<int> & vPid, vector<int> & vMidx);
    void           recurHighHierExchOrd(vector<int> & vIdxYngi, vector<int> & vIdxYngj, vector<int> & vPid, vector<int> & vMidx);
    void           sortPs(vector<int> & vPid, vector<int> & vMidx);
    int		   getCcPid(int pid);
    void           getDcyTr(vector<int> vPid,vector<int> vMidx,vector< list<int> > & dcyTr);
    void           getDcyTr(vector<int> vPid,vector<int> vMidx,vector< list<int> > & dcyTr, vector<int> & vIdxOfHead, vector<int> & vMidxOfHead);
    void           getDcyTr(vector<int> vPid,vector<int> vMidx,vector< list<int> > & dcyTr, vector<int> & vIdxOfHead, vector<int> & vMidxOfHead, vector<int> & vIIncIncCascDcyBrs);
    void           getDcyTr(vector<int> vPid,vector<int> vMidx,vector< list<int> > & dcyTr, vector<int> & vIdxOfHead, vector<int> & vMidxOfHead, vector<int> & vIIncIncOrIRACascDcyBrs, vector<int> & vIIRAIncOrIRACascDcyBrs);
    void           sortByPidAndPchrg(list<int> &lia);
    void           getDcyIFSts(vector<int> & vPid,vector<int> & vMidx,list<int> & dcyIFSts);
    unsigned int   countIRADcyBr(vector<int> & vPid, vector<int> & vMidx, list<int> IRADcyBr, bool areHeadsRequiredToBeMatched=false,vector< vector< list<int> > > * vDcyBrIRADcyBr=0);
    void           readOpenCurly(ifstream & fin, string & line, string prompt);
    void           read1stLineOrCloseCurly(ifstream & fin, string & line, bool essential, string errinforprompt);
    void           readExtraLinesOrCloseCurly(ifstream & fin, string & line, string prompt);
    void           readCloseCurly(ifstream & fin, string & line, string prompt);
    void           readCard(string cardFlNm);
    void	   checkInput();
    unsigned int   countIncLiaInVlib(list<int> & lia, vector< list<int> > & Vlib);
    bool	   isLiaMatchedWithLib(list<int> & lia, list<int> & lib);
    unsigned int   countCascDcyBrsInDcyTr(vector< list<int> > & cascDcyBrs, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2);
    unsigned int   countIncCascDcyBrsInDcyTr(vector<int> vIIncIncCascDcyBrs, vector< list<int> > & incCascDcyBrs, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2);
    void           getSubsetsOfVPidandVMidxFromAP(vector<int> & vPid,vector<int> & vMidx, int idx);
    bool	   isPaADescendantOfPb(vector<int> vMidx, int idxA, int idxB);
    unsigned int   countIncOrIRACascDcyBrsInDcyTr(vector<int> vIIncIncOrIRACascDcyBrs, vector<int> vIIRAIncOrIRACascDcyBrs, vector< list<int> > & incOrIRACascDcyBrs, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2, vector<int> vPid, vector<int> vMidx);
    void           flatArrayBrs(string nmOfOptRootFl);
    void           rmIptBrs(string nmOfOptRootFl);
    void           sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector< vector< list<int> > > &vVLib1,vector< vector< list<int> > > &vVLib2,vector<int> &vic1,vector<int> &vic2);
    void           sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector< vector< list<int> > > &vVLib1,vector< vector< list<int> > > &vVLib2,vector<int> &vic1,vector<int> &vic2,vector< vector<int> > &vid1,vector< vector<int> > &vid2,vector< vector<int> > &vie1,vector< vector<int> > &vie2);
    void           sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector< list<int> > &vLib1,vector< list<int> > &vLib2,vector<int> &vic1,vector<int> &vic2);
    void           sortBySumOf1stAnd2ndFromLrgToSml(vector<int> &via1,vector<int> &via2,vector<int> &vib1,vector<int> &vib2,vector<int> &vic1,vector<int> &vic2);
    void           sortBy1stFromLrgToSml(vector<int> &via,vector< vector< list<int> > > &vVLib,vector<int> &vic);
    void           sortBy1stFromLrgToSml(vector<int> &via,vector< vector< list<int> > > &vVLib,vector<int> &vic,vector< vector<int> > &vVid,vector< vector<int> > &vVie);
    void           sortBy1stFromLrgToSml(vector<int> &via,vector< list<int> > &vLib,vector<int> &vic);
    void           sortBy1stFromLrgToSml(vector<int> &via,vector<int> &vib,vector<int> &vic);
    void           getRslt();
    void           writeRsltIntoTxtFl();
    void           writeRsltIntoTexFl();
    void           getPdfFlFromTexFl();
    void           writeInfOnRslt();
};

#endif
