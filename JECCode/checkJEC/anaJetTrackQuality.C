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
#include "hiForest.h"
#include "commonSetup.h"

using namespace std;

//define the kinematics cuts for the analysis
const double conesize = 0.5 ;
const double deltacone = 0.1 ;

//const double radius = 0.025;

//const int nrbin = 10 ;
//double rbin[nrbin+1]={0.0,0.05,0.10, 0.15, 0.20,0.25,0.30,0.35,0.40,0.45,0.50};

const int nrbin = 5 ;
double rbin[nrbin+1]={0.0,0.1, 0.2,0.3, 0.4, 0.5};

const double etacut = 2.0 ;
//const double dphicut = TMath::TwoPi()/3. ;
const double dphicut = 2*TMath::Pi()/3. ;
const double leadingjetcut = 20. ;
const double trackcut = 1.;
const double tracketacut = 2.4; //make sure the tracks around jet cone inside eta range

////for etalimit = 0.3, to remove the possible overlap region by ER method 
const double etalimit = 0.3 ; 

TString model = "PYTHIA"; //or AMPT generator
const Int_t pthat = 30 ;
const bool DoGenAna=kTRUE ; //should be only be true for MC sample

//do tracking corrections
const bool doTrackCorrections = kFALSE; //for tracking efficiency correction
TString corrMet = "Hist" ; //Hist table from Frank, or Para from Krisztian
TrackingParam *trackCorrFromParam;

vector<TrackingCorrections*> trackCorrections;


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
const double pt[]={0., 500.};

const int ntrkptbin = 6 ;
const double trkpt[]={1., 2., 4., 8., 16., 32., 500.};

//const int ntrkptbin = 3 ;
//const double trkpt[]={1.,4., 16., 300.};

const Double_t jetPtBin[] = {20, 30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,400};
//const Double_t jetPtBin[] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 200, 240, 300};
//const Double_t jetPtBin[] = {100, 110, 120, 130, 140, 150, 160, 180, 200, 240, 300, 500};
const int nJetPtBin = sizeof(jetPtBin)/sizeof(Double_t)-1 ;

const int netabin = 4 ;
const double deta[]={0.0,0.5,1.0,1.5,2.0} ;
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
    TH2F * jeteta[nbin];
    TH2F * jetphi[nbin];

    TH2F * trackpt[nbin];
    TH2F * trackphi[nbin];
    TH2F * tracketa[nbin];
    TH2F * trackdr[nbin][nptbin];
    TH2F * bkgtrackdr[nbin][nptbin];
    TH2F * wttrackdr[nbin][nptbin];
    TH2F * bkgwttrackdr[nbin][nptbin];
    TH2F * jetaxisRes[nbin];

    //jet ID check
    TH2F * trackMax[nbin];
    TH2F * trackSum[nbin];
    TH2D * trackN[nbin];
    TH2F * photonMax[nbin];
    TH2F * photonSum[nbin];    
    TH2D * photonN[nbin];
    TH2F * neutralMax[nbin];
    TH2F * neutralSum[nbin];   
    TH2D * neutralN[nbin];
    TH2F * hcalSum[nbin];
    TH2F * ecalSum[nbin];
    
    TH2F * leadingtrackjet[nbin];
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
    TH1D * RareEvt;
    TH1F * Vertex ;

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
    //   if(IsMC){
    TH2F * genjetpt[nbin];
    TH2F * genjeteta[nbin];
    TH2F * genjetphi[nbin];
    TH2F * gendphi[nbin];
     TH2F * genptRatio[nbin];
    TH2F * genphiRatio[nbin] ;
    TH2F * genetaRatio[nbin] ; 
    TH2F * genpartpt[nbin] ;
    TH2F * genpartphi[nbin] ;
    TH2F * genparteta[nbin] ;
    TH2F * bkgpartpt[nbin];
    TH2F * bkgparteta[nbin];
    TH2F * genpartdr[nbin][nptbin];
    TH2F * matchpartdr[nbin][nptbin];
    TH2F * genbkgpartdr[nbin][nptbin];
    TH2F * matchbkgpartdr[nbin][nptbin];
    
    //weighted pt distribution
    TH2F * wtgenpartdr[nbin][nptbin];
    TH2F * wtmatchpartdr[nbin][nptbin];
    TH2F * wtgenbkgpartdr[nbin][nptbin];
    TH2F * wtmatchbkgpartdr[nbin][nptbin];

    TH1F * genjetdrSumTrkPt[nbin][nptbin][ntrkptbin];
    TH1F * bkggenjetdrSumTrkPt[nbin][nptbin][ntrkptbin];

    TH2F * genSumPt[nbin] ;
    TH2F * genChargePt[nbin][nrbin];
    TH2F * genSumChPt[nbin][nrbin];
    TH2F * genChargeMult[nbin][nrbin];   
    TH2F * genDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * genIntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.
    //  TH2F * dphiJS[nbin]; //phi diviration from jet phi 
    //   TH2F * detaJS[nbin] ; //eta diviration from jet eta 
    
    //for jet shape background study  
    TH2F * genbkgChargePt[nbin][nrbin];
    TH2F * genbkgSumChPt[nbin][nrbin];
    TH2F * genbkgChargeMult[nbin][nrbin];   
    TH2F * genbkgDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * genbkgIntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.

//    //for subleading jet shape, fill according leading jet bins
//    TH2F * gensubDiffJS[nbin][nptbin][nrbin]; //differential sub-jet shapes (pho(r)) hist.
//    TH2F * gensubIntJS[nbin][nptbin][nrbin]; //Integrated sub-jet shapes (psi(r)) hist.
//    TH2F * genbkgsubDiffJS[nbin][nptbin][nrbin]; //differential sub-jet shapes (pho(r)) hist.
//    TH2F * genbkgsubIntJS[nbin][nptbin][nrbin]; //Integrated sub-jet shapes (psi(r)) hist. 

    //   }
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
        jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.);	
  //    else   jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin);
        jetpt[ibin]->Sumw2();
      //  jeteta[ibin] = new TH2F(Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin,100, -5., 5.);
        jeteta[ibin] = new TH2F(Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -5., 5.);
        jeteta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jeteta[ibin]->GetYaxis()->SetTitle("#eta");
        jeteta[ibin]->Sumw2();
      //  jetphi[ibin] = new TH2F(Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), nJetPtBin, jetPtBin,100, -5., 5.);
        jetphi[ibin] = new TH2F(Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -5., 5.);
        jetphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetphi[ibin]->GetYaxis()->SetTitle("#phi");
        jetphi[ibin]->Sumw2();

        trackpt[ibin] = new TH2F(Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 200, 0., 200); 
        trackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackpt[ibin]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        trackpt[ibin]->Sumw2();
        trackphi[ibin] = new TH2F(Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5., 5.); 
        trackphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackphi[ibin]->GetYaxis()->SetTitle("#phi^{trk}");   
        trackphi[ibin]->Sumw2();
        tracketa[ibin] = new TH2F(Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5., 5.); 
        tracketa[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        tracketa[ibin]->GetYaxis()->SetTitle("#eta^{trk}");   
        tracketa[ibin]->Sumw2();

        //jet ID variables
        trackMax[ibin] = new TH2F(Form("trackMax_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackMax_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        trackMax[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackMax[ibin]->GetYaxis()->SetTitle("p_{T}^{TrkMax}/p_{T}^{jet}");
        trackMax[ibin]->Sumw2();
        trackSum[ibin] = new TH2F(Form("trackSum_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackSum_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        trackSum[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackSum[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{track}/p_{T}^{jet}");
        trackSum[ibin]->Sumw2();
        trackN[ibin] = new TH2D(Form("trackN_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackN_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0, 100);
        trackN[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackN[ibin]->GetYaxis()->SetTitle("Track Multiplicity");
        trackN[ibin]->Sumw2();
        photonMax[ibin] = new TH2F(Form("photonMax_%d-%d%%",centr[ibin],centr[ibin+1]), Form("photonMax_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        photonMax[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        photonMax[ibin]->GetYaxis()->SetTitle("p_{T}^{PhotonMax}/p_{T}^{jet}");
        photonMax[ibin]->Sumw2();
        photonSum[ibin] = new TH2F(Form("photonSum_%d-%d%%",centr[ibin],centr[ibin+1]), Form("photonSum_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        photonSum[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        photonSum[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{photon}/p_{T}^{jet}");
        photonSum[ibin]->Sumw2();
        photonN[ibin] = new TH2D(Form("photonN_%d-%d%%",centr[ibin],centr[ibin+1]), Form("photonN_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0, 100);
        photonN[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        photonN[ibin]->GetYaxis()->SetTitle("photon Multiplicity");
        photonN[ibin]->Sumw2();
        neutralMax[ibin] = new TH2F(Form("neutralMax_%d-%d%%",centr[ibin],centr[ibin+1]), Form("neutralMax_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        neutralMax[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        neutralMax[ibin]->GetYaxis()->SetTitle("p_{T}^{neutralMax}/p_{T}^{jet}");
        neutralMax[ibin]->Sumw2();
        neutralSum[ibin] = new TH2F(Form("neutralSum_%d-%d%%",centr[ibin],centr[ibin+1]), Form("neutralSum_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        neutralSum[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        neutralSum[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{Neutral}/p_{T}^{jet}");
        neutralSum[ibin]->Sumw2();
        neutralN[ibin] = new TH2D(Form("neutralN_%d-%d%%",centr[ibin],centr[ibin+1]), Form("neutralN_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 100);
        neutralN[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        neutralN[ibin]->GetYaxis()->SetTitle("Neutral Multiplicity");
        neutralN[ibin]->Sumw2();
        ecalSum[ibin] = new TH2F(Form("ecalSum_%d-%d%%",centr[ibin],centr[ibin+1]), Form("ecalSum_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        ecalSum[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        ecalSum[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{ecal}/p_{T}^{jet}");
        ecalSum[ibin]->Sumw2();
        hcalSum[ibin] = new TH2F(Form("hcalSum_%d-%d%%",centr[ibin],centr[ibin+1]), Form("hcalSum_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        hcalSum[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        hcalSum[ibin]->GetYaxis()->SetTitle("#Sigma p_{T}^{hcal}/p_{T}^{jet}");
        hcalSum[ibin]->Sumw2();
        
        leadingtrackjet[ibin] = new TH2F(Form("leadingtrackjetratio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("leadingtrackjetratio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, 0., 10.);
        leadingtrackjet[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        //  jetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet}/p_{T}^{h})");
        leadingtrackjet[ibin]->GetYaxis()->SetTitle("p_{T}^{trk}/p_{T}^{jet}");
        leadingtrackjet[ibin]->Sumw2();
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
        //jet pt bins loop
        for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
	  trackdr[ibin][ipt] = new TH2F(Form("recoTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recoTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
            trackdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
            trackdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
            trackdr[ibin][ipt]->Sumw2();
            bkgtrackdr[ibin][ipt] = new TH2F(Form("recobkgTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recobkgTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
            bkgtrackdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
            bkgtrackdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");
            bkgtrackdr[ibin][ipt]->Sumw2();
            wttrackdr[ibin][ipt] = new TH2F(Form("recowtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recowtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
            wttrackdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{trk} (GeV/c)");
            wttrackdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
            wttrackdr[ibin][ipt]->Sumw2();
            bkgwttrackdr[ibin][ipt] = new TH2F(Form("recobkgwtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("recobkgwtTrackJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
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
        JetBkgCone[ibin] = new TH2F(Form("JetBkgAxisDifference_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetBkgAxisDifference_%d-%d%%",centr[ibin],centr[ibin+1]), 140, -7., 7.,100, -5., 5.);
        JetBkgCone[ibin]->GetXaxis()->SetTitle("#phi_{bkg}-#phi_{jet}");
        JetBkgCone[ibin]->GetYaxis()->SetTitle("#eta_{bkg}-#eta_{jet}");
        JetBkgCone[ibin]->Sumw2();
        IncTrackDphi[ibin] = new TH2F(Form("AllTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("AllTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4., 8.);
        IncTrackDphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        IncTrackDphi[ibin]->GetYaxis()->SetTitle("#phi_{trk}-#phi_{jet}");
        IncTrackDphi[ibin]->Sumw2();
        JetTrackDphi[ibin] = new TH2F(Form("JetTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4., 8.);
        JetTrackDphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetTrackDphi[ibin]->GetYaxis()->SetTitle("#phi_{trk}-#phi_{jet}");
        JetTrackDphi[ibin]->Sumw2();
        JetBkgTrackDphi[ibin] = new TH2F(Form("JetBkgTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetBkgTrackDphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4., 8.);
        JetBkgTrackDphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetBkgTrackDphi[ibin]->GetYaxis()->SetTitle("#phi_{trk}-#phi_{jet}");
        JetBkgTrackDphi[ibin]->Sumw2();
        JetTrackDeta[ibin] = new TH2F(Form("JetTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -5., 5.);
        JetTrackDeta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetTrackDeta[ibin]->GetYaxis()->SetTitle("#eta_{trk}-#eta_{jet}");
        JetTrackDeta[ibin]->Sumw2();
        JetBkgTrackDeta[ibin] = new TH2F(Form("JetBkgTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetBkgTrackDeta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -5., 5.);
        JetBkgTrackDeta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        JetBkgTrackDeta[ibin]->GetYaxis()->SetTitle("#eta_{trk}-#eta_{jet}");
        JetBkgTrackDeta[ibin]->Sumw2();
        bkgtrackpt[ibin] = new TH2F(Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 200, 0., 200); 
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
        if(IsMC&&DoGenAna){
            genjetpt[ibin] = new TH2F(Form("genjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 500, 0., 500.);
            genjetpt[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            genjetpt[ibin]->GetYaxis()->SetTitle("p_{T}^{gen} (GeV/c)");   
            genjetpt[ibin]->Sumw2();
            genjeteta[ibin] = new TH2F(Form("genjeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjeteta_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -5., 5.,100, -5., 5.);
            genjeteta[ibin]->GetXaxis()->SetTitle("#eta^{rec}");
            genjeteta[ibin]->GetYaxis()->SetTitle("#eta^{gen}");
            genjeteta[ibin]->Sumw2();
            genjetphi[ibin] = new TH2F(Form("genjetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjetphi_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -5., 5.,100, -5., 5.);
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
            genpartpt[ibin] = new TH2F(Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 200, 0., 200);
            genpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genpartpt[ibin]->GetYaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            genpartpt[ibin]->Sumw2();
            genpartphi[ibin] = new TH2F(Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, -5., 5.);
            genpartphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genpartphi[ibin]->GetYaxis()->SetTitle("#phi^{part}");   
            genpartphi[ibin]->Sumw2();
            genparteta[ibin] = new TH2F(Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 100, -5., 5.);
            genparteta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genparteta[ibin]->GetYaxis()->SetTitle("#eta^{part} ");   
            genparteta[ibin]->Sumw2();
            bkgpartpt[ibin] = new TH2F(Form("bkgpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 200, 0., 200); 
            bkgpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgpartpt[ibin]->GetYaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            bkgpartpt[ibin]->Sumw2();
            bkgparteta[ibin] = new TH2F(Form("bkgparteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgparteta_%d-%d%%",centr[ibin],centr[ibin+1]), 200, 0., 200, 100, -5., 5.); 
            bkgparteta[ibin]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
            bkgparteta[ibin]->GetYaxis()->SetTitle("#eta^{part} (GeV/c)");   
            bkgparteta[ibin]->Sumw2();

            genSumPt[ibin] = new TH2F(Form("genSumPt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genSumPto_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,500, 0., 500.);  
            genSumPt[ibin]->GetXaxis()->SetTitle("#Sum p_{T}^{rec}(R) (GeV/c)");
            genSumPt[ibin]->GetYaxis()->SetTitle("#Sum p_{T}^{gen}(R) (GeV/c)");
            genSumPt[ibin]->Sumw2();
            jetaxisRes[ibin] = new TH2F(Form("JetAxisRes_%d-%d%%",centr[ibin],centr[ibin+1]), Form("JetAxisRes_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500., 200, -1., 1.);
            jetaxisRes[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            jetaxisRes[ibin]->GetYaxis()->SetTitle("#Delta r=r_{genAxis}-r_{recoAxis}");
            jetaxisRes[ibin]->Sumw2();
            for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
                genpartdr[ibin][ipt] = new TH2F(Form("genPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("genPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                genpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                genpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                genpartdr[ibin][ipt]->Sumw2();
                matchpartdr[ibin][ipt] = new TH2F(Form("matchPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("matchPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                matchpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                matchpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                matchpartdr[ibin][ipt]->Sumw2();
                genbkgpartdr[ibin][ipt] = new TH2F(Form("genbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("genbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                genbkgpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                genbkgpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                genbkgpartdr[ibin][ipt]->Sumw2();
                matchbkgpartdr[ibin][ipt] = new TH2F(Form("matchbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("matchbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                matchbkgpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                matchbkgpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                matchbkgpartdr[ibin][ipt]->Sumw2();

                wtgenpartdr[ibin][ipt] = new TH2F(Form("wtgenPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("wtgenPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                wtgenpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                wtgenpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                wtgenpartdr[ibin][ipt]->Sumw2();
                wtmatchpartdr[ibin][ipt] = new TH2F(Form("wtmatchPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("wtmatchPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                wtmatchpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                wtmatchpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                wtmatchpartdr[ibin][ipt]->Sumw2();
                wtgenbkgpartdr[ibin][ipt] = new TH2F(Form("wtgenbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("wtgenbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                wtgenbkgpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                wtgenbkgpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                wtgenbkgpartdr[ibin][ipt]->Sumw2();
                wtmatchbkgpartdr[ibin][ipt] = new TH2F(Form("wtmatchbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), Form("wtmatchbkgPartJetPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1], centr[ibin],centr[ibin+1]), 200, 0., 200, (Int_t)(conesize*100/(deltacone*100)), 0., conesize); 
                wtmatchbkgpartdr[ibin][ipt]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
                wtmatchbkgpartdr[ibin][ipt]->GetYaxis()->SetTitle("radius r");   
                wtmatchbkgpartdr[ibin][ipt]->Sumw2();

                for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){ //track bins loop
                    genjetdrSumTrkPt[ibin][ipt][itr]=new TH1F(Form("genJetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), Form("genJetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
                    genjetdrSumTrkPt[ibin][ipt][itr]->GetXaxis()->SetTitle("radius r"); 
                    genjetdrSumTrkPt[ibin][ipt][itr]->GetYaxis()->SetTitle("#Sigma p_{T}^{trk}/p_{T}^{jet}"); 
                    genjetdrSumTrkPt[ibin][ipt][itr]->Sumw2();
                    
                    bkggenjetdrSumTrkPt[ibin][ipt][itr]=new TH1F(Form("bkggenJetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), Form("bkggenJetPt%.f_%.fSumTrkPt%.f_%.f_%d-%d%%",pt[ipt],pt[ipt+1],trkpt[itr],trkpt[itr+1], centr[ibin],centr[ibin+1]), (Int_t)(conesize*100/(deltacone*100)), 0., conesize);
                    bkggenjetdrSumTrkPt[ibin][ipt][itr]->GetXaxis()->SetTitle("radius r"); 
                    bkggenjetdrSumTrkPt[ibin][ipt][itr]->GetYaxis()->SetTitle("#Sigma p_{T}^{trk}/p_{T}^{jet}"); 
                    bkggenjetdrSumTrkPt[ibin][ipt][itr]->Sumw2();
                } //track bins loop

            }  //jet bins loop
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
        if(IsMC&&DoGenAna){
            for(int ir = 0 ; ir <nrbin; ir++){
                genChargePt[ibin][ir] = new TH2F(Form("genchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500);
                genChargePt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genChargePt[ibin][ir]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
                genChargePt[ibin][ir]->Sumw2();
                genSumChPt[ibin][ir] = new TH2F(Form("gensumchptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("gensumchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                genSumChPt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genSumChPt[ibin][ir]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");
                genSumChPt[ibin][ir]->Sumw2();
                genChargeMult[ibin][ir] = new TH2F(Form("genChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -0.5, 99.5);
                genChargeMult[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genChargeMult[ibin][ir]->GetYaxis()->SetTitle("# of Charge");   
                genChargeMult[ibin][ir]->Sumw2();
                
                genDiffJS[ibin][ir] = new TH2F(Form("gendifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("gendifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                genDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
                genDiffJS[ibin][ir]->Sumw2();
                genIntJS[ibin][ir] = new TH2F(Form("genIntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genIntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                genIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
                genIntJS[ibin][ir]->Sumw2();
                //for bkg histos.
                genbkgChargePt[ibin][ir] = new TH2F(Form("genbkgchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genbkgchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500);
                genbkgChargePt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genbkgChargePt[ibin][ir]->GetYaxis()->SetTitle("p_{T} (GeV/c)");
                genbkgChargePt[ibin][ir]->Sumw2();
                genbkgSumChPt[ibin][ir] = new TH2F(Form("genbkgsumchptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genbkgsumchargeptdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                genbkgSumChPt[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genbkgSumChPt[ibin][ir]->GetYaxis()->SetTitle("#Sigma p_{T}^{h^{#pm}}/p_{T}^{jet}");    
                genbkgSumChPt[ibin][ir]->Sumw2();
                genbkgChargeMult[ibin][ir] = new TH2F(Form("genbkgChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genbkgChMultdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -0.5, 99.5);
                genbkgChargeMult[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genbkgChargeMult[ibin][ir]->GetYaxis()->SetTitle("# of Charge");
                genbkgChargeMult[ibin][ir]->Sumw2();
                
                genbkgDiffJS[ibin][ir] = new TH2F(Form("genbkgdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genbkgdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                genbkgDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genbkgDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
                genbkgDiffJS[ibin][ir]->Sumw2();
                genbkgIntJS[ibin][ir] = new TH2F(Form("genbkgIntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genbkgIntegratedJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                genbkgIntJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                genbkgIntJS[ibin][ir]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
                genbkgIntJS[ibin][ir]->Sumw2();
                GenAxisDiffJS[ibin][ir] = new TH2F(Form("GenAxisdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("GenAxisdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                GenAxisDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                GenAxisDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
                GenAxisDiffJS[ibin][ir]->Sumw2();
                GenAxisbkgDiffJS[ibin][ir] = new TH2F(Form("GenAxisbkgdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("GenAxisbkgdifferentialJSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                GenAxisbkgDiffJS[ibin][ir]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                GenAxisbkgDiffJS[ibin][ir]->GetYaxis()->SetTitle("#rho (r)");
                GenAxisbkgDiffJS[ibin][ir]->Sumw2();
                                
            }

        } //for MC histograms
        }  //centrality bins loop
        
    //    for(int i = 0 ; i < 6 ; i++){
    //     ptbin[i] = new TH1F(Form("ptbin_%.f-%.f",pt[i], pt[i+1]), Form("ptbin_%.f-%.f",pt[i], pt[i+1]), 500, 0., 500.);
    //    }
    // if(!deltaR)
    deltaR = new TH1F((TString) (desc + "_deltaR"), "", 100, 0., 10.);
    CenBin = new TH1D((TString) (desc + "_Cent"), "", 100, 0, 100);
    CenBin->Sumw2();
    Vertex = new TH1F((TString) (desc + "_Vz"), "", 400, -20., 20.);
    Vertex->Sumw2();
    RareEvt = new TH1D((TString) (desc + "_RareEvt"), "", 100, 0, 100);
    
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
        delete jeteta[ibin];
        delete jetphi[ibin];
        delete trackpt[ibin];
        delete trackphi[ibin];
        delete tracketa[ibin];
        
        delete trackMax[ibin];
        delete trackSum[ibin];
        delete trackN[ibin];
        delete photonMax[ibin];
        delete photonSum[ibin];
        delete photonN[ibin];
        delete neutralMax[ibin];
        delete neutralSum[ibin];
        delete neutralN[ibin];
        delete ecalSum[ibin];
        delete hcalSum[ibin];
        
        delete leadingtrackjet[ibin];
        delete jetfrag[ibin];
        delete jetbkgfrag[ibin];
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
        if(IsMC&&DoGenAna){
            delete genjetpt[ibin];
            delete genjeteta[ibin];
            delete genjetphi[ibin];
            delete genptRatio[ibin];
            delete genphiRatio[ibin];
            delete genetaRatio[ibin];
            delete genpartpt[ibin];
            delete genpartphi[ibin];
            delete genparteta[ibin];
            delete bkgpartpt[ibin];
            delete bkgparteta[ibin];
            delete genSumPt[ibin];
            delete jetaxisRes[ibin];
            for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
                delete genpartdr[ibin][ipt];
                delete matchpartdr[ibin][ipt];
                delete genbkgpartdr[ibin][ipt];
                delete matchbkgpartdr[ibin][ipt];
                delete wtgenpartdr[ibin][ipt];
                delete wtmatchpartdr[ibin][ipt];
                delete wtgenbkgpartdr[ibin][ipt];
                delete wtmatchbkgpartdr[ibin][ipt];
                for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){
                    delete genjetdrSumTrkPt[ibin][ipt][itr];
                    delete bkggenjetdrSumTrkPt[ibin][ipt][itr];
                }
            }
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
        if(IsMC&&DoGenAna){
            for(int ir = 0 ; ir <nrbin; ir++){
                delete genChargePt[ibin][ir];
                delete genSumChPt[ibin][ir];
                delete genChargeMult[ibin][ir];
                delete genDiffJS[ibin][ir];
                delete genIntJS[ibin][ir];
                delete genbkgChargePt[ibin][ir];      
                delete genbkgSumChPt[ibin][ir];
                delete genbkgChargeMult[ibin][ir];
                delete genbkgDiffJS[ibin][ir];
                delete genbkgIntJS[ibin][ir];
                delete GenAxisDiffJS[ibin][ir];
                delete GenAxisbkgDiffJS[ibin][ir];
 
            }
        }
        
    } //centrality loop
    //   for(int i=0; i<6;i++) delete ptbin[i];
    delete deltaR;
    delete CenBin;
    delete RareEvt;
    delete Vertex;

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
    TString Norm ;
    if(DoSumPtNorm)Norm="NormSum";
    else Norm ="NormJet";
    if(doTrackCorrections){
     if(IsMC==kTRUE)   
          out_name=Form("%s%s_IncJetPerformPt%.f_%sCent4BinCorrTrk%.fEtaCut%.fLimit%.f_%sbkg%sCone%.f_CenBin%d_Nrbin%d_LJbin%d_trkbin%d_%s",dataType.Data(),model.Data(), leadingjetcut,corrMet.Data(), trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin,intputFile.Data());
       else 
         out_name=Form("%s_IncJetPerformPt%.f_%sCent4BinCorrTrk%.fEtaCut%.fLimit%.f_%sbkg%sCone%.f_CenBin%d_Nrbin%d_LJbin%dtrkbin%d_%s",dataType.Data(),leadingjetcut,corrMet.Data(), trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin, intputFile.Data());
      }
       else {
    if(IsMC==kTRUE)
            out_name=Form("%s%s_PFJetPerformPt%.f_Trk%.fEtaCut%.fLimit%.f_%sbkg%sCone%.f_CenBin%d_Nrbin%d_LJbin%dtrkbin%d_%s",dataType.Data(),model.Data(),leadingjetcut,trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin,intputFile.Data());
    else        
            out_name=Form("%s_IncJetPerformPt%.f_Trk%.fEtaCut%.fLimit%.f_%sbkg%sCone%.f_CenBin%d_Nrbin%d_LJbin%dtrkbin%d_%s",dataType.Data(),leadingjetcut,trackcut,etacut*10, etalimit*10,met.Data(), Norm.Data(),conesize*10, nbin,nrbin,nptbin,ntrkptbin, intputFile.Data());       
    }
     
    TFile *out_file = new TFile(Form("/net/hidsk0001/d00/scratch/maoyx/pPb/CMSSW_5_3_8_HI_patch2/src/checkJEC/%s",out_name.Data()), "RECREATE");
    //   TFile *out_file = new TFile(Form("/afs/cern.ch/work/y/ymao/pA/CMSSW_5_3_8_HI_patch2/src/Run210498/%s",out_name.Data()), "RECREATE");
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin]->Write();
        NJets[ibin]->Write();
        Ntrack[ibin]->Write();
        jetpt[ibin]->Write();
        jeteta[ibin]->Write();
        jetphi[ibin]->Write();
         trackpt[ibin]->Write();
        trackphi[ibin]->Write();
        tracketa[ibin]->Write();
        
        trackMax[ibin]->Write();
        trackSum[ibin]->Write();
        trackN[ibin]->Write();
        photonMax[ibin]->Write();
        photonSum[ibin]->Write();
        photonN[ibin]->Write();
        neutralMax[ibin]->Write();
        neutralSum[ibin]->Write();
        neutralN[ibin]->Write();
        ecalSum[ibin]->Write();
        hcalSum[ibin]->Write();
        
        leadingtrackjet[ibin]->Write();
        jetfrag[ibin]->Write();
        jetbkgfrag[ibin]->Write();
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
        if(IsMC&&DoGenAna){
            genjetpt[ibin]->Write();
            genjeteta[ibin]->Write();
            genjetphi[ibin]->Write();
             genptRatio[ibin]->Write();
            genphiRatio[ibin]->Write();
            genetaRatio[ibin]->Write();
            genpartpt[ibin]->Write();
            genpartphi[ibin]->Write();
            genparteta[ibin]->Write();
            bkgpartpt[ibin]->Write();
            bkgparteta[ibin]->Write();
            genSumPt[ibin]->Write();
            jetaxisRes[ibin]->Write();
            for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
                genpartdr[ibin][ipt]->Write();
                matchpartdr[ibin][ipt]->Write();
                genbkgpartdr[ibin][ipt]->Write();
                matchbkgpartdr[ibin][ipt]->Write();
                wtgenpartdr[ibin][ipt]->Write();
                wtmatchpartdr[ibin][ipt]->Write();
                wtgenbkgpartdr[ibin][ipt]->Write();
                wtmatchbkgpartdr[ibin][ipt]->Write();
                for(Int_t itr = 0 ; itr <ntrkptbin ; itr++){
                    genjetdrSumTrkPt[ibin][ipt][itr]->Write();
                    bkggenjetdrSumTrkPt[ibin][ipt][itr]->Write();
                }
            }    
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
            if(IsMC&&DoGenAna){
                for(int ir = 0 ; ir <nrbin; ir++){
                genChargePt[ibin][ir]->Write();    
                genSumChPt[ibin][ir]->Write(); 
                genChargeMult[ibin][ir]->Write();    
                genDiffJS[ibin][ir]->Write();
                genIntJS[ibin][ir]->Write();
                genbkgChargePt[ibin][ir]->Write();    
                genbkgSumChPt[ibin][ir]->Write(); 
                genbkgChargeMult[ibin][ir]->Write();   
                genbkgDiffJS[ibin][ir]->Write();
                genbkgIntJS[ibin][ir]->Write();
                GenAxisDiffJS[ibin][ir]->Write();
                GenAxisbkgDiffJS[ibin][ir]->Write();

                }
            } //only write if it MC
        } //centrality bins
    
    //  for(int i=0; i<6;i++) ptbin[i]->Write();
    deltaR->Write();
    CenBin->Write();
    RareEvt->Write();
    Vertex->Write();

    out_file->Close();
    cout <<"Output file: " <<Form("%s",out_name.Data()) <<endl ;
    
}


void anaJetTrackQuality()
{
//    //for centrality reweight parameterization
//    TF1 *fcen = new TF1("fcen","[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)",0,40);
//   // fcen->SetParameters(2.10653e-02,5.61607,-1.41493e-01,1.00586e-03,-1.32625e-04); //from Pawn/Pelin
//    fcen->SetParameters(1.98261e-02,5.55963e+00,-1.34951e-01,1.70895e-03,-9.28386e-05); //fit by myself
//   
//    //for vertex reweight parameterization
//    TF1 * fVz = new TF1("fVx","[0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3)+[4]*TMath::Power(x,4)", -15., 15.);
//    if(coll=="HI")
//      //  fVz->SetParameters(0.803816, -0.0179222, 0.00716733, -0.000165785, 7.30741e-05); //PbPb vertex reweighting
//        fVz->SetParameters(7.62788e-01,-1.13228e-02,5.85199e-03,-3.04550e-04,4.43440e-05); 
//    else 
//     //    fVz->SetParameters(0.86946, -0.0353677, 0.00497902, -0.00016535, 4.53564e-05); //p vertex reweighting
//      fVz->SetParameters(8.41684e-01,-2.58609e-02,4.86550e-03,-3.10581e-04,2.07918e-05); 
        
    hist_class *my_hists = new hist_class("pfjet");
    cout <<my_hists->IsMC<<endl ;

    std::cout << "start working\n";
    if(my_hists->IsMC!=kTRUE)
     //   dataPath="/net/hisrv0001/home/yenjie/scratch/production/CMSSW_5_3_3_patch3/test";//mit path
      //  dataPath="root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged_HiForest" ;//pPb data path lxplus
        dataPath="root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged" ;//pPb data path lxplus
    else {
        if(model=="HIJING")
         //   dataPath="/mnt/hadoop/cms/store/user/tuos/pPb/HiForest/5_3_3_patch3";
            dataPath=Form("root://eoscms//eos/cms/store/caf/user/dgulhan/pPb_A04/Hijing_Pythia_pt%d/HiForest_v01_mergedv01",pthat);
          //  dataPath="root://eoscms//eos/cms/store/caf/user/dgulhan/pPb_A03/Hijing_Pythia_pt15/HiForest2_v02_mergedv02";
       else if(model=="PYTHIA")
           dataPath=Form("/mnt/hadoop/cms/store/user/dgulhan/pPb_A03/Signal_Pythia%d/HiForest2_v02_mergedv01",pthat);
        else 
      //      dataPath="/mnt/hadoop/cms/store/user/frankmalocal/forest";
            dataPath="/afs/cern.ch/user/t/tuos/work/public/pPb/AMPT/evening";
    }

    if(my_hists->IsMC!=kTRUE){  //real data analysis
          intputFile="pPb_hiForest2_1_15_test.root" ; //test run dataset
     //       intputFile="PA2013_HiForest_Express_r210498_stablebeams.root" ; //real data dataset
     //       intputFile="PA2013_HiForest_Express_r210534_stablebeams_72bunch.root" ; //real data dataset
    }
    else { //MC sample
        if(model=="HIJING")
//            intputFile="pPbHijing_5_3_3_v0_HiForest2_v07_WithCentrality.root" ;
         //   intputFile="pPbHijing_5_3_3_v0_HiForest2_v07.root" ;
            intputFile="merged_forest_3.root" ;
       else if(model=="PYTHIA")
            intputFile="merged_forest_0.root";
        else 
            intputFile="HiForest_AMPT_Evening_5_3_3_v1.root";
//            intputFile="HiForest_AMPT_Evening_5_3_3_v1_WithCentrality.root";
    }
    
    TString inname=Form("%s/%s", dataPath.Data(),intputFile.Data());
    // Define the input file and HiForest

    HiForest * c = new HiForest(inname,"forest",cPPb);
   // HiForest *c = new HiForest(inname);
    if(doTrackCorrections) c->doTrackCorrections = 1;
    else c->doTrackCorrections = 0;
    c->doTrackingSeparateLeadingSubleading = false;
    c->InitTree();
  //  cout << "start working222222\n";
  //  TFile *my_file=TFile::Open(Form("%s/%s", dataPath.Data(),intputFile.Data()));
    cout <<"Input file" << inname<<endl ;
    
    // evt tree
    Evts * offSel = &(c->evt); 

    //skim tree
    Skims * my_skim = &(c->skim); 

    //hlt tree
    Hlts * trigSel = &(c->hlt); 
    //jet tree
    
        Jets * my_ct = &(c->ak3PF); 

    Tracks * my_tr = &(c->track);
    
    //GenParticle tree
    GenParticles * my_GenPart = &(c->genparticle);

    int curr_bin = nbin-1 ;
    cout <<"Number of events ="<<c->GetEntries()<<endl ;
    for(int evi = 0; evi < c->GetEntries(); evi++) {
        //          for(int evi = 0; evi < 10; evi++) {
        c->GetEntry(evi);
       //  if(evi%2==1) continue ; 
       //cout <<"evt = "<<evi <<endl ; 
        //        int ecal_noise = my_skim->phiEcalRecHitSpikeFilter ;
        //        if(ecal_noise==0) continue ;
        
        double vz = offSel->vz ;
        int hiBin = offSel->hiBin ;
        weight = 1. ;       
        //   cout <<"vz =" <<vz <<endl ;
//        if(my_hists->IsMC==kTRUE) weight*=fVz->Eval(vz);
//        else weight=1. ;
        
 //  if(coll=="HI") {
       if(my_hists->IsMC!=kTRUE){
        if(TMath::Abs(vz)>15.) continue ;
          //  bool evt_sel = my_skim->phfPosFilter1 && my_skim->phfNegFilter1 && my_skim->phltPixelClusterShapeFilter && my_skim->pprimaryvertexFilter;
            bool evt_sel = my_skim->pPAcollisionEventSelectionPA;
            if(evt_sel==0) continue ;
            int noise_evt = my_skim->pHBHENoiseFilter ;
            if(noise_evt==0) continue ;
	      int jetTr2 = trigSel->HLT_PAZeroBiasPixel_SingleTrack_v1 ;
          //  if(jetTr2==0) continue ;
           int run = offSel->run ;
         //  if(run!=202792) continue ;
         //  if(run!=210498) continue ;
           int lumi = offSel->lumi ;
         //  if(lumi>1014 || lumi < 317) continue ;
         //  if(lumi < 120) continue ;
	}

       //  cout <<"njets =" <<my_ct->nref <<endl ; 
        //if there is no jets or no PF candidates, skip the event
        if(my_ct->nref==0) continue ;
                
            double centrality = hiBin ;
             //  my_hists->CenBin->Fill(offSel->hiBin);
            
            for(int ibin = 0 ; ibin <nbin; ibin++){
                if(centrality >=centr[ibin] && centrality<centr[ibin+1]) curr_bin = ibin ;
            }
        //    cout << "  cent_bin:" <<curr_bin <<endl ;
        
        if(evi%10000==1)cout <<" evt = " <<evi <<endl ;
        
        my_hists->Ntrack[curr_bin]->Fill(1, weight);
        //cout <<my_hists->NEvents[curr_bin]->GetName() <<endl;
        //cout << "start working222222\n";
        
        
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
        
        //   if(DoGenAna){
        //for MC gen jet info
        double genjet_pt = -999. ;
        double genjet_phi = -999.;
        double genjet_eta = -999. ;
        double genbkg_phi = -999. ;
        double genbkg_eta = -999. ;
    
        int gencharge[nrbin] ;
        double gensumchpt[nrbin];
        double genrho[nrbin] ;
        double genpsi[nrbin] ;
        double gensumpt = 0. ;
        int genbkgcharge[nrbin] ;
        double genbkgsumchpt[nrbin]  ;
        double genbkgrho[nrbin];
        double genbkgpsi[nrbin] ;
        double genbkgsumpt = 0. ;
        double gensumTrkpt[nrbin][ntrkptbin];
        double genbkgsumTrkpt[nrbin][ntrkptbin];
        
        //    }
        
        double flavor = 0 ;
       //make an munual cut for icPu5 calo jet cut (similar as jet skim threshold)
   //    for(int i = 0 ; i < jetthres->nref ; i++) {
   //      if(jetthres->jtpt[i]<100.) continue ;
   //     }

        for(int j4i = 0; j4i < my_ct->nref ; j4i++) {
            
            jet_pt= my_ct->jtpt[j4i];
            if(TMath::Abs(my_ct->jteta[j4i])>etacut) continue ;
          //  if(TMath::Abs(my_ct->jteta[j4i])<etalimit) continue ;            
            if(jet_pt<leadingjetcut) continue ;
        //    if(my_hists->IsMC!=kTRUE)if(my_ct->trackMax[j4i]/jet_pt <=0.01) continue ;            
            my_hists->jetpt[curr_bin]->Fill(jet_pt, weight);
            my_hists->jeteta[curr_bin]->Fill(jet_pt, jet_eta, weight);
            my_hists->jetphi[curr_bin]->Fill(jet_pt, jet_phi, weight);
            
            my_hists->trackMax[curr_bin]->Fill(jet_pt,my_ct->trackMax[j4i]/jet_pt, weight);
            my_hists->trackSum[curr_bin]->Fill(jet_pt,my_ct->trackSum[j4i]/jet_pt, weight);
            my_hists->trackN[curr_bin]->Fill(jet_pt,my_ct->trackN[j4i], weight);
            my_hists->photonMax[curr_bin]->Fill(jet_pt,my_ct->photonMax[j4i]/jet_pt, weight);
            my_hists->photonSum[curr_bin]->Fill(jet_pt,my_ct->photonSum[j4i]/jet_pt, weight);
            my_hists->photonN[curr_bin]->Fill(jet_pt,my_ct->photonN[j4i], weight);
            my_hists->neutralMax[curr_bin]->Fill(jet_pt,my_ct->neutralMax[j4i]/jet_pt, weight);
            my_hists->neutralSum[curr_bin]->Fill(jet_pt,my_ct->neutralSum[j4i]/jet_pt, weight);
            my_hists->neutralN[curr_bin]->Fill(jet_pt,my_ct->neutralN[j4i], weight);
            my_hists->ecalSum[curr_bin]->Fill(jet_pt,my_ct->ecalSum[j4i]/jet_pt, weight);
            my_hists->hcalSum[curr_bin]->Fill(jet_pt,my_ct->hcalSum[j4i]/jet_pt, weight);
            
            
            jet_phi =my_ct->jtphi[j4i];
            if(jet_phi<=-TMath::Pi())jet_phi+=TMath::TwoPi();
            jet_eta = my_ct->jteta[j4i];
            if(my_hists->IsMC==kTRUE) flavor = TMath::Abs(my_ct->refparton_flavor[j4i]);
             //seperate quark and gluon jet analysis
          //  if(my_hists->IsMC==kTRUE) {
          //   if(flavor<1 || flavor >6) continue ; //only quark jets selected
          //  if(flavor!=21) continue ;  //only gluon jets selected
           //  }
            njets++ ;        
            bkg_phi = jet_phi;
            bkg_eta = -jet_eta;
            if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetBkgCone[curr_bin]->Fill(bkg_phi-jet_phi, bkg_eta-jet_eta, weight);
            for(Int_t ieta = 0 ; ieta <netabin; ieta++){
                //   if(TMath::Abs(bkg_eta-jet_eta)>deta[ieta]&&TMath::Abs(bkg_eta-jet_eta)<=deta[ieta+1]) dEtaBin = ieta ; 
                if(TMath::Abs(jet_eta)>deta[ieta]&&TMath::Abs(jet_eta)<=deta[ieta+1]) dEtaBin = ieta ; 
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
             //   cout <<"gen jet =" <<genjet_pt <<endl ;
               genbkg_phi = genjet_phi;
               genbkg_eta = -genjet_eta;
            }            
                if(my_hists->IsMC==kTRUE&&DoGenAna){
                if(genjet_pt<0.) continue ; 
                my_hists->genjetpt[curr_bin]->Fill(jet_pt,genjet_pt, weight);
                my_hists->genjeteta[curr_bin]->Fill(jet_eta, genjet_eta, weight);
                my_hists->genjetphi[curr_bin]->Fill(jet_phi, genjet_phi, weight);
                my_hists->genptRatio[curr_bin]->Fill(genjet_pt,jet_pt/genjet_pt, weight);
                my_hists->genphiRatio[curr_bin]->Fill(jet_pt,genjet_phi-jet_phi, weight);
                my_hists->genetaRatio[curr_bin]->Fill(jet_pt,genjet_eta-jet_eta, weight);
                }
            //    if(jet_pt<leadingjetcut) continue ;   
               //cout <<"jet pt =" <<jet_pt <<endl ; 

            for(Int_t ipt = 0 ; ipt <nptbin; ipt++){
                    if(jet_pt>=pt[ipt] && jet_pt <pt[ipt+1]) ptBin = ipt ;
                }
                my_hists->NEvents[curr_bin]->Fill(1, weight);
                if(TMath::Abs(my_ct->jteta[j4i])>etalimit) { //continue ;
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
                    Int_t leadingIndex = -1 ;
                    Double_t leadingTrack = 0. ;
                    
                    for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
                        double dr = 0.;
                        double bkg_dr =0.;
                        double tr_pt = my_tr->trkPt[itr];
                        double tr_phi = my_tr->trkPhi[itr];
                        double tr_eta = my_tr->trkEta[itr];
                        if(TMath::Abs(tr_eta)>tracketacut) continue ;
                        
                        //  if(my_tr->trkNHit[itr]<8 ||(my_tr->highPurity[itr]&&my_tr->trkAlgo[itr]==4.0)){
                        if(my_tr->trkAlgo[itr]<4 ||(my_tr->highPurity[itr])){
                            //            if(my_tr->highPurity[itr]==0) continue ;
                            //            if(my_tr->trkAlgo[itr]!=4.0) continue ;
                            // if(TMath::Abs(tr_eta)>tracketacut) continue ;
                            if(tr_pt<trackcut) continue ;
                            
                            trkweight=1. ;
                            if(tr_pt>leadingTrack) leadingTrack = tr_pt ;
                            
                            if(doTrackCorrections){
                                if(corrMet=="Hist")trkweight = c->getTrackCorrection(itr);  
                                else trkweight = c->getTrackCorrectionPara(itr); 
                                //  if(TMath::Abs(trkweight-1.)<0.001)trkweight = c->getTrackCorrection(itr);  
                            }
                            
                            dr =TMath::Sqrt((tr_phi-jet_phi)*(tr_phi-jet_phi)+(tr_eta-jet_eta)*(tr_eta-jet_eta));
                            bkg_dr = TMath::Sqrt((tr_phi-bkg_phi)*(tr_phi-bkg_phi)+(tr_eta-bkg_eta)*(tr_eta-bkg_eta));
                            
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->deltaR->Fill(dr, weight); 
                            double jtrdphi = tr_phi-jet_phi ;
                                        if(jtrdphi>3*TMath::Pi()/2.)jtrdphi-=TMath::TwoPi();
                                        if(jtrdphi<=-TMath::Pi()/2.) jtrdphi+=TMath::TwoPi();            
                            if(TMath::Abs(jet_eta)>=etalimit)my_hists->IncTrackDphi[curr_bin]->Fill(jet_pt,jtrdphi, weight);
                            if(dr<=conesize){  //for leading jet shape study                        
                                trackcount++;
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetTrackDphi[curr_bin]->Fill(jet_pt,jtrdphi, weight*trkweight);                
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetTrackDeta[curr_bin]->Fill(jet_pt,tr_eta-jet_eta, weight*trkweight);                
                                
                                //  if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetfrag[curr_bin]->Fill(jet_pt, TMath::Log(jet_pt/tr_pt), weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetfrag[curr_bin]->Fill(jet_pt, TMath::Log((jet_pt*TMath::CosH(jet_eta))/(tr_pt*TMath::CosH(tr_eta)*TMath::Cos(dr))), weight*trkweight);
                                if(TMath::Abs(jet_eta)>=etalimit)my_hists->trackpt[curr_bin]->Fill(jet_pt, tr_pt, weight*trkweight);
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
                                        //     cout<<" !!!! track index =" <<itr << " trk pt =" <<tr_pt << " tr phi =" <<tr_phi << " tr eta =" <<tr_eta  <<" dr =" <<dr <<" rho =" <<rho[ir]<<endl ;
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
                                if(bkg_dr<=conesize){
                                    if(TMath::Abs(jet_eta)>=etalimit)my_hists->bkgtrackpt[curr_bin]->Fill(jet_pt, tr_pt, weight);
                                    if(TMath::Abs(jet_eta)>=etalimit)my_hists->bkgtrackdr[curr_bin][ptBin]->Fill(tr_pt,bkg_dr, weight*trkweight);
                                    if(TMath::Abs(jet_eta)>=etalimit)my_hists->bkgwttrackdr[curr_bin][ptBin]->Fill(tr_pt,bkg_dr, tr_pt*weight*trkweight);
                                    bkgsumpt+=tr_pt*trkweight ;
                                    for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                                        //  if(tr_pt*trkweight>trkpt[ipt] && tr_pt*trkweight<=trkpt[ipt+1])bkgjetsumTrk[ipt]+=tr_pt*trkweight ;
                                        if(tr_pt*trkweight<=trkpt[ipt+1])bkgjetsumTrk[ipt]+=tr_pt*trkweight ;
                                    }
                                    if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetBkgTrackDphi[curr_bin]->Fill(jet_pt,jtrdphi, weight*trkweight);
                                    if(TMath::Abs(jet_eta)>=etalimit)my_hists->JetBkgTrackDeta[curr_bin]->Fill(jet_pt,tr_eta-jet_eta, weight*trkweight);
                                    //   if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetbkgfrag[curr_bin]->Fill(jet_pt, TMath::Log(jet_pt/tr_pt), weight*trkweight);
                                    if(TMath::Abs(jet_eta)>=etalimit)my_hists->jetbkgfrag[curr_bin]->Fill(jet_pt, TMath::Log((jet_pt*TMath::CosH(jet_eta))/(tr_pt*TMath::CosH(tr_eta)*TMath::Cos(bkg_dr))), weight*trkweight);
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
                            if(my_hists->IsMC==kTRUE&&DoGenAna){
                                double GenAxisdr =TMath::Sqrt((tr_phi-genjet_phi)*(tr_phi-genjet_phi)+(tr_eta-genjet_eta)*(tr_eta-genjet_eta));
                                double GenAxisbkgdr =TMath::Sqrt((tr_phi-genbkg_phi)*(tr_phi-genbkg_phi)+(tr_eta-genbkg_eta)*(tr_eta-genbkg_eta));
                                
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
                    
                    my_hists->leadingtrackjet[curr_bin]->Fill(jet_pt,leadingTrack/jet_pt, weight);                    
                    my_hists->SumptJetPt[curr_bin]->Fill(jet_pt,sumpt/jet_pt, weight);
                    if(DoSumPtNorm){
                        if(sumpt==0.) continue ;
                    }
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
                        if(my_hists->IsMC==kTRUE&&DoGenAna){ 
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
                    } //radius bin loop            
                    my_hists->NJets[curr_bin]->Fill(1, weight);   
                    if(bkgsumpt>sumpt)my_hists->RareEvt->Fill(offSel->hiBin, weight);
                }  //remove overlape eta regions from jet cone and ER bkg cone
            if(my_hists->IsMC==kTRUE&&DoGenAna){
                if(TMath::Abs(genjet_eta)>=etalimit){
                    for(int ir = 0 ; ir <nrbin ; ir++){
                        gencharge[ir]=0;
                        gensumchpt[ir]=0. ;
                        genrho[ir]=0. ;
                        genpsi[ir]= 0.;
                        genbkgcharge[ir]=0 ;
                        genbkgsumchpt[ir]=0. ;
                        genbkgrho[ir]=0.;
                        genbkgpsi[ir]=0. ;
                        
                        for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                            gensumTrkpt[ir][ipt]=0.;
                            genbkgsumTrkpt[ir][ipt]=0.;
                        }
                        
                    }
                    //using the sim track to calculate the tracking efficiency 
                    for(int ipart = 0 ; ipart < my_tr->nParticle ; ipart++){ //sim track loop 
                        double gen_pt = my_tr->pPt[ipart];
                        double gen_phi = my_tr->pPhi[ipart];
                        double gen_eta = my_tr->pEta[ipart];  
                        if(gen_pt<trackcut)continue ;
                        if(TMath::Abs(gen_eta)>2.4)continue ;
                        //   cout <<"gen pt =" <<gen_pt <<endl ;
                        double gendr =TMath::Sqrt((gen_phi-jet_phi)*(gen_phi-jet_phi)+(gen_eta-jet_eta)*(gen_eta-jet_eta));
                        double genbkg_dr = TMath::Sqrt((gen_phi-bkg_phi)*(gen_phi-bkg_phi)+(gen_eta-bkg_eta)*(gen_eta-bkg_eta));
                        //   double gendr =TMath::Sqrt((gen_phi-genjet_phi)*(gen_phi-genjet_phi)+(gen_eta-genjet_eta)*(gen_eta-genjet_eta));
                        //    double genbkg_dr = TMath::Sqrt((gen_phi-genbkg_phi)*(gen_phi-genbkg_phi)+(gen_eta-genbkg_eta)*(gen_eta-genbkg_eta));
                        if(gendr<=conesize)my_hists->genpartdr[curr_bin][ptBin]->Fill(gen_pt, gendr, weight);
                        if(genbkg_dr<=conesize)my_hists->genbkgpartdr[curr_bin][ptBin]->Fill(gen_pt, genbkg_dr, weight);
                        if(gendr<=conesize)my_hists->wtgenpartdr[curr_bin][ptBin]->Fill(gen_pt, gendr,gen_pt*weight);
                        if(genbkg_dr<=conesize)my_hists->wtgenbkgpartdr[curr_bin][ptBin]->Fill(gen_pt, genbkg_dr, gen_pt*weight);
                        if(my_tr->pNRec[ipart]>0&&(my_tr->mtrkAlgo[ipart]<4||(my_tr->mtrkQual[ipart]))){
                            //   if(my_tr->pNRec[ipart]>0){  //no quality cuts                  
                            if(gendr<=conesize){
                                my_hists->matchpartdr[curr_bin][ptBin]->Fill(gen_pt, gendr,weight);
                                my_hists->wtmatchpartdr[curr_bin][ptBin]->Fill(gen_pt, gendr, gen_pt*weight);
                                gensumpt+=gen_pt ;
                                if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genpartpt[curr_bin]->Fill(jet_pt,gen_pt, weight);
                                //      my_hists->genpartpt[curr_bin]->Fill(jet_pt,gen_pt, weight);
                                if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genpartphi[curr_bin]->Fill(jet_pt,gen_phi, weight);
                                if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genparteta[curr_bin]->Fill(jet_pt,gen_eta, weight);
                                for(int ir = 0 ; ir <nrbin ; ir++){
                                    if(gendr>rbin[ir]&&gendr<=rbin[ir+1]){
                                        genrho[ir]+=gen_pt ;
                                        if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genChargePt[curr_bin][ir]->Fill(jet_pt, gen_pt, weight);
                                        gensumchpt[ir]+=gen_pt ;
                                        gencharge[ir]++ ;
                                        for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                                            if(gen_pt<=trkpt[ipt+1])gensumTrkpt[ir][ipt]+=gen_pt ;
                                        }
                                        
                                    }
                                    if(gendr<=rbin[ir+1]) {
                                        genpsi[ir]+=gen_pt ; 
                                    }
                                }  //radius loop
                                
                            } //inside jet cone
                            if(genbkg_dr<=conesize){
                                my_hists->matchbkgpartdr[curr_bin][ptBin]->Fill(gen_pt, genbkg_dr, weight); 
                                my_hists->wtmatchbkgpartdr[curr_bin][ptBin]->Fill(gen_pt, genbkg_dr, gen_pt*weight); 
                                genbkgsumpt+=gen_pt ;
                                if(TMath::Abs(genjet_eta)>=etalimit)my_hists->bkgpartpt[curr_bin]->Fill(jet_pt,gen_pt, weight);
                                if(TMath::Abs(genjet_eta)>=etalimit)my_hists->bkgparteta[curr_bin]->Fill(gen_pt,gen_eta, weight);
                                for(int ir = 0 ; ir <nrbin ; ir++){
                                    if(genbkg_dr>rbin[ir]&&genbkg_dr<=rbin[ir+1]){
                                        genbkgrho[ir]+=gen_pt ;
                                        if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genbkgChargePt[curr_bin][ir]->Fill(jet_pt, gen_pt,weight);
                                        genbkgsumchpt[ir]+=gen_pt ;
                                        genbkgcharge[ir]++ ;   
                                        for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                                            if(gen_pt<=trkpt[ipt+1])genbkgsumTrkpt[ir][ipt]+=gen_pt ;
                                        }
                                    }
                                    if(genbkg_dr<=rbin[ir+1]) {
                                        genbkgpsi[ir]+=gen_pt ;
                                    }
                                }  //radius loop for JS calculation  
                            } //inside bkg cone
                            
                        } //gen matched track selection
                    }  //sim track loop
                    if(DoSumPtNorm){
                        if(gensumpt==0.) continue ;
                    }
                    my_hists->genSumPt[curr_bin]->Fill(genjet_pt,gensumpt, weight);
                    
                    for(int ir = 0 ; ir <nrbin; ir++){  
                        if(DoSumPtNorm){
                            genpsi[ir]/=gensumpt;
                            genrho[ir]/=gensumpt;
                            genbkgpsi[ir]/=gensumpt;
                            genbkgrho[ir]/=gensumpt;
                            gensumchpt[ir]/=gensumpt ;
                            genbkgsumchpt[ir]/=gensumpt ;
                        }
                        else {

                             genpsi[ir]/=jet_pt;
                             genrho[ir]/=jet_pt;
                             genbkgpsi[ir]/=jet_pt;
                             genbkgrho[ir]/=jet_pt;
                             gensumchpt[ir]/=jet_pt ;
                             genbkgsumchpt[ir]/=jet_pt ;
                             /*
                            genpsi[ir]/=genjet_pt;
                            genrho[ir]/=genjet_pt;
                            genbkgpsi[ir]/=genjet_pt;
                            genbkgrho[ir]/=genjet_pt;
                            gensumchpt[ir]/=genjet_pt ;
                            genbkgsumchpt[ir]/=genjet_pt ;            
                       */ }
                        for(int ipt = 0 ; ipt <ntrkptbin; ipt++){
                            my_hists->genjetdrSumTrkPt[curr_bin][ptBin][ipt]->Fill((rbin[ir]+0.025), gensumTrkpt[ir][ipt]*weight);
                            my_hists->bkggenjetdrSumTrkPt[curr_bin][ptBin][ipt]->Fill((rbin[ir]+0.025), genbkgsumTrkpt[ir][ipt]*weight);
                        }
                        my_hists->genChargeMult[curr_bin][ir]->Fill(jet_pt, gencharge[ir], weight);
                        my_hists->genSumChPt[curr_bin][ir]->Fill(jet_pt, gensumchpt[ir], weight); 
                        my_hists->genbkgChargeMult[curr_bin][ir]->Fill(jet_pt, genbkgcharge[ir], weight);
                        my_hists->genbkgSumChPt[curr_bin][ir]->Fill(jet_pt, genbkgsumchpt[ir], weight); 
                        
                        my_hists->genDiffJS[curr_bin][ir]->Fill(jet_pt, genrho[ir], weight);
                        //       my_hists->genDiffJS[curr_bin][ir]->Fill(jet_pt, genrho[ir],weight);
                        my_hists->genIntJS[curr_bin][ir]->Fill(jet_pt, genpsi[ir],weight);
                        // rho/=deltacone ;
                        my_hists->genbkgDiffJS[curr_bin][ir]->Fill(jet_pt, genbkgrho[ir],weight);
                        //      my_hists->genbkgDiffJS[curr_bin][ir]->Fill(jet_pt, genbkgrho[ir],weight);
                        //   my_hists->IntJS[curr_bin]->Fill(jet_pt, 1-psi);
                        my_hists->genbkgIntJS[curr_bin][ir]->Fill(jet_pt, genbkgpsi[ir],weight);
                    }  //radius loop in order to fill jet shape histograms   
                } //eta limit cut for ER bkg
                
            }//MC sim track loop for efficiency study   
        
        //   if(sumpt==0) cout<<"evt ="<<evi <<"jet pt =" <<jet_pt<<" without tracks" <<endl ;
        
//            if(my_hists->IsMC==kTRUE&&DoGenAna){ 
//                
//                genbkg_phi = genjet_phi;
//                genbkg_eta = -genjet_eta;
//                for(int ir = 0 ; ir <nrbin ; ir++){
//                    gencharge[ir]=0;
//                    gensumchpt[ir]=0. ;
//                    genrho[ir]=0. ;
//                    genpsi[ir]= 0.;
//                    genbkgcharge[ir]=0 ;
//                    genbkgsumchpt[ir]=0. ;
//                    genbkgrho[ir]=0.;
//                    genbkgpsi[ir]=0. ;
//                }
//                // for(int ipart = 0 ; ipart < my_tr->nParticle ; ipart++){ //sim track loop
//                for(int ipart = 0 ; ipart < my_GenPart->mult ; ipart++){//gen particle loop
//                    double gen_pt = my_GenPart->pt[ipart];
//                    double gen_phi = my_GenPart->phi[ipart];
//                    double gen_eta = my_GenPart->eta[ipart];
//                    int chg = my_GenPart->chg[ipart];
//                    if(chg==0) continue ;
//                    if(TMath::Abs(gen_eta)>2.4) continue ;
//                    //cout <<"charge =" <<chg <<endl ;
//                   //  int sube = my_GenPart->sube[ipart];
//                    // if(sube>0) continue ; //only PYTHIA signale particles
//                    // if(sube>0)cout <<"sube =" <<sube <<endl ;
//                    //                double gen_pt = my_tr->pPt[ipart];
//                    //                double gen_phi = my_tr->pPhi[ipart];
//                    //                double gen_eta = my_tr->pEta[ipart];  
//                    if(gen_pt<trackcut)continue ;
//                    double gendr =TMath::Sqrt((gen_phi-genjet_phi)*(gen_phi-genjet_phi)+(gen_eta-genjet_eta)*(gen_eta-genjet_eta));
//                    //     double gendr =TMath::Sqrt((gen_phi-jet_phi)*(gen_phi-jet_phi)+(gen_eta-jet_eta)*(gen_eta-jet_eta));
//                    //                double gendr =TMath::Sqrt((gen_phi-jet_phi)*(gen_phi-jet_phi)+(gen_eta-jet_eta)*(gen_eta-jet_eta));
//                    //                double gendr2 =TMath::Sqrt((gen_phi-subjet_phi)*(gen_phi-subjet_phi)+(gen_eta-subjet_eta)*(gen_eta-subjet_eta));
//                    if(gendr <=conesize){
//                        gensumpt+=gen_pt ;
//                        if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genpartpt[curr_bin]->Fill(jet_pt,gen_pt, weight);
//                        //      my_hists->genpartpt[curr_bin]->Fill(jet_pt,gen_pt, weight);
//                        if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genpartphi[curr_bin]->Fill(jet_pt,gen_phi, weight);
//                        if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genparteta[curr_bin]->Fill(jet_pt,gen_eta, weight);
//                        for(int ir = 0 ; ir <nrbin ; ir++){
//                            if(gendr>rbin[ir]&&gendr<=rbin[ir+1]){
//                                genrho[ir]+=gen_pt ;
//                                if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genChargePt[curr_bin][ir]->Fill(jet_pt, gen_pt, weight);
//                                gensumchpt[ir]+=gen_pt ;
//                                gencharge[ir]++ ;
//                                
//                            }
//                            if(gendr<=rbin[ir+1]) {
//                                genpsi[ir]+=gen_pt ; 
//                            }
//                        }  //radius loop
//                        
//                    } //tracks inside for jet
//                    else {
//                        double genbkg_dr = TMath::Sqrt((gen_phi-genbkg_phi)*(gen_phi-genbkg_phi)+(gen_eta-genbkg_eta)*(gen_eta-genbkg_eta));  
//                        //                        double genbkg_dr = TMath::Sqrt((gen_phi-bkg_phi)*(gen_phi-bkg_phi)+(gen_eta-bkg_eta)*(gen_eta-bkg_eta));  
//                        if(genbkg_dr<=conesize){
//                            genbkgsumpt+=gen_pt ;
//                            if(TMath::Abs(genjet_eta)>=etalimit)my_hists->bkgpartpt[curr_bin]->Fill(jet_pt,gen_pt, weight);
//                            if(TMath::Abs(genjet_eta)>=etalimit)my_hists->bkgparteta[curr_bin]->Fill(gen_pt,gen_eta, weight);
//                            for(int ir = 0 ; ir <nrbin ; ir++){
//                                if(genbkg_dr>rbin[ir]&&genbkg_dr<=rbin[ir+1]){
//                                    genbkgrho[ir]+=gen_pt ;
//                                    if(TMath::Abs(genjet_eta)>=etalimit)my_hists->genbkgChargePt[curr_bin][ir]->Fill(jet_pt, gen_pt, weight);
//                                    genbkgsumchpt[ir]+=gen_pt ;
//                                    genbkgcharge[ir]++ ;   
//                                }
//                                if(genbkg_dr<=rbin[ir+1]) {
//                                    genbkgpsi[ir]+=gen_pt ;
//                                }
//                            }  //radius loop for JS calculation
//                            
//                        }  // inside bkg cone   
//                    } //outside leading jet
//                    //     }
//                } //gen particle loop 
//                if(TMath::Abs(genjet_eta)>=etalimit){
//                    if(DoSumPtNorm && gensumpt==0.) continue ;
//                    //    if(gensumpt==0.|| genbkgsumpt>gensumpt) continue ;
//                    //      
//                    my_hists->genSumPt[curr_bin]->Fill(genjet_pt,gensumpt, weight);
//                    
//                    //    if(genbkgsumpt>=gensumpt || genbkgsumsubpt>=gensumsubpt) continue ;
//                    for(int ir = 0 ; ir <nrbin; ir++){  
//                        if(DoSumPtNorm){
//                            genpsi[ir]/=gensumpt;
//                            genrho[ir]/=gensumpt;
//                            genbkgpsi[ir]/=gensumpt;
//                            genbkgrho[ir]/=gensumpt;
//                            gensumchpt[ir]/=gensumpt ;
//                            genbkgsumchpt[ir]/=gensumpt ;
//                        }
//                        else {
//                            genpsi[ir]/=genjet_pt;
//                            genrho[ir]/=genjet_pt;
//                            genbkgpsi[ir]/=genjet_pt;
//                            genbkgrho[ir]/=genjet_pt;
//                            gensumchpt[ir]/=genjet_pt ;
//                            genbkgsumchpt[ir]/=genjet_pt ;
//                            
//                        }
//                        my_hists->genChargeMult[curr_bin][ir]->Fill(jet_pt, gencharge[ir], weight);
//                        my_hists->genSumChPt[curr_bin][ir]->Fill(jet_pt, gensumchpt[ir],weight); 
//                        my_hists->genbkgChargeMult[curr_bin][ir]->Fill(jet_pt, genbkgcharge[ir],weight);
//                        my_hists->genbkgSumChPt[curr_bin][ir]->Fill(jet_pt, genbkgsumchpt[ir],weight); 
//                        
//                        my_hists->genDiffJS[curr_bin][ir]->Fill(jet_pt, genrho[ir],weight);
//                        //       my_hists->genDiffJS[curr_bin][ir]->Fill(jet_pt, genrho[ir],weight);
//                        my_hists->genIntJS[curr_bin][ir]->Fill(jet_pt, genpsi[ir],weight);
//                        // rho/=deltacone ;
//                        my_hists->genbkgDiffJS[curr_bin][ir]->Fill(jet_pt, genbkgrho[ir],weight);
//                        //      my_hists->genbkgDiffJS[curr_bin][ir]->Fill(jet_pt, genbkgrho[ir],weight);
//                        //   my_hists->IntJS[curr_bin]->Fill(jet_pt, 1-psi);
//                        my_hists->genbkgIntJS[curr_bin][ir]->Fill(jet_pt, genbkgpsi[ir],weight);
//                    }  //radius loop in order to fill jet shape histograms   
//                } //eta limit cut for ER bkg
//
//            } //it is MC and gen level 

        } //jet loop
        //  cout << "still working222222\n";
        my_hists->Vertex->Fill(offSel->vz, weight);
        my_hists->CenBin->Fill(offSel->hiBin,weight); 
    }  ///event loop
    
    my_hists->Write();
    //   my_hists->Delete();
    //  delete my_hists;
    std::cout << "working done\n";
}




