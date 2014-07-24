//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Feb 12 14:26:48 2012 by ROOT version 5.30/03
// from TTree HltTree/
// found on file: /Volumes/WORKDISK/backup/pc93/2012-01-26/WorkSpace/data/HI2011/forest/merged_pp2760_AllPhysics_Part_Prod03.root
//////////////////////////////////////////////////////////

#ifndef HLT_h
#define HLT_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class HLT {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           NohBJetL2;
   Float_t         ohBJetL2Energy[1];   //[NohBJetL2]
   Float_t         ohBJetL2Et[1];   //[NohBJetL2]
   Float_t         ohBJetL2Pt[1];   //[NohBJetL2]
   Float_t         ohBJetL2Eta[1];   //[NohBJetL2]
   Float_t         ohBJetL2Phi[1];   //[NohBJetL2]
   Int_t           NohBJetL2Corrected;
   Float_t         ohBJetL2CorrectedEnergy[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedEt[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedPt[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedEta[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetL2CorrectedPhi[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetIPL25Tag[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetIPL3Tag[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetIPL25TagSingleTrack[1];   //[NohBJetL2Corrected]
   Float_t         ohBJetIPL3TagSingleTrack[1];   //[NohBJetL2Corrected]
   Int_t           ohBJetPerfL25Tag[1];   //[NohBJetL2Corrected]
   Int_t           ohBJetPerfL3Tag[1];   //[NohBJetL2Corrected]
   Int_t           NrecoElec;
   Float_t         recoElecPt[6];   //[NrecoElec]
   Float_t         recoElecPhi[6];   //[NrecoElec]
   Float_t         recoElecEta[6];   //[NrecoElec]
   Float_t         recoElecEt[6];   //[NrecoElec]
   Float_t         recoElecE[6];   //[NrecoElec]
   Int_t           recoElecEleID[6];   //[NrecoElec]
   Float_t         recoElecIP[6];   //[NrecoElec]
   Int_t           recoElecNLostHits[6];   //[NrecoElec]
   Float_t         recoElecChi2NDF[6];   //[NrecoElec]
   Float_t         recoElecTrkIsoR03[6];   //[NrecoElec]
   Float_t         recoElecECaloIsoR03[6];   //[NrecoElec]
   Float_t         recoElecHCaloIsoR03[6];   //[NrecoElec]
   Bool_t          recoElecIsEcalDriven[6];   //[NrecoElec]
   Float_t         recoElecFbrem[6];   //[NrecoElec]
   Int_t           recoElecmishits[6];   //[NrecoElec]
   Float_t         recoElecdist[6];   //[NrecoElec]
   Float_t         recoElecdcot[6];   //[NrecoElec]
   Float_t         recoElectrkiso[6];   //[NrecoElec]
   Float_t         recoElececaliso[6];   //[NrecoElec]
   Float_t         recoElechcaliso[6];   //[NrecoElec]
   Float_t         recoElecsigmaietaieta[6];   //[NrecoElec]
   Float_t         recoElecdeltaPhiIn[6];   //[NrecoElec]
   Float_t         recoElecdeltaEtaIn[6];   //[NrecoElec]
   Float_t         recoElechOverE[6];   //[NrecoElec]
   Float_t         recoElecscEt[6];   //[NrecoElec]
   Float_t         recoElecd0corr[6];   //[NrecoElec]
   Bool_t          recoElecqGsfCtfScPixConsistent[6];   //[NrecoElec]
   Int_t           NrecoPhot;
   Float_t         recoPhotPt[25];   //[NrecoPhot]
   Float_t         recoPhotPhi[25];   //[NrecoPhot]
   Float_t         recoPhotEta[25];   //[NrecoPhot]
   Float_t         recoPhotEt[25];   //[NrecoPhot]
   Float_t         recoPhotE[25];   //[NrecoPhot]
   Float_t         recoPhotTiso[25];   //[NrecoPhot]
   Float_t         recoPhotEiso[25];   //[NrecoPhot]
   Float_t         recoPhotHiso[25];   //[NrecoPhot]
   Float_t         recoPhotHoverE[25];   //[NrecoPhot]
   Float_t         recoPhotClusShap[25];   //[NrecoPhot]
   Float_t         recoPhotR9ID[25];   //[NrecoPhot]
   Int_t           NohPhot;
   Float_t         ohPhotEt[1];   //[NohPhot]
   Float_t         ohPhotEta[1];   //[NohPhot]
   Float_t         ohPhotPhi[1];   //[NohPhot]
   Float_t         ohPhotEiso[1];   //[NohPhot]
   Float_t         ohPhotHiso[1];   //[NohPhot]
   Float_t         ohPhotTiso[1];   //[NohPhot]
   Int_t           ohPhotL1iso[1];   //[NohPhot]
   Float_t         ohPhotClusShap[1];   //[NohPhot]
   Float_t         ohPhotR9[1];   //[NohPhot]
   Float_t         ohPhotHforHoverE[1];   //[NohPhot]
   Float_t         ohPhotR9ID[1];   //[NohPhot]
   Int_t           NohEcalActiv;
   Float_t         ohEcalActivEt[1];   //[NohEcalActiv]
   Float_t         ohEcalActivEta[1];   //[NohEcalActiv]
   Float_t         ohEcalActivPhi[1];   //[NohEcalActiv]
   Float_t         ohEcalActivEiso[1];   //[NohEcalActiv]
   Float_t         ohEcalActivHiso[1];   //[NohEcalActiv]
   Float_t         ohEcalActivTiso[1];   //[NohEcalActiv]
   Int_t           ohEcalActivL1iso[1];   //[NohEcalActiv]
   Float_t         ohEcalActivClusShap[1];   //[NohEcalActiv]
   Float_t         ohEcalActivR9[1];   //[NohEcalActiv]
   Float_t         ohEcalActivHforHoverE[1];   //[NohEcalActiv]
   Float_t         ohEcalActivR9ID[1];   //[NohEcalActiv]
   Int_t           NohEle;
   Float_t         ohEleEt[1];   //[NohEle]
   Float_t         ohEleEta[1];   //[NohEle]
   Float_t         ohElePhi[1];   //[NohEle]
   Float_t         ohEleVtxZ[1];   //[NohEle]
   Float_t         ohEleE[1];   //[NohEle]
   Float_t         ohEleP[1];   //[NohEle]
   Float_t         ohEleHiso[1];   //[NohEle]
   Float_t         ohEleTiso[1];   //[NohEle]
   Float_t         ohEleEiso[1];   //[NohEle]
   Int_t           ohEleL1iso[1];   //[NohEle]
   Int_t           ohElePixelSeeds[1];   //[NohEle]
   Int_t           ohEleNewSC[1];   //[NohEle]
   Float_t         ohEleClusShap[1];   //[NohEle]
   Float_t         ohEleDeta[1];   //[NohEle]
   Float_t         ohEleDphi[1];   //[NohEle]
   Float_t         ohEleR9[1];   //[NohEle]
   Float_t         ohEleHforHoverE[1];   //[NohEle]
   Float_t         ohEleR9ID[1];   //[NohEle]
   Int_t           NohHFEle;
   Float_t         ohHFElePt[1];   //[NohHFEle]
   Float_t         ohHFEleEta[1];   //[NohHFEle]
   Int_t           NohHFECALClus;
   Float_t         ohHFEleClustere9e25[1];   //[NohHFECALClus]
   Float_t         ohHFEleClustere1e9[1];   //[NohHFECALClus]
   Float_t         ohHFEleClustereCOREe9[1];   //[NohHFECALClus]
   Float_t         ohHFEleClustereSeL[1];   //[NohHFECALClus]
   Float_t         ohHFEleCluster2Dcut[1];   //[NohHFECALClus]
   Float_t         ohHFEleClusterEta[1];   //[NohHFECALClus]
   Float_t         ohHFEleClusterPhi[1];   //[NohHFECALClus]
   Int_t           NL1IsolEm;
   Float_t         L1IsolEmEt[1];   //[NL1IsolEm]
   Float_t         L1IsolEmE[1];   //[NL1IsolEm]
   Float_t         L1IsolEmEta[1];   //[NL1IsolEm]
   Float_t         L1IsolEmPhi[1];   //[NL1IsolEm]
   Int_t           NL1NIsolEm;
   Float_t         L1NIsolEmEt[1];   //[NL1NIsolEm]
   Float_t         L1NIsolEmE[1];   //[NL1NIsolEm]
   Float_t         L1NIsolEmEta[1];   //[NL1NIsolEm]
   Float_t         L1NIsolEmPhi[1];   //[NL1NIsolEm]
   Int_t           NL1Mu;
   Float_t         L1MuPt[1];   //[NL1Mu]
   Float_t         L1MuE[1];   //[NL1Mu]
   Float_t         L1MuEta[1];   //[NL1Mu]
   Float_t         L1MuPhi[1];   //[NL1Mu]
   Int_t           L1MuIsol[1];   //[NL1Mu]
   Int_t           L1MuMip[1];   //[NL1Mu]
   Int_t           L1MuFor[1];   //[NL1Mu]
   Int_t           L1MuRPC[1];   //[NL1Mu]
   Int_t           L1MuQal[1];   //[NL1Mu]
   Int_t           L1MuChg[1];   //[NL1Mu]
   Int_t           NL1CenJet;
   Float_t         L1CenJetEt[1];   //[NL1CenJet]
   Float_t         L1CenJetE[1];   //[NL1CenJet]
   Float_t         L1CenJetEta[1];   //[NL1CenJet]
   Float_t         L1CenJetPhi[1];   //[NL1CenJet]
   Int_t           NL1ForJet;
   Float_t         L1ForJetEt[1];   //[NL1ForJet]
   Float_t         L1ForJetE[1];   //[NL1ForJet]
   Float_t         L1ForJetEta[1];   //[NL1ForJet]
   Float_t         L1ForJetPhi[1];   //[NL1ForJet]
   Int_t           NL1Tau;
   Float_t         L1TauEt[1];   //[NL1Tau]
   Float_t         L1TauE[1];   //[NL1Tau]
   Float_t         L1TauEta[1];   //[NL1Tau]
   Float_t         L1TauPhi[1];   //[NL1Tau]
   Float_t         L1Met;
   Float_t         L1MetPhi;
   Float_t         L1EtTot;
   Float_t         L1Mht;
   Float_t         L1MhtPhi;
   Float_t         L1EtHad;
   Int_t           L1HfRing1EtSumPositiveEta;
   Int_t           L1HfRing2EtSumPositiveEta;
   Int_t           L1HfRing1EtSumNegativeEta;
   Int_t           L1HfRing2EtSumNegativeEta;
   Int_t           L1HfTowerCountPositiveEtaRing1;
   Int_t           L1HfTowerCountNegativeEtaRing1;
   Int_t           L1HfTowerCountPositiveEtaRing2;
   Int_t           L1HfTowerCountNegativeEtaRing2;
   Int_t           recoNVrtHLT;
   Float_t         recoVrtXHLT[1];   //[NVrtx]
   Float_t         recoVrtYHLT[1];   //[NVrtx]
   Float_t         recoVrtZHLT[1];   //[NVrtx]
   Int_t           recoVrtNtrkHLT[1];   //[NVrtx]
   Float_t         recoVrtChi2HLT[1];   //[NVrtx]
   Float_t         recoVrtNdofHLT[1];   //[NVrtx]
   Int_t           recoNVrtOffline0;
   Float_t         recoVrtXOffline0[1];   //[NVrtx]
   Float_t         recoVrtYOffline0[1];   //[NVrtx]
   Float_t         recoVrtZOffline0[1];   //[NVrtx]
   Int_t           recoVrtNtrkOffline0[1];   //[NVrtx]
   Float_t         recoVrtChi2Offline0[1];   //[NVrtx]
   Float_t         recoVrtNdofOffline0[1];   //[NVrtx]
   Float_t         Npart;
   Float_t         Ncoll;
   Float_t         Nhard;
   Float_t         phi0;
   Float_t         b;
   Int_t           Ncharged;
   Int_t           NchargedMR;
   Float_t         MeanPt;
   Float_t         MeanPtMR;
   Float_t         EtMR;
   Int_t           NchargedPtCut;
   Int_t           NchargedPtCutMR;
   Int_t           hiBin;
   Float_t         hiHF;
   Float_t         hiHFplus;
   Float_t         hiHFminus;
   Float_t         hiZDC;
   Float_t         hiZDCplus;
   Float_t         hiZDCminus;
   Float_t         hiHFhit;
   Float_t         hiHFhitPlus;
   Float_t         hiHFhitMinus;
   Float_t         hiET;
   Float_t         hiEE;
   Float_t         hiEB;
   Float_t         hiEEplus;
   Float_t         hiEEminus;
   Int_t           hiNpix;
   Int_t           hiNpixelTracks;
   Int_t           hiNtracks;
   Int_t           hiNevtPlane;
   Float_t         hiEvtPlanes[1];   //[hiNevtPlane]
   Int_t           hiNtracksPtCut;
   Int_t           hiNtracksEtaCut;
   Int_t           hiNtracksEtaPtCut;
   Int_t           Run;
   Int_t           Event;
   Int_t           LumiBlock;
   Int_t           Bx;
   Int_t           Orbit;
   Double_t        AvgInstDelLumi;
   Int_t           AlCa_EcalPhiSym_v2;
   Int_t           AlCa_EcalPhiSym_v2_Prescl;
   Int_t           AlCa_EcalEta_v3;
   Int_t           AlCa_EcalEta_v3_Prescl;
   Int_t           AlCa_EcalPi0_v4;
   Int_t           AlCa_EcalPi0_v4_Prescl;
   Int_t           AlCa_RPCMuonNoHits_v2;
   Int_t           AlCa_RPCMuonNoHits_v2_Prescl;
   Int_t           AlCa_RPCMuonNoTriggers_v2;
   Int_t           AlCa_RPCMuonNoTriggers_v2_Prescl;
   Int_t           AlCa_RPCMuonNormalisation_v2;
   Int_t           AlCa_RPCMuonNormalisation_v2_Prescl;
   Int_t           HLT_BeamGas_BSC_v2;
   Int_t           HLT_BeamGas_BSC_v2_Prescl;
   Int_t           HLT_BeamGas_HF_v2;
   Int_t           HLT_BeamGas_HF_v2_Prescl;
   Int_t           HLT_BeamHalo_v2;
   Int_t           HLT_BeamHalo_v2_Prescl;
   Int_t           HLT_Calibration_v1;
   Int_t           HLT_Calibration_v1_Prescl;
   Int_t           HLT_DTErrors_v1;
   Int_t           HLT_DTErrors_v1_Prescl;
   Int_t           HLT_DoubleMu3_v3;
   Int_t           HLT_DoubleMu3_v3_Prescl;
   Int_t           HLT_EcalCalibration_v1;
   Int_t           HLT_EcalCalibration_v1_Prescl;
   Int_t           HLT_Ele8_v2;
   Int_t           HLT_Ele8_v2_Prescl;
   Int_t           HLT_GlobalRunHPDNoise_v2;
   Int_t           HLT_GlobalRunHPDNoise_v2_Prescl;
   Int_t           HLT_HcalCalibration_v1;
   Int_t           HLT_HcalCalibration_v1_Prescl;
   Int_t           HLT_HcalNZS_v3;
   Int_t           HLT_HcalNZS_v3_Prescl;
   Int_t           HLT_HcalPhiSym_v3;
   Int_t           HLT_HcalPhiSym_v3_Prescl;
   Int_t           HLT_IsoTrackHB_v2;
   Int_t           HLT_IsoTrackHB_v2_Prescl;
   Int_t           HLT_IsoTrackHE_v3;
   Int_t           HLT_IsoTrackHE_v3_Prescl;
   Int_t           HLT_Jet20_v1;
   Int_t           HLT_Jet20_v1_Prescl;
   Int_t           HLT_Jet40_v1;
   Int_t           HLT_Jet40_v1_Prescl;
   Int_t           HLT_Jet60_v1;
   Int_t           HLT_Jet60_v1_Prescl;
   Int_t           HLT_L1DoubleForJet32_EtaOpp_v1;
   Int_t           HLT_L1DoubleForJet32_EtaOpp_v1_Prescl;
   Int_t           HLT_L1DoubleForJet8_EtaOpp_v1;
   Int_t           HLT_L1DoubleForJet8_EtaOpp_v1_Prescl;
   Int_t           HLT_L1DoubleMu0_v1;
   Int_t           HLT_L1DoubleMu0_v1_Prescl;
   Int_t           HLT_L1SingleEG12_v1;
   Int_t           HLT_L1SingleEG12_v1_Prescl;
   Int_t           HLT_L1SingleEG5_v1;
   Int_t           HLT_L1SingleEG5_v1_Prescl;
   Int_t           HLT_L1SingleJet36_v1;
   Int_t           HLT_L1SingleJet36_v1_Prescl;
   Int_t           HLT_L1SingleMuOpen_AntiBPTX_v1;
   Int_t           HLT_L1SingleMuOpen_AntiBPTX_v1_Prescl;
   Int_t           HLT_L1SingleMuOpen_DT_v1;
   Int_t           HLT_L1SingleMuOpen_DT_v1_Prescl;
   Int_t           HLT_L1SingleMuOpen_v1;
   Int_t           HLT_L1SingleMuOpen_v1_Prescl;
   Int_t           HLT_L1Tech_BSC_halo_v1;
   Int_t           HLT_L1Tech_BSC_halo_v1_Prescl;
   Int_t           HLT_L1Tech_HBHEHO_totalOR_v1;
   Int_t           HLT_L1Tech_HBHEHO_totalOR_v1_Prescl;
   Int_t           HLT_L1TrackerCosmics_v2;
   Int_t           HLT_L1TrackerCosmics_v2_Prescl;
   Int_t           HLT_L1_Interbunch_BSC_v1;
   Int_t           HLT_L1_Interbunch_BSC_v1_Prescl;
   Int_t           HLT_L1_PreCollisions_v1;
   Int_t           HLT_L1_PreCollisions_v1_Prescl;
   Int_t           HLT_L2DoubleMu0_v2;
   Int_t           HLT_L2DoubleMu0_v2_Prescl;
   Int_t           HLT_L3MuonsCosmicTracking_v1;
   Int_t           HLT_L3MuonsCosmicTracking_v1_Prescl;
   Int_t           HLT_LogMonitor_v1;
   Int_t           HLT_LogMonitor_v1_Prescl;
   Int_t           HLT_L1BscMinBiasORBptxPlusANDMinus_v1;
   Int_t           HLT_L1BscMinBiasORBptxPlusANDMinus_v1_Prescl;
   Int_t           HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1;
   Int_t           HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1_Prescl;
   Int_t           HLT_Mu0_v3;
   Int_t           HLT_Mu0_v3_Prescl;
   Int_t           HLT_Mu3_v3;
   Int_t           HLT_Mu3_v3_Prescl;
   Int_t           HLT_Mu5_v3;
   Int_t           HLT_Mu5_v3_Prescl;
   Int_t           HLT_Photon10_CaloIdVL_v1;
   Int_t           HLT_Photon10_CaloIdVL_v1_Prescl;
   Int_t           HLT_Photon15_CaloIdVL_v1;
   Int_t           HLT_Photon15_CaloIdVL_v1_Prescl;
   Int_t           HLT_Physics_NanoDST_v1;
   Int_t           HLT_Physics_NanoDST_v1_Prescl;
   Int_t           HLT_PixelTracks_Multiplicity50_Loose;
   Int_t           HLT_PixelTracks_Multiplicity50_Loose_Prescl;
   Int_t           HLT_PixelTracks_Multiplicity60_Loose;
   Int_t           HLT_PixelTracks_Multiplicity60_Loose_Prescl;
   Int_t           HLT_PixelTracks_Multiplicity70_Loose;
   Int_t           HLT_PixelTracks_Multiplicity70_Loose_Prescl;
   Int_t           HLT_Random_v1;
   Int_t           HLT_Random_v1_Prescl;
   Int_t           HLT_RegionalCosmicTracking_v1;
   Int_t           HLT_RegionalCosmicTracking_v1_Prescl;
   Int_t           HLT_TrackerCalibration_v1;
   Int_t           HLT_TrackerCalibration_v1_Prescl;
   Int_t           HLT_ZeroBiasPixel_SingleTrack_v1;
   Int_t           HLT_ZeroBiasPixel_SingleTrack_v1_Prescl;
   Int_t           HLT_ZeroBias_v1;
   Int_t           HLT_ZeroBias_v1_Prescl;
   Int_t           HLTriggerFinalPath;
   Int_t           HLTriggerFinalPath_Prescl;
   Int_t           L1_BeamGas_Bsc;
   Int_t           L1_BeamGas_Bsc_Prescl;
   Int_t           L1_BeamGas_Hf;
   Int_t           L1_BeamGas_Hf_Prescl;
   Int_t           L1_BeamHalo;
   Int_t           L1_BeamHalo_Prescl;
   Int_t           L1_BptxMinus_NotBptxPlus;
   Int_t           L1_BptxMinus_NotBptxPlus_Prescl;
   Int_t           L1_BptxPlusANDMinus;
   Int_t           L1_BptxPlusANDMinus_Prescl;
   Int_t           L1_BptxPlus_NotBptxMinus;
   Int_t           L1_BptxPlus_NotBptxMinus_Prescl;
   Int_t           L1_Bsc2Minus_BptxMinus;
   Int_t           L1_Bsc2Minus_BptxMinus_Prescl;
   Int_t           L1_Bsc2Plus_BptxPlus;
   Int_t           L1_Bsc2Plus_BptxPlus_Prescl;
   Int_t           L1_BscMinBiasOR_BptxPlusANDMinus;
   Int_t           L1_BscMinBiasOR_BptxPlusANDMinus_Prescl;
   Int_t           L1_DoubleEG10;
   Int_t           L1_DoubleEG10_Prescl;
   Int_t           L1_DoubleEG2_FwdVeto;
   Int_t           L1_DoubleEG2_FwdVeto_Prescl;
   Int_t           L1_DoubleEG3;
   Int_t           L1_DoubleEG3_Prescl;
   Int_t           L1_DoubleEG5;
   Int_t           L1_DoubleEG5_Prescl;
   Int_t           L1_DoubleEG5_HTT50;
   Int_t           L1_DoubleEG5_HTT50_Prescl;
   Int_t           L1_DoubleEG5_HTT75;
   Int_t           L1_DoubleEG5_HTT75_Prescl;
   Int_t           L1_DoubleEG8;
   Int_t           L1_DoubleEG8_Prescl;
   Int_t           L1_DoubleEG_12_5;
   Int_t           L1_DoubleEG_12_5_Prescl;
   Int_t           L1_DoubleEG_12_5_Eta1p39;
   Int_t           L1_DoubleEG_12_5_Eta1p39_Prescl;
   Int_t           L1_DoubleForJet32_EtaOpp;
   Int_t           L1_DoubleForJet32_EtaOpp_Prescl;
   Int_t           L1_DoubleForJet44_EtaOpp;
   Int_t           L1_DoubleForJet44_EtaOpp_Prescl;
   Int_t           L1_DoubleForJet8_EtaOpp;
   Int_t           L1_DoubleForJet8_EtaOpp_Prescl;
   Int_t           L1_DoubleIsoEG10;
   Int_t           L1_DoubleIsoEG10_Prescl;
   Int_t           L1_DoubleJet36_Central;
   Int_t           L1_DoubleJet36_Central_Prescl;
   Int_t           L1_DoubleJet44_Central;
   Int_t           L1_DoubleJet44_Central_Prescl;
   Int_t           L1_DoubleJet52;
   Int_t           L1_DoubleJet52_Prescl;
   Int_t           L1_DoubleMu0;
   Int_t           L1_DoubleMu0_Prescl;
   Int_t           L1_DoubleMu0_HighQ;
   Int_t           L1_DoubleMu0_HighQ_Prescl;
   Int_t           L1_DoubleMu0_HighQ_EtaCuts;
   Int_t           L1_DoubleMu0_HighQ_EtaCuts_Prescl;
   Int_t           L1_DoubleMu3;
   Int_t           L1_DoubleMu3_Prescl;
   Int_t           L1_DoubleMu3_EG5;
   Int_t           L1_DoubleMu3_EG5_Prescl;
   Int_t           L1_DoubleMu3p5;
   Int_t           L1_DoubleMu3p5_Prescl;
   Int_t           L1_DoubleMu5_v1;
   Int_t           L1_DoubleMu5_v1_Prescl;
   Int_t           L1_DoubleTauJet28;
   Int_t           L1_DoubleTauJet28_Prescl;
   Int_t           L1_DoubleTauJet32;
   Int_t           L1_DoubleTauJet32_Prescl;
   Int_t           L1_DoubleTauJet36;
   Int_t           L1_DoubleTauJet36_Prescl;
   Int_t           L1_DoubleTauJet40;
   Int_t           L1_DoubleTauJet40_Prescl;
   Int_t           L1_EG10_Jet24_Central_deltaPhi1;
   Int_t           L1_EG10_Jet24_Central_deltaPhi1_Prescl;
   Int_t           L1_EG12_Jet24_Central_deltaPhi1;
   Int_t           L1_EG12_Jet24_Central_deltaPhi1_Prescl;
   Int_t           L1_EG12_TauJet20_deltaPhi1;
   Int_t           L1_EG12_TauJet20_deltaPhi1_Prescl;
   Int_t           L1_EG5_HTT100;
   Int_t           L1_EG5_HTT100_Prescl;
   Int_t           L1_EG5_HTT125;
   Int_t           L1_EG5_HTT125_Prescl;
   Int_t           L1_EG5_HTT75;
   Int_t           L1_EG5_HTT75_Prescl;
   Int_t           L1_EG5_Jet36_deltaPhi1;
   Int_t           L1_EG5_Jet36_deltaPhi1_Prescl;
   Int_t           L1_EG8_Jet20_Central_deltaPhi1;
   Int_t           L1_EG8_Jet20_Central_deltaPhi1_Prescl;
   Int_t           L1_ETM100;
   Int_t           L1_ETM100_Prescl;
   Int_t           L1_ETM20;
   Int_t           L1_ETM20_Prescl;
   Int_t           L1_ETM30;
   Int_t           L1_ETM30_Prescl;
   Int_t           L1_ETM50;
   Int_t           L1_ETM50_Prescl;
   Int_t           L1_ETM70;
   Int_t           L1_ETM70_Prescl;
   Int_t           L1_ETT20;
   Int_t           L1_ETT20_Prescl;
   Int_t           L1_ETT40;
   Int_t           L1_ETT40_Prescl;
   Int_t           L1_ETT60;
   Int_t           L1_ETT60_Prescl;
   Int_t           L1_HTM50;
   Int_t           L1_HTM50_Prescl;
   Int_t           L1_HTT100;
   Int_t           L1_HTT100_Prescl;
   Int_t           L1_HTT150;
   Int_t           L1_HTT150_Prescl;
   Int_t           L1_HTT50;
   Int_t           L1_HTT50_Prescl;
   Int_t           L1_HTT50_HTM30;
   Int_t           L1_HTT50_HTM30_Prescl;
   Int_t           L1_HTT50_HTM50;
   Int_t           L1_HTT50_HTM50_Prescl;
   Int_t           L1_HTT75;
   Int_t           L1_HTT75_Prescl;
   Int_t           L1_InterBunch_Bsc;
   Int_t           L1_InterBunch_Bsc_Prescl;
   Int_t           L1_InterBunch_Hf;
   Int_t           L1_InterBunch_Hf_Prescl;
   Int_t           L1_Mu0_HTT50;
   Int_t           L1_Mu0_HTT50_Prescl;
   Int_t           L1_Mu0_HTT75;
   Int_t           L1_Mu0_HTT75_Prescl;
   Int_t           L1_Mu10_Jet36_Central;
   Int_t           L1_Mu10_Jet36_Central_Prescl;
   Int_t           L1_Mu12_EG5;
   Int_t           L1_Mu12_EG5_Prescl;
   Int_t           L1_Mu3_DoubleEG5;
   Int_t           L1_Mu3_DoubleEG5_Prescl;
   Int_t           L1_Mu3_EG5;
   Int_t           L1_Mu3_EG5_Prescl;
   Int_t           L1_Mu3_Jet16_Central;
   Int_t           L1_Mu3_Jet16_Central_Prescl;
   Int_t           L1_Mu3_Jet20_Central;
   Int_t           L1_Mu3_Jet20_Central_Prescl;
   Int_t           L1_Mu3_Jet28_Central;
   Int_t           L1_Mu3_Jet28_Central_Prescl;
   Int_t           L1_Mu5_EG12;
   Int_t           L1_Mu5_EG12_Prescl;
   Int_t           L1_Mu7_EG5;
   Int_t           L1_Mu7_EG5_Prescl;
   Int_t           L1_Mu7_Jet20_Central;
   Int_t           L1_Mu7_Jet20_Central_Prescl;
   Int_t           L1_Mu7_TauJet16;
   Int_t           L1_Mu7_TauJet16_Prescl;
   Int_t           L1_MuOpen_EG12;
   Int_t           L1_MuOpen_EG12_Prescl;
   Int_t           L1_MuOpen_EG5;
   Int_t           L1_MuOpen_EG5_Prescl;
   Int_t           L1_PreCollisions;
   Int_t           L1_PreCollisions_Prescl;
   Int_t           L1_QuadJet20_Central;
   Int_t           L1_QuadJet20_Central_Prescl;
   Int_t           L1_QuadJet28_Central;
   Int_t           L1_QuadJet28_Central_Prescl;
   Int_t           L1_SingleEG12;
   Int_t           L1_SingleEG12_Prescl;
   Int_t           L1_SingleEG12_Eta1p39;
   Int_t           L1_SingleEG12_Eta1p39_Prescl;
   Int_t           L1_SingleEG12_Eta2p17;
   Int_t           L1_SingleEG12_Eta2p17_Prescl;
   Int_t           L1_SingleEG15;
   Int_t           L1_SingleEG15_Prescl;
   Int_t           L1_SingleEG20;
   Int_t           L1_SingleEG20_Prescl;
   Int_t           L1_SingleEG30;
   Int_t           L1_SingleEG30_Prescl;
   Int_t           L1_SingleEG5;
   Int_t           L1_SingleEG5_Prescl;
   Int_t           L1_SingleIsoEG12;
   Int_t           L1_SingleIsoEG12_Prescl;
   Int_t           L1_SingleIsoEG12_Eta1p39;
   Int_t           L1_SingleIsoEG12_Eta1p39_Prescl;
   Int_t           L1_SingleIsoEG12_Eta2p17;
   Int_t           L1_SingleIsoEG12_Eta2p17_Prescl;
   Int_t           L1_SingleJet16;
   Int_t           L1_SingleJet16_Prescl;
   Int_t           L1_SingleJet20_NotBptxOR;
   Int_t           L1_SingleJet20_NotBptxOR_Prescl;
   Int_t           L1_SingleJet20_NotBptxOR_NotMuBeamHalo;
   Int_t           L1_SingleJet20_NotBptxOR_NotMuBeamHalo_Prescl;
   Int_t           L1_SingleJet32_NotBptxOR_NotMuBeamHalo;
   Int_t           L1_SingleJet32_NotBptxOR_NotMuBeamHalo_Prescl;
   Int_t           L1_SingleJet36;
   Int_t           L1_SingleJet36_Prescl;
   Int_t           L1_SingleJet36_FwdVeto;
   Int_t           L1_SingleJet36_FwdVeto_Prescl;
   Int_t           L1_SingleJet52;
   Int_t           L1_SingleJet52_Prescl;
   Int_t           L1_SingleJet68;
   Int_t           L1_SingleJet68_Prescl;
   Int_t           L1_SingleJet8;
   Int_t           L1_SingleJet8_Prescl;
   Int_t           L1_SingleJet80_Central;
   Int_t           L1_SingleJet80_Central_Prescl;
   Int_t           L1_SingleJet92;
   Int_t           L1_SingleJet92_Prescl;
   Int_t           L1_SingleJet92_Central;
   Int_t           L1_SingleJet92_Central_Prescl;
   Int_t           L1_SingleMu10;
   Int_t           L1_SingleMu10_Prescl;
   Int_t           L1_SingleMu12;
   Int_t           L1_SingleMu12_Prescl;
   Int_t           L1_SingleMu12_Debug;
   Int_t           L1_SingleMu12_Debug_Prescl;
   Int_t           L1_SingleMu16;
   Int_t           L1_SingleMu16_Prescl;
   Int_t           L1_SingleMu20;
   Int_t           L1_SingleMu20_Prescl;
   Int_t           L1_SingleMu25;
   Int_t           L1_SingleMu25_Prescl;
   Int_t           L1_SingleMu3;
   Int_t           L1_SingleMu3_Prescl;
   Int_t           L1_SingleMu5_Eta1p5_Q80_v1;
   Int_t           L1_SingleMu5_Eta1p5_Q80_v1_Prescl;
   Int_t           L1_SingleMu7;
   Int_t           L1_SingleMu7_Prescl;
   Int_t           L1_SingleMu7_Barrel;
   Int_t           L1_SingleMu7_Barrel_Prescl;
   Int_t           L1_SingleMu7_Eta2p1;
   Int_t           L1_SingleMu7_Eta2p1_Prescl;
   Int_t           L1_SingleMuBeamHalo;
   Int_t           L1_SingleMuBeamHalo_Prescl;
   Int_t           L1_SingleMuOpen;
   Int_t           L1_SingleMuOpen_Prescl;
   Int_t           L1_SingleTauJet52;
   Int_t           L1_SingleTauJet52_Prescl;
   Int_t           L1_SingleTauJet68;
   Int_t           L1_SingleTauJet68_Prescl;
   Int_t           L1_SingleTauJet80;
   Int_t           L1_SingleTauJet80_Prescl;
   Int_t           L1_TripleEG5;
   Int_t           L1_TripleEG5_Prescl;
   Int_t           L1_TripleEG7;
   Int_t           L1_TripleEG7_Prescl;
   Int_t           L1_TripleEG_8_5_5;
   Int_t           L1_TripleEG_8_5_5_Prescl;
   Int_t           L1_TripleEG_8_8_5;
   Int_t           L1_TripleEG_8_8_5_Prescl;
   Int_t           L1_TripleJet28_Central;
   Int_t           L1_TripleJet28_Central_Prescl;
   Int_t           L1_ZeroBias;
   Int_t           L1_ZeroBias_Prescl;
   Int_t           L1Tech_BPTX_minus_v0;
   Int_t           L1Tech_BPTX_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_minus_AND_not_plus_v0;
   Int_t           L1Tech_BPTX_minus_AND_not_plus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_v0;
   Int_t           L1Tech_BPTX_plus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_NOT_minus_v0;
   Int_t           L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_minus_v0;
   Int_t           L1Tech_BPTX_plus_AND_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_AND_minus_instance1_v0;
   Int_t           L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl;
   Int_t           L1Tech_BPTX_plus_OR_minus_v0;
   Int_t           L1Tech_BPTX_plus_OR_minus_v0_Prescl;
   Int_t           L1Tech_BPTX_quiet_v0;
   Int_t           L1Tech_BPTX_quiet_v0_Prescl;
   Int_t           L1Tech_BSC_HighMultiplicity_v0;
   Int_t           L1Tech_BSC_HighMultiplicity_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam1_inner_v0;
   Int_t           L1Tech_BSC_halo_beam1_inner_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam1_outer_v0;
   Int_t           L1Tech_BSC_halo_beam1_outer_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam2_inner_v0;
   Int_t           L1Tech_BSC_halo_beam2_inner_v0_Prescl;
   Int_t           L1Tech_BSC_halo_beam2_outer_v0;
   Int_t           L1Tech_BSC_halo_beam2_outer_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_OR_v0;
   Int_t           L1Tech_BSC_minBias_OR_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_inner_threshold1_v0;
   Int_t           L1Tech_BSC_minBias_inner_threshold1_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_inner_threshold2_v0;
   Int_t           L1Tech_BSC_minBias_inner_threshold2_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_threshold1_v0;
   Int_t           L1Tech_BSC_minBias_threshold1_v0_Prescl;
   Int_t           L1Tech_BSC_minBias_threshold2_v0;
   Int_t           L1Tech_BSC_minBias_threshold2_v0_Prescl;
   Int_t           L1Tech_BSC_splash_beam1_v0;
   Int_t           L1Tech_BSC_splash_beam1_v0_Prescl;
   Int_t           L1Tech_BSC_splash_beam2_v0;
   Int_t           L1Tech_BSC_splash_beam2_v0_Prescl;
   Int_t           L1Tech_CASTOR_HaloMuon_v0;
   Int_t           L1Tech_CASTOR_HaloMuon_v0_Prescl;
   Int_t           L1Tech_DT_GlobalOR_v0;
   Int_t           L1Tech_DT_GlobalOR_v0_Prescl;
   Int_t           L1Tech_HCAL_HBHE_totalOR_v0;
   Int_t           L1Tech_HCAL_HBHE_totalOR_v0_Prescl;
   Int_t           L1Tech_HCAL_HF_MMP_or_MPP_v0;
   Int_t           L1Tech_HCAL_HF_MMP_or_MPP_v0_Prescl;
   Int_t           L1Tech_HCAL_HF_MM_or_PP_or_PM_v0;
   Int_t           L1Tech_HCAL_HF_MM_or_PP_or_PM_v0_Prescl;
   Int_t           L1Tech_HCAL_HF_coincidence_PM_v1;
   Int_t           L1Tech_HCAL_HF_coincidence_PM_v1_Prescl;
   Int_t           L1Tech_HCAL_HO_totalOR_v0;
   Int_t           L1Tech_HCAL_HO_totalOR_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RB0_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBminus1_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBminus2_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBplus1_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBplus2_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_RBst1_collisions_v0;
   Int_t           L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_barrel_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl;
   Int_t           L1Tech_RPC_TTU_pointing_Cosmics_v0;
   Int_t           L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_loose_vertex_v0;
   Int_t           L1Tech_ZDC_Scint_loose_vertex_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_minus_v0;
   Int_t           L1Tech_ZDC_Scint_minus_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_plus_v0;
   Int_t           L1Tech_ZDC_Scint_plus_v0_Prescl;
   Int_t           L1Tech_ZDC_Scint_tight_vertex_v0;
   Int_t           L1Tech_ZDC_Scint_tight_vertex_v0_Prescl;

   // List of branches
   TBranch        *b_NohBJetL2;   //!
   TBranch        *b_ohBJetL2Energy;   //!
   TBranch        *b_ohBJetL2Et;   //!
   TBranch        *b_ohBJetL2Pt;   //!
   TBranch        *b_ohBJetL2Eta;   //!
   TBranch        *b_ohBJetL2Phi;   //!
   TBranch        *b_NohBJetL2Corrected;   //!
   TBranch        *b_ohBJetL2CorrectedEnergy;   //!
   TBranch        *b_ohBJetL2CorrectedEt;   //!
   TBranch        *b_ohBJetL2CorrectedPt;   //!
   TBranch        *b_ohBJetL2CorrectedEta;   //!
   TBranch        *b_ohBJetL2CorrectedPhi;   //!
   TBranch        *b_ohBJetIPL25Tag;   //!
   TBranch        *b_ohBJetIPL3Tag;   //!
   TBranch        *b_ohBJetIPL25TagSingleTrack;   //!
   TBranch        *b_ohBJetIPL3TagSingleTrack;   //!
   TBranch        *b_ohBJetPerfL25Tag;   //!
   TBranch        *b_ohBJetPerfL3Tag;   //!
   TBranch        *b_NrecoElec;   //!
   TBranch        *b_recoElecPt;   //!
   TBranch        *b_recoElecPhi;   //!
   TBranch        *b_recoElecEta;   //!
   TBranch        *b_recoElecEt;   //!
   TBranch        *b_recoElecE;   //!
   TBranch        *b_recoElecEleID;   //!
   TBranch        *b_recoElecIP;   //!
   TBranch        *b_recoElecNLostHits;   //!
   TBranch        *b_recoElecChi2NDF;   //!
   TBranch        *b_recoElecTrkIsoR03;   //!
   TBranch        *b_recoElecECaloIsoR03;   //!
   TBranch        *b_recoElecHCaloIsoR03;   //!
   TBranch        *b_recoElecIsEcalDriven;   //!
   TBranch        *b_recoElecFbrem;   //!
   TBranch        *b_recoElecmishits;   //!
   TBranch        *b_recoElecdist;   //!
   TBranch        *b_recoElecdcot;   //!
   TBranch        *b_recoElectrkiso;   //!
   TBranch        *b_recoElececaliso;   //!
   TBranch        *b_recoElechcaliso;   //!
   TBranch        *b_recoElecsigmaietaieta;   //!
   TBranch        *b_recoElecdeltaPhiIn;   //!
   TBranch        *b_recoElecdeltaEtaIn;   //!
   TBranch        *b_recoElechOverE;   //!
   TBranch        *b_recoElecscEt;   //!
   TBranch        *b_recoElecd0corr;   //!
   TBranch        *b_recoElecqGsfCtfScPixConsistent;   //!
   TBranch        *b_NrecoPhot;   //!
   TBranch        *b_recoPhotPt;   //!
   TBranch        *b_recoPhotPhi;   //!
   TBranch        *b_recoPhotEta;   //!
   TBranch        *b_recoPhotEt;   //!
   TBranch        *b_recoPhotE;   //!
   TBranch        *b_recoPhotTiso;   //!
   TBranch        *b_recoPhotEiso;   //!
   TBranch        *b_recoPhotHiso;   //!
   TBranch        *b_recoPhotHoverE;   //!
   TBranch        *b_recoPhotClusShap;   //!
   TBranch        *b_recoPhotR9ID;   //!
   TBranch        *b_NohPhot;   //!
   TBranch        *b_ohPhotEt;   //!
   TBranch        *b_ohPhotEta;   //!
   TBranch        *b_ohPhotPhi;   //!
   TBranch        *b_ohPhotEiso;   //!
   TBranch        *b_ohPhotHiso;   //!
   TBranch        *b_ohPhotTiso;   //!
   TBranch        *b_ohPhotL1iso;   //!
   TBranch        *b_ohPhotClusShap;   //!
   TBranch        *b_ohPhotR9;   //!
   TBranch        *b_ohPhotHforHoverE;   //!
   TBranch        *b_ohPhotR9ID;   //!
   TBranch        *b_NohEcalActiv;   //!
   TBranch        *b_ohEcalActivEt;   //!
   TBranch        *b_ohEcalActivEta;   //!
   TBranch        *b_ohEcalActivPhi;   //!
   TBranch        *b_ohEcalActivEiso;   //!
   TBranch        *b_ohEcalActivHiso;   //!
   TBranch        *b_ohEcalActivTiso;   //!
   TBranch        *b_ohEcalActivL1iso;   //!
   TBranch        *b_ohEcalActivClusShap;   //!
   TBranch        *b_ohEcalActivR9;   //!
   TBranch        *b_ohEcalActivHforHoverE;   //!
   TBranch        *b_ohEcalActivR9ID;   //!
   TBranch        *b_NohEle;   //!
   TBranch        *b_ohEleEt;   //!
   TBranch        *b_ohEleEta;   //!
   TBranch        *b_ohElePhi;   //!
   TBranch        *b_ohEleVtxZ;   //!
   TBranch        *b_ohEleE;   //!
   TBranch        *b_ohEleP;   //!
   TBranch        *b_ohEleHiso;   //!
   TBranch        *b_ohEleTiso;   //!
   TBranch        *b_ohEleEiso;   //!
   TBranch        *b_ohEleL1iso;   //!
   TBranch        *b_ohElePixelSeeds;   //!
   TBranch        *b_ohEleNewSC;   //!
   TBranch        *b_ohEleClusShap;   //!
   TBranch        *b_ohEleDeta;   //!
   TBranch        *b_ohEleDphi;   //!
   TBranch        *b_ohEleR9;   //!
   TBranch        *b_ohEleHforHoverE;   //!
   TBranch        *b_ohEleR9ID;   //!
   TBranch        *b_NohHFEle;   //!
   TBranch        *b_ohHFElePt;   //!
   TBranch        *b_ohHFEleEta;   //!
   TBranch        *b_NohHFECALClus;   //!
   TBranch        *b_ohHFEleClustere9e25;   //!
   TBranch        *b_ohHFEleClustere1e9;   //!
   TBranch        *b_ohHFEleClustereCOREe9;   //!
   TBranch        *b_ohHFEleClustereSeL;   //!
   TBranch        *b_ohHFEleCluster2Dcut;   //!
   TBranch        *b_ohHFEleClusterEta;   //!
   TBranch        *b_ohHFEleClusterPhi;   //!
   TBranch        *b_NL1IsolEm;   //!
   TBranch        *b_L1IsolEmEt;   //!
   TBranch        *b_L1IsolEmE;   //!
   TBranch        *b_L1IsolEmEta;   //!
   TBranch        *b_L1IsolEmPhi;   //!
   TBranch        *b_NL1NIsolEm;   //!
   TBranch        *b_L1NIsolEmEt;   //!
   TBranch        *b_L1NIsolEmE;   //!
   TBranch        *b_L1NIsolEmEta;   //!
   TBranch        *b_L1NIsolEmPhi;   //!
   TBranch        *b_NL1Mu;   //!
   TBranch        *b_L1MuPt;   //!
   TBranch        *b_L1MuE;   //!
   TBranch        *b_L1MuEta;   //!
   TBranch        *b_L1MuPhi;   //!
   TBranch        *b_L1MuIsol;   //!
   TBranch        *b_L1MuMip;   //!
   TBranch        *b_L1MuFor;   //!
   TBranch        *b_L1MuRPC;   //!
   TBranch        *b_L1MuQal;   //!
   TBranch        *b_L1MuChg;   //!
   TBranch        *b_NL1CenJet;   //!
   TBranch        *b_L1CenJetEt;   //!
   TBranch        *b_L1CenJetE;   //!
   TBranch        *b_L1CenJetEta;   //!
   TBranch        *b_L1CenJetPhi;   //!
   TBranch        *b_NL1ForJet;   //!
   TBranch        *b_L1ForJetEt;   //!
   TBranch        *b_L1ForJetE;   //!
   TBranch        *b_L1ForJetEta;   //!
   TBranch        *b_L1ForJetPhi;   //!
   TBranch        *b_NL1Tau;   //!
   TBranch        *b_L1TauEt;   //!
   TBranch        *b_L1TauE;   //!
   TBranch        *b_L1TauEta;   //!
   TBranch        *b_L1TauPhi;   //!
   TBranch        *b_L1Met;   //!
   TBranch        *b_L1MetPhi;   //!
   TBranch        *b_L1EtTot;   //!
   TBranch        *b_L1Mht;   //!
   TBranch        *b_L1MhtPhi;   //!
   TBranch        *b_L1EtHad;   //!
   TBranch        *b_L1HfRing1EtSumPositiveEta;   //!
   TBranch        *b_L1HfRing2EtSumPositiveEta;   //!
   TBranch        *b_L1HfRing1EtSumNegativeEta;   //!
   TBranch        *b_L1HfRing2EtSumNegativeEta;   //!
   TBranch        *b_L1HfTowerCountPositiveEtaRing1;   //!
   TBranch        *b_L1HfTowerCountNegativeEtaRing1;   //!
   TBranch        *b_L1HfTowerCountPositiveEtaRing2;   //!
   TBranch        *b_L1HfTowerCountNegativeEtaRing2;   //!
   TBranch        *b_NVrtx;   //!
   TBranch        *b_recoVrtXHLT;   //!
   TBranch        *b_recoVrtYHLT;   //!
   TBranch        *b_recoVrtZHLT;   //!
   TBranch        *b_recoVrtNtrkHLT;   //!
   TBranch        *b_recoVrtChi2HLT;   //!
   TBranch        *b_recoVrtNdofHLT;   //!
   TBranch        *b_recoVrtXOffline0;   //!
   TBranch        *b_recoVrtYOffline0;   //!
   TBranch        *b_recoVrtZOffline0;   //!
   TBranch        *b_recoVrtNtrkOffline0;   //!
   TBranch        *b_recoVrtChi2Offline0;   //!
   TBranch        *b_recoVrtNdofOffline0;   //!
   TBranch        *b_Npart;   //!
   TBranch        *b_Ncoll;   //!
   TBranch        *b_Nhard;   //!
   TBranch        *b_NPhi0;   //!
   TBranch        *b_b;   //!
   TBranch        *b_Ncharged;   //!
   TBranch        *b_NchargedMR;   //!
   TBranch        *b_MeanPt;   //!
   TBranch        *b_MeanPtMR;   //!
   TBranch        *b_EtMR;   //!
   TBranch        *b_NchargedPtCut;   //!
   TBranch        *b_NchargedPtCutMR;   //!
   TBranch        *b_hiBin;   //!
   TBranch        *b_hiHF;   //!
   TBranch        *b_hiHFplus;   //!
   TBranch        *b_hiHFminus;   //!
   TBranch        *b_hiZDC;   //!
   TBranch        *b_hiZDCplus;   //!
   TBranch        *b_hiZDCminus;   //!
   TBranch        *b_hiHFhit;   //!
   TBranch        *b_hiHFhitPlus;   //!
   TBranch        *b_hiHFhitMinus;   //!
   TBranch        *b_hiET;   //!
   TBranch        *b_hiEE;   //!
   TBranch        *b_hiEB;   //!
   TBranch        *b_hiEEplus;   //!
   TBranch        *b_hiEEminus;   //!
   TBranch        *b_hiNpix;   //!
   TBranch        *b_hiNpixelTracks;   //!
   TBranch        *b_hiNtracks;   //!
   TBranch        *b_hiNevtPlane;   //!
   TBranch        *b_hiEvtPlanes;   //!
   TBranch        *b_hiNtracksPtCut;   //!
   TBranch        *b_hiNtracksEtaCut;   //!
   TBranch        *b_hiNtracksEtaPtCut;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_LumiBlock;   //!
   TBranch        *b_Bx;   //!
   TBranch        *b_Orbit;   //!
   TBranch        *b_AvgInstDelLumi;   //!
   TBranch        *b_AlCa_EcalPhiSym_v2;   //!
   TBranch        *b_AlCa_EcalPhiSym_v2_Prescl;   //!
   TBranch        *b_AlCa_EcalEta_v3;   //!
   TBranch        *b_AlCa_EcalEta_v3_Prescl;   //!
   TBranch        *b_AlCa_EcalPi0_v4;   //!
   TBranch        *b_AlCa_EcalPi0_v4_Prescl;   //!
   TBranch        *b_AlCa_RPCMuonNoHits_v2;   //!
   TBranch        *b_AlCa_RPCMuonNoHits_v2_Prescl;   //!
   TBranch        *b_AlCa_RPCMuonNoTriggers_v2;   //!
   TBranch        *b_AlCa_RPCMuonNoTriggers_v2_Prescl;   //!
   TBranch        *b_AlCa_RPCMuonNormalisation_v2;   //!
   TBranch        *b_AlCa_RPCMuonNormalisation_v2_Prescl;   //!
   TBranch        *b_HLT_BeamGas_BSC_v2;   //!
   TBranch        *b_HLT_BeamGas_BSC_v2_Prescl;   //!
   TBranch        *b_HLT_BeamGas_HF_v2;   //!
   TBranch        *b_HLT_BeamGas_HF_v2_Prescl;   //!
   TBranch        *b_HLT_BeamHalo_v2;   //!
   TBranch        *b_HLT_BeamHalo_v2_Prescl;   //!
   TBranch        *b_HLT_Calibration_v1;   //!
   TBranch        *b_HLT_Calibration_v1_Prescl;   //!
   TBranch        *b_HLT_DTErrors_v1;   //!
   TBranch        *b_HLT_DTErrors_v1_Prescl;   //!
   TBranch        *b_HLT_DoubleMu3_v3;   //!
   TBranch        *b_HLT_DoubleMu3_v3_Prescl;   //!
   TBranch        *b_HLT_EcalCalibration_v1;   //!
   TBranch        *b_HLT_EcalCalibration_v1_Prescl;   //!
   TBranch        *b_HLT_Ele8_v2;   //!
   TBranch        *b_HLT_Ele8_v2_Prescl;   //!
   TBranch        *b_HLT_GlobalRunHPDNoise_v2;   //!
   TBranch        *b_HLT_GlobalRunHPDNoise_v2_Prescl;   //!
   TBranch        *b_HLT_HcalCalibration_v1;   //!
   TBranch        *b_HLT_HcalCalibration_v1_Prescl;   //!
   TBranch        *b_HLT_HcalNZS_v3;   //!
   TBranch        *b_HLT_HcalNZS_v3_Prescl;   //!
   TBranch        *b_HLT_HcalPhiSym_v3;   //!
   TBranch        *b_HLT_HcalPhiSym_v3_Prescl;   //!
   TBranch        *b_HLT_IsoTrackHB_v2;   //!
   TBranch        *b_HLT_IsoTrackHB_v2_Prescl;   //!
   TBranch        *b_HLT_IsoTrackHE_v3;   //!
   TBranch        *b_HLT_IsoTrackHE_v3_Prescl;   //!
   TBranch        *b_HLT_Jet20_v1;   //!
   TBranch        *b_HLT_Jet20_v1_Prescl;   //!
   TBranch        *b_HLT_Jet40_v1;   //!
   TBranch        *b_HLT_Jet40_v1_Prescl;   //!
   TBranch        *b_HLT_Jet60_v1;   //!
   TBranch        *b_HLT_Jet60_v1_Prescl;   //!
   TBranch        *b_HLT_L1DoubleForJet32_EtaOpp_v1;   //!
   TBranch        *b_HLT_L1DoubleForJet32_EtaOpp_v1_Prescl;   //!
   TBranch        *b_HLT_L1DoubleForJet8_EtaOpp_v1;   //!
   TBranch        *b_HLT_L1DoubleForJet8_EtaOpp_v1_Prescl;   //!
   TBranch        *b_HLT_L1DoubleMu0_v1;   //!
   TBranch        *b_HLT_L1DoubleMu0_v1_Prescl;   //!
   TBranch        *b_HLT_L1SingleEG12_v1;   //!
   TBranch        *b_HLT_L1SingleEG12_v1_Prescl;   //!
   TBranch        *b_HLT_L1SingleEG5_v1;   //!
   TBranch        *b_HLT_L1SingleEG5_v1_Prescl;   //!
   TBranch        *b_HLT_L1SingleJet36_v1;   //!
   TBranch        *b_HLT_L1SingleJet36_v1_Prescl;   //!
   TBranch        *b_HLT_L1SingleMuOpen_AntiBPTX_v1;   //!
   TBranch        *b_HLT_L1SingleMuOpen_AntiBPTX_v1_Prescl;   //!
   TBranch        *b_HLT_L1SingleMuOpen_DT_v1;   //!
   TBranch        *b_HLT_L1SingleMuOpen_DT_v1_Prescl;   //!
   TBranch        *b_HLT_L1SingleMuOpen_v1;   //!
   TBranch        *b_HLT_L1SingleMuOpen_v1_Prescl;   //!
   TBranch        *b_HLT_L1Tech_BSC_halo_v1;   //!
   TBranch        *b_HLT_L1Tech_BSC_halo_v1_Prescl;   //!
   TBranch        *b_HLT_L1Tech_HBHEHO_totalOR_v1;   //!
   TBranch        *b_HLT_L1Tech_HBHEHO_totalOR_v1_Prescl;   //!
   TBranch        *b_HLT_L1TrackerCosmics_v2;   //!
   TBranch        *b_HLT_L1TrackerCosmics_v2_Prescl;   //!
   TBranch        *b_HLT_L1_Interbunch_BSC_v1;   //!
   TBranch        *b_HLT_L1_Interbunch_BSC_v1_Prescl;   //!
   TBranch        *b_HLT_L1_PreCollisions_v1;   //!
   TBranch        *b_HLT_L1_PreCollisions_v1_Prescl;   //!
   TBranch        *b_HLT_L2DoubleMu0_v2;   //!
   TBranch        *b_HLT_L2DoubleMu0_v2_Prescl;   //!
   TBranch        *b_HLT_L3MuonsCosmicTracking_v1;   //!
   TBranch        *b_HLT_L3MuonsCosmicTracking_v1_Prescl;   //!
   TBranch        *b_HLT_LogMonitor_v1;   //!
   TBranch        *b_HLT_LogMonitor_v1_Prescl;   //!
   TBranch        *b_HLT_L1BscMinBiasORBptxPlusANDMinus_v1;   //!
   TBranch        *b_HLT_L1BscMinBiasORBptxPlusANDMinus_v1_Prescl;   //!
   TBranch        *b_HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1;   //!
   TBranch        *b_HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1_Prescl;   //!
   TBranch        *b_HLT_Mu0_v3;   //!
   TBranch        *b_HLT_Mu0_v3_Prescl;   //!
   TBranch        *b_HLT_Mu3_v3;   //!
   TBranch        *b_HLT_Mu3_v3_Prescl;   //!
   TBranch        *b_HLT_Mu5_v3;   //!
   TBranch        *b_HLT_Mu5_v3_Prescl;   //!
   TBranch        *b_HLT_Photon10_CaloIdVL_v1;   //!
   TBranch        *b_HLT_Photon10_CaloIdVL_v1_Prescl;   //!
   TBranch        *b_HLT_Photon15_CaloIdVL_v1;   //!
   TBranch        *b_HLT_Photon15_CaloIdVL_v1_Prescl;   //!
   TBranch        *b_HLT_Physics_NanoDST_v1;   //!
   TBranch        *b_HLT_Physics_NanoDST_v1_Prescl;   //!
   TBranch        *b_HLT_PixelTracks_Multiplicity50_Loose;   //!
   TBranch        *b_HLT_PixelTracks_Multiplicity50_Loose_Prescl;   //!
   TBranch        *b_HLT_PixelTracks_Multiplicity60_Loose;   //!
   TBranch        *b_HLT_PixelTracks_Multiplicity60_Loose_Prescl;   //!
   TBranch        *b_HLT_PixelTracks_Multiplicity70_Loose;   //!
   TBranch        *b_HLT_PixelTracks_Multiplicity70_Loose_Prescl;   //!
   TBranch        *b_HLT_Random_v1;   //!
   TBranch        *b_HLT_Random_v1_Prescl;   //!
   TBranch        *b_HLT_RegionalCosmicTracking_v1;   //!
   TBranch        *b_HLT_RegionalCosmicTracking_v1_Prescl;   //!
   TBranch        *b_HLT_TrackerCalibration_v1;   //!
   TBranch        *b_HLT_TrackerCalibration_v1_Prescl;   //!
   TBranch        *b_HLT_ZeroBiasPixel_SingleTrack_v1;   //!
   TBranch        *b_HLT_ZeroBiasPixel_SingleTrack_v1_Prescl;   //!
   TBranch        *b_HLT_ZeroBias_v1;   //!
   TBranch        *b_HLT_ZeroBias_v1_Prescl;   //!
   TBranch        *b_HLTriggerFinalPath;   //!
   TBranch        *b_HLTriggerFinalPath_Prescl;   //!
   TBranch        *b_L1_BeamGas_Bsc;   //!
   TBranch        *b_L1_BeamGas_Bsc_Prescl;   //!
   TBranch        *b_L1_BeamGas_Hf;   //!
   TBranch        *b_L1_BeamGas_Hf_Prescl;   //!
   TBranch        *b_L1_BeamHalo;   //!
   TBranch        *b_L1_BeamHalo_Prescl;   //!
   TBranch        *b_L1_BptxMinus_NotBptxPlus;   //!
   TBranch        *b_L1_BptxMinus_NotBptxPlus_Prescl;   //!
   TBranch        *b_L1_BptxPlusANDMinus;   //!
   TBranch        *b_L1_BptxPlusANDMinus_Prescl;   //!
   TBranch        *b_L1_BptxPlus_NotBptxMinus;   //!
   TBranch        *b_L1_BptxPlus_NotBptxMinus_Prescl;   //!
   TBranch        *b_L1_Bsc2Minus_BptxMinus;   //!
   TBranch        *b_L1_Bsc2Minus_BptxMinus_Prescl;   //!
   TBranch        *b_L1_Bsc2Plus_BptxPlus;   //!
   TBranch        *b_L1_Bsc2Plus_BptxPlus_Prescl;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxPlusANDMinus;   //!
   TBranch        *b_L1_BscMinBiasOR_BptxPlusANDMinus_Prescl;   //!
   TBranch        *b_L1_DoubleEG10;   //!
   TBranch        *b_L1_DoubleEG10_Prescl;   //!
   TBranch        *b_L1_DoubleEG2_FwdVeto;   //!
   TBranch        *b_L1_DoubleEG2_FwdVeto_Prescl;   //!
   TBranch        *b_L1_DoubleEG3;   //!
   TBranch        *b_L1_DoubleEG3_Prescl;   //!
   TBranch        *b_L1_DoubleEG5;   //!
   TBranch        *b_L1_DoubleEG5_Prescl;   //!
   TBranch        *b_L1_DoubleEG5_HTT50;   //!
   TBranch        *b_L1_DoubleEG5_HTT50_Prescl;   //!
   TBranch        *b_L1_DoubleEG5_HTT75;   //!
   TBranch        *b_L1_DoubleEG5_HTT75_Prescl;   //!
   TBranch        *b_L1_DoubleEG8;   //!
   TBranch        *b_L1_DoubleEG8_Prescl;   //!
   TBranch        *b_L1_DoubleEG_12_5;   //!
   TBranch        *b_L1_DoubleEG_12_5_Prescl;   //!
   TBranch        *b_L1_DoubleEG_12_5_Eta1p39;   //!
   TBranch        *b_L1_DoubleEG_12_5_Eta1p39_Prescl;   //!
   TBranch        *b_L1_DoubleForJet32_EtaOpp;   //!
   TBranch        *b_L1_DoubleForJet32_EtaOpp_Prescl;   //!
   TBranch        *b_L1_DoubleForJet44_EtaOpp;   //!
   TBranch        *b_L1_DoubleForJet44_EtaOpp_Prescl;   //!
   TBranch        *b_L1_DoubleForJet8_EtaOpp;   //!
   TBranch        *b_L1_DoubleForJet8_EtaOpp_Prescl;   //!
   TBranch        *b_L1_DoubleIsoEG10;   //!
   TBranch        *b_L1_DoubleIsoEG10_Prescl;   //!
   TBranch        *b_L1_DoubleJet36_Central;   //!
   TBranch        *b_L1_DoubleJet36_Central_Prescl;   //!
   TBranch        *b_L1_DoubleJet44_Central;   //!
   TBranch        *b_L1_DoubleJet44_Central_Prescl;   //!
   TBranch        *b_L1_DoubleJet52;   //!
   TBranch        *b_L1_DoubleJet52_Prescl;   //!
   TBranch        *b_L1_DoubleMu0;   //!
   TBranch        *b_L1_DoubleMu0_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_HighQ;   //!
   TBranch        *b_L1_DoubleMu0_HighQ_Prescl;   //!
   TBranch        *b_L1_DoubleMu0_HighQ_EtaCuts;   //!
   TBranch        *b_L1_DoubleMu0_HighQ_EtaCuts_Prescl;   //!
   TBranch        *b_L1_DoubleMu3;   //!
   TBranch        *b_L1_DoubleMu3_Prescl;   //!
   TBranch        *b_L1_DoubleMu3_EG5;   //!
   TBranch        *b_L1_DoubleMu3_EG5_Prescl;   //!
   TBranch        *b_L1_DoubleMu3p5;   //!
   TBranch        *b_L1_DoubleMu3p5_Prescl;   //!
   TBranch        *b_L1_DoubleMu5_v1;   //!
   TBranch        *b_L1_DoubleMu5_v1_Prescl;   //!
   TBranch        *b_L1_DoubleTauJet28;   //!
   TBranch        *b_L1_DoubleTauJet28_Prescl;   //!
   TBranch        *b_L1_DoubleTauJet32;   //!
   TBranch        *b_L1_DoubleTauJet32_Prescl;   //!
   TBranch        *b_L1_DoubleTauJet36;   //!
   TBranch        *b_L1_DoubleTauJet36_Prescl;   //!
   TBranch        *b_L1_DoubleTauJet40;   //!
   TBranch        *b_L1_DoubleTauJet40_Prescl;   //!
   TBranch        *b_L1_EG10_Jet24_Central_deltaPhi1;   //!
   TBranch        *b_L1_EG10_Jet24_Central_deltaPhi1_Prescl;   //!
   TBranch        *b_L1_EG12_Jet24_Central_deltaPhi1;   //!
   TBranch        *b_L1_EG12_Jet24_Central_deltaPhi1_Prescl;   //!
   TBranch        *b_L1_EG12_TauJet20_deltaPhi1;   //!
   TBranch        *b_L1_EG12_TauJet20_deltaPhi1_Prescl;   //!
   TBranch        *b_L1_EG5_HTT100;   //!
   TBranch        *b_L1_EG5_HTT100_Prescl;   //!
   TBranch        *b_L1_EG5_HTT125;   //!
   TBranch        *b_L1_EG5_HTT125_Prescl;   //!
   TBranch        *b_L1_EG5_HTT75;   //!
   TBranch        *b_L1_EG5_HTT75_Prescl;   //!
   TBranch        *b_L1_EG5_Jet36_deltaPhi1;   //!
   TBranch        *b_L1_EG5_Jet36_deltaPhi1_Prescl;   //!
   TBranch        *b_L1_EG8_Jet20_Central_deltaPhi1;   //!
   TBranch        *b_L1_EG8_Jet20_Central_deltaPhi1_Prescl;   //!
   TBranch        *b_L1_ETM100;   //!
   TBranch        *b_L1_ETM100_Prescl;   //!
   TBranch        *b_L1_ETM20;   //!
   TBranch        *b_L1_ETM20_Prescl;   //!
   TBranch        *b_L1_ETM30;   //!
   TBranch        *b_L1_ETM30_Prescl;   //!
   TBranch        *b_L1_ETM50;   //!
   TBranch        *b_L1_ETM50_Prescl;   //!
   TBranch        *b_L1_ETM70;   //!
   TBranch        *b_L1_ETM70_Prescl;   //!
   TBranch        *b_L1_ETT20;   //!
   TBranch        *b_L1_ETT20_Prescl;   //!
   TBranch        *b_L1_ETT40;   //!
   TBranch        *b_L1_ETT40_Prescl;   //!
   TBranch        *b_L1_ETT60;   //!
   TBranch        *b_L1_ETT60_Prescl;   //!
   TBranch        *b_L1_HTM50;   //!
   TBranch        *b_L1_HTM50_Prescl;   //!
   TBranch        *b_L1_HTT100;   //!
   TBranch        *b_L1_HTT100_Prescl;   //!
   TBranch        *b_L1_HTT150;   //!
   TBranch        *b_L1_HTT150_Prescl;   //!
   TBranch        *b_L1_HTT50;   //!
   TBranch        *b_L1_HTT50_Prescl;   //!
   TBranch        *b_L1_HTT50_HTM30;   //!
   TBranch        *b_L1_HTT50_HTM30_Prescl;   //!
   TBranch        *b_L1_HTT50_HTM50;   //!
   TBranch        *b_L1_HTT50_HTM50_Prescl;   //!
   TBranch        *b_L1_HTT75;   //!
   TBranch        *b_L1_HTT75_Prescl;   //!
   TBranch        *b_L1_InterBunch_Bsc;   //!
   TBranch        *b_L1_InterBunch_Bsc_Prescl;   //!
   TBranch        *b_L1_InterBunch_Hf;   //!
   TBranch        *b_L1_InterBunch_Hf_Prescl;   //!
   TBranch        *b_L1_Mu0_HTT50;   //!
   TBranch        *b_L1_Mu0_HTT50_Prescl;   //!
   TBranch        *b_L1_Mu0_HTT75;   //!
   TBranch        *b_L1_Mu0_HTT75_Prescl;   //!
   TBranch        *b_L1_Mu10_Jet36_Central;   //!
   TBranch        *b_L1_Mu10_Jet36_Central_Prescl;   //!
   TBranch        *b_L1_Mu12_EG5;   //!
   TBranch        *b_L1_Mu12_EG5_Prescl;   //!
   TBranch        *b_L1_Mu3_DoubleEG5;   //!
   TBranch        *b_L1_Mu3_DoubleEG5_Prescl;   //!
   TBranch        *b_L1_Mu3_EG5;   //!
   TBranch        *b_L1_Mu3_EG5_Prescl;   //!
   TBranch        *b_L1_Mu3_Jet16_Central;   //!
   TBranch        *b_L1_Mu3_Jet16_Central_Prescl;   //!
   TBranch        *b_L1_Mu3_Jet20_Central;   //!
   TBranch        *b_L1_Mu3_Jet20_Central_Prescl;   //!
   TBranch        *b_L1_Mu3_Jet28_Central;   //!
   TBranch        *b_L1_Mu3_Jet28_Central_Prescl;   //!
   TBranch        *b_L1_Mu5_EG12;   //!
   TBranch        *b_L1_Mu5_EG12_Prescl;   //!
   TBranch        *b_L1_Mu7_EG5;   //!
   TBranch        *b_L1_Mu7_EG5_Prescl;   //!
   TBranch        *b_L1_Mu7_Jet20_Central;   //!
   TBranch        *b_L1_Mu7_Jet20_Central_Prescl;   //!
   TBranch        *b_L1_Mu7_TauJet16;   //!
   TBranch        *b_L1_Mu7_TauJet16_Prescl;   //!
   TBranch        *b_L1_MuOpen_EG12;   //!
   TBranch        *b_L1_MuOpen_EG12_Prescl;   //!
   TBranch        *b_L1_MuOpen_EG5;   //!
   TBranch        *b_L1_MuOpen_EG5_Prescl;   //!
   TBranch        *b_L1_PreCollisions;   //!
   TBranch        *b_L1_PreCollisions_Prescl;   //!
   TBranch        *b_L1_QuadJet20_Central;   //!
   TBranch        *b_L1_QuadJet20_Central_Prescl;   //!
   TBranch        *b_L1_QuadJet28_Central;   //!
   TBranch        *b_L1_QuadJet28_Central_Prescl;   //!
   TBranch        *b_L1_SingleEG12;   //!
   TBranch        *b_L1_SingleEG12_Prescl;   //!
   TBranch        *b_L1_SingleEG12_Eta1p39;   //!
   TBranch        *b_L1_SingleEG12_Eta1p39_Prescl;   //!
   TBranch        *b_L1_SingleEG12_Eta2p17;   //!
   TBranch        *b_L1_SingleEG12_Eta2p17_Prescl;   //!
   TBranch        *b_L1_SingleEG15;   //!
   TBranch        *b_L1_SingleEG15_Prescl;   //!
   TBranch        *b_L1_SingleEG20;   //!
   TBranch        *b_L1_SingleEG20_Prescl;   //!
   TBranch        *b_L1_SingleEG30;   //!
   TBranch        *b_L1_SingleEG30_Prescl;   //!
   TBranch        *b_L1_SingleEG5;   //!
   TBranch        *b_L1_SingleEG5_Prescl;   //!
   TBranch        *b_L1_SingleIsoEG12;   //!
   TBranch        *b_L1_SingleIsoEG12_Prescl;   //!
   TBranch        *b_L1_SingleIsoEG12_Eta1p39;   //!
   TBranch        *b_L1_SingleIsoEG12_Eta1p39_Prescl;   //!
   TBranch        *b_L1_SingleIsoEG12_Eta2p17;   //!
   TBranch        *b_L1_SingleIsoEG12_Eta2p17_Prescl;   //!
   TBranch        *b_L1_SingleJet16;   //!
   TBranch        *b_L1_SingleJet16_Prescl;   //!
   TBranch        *b_L1_SingleJet20_NotBptxOR;   //!
   TBranch        *b_L1_SingleJet20_NotBptxOR_Prescl;   //!
   TBranch        *b_L1_SingleJet20_NotBptxOR_NotMuBeamHalo;   //!
   TBranch        *b_L1_SingleJet20_NotBptxOR_NotMuBeamHalo_Prescl;   //!
   TBranch        *b_L1_SingleJet32_NotBptxOR_NotMuBeamHalo;   //!
   TBranch        *b_L1_SingleJet32_NotBptxOR_NotMuBeamHalo_Prescl;   //!
   TBranch        *b_L1_SingleJet36;   //!
   TBranch        *b_L1_SingleJet36_Prescl;   //!
   TBranch        *b_L1_SingleJet36_FwdVeto;   //!
   TBranch        *b_L1_SingleJet36_FwdVeto_Prescl;   //!
   TBranch        *b_L1_SingleJet52;   //!
   TBranch        *b_L1_SingleJet52_Prescl;   //!
   TBranch        *b_L1_SingleJet68;   //!
   TBranch        *b_L1_SingleJet68_Prescl;   //!
   TBranch        *b_L1_SingleJet8;   //!
   TBranch        *b_L1_SingleJet8_Prescl;   //!
   TBranch        *b_L1_SingleJet80_Central;   //!
   TBranch        *b_L1_SingleJet80_Central_Prescl;   //!
   TBranch        *b_L1_SingleJet92;   //!
   TBranch        *b_L1_SingleJet92_Prescl;   //!
   TBranch        *b_L1_SingleJet92_Central;   //!
   TBranch        *b_L1_SingleJet92_Central_Prescl;   //!
   TBranch        *b_L1_SingleMu10;   //!
   TBranch        *b_L1_SingleMu10_Prescl;   //!
   TBranch        *b_L1_SingleMu12;   //!
   TBranch        *b_L1_SingleMu12_Prescl;   //!
   TBranch        *b_L1_SingleMu12_Debug;   //!
   TBranch        *b_L1_SingleMu12_Debug_Prescl;   //!
   TBranch        *b_L1_SingleMu16;   //!
   TBranch        *b_L1_SingleMu16_Prescl;   //!
   TBranch        *b_L1_SingleMu20;   //!
   TBranch        *b_L1_SingleMu20_Prescl;   //!
   TBranch        *b_L1_SingleMu25;   //!
   TBranch        *b_L1_SingleMu25_Prescl;   //!
   TBranch        *b_L1_SingleMu3;   //!
   TBranch        *b_L1_SingleMu3_Prescl;   //!
   TBranch        *b_L1_SingleMu5_Eta1p5_Q80_v1;   //!
   TBranch        *b_L1_SingleMu5_Eta1p5_Q80_v1_Prescl;   //!
   TBranch        *b_L1_SingleMu7;   //!
   TBranch        *b_L1_SingleMu7_Prescl;   //!
   TBranch        *b_L1_SingleMu7_Barrel;   //!
   TBranch        *b_L1_SingleMu7_Barrel_Prescl;   //!
   TBranch        *b_L1_SingleMu7_Eta2p1;   //!
   TBranch        *b_L1_SingleMu7_Eta2p1_Prescl;   //!
   TBranch        *b_L1_SingleMuBeamHalo;   //!
   TBranch        *b_L1_SingleMuBeamHalo_Prescl;   //!
   TBranch        *b_L1_SingleMuOpen;   //!
   TBranch        *b_L1_SingleMuOpen_Prescl;   //!
   TBranch        *b_L1_SingleTauJet52;   //!
   TBranch        *b_L1_SingleTauJet52_Prescl;   //!
   TBranch        *b_L1_SingleTauJet68;   //!
   TBranch        *b_L1_SingleTauJet68_Prescl;   //!
   TBranch        *b_L1_SingleTauJet80;   //!
   TBranch        *b_L1_SingleTauJet80_Prescl;   //!
   TBranch        *b_L1_TripleEG5;   //!
   TBranch        *b_L1_TripleEG5_Prescl;   //!
   TBranch        *b_L1_TripleEG7;   //!
   TBranch        *b_L1_TripleEG7_Prescl;   //!
   TBranch        *b_L1_TripleEG_8_5_5;   //!
   TBranch        *b_L1_TripleEG_8_5_5_Prescl;   //!
   TBranch        *b_L1_TripleEG_8_8_5;   //!
   TBranch        *b_L1_TripleEG_8_8_5_Prescl;   //!
   TBranch        *b_L1_TripleJet28_Central;   //!
   TBranch        *b_L1_TripleJet28_Central_Prescl;   //!
   TBranch        *b_L1_ZeroBias;   //!
   TBranch        *b_L1_ZeroBias_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_minus_AND_not_plus_v0;   //!
   TBranch        *b_L1Tech_BPTX_minus_AND_not_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_NOT_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_instance1_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_plus_OR_minus_v0;   //!
   TBranch        *b_L1Tech_BPTX_plus_OR_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_BPTX_quiet_v0;   //!
   TBranch        *b_L1Tech_BPTX_quiet_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_HighMultiplicity_v0;   //!
   TBranch        *b_L1Tech_BSC_HighMultiplicity_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_inner_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_inner_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_outer_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam1_outer_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_inner_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_inner_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_outer_v0;   //!
   TBranch        *b_L1Tech_BSC_halo_beam2_outer_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_OR_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_OR_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold1_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold2_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_inner_threshold2_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold1_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold2_v0;   //!
   TBranch        *b_L1Tech_BSC_minBias_threshold2_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_splash_beam1_v0;   //!
   TBranch        *b_L1Tech_BSC_splash_beam1_v0_Prescl;   //!
   TBranch        *b_L1Tech_BSC_splash_beam2_v0;   //!
   TBranch        *b_L1Tech_BSC_splash_beam2_v0_Prescl;   //!
   TBranch        *b_L1Tech_CASTOR_HaloMuon_v0;   //!
   TBranch        *b_L1Tech_CASTOR_HaloMuon_v0_Prescl;   //!
   TBranch        *b_L1Tech_DT_GlobalOR_v0;   //!
   TBranch        *b_L1Tech_DT_GlobalOR_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HBHE_totalOR_v0;   //!
   TBranch        *b_L1Tech_HCAL_HBHE_totalOR_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HF_MMP_or_MPP_v0;   //!
   TBranch        *b_L1Tech_HCAL_HF_MMP_or_MPP_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HF_MM_or_PP_or_PM_v0;   //!
   TBranch        *b_L1Tech_HCAL_HF_MM_or_PP_or_PM_v0_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HF_coincidence_PM_v1;   //!
   TBranch        *b_L1Tech_HCAL_HF_coincidence_PM_v1_Prescl;   //!
   TBranch        *b_L1Tech_HCAL_HO_totalOR_v0;   //!
   TBranch        *b_L1Tech_HCAL_HO_totalOR_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RB0_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBst1_collisions_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_barrel_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_RPC_TTU_pointing_Cosmics_v0;   //!
   TBranch        *b_L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_loose_vertex_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_loose_vertex_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_minus_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_minus_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_plus_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_plus_v0_Prescl;   //!
   TBranch        *b_L1Tech_ZDC_Scint_tight_vertex_v0;   //!
   TBranch        *b_L1Tech_ZDC_Scint_tight_vertex_v0_Prescl;   //!

   HLT(TTree *tree=0);
   virtual ~HLT();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HLT_cxx
HLT::HLT(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
/*   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Volumes/WORKDISK/backup/pc93/2012-01-26/WorkSpace/data/HI2011/forest/merged_pp2760_AllPhysics_Part_Prod03.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Volumes/WORKDISK/backup/pc93/2012-01-26/WorkSpace/data/HI2011/forest/merged_pp2760_AllPhysics_Part_Prod03.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/Volumes/WORKDISK/backup/pc93/2012-01-26/WorkSpace/data/HI2011/forest/merged_pp2760_AllPhysics_Part_Prod03.root:/hltanalysis");
      dir->GetObject("HltTree",tree);

   }*/
   Init(tree);
}

HLT::~HLT()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HLT::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HLT::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HLT::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("NohBJetL2", &NohBJetL2, &b_NohBJetL2);
   fChain->SetBranchAddress("ohBJetL2Energy", &ohBJetL2Energy, &b_ohBJetL2Energy);
   fChain->SetBranchAddress("ohBJetL2Et", &ohBJetL2Et, &b_ohBJetL2Et);
   fChain->SetBranchAddress("ohBJetL2Pt", &ohBJetL2Pt, &b_ohBJetL2Pt);
   fChain->SetBranchAddress("ohBJetL2Eta", &ohBJetL2Eta, &b_ohBJetL2Eta);
   fChain->SetBranchAddress("ohBJetL2Phi", &ohBJetL2Phi, &b_ohBJetL2Phi);
   fChain->SetBranchAddress("NohBJetL2Corrected", &NohBJetL2Corrected, &b_NohBJetL2Corrected);
   fChain->SetBranchAddress("ohBJetL2CorrectedEnergy", &ohBJetL2CorrectedEnergy, &b_ohBJetL2CorrectedEnergy);
   fChain->SetBranchAddress("ohBJetL2CorrectedEt", &ohBJetL2CorrectedEt, &b_ohBJetL2CorrectedEt);
   fChain->SetBranchAddress("ohBJetL2CorrectedPt", &ohBJetL2CorrectedPt, &b_ohBJetL2CorrectedPt);
   fChain->SetBranchAddress("ohBJetL2CorrectedEta", &ohBJetL2CorrectedEta, &b_ohBJetL2CorrectedEta);
   fChain->SetBranchAddress("ohBJetL2CorrectedPhi", &ohBJetL2CorrectedPhi, &b_ohBJetL2CorrectedPhi);
   fChain->SetBranchAddress("ohBJetIPL25Tag", &ohBJetIPL25Tag, &b_ohBJetIPL25Tag);
   fChain->SetBranchAddress("ohBJetIPL3Tag", &ohBJetIPL3Tag, &b_ohBJetIPL3Tag);
   fChain->SetBranchAddress("ohBJetIPL25TagSingleTrack", &ohBJetIPL25TagSingleTrack, &b_ohBJetIPL25TagSingleTrack);
   fChain->SetBranchAddress("ohBJetIPL3TagSingleTrack", &ohBJetIPL3TagSingleTrack, &b_ohBJetIPL3TagSingleTrack);
   fChain->SetBranchAddress("ohBJetPerfL25Tag", &ohBJetPerfL25Tag, &b_ohBJetPerfL25Tag);
   fChain->SetBranchAddress("ohBJetPerfL3Tag", &ohBJetPerfL3Tag, &b_ohBJetPerfL3Tag);
   fChain->SetBranchAddress("NrecoElec", &NrecoElec, &b_NrecoElec);
   fChain->SetBranchAddress("recoElecPt", recoElecPt, &b_recoElecPt);
   fChain->SetBranchAddress("recoElecPhi", recoElecPhi, &b_recoElecPhi);
   fChain->SetBranchAddress("recoElecEta", recoElecEta, &b_recoElecEta);
   fChain->SetBranchAddress("recoElecEt", recoElecEt, &b_recoElecEt);
   fChain->SetBranchAddress("recoElecE", recoElecE, &b_recoElecE);
   fChain->SetBranchAddress("recoElecEleID", recoElecEleID, &b_recoElecEleID);
   fChain->SetBranchAddress("recoElecIP", recoElecIP, &b_recoElecIP);
   fChain->SetBranchAddress("recoElecNLostHits", recoElecNLostHits, &b_recoElecNLostHits);
   fChain->SetBranchAddress("recoElecChi2NDF", recoElecChi2NDF, &b_recoElecChi2NDF);
   fChain->SetBranchAddress("recoElecTrkIsoR03", recoElecTrkIsoR03, &b_recoElecTrkIsoR03);
   fChain->SetBranchAddress("recoElecECaloIsoR03", recoElecECaloIsoR03, &b_recoElecECaloIsoR03);
   fChain->SetBranchAddress("recoElecHCaloIsoR03", recoElecHCaloIsoR03, &b_recoElecHCaloIsoR03);
   fChain->SetBranchAddress("recoElecIsEcalDriven", recoElecIsEcalDriven, &b_recoElecIsEcalDriven);
   fChain->SetBranchAddress("recoElecFbrem", recoElecFbrem, &b_recoElecFbrem);
   fChain->SetBranchAddress("recoElecmishits", recoElecmishits, &b_recoElecmishits);
   fChain->SetBranchAddress("recoElecdist", recoElecdist, &b_recoElecdist);
   fChain->SetBranchAddress("recoElecdcot", recoElecdcot, &b_recoElecdcot);
   fChain->SetBranchAddress("recoElectrkiso", recoElectrkiso, &b_recoElectrkiso);
   fChain->SetBranchAddress("recoElececaliso", recoElececaliso, &b_recoElececaliso);
   fChain->SetBranchAddress("recoElechcaliso", recoElechcaliso, &b_recoElechcaliso);
   fChain->SetBranchAddress("recoElecsigmaietaieta", recoElecsigmaietaieta, &b_recoElecsigmaietaieta);
   fChain->SetBranchAddress("recoElecdeltaPhiIn", recoElecdeltaPhiIn, &b_recoElecdeltaPhiIn);
   fChain->SetBranchAddress("recoElecdeltaEtaIn", recoElecdeltaEtaIn, &b_recoElecdeltaEtaIn);
   fChain->SetBranchAddress("recoElechOverE", recoElechOverE, &b_recoElechOverE);
   fChain->SetBranchAddress("recoElecscEt", recoElecscEt, &b_recoElecscEt);
   fChain->SetBranchAddress("recoElecd0corr", recoElecd0corr, &b_recoElecd0corr);
   fChain->SetBranchAddress("recoElecqGsfCtfScPixConsistent", recoElecqGsfCtfScPixConsistent, &b_recoElecqGsfCtfScPixConsistent);
   fChain->SetBranchAddress("NrecoPhot", &NrecoPhot, &b_NrecoPhot);
   fChain->SetBranchAddress("recoPhotPt", recoPhotPt, &b_recoPhotPt);
   fChain->SetBranchAddress("recoPhotPhi", recoPhotPhi, &b_recoPhotPhi);
   fChain->SetBranchAddress("recoPhotEta", recoPhotEta, &b_recoPhotEta);
   fChain->SetBranchAddress("recoPhotEt", recoPhotEt, &b_recoPhotEt);
   fChain->SetBranchAddress("recoPhotE", recoPhotE, &b_recoPhotE);
   fChain->SetBranchAddress("recoPhotTiso", recoPhotTiso, &b_recoPhotTiso);
   fChain->SetBranchAddress("recoPhotEiso", recoPhotEiso, &b_recoPhotEiso);
   fChain->SetBranchAddress("recoPhotHiso", recoPhotHiso, &b_recoPhotHiso);
   fChain->SetBranchAddress("recoPhotHoverE", recoPhotHoverE, &b_recoPhotHoverE);
   fChain->SetBranchAddress("recoPhotClusShap", recoPhotClusShap, &b_recoPhotClusShap);
   fChain->SetBranchAddress("recoPhotR9ID", recoPhotR9ID, &b_recoPhotR9ID);
   fChain->SetBranchAddress("NohPhot", &NohPhot, &b_NohPhot);
   fChain->SetBranchAddress("ohPhotEt", &ohPhotEt, &b_ohPhotEt);
   fChain->SetBranchAddress("ohPhotEta", &ohPhotEta, &b_ohPhotEta);
   fChain->SetBranchAddress("ohPhotPhi", &ohPhotPhi, &b_ohPhotPhi);
   fChain->SetBranchAddress("ohPhotEiso", &ohPhotEiso, &b_ohPhotEiso);
   fChain->SetBranchAddress("ohPhotHiso", &ohPhotHiso, &b_ohPhotHiso);
   fChain->SetBranchAddress("ohPhotTiso", &ohPhotTiso, &b_ohPhotTiso);
   fChain->SetBranchAddress("ohPhotL1iso", &ohPhotL1iso, &b_ohPhotL1iso);
   fChain->SetBranchAddress("ohPhotClusShap", &ohPhotClusShap, &b_ohPhotClusShap);
   fChain->SetBranchAddress("ohPhotR9", &ohPhotR9, &b_ohPhotR9);
   fChain->SetBranchAddress("ohPhotHforHoverE", &ohPhotHforHoverE, &b_ohPhotHforHoverE);
   fChain->SetBranchAddress("ohPhotR9ID", &ohPhotR9ID, &b_ohPhotR9ID);
   fChain->SetBranchAddress("NohEcalActiv", &NohEcalActiv, &b_NohEcalActiv);
   fChain->SetBranchAddress("ohEcalActivEt", &ohEcalActivEt, &b_ohEcalActivEt);
   fChain->SetBranchAddress("ohEcalActivEta", &ohEcalActivEta, &b_ohEcalActivEta);
   fChain->SetBranchAddress("ohEcalActivPhi", &ohEcalActivPhi, &b_ohEcalActivPhi);
   fChain->SetBranchAddress("ohEcalActivEiso", &ohEcalActivEiso, &b_ohEcalActivEiso);
   fChain->SetBranchAddress("ohEcalActivHiso", &ohEcalActivHiso, &b_ohEcalActivHiso);
   fChain->SetBranchAddress("ohEcalActivTiso", &ohEcalActivTiso, &b_ohEcalActivTiso);
   fChain->SetBranchAddress("ohEcalActivL1iso", &ohEcalActivL1iso, &b_ohEcalActivL1iso);
   fChain->SetBranchAddress("ohEcalActivClusShap", &ohEcalActivClusShap, &b_ohEcalActivClusShap);
   fChain->SetBranchAddress("ohEcalActivR9", &ohEcalActivR9, &b_ohEcalActivR9);
   fChain->SetBranchAddress("ohEcalActivHforHoverE", &ohEcalActivHforHoverE, &b_ohEcalActivHforHoverE);
   fChain->SetBranchAddress("ohEcalActivR9ID", &ohEcalActivR9ID, &b_ohEcalActivR9ID);
   fChain->SetBranchAddress("NohEle", &NohEle, &b_NohEle);
   fChain->SetBranchAddress("ohEleEt", &ohEleEt, &b_ohEleEt);
   fChain->SetBranchAddress("ohEleEta", &ohEleEta, &b_ohEleEta);
   fChain->SetBranchAddress("ohElePhi", &ohElePhi, &b_ohElePhi);
   fChain->SetBranchAddress("ohEleVtxZ", &ohEleVtxZ, &b_ohEleVtxZ);
   fChain->SetBranchAddress("ohEleE", &ohEleE, &b_ohEleE);
   fChain->SetBranchAddress("ohEleP", &ohEleP, &b_ohEleP);
   fChain->SetBranchAddress("ohEleHiso", &ohEleHiso, &b_ohEleHiso);
   fChain->SetBranchAddress("ohEleTiso", &ohEleTiso, &b_ohEleTiso);
   fChain->SetBranchAddress("ohEleEiso", &ohEleEiso, &b_ohEleEiso);
   fChain->SetBranchAddress("ohEleL1iso", &ohEleL1iso, &b_ohEleL1iso);
   fChain->SetBranchAddress("ohElePixelSeeds", &ohElePixelSeeds, &b_ohElePixelSeeds);
   fChain->SetBranchAddress("ohEleNewSC", &ohEleNewSC, &b_ohEleNewSC);
   fChain->SetBranchAddress("ohEleClusShap", &ohEleClusShap, &b_ohEleClusShap);
   fChain->SetBranchAddress("ohEleDeta", &ohEleDeta, &b_ohEleDeta);
   fChain->SetBranchAddress("ohEleDphi", &ohEleDphi, &b_ohEleDphi);
   fChain->SetBranchAddress("ohEleR9", &ohEleR9, &b_ohEleR9);
   fChain->SetBranchAddress("ohEleHforHoverE", &ohEleHforHoverE, &b_ohEleHforHoverE);
   fChain->SetBranchAddress("ohEleR9ID", &ohEleR9ID, &b_ohEleR9ID);
   fChain->SetBranchAddress("NohHFEle", &NohHFEle, &b_NohHFEle);
   fChain->SetBranchAddress("ohHFElePt", &ohHFElePt, &b_ohHFElePt);
   fChain->SetBranchAddress("ohHFEleEta", &ohHFEleEta, &b_ohHFEleEta);
   fChain->SetBranchAddress("NohHFECALClus", &NohHFECALClus, &b_NohHFECALClus);
   fChain->SetBranchAddress("ohHFEleClustere9e25", &ohHFEleClustere9e25, &b_ohHFEleClustere9e25);
   fChain->SetBranchAddress("ohHFEleClustere1e9", &ohHFEleClustere1e9, &b_ohHFEleClustere1e9);
   fChain->SetBranchAddress("ohHFEleClustereCOREe9", &ohHFEleClustereCOREe9, &b_ohHFEleClustereCOREe9);
   fChain->SetBranchAddress("ohHFEleClustereSeL", &ohHFEleClustereSeL, &b_ohHFEleClustereSeL);
   fChain->SetBranchAddress("ohHFEleCluster2Dcut", &ohHFEleCluster2Dcut, &b_ohHFEleCluster2Dcut);
   fChain->SetBranchAddress("ohHFEleClusterEta", &ohHFEleClusterEta, &b_ohHFEleClusterEta);
   fChain->SetBranchAddress("ohHFEleClusterPhi", &ohHFEleClusterPhi, &b_ohHFEleClusterPhi);
   fChain->SetBranchAddress("NL1IsolEm", &NL1IsolEm, &b_NL1IsolEm);
   fChain->SetBranchAddress("L1IsolEmEt", &L1IsolEmEt, &b_L1IsolEmEt);
   fChain->SetBranchAddress("L1IsolEmE", &L1IsolEmE, &b_L1IsolEmE);
   fChain->SetBranchAddress("L1IsolEmEta", &L1IsolEmEta, &b_L1IsolEmEta);
   fChain->SetBranchAddress("L1IsolEmPhi", &L1IsolEmPhi, &b_L1IsolEmPhi);
   fChain->SetBranchAddress("NL1NIsolEm", &NL1NIsolEm, &b_NL1NIsolEm);
   fChain->SetBranchAddress("L1NIsolEmEt", &L1NIsolEmEt, &b_L1NIsolEmEt);
   fChain->SetBranchAddress("L1NIsolEmE", &L1NIsolEmE, &b_L1NIsolEmE);
   fChain->SetBranchAddress("L1NIsolEmEta", &L1NIsolEmEta, &b_L1NIsolEmEta);
   fChain->SetBranchAddress("L1NIsolEmPhi", &L1NIsolEmPhi, &b_L1NIsolEmPhi);
   fChain->SetBranchAddress("NL1Mu", &NL1Mu, &b_NL1Mu);
   fChain->SetBranchAddress("L1MuPt", &L1MuPt, &b_L1MuPt);
   fChain->SetBranchAddress("L1MuE", &L1MuE, &b_L1MuE);
   fChain->SetBranchAddress("L1MuEta", &L1MuEta, &b_L1MuEta);
   fChain->SetBranchAddress("L1MuPhi", &L1MuPhi, &b_L1MuPhi);
   fChain->SetBranchAddress("L1MuIsol", &L1MuIsol, &b_L1MuIsol);
   fChain->SetBranchAddress("L1MuMip", &L1MuMip, &b_L1MuMip);
   fChain->SetBranchAddress("L1MuFor", &L1MuFor, &b_L1MuFor);
   fChain->SetBranchAddress("L1MuRPC", &L1MuRPC, &b_L1MuRPC);
   fChain->SetBranchAddress("L1MuQal", &L1MuQal, &b_L1MuQal);
   fChain->SetBranchAddress("L1MuChg", &L1MuChg, &b_L1MuChg);
   fChain->SetBranchAddress("NL1CenJet", &NL1CenJet, &b_NL1CenJet);
   fChain->SetBranchAddress("L1CenJetEt", &L1CenJetEt, &b_L1CenJetEt);
   fChain->SetBranchAddress("L1CenJetE", &L1CenJetE, &b_L1CenJetE);
   fChain->SetBranchAddress("L1CenJetEta", &L1CenJetEta, &b_L1CenJetEta);
   fChain->SetBranchAddress("L1CenJetPhi", &L1CenJetPhi, &b_L1CenJetPhi);
   fChain->SetBranchAddress("NL1ForJet", &NL1ForJet, &b_NL1ForJet);
   fChain->SetBranchAddress("L1ForJetEt", &L1ForJetEt, &b_L1ForJetEt);
   fChain->SetBranchAddress("L1ForJetE", &L1ForJetE, &b_L1ForJetE);
   fChain->SetBranchAddress("L1ForJetEta", &L1ForJetEta, &b_L1ForJetEta);
   fChain->SetBranchAddress("L1ForJetPhi", &L1ForJetPhi, &b_L1ForJetPhi);
   fChain->SetBranchAddress("NL1Tau", &NL1Tau, &b_NL1Tau);
   fChain->SetBranchAddress("L1TauEt", &L1TauEt, &b_L1TauEt);
   fChain->SetBranchAddress("L1TauE", &L1TauE, &b_L1TauE);
   fChain->SetBranchAddress("L1TauEta", &L1TauEta, &b_L1TauEta);
   fChain->SetBranchAddress("L1TauPhi", &L1TauPhi, &b_L1TauPhi);
   fChain->SetBranchAddress("L1Met", &L1Met, &b_L1Met);
   fChain->SetBranchAddress("L1MetPhi", &L1MetPhi, &b_L1MetPhi);
   fChain->SetBranchAddress("L1EtTot", &L1EtTot, &b_L1EtTot);
   fChain->SetBranchAddress("L1Mht", &L1Mht, &b_L1Mht);
   fChain->SetBranchAddress("L1MhtPhi", &L1MhtPhi, &b_L1MhtPhi);
   fChain->SetBranchAddress("L1EtHad", &L1EtHad, &b_L1EtHad);
   fChain->SetBranchAddress("L1HfRing1EtSumPositiveEta", &L1HfRing1EtSumPositiveEta, &b_L1HfRing1EtSumPositiveEta);
   fChain->SetBranchAddress("L1HfRing2EtSumPositiveEta", &L1HfRing2EtSumPositiveEta, &b_L1HfRing2EtSumPositiveEta);
   fChain->SetBranchAddress("L1HfRing1EtSumNegativeEta", &L1HfRing1EtSumNegativeEta, &b_L1HfRing1EtSumNegativeEta);
   fChain->SetBranchAddress("L1HfRing2EtSumNegativeEta", &L1HfRing2EtSumNegativeEta, &b_L1HfRing2EtSumNegativeEta);
   fChain->SetBranchAddress("L1HfTowerCountPositiveEtaRing1", &L1HfTowerCountPositiveEtaRing1, &b_L1HfTowerCountPositiveEtaRing1);
   fChain->SetBranchAddress("L1HfTowerCountNegativeEtaRing1", &L1HfTowerCountNegativeEtaRing1, &b_L1HfTowerCountNegativeEtaRing1);
   fChain->SetBranchAddress("L1HfTowerCountPositiveEtaRing2", &L1HfTowerCountPositiveEtaRing2, &b_L1HfTowerCountPositiveEtaRing2);
   fChain->SetBranchAddress("L1HfTowerCountNegativeEtaRing2", &L1HfTowerCountNegativeEtaRing2, &b_L1HfTowerCountNegativeEtaRing2);
   fChain->SetBranchAddress("recoNVrtHLT", &recoNVrtHLT, &b_NVrtx);
   fChain->SetBranchAddress("recoVrtXHLT", recoVrtXHLT, &b_recoVrtXHLT);
   fChain->SetBranchAddress("recoVrtYHLT", recoVrtYHLT, &b_recoVrtYHLT);
   fChain->SetBranchAddress("recoVrtZHLT", recoVrtZHLT, &b_recoVrtZHLT);
   fChain->SetBranchAddress("recoVrtNtrkHLT", recoVrtNtrkHLT, &b_recoVrtNtrkHLT);
   fChain->SetBranchAddress("recoVrtChi2HLT", recoVrtChi2HLT, &b_recoVrtChi2HLT);
   fChain->SetBranchAddress("recoVrtNdofHLT", recoVrtNdofHLT, &b_recoVrtNdofHLT);
   fChain->SetBranchAddress("recoNVrtOffline0", &recoNVrtOffline0, &b_NVrtx);
   fChain->SetBranchAddress("recoVrtXOffline0", recoVrtXOffline0, &b_recoVrtXOffline0);
   fChain->SetBranchAddress("recoVrtYOffline0", recoVrtYOffline0, &b_recoVrtYOffline0);
   fChain->SetBranchAddress("recoVrtZOffline0", recoVrtZOffline0, &b_recoVrtZOffline0);
   fChain->SetBranchAddress("recoVrtNtrkOffline0", recoVrtNtrkOffline0, &b_recoVrtNtrkOffline0);
   fChain->SetBranchAddress("recoVrtChi2Offline0", recoVrtChi2Offline0, &b_recoVrtChi2Offline0);
   fChain->SetBranchAddress("recoVrtNdofOffline0", recoVrtNdofOffline0, &b_recoVrtNdofOffline0);
   fChain->SetBranchAddress("Npart", &Npart, &b_Npart);
   fChain->SetBranchAddress("Ncoll", &Ncoll, &b_Ncoll);
   fChain->SetBranchAddress("Nhard", &Nhard, &b_Nhard);
   fChain->SetBranchAddress("phi0", &phi0, &b_NPhi0);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("Ncharged", &Ncharged, &b_Ncharged);
   fChain->SetBranchAddress("NchargedMR", &NchargedMR, &b_NchargedMR);
   fChain->SetBranchAddress("MeanPt", &MeanPt, &b_MeanPt);
   fChain->SetBranchAddress("MeanPtMR", &MeanPtMR, &b_MeanPtMR);
   fChain->SetBranchAddress("EtMR", &EtMR, &b_EtMR);
   fChain->SetBranchAddress("NchargedPtCut", &NchargedPtCut, &b_NchargedPtCut);
   fChain->SetBranchAddress("NchargedPtCutMR", &NchargedPtCutMR, &b_NchargedPtCutMR);
   fChain->SetBranchAddress("hiBin", &hiBin, &b_hiBin);
   fChain->SetBranchAddress("hiHF", &hiHF, &b_hiHF);
   fChain->SetBranchAddress("hiHFplus", &hiHFplus, &b_hiHFplus);
   fChain->SetBranchAddress("hiHFminus", &hiHFminus, &b_hiHFminus);
   fChain->SetBranchAddress("hiZDC", &hiZDC, &b_hiZDC);
   fChain->SetBranchAddress("hiZDCplus", &hiZDCplus, &b_hiZDCplus);
   fChain->SetBranchAddress("hiZDCminus", &hiZDCminus, &b_hiZDCminus);
   fChain->SetBranchAddress("hiHFhit", &hiHFhit, &b_hiHFhit);
   fChain->SetBranchAddress("hiHFhitPlus", &hiHFhitPlus, &b_hiHFhitPlus);
   fChain->SetBranchAddress("hiHFhitMinus", &hiHFhitMinus, &b_hiHFhitMinus);
   fChain->SetBranchAddress("hiET", &hiET, &b_hiET);
   fChain->SetBranchAddress("hiEE", &hiEE, &b_hiEE);
   fChain->SetBranchAddress("hiEB", &hiEB, &b_hiEB);
   fChain->SetBranchAddress("hiEEplus", &hiEEplus, &b_hiEEplus);
   fChain->SetBranchAddress("hiEEminus", &hiEEminus, &b_hiEEminus);
   fChain->SetBranchAddress("hiNpix", &hiNpix, &b_hiNpix);
   fChain->SetBranchAddress("hiNpixelTracks", &hiNpixelTracks, &b_hiNpixelTracks);
   fChain->SetBranchAddress("hiNtracks", &hiNtracks, &b_hiNtracks);
   fChain->SetBranchAddress("hiNevtPlane", &hiNevtPlane, &b_hiNevtPlane);
   fChain->SetBranchAddress("hiEvtPlanes", &hiEvtPlanes, &b_hiEvtPlanes);
   fChain->SetBranchAddress("hiNtracksPtCut", &hiNtracksPtCut, &b_hiNtracksPtCut);
   fChain->SetBranchAddress("hiNtracksEtaCut", &hiNtracksEtaCut, &b_hiNtracksEtaCut);
   fChain->SetBranchAddress("hiNtracksEtaPtCut", &hiNtracksEtaPtCut, &b_hiNtracksEtaPtCut);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
   fChain->SetBranchAddress("Bx", &Bx, &b_Bx);
   fChain->SetBranchAddress("Orbit", &Orbit, &b_Orbit);
   fChain->SetBranchAddress("AvgInstDelLumi", &AvgInstDelLumi, &b_AvgInstDelLumi);
   fChain->SetBranchAddress("AlCa_EcalPhiSym_v2", &AlCa_EcalPhiSym_v2, &b_AlCa_EcalPhiSym_v2);
   fChain->SetBranchAddress("AlCa_EcalPhiSym_v2_Prescl", &AlCa_EcalPhiSym_v2_Prescl, &b_AlCa_EcalPhiSym_v2_Prescl);
   fChain->SetBranchAddress("AlCa_EcalEta_v3", &AlCa_EcalEta_v3, &b_AlCa_EcalEta_v3);
   fChain->SetBranchAddress("AlCa_EcalEta_v3_Prescl", &AlCa_EcalEta_v3_Prescl, &b_AlCa_EcalEta_v3_Prescl);
   fChain->SetBranchAddress("AlCa_EcalPi0_v4", &AlCa_EcalPi0_v4, &b_AlCa_EcalPi0_v4);
   fChain->SetBranchAddress("AlCa_EcalPi0_v4_Prescl", &AlCa_EcalPi0_v4_Prescl, &b_AlCa_EcalPi0_v4_Prescl);
   fChain->SetBranchAddress("AlCa_RPCMuonNoHits_v2", &AlCa_RPCMuonNoHits_v2, &b_AlCa_RPCMuonNoHits_v2);
   fChain->SetBranchAddress("AlCa_RPCMuonNoHits_v2_Prescl", &AlCa_RPCMuonNoHits_v2_Prescl, &b_AlCa_RPCMuonNoHits_v2_Prescl);
   fChain->SetBranchAddress("AlCa_RPCMuonNoTriggers_v2", &AlCa_RPCMuonNoTriggers_v2, &b_AlCa_RPCMuonNoTriggers_v2);
   fChain->SetBranchAddress("AlCa_RPCMuonNoTriggers_v2_Prescl", &AlCa_RPCMuonNoTriggers_v2_Prescl, &b_AlCa_RPCMuonNoTriggers_v2_Prescl);
   fChain->SetBranchAddress("AlCa_RPCMuonNormalisation_v2", &AlCa_RPCMuonNormalisation_v2, &b_AlCa_RPCMuonNormalisation_v2);
   fChain->SetBranchAddress("AlCa_RPCMuonNormalisation_v2_Prescl", &AlCa_RPCMuonNormalisation_v2_Prescl, &b_AlCa_RPCMuonNormalisation_v2_Prescl);
   fChain->SetBranchAddress("HLT_BeamGas_BSC_v2", &HLT_BeamGas_BSC_v2, &b_HLT_BeamGas_BSC_v2);
   fChain->SetBranchAddress("HLT_BeamGas_BSC_v2_Prescl", &HLT_BeamGas_BSC_v2_Prescl, &b_HLT_BeamGas_BSC_v2_Prescl);
   fChain->SetBranchAddress("HLT_BeamGas_HF_v2", &HLT_BeamGas_HF_v2, &b_HLT_BeamGas_HF_v2);
   fChain->SetBranchAddress("HLT_BeamGas_HF_v2_Prescl", &HLT_BeamGas_HF_v2_Prescl, &b_HLT_BeamGas_HF_v2_Prescl);
   fChain->SetBranchAddress("HLT_BeamHalo_v2", &HLT_BeamHalo_v2, &b_HLT_BeamHalo_v2);
   fChain->SetBranchAddress("HLT_BeamHalo_v2_Prescl", &HLT_BeamHalo_v2_Prescl, &b_HLT_BeamHalo_v2_Prescl);
   fChain->SetBranchAddress("HLT_Calibration_v1", &HLT_Calibration_v1, &b_HLT_Calibration_v1);
   fChain->SetBranchAddress("HLT_Calibration_v1_Prescl", &HLT_Calibration_v1_Prescl, &b_HLT_Calibration_v1_Prescl);
   fChain->SetBranchAddress("HLT_DTErrors_v1", &HLT_DTErrors_v1, &b_HLT_DTErrors_v1);
   fChain->SetBranchAddress("HLT_DTErrors_v1_Prescl", &HLT_DTErrors_v1_Prescl, &b_HLT_DTErrors_v1_Prescl);
   fChain->SetBranchAddress("HLT_DoubleMu3_v3", &HLT_DoubleMu3_v3, &b_HLT_DoubleMu3_v3);
   fChain->SetBranchAddress("HLT_DoubleMu3_v3_Prescl", &HLT_DoubleMu3_v3_Prescl, &b_HLT_DoubleMu3_v3_Prescl);
   fChain->SetBranchAddress("HLT_EcalCalibration_v1", &HLT_EcalCalibration_v1, &b_HLT_EcalCalibration_v1);
   fChain->SetBranchAddress("HLT_EcalCalibration_v1_Prescl", &HLT_EcalCalibration_v1_Prescl, &b_HLT_EcalCalibration_v1_Prescl);
   fChain->SetBranchAddress("HLT_Ele8_v2", &HLT_Ele8_v2, &b_HLT_Ele8_v2);
   fChain->SetBranchAddress("HLT_Ele8_v2_Prescl", &HLT_Ele8_v2_Prescl, &b_HLT_Ele8_v2_Prescl);
   fChain->SetBranchAddress("HLT_GlobalRunHPDNoise_v2", &HLT_GlobalRunHPDNoise_v2, &b_HLT_GlobalRunHPDNoise_v2);
   fChain->SetBranchAddress("HLT_GlobalRunHPDNoise_v2_Prescl", &HLT_GlobalRunHPDNoise_v2_Prescl, &b_HLT_GlobalRunHPDNoise_v2_Prescl);
   fChain->SetBranchAddress("HLT_HcalCalibration_v1", &HLT_HcalCalibration_v1, &b_HLT_HcalCalibration_v1);
   fChain->SetBranchAddress("HLT_HcalCalibration_v1_Prescl", &HLT_HcalCalibration_v1_Prescl, &b_HLT_HcalCalibration_v1_Prescl);
   fChain->SetBranchAddress("HLT_HcalNZS_v3", &HLT_HcalNZS_v3, &b_HLT_HcalNZS_v3);
   fChain->SetBranchAddress("HLT_HcalNZS_v3_Prescl", &HLT_HcalNZS_v3_Prescl, &b_HLT_HcalNZS_v3_Prescl);
   fChain->SetBranchAddress("HLT_HcalPhiSym_v3", &HLT_HcalPhiSym_v3, &b_HLT_HcalPhiSym_v3);
   fChain->SetBranchAddress("HLT_HcalPhiSym_v3_Prescl", &HLT_HcalPhiSym_v3_Prescl, &b_HLT_HcalPhiSym_v3_Prescl);
   fChain->SetBranchAddress("HLT_IsoTrackHB_v2", &HLT_IsoTrackHB_v2, &b_HLT_IsoTrackHB_v2);
   fChain->SetBranchAddress("HLT_IsoTrackHB_v2_Prescl", &HLT_IsoTrackHB_v2_Prescl, &b_HLT_IsoTrackHB_v2_Prescl);
   fChain->SetBranchAddress("HLT_IsoTrackHE_v3", &HLT_IsoTrackHE_v3, &b_HLT_IsoTrackHE_v3);
   fChain->SetBranchAddress("HLT_IsoTrackHE_v3_Prescl", &HLT_IsoTrackHE_v3_Prescl, &b_HLT_IsoTrackHE_v3_Prescl);
   fChain->SetBranchAddress("HLT_Jet20_v1", &HLT_Jet20_v1, &b_HLT_Jet20_v1);
   fChain->SetBranchAddress("HLT_Jet20_v1_Prescl", &HLT_Jet20_v1_Prescl, &b_HLT_Jet20_v1_Prescl);
   fChain->SetBranchAddress("HLT_Jet40_v1", &HLT_Jet40_v1, &b_HLT_Jet40_v1);
   fChain->SetBranchAddress("HLT_Jet40_v1_Prescl", &HLT_Jet40_v1_Prescl, &b_HLT_Jet40_v1_Prescl);
   fChain->SetBranchAddress("HLT_Jet60_v1", &HLT_Jet60_v1, &b_HLT_Jet60_v1);
   fChain->SetBranchAddress("HLT_Jet60_v1_Prescl", &HLT_Jet60_v1_Prescl, &b_HLT_Jet60_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1DoubleForJet32_EtaOpp_v1", &HLT_L1DoubleForJet32_EtaOpp_v1, &b_HLT_L1DoubleForJet32_EtaOpp_v1);
   fChain->SetBranchAddress("HLT_L1DoubleForJet32_EtaOpp_v1_Prescl", &HLT_L1DoubleForJet32_EtaOpp_v1_Prescl, &b_HLT_L1DoubleForJet32_EtaOpp_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1DoubleForJet8_EtaOpp_v1", &HLT_L1DoubleForJet8_EtaOpp_v1, &b_HLT_L1DoubleForJet8_EtaOpp_v1);
   fChain->SetBranchAddress("HLT_L1DoubleForJet8_EtaOpp_v1_Prescl", &HLT_L1DoubleForJet8_EtaOpp_v1_Prescl, &b_HLT_L1DoubleForJet8_EtaOpp_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1DoubleMu0_v1", &HLT_L1DoubleMu0_v1, &b_HLT_L1DoubleMu0_v1);
   fChain->SetBranchAddress("HLT_L1DoubleMu0_v1_Prescl", &HLT_L1DoubleMu0_v1_Prescl, &b_HLT_L1DoubleMu0_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1SingleEG12_v1", &HLT_L1SingleEG12_v1, &b_HLT_L1SingleEG12_v1);
   fChain->SetBranchAddress("HLT_L1SingleEG12_v1_Prescl", &HLT_L1SingleEG12_v1_Prescl, &b_HLT_L1SingleEG12_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1SingleEG5_v1", &HLT_L1SingleEG5_v1, &b_HLT_L1SingleEG5_v1);
   fChain->SetBranchAddress("HLT_L1SingleEG5_v1_Prescl", &HLT_L1SingleEG5_v1_Prescl, &b_HLT_L1SingleEG5_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1SingleJet36_v1", &HLT_L1SingleJet36_v1, &b_HLT_L1SingleJet36_v1);
   fChain->SetBranchAddress("HLT_L1SingleJet36_v1_Prescl", &HLT_L1SingleJet36_v1_Prescl, &b_HLT_L1SingleJet36_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1SingleMuOpen_AntiBPTX_v1", &HLT_L1SingleMuOpen_AntiBPTX_v1, &b_HLT_L1SingleMuOpen_AntiBPTX_v1);
   fChain->SetBranchAddress("HLT_L1SingleMuOpen_AntiBPTX_v1_Prescl", &HLT_L1SingleMuOpen_AntiBPTX_v1_Prescl, &b_HLT_L1SingleMuOpen_AntiBPTX_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1SingleMuOpen_DT_v1", &HLT_L1SingleMuOpen_DT_v1, &b_HLT_L1SingleMuOpen_DT_v1);
   fChain->SetBranchAddress("HLT_L1SingleMuOpen_DT_v1_Prescl", &HLT_L1SingleMuOpen_DT_v1_Prescl, &b_HLT_L1SingleMuOpen_DT_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1SingleMuOpen_v1", &HLT_L1SingleMuOpen_v1, &b_HLT_L1SingleMuOpen_v1);
   fChain->SetBranchAddress("HLT_L1SingleMuOpen_v1_Prescl", &HLT_L1SingleMuOpen_v1_Prescl, &b_HLT_L1SingleMuOpen_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1Tech_BSC_halo_v1", &HLT_L1Tech_BSC_halo_v1, &b_HLT_L1Tech_BSC_halo_v1);
   fChain->SetBranchAddress("HLT_L1Tech_BSC_halo_v1_Prescl", &HLT_L1Tech_BSC_halo_v1_Prescl, &b_HLT_L1Tech_BSC_halo_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1Tech_HBHEHO_totalOR_v1", &HLT_L1Tech_HBHEHO_totalOR_v1, &b_HLT_L1Tech_HBHEHO_totalOR_v1);
   fChain->SetBranchAddress("HLT_L1Tech_HBHEHO_totalOR_v1_Prescl", &HLT_L1Tech_HBHEHO_totalOR_v1_Prescl, &b_HLT_L1Tech_HBHEHO_totalOR_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1TrackerCosmics_v2", &HLT_L1TrackerCosmics_v2, &b_HLT_L1TrackerCosmics_v2);
   fChain->SetBranchAddress("HLT_L1TrackerCosmics_v2_Prescl", &HLT_L1TrackerCosmics_v2_Prescl, &b_HLT_L1TrackerCosmics_v2_Prescl);
   fChain->SetBranchAddress("HLT_L1_Interbunch_BSC_v1", &HLT_L1_Interbunch_BSC_v1, &b_HLT_L1_Interbunch_BSC_v1);
   fChain->SetBranchAddress("HLT_L1_Interbunch_BSC_v1_Prescl", &HLT_L1_Interbunch_BSC_v1_Prescl, &b_HLT_L1_Interbunch_BSC_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1_PreCollisions_v1", &HLT_L1_PreCollisions_v1, &b_HLT_L1_PreCollisions_v1);
   fChain->SetBranchAddress("HLT_L1_PreCollisions_v1_Prescl", &HLT_L1_PreCollisions_v1_Prescl, &b_HLT_L1_PreCollisions_v1_Prescl);
   fChain->SetBranchAddress("HLT_L2DoubleMu0_v2", &HLT_L2DoubleMu0_v2, &b_HLT_L2DoubleMu0_v2);
   fChain->SetBranchAddress("HLT_L2DoubleMu0_v2_Prescl", &HLT_L2DoubleMu0_v2_Prescl, &b_HLT_L2DoubleMu0_v2_Prescl);
   fChain->SetBranchAddress("HLT_L3MuonsCosmicTracking_v1", &HLT_L3MuonsCosmicTracking_v1, &b_HLT_L3MuonsCosmicTracking_v1);
   fChain->SetBranchAddress("HLT_L3MuonsCosmicTracking_v1_Prescl", &HLT_L3MuonsCosmicTracking_v1_Prescl, &b_HLT_L3MuonsCosmicTracking_v1_Prescl);
   fChain->SetBranchAddress("HLT_LogMonitor_v1", &HLT_LogMonitor_v1, &b_HLT_LogMonitor_v1);
   fChain->SetBranchAddress("HLT_LogMonitor_v1_Prescl", &HLT_LogMonitor_v1_Prescl, &b_HLT_LogMonitor_v1_Prescl);
   fChain->SetBranchAddress("HLT_L1BscMinBiasORBptxPlusANDMinus_v1", &HLT_L1BscMinBiasORBptxPlusANDMinus_v1, &b_HLT_L1BscMinBiasORBptxPlusANDMinus_v1);
   fChain->SetBranchAddress("HLT_L1BscMinBiasORBptxPlusANDMinus_v1_Prescl", &HLT_L1BscMinBiasORBptxPlusANDMinus_v1_Prescl, &b_HLT_L1BscMinBiasORBptxPlusANDMinus_v1_Prescl);
   fChain->SetBranchAddress("HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1", &HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1, &b_HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1);
   fChain->SetBranchAddress("HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1_Prescl", &HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1_Prescl, &b_HLT_Mu5_TkMu0_OST_Jpsi_Tight_B5Q7_v1_Prescl);
   fChain->SetBranchAddress("HLT_Mu0_v3", &HLT_Mu0_v3, &b_HLT_Mu0_v3);
   fChain->SetBranchAddress("HLT_Mu0_v3_Prescl", &HLT_Mu0_v3_Prescl, &b_HLT_Mu0_v3_Prescl);
   fChain->SetBranchAddress("HLT_Mu3_v3", &HLT_Mu3_v3, &b_HLT_Mu3_v3);
   fChain->SetBranchAddress("HLT_Mu3_v3_Prescl", &HLT_Mu3_v3_Prescl, &b_HLT_Mu3_v3_Prescl);
   fChain->SetBranchAddress("HLT_Mu5_v3", &HLT_Mu5_v3, &b_HLT_Mu5_v3);
   fChain->SetBranchAddress("HLT_Mu5_v3_Prescl", &HLT_Mu5_v3_Prescl, &b_HLT_Mu5_v3_Prescl);
   fChain->SetBranchAddress("HLT_Photon10_CaloIdVL_v1", &HLT_Photon10_CaloIdVL_v1, &b_HLT_Photon10_CaloIdVL_v1);
   fChain->SetBranchAddress("HLT_Photon10_CaloIdVL_v1_Prescl", &HLT_Photon10_CaloIdVL_v1_Prescl, &b_HLT_Photon10_CaloIdVL_v1_Prescl);
   fChain->SetBranchAddress("HLT_Photon15_CaloIdVL_v1", &HLT_Photon15_CaloIdVL_v1, &b_HLT_Photon15_CaloIdVL_v1);
   fChain->SetBranchAddress("HLT_Photon15_CaloIdVL_v1_Prescl", &HLT_Photon15_CaloIdVL_v1_Prescl, &b_HLT_Photon15_CaloIdVL_v1_Prescl);
   fChain->SetBranchAddress("HLT_Physics_NanoDST_v1", &HLT_Physics_NanoDST_v1, &b_HLT_Physics_NanoDST_v1);
   fChain->SetBranchAddress("HLT_Physics_NanoDST_v1_Prescl", &HLT_Physics_NanoDST_v1_Prescl, &b_HLT_Physics_NanoDST_v1_Prescl);
   fChain->SetBranchAddress("HLT_PixelTracks_Multiplicity50_Loose", &HLT_PixelTracks_Multiplicity50_Loose, &b_HLT_PixelTracks_Multiplicity50_Loose);
   fChain->SetBranchAddress("HLT_PixelTracks_Multiplicity50_Loose_Prescl", &HLT_PixelTracks_Multiplicity50_Loose_Prescl, &b_HLT_PixelTracks_Multiplicity50_Loose_Prescl);
   fChain->SetBranchAddress("HLT_PixelTracks_Multiplicity60_Loose", &HLT_PixelTracks_Multiplicity60_Loose, &b_HLT_PixelTracks_Multiplicity60_Loose);
   fChain->SetBranchAddress("HLT_PixelTracks_Multiplicity60_Loose_Prescl", &HLT_PixelTracks_Multiplicity60_Loose_Prescl, &b_HLT_PixelTracks_Multiplicity60_Loose_Prescl);
   fChain->SetBranchAddress("HLT_PixelTracks_Multiplicity70_Loose", &HLT_PixelTracks_Multiplicity70_Loose, &b_HLT_PixelTracks_Multiplicity70_Loose);
   fChain->SetBranchAddress("HLT_PixelTracks_Multiplicity70_Loose_Prescl", &HLT_PixelTracks_Multiplicity70_Loose_Prescl, &b_HLT_PixelTracks_Multiplicity70_Loose_Prescl);
   fChain->SetBranchAddress("HLT_Random_v1", &HLT_Random_v1, &b_HLT_Random_v1);
   fChain->SetBranchAddress("HLT_Random_v1_Prescl", &HLT_Random_v1_Prescl, &b_HLT_Random_v1_Prescl);
   fChain->SetBranchAddress("HLT_RegionalCosmicTracking_v1", &HLT_RegionalCosmicTracking_v1, &b_HLT_RegionalCosmicTracking_v1);
   fChain->SetBranchAddress("HLT_RegionalCosmicTracking_v1_Prescl", &HLT_RegionalCosmicTracking_v1_Prescl, &b_HLT_RegionalCosmicTracking_v1_Prescl);
   fChain->SetBranchAddress("HLT_TrackerCalibration_v1", &HLT_TrackerCalibration_v1, &b_HLT_TrackerCalibration_v1);
   fChain->SetBranchAddress("HLT_TrackerCalibration_v1_Prescl", &HLT_TrackerCalibration_v1_Prescl, &b_HLT_TrackerCalibration_v1_Prescl);
   fChain->SetBranchAddress("HLT_ZeroBiasPixel_SingleTrack_v1", &HLT_ZeroBiasPixel_SingleTrack_v1, &b_HLT_ZeroBiasPixel_SingleTrack_v1);
   fChain->SetBranchAddress("HLT_ZeroBiasPixel_SingleTrack_v1_Prescl", &HLT_ZeroBiasPixel_SingleTrack_v1_Prescl, &b_HLT_ZeroBiasPixel_SingleTrack_v1_Prescl);
   fChain->SetBranchAddress("HLT_ZeroBias_v1", &HLT_ZeroBias_v1, &b_HLT_ZeroBias_v1);
   fChain->SetBranchAddress("HLT_ZeroBias_v1_Prescl", &HLT_ZeroBias_v1_Prescl, &b_HLT_ZeroBias_v1_Prescl);
   fChain->SetBranchAddress("HLTriggerFinalPath", &HLTriggerFinalPath, &b_HLTriggerFinalPath);
   fChain->SetBranchAddress("HLTriggerFinalPath_Prescl", &HLTriggerFinalPath_Prescl, &b_HLTriggerFinalPath_Prescl);
   fChain->SetBranchAddress("L1_BeamGas_Bsc", &L1_BeamGas_Bsc, &b_L1_BeamGas_Bsc);
   fChain->SetBranchAddress("L1_BeamGas_Bsc_Prescl", &L1_BeamGas_Bsc_Prescl, &b_L1_BeamGas_Bsc_Prescl);
   fChain->SetBranchAddress("L1_BeamGas_Hf", &L1_BeamGas_Hf, &b_L1_BeamGas_Hf);
   fChain->SetBranchAddress("L1_BeamGas_Hf_Prescl", &L1_BeamGas_Hf_Prescl, &b_L1_BeamGas_Hf_Prescl);
   fChain->SetBranchAddress("L1_BeamHalo", &L1_BeamHalo, &b_L1_BeamHalo);
   fChain->SetBranchAddress("L1_BeamHalo_Prescl", &L1_BeamHalo_Prescl, &b_L1_BeamHalo_Prescl);
   fChain->SetBranchAddress("L1_BptxMinus_NotBptxPlus", &L1_BptxMinus_NotBptxPlus, &b_L1_BptxMinus_NotBptxPlus);
   fChain->SetBranchAddress("L1_BptxMinus_NotBptxPlus_Prescl", &L1_BptxMinus_NotBptxPlus_Prescl, &b_L1_BptxMinus_NotBptxPlus_Prescl);
   fChain->SetBranchAddress("L1_BptxPlusANDMinus", &L1_BptxPlusANDMinus, &b_L1_BptxPlusANDMinus);
   fChain->SetBranchAddress("L1_BptxPlusANDMinus_Prescl", &L1_BptxPlusANDMinus_Prescl, &b_L1_BptxPlusANDMinus_Prescl);
   fChain->SetBranchAddress("L1_BptxPlus_NotBptxMinus", &L1_BptxPlus_NotBptxMinus, &b_L1_BptxPlus_NotBptxMinus);
   fChain->SetBranchAddress("L1_BptxPlus_NotBptxMinus_Prescl", &L1_BptxPlus_NotBptxMinus_Prescl, &b_L1_BptxPlus_NotBptxMinus_Prescl);
   fChain->SetBranchAddress("L1_Bsc2Minus_BptxMinus", &L1_Bsc2Minus_BptxMinus, &b_L1_Bsc2Minus_BptxMinus);
   fChain->SetBranchAddress("L1_Bsc2Minus_BptxMinus_Prescl", &L1_Bsc2Minus_BptxMinus_Prescl, &b_L1_Bsc2Minus_BptxMinus_Prescl);
   fChain->SetBranchAddress("L1_Bsc2Plus_BptxPlus", &L1_Bsc2Plus_BptxPlus, &b_L1_Bsc2Plus_BptxPlus);
   fChain->SetBranchAddress("L1_Bsc2Plus_BptxPlus_Prescl", &L1_Bsc2Plus_BptxPlus_Prescl, &b_L1_Bsc2Plus_BptxPlus_Prescl);
   fChain->SetBranchAddress("L1_BscMinBiasOR_BptxPlusANDMinus", &L1_BscMinBiasOR_BptxPlusANDMinus, &b_L1_BscMinBiasOR_BptxPlusANDMinus);
   fChain->SetBranchAddress("L1_BscMinBiasOR_BptxPlusANDMinus_Prescl", &L1_BscMinBiasOR_BptxPlusANDMinus_Prescl, &b_L1_BscMinBiasOR_BptxPlusANDMinus_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG10", &L1_DoubleEG10, &b_L1_DoubleEG10);
   fChain->SetBranchAddress("L1_DoubleEG10_Prescl", &L1_DoubleEG10_Prescl, &b_L1_DoubleEG10_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG2_FwdVeto", &L1_DoubleEG2_FwdVeto, &b_L1_DoubleEG2_FwdVeto);
   fChain->SetBranchAddress("L1_DoubleEG2_FwdVeto_Prescl", &L1_DoubleEG2_FwdVeto_Prescl, &b_L1_DoubleEG2_FwdVeto_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG3", &L1_DoubleEG3, &b_L1_DoubleEG3);
   fChain->SetBranchAddress("L1_DoubleEG3_Prescl", &L1_DoubleEG3_Prescl, &b_L1_DoubleEG3_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG5", &L1_DoubleEG5, &b_L1_DoubleEG5);
   fChain->SetBranchAddress("L1_DoubleEG5_Prescl", &L1_DoubleEG5_Prescl, &b_L1_DoubleEG5_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG5_HTT50", &L1_DoubleEG5_HTT50, &b_L1_DoubleEG5_HTT50);
   fChain->SetBranchAddress("L1_DoubleEG5_HTT50_Prescl", &L1_DoubleEG5_HTT50_Prescl, &b_L1_DoubleEG5_HTT50_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG5_HTT75", &L1_DoubleEG5_HTT75, &b_L1_DoubleEG5_HTT75);
   fChain->SetBranchAddress("L1_DoubleEG5_HTT75_Prescl", &L1_DoubleEG5_HTT75_Prescl, &b_L1_DoubleEG5_HTT75_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG8", &L1_DoubleEG8, &b_L1_DoubleEG8);
   fChain->SetBranchAddress("L1_DoubleEG8_Prescl", &L1_DoubleEG8_Prescl, &b_L1_DoubleEG8_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG_12_5", &L1_DoubleEG_12_5, &b_L1_DoubleEG_12_5);
   fChain->SetBranchAddress("L1_DoubleEG_12_5_Prescl", &L1_DoubleEG_12_5_Prescl, &b_L1_DoubleEG_12_5_Prescl);
   fChain->SetBranchAddress("L1_DoubleEG_12_5_Eta1p39", &L1_DoubleEG_12_5_Eta1p39, &b_L1_DoubleEG_12_5_Eta1p39);
   fChain->SetBranchAddress("L1_DoubleEG_12_5_Eta1p39_Prescl", &L1_DoubleEG_12_5_Eta1p39_Prescl, &b_L1_DoubleEG_12_5_Eta1p39_Prescl);
   fChain->SetBranchAddress("L1_DoubleForJet32_EtaOpp", &L1_DoubleForJet32_EtaOpp, &b_L1_DoubleForJet32_EtaOpp);
   fChain->SetBranchAddress("L1_DoubleForJet32_EtaOpp_Prescl", &L1_DoubleForJet32_EtaOpp_Prescl, &b_L1_DoubleForJet32_EtaOpp_Prescl);
   fChain->SetBranchAddress("L1_DoubleForJet44_EtaOpp", &L1_DoubleForJet44_EtaOpp, &b_L1_DoubleForJet44_EtaOpp);
   fChain->SetBranchAddress("L1_DoubleForJet44_EtaOpp_Prescl", &L1_DoubleForJet44_EtaOpp_Prescl, &b_L1_DoubleForJet44_EtaOpp_Prescl);
   fChain->SetBranchAddress("L1_DoubleForJet8_EtaOpp", &L1_DoubleForJet8_EtaOpp, &b_L1_DoubleForJet8_EtaOpp);
   fChain->SetBranchAddress("L1_DoubleForJet8_EtaOpp_Prescl", &L1_DoubleForJet8_EtaOpp_Prescl, &b_L1_DoubleForJet8_EtaOpp_Prescl);
   fChain->SetBranchAddress("L1_DoubleIsoEG10", &L1_DoubleIsoEG10, &b_L1_DoubleIsoEG10);
   fChain->SetBranchAddress("L1_DoubleIsoEG10_Prescl", &L1_DoubleIsoEG10_Prescl, &b_L1_DoubleIsoEG10_Prescl);
   fChain->SetBranchAddress("L1_DoubleJet36_Central", &L1_DoubleJet36_Central, &b_L1_DoubleJet36_Central);
   fChain->SetBranchAddress("L1_DoubleJet36_Central_Prescl", &L1_DoubleJet36_Central_Prescl, &b_L1_DoubleJet36_Central_Prescl);
   fChain->SetBranchAddress("L1_DoubleJet44_Central", &L1_DoubleJet44_Central, &b_L1_DoubleJet44_Central);
   fChain->SetBranchAddress("L1_DoubleJet44_Central_Prescl", &L1_DoubleJet44_Central_Prescl, &b_L1_DoubleJet44_Central_Prescl);
   fChain->SetBranchAddress("L1_DoubleJet52", &L1_DoubleJet52, &b_L1_DoubleJet52);
   fChain->SetBranchAddress("L1_DoubleJet52_Prescl", &L1_DoubleJet52_Prescl, &b_L1_DoubleJet52_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0", &L1_DoubleMu0, &b_L1_DoubleMu0);
   fChain->SetBranchAddress("L1_DoubleMu0_Prescl", &L1_DoubleMu0_Prescl, &b_L1_DoubleMu0_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_HighQ", &L1_DoubleMu0_HighQ, &b_L1_DoubleMu0_HighQ);
   fChain->SetBranchAddress("L1_DoubleMu0_HighQ_Prescl", &L1_DoubleMu0_HighQ_Prescl, &b_L1_DoubleMu0_HighQ_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu0_HighQ_EtaCuts", &L1_DoubleMu0_HighQ_EtaCuts, &b_L1_DoubleMu0_HighQ_EtaCuts);
   fChain->SetBranchAddress("L1_DoubleMu0_HighQ_EtaCuts_Prescl", &L1_DoubleMu0_HighQ_EtaCuts_Prescl, &b_L1_DoubleMu0_HighQ_EtaCuts_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu3", &L1_DoubleMu3, &b_L1_DoubleMu3);
   fChain->SetBranchAddress("L1_DoubleMu3_Prescl", &L1_DoubleMu3_Prescl, &b_L1_DoubleMu3_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu3_EG5", &L1_DoubleMu3_EG5, &b_L1_DoubleMu3_EG5);
   fChain->SetBranchAddress("L1_DoubleMu3_EG5_Prescl", &L1_DoubleMu3_EG5_Prescl, &b_L1_DoubleMu3_EG5_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu3p5", &L1_DoubleMu3p5, &b_L1_DoubleMu3p5);
   fChain->SetBranchAddress("L1_DoubleMu3p5_Prescl", &L1_DoubleMu3p5_Prescl, &b_L1_DoubleMu3p5_Prescl);
   fChain->SetBranchAddress("L1_DoubleMu5_v1", &L1_DoubleMu5_v1, &b_L1_DoubleMu5_v1);
   fChain->SetBranchAddress("L1_DoubleMu5_v1_Prescl", &L1_DoubleMu5_v1_Prescl, &b_L1_DoubleMu5_v1_Prescl);
   fChain->SetBranchAddress("L1_DoubleTauJet28", &L1_DoubleTauJet28, &b_L1_DoubleTauJet28);
   fChain->SetBranchAddress("L1_DoubleTauJet28_Prescl", &L1_DoubleTauJet28_Prescl, &b_L1_DoubleTauJet28_Prescl);
   fChain->SetBranchAddress("L1_DoubleTauJet32", &L1_DoubleTauJet32, &b_L1_DoubleTauJet32);
   fChain->SetBranchAddress("L1_DoubleTauJet32_Prescl", &L1_DoubleTauJet32_Prescl, &b_L1_DoubleTauJet32_Prescl);
   fChain->SetBranchAddress("L1_DoubleTauJet36", &L1_DoubleTauJet36, &b_L1_DoubleTauJet36);
   fChain->SetBranchAddress("L1_DoubleTauJet36_Prescl", &L1_DoubleTauJet36_Prescl, &b_L1_DoubleTauJet36_Prescl);
   fChain->SetBranchAddress("L1_DoubleTauJet40", &L1_DoubleTauJet40, &b_L1_DoubleTauJet40);
   fChain->SetBranchAddress("L1_DoubleTauJet40_Prescl", &L1_DoubleTauJet40_Prescl, &b_L1_DoubleTauJet40_Prescl);
   fChain->SetBranchAddress("L1_EG10_Jet24_Central_deltaPhi1", &L1_EG10_Jet24_Central_deltaPhi1, &b_L1_EG10_Jet24_Central_deltaPhi1);
   fChain->SetBranchAddress("L1_EG10_Jet24_Central_deltaPhi1_Prescl", &L1_EG10_Jet24_Central_deltaPhi1_Prescl, &b_L1_EG10_Jet24_Central_deltaPhi1_Prescl);
   fChain->SetBranchAddress("L1_EG12_Jet24_Central_deltaPhi1", &L1_EG12_Jet24_Central_deltaPhi1, &b_L1_EG12_Jet24_Central_deltaPhi1);
   fChain->SetBranchAddress("L1_EG12_Jet24_Central_deltaPhi1_Prescl", &L1_EG12_Jet24_Central_deltaPhi1_Prescl, &b_L1_EG12_Jet24_Central_deltaPhi1_Prescl);
   fChain->SetBranchAddress("L1_EG12_TauJet20_deltaPhi1", &L1_EG12_TauJet20_deltaPhi1, &b_L1_EG12_TauJet20_deltaPhi1);
   fChain->SetBranchAddress("L1_EG12_TauJet20_deltaPhi1_Prescl", &L1_EG12_TauJet20_deltaPhi1_Prescl, &b_L1_EG12_TauJet20_deltaPhi1_Prescl);
   fChain->SetBranchAddress("L1_EG5_HTT100", &L1_EG5_HTT100, &b_L1_EG5_HTT100);
   fChain->SetBranchAddress("L1_EG5_HTT100_Prescl", &L1_EG5_HTT100_Prescl, &b_L1_EG5_HTT100_Prescl);
   fChain->SetBranchAddress("L1_EG5_HTT125", &L1_EG5_HTT125, &b_L1_EG5_HTT125);
   fChain->SetBranchAddress("L1_EG5_HTT125_Prescl", &L1_EG5_HTT125_Prescl, &b_L1_EG5_HTT125_Prescl);
   fChain->SetBranchAddress("L1_EG5_HTT75", &L1_EG5_HTT75, &b_L1_EG5_HTT75);
   fChain->SetBranchAddress("L1_EG5_HTT75_Prescl", &L1_EG5_HTT75_Prescl, &b_L1_EG5_HTT75_Prescl);
   fChain->SetBranchAddress("L1_EG5_Jet36_deltaPhi1", &L1_EG5_Jet36_deltaPhi1, &b_L1_EG5_Jet36_deltaPhi1);
   fChain->SetBranchAddress("L1_EG5_Jet36_deltaPhi1_Prescl", &L1_EG5_Jet36_deltaPhi1_Prescl, &b_L1_EG5_Jet36_deltaPhi1_Prescl);
   fChain->SetBranchAddress("L1_EG8_Jet20_Central_deltaPhi1", &L1_EG8_Jet20_Central_deltaPhi1, &b_L1_EG8_Jet20_Central_deltaPhi1);
   fChain->SetBranchAddress("L1_EG8_Jet20_Central_deltaPhi1_Prescl", &L1_EG8_Jet20_Central_deltaPhi1_Prescl, &b_L1_EG8_Jet20_Central_deltaPhi1_Prescl);
   fChain->SetBranchAddress("L1_ETM100", &L1_ETM100, &b_L1_ETM100);
   fChain->SetBranchAddress("L1_ETM100_Prescl", &L1_ETM100_Prescl, &b_L1_ETM100_Prescl);
   fChain->SetBranchAddress("L1_ETM20", &L1_ETM20, &b_L1_ETM20);
   fChain->SetBranchAddress("L1_ETM20_Prescl", &L1_ETM20_Prescl, &b_L1_ETM20_Prescl);
   fChain->SetBranchAddress("L1_ETM30", &L1_ETM30, &b_L1_ETM30);
   fChain->SetBranchAddress("L1_ETM30_Prescl", &L1_ETM30_Prescl, &b_L1_ETM30_Prescl);
   fChain->SetBranchAddress("L1_ETM50", &L1_ETM50, &b_L1_ETM50);
   fChain->SetBranchAddress("L1_ETM50_Prescl", &L1_ETM50_Prescl, &b_L1_ETM50_Prescl);
   fChain->SetBranchAddress("L1_ETM70", &L1_ETM70, &b_L1_ETM70);
   fChain->SetBranchAddress("L1_ETM70_Prescl", &L1_ETM70_Prescl, &b_L1_ETM70_Prescl);
   fChain->SetBranchAddress("L1_ETT20", &L1_ETT20, &b_L1_ETT20);
   fChain->SetBranchAddress("L1_ETT20_Prescl", &L1_ETT20_Prescl, &b_L1_ETT20_Prescl);
   fChain->SetBranchAddress("L1_ETT40", &L1_ETT40, &b_L1_ETT40);
   fChain->SetBranchAddress("L1_ETT40_Prescl", &L1_ETT40_Prescl, &b_L1_ETT40_Prescl);
   fChain->SetBranchAddress("L1_ETT60", &L1_ETT60, &b_L1_ETT60);
   fChain->SetBranchAddress("L1_ETT60_Prescl", &L1_ETT60_Prescl, &b_L1_ETT60_Prescl);
   fChain->SetBranchAddress("L1_HTM50", &L1_HTM50, &b_L1_HTM50);
   fChain->SetBranchAddress("L1_HTM50_Prescl", &L1_HTM50_Prescl, &b_L1_HTM50_Prescl);
   fChain->SetBranchAddress("L1_HTT100", &L1_HTT100, &b_L1_HTT100);
   fChain->SetBranchAddress("L1_HTT100_Prescl", &L1_HTT100_Prescl, &b_L1_HTT100_Prescl);
   fChain->SetBranchAddress("L1_HTT150", &L1_HTT150, &b_L1_HTT150);
   fChain->SetBranchAddress("L1_HTT150_Prescl", &L1_HTT150_Prescl, &b_L1_HTT150_Prescl);
   fChain->SetBranchAddress("L1_HTT50", &L1_HTT50, &b_L1_HTT50);
   fChain->SetBranchAddress("L1_HTT50_Prescl", &L1_HTT50_Prescl, &b_L1_HTT50_Prescl);
   fChain->SetBranchAddress("L1_HTT50_HTM30", &L1_HTT50_HTM30, &b_L1_HTT50_HTM30);
   fChain->SetBranchAddress("L1_HTT50_HTM30_Prescl", &L1_HTT50_HTM30_Prescl, &b_L1_HTT50_HTM30_Prescl);
   fChain->SetBranchAddress("L1_HTT50_HTM50", &L1_HTT50_HTM50, &b_L1_HTT50_HTM50);
   fChain->SetBranchAddress("L1_HTT50_HTM50_Prescl", &L1_HTT50_HTM50_Prescl, &b_L1_HTT50_HTM50_Prescl);
   fChain->SetBranchAddress("L1_HTT75", &L1_HTT75, &b_L1_HTT75);
   fChain->SetBranchAddress("L1_HTT75_Prescl", &L1_HTT75_Prescl, &b_L1_HTT75_Prescl);
   fChain->SetBranchAddress("L1_InterBunch_Bsc", &L1_InterBunch_Bsc, &b_L1_InterBunch_Bsc);
   fChain->SetBranchAddress("L1_InterBunch_Bsc_Prescl", &L1_InterBunch_Bsc_Prescl, &b_L1_InterBunch_Bsc_Prescl);
   fChain->SetBranchAddress("L1_InterBunch_Hf", &L1_InterBunch_Hf, &b_L1_InterBunch_Hf);
   fChain->SetBranchAddress("L1_InterBunch_Hf_Prescl", &L1_InterBunch_Hf_Prescl, &b_L1_InterBunch_Hf_Prescl);
   fChain->SetBranchAddress("L1_Mu0_HTT50", &L1_Mu0_HTT50, &b_L1_Mu0_HTT50);
   fChain->SetBranchAddress("L1_Mu0_HTT50_Prescl", &L1_Mu0_HTT50_Prescl, &b_L1_Mu0_HTT50_Prescl);
   fChain->SetBranchAddress("L1_Mu0_HTT75", &L1_Mu0_HTT75, &b_L1_Mu0_HTT75);
   fChain->SetBranchAddress("L1_Mu0_HTT75_Prescl", &L1_Mu0_HTT75_Prescl, &b_L1_Mu0_HTT75_Prescl);
   fChain->SetBranchAddress("L1_Mu10_Jet36_Central", &L1_Mu10_Jet36_Central, &b_L1_Mu10_Jet36_Central);
   fChain->SetBranchAddress("L1_Mu10_Jet36_Central_Prescl", &L1_Mu10_Jet36_Central_Prescl, &b_L1_Mu10_Jet36_Central_Prescl);
   fChain->SetBranchAddress("L1_Mu12_EG5", &L1_Mu12_EG5, &b_L1_Mu12_EG5);
   fChain->SetBranchAddress("L1_Mu12_EG5_Prescl", &L1_Mu12_EG5_Prescl, &b_L1_Mu12_EG5_Prescl);
   fChain->SetBranchAddress("L1_Mu3_DoubleEG5", &L1_Mu3_DoubleEG5, &b_L1_Mu3_DoubleEG5);
   fChain->SetBranchAddress("L1_Mu3_DoubleEG5_Prescl", &L1_Mu3_DoubleEG5_Prescl, &b_L1_Mu3_DoubleEG5_Prescl);
   fChain->SetBranchAddress("L1_Mu3_EG5", &L1_Mu3_EG5, &b_L1_Mu3_EG5);
   fChain->SetBranchAddress("L1_Mu3_EG5_Prescl", &L1_Mu3_EG5_Prescl, &b_L1_Mu3_EG5_Prescl);
   fChain->SetBranchAddress("L1_Mu3_Jet16_Central", &L1_Mu3_Jet16_Central, &b_L1_Mu3_Jet16_Central);
   fChain->SetBranchAddress("L1_Mu3_Jet16_Central_Prescl", &L1_Mu3_Jet16_Central_Prescl, &b_L1_Mu3_Jet16_Central_Prescl);
   fChain->SetBranchAddress("L1_Mu3_Jet20_Central", &L1_Mu3_Jet20_Central, &b_L1_Mu3_Jet20_Central);
   fChain->SetBranchAddress("L1_Mu3_Jet20_Central_Prescl", &L1_Mu3_Jet20_Central_Prescl, &b_L1_Mu3_Jet20_Central_Prescl);
   fChain->SetBranchAddress("L1_Mu3_Jet28_Central", &L1_Mu3_Jet28_Central, &b_L1_Mu3_Jet28_Central);
   fChain->SetBranchAddress("L1_Mu3_Jet28_Central_Prescl", &L1_Mu3_Jet28_Central_Prescl, &b_L1_Mu3_Jet28_Central_Prescl);
   fChain->SetBranchAddress("L1_Mu5_EG12", &L1_Mu5_EG12, &b_L1_Mu5_EG12);
   fChain->SetBranchAddress("L1_Mu5_EG12_Prescl", &L1_Mu5_EG12_Prescl, &b_L1_Mu5_EG12_Prescl);
   fChain->SetBranchAddress("L1_Mu7_EG5", &L1_Mu7_EG5, &b_L1_Mu7_EG5);
   fChain->SetBranchAddress("L1_Mu7_EG5_Prescl", &L1_Mu7_EG5_Prescl, &b_L1_Mu7_EG5_Prescl);
   fChain->SetBranchAddress("L1_Mu7_Jet20_Central", &L1_Mu7_Jet20_Central, &b_L1_Mu7_Jet20_Central);
   fChain->SetBranchAddress("L1_Mu7_Jet20_Central_Prescl", &L1_Mu7_Jet20_Central_Prescl, &b_L1_Mu7_Jet20_Central_Prescl);
   fChain->SetBranchAddress("L1_Mu7_TauJet16", &L1_Mu7_TauJet16, &b_L1_Mu7_TauJet16);
   fChain->SetBranchAddress("L1_Mu7_TauJet16_Prescl", &L1_Mu7_TauJet16_Prescl, &b_L1_Mu7_TauJet16_Prescl);
   fChain->SetBranchAddress("L1_MuOpen_EG12", &L1_MuOpen_EG12, &b_L1_MuOpen_EG12);
   fChain->SetBranchAddress("L1_MuOpen_EG12_Prescl", &L1_MuOpen_EG12_Prescl, &b_L1_MuOpen_EG12_Prescl);
   fChain->SetBranchAddress("L1_MuOpen_EG5", &L1_MuOpen_EG5, &b_L1_MuOpen_EG5);
   fChain->SetBranchAddress("L1_MuOpen_EG5_Prescl", &L1_MuOpen_EG5_Prescl, &b_L1_MuOpen_EG5_Prescl);
   fChain->SetBranchAddress("L1_PreCollisions", &L1_PreCollisions, &b_L1_PreCollisions);
   fChain->SetBranchAddress("L1_PreCollisions_Prescl", &L1_PreCollisions_Prescl, &b_L1_PreCollisions_Prescl);
   fChain->SetBranchAddress("L1_QuadJet20_Central", &L1_QuadJet20_Central, &b_L1_QuadJet20_Central);
   fChain->SetBranchAddress("L1_QuadJet20_Central_Prescl", &L1_QuadJet20_Central_Prescl, &b_L1_QuadJet20_Central_Prescl);
   fChain->SetBranchAddress("L1_QuadJet28_Central", &L1_QuadJet28_Central, &b_L1_QuadJet28_Central);
   fChain->SetBranchAddress("L1_QuadJet28_Central_Prescl", &L1_QuadJet28_Central_Prescl, &b_L1_QuadJet28_Central_Prescl);
   fChain->SetBranchAddress("L1_SingleEG12", &L1_SingleEG12, &b_L1_SingleEG12);
   fChain->SetBranchAddress("L1_SingleEG12_Prescl", &L1_SingleEG12_Prescl, &b_L1_SingleEG12_Prescl);
   fChain->SetBranchAddress("L1_SingleEG12_Eta1p39", &L1_SingleEG12_Eta1p39, &b_L1_SingleEG12_Eta1p39);
   fChain->SetBranchAddress("L1_SingleEG12_Eta1p39_Prescl", &L1_SingleEG12_Eta1p39_Prescl, &b_L1_SingleEG12_Eta1p39_Prescl);
   fChain->SetBranchAddress("L1_SingleEG12_Eta2p17", &L1_SingleEG12_Eta2p17, &b_L1_SingleEG12_Eta2p17);
   fChain->SetBranchAddress("L1_SingleEG12_Eta2p17_Prescl", &L1_SingleEG12_Eta2p17_Prescl, &b_L1_SingleEG12_Eta2p17_Prescl);
   fChain->SetBranchAddress("L1_SingleEG15", &L1_SingleEG15, &b_L1_SingleEG15);
   fChain->SetBranchAddress("L1_SingleEG15_Prescl", &L1_SingleEG15_Prescl, &b_L1_SingleEG15_Prescl);
   fChain->SetBranchAddress("L1_SingleEG20", &L1_SingleEG20, &b_L1_SingleEG20);
   fChain->SetBranchAddress("L1_SingleEG20_Prescl", &L1_SingleEG20_Prescl, &b_L1_SingleEG20_Prescl);
   fChain->SetBranchAddress("L1_SingleEG30", &L1_SingleEG30, &b_L1_SingleEG30);
   fChain->SetBranchAddress("L1_SingleEG30_Prescl", &L1_SingleEG30_Prescl, &b_L1_SingleEG30_Prescl);
   fChain->SetBranchAddress("L1_SingleEG5", &L1_SingleEG5, &b_L1_SingleEG5);
   fChain->SetBranchAddress("L1_SingleEG5_Prescl", &L1_SingleEG5_Prescl, &b_L1_SingleEG5_Prescl);
   fChain->SetBranchAddress("L1_SingleIsoEG12", &L1_SingleIsoEG12, &b_L1_SingleIsoEG12);
   fChain->SetBranchAddress("L1_SingleIsoEG12_Prescl", &L1_SingleIsoEG12_Prescl, &b_L1_SingleIsoEG12_Prescl);
   fChain->SetBranchAddress("L1_SingleIsoEG12_Eta1p39", &L1_SingleIsoEG12_Eta1p39, &b_L1_SingleIsoEG12_Eta1p39);
   fChain->SetBranchAddress("L1_SingleIsoEG12_Eta1p39_Prescl", &L1_SingleIsoEG12_Eta1p39_Prescl, &b_L1_SingleIsoEG12_Eta1p39_Prescl);
   fChain->SetBranchAddress("L1_SingleIsoEG12_Eta2p17", &L1_SingleIsoEG12_Eta2p17, &b_L1_SingleIsoEG12_Eta2p17);
   fChain->SetBranchAddress("L1_SingleIsoEG12_Eta2p17_Prescl", &L1_SingleIsoEG12_Eta2p17_Prescl, &b_L1_SingleIsoEG12_Eta2p17_Prescl);
   fChain->SetBranchAddress("L1_SingleJet16", &L1_SingleJet16, &b_L1_SingleJet16);
   fChain->SetBranchAddress("L1_SingleJet16_Prescl", &L1_SingleJet16_Prescl, &b_L1_SingleJet16_Prescl);
   fChain->SetBranchAddress("L1_SingleJet20_NotBptxOR", &L1_SingleJet20_NotBptxOR, &b_L1_SingleJet20_NotBptxOR);
   fChain->SetBranchAddress("L1_SingleJet20_NotBptxOR_Prescl", &L1_SingleJet20_NotBptxOR_Prescl, &b_L1_SingleJet20_NotBptxOR_Prescl);
   fChain->SetBranchAddress("L1_SingleJet20_NotBptxOR_NotMuBeamHalo", &L1_SingleJet20_NotBptxOR_NotMuBeamHalo, &b_L1_SingleJet20_NotBptxOR_NotMuBeamHalo);
   fChain->SetBranchAddress("L1_SingleJet20_NotBptxOR_NotMuBeamHalo_Prescl", &L1_SingleJet20_NotBptxOR_NotMuBeamHalo_Prescl, &b_L1_SingleJet20_NotBptxOR_NotMuBeamHalo_Prescl);
   fChain->SetBranchAddress("L1_SingleJet32_NotBptxOR_NotMuBeamHalo", &L1_SingleJet32_NotBptxOR_NotMuBeamHalo, &b_L1_SingleJet32_NotBptxOR_NotMuBeamHalo);
   fChain->SetBranchAddress("L1_SingleJet32_NotBptxOR_NotMuBeamHalo_Prescl", &L1_SingleJet32_NotBptxOR_NotMuBeamHalo_Prescl, &b_L1_SingleJet32_NotBptxOR_NotMuBeamHalo_Prescl);
   fChain->SetBranchAddress("L1_SingleJet36", &L1_SingleJet36, &b_L1_SingleJet36);
   fChain->SetBranchAddress("L1_SingleJet36_Prescl", &L1_SingleJet36_Prescl, &b_L1_SingleJet36_Prescl);
   fChain->SetBranchAddress("L1_SingleJet36_FwdVeto", &L1_SingleJet36_FwdVeto, &b_L1_SingleJet36_FwdVeto);
   fChain->SetBranchAddress("L1_SingleJet36_FwdVeto_Prescl", &L1_SingleJet36_FwdVeto_Prescl, &b_L1_SingleJet36_FwdVeto_Prescl);
   fChain->SetBranchAddress("L1_SingleJet52", &L1_SingleJet52, &b_L1_SingleJet52);
   fChain->SetBranchAddress("L1_SingleJet52_Prescl", &L1_SingleJet52_Prescl, &b_L1_SingleJet52_Prescl);
   fChain->SetBranchAddress("L1_SingleJet68", &L1_SingleJet68, &b_L1_SingleJet68);
   fChain->SetBranchAddress("L1_SingleJet68_Prescl", &L1_SingleJet68_Prescl, &b_L1_SingleJet68_Prescl);
   fChain->SetBranchAddress("L1_SingleJet8", &L1_SingleJet8, &b_L1_SingleJet8);
   fChain->SetBranchAddress("L1_SingleJet8_Prescl", &L1_SingleJet8_Prescl, &b_L1_SingleJet8_Prescl);
   fChain->SetBranchAddress("L1_SingleJet80_Central", &L1_SingleJet80_Central, &b_L1_SingleJet80_Central);
   fChain->SetBranchAddress("L1_SingleJet80_Central_Prescl", &L1_SingleJet80_Central_Prescl, &b_L1_SingleJet80_Central_Prescl);
   fChain->SetBranchAddress("L1_SingleJet92", &L1_SingleJet92, &b_L1_SingleJet92);
   fChain->SetBranchAddress("L1_SingleJet92_Prescl", &L1_SingleJet92_Prescl, &b_L1_SingleJet92_Prescl);
   fChain->SetBranchAddress("L1_SingleJet92_Central", &L1_SingleJet92_Central, &b_L1_SingleJet92_Central);
   fChain->SetBranchAddress("L1_SingleJet92_Central_Prescl", &L1_SingleJet92_Central_Prescl, &b_L1_SingleJet92_Central_Prescl);
   fChain->SetBranchAddress("L1_SingleMu10", &L1_SingleMu10, &b_L1_SingleMu10);
   fChain->SetBranchAddress("L1_SingleMu10_Prescl", &L1_SingleMu10_Prescl, &b_L1_SingleMu10_Prescl);
   fChain->SetBranchAddress("L1_SingleMu12", &L1_SingleMu12, &b_L1_SingleMu12);
   fChain->SetBranchAddress("L1_SingleMu12_Prescl", &L1_SingleMu12_Prescl, &b_L1_SingleMu12_Prescl);
   fChain->SetBranchAddress("L1_SingleMu12_Debug", &L1_SingleMu12_Debug, &b_L1_SingleMu12_Debug);
   fChain->SetBranchAddress("L1_SingleMu12_Debug_Prescl", &L1_SingleMu12_Debug_Prescl, &b_L1_SingleMu12_Debug_Prescl);
   fChain->SetBranchAddress("L1_SingleMu16", &L1_SingleMu16, &b_L1_SingleMu16);
   fChain->SetBranchAddress("L1_SingleMu16_Prescl", &L1_SingleMu16_Prescl, &b_L1_SingleMu16_Prescl);
   fChain->SetBranchAddress("L1_SingleMu20", &L1_SingleMu20, &b_L1_SingleMu20);
   fChain->SetBranchAddress("L1_SingleMu20_Prescl", &L1_SingleMu20_Prescl, &b_L1_SingleMu20_Prescl);
   fChain->SetBranchAddress("L1_SingleMu25", &L1_SingleMu25, &b_L1_SingleMu25);
   fChain->SetBranchAddress("L1_SingleMu25_Prescl", &L1_SingleMu25_Prescl, &b_L1_SingleMu25_Prescl);
   fChain->SetBranchAddress("L1_SingleMu3", &L1_SingleMu3, &b_L1_SingleMu3);
   fChain->SetBranchAddress("L1_SingleMu3_Prescl", &L1_SingleMu3_Prescl, &b_L1_SingleMu3_Prescl);
   fChain->SetBranchAddress("L1_SingleMu5_Eta1p5_Q80_v1", &L1_SingleMu5_Eta1p5_Q80_v1, &b_L1_SingleMu5_Eta1p5_Q80_v1);
   fChain->SetBranchAddress("L1_SingleMu5_Eta1p5_Q80_v1_Prescl", &L1_SingleMu5_Eta1p5_Q80_v1_Prescl, &b_L1_SingleMu5_Eta1p5_Q80_v1_Prescl);
   fChain->SetBranchAddress("L1_SingleMu7", &L1_SingleMu7, &b_L1_SingleMu7);
   fChain->SetBranchAddress("L1_SingleMu7_Prescl", &L1_SingleMu7_Prescl, &b_L1_SingleMu7_Prescl);
   fChain->SetBranchAddress("L1_SingleMu7_Barrel", &L1_SingleMu7_Barrel, &b_L1_SingleMu7_Barrel);
   fChain->SetBranchAddress("L1_SingleMu7_Barrel_Prescl", &L1_SingleMu7_Barrel_Prescl, &b_L1_SingleMu7_Barrel_Prescl);
   fChain->SetBranchAddress("L1_SingleMu7_Eta2p1", &L1_SingleMu7_Eta2p1, &b_L1_SingleMu7_Eta2p1);
   fChain->SetBranchAddress("L1_SingleMu7_Eta2p1_Prescl", &L1_SingleMu7_Eta2p1_Prescl, &b_L1_SingleMu7_Eta2p1_Prescl);
   fChain->SetBranchAddress("L1_SingleMuBeamHalo", &L1_SingleMuBeamHalo, &b_L1_SingleMuBeamHalo);
   fChain->SetBranchAddress("L1_SingleMuBeamHalo_Prescl", &L1_SingleMuBeamHalo_Prescl, &b_L1_SingleMuBeamHalo_Prescl);
   fChain->SetBranchAddress("L1_SingleMuOpen", &L1_SingleMuOpen, &b_L1_SingleMuOpen);
   fChain->SetBranchAddress("L1_SingleMuOpen_Prescl", &L1_SingleMuOpen_Prescl, &b_L1_SingleMuOpen_Prescl);
   fChain->SetBranchAddress("L1_SingleTauJet52", &L1_SingleTauJet52, &b_L1_SingleTauJet52);
   fChain->SetBranchAddress("L1_SingleTauJet52_Prescl", &L1_SingleTauJet52_Prescl, &b_L1_SingleTauJet52_Prescl);
   fChain->SetBranchAddress("L1_SingleTauJet68", &L1_SingleTauJet68, &b_L1_SingleTauJet68);
   fChain->SetBranchAddress("L1_SingleTauJet68_Prescl", &L1_SingleTauJet68_Prescl, &b_L1_SingleTauJet68_Prescl);
   fChain->SetBranchAddress("L1_SingleTauJet80", &L1_SingleTauJet80, &b_L1_SingleTauJet80);
   fChain->SetBranchAddress("L1_SingleTauJet80_Prescl", &L1_SingleTauJet80_Prescl, &b_L1_SingleTauJet80_Prescl);
   fChain->SetBranchAddress("L1_TripleEG5", &L1_TripleEG5, &b_L1_TripleEG5);
   fChain->SetBranchAddress("L1_TripleEG5_Prescl", &L1_TripleEG5_Prescl, &b_L1_TripleEG5_Prescl);
   fChain->SetBranchAddress("L1_TripleEG7", &L1_TripleEG7, &b_L1_TripleEG7);
   fChain->SetBranchAddress("L1_TripleEG7_Prescl", &L1_TripleEG7_Prescl, &b_L1_TripleEG7_Prescl);
   fChain->SetBranchAddress("L1_TripleEG_8_5_5", &L1_TripleEG_8_5_5, &b_L1_TripleEG_8_5_5);
   fChain->SetBranchAddress("L1_TripleEG_8_5_5_Prescl", &L1_TripleEG_8_5_5_Prescl, &b_L1_TripleEG_8_5_5_Prescl);
   fChain->SetBranchAddress("L1_TripleEG_8_8_5", &L1_TripleEG_8_8_5, &b_L1_TripleEG_8_8_5);
   fChain->SetBranchAddress("L1_TripleEG_8_8_5_Prescl", &L1_TripleEG_8_8_5_Prescl, &b_L1_TripleEG_8_8_5_Prescl);
   fChain->SetBranchAddress("L1_TripleJet28_Central", &L1_TripleJet28_Central, &b_L1_TripleJet28_Central);
   fChain->SetBranchAddress("L1_TripleJet28_Central_Prescl", &L1_TripleJet28_Central_Prescl, &b_L1_TripleJet28_Central_Prescl);
   fChain->SetBranchAddress("L1_ZeroBias", &L1_ZeroBias, &b_L1_ZeroBias);
   fChain->SetBranchAddress("L1_ZeroBias_Prescl", &L1_ZeroBias_Prescl, &b_L1_ZeroBias_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_minus.v0", &L1Tech_BPTX_minus_v0, &b_L1Tech_BPTX_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_minus.v0_Prescl", &L1Tech_BPTX_minus_v0_Prescl, &b_L1Tech_BPTX_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0", &L1Tech_BPTX_minus_AND_not_plus_v0, &b_L1Tech_BPTX_minus_AND_not_plus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_minus_AND_not_plus.v0_Prescl", &L1Tech_BPTX_minus_AND_not_plus_v0_Prescl, &b_L1Tech_BPTX_minus_AND_not_plus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus.v0", &L1Tech_BPTX_plus_v0, &b_L1Tech_BPTX_plus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus.v0_Prescl", &L1Tech_BPTX_plus_v0_Prescl, &b_L1Tech_BPTX_plus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0", &L1Tech_BPTX_plus_AND_NOT_minus_v0, &b_L1Tech_BPTX_plus_AND_NOT_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_NOT_minus.v0_Prescl", &L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl, &b_L1Tech_BPTX_plus_AND_NOT_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0", &L1Tech_BPTX_plus_AND_minus_v0, &b_L1Tech_BPTX_plus_AND_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus.v0_Prescl", &L1Tech_BPTX_plus_AND_minus_v0_Prescl, &b_L1Tech_BPTX_plus_AND_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0", &L1Tech_BPTX_plus_AND_minus_instance1_v0, &b_L1Tech_BPTX_plus_AND_minus_instance1_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_AND_minus_instance1.v0_Prescl", &L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl, &b_L1Tech_BPTX_plus_AND_minus_instance1_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0", &L1Tech_BPTX_plus_OR_minus_v0, &b_L1Tech_BPTX_plus_OR_minus_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_plus_OR_minus.v0_Prescl", &L1Tech_BPTX_plus_OR_minus_v0_Prescl, &b_L1Tech_BPTX_plus_OR_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BPTX_quiet.v0", &L1Tech_BPTX_quiet_v0, &b_L1Tech_BPTX_quiet_v0);
   fChain->SetBranchAddress("L1Tech_BPTX_quiet.v0_Prescl", &L1Tech_BPTX_quiet_v0_Prescl, &b_L1Tech_BPTX_quiet_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0", &L1Tech_BSC_HighMultiplicity_v0, &b_L1Tech_BSC_HighMultiplicity_v0);
   fChain->SetBranchAddress("L1Tech_BSC_HighMultiplicity.v0_Prescl", &L1Tech_BSC_HighMultiplicity_v0_Prescl, &b_L1Tech_BSC_HighMultiplicity_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0", &L1Tech_BSC_halo_beam1_inner_v0, &b_L1Tech_BSC_halo_beam1_inner_v0);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam1_inner.v0_Prescl", &L1Tech_BSC_halo_beam1_inner_v0_Prescl, &b_L1Tech_BSC_halo_beam1_inner_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0", &L1Tech_BSC_halo_beam1_outer_v0, &b_L1Tech_BSC_halo_beam1_outer_v0);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam1_outer.v0_Prescl", &L1Tech_BSC_halo_beam1_outer_v0_Prescl, &b_L1Tech_BSC_halo_beam1_outer_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0", &L1Tech_BSC_halo_beam2_inner_v0, &b_L1Tech_BSC_halo_beam2_inner_v0);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam2_inner.v0_Prescl", &L1Tech_BSC_halo_beam2_inner_v0_Prescl, &b_L1Tech_BSC_halo_beam2_inner_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0", &L1Tech_BSC_halo_beam2_outer_v0, &b_L1Tech_BSC_halo_beam2_outer_v0);
   fChain->SetBranchAddress("L1Tech_BSC_halo_beam2_outer.v0_Prescl", &L1Tech_BSC_halo_beam2_outer_v0_Prescl, &b_L1Tech_BSC_halo_beam2_outer_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_OR.v0", &L1Tech_BSC_minBias_OR_v0, &b_L1Tech_BSC_minBias_OR_v0);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_OR.v0_Prescl", &L1Tech_BSC_minBias_OR_v0_Prescl, &b_L1Tech_BSC_minBias_OR_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0", &L1Tech_BSC_minBias_inner_threshold1_v0, &b_L1Tech_BSC_minBias_inner_threshold1_v0);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold1.v0_Prescl", &L1Tech_BSC_minBias_inner_threshold1_v0_Prescl, &b_L1Tech_BSC_minBias_inner_threshold1_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0", &L1Tech_BSC_minBias_inner_threshold2_v0, &b_L1Tech_BSC_minBias_inner_threshold2_v0);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_inner_threshold2.v0_Prescl", &L1Tech_BSC_minBias_inner_threshold2_v0_Prescl, &b_L1Tech_BSC_minBias_inner_threshold2_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0", &L1Tech_BSC_minBias_threshold1_v0, &b_L1Tech_BSC_minBias_threshold1_v0);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_threshold1.v0_Prescl", &L1Tech_BSC_minBias_threshold1_v0_Prescl, &b_L1Tech_BSC_minBias_threshold1_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0", &L1Tech_BSC_minBias_threshold2_v0, &b_L1Tech_BSC_minBias_threshold2_v0);
   fChain->SetBranchAddress("L1Tech_BSC_minBias_threshold2.v0_Prescl", &L1Tech_BSC_minBias_threshold2_v0_Prescl, &b_L1Tech_BSC_minBias_threshold2_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_splash_beam1.v0", &L1Tech_BSC_splash_beam1_v0, &b_L1Tech_BSC_splash_beam1_v0);
   fChain->SetBranchAddress("L1Tech_BSC_splash_beam1.v0_Prescl", &L1Tech_BSC_splash_beam1_v0_Prescl, &b_L1Tech_BSC_splash_beam1_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_BSC_splash_beam2.v0", &L1Tech_BSC_splash_beam2_v0, &b_L1Tech_BSC_splash_beam2_v0);
   fChain->SetBranchAddress("L1Tech_BSC_splash_beam2.v0_Prescl", &L1Tech_BSC_splash_beam2_v0_Prescl, &b_L1Tech_BSC_splash_beam2_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0", &L1Tech_CASTOR_HaloMuon_v0, &b_L1Tech_CASTOR_HaloMuon_v0);
   fChain->SetBranchAddress("L1Tech_CASTOR_HaloMuon.v0_Prescl", &L1Tech_CASTOR_HaloMuon_v0_Prescl, &b_L1Tech_CASTOR_HaloMuon_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_DT_GlobalOR.v0", &L1Tech_DT_GlobalOR_v0, &b_L1Tech_DT_GlobalOR_v0);
   fChain->SetBranchAddress("L1Tech_DT_GlobalOR.v0_Prescl", &L1Tech_DT_GlobalOR_v0_Prescl, &b_L1Tech_DT_GlobalOR_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0", &L1Tech_HCAL_HBHE_totalOR_v0, &b_L1Tech_HCAL_HBHE_totalOR_v0);
   fChain->SetBranchAddress("L1Tech_HCAL_HBHE_totalOR.v0_Prescl", &L1Tech_HCAL_HBHE_totalOR_v0_Prescl, &b_L1Tech_HCAL_HBHE_totalOR_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_MMP_or_MPP.v0", &L1Tech_HCAL_HF_MMP_or_MPP_v0, &b_L1Tech_HCAL_HF_MMP_or_MPP_v0);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_MMP_or_MPP.v0_Prescl", &L1Tech_HCAL_HF_MMP_or_MPP_v0_Prescl, &b_L1Tech_HCAL_HF_MMP_or_MPP_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_MM_or_PP_or_PM.v0", &L1Tech_HCAL_HF_MM_or_PP_or_PM_v0, &b_L1Tech_HCAL_HF_MM_or_PP_or_PM_v0);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_MM_or_PP_or_PM.v0_Prescl", &L1Tech_HCAL_HF_MM_or_PP_or_PM_v0_Prescl, &b_L1Tech_HCAL_HF_MM_or_PP_or_PM_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_coincidence_PM.v1", &L1Tech_HCAL_HF_coincidence_PM_v1, &b_L1Tech_HCAL_HF_coincidence_PM_v1);
   fChain->SetBranchAddress("L1Tech_HCAL_HF_coincidence_PM.v1_Prescl", &L1Tech_HCAL_HF_coincidence_PM_v1_Prescl, &b_L1Tech_HCAL_HF_coincidence_PM_v1_Prescl);
   fChain->SetBranchAddress("L1Tech_HCAL_HO_totalOR.v0", &L1Tech_HCAL_HO_totalOR_v0, &b_L1Tech_HCAL_HO_totalOR_v0);
   fChain->SetBranchAddress("L1Tech_HCAL_HO_totalOR.v0_Prescl", &L1Tech_HCAL_HO_totalOR_v0_Prescl, &b_L1Tech_HCAL_HO_totalOR_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0", &L1Tech_RPC_TTU_RB0_Cosmics_v0, &b_L1Tech_RPC_TTU_RB0_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RB0_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_RB0_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0", &L1Tech_RPC_TTU_RBminus1_Cosmics_v0, &b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBminus1_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_RBminus1_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0", &L1Tech_RPC_TTU_RBminus2_Cosmics_v0, &b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBminus2_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_RBminus2_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0", &L1Tech_RPC_TTU_RBplus1_Cosmics_v0, &b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus1_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_RBplus1_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0", &L1Tech_RPC_TTU_RBplus2_Cosmics_v0, &b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBplus2_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_RBplus2_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0", &L1Tech_RPC_TTU_RBst1_collisions_v0, &b_L1Tech_RPC_TTU_RBst1_collisions_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_RBst1_collisions.v0_Prescl", &L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl, &b_L1Tech_RPC_TTU_RBst1_collisions_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0", &L1Tech_RPC_TTU_barrel_Cosmics_v0, &b_L1Tech_RPC_TTU_barrel_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_barrel_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_barrel_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0", &L1Tech_RPC_TTU_pointing_Cosmics_v0, &b_L1Tech_RPC_TTU_pointing_Cosmics_v0);
   fChain->SetBranchAddress("L1Tech_RPC_TTU_pointing_Cosmics.v0_Prescl", &L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl, &b_L1Tech_RPC_TTU_pointing_Cosmics_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0", &L1Tech_ZDC_Scint_loose_vertex_v0, &b_L1Tech_ZDC_Scint_loose_vertex_v0);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_loose_vertex.v0_Prescl", &L1Tech_ZDC_Scint_loose_vertex_v0_Prescl, &b_L1Tech_ZDC_Scint_loose_vertex_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0", &L1Tech_ZDC_Scint_minus_v0, &b_L1Tech_ZDC_Scint_minus_v0);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_minus.v0_Prescl", &L1Tech_ZDC_Scint_minus_v0_Prescl, &b_L1Tech_ZDC_Scint_minus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0", &L1Tech_ZDC_Scint_plus_v0, &b_L1Tech_ZDC_Scint_plus_v0);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_plus.v0_Prescl", &L1Tech_ZDC_Scint_plus_v0_Prescl, &b_L1Tech_ZDC_Scint_plus_v0_Prescl);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0", &L1Tech_ZDC_Scint_tight_vertex_v0, &b_L1Tech_ZDC_Scint_tight_vertex_v0);
   fChain->SetBranchAddress("L1Tech_ZDC_Scint_tight_vertex.v0_Prescl", &L1Tech_ZDC_Scint_tight_vertex_v0_Prescl, &b_L1Tech_ZDC_Scint_tight_vertex_v0_Prescl);
   Notify();
}

Bool_t HLT::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HLT::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HLT::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HLT_cxx
