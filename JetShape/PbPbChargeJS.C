#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "class_def/skim.h"
#include "class_def/Evt.h"
#include "class_def/HIHLT.h"
#include "class_def/track.h"
#include "class_def/akPu3PFJet.h"
#include "class_def/pfTree.h"
#include "class_def/GenParticle.h"
#include "TMath.h"
#include <iostream>
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
const double dphicut = TMath::TwoPi()/3. ;
const double leadingjetcut = 80. ;
const double subleadjetcut = 40. ;
const double trackcut = 1.;
const double tracketacut = 3.; //make sure the tracks around jet cone inside eta range

////for etalimt = 0.3, to remove the possible overlap region by ER method 
const double etalimit = 2.0 ; 

const int pthat =200 ; //30 and 80 for pp; 30,50,80,120,170,200 for PbPb MC 
TString coll = "HI";

const bool DoGenAna=kFALSE ; //should be only be true for MC sample

double weight ;
TString intputFile ;

//TString dataPath="/Users/ymao/group/CMS/hiForest";
TString dataPath ;

////if it is pp, no centrality bins, only one
//const int nbin = 1 ;
//const int centr[] ={0,100};
//for HI centrality bin
//const int nbin = 6 ;
//const int centr[] ={0,10,20,30,50,70,100};
const int nbin = 4 ;
const int centr[] ={0,10,30,50,100};

const int nptbin = 6 ;
const double pt[]={80., 100., 120., 140., 160.,200., 300., 500.};

const int netabin = 5 ;
const double deta[]={0.0,0.5,1.0,1.5,2.0, 4.0} ; 
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
    TH1F * subjetpt[nbin];
    TH2F * dijet[nbin];
    TH1F * Rjj[nbin];
    TH1F * Ajj[nbin] ;
    TH2F * trackpt[nbin];
    TH2F * trackphi[nbin];
    TH2F * tracketa[nbin];
    
    TH2F * jetfrag[nbin] ;
    TH2F * subjetfrag[nbin] ;
    TH2F * SumptJetPt[nbin] ;
    TH2F * JetBkgCone[nbin] ;
    TH2F * IncTrackDphi[nbin];
    TH2F * JetTrackDphi[nbin];
    TH2F * JetBkgTrackDphi[nbin];
    TH2F * JetTrackDeta[nbin];
    TH2F * JetBkgTrackDeta[nbin];
    TH2F * bkgtrackpt[nbin];

    TH1F * deltaR;
    TH1D * CenBin;
    
    //   TH1F * ptbin[6];
    //for jet shape variables
    TH2F * ChargePt[nbin][nrbin];
    TH2F * SumChPt[nbin][nrbin];
    TH2F * ChargeMult[nbin][nrbin];   
    TH2F * DiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * IntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.
    //  TH2F * dphiJS[nbin]; //phi diviration from jet phi 
    //   TH2F * detaJS[nbin] ; //eta diviration from jet eta 
    TH1F * DiffJSPt80_100[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    
    //for jet shape background study
    TH2F * bkgChargePt[nbin][nrbin];
    TH2F * bkgSumChPt[nbin][nrbin];
    TH2F * bkgChargeMult[nbin][nrbin];   
    TH2F * bkgDiffJS[nbin][nrbin]; //differential jet shapes (pho(r)) hist.
    TH2F * bkgIntJS[nbin][nrbin]; //Integrated jet shapes (psi(r)) hist.

//    TH2F * subDiffAjbin[nbin][nrbin][3]; //differential sub-jet shapes in Aj bins.
//    TH2F * bkgsubDiffAjbin[nbin][nrbin][3]; //differential sub-jet shapes in Aj bins.
    //for subleading jet shape, fill according leading jet bins
    TH2F * subDiffJS[nbin][nrbin][nptbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * subIntJS[nbin][nrbin][nptbin]; //Integrated sub-jet shapes (psi(r)) hist.
    TH2F * bkgsubDiffJS[nbin][nrbin][nptbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * bkgsubIntJS[nbin][nrbin][nptbin]; //Integrated sub-jet shapes (psi(r)) hist. 
    TH2F * DiffEtaBinJS[nbin][nrbin][netabin]; //differential jet shapes (pho(r)) hist.
    TH2F * bkgDiffEtaBinJS[nbin][nrbin][netabin]; //differential jet shapes (pho(r)) hist.

    
    //   if(IsMC){
    TH2F * genjetpt[nbin];
    TH2F * gensubjetpt[nbin];
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

    //for subleading jet shape, fill according leading jet bins
    TH2F * gensubDiffJS[nbin][nrbin][nptbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * gensubIntJS[nbin][nrbin][nptbin]; //Integrated sub-jet shapes (psi(r)) hist.
    TH2F * genbkgsubDiffJS[nbin][nrbin][nptbin]; //differential sub-jet shapes (pho(r)) hist.
    TH2F * genbkgsubIntJS[nbin][nrbin][nptbin]; //Integrated sub-jet shapes (psi(r)) hist. 

    //   }
};

hist_class::hist_class(TString the_desc)
{
    
    desc = the_desc;
    IsMC =kFALSE ;
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin] = new TH1F(Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Nevents_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -0.5, 99.5);
        NJets[ibin] = new TH1F(Form("NJets_%d-%d%%",centr[ibin],centr[ibin+1]), Form("NJets_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -0.5, 99.5);
        Ntrack[ibin] = new TH1F(Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Ntracks_%d-%d%%",centr[ibin],centr[ibin+1]), 800, -1., 799);
        jetpt[ibin] = new TH1F(Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.);
        jetpt[ibin]->Sumw2();
        subjetpt[ibin] = new TH1F(Form("subjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("subjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500);
        subjetpt[ibin]->Sumw2();
        jeteta[ibin] = new TH2F(Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jeteta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -5.05, 4.95);
        jeteta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jeteta[ibin]->GetYaxis()->SetTitle("#eta");
        jeteta[ibin]->Sumw2();
        jetphi[ibin] = new TH2F(Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("jetphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -5.05, 4.95);
        jetphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetphi[ibin]->GetYaxis()->SetTitle("#phi");
        jetphi[ibin]->Sumw2();
        dijet[ibin] = new TH2F(Form("dphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("dphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4.05, 7.95);
        //        dijet[ibin] = new TH2F(Form("dphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("dphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,30, 0.,TMath::Pi());
        dijet[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        dijet[ibin]->GetYaxis()->SetTitle("#Delta#phi");
        dijet[ibin]->Sumw2();
        Rjj[ibin] = new TH1F(Form("Rjj_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Rjj_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -0.01, 1.99);
        Rjj[ibin]->Sumw2();
        Ajj[ibin] = new TH1F(Form("Aj_%d-%d%%",centr[ibin],centr[ibin+1]), Form("Aj_%d-%d%%",centr[ibin],centr[ibin+1]), 150, -0.005, 1.495);
        Ajj[ibin]->Sumw2();
        trackpt[ibin] = new TH2F(Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500); 
        trackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackpt[ibin]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        trackpt[ibin]->Sumw2();
        trackphi[ibin] = new TH2F(Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("trackphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95); 
        trackphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        trackphi[ibin]->GetYaxis()->SetTitle("#phi^{trk}");   
        trackphi[ibin]->Sumw2();
        tracketa[ibin] = new TH2F(Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), Form("tracketa_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95); 
        tracketa[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        tracketa[ibin]->GetYaxis()->SetTitle("#eta^{trk}");   
        tracketa[ibin]->Sumw2();
        jetfrag[ibin] = new TH2F(Form("FFleading_%d-%d%%",centr[ibin],centr[ibin+1]), Form("FFleading_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 101, -0.05, 10.05);
        jetfrag[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        jetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet}/p_{T}^{h})");
        jetfrag[ibin]->Sumw2();
        subjetfrag[ibin] = new TH2F(Form("FFsubleading_%d-%d%%",centr[ibin],centr[ibin+1]), Form("FFsubleading_%d-%d%%",centr[ibin],centr[ibin+1]), 101, -0.05, 10.05,101, -0.05, 10.05);
        subjetfrag[ibin]->GetXaxis()->SetTitle("#xi = ln(p_{T}^{jet1}/p_{T}^{h})");
        subjetfrag[ibin]->GetYaxis()->SetTitle("#xi = ln(p_{T}^{jet2}/p_{T}^{h})");
        subjetfrag[ibin]->Sumw2();
        SumptJetPt[ibin] = new TH2F(Form("SumptJetPtRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("SumptJetPtRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500.,100, -0.01, 1.99);  
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
        bkgtrackpt[ibin] = new TH2F(Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgtrackpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500); 
        bkgtrackpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
        bkgtrackpt[ibin]->GetYaxis()->SetTitle("p_{T}^{trk} (GeV/c)");   
        bkgtrackpt[ibin]->Sumw2();
        if(IsMC&&DoGenAna){
            genjetpt[ibin] = new TH2F(Form("genjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500);
            genjetpt[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            genjetpt[ibin]->GetYaxis()->SetTitle("p_{T}^{gen} (GeV/c)");   
            genjetpt[ibin]->Sumw2();
            gensubjetpt[ibin] = new TH2F(Form("gensubjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("gensubjetpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,500, 0., 500);
            gensubjetpt[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            gensubjetpt[ibin]->GetYaxis()->SetTitle("p_{T}^{gen} (GeV/c)");  
            gensubjetpt[ibin]->Sumw2();
            genjeteta[ibin] = new TH2F(Form("genjeteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjeteta_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -5.05, 4.95,100, -5.05, 4.95);
            genjeteta[ibin]->GetXaxis()->SetTitle("#eta^{rec}");
            genjeteta[ibin]->GetYaxis()->SetTitle("#eta^{gen}");
            genjeteta[ibin]->Sumw2();
            genjetphi[ibin] = new TH2F(Form("genjetphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genjetphi_%d-%d%%",centr[ibin],centr[ibin+1]), 100, -5.05, 4.95,100, -5.05, 4.95);
            genjetphi[ibin]->GetXaxis()->SetTitle("#phi^{rec}");
            genjetphi[ibin]->GetYaxis()->SetTitle("#phi^{gen}");
            genjetphi[ibin]->Sumw2();
            gendphi[ibin] = new TH2F(Form("gendphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("gendphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,120, -4.05, 7.95);
            gendphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            gendphi[ibin]->GetYaxis()->SetTitle("#Delta#phi");   
            gendphi[ibin]->Sumw2();
            genptRatio[ibin] = new TH2F(Form("genptRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genptRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 51, -0.05,5.05);
            genptRatio[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            genptRatio[ibin]->GetYaxis()->SetTitle("p_{T}^{gen}/p_{T}^{rec}"); 
            genptRatio[ibin]->Sumw2();
            genphiRatio[ibin] = new TH2F(Form("genphiRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genphiRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -1.01,0.99);
            genphiRatio[ibin]->GetXaxis()->SetTitle("p_{T}^{rec} (GeV/c)");
            genphiRatio[ibin]->GetYaxis()->SetTitle("#phi_{gen}-#phi_{rec}"); 
            genphiRatio[ibin]->Sumw2();
            genetaRatio[ibin] = new TH2F(Form("genetaRatio_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genetaRatio_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500,100, -1.01,0.99);
            genetaRatio[ibin]->Sumw2();
            genetaRatio[ibin]->GetXaxis()->SetTitle("p_{T}^{gen} (GeV/c)");
            genetaRatio[ibin]->GetYaxis()->SetTitle("#eta_{gen}-#eta_{rec}"); 
            genpartpt[ibin] = new TH2F(Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500);
            genpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genpartpt[ibin]->GetYaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            genpartpt[ibin]->Sumw2();
            genpartphi[ibin] = new TH2F(Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genpartphi_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95);
            genpartphi[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genpartphi[ibin]->GetYaxis()->SetTitle("#phi^{part}");   
            genpartphi[ibin]->Sumw2();
            genparteta[ibin] = new TH2F(Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("genparteta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95);
            genparteta[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            genparteta[ibin]->GetYaxis()->SetTitle("#eta^{part} ");   
            genparteta[ibin]->Sumw2();
            bkgpartpt[ibin] = new TH2F(Form("bkgpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgpartpt_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 500, 0., 500); 
            bkgpartpt[ibin]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
            bkgpartpt[ibin]->GetYaxis()->SetTitle("p_{T}^{part} (GeV/c)");   
            bkgpartpt[ibin]->Sumw2();
            bkgparteta[ibin] = new TH2F(Form("bkgparteta_%d-%d%%",centr[ibin],centr[ibin+1]), Form("bkgparteta_%d-%d%%",centr[ibin],centr[ibin+1]), 500, 0., 500, 100, -5.05, 4.95); 
            bkgparteta[ibin]->GetXaxis()->SetTitle("p_{T}^{part} (GeV/c)");
            bkgparteta[ibin]->GetYaxis()->SetTitle("#eta^{part} (GeV/c)");   
            bkgparteta[ibin]->Sumw2();

        }
        
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
            DiffJSPt80_100[ibin][ir] = new TH1F(Form("diffJSPt80_100dR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("diffJSPt80_100JSdR%.f_%.f_Cen%d-%d%%",rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 150, -0.005, 1.495);
            DiffJSPt80_100[ibin][ir]->GetXaxis()->SetTitle("#rho (r)");
            DiffJSPt80_100[ibin][ir]->Sumw2();
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
            for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){
                subDiffJS[ibin][ir][ipt] = new TH2F(Form("subjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("subjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                subDiffJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                subDiffJS[ibin][ir][ipt]->GetYaxis()->SetTitle("#rho (r)");
                subDiffJS[ibin][ir][ipt]->Sumw2();
                subIntJS[ibin][ir][ipt] = new TH2F(Form("subjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("subjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                subIntJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                subIntJS[ibin][ir][ipt]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
                subIntJS[ibin][ir][ipt]->Sumw2();
                
                bkgsubDiffJS[ibin][ir][ipt] = new TH2F(Form("bkgsubjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsubjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                bkgsubDiffJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                bkgsubDiffJS[ibin][ir][ipt]->GetYaxis()->SetTitle("#rho (r)");
                bkgsubDiffJS[ibin][ir][ipt]->Sumw2();
                bkgsubIntJS[ibin][ir][ipt] = new TH2F(Form("bkgsubjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgsubjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                bkgsubIntJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                bkgsubIntJS[ibin][ir][ipt]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));    
                bkgsubIntJS[ibin][ir][ipt]->Sumw2();
          
            }
            for(Int_t ieta = 0 ; ieta <netabin ; ieta++){
                DiffEtaBinJS[ibin][ir][ieta] = new TH2F(Form("diffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10, rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("diffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10,rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                DiffEtaBinJS[ibin][ir][ieta]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                DiffEtaBinJS[ibin][ir][ieta]->GetYaxis()->SetTitle("#rho (r)");
                DiffEtaBinJS[ibin][ir][ieta]->Sumw2();
                bkgDiffEtaBinJS[ibin][ir][ieta] = new TH2F(Form("bkgdiffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10, rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("bkgdiffJSdEtaBin%.f_%.fdR%.f_%.f_Cen%d-%d%%", deta[ieta]*10,deta[ieta+1]*10,rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                bkgDiffEtaBinJS[ibin][ir][ieta]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                bkgDiffEtaBinJS[ibin][ir][ieta]->GetYaxis()->SetTitle("#rho (r)");
                bkgDiffEtaBinJS[ibin][ir][ieta]->Sumw2();
  
            }
            if(IsMC&&DoGenAna){
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
                for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){ //jet pt bin loop
                    gensubDiffJS[ibin][ir][ipt] = new TH2F(Form("gensubjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("gensubjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                    gensubDiffJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                    gensubDiffJS[ibin][ir][ipt]->GetYaxis()->SetTitle("#rho (r)");
                    gensubDiffJS[ibin][ir][ipt]->Sumw2();
                    gensubIntJS[ibin][ir][ipt] = new TH2F(Form("gensubjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("gensubjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                    gensubIntJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                    gensubIntJS[ibin][ir][ipt]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));
                    gensubIntJS[ibin][ir][ipt]->Sumw2();
                    genbkgsubDiffJS[ibin][ir][ipt] = new TH2F(Form("genbkgsubjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genbkgsubjetdiffJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                    genbkgsubDiffJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                    genbkgsubDiffJS[ibin][ir][ipt]->GetYaxis()->SetTitle("#rho (r)");
                    genbkgsubDiffJS[ibin][ir][ipt]->Sumw2();
                    genbkgsubIntJS[ibin][ir][ipt] = new TH2F(Form("genbkgsubjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), Form("genbkgsubjetIntJetPt%.f_%.fdR%.f_%.f_Cen%d-%d%%",pt[ipt],pt[ipt+1],rbin[ir]*100,rbin[ir+1]*100,centr[ibin],centr[ibin+1]), 500, 0., 500, 150, -0.005, 1.495);
                    genbkgsubIntJS[ibin][ir][ipt]->GetXaxis()->SetTitle("p_{T}^{jet} (GeV/c)");
                    genbkgsubIntJS[ibin][ir][ipt]->GetYaxis()->SetTitle(Form("#psi(r=%1.2f)",deltacone*(ir+1)));    
                    genbkgsubIntJS[ibin][ir][ipt]->Sumw2();
 
                } //end of jet pt bin loop
            } //for MC histograms
        }  //radius bins loop
        
    }
    //    for(int i = 0 ; i < 6 ; i++){
    //     ptbin[i] = new TH1F(Form("ptbin_%.f-%.f",pt[i], pt[i+1]), Form("ptbin_%.f-%.f",pt[i], pt[i+1]), 500, 0., 500.);
    //    }
    // if(!deltaR)
    deltaR = new TH1F((TString) (desc + "_deltaR"), "", 100, 0., 10.);
    CenBin = new TH1D((TString) (desc + "_Cent"), "", 40, 0, 40);
}

void hist_class::Delete()
{
    for(int ibin = 0 ; ibin <nbin; ibin++){
        delete NEvents[ibin];
        delete NJets[ibin];
        delete Ntrack[ibin];  
        delete jetpt[ibin];
        delete jeteta[ibin];
        delete jetphi[ibin];
        delete subjetpt[ibin];
        delete dijet[ibin];
        delete Rjj[ibin] ;  
        delete Ajj[ibin];
        delete trackpt[ibin];
        delete trackphi[ibin];
        delete tracketa[ibin];
        
        delete jetfrag[ibin];
        delete subjetfrag[ibin];
        delete SumptJetPt[ibin];
        delete JetBkgCone[ibin];
        delete IncTrackDphi[ibin];
        delete JetTrackDphi[ibin];
        delete JetBkgTrackDphi[ibin];
        delete JetTrackDeta[ibin];
        delete JetBkgTrackDeta[ibin];
        delete bkgtrackpt[ibin];
        if(IsMC&&DoGenAna){
            delete genjetpt[ibin];
            delete gensubjetpt[ibin];
            delete genjeteta[ibin];
            delete genjetphi[ibin];
            delete gendphi[ibin];
            delete genptRatio[ibin];
            delete genphiRatio[ibin];
            delete genetaRatio[ibin];
            delete genpartpt[ibin];
            delete genpartphi[ibin];
            delete genparteta[ibin];
            delete bkgpartpt[ibin];
            delete bkgparteta[ibin];
        }
        
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
            delete DiffJSPt80_100[ibin][ir];
            for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){ //jet pt bin loop
                delete subDiffJS[ibin][ir][ipt];
                delete subIntJS[ibin][ir][ipt];
                delete bkgsubDiffJS[ibin][ir][ipt];
                delete bkgsubIntJS[ibin][ir][ipt];
            }
            for(Int_t ieta = 0 ; ieta <netabin ; ieta++){
                delete DiffEtaBinJS[ibin][ir][ieta];
                delete bkgDiffEtaBinJS[ibin][ir][ieta];
            }
            if(IsMC&&DoGenAna){
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
                for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){ //jet pt bin loop
                    delete gensubDiffJS[ibin][ir][ipt];
                    delete gensubIntJS[ibin][ir][ipt];
                    delete genbkgsubDiffJS[ibin][ir][ipt];
                    delete genbkgsubIntJS[ibin][ir][ipt];                    
                } //end of jet pt bins
            }
        }
    }
    //   for(int i=0; i<6;i++) delete ptbin[i];
    delete deltaR;
    delete CenBin;
}

void hist_class::Write()
{
    TString out_name ;
    TString dataType ; 
    if(IsMC) dataType="MC" ;
    else dataType="DATA";
    if(IsMC){
        if(etalimit==etacut)
            out_name=Form("%s%s_ChargedJetPt%.f_%.fTrk%.fEta%.f_RCbkgEtaBound%.f_CenBin%d_Nrbin%d_Pthat%d%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, etacut,etalimit*10, nbin,nrbin,pthat, intputFile.Data());
        else 
            out_name=Form("%s%s_ChargedJetPt%.f_%.fTrk%.fEta%.f_ERbkgEtaBound%.f_CenBin%d_Nrbin%d_Pthat%d%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, etacut,etalimit*10, nbin,nrbin,pthat, intputFile.Data());
    }
    else {
        if(etalimit==etacut)
            out_name=Form("%s%s_ChargedJetPt%.f_%.fTrk%.fEta%.f_RCbkgEtaBound%.f_CenBin%d_Nrbin%d_%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, etacut,etalimit*10, nbin,nrbin, intputFile.Data());
        else 
            out_name=Form("%s%s_ChargedJetPt%.f_%.fTrk%.fEta%.f_ERbkgEtaBound%.f_CenBin%d_Nrbin%d_%s",dataType.Data(),coll.Data(),leadingjetcut,subleadjetcut,trackcut, etacut,etalimit*10, nbin,nrbin, intputFile.Data());   
    }
    
    //sprintf(out_name,Form("%s_ptCut%3f_%2f_CenBin%d_%s",dataType,leadingjetcut,subleadjetcut,nbin,intputFile));
  //  TFile *out_file = new TFile(Form("/Users/ymao/group/CMS/anaOutputs/%s",out_name.Data()), "RECREATE");
        TFile *out_file = new TFile(Form("/net/hidsk0001/d00/scratch/maoyx/JetShape/%s",out_name.Data()), "RECREATE");
    for(int ibin = 0 ; ibin <nbin; ibin++){
        NEvents[ibin]->Write();
        NJets[ibin]->Write();
        Ntrack[ibin]->Write();
        jetpt[ibin]->Write();
        subjetpt[ibin]->Write();
        jeteta[ibin]->Write();
        jetphi[ibin]->Write();
        dijet[ibin]->Write();
        Rjj[ibin]->Write();  
        Ajj[ibin]->Write();
        trackpt[ibin]->Write();
        trackphi[ibin]->Write();
        tracketa[ibin]->Write();
        
        jetfrag[ibin]->Write();
        subjetfrag[ibin]->Write();
        SumptJetPt[ibin]->Write();
        JetBkgCone[ibin]->Write();
        IncTrackDphi[ibin]->Write();
        JetTrackDphi[ibin]->Write();
        JetBkgTrackDphi[ibin]->Write();
        JetTrackDeta[ibin]->Write();
        JetBkgTrackDeta[ibin]->Write();
        bkgtrackpt[ibin]->Write();
        if(IsMC&&DoGenAna){
            genjetpt[ibin]->Write();
            gensubjetpt[ibin]->Write();
            genjeteta[ibin]->Write();
            genjetphi[ibin]->Write();
            gendphi[ibin]->Write();
            genptRatio[ibin]->Write();
            genphiRatio[ibin]->Write();
            genetaRatio[ibin]->Write();
            genpartpt[ibin]->Write();
            genpartphi[ibin]->Write();
            genparteta[ibin]->Write();
            bkgpartpt[ibin]->Write();
            bkgparteta[ibin]->Write();
        }
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
            DiffJSPt80_100[ibin][ir]->Write();
            for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){ //jet pt bin loop
                subDiffJS[ibin][ir][ipt]->Write();
                subIntJS[ibin][ir][ipt]->Write();
                bkgsubDiffJS[ibin][ir][ipt]->Write();
                bkgsubIntJS[ibin][ir][ipt]->Write();
            }    
            for(Int_t ieta = 0 ; ieta <netabin ; ieta++){
                DiffEtaBinJS[ibin][ir][ieta]->Write();
                bkgDiffEtaBinJS[ibin][ir][ieta]->Write();
            }
            if(IsMC&&DoGenAna){
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
                
                for(Int_t ipt = 0 ; ipt <nptbin ; ipt++){ //jet pt bin loop
                    gensubDiffJS[ibin][ir][ipt]->Write();
                    gensubIntJS[ibin][ir][ipt]->Write();
                    genbkgsubDiffJS[ibin][ir][ipt]->Write();
                    genbkgsubIntJS[ibin][ir][ipt]->Write();
                } //end of jet pt bins
            } //only write if it MC
        }
    }
    //  for(int i=0; i<6;i++) ptbin[i]->Write();
    deltaR->Write();
    CenBin->Write();
    out_file->Close();
    cout <<"Output file: " <<Form("%s",out_name.Data()) <<endl ;
    
}


int main()
{
    // gROOT->ForceStyle(0);
    
    hist_class *my_hists = new hist_class("pfjet");
    cout <<my_hists->IsMC<<endl ;
    double wt[40];
    if(my_hists->IsMC==kTRUE && coll=="HI"){
      //  TFile * wtfile = TFile::Open("/Users/ymao/group/CMS/PFjet/McCentralityReweight.root", "readonly");
            TFile * wtfile = TFile::Open("/net/hidsk0001/d00/scratch/maoyx/JetShape/McCentralityReweight.root", "readonly");
        TH1D * hReWt = (TH1D*)wtfile->Get("CentWeight");
        for(int ibin = 0 ; ibin < hReWt->GetNbinsX() ; ibin++){
            if(hReWt->GetBinContent(ibin)==0)
                wt[ibin]=1.;
            else       
                wt[ibin]=hReWt->GetBinContent(ibin);
        }
        wtfile->Close();
    }
    else {
        for(int ibin = 0 ; ibin < 40 ; ibin++) wt[ibin]=1. ; 
    }
    std::cout << "start working\n";
    if(my_hists->IsMC!=kTRUE) 
    //    dataPath="/Volumes/WORKDISK/backup/pc93/2012-01-26/WorkSpace/data/HI2011/forest";
    // dataPath="/mnt/hadoop/cms/store/user/pelin/ppdijet/pp_hi" ; //mit pp data path
     // dataPath="/mnt/hadoop/cms/store/user/velicanu/forest" ;//mit PbPb data path
       dataPath="/mnt/hadoop/cms/store/user/frankmalocal/forest" ;//mit PbPb data path
    else {
     //   dataPath= "/Users/ymao/group/CMS/hiForest"; //local analysis
               if(coll=="HI") 
                    dataPath= Form("/mnt/hadoop/cms/store/user/mnguyen/MC_Production/Pythia%d_HydjetDrum_mix01",pthat); //mit path for HI
                else    
        //        //        dataPath= Form("/mnt/hadoop/cms/store/user/mnguyen/MC_Production/pythia%d",pthat); //mit path for pp
                   dataPath= Form("/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged"); //mit path for pp
    }
    if(my_hists->IsMC!=kTRUE){  //real data analysis
        if(coll=="HI")             
         //   intputFile="HiForestData2011_FullStat_JSON_Dijet_v7.root";
         //  intputFile="HiForestDijet_v7.root";
           intputFile="promptskim-hihighpt-hltjet80-pt90-v1_part.root";
        else 
            intputFile="merged_pp2760_AllPhysics_Part_Prod03.root";
        // intputFile="mit_pelin_dijet_hiforest_pp_276TeV_data.root";
    }
    else { //MC sample
        if(coll=="HI")             
         //   intputFile=Form("mit_pawan_PbPb2760_Dijet_Hydrum_dijet%d.root", pthat);
          intputFile="merged_HydjetDrum.root";
        else 
            //     intputFile="merged_hiForest.root";
            //  intputFile="mit_mnguyen_pp2760_pythia80_dijet80.root";
            intputFile=Form("mit_ivan_pp276Dijet%d_merged.root",pthat);  
    }
    TFile *my_file=TFile::Open(Form("%s/%s", dataPath.Data(),intputFile.Data()));
    cout <<"Input file" << Form("%s/%s", dataPath.Data(),intputFile.Data())<<endl ;
    
    if(my_file->IsZombie()) {
    }
    
    TTree *evt_tree = (TTree*) my_file->Get("hiEvtAnalyzer/HiTree");
    Evt * offSel = new Evt(evt_tree);
    
    TTree *skim_tree = (TTree*) my_file->Get("skimanalysis/HltTree");
    skim * my_skim = new skim(skim_tree);
    
    
    TTree *hlt_tree = (TTree*) my_file->Get("hltanalysis/HltTree");
    //    if(coll=="HI") 
      HIHLT * trigSel = new HIHLT(hlt_tree);
    //    else 
   // HLT * trigSel = new HLT(hlt_tree);
    
    TTree *inp_tree = (TTree*) my_file->Get("akPu3PFJetAnalyzer/t");
    akPu3PFJet * my_ct = new akPu3PFJet(inp_tree);
    
    TTree *pf_tree = (TTree*) my_file->Get("pfcandAnalyzer/pfTree");
    pfTree * pfpart = new pfTree(pf_tree);
    
    TTree *tr_tree = (TTree*) my_file->Get("anaTrack/trackTree");
    track * my_tr = new track(tr_tree);
    
    //   if(my_hists->IsMC==kTRUE){
    TTree *GenPart_tree = (TTree*) my_file->Get("HiGenParticleAna/hi");
    GenParticle * my_GenPart = new GenParticle(GenPart_tree);      
    //   }
    
    int n_evt = my_ct->fChain->GetEntriesFast();
    int curr_bin = nbin-1 ;
    cout <<"Number of events =" <<n_evt <<endl ;
    for(int evi = 0; evi < n_evt; evi++) {
        //     for(int evi = 0; evi < 10; evi++) {
        my_skim->fChain->GetEntry(evi); 
        trigSel->fChain->GetEntry(evi);
        
        int noise_evt = my_skim->pHBHENoiseFilter ;
        int ecal_noise = my_skim->phiEcalRecHitSpikeFilter ;
      //  if(ecal_noise==0) continue ;
        if(coll=="HI") {
            int evt_sel = my_skim->pcollisionEventSelection ;
            if(evt_sel==0) continue ;
        }
        if(my_hists->IsMC!=kTRUE){
            if(noise_evt==0) continue ;
            //if(coll=="HI")
                    int jetTr1 = trigSel->HLT_HIJet65_v1 ;
                    int jetTr2 = trigSel->HLT_HIJet80_v1 ;
            // else 
           // int jetTr1 = trigSel->HLT_Jet40_v1 ;
           // int jetTr2 = trigSel->HLT_Jet60_v1 ;
            //                
          //  if(jetTr1==0 || jetTr2==0) continue ;
        }
        
        my_ct->fChain->GetEntry(evi);
        my_tr->fChain->GetEntry(evi);
        pfpart->fChain->GetEntry(evi);
        if(my_hists->IsMC==kTRUE && DoGenAna)my_GenPart->fChain->GetEntry(evi);
        // std::cout <<"!!!!!!!!!!!!!!still working\n";
        
        //if there is no jets or no PF candidates, skip the event
        if(my_ct->nref==0) continue ;
        
        if(coll=="HI"){
            offSel->fChain->GetEntry(evi);
            int hiBin = offSel->hiBin ;
            if(my_hists->IsMC==kTRUE) weight = wt[hiBin]; 
            else weight = 1. ;
            double centrality = offSel->hiBin*2.5 ;
            //   my_hists->CenBin->Fill(offSel->hiBin);
            
            for(int ibin = 0 ; ibin <nbin; ibin++){
                if(centrality >=centr[ibin] && centrality<centr[ibin+1]) curr_bin = ibin ;
            }
        }
        else {
            curr_bin=nbin-1 ;
            weight = 1. ;
        }
        //   cout << "  cent_bin:" <<curr_bin <<endl ;
        
        if(evi%10000==1)cout <<" coll = " <<coll <<" weight = " <<weight <<" evt = " <<evi <<endl ;
        
        my_hists->Ntrack[curr_bin]->Fill(my_tr->fChain->GetEntry(evi), weight);
        //cout <<my_hists->NEvents[curr_bin]->GetName() <<endl;
        //cout << "start working222222\n";
        
        
        ///--------------------------------------------------------------------
        /// ---- JETS  ----- ///////////////////////////////////////////
        ///--------------------------------------------------------------------
        
        //define the variables used
        double lead_pt=0. ;
        int lead_index=-1 ;
        double sublead_pt=0. ;
        int sublead_index=-1 ;      
        double jet_phi = -999.;
        double jet_eta = -999. ;
        double bkg_phi = -999.;
        double bkg_eta = -999.;
        
        int njets = 0 ;
        double subjet_phi = -999. ;
        double subjet_eta = -999. ;
        double bkg_subphi = -999. ;
        double bkg_subeta = -999. ; 
        
        int ptBin = -1 ;
        double Aj = -999. ;
        double bkgphicut = 0. ;
        double bkgetacut = 0. ;
        int dEtaBin = -1. ;
        
        //   if(DoGenAna){
        //for MC gen jet info
        double genjet_pt = -999. ;
        double genjet_phi = -999.;
        double genjet_eta = -999. ;
        double gensubjet_pt = -999. ;
        double gensubjet_phi = -999.;
        double gensubjet_eta = -999. ;
        double genbkg_phi = -999. ;
        double genbkg_eta = -999. ;
        double genbkg_subphi = -999. ;
        double genbkg_subeta = -999. ;            
        double genbkgphicut = 0. ;
        double genbkgetacut = 0. ;
        int genptBin = -1 ;
        //    }
        
        for(int j4i = 0; j4i < my_ct->nref ; j4i++) {
            
            double jet_pt= my_ct->jtpt[j4i];
            if(TMath::Abs(my_ct->jteta[j4i])>etacut) continue ;
            if(jet_pt<leadingjetcut) continue ;
            //remove flucluation with too large pt from small MC pthat sample
              if(my_hists->IsMC==kTRUE && jet_pt>6*pthat) continue ; 
            if(jet_pt >lead_pt){
                lead_pt=jet_pt;
                lead_index=j4i;
            }
        } //search for leading jet loop
        if(lead_index<0) continue ; //no leading found
        
        //   if(lead_index!=-1){ //if leading jet found
        jet_phi =my_ct->jtphi[lead_index];
        if(jet_phi<=-TMath::Pi())jet_phi+=TMath::TwoPi();
        jet_eta = my_ct->jteta[lead_index];
        my_hists->jetpt[curr_bin]->Fill(lead_pt, weight);
        my_hists->jeteta[curr_bin]->Fill(lead_pt, jet_eta, weight);
        my_hists->jetphi[curr_bin]->Fill(lead_pt, jet_phi, weight);
        
        if(my_hists->IsMC==kTRUE&&DoGenAna){
            
            genjet_pt =my_ct->refpt[lead_index];  
            genjet_phi =my_ct->refphi[lead_index]; 
            if(genjet_phi<=-TMath::Pi())genjet_phi+=TMath::TwoPi();            
            genjet_eta =my_ct->refeta[lead_index];  
            my_hists->genjetpt[curr_bin]->Fill(lead_pt,genjet_pt, weight);
            my_hists->genjeteta[curr_bin]->Fill(jet_eta, genjet_eta, weight);
            my_hists->genjetphi[curr_bin]->Fill(jet_phi, genjet_phi, weight);
            my_hists->genptRatio[curr_bin]->Fill(lead_pt,genjet_pt/lead_pt, weight);
            my_hists->genphiRatio[curr_bin]->Fill(lead_pt,genjet_phi-jet_phi, weight);
            my_hists->genetaRatio[curr_bin]->Fill(lead_pt,genjet_eta-jet_eta, weight);
            
        }
        //search for subleading jet
        for(int ijet = 0 ; ijet <my_ct->nref; ijet++){
            if(ijet==lead_index) continue ;
            if(TMath::Abs(my_ct->jteta[ijet])>etacut) continue ;
            //remove flucluation with too large pt from small MC pthat sample
            if(my_hists->IsMC==kTRUE && my_ct->jtpt[ijet]>6*pthat) continue ;
            
            //                double deltaphi = my_ct->jtphi[ijet]-jet_phi ;
            //                if(deltaphi>=TMath::Pi()) deltaphi-=TMath::TwoPi();
            //                if(deltaphi<-TMath::Pi()) deltaphi+=TMath::TwoPi();
            //                if(TMath::Abs(deltaphi)<dphicut) continue ;
            
            if(my_ct->jtpt[ijet]<subleadjetcut) continue ;            
            
            if(my_ct->jtpt[ijet] >sublead_pt){
                sublead_pt=my_ct->jtpt[ijet];
                sublead_index=ijet;
            }
        }  //end of subleading jet search
        if(sublead_index<0) continue ; //no subjet found
        
        //    if(sublead_index!=-1){ //subleading jet found
        subjet_phi =my_ct->jtphi[sublead_index];
        if(subjet_phi<=-TMath::Pi())subjet_phi+=TMath::TwoPi();        
        subjet_eta = my_ct->jteta[sublead_index];
        double dphi = subjet_phi-jet_phi;
//        if(dphi>TMath::Pi()) dphi-=TMath::TwoPi();
//        if(dphi<=-TMath::Pi()) dphi+=TMath::TwoPi();
        my_hists->dijet[curr_bin]->Fill(lead_pt, TMath::Abs(dphi), weight);
        
        //first search for highest two jets, to remove 4 jets events if the highest two jets are at the same side
        if(TMath::Abs(dphi)<=dphicut) continue ;
        
        //if(dphi >=TMath::TwoPi()/2.)dphi-=TMath::TwoPi(); 
        //if(dphi <-TMath::PiOver2())dphi+=TMath::TwoPi();
        Aj = TMath::Abs((lead_pt-sublead_pt)/(lead_pt+sublead_pt)) ;
        my_hists->subjetpt[curr_bin]->Fill(sublead_pt, weight);
        //                //in order to compare Pelin's delta phi (werid bins)
        //                if(dphi>TMath::Pi())dphi-=TMath::TwoPi();
        //                my_hists->dijet[curr_bin]->Fill(lead_pt, TMath::Abs(dphi));
        my_hists->Ajj[curr_bin]->Fill(Aj, weight);
        my_hists->Rjj[curr_bin]->Fill(sublead_pt/lead_pt, weight);
        njets++ ;        
        //   my_hists->NEvents[curr_bin]->Fill(my_ct->fChain->GetEntry(evi), weight);
        for(Int_t ipt = 0 ; ipt <nptbin; ipt++){
            if(lead_pt>=pt[ipt] && lead_pt <pt[ipt+1]) ptBin = ipt ;
        }
        if(my_hists->IsMC==kTRUE&&DoGenAna){
            gensubjet_pt =my_ct->refpt[sublead_index];  
            gensubjet_phi =my_ct->refphi[sublead_index];  
            if(gensubjet_phi<=-TMath::Pi())gensubjet_phi+=TMath::TwoPi();        
            gensubjet_eta =my_ct->refeta[sublead_index];               
            my_hists->gensubjetpt[curr_bin]->Fill(sublead_pt,gensubjet_pt, weight);
            my_hists->gendphi[curr_bin]->Fill(lead_pt,TMath::Abs(genjet_phi-gensubjet_phi), weight);
            if(TMath::Abs(genjet_phi-gensubjet_phi)<=dphicut) continue ;
            genbkgphicut = TMath::Abs(genjet_phi-gensubjet_phi)/2. ;
            genbkgetacut = TMath::Abs(genjet_eta-gensubjet_eta)/2. ;
            for(Int_t ipt = 0 ; ipt < nptbin; ipt++){
                if(genjet_pt>=pt[ipt] && genjet_pt<pt[ipt+1]) genptBin = ipt ;
            }

        }
        //set background cone 
        bkgphicut = TMath::Abs(jet_phi-subjet_phi)/2. ;
        bkgetacut = TMath::Abs(jet_eta-subjet_eta)/2. ;
//        if(TMath::Abs(jet_eta)<0.3) continue ;            
//        if(TMath::Abs(subjet_eta) < 0.3) continue ;                
     //   cout <<"deta =" << bkgetacut <<endl ;

        if(etalimit==etacut){ //for Random Cone method 
            //cout <<"Using random cone Bkg method!"<<endl ;
            if(jet_eta<0.) bkg_eta = jet_eta+bkgetacut;
            else bkg_eta = jet_eta-bkgetacut;
            if(jet_phi<0.)bkg_phi = jet_phi+bkgphicut;
            else bkg_phi = jet_phi-bkgphicut;
            if(subjet_eta<0.) bkg_subeta = subjet_eta+bkgetacut;
            else bkg_subeta = subjet_eta-bkgetacut;
            if(subjet_phi<0.)bkg_subphi = subjet_phi+bkgphicut;
            else bkg_subphi = subjet_phi-bkgphicut;
        }            
        else { //Eta reflected method 
            if(TMath::Abs(jet_eta)<0.3) continue ;            
            if(TMath::Abs(subjet_eta) < 0.3) continue ;                
            bkg_phi = jet_phi;
            bkg_eta = -jet_eta;
            bkg_subphi = subjet_phi ;
            bkg_subeta = -subjet_eta ;
        }
                
        my_hists->NEvents[curr_bin]->Fill(my_ct->fChain->GetEntry(evi), weight);
        
        if(TMath::Abs(bkg_eta)>2.) cout <<"jet_eta =" <<jet_eta<<" bkg =" <<bkg_eta<<endl ;
        if(TMath::Abs(bkg_subeta)>2.) cout <<"subjet_eta =" <<subjet_eta<<" bkg =" <<bkg_subeta<<endl ;
        if(TMath::Abs(bkg_eta)>2.) continue ;   
        if(TMath::Abs(bkg_subeta)>2.) continue ;   
        
        if(TMath::Sqrt((bkg_phi-jet_phi)*(bkg_phi-jet_phi)+(bkg_eta-jet_eta)*(bkg_eta-jet_eta))<=conesize){
            printf ("jet bkg inside leading jet cone \n");
            continue ;
        }
        if(TMath::Sqrt((bkg_subphi-subjet_phi)*(bkg_subphi-subjet_phi)+(bkg_subeta-subjet_eta)*(bkg_subeta-subjet_eta))<=conesize){
            printf ("subjet bkg inside subleading jet cone \n");
            continue ;
        }
        if(TMath::Sqrt((bkg_subphi-jet_phi)*(bkg_subphi-jet_phi)+(bkg_subeta-jet_eta)*(bkg_subeta-jet_eta))<=conesize){
            printf ("subjet bkg inside leading jet cone \n");
            continue ;
        }
        if(TMath::Sqrt((bkg_phi-subjet_phi)*(bkg_phi-subjet_phi)+(bkg_eta-subjet_eta)*(bkg_eta-subjet_eta))<=conesize){
            printf ("jet bkg inside subleading jet cone \n");
            continue ;
        }
        //      }
        
        my_hists->JetBkgCone[curr_bin]->Fill(bkg_phi-jet_phi, bkg_eta-jet_eta, weight);
        for(Int_t ieta = 0 ; ieta <netabin; ieta++){
            if(TMath::Abs(bkg_eta-jet_eta)>deta[ieta]&&TMath::Abs(bkg_eta-jet_eta)<=deta[ieta+1]) dEtaBin = ieta ; 
        }
        //  my_hists->jetpt[curr_bin]->Fill(lead_pt, weight);
        
        //        for(int i = 0 ; i <6 ; i++){
        //            if(lead_pt >=pt[i] && lead_pt<pt[i+1])my_hists->ptbin[i]->Fill(lead_pt, weight);
        //        }
        //for track analysis
        int charge[nrbin] ;
        double sumchpt[nrbin];
        double rho[nrbin] ;
        double psi[nrbin] ;
        double subrho[nrbin] ;
        double subpsi[nrbin] ;
        double sumpt = 0. ;
        double sumsubpt = 0. ;
        double meanphi = 0.;
        double meaneta = 0. ;
        int bkgcharge[nrbin] ;
        double bkgsumchpt[nrbin]  ;
        double bkgrho[nrbin];
        double bkgpsi[nrbin] ;
        double bkgsubrho[nrbin] ;
        double bkgsubpsi[nrbin] ;
        double bkgsumpt = 0. ;
        double bkgsumsubpt = 0. ;
        for(int ir = 0 ; ir <nrbin ; ir++){
            charge[ir]=0 ;
            sumchpt[ir]=0. ;
            rho[ir]=0. ;
            psi[ir]= 0.;
            subrho[ir]=0.;
            subpsi[ir]=0.;
            bkgcharge[ir]=0 ;
            bkgsumchpt[ir]=0. ;
            bkgrho[ir]=0.;
            bkgpsi[ir]=0. ;
            bkgsubrho[ir]=0.;
            bkgsubpsi[ir]=0.;
        }
        
        for(int itr = 0 ; itr < my_tr->nTrk ; itr++){
            
            
            double dr = 0.;
            double dr2 = 0.;
            double bkg_dr =0.;
            double bkgsub_dr =0.;
            double tr_pt = my_tr->trkPt[itr];
            double tr_phi = my_tr->trkPhi[itr];
            double tr_eta = my_tr->trkEta[itr];
            // if(TMath::Abs(tr_eta)>tracketacut) continue ;
            if(tr_pt<trackcut) continue ;
            
            //for leading jet shape study
            dr =TMath::Sqrt((tr_phi-jet_phi)*(tr_phi-jet_phi)+(tr_eta-jet_eta)*(tr_eta-jet_eta));
            my_hists->deltaR->Fill(dr, weight); 
            dr2 =TMath::Sqrt((tr_phi-subjet_phi)*(tr_phi-subjet_phi)+(tr_eta-subjet_eta)*(tr_eta-subjet_eta));            
            if(dr<conesize && dr2<conesize) {
                cout <<"!!!! two jets are overlap with track: "<<itr <<"eta: " <<tr_eta <<" phi:" <<tr_phi << endl;
                continue ;
            }        
            double jtrdphi = tr_phi-jet_phi ;
//            if(jtrdphi>TMath::Pi())jtrdphi-=TMath::TwoPi();
//            if(jtrdphi<=-TMath::Pi()) jtrdphi+=TMath::TwoPi();            
            my_hists->IncTrackDphi[curr_bin]->Fill(lead_pt,TMath::Abs(jtrdphi), weight);
            if(dr<=conesize){
                sumpt+=tr_pt ;
                meaneta+=tr_pt*tr_eta;
                meanphi+=tr_pt*tr_phi;
                my_hists->JetTrackDphi[curr_bin]->Fill(lead_pt,TMath::Abs(jtrdphi), weight);                
                my_hists->JetTrackDeta[curr_bin]->Fill(lead_pt,tr_eta-jet_eta, weight);                
                my_hists->jetfrag[curr_bin]->Fill(lead_pt, TMath::Log(lead_pt/tr_pt), weight);
                my_hists->trackpt[curr_bin]->Fill(lead_pt, tr_pt, weight);
                my_hists->trackphi[curr_bin]->Fill(lead_pt, tr_phi, weight);
                my_hists->tracketa[curr_bin]->Fill(lead_pt, tr_eta, weight);
                for(int ir = 0 ; ir <nrbin; ir++){
                    if(dr>rbin[ir]&&dr<=rbin[ir+1]){
                        rho[ir]+=tr_pt ;
                        //     cout<<" !!!! track index =" <<itr << " trk pt =" <<tr_pt << " tr phi =" <<tr_phi << " tr eta =" <<tr_eta  <<" dr =" <<dr <<" rho =" <<rho[ir]<<endl ;
                        
                        my_hists->ChargePt[curr_bin][ir]->Fill(lead_pt, tr_pt, weight);
                        sumchpt[ir]+=tr_pt ;
                        charge[ir]++ ;
                    }
                    if(dr<=rbin[ir+1]) {
                        psi[ir]+=tr_pt ; 
                    }
                }  //radius loop to fill leading jet JS histogram
                
            } //tracks inside for leading jet
            else {
                //study subleading jet shape
                if(dr2<=conesize) {
                    sumsubpt+=tr_pt;
                    my_hists->JetTrackDphi[curr_bin]->Fill(lead_pt,TMath::Abs(jtrdphi), weight);
                    my_hists->JetTrackDeta[curr_bin]->Fill(lead_pt,tr_eta-jet_eta, weight);                
                   my_hists->subjetfrag[curr_bin]->Fill(TMath::Log(lead_pt/tr_pt), TMath::Log(sublead_pt/tr_pt), weight);   
                    for(int ir = 0 ; ir <nrbin; ir++){
                        if(dr2>rbin[ir]&&dr2<=rbin[ir+1]){
                            subrho[ir]+=tr_pt ;
                        }
                        if(dr2<=rbin[ir+1]) {
                            subpsi[ir]+=tr_pt ;
                        }                      
                    } //JS histogram for subleading leading
                    
                } //track inside the second jet
                else {
                    bkgsub_dr = TMath::Sqrt((tr_phi-bkg_subphi)*(tr_phi-bkg_subphi)+(tr_eta-bkg_subeta)*(tr_eta-bkg_subeta));
                    bkg_dr = TMath::Sqrt((tr_phi-bkg_phi)*(tr_phi-bkg_phi)+(tr_eta-bkg_eta)*(tr_eta-bkg_eta));
             //       my_hists->JetBkgTrackDphi[curr_bin]->Fill(lead_pt,TMath::Abs(jtrdphi), weight);
                    if(bkgsub_dr<=conesize) {
                        bkgsumsubpt+=tr_pt;
                        my_hists->JetBkgTrackDphi[curr_bin]->Fill(lead_pt,TMath::Abs(jtrdphi), weight);
                        my_hists->JetBkgTrackDeta[curr_bin]->Fill(lead_pt,tr_eta-jet_eta, weight);
                        for(int ir = 0 ; ir <nrbin; ir++){
                            if(bkgsub_dr>rbin[ir]&&bkgsub_dr<=rbin[ir+1])
                                bkgsubrho[ir]+=tr_pt ;
                            if(bkgsub_dr<=rbin[ir+1]) {
                                bkgsubpsi[ir]+=tr_pt ;
                            }
                        }  
                    } //track inside subject background cone  
                    if(bkg_dr<=conesize){
                        bkgsumpt+=tr_pt ;
                        my_hists->bkgtrackpt[curr_bin]->Fill(lead_pt, tr_pt, weight);
                        my_hists->JetBkgTrackDphi[curr_bin]->Fill(lead_pt,TMath::Abs(jtrdphi), weight);
                        my_hists->JetBkgTrackDeta[curr_bin]->Fill(lead_pt,tr_eta-jet_eta, weight);
                        for(int ir = 0 ; ir <nrbin; ir++){
                            if(bkg_dr>rbin[ir]&&bkg_dr<=rbin[ir+1]){
                                bkgrho[ir]+=tr_pt ;
                                my_hists->bkgChargePt[curr_bin][ir]->Fill(lead_pt, tr_pt, weight);
                                bkgsumchpt[ir]+=tr_pt ;
                                bkgcharge[ir]++ ;  
                            }
                            if(bkg_dr<=rbin[ir+1]) {
                                bkgpsi[ir]+=tr_pt ;                                       
                            } //fill bkg subleading JS
                        } //radius loop to fill bkg JS histos 
                    }  //bkg cone for leading       

                } //outside subleading and leading                
            } //outside leading jet cone
            
        } //track loop
        
        //  if(sumpt==0) cout<<"evt ="<<evi <<"jet pt =" <<lead_pt<<" without tracks" <<endl ;
        my_hists->SumptJetPt[curr_bin]->Fill(lead_pt,sumpt/lead_pt, weight);
        
        if(sumpt==0.) continue ;
        //   if(bkgsumpt>=sumpt || bkgsumsubpt>=sumsubpt) continue ;
        meanphi/=sumpt;
        meaneta/=sumpt;
        //  if(sumpt/lead_pt<0.3) continue ;
        // rho/=deltacone ;
        for(int ir = 0 ; ir <nrbin; ir++){
            //  if(ir==nrbin-1)cout<<"psi="<<psi[ir]<<"sum ="<<sumpt<<endl;
            //  if(rho[ir]==sumpt&&ir>0) cout<<"!!!!!!!!!evt ="<<evi<<" ir="<<ir<<"sum ="<<sumpt<<"psi ="<<psi[ir]<<"psi[ir-1] ="<<psi[ir-1] <<" rho ="<<rho[ir-1]<<" sumpt/jetpt ="<<sumpt/lead_pt<<endl;
            //  if(rho[ir]==sumpt&&ir>0) continue ;
            psi[ir]/=sumpt;
            rho[ir]/=sumpt;
            bkgpsi[ir]/=sumpt;
            bkgrho[ir]/=sumpt;
            sumchpt[ir]/=sumpt ;
            bkgsumchpt[ir]/=sumpt ;
            //  cout<<"evt ="<<evi<<" ir="<<ir<<"jet pt =" <<lead_pt<<"sum ="<<sumpt<<" rho ="<<rho[ir]<<" psi ="<<psi[ir] <<endl;
            //   if(bkgcharge[ir])cout<<"evt ="<<evi<<" ir="<<ir<<"mult ="<<charge[ir]<<"sumch ="<<sumchpt[ir] <<" bkg mult ="<<bkgcharge[ir]<<"bkgsumch ="<<bkgsumchpt[ir]<<endl;
            //   if(ir>0) cout<<"evt ="<<evi<<" ir="<<ir<< "jet pt =" <<lead_pt << " rho =" <<rho[ir]<< " psi - ="<<psi[ir]-psi[ir-1]<<endl ;
            
            my_hists->ChargeMult[curr_bin][ir]->Fill(lead_pt, charge[ir], weight);
            my_hists->SumChPt[curr_bin][ir]->Fill(lead_pt, sumchpt[ir],weight); 
            my_hists->bkgChargeMult[curr_bin][ir]->Fill(lead_pt, bkgcharge[ir],weight);
            my_hists->bkgSumChPt[curr_bin][ir]->Fill(lead_pt, bkgsumchpt[ir],weight); 
            my_hists->DiffJS[curr_bin][ir]->Fill(lead_pt, rho[ir],weight);
            my_hists->IntJS[curr_bin][ir]->Fill(lead_pt, psi[ir],weight);
            // rho/=deltacone ;
            my_hists->bkgDiffJS[curr_bin][ir]->Fill(lead_pt, bkgrho[ir],weight);
            //   my_hists->IntJS[curr_bin]->Fill(lead_pt, 1-psi);
            my_hists->bkgIntJS[curr_bin][ir]->Fill(lead_pt, bkgpsi[ir],weight);
 
            if(lead_pt>=80 &&lead_pt<100)             
                my_hists->DiffJSPt80_100[curr_bin][ir]->Fill(rho[ir]);
            if(dEtaBin!=-1){
                my_hists->DiffEtaBinJS[curr_bin][ir][dEtaBin]->Fill(lead_pt, rho[ir],weight);
                my_hists->bkgDiffEtaBinJS[curr_bin][ir][dEtaBin]->Fill(lead_pt, bkgrho[ir],weight);
            }
        }
            if(ptBin!=-1){
                if(sumsubpt==0.) continue ;
                for(int ir = 0 ; ir <nrbin; ir++){
                    subpsi[ir]/=sumsubpt;
                    subrho[ir]/=sumsubpt;
                    bkgsubpsi[ir]/=sumsubpt;
                    bkgsubrho[ir]/=sumsubpt;

                    my_hists->subDiffJS[curr_bin][ir][ptBin]->Fill(sublead_pt, subrho[ir],weight);
                    my_hists->subIntJS[curr_bin][ir][ptBin]->Fill(sublead_pt, subpsi[ir],weight);
                    my_hists->bkgsubDiffJS[curr_bin][ir][ptBin]->Fill(sublead_pt, bkgsubrho[ir],weight);
                    my_hists->bkgsubIntJS[curr_bin][ir][ptBin]->Fill(sublead_pt, bkgsubpsi[ir],weight);   
            }
//            if(AjBin!=-1)my_hists->subDiffAjbin[curr_bin][ir][AjBin]->Fill(sublead_pt, subrho[ir],weight);
//            if(AjBin!=-1)my_hists->bkgsubDiffAjbin[curr_bin][ir][AjBin]->Fill(sublead_pt, bkgsubrho[ir],weight);

            //    cout <<"ievt =" <<evi <<" leading index =" <<lead_index << " pt =" <<lead_pt <<" sumpt ="<<sumpt <<" rho = "<<rho[ir] << " psi =" <<psi[ir]<<endl ;
            
        }
        if(njets)my_hists->NJets[curr_bin]->Fill(my_ct->fChain->GetEntry(evi),weight);
        
        if(coll=="HI"){
            offSel->fChain->GetEntry(evi); 
            my_hists->CenBin->Fill(offSel->hiBin,weight);
        }
        
        
        if(my_hists->IsMC==kTRUE&&DoGenAna){  
//            if(TMath::Abs(genjet_eta)<0.3) continue ;            
//            if(TMath::Abs(gensubjet_eta) < 0.3) continue ;                

            if(etalimit==etacut){ //for Random Cone method 
                //cout <<"Using random cone Bkg method!"<<endl ;
                if(genjet_eta<0.) genbkg_eta = genjet_eta+genbkgetacut;
                else genbkg_eta = genjet_eta-genbkgetacut;
                if(genjet_phi<0.)genbkg_phi = genjet_phi+genbkgphicut;
                else genbkg_phi = genjet_phi-genbkgphicut;
                if(gensubjet_eta<0.) genbkg_subeta = gensubjet_eta+genbkgetacut;
                else genbkg_subeta = gensubjet_eta-genbkgetacut;
                if(gensubjet_phi<0.)genbkg_subphi = gensubjet_phi+genbkgphicut;
                else genbkg_subphi = gensubjet_phi-genbkgphicut;
            }            
            else { //Eta reflected method 
                if(TMath::Abs(genjet_eta)<0.3) continue ;            
                if(TMath::Abs(gensubjet_eta) < 0.3) continue ;                
                genbkg_phi = genjet_phi;
                genbkg_eta = -genjet_eta;
                genbkg_subphi = gensubjet_phi ;
                genbkg_subeta = -gensubjet_eta ;
            }
            
            
            int gencharge[nrbin] ;
            double gensumchpt[nrbin];
            double genrho[nrbin] ;
            double genpsi[nrbin] ;
            double gensubrho[nrbin] ;
            double gensubpsi[nrbin] ;
            double gensumpt = 0. ;
            double gensumsubpt = 0. ;            
            int genbkgcharge[nrbin] ;
            double genbkgsumchpt[nrbin]  ;
            double genbkgrho[nrbin];
            double genbkgpsi[nrbin] ;
            double genbkgsubrho[nrbin] ;
            double genbkgsubpsi[nrbin] ;
            double genbkgsumpt = 0. ;
            double genbkgsumsubpt = 0. ;
            for(int ir = 0 ; ir <nrbin ; ir++){
                gencharge[ir]=0;
                gensumchpt[ir]=0. ;
                genrho[ir]=0. ;
                genpsi[ir]= 0.;
                gensubrho[ir]=0.;
                gensubpsi[ir]=0.;
                genbkgcharge[ir]=0 ;
                genbkgsumchpt[ir]=0. ;
                genbkgrho[ir]=0.;
                genbkgpsi[ir]=0. ;
                genbkgsubrho[ir]=0.;
                genbkgsubpsi[ir]=0.;
            }
            for(int ipart = 0 ; ipart < my_GenPart->mult ; ipart++){
                double gen_pt = my_GenPart->pt[ipart];
                double gen_phi = my_GenPart->phi[ipart];
                double gen_eta = my_GenPart->eta[ipart];
                // if(TMath::Abs(gen_eta)>tracketacut) continue ;
                if(gen_pt<trackcut) continue ;
                double gendr =TMath::Sqrt((gen_phi-genjet_phi)*(gen_phi-genjet_phi)+(gen_eta-genjet_eta)*(gen_eta-genjet_eta));
                double gendr2 =TMath::Sqrt((gen_phi-gensubjet_phi)*(gen_phi-gensubjet_phi)+(gen_eta-gensubjet_eta)*(gen_eta-gensubjet_eta));
                if(gendr<=conesize && gendr2<=conesize) {
                    cout <<"!!!! two jets are overlap with gen particle: "<<ipart <<"eta: " <<gen_eta <<" phi:" <<gen_phi << endl;
                    continue ;
                }       
                if(gendr <=conesize){
                    gensumpt+=gen_pt ;
                    my_hists->genpartpt[curr_bin]->Fill(genjet_pt,gen_pt, weight);
                    my_hists->genpartphi[curr_bin]->Fill(genjet_pt,gen_phi, weight);
                    my_hists->genparteta[curr_bin]->Fill(genjet_pt,gen_eta, weight);
                    for(int ir = 0 ; ir <nrbin ; ir++){
                        if(gendr>rbin[ir]&&gendr<=rbin[ir+1]){
                            genrho[ir]+=gen_pt ;
                            my_hists->genChargePt[curr_bin][ir]->Fill(genjet_pt, gen_pt, weight);
                            gensumchpt[ir]+=gen_pt ;
                            gencharge[ir]++ ;
                            
                        }
                        if(gendr<=rbin[ir+1]) {
                            genpsi[ir]+=gen_pt ; 
                        }
                    }  //radius loop

                } //tracks inside for jet
                else {
                    if(gendr2<=conesize) {
                        gensumsubpt+=gen_pt;
                        for(int ir = 0 ; ir <nrbin ; ir++){
                            if(gendr2>rbin[ir]&&gendr2<=rbin[ir+1])
                                gensubrho[ir]+=gen_pt ;
                            if(gendr2<=rbin[ir+1]) {
                                gensubpsi[ir]+=gen_pt ;
                            }                        
                            
                        }  //radius loop
                    } //track inside the second jet
                    else{
                        double genbkg_dr = TMath::Sqrt((gen_phi-genbkg_phi)*(gen_phi-genbkg_phi)+(gen_eta-genbkg_eta)*(gen_eta-genbkg_eta));  
                        double genbkgsub_dr = TMath::Sqrt((gen_phi-genbkg_subphi)*(gen_phi-genbkg_subphi)+(gen_eta-genbkg_subeta)*(gen_eta-genbkg_subeta)); 
                        if(genbkg_dr<=conesize){
                            genbkgsumpt+=gen_pt ;
                            my_hists->bkgpartpt[curr_bin]->Fill(genjet_pt,gen_pt, weight);
                            my_hists->bkgparteta[curr_bin]->Fill(gen_pt,gen_eta, weight);
                            for(int ir = 0 ; ir <nrbin ; ir++){
                                if(genbkg_dr>rbin[ir]&&genbkg_dr<=rbin[ir+1]){
                                    genbkgrho[ir]+=gen_pt ;
                                    my_hists->genbkgChargePt[curr_bin][ir]->Fill(genjet_pt, gen_pt, weight);
                                    genbkgsumchpt[ir]+=gen_pt ;
                                    genbkgcharge[ir]++ ;   
                                }
                                if(genbkg_dr<=rbin[ir+1]) {
                                    genbkgpsi[ir]+=gen_pt ;
                                }
                            }  //radius loop for JS calculation

                        }  // inside bkg cone   
                        if(genbkgsub_dr<=conesize) {
                            genbkgsumsubpt+=gen_pt;
                            for(int ir = 0 ; ir <nrbin ; ir++){
                                if(genbkgsub_dr>rbin[ir]&&genbkgsub_dr<=rbin[ir+1])
                                    genbkgsubrho[ir]+=gen_pt ;
                                if(genbkgsub_dr<=rbin[ir+1]) {
                                    genbkgsubpsi[ir]+=gen_pt ;
                                }                                
                            } //radius loop for sub bkg JS calculation
    
                        } //track inside subject background cone

                    }  //outside both leading and subleading jet
                    
                } //outside leading jet
            } //gen particle loop     
            if(gensumpt==0) continue ;
            //    if(genbkgsumpt>=gensumpt || genbkgsumsubpt>=gensumsubpt) continue ;
            for(int ir = 0 ; ir <nrbin; ir++){            
                genpsi[ir]/=gensumpt;
                genrho[ir]/=gensumpt;
                genbkgpsi[ir]/=gensumpt;
                genbkgrho[ir]/=gensumpt;
                gensumchpt[ir]/=gensumpt ;
                genbkgsumchpt[ir]/=gensumpt ;
                my_hists->genChargeMult[curr_bin][ir]->Fill(genjet_pt, gencharge[ir], weight);
                my_hists->genSumChPt[curr_bin][ir]->Fill(genjet_pt, gensumchpt[ir],weight); 
                my_hists->genbkgChargeMult[curr_bin][ir]->Fill(genjet_pt, genbkgcharge[ir],weight);
                my_hists->genbkgSumChPt[curr_bin][ir]->Fill(genjet_pt, genbkgsumchpt[ir],weight); 

                //       cout<<"evt ="<<evi<< " ir ="<<ir << " gen rho =" <<genrho[ir]<< " gen psi ="<<genpsi[ir] <<endl ;
                
                //                if(ir==0){
                //                    genrho[ir]=genpsi[ir];
                //                    gensubrho[ir]=gensubpsi[ir];
                //                    genbkgrho[ir]=genbkgpsi[ir];
                //                    genbkgsubrho[ir]=genbkgpsi[ir];
                //                }
                //                else {
                //                    genrho[ir]=genpsi[ir]-genpsi[ir-1];
                //                    gensubrho[ir]=gensubpsi[ir]-gensubpsi[ir-1];
                //                    genbkgrho[ir]=genbkgpsi[ir]-genbkgpsi[ir-1];
                //                    genbkgsubrho[ir]=genbkgpsi[ir]-genbkgsubpsi[ir-1];
                //
                //                }
                //      cout<<"evt ="<<evi<< " ir ="<<ir << " gen rho =" <<genrho[ir]<< " gen psi ="<<genpsi[ir] <<endl ;
                //        if(ir>0 && genrho[ir]==1) cout<<"evt ="<<evi<<" ir-1="<<ir-1 << "gen jet pt =" <<genjet_pt << " gen rho[ir-1] =" <<genrho[ir-1]<< " gen rho[ir] ="<<genpsi[ir]-genpsi[ir-1] <<"sum =" <<gensumpt<<endl ;
                //  if(ir>0) cout<<"evt ="<<evi<<" ir="<<ir << "gen jet pt =" <<genjet_pt << " gen rho =" <<genrho[ir]<< " gen psi - ="<<genpsi[ir]-genpsi[ir-1]<<endl ;
                my_hists->genDiffJS[curr_bin][ir]->Fill(genjet_pt, genrho[ir],weight);
                my_hists->genIntJS[curr_bin][ir]->Fill(genjet_pt, genpsi[ir],weight);
                // rho/=deltacone ;
                my_hists->genbkgDiffJS[curr_bin][ir]->Fill(genjet_pt, genbkgrho[ir],weight);
                //   my_hists->IntJS[curr_bin]->Fill(lead_pt, 1-psi);
                my_hists->genbkgIntJS[curr_bin][ir]->Fill(genjet_pt, genbkgpsi[ir],weight);
            }  //radius loop in order to fill jet shape histograms
            
              //fill subleading jet JS
                if(genptBin!=-1){
                    if(gensumsubpt==0) continue ;
                    for(int ir = 0 ; ir <nrbin; ir++){   
                        gensubpsi[ir]/=gensumsubpt;
                        gensubrho[ir]/=gensumsubpt;
                        genbkgsubpsi[ir]/=gensumsubpt;
                        genbkgsubrho[ir]/=gensumsubpt;
                  //  for(Int_t ipt = 0; ipt <nptbin ; ipt++){
                        my_hists->gensubDiffJS[curr_bin][ir][genptBin]->Fill(gensubjet_pt, gensubrho[ir],weight);
                        my_hists->gensubIntJS[curr_bin][ir][genptBin]->Fill(gensubjet_pt, gensubpsi[ir],weight);
                        my_hists->genbkgsubDiffJS[curr_bin][ir][genptBin]->Fill(gensubjet_pt, genbkgsubrho[ir],weight);
                        my_hists->genbkgsubIntJS[curr_bin][ir][genptBin]->Fill(gensubjet_pt, genbkgsubpsi[ir],weight);   
                //    } //end of jet pt bins 
                } //radius loop in order to fill jet shape histograms
            }  //radius loop in order to fill jet shape histograms
            
        } //if it is MC
        
    }  ///event loop
    
    my_hists->Write();
    // my_hists->Delete();
    delete my_hists;
    std::cout << "working done\n";
}




