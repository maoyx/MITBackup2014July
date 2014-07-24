#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TVector3.h"
#include "TMath.h"
#include "TF1.h"
#include <TH1D.h>
#include <TNtuple.h>
#include "TChain.h"
#include <iostream>
#include <TString.h>
#include <TCut.h>
#include "../SmearingFactors.h"
#include "hiForest.h"
#include "commonSetup.h"

using namespace std;

//define the kinematics cuts for the analysis
const double conesize = 0.3 ;
const double deltacone = 0.05 ;

//const double radius = 0.025;

//const int nrbin = 10 ;
//double rbin[nrbin+1]={0.0,0.05,0.10, 0.15, 0.20,0.25,0.30,0.35,0.40,0.45,0.50};

const int nrbin = 6 ;
double rbin[nrbin+1]={0.0,0.05,0.10, 0.15, 0.20,0.25,0.30};

const double etacut = 2.0 ;
//const double dphicut = TMath::TwoPi()/3. ;
const double dphicut = 7*TMath::Pi()/8. ;
const double leadingjetcut = 50. ;
const double trackcut = 1.;
const double tracketacut = 2.4; //make sure the tracks around jet cone inside eta range
const double btagcut = 2; //btagging cut on ssvHighEff

////for etalimit = 0.3, to remove the possible overlap region by ER method 
const double etalimit = 0.3 ; 

int pthat ; //= 120 ; //=300 ; //30 and 80 for pp; 30,50,80,120,170,200 for PbPb MC 
int ptmax ; //= 170 ;
TString coll = "PP";
TString para ="Full" ; //PYQUEN parameters setting: Wide or Full

//do tracking corrections
const bool doTrackCorrections = kFALSE; //for tracking efficiency correction
TString corrMet = "Hist" ; //Hist table from Frank, or Para from Krisztian
TrackingParam *trackCorrFromParam;

vector<TrackingCorrections*> trackCorrections;

//for jet pt smearing and reweight
const bool DoSmear = kFALSE ;
const bool DoJetPtWeight = kFALSE ; //!only be true when DoSmear TRUE 

const bool DoSumPtNorm = kFALSE ;
//weight factor from vertex and centrality
double weight =1. ;

TString intputFile ;

//TString dataPath="/Users/ymao/group/CMS/hiForest";
TString dataPath ;

//if it is pp, no centrality bins, only one
const int nbin = 1 ;
const int centr[] ={0,100};
////for HI centrality bin
//const int nbin = 4 ;
//const int centr[] ={0,10,30,50,100};
//const int nbin = 6 ;
//const int centr[] ={0,5, 10, 30,50, 70, 90};

//const double pt[]={100., 120., 140., 160., 200., 300., 500.};
const int nptbin = 1 ;
const double pt[]={50., 500.};
//const int ntrkptbin = 6 ;
//const double trkpt[]={1., 2., 4., 8., 16., 32., 500.};

const int ntrkptbin = 4 ;
const double trkpt[]={1.,4., 16., 64., 500.};

const Double_t jetPtBin[] = {30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,400};
//const Double_t jetPtBin[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 200, 240, 300};
//const Double_t jetPtBin[] = {100, 110, 120, 130, 140, 150, 160, 180, 200, 240, 300, 500};
const int nJetPtBin = sizeof(jetPtBin)/sizeof(Double_t)-1 ;

//const int nPtBin = 27;
//double TrkBin[nPtBin+1] = {0, 0.5, 1, 1.203915, 1.449412, 1.74497, 2.100796, 2.529181, 3.04492, 3.665826, 4.413344, 5.313293, 6.396755, 7.701152, 9.271536, 11.16214, 13.43828, 16.17855, 19.47761, 23.44939, 28.23108, 33.98783, 40.91848, 49.26238, 59.30774, 71.40151, 85.96137, 103.4902}; 

const Double_t TrkBin[]={0, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.5, 3.0, 4., 5., 6., 8.,10.,12.,15.,20.,25.,30.,45.,60.,80.,100., 120.,150., 180.,300.,500.};
const int nPtBin = sizeof(TrkBin)/sizeof(Double_t)-1 ;

const int netabin = 10 ;
const double deta[]={-2.5, -2.0, -1.5, -1.0, -0.5, 0.0,0.5,1.0,1.5,2.0, 2.5} ;

class hist_class {
public:
    hist_class(TString the_desc);
    void Delete();
    void Write();
    
    TString desc;
    bool IsMC ;
    
    TH1F * NEvents[nbin];
    TH1F * NJets[nbin];
    TH1F * Ntrack[nbin];
    TH1F * jetpt[nbin];
    TH1F * quarkjetpt[nbin];
    TH1F * bjetpt[nbin];
    TH1F * gluonjetpt[nbin];
    TH1F * rawjetpt[nbin];
    TH2F * jesrawpt[nbin];
    TH2F * jeteta[nbin];
    TH2F * jetphi[nbin];
    TH2F * jetsmf[nbin]; //jet smear factor
    TH2F * jetms[nbin]; //mean shift

   //b-tagging variables
   TH2F * jetSSVHE[nbin];
   TH2F * BjetSSVHE[nbin];
   TH2F * jetProb[nbin];
   TH2F * BjetProb[nbin];
    
    TH2F * trackpt[nbin];
    TH1F * trackrawpt[nbin];
    TH2F * trackphi[nbin];
    TH2F * tracketa[nbin];
    TH2F * trackpteff[nbin];
    TH2F * bkgtrackpteff[nbin];
    TProfile * trackdreff[nbin];
    TProfile * bkgtrackdreff[nbin];
    TH2F * trackdr[nbin][nptbin];
    TH2F * bkgtrackdr[nbin][nptbin];
    TH2F * wttrackdr[nbin][nptbin];
     TH2F * bkgwttrackdr[nbin][nptbin];
   TH2F * jetaxisRes[nbin];
    
    TH2F * jetfrag[nbin] ;
    TH2F * jetbkgfrag[nbin] ;
    TH2F * SumptJetPt[nbin] ;
    TH2F * JetBkgCone[nbin] ;
    TH2F * IncTrackDphi[nbin];
    TH2F * JetTrackDphi[nbin];
    TH2F * JetBkgTrackDphi[nbin];
    TH2F * JetTrackDeta[nbin];
    TH2F * JetBkgTrackDeta[nbin];
    TH2F * bkgtrackpt[nbin];

    TH1F * jetdrSumTrkPt[nbin][nptbin][ntrkptbin];

    TH2F * jetPtSumTrk[nbin][ntrkptbin];

    TH1F * bkgjetdrSumTrkPt[nbin][nptbin][ntrkptbin];
    TH2F * bkgjetPtSumTrk[nbin][ntrkptbin];

    TH1F * deltaR;
    TH1D * CenBin;
    TH1D * CenBinWt;
    TH1D * RareEvt;
    TH1F * Vertex ;
    TH1F * VertexWt ;

    //For inclusive track analysis, outside jet loop
    TH1F * inctrkpt[nbin];

    //   TH1F * ptbin[6];
    //for jet shape variables
    TH2F * ChargePt[nbin][nrbin];
    TH2F * SumChPt[nbin][nrbin];
    TH2F * ChargeMult[nbin][nrbin];   
    TH2F * DiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * IntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.
    //  TH2F * dphiJS[nbin]; //phi diviration from jet phi 
    //   TH2F * detaJS[nbin] ; //eta diviration from jet eta 
    TH1F * DiffJSPt80_100[nbin]; //differential jet shapes (pho(r)) hist.
    TH1F * bkgDiffJSPt80_100[nbin]; //differential jet shapes (pho(r)) hist.

    TH1F * DiffJSPt80_100Rbin[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH1F * bkgDiffJSPt80_100Rbin[nbin][nrbin]; //differential jet shapes (pho(r)) hist.

    //for jet shape background study
    TH2F * bkgChargePt[nbin][nrbin];
    TH2F * bkgSumChPt[nbin][nrbin];
    TH2F * bkgChargeMult[nbin][nrbin];   
    TH2F * bkgDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * bkgIntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.

    TH2F * GenAxisDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * GenAxisbkgDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    
    TH2F * DiffEtaBinJS[nbin][netabin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * bkgDiffEtaBinJS[nbin][netabin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * jetFFEtaBin[nbin][netabin]; //jet FF hist. in eta bins
    TH2F * bkgFFEtaBin[nbin][netabin]; //bkg FF in eta bins
    TH2F * trackPtEtaBin[nbin][netabin]; //jet FF hist. in eta bins
    TH2F * bkgtrackPtEtaBin[nbin][netabin]; //bkg FF in eta bins
    TH1F * jetptEtaBin[nbin][netabin];

    //   if(IsMC){
    TH2F * genjetpt[nbin];
    TH2F * genjeteta[nbin];
    TH2F * genjetphi[nbin];
    TH2F * gendphi[nbin];
     TH2F * genptRatio[nbin];
    TH2F * genphiRatio[nbin] ;
    TH2F * genetaRatio[nbin] ; 

    TH1F * genjetdrSumTrkPt[nbin][nptbin][ntrkptbin];
    TH1F * bkggenjetdrSumTrkPt[nbin][nptbin][ntrkptbin];

};

hist_class::hist_class(TString the_desc)
{
    
    desc = the_desc;
    IsMC =kTRUE ;
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin] = new TH1F(Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), 100, 0, 2.);
        NJets[ibin] = new TH1F(Form("NJets_%d-%d%%",centr[ibin],centr[ibin+1]), Form("NJets_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -0.5, 99.5);
        Ntrack[ibin] = new TH1F(Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), 800, -1., 799);
    //   if(IsMC)
        jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500.);	
   //   else   jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin);
        jetpt[ibin]->Sumw2();
        rawjetpt[ibin] = new TH1F(Form("rawjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("rawjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500.);	
        rawjetpt[ibin]->Sumw2();
        jesrawpt[ibin] = new TH2F(Form("jesrawpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jesrawpt_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500., 200, 0., 2.);
        jesrawpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jetRaw} (GeV/c)");
        jesrawpt[ibin]->GetYaxis()->SetTitle("p_{T}^{Raw}/p_{T}^{Corr}");
        jesrawpt[ibin]->Sumw2();
      //  jeteta[ibin] = new TH2F(Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin,100, -5.05, 4.95);
        jeteta[ibin] = new TH2F(Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500.,100, -5.05, 4.95);
        jeteta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jeteta[ibin]->GetYaxis()->SetTitle("#eta");
        jeteta[ibin]->Sumw2();
      //  jetphi[ibin] = new TH2F(Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin,100, -5.05, 4.95);
        jetphi[ibin] = new TH2F(Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -5.05, 4.95);
        jetphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetphi[ibin]->GetYaxis()->SetTitle("#phi");
        jetphi[ibin]->Sumw2();
        if(DoSmear){
      //  jetsmf[ibin] = new TH2F(Form("jetSmearFactor_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetSmearFactor_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin,100, 0., 100);
        jetsmf[ibin] = new TH2F(Form("jetSmearFactor_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetSmearFactor_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, 0., 100);
        jetsmf[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetsmf[ibin]->GetYaxis()->SetTitle("Smear Factor");
        jetsmf[ibin]->Sumw2();
      //  jetms[ibin] = new TH2F(Form("jetMeanShift_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetMeanShift_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin,100, -50., 50.);
        jetms[ibin] = new TH2F(Form("jetMeanShift_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetMeanShift_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -50., 50.);
        jetms[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetms[ibin]->GetYaxis()->SetTitle("Mean Shift");
        jetms[ibin]->Sumw2();
        }
        jetSSVHE[ibin] = new TH2F(Form("jetSSVHE_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetSSVHE_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -2., 8.);
        jetSSVHE[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetSSVHE[ibin]->GetYaxis()->SetTitle("discr_ssvHighEff");
        jetSSVHE[ibin]->Sumw2();
        jetProb[ibin] = new TH2F(Form("jetProb_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetProb_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -0., 5.);
        jetProb[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetProb[ibin]->GetYaxis()->SetTitle("discr_prob");
        jetProb[ibin]->Sumw2();
        BjetSSVHE[ibin] = new TH2F(Form("BjetSSVHE_%d-%d%%",centr[ibin],centr[ibin+1]), Form("BjetSSVHE_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -2., 8.);
        BjetSSVHE[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        BjetSSVHE[ibin]->GetYaxis()->SetTitle("discr_ssvHighEff");
        BjetSSVHE[ibin]->Sumw2();
        BjetProb[ibin] = new TH2F(Form("BjetProb_%d-%d%%",centr[ibin],centr[ibin+1]), Form("BjetProb_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -0., 5.);
        BjetProb[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        BjetProb[ibin]->GetYaxis()->SetTitle("discr_prob");
        BjetProb[ibin]->Sumw2();

     //   trackpt[ibin] = new TH2F(Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 200, 0., 200); 
        trackpt[ibin] = new TH2F(Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, nPtBin, TrkBin); 
        trackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackpt[ibin]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        trackpt[ibin]->Sumw2();
        trackrawpt[ibin] = new TH1F(Form("trackrawpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackrawpt_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin);
        trackrawpt[ibin]->GetXaxis()->SetTitle("p_{T}^{trkRAW} (GeV/c)");
        trackrawpt[ibin]->Sumw2();
        trackphi[ibin] = new TH2F(Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95); 
        trackphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackphi[ibin]->GetYaxis()->SetTitle("#phi^{trk}");   
        trackphi[ibin]->Sumw2();
        tracketa[ibin] = new TH2F(Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95); 
        tracketa[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        tracketa[ibin]->GetYaxis()->SetTitle("#eta^{trk}");   
        tracketa[ibin]->Sumw2();

        jetfrag[ibin] = new TH2F(Form("FFleading_%d-%d%%",centr[ibin],centr[ibin+1]), Form("FFleading_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        jetfrag[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
      //  jetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet}/p_{T}^{h})");
        jetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p^{jet}/p_{||}^{trk})");
        jetfrag[ibin]->Sumw2();
        jetbkgfrag[ibin] = new TH2F(Form("bkgFFleading_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgFFleading_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        jetbkgfrag[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
      //  jetbkgfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet}/p_{T}^{h})");
        jetbkgfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p^{jet}/p_{||}^{trk})");
        jetbkgfrag[ibin]->Sumw2();

        for(Int_t ieta = 0 ; ieta < netabin ; ieta++){
        jetptEtaBin[ibin][ieta] = new TH1F(Form("jetptEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("jetptEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 50, 0., 500.);
   //   else   jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin);
        jetptEtaBin[ibin][ieta]->Sumw2();
        trackPtEtaBin[ibin][ieta] = new TH2F(Form("trackptInJetEta%.f_%.f_Cen%d-%d%%",  deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("trackptInJetEta%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 500, 0., 500, nPtBin, TrkBin);
        trackPtEtaBin[ibin][ieta]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackPtEtaBin[ibin][ieta]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        trackPtEtaBin[ibin][ieta]->Sumw2();
        bkgtrackPtEtaBin[ibin][ieta] = new TH2F(Form("bkgtrackptInJetEta%.f_%.f_Cen%d-%d%%",  deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("bkgtrackptInJetEta%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 500, 0., 500, nPtBin, TrkBin);
        bkgtrackPtEtaBin[ibin][ieta]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgtrackPtEtaBin[ibin][ieta]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        bkgtrackPtEtaBin[ibin][ieta]->Sumw2();

        jetFFEtaBin[ibin][ieta] = new TH2F(Form("FFleadingEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("FFleadingEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        jetFFEtaBin[ibin][ieta]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
      //  jetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet}/p_{T}^{h})");
        jetFFEtaBin[ibin][ieta]->GetYaxis()->SetTitle("#xi = ln(p^{jet}/p_{||}^{trk})");
        jetFFEtaBin[ibin][ieta]->Sumw2();
        bkgFFEtaBin[ibin][ieta] = new TH2F(Form("bkgFFleadingEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), Form("bkgFFleadingEtaBin%.f_%.f_Cen%d-%d%%",deta[ieta]*10,deta[ieta+1]*10, centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        bkgFFEtaBin[ibin][ieta]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgFFEtaBin[ibin][ieta]->GetYaxis()->SetTitle("#xi = ln(p^{jet}/p_{||}^{trk})");
        bkgFFEtaBin[ibin][ieta]->Sumw2();
        }
        if(doTrackCorrections){
        trackpteff[ibin] = new TH2F(Form("jettrackpteff_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jettrackpteff_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin, 200, 0., 2.);
        trackpteff[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        trackpteff[ibin]->Sumw2();
        bkgtrackpteff[ibin] = new TH2F(Form("bkgtrackpteff_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgtrackpteff_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin, 200, 0., 2.);
        bkgtrackpteff[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        bkgtrackpteff[ibin]->Sumw2();
        trackdreff[ibin] = new TProfile(Form("jettrackdreff_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jettrackdreff_%d-%d%%",centr[ibin],centr[ibin+1]), (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
        trackdreff[ibin]->GetXaxis()->SetTitle("radius r");
        trackdreff[ibin]->Sumw2();
        bkgtrackdreff[ibin] = new TProfile(Form("bkgtrackdreff_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgtrackdreff_%d-%d%%",centr[ibin],centr[ibin+1]), (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
        bkgtrackdreff[ibin]->GetXaxis()->SetTitle("radius r");
        bkgtrackdreff[ibin]->Sumw2();
        }
        //jet pt bins loop
        for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
	  trackdr[ibin][ipt] = new TH2F(Form("recoTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recoTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), nPtBin, TrkBin, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
            trackdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
            trackdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
            trackdr[ibin][ipt]->Sumw2();
            bkgtrackdr[ibin][ipt] = new TH2F(Form("recobkgTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recobkgTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), nPtBin, TrkBin, (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
            bkgtrackdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
            bkgtrackdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");
            bkgtrackdr[ibin][ipt]->Sumw2();
            wttrackdr[ibin][ipt] = new TH2F(Form("recowtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recowtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), nPtBin, TrkBin, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
            wttrackdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
            wttrackdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
            wttrackdr[ibin][ipt]->Sumw2();
            bkgwttrackdr[ibin][ipt] = new TH2F(Form("recobkgwtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recobkgwtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), nPtBin, TrkBin, (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
            bkgwttrackdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
            bkgwttrackdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");
            bkgwttrackdr[ibin][ipt]->Sumw2();            
            for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){ //track bins loop
                jetdrSumTrkPt[ibin][ipt][itr]=new TH1F(Form("JetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), Form("JetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
                jetdrSumTrkPt[ibin][ipt][itr]->GetXaxis()->SetTitle("radius r"); 
                jetdrSumTrkPt[ibin][ipt][itr]->GetYaxis()->SetTitle("#Sigma p_{T}^{trk}/p_{T}^{jet}"); 
                jetdrSumTrkPt[ibin][ipt][itr]->Sumw2();
   
                bkgjetdrSumTrkPt[ibin][ipt][itr]=new TH1F(Form("bkgJetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), Form("bkgJetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
                bkgjetdrSumTrkPt[ibin][ipt][itr]->GetXaxis()->SetTitle("radius r"); 
                bkgjetdrSumTrkPt[ibin][ipt][itr]->GetYaxis()->SetTitle("#Sigma p_{T}^{trk}/p_{T}^{jet}"); 
                bkgjetdrSumTrkPt[ibin][ipt][itr]->Sumw2();
            }
        }
        SumptJetPt[ibin] = new TH2F(Form("SumptJetPtRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("SumptJetPtRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, 0., 1.);  
        SumptJetPt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        SumptJetPt[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{trk}/p_{T}^{jet}");
        SumptJetPt[ibin]->Sumw2();
        JetBkgCone[ibin] = new TH2F(Form("JetBkgAxisDifference_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetBkgAxisDifference_%d-%d%%",centr[ibin],centr[ibin+1]), 140, -7., 7.,100, -5.05, 4.95);
        JetBkgCone[ibin]->GetXaxis()->SetTitle("#phi_{bkg}-#phi_{jet}");
        JetBkgCone[ibin]->GetYaxis()->SetTitle("#eta_{bkg}-#eta_{jet}");
        JetBkgCone[ibin]->Sumw2();
        IncTrackDphi[ibin] = new TH2F(Form("AllTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("AllTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4.05, 7.95);
        IncTrackDphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        IncTrackDphi[ibin]->GetYaxis()->SetTitle("#phi_{trk}-#phi_{jet}");
        IncTrackDphi[ibin]->Sumw2();
        JetTrackDphi[ibin] = new TH2F(Form("JetTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4.05, 7.95);
        JetTrackDphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetTrackDphi[ibin]->GetYaxis()->SetTitle("#phi_{trk}-#phi_{jet}");
        JetTrackDphi[ibin]->Sumw2();
        JetBkgTrackDphi[ibin] = new TH2F(Form("JetBkgTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetBkgTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4.05, 7.95);
        JetBkgTrackDphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetBkgTrackDphi[ibin]->GetYaxis()->SetTitle("#phi_{trk}-#phi_{jet}");
        JetBkgTrackDphi[ibin]->Sumw2();
        JetTrackDeta[ibin] = new TH2F(Form("JetTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -5.05, 4.95);
        JetTrackDeta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetTrackDeta[ibin]->GetYaxis()->SetTitle("#eta_{trk}-#eta_{jet}");
        JetTrackDeta[ibin]->Sumw2();
        JetBkgTrackDeta[ibin] = new TH2F(Form("JetBkgTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetBkgTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -5.05, 4.95);
        JetBkgTrackDeta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetBkgTrackDeta[ibin]->GetYaxis()->SetTitle("#eta_{trk}-#eta_{jet}");
        JetBkgTrackDeta[ibin]->Sumw2();
      //  bkgtrackpt[ibin] = new TH2F(Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 200, 0., 200); 
        bkgtrackpt[ibin] = new TH2F(Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, nPtBin, TrkBin); 
        bkgtrackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgtrackpt[ibin]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        bkgtrackpt[ibin]->Sumw2();
        for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){
            jetPtSumTrk[ibin][itr]=new TH2F(Form("JetSumTrkPt%.f_%.f_%d-%d%%",trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), Form("JetSumTrkPt%.f_%.f_%d-%d%%",trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500.);
            jetPtSumTrk[ibin][itr]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)"); 
            jetPtSumTrk[ibin][itr]->GetYaxis()->SetTitle("#Sigma p_{T}^{trk}"); 
            jetPtSumTrk[ibin][itr]->Sumw2();
            bkgjetPtSumTrk[ibin][itr]=new TH2F(Form("bkgJetSumTrkPt%.f_%.f_%d-%d%%",trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), Form("bkgJetSumTrkPt%.f_%.f_%d-%d%%",trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500.);
            bkgjetPtSumTrk[ibin][itr]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)"); 
            bkgjetPtSumTrk[ibin][itr]->GetYaxis()->SetTitle("#Sigma p_{T}^{trk}"); 
            bkgjetPtSumTrk[ibin][itr]->Sumw2();
 
        }

        //for inclusive track histgram
        inctrkpt[ibin] = new TH1F(Form("inclusivetrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("inclusivetrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), nPtBin, TrkBin);
        inctrkpt[ibin]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
        inctrkpt[ibin]->Sumw2();

        if(IsMC){
        quarkjetpt[ibin] = new TH1F(Form("quarkjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("quarkjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500.);
        quarkjetpt[ibin]->Sumw2();
        bjetpt[ibin] = new TH1F(Form("bjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500.);
        bjetpt[ibin]->Sumw2();
        gluonjetpt[ibin] = new TH1F(Form("gluonjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("gluonjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 50, 0., 500.);
        gluonjetpt[ibin]->Sumw2();
            genjetpt[ibin] = new TH2F(Form("genjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
            genjetpt[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            genjetpt[ibin]->GetYaxis()->SetTitle("p_{T}^{gen} (GeV/c)");   
            genjetpt[ibin]->Sumw2();
            genjeteta[ibin] = new TH2F(Form("genjeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjeteta_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -5.05, 4.95,100, -5.05, 4.95);
            genjeteta[ibin]->GetXaxis()->SetTitle("#eta^{rec}");
            genjeteta[ibin]->GetYaxis()->SetTitle("#eta^{gen}");
            genjeteta[ibin]->Sumw2();
            genjetphi[ibin] = new TH2F(Form("genjetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjetphi_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -5.05, 4.95,100, -5.05, 4.95);
            genjetphi[ibin]->GetXaxis()->SetTitle("#phi^{rec}");
            genjetphi[ibin]->GetYaxis()->SetTitle("#phi^{gen}");
            genjetphi[ibin]->Sumw2();
            genptRatio[ibin] = new TH2F(Form("genptRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genptRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0.,500., 51, -0.05,5.05);
            genptRatio[ibin]->GetXaxis()->SetTitle("p_{T}^{gen} (GeV/c)");
            genptRatio[ibin]->GetYaxis()->SetTitle("p_{T}^{rec}/p_{T}^{gen}"); 
            genptRatio[ibin]->Sumw2();
            genphiRatio[ibin] = new TH2F(Form("genphiRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genphiRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500,0., 500.,100, -1.01,0.99);
            genphiRatio[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            genphiRatio[ibin]->GetYaxis()->SetTitle("#phi_{gen}-#phi_{rec}"); 
            genphiRatio[ibin]->Sumw2();
            genetaRatio[ibin] = new TH2F(Form("genetaRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genetaRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -1.01,0.99);
            genetaRatio[ibin]->Sumw2();
            genetaRatio[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            genetaRatio[ibin]->GetYaxis()->SetTitle("#eta_{gen}-#eta_{rec}"); 
            jetaxisRes[ibin] = new TH2F(Form("JetAxisRes_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetAxisRes_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 200, -1., 1.);
            jetaxisRes[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            jetaxisRes[ibin]->GetYaxis()->SetTitle("#Delta r=r_{genAxis}-r_{recoAxis}");
            jetaxisRes[ibin]->Sumw2();
        } //MC histogram
        DiffJSPt80_100[ibin] = new TH1F(Form("diffJSPt80_100_Cen%d-%d%%",centr[ibin],centr[ibin+1]), Form("diffJSPt80_100JS_Cen%d-%d%%",centr[ibin],centr[ibin+1]), 8, -0.05, 0.35);
        DiffJSPt80_100[ibin]->GetXaxis()->SetTitle("#rho (r)");
        DiffJSPt80_100[ibin]->Sumw2();
        bkgDiffJSPt80_100[ibin] = new TH1F(Form("bkgdiffJSPt80_100_Cen%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgdiffJSPt80_100JS_Cen%d-%d%%",centr[ibin],centr[ibin+1]), 8, -0.05, 0.35);
        bkgDiffJSPt80_100[ibin]->GetXaxis()->SetTitle("#rho (r)");
        bkgDiffJSPt80_100[ibin]->Sumw2();

        for(int ir = 0 ; ir <nrbin; ir++){
            ChargePt[ibin][ir] = new TH2F(Form("chargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("chargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500);
            ChargePt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            ChargePt[ibin][ir]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
            ChargePt[ibin][ir]->Sumw2();
            SumChPt[ibin][ir] = new TH2F(Form("sumchptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("sumchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
            SumChPt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            SumChPt[ibin][ir]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");
            SumChPt[ibin][ir]->Sumw2();
            ChargeMult[ibin][ir] = new TH2F(Form("ChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("ChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -0.5, 99.5);
            ChargeMult[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            ChargeMult[ibin][ir]->GetYaxis()->SetTitle("# of Charge");   
            ChargeMult[ibin][ir]->Sumw2();
            DiffJS[ibin][ir] = new TH2F(Form("differentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("differentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
            DiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            DiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            DiffJS[ibin][ir]->Sumw2();
            IntJS[ibin][ir] = new TH2F(Form("IntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("IntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
            IntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            IntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            IntJS[ibin][ir]->Sumw2();
            DiffJSPt80_100Rbin[ibin][ir] = new TH1F(Form("diffJSPt80_100dR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("diffJSPt80_100JSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 150, -0.005, 1.495);
            DiffJSPt80_100Rbin[ibin][ir]->GetXaxis()->SetTitle("#rho (r)");
            DiffJSPt80_100Rbin[ibin][ir]->Sumw2();
            bkgDiffJSPt80_100Rbin[ibin][ir] = new TH1F(Form("bkgdiffJSPt80_100dR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgdiffJSPt80_100JSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 150, -0.005, 1.495);
            bkgDiffJSPt80_100Rbin[ibin][ir]->GetXaxis()->SetTitle("#rho (r)");
            bkgDiffJSPt80_100Rbin[ibin][ir]->Sumw2();
            
            //for bkg histos.
            bkgChargePt[ibin][ir] = new TH2F(Form("bkgchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500);
            bkgChargePt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgChargePt[ibin][ir]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
            bkgChargePt[ibin][ir]->Sumw2();
            bkgSumChPt[ibin][ir] = new TH2F(Form("bkgsumchptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsumchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
            bkgSumChPt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgSumChPt[ibin][ir]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");    
            bkgSumChPt[ibin][ir]->Sumw2();
            bkgChargeMult[ibin][ir] = new TH2F(Form("bkgChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -0.5, 99.5);
            bkgChargeMult[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgChargeMult[ibin][ir]->GetYaxis()->SetTitle("# of Charge");
            bkgChargeMult[ibin][ir]->Sumw2();
            bkgDiffJS[ibin][ir] = new TH2F(Form("bkgdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
            bkgDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
            bkgDiffJS[ibin][ir]->Sumw2();
            bkgIntJS[ibin][ir] = new TH2F(Form("bkgIntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgIntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
            bkgIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
            bkgIntJS[ibin][ir]->Sumw2();
        }
            for(Int_t ieta = 0 ; ieta <netabin ; ieta++){
                for(int ir = 0 ; ir <nrbin; ir++){
                DiffEtaBinJS[ibin][ieta][ir] = new TH2F(Form("diffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10, rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("diffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10,rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                DiffEtaBinJS[ibin][ieta][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                DiffEtaBinJS[ibin][ieta][ir]->GetYaxis()->SetTitle("#rho (r)");
                DiffEtaBinJS[ibin][ieta][ir]->Sumw2();
                bkgDiffEtaBinJS[ibin][ieta][ir] = new TH2F(Form("bkgdiffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10, rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgdiffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10,rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                bkgDiffEtaBinJS[ibin][ieta][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                bkgDiffEtaBinJS[ibin][ieta][ir]->GetYaxis()->SetTitle("#rho (r)");
                bkgDiffEtaBinJS[ibin][ieta][ir]->Sumw2();
                }
  
            }
        }  //centrality bins loop
        
    //    for(int i = 0 ; i < 6 ; i++){
    //     ptbin[i] = new TH1F(Form("ptbin_%.f-%.f",pt[i], pt[i+1]), Form("ptbin_%.f-%.f",pt[i], pt[i+1]), 500, 0., 500.);
    //    }
    // if(!deltaR)
    deltaR = new TH1F((TString) (desc + "_deltaR"), "", 100, 0., 10.);
    CenBin = new TH1D((TString) (desc + "_Cent"), "", 100, 0, 100);
    CenBin->Sumw2();
    CenBinWt = new TH1D((TString) (desc + "_CentWeighted"), "", 100, 0, 100);
    CenBinWt->Sumw2();
    Vertex = new TH1F((TString) (desc + "_Vz"), "", 400, -20., 20.);
    Vertex->Sumw2();
    VertexWt = new TH1F((TString) (desc + "_VzWeighted"), "", 400, -20., 20.);
    VertexWt->Sumw2();
    RareEvt = new TH1D((TString) (desc + "_RareEvt"), "", 40, 0, 40);
    
}

void hist_class::Delete()
{
    for(int ibin = 0 ; ibin <nbin; ibin++){
        delete NEvents[ibin];
        //        delete TwoTrackTwoJet[ibin];
        //        delete TwoTrackThreeJet[ibin];
        //        delete OneTrackTwoJet[ibin];
        //        delete OneTrackThreeJet[ibin];
        //        delete SumPtFraction[ibin];
        delete NJets[ibin];
        delete Ntrack[ibin];  
        delete jetpt[ibin];
        delete rawjetpt[ibin];
        delete jesrawpt[ibin];
        delete jeteta[ibin];
        delete jetphi[ibin];
        if(DoSmear){
            delete jetsmf[ibin];
            delete jetms[ibin];
        } 
        delete jetSSVHE[ibin];
        delete BjetSSVHE[ibin];
        delete jetProb[ibin];     
        delete BjetProb[ibin];     
        delete trackpt[ibin];
        delete trackrawpt[ibin];
        delete trackphi[ibin];
        delete tracketa[ibin];
       
        delete inctrkpt[ibin] ; 
        delete jetfrag[ibin];
        delete jetbkgfrag[ibin];
        if(doTrackCorrections){
        delete trackpteff[ibin];
        delete bkgtrackpteff[ibin];
        delete trackdreff[ibin];
        delete bkgtrackdreff[ibin];
        }
        for(Int_t ieta = 0 ; ieta < netabin ; ieta++){
        delete jetptEtaBin[ibin][ieta];
        delete trackPtEtaBin[ibin][ieta]; 
        delete bkgtrackPtEtaBin[ibin][ieta]; 
        delete jetFFEtaBin[ibin][ieta]; 
        delete bkgFFEtaBin[ibin][ieta]; 
        }
        for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
            delete trackdr[ibin][ipt];
            delete bkgtrackdr[ibin][ipt];
            delete wttrackdr[ibin][ipt];
            delete bkgwttrackdr[ibin][ipt];
            for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){
              delete jetdrSumTrkPt[ibin][ipt][itr];
                delete bkgjetdrSumTrkPt[ibin][ipt][itr];
            }
        }
        delete SumptJetPt[ibin];
        delete JetBkgCone[ibin];
        delete IncTrackDphi[ibin];
        delete JetTrackDphi[ibin];
        delete JetBkgTrackDphi[ibin];
        delete JetTrackDeta[ibin];
        delete JetBkgTrackDeta[ibin];
        delete bkgtrackpt[ibin];
        for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){
            delete jetPtSumTrk[ibin][itr];
            delete bkgjetPtSumTrk[ibin][itr];
            
        }
        if(IsMC){
        delete quarkjetpt[ibin];
        delete bjetpt[ibin];
        delete gluonjetpt[ibin]; 
           delete genjetpt[ibin];
            delete genjeteta[ibin];
            delete genjetphi[ibin];
            delete genptRatio[ibin];
            delete genphiRatio[ibin];
            delete genetaRatio[ibin];
            delete jetaxisRes[ibin];
        }
        delete DiffJSPt80_100[ibin];        
        delete bkgDiffJSPt80_100[ibin];  
        for(int ir = 0 ; ir <nrbin; ir++){
            delete ChargePt[ibin][ir];
            delete SumChPt[ibin][ir];
            delete ChargeMult[ibin][ir];
            delete DiffJS[ibin][ir];
            delete IntJS[ibin][ir];
            delete bkgChargePt[ibin][ir];      
            delete bkgSumChPt[ibin][ir];
            delete bkgChargeMult[ibin][ir];
            delete bkgDiffJS[ibin][ir];
            delete bkgIntJS[ibin][ir];
            delete DiffJSPt80_100Rbin[ibin][ir];        
            delete bkgDiffJSPt80_100Rbin[ibin][ir];  
         }
        for(Int_t ieta = 0 ; ieta <netabin ; ieta++){
            for(int ir = 0 ; ir <nrbin; ir++){
                delete DiffEtaBinJS[ibin][ieta][ir];
                delete bkgDiffEtaBinJS[ibin][ieta][ir];
            }
        }
        
    } //centrality loop
    //   for(int i=0; i<6;i++) delete ptbin[i];
    delete deltaR;
    delete CenBin;
    delete CenBinWt;
    delete RareEvt;
    delete Vertex;
    delete VertexWt;

}

void hist_class::Write()
{
    TString out_name ;
    TString dataType ; 
    if(IsMC) dataType="MC" ;
    else dataType="DATA";
    TString met ;
    if(etalimit==etacut) met = "RC";
    else met = "ER";
    TString level ;
    if(DoJetPtWeight) level = "wt";
    else level = "";
    TString Norm ;
    if(DoSumPtNorm)Norm="NormSum";
    else Norm ="NormJet";

    if(doTrackCorrections){
     if(IsMC==kTRUE && coll=="PP")   
          out_name=Form("%s%s_AkPu3PF%sBJetPt%.f_2013%sIterTrkCorrtest%.fEtaCut%.fLimit%.f_%sbkgJS%sCone%.f_CenBin%d_Nrbin%d_LJbin%dtrkbin%dpthat%d_%s",dataType.Data(),coll.Data(),level.Data(),leadingjetcut,corrMet.Data(), trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin,pthat, intputFile.Data());
       else 
         out_name=Form("%s%s_AkPu3PF%sBJetPt%.f_2013%sIterTrkCorrtest%.fEtaCut%.fLimit%.f_%sbkgJS%sCone%.f_CenBin%d_Nrbin%d_LJbin%dtrkbin%d_%s",dataType.Data(),coll.Data(),level.Data(),leadingjetcut,corrMet.Data(), trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin, intputFile.Data());
      }
       else {
    if(IsMC==kTRUE && coll=="PP" )
            out_name=Form("%s%s_AkPu3PF%sBJetPt%.f_Trk%.fEtaCut%.fLimit%.f_%sbkgJS%sCone%.f_CenBin%d_Nrbin%d_LJbin%dtrkbin%dpthat%d_%s",dataType.Data(),coll.Data(),level.Data(),leadingjetcut,trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin,pthat, intputFile.Data());
    else        
            out_name=Form("%s%s_AkPu3PF%sBJetPt%.f_Trk%.fEtaCut%.fLimit%.f_%sbkgJS%sCone%.f_CenBin%d_Nrbin%d_LJbin%dtrkbin%d_%s",dataType.Data(),coll.Data(),level.Data(),leadingjetcut,trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin, intputFile.Data());
    }
     
       TFile *out_file = new TFile(Form("/net/hidsk0001/d00/scratch/maoyx/JetShape/pAana/CMSSW_5_3_8_HI_patch2/src/pPbAnalysis/%s",out_name.Data()), "RECREATE");
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin]->Write();
        NJets[ibin]->Write();
        Ntrack[ibin]->Write();
        jetpt[ibin]->Write();
        rawjetpt[ibin]->Write();
        jesrawpt[ibin]->Write();
        jeteta[ibin]->Write();
        jetphi[ibin]->Write();
        if(DoSmear){
                jetsmf[ibin]->Write();
                jetms[ibin]->Write();
        }
         jetSSVHE[ibin]->Write();
         BjetSSVHE[ibin]->Write();
         jetProb[ibin]->Write();
         BjetProb[ibin]->Write();
         trackpt[ibin]->Write();
         trackrawpt[ibin]->Write();
        trackphi[ibin]->Write();
        tracketa[ibin]->Write();
        inctrkpt[ibin]->Write();
        jetfrag[ibin]->Write();
        jetbkgfrag[ibin]->Write();
        if(doTrackCorrections){
        trackpteff[ibin]->Write();
        bkgtrackpteff[ibin]->Write();
        trackdreff[ibin]->Write();
        bkgtrackdreff[ibin]->Write();
        }
        for(Int_t ieta = 0 ; ieta < netabin ; ieta++){
        jetptEtaBin[ibin][ieta]->Write();
         trackPtEtaBin[ibin][ieta]->Write();
         bkgtrackPtEtaBin[ibin][ieta]->Write();
         jetFFEtaBin[ibin][ieta]->Write();  
         bkgFFEtaBin[ibin][ieta]->Write();  
        }

        for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
            trackdr[ibin][ipt]->Write();
            bkgtrackdr[ibin][ipt]->Write();
            wttrackdr[ibin][ipt]->Write();
            bkgwttrackdr[ibin][ipt]->Write();
            for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){
                jetdrSumTrkPt[ibin][ipt][itr]->Write();
                 bkgjetdrSumTrkPt[ibin][ipt][itr]->Write();
            }

        }
        SumptJetPt[ibin]->Write();
        JetBkgCone[ibin]->Write();
        IncTrackDphi[ibin]->Write();
        JetTrackDphi[ibin]->Write();
        JetBkgTrackDphi[ibin]->Write();
        JetTrackDeta[ibin]->Write();
        JetBkgTrackDeta[ibin]->Write();
        bkgtrackpt[ibin]->Write();
        for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){
            jetPtSumTrk[ibin][itr]->Write();
            bkgjetPtSumTrk[ibin][itr]->Write();
            
        }
        if(IsMC){
        quarkjetpt[ibin]->Write();
        bjetpt[ibin]->Write();
        gluonjetpt[ibin]->Write();
            genjetpt[ibin]->Write();
            genjeteta[ibin]->Write();
            genjetphi[ibin]->Write();
             genptRatio[ibin]->Write();
            genphiRatio[ibin]->Write();
            genetaRatio[ibin]->Write();
            jetaxisRes[ibin]->Write();
    
        }
        DiffJSPt80_100[ibin]->Write();
        bkgDiffJSPt80_100[ibin]->Write();
        for(int ir = 0 ; ir <nrbin; ir++){
            ChargePt[ibin][ir]->Write();    
            SumChPt[ibin][ir]->Write(); 
            ChargeMult[ibin][ir]->Write();    
            DiffJS[ibin][ir]->Write();
            IntJS[ibin][ir]->Write();
            bkgChargePt[ibin][ir]->Write();    
            bkgSumChPt[ibin][ir]->Write(); 
            bkgChargeMult[ibin][ir]->Write();   
            bkgDiffJS[ibin][ir]->Write();
            bkgIntJS[ibin][ir]->Write();
            DiffJSPt80_100Rbin[ibin][ir]->Write();
            bkgDiffJSPt80_100Rbin[ibin][ir]->Write();
    
        }
            for(Int_t ieta = 0 ; ieta <netabin ; ieta++){
                for(int ir = 0 ; ir <nrbin; ir++){
                DiffEtaBinJS[ibin][ieta][ir]->Write();
                bkgDiffEtaBinJS[ibin][ieta][ir]->Write();
                }
            }
        } //centrality bins
    
    //  for(int i=0; i<6;i++) ptbin[i]->Write();
    deltaR->Write();
    CenBin->Write();
    CenBinWt->Write();
    RareEvt->Write();
    Vertex->Write();
    VertexWt->Write();

    out_file->Close();
    cout <<"Output file: " <<Form("%s",out_name.Data()) <<endl ;
    
}


void anaBJet()
{
    //  pthat=atoi(getenv("PTHAT")) ;
    //  ptmax=atoi(getenv("PTMAX")) ;
    // cout <<"pthat = " <<pthat <<"  pthatmax =" <<ptmax <<endl ;
    // gROOT->ForceStyle(0);
    //for centrality reweight parameterization
    TF1 *fcen = new TF1("fcen","[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)",0,100);
    // fcen->SetParameters(2.10653e-02,5.61607,-1.41493e-01,1.00586e-03,-1.32625e-04); //from Pawn/Pelin
    fcen->SetParameters(1.98261e-02,5.55963e+00,-1.34951e-01,1.70895e-03,-9.28386e-05); //fit by myself
    
    //  TF1 * fcen = new TF1("fcen","[0]+[1]*x+[2]*x*x+[3]*TMath::Power(x,3)", 0, 40);
    //  fcen->SetParameters(3.55169, -0.246077, 0.00541725,-3.64594e-05);
    //  fcen->SetParErrors(0.143397, 0.0166513, 0.000639065,7.94585e-06);
    //for vertex reweight parameterization
    TF1 * fVz = new TF1("fVx","[0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3)+[4]*TMath::Power(x,4)", -15., 15.);
    if(coll=="HI")
        //  fVz->SetParameters(0.803816, -0.0179222, 0.00716733, -0.000165785, 7.30741e-05); //PbPb vertex reweighting
        fVz->SetParameters(7.62788e-01,-1.13228e-02,5.85199e-03,-3.04550e-04,4.43440e-05);
    else if(coll=="PPb")
        fVz->SetParameters(1.60182e+00,1.08425e-03,-1.29156e-02,-7.24899e-06,2.80750e-05);
    else if(coll=="PbP")
        fVz->SetParameters(1.64354e+00,-3.63562e-03,-1.42033e-02,1.70149e-05,3.30168e-05);
    else
        fVz->SetParameters(1.28206e+00, 1.34215e-02, -5.85163e-03, -3.54998e-05, 7.35499e-06); //! data/MC without data shift
    //   fVz->SetParameters(1.26536e+00, 2.77455e-02, -5.47913e-03, -7.76245e-05, 6.25962e-06);//! data shift to vz+0.4847
    //   fVz->SetParErrors(0.0218623, 0.00619651,  0.00144498,0.000105209, 1.3927e-05); //for PbPb vertext reweight parameters error
    //   fVz->SetParErrors( 0.0280385, 0.00792399,  0.00173743,0.000122401, 1.59032e-05); //for PbPb vertext reweight parameters error
    
    hist_class *my_hists = new hist_class("bjet");
    cout <<my_hists->IsMC<<endl ;
    if(my_hists->IsMC==kTRUE){
        pthat=atoi(getenv("PTHAT")) ;
        ptmax=atoi(getenv("PTMAX")) ;
        cout <<"pthat = " <<pthat <<"  pthatmax =" <<ptmax <<endl ;
    }
    
    //! Edited by Pawan
    //! Load the Smearing factors
    // if(coll=="PP"&& DoSmear)
    LoadParameters();
    
    //for pt jet reweight after smearing
    TH1F * ptwt[nbin];
    TFile * ptwtfile ;
    if(DoJetPtWeight && DoSmear && (coll=="PP")){
        //     TFile * ptwtfile = TFile::Open("/Users/ymao/group/CMS/macros/DataJetPtReweight.root", "readonly");
        //      TFile * ptwtfile = TFile::Open("/home/group/CMS/WorkSpace/analysis/PFjet/DataJetPtReweight.root", "readonly");
        //  TFile * ptwtfile = TFile::Open("/afs/cern.ch/user/y/ymao/scratch0/JetShape/DataSubjetPtReweight.root", "readonly");
        //   TFile * ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataJetPtReweight.root", "readonly");
        if(my_hists->IsMC==kTRUE)
            ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/MCJetPtReweightRebin.root", "readonly");
        //   ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/2013MCHITrackingAk3PFJetPtReweightRebin.root", "readonly");
        else
            //   ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataJetPtReweightRebin.root", "readonly");
            //    ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataJetPtReweight.root", "readonly");
            //   ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataAk3PFJetPtReweightRebin.root", "readonly");
            //    ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataAk3PFJetPtReweightRebin.root", "readonly");
            ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/2013DataHITrackingAk3PFJetPtReweightRebin.root", "readonly");
        
        //     ptwtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/CMSSW_4_4_2_patch5/src/DataAk3PFJetPtReweightRebin.root", "readonly");
        for(int ibin = 0 ; ibin <nbin; ibin++){
            //  ptwt[ibin] = (TH1F*)ptwtfile->Get(Form("WeightFactor_JetPtCen%d-%d%%", centr[ibin],centr[ibin+1]));
            ptwt[ibin] = (TH1F*)ptwtfile->Get(Form("SmearedRatioJetPtCen%d-%d%%", centr[ibin],centr[ibin+1]));
            
        }
        //   ptwtfile->Close();
    }
    
    std::cout << "start working\n";
    if(my_hists->IsMC!=kTRUE){
        if(coll=="HI")
            dataPath="/net/hidsk0001/d00/scratch/yjlee/merge/pbpbDijet_v20" ;//mit PbPb data path
        else    dataPath="/mnt/hadoop/cms/store/user/maoyx/hiForest";  //2013 pp data
    }
    else { //MC analysis
        if(coll=="HI") {
            if(pthat==50||pthat==80||pthat==100||pthat==170)
                dataPath= Form("/mnt/hadoop/cms/store/user/yenjie/HiForest_v27/"); //MIT MC normial
            else
                dataPath= Form("/mnt/hadoop/cms/store/user/yenjie/HiForest_v28/"); //MIT MC normial
        }
        else if(coll=="PPb")
            dataPath=Form("/mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt%d/HiForest_v77_merged01", pthat);
        else if(coll=="PbP")
            dataPath=Form("/mnt/hadoop/cms/store/user/dgulhan/Pbp/HP05/prod24/Hijing_Pythia_pt%d/HiForest_v84_merged02", pthat);
        else {
            //  dataPath= Form("/mnt/hadoop/cms/store/user/dgulhan/ppHiIterativeTrack/P01/prod24/Signal_Pythia_pt%d/HiForest_v84_merged01", pthat); //2013 pp HI tracking
            //  dataPath= Form("/mnt/hadoop/cms/store/user/dgulhan/pp2013/P01/prod22/Signal_Pythia_pt%d/HiForest_v81_merged01", pthat); //2013 pp tracking for 2.76TeV
            dataPath= Form("/mnt/hadoop/cms/store/user/kjung/pp_Fix2_MergedForest", pthat); //2013 pp tracking for B-tagging at 2.76TeV
        }
    }
    if(my_hists->IsMC!=kTRUE){  //real data analysis
        if(coll=="HI")
            intputFile="promptskim-hihighpt-hltjet80-pt90-v20.root" ; //full dataset
        else if(coll=="PbPb")
            intputFile="PbPHiForest2_PbPbPAHighPtJet80_cent50-100_pprereco.root";
        else if(coll=="PPb")
            intputFile="PA2013_HiForest_PromptReco_JSonPPb_forestv77.root";
        else if(coll=="PbP")
            intputFile="PA2013_HiForest_PromptReco_JSonPbp_JECdb_forestv84.root" ;
        else            intputFile="PP2013_HiForest_PromptReco_JsonPP_Jet80_PPReco_forestv82.root";  //! 2013 pp data with pp tracking
    }
    else { //MC sample
        if(coll=="HI"){
            if(pthat==50||pthat==80||pthat==100||pthat==170)
                intputFile=Form("Dijet%d_HydjetDrum_v27_mergedV1.root", pthat);
            else
                intputFile=Form("Dijet%d_HydjetDrum_v28_mergedV1.root", pthat);
        }
        else if(coll=="PPb")
            intputFile=Form("pt%d_HP04_prod16_v77_merged_forest_0.root", pthat);
        else if(coll=="PbP")
            intputFile=Form("pt%d_HP05_prod24_v84_merged_forest_0.root", pthat);
        else
            //   intputFile=Form("pp276Dijet%d_merged.root",pthat);
            //  intputFile=Form("pt%d_JEC_ppHiIterativeTrack_P01_prod24_v84_merged_forest_0.root", pthat); // ! 2013 pp@2.76TeV MC with HI tracking
            //    intputFile=Form("pt%d_pp2013_P01_prod22_v81_merged_forest_0.root", pthat); // ! 2013 pp@2.76TeV MC with pp tracking
            //   intputFile=Form("pt%d_HP04_hiforest77_hiSignal.root", pthat); // ! 2013 pp 5.02TeV MC with pp tracking
            intputFile=Form("pp_Fix2_MCBForest%doutput.root", pthat); // ! 2013 pp 2.76TeV MC with pp tracking for b-tagging
    }
    
    TString inname=Form("%s/%s", dataPath.Data(),intputFile.Data());
    // Define the input file and HiForest
    //  bool isPP =false ;
    HiForest * c ;
    if(coll=="PP" )
        c = new HiForest(inname,"forest",cPP);
    else if(coll=="PPb" || coll=="PbP")
        c = new HiForest(inname,"forest",cPPb);
    else
        c = new HiForest(inname,"forest",cPbPb);
    //  HiForest * c = new HiForest(inname,"forest",isPP);
    // HiForest *c = new HiForest(inname);
    if(doTrackCorrections)c->doTrackCorrections = 1;
    else c->doTrackCorrections = false;
    c->doTrackingSeparateLeadingSubleading = false;
    c->InitTree();
    //  cout << "start working222222\n";
    //  TFile *my_file=TFile::Open(Form("%s/%s", dataPath.Data(),intputFile.Data()));
    cout <<"Input file" << inname<<endl ;
    
    Evts * offSel = &(c->evt);
    
    
    Skims * my_skim = &(c->skim);
    
    Hlts * trigSel = &(c->hlt);
    //jet tree
    
    //    if(coll=="HI")
    Jets * my_ct = &(c->akPu3PF);
    //   else
    //    Jets * my_ct = &(c->ak3PF);
    //  Jets * jetthres =  &(c->icPu5);
    //track tree
    
    Tracks * my_tr = &(c->track);
    
    //GenParticle tree
    
    int curr_bin = nbin-1 ;
    cout <<"Number of events ="<<c->GetEntries()<<endl ;
    for(int evi = 0; evi < c->GetEntries(); evi++) {
     //          for(int evi = 0; evi < 100; evi++) {
        c->GetEntry(evi);
        //  if(evi%2==1) continue ;
        //  if(evi%2==0) continue ;
       // cout <<"evt = "<<evi <<endl ;
        int noise_evt = my_skim->pHBHENoiseFilter ;
        //        int ecal_noise = my_skim->phiEcalRecHitSpikeFilter ;
        //        if(ecal_noise==0) continue ;
        
        double vz = offSel->vz ;
        int hiBin = offSel->hiBin ;
        weight = 1. ;
        
        int pileup_Gplus ;
        //  if(coll=="HI") {
        if(my_hists->IsMC!=kTRUE){
            int evt_sel ;
            pileup_Gplus = my_skim->pVertexFilterCutGplus ;
            if(coll=="PbPb"|| coll=="HI")  evt_sel = my_skim->pcollisionEventSelection ;
            else  evt_sel = my_skim->pPAcollisionEventSelectionPA;
            if(evt_sel==0) continue ;
        }
        if(my_hists->IsMC!=kTRUE){
            if(noise_evt==0) continue ;
            int jetTr2 ;
            if(coll=="HI"|| coll=="PbPb")
                jetTr2 = trigSel->HLT_HIJet80_v1 ;
            else
                jetTr2 = trigSel->HLT_PAJet80_NoJetID_v1 ;
            //         if(coll=="HI"){
            //	      int jetTr2 = trigSel->HLT_HIJet80_v1 ;
            //    else
            //            int jetTr1 = trigSel->HLT_Jet40_v1 ;
            //    int jetTr2 = trigSel->HLT_Jet60_v1 ;
            //
            if(jetTr2==0) continue ;
            int run=offSel->run ;
            if(coll=="PPb"){
                if(pileup_Gplus==0) continue ;
                if(run>211257) continue ;
                if(run<=210658) continue ;  //remove the runs with old alignment
            }
            if(coll=="PbP"){
                if(pileup_Gplus==0) continue ;
                if(run<=211257) continue ;
            }
            //	}
        }
        
        //if there is no jets or no PF candidates, skip the event
        if(my_ct->nref==0) continue ;
        //put the higher pthat cut
        if(my_hists->IsMC==kTRUE && my_ct->pthat>ptmax) continue ;
        if(my_ct->pthat>ptmax) cout <<"pthat =" <<my_ct->pthat <<endl ;
        if(coll=="HI")
            my_hists->CenBin->Fill(hiBin*2.5);
        else my_hists->CenBin->Fill(hiBin);
        
        my_hists->Vertex->Fill(vz);
        
        //   cout <<"vz =" <<vz <<endl ;
        if(TMath::Abs(vz)>15.) continue ;
        if(my_hists->IsMC==kTRUE) weight*=fVz->Eval(vz);
        else weight=1. ;
        
        if(coll=="HI"){
            if(my_hists->IsMC==kTRUE)
                // weight = wt[hiBin];
                weight*=fcen->Eval(hiBin);
            // weight = 1.;
            else
                weight = 1. ;
            double centrality = hiBin*2.5 ;
            //   my_hists->CenBin->Fill(offSel->hiBin);
            
            for(int ibin = 0 ; ibin <nbin; ibin++){
                if(centrality >=centr[ibin] && centrality<centr[ibin+1]) curr_bin = ibin ;
            }
        }
        else {
            curr_bin=nbin-1 ;
              weight = 1. ;
        }
        //   weight = 1. ;
        
          //  cout << "  cent_bin:" <<curr_bin <<endl ;
        if(evi%1000==1) cout <<" coll = " <<coll <<" weight = " <<weight <<" evt = " <<evi <<endl ;
        
        my_hists->Ntrack[curr_bin]->Fill(1, weight);
        //cout <<my_hists->NEvents[curr_bin]->GetName() <<endl;
      //  cout << "start working222222\n";
        
        
        ///--------------------------------------------------------------------
        /// ---- JETS  ----- ///////////////////////////////////////////
        ///--------------------------------------------------------------------
        
        //define the variables used
        double jet_pt = -999.;
        double jet_phi = -999.;
        double jet_eta = -999. ;
        double bkg_phi = -999.;
        double bkg_eta = -999.;
        
        int njets = 0 ;
        int ptBin = -1 ;
        
        int dEtaBin = -1. ;
        
        //for MC gen jet info
        double genjet_pt = -999. ;
        double genjet_phi = -999.;
        double genjet_eta = -999. ;
        double genbkg_phi = -999. ;
        double genbkg_eta = -999. ;
        
        TVector3 genjet_vec;
        TVector3 genbkg_vec;
        TVector3 genpart_vec;
        genjet_vec.SetPtEtaPhi(0, 0, 0);
        genbkg_vec.SetPtEtaPhi(0, 0, 0);
        genpart_vec.SetPtEtaPhi(0, 0, 0);
        //    }
        
        double flavor = 0 ;
        //make an munual cut for icPu5 calo jet cut (similar as jet skim threshold)
        //  for(int i = 0 ; i < jetthres->nref ; i++) {
        //     if(jetthres->jtpt[i]<90.) continue ;
        //    }
        
        for(int j4i = 0; j4i < my_ct->nref ; j4i++) {
            //only looks for signal jets, for PYTHIA, it removes the fake jets
         //   if( my_hists->IsMC==kTRUE && my_ct->subid[j4i] != 0) continue;
            jet_pt= my_ct->jtpt[j4i];
            if(my_ct->trackMax[j4i]/jet_pt <=0.01) continue ;
           //  cout << "jet loop = " << j4i <<endl ;
            if(!DoSmear && jet_pt>pt[nptbin]) continue ;
            if(DoSmear && jet_pt < 50.) continue ;
         //   if(TMath::Abs(my_ct->jteta[j4i])<etalimit) continue ;
            //  if(!DoSmear && jet_pt<leadingjetcut) continue ;
            //  if(jet_pt<leadingjetcut) continue ;
            //remove flucluation with too large pt from small MC pthat sample
            if(my_hists->IsMC==kTRUE && jet_pt>=4*pthat) continue ;
            //remove too high energy jets flucutulation
            if(jet_pt>pt[nptbin]) continue ;
            jet_phi =my_ct->jtphi[j4i];
            if(jet_phi<=-TMath::Pi())jet_phi+=TMath::TwoPi();
            jet_eta = my_ct->jteta[j4i];
            //   if(coll=="PPb") jet_eta = jet_eta+0.465 ;
            //   if(coll=="PbP") jet_eta = jet_eta-0.465;
            if(TMath::Abs(jet_eta)>etacut) continue ;
            my_hists->jetSSVHE[curr_bin]->Fill(jet_pt, my_ct->discr_ssvHighEff[j4i], weight);
            my_hists->jetProb[curr_bin]->Fill(jet_pt, my_ct->discr_prob[j4i], weight);
            if(my_hists->IsMC==kTRUE) {
                //   flavor = TMath::Abs(my_ct->refparton_flavor[j4i]);
                flavor = TMath::Abs(my_ct->refparton_flavorForB[j4i]);
             //   if(flavor>=1 && flavor <=6) my_hists->quarkjetpt[curr_bin]->Fill(jet_pt, weight);
                if(flavor==5) my_hists->bjetpt[curr_bin]->Fill(jet_pt, weight);
            //    if(flavor==21) my_hists->gluonjetpt[curr_bin]->Fill(jet_pt, weight);
                if(flavor!=5) continue ;  //only B jets selected
            }
            my_hists->BjetSSVHE[curr_bin]->Fill(jet_pt, my_ct->discr_ssvHighEff[j4i], weight);
            my_hists->BjetProb[curr_bin]->Fill(jet_pt, my_ct->discr_prob[j4i], weight);
            //seperate quark and gluon jet analysis
          //  if(my_hists->IsMC==kTRUE) {
                //   if(jet_pt/my_ct->refpt[j4i]<0.8 ||jet_pt/my_ct->refpt[j4i]>1.2)continue ;
                //  if(flavor<1 || flavor >6) continue ; //only quark jets selected
                //   if(flavor!=21) continue ;  //only gluon jets selected
         //   }
            
            //b-jet tagging
            if(my_ct->discr_ssvHighEff[j4i]<btagcut) continue ;
            
            // cout << "jet loop = " << my_ct->discr_ssvHighEff[j4i] <<endl ;
            njets++ ;
            
            my_hists->jesrawpt[curr_bin]->Fill(my_ct->rawpt[j4i], my_ct->rawpt[j4i]/jet_pt, weight);
            my_hists->rawjetpt[curr_bin]->Fill(my_ct->rawpt[j4i], weight);
            bkg_phi = jet_phi;
            bkg_eta = -jet_eta;
            if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetBkgCone[curr_bin]->Fill(bkg_phi-jet_phi, bkg_eta-jet_eta, weight);
            for(Int_t ieta = 0 ; ieta <netabin; ieta++){
                //   if(TMath::Abs(bkg_eta-jet_eta)>deta[ieta]&&TMath::Abs(bkg_eta-jet_eta)<=deta[ieta+1]) dEtaBin = ieta ;
                //  if(TMath::Abs(jet_eta)>deta[ieta]&&TMath::Abs(jet_eta)<=deta[ieta+1]) dEtaBin = ieta ;
           /*     if(coll=="PPb"){
                    if((jet_eta+0.465)>deta[ieta]&&(jet_eta+0.465)<=deta[ieta+1]) dEtaBin = ieta ;
                }
                else if(coll=="PbP"){
                    if((jet_eta-0.465)>deta[ieta]&&(jet_eta-0.465)<=deta[ieta+1]) dEtaBin = ieta ;
                }
                else
             */       if((jet_eta)>deta[ieta]&&(jet_eta)<=deta[ieta+1]) dEtaBin = ieta ;
            }
            
            if(my_hists->IsMC==kTRUE){
                //                //search for leading at the generator level with all matched jets
                //                for(int j4i = 0; j4i < my_ct->nref ; j4i++){
                //
                //                    double refjet_pt= my_ct->refpt[j4i];
                //                    if(TMath::Abs(my_ct->refeta[j4i])>etacut) continue ;
                //                    if(refjet_pt<leadingjetcut) continue ;
                //                    //remove flucluation with too large pt from small MC pthat sample
                //                    if(my_hists->IsMC==kTRUE && refjet_pt>5*pthat) continue ;
                //                    if(refjet_pt >genjet_pt){
                //                        genjet_pt=refjet_pt;
                //                        genj4i=j4i;
                //                    }
                //                } //search for generator leading jet loop
                //                if(genj4i<0) continue ; //no leading found
                //                genjet_pt =my_ct->refpt[genj4i];
                //                genjet_phi =my_ct->refphi[genj4i];
                //                if(genjet_phi<=-TMath::Pi())genjet_phi+=TMath::TwoPi();
                //                genjet_eta =my_ct->refeta[genj4i];
                
                genjet_pt =my_ct->refpt[j4i];
                genjet_phi =my_ct->refphi[j4i];
                if(genjet_phi<=-TMath::Pi())genjet_phi+=TMath::TwoPi();
                genjet_eta =my_ct->refeta[j4i];
             //    cout <<"gen jet =" <<genjet_pt <<endl ;
                if(genjet_pt<0.) continue ;
                genbkg_phi = genjet_phi;
                genbkg_eta = -genjet_eta;
            }
            TVector3 jet_vec;
            TVector3 bkg_vec;
            TVector3 track_vec;
            jet_vec.SetPtEtaPhi(0, 0, 0);
            bkg_vec.SetPtEtaPhi(0, 0, 0);
            track_vec.SetPtEtaPhi(0, 0, 0);
            
            if(my_hists->IsMC==kTRUE){
                
                my_hists->genjetpt[curr_bin]->Fill(jet_pt,genjet_pt, weight);
                my_hists->genjeteta[curr_bin]->Fill(jet_eta, genjet_eta, weight);
                my_hists->genjetphi[curr_bin]->Fill(jet_phi, genjet_phi, weight);
                my_hists->genptRatio[curr_bin]->Fill(genjet_pt,jet_pt/genjet_pt, weight);
                my_hists->genphiRatio[curr_bin]->Fill(jet_pt,genjet_phi-jet_phi, weight);
                my_hists->genetaRatio[curr_bin]->Fill(jet_pt,genjet_eta-jet_eta, weight);
            }
            if(jet_pt<leadingjetcut) continue ;
            my_hists->jetpt[curr_bin]->Fill(jet_pt, weight);
            if(dEtaBin!=-1)my_hists->jetptEtaBin[curr_bin][dEtaBin]->Fill(jet_pt, weight);
            my_hists->jeteta[curr_bin]->Fill(jet_pt, jet_eta, weight);
            my_hists->jetphi[curr_bin]->Fill(jet_pt, jet_phi, weight);
            
            for(Int_t ipt = 0 ; ipt <nptbin; ipt++){
                if(jet_pt>=pt[ipt] && jet_pt <pt[ipt+1]) ptBin = ipt ;
            }
            my_hists->NEvents[curr_bin]->Fill(1, weight);
        /*
            if(TMath::Abs(my_ct->jteta[j4i])>etalimit) { //continue ;
                jet_vec.SetPtEtaPhi(jet_pt, jet_eta, jet_phi);
                bkg_vec.SetPtEtaPhi(jet_pt, bkg_eta, bkg_phi);
                //for track analysis
                int charge[nrbin] ;
                double sumchpt[nrbin];
                double rho[nrbin] ;
                double psi[nrbin] ;
                double sumpt = 0. ;
                double meanphi = 0.;
                double meaneta = 0. ;
                int bkgcharge[nrbin] ;
                double bkgsumchpt[nrbin]  ;
                double bkgrho[nrbin];
                double bkgpsi[nrbin] ;
                double bkgsumpt = 0. ;
                double GenAxisrho[nrbin] ;
                double GenAxisbkgrho[nrbin] ;
                
                double sumTrkpt[nrbin][ntrkptbin];
                
                double jetsumTrk[ntrkptbin];
                
                double bkgsumTrkpt[nrbin][ntrkptbin];
                
                double bkgjetsumTrk[ntrkptbin];
                
                for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                    jetsumTrk[ipt]=0.;
                    bkgjetsumTrk[ipt]=0.;
                }
                for(int ir = 0 ; ir <nrbin ; ir++){
                    charge[ir]=0 ;
                    sumchpt[ir]=0. ;
                    rho[ir]=0. ;
                    psi[ir]= 0.;
                    bkgcharge[ir]=0 ;
                    bkgsumchpt[ir]=0. ;
                    bkgrho[ir]=0.;
                    bkgpsi[ir]=0. ;
                    GenAxisrho[ir]=0. ;
                    GenAxisbkgrho[ir]=0. ;
                    for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                        sumTrkpt[ir][ipt]=0.;
                        bkgsumTrkpt[ir][ipt]=0.;
                    }
                    
                    
                }
                //for tracking correction factors
                float trkweight = 1.;
                Int_t trackcount = 0 ;
                
                for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
                    double dr = 0.;
                    double bkg_dr =0.;
                    double tr_pt = my_tr->trkPt[itr];
                    double tr_phi = my_tr->trkPhi[itr];
                    double tr_eta = my_tr->trkEta[itr];
                    if(TMath::Abs(tr_eta)>2.4) continue ;
                 //   if(my_tr->trkPtError[itr]/my_tr->trkPt[itr]>=0.1 || TMath::Abs(my_tr->trkDz1[itr]/my_tr->trkDzError1[itr])>=3.0 || TMath::Abs(my_tr->trkDxy1[itr]/my_tr->trkDxyError1[itr])>=3.0) continue ; //ridge cut for tracks
                    //    if(coll=="HI" || coll=="PbPb") {
                    //           if(my_tr->trkAlgo[itr]>=4) continue ;
                    //       }
                    //  if(my_tr->trkNHit[itr]<8 ||(my_tr->highPurity[itr]&&my_tr->trkAlgo[itr]==4.0)){
                    //  if(my_tr->trkAlgo[itr]<4 ||(my_tr->highPurity[itr])){
                    if((my_tr->highPurity[itr])){
                        //            if(my_tr->highPurity[itr]==0) continue ;
                        //         if(my_tr->trkAlgo[itr]!=4.0) continue ;
                        // if(TMath::Abs(tr_eta)>tracketacut) continue ;
                        if(tr_pt<trackcut) continue ;
                        track_vec.SetPtEtaPhi(tr_pt, tr_eta, tr_phi);
                        dr = jet_vec.DeltaR(track_vec);
                        bkg_dr = bkg_vec.DeltaR(track_vec);
                        trkweight=1. ;
                        if(doTrackCorrections){
                            if(corrMet=="Hist")trkweight = c->getTrackCorrection(itr);
                            else trkweight = c->getTrackCorrectionPara(itr);
                            //  if(TMath::Abs(trkweight-1.)<0.001)trkweight = c->getTrackCorrection(itr);
                            if(TMath::Abs(jet_eta)>=etalimit) my_hists->trackpteff[curr_bin]->Fill(tr_pt,1./trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit) my_hists->trackdreff[curr_bin]->Fill(dr,tr_pt*trkweight);                               }
                        
                        
                        if(TMath::Abs(jet_eta)>=etalimit)my_hists->deltaR->Fill(dr, weight);
                        double jtrdphi = tr_phi-jet_phi ;
                        //            if(jtrdphi>TMath::Pi())jtrdphi-=TMath::TwoPi();
                        //            if(jtrdphi<=-TMath::Pi()) jtrdphi+=TMath::TwoPi();
                        if(TMath::Abs(jet_eta)>=etalimit)my_hists->IncTrackDphi[curr_bin]->Fill(jet_pt,TMath::Abs(jtrdphi), weight);
                        if(dr<=conesize){  //for leading jet shape study
                           //     if(curr_bin==nbin-1 && evi <10000) cout << ", evi: " << evi << " of " << c->GetEntries() << "  icentrality = " <<curr_bin << "   jet index : " << j4i << "   jetpt : " <<  jet_pt << " jet eta : "  << jet_eta <<  "   jetphi :  " << jet_phi <<    "   trkId : " << itr <<  "   trkpt : " << tr_pt<<  "   trk weight : " << c->getTrackCorrection(itr) << "  trkEta: " << tr_eta << "   trkPhi : " <<  tr_phi << "    deltaR : " << dr  << endl;
                            trackcount++;
                            
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetTrackDphi[curr_bin]->Fill(jet_pt,TMath::Abs(jtrdphi), weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetTrackDeta[curr_bin]->Fill(jet_pt,tr_eta-jet_eta, weight*trkweight);
                            
                            //  if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetfrag[curr_bin]->Fill(jet_pt, TMath::Log(jet_pt/tr_pt), weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetfrag[curr_bin]->Fill(jet_pt, TMath::Log((jet_pt*TMath::CosH(jet_eta))/(tr_pt*TMath::CosH(tr_eta)*TMath::Cos(dr))), weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit && dEtaBin!=-1)my_hists->jetFFEtaBin[curr_bin][dEtaBin]->Fill(jet_pt, TMath::Log((jet_pt*TMath::CosH(jet_eta))/(tr_pt*TMath::CosH(tr_eta)*TMath::Cos(dr))), weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->trackpt[curr_bin]->Fill(jet_pt, tr_pt, weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit && dEtaBin!=-1)my_hists->trackPtEtaBin[curr_bin][dEtaBin]->Fill(jet_pt, tr_pt, weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->trackrawpt[curr_bin]->Fill(tr_pt, weight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->trackphi[curr_bin]->Fill(jet_pt, tr_phi, weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->tracketa[curr_bin]->Fill(jet_pt, tr_eta, weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->trackdr[curr_bin][ptBin]->Fill(tr_pt,dr, weight*trkweight);
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->wttrackdr[curr_bin][ptBin]->Fill(tr_pt,dr, tr_pt*weight*trkweight);
                            sumpt+=tr_pt*trkweight ;
                            meaneta+=tr_pt*tr_eta*trkweight;
                            meanphi+=tr_pt*tr_phi*trkweight;
                            for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                                //  if(tr_pt*trkweight>trkpt[ipt] && tr_pt*trkweight<=trkpt[ipt+1])jetsumTrk[ipt]+=tr_pt*trkweight ;
                                if(tr_pt*trkweight<=trkpt[ipt+1])jetsumTrk[ipt]+=tr_pt*trkweight ;
                            }
                            
                            for(int ir = 0 ; ir <nrbin; ir++){
                                if(dr>rbin[ir]&&dr<=rbin[ir+1]){
                                    rho[ir]+=tr_pt*trkweight ;
                                //         cout<<" !!!! track index =" <<itr << " trk pt =" <<tr_pt << " tr phi =" <<tr_phi << " tr eta =" <<tr_eta  <<" dr =" <<dr <<" rho =" <<rho[ir]<<endl ;
                                    if(TMath::Abs(jet_eta)>=etalimit)my_hists->ChargePt[curr_bin][ir]->Fill(jet_pt, tr_pt, weight*trkweight);
                                    sumchpt[ir]+=tr_pt*trkweight ;
                                    charge[ir]++ ;
                                    for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                                        //  if(tr_pt*trkweight>trkpt[ipt] && tr_pt*trkweight<=trkpt[ipt+1])sumTrkpt[ir][ipt]+=tr_pt*trkweight ;
                                        if(tr_pt*trkweight<=trkpt[ipt+1])sumTrkpt[ir][ipt]+=tr_pt*trkweight ;
                                    }
                                    
                                }
                                if(dr<=rbin[ir+1]) {
                                    psi[ir]+=tr_pt*trkweight ;
                                }
                            }  //radius loop for rho calculation
                        } //inside leading jet cone
                        else { //outside leading and subleading jet cone
         //              cout << "track loop = " << bkg_dr<<endl ;
                            if(bkg_dr<=conesize){
                                if(doTrackCorrections){
                                    if(TMath::Abs(jet_eta)>=etalimit) my_hists->bkgtrackpteff[curr_bin]->Fill(tr_pt,1./trkweight);
                                    if(TMath::Abs(jet_eta)>=etalimit) my_hists->bkgtrackdreff[curr_bin]->Fill(bkg_dr,tr_pt*trkweight);
                                }
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->bkgtrackpt[curr_bin]->Fill(jet_pt, tr_pt, weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit && dEtaBin!=-1)my_hists->bkgtrackPtEtaBin[curr_bin][dEtaBin]->Fill(jet_pt, tr_pt, weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->bkgtrackdr[curr_bin][ptBin]->Fill(tr_pt,bkg_dr, weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->bkgwttrackdr[curr_bin][ptBin]->Fill(tr_pt,bkg_dr, tr_pt*weight*trkweight);
                                bkgsumpt+=tr_pt*trkweight ;
                                for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                                    //  if(tr_pt*trkweight>trkpt[ipt] && tr_pt*trkweight<=trkpt[ipt+1])bkgjetsumTrk[ipt]+=tr_pt*trkweight ;
                                    if(tr_pt*trkweight<=trkpt[ipt+1])bkgjetsumTrk[ipt]+=tr_pt*trkweight ;
                                }
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetBkgTrackDphi[curr_bin]->Fill(jet_pt,TMath::Abs(jtrdphi), weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetBkgTrackDeta[curr_bin]->Fill(jet_pt,tr_eta-jet_eta, weight*trkweight);
                                //   if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetbkgfrag[curr_bin]->Fill(jet_pt, TMath::Log(jet_pt/tr_pt), weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetbkgfrag[curr_bin]->Fill(jet_pt, TMath::Log((jet_pt*TMath::CosH(jet_eta))/(tr_pt*TMath::CosH(tr_eta)*TMath::Cos(bkg_dr))), weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit && dEtaBin!=-1)my_hists->bkgFFEtaBin[curr_bin][dEtaBin]->Fill(jet_pt, TMath::Log((jet_pt*TMath::CosH(jet_eta))/(tr_pt*TMath::CosH(tr_eta)*TMath::Cos(bkg_dr))), weight*trkweight);
                                for(int ir = 0 ; ir <nrbin; ir++){
                                    if(bkg_dr>rbin[ir]&&bkg_dr<=rbin[ir+1]){
                                        if(TMath::Abs(jet_eta)>=etalimit)my_hists->bkgChargePt[curr_bin][ir]->Fill(jet_pt, tr_pt, weight*trkweight);
                                        bkgrho[ir]+=tr_pt*trkweight ;
                                        bkgsumchpt[ir]+=tr_pt*trkweight ;
                                        bkgcharge[ir]++ ;
                                        for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                                            //  if(tr_pt*trkweight>trkpt[ipt] && tr_pt*trkweight<=trkpt[ipt+1])bkgsumTrkpt[ir][ipt]+=tr_pt*trkweight ;
                                            if(tr_pt*trkweight<=trkpt[ipt+1])bkgsumTrkpt[ir][ipt]+=tr_pt*trkweight ;
                                        }
                                        
                                    }
                                    if(bkg_dr<=rbin[ir+1]) {
                                        bkgpsi[ir]+=tr_pt*trkweight ;
                                    } //fill bkg subleading JS
                                }  //radius loop for leading jet backgound
                            }  //bkg cone for leading jet bkg
                        }
                        if(my_hists->IsMC==kTRUE){
                            genjet_vec.SetPtEtaPhi(genjet_pt, genjet_eta, genjet_phi);
                            genbkg_vec.SetPtEtaPhi(genjet_pt, genbkg_eta, genbkg_phi);
                            track_vec.SetPtEtaPhi(tr_pt, tr_eta, tr_phi);
                            
                            double GenAxisdr = genjet_vec.DeltaR(track_vec);
                            double GenAxisbkgdr = genbkg_vec.DeltaR(track_vec);
                            //   double GenAxisdr =TMath::Sqrt((tr_phi-genjet_phi)*(tr_phi-genjet_phi)+(tr_eta-genjet_eta)*(tr_eta-genjet_eta));
                            //    double GenAxisbkgdr =TMath::Sqrt((tr_phi-genbkg_phi)*(tr_phi-genbkg_phi)+(tr_eta-genbkg_eta)*(tr_eta-genbkg_eta));
                            
                            if(dr<=conesize&&TMath::Abs(jet_eta)>=etalimit)my_hists->jetaxisRes[curr_bin]->Fill(jet_pt, (GenAxisdr-dr)/dr, weight);
                            if(GenAxisdr<=conesize){
                                for(int ir = 0 ; ir <nrbin; ir++){
                                    if(GenAxisdr>rbin[ir]&&GenAxisdr<=rbin[ir+1]){
                                        GenAxisrho[ir]+=tr_pt*trkweight ;
                                    }
                                }  //radius loop to fill leading jet JS histogram
                            } //tracks inside for leading jet
                            if(GenAxisbkgdr<=conesize){
                                trkweight=1. ;
                                //                        if(doTrackCorrections)trkweight = c->getTrackCorrection(itr);
                                if(doTrackCorrections){
                                    if(corrMet=="Hist")trkweight = c->getTrackCorrection(itr);
                                    else trkweight = c->getTrackCorrectionPara(itr);
                                }
                                for(int ir = 0 ; ir <nrbin; ir++){
                                    if(GenAxisbkgdr>rbin[ir]&&GenAxisbkgdr<=rbin[ir+1]){
                                        GenAxisbkgrho[ir]+=tr_pt*trkweight ;
                                    }
                                }  //radius loop to fill leading jet bkg JS histogram
                            } //leading jet with gen axis background JS
                        } //fill only when MC
                    } //track selection
                } //track loop
                //     if(TMath::Abs(jet_eta)>=etalimit){ //remove overlap region for ER bkg
                  //  cout << "finish track loop = " << jet_pt <<endl ;
                my_hists->SumptJetPt[curr_bin]->Fill(jet_pt,sumpt/jet_pt, weight);
                if(DoSumPtNorm && sumpt==0.)  continue ;
                
                for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                    my_hists->jetPtSumTrk[curr_bin][ipt]->Fill(jet_pt, jetsumTrk[ipt], weight);
                    my_hists->bkgjetPtSumTrk[curr_bin][ipt]->Fill(jet_pt, bkgjetsumTrk[ipt], weight);
                    
                }
                //fill jet shape histogram
                for(int ir = 0 ; ir <nrbin; ir++){
                    if(DoSumPtNorm){
                        psi[ir]/=sumpt;
                        rho[ir]/=sumpt;
                        bkgpsi[ir]/=sumpt;
                        bkgrho[ir]/=sumpt;
                        sumchpt[ir]/=sumpt ;
                        bkgsumchpt[ir]/=sumpt ;
                        for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                            sumTrkpt[ir][ipt]/=sumpt ;
                            bkgsumTrkpt[ir][ipt]/=sumpt ;
                        }
                        
                    }
                    else {
                        psi[ir]/=jet_pt;
                        rho[ir]/=jet_pt;
                        bkgpsi[ir]/=jet_pt;
                        bkgrho[ir]/=jet_pt;
                        sumchpt[ir]/=jet_pt ;
                        bkgsumchpt[ir]/=jet_pt ;
                        for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                            sumTrkpt[ir][ipt]/=jet_pt ;
                            bkgsumTrkpt[ir][ipt]/=jet_pt ;
                        }
                        
                        
                    }
                    for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                        my_hists->jetdrSumTrkPt[curr_bin][ptBin][ipt]->Fill((rbin[ir]+0.025), sumTrkpt[ir][ipt]*weight);
                        my_hists->bkgjetdrSumTrkPt[curr_bin][ptBin][ipt]->Fill((rbin[ir]+0.025), bkgsumTrkpt[ir][ipt]*weight);
                    }
                    
                    my_hists->ChargeMult[curr_bin][ir]->Fill(jet_pt, charge[ir], weight);
                    my_hists->SumChPt[curr_bin][ir]->Fill(jet_pt, sumchpt[ir],weight);
                    my_hists->bkgChargeMult[curr_bin][ir]->Fill(jet_pt, bkgcharge[ir],weight);
                    my_hists->bkgSumChPt[curr_bin][ir]->Fill(jet_pt, bkgsumchpt[ir],weight);
                    my_hists->DiffJS[curr_bin][ir]->Fill(jet_pt, rho[ir],weight);
                    my_hists->IntJS[curr_bin][ir]->Fill(jet_pt, psi[ir],weight);
                    // rho/=deltacone ;
                    my_hists->bkgDiffJS[curr_bin][ir]->Fill(jet_pt, bkgrho[ir],weight);
                    //   my_hists->IntJS[curr_bin]->Fill(jet_pt, 1-psi);
                    my_hists->bkgIntJS[curr_bin][ir]->Fill(jet_pt, bkgpsi[ir],weight);
                    if(my_hists->IsMC==kTRUE){
                        if(DoSumPtNorm){
                            GenAxisrho[ir]/=sumpt;
                            GenAxisbkgrho[ir]/=sumpt;
                        }
                        else {
                            GenAxisrho[ir]/=jet_pt;
                            GenAxisbkgrho[ir]/=jet_pt;
                        }
                        my_hists->GenAxisDiffJS[curr_bin][ir]->Fill(jet_pt, GenAxisrho[ir],weight);
                        my_hists->GenAxisbkgDiffJS[curr_bin][ir]->Fill(jet_pt, GenAxisbkgrho[ir],weight);
                    }
                    if(jet_pt>=100 &&jet_pt<120) {
                        //   my_hists->DiffJSPt80_100[curr_bin][ir]->Fill(rho[ir]);
                        my_hists->DiffJSPt80_100[curr_bin]->Fill(rbin[ir]+0.025, rho[ir]*weight);
                        my_hists->bkgDiffJSPt80_100[curr_bin]->Fill(rbin[ir]+0.025, bkgrho[ir]*weight);
                        my_hists->DiffJSPt80_100Rbin[curr_bin][ir]->Fill(rho[ir],weight);
                        my_hists->bkgDiffJSPt80_100Rbin[curr_bin][ir]->Fill(bkgrho[ir],weight);
                    }
                    if(dEtaBin!=-1){
                        my_hists->DiffEtaBinJS[curr_bin][dEtaBin][ir]->Fill(jet_pt, rho[ir],weight);
                        my_hists->bkgDiffEtaBinJS[curr_bin][dEtaBin][ir]->Fill(jet_pt, bkgrho[ir],weight);
                    }
                    cout << "fill JS histogram = " << ir <<endl ;
                } //radius bin loop
                my_hists->NJets[curr_bin]->Fill(1, weight);
                if(bkgsumpt>sumpt)my_hists->RareEvt->Fill(offSel->hiBin, weight);
            }  //remove overlape eta regions from jet cone and ER bkg cone
          */  
        } //jet loop
        //  cout << "still working222222\n";
        if(my_hists->IsMC==kFALSE)my_hists->VertexWt->Fill(vz+0.4847, weight);
        else  my_hists->VertexWt->Fill(vz, weight);
        if(coll=="HI")
            my_hists->CenBinWt->Fill(offSel->hiBin*2.5,weight);
        else
            my_hists->CenBinWt->Fill(offSel->hiBin,weight);
        
/*        //for inclusive track analysis, without jet selection and requirement
        for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
            double tr_pt = my_tr->trkPt[itr];
            double tr_phi = my_tr->trkPhi[itr];
            double tr_eta = my_tr->trkEta[itr];
            if(TMath::Abs(tr_eta)>2.4) continue ;
          //  if(my_tr->trkPtError[itr]/my_tr->trkPt[itr]>=0.1 || TMath::Abs(my_tr->trkDz1[itr]/my_tr->trkDzError1[itr])>=3.0 ||TMath::Abs(my_tr->trkDxy1[itr]/my_tr->trkDxyError1[itr])>=3.0) continue ; //ridge cut for tracks
            if((my_tr->highPurity[itr])){
                if(tr_pt<trackcut) continue ;
                double trkweight=1. ;
                if(doTrackCorrections){
                    if(corrMet=="Hist")trkweight = c->getTrackCorrection(itr);
                    else trkweight = c->getTrackCorrectionPara(itr);
                }
                my_hists->inctrkpt[curr_bin]->Fill(tr_pt, weight*trkweight);
            } //! high purity track cuts
        }  //! inclusive track loop
*/    }  ///event loop
    
    my_hists->Write();
    //   my_hists->Delete();
    //  delete my_hists;
    std::cout << "working done\n";
}




