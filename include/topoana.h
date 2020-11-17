#ifndef TOPOANA_H
#define TOPOANA_H

// Begin the declaration of the topoana class

#include <vector>
#include <string>
#include <list>
#include <map>
#include <climits>
#include <unordered_map>
#include "TTree.h"
#include "TChain.h"
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
    map<int,string> m_nNmMap;

    vector<string> m_nmsOfIptRootFls;
    string m_ttrNm;
    string m_tbrNmOfNps;
    string m_tbrNmOfPid;
    string m_tbrNmOfMidx;
    unsigned int m_nMinTbrOfPidMidx;
    bool m_avoidOverCounting;
    string m_tbrNmOfIcandi;
    string m_tbrNmOfRidx;
    bool m_useRidx;
    string m_strgTpOfRawIptTopoDat;
    bool m_fixMidxBESIII;
    unsigned long m_nEtrMax;
    vector<string> m_vCut;
    string m_cut;
    bool m_cutMethod;
    unsigned long m_hHdDcyBrsMax;
    vector<int> m_vIdPid;
    vector<int> m_vIddPid;
    bool m_retainPi02GamGam;
    vector< vector<int> > m_vVPid_ignoreFDcyBr;
    string m_ignoreISR;
    string m_ignoreFSR;

    bool m_compAnaOfDcyTrs;
    unsigned long m_nDcyTrsToBePrtdMax;
    bool m_dcyIFStsUnderDcyTr;
    bool m_optIdxAndMidxOfDcyBrInDcyTr;
    bool m_compAnaOfDcyIFSts;
    unsigned long m_nDcyIFStsToBePrtdMax;
    vector<int> m_vPid_compDcyBrP;
    vector<string> m_vNm_compDcyBrP;
    vector<unsigned long> m_vNDcyBrToBePrtdMax;
    vector<unsigned long> m_vNDcyBrP; // The variable is not truely used but only taken as a placeholder for the fourth parameter of the function readPItem.
    vector<string> m_vTypeOfTagRec_compDcyBrP;
    vector<string> m_vTBrNmOfTagRec_compDcyBrP;
    vector<string> m_vTBrNmOfNRec_compDcyBrP;
    vector<int> m_vPid_compCascDcyBrP;
    vector<string> m_vNm_compCascDcyBrP;
    vector<unsigned long> m_vNCascDcyBrToBePrtdMax;
    vector<unsigned long> m_vHCascDcyBrMax;
    vector<string> m_vTypeOfTagRec_compCascDcyBrP;
    vector<string> m_vTBrNmOfTagRec_compCascDcyBrP;
    vector<string> m_vTBrNmOfNRec_compCascDcyBrP;
    vector<bool> m_vOptIdxAndMidxOfDcyBrInCascDcyBrP;
    vector<int> m_vPid_compDcyFStP;
    vector<string> m_vNm_compDcyFStP;
    vector<unsigned long> m_vNDcyFStToBePrtdMax;
    vector<unsigned long> m_vNDcyFStP;
    vector<string> m_vTypeOfTagRec_compDcyFStP;
    vector<string> m_vTBrNmOfTagRec_compDcyFStP;
    vector<string> m_vTBrNmOfNRec_compDcyFStP;
    vector<int> m_vPid_compProdBrP;
    vector<string> m_vNm_compProdBrP;
    vector<unsigned long> m_vNProdBrToBePrtdMax;
    vector<unsigned long> m_vNProdBrP; // The variable is not truely used but only taken as a placeholder for the fourth parameter of the function readPItem.
    vector<string> m_vTypeOfTagRec_compProdBrP;
    vector<string> m_vTBrNmOfTagRec_compProdBrP;
    vector<string> m_vTBrNmOfNRec_compProdBrP;
    vector<int> m_vPid_compMP;
    vector<string> m_vNm_compMP;
    vector<unsigned long> m_vNMToBePrtdMax;
    vector<unsigned long> m_vNMP; // The variable is not truely used but only taken as a placeholder for the fourth parameter of the function readPItem.
    vector<string> m_vTypeOfTagRec_compMP;
    vector<string> m_vTBrNmOfTagRec_compMP;
    vector<string> m_vTBrNmOfNRec_compMP;
    vector< vector<int> > m_vVPid_compIncDcyBr;
    vector<string> m_vNm_compIncDcyBr;
    vector<unsigned long> m_vNExcCompsToBePrtdMax;
    vector<string> m_vOption_compIncDcyBr;
    vector< vector<int> > m_vVPid_compIRADcyBr;
    vector<string> m_vNm_compIRADcyBr;
    vector<unsigned long> m_vNIntStrusToBePrtdMax;

    vector< vector<int> > m_vVPid_sigDcyTr;
    vector< vector<int> > m_vVMidx_sigDcyTr;
    vector<string> m_vNm_sigDcyTr;
    bool m_sigDcyIFStsUnderSigDcyTr;
    bool m_optIdxAndMidxOfSigDcyBrInSigDcyTr;
    bool m_sigDcyIFSts_tr;
    vector< vector<int> > m_vVPid_sigDcyIFSts;
    vector<string> m_vNm_sigDcyIFSts;
    vector<int> m_vPid_sigP;
    vector<string> m_vNm_sigP;
    vector< vector<int> > m_vVPid_sigDcyBr;
    vector<string> m_vNm_sigDcyBr;
    vector< vector<int> > m_vVPid_sigIncDcyBr;
    vector<string> m_vNm_sigIncDcyBr;
    vector< vector<int> > m_vVPid_sigCascDcyBr;
    vector< vector<int> > m_vVMidx_sigCascDcyBr;
    vector<string> m_vNm_sigCascDcyBr;
    bool m_optIdxAndMidxOfSigDcyBrInSigCascDcyBr;
    vector< vector<int> > m_vVPid_sigIncCascDcyBr;
    vector< vector<int> > m_vVMidx_sigIncCascDcyBr;
    vector<string> m_vNm_sigIncCascDcyBr;
    bool m_optIdxAndMidxOfSigDcyBrInSigIncCascDcyBr;
    vector< vector<int> > m_vVPid_sigIRADcyBr;
    vector<string> m_vNm_sigIRADcyBr;
    vector< vector<int> > m_vVPid_sigIncOrIRACascDcyBr;
    vector< vector<int> > m_vVMidx_sigIncOrIRACascDcyBr;
    vector<string> m_vNm_sigIncOrIRACascDcyBr;
    bool m_optIdxAndMidxOfSigDcyBrInSigIncOrIRACascDcyBr;

    bool m_ccSwitch;
    string m_anaTasksForSigIds;
    bool m_sortSigsInTopoMapsRltdToSigIds;
    bool m_iStPsSwitch;

    string m_comNmOfOptFls;
    bool m_cmpltHVLines;
    bool m_centDcyObjs;
    bool m_oneOptRootFlByOneIptRootFl;
    unsigned long m_nEtrMaxInASngOptRootFl;
    bool m_useArrayTBrsOpt;
    bool m_rmIptTBrs;
    bool m_convtMSIMSDIntoAOI;
    vector<string> m_othTtrNms;
    bool m_supprOptRootFls;
    bool m_flatArrayBrsLocally;
    bool m_vbsLevStdOut;

    vector<int> m_vIdCcPid;
    vector<int> m_vIdICcPid;
    vector<int> m_vIddCcPid;
    vector<int> m_vIddICcPid;
    vector< list<int> > m_vIgnoreFDcyBr, m_vCcIgnoreFDcyBr;
    vector<int> m_vICcIgnoreFDcyBr;

    vector< vector< list<int> > > m_vDcyTr, m_vCcDcyTr;
    vector<int> m_vIDcyTr, m_vICcDcyTr;
    vector<int> m_vNDcyTr, m_vNCcDcyTr;
    unordered_map<string,int> m_uomDcyTr, m_uomCcDcyTr;
    vector< list<int> > m_vDcyIFSts, m_vCcDcyIFSts;
    vector<int> m_vIDcyIFSts, m_vICcDcyIFSts;
    vector<int> m_vNDcyIFSts, m_vNCcDcyIFSts;
    unordered_map<string,int> m_uomDcyIFSts, m_uomCcDcyIFSts;
    map<int,int> m_iDcyTrIDcyIFStsMap, m_iDcyTrICcDcyIFStsMap;
    vector<int> m_vPid_ccCompDcyBrP;
    vector<int> m_vICcCompDcyBrP;
    // Pay attention to that m_vVDcyBrCcP, m_vVIDcyBrCcP and m_vVNDcyBrCcP equate to m_vVCcDcyBrP, m_vVICcDcyBrP and m_vVNCcDcyBrP for self-charge-conjugate particles.
    vector< vector< list<int> > > m_vVDcyBrP, m_vVDcyBrCcP;
    vector< vector<int> > m_vVIDcyBrP, m_vVIDcyBrCcP;
    vector< vector<int> > m_vVNDcyBrP, m_vVNDcyBrCcP;
    vector<int> m_vPid_ccCompCascDcyBrP;
    vector<int> m_vICcCompCascDcyBrP;
    // Pay attention to that m_vVCascDcyBrCcP, m_vVICascDcyBrCcP and m_vVNCascDcyBrCcP equate to m_vVCcCascDcyBrP, m_vVICcCascDcyBrP and m_vVNCcCascDcyBrP for self-charge-conjugate particles.
    vector< vector< vector< list<int> > > > m_vVCascDcyBrP, m_vVCascDcyBrCcP;
    vector< vector<int> > m_vVICascDcyBrP, m_vVICascDcyBrCcP;
    vector< vector<int> > m_vVNCascDcyBrP, m_vVNCascDcyBrCcP;
    vector< unordered_map<string,int> > m_vUomCascDcyBrP, m_vUomCascDcyBrCcP;
    vector<int> m_vPid_ccCompDcyFStP;
    vector<int> m_vICcCompDcyFStP;
    // Pay attention to that m_vVDcyFStCcP, m_vVIDcyFStCcP and m_vVNDcyFStCcP equate to m_vVCcDcyFStP, m_vVICcDcyFStP and m_vVNCcDcyFStP for self-charge-conjugate particles.
    vector< vector< list<int> > > m_vVDcyFStP, m_vVDcyFStCcP;
    vector< vector<int> > m_vVIDcyFStP, m_vVIDcyFStCcP;
    vector< vector<int> > m_vVNDcyFStP, m_vVNDcyFStCcP;
    vector< unordered_map<string,int> > m_vUomDcyFStP, m_vUomDcyFStCcP;
    vector<int> m_vPid_ccCompProdBrP;
    vector<int> m_vICcCompProdBrP;
    // Pay attention to that m_vVProdBrCcP, m_vVIProdBrCcP and m_vVNProdBrCcP equate to m_vVCcProdBrP, m_vVICcProdBrP and m_vVNCcProdBrP for self-charge-conjugate particles.
    vector< vector< list<int> > > m_vVProdBrP, m_vVProdBrCcP;
    vector< vector<int> > m_vVIProdBrP, m_vVIProdBrCcP;
    vector< vector<int> > m_vVNProdBrP, m_vVNProdBrCcP;
    vector<int> m_vPid_ccCompMP;
    vector<int> m_vICcCompMP;
    // Pay attention to that m_vVMCcP, m_vVIMCcP and m_vVNMCcP equate to m_vVCcMP, m_vVICcMP and m_vVNCcMP for self-charge-conjugate particles.
    vector< vector<int> > m_vVMpidP, m_vVMpidCcP;
    vector< vector<int> > m_vVIMP, m_vVIMCcP;
    vector< vector<int> > m_vVNMP, m_vVNMCcP;
    vector< list<int> > m_vCompIncDcyBr,m_vCompCcIncDcyBr;
    vector<int> m_vICcCompIncDcyBr;
    // Pay attention to that m_vVDcyBrCcIncDcyBr, m_vVIDcyBrCcIncDcyBr and m_vVNDcyBrCcIncDcyBr equate to m_vVCcDcyBrIncDcyBr, m_vVICcDcyBrIncDcyBr and m_vVNCcDcyBrIncDcyBr for self-charge-conjugate inclusive decays.
    vector< vector< list<int> > > m_vVDcyBrIncDcyBr, m_vVDcyBrCcIncDcyBr;
    vector< vector<int> > m_vVIDcyBrIncDcyBr, m_vVIDcyBrCcIncDcyBr;
    vector< vector<int> > m_vVNDcyBrIncDcyBr, m_vVNDcyBrCcIncDcyBr;
    vector< list<int> > m_vCompIRADcyBr,m_vCompCcIRADcyBr;
    vector<int> m_vICcCompIRADcyBr;
    // Pay attention to that m_vVDcyBrCcIRADcyBr, m_vVIDcyBrCcIRADcyBr and m_vVNDcyBrCcIRADcyBr equate to m_vVCcDcyBrIRADcyBr, m_vVICcDcyBrIRADcyBr and m_vVNCcDcyBrIRADcyBr for self-charge-conjugate inclusive decays.
    vector< vector< vector< list<int> > > > m_vVDcyBrIRADcyBr, m_vVDcyBrCcIRADcyBr;
    vector< vector<int> > m_vVIDcyBrIRADcyBr, m_vVIDcyBrCcIRADcyBr;
    vector< vector<int> > m_vVNDcyBrIRADcyBr, m_vVNDcyBrCcIRADcyBr;

    vector< vector< list<int> > > m_vSigDcyTr, m_vCcSigDcyTr;
    vector<int> m_vISigDcyTr, m_vICcSigDcyTr;
    vector<int> m_vNSigDcyTr, m_vNCcSigDcyTr;
    vector< list<int> > m_vSigDcyIFSts_tr, m_vCcSigDcyIFSts_tr;
    vector<int> m_vISigDcyIFSts_tr, m_vICcSigDcyIFSts_tr;
    vector<int> m_vNSigDcyIFSts_tr, m_vNCcSigDcyIFSts_tr;
    map<int,int> m_iSigDcyTrISigDcyIFSts_trMap, m_iSigDcyTrICcSigDcyIFSts_trMap;
    vector< list<int> > m_vSigDcyIFSts, m_vCcSigDcyIFSts;
    vector<int> m_vISigDcyIFSts, m_vICcSigDcyIFSts;
    vector<int> m_vNSigDcyIFSts, m_vNCcSigDcyIFSts;
    map<int,int> m_iSigDcyTrIDcyTrMap, m_iSigDcyTrICcDcyTrMap;
    map<int,int> m_iSigDcyIFSts_trIDcyIFStsMap, m_iSigDcyIFSts_trICcDcyIFStsMap;
    map<int,int> m_iSigDcyIFStsIDcyIFStsMap, m_iSigDcyIFStsICcDcyIFStsMap;
    vector<int> m_vPid_ccSigP;
    vector<int> m_vISigP, m_vICcSigP;              
    vector<int> m_vNSigP, m_vNCcSigP;
    vector< list<int> > m_vSigDcyBr, m_vCcSigDcyBr;
    vector<int> m_vISigDcyBr, m_vICcSigDcyBr;
    vector<int> m_vNSigDcyBr, m_vNCcSigDcyBr;
    vector< list<int> > m_vSigIncDcyBr, m_vCcSigIncDcyBr;
    vector<int> m_vISigIncDcyBr, m_vICcSigIncDcyBr;
    vector<int> m_vNSigIncDcyBr, m_vNCcSigIncDcyBr;
    vector< vector< list<int> > > m_vSigCascDcyBr, m_vCcSigCascDcyBr;
    vector< vector<int> > m_vVSigCascDcyBrIdxOfHead, m_vVCcSigCascDcyBrIdxOfHead;
    vector< vector<int> > m_vVSigCascDcyBrMidxOfHead, m_vVCcSigCascDcyBrMidxOfHead;
    vector<int> m_vISigCascDcyBr, m_vICcSigCascDcyBr;
    vector<int> m_vNSigCascDcyBr, m_vNCcSigCascDcyBr;
    vector< vector< list<int> > > m_vSigIncCascDcyBr, m_vCcSigIncCascDcyBr;
    vector< vector<int> > m_vVSigIncCascDcyBrIdxOfHead, m_vVCcSigIncCascDcyBrIdxOfHead;
    vector< vector<int> > m_vVSigIncCascDcyBrMidxOfHead, m_vVCcSigIncCascDcyBrMidxOfHead;
    vector< vector<int> > m_vVIIncSigIncCascDcyBr;
    vector<int> m_vISigIncCascDcyBr, m_vICcSigIncCascDcyBr;
    vector<int> m_vNSigIncCascDcyBr, m_vNCcSigIncCascDcyBr;
    vector< list<int> > m_vSigIRADcyBr, m_vCcSigIRADcyBr;
    vector<int> m_vISigIRADcyBr, m_vICcSigIRADcyBr;
    vector<int> m_vNSigIRADcyBr, m_vNCcSigIRADcyBr;
    vector< vector< list<int> > > m_vSigIncOrIRACascDcyBr, m_vCcSigIncOrIRACascDcyBr;
    vector< vector<int> > m_vVSigIncOrIRACascDcyBrIdxOfHead, m_vVCcSigIncOrIRACascDcyBrIdxOfHead;
    vector< vector<int> > m_vVSigIncOrIRACascDcyBrMidxOfHead, m_vVCcSigIncOrIRACascDcyBrMidxOfHead;
    vector< vector<int> > m_vVIIncSigIncOrIRACascDcyBr;
    vector< vector<int> > m_vVIIRASigIncOrIRACascDcyBr;
    vector<int> m_vISigIncOrIRACascDcyBr, m_vICcSigIncOrIRACascDcyBr;
    vector<int> m_vNSigIncOrIRACascDcyBr, m_vNCcSigIncOrIRACascDcyBr;

    int m_pidOfSISRGam;
    int m_pidOfSFSRGam;
    int m_pidOfSISRGamUser;
    int m_pidOfSFSRGamUser;
    int m_pidOfGISRGam;
    int m_pidOfGFSRGam;
    int m_pidOfISt;
    int m_pidOfISt1;
    int m_pidOfISt2;
    int m_pidOfGam;
    int m_pidOfPi0;
    int m_pidOfE;
    int m_pidOfMu;
    int m_pidOfPi;
    int m_pidOfK;
    int m_pidOfP;
    int m_pidOfAnything;
    int m_pidOfIRAFlag;
  public:
    topoana()
    {
      m_pkgPath="/workfs/bes/zhouxy/topoana-02-08-03/";
      m_verNum="v2.8.3";
      m_cardFlNm0=m_pkgPath+"share/underlying_topoana.card";

      m_nmsOfIptRootFls.clear();
      m_tbrNmOfNps="nMCGen";
      m_tbrNmOfPid="MCGenPDG";
      m_tbrNmOfMidx="MCGenMothIndex";
      m_nMinTbrOfPidMidx=9999;
      m_avoidOverCounting=false;
      m_tbrNmOfIcandi="__candidate__";
      m_tbrNmOfRidx="MCGenRawIndex";
      m_useRidx=false;
      m_strgTpOfRawIptTopoDat="AOI";
      m_fixMidxBESIII=false;
      m_nEtrMax=ULONG_MAX; // ULONG_MAX=9223372036854775807 is the maximum unsigned long int number. 
      m_vCut.clear();
      m_cutMethod=false;
      m_hHdDcyBrsMax=ULONG_MAX;
      m_vIdPid.clear();
      m_vIddPid.clear();
      m_vIgnoreFDcyBr.clear();
      m_vCcIgnoreFDcyBr.clear();
      m_vICcIgnoreFDcyBr.clear();
      m_retainPi02GamGam=false;
      m_vVPid_ignoreFDcyBr.clear();
      m_ignoreISR="N";
      m_ignoreFSR="N";

      m_compAnaOfDcyTrs=false;
      m_nDcyTrsToBePrtdMax=ULONG_MAX;
      m_dcyIFStsUnderDcyTr=false;
      m_optIdxAndMidxOfDcyBrInDcyTr=false;
      m_compAnaOfDcyIFSts=false;
      m_nDcyIFStsToBePrtdMax=ULONG_MAX;

      m_vPid_compDcyBrP.clear();
      m_vNm_compDcyBrP.clear();
      m_vNDcyBrToBePrtdMax.clear();
      m_vNDcyBrP.clear();
      m_vTypeOfTagRec_compDcyBrP.clear();
      m_vTBrNmOfTagRec_compDcyBrP.clear();
      m_vTBrNmOfNRec_compDcyBrP.clear();
      m_vPid_compCascDcyBrP.clear();
      m_vNm_compCascDcyBrP.clear();
      m_vNCascDcyBrToBePrtdMax.clear();
      m_vHCascDcyBrMax.clear();
      m_vTypeOfTagRec_compCascDcyBrP.clear();
      m_vTBrNmOfTagRec_compCascDcyBrP.clear();
      m_vTBrNmOfNRec_compCascDcyBrP.clear();
      m_vOptIdxAndMidxOfDcyBrInCascDcyBrP.clear();
      m_vPid_compDcyFStP.clear();
      m_vNm_compDcyFStP.clear();
      m_vNDcyFStToBePrtdMax.clear();
      m_vNDcyFStP.clear();
      m_vTypeOfTagRec_compDcyFStP.clear();
      m_vTBrNmOfTagRec_compDcyFStP.clear();
      m_vTBrNmOfNRec_compDcyFStP.clear();
      m_vPid_compProdBrP.clear();
      m_vNm_compProdBrP.clear();
      m_vNProdBrToBePrtdMax.clear();
      m_vNProdBrP.clear();
      m_vTypeOfTagRec_compProdBrP.clear();
      m_vTBrNmOfTagRec_compProdBrP.clear();
      m_vTBrNmOfNRec_compProdBrP.clear();
      m_vPid_compMP.clear();
      m_vNm_compMP.clear();
      m_vNMToBePrtdMax.clear();
      m_vNMP.clear();
      m_vTypeOfTagRec_compMP.clear();
      m_vTBrNmOfTagRec_compMP.clear();
      m_vTBrNmOfNRec_compMP.clear();
      m_vVPid_compIncDcyBr.clear();
      m_vNm_compIncDcyBr.clear();
      m_vNExcCompsToBePrtdMax.clear();
      m_vOption_compIncDcyBr.clear();
      m_vVPid_compIRADcyBr.clear();
      m_vNm_compIRADcyBr.clear();
      m_vNIntStrusToBePrtdMax.clear();

      m_vVPid_sigDcyTr.clear();
      m_vVMidx_sigDcyTr.clear();
      m_vNm_sigDcyTr.clear();
      m_sigDcyIFStsUnderSigDcyTr=false;
      m_optIdxAndMidxOfSigDcyBrInSigDcyTr=false;
      m_sigDcyIFSts_tr=false;
      m_vVPid_sigDcyIFSts.clear();
      m_vNm_sigDcyIFSts.clear();
      m_vPid_sigP.clear();
      m_vNm_sigP.clear();
      m_vVPid_sigDcyBr.clear();
      m_vNm_sigDcyBr.clear();
      m_vVPid_sigIncDcyBr.clear();
      m_vNm_sigIncDcyBr.clear();
      m_vVPid_sigCascDcyBr.clear();
      m_vVMidx_sigCascDcyBr.clear();
      m_vNm_sigCascDcyBr.clear();
      m_optIdxAndMidxOfSigDcyBrInSigCascDcyBr=false;
      m_vVPid_sigIncCascDcyBr.clear();
      m_vVMidx_sigIncCascDcyBr.clear();
      m_vNm_sigIncCascDcyBr.clear();
      m_optIdxAndMidxOfSigDcyBrInSigIncCascDcyBr=false;
      m_vVPid_sigIRADcyBr.clear();
      m_vNm_sigIRADcyBr.clear();
      m_vVPid_sigIncOrIRACascDcyBr.clear();
      m_vVMidx_sigIncOrIRACascDcyBr.clear();
      m_vNm_sigIncOrIRACascDcyBr.clear();
      m_optIdxAndMidxOfSigDcyBrInSigIncOrIRACascDcyBr=false;

      m_ccSwitch=false;
      m_anaTasksForSigIds="TC";
      m_sortSigsInTopoMapsRltdToSigIds=false;
      m_iStPsSwitch=false;

      m_cmpltHVLines=false;
      m_centDcyObjs=false;
      m_oneOptRootFlByOneIptRootFl=false;
      m_nEtrMaxInASngOptRootFl=ULONG_MAX;
      m_useArrayTBrsOpt=false;
      m_rmIptTBrs=false;
      m_convtMSIMSDIntoAOI=false;
      m_othTtrNms.clear();
      m_supprOptRootFls=false;
      m_flatArrayBrsLocally=false;
      m_vbsLevStdOut=false;

      m_pidOfSISRGam=222222222;
      m_pidOfSFSRGam=-22;
      m_pidOfSISRGamUser=m_pidOfSISRGam;
      m_pidOfSFSRGamUser=m_pidOfSFSRGam;
      m_pidOfGISRGam=22222222;
      m_pidOfGFSRGam=-22222222;
      m_pidOfISt=99999999;
      m_pidOfISt1=11;
      m_pidOfISt2=-11;
      m_pidOfGam=22;
      m_pidOfPi0=111;
      m_pidOfE=11;
      m_pidOfMu=13;
      m_pidOfPi=211;
      m_pidOfK=321;
      m_pidOfP=2212;
      m_pidOfAnything=-99999999;
      m_pidOfIRAFlag=100000000;
    }
    ~topoana(){}
    string         getCardFlNm0() {return m_cardFlNm0;};
    void           setCardFlNmAndDftComNmOfOptFls(string cardFlNm);
    string         getCardFlNm() {return m_cardFlNm;};
    void           clearNmsOfIptRootFls() {m_nmsOfIptRootFls.clear();};
    void           pushBackNmOfIptRootFl(string nmOfIptRootFl) {m_nmsOfIptRootFls.push_back(nmOfIptRootFl);};
    void           resetTtrNm(string ttrNm) {m_ttrNm=ttrNm;};
    void	   resetComNmOfOptFls(string comNmOfOptFls) {m_comNmOfOptFls=comNmOfOptFls;};
    void           resetNEtrMax(unsigned long nEtrMax) {m_nEtrMax=nEtrMax;};
    string &       trim(string & line);
    void           makeMapsOnPdata();
    void	   makeNNmMap();
    int 	   getPidFromTxtPnm(string pnm);
    void           writeErrInfOnPid3PchrgMap(int pid);
    void           writePnmFromPid(ostream & out,string pnmType,int pid);
    void           reviseIptQts(double & Npsd, double Pidd[], double Midxd[], int & Nps, int Pid[], int Midx[], int Ridx[]);
    void           sortByPidAndPchrg(vector<int> &via,vector<int> &vib,vector<int> &vic,vector<int> &vid);
    void           sortBySzPidAndPchrg(vector< vector<int> > &vVia,vector< vector<int> > &vVib,vector< vector<int> >&vVic,vector< vector<int> > &vVid);
    bool           cmprBySzPidAndPchrg(vector<int> & via, vector<int> & vib);
    bool	   isIgnoreFDcyBr(int mPid, vector<int> vPidYngSbst, vector< list<int> > vIgnoreFDcyBr);
    void           recurHigherHierExchOrd(vector<int> & vNewIdx, vector<int> & vOldIdx, vector<int> & vPid, vector<int> & vMidx, vector<int> * vIdxOrg=0);
    void           recurHighHierExchOrd(vector<int> & vIdxYngi, vector<int> & vIdxYngj, vector<int> & vPid, vector<int> & vMidx, vector<int> * vIdxOrg=0);
    void           sortPs(vector<int> & vPid, vector<int> & vMidx, vector<int> * vIdxOrg=0);
    int		   getCcPid(int pid);
    void           getDcyTr(vector<int> vPid, vector<int> vMidx, vector< list<int> > & dcyTr, vector<int> * vIdxOfHead=0, vector<int> * vMidxOfHead=0, vector<int> * vIIncIncOrIRACascDcyBr=0, vector<int> * vIIRAIncOrIRACascDcyBr=0);
    void           sortByPidAndPchrg(list<int> &lia);
    void           getDcyIFSts(vector<int> & vPid,vector<int> & vMidx,list<int> & dcyIFSts);
    unsigned int   countIRADcyBr(vector<int> & vPid, vector<int> & vMidx, list<int> IRADcyBr, bool areHeadsRequiredToBeMatched=false,vector< vector< list<int> > > * vDcyBrIRADcyBr=0,vector< list<int> > * vIRADcyBrWithRGam=0,string option="");
    void           readOpenCurly(ifstream & fin, string & line, string prompt);
    void           read1stLineOrCloseCurly(ifstream & fin, string & line, bool essential, string errinforprompt);
    void           readExtraLinesOrCloseCurly(ifstream & fin, string & line, string prompt);
    void           readCloseCurly(ifstream & fin, string & line, string prompt);
    void           readNumItem(ifstream & fin, string & line, string prompt, unsigned long & ulvar);
    void           readNumItem(ifstream & fin, string & line, string prompt, int & ivar, int ivarDft=INT_MAX);
    void 	   readVPItem(ifstream & fin, string & line, string prompt, vector<int> & vPid);
    void 	   readYNItem(ifstream & fin, string & line, string prompt, bool & bvar);
    int 	   countSubstr(const std::string & str, const std::string & substr);
    void	   parseIptStrIntoRecStrs(string line, string prompt, string str, string & typeOfTagRec, string & tBrNmOfTagRec, string & tBrNmOfNRec);
    void           readP(string & line, string prompt, vector<int> & vPid, vector<string> & vNm, vector<unsigned long> * vNMax, vector<unsigned long> * vHMax, vector<string> * vTypeOfTagRec, vector<string> * vTBrNmOfTagRec, vector<string> * vTBrNmOfNRec, vector<bool> * vOpt);
    void           readPItem(ifstream & fin, string & line, string prompt, vector<int> & vPid, vector<string> & vNm, vector<unsigned long> * vNMax=0, vector<unsigned long> * vHMax=0, vector<string> * vTypeOfTagRec=0, vector<string> * vTBrNmOfTagRec=0, vector<string> * vTBrNmOfNRec=0, vector<bool> * vOpt=0);
    void           readSmpDcyOld(string & line, string prompt, vector<int> & vPid, vector< vector<int> > & vVPid, vector<string> * vNm, vector<unsigned long> * vNMax);
    void           readSmpDcyNew(string & line, string prompt, vector< vector<int> > & vVPid, vector<string> * vNm, vector<unsigned long> * vNMax, vector<string> * vOption);
    void           readSmpDcyItem(ifstream & fin, string & line, string prompt, vector< vector<int> > & vVPid, vector<string> * vNm=0, vector<unsigned long> * vNMax=0, vector<string> * vOption=0);
    void	   getVPidandVMidx(vector< vector<int> > & vDcyBr, vector<int> & vIMDcyBr, vector<int> & vPid, vector<int> & vMidx);
    void           readCmplxDcyOld(string & line, vector<int> & vPid, vector< vector<int> > & vVPid, vector<int> & vMidx, vector< vector<int> > & vVMidx, vector<string> & vNm, bool useAsterisk=false);
    void           readCmplxDcyNew(string & line, string prompt, vector< vector<int> > & vDcyBr, vector<int> & vIMDcyBr, vector<int> & vPid, vector<int> & vMidx, vector<string> & vNm, bool & bvar1, bool & bvar2, bool useAsterisk=false);
    void           readCmplxDcyItem(ifstream & fin, string & line, string prompt, vector< vector<int> > & vVPid, vector< vector<int> > & vVMidx, vector<string> & vNm, bool & bvar1, bool & bvar2, bool useAsterisk=false);
    void           readCard(string cardFlNm);
    bool           useRidx(vector<string> vTypeOfTagRec);
    void	   findBranch(string nmOfIptRootFl, string ttrNm, TTree * tr, vector<string> vTypeOfTagRec, vector<string> vTBrNmOfTagRec, vector<string> vTBrNmOfNRec, bool & allIptsAreOK, string prompt);
    void	   checkInput();
    void           setBranchAddress(vector<string> vTypeOfTagRec, vector<string> vTBrNmOfTagRec, vector<string> vTBrNmOfNRec, TChain * chn, double * Tagrecsd, int * Tagrecsi, int Tagreca[][20], int * Nrec);
    void 	   createBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, int * aICc, TTree * tr, unsigned int nMax, int * nq, int * iq, int * iCcq, int * nCcq, int * iqCc, int * nAllq);
    void           createBrs(unsigned int size, string NM, vector<string> vNm, int * aICc, TTree * tr, int * nq, int * nCcq, int * nAllq);
    void           cpBrVals(vector<string> vTypeOfTagRec1, vector<string> vTBrNmOfTagRec1, vector<string> vTBrNmOfNRec1, double * Tagrecsd1, int * Tagrecsi1, int Tagreca1[][20], int * Nrec1, string prompt1, vector<string> vTypeOfTagRec2, vector<string> vTBrNmOfTagRec2, vector<string> vTBrNmOfNRec2, double * Tagrecsd2, int * Tagrecsi2, int Tagreca2[][20], int * Nrec2, string prompt2);
    void	   getVCascDcyBrP(vector< vector< list<int> > > & vCascDcyBrP, vector<int> & vIdxOfHead_CascDcyBrP, vector< list<int> > & dcyTr, vector<int> & vIdxOfHead, vector<int> & vMidxOfHead, int pid, unsigned long hCascDcyBrMax=ULONG_MAX);
    void           getVDcyFStP(vector< list<int> > & vDcyFStP, vector<int> & vIdxOfHead_DcyFStP, vector<int> & vPid, vector<int> & vMidx, int pid, unsigned long nDcyFSt=ULONG_MAX);
    unsigned int   countIncLiaInVlib(list<int> & lia, vector< list<int> > & Vlib);
    bool	   isLiaMatchedWithLib(list<int> & lia, list<int> & lib, string option="");
    unsigned int   countCascDcyBrInDcyTr(vector< list<int> > & cascDcyBr, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2);
    unsigned int   countIncCascDcyBrInDcyTr(vector<int> vIIncIncCascDcyBr, vector< list<int> > & incCascDcyBr, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2);
    void           getSubsetsOfVPidandVMidxFromAP(vector<int> & vPid,vector<int> & vMidx, int idx);
    bool	   isPaADescendantOfPb(vector<int> vMidx, int idxA, int idxB);
    unsigned int   countIncOrIRACascDcyBrInDcyTr(vector<int> vIIncIncOrIRACascDcyBr, vector<int> vIIRAIncOrIRACascDcyBr, vector< list<int> > & incOrIRACascDcyBr, vector<int> vIdxOfHead1, vector<int> vMidxOfHead1, vector< list<int> > & dcyTr, vector<int> vIdxOfHead2, vector<int> vMidxOfHead2, vector<int> vPid, vector<int> vMidx);
    // The following five functions will be used in the flatArrayBrs functions.
    void 	   disableBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, vector<int> vICc, TTree * tr);
    void           activateBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, vector<int> vICc, TTree * tr, unsigned int * nMax, unsigned int & nMax_Max, unsigned int * nCcMax, unsigned int & nCcMax_Max);
    void           createBrs(unsigned int size, string NM1, string NM2, string NM3, string NM4, string NM5, vector<string> vNm, vector<int> vICc, TTree * tr_old, TTree * tr_new, unsigned int * nMax, unsigned int nMax_Max, unsigned int * nCcMax, unsigned int nCcMax_Max, int * nq, int * iq, int * iCcq, int * nCcq, int * iqCc);
    void           assignDftVals(unsigned int size, vector<int> vICc, unsigned int * nMax, unsigned int nMax_Max, unsigned int * nCcMax, unsigned int nCcMax_Max, int * nq, int * iq, int * iCcq, int * nCcq, int * iqCc, bool isForMoth=false);
    void           getMaxAndMax_Max(unsigned int size, string NM, vector<string> vNm, vector<int> vICc, TChain * chn, unsigned int * nMax, unsigned int & nMax_Max, unsigned int * nCcMax, unsigned int & nCcMax_Max);
    void           flatArrayBrs(string nmOfOptRootFl, unsigned int * nPIMax_DcyBr, unsigned int * nCcPIMax_DcyBr, unsigned int nPIMax_Max_DcyBr, unsigned int nCcPIMax_Max_DcyBr, unsigned int * nPIMax_CascDcyBr, unsigned int * nCcPIMax_CascDcyBr, unsigned int nPIMax_Max_CascDcyBr, unsigned int nCcPIMax_Max_CascDcyBr, unsigned int * nPIMax_DcyFSt, unsigned int * nCcPIMax_DcyFSt, unsigned int nPIMax_Max_DcyFSt, unsigned int nCcPIMax_Max_DcyFSt, unsigned int * nPIMax_ProdBr, unsigned int * nCcPIMax_ProdBr, unsigned int nPIMax_Max_ProdBr, unsigned int nCcPIMax_Max_ProdBr, unsigned int * nPIMax_Moth, unsigned int * nCcPIMax_Moth, unsigned int nPIMax_Max_Moth, unsigned int nCcPIMax_Max_Moth, unsigned int * nIncDcyBrIMax, unsigned int * nCcIncDcyBrIMax, unsigned int nIncDcyBrIMaxMax, unsigned int nCcIncDcyBrIMaxMax, unsigned int * nIRADcyBrIMax, unsigned int * nCcIRADcyBrIMax, unsigned int nIRADcyBrIMaxMax, unsigned int nCcIRADcyBrIMaxMax);
    void           flatArrayBrs(vector<string> nmOfOptRootFl);
    void           rmIptBrs(string nmOfOptRootFl);
    template < typename T >
    void           sortBySumOf1stAnd2ndFromLrgToSml(vector<int> & via1, vector<int> & via2, vector<T> & vib1, vector<T> & vib2, vector<int> & vic1, vector<int> & vic2, vector< vector<int> > * vVid1=0, vector< vector<int> > * vVid2=0, vector< vector<int> > * vVie1=0, vector< vector<int> > * vVie2=0);
    template < typename T >
    void           sortBySumOf1stAnd2ndFromLrgToSml_new(unsigned long nMax, vector<int> & via1, vector<int> & via2, vector<T> & vib1, vector<T> & vib2, vector<int> & vic1, vector<int> & vic2, vector< vector<int> > * vVid1=0, vector< vector<int> > * vVid2=0, vector< vector<int> > * vVie1=0, vector< vector<int> > * vVie2=0);
    template < typename T >
    void           sortBy1stFromLrgToSml(vector<int> & via, vector< T > & vib, vector<int> & vic, vector< vector<int> > * vVid=0, vector< vector<int> > * vVie=0);
    template < typename T >
    void           sortBy1stFromLrgToSml_new(unsigned long nMax, vector<int> & via, vector< T > & vib, vector<int> & vic, vector< vector<int> > * vVid=0, vector< vector<int> > * vVie=0);
    template < typename T >
    void           countAndSort(TChain * chn, const unsigned int size, string NM, vector<string> vNm, vector<int> vN, vector<int> vNCc, vector<T> v, vector<T> vCc, vector<int> vI, vector<int> vICc, vector< vector<int> > * vVIdxOfHead=0, vector< vector<int> > * vVCcIdxOfHead=0, vector< vector<int> > * vVMidxOfHead=0, vector< vector<int> > * vVCcMidxOfHead=0);
    void	   getStrFromVli(vector< list<int> > & dcyTr, string & strDcyTr);
    void           getStrFromLi(list<int> & dcyIFSts, string & strDcyIFSts);
    bool 	   isTagMatched(string typeOfTagrec, int Tagrecs, int * Tagreca, int Nrec, int Tagtruth);
    void           getRslt();
    void           writeRsltIntoTxtFl();
    void           getVIMDcyBr(vector< list<int> > & vDcyBr, vector<int> & vIMDcyBr);
    void           writeRsltIntoTexFl();
    void           getPdfFlFromTexFl();
    void           writeInforOnRslt();
};

// End the declaration of the topoana class

// Pay attention to that all of the template statements above and below are indispensable.

// Begin the definitions of the template member functions of the topoana class

#include <iostream>
#include <cstdlib>
#include "TBranch.h"

template < typename T >
void topoana::sortBy1stFromLrgToSml(vector<int> & via, vector<T> & vib, vector<int> & vic, vector< vector<int> > * vVid, vector< vector<int> > * vVie)
{
  if(via.size()!=vib.size()||vib.size()!=vic.size()||((vVid!=0&&vVie!=0)&&(vic.size()!=(*vVid).size()||(*vVid).size()!=(*vVie).size())))
    {
      if(vVid!=0&&vVie!=0) cerr<<"Error: The five vectors have different sizes!"<<endl;
      else cerr<<"Error: The three vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<vib.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vic.size()<<"."<<endl;
      if(vVid!=0&&vVie!=0)
        {
          cerr<<"Infor: The size of the fourth vector is "<<(*vVid).size()<<"."<<endl;
          cerr<<"Infor: The size of the fifth vector is "<<(*vVie).size()<<"."<<endl;
        }
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }
   
  if(via.size()==0)
    {
      if(vVid!=0&&vVie!=0) cerr<<"Infor: The sizes of the five vectors are zero!"<<endl<<endl;
      else cerr<<"Infor: The sizes of the three vectors are zero!"<<endl<<endl;
      return;
    }

  int iaTmp; T ibTmp; int icTmp; vector<int> vidTmp,vieTmp;
  for(unsigned int i=0;i<(via.size()-1);i++)
    for(unsigned int j=i+1;j<via.size();j++)
      if(via[i]<via[j])
        {
          iaTmp=via[i];
          via[i]=via[j];
          via[j]=iaTmp;
          ibTmp=vib[i];
          vib[i]=vib[j];
          vib[j]=ibTmp;
          icTmp=vic[i];
          vic[i]=vic[j];
          vic[j]=icTmp;
          if(vVid!=0&&vVie!=0)
            {
              vidTmp=(*vVid)[i];
              (*vVid)[i]=(*vVid)[j];
              (*vVid)[j]=vidTmp;
              vieTmp=(*vVie)[i];
              (*vVie)[i]=(*vVie)[j];
              (*vVie)[j]=vieTmp;
            }
        } 
}

template < typename T >
void topoana::sortBy1stFromLrgToSml_new(unsigned long nMax, vector<int> & via, vector<T> & vib, vector<int> & vic, vector< vector<int> > * vVid, vector< vector<int> > * vVie)
{
  if(via.size()!=vib.size()||vib.size()!=vic.size()||((vVid!=0&&vVie!=0)&&(vic.size()!=(*vVid).size()||(*vVid).size()!=(*vVie).size())))
    {
      if(vVid!=0&&vVie!=0) cerr<<"Error: The five vectors have different sizes!"<<endl;
      else cerr<<"Error: The three vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<vib.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vic.size()<<"."<<endl;
      if(vVid!=0&&vVie!=0)
        {
          cerr<<"Infor: The size of the fourth vector is "<<(*vVid).size()<<"."<<endl;
          cerr<<"Infor: The size of the fifth vector is "<<(*vVie).size()<<"."<<endl;
        }
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(via.size()==0)
    {
      if(vVid!=0&&vVie!=0) cerr<<"Infor: The sizes of the five vectors are zero!"<<endl<<endl;
      else cerr<<"Infor: The sizes of the three vectors are zero!"<<endl<<endl;
      return;
    }

  vector<unsigned int> vIdxTmp; vector<int> viaTmp; vector<T> vibTmp; vector<int> vicTmp; vector< vector<int> > vVidTmp; vector< vector<int> > vVieTmp;

  for(unsigned int i=0;i<(via.size()<nMax?via.size():nMax);i++)
    {
      vIdxTmp.push_back(i);
      viaTmp.push_back(via[i]);
      vibTmp.push_back(vib[i]);
      vicTmp.push_back(vic[i]);
    }

  unsigned int idxTmp; int iaTmp; T ibTmp; int icTmp;
  for(unsigned int i=0;i<(vIdxTmp.size()-1);i++)
    for(unsigned int j=i+1;j<vIdxTmp.size();j++)
      if(viaTmp[i]<viaTmp[j])
        {
          idxTmp=vIdxTmp[i];
          vIdxTmp[i]=vIdxTmp[j];
          vIdxTmp[j]=idxTmp;
          iaTmp=viaTmp[i];
          viaTmp[i]=viaTmp[j];
          viaTmp[j]=iaTmp;
          ibTmp=vibTmp[i];
          vibTmp[i]=vibTmp[j];
          vibTmp[j]=ibTmp;
          icTmp=vicTmp[i];
          vicTmp[i]=vicTmp[j];
          vicTmp[j]=icTmp;
        }

  if(via.size()>nMax)
    {
      bool isTop;
      for(unsigned int i=nMax;i<via.size();i++)
        {
          isTop=false;
          for(unsigned int j=0;j<nMax;j++)
            {
              if(via[i]>viaTmp[j])
                {
                  viaTmp.push_back(viaTmp[nMax-1]);
                  vibTmp.push_back(vibTmp[nMax-1]);
                  vicTmp.push_back(vicTmp[nMax-1]);
                  // Considering k is an unsigned integer, please do not omit "&&k!=UINT_MAX" in the condition. Otherwise, the program is very likely to break due to array index overflow.
                  for(unsigned int k=nMax-2;k>=j&&k!=UINT_MAX;k--)
                    {
                      vIdxTmp[k+1]=vIdxTmp[k];
                      viaTmp[k+1]=viaTmp[k];
                      vibTmp[k+1]=vibTmp[k];
                      vicTmp[k+1]=vicTmp[k];
                    }
                  vIdxTmp[j]=i;
                  viaTmp[j]=via[i];
                  vibTmp[j]=vib[i];
                  vicTmp[j]=vic[i];
                  isTop=true;
                  break;
                }
            }
          if(isTop==false)
            {
              viaTmp.push_back(via[i]);
              vibTmp.push_back(vib[i]);
              vicTmp.push_back(vic[i]);
            }
        }
    }

  for(unsigned int i=0;i<vIdxTmp.size();i++)
    {
      // If we handle b and c like d and e, there will be a problem related to the simultaneous component analysis of decay trees and decay initial-final states, with a specified maximum number of the decay initial-final states to be printed. So, the function could not be further simplified in this aspect.
      if(vVid!=0&&vVie!=0)
        {
          vVidTmp.push_back((*vVid)[vIdxTmp[i]]);
          vVieTmp.push_back((*vVie)[vIdxTmp[i]]);
        }
    }

  via=viaTmp;
  vib=vibTmp;
  vic=vicTmp;
  if(vVid!=0&&vVie!=0)
    {
      for(unsigned int i=0;i<vIdxTmp.size();i++)
        {
          (*vVid)[i]=vVidTmp[i];
          (*vVie)[i]=vVieTmp[i];
        }
    }
}

template < typename T >
void topoana::sortBySumOf1stAnd2ndFromLrgToSml(vector<int> & via1, vector<int> & via2, vector<T> & vib1, vector<T> & vib2, vector<int> & vic1, vector<int> & vic2, vector< vector<int> > * vVid1, vector< vector<int> > * vVid2, vector< vector<int> > * vVie1, vector< vector<int> > * vVie2)
{
  if(via1.size()!=via2.size()||via2.size()!=vib1.size()||vib1.size()!=vib2.size()||vib2.size()!=vic1.size()||vic1.size()!=vic2.size()||((vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0)&&(vic2.size()!=(*vVid1).size()||(*vVid1).size()!=(*vVid2).size()||(*vVid2).size()!=(*vVie1).size()||(*vVie1).size()!=(*vVie2).size())))
    {
      if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0) cerr<<"Error: The ten vectors have different sizes!"<<endl;
      else cerr<<"Error: The six vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via1.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<via2.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vib1.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vib2.size()<<"."<<endl;
      cerr<<"Infor: The size of the fifth vector is "<<vic1.size()<<"."<<endl;
      cerr<<"Infor: The size of the sixth vector is "<<vic2.size()<<"."<<endl;
      if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0)
        {
          cerr<<"Infor: The size of the seventh vector is "<<(*vVid1).size()<<"."<<endl;
          cerr<<"Infor: The size of the eighth vector is "<<(*vVid2).size()<<"."<<endl;
          cerr<<"Infor: The size of the ninth vector is "<<(*vVie1).size()<<"."<<endl;
          cerr<<"Infor: The size of the tenth vector is "<<(*vVie2).size()<<"."<<endl;
        }
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(via1.size()==0)
    {
      if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0) cerr<<"Infor: The sizes of the ten vectors are zero!"<<endl<<endl;
      else cerr<<"Infor: The sizes of the six vectors are zero!"<<endl<<endl;
      return;
    }

  int iaTmp1,iaTmp2; T ibTmp1,ibTmp2; int icTmp1,icTmp2; vector<int> vidTmp1,vidTmp2,vieTmp1,vieTmp2;
  for(unsigned int i=0;i<(via1.size()-1);i++)
    for(unsigned int j=i+1;j<via1.size();j++)
      if(via1[i]+via2[i]<via1[j]+via2[j])
        {
          iaTmp1=via1[i];
          via1[i]=via1[j];
          via1[j]=iaTmp1;
          iaTmp2=via2[i];
          via2[i]=via2[j];
          via2[j]=iaTmp2;
          ibTmp1=vib1[i];
          vib1[i]=vib1[j];
          vib1[j]=ibTmp1;
          ibTmp2=vib2[i];
          vib2[i]=vib2[j];
          vib2[j]=ibTmp2;
          icTmp1=vic1[i];
          vic1[i]=vic1[j];
          vic1[j]=icTmp1;
          icTmp2=vic2[i];
          vic2[i]=vic2[j];
          vic2[j]=icTmp2;
          if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0)
            {
              vidTmp1=(*vVid1)[i];
              (*vVid1)[i]=(*vVid1)[j];
              (*vVid1)[j]=vidTmp1;
              vidTmp2=(*vVid2)[i];
              (*vVid2)[i]=(*vVid2)[j];
              (*vVid2)[j]=vidTmp2;
              vieTmp1=(*vVie1)[i];
              (*vVie1)[i]=(*vVie1)[j];
              (*vVie1)[j]=vieTmp1;
              vieTmp2=(*vVie2)[i];
              (*vVie2)[i]=(*vVie2)[j];
              (*vVie2)[j]=vieTmp2;
            }
        }
}

template < typename T >
void topoana::sortBySumOf1stAnd2ndFromLrgToSml_new(unsigned long nMax, vector<int> & via1, vector<int> & via2, vector<T> & vib1, vector<T> & vib2, vector<int> & vic1, vector<int> & vic2, vector< vector<int> > * vVid1, vector< vector<int> > * vVid2, vector< vector<int> > * vVie1, vector< vector<int> > * vVie2)
{
  if(via1.size()!=via2.size()||via2.size()!=vib1.size()||vib1.size()!=vib2.size()||vib2.size()!=vic1.size()||vic1.size()!=vic2.size()||((vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0)&&(vic2.size()!=(*vVid1).size()||(*vVid1).size()!=(*vVid2).size()||(*vVid2).size()!=(*vVie1).size()||(*vVie1).size()!=(*vVie2).size())))
    {
      if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0) cerr<<"Error: The ten vectors have different sizes!"<<endl;
      else cerr<<"Error: The six vectors have different sizes!"<<endl;
      cerr<<"Infor: The size of the first vector is "<<via1.size()<<"."<<endl;
      cerr<<"Infor: The size of the second vector is "<<via2.size()<<"."<<endl;
      cerr<<"Infor: The size of the third vector is "<<vib1.size()<<"."<<endl;
      cerr<<"Infor: The size of the fourth vector is "<<vib2.size()<<"."<<endl;
      cerr<<"Infor: The size of the fifth vector is "<<vic1.size()<<"."<<endl;
      cerr<<"Infor: The size of the sixth vector is "<<vic2.size()<<"."<<endl;
      if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0)
        {
          cerr<<"Infor: The size of the seventh vector is "<<(*vVid1).size()<<"."<<endl;
          cerr<<"Infor: The size of the eighth vector is "<<(*vVid2).size()<<"."<<endl;
          cerr<<"Infor: The size of the ninth vector is "<<(*vVie1).size()<<"."<<endl;
          cerr<<"Infor: The size of the tenth vector is "<<(*vVie2).size()<<"."<<endl;
        }
      cerr<<"Infor: Please check them."<<endl;
      exit(-1);
    }

  if(via1.size()==0)
    {
      if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0) cerr<<"Infor: The sizes of the ten vectors are zero!"<<endl<<endl;
      else cerr<<"Infor: The sizes of the six vectors are zero!"<<endl<<endl;
      return;
    }

  vector<unsigned int> vIdxTmp; vector<int> via1Tmp, via2Tmp; vector<T> vib1Tmp, vib2Tmp; vector<int> vic1Tmp, vic2Tmp; vector< vector<int> > vVid1Tmp, vVid2Tmp; vector< vector<int> > vVie1Tmp, vVie2Tmp;

  for(unsigned int i=0;i<(via1.size()<nMax?via1.size():nMax);i++)
    {
      vIdxTmp.push_back(i);
      via1Tmp.push_back(via1[i]);
      via2Tmp.push_back(via2[i]);
      vib1Tmp.push_back(vib1[i]);
      vib2Tmp.push_back(vib2[i]);
      vic1Tmp.push_back(vic1[i]);
      vic2Tmp.push_back(vic2[i]);
    }

  unsigned int idxTmp; int ia1Tmp, ia2Tmp; T ib1Tmp, ib2Tmp; int ic1Tmp, ic2Tmp;
  for(unsigned int i=0;i<(vIdxTmp.size()-1);i++)
    for(unsigned int j=i+1;j<vIdxTmp.size();j++)
      if(via1Tmp[i]+via2Tmp[i]<via1Tmp[j]+via2Tmp[j])
        {
          idxTmp=vIdxTmp[i];
          vIdxTmp[i]=vIdxTmp[j];
          vIdxTmp[j]=idxTmp;
          ia1Tmp=via1Tmp[i];
          via1Tmp[i]=via1Tmp[j];
          via1Tmp[j]=ia1Tmp;
          ia2Tmp=via2Tmp[i];
          via2Tmp[i]=via2Tmp[j];
          via2Tmp[j]=ia2Tmp;
          ib1Tmp=vib1Tmp[i];
          vib1Tmp[i]=vib1Tmp[j];
          vib1Tmp[j]=ib1Tmp;
          ib2Tmp=vib2Tmp[i];
          vib2Tmp[i]=vib2Tmp[j];
          vib2Tmp[j]=ib2Tmp;
          ic1Tmp=vic1Tmp[i];
          vic1Tmp[i]=vic1Tmp[j];
          vic1Tmp[j]=ic1Tmp;
          ic2Tmp=vic2Tmp[i];
          vic2Tmp[i]=vic2Tmp[j];
          vic2Tmp[j]=ic2Tmp;
        }

  if(via1.size()>nMax)
    {
      bool isTop;
      for(unsigned int i=nMax;i<via1.size();i++)
        {
          isTop=false;
          for(unsigned int j=0;j<nMax;j++)
            {
              if(via1[i]+via2[i]>via1Tmp[j]+via2Tmp[j])
                {
                  via1Tmp.push_back(via1Tmp[nMax-1]);
                  via2Tmp.push_back(via2Tmp[nMax-1]);
                  vib1Tmp.push_back(vib1Tmp[nMax-1]);
                  vib2Tmp.push_back(vib2Tmp[nMax-1]);
                  vic1Tmp.push_back(vic1Tmp[nMax-1]);
                  vic2Tmp.push_back(vic2Tmp[nMax-1]);
                  // Considering k is an unsigned integer, please do not omit "&&k!=UINT_MAX" in the condition. Otherwise, the program is very likely to break due to array index overflow.
                  for(unsigned int k=nMax-2;k>=j&&k!=UINT_MAX;k--)
                    {
                      vIdxTmp[k+1]=vIdxTmp[k];
                      via1Tmp[k+1]=via1Tmp[k];
                      via2Tmp[k+1]=via2Tmp[k];
                      vib1Tmp[k+1]=vib1Tmp[k];
                      vib2Tmp[k+1]=vib2Tmp[k];
                      vic1Tmp[k+1]=vic1Tmp[k];
                      vic2Tmp[k+1]=vic2Tmp[k];
                    }
                  vIdxTmp[j]=i;
                  via1Tmp[j]=via1[i];
                  via2Tmp[j]=via2[i];
                  vib1Tmp[j]=vib1[i];
                  vib2Tmp[j]=vib2[i];
                  vic1Tmp[j]=vic1[i];
                  vic2Tmp[j]=vic2[i];
                  isTop=true;
                  break;
                }
            }
          if(isTop==false)
            {
              via1Tmp.push_back(via1[i]);
              via2Tmp.push_back(via2[i]);
              vib1Tmp.push_back(vib1[i]);
              vib2Tmp.push_back(vib2[i]);
              vic1Tmp.push_back(vic1[i]);
              vic2Tmp.push_back(vic2[i]);
            }
        }
    }

  for(unsigned int i=0;i<vIdxTmp.size();i++)
    {
      // If we handle b and c like d and e, there will be a problem related to the simultaneous component analysis of decay trees and decay initial-final states, with a specified maximum number of the decay initial-final states to be printed. So, the function could not be further simplified in this aspect.
      if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0)
        {
          vVid1Tmp.push_back((*vVid1)[vIdxTmp[i]]);
          vVid2Tmp.push_back((*vVid2)[vIdxTmp[i]]);
          vVie1Tmp.push_back((*vVie1)[vIdxTmp[i]]);
          vVie2Tmp.push_back((*vVie2)[vIdxTmp[i]]);
        }
    }

  via1=via1Tmp;
  via2=via2Tmp;
  vib1=vib1Tmp;
  vib2=vib2Tmp;
  vic1=vic1Tmp;
  vic2=vic2Tmp;
  if(vVid1!=0&&vVid2!=0&&vVie1!=0&&vVie2!=0)
    {
      for(unsigned int i=0;i<vIdxTmp.size();i++)
        {
          (*vVid1)[i]=vVid1Tmp[i];
          (*vVid2)[i]=vVid2Tmp[i];
          (*vVie1)[i]=vVie1Tmp[i];
          (*vVie2)[i]=vVie2Tmp[i];
        }
    }
}

template < typename T >
void topoana::countAndSort(TChain * chn, const unsigned int size, string NM, vector<string> vNm, vector<int> vN, vector<int> vNCc, vector<T> v, vector<T> vCc, vector<int> vI, vector<int> vICc, vector< vector<int> > * vVIdxOfHead, vector< vector<int> > * vVCcIdxOfHead, vector< vector<int> > * vVMidxOfHead, vector< vector<int> > * vVCcMidxOfHead)
{
  if(m_anaTasksForSigIds=="C")
    { 
      int nq[size],nCcq[size];
      char specifier[100];
      if(m_useArrayTBrsOpt==true)
        {
          sprintf(specifier, "n%s", NM.c_str()); 
          chn->SetBranchAddress(specifier, &nq);
          if(m_ccSwitch==true)
            {
              sprintf(specifier, "nCc%s", NM.c_str());
              chn->SetBranchAddress(specifier, &nCcq);
            }
        }
      else
        { 
          for(unsigned int i=0;i<size;i++)
            { 
              sprintf(specifier, "n%s_%s", NM.c_str(), vNm[i].c_str());
              chn->SetBranchAddress(specifier, &nq[i]);
              if(m_ccSwitch==true)
                { 
                  sprintf(specifier, "nCc%s_%s", NM.c_str(), vNm[i].c_str());
                  chn->SetBranchAddress(specifier, &nCcq[i]);
                }
            }
        }
      for(unsigned int i=0;i<chn->GetEntries();i++)
        { 
          chn->GetEntry(i);
          for(unsigned int j=0;j<size;j++)
            { 
              vN[j]=vN[j]+nq[j];
              if(m_ccSwitch==true) vNCc[j]=vNCc[j]+nCcq[j];
            }
        }
    }
  if(m_sortSigsInTopoMapsRltdToSigIds==true)
    {
      if(m_ccSwitch==true)
        {
          // if(vVIdxOfHead==0&&vVCcIdxOfHead==0&&vVMidxOfHead==0&&vVCcMidxOfHead==0) sortBySumOf1stAnd2ndFromLrgToSml(vN, vNCc, v, vCc, vI, vICc);
          // else sortBySumOf1stAnd2ndFromLrgToSml(vN, vNCc, v, vCc, vI, vICc, vVIdxOfHead, vVCcIdxOfHead, vVMidxOfHead, vVCcMidxOfHead);
          if(vVIdxOfHead==0&&vVCcIdxOfHead==0&&vVMidxOfHead==0&&vVCcMidxOfHead==0) sortBySumOf1stAnd2ndFromLrgToSml_new(size, vN, vNCc, v, vCc, vI, vICc);
          else sortBySumOf1stAnd2ndFromLrgToSml_new(size, vN, vNCc, v, vCc, vI, vICc, vVIdxOfHead, vVCcIdxOfHead, vVMidxOfHead, vVCcMidxOfHead);
        }
      else
        {
          // if(vVIdxOfHead==0&&vVCcIdxOfHead==0&&vVMidxOfHead==0&&vVCcMidxOfHead==0) sortBy1stFromLrgToSml(vN, v, vI);
          // else sortBy1stFromLrgToSml(vN, v, vI, vVIdxOfHead, vVMidxOfHead);
          if(vVIdxOfHead==0&&vVCcIdxOfHead==0&&vVMidxOfHead==0&&vVCcMidxOfHead==0) sortBy1stFromLrgToSml_new(size, vN, v, vI);
          else sortBy1stFromLrgToSml_new(size, vN, v, vI, vVIdxOfHead, vVMidxOfHead);
        }
    }
}

// End the definitions of the template member functions of the topoana class

#endif
